#include "Scripts/Avatar.as"

const float mouseSensitivity = 0.125;
const float cameraMinDist = 1;
const float cameraMaxDist = 6;
const float cameraSafetyDist = 0.30;

Scene@ gameScene;
Camera@ gameCamera;

Controls playerControls;
Controls prevPlayerControls;
bool drawDebug = false;

void start()
{
    initConsole();
    initScene();
    createCamera();
    startGame();

    subscribeToEvent("Update", "handleUpdate");
    subscribeToEvent("PostUpdate", "handlePostUpdate");
    subscribeToEvent("PostRenderUpdate", "handlePostRenderUpdate");
    subscribeToEvent("KeyDown", "handleKeyDown");
    subscribeToEvent("ScreenMode", "handleScreenMode");
}

void initConsole()
{
    if (engine.isHeadless())
        return;

    XMLFile@ uiStyle = cache.getResource("XMLFile", "UI/DefaultStyle.xml");

    Console@ console = engine.createConsole();
    console.setStyle(uiStyle);
    console.setNumRows(16);

    engine.createDebugHud();
    debugHud.setStyle(uiStyle);
}

void initScene()
{
    @gameScene = engine.createScene("AvatarTest", BoundingBox(-1000.0, 1000.0), 8, true);
    // Make the scene & script classes directly accessible from the console
    engine.setDefaultScene(gameScene);
    engine.setDefaultScriptFile(scriptFile);

    File@ levelFile = cache.getFile("GraphicsTestScene.xml");
    gameScene.loadXML(levelFile);
}

void createCamera()
{
    Entity@ cameraEntity = gameScene.createEntity("Camera");
    @gameCamera = cameraEntity.createComponent("Camera");
    gameCamera.setNearClip(0.1);
    gameCamera.setFarClip(500.0);

    if (!engine.isHeadless())
        pipeline.setViewport(0, Viewport(gameScene, gameCamera));
}

void startGame()
{
    Entity@ playerEntity = gameScene.createEntity("Player");
    Avatar@ playerAvatar = cast<Avatar>(playerEntity.createScriptObject(scriptFile, "Avatar"));
    playerAvatar.create(Vector3(50, 5, 50), Quaternion());
    playerAvatar.controls = playerAvatar.prevControls = playerControls;
}

void handleUpdate(StringHash eventType, VariantMap& eventData)
{
    float timeStep = eventData["TimeStep"].getFloat();

    if (input.getKeyPress(KEY_F1))
        debugHud.toggleAll();
    if (input.getKeyPress(KEY_F2))
        drawDebug = !drawDebug;
        
    if (input.getKeyPress(KEY_F5))
        gameScene.save(File(getExecutableDirectory() + "Data/Save.dat", FILE_WRITE));

    if (input.getKeyPress(KEY_ESC))
    {
        if (!console.isVisible())
            engine.exit();
        else
        console.setVisible(false);
    }

    if (!gameScene.isPaused())
        updateControls();
}

void handlePostUpdate()
{
    updateCamera();
    updateStatus();
}

void handlePostRenderUpdate()
{
    if (drawDebug)
        gameScene.getPhysicsWorld().drawDebugGeometry(true);
}

void updateControls()
{
    prevPlayerControls = playerControls;
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
        if (input.getKeyDown(KEY_CTRL))
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

    Entity@ playerEntity = gameScene.getEntity("Player");
    if (playerEntity !is null)
    {
        Avatar@ playerAvatar = cast<Avatar>(playerEntity.getScriptObject());
        playerAvatar.controls = playerControls;
    }
}

void updateCamera()
{
    Entity@ playerEntity = gameScene.getEntity("Player");
    if (playerEntity is null)
        return;

    RigidBody@ body = playerEntity.getComponent("RigidBody");
    Vector3 pos = body.getWorldPosition();
    Quaternion dir;
    dir = dir * Quaternion(playerControls.yaw, Vector3(0, 1, 0));
    dir = dir * Quaternion(playerControls.pitch, Vector3(1, 0, 0));

    Vector3 aimPoint = pos + Vector3(0, 1, 0);
    Vector3 minDist = aimPoint + dir * Vector3(0, 0, -cameraMinDist);
    Vector3 maxDist = aimPoint + dir * Vector3(0, 0, -cameraMaxDist);

    // Collide camera ray with static objects (collision mask 2)
    Vector3 rayDir = (maxDist - minDist).getNormalized();
    float rayDistance = cameraMaxDist - cameraMinDist + cameraSafetyDist;
    array<PhysicsRaycastResult>@ result = gameScene.getPhysicsWorld().raycast(Ray(minDist, rayDir), rayDistance, 2);
    if (result.size() > 0)
        rayDistance = min(rayDistance, result[0].distance - cameraSafetyDist);

    gameCamera.setPosition(minDist + rayDir * rayDistance);
    gameCamera.setRotation(dir);

    audio.setListenerPosition(pos);
    audio.setListenerRotation(dir);
}

void updateStatus()
{
    if (engine.isHeadless())
        return;
}

void handleKeyDown(StringHash eventType, VariantMap& eventData)
{
    // Check for toggling the console
    if (eventData["Key"].getInt() == 220)
    {
        console.toggle();
        input.suppressNextChar();
    }
}

void handleScreenMode()
{
}
