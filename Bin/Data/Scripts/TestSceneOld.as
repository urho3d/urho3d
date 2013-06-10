// GraphicsTest rewrite from Urho3D 1.0

const uint NUM_OBJECTS = 250;
const uint NUM_LIGHTS = 20;
const uint NUM_INSTANCENODES = 20;
const uint NUM_INSTANCES = 50;
const uint NUM_BILLBOARDNODES = 20;
const uint NUM_BILLBOARDS = 15;

Scene@ testScene;
Node@ cameraNode;
Camera@ camera;
Node@ cameraLightNode;
Light@ cameraLight;

float yaw = 0.0;
float pitch = 0.0;
float objectangle = 0.0;
bool paused = true;
int drawDebug = 0;

Array<Node@> animatingObjects;
Array<Node@> billboards;
Array<Node@> lights;

void Start()
{
    if (engine.headless)
    {
        ErrorDialog("GraphicsTest", "Headless mode is not supported. The program will now exit.");
        engine.Exit();
        return;
    }

    InitConsole();
    InitScene();
    InitUI();
    CreateCamera();

    SubscribeToEvent("Update", "HandleUpdate");
    SubscribeToEvent("KeyDown", "HandleKeyDown");
    SubscribeToEvent("MouseMove", "HandleMouseMove");
    SubscribeToEvent("MouseButtonDown", "HandleMouseButtonDown");
    SubscribeToEvent("MouseButtonUp", "HandleMouseButtonUp");
    SubscribeToEvent("PostRenderUpdate", "HandlePostRenderUpdate");
    SubscribeToEvent("PhysicsCollision", "HandlePhysicsCollision");
}

