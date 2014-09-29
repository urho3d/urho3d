// Remake of NinjaSnowWar in script

#include "Scripts/NinjaSnowWar/FootSteps.as"
#include "Scripts/NinjaSnowWar/LightFlash.as"
#include "Scripts/NinjaSnowWar/Ninja.as"
#include "Scripts/NinjaSnowWar/Player.as"
#include "Scripts/NinjaSnowWar/Potion.as"
#include "Scripts/NinjaSnowWar/SnowBall.as"
#include "Scripts/NinjaSnowWar/SnowCrate.as"
#include "Scripts/Utilities/Network.as"

const float mouseSensitivity = 0.125;
const float touchSensitivity = 2.0;
const float joySensitivity = 0.5;
const float joyMoveDeadZone = 0.333;
const float joyLookDeadZone = 0.05;
const float cameraMinDist = 0.25;
const float cameraMaxDist = 5;
const float cameraSafetyDist = 0.3;
const int initialMaxEnemies = 5;
const int finalMaxEnemies = 25;
const int maxPowerups = 5;
const int incrementEach = 10;
const int playerHealth = 20;
const float enemySpawnRate = 1;
const float powerupSpawnRate = 15;
const float spawnAreaSize = 5;

Scene@ gameScene;
Node@ gameCameraNode;
Node@ musicNode;
Camera@ gameCamera;
Text@ scoreText;
Text@ hiscoreText;
Text@ messageText;
BorderImage@ healthBar;
BorderImage@ sight;
BorderImage@ moveButton;
BorderImage@ fireButton;
SoundSource@ musicSource;

Controls playerControls;
Controls prevPlayerControls;
bool singlePlayer = true;
bool gameOn = false;
bool drawDebug = false;
bool drawOctreeDebug = false;
int maxEnemies = 0;
int incrementCounter = 0;
float enemySpawnTimer = 0;
float powerupSpawnTimer = 0;
uint clientNodeID = 0;
int clientScore = 0;

int screenJoystickID = -1;
int screenJoystickSettingsID = -1;
bool touchEnabled = false;

Array<Player> players;
Array<HiscoreEntry> hiscores;

void Start()
{
    if (engine.headless)
        OpenConsoleWindow();

    ParseNetworkArguments();
    if (runServer || runClient)
        singlePlayer = false;

    InitAudio();
    InitConsole();
    InitScene();
    InitNetworking();
    CreateCamera();
    CreateOverlays();

    SubscribeToEvent(gameScene, "SceneUpdate", "HandleUpdate");
    if (gameScene.physicsWorld !is null)
        SubscribeToEvent(gameScene.physicsWorld, "PhysicsPreStep", "HandleFixedUpdate");
    SubscribeToEvent(gameScene, "ScenePostUpdate", "HandlePostUpdate");
    SubscribeToEvent("PostRenderUpdate", "HandlePostRenderUpdate");
    SubscribeToEvent("KeyDown", "HandleKeyDown");
    SubscribeToEvent("Points", "HandlePoints");
    SubscribeToEvent("Kill", "HandleKill");
    SubscribeToEvent("ScreenMode", "HandleScreenMode");

    if (singlePlayer)
    {
        StartGame(null);
        engine.pauseMinimized = true;
    }
}

void InitAudio()
{
    if (engine.headless)
        return;

    // Lower mastervolumes slightly.
    audio.masterGain[SOUND_MASTER] = 0.75;
    audio.masterGain[SOUND_MUSIC] = 0.9;

    if (!nobgm)
    {
        Sound@ musicFile = cache.GetResource("Sound", "Music/Ninja Gods.ogg");
        musicFile.looped = true;

        // Note: the non-positional sound source component need to be attached to a node to become effective
        // Due to networked mode clearing the scene on connect, do not attach to the scene itself
        musicNode = Node();
        musicSource = musicNode.CreateComponent("SoundSource");
        musicSource.soundType = SOUND_MUSIC;
        musicSource.Play(musicFile);
    }
}

void InitConsole()
{
    if (engine.headless)
        return;

    XMLFile@ uiStyle = cache.GetResource("XMLFile", "UI/DefaultStyle.xml");
    ui.root.defaultStyle = uiStyle;

    Console@ console = engine.CreateConsole();
    console.defaultStyle = uiStyle;
    console.background.opacity = 0.8;

    engine.CreateDebugHud();
    debugHud.defaultStyle = uiStyle;
}

