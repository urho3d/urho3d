// Physics stress test example.
// This sample demonstrates:
//     - Physics and rendering performance with a high (1000) moving object count
//     - Using triangle meshes for collision
//     - Optimizing physics simulation by leaving out collision event signaling

#include "Scripts/Utilities/Sample.as"

void Start()
{
    // Execute the common startup for samples
    SampleStart();

    // Create the scene content
    CreateScene();

    // Create the UI content
    CreateInstructions();

    // Setup the viewport for displaying the scene
    SetupViewport();

    // Hook up to the frame update and render post-update events
    SubscribeToEvents();
}

void CreateScene()
{
    scene_ = Scene();

    // Create octree, use default volume (-1000, -1000, -1000) to (1000, 1000, 1000)
    // Create a physics simulation world with default parameters, which will update at 60fps. Like the Octree must
    // exist before creating drawable components, the PhysicsWorld must exist before creating physics components.
    // Finally, create a DebugRenderer component so that we can draw physics debug geometry
    scene_.CreateComponent("Octree");
    scene_.CreateComponent("PhysicsWorld");
    scene_.CreateComponent("DebugRenderer");

    // Create a Zone component for ambient lighting & fog control
    Node@ zoneNode = scene_.CreateChild("Zone");
    Zone@ zone = zoneNode.CreateComponent("Zone");
    zone.boundingBox = BoundingBox(-1000.0f, 1000.0f);
    zone.ambientColor = Color(0.15f, 0.15f, 0.15f);
    zone.fogColor = Color(0.5f, 0.5f, 0.7f);
    zone.fogStart = 100.0f;
    zone.fogEnd = 300.0f;

    // Create a directional light to the world. Enable cascaded shadows on it
    Node@ lightNode = scene_.CreateChild("DirectionalLight");
    lightNode.direction = Vector3(0.6f, -1.0f, 0.8f);
    Light@ light = lightNode.CreateComponent("Light");
    light.lightType = LIGHT_DIRECTIONAL;
    light.castShadows = true;
    light.shadowBias = BiasParameters(0.00025f, 0.5f);
    // Set cascade splits at 10, 50 and 200 world units, fade shadows out at 80% of maximum shadow distance
    light.shadowCascade = CascadeParameters(10.0f, 50.0f, 200.0f, 0.0f, 0.8f);

    {
        // Create a floor object, 500 x 500 world units. Adjust position so that the ground is at zero Y
        Node@ floorNode = scene_.CreateChild("Floor");
        floorNode.position = Vector3(0.0f, -0.5f, 0.0f);
        floorNode.scale = Vector3(500.0f, 1.0f, 500.0f);
        StaticModel@ floorObject = floorNode.CreateComponent("StaticModel");
        floorObject.model = cache.GetResource("Model", "Models/Box.mdl");
        floorObject.material = cache.GetResource("Material", "Materials/StoneTiled.xml");

        // Make the floor physical by adding RigidBody and CollisionShape components
        RigidBody@ body = floorNode.CreateComponent("RigidBody");
        CollisionShape@ shape = floorNode.CreateComponent("CollisionShape");
        // Set a box shape of size 1 x 1 x 1 for collision. The shape will be scaled with the scene node scale, so the
        // rendering and physics representation sizes should match (the box model is also 1 x 1 x 1.)
        shape.SetBox(Vector3(1.0f, 1.0f, 1.0f));
    }

    {
        // Create static mushrooms with triangle mesh collision
        const uint NUM_MUSHROOMS = 50;
        for (uint i = 0; i < NUM_MUSHROOMS; ++i)
        {
            Node@ mushroomNode = scene_.CreateChild("Mushroom");
            mushroomNode.position = Vector3(Random(400.0f) - 200.0f, 0.0f, Random(400.0f) - 200.0f);
            mushroomNode.rotation = Quaternion(0.0f, Random(360.0f), 0.0f);
            mushroomNode.SetScale(5.0f + Random(5.0f));
            StaticModel@ mushroomObject = mushroomNode.CreateComponent("StaticModel");
            mushroomObject.model = cache.GetResource("Model", "Models/Mushroom.mdl");
            mushroomObject.material = cache.GetResource("Material", "Materials/Mushroom.xml");
            mushroomObject.castShadows = true;

            RigidBody@ body = mushroomNode.CreateComponent("RigidBody");
            CollisionShape@ shape = mushroomNode.CreateComponent("CollisionShape");
            // By default the highest LOD level will be used, the LOD level can be passed as an optional parameter
            shape.SetTriangleMesh(mushroomObject.model);
        }
    }

    {
        // Create a large amount of falling physics objects
        const uint NUM_OBJECTS = 1000;
        for (uint i = 0; i < NUM_OBJECTS; ++i)
        {
            Node@ boxNode = scene_.CreateChild("Box");
            boxNode.position = Vector3(0.0f, i * 2.0f + 100.0f, 0.0f);
            StaticModel@ boxObject = boxNode.CreateComponent("StaticModel");
            boxObject.model = cache.GetResource("Model", "Models/Box.mdl");
            boxObject.material = cache.GetResource("Material", "Materials/StoneSmall.xml");
            boxObject.castShadows = true;

            // Give the RigidBody mass to make it movable and also adjust friction
            RigidBody@ body = boxNode.CreateComponent("RigidBody");
            body.mass = 1.0f;
            body.friction = 1.0f;
            // Disable collision event signaling to reduce CPU load of the physics simulation
            body.collisionEventMode = COLLISION_NEVER;
            CollisionShape@ shape = boxNode.CreateComponent("CollisionShape");
            shape.SetBox(Vector3(1.0f, 1.0f, 1.0f));
        }
    }

    // Create the camera. Limit far clip distance to match the fog. Note: now we actually create the camera node outside
    // the scene, because we want it to be unaffected by scene load / save
    cameraNode = Node();
    Camera@ camera = cameraNode.CreateComponent("Camera");
    camera.farClip = 300.0f;

    // Set an initial position for the camera scene node above the floor
    cameraNode.position = Vector3(0.0f, 3.0f, -20.0f);
}