void InitScene()
{
    testScene = Scene("GraphicsTest");

    // Make the scene directly accessible from the console
    script.defaultScene = testScene;

    testScene.CreateComponent("Octree");
    testScene.CreateComponent("DebugRenderer");
    PhysicsWorld@ world = testScene.CreateComponent("PhysicsWorld");

    // Create the directional light
    Node@ sunNode = testScene.CreateChild();
    sunNode.direction = Vector3(0.5, -1, 0.5);
    Light@ sunLight = sunNode.CreateComponent("Light");
    sunLight.lightType = LIGHT_DIRECTIONAL;
    sunLight.color = Color(0.2, 0.2, 0.2);
    sunLight.specularIntensity = 1;

    // Create a zone to control the ambient lighting
    Node@ zoneNode = testScene.CreateChild();
    Zone@ zone = zoneNode.CreateComponent("Zone");
    zone.boundingBox = BoundingBox(-1000, 1000);
    zone.ambientColor = Color(0.1, 0.1, 0.1);

    // Create the "floor"
    for (int y = -5; y <= 5; y++)
    {
        for (int x = -5; x <= 5; x++)
        {
            Node@ newNode = testScene.CreateChild();
            newNode.position = Vector3(x * 20.5, -0.5, y * 20.5);
            newNode.scale = Vector3(20, 1, 20);

            RigidBody@ body = newNode.CreateComponent("RigidBody");
            CollisionShape@ shape = newNode.CreateComponent("CollisionShape");
            shape.SetBox(Vector3(1, 1, 1));

            StaticModel@ object = newNode.CreateComponent("StaticModel");
            object.model = cache.GetResource("Model", "Models/Box.mdl");
            object.material = cache.GetResource("Material", "Materials/Stone.xml");
            object.viewMask = 1;
        }
    }

    // Create 2 occluder walls
    for (int x = 0; x < 2; x++)
    {
        Node@ newNode = testScene.CreateChild();
        newNode.position = Vector3(0, 5, 0);
        newNode.rotation = Quaternion(x * 90, Vector3(0, 1, 0));
        newNode.scale = Vector3(224, 10, 1);

        RigidBody@ body = newNode.CreateComponent("RigidBody");
        CollisionShape@ shape = newNode.CreateComponent("CollisionShape");
        shape.SetBox(Vector3(1, 1, 1));

        StaticModel@ object = newNode.CreateComponent("StaticModel");
        object.model = cache.GetResource("Model", "Models/Box.mdl");
        object.material = cache.GetResource("Material", "Materials/StoneTiledH.xml");
        object.castShadows = true;
        object.occluder = true;
        object.viewMask = 1;
    }

    // Create static mushroom with physics
    {
        Node@ newNode = testScene.CreateChild();
        newNode.position = Vector3(50, 0, 50);
        newNode.SetScale(10);

        StaticModel@ object = newNode.CreateComponent("StaticModel");
        object.model = cache.GetResource("Model", "Models/Mushroom.mdl");
        object.material = cache.GetResource("Material", "Materials/Mushroom.xml");
        object.castShadows = true;
        object.occluder = true;
        object.viewMask = 1;

        RigidBody@ body = newNode.CreateComponent("RigidBody");
        CollisionShape@ shape = newNode.CreateComponent("CollisionShape");
        shape.SetTriangleMesh(object.model, 0);
    }

    // Create mushroom groups
    for (uint i = 0; i < NUM_INSTANCENODES; ++i)
    {
        Node@ newNode = testScene.CreateChild();
        newNode.position = Vector3(Random() * 160 - 80, 0, Random() * 160 - 80);

        for (uint j = 0; j < NUM_INSTANCES; ++j)
        {
            Vector3 position = Vector3(Random() * 20 - 10, 0, Random() * 20 - 10);
            float angle = Random() * 360;
            float size = 1 + Random() * 2;

            Node@ instance = newNode.CreateChild();
            instance.position = position;
            instance.rotation = Quaternion(angle, Vector3(0, 1, 0));
            instance.SetScale(size);

            StaticModel@ object = instance.CreateComponent("StaticModel");
            object.model = cache.GetResource("Model", "Models/Mushroom.mdl");
            object.material = cache.GetResource("Material", "Materials/Mushroom.xml");
            object.castShadows = true;
            object.viewMask = 1;
        }
    }

    // Create animated models
    for (uint i = 0; i < NUM_OBJECTS; ++i)
    {
        Node@ newNode = testScene.CreateChild("Jack");
        newNode.position = Vector3(Random() * 180 - 90, 0, Random() * 180 - 90);
        newNode.rotation = Quaternion(Random() * 360, Vector3(0, 1, 0));
        newNode.SetScale(1 + Random() * 0.25);

        AnimatedModel@ object = newNode.CreateComponent("AnimatedModel");
        object.model = cache.GetResource("Model", "Models/Jack.mdl");
        object.material = cache.GetResource("Material", "Materials/Jack.xml");
        object.drawDistance = 300;
        object.castShadows = true;
        object.maxLights = 2;
        object.viewMask = 1;

        // Because there are many animated models in the scene, test reducing animation LOD for less CPU use
        object.animationLodBias = 0.75;

        // Create a capsule shape for detecting collisions
        RigidBody@ body = newNode.CreateComponent("RigidBody");
        body.phantom = true;
        CollisionShape@ shape = newNode.CreateComponent("CollisionShape");
        shape.SetCapsule(0.7, 1.8, Vector3(0.0, 0.9, 0.0));

        AnimationState@ anim = object.AddAnimationState(cache.GetResource("Animation", "Models/Jack_Walk.ani"));
        anim.looped = true;
        anim.weight = 1.0;

        animatingObjects.Push(newNode);
    }

    // Create floating smoke clouds
    for (uint i = 0; i < NUM_BILLBOARDNODES; ++i)
    {
        Node@ newNode = testScene.CreateChild("Smoke");
        newNode.position = Vector3(Random() * 200 - 100, Random() * 15 + 5, Random() * 200 - 100);

        BillboardSet@ billboard = newNode.CreateComponent("BillboardSet");
        billboard.numBillboards = NUM_BILLBOARDS;
        billboard.material = cache.GetResource("Material", "Materials/LitSmoke.xml");
        billboard.sorted = true;
        billboard.viewMask = 2;

        for (uint j = 0; j < NUM_BILLBOARDS; ++j)
        {
            Billboard@ bb = billboard.billboards[j];
            bb.position = Vector3(Random() * 15 - 7.5, Random() * 8 - 4, Random() * 15 - 7.5);
            bb.size = Vector2(Random() * 2 + 3, Random() * 2 + 3);
            bb.rotation = Random() * 360;
            bb.enabled = true;
        }
        billboard.Commit();

        billboards.Push(newNode);
    }

    // Create lights
    for (uint i = 0; i < NUM_LIGHTS; ++i)
    {
        Node@ newNode = testScene.CreateChild("Light");
        Light@ light = newNode.CreateComponent("Light");

        Vector3 position(
            Random() * 150 - 75,
            Random() * 30 + 30,
            Random() * 150 - 75
        );

        Color color((RandomInt() & 1) * 0.5 + 0.5, (RandomInt() & 1) * 0.5 + 0.5, (RandomInt() & 1) * 0.5 + 0.5);
        if (color.r == 0.5 && color.g == 0.5 && color.b == 0.5)
            color = Color(1, 1, 1);

        float angle = Random() * 360;

        newNode.position = position;
        newNode.direction = Vector3(Sin(angle), -1, Cos(angle));
        light.lightType = LIGHT_SPOT;
        light.range = 75;
        light.rampTexture = cache.GetResource("Texture2D", "Textures/RampExtreme.png");
        light.fov = 15;
        light.color = color;
        light.specularIntensity = 1;
        light.castShadows = true;
        light.shadowBias = BiasParameters(0.00002, 0.0);
        light.shadowDistance = 200;
        light.shadowFadeDistance = 150;
        light.shadowResolution = 0.5;

        // The spot lights will not have anything near them, so move the near plane of the shadow camera farther
        // for better shadow depth resolution
        light.shadowNearFarRatio = 0.01;

        // Store the original rotation as a node property
        newNode.vars["rotation"] = newNode.rotation;

        lights.Push(newNode);
    }
}

