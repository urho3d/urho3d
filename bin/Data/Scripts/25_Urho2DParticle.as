// Urho2D particle example.
// This sample demonstrates:
//     - Creating a 2D scene with particle
//     - Displaying the scene using the Renderer subsystem
//     - Handling mouse move to move particle

#include "Scripts/Utilities/Sample.as"

Node@ particleNode;

void Start()
{
    // Execute the common startup for samples
    SampleStart();

    // Set mouse visible
    input.mouseVisible = true;

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

    // Create a scene node for the camera, which we will move around
    // The camera will use default settings (1000 far clip distance, 45 degrees FOV, set aspect ratio automatically)
    cameraNode = scene_.CreateChild("Camera");
    // Set an initial position for the camera scene node above the plane
    cameraNode.position = Vector3(0.0f, 0.0f, -10.0f);

    Camera@ camera = cameraNode.CreateComponent("Camera");
    camera.orthographic = true;
    camera.orthoSize = graphics.height * PIXEL_SIZE;
    camera.zoom = 1.2f * Min(graphics.width / 1280.0f, graphics.height / 800.0f); // Set zoom according to user's resolution to ensure full visibility (initial zoom (1.2) is set for full visibility at 1280x800 resolution)

    ParticleEffect2D@ particleEffect = cache.GetResource("ParticleEffect2D", "Urho2D/sun.pex");
    if (particleEffect is null)
        return;

    particleNode = scene_.CreateChild("ParticleEmitter2D");
    ParticleEmitter2D@ particleEmitter = particleNode.CreateComponent("ParticleEmitter2D");
    particleEmitter.effect = particleEffect;

    ParticleEffect2D@ greenSpiralEffect = cache.GetResource("ParticleEffect2D", "Urho2D/greenspiral.pex");
    if (greenSpiralEffect is null)
        return;

    Node@ greenSpiralNode = scene_.CreateChild("GreenSpiral");
    ParticleEmitter2D@ greenSpiralEmitter = greenSpiralNode.CreateComponent("ParticleEmitter2D");
    greenSpiralEmitter.effect = greenSpiralEffect;
}

void CreateInstructions()
{
    // Construct new Text object, set string to display and font to use
    Text@ instructionText = ui.root.CreateChild("Text");
    instructionText.text = "Use mouse to move the particle.";
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

void SubscribeToEvents()
{
    // Subscribe HandleMouseMove() function for tracking mouse/touch move events
    SubscribeToEvent("MouseMove", "HandleMouseMove");
    if (touchEnabled)
        SubscribeToEvent("TouchMove", "HandleMouseMove");

    // Unsubscribe the SceneUpdate event from base class to prevent camera pitch and yaw in 2D sample
    UnsubscribeFromEvent("SceneUpdate");
}

void HandleMouseMove(StringHash eventType, VariantMap& eventData)
{
    if (particleNode !is null)
    {
        float x = eventData["x"].GetInt();
        float y = eventData["y"].GetInt();
        Camera@ camera = cameraNode.GetComponent("Camera");
        particleNode.position = camera.ScreenToWorldPoint(Vector3(x / graphics.width, y / graphics.height, 10.0f));
    }
}

// Create XML patch instructions for screen joystick layout specific to this sample app
String patchInstructions =
        "<patch>" +
        "    <add sel=\"/element/element[./attribute[@name='Name' and @value='Hat0']]\">" +
        "        <attribute name=\"Is Visible\" value=\"false\" />" +
        "    </add>" +
        "</patch>";
