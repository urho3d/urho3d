// Convenient functions for Urho2D and Physics2D samples:
//    - Generate collision shapes from a tmx file objects
//    - Create Spriter Imp character
//    - Load Mover script object class from file
//    - Create enemies, coins and platforms to tile map placeholders
//    - Handle camera zoom using PageUp, PageDown and MouseWheel
//    - Create UI interface
//    - Create a particle emitter attached to a given node
//    - Play a non-looping sound effect
//    - Load/Save the scene
//    - Set global variables
//    - Set XML patch instructions for screen joystick

#include "Scripts/Utilities/2D/Mover.as"

float CAMERA_MIN_DIST = 0.1f;
float CAMERA_MAX_DIST = 6.0f;

const float MOVE_SPEED = 23.0f; // Movement speed as world units per second
const float MOVE_SPEED_X = 1.5f; // Movement speed as world units per second
float MOVE_SPEED_SCALE = 1.0f; // Scaling factor based on tiles' aspect ratio

const int LIFES = 3;
float zoom = 2.0f; // Speed is scaled according to zoom
String demoFilename = "";
Node@ character2DNode;


void CreateCollisionShapesFromTMXObjects(Node@ tileMapNode, TileMapLayer2D@ tileMapLayer, const TileMapInfo2D@ info)
{
    // Create rigid body to the root node
    RigidBody2D@ body = tileMapNode.CreateComponent("RigidBody2D");
    body.bodyType = BT_STATIC;

    // Generate physics collision shapes and rigid bodies from the tmx file's objects located in "Physics" layer
    for (uint i = 0; i < tileMapLayer.numObjects; ++i)
    {
        TileMapObject2D@ tileMapObject = tileMapLayer.GetObject(i); // Get physics objects

        // Create collision shape from tmx object
        switch (tileMapObject.objectType)
        {
            case OT_RECTANGLE:
                CreateRectangleShape(tileMapNode, tileMapObject, tileMapObject.size, info);
                continue;
            case OT_ELLIPSE:
                CreateCircleShape(tileMapNode, tileMapObject, tileMapObject.size.x / 2, info); // Ellipse is built as a Circle shape as it doesn't exist in Box2D
                continue;
            case OT_POLYGON:
                CreatePolygonShape(tileMapNode, tileMapObject);
                continue;
            case OT_POLYLINE:
                CreatePolyLineShape(tileMapNode, tileMapObject);
                continue;
            default:
                continue;
        }
    }
}

CollisionBox2D@ CreateRectangleShape(Node@ node, TileMapObject2D@ object, Vector2 size, const TileMapInfo2D@ info)
{
    CollisionBox2D@ shape = node.CreateComponent("CollisionBox2D");
    shape.size = size;
    if (info.orientation == O_ORTHOGONAL)
        shape.center = object.position + size / 2;
    else
    {
        shape.center = object.position + Vector2(info.tileWidth / 2, 0.0f);
        shape.angle = 45.0f; // If our tile map is isometric then shape is losange
    }
    shape.friction = 0.8f;
    if (object.HasProperty("Friction"))
        shape.friction = object.GetProperty("Friction").ToFloat();
    return shape;
}

CollisionCircle2D@ CreateCircleShape(Node@ node, TileMapObject2D@ object, float radius, const TileMapInfo2D@ info)
{
    CollisionCircle2D@ shape = node.CreateComponent("CollisionCircle2D");
    Vector2 size = object.size;
    shape.radius = radius;
    if (info.orientation == O_ORTHOGONAL)
        shape.center = object.position + size / 2;
    else
    {
        shape.center = object.position + Vector2(info.tileWidth / 2, 0.0f);
    }
    shape.friction = 0.8f;
    if (object.HasProperty("Friction"))
        shape.friction = object.GetProperty("Friction").ToFloat();
    return shape;
}

CollisionPolygon2D@ CreatePolygonShape(Node@ node, const TileMapObject2D@ object)
{
    CollisionPolygon2D@ shape = node.CreateComponent("CollisionPolygon2D");
    uint numVertices = object.numPoints;
    shape.vertexCount = numVertices;
    for (uint i = 0; i < numVertices; ++i)
        shape.SetVertex(i, object.GetPoint(i));
    shape.friction = 0.8f;
    if (object.HasProperty("Friction"))
        shape.friction = object.GetProperty("Friction").ToFloat();
    return shape;
}

