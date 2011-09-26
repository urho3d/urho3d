// Remake of NinjaSnowWar in script

#include "Scripts/NinjaSnowWar/LightFlash.as"
#include "Scripts/NinjaSnowWar/Ninja.as"
#include "Scripts/NinjaSnowWar/Player.as"
#include "Scripts/NinjaSnowWar/Potion.as"
#include "Scripts/NinjaSnowWar/SnowBall.as"
#include "Scripts/NinjaSnowWar/SnowCrate.as"
#include "Scripts/Utilities/Network.as"

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
const float spawnAreaSize = 500;

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

    SubscribeToEvent("Update", "HandleUpdate");
    if (gameScene.physicsWorld !is null)
        SubscribeToEvent(gameScene.physicsWorld, "PhysicsPreStep", "HandleFixedUpdate");
    SubscribeToEvent(gameScene, "ScenePostUpdate", "HandlePostUpdate");
    SubscribeToEvent("PostRenderUpdate", "HandlePostRenderUpdate");
    SubscribeToEvent("Points", "HandlePoints");
    SubscribeToEvent("Kill", "HandleKill");
    SubscribeToEvent("ScreenMode", "HandleScreenMode");

    if (singlePlayer)
        StartGame(null);
}

void InitAudio()
{
    if (engine.headless)
        return;

    // Lower mastervolumes slightly. On the server, turn sound off completely
    audio.masterGain[SOUND_MASTER] = runServer ? 0.0 : 0.75;
    audio.masterGain[SOUND_MUSIC] = 0.75;

    // Start music playback (play in singleplayer only to avoid cacophony if testing with multiple connections)
    // Note: the non-positional sound source component does not need to be in the scene
    if (singlePlayer)
    {
        Sound@ musicFile = cache.GetResource("Sound", "Music/Ninja Gods.ogg");
        musicFile.looped = true;
        musicSource = SoundSource();
        musicSource.Play(musicFile);
    }
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
    
    // Set network snap threshold higher, as the world unit is centimeter
    gameScene.snapThreshold = 100.0;

    // Enable access to this script file & scene from the console
    script.defaultScene = gameScene;
    script.defaultScriptFile = scriptFile;

    // For the multiplayer client, do not create the scene, let it load from the server
    if (runClient)
        return;

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

    Node@ lightNode = gameScene.CreateChild("GlobalLight");
    lightNode.rotation = Quaternion(0.888074, 0.325058, -0.325058, 0);
    Light@ light = lightNode.CreateComponent("Light");
    light.lightType = LIGHT_DIRECTIONAL;
    light.castShadows = true;
    light.shadowNearFarRatio = 0.002;
    light.shadowBias = BiasParameters(0.00025, 0.001);
    light.shadowCascade = CascadeParameters(1000.0, 2000.0, 5000.0, 0.0, 0.8);
    light.shadowFocus = FocusParameters(true, true, true, 25, 500);

    Node@ staticNode = gameScene.CreateChild("Static");
    StaticModel@ staticModel = staticNode.CreateComponent("StaticModel");
    staticModel.model = cache.GetResource("Model", "Models/Level.mdl");
    staticModel.material = cache.GetResource("Material", "Materials/Snow.xml");
    CollisionShape@ shape = staticNode.CreateComponent("CollisionShape");
    shape.SetTriangleMesh(cache.GetResource("Model", "Models/Level.mdl"), 0);
    shape.collisionLayer = 2;
    shape.collisionMask = 3;

    Node@ skyNode = gameScene.CreateChild("Sky");
    skyNode.position = Vector3(0, 3000, 0);
    skyNode.scale = Vector3(30000, 1, 30000);
    Skybox@ skybox = skyNode.CreateComponent("Skybox");
    skybox.model = cache.GetResource("Model", "Models/CloudPlane.mdl");
    skybox.material = cache.GetResource("Material", "Materials/CloudPlane.xml");
}

void InitNetworking()
{
    network.RegisterRemoteEvent("PlayerSpawned");
    network.RegisterRemoteEvent("UpdateScore");
    network.RegisterRemoteEvent("UpdateHiscores");

    if (runServer)
    {
        network.StartServer(serverPort);

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
    }
}

void CreateCamera()
{
    // Note: the camera is not in the scene
    gameCameraNode = Node();
    gameCameraNode.position = Vector3(0, 200, -1000);

    gameCamera = gameCameraNode.CreateComponent("Camera");
    gameCamera.nearClip = 50.0;
    gameCamera.farClip = 16000.0;

    if (!engine.headless)
        renderer.viewports[0] = Viewport(gameScene, gameCamera);
}

