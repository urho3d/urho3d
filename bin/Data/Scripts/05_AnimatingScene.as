// Animating 3D scene example.
// This sample demonstrates:
//     - Creating a 3D scene and using a script component to animate the objects
//     - Controlling scene ambience with the Zone component
//     - Attaching a light to an object (the camera)

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
    SampleInitMouseMode(MM_RELATIVE);

    // Hook up to the frame update events
    SubscribeToEvents();
}

void CreateScene()
{
    scene_ = Scene();

    // Create the Octree component to the scene so that drawable objects can be rendered. Use default volume
    // (-1000, -1000, -1000) to (1000, 1000, 1000)
    scene_.CreateComponent("Octree");

    // Create a Zone component into a child scene node. The Zone controls ambient lighting and fog settings. Like the Octree,
    // it also defines its volume with a bounding box, but can be rotated (so it does not need to be aligned to the world X, Y
    // and Z axes.) Drawable objects "pick up" the zone they belong to and use it when rendering; several zones can exist
    Node@ zoneNode = scene_.CreateChild("Zone");
    Zone@ zone = zoneNode.CreateComponent("Zone");
    // Set same volume as the Octree, set a close bluish fog and some ambient light
    zone.boundingBox = BoundingBox(-1000.0f, 1000.0f);
    zone.ambientColor = Color(0.05f, 0.1f, 0.15f);
    zone.fogColor = Color(0.1f, 0.2f, 0.3f);
    zone.fogStart = 10.0f;
    zone.fogEnd = 100.0f;

    // Create randomly positioned and oriented box StaticModels in the scene
    const uint NUM_OBJECTS = 2000;
    for (uint i = 0; i < NUM_OBJECTS; ++i)
    {
        Node@ boxNode = scene_.CreateChild("Box");
        boxNode.position = Vector3(Random(200.0f) - 100.0f, Random(200.0f) - 100.0f, Random(200.0f) - 100.0f);
        // Orient using random pitch, yaw and roll Euler angles
        boxNode.rotation = Quaternion(Random(360.0f), Random(360.0f), Random(360.0f));
        StaticModel@ boxObject = boxNode.CreateComponent("StaticModel");
        boxObject.model = cache.GetResource("Model", "Models/Box.mdl");
        boxObject.material = cache.GetResource("Material", "Materials/Stone.xml");

        // Add the Rotator script object which will rotate the scene node each frame, when the scene sends its update event.
        // This requires the C++ component ScriptInstance in the scene node, which acts as a container. We need to tell the
        // script file and class name to instantiate the object (scriptFile is a global property which refers to the currently
        // executing script file.) There is also a shortcut for creating the ScriptInstance component and the script object,
        // which is shown in a later sample, but this is what happens "under the hood."
        ScriptInstance@ instance = boxNode.CreateComponent("ScriptInstance");
        instance.CreateObject(scriptFile, "Rotator");
        // Retrieve the created script object and set its rotation speed member variable
        Rotator@ rotator = cast<Rotator>(instance.scriptObject);
        rotator.rotationSpeed = Vector3(10.0f, 20.0f, 30.0f);
    }

    // Create the camera. Let the starting position be at the world origin. As the fog limits maximum visible distance, we can
    // bring the far clip plane closer for more effective culling of distant objects
    cameraNode = scene_.CreateChild("Camera");
    Camera@ camera = cameraNode.CreateComponent("Camera");
    camera.farClip = 100.0f;

    // Create a point light to the camera scene node
    Light@ light = cameraNode.CreateComponent("Light");
    light.lightType = LIGHT_POINT;
    light.range = 30.0f;
}

void CreateInstructions()
{
    // Construct new Text object, set string to display and font to use
    Text@ instructionText = ui.root.CreateChild("Text");
    instructionText.text = "Use WASD keys and mouse to move";
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
}

void SubscribeToEvents()
{
    // Subscribe HandleUpdate() function for processing update events
    SubscribeToEvent("Update", "HandleUpdate");
}

void HandleUpdate(StringHash eventType, VariantMap& eventData)
{
    // Take the frame time step, which is stored as a float
    float timeStep = eventData["TimeStep"].GetFloat();

    // Move the camera, scale movement with time step
    MoveCamera(timeStep);
}

// Rotator script object class. Script objects to be added to a scene node must implement the empty ScriptObject interface
class Rotator : ScriptObject
{
    Vector3 rotationSpeed;

    // Update is called during the variable timestep scene update
    void Update(float timeStep)
    {
        node.Rotate(Quaternion(rotationSpeed.x * timeStep, rotationSpeed.y * timeStep, rotationSpeed.z * timeStep));
    }
}

// Create XML patch instructions for screen joystick layout specific to this sample app
String patchInstructions = "";
