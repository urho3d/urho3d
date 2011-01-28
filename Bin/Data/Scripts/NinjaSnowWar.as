#include "Scripts/Controls.as"
#include "Scripts/GameObject.as"

Scene@ gameScene;
Camera@ gameCamera;
Text@ scoreText;
Text@ hiscoreText;
Text@ messageText;
BorderImage@ healthBar;

Controls playerControls;
float mouseSensitivity = 0.125;
float cameraMinDist = 25;
float cameraMaxDist = 500;
float cameraSafetyDist = 30;
bool paused = false;

void init()
{
    initAudio();
    initConsole();
    initScene();
    createCamera();
    createOverlays();
    spawnPlayer();

    engine.createDebugHud();
    debugHud.setFont(cache.getResource("Font", "cour.ttf"), 12);

    subscribeToEvent("Update", "handleUpdate");
    subscribeToEvent("PostUpdate", "handlePostUpdate");
}

void runFrame()
{
    engine.runFrame(gameScene, gameCamera, !paused);

    if (input.getKeyPress(KEY_ESCAPE))
        engine.exit();
}

void initAudio()
{
    // Lower mastervolumes slightly
    audio.setMasterGain(CHANNEL_MASTER, 0.75f);
    audio.setMasterGain(CHANNEL_MUSIC, 0.75f);

    // Start music playback
    Song@ song = cache.getResource("XM", "Music/NinjaGods.xm");
    song.play(0);
}

void initConsole()
{
    Console@ console = engine.createConsole();
    console.setNumRows(16);
    console.setFont(cache.getResource("Font", "cour.ttf"), 12);
    BorderImage@ cursor = console.getLineEditElement().getCursorElement();
    cursor.setWidth(4);
    cursor.setTexture(cache.getResource("Texture2D", "Textures/UI.png"));
    cursor.setImageRect(112, 0, 116, 16);
}

void initScene()
{
    @gameScene = engine.createScene("ScriptTest", BoundingBox(-100000.0, 100000.0), 8, true);

    File@ levelFile = cache.getFile("TestLevel.xml");
    gameScene.loadXML(levelFile);
}

void createCamera()
{
    Entity@ cameraEntity = gameScene.createEntity("Camera");
    @gameCamera = cameraEntity.createComponent("Camera");
    gameCamera.setAspectRatio(float(renderer.getWidth()) / float(renderer.getHeight()));
    gameCamera.setNearClip(10.0);
    gameCamera.setFarClip(16000.0);
    gameCamera.setPosition(Vector3(0, 200, -1000));
}

void createOverlays()
{
    BorderImage@ sight = BorderImage();
    sight.setTexture(cache.getResource("Texture2D", "Textures/Sight.png"));
    sight.setAlignment(HA_CENTER, VA_CENTER);
    int height = renderer.getHeight() / 22;
    if (height > 64)
        height = 64;
    sight.setSize(height, height);
    uiRoot.addChild(sight);

    Font@ font = cache.getResource("Font", "Fonts/BlueHighway.ttf");

    @scoreText = Text();
    scoreText.setFont(font, 17);
    scoreText.setAlignment(HA_LEFT, VA_TOP);
    scoreText.setPosition(5, 5);
    scoreText.setColor(C_BOTTOMLEFT, Color(1, 1, 0.25));
    scoreText.setColor(C_BOTTOMRIGHT, Color(1, 1, 0.25));
    uiRoot.addChild(scoreText);

    @hiscoreText = Text();
    hiscoreText.setFont(font, 17);
    hiscoreText.setAlignment(HA_RIGHT, VA_TOP);
    hiscoreText.setPosition(-5, 5);
    hiscoreText.setColor(C_BOTTOMLEFT, Color(1, 1, 0.25));
    hiscoreText.setColor(C_BOTTOMRIGHT, Color(1, 1, 0.25));
    uiRoot.addChild(hiscoreText);

    @messageText = Text();
    messageText.setFont(font, 17);
    messageText.setColor(Color(1, 0, 0));
    messageText.setAlignment(HA_CENTER, VA_CENTER);
    messageText.setPosition(0, -height * 2);
    uiRoot.addChild(messageText);

    BorderImage@ healthBorder = BorderImage();
    healthBorder.setTexture(cache.getResource("Texture2D", "Textures/HealthBarBorder.png"));
    healthBorder.setAlignment(HA_CENTER, VA_TOP);
    healthBorder.setPosition(0, 8);
    healthBorder.setSize(120, 20);
    uiRoot.addChild(healthBorder);

    @healthBar = BorderImage();
    healthBar.setTexture(cache.getResource("Texture2D", "Textures/HealthBarInside.png"));
    healthBar.setPosition(2, 2);
    healthBar.setSize(116, 16);
    healthBorder.addChild(healthBar);
    uiRoot.addChild(healthBorder);
}

