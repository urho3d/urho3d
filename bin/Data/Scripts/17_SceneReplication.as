// Scene network replication example.
// This sample demonstrates:
//     - Creating a scene in which network clients can join
//     - Giving each client an object to control and sending the controls from the clients to the server,
//       where the authoritative simulation happens
//     - Controlling a physics object's movement by applying forces

#include "Scripts/Utilities/Sample.as"

// UDP port we will use
const uint SERVER_PORT = 2345;

// Control bits we define
const uint CTRL_FORWARD = 1;
const uint CTRL_BACK = 2;
const uint CTRL_LEFT = 4;
const uint CTRL_RIGHT = 8;

// Record for each connected client
class Client
{
    Connection@ connection;
    Node@ object;
}

Text@ instructionsText;
UIElement@ buttonContainer;
LineEdit@ textEdit;
Button@ connectButton;
Button@ disconnectButton;
Button@ startServerButton;
Array<Client> clients;
uint clientObjectID = 0;

void Start()
{
    // Execute the common startup for samples
    SampleStart();

    // Create the scene content
    CreateScene();

    // Create the UI content
    CreateUI();

    // Setup the viewport for displaying the scene
    SetupViewport();

    // Set the mouse mode to use in the sample
    SampleInitMouseMode(MM_RELATIVE);

    // Hook up to necessary events
    SubscribeToEvents();
}

void CreateScene()
{
    scene_ = Scene();

    // Create octree and physics world with default settings. Create them as local so that they are not needlessly replicated
    // when a client connects
    scene_.CreateComponent("Octree", LOCAL);
    scene_.CreateComponent("PhysicsWorld", LOCAL);

    // All static scene content and the camera are also created as local, so that they are unaffected by scene replication and are
    // not removed from the client upon connection. Create a Zone component first for ambient lighting & fog control.
    Node@ zoneNode = scene_.CreateChild("Zone", LOCAL);
    Zone@ zone = zoneNode.CreateComponent("Zone");
    zone.boundingBox = BoundingBox(-1000.0f, 1000.0f);
    zone.ambientColor = Color(0.1f, 0.1f, 0.1f);
    zone.fogStart = 100.0f;
    zone.fogEnd = 300.0f;

    // Create a directional light without shadows
    Node@ lightNode = scene_.CreateChild("DirectionalLight", LOCAL);
    lightNode.direction = Vector3(0.5f, -1.0f, 0.5f);
    Light@ light = lightNode.CreateComponent("Light");
    light.lightType = LIGHT_DIRECTIONAL;
    light.color = Color(0.2f, 0.2f, 0.2f);
    light.specularIntensity = 1.0f;

    // Create a "floor" consisting of several tiles. Make the tiles physical but leave small cracks between them
    for (int y = -20; y <= 20; ++y)
    {
        for (int x = -20; x <= 20; ++x)
        {
            Node@ floorNode = scene_.CreateChild("FloorTile", LOCAL);
            floorNode.position = Vector3(x * 20.2f, -0.5f, y * 20.2f);
            floorNode.scale = Vector3(20.0f, 1.0f, 20.0f);
            StaticModel@ floorObject = floorNode.CreateComponent("StaticModel");
            floorObject.model = cache.GetResource("Model", "Models/Box.mdl");
            floorObject.material = cache.GetResource("Material", "Materials/Stone.xml");

            RigidBody@ body = floorNode.CreateComponent("RigidBody");
            body.friction = 1.0f;
            CollisionShape@ shape = floorNode.CreateComponent("CollisionShape");
            shape.SetBox(Vector3(1.0f, 1.0f, 1.0f));
        }
    }

    // Create the camera. Limit far clip distance to match the fog
    // The camera needs to be created into a local node so that each client can retain its own camera, that is unaffected by
    // network messages. Furthermore, because the client removes all replicated scene nodes when connecting to a server scene,
    // the screen would become blank if the camera node was replicated (as only the locally created camera is assigned to a
    // viewport in SetupViewports() below)
    cameraNode = scene_.CreateChild("Camera", LOCAL);
    Camera@ camera = cameraNode.CreateComponent("Camera");
    camera.farClip = 300.0f;

    // Set an initial position for the camera scene node above the plane
    cameraNode.position = Vector3(0.0f, 5.0f, 0.0f);
}