void CreatePolyLineShape(Node@ node, TileMapObject2D@ object)
{
/*
    CollisionChain2D@ shape = node.CreateComponent("CollisionChain2D");
    uint numVertices = object.numPoints;
    shape.vertexCount = numVertices;
    for (uint i = 0; i < numVertices; ++i)
        shape.SetVertex(i, object.GetPoint(i));
    shape.friction = 0.8f;
    if (object.HasProperty("Friction"))
        shape.friction = object.GetProperty("Friction").ToFloat();
    return shape;
*/

    // Latest Box2D supports only one sided chains with ghost vertices, use two sided edges instead.
    // But this can cause stuck at the edges ends https://box2d.org/posts/2020/06/ghost-collisions/

    int numVertices = object.numPoints;

    for (int i = 1; i < numVertices; ++i)
    {
        CollisionEdge2D@ shape = node.CreateComponent("CollisionEdge2D");
        shape.SetVertices(object.GetPoint(i - 1), object.GetPoint(i));
        shape.friction = 0.8f;
        if (object.HasProperty("Friction"))
            shape.friction = object.GetProperty("Friction").ToFloat();
    }
}

void CreateCharacter(const TileMapInfo2D@ info, bool createObject, float friction, Vector3 position, float scale)
{
    character2DNode = scene_.CreateChild("Imp");
    character2DNode.position = position;
    character2DNode.SetScale(scale);
    AnimatedSprite2D@ animatedSprite = character2DNode.CreateComponent("AnimatedSprite2D");
    
    AnimationSet2D@ spriterAnimationSet = cache.GetResource("AnimationSet2D", "Urho2D/imp/imp.scml");
    if (spriterAnimationSet is null)
        return;

    animatedSprite.animationSet = spriterAnimationSet;
    animatedSprite.SetAnimation("idle"); // Get scml file and Play "idle" anim
    animatedSprite.layer = 3; // Put character over tile map (which is on layer 0) and over Orcs (which are on layer 2)
    RigidBody2D@ characterBody = character2DNode.CreateComponent("RigidBody2D");
    characterBody.bodyType = BT_DYNAMIC;
    characterBody.allowSleep = false;
    characterBody.fixedRotation = true;
    CollisionCircle2D@ shape = character2DNode.CreateComponent("CollisionCircle2D");
    shape.radius = 1.1f; // Set shape size
    shape.friction = friction; // Set friction
    shape.restitution = 0.1f; // Bounce
    shape.density = 6.6f;

    if (createObject)
        character2DNode.CreateScriptObject(scriptFile, "Character2D"); // Create a ScriptObject to handle character behavior

    // Scale character's speed on the Y axis according to tiles' aspect ratio (for isometric only)
    MOVE_SPEED_SCALE = info.tileHeight / info.tileWidth;
}

Node@ CreateTrigger()
{
    Node@ node = scene_.CreateChild(); // Clones will be renamed according to object type
    RigidBody2D@ body = node.CreateComponent("RigidBody2D");
    body.bodyType = BT_STATIC;
    CollisionBox2D@ shape = node.CreateComponent("CollisionBox2D"); // Create box shape
    shape.trigger = true;
    return node;
}

Node@ CreateEnemy()
{
    Node@ node = scene_.CreateChild("Enemy");
    StaticSprite2D@ staticSprite = node.CreateComponent("StaticSprite2D");
    staticSprite.sprite = cache.GetResource("Sprite2D", "Urho2D/Aster.png");
    RigidBody2D@ body = node.CreateComponent("RigidBody2D");
    body.bodyType = BT_STATIC;
    CollisionCircle2D@ shape = node.CreateComponent("CollisionCircle2D"); // Create circle shape
    shape.radius = 0.25f; // Set radius
    return node;
}