void spawnPlayer()
{
    Entity@ playerEntity = gameScene.createEntity("ObjPlayer");
    ScriptInstance@ instance = playerEntity.createComponent("ScriptInstance");
    instance.setScriptClass(cache.getResource("ScriptFile", "Scripts/Ninja.as"), "Ninja");
    GameObject@ object = cast<GameObject>(instance.getScriptObject());
    object.create(Vector3(0, 90, 0), Quaternion());
}

void handleUpdate(StringHash eventType, VariantMap& eventData)
{
    if (input.getKeyPress(220))
        console.toggle();
    if (input.getKeyPress(KEY_F1))
        debugHud.toggleAll();
    if (input.getKeyPress(KEY_F2))
        engine.setDebugDrawMode(engine.getDebugDrawMode() ^ DEBUGDRAW_PHYSICS);

    if ((!console.isVisible()) && (input.getKeyPress('P')))
    {
        paused = !paused;
        if (paused)
            messageText.setText("PAUSED");
        else
            messageText.setText("");
    }

    if (!paused)
        updateControls();
}

void handlePostUpdate(StringHash eventType, VariantMap& eventData)
{
    updateCamera();
}

void updateControls()
{
    playerControls.set(CTRL_ALL, false);

    if (!console.isVisible())
    {
        if (input.getKeyDown('W'))
            playerControls.set(CTRL_UP, true);
        if (input.getKeyDown('S'))
            playerControls.set(CTRL_DOWN, true);
        if (input.getKeyDown('A'))
            playerControls.set(CTRL_LEFT, true);
        if (input.getKeyDown('D'))
            playerControls.set(CTRL_RIGHT, true);
        if (input.getKeyDown(KEY_CONTROL))
            playerControls.set(CTRL_FIRE, true);
        if (input.getKeyDown(' '))
            playerControls.set(CTRL_JUMP, true);
    }

    if (input.getMouseButtonDown(MOUSEB_LEFT))
        playerControls.set(CTRL_FIRE, true);
    if (input.getMouseButtonDown(MOUSEB_RIGHT))
        playerControls.set(CTRL_JUMP, true);

    playerControls.yaw += mouseSensitivity * input.getMouseMoveX();
    playerControls.pitch += mouseSensitivity * input.getMouseMoveY();
    playerControls.pitch = clamp(playerControls.pitch, -60, 60);

    Entity@ playerEntity = gameScene.getEntity("ObjPlayer");
    if (@playerEntity == null)
        return;

    ScriptInstance@ instance = playerEntity.getComponent("ScriptInstance");
    GameObject@ object = cast<GameObject>(instance.getScriptObject());
    object.setControls(playerControls);
}

void updateCamera()
{
    Entity@ playerEntity = gameScene.getEntity("ObjPlayer");
    if (@playerEntity == null)
        return;

    RigidBody@ body = playerEntity.getComponent("RigidBody");
    Vector3 pos = body.getWorldPosition();
    Quaternion dir;
    dir = dir * Quaternion(playerControls.yaw, Vector3(0, 1, 0));
    dir = dir * Quaternion(playerControls.pitch, Vector3(1, 0, 0));

    Vector3 aimPoint = pos + Vector3(0, 100, 0);
    Vector3 minDist = aimPoint + dir * Vector3(0, 0, -cameraMinDist);
    Vector3 maxDist = aimPoint + dir * Vector3(0, 0, -cameraMaxDist);

    // Collide camera ray with static objects (collision mask 2)
    Vector3 rayDir = (maxDist - minDist).getNormalized();
    float rayDistance = cameraMaxDist - cameraMinDist + cameraSafetyDist;
    array<PhysicsRaycastResult>@ result = gameScene.getPhysicsWorld().raycast(Ray(minDist, rayDir), rayDistance, 2);
    if (result.length() > 0)
        rayDistance = min(rayDistance, result[0].distance - cameraSafetyDist);
    
    gameCamera.setPosition(minDist + rayDir * rayDistance);
    gameCamera.setRotation(dir);

    audio.setListenerPosition(pos);
    audio.setListenerRotation(dir);
}
