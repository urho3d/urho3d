// GraphicsTest example

const uint NUM_OBJECTS = 250;
const uint NUM_LIGHTS = 20;
const uint NUM_INSTANCENODES = 20;
const uint NUM_INSTANCES = 50;
const uint NUM_BILLBOARDNODES = 20;
const uint NUM_BILLBOARDS = 15;

Scene@ testScene;
Camera@ camera;
Light@ cameraLight;
float yaw = 0.0;
float pitch = 0.0;
float objectangle = 0.0;
bool paused = true;

int texturequality = 2;
int materialquality = 2;
bool usespecular = true;
bool drawshadows = true;
int shadowmapsize = 1024;
bool hiresshadowmap = false;
bool useocclusion = true;
bool attach = true;
int drawdebug = 0;

array<Entity@> animatingObjects;
array<Entity@> billboards;
array<Entity@> lights;

FileSelector@ fileSelector;

void start()
{
    if (engine.isHeadless())
    {
        errorDialog("GraphicsTest", "Headless mode is not supported. The program will now exit.");
        engine.exit();
        return;
    }

    initConsole();
    initScene();
    initUI();
    createCamera();

    subscribeToEvent("Update", "handleUpdate");
    subscribeToEvent("KeyDown", "handleKeyDown");
    subscribeToEvent("MouseMove", "handleMouseMove");
    subscribeToEvent("MouseButtonDown", "handleMouseButtonDown");
    subscribeToEvent("MouseButtonUp", "handleMouseButtonUp");
    subscribeToEvent("PostRenderUpdate", "handlePostRenderUpdate");
}

