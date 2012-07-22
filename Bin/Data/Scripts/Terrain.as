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
    SubscribeToEvent("PhysicsCollision", "HandlePhysicsCollision");

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
    if (GetPlatform() == "Android")
        ui.cursor.visible = false;

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
    camera.farClip = 1000;
    cameraNode.position = Vector3(0, 20, 0);

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
    zone.ambientColor = Color(0.15, 0.15, 0.15);
    zone.fogColor = Color(0.5, 0.5, 0.7);
    zone.fogStart = 500.0;
    zone.fogEnd = 1000.0;
    zone.boundingBox = BoundingBox(-2000, 2000);

    {
        Node@ lightNode = testScene.CreateChild("GlobalLight");
        lightNode.direction = Vector3(0.5, -0.5, 0.5);

        Light@ light = lightNode.CreateComponent("Light");
        light.lightType = LIGHT_DIRECTIONAL;
        light.castShadows = true;
        light.shadowBias = BiasParameters(0.0001, 0.5);
        light.shadowCascade = CascadeParameters(10.0, 50.0, 200.0, 0.0, 0.8);
        light.specularIntensity = 0.5;
    }

    Terrain@ terrain;

    {
        Node@ terrainNode = testScene.CreateChild("Terrain");
        terrainNode.position = Vector3(0, 0, 0);
        terrain = terrainNode.CreateComponent("Terrain");
        terrain.patchSize = 64;
        terrain.spacing = Vector3(2, 0.5, 2);
        terrain.heightMap = cache.GetResource("Image", "Textures/HeightMap.png");
        terrain.material = cache.GetResource("Material", "Materials/Terrain.xml");
        terrain.occluder = true;

        RigidBody@ body = terrainNode.CreateComponent("RigidBody");
        CollisionShape@ shape = terrainNode.CreateComponent("CollisionShape");
        shape.SetTerrain();
        shape.margin = 0.01;
    }

    for (uint i = 0; i < 1000; ++i)
    {
        Node@ objectNode = testScene.CreateChild("Mushroom");
        Vector3 position(Random() * 2000 - 1000, 0, Random() * 2000 - 1000);
        position.y = terrain.GetHeight(position) - 0.1;

        objectNode.position = position;
        objectNode.rotation = Quaternion(Vector3(0, 1, 0), terrain.GetNormal(position));
        objectNode.SetScale(3);

        StaticModel@ object = objectNode.CreateComponent("StaticModel");
        object.model = cache.GetResource("Model", "Models/Mushroom.mdl");
        object.material = cache.GetResource("Material", "Materials/Mushroom.xml");
        object.castShadows = true;

        RigidBody@ body = objectNode.CreateComponent("RigidBody");
        CollisionShape@ shape = objectNode.CreateComponent("CollisionShape");
        shape.SetTriangleMesh(cache.GetResource("Model", "Models/Mushroom.mdl"), 0);
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
    int key = eventData["Key"].GetInt();

    if (key == KEY_ESC)
    {
        if (ui.focusElement is null)
            engine.Exit();
        else
            console.visible = false;
    }

    if (key == KEY_F1)
        console.Toggle();

    if (ui.focusElement is null)
    {
        if (key == '1')
            renderer.renderMode = RenderMode((renderer.renderMode + 1) % 3);

        if (key == '2')
        {
            int quality = renderer.textureQuality;
            ++quality;
            if (quality > 2)
                quality = 0;
            renderer.textureQuality = quality;
        }

        if (key == '3')
        {
            int quality = renderer.materialQuality;
            ++quality;
            if (quality > 2)
                quality = 0;
            renderer.materialQuality = quality;
        }

        if (key == '4')
            renderer.specularLighting = !renderer.specularLighting;

        if (key == '5')
            renderer.drawShadows = !renderer.drawShadows;

        if (key == '6')
        {
            int size = renderer.shadowMapSize;
            size *= 2;
            if (size > 2048)
                size = 512;
            renderer.shadowMapSize = size;
        }

        if (key == '7')
            renderer.shadowQuality = renderer.shadowQuality + 1;

        if (key == '8')
        {
            bool occlusion = renderer.maxOccluderTriangles > 0;
            occlusion = !occlusion;
            renderer.maxOccluderTriangles = occlusion ? 5000 : 0;
        }

        if (key == '9')
            renderer.dynamicInstancing = !renderer.dynamicInstancing;

        if (key == ' ')
        {
            drawDebug++;
            if (drawDebug > 2)
                drawDebug = 0;
        }

        if (key == 'O')
            camera.orthographic = !camera.orthographic;

        if (key == 'B')
            bloom.active = !bloom.active;

        if (key == 'F')
            edgeFilter.active = !edgeFilter.active;

        if (key == 'T')
            debugHud.Toggle(DEBUGHUD_SHOW_PROFILER);

        if (key == KEY_F5)
        {
            File@ xmlFile = File(fileSystem.programDir + "Data/Scenes/Terrain.xml", FILE_WRITE);
            testScene.SaveXML(xmlFile);
        }

        if (key == KEY_F7)
        {
            File@ xmlFile = File(fileSystem.programDir + "Data/Scenes/Terrain.xml", FILE_READ);
            if (xmlFile.open)
                testScene.LoadXML(xmlFile);
        }
    }
}

