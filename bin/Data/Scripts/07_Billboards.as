// Billboard example.
// This sample demonstrates:
//     - Populating a 3D scene with billboard sets and several shadow casting spotlights
//     - Parenting scene nodes to allow more intuitive creation of groups of objects
//     - Examining rendering performance with a somewhat large object and light count

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

    // Create groups of mushrooms, which act as shadow casters
    const uint NUM_MUSHROOMGROUPS = 25;
    const uint NUM_MUSHROOMS = 25;

    for (uint i = 0; i < NUM_MUSHROOMGROUPS; ++i)
    {
        // First create a scene node for the group. The individual mushrooms nodes will be created as children
        Node@ groupNode = scene_.CreateChild("MushroomGroup");
        groupNode.position = Vector3(Random(190.0f) - 95.0f, 0.0f, Random(190.0f) - 95.0f);

        for (uint j = 0; j < NUM_MUSHROOMS; ++j)
        {
            Node@ mushroomNode = groupNode.CreateChild("Mushroom");
            mushroomNode.position = Vector3(Random(25.0f) - 12.5f, 0.0f, Random(25.0f) - 12.5f);
            mushroomNode.rotation = Quaternion(0.0f, Random() * 360.0f, 0.0f);
            mushroomNode.SetScale(1.0f + Random() * 4.0f);
            StaticModel@ mushroomObject = mushroomNode.CreateComponent("StaticModel");
            mushroomObject.model = cache.GetResource("Model", "Models/Mushroom.mdl");
            mushroomObject.material = cache.GetResource("Material", "Materials/Mushroom.xml");
            mushroomObject.castShadows = true;
        }
    }

    // Create billboard sets (floating smoke)
    const uint NUM_BILLBOARDNODES = 25;
    const uint NUM_BILLBOARDS = 10;

    for (uint i = 0; i < NUM_BILLBOARDNODES; ++i)
    {
        Node@ smokeNode = scene_.CreateChild("Smoke");
        smokeNode.position = Vector3(Random(200.0f) - 100.0f, Random(20.0f) + 10.0f, Random(200.0f) - 100.0f);

        BillboardSet@ billboardObject = smokeNode.CreateComponent("BillboardSet");
        billboardObject.numBillboards = NUM_BILLBOARDS;
        billboardObject.material = cache.GetResource("Material", "Materials/LitSmoke.xml");
        billboardObject.sorted = true;

        for (uint j = 0; j < NUM_BILLBOARDS; ++j)
        {
            Billboard@ bb = billboardObject.billboards[j];
            bb.position = Vector3(Random(12.0f) - 6.0f, Random(8.0f) - 4.0f, Random(12.0f) - 6.0f);
            bb.size = Vector2(Random(2.0f) + 3.0f, Random(2.0f) + 3.0f);
            bb.rotation = Random() * 360.0f;
            bb.enabled = true;
        }

        // After modifying the billboards, they need to be "commited" so that the BillboardSet updates its internals
        billboardObject.Commit();
    }

    // Create shadow casting spotlights
    const uint NUM_LIGHTS = 9;

    for (uint i = 0; i < NUM_LIGHTS; ++i)
    {
        Node@ lightNode = scene_.CreateChild("SpotLight");
        Light@ light = lightNode.CreateComponent("Light");

        float angle = 0.0f;

        Vector3 position((i % 3) * 60.0f - 60.0f, 45.0f, (i / 3) * 60.0f - 60.0f);
        Color color(((i + 1) & 1) * 0.5f + 0.5f, (((i + 1) >> 1) & 1) * 0.5f + 0.5f, (((i + 1) >> 2) & 1) * 0.5f + 0.5f);

        lightNode.position = position;
        lightNode.direction = Vector3(Sin(angle), -1.5f, Cos(angle));

        light.lightType = LIGHT_SPOT;
        light.range = 90.0f;
        light.rampTexture = cache.GetResource("Texture2D", "Textures/RampExtreme.png");
        light.fov = 45.0f;
        light.color = color;
        light.specularIntensity = 1.0f;
        light.castShadows = true;
        light.shadowBias = BiasParameters(0.00002f, 0.0f);

        // Configure shadow fading for the lights. When they are far away enough, the lights eventually become unshadowed for
        // better GPU performance. Note that we could also set the maximum distance for each object to cast shadows
        light.shadowFadeDistance = 100.0f; // Fade start distance
        light.shadowDistance = 125.0f; // Fade end distance, shadows are disabled
        // Set half resolution for the shadow maps for increased performance
        light.shadowResolution = 0.5f;
        // The spot lights will not have anything near them, so move the near plane of the shadow camera farther
        // for better shadow depth resolution
        light.shadowNearFarRatio = 0.01f;
    }

    // Create the camera. Limit far clip distance to match the fog
    cameraNode = scene_.CreateChild("Camera");
    Camera@ camera = cameraNode.CreateComponent("Camera");
    camera.farClip = 300.0f;

    // Set an initial position for the camera scene node above the plane
    cameraNode.position = Vector3(0.0f, 5.0f, 0.0f);
}

