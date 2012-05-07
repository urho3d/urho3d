#include "Scripts/Utilities/Network.as"

Scene@ testScene;
Camera@ camera;
Node@ cameraNode;
PostProcess@ edgeFilter;
PostProcess@ bloom;

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

    ParseNetworkArguments();

    InitScene();

    SubscribeToEvent("Update", "HandleUpdate");
    SubscribeToEvent("KeyDown", "HandleKeyDown");
    SubscribeToEvent("MouseMove", "HandleMouseMove");
    SubscribeToEvent("MouseButtonDown", "HandleMouseButtonDown");
    SubscribeToEvent("MouseButtonUp", "HandleMouseButtonUp");
    SubscribeToEvent("PostRenderUpdate", "HandlePostRenderUpdate");
    SubscribeToEvent("SpawnBox", "HandleSpawnBox");

    network.RegisterRemoteEvent("SpawnBox");

    if (runServer)
    {
        network.StartServer(serverPort);
        SubscribeToEvent("ClientConnected", "HandleClientConnected");

        // Disable physics interpolation to ensure clients get sent physically correct transforms
        testScene.physicsWorld.interpolation = false;

        // Test package download by adding all package files in the cache as requirements for the scene
        Array<PackageFile@> packages = cache.packageFiles;
        for (uint i = 0; i < packages.length; ++i)
            testScene.AddRequiredPackageFile(packages[i]);
    }
    if (runClient)
    {
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

    // Enable access to this script file & scene from the console
    script.defaultScene = testScene;
    script.defaultScriptFile = scriptFile;

    // Create the camera outside the scene so it is unaffected by scene load/save
    cameraNode = Node();
    camera = cameraNode.CreateComponent("Camera");
    cameraNode.position = Vector3(0, 2, 0);

    if (!engine.headless)
    {
        edgeFilter = PostProcess();
        edgeFilter.parameters = cache.GetResource("XMLFile", "PostProcess/EdgeFilter.xml");
        edgeFilter.active = false; // Start out disabled

        bloom = PostProcess();
        bloom.parameters = cache.GetResource("XMLFile", "PostProcess/Bloom.xml");
        bloom.active = false;

        renderer.viewports[0] = Viewport(testScene, camera);
        renderer.viewports[0].AddPostProcess(edgeFilter);
        renderer.viewports[0].AddPostProcess(bloom);
    }
    
    if (runClient)
        return;

    PhysicsWorld@ world = testScene.CreateComponent("PhysicsWorld");
    testScene.CreateComponent("Octree");
    testScene.CreateComponent("DebugRenderer");

    Node@ zoneNode = testScene.CreateChild("Zone");
    Zone@ zone = zoneNode.CreateComponent("Zone");
    zone.ambientColor = Color(0.1, 0.1, 0.1);
    zone.fogColor = Color(0.5, 0.5, 0.7);
    zone.fogStart = 100.0;
    zone.fogEnd = 300.0;
    zone.boundingBox = BoundingBox(-1000.0, 1000.0);

    {
        Node@ lightNode = testScene.CreateChild("GlobalLight");
        lightNode.direction = Vector3(0.5, -0.5, 0.5);

        Light@ light = lightNode.CreateComponent("Light");
        light.lightType = LIGHT_DIRECTIONAL;
        light.castShadows = true;
        light.shadowBias = BiasParameters(0.0001, 0.5);
        light.shadowCascade = CascadeParameters(10.0, 50.0, 200.0, 0.0, 0.8);
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

        RigidBody@ body = objectNode.CreateComponent("RigidBody");
        CollisionShape@ shape = objectNode.CreateComponent("CollisionShape");
        shape.SetBox(Vector3(2.0, 2.0, 2.0));
    }

    for (uint i = 0; i < 50; ++i)
    {
        Node@ objectNode = testScene.CreateChild("Box");
        objectNode.position = Vector3(Random(180.0) - 90.0, 1.0, Random(180.0) - 90.0);

        StaticModel@ object = objectNode.CreateComponent("StaticModel");
        object.model = cache.GetResource("Model", "Models/Box.mdl");
        object.material = cache.GetResource("Material", "Materials/Test.xml");
        object.castShadows = true;

        RigidBody@ body = objectNode.CreateComponent("RigidBody");
        CollisionShape@ shape = objectNode.CreateComponent("CollisionShape");
        shape.SetBox(Vector3(2.0, 2.0, 2.0));
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

        RigidBody@ body = objectNode.CreateComponent("RigidBody");
        CollisionShape@ shape = objectNode.CreateComponent("CollisionShape");
        shape.SetBox(Vector3(2.0, 2.0, 2.0));
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

        RigidBody@ body = objectNode.CreateComponent("RigidBody");
        CollisionShape@ shape = objectNode.CreateComponent("CollisionShape");
        shape.SetTriangleMesh(cache.GetResource("Model", "Models/Mushroom.mdl"), 0);
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
            renderer.renderMode = RenderMode((renderer.renderMode + 1) % 3);
        
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
            renderer.shadowQuality = renderer.shadowQuality + 1;

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

        if (input.keyPress['B'])
            bloom.active = !bloom.active;

        if (input.keyPress['F'])
            edgeFilter.active = !edgeFilter.active;

        if (input.keyPress['T'])
            debugHud.Toggle(DEBUGHUD_SHOW_PROFILER);

        if (input.keyPress[KEY_F5])
        {
            File@ xmlFile = File(fileSystem.programDir + "Data/Scenes/Scene.xml", FILE_WRITE);
            testScene.SaveXML(xmlFile);
        }

        if (input.keyPress[KEY_F7])
        {
            File@ xmlFile = File(fileSystem.programDir + "Data/Scenes/Scene.xml", FILE_READ);
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

    RigidBody@ body = newNode.CreateComponent("RigidBody");
    body.mass = 1.0;
    body.friction = 1.0;
    body.linearVelocity = rotation * Vector3(0.0, 1.0, 10.0);

    CollisionShape@ shape = newNode.CreateComponent("CollisionShape");
    shape.SetBox(Vector3(2.0, 2.0, 2.0));

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
        RayQueryResult result = testScene.octree.RaycastSingle(cameraRay, RAY_TRIANGLE, 250.0, DRAWABLE_GEOMETRY);
        if (result.drawable !is null)
        {
            Vector3 rayHitPos = cameraRay.origin + cameraRay.direction * result.distance;
            testScene.debugRenderer.AddBoundingBox(BoundingBox(rayHitPos + Vector3(-0.01, -0.01, -0.01), rayHitPos +
                Vector3(0.01, 0.01, 0.01)), Color(1.0, 1.0, 1.0), true);
                
            // Test creating a ragdoll
            if (input.keyPress['R'] && result.drawable.typeName == "AnimatedModel")
                CreateRagdoll(result.drawable);
        }
    }
}

void HandleClientConnected(StringHash eventType, VariantMap& eventData)
{
    Connection@ connection = eventData["Connection"].GetConnection();
    connection.scene = testScene; // Begin scene replication to the client
    connection.logStatistics = true;
}

void CreateRagdoll(AnimatedModel@ model)
{
    Node@ root = model.node;
    
    CreateRagdollBone(root, "Bip01_Pelvis", 1.0, SHAPE_BOX, Vector3(0.15, 0.2, 0.3), Vector3(0.1, 0, 0), Quaternion(0, 0, 0));
    CreateRagdollBone(root, "Bip01_Spine1", 1.0, SHAPE_BOX, Vector3(0.3, 0.25, 0.3), Vector3(0.15, 0, 0), Quaternion(0, 0, 0));
    CreateRagdollBone(root, "Bip01_L_Thigh", 1.0, SHAPE_CAPSULE, Vector3(0.2, 0.5, 0.2), Vector3(0.2, 0, 0), Quaternion(0, 0, 90));
    CreateRagdollBone(root, "Bip01_R_Thigh", 1.0, SHAPE_CAPSULE, Vector3(0.2, 0.5, 0.2), Vector3(0.2, 0, 0), Quaternion(0, 0, 90));
    CreateRagdollBone(root, "Bip01_L_Calf", 1.0, SHAPE_CAPSULE, Vector3(0.2, 0.45, 0.2), Vector3(0.2, 0, 0), Quaternion(0, 0, 90));
    CreateRagdollBone(root, "Bip01_R_Calf", 1.0, SHAPE_CAPSULE, Vector3(0.2, 0.45, 0.2), Vector3(0.2, 0, 0), Quaternion(0, 0, 90));
    CreateRagdollBone(root, "Bip01_Head", 1.0, SHAPE_SPHERE, Vector3(0.3, 0.3, 0.3), Vector3(0.1, 0, 0), Quaternion(0, 0, 0));
    CreateRagdollBone(root, "Bip01_L_UpperArm", 1.0, SHAPE_CAPSULE, Vector3(0.15, 0.3, 0.15), Vector3(0.1, 0, 0), Quaternion(0, 0, 90));
    CreateRagdollBone(root, "Bip01_R_UpperArm", 1.0, SHAPE_CAPSULE, Vector3(0.15, 0.3, 0.15), Vector3(0.1, 0, 0), Quaternion(0, 0, 90));
    CreateRagdollBone(root, "Bip01_L_Forearm", 1.0, SHAPE_CAPSULE, Vector3(0.1, 0.3, 0.1), Vector3(0.2, 0, 0), Quaternion(0, 0, 90));
    CreateRagdollBone(root, "Bip01_R_Forearm", 1.0, SHAPE_CAPSULE, Vector3(0.1, 0.3, 0.1), Vector3(0.2, 0, 0), Quaternion(0, 0, 90));

    CreateRagdollConstraint(root, "Bip01_L_Thigh", "Bip01_Pelvis", CONSTRAINT_CONETWIST, Vector3(0, 0, -1), Vector3(0, 0, 1), Vector2(45, 10), Vector2(0, 0));
    CreateRagdollConstraint(root, "Bip01_R_Thigh", "Bip01_Pelvis", CONSTRAINT_CONETWIST, Vector3(0, 0, -1), Vector3(0, 0, 1), Vector2(45, 10), Vector2(0, 0));
    CreateRagdollConstraint(root, "Bip01_L_Calf", "Bip01_L_Thigh", CONSTRAINT_HINGE, Vector3(0, 0, -1), Vector3(0, 0, -1), Vector2(90, 0), Vector2(0, 0));
    CreateRagdollConstraint(root, "Bip01_R_Calf", "Bip01_R_Thigh", CONSTRAINT_HINGE, Vector3(0, 0, -1), Vector3(0, 0, -1), Vector2(90, 0), Vector2(0, 0));
    CreateRagdollConstraint(root, "Bip01_Spine1", "Bip01_Pelvis", CONSTRAINT_CONETWIST, Vector3(0, 0, 1), Vector3(0, 0, 1), Vector2(25, 10), Vector2(0, 0));
    CreateRagdollConstraint(root, "Bip01_Head", "Bip01_Spine1", CONSTRAINT_CONETWIST, Vector3(0, 0, 1), Vector3(0, 0, 1), Vector2(45, 15), Vector2(0, 0));
    CreateRagdollConstraint(root, "Bip01_L_UpperArm", "Bip01_Spine1", CONSTRAINT_CONETWIST, Vector3(0, -1, 0), Vector3(0, 1, 0), Vector2(25, 45), Vector2(0, 0));
    CreateRagdollConstraint(root, "Bip01_R_UpperArm", "Bip01_Spine1", CONSTRAINT_CONETWIST, Vector3(0, -1, 0), Vector3(0, 1, 0), Vector2(25, 45), Vector2(0, 0));
    CreateRagdollConstraint(root, "Bip01_L_Forearm", "Bip01_L_UpperArm", CONSTRAINT_HINGE, Vector3(0, 0, -1), Vector3(0, 0, -1), Vector2(45, 0), Vector2(0, 0));
    CreateRagdollConstraint(root, "Bip01_R_Forearm", "Bip01_R_UpperArm", CONSTRAINT_HINGE, Vector3(0, 0, -1), Vector3(0, 0, -1), Vector2(45, 0), Vector2(0, 0));

    // Disable animation from all bones (both physical and non-physical) to not interfere
    Skeleton@ skel = model.skeleton;
    for (uint i = 0; i < skel.numBones; ++i)
        skel.bones[i].animated = false;
}

void CreateRagdollBone(Node@ root, String boneName, float mass, ShapeType type, Vector3 size, Vector3 position, Quaternion rotation)
{
    Node@ boneNode = root.GetChild(boneName, true);
    if (boneNode is null || boneNode.HasComponent("RigidBody"))
        return;
    
    RigidBody@ body = boneNode.CreateComponent("RigidBody", LOCAL);
    body.mass = mass;
    body.linearDamping = 0.5;
    body.angularDamping = 0.5;

    CollisionShape@ shape = boneNode.CreateComponent("CollisionShape", LOCAL);
    shape.shapeType = type;
    shape.size = size;
    shape.position = position;
    shape.rotation = rotation;
}

void CreateRagdollConstraint(Node@ root, String boneName, String parentName, ConstraintType type, Vector3 axis, Vector3 parentAxis, Vector2 highLimit, Vector2 lowLimit)
{
    Node@ boneNode = root.GetChild(boneName, true);
    Node@ parentNode = root.GetChild(parentName, true);
    if (boneNode is null || parentNode is null || boneNode.HasComponent("Constraint"))
        return;
        
    Constraint@ constraint = boneNode.CreateComponent("Constraint");
    constraint.constraintType = type;
    constraint.disableCollision = true;
    // The connected body must be specified before setting the world position
    constraint.otherBody = parentNode.GetComponent("RigidBody");
    constraint.worldPosition = boneNode.worldPosition;
    constraint.axis = axis;
    constraint.otherAxis = parentAxis;
    constraint.highLimit = highLimit;
    constraint.lowLimit = lowLimit;
}
