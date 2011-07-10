// Remake of NinjaSnowWar in script
// Does not support load/save, or multiplayer yet.

#include "Scripts/Ninja.as"
#include "Scripts/LightFlash.as"
#include "Scripts/Potion.as"
#include "Scripts/SnowBall.as"
#include "Scripts/SnowCrate.as"

const float mouseSensitivity = 0.125;
const float cameraMinDist = 25;
const float cameraMaxDist = 500;
const float cameraSafetyDist = 30;
const int initialMaxEnemies = 5;
const int finalMaxEnemies = 25;
const int maxPowerups = 5;
const int incrementEach = 10;
const int playerHealth = 20;
const float enemySpawnRate = 1;
const float powerupSpawnRate = 15;

Scene@ gameScene;
Node@ gameCameraNode;
Camera@ gameCamera;
Text@ scoreText;
Text@ hiscoreText;
Text@ messageText;
BorderImage@ healthBar;
BorderImage@ sight;
SoundSource@ musicSource;

Controls playerControls;
Controls prevPlayerControls;
bool gameOn = false;
bool drawDebug = false;
bool drawOctreeDebug = false;
int score = 0;
int hiscore = 0;
int maxEnemies = 0;
int incrementCounter = 0;
float enemySpawnTimer = 0;
float powerupSpawnTimer = 0;

void Start()
{
    if (engine.headless)
        OpenConsoleWindow();

    InitAudio();
    InitConsole();
    InitScene();
    CreateCamera();
    CreateOverlays();
    StartGame();

    SubscribeToEvent("Update", "HandleUpdate");
    SubscribeToEvent(gameScene.physicsWorld, "PhysicsPreStep", "HandleFixedUpdate");
    SubscribeToEvent(gameScene, "ScenePostUpdate", "HandlePostUpdate");
    SubscribeToEvent("PostRenderUpdate", "HandlePostRenderUpdate");
    SubscribeToEvent("Points", "HandlePoints");
    SubscribeToEvent("Kill", "HandleKill");
    SubscribeToEvent("KeyDown", "HandleKeyDown");
    SubscribeToEvent("ScreenMode", "HandleScreenMode");
}

void InitAudio()
{
    // Lower mastervolumes slightly
    audio.masterGain[SOUND_MASTER] = 0.75;
    audio.masterGain[SOUND_MUSIC] = 0.75;

    // Start music playback. Note: the non-positional sound source component does not need to be in the scene
    Sound@ musicFile = cache.GetResource("Sound", "Music/Ninja Gods.ogg");
    musicFile.looped = true;
    musicSource = SoundSource();
    musicSource.Play(musicFile);
}

void InitConsole()
{
    if (engine.headless)
        return;

    XMLFile@ uiStyle = cache.GetResource("XMLFile", "UI/DefaultStyle.xml");

    Console@ console = engine.CreateConsole();
    console.style = uiStyle;
    console.numRows = 16;

    engine.CreateDebugHud();
    debugHud.style = uiStyle;
}

void InitScene()
{
    gameScene = Scene("NinjaSnowWar");

    // Create the static level programmatically
    Octree@ octree = gameScene.CreateComponent("Octree");
    octree.Resize(BoundingBox(-20000, 20000), 7);

    PhysicsWorld@ world = gameScene.CreateComponent("PhysicsWorld");
    world.fps = 200;
    world.gravity = Vector3(0, -981, 0);
    world.linearRestThreshold = 0.1;
    world.linearDampingThreshold = 0;
    world.linearDampingScale = 0.001;

    gameScene.CreateComponent("DebugRenderer");

    Node@ zoneNode = gameScene.CreateChild("Zone");
    Zone@ zone = zoneNode.CreateComponent("Zone");
    zone.boundingBox = BoundingBox(-100000, 100000);
    zone.ambientColor = Color(0.2, 0.2, 0.7);
    zone.fogColor = Color(0.2, 0.2, 0.7);
    zone.fogStart = 5000;
    zone.fogEnd = 15000;
    
    Node@ lightNode = gameScene.CreateChild("Sunlight");
    lightNode.rotation = Quaternion(0.888074, 0.325058, -0.325058, 0);
    Light@ light = lightNode.CreateComponent("Light");
    light.lightType = LIGHT_DIRECTIONAL;
    light.castShadows = true;
    light.shadowNearFarRatio = 0.002;
    light.shadowBias = BiasParameters(0.00025, 0.001);
    light.shadowCascade = CascadeParameters(2, 0.5, 0.2, 5000);
    light.shadowFocus = FocusParameters(true, true, true, 50, 900);

    Node@ staticNode = gameScene.CreateChild("Static");
    StaticModel@ staticModel = staticNode.CreateComponent("StaticModel");
    staticModel.model = cache.GetResource("Model", "Models/Level.mdl");
    staticModel.material = cache.GetResource("Material", "Materials/Snow.xml");
    CollisionShape@ shape = staticNode.CreateComponent("CollisionShape");
    shape.SetTriangleMesh(cache.GetResource("Model", "Models/Level.mdl"), 0, Vector3(), Quaternion());
    shape.collisionGroup = 2;
    shape.collisionMask = 3;

    Node@ skyNode = gameScene.CreateChild("Sky");
    skyNode.position = Vector3(0, 3000, 0);
    skyNode.scale = Vector3(30000, 1, 30000);
    Skybox@ skybox = skyNode.CreateComponent("Skybox");
    skybox.model = cache.GetResource("Model", "Models/CloudPlane.mdl");
    skybox.material = cache.GetResource("Material", "Materials/CloudPlane.xml");

    // Enable access to this script file & scene from the console
    script.defaultScene = gameScene;
    script.defaultScriptFile = scriptFile;
}