void InitScene()
{
    gameScene = Scene("NinjaSnowWar");

    // Enable access to this script file & scene from the console
    script.defaultScene = gameScene;
    script.defaultScriptFile = scriptFile;

    // For the multiplayer client, do not load the scene, let it load from the server
    if (runClient)
        return;

    gameScene.LoadXML(cache.GetFile("Scenes/NinjaSnowWar.xml"));

    // On mobile devices render the shadowmap first. Also adjust the shadow quality for performance
    String platform = GetPlatform();
    if (platform == "Android" || platform == "iOS" || platform == "Raspberry Pi")
    {
        renderer.reuseShadowMaps = false;
        renderer.shadowQuality = SHADOWQUALITY_LOW_16BIT;
        // Adjust the directional light shadow range slightly further, as only the first
        // cascade is supported
        Node@ dirLightNode = gameScene.GetChild("GlobalLight", true);
        if (dirLightNode !is null)
        {
            Light@ dirLight = dirLightNode.GetComponent("Light");
            dirLight.shadowCascade = CascadeParameters(15.0f, 0.0f, 0.0f, 0.0f, 0.9f);
            dirLight.shadowIntensity = 0.333f;
        }
    }

    // Precache shaders if possible
    if (!engine.headless && cache.Exists("NinjaSnowWarShaders.xml"))
        graphics.PrecacheShaders(cache.GetFile("NinjaSnowWarShaders.xml"));
}

void InitNetworking()
{
    network.updateFps = 25; // 1/4 of physics FPS
    // Remote events sent between client & server must be explicitly registered or else they are not allowed to be received
    network.RegisterRemoteEvent("PlayerSpawned");
    network.RegisterRemoteEvent("UpdateScore");
    network.RegisterRemoteEvent("UpdateHiscores");
    network.RegisterRemoteEvent("ParticleEffect");

    if (runServer)
    {
        network.StartServer(serverPort);

        // Disable physics interpolation to ensure clients get sent physically correct transforms
        gameScene.physicsWorld.interpolation = false;

        SubscribeToEvent("ClientIdentity", "HandleClientIdentity");
        SubscribeToEvent("ClientSceneLoaded", "HandleClientSceneLoaded");
        SubscribeToEvent("ClientDisconnected", "HandleClientDisconnected");
    }
    if (runClient)
    {
        VariantMap identity;
        identity["UserName"] = userName;
        network.updateFps = 50; // Increase controls send rate for better responsiveness
        network.Connect(serverAddress, serverPort, gameScene, identity);

        SubscribeToEvent("PlayerSpawned", "HandlePlayerSpawned");
        SubscribeToEvent("UpdateScore", "HandleUpdateScore");
        SubscribeToEvent("UpdateHiscores", "HandleUpdateHiscores");
        SubscribeToEvent("NetworkUpdateSent", "HandleNetworkUpdateSent");
    }
}

void InitTouchInput()
{
    touchEnabled = true;
    screenJoystickID = input.AddScreenJoystick(cache.GetResource("XMLFile", "UI/ScreenJoystick_NinjaSnowWar.xml"));
}

void CreateCamera()
{
    // Note: the camera is not in the scene
    gameCameraNode = Node();
    gameCameraNode.position = Vector3(0, 2, -10);

    gameCamera = gameCameraNode.CreateComponent("Camera");
    gameCamera.nearClip = 0.5;
    gameCamera.farClip = 160;

    if (!engine.headless)
    {
        renderer.viewports[0] = Viewport(gameScene, gameCamera);
        audio.listener = gameCameraNode.CreateComponent("SoundListener");
    }
}

void CreateOverlays()
{
    if (engine.headless || runServer)
        return;

    int height = graphics.height / 22;
    if (height > 64)
        height = 64;

    sight = BorderImage();
    sight.texture = cache.GetResource("Texture2D", "Textures/NinjaSnowWar/Sight.png");
    sight.SetAlignment(HA_CENTER, VA_CENTER);
    sight.SetSize(height, height);
    ui.root.AddChild(sight);

    Font@ font = cache.GetResource("Font", "Fonts/BlueHighway.ttf");

    scoreText = Text();
    scoreText.SetFont(font, 13);
    scoreText.SetAlignment(HA_LEFT, VA_TOP);
    scoreText.SetPosition(5, 5);
    scoreText.colors[C_BOTTOMLEFT] = Color(1, 1, 0.25);
    scoreText.colors[C_BOTTOMRIGHT] = Color(1, 1, 0.25);
    ui.root.AddChild(scoreText);

    @hiscoreText = Text();
    hiscoreText.SetFont(font, 13);
    hiscoreText.SetAlignment(HA_RIGHT, VA_TOP);
    hiscoreText.SetPosition(-5, 5);
    hiscoreText.colors[C_BOTTOMLEFT] = Color(1, 1, 0.25);
    hiscoreText.colors[C_BOTTOMRIGHT] = Color(1, 1, 0.25);
    ui.root.AddChild(hiscoreText);

    @messageText = Text();
    messageText.SetFont(font, 13);
    messageText.SetAlignment(HA_CENTER, VA_CENTER);
    messageText.SetPosition(0, -height * 2);
    messageText.color = Color(1, 0, 0);
    ui.root.AddChild(messageText);

    BorderImage@ healthBorder = BorderImage();
    healthBorder.texture = cache.GetResource("Texture2D", "Textures/NinjaSnowWar/HealthBarBorder.png");
    healthBorder.SetAlignment(HA_CENTER, VA_TOP);
    healthBorder.SetPosition(0, 8);
    healthBorder.SetSize(120, 20);
    ui.root.AddChild(healthBorder);

    healthBar = BorderImage();
    healthBar.texture = cache.GetResource("Texture2D", "Textures/NinjaSnowWar/HealthBarInside.png");
    healthBar.SetPosition(2, 2);
    healthBar.SetSize(116, 16);
    healthBorder.AddChild(healthBar);

    if (GetPlatform() == "Android" || GetPlatform() == "iOS")
        // On mobile platform, enable touch by adding a screen joystick
        InitTouchInput();
    else if (input.numJoysticks == 0)
        // On desktop platform, do not detect touch when we already got a joystick
        SubscribeToEvent("TouchBegin", "HandleTouchBegin");
}