void initScene()
{
    @testScene = engine.createScene("GraphicsTest", BoundingBox(-1000.0, 1000.0), 8, true);
    // Make the scene directly accessible from the console
    engine.setDefaultScene(testScene);

    PhysicsWorld@ world = testScene.getPhysicsWorld();

    // Set the physics world parameters
    world.setGravity(Vector3(0.0, -9.81, 0.0));
    world.setFps(100);
    world.setLinearRestThreshold(0.1);
    world.setAngularRestThreshold(0.1);
    world.setContactSurfaceLayer(0.001);

    // Create the directional light
    Entity@ sun = testScene.createEntity();
    Light@ sunLight = sun.createComponent("Light");
    sunLight.setLightType(LIGHT_DIRECTIONAL);
    sunLight.setDirection(Vector3(0.5, -1.0, 0.5));
    sunLight.setColor(Color(0.2, 0.2, 0.2));
    sunLight.setSpecularIntensity(1.0);
    //sunLight.setCastShadows(true);
    //sunLight.setShadowCascade(CascadeParameters(3, 0.95, 0.2, 500.0));

    // Create a zone to control the ambient lighting
    Entity@ zoneEntity = testScene.createEntity();
    Zone@ zone = zoneEntity.createComponent("Zone");
    zone.setBoundingBox(BoundingBox(-1000.0, 1000.0));
    zone.setAmbientColor(Color(0.1, 0.1, 0.1));

    // Create the "floor"
    for (int y = -5; y <= 5; y++)
    {
        for (int x = -5; x <= 5; x++)
        {
            Entity@ newEntity = testScene.createEntity();
            RigidBody@ body = newEntity.createComponent("RigidBody");
            body.setPosition(Vector3(x * 20.5, -0.5, y * 20.5));
            body.setScale(Vector3(10.0, 0.5, 10.0));
            body.setCollisionShape(cache.getResource("CollisionShape", "Physics/Box.xml"));
            body.setCollisionGroup(2);
            body.setCollisionMask(1);

            StaticModel@ object = newEntity.createComponent("StaticModel");
            object.setModel(cache.getResource("Model", "Models/Box.mdl"));
            object.setMaterial(cache.getResource("Material", "Materials/Test.xml"));
            body.addChild(object);
        }
    }

    // Create 2 occluder walls
    for (int x = 0; x < 2; x++)
    {
        Entity@ newEntity = testScene.createEntity();
        RigidBody@ body = newEntity.createComponent("RigidBody");
        body.setPosition(Vector3(0.0, 5.0, 0.0));
        body.setRotation(Quaternion(x * 90.0f, Vector3(0, 1, 0)));
        body.setScale(Vector3(112.0, 5.0, 0.5));
        body.setCollisionShape(cache.getResource("CollisionShape", "Physics/Box.xml"));
        body.setCollisionGroup(2);
        body.setCollisionMask(1);

        StaticModel@ object = newEntity.createComponent("StaticModel");
        object.setModel(cache.getResource("Model", "Models/Box.mdl"));
        object.setMaterial(cache.getResource("Material", "Materials/Test.xml"));
        object.setCastShadows(true);
        object.setOccluder(true);
        body.addChild(object);
    }
    
    // Create static mushroom with physics
    {
        Entity@ newEntity = testScene.createEntity();
        RigidBody@ body = newEntity.createComponent("RigidBody");
        body.setPosition(Vector3(50.0, 0.0, 50.0));
        body.setScale(10.0);
        body.setCollisionShape(cache.getResource("CollisionShape", "Physics/Mushroom.xml"));
        body.setCollisionGroup(2);
        body.setCollisionMask(1);

        StaticModel@ object = newEntity.createComponent("StaticModel");
        object.setModel(cache.getResource("Model", "Models/Mushroom.mdl"));
        object.setMaterial(cache.getResource("Material", "Materials/Mushroom.xml"));
        object.setCastShadows(true);
        object.setOccluder(true);
        body.addChild(object);
    }
    
    // Create instanced mushrooms
    for (uint i = 0; i < NUM_INSTANCENODES; ++i)
    {
        Entity@ newEntity = testScene.createEntity();
        InstancedModel@ instanced = newEntity.createComponent("InstancedModel");

        instanced.setModel(cache.getResource("Model", "Models/Mushroom.mdl"));
        instanced.setMaterial(cache.getResource("Material", "Materials/Mushroom.xml"));
        instanced.setPosition(Vector3(random() * 160.0 - 80.0, 0.0, random() * 160.0 - 80.0));
        instanced.setCastShadows(true);
        instanced.setNumInstances(NUM_INSTANCES);

        for (uint j = 0; j < NUM_INSTANCES; ++j)
        {
            Vector3 position(random() * 20.0f - 10.0f, 0.0f, random() * 20.0f - 10.0f);
            float angle = random() * 360.0f;
            float size = 1.0f + random() * 2.0f;
            
            Instance@ instance = instanced.getInstance(j);
            instance.position = position;
            instance.rotation = Quaternion(angle, Vector3(0, 1, 0));
            instance.scale = Vector3(size, size, size);
        }
        
        instanced.updated();
    }
    
    // Create animated models
    for (uint i = 0; i < NUM_OBJECTS; ++i)
    {
        Entity@ newEntity = testScene.createEntity();
        AnimatedModel@ object = newEntity.createComponent("AnimatedModel");
        
        Vector3 position(random() * 180.0 - 90.0, 0.0, random() * 180.0 - 90.0);
        float angle = random() * 360.0f;
        
        object.setPosition(position);
        object.setRotation(Quaternion(angle, Vector3(0, 1, 0)));
        object.setCastShadows(true);
        object.setScale(1.0 + random() * 0.25);
        object.setModel(cache.getResource("Model", "Models/Jack.mdl"));
        object.setMaterial(cache.getResource("Material", "Materials/Jack.xml"));
        object.setShadowDistance(200.0);
        object.setDrawDistance(300.0);
        
        AnimationState@ anim = object.addAnimationState(cache.getResource("Animation", "Models/Jack_Walk.ani"));
        anim.setUseNlerp(true);
        anim.setLooped(true);
        anim.setWeight(1.0f);

        animatingObjects.push(newEntity);
    }
    
    // Create floating smoke clouds
    for (uint i = 0; i < NUM_BILLBOARDNODES; ++i)
    {
        Entity@ newEntity = testScene.createEntity();
        BillboardSet@ billboard = newEntity.createComponent("BillboardSet");

        billboard.setNumBillboards(NUM_BILLBOARDS);
        billboard.setPosition(Vector3(random() * 200.0 - 100.0, random() * 15.0 + 5.0, random() * 200.0 - 100.0));
        billboard.setMaterial(cache.getResource("Material", "Materials/LitSmoke.xml"));
        billboard.setBillboardsSorted(true);

        for (uint j = 0; j < NUM_BILLBOARDS; ++j)
        {
            Billboard@ bb = billboard.getBillboard(j);
            bb.position = Vector3(random() * 15.0 - 7.5, random() * 8.0 - 4.0, random() * 15.0 - 7.5);
            bb.size = Vector2(random() * 2.0 + 3.0, random() * 2.0 + 3.0);
            bb.rotation = random() * 360.0;
            bb.enabled = true;
        }
        
        billboard.updated();
        
        billboards.push(newEntity);
    }
    
    // Create lights
    for (uint i = 0; i < NUM_LIGHTS; ++i)
    {
        Entity@ newEntity = testScene.createEntity();
        Light@ light = newEntity.createComponent("Light");

        Vector3 position(
            random() * 150.0 - 75.0,
            random() * 30.0 + 30.0,
            random() * 150.0 - 75.0
        );
        
        Color color(
            (randomInt() & 1) * 0.5 + 0.5,
            (randomInt() & 1) * 0.5 + 0.5,
            (randomInt() & 1) * 0.5 + 0.5
        );
        
        if ((color.r == 0.5) && (color.g == 0.5) && (color.b == 0.5))
            color = Color(1.0, 1.0, 1.0);
        
        float angle = random() * 360.0;
        
        light.setPosition(position);
        light.setDirection(Vector3(sin(angle), -1.0, cos(angle)));
        light.setLightType(LIGHT_SPOT);
        light.setRange(75.0);
        light.setRampTexture(cache.getResource("Texture2D", "Textures/RampExtreme.png"));
        light.setFov(15.0);
        light.setColor(color);
        light.setSpecularIntensity(1.0f);
        light.setCastShadows(true);
        light.setShadowBias(BiasParameters(0.00002, 0.0));
        light.setShadowResolution(0.5);
        // The spot lights will not have anything near them, so move the near plane of the shadow camera farther
        // for better shadow depth resolution
        light.setShadowNearFarRatio(0.01);
        
        lights.push(newEntity);
    }
    
    // Save the ready scene for examination
    scene.saveXML(File("Data/GraphicsTestScene.xml", FILE_WRITE));
    scene.save(File("Data/GraphicsTestScene.scn", FILE_WRITE));
}