void CreateUI()
{
    XMLFile@ uiStyle = cache.GetResource("XMLFile", "UI/DefaultStyle.xml");
    // Set style to the UI root so that elements will inherit it
    ui.root.defaultStyle = uiStyle;

    // Create a Cursor UI element because we want to be able to hide and show it at will. When hidden, the mouse cursor will
    // control the camera, and when visible, it will point the raycast target
    Cursor@ cursor = Cursor();
    cursor.SetStyleAuto(uiStyle);
    ui.cursor = cursor;
    // Set starting position of the cursor at the rendering window center
    cursor.SetPosition(graphics.width / 2, graphics.height / 2);

    // Construct the instructions text element
    instructionsText = ui.root.CreateChild("Text");
    instructionsText.text = "Use WASD keys to move and RMB to rotate view";
    instructionsText.SetFont(cache.GetResource("Font", "Fonts/Anonymous Pro.ttf"), 15);
    // Position the text relative to the screen center
    instructionsText.horizontalAlignment = HA_CENTER;
    instructionsText.verticalAlignment = VA_CENTER;
    instructionsText.SetPosition(0, graphics.height / 4);
    // Hide until connected
    instructionsText.visible = false;

    buttonContainer = ui.root.CreateChild("UIElement");
    buttonContainer.SetFixedSize(500, 20);
    buttonContainer.SetPosition(20, 20);
    buttonContainer.layoutMode = LM_HORIZONTAL;

    textEdit = buttonContainer.CreateChild("LineEdit");
    textEdit.SetStyleAuto();

    connectButton = CreateButton("Connect", 90);
    disconnectButton = CreateButton("Disconnect", 100);
    startServerButton = CreateButton("Start Server", 110);

    UpdateButtons();
}

void SetupViewport()
{
    // Set up a viewport to the Renderer subsystem so that the 3D scene can be seen
    Viewport@ viewport = Viewport(scene_, cameraNode.GetComponent("Camera"));
    renderer.viewports[0] = viewport;
}

void SubscribeToEvents()
{
    // Subscribe to fixed timestep physics updates for setting or applying controls
    SubscribeToEvent("PhysicsPreStep", "HandlePhysicsPreStep");

    // Subscribe HandlePostUpdate() method for processing update events. Subscribe to PostUpdate instead
    // of the usual Update so that physics simulation has already proceeded for the frame, and can
    // accurately follow the object with the camera
    SubscribeToEvent("PostUpdate", "HandlePostUpdate");

    // Subscribe to button actions
    SubscribeToEvent(connectButton, "Released", "HandleConnect");
    SubscribeToEvent(disconnectButton, "Released", "HandleDisconnect");
    SubscribeToEvent(startServerButton, "Released", "HandleStartServer");

    // Subscribe to network events
    SubscribeToEvent("ServerConnected", "HandleConnectionStatus");
    SubscribeToEvent("ServerDisconnected", "HandleConnectionStatus");
    SubscribeToEvent("ConnectFailed", "HandleConnectionStatus");
    SubscribeToEvent("ClientConnected", "HandleClientConnected");
    SubscribeToEvent("ClientDisconnected", "HandleClientDisconnected");
    // This is a custom event, sent from the server to the client. It tells the node ID of the object the client should control
    SubscribeToEvent("ClientObjectID", "HandleClientObjectID");
    // Events sent between client & server (remote events) must be explicitly registered or else they are not allowed to be received
    network.RegisterRemoteEvent("ClientObjectID");
}

Button@ CreateButton(const String& text, int width)
{
    Font@ font = cache.GetResource("Font", "Fonts/Anonymous Pro.ttf");

    Button@ button = buttonContainer.CreateChild("Button");
    button.SetStyleAuto();
    button.SetFixedWidth(width);

    Text@ buttonText = button.CreateChild("Text");
    buttonText.SetFont(font, 12);
    buttonText.SetAlignment(HA_CENTER, VA_CENTER);
    buttonText.text = text;

    return button;
}

void UpdateButtons()
{
    Connection@ serverConnection = network.serverConnection;
    bool serverRunning = network.serverRunning;

    // Show and hide buttons so that eg. Connect and Disconnect are never shown at the same time
    connectButton.visible = serverConnection is null && !serverRunning;
    disconnectButton.visible = serverConnection !is null || serverRunning;
    startServerButton.visible = serverConnection is null && !serverRunning;
    textEdit.visible = serverConnection is null && !serverRunning;
}