Node@ CreateOrc()
{
    Node@ node = scene_.CreateChild("Orc");
    node.scale = character2DNode.scale; // Use same scale as player character
    AnimatedSprite2D@ animatedSprite = node.CreateComponent("AnimatedSprite2D");

    AnimationSet2D@ spriterAnimationSet = cache.GetResource("AnimationSet2D", "Urho2D/Orc/Orc.scml");
    if (spriterAnimationSet is null)
        return null;

    animatedSprite.animationSet = spriterAnimationSet;
    animatedSprite.SetAnimation("run"); // Get scml file and Play "run" anim
    animatedSprite.layer = 2; // Make orc always visible
    RigidBody2D@ body = node.CreateComponent("RigidBody2D");
    CollisionCircle2D@ shape = node.CreateComponent("CollisionCircle2D"); // Create circle shape
    shape.radius = 1.3f; // Set shape size
    shape.trigger = true;
    return node;
}

Node@ CreateCoin()
{
    Node@ node = scene_.CreateChild("Coin");
    node.SetScale(0.5);
    AnimatedSprite2D@ animatedSprite = node.CreateComponent("AnimatedSprite2D");
    animatedSprite.layer = 4;
    AnimationSet2D@ spriterAnimationSet = cache.GetResource("AnimationSet2D", "Urho2D/GoldIcon.scml");
    if (spriterAnimationSet is null)
        return null;

    animatedSprite.animationSet = spriterAnimationSet;
    animatedSprite.SetAnimation("idle"); // Get scml file and Play "idle" anim
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
    CollisionBox2D@ shape = node.CreateComponent("CollisionBox2D"); // Create box shape
    shape.size = Vector2(0.32f, 0.32f); // Set box size
    shape.friction = 0.8f; // Set friction
    return node;
}

void PopulateMovingEntities(TileMapLayer2D@ movingEntitiesLayer)
{
    // Create enemy, Orc and moving platform nodes (will be cloned at each placeholder)
    Node@ enemyNode = CreateEnemy();
    Node@ orcNode = CreateOrc();
    Node@ platformNode = CreateMovingPlatform();

    // Instantiate enemies and moving platforms at each placeholder (placeholders are Poly Line objects defining a path from points)
    for (uint i=0; i < movingEntitiesLayer.numObjects; ++i)
    {
        // Get placeholder object
        TileMapObject2D@ movingObject = movingEntitiesLayer.GetObject(i); // Get placeholder object
        if (movingObject.objectType == OT_POLYLINE)
        {
            // Clone the moving entity node and position it at placeholder point
            Node@ movingClone;
            Vector2 offset = Vector2(0.0f, 0.0f);
            if (movingObject.type == "Enemy")
            {
                movingClone = enemyNode.Clone();
                offset = Vector2(0.0f, -0.32f);
            }
            else if (movingObject.type == "Orc")
                movingClone = orcNode.Clone();
            else if (movingObject.type == "MovingPlatform")
                movingClone = platformNode.Clone();
            else
                continue;
            movingClone.position2D = movingObject.GetPoint(0) + offset;

            // Create script object that handles entity translation along its path (load from file included)
            Mover@ mover = cast<Mover>(movingClone.CreateScriptObject(scriptFile, "Mover"));

            // Set path from points
            mover.path = CreatePathFromPoints(movingObject, offset);

            // Override default speed
            if (movingObject.HasProperty("Speed"))
                mover.speed = movingObject.GetProperty("Speed").ToFloat();
        }
    }

    // Remove nodes used for cloning purpose
    enemyNode.Remove();
    orcNode.Remove();
    platformNode.Remove();
}

void PopulateCoins(TileMapLayer2D@ coinsLayer)
{
    // Create coin (will be cloned at each placeholder)
    Node@ coinNode = CreateCoin();

    // Instantiate coins to pick at each placeholder
    for (uint i=0; i < coinsLayer.numObjects; ++i)
    {
        TileMapObject2D@ coinObject = coinsLayer.GetObject(i); // Get placeholder object
        Node@ coinClone = coinNode.Clone();
        coinClone.position2D = coinObject.position + coinObject.size / 2 + Vector2(0.0f, 0.16f);
    }

    // Init coins counters
    Character2D@ character = cast<Character2D>(character2DNode.scriptObject);
    character.remainingCoins = coinsLayer.numObjects;
    character.maxCoins = coinsLayer.numObjects;

    // Remove node used for cloning purpose
    coinNode.Remove();
}

