// Multiple viewports example.
// This sample demonstrates:
//     - Setting up two viewports with two separate cameras;
//     - Adding post processing effects to a viewport's render path and toggling them;

#include "Scripts/Utilities/Sample.as"

Scene@ scene_;
Node@ cameraNode;
Node@ rearCameraNode;
float yaw = 0.0f;
float pitch = 0.0f;
bool drawDebug = false;

void Start()
{
    // Execute the common startup for samples
    SampleStart();

    // Create the scene content
    CreateScene();
    
    // Create the UI content
    CreateInstructions();
    
    // Setup the viewports for displaying the scene
    SetupViewports();

    // Hook up to the frame update and render post-update events
    SubscribeToEvents();
}

void CreateScene()
{
    scene_ = Scene();

    // Create octree, use default volume (-1000, -1000, -1000) to (1000, 1000, 1000)
    // Also create a DebugRenderer component so that we can draw debug geometry
    scene_.CreateComponent("Octree");
    scene_.CreateComponent("DebugRenderer");
    
    // Create scene node & StaticModel component for showing a static plane
    Node@ planeNode = scene_.CreateChild("Plane");
    planeNode.scale = Vector3(100.0f, 1.0f, 100.0f);
    StaticModel@ planeObject = planeNode.CreateComponent("StaticModel");
    planeObject.model = cache.GetResource("Model", "Models/Plane.mdl");
    planeObject.material = cache.GetResource("Material", "Materials/StoneTiled.xml");
    
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
    light.shadowBias = BiasParameters(0.0001f, 0.5f);
    // Set cascade splits at 10, 50 and 200 world units, fade shadows out at 80% of maximum shadow distance
    light.shadowCascade = CascadeParameters(10.0f, 50.0f, 200.0f, 0.0f, 0.8f);

    // Create some mushrooms
    const uint NUM_MUSHROOMS = 240;
    for (uint i = 0; i < NUM_MUSHROOMS; ++i)
    {
        Node@ mushroomNode = scene_.CreateChild("Mushroom");
        mushroomNode.position = Vector3(Random(90.0f) - 45.0f, 0.0f, Random(90.0f) - 45.0f);
        mushroomNode.rotation = Quaternion(0.0f, Random(360.0f), 0.0f);
        mushroomNode.SetScale(0.5f + Random(2.0f));
        StaticModel@ mushroomObject = mushroomNode.CreateComponent("StaticModel");
        mushroomObject.model = cache.GetResource("Model", "Models/Mushroom.mdl");
        mushroomObject.material = cache.GetResource("Material", "Materials/Mushroom.xml");
        mushroomObject.castShadows = true;
    }

    // Create randomly sized boxes. If boxes are big enough, make them occluders. Occluders will be software rasterized before
    // rendering to a low-resolution depth-only buffer to test the objects in the view frustum for visibility
    const uint NUM_BOXES = 20;
    for (uint i = 0; i < NUM_BOXES; ++i)
    {
        Node@ boxNode = scene_.CreateChild("Box");
        float size = 1.0f + Random(10.0f);
        boxNode.position = Vector3(Random(80.0f) - 40.0f, size * 0.5f, Random(80.0f) - 40.0f);
        boxNode.SetScale(size);
        StaticModel@ boxObject = boxNode.CreateComponent("StaticModel");
        boxObject.model = cache.GetResource("Model", "Models/Box.mdl");
        boxObject.material = cache.GetResource("Material", "Materials/Stone.xml");
        boxObject.castShadows = true;
        if (size >= 3.0f)
            boxObject.occluder = true;
    }

    // Create the cameras. Limit far clip distance to match the fog
    cameraNode = scene_.CreateChild("Camera");
    Camera@ camera = cameraNode.CreateComponent("Camera");
    camera.farClip = 300.0f;

    // Parent the rear camera node to the front camera node and turn it 180 degrees to face backward
    // Here, we use the angle-axis constructor for Quaternion instead of the usual Euler angles
    rearCameraNode = cameraNode.CreateChild("RearCamera");
    rearCameraNode.Rotate(Quaternion(180.0f, Vector3(0.0f, 1.0f, 0.0f)));
    Camera@ rearCamera = rearCameraNode.CreateComponent("Camera");
    rearCamera.farClip = 300.0f;
    // Because the rear viewport is rather small, disable occlusion culling from it. Use the camera's
    // "view override flags" for this. We could also disable eg. shadows or force low material quality
    // if we wanted
    rearCamera.viewOverrideFlags = VO_DISABLE_OCCLUSION;

    // Set an initial position for the front camera scene node above the plane
    cameraNode.position = Vector3(0.0f, 5.0f, 0.0f);
}