void CreateOverlays()
{
    if (engine.headless || runServer)
        return;

    int height = graphics.height / 22;
    if (height > 64)
        height = 64;

    sight = BorderImage();
    sight.texture = cache.GetResource("Texture2D", "Textures/Sight.png");
    sight.SetAlignment(HA_CENTER, VA_CENTER);
    sight.SetSize(height, height);
    ui.root.AddChild(sight);

    Font@ font = cache.GetResource("Font", "Fonts/BlueHighway.ttf");

    scoreText = Text();
    scoreText.SetFont(font, 17);
    scoreText.SetAlignment(HA_LEFT, VA_TOP);
    scoreText.SetPosition(5, 5);
    scoreText.colors[C_BOTTOMLEFT] = Color(1, 1, 0.25);
    scoreText.colors[C_BOTTOMRIGHT] = Color(1, 1, 0.25);
    ui.root.AddChild(scoreText);

    @hiscoreText = Text();
    hiscoreText.SetFont(font, 17);
    hiscoreText.SetAlignment(HA_RIGHT, VA_TOP);
    hiscoreText.SetPosition(-5, 5);
    hiscoreText.colors[C_BOTTOMLEFT] = Color(1, 1, 0.25);
    hiscoreText.colors[C_BOTTOMRIGHT] = Color(1, 1, 0.25);
    ui.root.AddChild(hiscoreText);

    @messageText = Text();
    messageText.SetFont(font, 17);
    messageText.SetAlignment(HA_CENTER, VA_CENTER);
    messageText.SetPosition(0, -height * 2);
    messageText.color = Color(1, 0, 0);
    ui.root.AddChild(messageText);

    BorderImage@ healthBorder = BorderImage();
    healthBorder.texture = cache.GetResource("Texture2D", "Textures/HealthBarBorder.png");
    healthBorder.SetAlignment(HA_CENTER, VA_TOP);
    healthBorder.SetPosition(0, 8);
    healthBorder.SetSize(120, 20);
    ui.root.AddChild(healthBorder);

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
    // Set owner connection. Owned nodes are always updated to the owner at full frequency
    Node@ playerNode = gameScene.CreateChild("Player");
    playerNode.owner = connection;

     // Create the logic object as local, as it only needs to run on server
    Ninja@ playerNinja = cast<Ninja>(playerNode.CreateScriptObject(scriptFile, "Ninja", LOCAL));
    if (singlePlayer)
        playerNinja.Create(Vector3(0, 90, 0), Quaternion());
    else
        playerNinja.Create(Vector3(Random(spawnAreaSize) - spawnAreaSize * 0.5, 90, Random(spawnAreaSize) - spawnAreaSize), Quaternion());
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
    }
}

void HandleUpdate(StringHash eventType, VariantMap& eventData)
{
    float timeStep = eventData["TimeStep"].GetFloat();

    if (input.keyPress[KEY_F1])
        console.Toggle();
    if (input.keyPress[KEY_F2])
        debugHud.ToggleAll();
    if (input.keyPress[KEY_F3])
        drawDebug = !drawDebug;
    if (input.keyPress[KEY_F4])
        drawOctreeDebug = !drawOctreeDebug;
    
    // Allow pause only in singleplayer
    if (singlePlayer && input.keyPress['P'] && !console.visible && gameOn)
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
    {
        UpdateControls();
        CheckEndAndRestart();
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
        connection.identity["UserName"] = "user" + RandomInt(999);
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
            const float maxOffset = 4000;
            float xOffset = Random(maxOffset * 2.0f) - maxOffset;
            float zOffset = Random(maxOffset * 2.0f) - maxOffset;

            Vector3 position(xOffset, 5000, zOffset);
            Node@ crateNode = gameScene.CreateChild();
            GameObject@ crateObject = cast<GameObject>(crateNode.CreateScriptObject(scriptFile, "SnowCrate", LOCAL));
            crateObject.Create(position, Quaternion());
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
            const float maxOffset = 4000;
            float offset = Random(maxOffset * 2.0) - maxOffset;
            // Random north/east/south/west direction
            int dir = RandomInt() & 3;
            dir *= 90;
            Quaternion q(dir, Vector3(0, 1, 0));
            Vector3 position(q * Vector3(offset, 1000, -12000));

            Node@ enemyNode = gameScene.CreateChild();
            Ninja@ enemyNinja = cast<Ninja>(enemyNode.CreateScriptObject(scriptFile, "Ninja", LOCAL));
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
            network.serverConnection.controls = playerControls;
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
    
    // In multiplayer, make controls seem more immediate by forcing the current mouse yaw into player ninja's Y-axis rotation
    if (runClient && playerNode.vars["Health"].GetInt() > 0)
        playerNode.SnapRotation(Quaternion(0, playerControls.yaw, 0));

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

void UpdateFreelookCamera()
{
    float timeStep = time.timeStep;
    float speedMultiplier = 1.0;
    if (input.keyDown[KEY_LSHIFT])
        speedMultiplier = 5.0;
    if (input.keyDown[KEY_LCTRL])
        speedMultiplier = 0.1;

    if (input.keyDown['W'])
        gameCameraNode.TranslateRelative(Vector3(0, 0, 1000) * timeStep * speedMultiplier);
    if (input.keyDown['S'])
        gameCameraNode.TranslateRelative(Vector3(0, 0, -1000) * timeStep * speedMultiplier);
    if (input.keyDown['A'])
        gameCameraNode.TranslateRelative(Vector3(-1000, 0, 0) * timeStep * speedMultiplier);
    if (input.keyDown['D'])
        gameCameraNode.TranslateRelative(Vector3(1000, 0, 0) * timeStep * speedMultiplier);

    playerControls.yaw += mouseSensitivity * input.mouseMoveX;
    playerControls.pitch += mouseSensitivity * input.mouseMoveY;
    playerControls.pitch = Clamp(playerControls.pitch, -90, 90);
    gameCameraNode.rotation = Quaternion(playerControls.pitch, playerControls.yaw, 0);
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
