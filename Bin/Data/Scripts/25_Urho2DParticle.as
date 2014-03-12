// Urho2D particle example.
// This sample demonstrates:
//     - Creating a 2D scene with particle
//     - Displaying the scene using the Renderer subsystem
//     - Handling mouse move to move particle

#include "Scripts/Utilities/Sample.as"

Scene@ scene_;
Node@ cameraNode;
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
    camera.SetOrthoSize(Vector2(graphics.width, graphics.height) * PIXEL_SIZE);

    ParticleModel2D@ particleModel = cache.GetResource("ParticleModel2D", "Urho2D/LavaFlow.plist");
    if (particleModel is null)
        return;

    particleNode = scene_.CreateChild("ParticleEmitter2D");
    ParticleEmitter2D@ particleEmitter = particleNode.CreateComponent("ParticleEmitter2D");
    particleEmitter.model = particleModel;
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
    SubscribeToEvent("MouseMove", "HandleMouseMove");
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