void HandleMouseMove(StringHash eventType, VariantMap& eventData)
{
    if (eventData["Buttons"].GetInt() & MOUSEB_RIGHT != 0)
    {
        int mousedx = eventData["DX"].GetInt();
        int mousedy = eventData["DY"].GetInt();
        yaw += mousedx / 10.0;
        pitch += mousedy / 10.0;
        if (pitch < -90.0)
            pitch = -90.0;
        if (pitch > 90.0)
            pitch = 90.0;

        cameraNode.rotation = Quaternion(pitch, yaw, 0);
    }
}

void HandleMouseButtonDown(StringHash eventType, VariantMap& eventData)
{
    int button = eventData["Button"].GetInt();
    if (button == MOUSEB_RIGHT)
        ui.cursor.visible = false;

    // Test either creating a new physics object or painting a decal (SHIFT down)
    if (button == MOUSEB_LEFT && ui.GetElementAt(ui.cursorPosition, true) is null && ui.focusElement is null)
    {
        if (!input.qualifierDown[QUAL_SHIFT])
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
        else
        {
            IntVector2 pos = ui.cursorPosition;
            if (ui.GetElementAt(pos, true) is null && testScene.octree !is null)
            {
                Ray cameraRay = camera.GetScreenRay(float(pos.x) / graphics.width, float(pos.y) / graphics.height);
                RayQueryResult result = testScene.octree.RaycastSingle(cameraRay, RAY_TRIANGLE, 250.0, DRAWABLE_GEOMETRY);
                if (result.drawable !is null)
                {
                    Vector3 rayHitPos = cameraRay.origin + cameraRay.direction * result.distance;
                    DecalSet@ decal = result.drawable.node.GetComponent("DecalSet");
                    if (decal is null)
                    {
                        decal = result.drawable.node.CreateComponent("DecalSet");
                        decal.material = cache.GetResource("Material", "Materials/UrhoDecal.xml");
                        // Increase max. vertices/indices if the target is skinned
                        if (result.drawable.typeName == "AnimatedModel")
                        {
                            decal.maxVertices = 2048;
                            decal.maxIndices = 4096;
                        }
                    }
                    decal.AddDecal(result.drawable, rayHitPos, cameraNode.worldRotation, 0.5, 1.0, 1.0, Vector2(0, 0),
                        Vector2(1, 1));
                }
            }
        }
    }
}

void HandleSpawnBox(StringHash eventType, VariantMap& eventData)
{
    Vector3 position = eventData["Pos"].GetVector3();
    Quaternion rotation = eventData["Rot"].GetQuaternion();

    Node@ newNode = testScene.CreateChild();
    newNode.position = position;
    newNode.rotation = rotation;
    newNode.SetScale(0.2);

    RigidBody@ body = newNode.CreateComponent("RigidBody");
    body.mass = 1.0;
    body.friction = 1.0;
    body.linearVelocity = rotation * Vector3(0.0, 1.0, 10.0);
    body.ccdRadius = 0.15;
    body.ccdMotionThreshold = 0.2;

    CollisionShape@ shape = newNode.CreateComponent("CollisionShape");
    shape.SetBox(Vector3(1, 1, 1));

    StaticModel@ object = newNode.CreateComponent("StaticModel");
    object.model = cache.GetResource("Model", "Models/Box.mdl");
    object.material = cache.GetResource("Material", "Materials/StoneSmall.xml");
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
        }
    }
}