void animateScene(float timeStep)
{
    objectangle += 10.0f * timeStep;
    
    for (uint i = 0; i < lights.size(); ++i)
    {
        Light@ light = lights[i].getComponent("Light");
        light.setRotation(Quaternion(0, objectangle * 2, 0));
    }
    
    for (uint i = 0; i < animatingObjects.size(); ++i)
    {
        AnimatedModel@ model = animatingObjects[i].getComponent("AnimatedModel");
        uint numAnims = model.getNumAnimationStates();
        for (uint j = 0; j < numAnims; ++j)
        {
            AnimationState@ state = model.getAnimationState(j);
            state.addTime(timeStep);
        }
    }
    
    for (uint i = 0; i < billboards.size(); ++i)
    {
        BillboardSet@ billboard = billboards[i].getComponent("BillboardSet");
        uint numBB = billboard.getNumBillboards();
        for (uint j = 0; j < numBB; ++j)
        {
            Billboard@ bb = billboard.getBillboard(j);
            bb.rotation += 50.0 * timeStep;
        }

        billboard.updated();
    }
}

void initConsole()
{
    XMLFile@ uiStyle = cache.getResource("XMLFile", "UI/DefaultStyle.xml");

    Console@ console = engine.createConsole();
    console.setStyle(uiStyle);
    console.setNumRows(16);

    engine.createDebugHud();
    debugHud.setStyle(uiStyle);
    debugHud.setMode(DEBUGHUD_SHOW_STATS | DEBUGHUD_SHOW_MODE);
}

void initUI()
{
    XMLFile@ uiStyle = cache.getResource("XMLFile", "UI/DefaultStyle.xml");

    Cursor@ cursor = Cursor("Cursor");
    cursor.setStyleAuto(uiStyle);
    cursor.setPosition(renderer.getWidth() / 2, renderer.getHeight() / 2);
    ui.setCursor(cursor);

    bool uiTest = false;
    array<string> arguments = getArguments();
    for (uint i = 0; i < arguments.size(); ++i)
    {
        if (arguments[i] == "-uitest")
            uiTest = true;
    }

    if (!uiTest)
        return;

    XMLFile@ uiLayout = cache.getResource("XMLFile", "UI/TestLayout.xml");
    UIElement@ layoutRoot = ui.loadLayout(uiLayout, uiStyle);
    uiRoot.addChild(layoutRoot);

    @fileSelector = FileSelector();
    fileSelector.setStyle(uiStyle);
    fileSelector.setTitle("Load file");
    fileSelector.setButtonTexts("Load", "Cancel");
    fileSelector.getWindow().setPosition(200, 100);

    array<string> filters;
    filters.resize(2);
    filters[0] = "*.*";
    filters[1] = "*.exe";
    fileSelector.setFilters(filters, 0);

    subscribeToEvent(fileSelector, "FileSelected", "handleFileSelected");

}

void handleFileSelected(StringHash eventType, VariantMap& eventData)
{
	unsubscribeFromEvent(fileSelector, "FileSelected");
	@fileSelector = null;
}

