Scene@ gameScene;
Camera@ gameCamera;

void init(Scene@ scene)
{
    @gameScene = @scene;

    initAudio();
    loadScene();
    createCamera();
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
}
