// Water example.
// This sample demonstrates:
//     - Creating a large plane to represent a water body for rendering
//     - Setting up a second camera to render reflections on the water surface

#include "Scripts/Utilities/Sample.as"

Node@ reflectionCameraNode;
Node@ waterNode;
Plane waterPlane;
Plane waterClipPlane;

void Start()
{
    // Execute the common startup for samples
    SampleStart();

    // Create the scene content
    CreateScene();

    // Create the UI content
    CreateInstructions();

    // Setup the viewports for displaying the scene and rendering the water reflection
    SetupViewports();

    // Set the mouse mode to use in the sample
    SampleInitMouseMode(MM_RELATIVE);

    // Hook up to the frame update and render post-update events
    SubscribeToEvents();
}

void CreateScene()
{
    scene_ = Scene();

    // Create octree, use default volume (-1000, -1000, -1000) to (1000, 1000, 1000)
    scene_.CreateComponent("Octree");
    scene_.CreateComponent("DebugRenderer");

    // Create a Zone component for ambient lighting & fog control
    Node@ zoneNode = scene_.CreateChild("Zone");
    Zone@ zone = zoneNode.CreateComponent("Zone");
    zone.boundingBox = BoundingBox(-1000.0f, 1000.0f);
    zone.ambientColor = Color(0.15f, 0.15f, 0.15f);
    zone.fogColor = Color(1.0f, 1.0f, 1.0f);
    zone.fogStart = 500.0f;
    zone.fogEnd = 750.0f;

    // Create a directional light to the world. Enable cascaded shadows on it
    Node@ lightNode = scene_.CreateChild("DirectionalLight");
    lightNode.direction = Vector3(0.3f, -0.5f, 0.425f);
    Light@ light = lightNode.CreateComponent("Light");
    light.lightType = LIGHT_DIRECTIONAL;
    light.castShadows = true;
    light.shadowBias = BiasParameters(0.00025f, 0.5f);
    light.shadowCascade = CascadeParameters(10.0f, 50.0f, 200.0f, 0.0f, 0.8f);
    light.specularIntensity = 0.5f;
    // Apply slightly overbright lighting to match the skybox
    light.color = Color(1.2f, 1.2f, 1.2f);

    // Create skybox. The Skybox component is used like StaticModel, but it will be always located at the camera, giving the
    // illusion of the box planes being far away. Use just the ordinary Box model and a suitable material, whose shader will
    // generate the necessary 3D texture coordinates for cube mapping
    Node@ skyNode = scene_.CreateChild("Sky");
    skyNode.SetScale(500.0); // The scale actually does not matter
    Skybox@ skybox = skyNode.CreateComponent("Skybox");
    skybox.model = cache.GetResource("Model", "Models/Box.mdl");
    skybox.material = cache.GetResource("Material", "Materials/Skybox.xml");

    // Create heightmap terrain
    Node@ terrainNode = scene_.CreateChild("Terrain");
    terrainNode.position = Vector3(0.0f, 0.0f, 0.0f);
    Terrain@ terrain = terrainNode.CreateComponent("Terrain");
    terrain.patchSize = 64;
    terrain.spacing = Vector3(2.0f, 0.5f, 2.0f); // Spacing between vertices and vertical resolution of the height map
    terrain.smoothing = true;
    terrain.heightMap = cache.GetResource("Image", "Textures/HeightMap.png");
    terrain.material = cache.GetResource("Material", "Materials/Terrain.xml");
    // The terrain consists of large triangles, which fits well for occlusion rendering, as a hill can occlude all
    // terrain patches and other objects behind it
    terrain.occluder = true;

    // Create 1000 boxes in the terrain. Always face outward along the terrain normal
    const uint NUM_OBJECTS = 1000;
    for (uint i = 0; i < NUM_OBJECTS; ++i)
    {
        Node@ objectNode = scene_.CreateChild("Box");
        Vector3 position(Random(2000.0f) - 1000.0f, 0.0f, Random(2000.0f) - 1000.0f);
        position.y = terrain.GetHeight(position) + 2.25f;
        objectNode.position = position;
        // Create a rotation quaternion from up vector to terrain normal
        objectNode.rotation = Quaternion(Vector3(0.0f, 1.0f, 0.0f), terrain.GetNormal(position));
        objectNode.SetScale(5.0f);
        StaticModel@ object = objectNode.CreateComponent("StaticModel");
        object.model = cache.GetResource("Model", "Models/Box.mdl");
        object.material = cache.GetResource("Material", "Materials/Stone.xml");
        object.castShadows = true;
    }

    // Create a water plane object that is as large as the terrain
    waterNode = scene_.CreateChild("Water");
    waterNode.scale = Vector3(2048.0f, 1.0f, 2048.0f);
    waterNode.position = Vector3(0.0f, 5.0f, 0.0f);
    StaticModel@ water = waterNode.CreateComponent("StaticModel");
    water.model = cache.GetResource("Model", "Models/Plane.mdl");
    water.material = cache.GetResource("Material", "Materials/Water.xml");
    // Set a different viewmask on the water plane to be able to hide it from the reflection camera
    water.viewMask = 0x80000000;

    // Create the camera. Set far clip to match the fog. Note: now we actually create the camera node outside
    // the scene, because we want it to be unaffected by scene load / save
    cameraNode = Node();
    Camera@ camera = cameraNode.CreateComponent("Camera");
    camera.farClip = 750.0f;

    // Set an initial position for the camera scene node above the ground
    cameraNode.position = Vector3(0.0f, 7.0f, -20.0f);
}