void HandleClientConnected(StringHash eventType, VariantMap& eventData)
{
    Connection@ connection = eventData["Connection"].GetConnection();
    connection.scene = testScene; // Begin scene replication to the client
    connection.logStatistics = true;
}

void HandlePhysicsCollision(StringHash eventType, VariantMap& eventData)
{
    // Check if either of the nodes has an AnimatedModel component
    Node@ nodeA = eventData["NodeA"].GetNode();
    Node@ nodeB = eventData["NodeB"].GetNode();
    if (nodeA.HasComponent("AnimatedModel"))
    {
        // Remove the trigger physics shape, and create the ragdoll
        nodeA.RemoveComponent("RigidBody");
        nodeA.RemoveComponent("CollisionShape");
        CreateRagdoll(nodeA.GetComponent("AnimatedModel"));
    }
    else if (nodeB.HasComponent("AnimatedModel"))
    {
        nodeB.RemoveComponent("RigidBody");
        nodeB.RemoveComponent("CollisionShape");
        CreateRagdoll(nodeB.GetComponent("AnimatedModel"));
    }
}

void CreateRagdoll(AnimatedModel@ model)
{
    Node@ root = model.node;

    CreateRagdollBone(root, "Bip01_Pelvis", SHAPE_CAPSULE, Vector3(0.3, 0.3, 0.3), Vector3(0.0, 0, 0), Quaternion(0, 0, 0));
    CreateRagdollBone(root, "Bip01_Spine1", SHAPE_CAPSULE, Vector3(0.3, 0.4, 0.3), Vector3(0.15, 0, 0), Quaternion(0, 0, 90));
    CreateRagdollBone(root, "Bip01_L_Thigh", SHAPE_CAPSULE, Vector3(0.175, 0.45, 0.175), Vector3(0.25, 0, 0), Quaternion(0, 0, 90));
    CreateRagdollBone(root, "Bip01_R_Thigh", SHAPE_CAPSULE, Vector3(0.175, 0.45, 0.175), Vector3(0.25, 0, 0), Quaternion(0, 0, 90));
    CreateRagdollBone(root, "Bip01_L_Calf", SHAPE_CAPSULE, Vector3(0.15, 0.55, 0.15), Vector3(0.25, 0, 0), Quaternion(0, 0, 90));
    CreateRagdollBone(root, "Bip01_R_Calf", SHAPE_CAPSULE, Vector3(0.15, 0.55, 0.15), Vector3(0.25, 0, 0), Quaternion(0, 0, 90));
    CreateRagdollBone(root, "Bip01_Head", SHAPE_SPHERE, Vector3(0.25, 0.25, 0.25), Vector3(0.1, 0, 0), Quaternion(0, 0, 0));
    CreateRagdollBone(root, "Bip01_L_UpperArm", SHAPE_CAPSULE, Vector3(0.125, 0.35, 0.125), Vector3(0.1, 0, 0), Quaternion(0, 0, 90));
    CreateRagdollBone(root, "Bip01_R_UpperArm", SHAPE_CAPSULE, Vector3(0.125, 0.35, 0.125), Vector3(0.1, 0, 0), Quaternion(0, 0, 90));
    CreateRagdollBone(root, "Bip01_L_Forearm", SHAPE_CAPSULE, Vector3(0.1, 0.3, 0.1), Vector3(0.15, 0, 0), Quaternion(0, 0, 90));
    CreateRagdollBone(root, "Bip01_R_Forearm", SHAPE_CAPSULE, Vector3(0.1, 0.3, 0.1), Vector3(0.15, 0, 0), Quaternion(0, 0, 90));

    CreateRagdollConstraint(root, "Bip01_L_Thigh", "Bip01_Pelvis", CONSTRAINT_CONETWIST, Vector3(0, 0, -1), Vector3(0, 0, 1), Vector2(45, 25), Vector2(0, 0));
    CreateRagdollConstraint(root, "Bip01_R_Thigh", "Bip01_Pelvis", CONSTRAINT_CONETWIST, Vector3(0, 0, -1), Vector3(0, 0, 1), Vector2(45, 25), Vector2(0, 0));
    CreateRagdollConstraint(root, "Bip01_L_Calf", "Bip01_L_Thigh", CONSTRAINT_HINGE, Vector3(0, 0, -1), Vector3(0, 0, -1), Vector2(90, 0), Vector2(0, 0));
    CreateRagdollConstraint(root, "Bip01_R_Calf", "Bip01_R_Thigh", CONSTRAINT_HINGE, Vector3(0, 0, -1), Vector3(0, 0, -1), Vector2(90, 0), Vector2(0, 0));
    CreateRagdollConstraint(root, "Bip01_Spine1", "Bip01_Pelvis", CONSTRAINT_HINGE, Vector3(0, 0, 1), Vector3(0, 0, 1), Vector2(90, 0), Vector2(-25, 0));
    CreateRagdollConstraint(root, "Bip01_Head", "Bip01_Spine1", CONSTRAINT_CONETWIST, Vector3(0, 0, 1), Vector3(0, 0, 1), Vector2(45, 25), Vector2(0, 0));
    CreateRagdollConstraint(root, "Bip01_L_UpperArm", "Bip01_Spine1", CONSTRAINT_CONETWIST, Vector3(0, -1, 0), Vector3(0, 1, 0), Vector2(45, 45), Vector2(0, 0));
    CreateRagdollConstraint(root, "Bip01_R_UpperArm", "Bip01_Spine1", CONSTRAINT_CONETWIST, Vector3(0, -1, 0), Vector3(0, 1, 0), Vector2(45, 45), Vector2(0, 0));
    CreateRagdollConstraint(root, "Bip01_L_Forearm", "Bip01_L_UpperArm", CONSTRAINT_HINGE, Vector3(0, 0, -1), Vector3(0, 0, -1), Vector2(90, 0), Vector2(0, 0));
    CreateRagdollConstraint(root, "Bip01_R_Forearm", "Bip01_R_UpperArm", CONSTRAINT_HINGE, Vector3(0, 0, -1), Vector3(0, 0, -1), Vector2(90, 0), Vector2(0, 0));

    // Disable animation from all bones (both physical and non-physical) to not interfere
    Skeleton@ skel = model.skeleton;
    for (uint i = 0; i < skel.numBones; ++i)
        skel.bones[i].animated = false;
}