void AnimateScene(float timeStep)
{
    objectangle += 10 * timeStep;

    for (uint i = 0; i < lights.length; ++i)
        lights[i].rotation = Quaternion(0, objectangle * 2, 0) * lights[i].vars["rotation"].GetQuaternion();

    for (uint i = 0; i < animatingObjects.length; ++i)
    {
        AnimatedModel@ model = animatingObjects[i].GetComponent("AnimatedModel");
        model.animationStates["Walk"].AddTime(timeStep);
    }

    for (uint i = 0; i < billboards.length; ++i)
    {
        BillboardSet@ billboard = billboards[i].GetComponent("BillboardSet");
        for (uint j = 0; j < billboard.numBillboards; ++j)
            billboard.billboards[j].rotation += 50 * timeStep;
        billboard.Commit();
    }
}

void InitConsole()
{
    XMLFile@ uiStyle = cache.GetResource("XMLFile", "UI/DefaultStyle.xml");

    Console@ console = engine.CreateConsole();
    console.defaultStyle = uiStyle;
    console.numRows = 16;

    DebugHud@ hud = engine.CreateDebugHud();
    debugHud.defaultStyle = uiStyle;
    debugHud.mode = DEBUGHUD_SHOW_ALL;
}

void InitUI()
{
    XMLFile@ uiStyle = cache.GetResource("XMLFile", "UI/DefaultStyle.xml");

    Cursor@ cursor = Cursor("Cursor");
    cursor.SetStyleAuto(uiStyle);
    cursor.position = IntVector2(graphics.width / 2, graphics.height / 2);
    ui.cursor = cursor;
    if (GetPlatform() == "Android" || GetPlatform() == "iOS")
        ui.cursor.visible = false;
}

void CreateCamera()
{
    cameraNode = testScene.CreateChild("Camera");
    camera = cameraNode.CreateComponent("Camera");
    cameraNode.position = Vector3(-50, 2, -50);

    cameraLightNode = cameraNode.CreateChild("CameraLight");
    cameraLight = cameraLightNode.CreateComponent("Light");
    cameraLight.lightType = LIGHT_SPOT;
    cameraLight.range = 50;
    cameraLight.color = Color(2, 2, 2);
    cameraLight.specularIntensity = 2;
    cameraLight.castShadows = true;
    cameraLight.shadowDistance = 200;
    cameraLight.shadowFadeDistance = 150;
    cameraLight.shadowResolution = 0.5;
    cameraLight.rampTexture = cache.GetResource("Texture2D", "Textures/RampWide.png");
    cameraLight.shapeTexture = cache.GetResource("Texture2D", "Textures/SpotWide.png");

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
}