void CreateInstructions()
{
    // Construct new Text object, set string to display and font to use
    Text@ instructionText = ui.root.CreateChild("Text");
    instructionText.text = "Use WASD keys and mouse to move";
    instructionText.SetFont(cache.GetResource("Font", "Fonts/Anonymous Pro.ttf"), 15);
    instructionText.textAlignment = HA_CENTER;

    // Position the text relative to the screen center
    instructionText.horizontalAlignment = HA_CENTER;
    instructionText.verticalAlignment = VA_CENTER;
    instructionText.SetPosition(0, ui.root.height / 4);
}

void SetupViewports()
{
    // Set up a viewport to the Renderer subsystem so that the 3D scene can be seen
    Viewport@ viewport = Viewport(scene_, cameraNode.GetComponent("Camera"));
    renderer.viewports[0] = viewport;

    // Create a mathematical plane to represent the water in calculations
    waterPlane = Plane(waterNode.worldRotation * Vector3(0.0f, 1.0f, 0.0f), waterNode.worldPosition);
    // Create a downward biased plane for reflection view clipping. Biasing is necessary to avoid too aggressive clipping
    waterClipPlane = Plane(waterNode.worldRotation * Vector3(0.0f, 1.0f, 0.0f), waterNode.worldPosition -
        Vector3(0.0f, 0.1f, 0.0f));

    // Create camera for water reflection
    // It will have the same farclip and position as the main viewport camera, but uses a reflection plane to modify
    // its position when rendering
    reflectionCameraNode = cameraNode.CreateChild();
    Camera@ reflectionCamera = reflectionCameraNode.CreateComponent("Camera");
    reflectionCamera.farClip = 750.0;
    reflectionCamera.viewMask = 0x7fffffff; // Hide objects with only bit 31 in the viewmask (the water plane)
    reflectionCamera.autoAspectRatio = false;
    reflectionCamera.useReflection = true;
    reflectionCamera.reflectionPlane = waterPlane;
    reflectionCamera.useClipping = true; // Enable clipping of geometry behind water plane
    reflectionCamera.clipPlane = waterClipPlane;
    // The water reflection texture is rectangular. Set reflection camera aspect ratio to match
    reflectionCamera.aspectRatio = float(graphics.width) / float(graphics.height);
    // View override flags could be used to optimize reflection rendering. For example disable shadows
    //reflectionCamera.viewOverrideFlags = VO_DISABLE_SHADOWS;

    // Create a texture and setup viewport for water reflection. Assign the reflection texture to the diffuse
    // texture unit of the water material
    int texSize = 1024;
    Texture2D@ renderTexture = Texture2D();
    renderTexture.SetSize(texSize, texSize, GetRGBFormat(), TEXTURE_RENDERTARGET);
    renderTexture.filterMode = FILTER_BILINEAR;
    RenderSurface@ surface = renderTexture.renderSurface;
    Viewport@ rttViewport = Viewport(scene_, reflectionCamera);
    surface.viewports[0] = rttViewport;
    Material@ waterMat = cache.GetResource("Material", "Materials/Water.xml");
    waterMat.textures[TU_DIFFUSE] = renderTexture;
}

void SubscribeToEvents()
{
    // Subscribe HandleUpdate() function for processing update events
    SubscribeToEvent("Update", "HandleUpdate");
}

void MoveCamera(float timeStep)
{
    // Do not move if the UI has a focused element (the console)
    if (ui.focusElement !is null)
        return;

    // Movement speed as world units per second
    const float MOVE_SPEED = 30.0;
    // Mouse sensitivity as degrees per pixel
    const float MOUSE_SENSITIVITY = 0.1;

    // Use this frame's mouse motion to adjust camera node yaw and pitch. Clamp the pitch between -90 and 90 degrees
    IntVector2 mouseMove = input.mouseMove;
    yaw += MOUSE_SENSITIVITY * mouseMove.x;
    pitch += MOUSE_SENSITIVITY * mouseMove.y;
    pitch = Clamp(pitch, -90.0, 90.0);

    // Construct new orientation for the camera scene node from yaw and pitch. Roll is fixed to zero
    cameraNode.rotation = Quaternion(pitch, yaw, 0.0);

    // Read WASD keys and move the camera scene node to the corresponding direction if they are pressed
    if (input.keyDown[KEY_W])
        cameraNode.Translate(Vector3(0.0f, 0.0f, 1.0f) * MOVE_SPEED * timeStep);
    if (input.keyDown[KEY_S])
        cameraNode.Translate(Vector3(0.0f, 0.0f, -1.0f) * MOVE_SPEED * timeStep);
    if (input.keyDown[KEY_A])
        cameraNode.Translate(Vector3(-1.0f, 0.0f, 0.0f) * MOVE_SPEED * timeStep);
    if (input.keyDown[KEY_D])
        cameraNode.Translate(Vector3(1.0f, 0.0f, 0.0f) * MOVE_SPEED * timeStep);

    // In case resolution has changed, adjust the reflection camera aspect ratio
    Camera@ reflectionCamera = reflectionCameraNode.GetComponent("Camera");
    reflectionCamera.aspectRatio = float(graphics.width) / float(graphics.height);
}

void HandleUpdate(StringHash eventType, VariantMap& eventData)
{
    // Take the frame time step, which is stored as a float
    float timeStep = eventData["TimeStep"].GetFloat();

    // Move the camera, scale movement with time step
    MoveCamera(timeStep);
}

// Create XML patch instructions for screen joystick layout specific to this sample app
String patchInstructions = "";