void CreateCamera()
{
    gameCameraNode = Node();
    gameCameraNode.position = Vector3(0, 200, -1000);

    gameCamera = gameCameraNode.CreateComponent("Camera");
    gameCamera.nearClip = 10.0;
    gameCamera.farClip = 16000.0;

    if (!engine.headless)
        renderer.viewports[0] = Viewport(gameScene, gameCamera);
}

void CreateOverlays()
{
    if (engine.headless)
        return;

    int height = graphics.height / 22;
    if (height > 64)
        height = 64;

    sight = BorderImage();
    sight.texture = cache.GetResource("Texture2D", "Textures/Sight.png");
    sight.SetAlignment(HA_CENTER, VA_CENTER);
    sight.SetSize(height, height);
    ui.rootElement.AddChild(sight);

    Font@ font = cache.GetResource("Font", "Fonts/BlueHighway.ttf");

    scoreText = Text();
    scoreText.SetFont(font, 17);
    scoreText.SetAlignment(HA_LEFT, VA_TOP);
    scoreText.SetPosition(5, 5);
    scoreText.colors[C_BOTTOMLEFT] = Color(1, 1, 0.25);
    scoreText.colors[C_BOTTOMRIGHT] = Color(1, 1, 0.25);
    ui.rootElement.AddChild(scoreText);

    @hiscoreText = Text();
    hiscoreText.SetFont(font, 17);
    hiscoreText.SetAlignment(HA_RIGHT, VA_TOP);
    hiscoreText.SetPosition(-5, 5);
    hiscoreText.colors[C_BOTTOMLEFT] = Color(1, 1, 0.25);
    hiscoreText.colors[C_BOTTOMRIGHT] = Color(1, 1, 0.25);
    ui.rootElement.AddChild(hiscoreText);

    @messageText = Text();
    messageText.SetFont(font, 17);
    messageText.SetAlignment(HA_CENTER, VA_CENTER);
    messageText.SetPosition(0, -height * 2);
    messageText.color = Color(1, 0, 0);
    ui.rootElement.AddChild(messageText);

    BorderImage@ healthBorder = BorderImage();
    healthBorder.texture = cache.GetResource("Texture2D", "Textures/HealthBarBorder.png");
    healthBorder.SetAlignment(HA_CENTER, VA_TOP);
    healthBorder.SetPosition(0, 8);
    healthBorder.SetSize(120, 20);
    ui.rootElement.AddChild(healthBorder);

    healthBar = BorderImage();
    healthBar.texture = cache.GetResource("Texture2D", "Textures/HealthBarInside.png");
    healthBar.SetPosition(2, 2);
    healthBar.SetSize(116, 16);
    healthBorder.AddChild(healthBar);
}

void SetMessage(const String&in message)
{
    if (messageText !is null)
        messageText.text = message;
}