void PopulateTriggers(TileMapLayer2D@ triggersLayer)
{
    // Create trigger node (will be cloned at each placeholder)
    Node@ triggerNode = CreateTrigger();

    // Instantiate triggers at each placeholder (Rectangle objects)
    for (uint i=0; i < triggersLayer.numObjects; ++i)
    {
        TileMapObject2D@ triggerObject = triggersLayer.GetObject(i); // Get placeholder object
        if (triggerObject.objectType == OT_RECTANGLE)
        {
            Node@ triggerClone = triggerNode.Clone();
            triggerClone.name = triggerObject.type;
            CollisionBox2D@ shape = triggerClone.GetComponent("CollisionBox2D");
            shape.size = triggerObject.size;
            triggerClone.position2D = triggerObject.position + triggerObject.size / 2;
        }
    }
}

void Zoom(Camera@ camera)
{
    if (input.mouseMoveWheel != 0)
        camera.zoom = Clamp(camera.zoom + input.mouseMoveWheel * 0.1, CAMERA_MIN_DIST, CAMERA_MAX_DIST);

    if (input.keyDown[KEY_PAGEUP])
    {
        zoom = Clamp(camera.zoom * 1.01f, CAMERA_MIN_DIST, CAMERA_MAX_DIST);
        camera.zoom = zoom;
    }

    if (input.keyDown[KEY_PAGEDOWN])
    {
        zoom = Clamp(camera.zoom * 0.99f, CAMERA_MIN_DIST, CAMERA_MAX_DIST);
        camera.zoom = zoom;
    }
}

Vector2[] CreatePathFromPoints(TileMapObject2D@ object, Vector2 offset)
{
    Array<Vector2> path;
    for (uint i=0; i < object.numPoints; ++i)
        path.Push(object.GetPoint(i) + offset);
    return path;
}

