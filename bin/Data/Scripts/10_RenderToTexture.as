// Render to texture example
// This sample demonstrates:
//     - Creating two 3D scenes and rendering the other into a texture
//     - Creating rendertarget texture and material programmatically

#include "Scripts/Utilities/Sample.as"

Scene@ rttScene_;
Node@ rttCameraNode;

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
    {
        // Create the scene which will be rendered to a texture
        rttScene_ = Scene();

        // Create octree, use default volume (-1000, -1000, -1000) to (1000, 1000, 1000)
        rttScene_.CreateComponent("Octree");

        // Create a Zone for ambient light & fog control
        Node@ zoneNode = rttScene_.CreateChild("Zone");
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
            Node@ boxNode = rttScene_.CreateChild("Box");
            boxNode.position = Vector3(Random(200.0f) - 100.0f, Random(200.0f) - 100.0f, Random(200.0f) - 100.0f);
            // Orient using random pitch, yaw and roll Euler angles
            boxNode.rotation = Quaternion(Random(360.0f), Random(360.0f), Random(360.0f));
            StaticModel@ boxObject = boxNode.CreateComponent("StaticModel");
            boxObject.model = cache.GetResource("Model", "Models/Box.mdl");
            boxObject.material = cache.GetResource("Material", "Materials/Stone.xml");

            // Add our custom Rotator component which will rotate the scene node each frame, when the scene sends its update event.
            // Simply set same rotation speed for all objects
            Rotator@ rotator = cast<Rotator>(boxNode.CreateScriptObject(scriptFile, "Rotator"));
            rotator.rotationSpeed = Vector3(10.0f, 20.0f, 30.0f);
        }

        // Create a camera for the render-to-texture scene. Simply leave it at the world origin and let it observe the scene
        rttCameraNode = rttScene_.CreateChild("Camera");
        Camera@ camera = rttCameraNode.CreateComponent("Camera");
        camera.farClip = 100.0f;

        // Create a point light to the camera scene node
        Light@ light = rttCameraNode.CreateComponent("Light");
        light.lightType = LIGHT_POINT;
        light.range = 30.0f;
    }

    {
        // Create the scene in which we move around
        scene_ = Scene();

        // Create octree, use also default volume (-1000, -1000, -1000) to (1000, 1000, 1000)
        scene_.CreateComponent("Octree");

        // Create a Zone component for ambient lighting & fog control
        Node@ zoneNode = scene_.CreateChild("Zone");
        Zone@ zone = zoneNode.CreateComponent("Zone");
        zone.boundingBox = BoundingBox(-1000.0f, 1000.0f);
        zone.ambientColor = Color(0.1f, 0.1f, 0.1f);
        zone.fogStart = 100.0f;
        zone.fogEnd = 300.0f;

        // Create a directional light without shadows
        Node@ lightNode = scene_.CreateChild("DirectionalLight");
        lightNode.direction = Vector3(0.5f, -1.0f, 0.5f);
        Light@ light = lightNode.CreateComponent("Light");
        light.lightType = LIGHT_DIRECTIONAL;
        light.color = Color(0.2f, 0.2f, 0.2f);
        light.specularIntensity = 1.0f;

        // Create a "floor" consisting of several tiles
        for (int y = -5; y <= 5; ++y)
        {
            for (int x = -5; x <= 5; ++x)
            {
                Node@ floorNode = scene_.CreateChild("FloorTile");
                floorNode.position = Vector3(x * 20.5f, -0.5f, y * 20.5f);
                floorNode.scale = Vector3(20.0f, 1.0f, 20.f);
                StaticModel@ floorObject = floorNode.CreateComponent("StaticModel");
                floorObject.model = cache.GetResource("Model", "Models/Box.mdl");
                floorObject.material = cache.GetResource("Material", "Materials/Stone.xml");
            }
        }

        // Create a "screen" like object for viewing the second scene. Construct it from two StaticModels, a box for the frame
        // and a plane for the actual view
        {
            Node@ boxNode = scene_.CreateChild("ScreenBox");
            boxNode.position = Vector3(0.0f, 10.0f, 0.0f);
            boxNode.scale = Vector3(21.0f, 16.0f, 0.5f);
            StaticModel@ boxObject = boxNode.CreateComponent("StaticModel");
            boxObject.model = cache.GetResource("Model", "Models/Box.mdl");
            boxObject.material = cache.GetResource("Material", "Materials/Stone.xml");

            Node@ screenNode = scene_.CreateChild("Screen");
            screenNode.position = Vector3(0.0f, 10.0f, -0.27f);
            screenNode.rotation = Quaternion(-90.0f, 0.0f, 0.0f);
            screenNode.scale = Vector3(20.0f, 0.0f, 15.0f);
            StaticModel@ screenObject = screenNode.CreateComponent("StaticModel");
            screenObject.model = cache.GetResource("Model", "Models/Plane.mdl");

            // Create a renderable texture (1024x768, RGB format), enable bilinear filtering on it
            Texture2D@ renderTexture = Texture2D();
            renderTexture.SetSize(1024, 768, GetRGBFormat(), TEXTURE_RENDERTARGET);
            renderTexture.filterMode = FILTER_BILINEAR;

            // Create a new material from scratch, use the diffuse unlit technique, assign the render texture
            // as its diffuse texture, then assign the material to the screen plane object
            Material@ renderMaterial = Material();
            renderMaterial.SetTechnique(0, cache.GetResource("Technique", "Techniques/DiffUnlit.xml"));
            renderMaterial.textures[TU_DIFFUSE] = renderTexture;
            screenObject.material = renderMaterial;

            // Get the texture's RenderSurface object (exists when the texture has been created in rendertarget mode)
            // and define the viewport for rendering the second scene, similarly as how backbuffer viewports are defined
            // to the Renderer subsystem. By default the texture viewport will be updated when the texture is visible
            // in the main view
            RenderSurface@ surface = renderTexture.renderSurface;
            Viewport@ rttViewport = Viewport(rttScene_, rttCameraNode.GetComponent("Camera"));
            surface.viewports[0] = rttViewport;
        }

        // Create the camera which we will move around. Limit far clip distance to match the fog
        cameraNode = scene_.CreateChild("Camera");
        Camera@ camera = cameraNode.CreateComponent("Camera");
        camera.farClip = 300.0f;

        // Set an initial position for the camera scene node above the plane
        cameraNode.position = Vector3(0.0f, 7.0f, -30.0f);
    }
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
    // Set up a viewport to the Renderer subsystem so that the 3D scene can be seen
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
