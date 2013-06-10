#include "Scripts/Utilities/Network.as"

Scene@ testScene;
Camera@ camera;
Node@ cameraNode;

float yaw = 0.0;
float pitch = 0.0;
int drawDebug = 0;

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
    }
    if (runClient)
        network.Connect(serverAddress, serverPort, testScene);
}

void InitConsole()
{
    XMLFile@ uiStyle = cache.GetResource("XMLFile", "UI/DefaultStyle.xml");

    engine.CreateDebugHud();
    debugHud.defaultStyle = uiStyle;
    debugHud.mode = DEBUGHUD_SHOW_ALL;

    engine.CreateConsole();
    console.defaultStyle = uiStyle;
}

void InitUI()
{
    XMLFile@ uiStyle = cache.GetResource("XMLFile", "UI/DefaultStyle.xml");

    Cursor@ newCursor = Cursor("Cursor");
    newCursor.SetStyleAuto(uiStyle);
    newCursor.position = IntVector2(graphics.width / 2, graphics.height / 2);
    ui.cursor = newCursor;
    if (GetPlatform() == "Android" || GetPlatform() == "iOS")
        ui.cursor.visible = false;
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
        renderer.viewports[0] = Viewport(testScene, camera);

        // Add bloom & FXAA effects to the renderpath. Clone the default renderpath so that we don't affect it
        RenderPath@ newRenderPath = renderer.viewports[0].renderPath.Clone();
        newRenderPath.Append(cache.GetResource("XMLFile", "PostProcess/Bloom.xml"));
        newRenderPath.Append(cache.GetResource("XMLFile", "PostProcess/EdgeFilter.xml"));
        newRenderPath.SetEnabled("Bloom", false);
        newRenderPath.SetEnabled("EdgeFilter", false);
        renderer.viewports[0].renderPath = newRenderPath;

        audio.listener = cameraNode.CreateComponent("SoundListener");
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
    zone.fogStart = 100.0;
    zone.fogEnd = 300.0;
    zone.boundingBox = BoundingBox(-1000, 1000);

    {
        Node@ lightNode = testScene.CreateChild("GlobalLight");
        lightNode.direction = Vector3(0.3, -0.5, 0.425);

        Light@ light = lightNode.CreateComponent("Light");
        light.lightType = LIGHT_DIRECTIONAL;
        light.castShadows = true;
        light.shadowBias = BiasParameters(0.0001, 0.5);
        light.shadowCascade = CascadeParameters(10.0, 50.0, 200.0, 0.0, 0.8);
        light.specularIntensity = 0.5;
    }

    {
        Node@ objectNode = testScene.CreateChild("Floor");
        objectNode.position = Vector3(0, -0.5, 0);
        objectNode.scale = Vector3(200, 1, 200);

        StaticModel@ object = objectNode.CreateComponent("StaticModel");
        object.model = cache.GetResource("Model", "Models/Box.mdl");
        object.material = cache.GetResource("Material", "Materials/StoneTiled.xml");
        object.occluder = true;

        RigidBody@ body = objectNode.CreateComponent("RigidBody");
        CollisionShape@ shape = objectNode.CreateComponent("CollisionShape");
        shape.SetBox(Vector3(1, 1, 1));
    }

    for (uint i = 0; i < 50; ++i)
    {
        Node@ objectNode = testScene.CreateChild("Box");
        objectNode.position = Vector3(Random() * 180 - 90, 1, Random() * 180 - 90);
        objectNode.SetScale(2);

        StaticModel@ object = objectNode.CreateComponent("StaticModel");
        object.model = cache.GetResource("Model", "Models/Box.mdl");
        object.material = cache.GetResource("Material", "Materials/Stone.xml");
        object.castShadows = true;

        RigidBody@ body = objectNode.CreateComponent("RigidBody");
        CollisionShape@ shape = objectNode.CreateComponent("CollisionShape");
        shape.SetBox(Vector3(1, 1, 1));
    }

    for (uint i = 0; i < 10; ++i)
    {
        Node@ objectNode = testScene.CreateChild("Box");
        objectNode.position = Vector3(Random() * 180 - 90, 10, Random() * 180 - 90);
        objectNode.SetScale(20);

        StaticModel@ object = objectNode.CreateComponent("StaticModel");
        object.model = cache.GetResource("Model", "Models/Box.mdl");
        object.material = cache.GetResource("Material", "Materials/Stone.xml");
        object.castShadows = true;
        object.occluder = true;

        RigidBody@ body = objectNode.CreateComponent("RigidBody");
        CollisionShape@ shape = objectNode.CreateComponent("CollisionShape");
        shape.SetBox(Vector3(1, 1, 1));
    }

    for (uint i = 0; i < 50; ++i)
    {
        Node@ objectNode = testScene.CreateChild("Mushroom");
        objectNode.position = Vector3(Random() * 180 - 90, 0, Random() * 180 - 90);
        objectNode.rotation = Quaternion(0, Random(360.0), 0);
        objectNode.SetScale(5);

        StaticModel@ object = objectNode.CreateComponent("StaticModel");
        object.model = cache.GetResource("Model", "Models/Mushroom.mdl");
        object.material = cache.GetResource("Material", "Materials/Mushroom.xml");
        object.castShadows = true;

        RigidBody@ body = objectNode.CreateComponent("RigidBody");
        CollisionShape@ shape = objectNode.CreateComponent("CollisionShape");
        shape.SetTriangleMesh(object.model, 0);
    }

    for (uint i = 0; i < 50; ++i)
    {
        Node@ objectNode = testScene.CreateChild("Jack");
        objectNode.position = Vector3(Random() * 180 - 90, 0, Random() * 180 - 90);
        objectNode.rotation = Quaternion(0, Random() * 360, 0);

        AnimatedModel@ object = objectNode.CreateComponent("AnimatedModel");
        object.model = cache.GetResource("Model", "Models/Jack.mdl");
        object.material = cache.GetResource("Material", "Materials/Jack.xml");
        object.castShadows = true;

        // Create a capsule shape for detecting collisions
        RigidBody@ body = objectNode.CreateComponent("RigidBody");
        body.phantom = true;
        CollisionShape@ shape = objectNode.CreateComponent("CollisionShape");
        shape.SetCapsule(0.7, 1.8, Vector3(0.0, 0.9, 0.0));

        AnimationController@ ctrl = objectNode.CreateComponent("AnimationController");
        ctrl.Play("Models/Jack_Walk.ani", 0, true, 0.0);
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
        {
            int quality = renderer.textureQuality;
            ++quality;
            if (quality > 2)
                quality = 0;
            renderer.textureQuality = quality;
        }

        if (key == '2')
        {
            int quality = renderer.materialQuality;
            ++quality;
            if (quality > 2)
                quality = 0;
            renderer.materialQuality = quality;
        }

        if (key == '3')
            renderer.specularLighting = !renderer.specularLighting;

        if (key == '4')
            renderer.drawShadows = !renderer.drawShadows;

        if (key == '5')
        {
            int size = renderer.shadowMapSize;
            size *= 2;
            if (size > 2048)
                size = 512;
            renderer.shadowMapSize = size;
        }

        if (key == '6')
            renderer.shadowQuality = renderer.shadowQuality + 1;

        if (key == '7')
        {
            bool occlusion = renderer.maxOccluderTriangles > 0;
            occlusion = !occlusion;
            renderer.maxOccluderTriangles = occlusion ? 5000 : 0;
        }

        if (key == '8')
            renderer.dynamicInstancing = !renderer.dynamicInstancing;

        if (key == ' ')
        {
            drawDebug++;
            if (drawDebug > 2)
                drawDebug = 0;
        }

        if (key == 'B')
            renderer.viewports[0].renderPath.ToggleEnabled("Bloom");

        if (key == 'F')
            renderer.viewports[0].renderPath.ToggleEnabled("EdgeFilter");

        if (key == 'O')
            camera.orthographic = !camera.orthographic;

        if (key == 'T')
            debugHud.Toggle(DEBUGHUD_SHOW_PROFILER);

        if (key == KEY_F5)
        {
            File@ xmlFile = File(fileSystem.programDir + "Data/Scenes/TestScene.xml", FILE_WRITE);
            testScene.SaveXML(xmlFile);
        }

        if (key == KEY_F7)
        {
            File@ xmlFile = File(fileSystem.programDir + "Data/Scenes/TestScene.xml", FILE_READ);
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
        HandleHit(nodeA);
    else if (nodeB.HasComponent("AnimatedModel"))
        HandleHit(nodeB);
}

void HandleHit(Node@ node)
{
    // Remove the trigger physics shape, and create the ragdoll
    node.RemoveComponent("RigidBody");
    node.RemoveComponent("CollisionShape");
    CreateRagdoll(node.GetComponent("AnimatedModel"));
}

void CreateRagdoll(AnimatedModel@ model)
{
    Node@ root = model.node;

    CreateRagdollBone(root, "Bip01_Pelvis", SHAPE_BOX, Vector3(0.3, 0.2, 0.25), Vector3(0, 0, 0), Quaternion(0, 0, 0));
    CreateRagdollBone(root, "Bip01_Spine1", SHAPE_BOX, Vector3(0.35, 0.2, 0.3), Vector3(0.15, 0, 0), Quaternion(0, 0, 0));
    CreateRagdollBone(root, "Bip01_L_Thigh", SHAPE_CAPSULE, Vector3(0.175, 0.45, 0.175), Vector3(0.25, 0, 0), Quaternion(0, 0, 90));
    CreateRagdollBone(root, "Bip01_R_Thigh", SHAPE_CAPSULE, Vector3(0.175, 0.45, 0.175), Vector3(0.25, 0, 0), Quaternion(0, 0, 90));
    CreateRagdollBone(root, "Bip01_L_Calf", SHAPE_CAPSULE, Vector3(0.15, 0.55, 0.15), Vector3(0.25, 0, 0), Quaternion(0, 0, 90));
    CreateRagdollBone(root, "Bip01_R_Calf", SHAPE_CAPSULE, Vector3(0.15, 0.55, 0.15), Vector3(0.25, 0, 0), Quaternion(0, 0, 90));
    CreateRagdollBone(root, "Bip01_Head", SHAPE_BOX, Vector3(0.2, 0.2, 0.2), Vector3(0.1, 0, 0), Quaternion(0, 0, 0));
    CreateRagdollBone(root, "Bip01_L_UpperArm", SHAPE_CAPSULE, Vector3(0.15, 0.35, 0.15), Vector3(0.1, 0, 0), Quaternion(0, 0, 90));
    CreateRagdollBone(root, "Bip01_R_UpperArm", SHAPE_CAPSULE, Vector3(0.15, 0.35, 0.15), Vector3(0.1, 0, 0), Quaternion(0, 0, 90));
    CreateRagdollBone(root, "Bip01_L_Forearm", SHAPE_CAPSULE, Vector3(0.125, 0.4, 0.125), Vector3(0.2, 0, 0), Quaternion(0, 0, 90));
    CreateRagdollBone(root, "Bip01_R_Forearm", SHAPE_CAPSULE, Vector3(0.125, 0.4, 0.125), Vector3(0.2, 0, 0), Quaternion(0, 0, 90));
    
    CreateRagdollConstraint(root, "Bip01_L_Thigh", "Bip01_Pelvis", CONSTRAINT_CONETWIST, Vector3(0, 0, -1), Vector3(0, 0, 1), Vector2(45, 45), Vector2(0, 0));
    CreateRagdollConstraint(root, "Bip01_R_Thigh", "Bip01_Pelvis", CONSTRAINT_CONETWIST, Vector3(0, 0, -1), Vector3(0, 0, 1), Vector2(45, 45), Vector2(0, 0));
    CreateRagdollConstraint(root, "Bip01_L_Calf", "Bip01_L_Thigh", CONSTRAINT_HINGE, Vector3(0, 0, -1), Vector3(0, 0, -1), Vector2(90, 0), Vector2(0, 0));
    CreateRagdollConstraint(root, "Bip01_R_Calf", "Bip01_R_Thigh", CONSTRAINT_HINGE, Vector3(0, 0, -1), Vector3(0, 0, -1), Vector2(90, 0), Vector2(0, 0));
    CreateRagdollConstraint(root, "Bip01_Spine1", "Bip01_Pelvis", CONSTRAINT_HINGE, Vector3(0, 0, 1), Vector3(0, 0, 1), Vector2(45, 0), Vector2(-10, 0));
    CreateRagdollConstraint(root, "Bip01_Head", "Bip01_Spine1", CONSTRAINT_CONETWIST, Vector3(1, 0, 0), Vector3(1, 0, 0), Vector2(0, 30), Vector2(0, 0));
    CreateRagdollConstraint(root, "Bip01_L_UpperArm", "Bip01_Spine1", CONSTRAINT_CONETWIST, Vector3(0, -1, 0), Vector3(0, 1, 0), Vector2(45, 45), Vector2(0, 0), false);
    CreateRagdollConstraint(root, "Bip01_R_UpperArm", "Bip01_Spine1", CONSTRAINT_CONETWIST, Vector3(0, -1, 0), Vector3(0, 1, 0), Vector2(45, 45), Vector2(0, 0), false);
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
    const Vector3&in axis, const Vector3&in parentAxis, const Vector2&in highLimit, const Vector2&in lowLimit,
    bool disableCollision = true)
{
    Node@ boneNode = root.GetChild(boneName, true);
    Node@ parentNode = root.GetChild(parentName, true);
    if (boneNode is null || parentNode is null || boneNode.HasComponent("Constraint"))
        return;

    Constraint@ constraint = boneNode.CreateComponent("Constraint", LOCAL);
    constraint.constraintType = type;
    constraint.disableCollision = disableCollision;
    // The connected body must be specified before setting the world position
    constraint.otherBody = parentNode.GetComponent("RigidBody");
    constraint.worldPosition = boneNode.worldPosition;
    constraint.axis = axis;
    constraint.otherAxis = parentAxis;
    constraint.highLimit = highLimit;
    constraint.lowLimit = lowLimit;
}