void CreateInstructions()
{
    // Construct new Text object, set string to display and font to use
    Text@ instructionText = ui.root.CreateChild("Text");
    instructionText.text =
        "Use WASD keys and mouse to move\n"
        "B to toggle bloom, F to toggle FXAA\n"
        "Space to toggle debug geometry\n";
    instructionText.SetFont(cache.GetResource("Font", "Fonts/Anonymous Pro.ttf"), 15);
    // The text has multiple rows. Center them in relation to each other
    instructionText.textAlignment = HA_CENTER;

    // Position the text relative to the screen center
    instructionText.horizontalAlignment = HA_CENTER;
    instructionText.verticalAlignment = VA_CENTER;
    instructionText.SetPosition(0, ui.root.height / 4);
}

void SetupViewports()
{
    renderer.numViewports = 2;

    // Set up the front camera viewport
    Viewport@ viewport = Viewport(scene_, cameraNode.GetComponent("Camera"));
    renderer.viewports[0] = viewport;
    
    // Clone the default render path so that we do not interfere with the other viewport, then add
    // bloom and FXAA post process effects to the front viewport. Render path commands can be tagged
    // for example with the effect name to allow easy toggling on and off. We start with the effects
    // disabled.
    RenderPath@ effectRenderPath = viewport.renderPath.Clone();
    effectRenderPath.Append(cache.GetResource("XMLFile", "PostProcess/Bloom.xml"));
    effectRenderPath.Append(cache.GetResource("XMLFile", "PostProcess/EdgeFilter.xml"));
    // Make the bloom mixing parameter more pronounced
    effectRenderPath.shaderParameters["BloomMix"] = Variant(Vector2(0.9f, 0.6f));
    effectRenderPath.SetEnabled("Bloom", false);
    effectRenderPath.SetEnabled("EdgeFilter", false);
    viewport.renderPath = effectRenderPath;

    // Set up the rear camera viewport on top of the front view ("rear view mirror")
    // The viewport index must be greater in that case, otherwise the view would be left behind
    Viewport@ rearViewport = Viewport(scene_, rearCameraNode.GetComponent("Camera"),
        IntRect(graphics.width * 2 / 3, 32, graphics.width - 32, graphics.height / 3));
    renderer.viewports[1] = rearViewport;
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
        cameraNode.TranslateRelative(Vector3(0.0f, 0.0f, 1.0f) * MOVE_SPEED * timeStep);
    if (input.keyDown['S'])
        cameraNode.TranslateRelative(Vector3(0.0f, 0.0f, -1.0f) * MOVE_SPEED * timeStep);
    if (input.keyDown['A'])
        cameraNode.TranslateRelative(Vector3(-1.0f, 0.0f, 0.0f) * MOVE_SPEED * timeStep);
    if (input.keyDown['D'])
        cameraNode.TranslateRelative(Vector3(1.0f, 0.0f, 0.0f) * MOVE_SPEED * timeStep);

    // Toggle post processing effects on the front viewport. Note that the rear viewport is unaffected
    RenderPath@ effectRenderPath = renderer.viewports[0].renderPath;
    if (input.keyPress['B'])
        effectRenderPath.ToggleEnabled("Bloom");
    if (input.keyPress['F'])
        effectRenderPath.ToggleEnabled("EdgeFilter");

    // Toggle debug geometry with space
    if (input.keyPress[KEY_SPACE])
        drawDebug = !drawDebug;
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
    // If draw debug mode is enabled, draw viewport debug geometry. Disable depth test so that we can see the effect of occlusion
    if (drawDebug)
        renderer.DrawDebugGeometry(false);
}