void CreateInstructions()
{
    // Construct new Text object, set string to display and font to use
    Text@ instructionText = ui.root.CreateChild("Text");
    instructionText.text =
        "Use WASD keys and mouse to move\n"
        "LMB to spawn physics objects\n"
        "F5 to save scene, F7 to load\n"
        "Space to toggle physics debug geometry";
    instructionText.SetFont(cache.GetResource("Font", "Fonts/Anonymous Pro.ttf"), 15);
    // The text has multiple rows. Center them in relation to each other
    instructionText.textAlignment = HA_CENTER;

    // Position the text relative to the screen center
    instructionText.horizontalAlignment = HA_CENTER;
    instructionText.verticalAlignment = VA_CENTER;
    instructionText.SetPosition(0, ui.root.height / 4);
}

void SetupViewport()
{
    // Set up a viewport to the Renderer subsystem so that the 3D scene can be seen
    Viewport@ viewport = Viewport(scene_, cameraNode.GetComponent("Camera"));
    renderer.viewports[0] = viewport;
}

void SubscribeToEvents()
{
    // Subscribe HandleUpdate() function for processing update events
    SubscribeToEvent("Update", "HandleUpdate");

    // Subscribe HandlePostRenderUpdate() function for processing the post-render update event, during which we request
    // debug geometry
    SubscribeToEvent("PostRenderUpdate", "HandlePostRenderUpdate");
}

void MoveCamera(float timeStep)
{
    // Do not move if the UI has a focused element (the console)
    if (ui.focusElement !is null)
        return;

    // Movement speed as world units per second
    const float MOVE_SPEED = 20.0f;
    // Mouse sensitivity as degrees per pixel
    const float MOUSE_SENSITIVITY = 0.1f;

    // Use this frame's mouse motion to adjust camera node yaw and pitch. Clamp the pitch between -90 and 90 degrees
    IntVector2 mouseMove = input.mouseMove;
    yaw += MOUSE_SENSITIVITY * mouseMove.x;
    pitch += MOUSE_SENSITIVITY * mouseMove.y;
    pitch = Clamp(pitch, -90.0f, 90.0f);

    // Construct new orientation for the camera scene node from yaw and pitch. Roll is fixed to zero
    cameraNode.rotation = Quaternion(pitch, yaw, 0.0f);

    // Read WASD keys and move the camera scene node to the corresponding direction if they are pressed
    if (input.keyDown['W'])
        cameraNode.Translate(Vector3(0.0f, 0.0f, 1.0f) * MOVE_SPEED * timeStep);
    if (input.keyDown['S'])
        cameraNode.Translate(Vector3(0.0f, 0.0f, -1.0f) * MOVE_SPEED * timeStep);
    if (input.keyDown['A'])
        cameraNode.Translate(Vector3(-1.0f, 0.0f, 0.0f) * MOVE_SPEED * timeStep);
    if (input.keyDown['D'])
        cameraNode.Translate(Vector3(1.0f, 0.0f, 0.0f) * MOVE_SPEED * timeStep);

    // "Shoot" a physics object with left mousebutton
    if (input.mouseButtonPress[MOUSEB_LEFT])
        SpawnObject();

    // Check for loading / saving the scene
    if (input.keyPress[KEY_F5])
    {
        File saveFile(fileSystem.programDir + "Data/Scenes/PhysicsStressTest.xml", FILE_WRITE);
        scene_.SaveXML(saveFile);
    }
    if (input.keyPress[KEY_F7])
    {
        File loadFile(fileSystem.programDir + "Data/Scenes/PhysicsStressTest.xml", FILE_READ);
        scene_.LoadXML(loadFile);
    }

    // Toggle debug geometry with space
    if (input.keyPress[KEY_SPACE])
        drawDebug = !drawDebug;
}