Node@ CreateControllableObject()
{
    // Create the scene node & visual representation. This will be a replicated object
    Node@ ballNode = scene_.CreateChild("Ball");
    ballNode.position = Vector3(Random(40.0f) - 20.0f, 5.0f, Random(40.0f) - 20.0f);
    ballNode.SetScale(0.5f);
    StaticModel@ ballObject = ballNode.CreateComponent("StaticModel");
    ballObject.model = cache.GetResource("Model", "Models/Sphere.mdl");
    ballObject.material = cache.GetResource("Material", "Materials/StoneSmall.xml");

    // Create the physics components
    RigidBody@ body = ballNode.CreateComponent("RigidBody");
    body.mass = 1.0f;
    body.friction = 1.0f;
    // In addition to friction, use motion damping so that the ball can not accelerate limitlessly
    body.linearDamping = 0.5f;
    body.angularDamping = 0.5f;
    CollisionShape@ shape = ballNode.CreateComponent("CollisionShape");
    shape.SetSphere(1.0f);

    // Create a random colored point light at the ball so that can see better where is going
    Light@ light = ballNode.CreateComponent("Light");
    light.range = 3.0f;
    light.color = Color(0.5f + (RandomInt() & 1) * 0.5f, 0.5f + (RandomInt() & 1) * 0.5f, 0.5f + (RandomInt() & 1) * 0.5f);

    return ballNode;
}

void MoveCamera()
{
    input.mouseVisible = input.mouseMode != MM_RELATIVE;
    bool mouseDown = input.mouseButtonDown[MOUSEB_RIGHT];

    // Override the MM_RELATIVE mouse grabbed settings, to allow interaction with UI
    input.mouseGrabbed = mouseDown;

    // Right mouse button controls mouse cursor visibility: hide when pressed
    ui.cursor.visible = !mouseDown;

    // Mouse sensitivity as degrees per pixel
    const float MOUSE_SENSITIVITY = 0.1f;

    // Use this frame's mouse motion to adjust camera node yaw and pitch. Clamp the pitch and only move the camera
    // when the cursor is hidden
    if (!ui.cursor.visible)
    {
        IntVector2 mouseMove = input.mouseMove;
        yaw += MOUSE_SENSITIVITY * mouseMove.x;
        pitch += MOUSE_SENSITIVITY * mouseMove.y;
        pitch = Clamp(pitch, 1.0f, 90.0f);
    }

    // Construct new orientation for the camera scene node from yaw and pitch. Roll is fixed to zero
    cameraNode.rotation = Quaternion(pitch, yaw, 0.0f);

    // Only move the camera / show instructions if we have a controllable object
    bool showInstructions = false;
    if (clientObjectID != 0)
    {
        Node@ ballNode = scene_.GetNode(clientObjectID);
        if (ballNode !is null)
        {
            const float CAMERA_DISTANCE = 5.0f;

            // Move camera some distance away from the ball
            cameraNode.position = ballNode.position + cameraNode.rotation * Vector3(0.0f, 0.0f, -1.0f) * CAMERA_DISTANCE;
            showInstructions = true;
        }
    }

    instructionsText.visible = showInstructions;
}

void HandlePostUpdate(StringHash eventType, VariantMap& eventData)
{
    // We only rotate the camera according to mouse movement since last frame, so do not need the time step
    MoveCamera();
}