void CreateUIContent(String demoTitle)
{
    // Set the default UI style and font
    ui.root.defaultStyle = cache.GetResource("XMLFile", "UI/DefaultStyle.xml");
    Font@ font = cache.GetResource("Font", "Fonts/Anonymous Pro.ttf");

    // We create in-game UIs (coins and lifes) first so that they are hidden by the fullscreen UI (we could also temporary hide them using SetVisible)

    // Create the UI for displaying the remaining coins
    BorderImage@ coinsUI = ui.root.CreateChild("BorderImage", "Coins");
    coinsUI.texture = cache.GetResource("Texture2D", "Urho2D/GoldIcon.png");
    coinsUI.SetSize(50, 50);
    coinsUI.imageRect = IntRect(0, 64, 60, 128);
    coinsUI.SetAlignment(HA_LEFT, VA_TOP);
    coinsUI.SetPosition(5, 5);
    Text@ coinsText = coinsUI.CreateChild("Text", "CoinsText");
    coinsText.SetAlignment(HA_CENTER, VA_CENTER);
    coinsText.SetFont(font, 24);
    coinsText.textEffect = TE_SHADOW;
    coinsText.text = cast<Character2D>(character2DNode.scriptObject).remainingCoins;

    // Create the UI for displaying the remaining lifes
    BorderImage@ lifeUI = ui.root.CreateChild("BorderImage", "Life");
    lifeUI.texture = cache.GetResource("Texture2D", "Urho2D/imp/imp_all.png");
    lifeUI.SetSize(70, 80);
    lifeUI.SetAlignment(HA_RIGHT, VA_TOP);
    lifeUI.SetPosition(-5, 5);
    Text@ lifeText = lifeUI.CreateChild("Text", "LifeText");
    lifeText.SetAlignment(HA_CENTER, VA_CENTER);
    lifeText.SetFont(font, 24);
    lifeText.textEffect = TE_SHADOW;
    lifeText.text = LIFES;

    // Create the fullscreen UI for start/end
    Window@ fullUI = ui.root.CreateChild("Window", "FullUI");
    fullUI.SetStyleAuto();
    fullUI.SetSize(ui.root.width, ui.root.height);
    fullUI.enabled = false; // Do not react to input, only the 'Exit' and 'Play' buttons will

    // Create the title
    BorderImage@ title = fullUI.CreateChild("BorderImage", "Title");
    title.SetMinSize(fullUI.width, 50);
    title.texture = cache.GetResource("Texture2D", "Textures/HeightMap.png");
    title.SetFullImageRect();
    title.SetAlignment(HA_CENTER, VA_TOP);
    Text@ titleText = title.CreateChild("Text", "TitleText");
    titleText.SetAlignment(HA_CENTER, VA_CENTER);
    titleText.SetFont(font, 24);
    titleText.text = demoTitle;

    // Create the image
    BorderImage@ spriteUI = fullUI.CreateChild("BorderImage", "Sprite");
    spriteUI.texture = cache.GetResource("Texture2D", "Urho2D/imp/imp_all.png");
    spriteUI.SetSize(238, 271);
    spriteUI.SetAlignment(HA_CENTER, VA_CENTER);
    spriteUI.SetPosition(0, - ui.root.height / 4);

    // Create the 'EXIT' button
    Button@ exitButton = ui.root.CreateChild("Button", "ExitButton");
    exitButton.SetStyleAuto();
    exitButton.focusMode = FM_RESETFOCUS;
    exitButton.SetSize(100, 50);
    exitButton.SetAlignment(HA_CENTER, VA_CENTER);
    exitButton.SetPosition(-100, 0);
    Text@ exitText = exitButton.CreateChild("Text", "ExitText");
    exitText.SetAlignment(HA_CENTER, VA_CENTER);
    exitText.SetFont(font, 24);
    exitText.text = "EXIT";
    SubscribeToEvent(exitButton, "Released", "HandleExitButton");

    // Create the 'PLAY' button
    Button@ playButton = ui.root.CreateChild("Button", "PlayButton");
    playButton.SetStyleAuto();
    playButton.focusMode = FM_RESETFOCUS;
    playButton.SetSize(100, 50);
    playButton.SetAlignment(HA_CENTER, VA_CENTER);
    playButton.SetPosition(100, 0);
    Text@ playText = playButton.CreateChild("Text", "PlayText");
    playText.SetAlignment(HA_CENTER, VA_CENTER);
    playText.SetFont(font, 24);
    playText.text = "PLAY";
    SubscribeToEvent(playButton, "Released", "HandlePlayButton");

    // Create the instructions
    Text@ instructionText = ui.root.CreateChild("Text", "Instructions");
    instructionText.SetFont(font, 15);
    instructionText.textAlignment = HA_CENTER; // Center rows in relation to each other
    instructionText.text = "Use WASD keys or Arrows to move\nPageUp/PageDown/MouseWheel to zoom\nF5/F7 to save/reload scene\n'Z' to toggle debug geometry\nSpace to fight";
    instructionText.SetAlignment(HA_CENTER, VA_CENTER);
    instructionText.SetPosition(0, ui.root.height / 4);

    // Show mouse cursor
    input.mouseVisible = true;
}

void HandleExitButton()
{
    engine.Exit();
}

void HandlePlayButton()
{
    // Remove fullscreen UI and unfreeze the scene
    if (ui.root.GetChild("FullUI", true) !is null)
    {
        ui.root.GetChild("FullUI", true).Remove();
        scene_.updateEnabled = true;
    }
    else
    {
        // Reload scene
        ReloadScene(true);
    }

    // Hide Instructions and Play/Exit buttons
    Text@ instructionText = ui.root.GetChild("Instructions", true);
    instructionText.text = "";
    Button@ exitButton = ui.root.GetChild("ExitButton", true);
    exitButton.visible = false;
    Button@ playButton = ui.root.GetChild("PlayButton", true);
    playButton.visible = false;

    // Hide mouse cursor
    input.mouseVisible = false;
}

void SaveScene(bool initial)
{
    String filename = demoFilename;
    if (!initial)
        filename = demoFilename + "InGame";

    File saveFile(fileSystem.programDir + "Data/Scenes/" + filename + ".xml", FILE_WRITE);
    scene_.SaveXML(saveFile);
}

