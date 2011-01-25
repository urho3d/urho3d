Scene@ gameScene;
Camera@ gameCamera;
Text@ scoreText;
Text@ hiscoreText;
Text@ messageText;
BorderImage@ healthBar;

void init(Scene@ scene)
{
    @gameScene = @scene;

    initAudio();
    loadScene();
    createCamera();
    createOverlays();
    spawnPlayer();

    engine.createDebugHud();
    debugHud.setFont(cache.getResource("Font", "cour.ttf"), 12);

    registerLocalOnlyEvent("Create");
    subscribeToEvent("Update", "handleUpdate");
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

void loadScene()
{
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

    // To work properly, the script object's methods must be executed in its own context. Therefore we don't (and can't) directly access the script object
    VariantMap eventData;
    eventData["Pos"] = Vector3(0, 90, 0);
    eventData["Rot"] = Quaternion();
    sendEvent(instance, "Create", eventData);
}

void handleUpdate(StringHash eventType, VariantMap& eventData)
{
    if (input.getKeyPress(KEY_F1))
        debugHud.toggleAll();
    if (input.getKeyPress(KEY_F2))
        engine.setDebugDrawMode(engine.getDebugDrawMode() ^ DEBUGDRAW_PHYSICS);
}