void createCamera()
{
    Entity@ cameraEntity = testScene.createEntity("Camera");
    @camera = cameraEntity.createComponent("Camera");
    camera.setPosition(Vector3(-50.0, 2.0, -50.0));

    @cameraLight = cameraEntity.createComponent("Light");
    cameraLight.setLightType(LIGHT_SPOT);
    cameraLight.setDirection(Vector3(0.0, 0.0, 1.0));
    cameraLight.setRange(50.0);
    cameraLight.setColor(Color(2.0, 2.0, 2.0));
    cameraLight.setSpecularIntensity(2.0);
    cameraLight.setCastShadows(true);
    cameraLight.setShadowResolution(0.5);
    cameraLight.setShadowFocus(FocusParameters(false, false, false, 0.5, 3.0));
    cameraLight.setRampTexture(cache.getResource("Texture2D", "Textures/RampWide.png"));
    cameraLight.setSpotTexture(cache.getResource("Texture2D", "Textures/SpotWide.png"));
    camera.addChild(cameraLight);

    pipeline.setViewport(0, Viewport(testScene, camera));

    /*
    // Auxiliary view test
    const int D3DFMT_A8R8G8B8 = 21;

    Texture2D@ rtTex = Texture2D(TEXTURE_RENDERTARGET, "RTT");
    rtTex.setSize(512, 512, D3DFMT_A8R8G8B8);
    rtTex.getRenderSurface().setViewport(Viewport(testScene, camera));
    rtTex.setBackupTexture(cache.getResource("Texture2D", "Textures/Diffuse.dds"));

    Material@ mat = cache.getResource("Material", "Materials/Test.xml");
    MaterialTechnique@ tech = mat.getTechnique(0);
    tech.setTexture(TU_DIFFUSE, rtTex);
    */
}