void CreateRagdollBone(Node@ root, const String&in boneName, ShapeType type, const Vector3&in size, const Vector3&in position,
    const Quaternion&in rotation)
{
    Node@ boneNode = root.GetChild(boneName, true);
    if (boneNode is null || boneNode.HasComponent("RigidBody"))
        return;

    // In networked operation both client and server detect collisions separately, and create ragdolls on their own
    // (bones are not synced over network.) To prevent replicated component ID range clashes when the client creates
    // any components, it is important that the LOCAL creation mode is specified.
    RigidBody@ body = boneNode.CreateComponent("RigidBody", LOCAL);
    body.mass = 1.0;
    body.linearDamping = 0.05;
    body.angularDamping = 0.85;
    body.linearRestThreshold = 1.5;
    body.angularRestThreshold = 2.5;

    CollisionShape@ shape = boneNode.CreateComponent("CollisionShape", LOCAL);
    shape.shapeType = type;
    shape.size = size;
    shape.position = position;
    shape.rotation = rotation;
}

void CreateRagdollConstraint(Node@ root, const String&in boneName, const String&in parentName, ConstraintType type,
    const Vector3&in axis, const Vector3&in parentAxis, const Vector2&in highLimit, const Vector2&in lowLimit)
{
    Node@ boneNode = root.GetChild(boneName, true);
    Node@ parentNode = root.GetChild(parentName, true);
    if (boneNode is null || parentNode is null || boneNode.HasComponent("Constraint"))
        return;

    Constraint@ constraint = boneNode.CreateComponent("Constraint", LOCAL);
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
