// Urho2D platformer example.
// This sample demonstrates:
//    - Creating an orthogonal 2D scene with tile map
//    - Displaying the scene using the Renderer subsystem
//    - Handling keyboard to move a character and zoom 2D camera
//    - Generating physics shapes from the tmx file's objects
//    - Using physics to move the character
// Note that this sample uses some functions from Sample2D utility class.

#include "Scripts/Utilities/Sample.as"
#include "Scripts/Utilities/Sample2D.as"


void Start()
{
    // Execute the common startup for samples
    SampleStart();

    // Create the scene content
    CreateScene();

    // Create the UI content
    CreateInstructions("Use WASD keys or Arrows to move\nPageUp/PageDown/MouseWheel to zoom\nF5/F7 to save/reload scene\n'Z' to toggle debug geometry\nSpace to fight");

    // Hook up to the frame update events
    SubscribeToEvents();
}

void CreateScene()
{
    scene_ = Scene();

    // Create the Octree, DebugRenderer and PhysicsWorld2D component to the scene
    scene_.CreateComponent("Octree");
    scene_.CreateComponent("DebugRenderer");
    PhysicsWorld2D@ physicsWorld = scene_.CreateComponent("PhysicsWorld2D");

    // Create camera
    cameraNode = Node();
    Camera@ camera = cameraNode.CreateComponent("Camera");
    camera.orthographic = true;
    camera.orthoSize = graphics.height * PIXEL_SIZE;
    camera.zoom = 1.8f * Min(graphics.width / 1280.0f, graphics.height / 800.0f); // Set zoom according to user's resolution to ensure full visibility (initial zoom (1.8) is set for full visibility at 1280x800 resolution)

    // Setup the viewport for displaying the scene
    renderer.viewports[0] = Viewport(scene_, camera);
    renderer.defaultZone.fogColor = Color(0.2f, 0.2f, 0.2f); // Set background color for the scene

    // Get tmx file
    TmxFile2D@ tmxFile = cache.GetResource("TmxFile2D", "Urho2D/Tilesets/Ortho.tmx");
    if (tmxFile is null)
        return;

    Node@ tileMapNode = scene_.CreateChild("TileMap");
    TileMap2D@ tileMap = tileMapNode.CreateComponent("TileMap2D");
    tileMap.tmxFile = tmxFile;
    TileMapInfo2D@ info = tileMap.info;

    // Set "Background" layer as lowest (currently not used as we can't control layer opacity)
    TileMapLayer2D@ backgroundLayer = tileMap.GetLayer(2);
    backgroundLayer.drawOrder = -1;

    // Get top layer ("Physics") which stores the objects for shapes
    TileMapLayer2D@ tileMapLayer = tileMap.GetLayer(tileMap.numLayers - 1);

    // Generate physics collision shapes from the tmx file's objects located in "Physics" layer
    CreateCollisionShapesFromTMXObjects(tileMapNode, tileMapLayer, info);

    // Get "Enemies" layer which stores the placeholder objects for enemies and their paths
    TileMapLayer2D@ enemiesLayer = tileMap.GetLayer(tileMap.numLayers - 2);

    // Create enemy (will be cloned at each placeholder)
    Node@ enemyNode = CreateEnemy();

    // Instantiate enemies at each placeholder (in this sample, placeholders are Poly Line objects defining start and end points)
    for (uint i=0; i < enemiesLayer.numObjects; ++i)
    {
        TileMapObject2D@ enemyObject = enemiesLayer.GetObject(i); // Get placeholder object (TileMapObject2D)
        if (enemyObject.objectType != OT_POLYLINE)
        {
            log.Warning("A non Poly Line Object has been found in 'Enemies' layer and skipped");
            continue;
        }
        Node@ enemyClone = scene_.GetChild("Enemy").Clone();
        Vector2 offset = Vector2(0, 0.15);
        enemyClone.position2D = enemyObject.GetPoint(0) + offset;
        enemyClone.CreateScriptObject(scriptFile, "Mover"); // Create script object that handles enemy translation
        Mover@ mover = cast<Mover>(enemyClone.scriptObject);
        mover.path = CreatePathFromPoints(enemyObject); // Set path from points
        // Override default speed
        if (enemyObject.HasProperty("Speed"))
            mover.speed = enemyObject.GetProperty("Speed").ToFloat();
    }

    // Get "Coins" layer which stores the placeholder objects for coins
    TileMapLayer2D@ coinsLayer = tileMap.GetLayer(tileMap.numLayers - 3);

    // Create coin (will be cloned at each placeholder)
    Node@ coinNode = CreateCoin();

    // Instantiate coins to pick at each placeholder
    for (uint i=0; i < coinsLayer.numObjects; ++i)
    {
        TileMapObject2D@ coinObject = coinsLayer.GetObject(i); // Get placeholder object
        Node@ coinClone = coinNode.Clone();
        coinClone.position2D = coinObject.position + coinObject.size / 2 + Vector2(0.0f, 0.15f);
    }

    // Get "MovingPlatforms" layer which stores the placeholder objects for moving platforms
    TileMapLayer2D@ platformsLayer = tileMap.GetLayer(tileMap.numLayers - 4);

    // Create platform (will be cloned at each placeholder)
    Node@ platformNode = CreateMovingPlatform();

    // Instantiate moving platforms at each placeholder
    for (uint i=0; i < platformsLayer.numObjects; ++i)
    {
        TileMapObject2D@ platformObject = platformsLayer.GetObject(i); // Get placeholder object
        if (platformObject.objectType != OT_POLYLINE)
        {
            log.Warning("A non Poly Line Object has been found in 'MovingPlatforms' layer and skipped");
            continue;
        }
        Node@ platformClone = platformNode.Clone();
        platformClone.position2D = platformObject.GetPoint(0);
        platformClone.CreateScriptObject(scriptFile, "Mover"); // Create script object that handles platform translation
        Mover@ mover = cast<Mover>(platformClone.scriptObject);
        mover.path = CreatePathFromPoints(platformObject); // Set path from points
        // Override default speed
        if (platformObject.HasProperty("Speed"))
            mover.speed = platformObject.GetProperty("Speed").ToFloat();
    }

    // Create Spriter Imp character (from sample 33_SpriterAnimation)
    CreateCharacter(info, true, 0.8f, Vector3(1.0f, 23.0f, 0.0f));
}

