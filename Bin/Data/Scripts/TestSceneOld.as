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
}

void InitScene()
{
    testScene = Scene("GraphicsTest");

    // Make the scene directly accessible from the console
    script.defaultScene = testScene;

    testScene.CreateComponent("Octree");
    testScene.CreateComponent("DebugRenderer");
    PhysicsWorld@ world = testScene.CreateComponent("PhysicsWorld");

    // Set the physics world parameters
    world.gravity = Vector3(0, -9.81, 0);
    world.fps = 100;
    world.linearRestThreshold = 0.1;
    world.angularRestThreshold = 0.1;
    world.contactSurfaceLayer = 0.001;

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
            newNode.scale = Vector3(10, 0.5, 10);

            CollisionShape@ shape = newNode.CreateComponent("CollisionShape");
            shape.SetBox(Vector3(2, 2, 2));
            shape.collisionLayer = 2;
            shape.collisionMask = 1;

            StaticModel@ object = newNode.CreateComponent("StaticModel");
            object.model = cache.GetResource("Model", "Models/Box.mdl");
            object.material = cache.GetResource("Material", "Materials/Test.xml");
        }
    }

    // Create 2 occluder walls
    for (int x = 0; x < 2; x++)
    {
        Node@ newNode = testScene.CreateChild();
        newNode.position = Vector3(0, 5, 0);
        newNode.rotation = Quaternion(x * 90, Vector3(0, 1, 0));
        newNode.scale = Vector3(112, 5, 0.5);

        CollisionShape@ shape = newNode.CreateComponent("CollisionShape");
        shape.SetBox(Vector3(2, 2, 2));
        shape.collisionLayer = 2;
        shape.collisionMask = 1;

        StaticModel@ object = newNode.CreateComponent("StaticModel");
        object.model = cache.GetResource("Model", "Models/Box.mdl");
        object.material = cache.GetResource("Material", "Materials/Test.xml");
        object.castShadows = true;
        object.occluder = true;
    }
    
    // Create static mushroom with physics
    {
        Node@ newNode = testScene.CreateChild();
        newNode.position = Vector3(50, 0, 50);
        newNode.SetScale(10);

        CollisionShape@ shape = newNode.CreateComponent("CollisionShape");
        shape.SetTriangleMesh(cache.GetResource("Model", "Models/Mushroom.mdl"), 0);
        shape.collisionLayer = 2;
        shape.collisionMask = 1;

        StaticModel@ object = newNode.CreateComponent("StaticModel");
        object.model = cache.GetResource("Model", "Models/Mushroom.mdl");
        object.material = cache.GetResource("Material", "Materials/Mushroom.xml");
        object.castShadows = true;
        object.occluder = true;
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
        }
    }

    // Create animated models
    for (uint i = 0; i < NUM_OBJECTS; ++i)
    {
        Node@ newNode = testScene.CreateChild();
        newNode.position = Vector3(Random() * 180 - 90, 0, Random() * 180 - 90);
        newNode.rotation = Quaternion(Random() * 360, Vector3(0, 1, 0));
        newNode.SetScale(1 + Random() * 0.25);

        AnimatedModel@ object = newNode.CreateComponent("AnimatedModel");
        object.model = cache.GetResource("Model", "Models/Jack.mdl");
        object.material = cache.GetResource("Material", "Materials/Jack.xml");
        object.drawDistance = 300;
        object.castShadows = true;
        object.maxLights = 2;

        AnimationState@ anim = object.AddAnimationState(cache.GetResource("Animation", "Models/Jack_Walk.ani"));
        anim.useNlerp = true;
        anim.looped = true;
        anim.weight = 1;

        animatingObjects.Push(newNode);
    }

    // Create floating smoke clouds
    for (uint i = 0; i < NUM_BILLBOARDNODES; ++i)
    {
        Node@ newNode = testScene.CreateChild();
        newNode.position = Vector3(Random() * 200 - 100, Random() * 15 + 5, Random() * 200 - 100);

        BillboardSet@ billboard = newNode.CreateComponent("BillboardSet");
        billboard.numBillboards = NUM_BILLBOARDS;
        billboard.material = cache.GetResource("Material", "Materials/LitSmoke.xml");
        billboard.sorted = true;

        for (uint j = 0; j < NUM_BILLBOARDS; ++j)
        {
            Billboard@ bb = billboard.billboards[j];
            bb.position = Vector3(Random() * 15 - 7.5, Random() * 8 - 4, Random() * 15 - 7.5);
            bb.size = Vector2(Random() * 2 + 3, Random() * 2 + 3);
            bb.rotation = Random() * 360;
            bb.enabled = true;
        }
        billboard.Updated();

        billboards.Push(newNode);
    }

    // Create lights
    for (uint i = 0; i < NUM_LIGHTS; ++i)
    {
        Node@ newNode = testScene.CreateChild();
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
        newNode.vars["rotation"] = Variant(newNode.rotation);

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
        billboard.Updated();
    }
}