void SetMessage(const String&in message)
{
    if (messageText !is null)
        messageText.text = message;
}

void StartGame(Connection@ connection)
{
    // Clear the scene of all existing scripted objects
    {
        Array<Node@> scriptedNodes = gameScene.GetChildrenWithScript(true);
        for (uint i = 0; i < scriptedNodes.length; ++i)
            scriptedNodes[i].Remove();
    }

    players.Clear();
    SpawnPlayer(connection);

    ResetAI();

    gameOn = true;
    maxEnemies = initialMaxEnemies;
    incrementCounter = 0;
    enemySpawnTimer = 0;
    powerupSpawnTimer = 0;

    if (singlePlayer)
    {
        playerControls.yaw = 0;
        playerControls.pitch = 0;
        SetMessage("");
    }
}

void SpawnPlayer(Connection@ connection)
{
    Vector3 spawnPosition;
    if (singlePlayer)
        spawnPosition = Vector3(0, 0.97, 0);
    else
        spawnPosition = Vector3(Random(spawnAreaSize) - spawnAreaSize * 0.5, 0.97, Random(spawnAreaSize) - spawnAreaSize);

    Node@ playerNode = SpawnObject(spawnPosition, Quaternion(), "Ninja");
    // Set owner connection. Owned nodes are always updated to the owner at full frequency
    playerNode.owner = connection;
    playerNode.name = "Player";

    // Initialize variables
    Ninja@ playerNinja = cast<Ninja>(playerNode.scriptObject);
    playerNinja.health = playerNinja.maxHealth = playerHealth;
    playerNinja.side = SIDE_PLAYER;
    // Make sure the player can not shoot on first frame by holding the button down
    if (connection is null)
        playerNinja.controls = playerNinja.prevControls = playerControls;
    else
        playerNinja.controls = playerNinja.prevControls = connection.controls;

    // Check if player entry already exists
    int playerIndex = -1;
    for (uint i = 0; i < players.length; ++i)
    {
        if (players[i].connection is connection)
        {
            playerIndex = i;
            break;
        }
    }

    // Does not exist, create new
    if (playerIndex < 0)
    {
        playerIndex = players.length;
        players.Resize(players.length + 1);
        players[playerIndex].connection = connection;

        if (connection !is null)
        {
            players[playerIndex].name = connection.identity["UserName"].GetString();
            // In multiplayer, send current hiscores to the new player
            SendHiscores(playerIndex);
        }
        else
        {
            players[playerIndex].name = "Player";
            // In singleplayer, create also the default hiscore entry immediately
            HiscoreEntry newHiscore;
            newHiscore.name = players[playerIndex].name;
            newHiscore.score = 0;
            hiscores.Push(newHiscore);
        }
    }

    players[playerIndex].nodeID = playerNode.id;
    players[playerIndex].score = 0;

    if (connection !is null)
    {
        // In multiplayer, send initial score, then send a remote event that tells the spawned node's ID
        // It is important for the event to be in-order so that the node has been replicated first
        SendScore(playerIndex);
        VariantMap eventData;
        eventData["NodeID"] = playerNode.id;
        connection.SendRemoteEvent("PlayerSpawned", true, eventData);

        // Create name tag (Text3D component) for players in multiplayer
        Node@ textNode = playerNode.CreateChild("NameTag");
        textNode.position = Vector3(0, 1.2, 0);
        Text3D@ text3D = textNode.CreateComponent("Text3D");
        Font@ font = cache.GetResource("Font", "Fonts/BlueHighway.ttf");
        text3D.SetFont(font, 19);
        text3D.color = Color(1, 1, 0);
        text3D.text = players[playerIndex].name;
        text3D.horizontalAlignment = HA_CENTER;
        text3D.verticalAlignment = VA_CENTER;
        text3D.faceCameraMode = FC_ROTATE_XYZ;
    }
}