void handleUpdate(StringHash eventType, VariantMap& eventData)
{
    float timeStep = eventData["TimeStep"].getFloat();

    if (!paused)
        animateScene(timeStep);

    if (ui.getFocusElement() is null)
    {
        float speedMultiplier = 1.0f;
        if (input.getKeyDown(KEY_SHIFT))
            speedMultiplier = 5.0f;
        if (input.getKeyDown(KEY_CTRL))
            speedMultiplier = 0.1f;

        if (input.getKeyDown('W'))
            camera.translateRelative(Vector3(0, 0, 10) * timeStep * speedMultiplier);
        if (input.getKeyDown('S'))
            camera.translateRelative(Vector3(0, 0, -10) * timeStep * speedMultiplier);
        if (input.getKeyDown('A'))
            camera.translateRelative(Vector3(-10, 0, 0) * timeStep * speedMultiplier);
        if (input.getKeyDown('D'))
            camera.translateRelative(Vector3(10, 0, 0) * timeStep * speedMultiplier);

        if (input.getKeyPress('1'))
        {
            int nextRenderMode = renderer.getRenderMode();
            if (input.getKeyDown(KEY_SHIFT))
            {
                --nextRenderMode;
                if (nextRenderMode < 0)
                    nextRenderMode = 2;
            }
            else
            {
                ++nextRenderMode;
                if (nextRenderMode > 2)
                    nextRenderMode = 0;
            }

            renderer.setMode(RenderMode(nextRenderMode), renderer.getWidth(), renderer.getHeight(), renderer.getFullscreen(),
                renderer.getVsync(), renderer.getMultiSample());
        }

        if (input.getKeyPress('2'))
        {
            texturequality++;
            if (texturequality > 2)
                texturequality = 0;
            pipeline.setTextureQuality(texturequality);
        }

        if (input.getKeyPress('3'))
        {
            materialquality++;
            if (materialquality > 2)
                materialquality = 0;
            pipeline.setMaterialQuality(materialquality);
        }

        if (input.getKeyPress('4'))
        {
            usespecular = !usespecular;
            pipeline.setSpecularLighting(usespecular);
        }

        if (input.getKeyPress('5'))
        {
            drawshadows = !drawshadows;
            pipeline.setDrawShadows(drawshadows);
        }

        if (input.getKeyPress('6'))
        {
            shadowmapsize *= 2;
            if (shadowmapsize > 2048)
                shadowmapsize = 512;

            pipeline.setShadowMapSize(shadowmapsize);
        }

        if (input.getKeyPress('7'))
        {
            hiresshadowmap = !hiresshadowmap;
            pipeline.setShadowMapHiresDepth(hiresshadowmap);
        }

        if (input.getKeyPress('8'))
        {
            useocclusion = !useocclusion;
            pipeline.setMaxOccluderTriangles(useocclusion ? 5000 : 0);
        }

        if (input.getKeyPress('L'))
        {
            attach = !attach;
            if (attach)
            {
                cameraLight.setPosition(Vector3(0, 0, 0));
                cameraLight.setRotation(Quaternion());
                camera.addChild(cameraLight);
            }
            else
            {
                // Detach child and set world transform to match what it was before detach
                camera.removeChild(cameraLight, true);
            }
        }

        if (input.getKeyPress(' '))
        {
            drawdebug++;
            if (drawdebug > 2) 
                drawdebug = 0;
            pipeline.setDrawDebugGeometry(drawdebug == 1);
            testScene.getPhysicsWorld().setDrawDebugGeometry(drawdebug == 2);
        }

        if (input.getKeyPress('P'))
        {
            paused = !paused;
        }

        if (input.getKeyPress('C'))
            camera.setOrthographic(!camera.isOrthographic());

        if (input.getKeyPress('T'))
            debugHud.toggle(DEBUGHUD_SHOW_PROFILER);

        if (input.getKeyPress('F'))
        {
            EdgeFilterParameters params = pipeline.getEdgeFilter();
            if (params.maxFilter > 0.0f)
                params.maxFilter = 0.0f;
            else
                params.maxFilter = 1.0f;
            pipeline.setEdgeFilter(params);
        }
    }

    if (input.getKeyPress(KEY_ESC))
    {
        if (ui.getFocusElement() is null)
            engine.exit();
        else
            console.setVisible(false);
    }
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

void handleMouseMove(StringHash eventType, VariantMap& eventData)
{
    if (eventData["Buttons"].getInt() & MOUSEB_RIGHT != 0)
    {
        int mousedx = eventData["X"].getInt();
        int mousedy = eventData["Y"].getInt();
        yaw += mousedx / 10.0f;
        pitch += mousedy / 10.0f;
        if (pitch < -90.0f)
            pitch = -90.0f;
        if (pitch > 90.0f)
            pitch = 90.0f;

        camera.setRotation(Quaternion(yaw, Vector3(0, 1, 0)) * Quaternion(pitch, Vector3(1, 0, 0)));
    }
}

void handleMouseButtonDown(StringHash eventType, VariantMap& eventData)
{
    int button = eventData["Button"].getInt();
    if (button == MOUSEB_RIGHT)
        uiCursor.setVisible(false);

    // Test creating a new physics object
    if ((button == MOUSEB_LEFT) && (ui.getElementAt(ui.getCursorPosition(), true) is null) && (ui.getFocusElement() is null))
    {
        Entity@ newEntity = testScene.createEntity();
        
        RigidBody@ body = newEntity.createComponent("RigidBody");
        body.setMode(PHYS_DYNAMIC);
        body.setPosition(camera.getPosition());
        body.setRotation(camera.getRotation());
        body.setScale(0.1);
        body.setFriction(1.0);
        body.setAngularMaxVelocity(500.0);
        body.setCollisionShape(cache.getResource("CollisionShape", "Physics/Box.xml"));
        body.setCollisionGroup(1);
        body.setCollisionMask(3);
        body.setLinearVelocity(camera.getUpVector() + camera.getForwardVector() * 10.0);
        
        StaticModel@ object = newEntity.createComponent("StaticModel");
        object.setModel(cache.getResource("Model", "Models/Box.mdl"));
        object.setMaterial(cache.getResource("Material", "Materials/Test.xml"));
        object.setCastShadows(true);
        object.setShadowDistance(75.0f);
        object.setDrawDistance(100.0f);
        body.addChild(object);
    }
}

void handleMouseButtonUp(StringHash eventType, VariantMap& eventData)
{
    if (eventData["Button"].getInt() == MOUSEB_RIGHT)
        uiCursor.setVisible(true);
}

void handlePostRenderUpdate(StringHash eventType, VariantMap& eventData)
{
    IntVector2 pos = ui.getCursorPosition();
    if (ui.getElementAt(pos, true) is null)
    {
        Ray cameraRay = camera.getScreenRay(float(pos.x) / renderer.getWidth(), float(pos.y) / renderer.getHeight());
        array<RayQueryResult> result = testScene.getOctree().raycast(cameraRay, NODE_STATICMODEL | NODE_ANIMATEDMODEL |
            NODE_INSTANCEDMODEL, 250.0f, RAY_TRIANGLE);
        if (result.size() > 0)
        {
            VolumeNode@ node = result[0].node;
            Vector3 rayHitPos = cameraRay.origin + cameraRay.direction * result[0].distance;
            debugRenderer.addBoundingBox(BoundingBox(rayHitPos + Vector3(-0.01, -0.01, -0.01), rayHitPos +
                Vector3(0.01, 0.01, 0.01)), Color(1.0, 1.0, 1.0), true);
        }
    }
}
