// Urho2D tile map example.
// This sample demonstrates:
//     - Creating a 2D scene with tile map
//     - Displaying the scene using the Renderer subsystem
//     - Handling keyboard to move and zoom 2D camera
//     - Interacting with the tile map

#include "Scripts/Utilities/Sample.as"

void Start()
{
    // Execute the common startup for samples
    SampleStart();

    // Enable OS cursor
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
    camera.zoom = 1.0f * Min(graphics.width / 1280.0f, graphics.height / 800.0f); // Set zoom according to user's resolution to ensure full visibility (initial zoom (1.0) is set for full visibility at 1280x800 resolution)

    // Get tmx file
    TmxFile2D@ tmxFile = cache.GetResource("TmxFile2D", "Urho2D/isometric_grass_and_water.tmx");
    if (tmxFile is null)
        return;

    Node@ tileMapNode = scene_.CreateChild("TileMap");
    tileMapNode.position = Vector3(0.0f, 0.0f, -1.0f);

    TileMap2D@ tileMap = tileMapNode.CreateComponent("TileMap2D");
    tileMap.tmxFile = tmxFile;

    // Set camera's position;
    TileMapInfo2D@ info = tileMap.info;
    float x = info.mapWidth * 0.5f;
    float y = info.mapHeight * 0.5f;
    cameraNode.position = Vector3(x, y, -10.0f);
}

void CreateInstructions()
{
    // Construct new Text object, set string to display and font to use
    Text@ instructionText = ui.root.CreateChild("Text");
    instructionText.text = "Use WASD keys and mouse to move, Use PageUp PageDown to zoom.\n LMB to remove a tile, RMB to swap grass and water.";
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
    if (input.keyDown[KEY_W])
        cameraNode.Translate(Vector3(0.0f, 1.0f, 0.0f) * MOVE_SPEED * timeStep);
    if (input.keyDown[KEY_S])
        cameraNode.Translate(Vector3(0.0f, -1.0f, 0.0f) * MOVE_SPEED * timeStep);
    if (input.keyDown[KEY_A])
        cameraNode.Translate(Vector3(-1.0f, 0.0f, 0.0f) * MOVE_SPEED * timeStep);
    if (input.keyDown[KEY_D])
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

    // Listen to mouse clicks
    SubscribeToEvent("MouseButtonDown", "HandleMouseButtonDown");

    // Unsubscribe the SceneUpdate event from base class to prevent camera pitch and yaw in 2D sample
    UnsubscribeFromEvent("SceneUpdate");
}

void HandleUpdate(StringHash eventType, VariantMap& eventData)
{
    // Take the frame time step, which is stored as a float
    float timeStep = eventData["TimeStep"].GetFloat();

    // Move the camera, scale movement with time step
    MoveCamera(timeStep);
}

void HandleMouseButtonDown(StringHash eventType, VariantMap& eventData)
{
    Node@ tileMapNode = scene_.GetChild("TileMap", true);
    TileMap2D@ map = tileMapNode.GetComponent("TileMap2D");
    TileMapLayer2D@ layer = map.GetLayer(0);

    Vector2 pos = GetMousePositionXY();
    int x, y;
    if (map.PositionToTileIndex(x, y, pos))
    {
        // Get tile's sprite. Note that layer.GetTile(x, y).sprite is read-only, so we get the sprite through tile's node
        Node@ n = layer.GetTileNode(x, y);
        if (n is null)
            return;
        StaticSprite2D@ sprite = n.GetComponent("StaticSprite2D");

        if (input.mouseButtonDown[MOUSEB_RIGHT])
        {
            // Swap grass and water
            if (layer.GetTile(x, y).gid < 9) // First 8 sprites in the "isometric_grass_and_water.png" tileset are mostly grass and from 9 to 24 they are mostly water
                sprite.sprite = layer.GetTile(0, 0).sprite; // Replace grass by water sprite used in top tile
            else sprite.sprite = layer.GetTile(24, 24).sprite; // Replace water by grass sprite used in bottom tile
        }
        else sprite.sprite = null; // 'Remove' sprite
    }
}

Vector2 GetMousePositionXY()
{
    Camera@ camera = cameraNode.GetComponent("Camera");
    Vector3 screenPoint = Vector3(float(input.mousePosition.x) / graphics.width, float(input.mousePosition.y) / graphics.height, 10.0f);
    Vector3 worldPoint = camera.ScreenToWorldPoint(screenPoint);
    return Vector2(worldPoint.x, worldPoint.y);
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
