#include "Scripts/Network.as"

Scene@ testScene;
Camera@ camera;
Node@ cameraNode;

float yaw = 0.0;
float pitch = 0.0;
int drawDebug = 0;

Text@ downloadsText;

void Start()
{
    if (!engine.headless)
    {
        InitConsole();
        InitUI();
    }
    else
        OpenConsoleWindow();

    InitScene();

    SubscribeToEvent("Update", "HandleUpdate");
    SubscribeToEvent("KeyDown", "HandleKeyDown");
    SubscribeToEvent("MouseMove", "HandleMouseMove");
    SubscribeToEvent("MouseButtonDown", "HandleMouseButtonDown");
    SubscribeToEvent("MouseButtonUp", "HandleMouseButtonUp");
    SubscribeToEvent("PostRenderUpdate", "HandlePostRenderUpdate");
    SubscribeToEvent("SpawnBox", "HandleSpawnBox");

    network.RegisterRemoteEvent("SpawnBox");
    
    ParseNetworkArguments();
    if (runServer)
    {
        network.StartServer(serverPort);
        SubscribeToEvent("ClientConnected", "HandleClientConnected");

        // Test package download by adding all package files in the cache as requirements for the scene
        Array<PackageFile@> packages = cache.packageFiles;
        for (uint i = 0; i < packages.length; ++i)
            testScene.AddRequiredPackageFile(packages[i]);
    }
    if (runClient)
    {
        testScene.Clear();

        // Test package download. Remove existing Data.pak from resource cache so that it will be downloaded
        // However, be sure to add the Data directory so that resource requests do not fail in the meanwhile
        String packageName = fileSystem.programDir + "Data.pak";
        cache.RemovePackageFile(packageName, false);
        cache.AddResourceDir(fileSystem.programDir + "Data");

        network.packageCacheDir = fileSystem.programDir;
        network.Connect(serverAddress, serverPort, testScene);
    }
}

void InitConsole()
{
    XMLFile@ uiStyle = cache.GetResource("XMLFile", "UI/DefaultStyle.xml");

    engine.CreateDebugHud();
    debugHud.style = uiStyle;
    debugHud.mode = DEBUGHUD_SHOW_ALL;

    engine.CreateConsole();
    console.style = uiStyle;
}

void InitUI()
{
    XMLFile@ uiStyle = cache.GetResource("XMLFile", "UI/DefaultStyle.xml");

    Cursor@ newCursor = Cursor("Cursor");
    newCursor.style = uiStyle;
    newCursor.position = IntVector2(graphics.width / 2, graphics.height / 2);
    ui.cursor = newCursor;
    
    downloadsText = Text();
    downloadsText.SetAlignment(HA_CENTER, VA_CENTER);
    downloadsText.SetFont(cache.GetResource("Font", "Fonts/Anonymous Pro.ttf"), 20);
    ui.root.AddChild(downloadsText);
}