void HandleUpdate(StringHash eventType, VariantMap& eventData)
{
    float timeStep = eventData["TimeStep"].GetFloat();

    UpdateControls();
    CheckEndAndRestart();

    if (engine.headless)
    {
        String command = GetConsoleInput();
        if (command.length > 0)
            script.Execute(command);
    }
    else
    {
        if (debugHud.mode != DEBUGHUD_SHOW_NONE)
        {
            Node@ playerNode = FindOwnNode();
            if (playerNode !is null)
            {
                debugHud.SetAppStats("Player Pos", playerNode.worldPosition.ToString());
                debugHud.SetAppStats("Player Yaw", Variant(playerNode.worldRotation.yaw));
            }
            else
                debugHud.ClearAppStats();
        }
    }
}

void HandleFixedUpdate(StringHash eventType, VariantMap& eventData)
{
    float timeStep = eventData["TimeStep"].GetFloat();

    // Spawn new objects, singleplayer or server only
    if (singlePlayer || runServer)
        SpawnObjects(timeStep);
}

void HandlePostUpdate()
{
    UpdateCamera();
    UpdateStatus();
}

void HandlePostRenderUpdate()
{
    if (engine.headless)
        return;

    if (drawDebug)
        gameScene.physicsWorld.DrawDebugGeometry(true);
    if (drawOctreeDebug)
        gameScene.octree.DrawDebugGeometry(true);
}

void HandleTouchBegin(StringHash eventType, VariantMap& eventData)
{
    // On some platforms like Windows the presence of touch input can only be detected dynamically
    InitTouchInput();
    UnsubscribeFromEvent("TouchBegin");
}

void HandleKeyDown(StringHash eventType, VariantMap& eventData)
{
    int key = eventData["Key"].GetInt();

    if (key == KEY_ESC)
    {
        if (!console.visible)
            engine.Exit();
        else
            console.visible = false;
    }

    if (key == KEY_F1)
        console.Toggle();

    if (key == KEY_F2)
        debugHud.ToggleAll();

    if (key == KEY_F3)
        drawDebug = !drawDebug;

    if (key == KEY_F4)
        drawOctreeDebug = !drawOctreeDebug;

    // Allow pause only in singleplayer
    if (key == 'P' && singlePlayer && !console.visible && gameOn)
    {
        gameScene.updateEnabled = !gameScene.updateEnabled;
        if (!gameScene.updateEnabled)
        {
            SetMessage("PAUSED");
            
            // Open the settings joystick only if the controls screen joystick was already open
            if (screenJoystickID >= 0)
            {
                // Lazy initialization
                if (screenJoystickSettingsID < 0)
                    screenJoystickSettingsID = input.AddScreenJoystick(cache.GetResource("XMLFile", "UI/ScreenJoystickSettings_NinjaSnowWar.xml"));
                else
                    input.screenJoystickVisible[screenJoystickSettingsID] = true;
            }
        }
        else
        {
            SetMessage("");

            // Hide the settings joystick
            if (screenJoystickSettingsID >= 0)
                input.screenJoystickVisible[screenJoystickSettingsID] = false;
        }
    }
}

