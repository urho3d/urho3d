// Urho2D physics rope sample.
// This sample demonstrates.
//     - Create revolute constraint
//     - Create roop constraint
//     - Displaying physics debug geometry

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

    // Set the mouse mode to use in the sample
    SampleInitMouseMode(MM_FREE);

    // Hook up to the frame update events
    SubscribeToEvents();
}

void CreateScene()
{
    scene_ = Scene();

    // Create the Octree component to the scene. This is required before adding any drawable components, or else nothing will
    // show up. The default octree volume will be from (-1000, -1000, -1000) to (1000, 1000, 1000) in world coordinates; it
    // is also legal to place objects outside the volume but their visibility can then not be checked in a hierarchically
    // optimizing manner
    scene_.CreateComponent("Octree");
    scene_.CreateComponent("DebugRenderer");

    // Create a scene node for the camera, which we will move around
    // The camera will use default settings (1000 far clip distance, 45 degrees FOV, set aspect ratio automatically)
    cameraNode = scene_.CreateChild("Camera");
    // Set an initial position for the camera scene node above the plane
    cameraNode.position = Vector3(0.0f, 5.0f, -10.0f);

    Camera@ camera = cameraNode.CreateComponent("Camera");
    camera.orthographic = true;
    camera.orthoSize = graphics.height * 0.05f;
    camera.zoom = 1.5f * Min(graphics.width / 1280.0f, graphics.height / 800.0f); // Set zoom according to user's resolution to ensure full visibility (initial zoom (1.5) is set for full visibility at 1280x800 resolution)

    // Create 2D physics world component
    PhysicsWorld2D@ physicsWorld = scene_.CreateComponent("PhysicsWorld2D");
    physicsWorld.drawJoint = true;

    // Create ground.
    Node@ groundNode = scene_.CreateChild("Ground");
    // Create 2D rigid body for gound
    RigidBody2D@ groundBody = groundNode.CreateComponent("RigidBody2D");
    // Create edge collider for ground
    CollisionEdge2D@ groundShape = groundNode.CreateComponent("CollisionEdge2D");
    groundShape.SetVertices(Vector2(-40.0f, 0.0f), Vector2(40.0f, 0.0f));

    const float y = 15.0f;
    RigidBody2D@ prevBody = groundBody;

    const uint NUM_OBJECTS = 10;
    for (uint i = 0; i < NUM_OBJECTS; ++i)
    {
        Node@ node  = scene_.CreateChild("RigidBody");
        // Create rigid body
        RigidBody2D@ body = node.CreateComponent("RigidBody2D");
        body.bodyType = BT_DYNAMIC;

        // Create box
        CollisionBox2D@ box = node.CreateComponent("CollisionBox2D");
        // Set friction
        box.friction = 0.2f;
        // Set mask bits.
        box.maskBits = 0xFFFF & ~0x0002;

        if (i == NUM_OBJECTS - 1)
        {
            node.position  = Vector3(1.0f * i, y, 0.0f);
            body.angularDamping = 0.4f;
            box.SetSize(3.0f, 3.0f);
            box.density = 100.0f;
            box.categoryBits = 0x0002;
        }
        else
        {
            node.position = Vector3(0.5f + 1.0f * i, y, 0.0f);
            box.SetSize(1.0f, 0.25f);
            box.density = 20.0f;
            box.categoryBits = 0x0001;
        }

        ConstraintRevolute2D@ joint = node.CreateComponent("ConstraintRevolute2D");
        joint.otherBody = prevBody;
        joint.anchor = Vector2(i, y);
        joint.collideConnected = false;

        prevBody = body;
    }

    ConstraintRope2D@ constraintRope = groundNode.CreateComponent("ConstraintRope2D");
    constraintRope.otherBody = prevBody;
    constraintRope.ownerBodyAnchor = Vector2(0.0f, y);
    constraintRope.maxLength = NUM_OBJECTS - 1.0f + 0.01f;
}

void CreateInstructions()
{
    // Construct new Text object, set string to display and font to use
    Text@ instructionText = ui.root.CreateChild("Text");
    instructionText.text = "Use WASD keys and mouse to move, Use PageUp PageDown to zoom.";
    instructionText.SetFont(cache.GetResource("Font", "Fonts/Anonymous Pro.ttf"), 15);

    // Position the text relative to the screen center
    instructionText.horizontalAlignment = HA_CENTER;
    instructionText.verticalAlignment = VA_CENTER;
    instructionText.SetPosition(0, ui.root.height / 4);
}