void SpawnObject()
{
    // Create a smaller box at camera position
    Node@ boxNode = scene_.CreateChild("SmallBox");
    boxNode.position = cameraNode.position;
    boxNode.rotation = cameraNode.rotation;
    boxNode.SetScale(0.25f);
    StaticModel@ boxObject = boxNode.CreateComponent("StaticModel");
    boxObject.model = cache.GetResource("Model", "Models/Box.mdl");
    boxObject.material = cache.GetResource("Material", "Materials/StoneSmall.xml");
    boxObject.castShadows = true;

    // Create physics components, use a smaller mass also
    RigidBody@ body = boxNode.CreateComponent("RigidBody");
    body.mass = 0.25f;
    body.friction = 0.75f;
    CollisionShape@ shape = boxNode.CreateComponent("CollisionShape");
    shape.SetBox(Vector3(1.0f, 1.0f, 1.0f));

    const float OBJECT_VELOCITY = 10.0f;

    // Set initial velocity for the RigidBody based on camera forward vector. Add also a slight up component
    // to overcome gravity better
    body.linearVelocity = cameraNode.rotation * Vector3(0.0f, 0.25f, 1.0f) * OBJECT_VELOCITY;
}

void HandleUpdate(StringHash eventType, VariantMap& eventData)
{
    // Take the frame time step, which is stored as a float
    float timeStep = eventData["TimeStep"].GetFloat();

    // Move the camera, scale movement with time step
    MoveCamera(timeStep);
}

void HandlePostRenderUpdate(StringHash eventType, VariantMap& eventData)
{
    // If draw debug mode is enabled, draw physics debug geometry. Use depth test to make the result easier to interpret
    if (drawDebug)
        scene_.physicsWorld.DrawDebugGeometry(true);
}

// Create XML patch instructions for screen joystick layout specific to this sample app
String patchInstructions =
        "<patch>" +
        "    <remove sel=\"/element/element[./attribute[@name='Name' and @value='Button0']]/attribute[@name='Is Visible']\" />" +
        "    <replace sel=\"/element/element[./attribute[@name='Name' and @value='Button0']]/element[./attribute[@name='Name' and @value='Label']]/attribute[@name='Text']/@value\">Spawn</replace>" +
        "    <add sel=\"/element/element[./attribute[@name='Name' and @value='Button0']]\">" +
        "        <element type=\"Text\">" +
        "            <attribute name=\"Name\" value=\"MouseButtonBinding\" />" +
        "            <attribute name=\"Text\" value=\"LEFT\" />" +
        "        </element>" +
        "    </add>" +
        "    <remove sel=\"/element/element[./attribute[@name='Name' and @value='Button1']]/attribute[@name='Is Visible']\" />" +
        "    <replace sel=\"/element/element[./attribute[@name='Name' and @value='Button1']]/element[./attribute[@name='Name' and @value='Label']]/attribute[@name='Text']/@value\">Debug</replace>" +
        "    <add sel=\"/element/element[./attribute[@name='Name' and @value='Button1']]\">" +
        "        <element type=\"Text\">" +
        "            <attribute name=\"Name\" value=\"KeyBinding\" />" +
        "            <attribute name=\"Text\" value=\"SPACE\" />" +
        "        </element>" +
        "    </add>" +
        "</patch>";