Node@ CreateEnemy()
{
    Node@ node = scene_.CreateChild("Enemy");
    StaticSprite2D@ staticSprite = node.CreateComponent("StaticSprite2D");
    staticSprite.sprite = cache.GetResource("Sprite2D", "Urho2D/Aster.png");
    RigidBody2D@ body = node.CreateComponent("RigidBody2D");
    body.bodyType = BT_STATIC;
    CollisionCircle2D@ shape = node.CreateComponent("CollisionCircle2D"); // Create circle shape
    shape.radius = 0.32f; // Set radius
    return node;
}

Node@ CreateCoin()
{
    Node@ node = scene_.CreateChild("Coin");
    node.SetScale(0.5);
    AnimatedSprite2D@ animatedSprite = node.CreateComponent("AnimatedSprite2D");
    animatedSprite.SetAnimation(cache.GetResource("AnimationSet2D", "Urho2D/GoldIcon.scml"), "idle"); // Get scml file and Play "idle" anim
    RigidBody2D@ body = node.CreateComponent("RigidBody2D");
    body.bodyType = BT_STATIC;
    CollisionCircle2D@ shape = node.CreateComponent("CollisionCircle2D"); // Create circle shape
    shape.radius = 0.32f; // Set radius
    shape.trigger = true;
    return node;
}

Node@ CreateMovingPlatform()
{
    Node@ node = scene_.CreateChild("MovingPlatform");
    node.scale = Vector3(3.0f, 1.0f, 0.0f);
    StaticSprite2D@ staticSprite = node.CreateComponent("StaticSprite2D");
    staticSprite.sprite = cache.GetResource("Sprite2D", "Urho2D/Box.png");
    RigidBody2D@ body = node.CreateComponent("RigidBody2D");
    body.bodyType = BT_STATIC;
    CollisionBox2D@ shape = node.CreateComponent("CollisionBox2D"); // Create rectangular shape
    shape.size = Vector2(0.32f, 0.32f); // Set box size
    shape.friction = 0.8f; // Set friction
    return node;
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
        File saveFile(fileSystem.programDir + "Data/Scenes/TileMap.xml", FILE_WRITE);
        scene_.SaveXML(saveFile);
    }
    if (input.keyPress[KEY_F7])
    {
        File loadFile(fileSystem.programDir + "Data/Scenes/TileMap.xml", FILE_READ);
        scene_.LoadXML(loadFile);
        // After loading we have to reacquire the character2D scene node, as it has been recreated
        // Simply find by name as there's only one of them
        character2DNode = scene_.GetChild("Imp", true);
        if (character2DNode is null)
            return;
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
    }
}

// Character2D script object class
class Character2D : ScriptObject
{
    void Update(float timeStep)
    {
        if (character2DNode is null)
            return;

        AnimatedSprite2D@ animatedSprite = character2DNode.GetComponent("AnimatedSprite2D");
        RigidBody2D@ body = character2DNode.GetComponent("RigidBody2D");

        // Set direction
        Vector2 moveDir = Vector2(0.0f, 0.0f); // Reset

        if (input.keyDown['A'] || input.keyDown[KEY_LEFT])
        {
            moveDir = moveDir + Vector2(-1.0f, 0.0f);
            animatedSprite.flipX = false; // Flip sprite (reset to default play on the X axis);
        }

        if (input.keyDown['D'] || input.keyDown[KEY_RIGHT])
        {
            moveDir = moveDir + Vector2(1.0f, 0.0f);
            animatedSprite.flipX = true; // Flip sprite (flip animation on the X axis)
        }

        if (input.keyPress['W'] || input.keyPress[KEY_UP]) // Jump
        {
            float jumpForce = 50.0f;
            if (moveDir.Equals(Vector2(0.0f, 0.0f)))
                jumpForce = 35.0f;
            moveDir = moveDir + Vector2(0.0f, jumpForce);
        }

        // Move
        if (!moveDir.Equals(Vector2(0.0f, 0.0f)))
        {
            body.ApplyForceToCenter(moveDir * MOVE_SPEED, true);
            body.ApplyForceToCenter(body.linearVelocity * -10.0f, true); // Limit max speed and facilitate return to rest
        }

        // Animate
        if (input.keyDown[KEY_SPACE])
        {
            if (animatedSprite.animation != "attack")
            {
                animatedSprite.SetAnimation("attack", LM_FORCE_LOOPED);
                animatedSprite.speed = 1.5f;
            }
        }
        else if (!moveDir.Equals(Vector2(0.0f, 0.0f)))
        {
            if (animatedSprite.animation != "run")
                animatedSprite.SetAnimation("run", LM_FORCE_LOOPED);
        }
        else if (animatedSprite.animation != "idle")
        {
            animatedSprite.SetAnimation("idle", LM_FORCE_LOOPED);
        }
    }
}