void SetupViewport()
{
    // Set up a viewport to the Renderer subsystem so that the 3D scene can be seen. We need to define the scene and the camera
    // at minimum. Additionally we could configure the viewport screen size and the rendering path (eg. forward / deferred) to
    // use, but now we just use full screen and default render path configured in the engine command line options
    Viewport@ viewport = Viewport(scene_, cameraNode.GetComponent("Camera"));
    renderer.viewports[0] = viewport;
}

void MoveCamera(float timeStep)
{
    // Do not move if the UI has a focused element (the console)
    if (ui.focusElement !is null)
        return;

    // Movement speed as world units per second
    const float MOVE_SPEED = 4.0f;

    // Read WASD keys and move the camera scene node to the corresponding direction if they are pressed
    if (input.keyDown['W'])
        cameraNode.Translate(Vector3(0.0f, 1.0f, 0.0f) * MOVE_SPEED * timeStep);
    if (input.keyDown['S'])
        cameraNode.Translate(Vector3(0.0f, -1.0f, 0.0f) * MOVE_SPEED * timeStep);
    if (input.keyDown['A'])
        cameraNode.Translate(Vector3(-1.0f, 0.0f, 0.0f) * MOVE_SPEED * timeStep);
    if (input.keyDown['D'])
        cameraNode.Translate(Vector3(1.0f, 0.0f, 0.0f) * MOVE_SPEED * timeStep);

    if (input.keyDown[KEY_PAGEUP])
    {
        Camera@ camera = cameraNode.GetComponent("Camera");
        camera.zoom = camera.zoom * 1.01f;
    }

    if (input.keyDown[KEY_PAGEDOWN])
    {
        Camera@ camera = cameraNode.GetComponent("Camera");
        camera.zoom = camera.zoom * 0.99f;
    }
}

void SubscribeToEvents()
{
    // Subscribe HandleUpdate() function for processing update events
    SubscribeToEvent("Update", "HandleUpdate");

    // Unsubscribe the SceneUpdate event from base class to prevent camera pitch and yaw in 2D sample
    UnsubscribeFromEvent("SceneUpdate");
}

void HandleUpdate(StringHash eventType, VariantMap& eventData)
{
    // Take the frame time step, which is stored as a float
    float timeStep = eventData["TimeStep"].GetFloat();

    // Move the camera, scale movement with time step
    MoveCamera(timeStep);

    PhysicsWorld2D@ physicsWorld = scene_.GetComponent("PhysicsWorld2D");
    physicsWorld.DrawDebugGeometry();
}

// Create XML patch instructions for screen joystick layout specific to this sample app
String patchInstructions =
        "<patch>" +
        "    <remove sel=\"/element/element[./attribute[@name='Name' and @value='Button0']]/attribute[@name='Is Visible']\" />" +
        "    <replace sel=\"/element/element[./attribute[@name='Name' and @value='Button0']]/element[./attribute[@name='Name' and @value='Label']]/attribute[@name='Text']/@value\">Zoom In</replace>" +
        "    <add sel=\"/element/element[./attribute[@name='Name' and @value='Button0']]\">" +
        "        <element type=\"Text\">" +
        "            <attribute name=\"Name\" value=\"KeyBinding\" />" +
        "            <attribute name=\"Text\" value=\"PAGEUP\" />" +
        "        </element>" +
        "    </add>" +
        "    <remove sel=\"/element/element[./attribute[@name='Name' and @value='Button1']]/attribute[@name='Is Visible']\" />" +
        "    <replace sel=\"/element/element[./attribute[@name='Name' and @value='Button1']]/element[./attribute[@name='Name' and @value='Label']]/attribute[@name='Text']/@value\">Zoom Out</replace>" +
        "    <add sel=\"/element/element[./attribute[@name='Name' and @value='Button1']]\">" +
        "        <element type=\"Text\">" +
        "            <attribute name=\"Name\" value=\"KeyBinding\" />" +
        "            <attribute name=\"Text\" value=\"PAGEDOWN\" />" +
        "        </element>" +
        "    </add>" +
        "</patch>";
