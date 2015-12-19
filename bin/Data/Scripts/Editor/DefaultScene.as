String defaultSceneFileName = fileSystem.GetAppPreferencesDir("urho3d", "Editor") + "DefaultScene.json";

void CreateDefaultScene()
{
    editorScene.CreateComponent("Octree");
    editorScene.CreateComponent("DebugRenderer");
    
    Node@ sampleNode = editorScene.CreateChild("Sample");
    sampleNode.position = Vector3(0.0f, 0.1f, 0.0f);

    Node@ zoneNode = sampleNode.CreateChild("Zone");
    Zone@ zone = zoneNode.CreateComponent("Zone");
    zone.boundingBox = BoundingBox(-1000.0f, 1000.0f);
    zone.ambientColor = Color(0.5f, 0.5f, 0.5f);
    zone.fogColor = Color(0.7f, 0.8f, 0.9f);
    zone.heightFog = true;
    zone.fogHeight = -0.5f;
    zone.fogHeightScale = 1.0f;
    zone.fogStart = 10.0f;
    zone.fogEnd = 100.0f;
    
    Node@ planeNode = sampleNode.CreateChild("Plane");
    planeNode.SetScale(1000.0f);
    planeNode.position = Vector3(0.0f, 0.0f, 0.0f);
    StaticModel@ planeObject = planeNode.CreateComponent("StaticModel");
    planeObject.model = cache.GetResource("Model", "Models/Plane.mdl");
    planeObject.castShadows = true;

    Node@ boxNode = sampleNode.CreateChild("Box");
    boxNode.SetScale(2.0f);
    boxNode.position = Vector3(0.0f, 1.0f, 0.0f);
    StaticModel@ boxObject = boxNode.CreateComponent("StaticModel");
    boxObject.model = cache.GetResource("Model", "Models/Box.mdl");
    boxObject.material = cache.GetResource("Material", "Materials/Stone.xml");
    boxObject.castShadows = true;
        
    Node@ lightNode = sampleNode.CreateChild("Light");
    lightNode.direction = Vector3(1.0f, -1.0f, 0.5f);
    Light@ light = lightNode.CreateComponent("Light");
    light.lightType = LIGHT_DIRECTIONAL;
    light.color = Color(0.8f, 0.8f, 0.8f);
    light.castShadows = true;
    light.shadowBias = BiasParameters(0.00005f, 0.5f);
    light.shadowCascade = CascadeParameters(10.0f, 50.0f, 100.0f, 0.0f, 0.8f);
}

void GetDefaultScene()
{
    editorScene.Clear();

    if (!fileSystem.FileExists(defaultSceneFileName))
    {
        CreateDefaultScene();
        return;
    }

    bool loaded = editorScene.LoadJSON(cache.GetFile(defaultSceneFileName));
    if (!loaded)
        CreateDefaultScene();
}

bool SaveSceneAsDefault()
{
    File file(defaultSceneFileName, FILE_WRITE);
    editorScene.SaveJSON(file);
    return true;
}