void StartGame()
{
    // Clear the scene of all existing scripted objects
    {
        Array<Node@> scriptedNodes = gameScene.GetScriptedChildren(true);
        for (uint i = 0; i < scriptedNodes.length; ++i)
            scriptedNodes[i].Remove();
    }

    Node@ playerNode = gameScene.CreateChild("Player");
    Ninja@ playerNinja = cast<Ninja>(playerNode.CreateScriptObject(scriptFile, "Ninja"));
    playerNinja.Create(Vector3(0, 90, 0), Quaternion());
    playerNinja.health = playerNinja.maxHealth = playerHealth;
    playerNinja.side = SIDE_PLAYER;
    // Make sure the player can not shoot on first frame by holding the button down
    playerNinja.controls = playerNinja.prevControls = playerControls;

    ResetAI();

    gameOn = true;
    score = 0;
    maxEnemies = initialMaxEnemies;
    incrementCounter = 0;
    enemySpawnTimer = 0;
    powerupSpawnTimer = 0;
    playerControls.yaw = 0;
    playerControls.pitch = 0;

    SetMessage("");
}

void HandleUpdate(StringHash eventType, VariantMap& eventData)
{
    float timeStep = eventData["TimeStep"].GetFloat();

    if (input.keyPress[KEY_F2])
        debugHud.ToggleAll();
    if (input.keyPress[KEY_F3])
        drawDebug = !drawDebug;
    if (input.keyPress[KEY_F4])
        drawOctreeDebug = !drawOctreeDebug;

    if (input.keyPress[KEY_F5])
        gameScene.Save(File(fileSystem.programDir + "Data/Save.dat", FILE_WRITE));

    if ((input.keyPress['P']) && (!console.visible) && (gameOn))
    {
        gameScene.active = !gameScene.active;
        if (!gameScene.active)
            SetMessage("PAUSED");
        else
            SetMessage("");
    }

    if (input.keyPress[KEY_ESC])
    {
        if (!console.visible)
            engine.Exit();
        else
            console.visible = false;
    }

    if (gameScene.active)
        UpdateControls();
}

void HandleFixedUpdate(StringHash eventType, VariantMap& eventData)
{
    float timeStep = eventData["TimeStep"].GetFloat();

    // Spawn new objects and check for end/restart of game
    SpawnObjects(timeStep);
    CheckEndAndRestart();
}

void HandlePostUpdate()
{
    UpdateCamera();
    UpdateStatus();
}

void HandlePostRenderUpdate()
{
    if (drawDebug)
        gameScene.physicsWorld.DrawDebugGeometry(true);
    if (drawOctreeDebug)
        gameScene.octree.DrawDebugGeometry(true);
}

void HandlePoints(StringHash eventType, VariantMap& eventData)
{
    if (eventData["DamageSide"].GetInt() == SIDE_PLAYER)
    {
        score += eventData["Points"].GetInt();
        if (score > hiscore)
            hiscore = score;
    }
}

void HandleKill(StringHash eventType, VariantMap& eventData)
{
    if (eventData["DamageSide"].GetInt() == SIDE_PLAYER)
    {
        MakeAIHarder();

        // Increment amount of simultaneous enemies after enough kills
        incrementCounter++;
        if (incrementCounter >= incrementEach)
        {
            incrementCounter = 0;
            if (maxEnemies < finalMaxEnemies)
                maxEnemies++;
        }
    }
}

void SpawnObjects(float timeStep)
{
    // Spawn powerups
    powerupSpawnTimer += timeStep;
    if (powerupSpawnTimer >= powerupSpawnRate)
    {
        powerupSpawnTimer = 0;
        int numPowerups = gameScene.GetScriptedChildren("SnowCrate", true).length + gameScene.GetScriptedChildren("Potion", true).length;

        if (numPowerups < maxPowerups)
        {
            const float maxOffset = 4000;
            float xOffset = Random(maxOffset * 2.0f) - maxOffset;
            float zOffset = Random(maxOffset * 2.0f) - maxOffset;

            Vector3 position(xOffset, 5000, zOffset);
            Node@ crateNode = gameScene.CreateChild();
            GameObject@ crateObject = cast<GameObject>(crateNode.CreateScriptObject(scriptFile, "SnowCrate"));
            crateObject.Create(position, Quaternion());
        }
    }

    // Spawn enemies
    enemySpawnTimer += timeStep;
    if (enemySpawnTimer > enemySpawnRate)
    {
        enemySpawnTimer = 0;
        // Take the player ninja into account
        int numEnemies = gameScene.GetScriptedChildren("Ninja", true).length - 1;

        if (numEnemies < maxEnemies)
        {
            const float maxOffset = 4000;
            float offset = Random(maxOffset * 2.0) - maxOffset;
            // Random north/east/south/west direction
            int dir = RandomInt() & 3;
            dir *= 90;
            Quaternion q(dir, Vector3(0, 1, 0));
            Vector3 position(q * Vector3(offset, 1000, -12000));

            Node@ enemyNode = gameScene.CreateChild();
            Ninja@ enemyNinja = cast<Ninja>(enemyNode.CreateScriptObject(scriptFile, "Ninja"));
            enemyNinja.Create(position, q);
            enemyNinja.side = SIDE_ENEMY;
            @enemyNinja.controller = AIController();
            RigidBody@ enemyBody = enemyNode.GetComponent("RigidBody");
            enemyBody.linearVelocity = (q * Vector3(0, 1000, 3000));
        }
    }
}