void InitScene()
{
    testScene = Scene("TestScene");

    PhysicsWorld@ world = testScene.CreateComponent("PhysicsWorld");
    testScene.CreateComponent("Octree");
    testScene.CreateComponent("DebugRenderer");

    world.gravity = Vector3(0.0, -9.81, 0.0);
    world.fps = 100;
    world.linearRestThreshold = 0.1;
    world.angularRestThreshold = 0.1;
    world.contactSurfaceLayer = 0.001;

    Zone@ zone = testScene.CreateComponent("Zone");
    zone.ambientColor = Color(0.1, 0.1, 0.1);
    zone.fogColor = Color(0.5, 0.5, 0.7);
    zone.fogStart = 100.0;
    zone.fogEnd = 300.0;
    zone.boundingBox = BoundingBox(-1000.0, 1000.0);

    {
        Node@ lightNode = testScene.CreateChild("Light");
        lightNode.direction = Vector3(0.5, -0.5, 0.5);

        Light@ light = lightNode.CreateComponent("Light");
        light.lightType = LIGHT_DIRECTIONAL;
        light.castShadows = true;
        light.shadowBias = BiasParameters(0.0001, 0.5);
        light.shadowCascade = CascadeParameters(3, 0.90, 0.2, 200.0);
        light.specularIntensity = 0.5f;
    }

    {
        Node@ objectNode = testScene.CreateChild("Floor");
        objectNode.position = Vector3(0.0, -0.5, 0.0);
        objectNode.scale = Vector3(100.0, 0.5, 100.0);

        StaticModel@ object = objectNode.CreateComponent("StaticModel");
        object.model = cache.GetResource("Model", "Models/Box.mdl");
        object.material = cache.GetResource("Material", "Materials/Test.xml");
        object.occluder = true;

        CollisionShape@ shape = objectNode.CreateComponent("CollisionShape");
        shape.SetBox(Vector3(2.0, 2.0, 2.0), Vector3(), Quaternion());
        shape.collisionGroup = 2;
        shape.collisionMask = 1;
    }

    for (uint i = 0; i < 50; ++i)
    {
        Node@ objectNode = testScene.CreateChild("Box");
        objectNode.position = Vector3(Random(180.0) - 90.0, 1.0, Random(180.0) - 90.0);

        StaticModel@ object = objectNode.CreateComponent("StaticModel");
        object.model = cache.GetResource("Model", "Models/Box.mdl");
        object.material = cache.GetResource("Material", "Materials/Test.xml");
        object.castShadows = true;

        CollisionShape@ shape = objectNode.CreateComponent("CollisionShape");
        shape.SetBox(Vector3(2.0, 2.0, 2.0), Vector3(), Quaternion());
        shape.collisionGroup = 2;
        shape.collisionMask = 1;
    }

    for (uint i = 0; i < 10; ++i)
    {
        Node@ objectNode = testScene.CreateChild("Box");
        objectNode.position = Vector3(Random(180.0) - 90.0, 10.0, Random(180.0) - 90.0);
        objectNode.SetScale(10.0);

        StaticModel@ object = objectNode.CreateComponent("StaticModel");
        object.model = cache.GetResource("Model", "Models/Box.mdl");
        object.material = cache.GetResource("Material", "Materials/Test.xml");
        object.castShadows = true;
        object.occluder = true;

        CollisionShape@ shape = objectNode.CreateComponent("CollisionShape");
        shape.SetBox(Vector3(2.0, 2.0, 2.0), Vector3(), Quaternion());
        shape.collisionGroup = 2;
        shape.collisionMask = 1;
    }

    for (uint i = 0; i < 50; ++i)
    {
        Node@ objectNode = testScene.CreateChild("Mushroom");
        objectNode.position = Vector3(Random(180.0) - 90.0, 0.0, Random(180.0) - 90.0);
        objectNode.rotation = Quaternion(0.0, Random(360.0), 0.0);
        objectNode.SetScale(5.0);

        StaticModel@ object = objectNode.CreateComponent("StaticModel");
        object.model = cache.GetResource("Model", "Models/Mushroom.mdl");
        object.material = cache.GetResource("Material", "Materials/Mushroom.xml");
        object.castShadows = true;

        CollisionShape@ shape = objectNode.CreateComponent("CollisionShape");
        shape.SetTriangleMesh(cache.GetResource("Model", "Models/Mushroom.mdl"), 0, Vector3(), Quaternion());
        shape.collisionGroup = 2;
        shape.collisionMask = 1;
    }

    for (uint i = 0; i < 50; ++i)
    {
        Node@ objectNode = testScene.CreateChild("Jack");
        objectNode.position = Vector3(Random(180.0) - 90.0, 0.0, Random(180.0) - 90.0);
        objectNode.rotation = Quaternion(0.0, Random(360.0), 0.0);

        AnimatedModel@ object = objectNode.CreateComponent("AnimatedModel");
        object.model = cache.GetResource("Model", "Models/Jack.mdl");
        object.material = cache.GetResource("Material", "Materials/Jack.xml");
        object.castShadows = true;

        AnimationController@ ctrl = objectNode.CreateComponent("AnimationController");
        ctrl.Play("Models/Jack_Walk.ani", 0, true, 0.0f);
    }

    // Enable access to this script file & scene from the console
    script.defaultScene = testScene;
    script.defaultScriptFile = scriptFile;

    // Create the camera outside the scene so it is unaffected by scene load/save
    cameraNode = Node();
    camera = cameraNode.CreateComponent("Camera");
    cameraNode.position = Vector3(0, 2, 0);

    if (!engine.headless)
        renderer.viewports[0] = Viewport(testScene, camera);
}

