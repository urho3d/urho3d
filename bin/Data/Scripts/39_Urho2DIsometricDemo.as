// Urho2D tile map example.
// This sample demonstrates:
//     - Creating an isometric 2D scene with tile map
//     - Displaying the scene using the Renderer subsystem
//     - Handling keyboard to move a 2D character and zoom 2D camera
//     - Generating physics shapes from the tmx file's objects
//    - Displaying debug geometry for physics and tile map
// Note that this sample uses some functions from Sample2D utility class.

#include "Scripts/Utilities/Sample.as"
#include "Scripts/Utilities/2D/Sample2D.as"


void Start()
{
    // Execute the common startup for samples
    SampleStart();

    // Create the scene content
    CreateScene();

    // Create the UI content
    CreateUIContent("ISOMETRIC 2.5D DEMO");

    // Hook up to the frame update events
    SubscribeToEvents();
}

void CreateScene()
{
    scene_ = Scene();

    // Create the Octree, DebugRenderer and PhysicsWorld2D components to the scene
    scene_.CreateComponent("Octree");
    scene_.CreateComponent("DebugRenderer");
    PhysicsWorld2D@ physicsWorld = scene_.CreateComponent("PhysicsWorld2D");
    physicsWorld.gravity = Vector2(0.0f, 0.0f); // Neutralize gravity as the character will always be grounded

    // Create camera and define viewport
    cameraNode = Node();
    Camera@ camera = cameraNode.CreateComponent("Camera");
    camera.orthographic = true;
    camera.orthoSize = graphics.height * PIXEL_SIZE;
    camera.zoom = 2.0f * Min(graphics.width / 1280.0f, graphics.height / 800.0f); // Set zoom according to user's resolution to ensure full visibility (initial zoom (2.0) is set for full visibility at 1280x800 resolution)
    renderer.viewports[0] = Viewport(scene_, camera);

    // Create tile map from tmx file
    TmxFile2D@ tmxFile = cache.GetResource("TmxFile2D", "Urho2D/Tilesets/atrium.tmx");
    if (tmxFile is null)
        return;

    Node@ tileMapNode = scene_.CreateChild("TileMap");
    TileMap2D@ tileMap = tileMapNode.CreateComponent("TileMap2D");
    tileMap.tmxFile = tmxFile;
    TileMapInfo2D@ info = tileMap.info;

    // Create Spriter Imp character (from sample 33_SpriterAnimation)
    CreateCharacter(info, true, 0.0f, Vector3(-5.0f, 11.0f, 0.0f), 0.15f);

    // Generate physics collision shapes from the tmx file's objects located in "Physics" (top) layer
    TileMapLayer2D@ tileMapLayer = tileMap.GetLayer(tileMap.numLayers - 1);
    CreateCollisionShapesFromTMXObjects(tileMapNode, tileMapLayer, info);

    // Instantiate enemies and moving platforms at each placeholder of "MovingEntities" layer (placeholders are Poly Line objects defining a path from points)
    PopulateMovingEntities(tileMap.GetLayer(tileMap.numLayers - 2));

    // Check when scene is rendered
    SubscribeToEvent("EndRendering", "HandleSceneRendered");
}

void HandleSceneRendered()
{
    UnsubscribeFromEvent("EndRendering");
    // Save the scene so we can reload it later
    SaveScene(true);
    // Pause the scene as long as the UI is hiding it
    scene_.updateEnabled = false;
}

void SubscribeToEvents()
{
    // Subscribe HandleUpdate() function for processing update events
    SubscribeToEvent("Update", "HandleUpdate");

    // Subscribe HandlePostUpdate() function for processing post update events
    SubscribeToEvent("PostUpdate", "HandlePostUpdate");

    // Subscribe to PostRenderUpdate to draw physics shapes
    SubscribeToEvent("PostRenderUpdate", "HandlePostRenderUpdate");

    // Unsubscribe the SceneUpdate event from base class to prevent camera pitch and yaw in 2D sample
    UnsubscribeFromEvent("SceneUpdate");
}