void HandleUpdate(StringHash eventType, VariantMap& eventData)
{
    float timeStep = eventData["TimeStep"].GetFloat();

    if (!paused)
        AnimateScene(timeStep);

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

        if (key == 'P')
            paused = !paused;

        if (key == 'L')
        {
            if (cameraLightNode.parent is testScene)
            {
                cameraLightNode.parent = cameraNode;
                cameraLightNode.position = Vector3(0, 0, 0);
                cameraLightNode.rotation = Quaternion();
            }
            else
                cameraLightNode.parent = testScene;
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
            File@ xmlFile = File("Data/Scenes/TestSceneOld.xml", FILE_WRITE);
            testScene.SaveXML(xmlFile);
        }

        if (key == KEY_F7)
        {
            File@ xmlFile = File("Data/Scenes/TestSceneOld.xml", FILE_READ);
            if (xmlFile.open)
            {
                testScene.LoadXML(xmlFile);
                // Reacquire camera, as it is part of the scene
                cameraNode = testScene.GetChild("Camera", true);
                camera = cameraNode.GetComponent("Camera");
                cameraLightNode = cameraNode.GetChild("CameraLight");
                renderer.viewports[0] = Viewport(testScene, camera);
                audio.listener = cameraNode.GetComponent("SoundListener");
                // Reacquire animating objects
                animatingObjects.Clear();
                billboards.Clear();
                lights.Clear();
                for (uint i = 0; i < testScene.numChildren; ++i)
                {
                    Node@ node = testScene.children[i];
                    if (node.name == "Jack")
                        animatingObjects.Push(node);
                    else if (node.name == "Smoke")
                        billboards.Push(node);
                    else if (node.name == "Light")
                        lights.Push(node);
                }
            }
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
            Node@ newNode = testScene.CreateChild();
            newNode.position = cameraNode.position;
            newNode.rotation = cameraNode.rotation;
            newNode.SetScale(0.2);

            RigidBody@ body = newNode.CreateComponent("RigidBody");
            body.mass = 1.0;
            body.friction = 1.0;
            body.linearVelocity = cameraNode.rotation * Vector3(0.0, 1.0, 10.0);

            CollisionShape@ shape = newNode.CreateComponent("CollisionShape");
            shape.SetBox(Vector3(1, 1, 1));

            StaticModel@ object = newNode.CreateComponent("StaticModel");
            object.model = cache.GetResource("Model", "Models/Box.mdl");
            object.material = cache.GetResource("Material", "Materials/StoneSmall.xml");
            object.castShadows = true;
            object.shadowDistance = 150.0;
            object.drawDistance = 200.0;
        }
        else
        {
            IntVector2 pos = ui.cursorPosition;
            if (ui.GetElementAt(pos, true) is null && testScene.octree !is null)
            {
                Ray cameraRay = camera.GetScreenRay(float(pos.x) / graphics.width, float(pos.y) / graphics.height);
                RayQueryResult result = testScene.octree.RaycastSingle(cameraRay, RAY_TRIANGLE, 250.0, DRAWABLE_GEOMETRY, 1);
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
        RayQueryResult result = testScene.octree.RaycastSingle(cameraRay, RAY_TRIANGLE, 250.0, DRAWABLE_GEOMETRY, 1);
        if (result.drawable !is null)
        {
            Vector3 rayHitPos = cameraRay.origin + cameraRay.direction * result.distance;
            testScene.debugRenderer.AddBoundingBox(BoundingBox(rayHitPos + Vector3(-0.01, -0.01, -0.01), rayHitPos +
                Vector3(0.01, 0.01, 0.01)), Color(1.0, 1.0, 1.0), true);
        }
    }
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
    body.linearDamping = 0.2;
    body.angularDamping = 0.9;
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