void HandleUpdate(StringHash eventType, VariantMap& eventData)
{
    float timeStep = eventData["TimeStep"].GetFloat();

    if (ui.focusElement is null)
    {
        float speedMultiplier = 1.0;
        if (input.keyDown[KEY_LSHIFT])
            speedMultiplier = 5.0;
        if (input.keyDown[KEY_LCTRL])
            speedMultiplier = 0.1;

        if (input.keyDown['W'])
            cameraNode.TranslateRelative(Vector3(0, 0, 10) * timeStep * speedMultiplier);
        if (input.keyDown['S'])
            cameraNode.TranslateRelative(Vector3(0, 0, -10) * timeStep * speedMultiplier);
        if (input.keyDown['A'])
            cameraNode.TranslateRelative(Vector3(-10, 0, 0) * timeStep * speedMultiplier);
        if (input.keyDown['D'])
            cameraNode.TranslateRelative(Vector3(10, 0, 0) * timeStep * speedMultiplier);

        if (input.keyPress['1'])
        {
            int nextRenderMode = graphics.renderMode;
            if (input.keyDown[KEY_LSHIFT])
            {
                --nextRenderMode;
                if (nextRenderMode < 0)
                    nextRenderMode = 1;
            }
            else
            {
                ++nextRenderMode;
                if (nextRenderMode > 1)
                    nextRenderMode = 0;
            }

            graphics.SetMode(RenderMode(nextRenderMode));
        }

        if (input.keyPress['2'])
        {
            int quality = renderer.textureQuality;
            ++quality;
            if (quality > 2)
                quality = 0;
            renderer.textureQuality = quality;
        }

        if (input.keyPress['3'])
        {
            int quality = renderer.materialQuality;
            ++quality;
            if (quality > 2)
                quality = 0;
            renderer.materialQuality = quality;
        }

        if (input.keyPress['4'])
            renderer.specularLighting = !renderer.specularLighting;

        if (input.keyPress['5'])
            renderer.drawShadows = !renderer.drawShadows;

        if (input.keyPress['6'])
        {
            int size = renderer.shadowMapSize;
            size *= 2;
            if (size > 2048)
                size = 512;
            renderer.shadowMapSize = size;
        }

        if (input.keyPress['7'])
            renderer.shadowMapHiresDepth = !renderer.shadowMapHiresDepth;

        if (input.keyPress['8'])
        {
            bool occlusion = renderer.maxOccluderTriangles > 0;
            occlusion = !occlusion;
            renderer.maxOccluderTriangles = occlusion ? 5000 : 0;
        }
        
        if (input.keyPress['9'])
            renderer.dynamicInstancing = !renderer.dynamicInstancing;

        if (input.keyPress[' '])
        {
            drawDebug++;
            if (drawDebug > 2)
                drawDebug = 0;
        }

        if (input.keyPress['C'])
            camera.orthographic = !camera.orthographic;

        if (input.keyPress['T'])
            debugHud.Toggle(DEBUGHUD_SHOW_PROFILER);

        if (input.keyPress[KEY_F5])
        {
            File@ xmlFile = File("scene.xml", FILE_WRITE);
            testScene.SaveXML(xmlFile);
        }

        if (input.keyPress[KEY_F7])
        {
            File@ xmlFile = File("scene.xml", FILE_READ);
            if (xmlFile.open)
                testScene.LoadXML(xmlFile);
        }
    }

    if (input.keyPress[KEY_ESC])
    {
        if (ui.focusElement is null)
            engine.Exit();
        else
            console.visible = false;
    }

    // Update package download status
    if (network.serverConnection !is null)
    {
        Connection@ connection = network.serverConnection;
        if (connection.numDownloads > 0)
        {
            downloadsText.text = "Downloads: " + connection.numDownloads + " Current download: " +
                connection.downloadName + " (" + int(connection.downloadProgress * 100.0) + "%)";
        }
        else if (!downloadsText.text.empty)
            downloadsText.text = "";
    }
}

void HandleKeyDown(StringHash eventType, VariantMap& eventData)
{
    // Check for toggling the console
    if (eventData["Key"].GetInt() == KEY_F1)
        console.Toggle();
}

