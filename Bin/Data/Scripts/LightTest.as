#include "Scripts/Utilities/Network.as"

Scene@ testScene;
Camera@ camera;
Node@ cameraNode;

float yaw = 0.0;
float pitch = 0.0;
int modelIndex = 0;
int maxLights = 100;
int maxObjects = 100;
int numLights = 0;
int numObjects = 1;

Array<String> modelNames = {"Models/Box.mdl", "Models/Mushroom.mdl", "Models/Jack.mdl"};
Array<String> materialNames = {"Materials/Test.xml", "Materials/Mushroom.xml", "Materials/Jack.xml"};
Array<Vector3> modelScales = {Vector3(0.6, 0.6, 0.6), Vector3(1, 1, 1), Vector3(1, 1, 1)};
Array<Light@> lights;
Array<StaticModel@> objects;

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
}

void InitScene()
{
    testScene = Scene("TestScene");
    testScene.CreateComponent("Octree");
    testScene.CreateComponent("DebugRenderer");

    Node@ zoneNode = testScene.CreateChild("Zone");
    Zone@ zone = zoneNode.CreateComponent("Zone");
    zone.ambientColor = Color(0.1, 0.1, 0.1);
    zone.fogColor = Color(0.0, 0.0, 0.0);
    zone.fogStart = 100.0;
    zone.fogEnd = 300.0;
    zone.boundingBox = BoundingBox(-1000.0, 1000.0);

    for (int i = 0; i < maxObjects; ++i)
    {
        Node@ objectNode = testScene.CreateChild("Object");
        if (i >= 1)
            objectNode.position = GetRandomPosition();

        StaticModel@ object = objectNode.CreateComponent("StaticModel");
        object.visible = false;
        objects.Push(object);
    }
    
    for (int i = 0; i < maxLights; ++i)
    {
        Node@ lightNode = testScene.CreateChild("Light");
        Light@ light = lightNode.CreateComponent("Light");
        lightNode.position = GetRandomPosition();

        Color color((RandomInt() & 1) * 0.5 + 0.5, (RandomInt() & 1) * 0.5 + 0.5, (RandomInt() & 1) * 0.5 + 0.5);
        if (color.r == 0.5 && color.g == 0.5 && color.b == 0.5)
            color = Color(1, 1, 1);

        light.visible = false;
        light.range = 2.0;
        light.color = color;
        light.specularIntensity = 1.0;
        lights.Push(light);
    }
    
    LoadNewModel();
    EnableLights();
    EnableObjects();

    // Enable access to this script file & scene from the console
    script.defaultScene = testScene;
    script.defaultScriptFile = scriptFile;

    // Create the camera outside the scene so it is unaffected by scene load/save
    cameraNode = Node();
    camera = cameraNode.CreateComponent("Camera");
    cameraNode.position = Vector3(0, 0, -10);

    if (!engine.headless)
        renderer.viewports[0] = Viewport(testScene, camera);
}

void LoadNewModel()
{
    for (uint i = 0; i < objects.length; ++i)
    {
        objects[i].model = cache.GetResource("Model", modelNames[modelIndex]);
        objects[i].material = cache.GetResource("Material", materialNames[modelIndex]);
        objects[i].node.scale = modelScales[modelIndex];
    }
}

void EnableLights()
{
    for (uint i = 0; i < lights.length; ++i)
        lights[i].visible = i < numLights;
}

void EnableObjects()
{
    for (uint i = 0; i < objects.length; ++i)
        objects[i].visible = i < numObjects;
}

void RandomizePositions()
{
    for (uint i = 0; i < objects.length; ++i)
        objects[i].node.position = GetRandomPosition();

    for (uint i = 0; i < lights.length; ++i)
        lights[i].node.position = GetRandomPosition();
}

void ToggleVertexLighting()
{
    for (uint i = 0; i < lights.length; ++i)
        lights[i].perVertex = !lights[i].perVertex;
}

Vector3 GetRandomPosition()
{
    return Vector3(Random(4.0) - 2.0, Random(3.0) - 1.5, Random(4.0) - 2.0);
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
            int quality = renderer.textureQuality;
            ++quality;
            if (quality > 2)
                quality = 0;
            renderer.textureQuality = quality;
        }

        if (input.keyPress['2'])
        {
            int quality = renderer.materialQuality;
            ++quality;
            if (quality > 2)
                quality = 0;
            renderer.materialQuality = quality;
        }

        if (input.keyPress['3'])
            renderer.specularLighting = !renderer.specularLighting;

        if (input.keyPress['4'])
            renderer.drawShadows = !renderer.drawShadows;

        if (input.keyPress['5'])
        {
            int size = renderer.shadowMapSize;
            size *= 2;
            if (size > 2048)
                size = 512;
            renderer.shadowMapSize = size;
        }

        if (input.keyPress['6'])
            renderer.shadowQuality = renderer.shadowQuality + 1;

        if (input.keyPress['7'])
        {
            bool occlusion = renderer.maxOccluderTriangles > 0;
            occlusion = !occlusion;
            renderer.maxOccluderTriangles = occlusion ? 5000 : 0;
        }
        
        if (input.keyPress['8'])
            renderer.dynamicInstancing = !renderer.dynamicInstancing;

        if (input.keyPress['9'])
            renderer.lightStencilMasking = !renderer.lightStencilMasking;

        if (input.keyPress['C'])
            camera.orthographic = !camera.orthographic;

        if (input.keyPress['T'])
            debugHud.Toggle(DEBUGHUD_SHOW_PROFILER);

        if (input.keyPress['Z'])
        {
            --modelIndex;
            if (modelIndex < 0)
                modelIndex = 0;
            LoadNewModel();
        }

        if (input.keyPress['X'])
        {
            ++modelIndex;
            if (modelIndex > modelNames.length - 1)
                modelIndex = modelNames.length - 1;
            LoadNewModel();
        }
        
        if (input.keyPress[KEY_RIGHT])
        {
            ++numObjects;
            if (numObjects > maxObjects)
                numObjects = maxObjects;
            EnableObjects();
        }

        if (input.keyPress[KEY_LEFT])
        {
            --numObjects;
            if (numObjects < 0)
                numObjects = 0;
            EnableObjects();
        }

        if (input.keyPress[KEY_UP])
        {
            ++numLights;
            if (numLights > maxLights)
                numLights = maxLights;
            EnableLights();
        }

        if (input.keyPress[KEY_DOWN])
        {
            --numLights;
            if (numLights < 0)
                numLights = 0;
            EnableLights();
        }

        if (input.keyPress[KEY_PAGEUP])
        {
            numLights += 10;
            if (numLights > maxLights)
                numLights = maxLights;
            EnableLights();
        }

        if (input.keyPress[KEY_PAGEDOWN])
        {
            numLights -= 10;
            if (numLights < 0)
                numLights = 0;
            EnableLights();
        }
        
        if (input.keyPress['R'])
            RandomizePositions();

        if (input.keyPress['V'])
            ToggleVertexLighting();
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
}

void HandleMouseButtonUp(StringHash eventType, VariantMap& eventData)
{
    if (eventData["Button"].GetInt() == MOUSEB_RIGHT)
        ui.cursor.visible = true;
}