void CreateInstructions()
{
    // Construct new Text object, set string to display and font to use
    Text@ instructionText = ui.root.CreateChild("Text");
    instructionText.text =
        "Use WASD keys and mouse to move\n"
        "Space to toggle debug geometry";
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

    // Toggle debug geometry with space
    if (input.keyPress[KEY_SPACE])
        drawDebug = !drawDebug;
}

void AnimateScene(float timeStep)
{
    // Get the light and billboard scene nodes
    Array<Node@> lightNodes = scene_.GetChildrenWithComponent("Light");
    Array<Node@> billboardNodes = scene_.GetChildrenWithComponent("BillboardSet");

    const float LIGHT_ROTATION_SPEED = 20.0f;
    const float BILLBOARD_ROTATION_SPEED = 50.0f;

    // Rotate the lights around the world Y-axis
    for (uint i = 0; i < lightNodes.length; ++i)
        lightNodes[i].Rotate(Quaternion(0.0f, LIGHT_ROTATION_SPEED * timeStep, 0.0f), TS_WORLD);

    // Rotate the individual billboards within the billboard sets, then recommit to make the changes visible
    for (uint i = 0; i < billboardNodes.length; ++i)
    {
        BillboardSet@ billboardObject = billboardNodes[i].GetComponent("BillboardSet");

        for (uint j = 0; j < billboardObject.numBillboards; ++j)
        {
            Billboard@ bb = billboardObject.billboards[j];
            bb.rotation += BILLBOARD_ROTATION_SPEED * timeStep;
        }

        billboardObject.Commit();
    }
}

void HandleUpdate(StringHash eventType, VariantMap& eventData)
{
    // Take the frame time step, which is stored as a float
    float timeStep = eventData["TimeStep"].GetFloat();

    // Move the camera and animate the scene, scale movement with time step
    MoveCamera(timeStep);
    AnimateScene(timeStep);
}

void HandlePostRenderUpdate(StringHash eventType, VariantMap& eventData)
{
    // If draw debug mode is enabled, draw viewport debug geometry. This time use depth test, as otherwise the result becomes
    // hard to interpret due to large object count
    if (drawDebug)
        renderer.DrawDebugGeometry(true);
}

// Create XML patch instructions for screen joystick layout specific to this sample app
String patchInstructions =
        "<patch>" +
        "    <remove sel=\"/element/element[./attribute[@name='Name' and @value='Button1']]/attribute[@name='Is Visible']\" />" +
        "    <replace sel=\"/element/element[./attribute[@name='Name' and @value='Button1']]/element[./attribute[@name='Name' and @value='Label']]/attribute[@name='Text']/@value\">Debug</replace>" +
        "    <add sel=\"/element/element[./attribute[@name='Name' and @value='Button1']]\">" +
        "        <element type=\"Text\">" +
        "            <attribute name=\"Name\" value=\"KeyBinding\" />" +
        "            <attribute name=\"Text\" value=\"SPACE\" />" +
        "        </element>" +
        "    </add>" +
        "</patch>";
