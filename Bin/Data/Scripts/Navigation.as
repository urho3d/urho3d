Scene@ testScene;
Camera@ camera;
Node@ cameraNode;

float yaw = 0.0;
float pitch = 0.0;
int drawDebug = 0;

Vector3 startPos;
Vector3 endPos;

bool startPosSet = false;
bool endPosSet = false;

Array<Vector3> path;

bool offMeshInProgress = false;
Vector3 offMeshStart;
Vector3 offMeshEnd;

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
}

void InitConsole()
{
    XMLFile@ uiStyle = cache.GetResource("XMLFile", "UI/DefaultStyle.xml");

    engine.CreateDebugHud();
    debugHud.style = uiStyle;
    debugHud.mode = DEBUGHUD_SHOW_ALL;
    debugHud.SetAppStats("Instructions:", "\nShift+LMB set startpoint\nLMB set endpoint\nMMB create/delete object\nCtrl+LMB set offmesh link start, then end");

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
    
    testScene.CreateComponent("Navigable");
    NavigationMesh@ navMesh = testScene.CreateComponent("NavigationMesh");
    // Add bounding box padding in the Y-direction to be able to add objects on top of the boxes
    navMesh.padding = Vector3(0, 10, 0);
    navMesh.Build();
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
            if (drawDebug > 3)
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
            File@ xmlFile = File(fileSystem.programDir + "Data/Scenes/Navigation.xml", FILE_WRITE);
            testScene.SaveXML(xmlFile);
        }

        if (key == KEY_F7)
        {
            File@ xmlFile = File(fileSystem.programDir + "Data/Scenes/Navigation.xml", FILE_READ);
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

    if (button == MOUSEB_LEFT && ui.GetElementAt(ui.cursorPosition, true) is null && ui.focusElement is null)
    {
        bool setStartPos = input.qualifierDown[QUAL_SHIFT];
        bool setOffMesh = input.qualifierDown[QUAL_CTRL];
        IntVector2 pos = ui.cursorPosition;
        Ray cameraRay = camera.GetScreenRay(float(pos.x) / graphics.width, float(pos.y) / graphics.height);
        RayQueryResult result = testScene.octree.RaycastSingle(cameraRay, RAY_TRIANGLE, 1000.0, DRAWABLE_GEOMETRY);

        if (result.drawable !is null)
        {
            NavigationMesh@ navMesh = testScene.GetComponent("NavigationMesh");

            Vector3 rayHitPos = cameraRay.origin + cameraRay.direction * result.distance;
            
            if (setOffMesh)
            {
                if (!offMeshInProgress)
                {
                    offMeshStart = rayHitPos;
                    offMeshInProgress = true;
                }
                else
                {
                    offMeshEnd = rayHitPos;
                    offMeshInProgress = false;
                    
                    Node@ start = testScene.CreateChild();
                    Node@ end = testScene.CreateChild();
                    start.position = offMeshStart;
                    end.position = offMeshEnd;
                    OffMeshConnection@ conn = start.CreateComponent("OffMeshConnection");
                    conn.endPoint = end;

                    BoundingBox rebuildBox(start.position - Vector3(1,1,1), start.position + Vector3(1,1,1));

                    navMesh.Build(rebuildBox);
                }
            }
            else
            {
                if (setStartPos)
                {
                    startPos = rayHitPos;
                    startPosSet = true;
                }
                else
                {
                    endPos = rayHitPos;
                    endPosSet = true;
                }
            }

            if (startPosSet && endPosSet)
            {
                path = navMesh.FindPath(startPos, endPos);
            }
        }
    }
    
    if (button == MOUSEB_MIDDLE)
    {
        IntVector2 pos = ui.cursorPosition;
        if (ui.GetElementAt(pos, true) !is null)
            return;
    
        Ray cameraRay = camera.GetScreenRay(float(pos.x) / graphics.width, float(pos.y) / graphics.height);
        RayQueryResult result = testScene.octree.RaycastSingle(cameraRay, RAY_TRIANGLE, 1000.0, DRAWABLE_GEOMETRY);
    
        bool rebuild = false;
        BoundingBox rebuildBox;
    
        if (result.drawable !is null)
        {
            Vector3 rayHitPos = cameraRay.origin + cameraRay.direction * result.distance;
            if (result.node.name == "Mushroom")
            {
                rebuild = true;
                rebuildBox = result.drawable.worldBoundingBox;
                result.node.Remove();
            }
            else
            {
                Node@ objectNode = testScene.CreateChild("Mushroom");
                objectNode.position = rayHitPos;
                objectNode.rotation = Quaternion(0, Random(360.0), 0);
                objectNode.SetScale(5);
    
                StaticModel@ object = objectNode.CreateComponent("StaticModel");
                object.model = cache.GetResource("Model", "Models/Mushroom.mdl");
                object.material = cache.GetResource("Material", "Materials/Mushroom.xml");
                object.castShadows = true;
    
                RigidBody@ body = objectNode.CreateComponent("RigidBody");
                CollisionShape@ shape = objectNode.CreateComponent("CollisionShape");
                shape.SetTriangleMesh(object.model, 0);
                
                rebuild = true;
                rebuildBox = object.worldBoundingBox;
            }
        }
        
        if (rebuild)
        {
            NavigationMesh@ navMesh = testScene.GetComponent("NavigationMesh");
            navMesh.Build(rebuildBox);
            
            // Recalculate path if applicable
            if (startPosSet && endPosSet)
                path = navMesh.FindPath(startPos, endPos);
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
    if (drawDebug == 3)
    {
        NavigationMesh@ navMesh = testScene.GetComponent("NavigationMesh");
        navMesh.DrawDebugGeometry(testScene.debugRenderer, true);
    }

    IntVector2 pos = ui.cursorPosition;
    if (ui.GetElementAt(pos, true) is null)
    {
        Ray cameraRay = camera.GetScreenRay(float(pos.x) / graphics.width, float(pos.y) / graphics.height);
        RayQueryResult result = testScene.octree.RaycastSingle(cameraRay, RAY_TRIANGLE, 1000.0, DRAWABLE_GEOMETRY);
        if (result.drawable !is null)
        {
            Vector3 rayHitPos = cameraRay.origin + cameraRay.direction * result.distance;
            testScene.debugRenderer.AddBoundingBox(BoundingBox(rayHitPos + Vector3(-0.01, -0.01, -0.01), rayHitPos +
                Vector3(0.01, 0.01, 0.01)), Color(1.0, 1.0, 1.0), true);
        }
    }
    
    if (startPosSet)
    {
        testScene.debugRenderer.AddBoundingBox(BoundingBox(startPos + Vector3(-0.1, -0.1, -0.1), startPos +
                Vector3(0.1, 0.1, 0.1)), Color(1.0, 1.0, 1.0), true);
    }
    if (endPosSet)
    {
        testScene.debugRenderer.AddBoundingBox(BoundingBox(endPos + Vector3(-0.1, -0.1, -0.1), endPos +
                Vector3(0.1, 0.1, 0.1)), Color(1.0, 1.0, 1.0), true);
    }

    if (path.length > 1)
    {
        for (uint i = 0; i < path.length - 1; ++i)
            testScene.debugRenderer.AddLine(path[i], path[i + 1], Color(1.0, 1.0, 1.0), false);
    }
}