void HandlePoints(StringHash eventType, VariantMap& eventData)
{
    if (eventData["DamageSide"].GetInt() == SIDE_PLAYER)
    {
        // Get node ID of the object that should receive points -> use it to find player index
        int playerIndex = FindPlayerIndex(eventData["Receiver"].GetInt());
        if (playerIndex >= 0)
        {
            players[playerIndex].score += eventData["Points"].GetInt();
            SendScore(playerIndex);

            bool newHiscore = CheckHiscore(playerIndex);
            if (newHiscore)
                SendHiscores(-1);
        }
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

void HandleClientIdentity(StringHash eventType, VariantMap& eventData)
{
    Connection@ connection = GetEventSender();
    // If user has empty name, invent one
    if (connection.identity["UserName"].GetString().Trimmed().empty)
        connection.identity["UserName"] = "user" + RandomInt(1000);
    // Assign scene to begin replicating it to the client
    connection.scene = gameScene;
}

void HandleClientSceneLoaded(StringHash eventType, VariantMap& eventData)
{
    // Now client is actually ready to begin. If first player, clear the scene and restart the game
    Connection@ connection = GetEventSender();
    if (players.empty)
        StartGame(connection);
    else
        SpawnPlayer(connection);
}

void HandleClientDisconnected(StringHash eventType, VariantMap& eventData)
{
    Connection@ connection = GetEventSender();
    // Erase the player entry, and make the player's ninja commit seppuku (if exists)
    for (uint i = 0; i < players.length; ++i)
    {
        if (players[i].connection is connection)
        {
            players[i].connection = null;
            Node@ playerNode = FindPlayerNode(i);
            if (playerNode !is null)
            {
                Ninja@ playerNinja = cast<Ninja>(playerNode.scriptObject);
                playerNinja.health = 0;
                playerNinja.lastDamageSide = SIDE_NEUTRAL; // No-one scores from this
            }
            players.Erase(i);
            return;
        }
    }
}

void HandlePlayerSpawned(StringHash eventType, VariantMap& eventData)
{
    // Store our node ID and mark the game as started
    clientNodeID = eventData["NodeID"].GetInt();
    gameOn = true;
    SetMessage("");

    // Copy initial yaw from the player node (we should have it replicated now)
    Node@ playerNode = FindOwnNode();
    if (playerNode !is null)
    {
        playerControls.yaw = playerNode.rotation.yaw;
        playerControls.pitch = 0;

        // Disable the nametag from own character
        Node@ nameTag = playerNode.GetChild("NameTag");
        nameTag.enabled = false;
    }
}

void HandleUpdateScore(StringHash eventType, VariantMap& eventData)
{
    clientScore = eventData["Score"].GetInt();
    scoreText.text = "Score " + clientScore;
}

void HandleUpdateHiscores(StringHash eventType, VariantMap& eventData)
{
    VectorBuffer data = eventData["Hiscores"].GetBuffer();
    hiscores.Resize(data.ReadVLE());
    for (uint i = 0; i < hiscores.length; ++i)
    {
        hiscores[i].name = data.ReadString();
        hiscores[i].score = data.ReadInt();
    }

    String allHiscores;
    for (uint i = 0; i < hiscores.length; ++i)
        allHiscores += hiscores[i].name + " " + hiscores[i].score + "\n";
    hiscoreText.text = allHiscores;
}

void HandleNetworkUpdateSent()
{
    // Clear accumulated buttons from the network controls
    if (network.serverConnection !is null)
        network.serverConnection.controls.Set(CTRL_ALL, false);
}

int FindPlayerIndex(uint nodeID)
{
    for (uint i = 0; i < players.length; ++i)
    {
        if (players[i].nodeID == nodeID)
            return i;
    }
    return -1;
}

Node@ FindPlayerNode(int playerIndex)
{
    if (playerIndex >= 0 && playerIndex < int(players.length))
        return gameScene.GetNode(players[playerIndex].nodeID);
    else
        return null;
}

Node@ FindOwnNode()
{
    if (singlePlayer)
        return gameScene.GetChild("Player", true);
    else
        return gameScene.GetNode(clientNodeID);
}

bool CheckHiscore(int playerIndex)
{
    for (uint i = 0; i < hiscores.length; ++i)
    {
        if (hiscores[i].name == players[playerIndex].name)
        {
            if (players[playerIndex].score > hiscores[i].score)
            {
                hiscores[i].score = players[playerIndex].score;
                SortHiscores();
                return true;
            }
            else
                return false; // No update to individual hiscore
        }
    }

    // Not found, create new hiscore entry
    HiscoreEntry newHiscore;
    newHiscore.name = players[playerIndex].name;
    newHiscore.score = players[playerIndex].score;
    hiscores.Push(newHiscore);
    SortHiscores();
    return true;
}

void SortHiscores()
{
    for (int i = 1; i < int(hiscores.length); ++i)
    {
        HiscoreEntry temp = hiscores[i];
        int j = i;
        while (j > 0 && temp.score > hiscores[j - 1].score)
        {
            hiscores[j] = hiscores[j - 1];
            --j;
        }
        hiscores[j] = temp;
    }
}

void SendScore(int playerIndex)
{
    if (!runServer || playerIndex < 0 || playerIndex >= int(players.length))
        return;

    VariantMap eventData;
    eventData["Score"] = players[playerIndex].score;
    players[playerIndex].connection.SendRemoteEvent("UpdateScore", true, eventData);
}

void SendHiscores(int playerIndex)
{
    if (!runServer)
        return;

    VectorBuffer data;
    data.WriteVLE(hiscores.length);
    for (uint i = 0; i < hiscores.length; ++i)
    {
        data.WriteString(hiscores[i].name);
        data.WriteInt(hiscores[i].score);
    }

    VariantMap eventData;
    eventData["Hiscores"] = data;

    if (playerIndex >= 0 && playerIndex < int(players.length))
        players[playerIndex].connection.SendRemoteEvent("UpdateHiscores", true, eventData);
    else
        network.BroadcastRemoteEvent(gameScene, "UpdateHiscores", true, eventData); // Send to all in scene
}

Node@ SpawnObject(const Vector3&in position, const Quaternion&in rotation, const String&in className)
{
    XMLFile@ xml = cache.GetResource("XMLFile", "Objects/" + className + ".xml");
    return scene.InstantiateXML(xml, position, rotation);
}

Node@ SpawnParticleEffect(const Vector3&in position, const String&in effectName, float duration, CreateMode mode = REPLICATED)
{
    Node@ newNode = scene.CreateChild("Effect", mode);
    newNode.position = position;

    // Create the particle emitter
    ParticleEmitter@ emitter = newNode.CreateComponent("ParticleEmitter");
    emitter.effect = cache.GetResource("ParticleEffect", effectName);

    // Create a GameObject for managing the effect lifetime. This is always local, so for server-controlled effects it
    // exists only on the server
    GameObject@ object = cast<GameObject>(newNode.CreateScriptObject(scriptFile, "GameObject", LOCAL));
    object.duration = duration;

    return newNode;
}

Node@ SpawnSound(const Vector3&in position, const String&in soundName, float duration)
{
    Node@ newNode = scene.CreateChild();
    newNode.position = position;

    // Create the sound source
    SoundSource3D@ source = newNode.CreateComponent("SoundSource3D");
    Sound@ sound = cache.GetResource("Sound", soundName);
    source.SetDistanceAttenuation(200, 5000, 1);
    source.Play(sound);

    // Create a GameObject for managing the sound lifetime
    GameObject@ object = cast<GameObject>(newNode.CreateScriptObject(scriptFile, "GameObject", LOCAL));
    object.duration = duration;

    return newNode;
}

void SpawnObjects(float timeStep)
{
    // If game not running, run only the random generator
    if (!gameOn)
    {
        Random();
        return;
    }

    // Spawn powerups
    powerupSpawnTimer += timeStep;
    if (powerupSpawnTimer >= powerupSpawnRate)
    {
        powerupSpawnTimer = 0;
        int numPowerups = gameScene.GetChildrenWithScript("SnowCrate", true).length + gameScene.GetChildrenWithScript("Potion", true).length;

        if (numPowerups < maxPowerups)
        {
            const float maxOffset = 40;
            float xOffset = Random(maxOffset * 2.0) - maxOffset;
            float zOffset = Random(maxOffset * 2.0) - maxOffset;

            SpawnObject(Vector3(xOffset, 50, zOffset), Quaternion(), "SnowCrate");
        }
    }

    // Spawn enemies
    enemySpawnTimer += timeStep;
    if (enemySpawnTimer > enemySpawnRate)
    {
        enemySpawnTimer = 0;
        int numEnemies = 0;
        Array<Node@> ninjaNodes = gameScene.GetChildrenWithScript("Ninja", true);
        for (uint i = 0; i < ninjaNodes.length; ++i)
        {
            Ninja@ ninja = cast<Ninja>(ninjaNodes[i].scriptObject);
            if (ninja.side == SIDE_ENEMY)
                ++numEnemies;
        }

        if (numEnemies < maxEnemies)
        {
            const float maxOffset = 40;
            float offset = Random(maxOffset * 2.0) - maxOffset;
            // Random north/east/south/west direction
            int dir = RandomInt() & 3;
            dir *= 90;
            Quaternion rotation(0, dir, 0);

            Node@ enemyNode = SpawnObject(rotation * Vector3(offset, 10, -120), rotation, "Ninja");

            // Initialize variables
            Ninja@ enemyNinja = cast<Ninja>(enemyNode.scriptObject);
            enemyNinja.side = SIDE_ENEMY;
            @enemyNinja.controller = AIController();
            RigidBody@ enemyBody = enemyNode.GetComponent("RigidBody");
            enemyBody.linearVelocity = rotation * Vector3(0, 10, 30);
        }
    }
}

void CheckEndAndRestart()
{
    // Only check end of game if singleplayer or client
    if (runServer)
        return;

    // Check if player node has vanished
    Node@ playerNode = FindOwnNode();
    if (gameOn && playerNode is null)
    {
        gameOn = false;
        SetMessage("Press Fire or Jump to restart!");
        return;
    }

    // Check for restart (singleplayer only)
    if (!gameOn && singlePlayer && playerControls.IsPressed(CTRL_FIRE | CTRL_JUMP, prevPlayerControls))
        StartGame(null);
}

void UpdateControls()
{
    if (singlePlayer || runClient)
    {
        prevPlayerControls = playerControls;
        playerControls.Set(CTRL_ALL, false);

        if (touchEnabled)
        {
            for (uint i = 0; i < input.numTouches; ++i)
            {
                TouchState@ touch = input.touches[i];
                if (touch.touchedElement is null)
                {
                    // Touch on empty space
                    playerControls.yaw += touchSensitivity * gameCamera.fov / graphics.height * touch.delta.x;
                    playerControls.pitch += touchSensitivity * gameCamera.fov / graphics.height * touch.delta.y;
                }
            }
        }

        if (input.numJoysticks > 0)
        {
            JoystickState@ joystick = touchEnabled ? input.joysticks[screenJoystickID] : input.joysticksByIndex[0];
            if (joystick.numButtons > 0)
            {
                if (joystick.buttonDown[0])
                    playerControls.Set(CTRL_JUMP, true);
                if (joystick.buttonDown[1])
                    playerControls.Set(CTRL_FIRE, true);
                if (joystick.numButtons >= 6)
                {
                    if (joystick.buttonDown[4])
                        playerControls.Set(CTRL_JUMP, true);
                    if (joystick.buttonDown[5])
                        playerControls.Set(CTRL_FIRE, true);
                }
                if (joystick.numHats > 0)
                {
                    if (joystick.hatPosition[0] & HAT_LEFT != 0)
                        playerControls.Set(CTRL_LEFT, true);
                    if (joystick.hatPosition[0] & HAT_RIGHT != 0)
                        playerControls.Set(CTRL_RIGHT, true);
                    if (joystick.hatPosition[0] & HAT_UP != 0)
                        playerControls.Set(CTRL_UP, true);
                    if (joystick.hatPosition[0] & HAT_DOWN != 0)
                        playerControls.Set(CTRL_DOWN, true);
                }
                if (joystick.numAxes >= 2)
                {
                    if (joystick.axisPosition[0] < -joyMoveDeadZone)
                        playerControls.Set(CTRL_LEFT, true);
                    if (joystick.axisPosition[0] > joyMoveDeadZone)
                        playerControls.Set(CTRL_RIGHT, true);
                    if (joystick.axisPosition[1] < -joyMoveDeadZone)
                        playerControls.Set(CTRL_UP, true);
                    if (joystick.axisPosition[1] > joyMoveDeadZone)
                        playerControls.Set(CTRL_DOWN, true);
                }
                if (joystick.numAxes >= 4)
                {
                    float lookX = joystick.axisPosition[2];
                    float lookY = joystick.axisPosition[3];

                    if (lookX < -joyLookDeadZone)
                        playerControls.yaw -= joySensitivity * lookX * lookX;
                    if (lookX > joyLookDeadZone)
                        playerControls.yaw += joySensitivity * lookX * lookX;
                    if (lookY < -joyLookDeadZone)
                        playerControls.pitch -= joySensitivity * lookY * lookY;
                    if (lookY > joyLookDeadZone)
                        playerControls.pitch += joySensitivity * lookY * lookY;
                }
            }
        }

        // For the triggered actions (fire & jump) check also for press, in case the FPS is low
        // and the key was already released
        if (console is null || !console.visible)
        {
            if (input.keyDown['W'])
                playerControls.Set(CTRL_UP, true);
            if (input.keyDown['S'])
                playerControls.Set(CTRL_DOWN, true);
            if (input.keyDown['A'])
                playerControls.Set(CTRL_LEFT, true);
            if (input.keyDown['D'])
                playerControls.Set(CTRL_RIGHT, true);
            if (input.keyDown[KEY_LCTRL] || input.keyPress[KEY_LCTRL])
                playerControls.Set(CTRL_FIRE, true);
            if (input.keyDown[' '] || input.keyPress[' '])
                playerControls.Set(CTRL_JUMP, true);

            if (input.mouseButtonDown[MOUSEB_LEFT] || input.mouseButtonPress[MOUSEB_LEFT])
                playerControls.Set(CTRL_FIRE, true);
            if (input.mouseButtonDown[MOUSEB_RIGHT] || input.mouseButtonPress[MOUSEB_RIGHT])
                playerControls.Set(CTRL_JUMP, true);

            playerControls.yaw += mouseSensitivity * input.mouseMoveX;
            playerControls.pitch += mouseSensitivity * input.mouseMoveY;
            playerControls.pitch = Clamp(playerControls.pitch, -60.0, 60.0);
        }

        // In singleplayer, set controls directly on the player's ninja. In multiplayer, transmit to server
        if (singlePlayer)
        {
            Node@ playerNode = gameScene.GetChild("Player", true);
            if (playerNode !is null)
            {
                Ninja@ playerNinja = cast<Ninja>(playerNode.scriptObject);
                playerNinja.controls = playerControls;
            }
        }
        else if (network.serverConnection !is null)
        {
            // Set the latest yaw & pitch to server controls, and accumulate the buttons so that we do not miss any presses
            network.serverConnection.controls.yaw = playerControls.yaw;
            network.serverConnection.controls.pitch = playerControls.pitch;
            network.serverConnection.controls.buttons |= playerControls.buttons;

            // Tell the camera position to server for interest management
            network.serverConnection.position = gameCameraNode.worldPosition;
        }
    }

    if (runServer)
    {
        // Apply each connection's controls to the ninja they control
        for (uint i = 0; i < players.length; ++i)
        {
            Node@ playerNode = FindPlayerNode(i);
            if (playerNode !is null)
            {
                Ninja@ playerNinja = cast<Ninja>(playerNode.scriptObject);
                playerNinja.controls = players[i].connection.controls;
            }
            else
            {
                // If player has no ninja, respawn if fire/jump is pressed
                if (players[i].connection.controls.IsPressed(CTRL_FIRE | CTRL_JUMP, players[i].lastControls))
                    SpawnPlayer(players[i].connection);
            }
            players[i].lastControls = players[i].connection.controls;
        }
    }
}

void UpdateCamera()
{
    if (engine.headless)
        return;

    // On the server, use a simple freelook camera
    if (runServer)
    {
        UpdateFreelookCamera();
        return;
    }

    Node@ playerNode = FindOwnNode();
    if (playerNode is null)
        return;

    Vector3 pos = playerNode.position;
    Quaternion dir;

    // Make controls seem more immediate by forcing the current mouse yaw to player ninja's Y-axis rotation
    if (playerNode.vars["Health"].GetInt() > 0)
        playerNode.rotation = Quaternion(0, playerControls.yaw, 0);

    dir = dir * Quaternion(playerNode.rotation.yaw, Vector3(0, 1, 0));
    dir = dir * Quaternion(playerControls.pitch, Vector3(1, 0, 0));

    Vector3 aimPoint = pos + Vector3(0, 1, 0);
    Vector3 minDist = aimPoint + dir * Vector3(0, 0, -cameraMinDist);
    Vector3 maxDist = aimPoint + dir * Vector3(0, 0, -cameraMaxDist);

    // Collide camera ray with static objects (collision mask 2)
    Vector3 rayDir = (maxDist - minDist).Normalized();
    float rayDistance = cameraMaxDist - cameraMinDist + cameraSafetyDist;
    PhysicsRaycastResult result = gameScene.physicsWorld.RaycastSingle(Ray(minDist, rayDir), rayDistance, 2);
    if (result.body !is null)
        rayDistance = Min(rayDistance, result.distance - cameraSafetyDist);

    gameCameraNode.position = minDist + rayDir * rayDistance;
    gameCameraNode.rotation = dir;
}

void UpdateFreelookCamera()
{
    if (console is null || !console.visible)
    {
        float timeStep = time.timeStep;
        float speedMultiplier = 1.0;
        if (input.keyDown[KEY_LSHIFT])
            speedMultiplier = 5.0;
        if (input.keyDown[KEY_LCTRL])
            speedMultiplier = 0.1;

        if (input.keyDown['W'])
            gameCameraNode.Translate(Vector3(0, 0, 10) * timeStep * speedMultiplier);
        if (input.keyDown['S'])
            gameCameraNode.Translate(Vector3(0, 0, -10) * timeStep * speedMultiplier);
        if (input.keyDown['A'])
            gameCameraNode.Translate(Vector3(-10, 0, 0) * timeStep * speedMultiplier);
        if (input.keyDown['D'])
            gameCameraNode.Translate(Vector3(10, 0, 0) * timeStep * speedMultiplier);

        playerControls.yaw += mouseSensitivity * input.mouseMoveX;
        playerControls.pitch += mouseSensitivity * input.mouseMoveY;
        playerControls.pitch = Clamp(playerControls.pitch, -90.0, 90.0);
        gameCameraNode.rotation = Quaternion(playerControls.pitch, playerControls.yaw, 0);
    }
}

void UpdateStatus()
{
    if (engine.headless || runServer)
        return;

    if (singlePlayer)
    {
        if (players.length > 0)
            scoreText.text = "Score " + players[0].score;
        if (hiscores.length > 0)
            hiscoreText.text = "Hiscore " + hiscores[0].score;
    }

    Node@ playerNode = FindOwnNode();
    if (playerNode !is null)
    {
        int health = 0;
        if (singlePlayer)
        {
            GameObject@ object = cast<GameObject>(playerNode.scriptObject);
            health = object.health;
        }
        else
        {
            // In multiplayer the client does not have script logic components, but health is replicated via node user variables
            health = playerNode.vars["Health"].GetInt();
        }
        healthBar.width = 116 * health / playerHealth;
    }
}

void HandleScreenMode()
{
    int height = graphics.height / 22;
    if (height > 64)
        height = 64;
    sight.SetSize(height, height);
    messageText.SetPosition(0, -height * 2);
}