void HandleMouseMove(StringHash eventType, VariantMap& eventData)
{
    if (eventData["Buttons"].GetInt() & MOUSEB_RIGHT != 0)
    {
        int mousedx = eventData["DX"].GetInt();
        int mousedy = eventData["DY"].GetInt();
        yaw += mousedx / 10.0f;
        pitch += mousedy / 10.0f;
        if (pitch < -90.0f)
            pitch = -90.0f;
        if (pitch > 90.0f)
            pitch = 90.0f;

        cameraNode.rotation = Quaternion(pitch, yaw, 0);
    }
}

void HandleMouseButtonDown(StringHash eventType, VariantMap& eventData)
{
    int button = eventData["Button"].GetInt();
    if (button == MOUSEB_RIGHT)
        ui.cursor.visible = false;

    // Test creating a new physics object
    if (button == MOUSEB_LEFT && ui.GetElementAt(ui.cursorPosition, true) is null && ui.focusElement is null)
    {
        VariantMap eventData;
        eventData["Pos"] = cameraNode.position;
        eventData["Rot"] = cameraNode.rotation;

        // If we are the client, send the spawn command as a remote event, else send locally
        if (runClient)
        {
            if (network.serverConnection !is null)
                network.serverConnection.SendRemoteEvent("SpawnBox", true, eventData);
        }
        else
            SendEvent("SpawnBox", eventData);
    }
}

void HandleSpawnBox(StringHash eventType, VariantMap& eventData)
{
    Vector3 position = eventData["Pos"].GetVector3();
    Quaternion rotation = eventData["Rot"].GetQuaternion();

    Node@ newNode = testScene.CreateChild();
    newNode.position = position;
    newNode.rotation = rotation;
    newNode.SetScale(0.1);

    CollisionShape@ shape = newNode.CreateComponent("CollisionShape");
    shape.SetBox(Vector3(2, 2, 2), Vector3(), Quaternion());
    shape.friction = 1.0;
    shape.collisionGroup = 1;
    shape.collisionMask = 3;

    RigidBody@ body = newNode.CreateComponent("RigidBody");
    body.angularMaxVelocity = 500.0;
    body.linearVelocity = rotation * Vector3(0.0, 1.0, 10.0);
    body.mass = 1;

    StaticModel@ object = newNode.CreateComponent("StaticModel");
    object.model = cache.GetResource("Model", "Models/Box.mdl");
    object.material = cache.GetResource("Material", "Materials/Test.xml");
    object.castShadows = true;
    object.shadowDistance = 150.0;
    object.drawDistance = 200.0;
}

void HandleMouseButtonUp(StringHash eventType, VariantMap& eventData)
{
    if (eventData["Button"].GetInt() == MOUSEB_RIGHT)
        ui.cursor.visible = true;
}

void HandlePostRenderUpdate()
{
    if (engine.headless)
        return;

    // Draw rendering debug geometry without depth test to see the effect of occlusion
    if (drawDebug == 1)
        renderer.DrawDebugGeometry(false);
    if (drawDebug == 2)
        testScene.physicsWorld.DrawDebugGeometry(true);

    IntVector2 pos = ui.cursorPosition;
    if (ui.GetElementAt(pos, true) is null && testScene.octree !is null)
    {
        Ray cameraRay = camera.GetScreenRay(float(pos.x) / graphics.width, float(pos.y) / graphics.height);
        Array<RayQueryResult> result = testScene.octree.Raycast(cameraRay, DRAWABLE_GEOMETRY, 250.0, RAY_TRIANGLE);
        if (result.length > 0)
        {
            Drawable@ object = result[0].drawable;
            Vector3 rayHitPos = cameraRay.origin + cameraRay.direction * result[0].distance;
            testScene.debugRenderer.AddBoundingBox(BoundingBox(rayHitPos + Vector3(-0.01, -0.01, -0.01), rayHitPos +
                Vector3(0.01, 0.01, 0.01)), Color(1.0, 1.0, 1.0), true);
        }
    }
}

void HandleClientConnected(StringHash eventType, VariantMap& eventData)
{
    Connection@ connection = eventData["Connection"].GetConnection();
    connection.scene = testScene; // Begin scene replication to the client
    connection.logStatistics = true;
}