void HandlePhysicsPreStep(StringHash eventType, VariantMap& eventData)
{
    // This function is different on the client and server. The client collects controls (WASD controls + yaw angle)
    // and sets them to its server connection object, so that they will be sent to the server automatically at a
    // fixed rate, by default 30 FPS. The server will actually apply the controls (authoritative simulation.)
    Connection@ serverConnection = network.serverConnection;

    // Client: collect controls
    if (serverConnection !is null)
    {
        Controls controls;

        // Copy mouse yaw
        controls.yaw = yaw;

        // Only apply WASD controls if there is no focused UI element
        if (ui.focusElement is null)
        {
            controls.Set(CTRL_FORWARD, input.keyDown['W']);
            controls.Set(CTRL_BACK, input.keyDown['S']);
            controls.Set(CTRL_LEFT, input.keyDown['A']);
            controls.Set(CTRL_RIGHT, input.keyDown['D']);
        }

        serverConnection.controls = controls;
        // In case the server wants to do position-based interest management using the NetworkPriority components, we should also
        // tell it our observer (camera) position. In this sample it is not in use, but eg. the NinjaSnowWar game uses it
        serverConnection.position = cameraNode.position;
    }
    // Server: apply controls to client objects
    else if (network.serverRunning)
    {
        for (uint i = 0; i < clients.length; ++i)
        {
            Connection@ connection = clients[i].connection;
            // Get the object this connection is controlling
            Node@ ballNode = clients[i].object;

            RigidBody@ body = ballNode.GetComponent("RigidBody");

            // Torque is relative to the forward vector
            Quaternion rotation(0.0f, connection.controls.yaw, 0.0f);

            const float MOVE_TORQUE = 3.0f;

            // Movement torque is applied before each simulation step, which happen at 60 FPS. This makes the simulation
            // independent from rendering framerate. We could also apply forces (which would enable in-air control),
            // but want to emphasize that it's a ball which should only control its motion by rolling along the ground
            if (connection.controls.IsDown(CTRL_FORWARD))
                body.ApplyTorque(rotation * Vector3(1.0f, 0.0f, 0.0f) * MOVE_TORQUE);
            if (connection.controls.IsDown(CTRL_BACK))
                body.ApplyTorque(rotation * Vector3(-1.0f, 0.0f, 0.0f) * MOVE_TORQUE);
            if (connection.controls.IsDown(CTRL_LEFT))
                body.ApplyTorque(rotation * Vector3(0.0f, 0.0f, 1.0f) * MOVE_TORQUE);
            if (connection.controls.IsDown(CTRL_RIGHT))
                body.ApplyTorque(rotation * Vector3(0.0f, 0.0f, -1.0f) * MOVE_TORQUE);
        }
    }
}

void HandleConnect(StringHash eventType, VariantMap& eventData)
{
    String address = textEdit.text.Trimmed();
    if (address.empty)
        address = "localhost"; // Use localhost to connect if nothing else specified

    // Connect to server, specify scene to use as a client for replication
    clientObjectID = 0; // Reset own object ID from possible previous connection
    network.Connect(address, SERVER_PORT, scene_);

    UpdateButtons();
}

void HandleDisconnect(StringHash eventType, VariantMap& eventData)
{
    Connection@ serverConnection = network.serverConnection;
    // If we were connected to server, disconnect. Or if we were running a server, stop it. In both cases clear the
    // scene of all replicated content, but let the local nodes & components (the static world + camera) stay
    if (serverConnection !is null)
    {
        serverConnection.Disconnect();
        scene_.Clear(true, false);
        clientObjectID = 0;
    }
    // Or if we were running a server, stop it
    else if (network.serverRunning)
    {
        network.StopServer();
        scene_.Clear(true, false);
    }

    UpdateButtons();
}

void HandleStartServer(StringHash eventType, VariantMap& eventData)
{
    network.StartServer(SERVER_PORT);

    UpdateButtons();
}

void HandleConnectionStatus(StringHash eventType, VariantMap& eventData)
{
    UpdateButtons();
}

void HandleClientConnected(StringHash eventType, VariantMap& eventData)
{
    // When a client connects, assign to scene to begin scene replication
    Connection@ newConnection = eventData["Connection"].GetPtr();
    newConnection.scene = scene_;

    // Then create a controllable object for that client
    Node@ newObject = CreateControllableObject();
    Client newClient;
    newClient.connection = newConnection;
    newClient.object = newObject;
    clients.Push(newClient);

    // Finally send the object's node ID using a remote event
    VariantMap remoteEventData;
    remoteEventData["ID"] = newObject.id;
    newConnection.SendRemoteEvent("ClientObjectID", true, remoteEventData);
}

void HandleClientDisconnected(StringHash eventType, VariantMap& eventData)
{
    // When a client disconnects, remove the controlled object
    Connection@ connection = eventData["Connection"].GetPtr();
    for (uint i = 0; i < clients.length; ++i)
    {
        if (clients[i].connection is connection)
        {
            clients[i].object.Remove();
            clients.Erase(i);
            break;
        }
    }
}

void HandleClientObjectID(StringHash eventType, VariantMap& eventData)
{
    clientObjectID = eventData["ID"].GetUInt();
}

// Create XML patch instructions for screen joystick layout specific to this sample app
String patchInstructions =
        "<patch>" +
        "    <add sel=\"/element/element[./attribute[@name='Name' and @value='Hat0']]\">" +
        "        <attribute name=\"Is Visible\" value=\"false\" />" +
        "    </add>" +
        "</patch>";