void InitConsole()
{
    XMLFile@ uiStyle = cache.GetResource("XMLFile", "UI/DefaultStyle.xml");

    Console@ console = engine.CreateConsole();
    console.style = uiStyle;
    console.numRows = 16;

    DebugHud@ hud = engine.CreateDebugHud();
    debugHud.style = uiStyle;
    debugHud.mode = DEBUGHUD_SHOW_ALL;
}

void InitUI()
{
    XMLFile@ uiStyle = cache.GetResource("XMLFile", "UI/DefaultStyle.xml");

    Cursor@ cursor = Cursor("Cursor");
    cursor.style = uiStyle;
    cursor.position = IntVector2(graphics.width / 2, graphics.height / 2);
    ui.cursor = cursor;
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

    renderer.viewports[0] = Viewport(testScene, camera);
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

        if (input.keyPress['1'])
            renderer.lightPrepass = !renderer.lightPrepass;
        
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

        if (input.keyPress['P'])
            paused = !paused;

        if (input.keyPress['L'])
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
        
        if (input.keyPress['V'])
            cameraLight.perVertex = !cameraLight.perVertex;

        if (input.keyPress['C'])
            camera.orthographic = !camera.orthographic;

        if (input.keyPress['F'])
            renderer.edgeFilter = !renderer.edgeFilter;

        if (input.keyPress['T'])
            debugHud.Toggle(DEBUGHUD_SHOW_PROFILER);

        if (input.keyPress[KEY_F5])
        {
            File@ xmlFile = File("Data/SceneOld.xml", FILE_WRITE);
            testScene.SaveXML(xmlFile);
        }

        if (input.keyPress[KEY_F7])
        {
            File@ xmlFile = File("Data/SceneOld.xml", FILE_READ);
            if (xmlFile.open)
            {
                testScene.LoadXML(xmlFile);
                // Reacquire camera, as it is part of the scene
                cameraNode = testScene.GetChild("Camera", true);
                camera = cameraNode.GetComponent("Camera");
                cameraLightNode = cameraNode.GetChild("CameraLight");
                renderer.viewports[0] = Viewport(testScene, camera);
            }
        }
    }

    if (input.keyPress[KEY_ESC])
    {
        if (ui.focusElement is null)
            engine.Exit();
        else
            console.visible = false;
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
        Vector3 position = eventData["Pos"].GetVector3();
        Quaternion rotation = eventData["Rot"].GetQuaternion();
    
        Node@ newNode = testScene.CreateChild();
        newNode.position = cameraNode.position;
        newNode.rotation = cameraNode.rotation;
        newNode.SetScale(0.1);
    
        CollisionShape@ shape = newNode.CreateComponent("CollisionShape");
        shape.SetBox(Vector3(2, 2, 2));
        shape.friction = 1.0;
        shape.collisionLayer = 1;
        shape.collisionMask = 3;
    
        RigidBody@ body = newNode.CreateComponent("RigidBody");
        body.angularMaxVelocity = 500.0;
        body.linearVelocity = cameraNode.rotation * Vector3(0.0, 1.0, 10.0);
        body.mass = 1;
    
        StaticModel@ object = newNode.CreateComponent("StaticModel");
        object.model = cache.GetResource("Model", "Models/Box.mdl");
        object.material = cache.GetResource("Material", "Materials/Test.xml");
        object.castShadows = true;
        object.shadowDistance = 150.0;
        object.drawDistance = 200.0;
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
        RayQueryResult result = testScene.octree.RaycastSingle(cameraRay, RAY_TRIANGLE, 250.0, DRAWABLE_GEOMETRY);
        if (result.drawable !is null)
        {
            Vector3 rayHitPos = cameraRay.origin + cameraRay.direction * result.distance;
            testScene.debugRenderer.AddBoundingBox(BoundingBox(rayHitPos + Vector3(-0.01, -0.01, -0.01), rayHitPos +
                Vector3(0.01, 0.01, 0.01)), Color(1.0, 1.0, 1.0), true);
        }
    }
}