void CheckEndAndRestart()
{
    if ((gameOn) && (gameScene.GetChild("Player", true) is null))
    {
        gameOn = false;
        SetMessage("Press Fire or Jump to restart!");
        return;
    }

    if ((!gameOn) && (playerControls.IsPressed(CTRL_FIRE | CTRL_JUMP, prevPlayerControls)))
        StartGame();
}

void UpdateControls()
{
    prevPlayerControls = playerControls;
    playerControls.Set(CTRL_ALL, false);

    if ((console is null) || (!console.visible))
    {
        if (input.keyDown['W'])
            playerControls.Set(CTRL_UP, true);
        if (input.keyDown['S'])
            playerControls.Set(CTRL_DOWN, true);
        if (input.keyDown['A'])
            playerControls.Set(CTRL_LEFT, true);
        if (input.keyDown['D'])
            playerControls.Set(CTRL_RIGHT, true);
        if (input.keyDown[KEY_LCTRL])
            playerControls.Set(CTRL_FIRE, true);
        if (input.keyDown[' '])
            playerControls.Set(CTRL_JUMP, true);
    }

    if (input.mouseButtonDown[MOUSEB_LEFT])
        playerControls.Set(CTRL_FIRE, true);
    if (input.mouseButtonDown[MOUSEB_RIGHT])
        playerControls.Set(CTRL_JUMP, true);

    playerControls.yaw += mouseSensitivity * input.mouseMoveX;
    playerControls.pitch += mouseSensitivity * input.mouseMoveY;
    playerControls.pitch = Clamp(playerControls.pitch, -60, 60);

    Node@ playerNode = gameScene.GetChild("Player", true);
    if (playerNode !is null)
    {
        Ninja@ playerNinja = cast<Ninja>(playerNode.scriptObject);
        playerNinja.controls = playerControls;
    }
}

void UpdateCamera()
{
    Node@ playerNode = gameScene.GetChild("Player", true);
    if (playerNode is null)
        return;

    Vector3 pos = playerNode.position;
    Quaternion dir;
    dir = dir * Quaternion(playerNode.rotation.yaw, Vector3(0, 1, 0));
    dir = dir * Quaternion(playerControls.pitch, Vector3(1, 0, 0));

    Vector3 aimPoint = pos + Vector3(0, 100, 0);
    Vector3 minDist = aimPoint + dir * Vector3(0, 0, -cameraMinDist);
    Vector3 maxDist = aimPoint + dir * Vector3(0, 0, -cameraMaxDist);

    // Collide camera ray with static objects (collision mask 2)
    Vector3 rayDir = (maxDist - minDist).Normalized();
    float rayDistance = cameraMaxDist - cameraMinDist + cameraSafetyDist;
    Array<PhysicsRaycastResult>@ result = gameScene.physicsWorld.Raycast(Ray(minDist, rayDir), rayDistance, 2);
    if (result.length > 0)
        rayDistance = Min(rayDistance, result[0].distance - cameraSafetyDist);

    gameCameraNode.position = minDist + rayDir * rayDistance;
    gameCameraNode.rotation = dir;

    audio.listenerPosition = pos;
    audio.listenerRotation = dir;
}

void UpdateStatus()
{
    if (engine.headless)
        return;

    scoreText.text = "Score " + score;
    hiscoreText.text = "Hiscore " + hiscore;

    Node@ playerNode = gameScene.GetChild("Player", true);
    if (playerNode is null)
        return;

    GameObject@ object = cast<GameObject>(playerNode.scriptObject);
    healthBar.width = 116 * object.health / playerHealth;
}

void HandleKeyDown(StringHash eventType, VariantMap& eventData)
{
    // Check for toggling the console
    if (eventData["Key"].GetInt() == KEY_F1)
        console.Toggle();
}

void HandleScreenMode()
{
    int height = graphics.height / 22;
    if (height > 64)
        height = 64;
    sight.SetSize(height, height);
    messageText.SetPosition(0, -height * 2);
}