void ReloadScene(bool reInit)
{
    String filename = demoFilename;
    if (!reInit)
        filename = demoFilename + "InGame";

    File loadFile(fileSystem.programDir + "Data/Scenes/" + filename + ".xml", FILE_READ);
    scene_.LoadXML(loadFile);
    // After loading we have to reacquire the character2D scene node, as it has been recreated
    // Simply find by name as there's only one of them
    character2DNode = scene_.GetChild("Imp", true);
    if (character2DNode is null)
        return;

    // Set what value to use depending whether reload is requested from 'PLAY' button (reInit=true) or 'F7' key (reInit=false)
    Character2D@ character = cast<Character2D>(character2DNode.scriptObject);
    int lifes = character.remainingLifes;
    int coins = character.remainingCoins;
    if (reInit)
    {
        lifes = LIFES;
        coins = character.maxCoins;
    }

    // Update lifes UI and variable
    Text@ lifeText = ui.root.GetChild("LifeText", true);
    lifeText.text = lifes;
    character.remainingLifes = lifes;

    // Update coins UI and variable
    Text@ coinsText = ui.root.GetChild("CoinsText", true);
    coinsText.text = coins;
    character.remainingCoins = coins;
}

void SpawnEffect(Node@ node)
{
    Node@ particleNode = node.CreateChild("Emitter");
    particleNode.SetScale(0.5 / node.scale.x);
    ParticleEmitter2D@ particleEmitter = particleNode.CreateComponent("ParticleEmitter2D");
    particleEmitter.effect = cache.GetResource("ParticleEffect2D", "Urho2D/sun.pex");
    particleEmitter.layer = 2;
}

void PlaySound(String soundName)
{
    Node@ soundNode = scene_.CreateChild("Sound");
    SoundSource@ source = soundNode.CreateComponent("SoundSource");
    source.Play(cache.GetResource("Sound", "Sounds/" + soundName));
}

void CreateBackgroundSprite(const TileMapInfo2D@ info, float scale, String texture, bool animate)
{
    Node@ node = scene_.CreateChild("Background");
    node.position = Vector3(info.mapWidth, info.mapHeight, 0) / 2;
    node.SetScale(scale);
    StaticSprite2D@ sprite = node.CreateComponent("StaticSprite2D");
    sprite.sprite = cache.GetResource("Sprite2D", texture);
    SetRandomSeed(time.systemTime); // Randomize from system clock
    sprite.color = Color(Random(0.0f, 1.0f), Random(0.0f, 1.0f), Random(0.0f, 1.0f), 1.0f);
    sprite.layer = -99;

    // Create rotation animation
    if (animate)
    {
        ValueAnimation@ animation = ValueAnimation();
        animation.SetKeyFrame(0, Variant(Quaternion(0.0f, 0.0f, 0.0f)));
        animation.SetKeyFrame(1, Variant(Quaternion(0.0f, 0.0f, 180.0f)));
        animation.SetKeyFrame(2, Variant(Quaternion(0.0f, 0.0f, 0.0f)));
        node.SetAttributeAnimation("Rotation", animation, WM_LOOP, 0.05f);
    }
}


// Create XML patch instructions for screen joystick layout specific to this sample app
String patchInstructions =
        "<patch>" +
        "    <remove sel=\"/element/element[./attribute[@name='Name' and @value='Button0']]/attribute[@name='Is Visible']\" />" +
        "    <replace sel=\"/element/element[./attribute[@name='Name' and @value='Button0']]/element[./attribute[@name='Name' and @value='Label']]/attribute[@name='Text']/@value\">Fight</replace>" +
        "    <add sel=\"/element/element[./attribute[@name='Name' and @value='Button0']]\">" +
        "        <element type=\"Text\">" +
        "            <attribute name=\"Name\" value=\"KeyBinding\" />" +
        "            <attribute name=\"Text\" value=\"SPACE\" />" +
        "        </element>" +
        "    </add>" +
        "    <remove sel=\"/element/element[./attribute[@name='Name' and @value='Button1']]/attribute[@name='Is Visible']\" />" +
        "    <replace sel=\"/element/element[./attribute[@name='Name' and @value='Button1']]/element[./attribute[@name='Name' and @value='Label']]/attribute[@name='Text']/@value\">Jump</replace>" +
        "    <add sel=\"/element/element[./attribute[@name='Name' and @value='Button1']]\">" +
        "        <element type=\"Text\">" +
        "            <attribute name=\"Name\" value=\"KeyBinding\" />" +
        "            <attribute name=\"Text\" value=\"UP\" />" +
        "        </element>" +
        "    </add>" +
        "</patch>";