void HandleUpdate(StringHash eventType, VariantMap& eventData)
{
    // Zoom in/out
    if (cameraNode !is null)
        Zoom(cameraNode.GetComponent("Camera"));

    // Toggle debug geometry with spacebar
    if (input.keyPress[KEY_Z]) drawDebug = !drawDebug;

    // Check for loading / saving the scene
    if (input.keyPress[KEY_F5])
    {
        SaveScene(false);
    }
    if (input.keyPress[KEY_F7])
    {
        ReloadScene(false);
    }
}

void HandlePostUpdate(StringHash eventType, VariantMap& eventData)
{
    if (character2DNode is null || cameraNode is null)
        return;
    cameraNode.position = Vector3(character2DNode.position.x, character2DNode.position.y, -10.0f); // Camera tracks character
}

void HandlePostRenderUpdate(StringHash eventType, VariantMap& eventData)
{
    if (drawDebug)
    {
        PhysicsWorld2D@ physicsWorld = scene_.GetComponent("PhysicsWorld2D");
        physicsWorld.DrawDebugGeometry();
        Node@ tileMapNode = scene_.GetChild("TileMap", true);
        TileMap2D@ map = tileMapNode.GetComponent("TileMap2D");
        map.DrawDebugGeometry(scene_.GetComponent("DebugRenderer"), false);
    }
}

// Character2D script object class
class Character2D : ScriptObject
{
    bool wounded = false;
    bool killed = false;
    float timer = 0.0f;
    int maxCoins = 0;
    int remainingCoins = 0;
    int remainingLifes = 3;

    void Update(float timeStep)
    {
        if (character2DNode is null)
            return;

        AnimatedSprite2D@ animatedSprite = character2DNode.GetComponent("AnimatedSprite2D");

        // Set direction
        Vector3 moveDir = Vector3(0.0f, 0.0f, 0.0f); // Reset
        float speedX = Clamp(MOVE_SPEED_X / zoom, 0.4f, 1.0f);
        float speedY = speedX;

        if (input.keyDown['A'] || input.keyDown[KEY_LEFT])
        {
            moveDir = moveDir + Vector3(-1.0f, 0.0f, 0.0f) * speedX;
            animatedSprite.flipX = false; // Flip sprite (reset to default play on the X axis)
        }
        if (input.keyDown['D'] || input.keyDown[KEY_RIGHT])
        {
            moveDir = moveDir + Vector3(1.0f, 0.0f, 0.0f) * speedX;
            animatedSprite.flipX = true; // Flip sprite (flip animation on the X axis)
        }

        if (!moveDir.Equals(Vector3(0.0f, 0.0f, 0.0f)))
            speedY = speedX * MOVE_SPEED_SCALE;

        if (input.keyDown['W'] || input.keyDown[KEY_UP])
            moveDir = moveDir + Vector3(0.0f, 1.0f, 0.0f) * speedY;
        if (input.keyDown['S'] || input.keyDown[KEY_DOWN])
            moveDir = moveDir + Vector3(0.0f, -1.0f, 0.0f) * speedY;

        // Move
        if (!moveDir.Equals(Vector3(0.0f, 0.0f, 0.0f)))
            character2DNode.Translate(moveDir * timeStep);

        // Animate
        if (input.keyDown[KEY_SPACE])
        {
            if (animatedSprite.animation != "attack")
                animatedSprite.SetAnimation("attack", LM_FORCE_LOOPED);
        }
        else if (!moveDir.Equals(Vector3(0.0f, 0.0f, 0.0f)))
        {
            if (animatedSprite.animation != "run")
                animatedSprite.SetAnimation("run");
        }
        else if (animatedSprite.animation != "idle")
        {
            animatedSprite.SetAnimation("idle");
        }
    }
}