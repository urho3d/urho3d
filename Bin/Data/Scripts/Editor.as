// Urho3D editor

#include "Scripts/Editor/EditorView.as"
#include "Scripts/Editor/EditorScene.as"
#include "Scripts/Editor/EditorGizmo.as"
#include "Scripts/Editor/EditorSettings.as"
#include "Scripts/Editor/EditorPreferences.as"
#include "Scripts/Editor/EditorUI.as"
#include "Scripts/Editor/EditorImport.as"

String configPath;
String configFileName;

// If loaded in OpenGL mode, remember the instancing setting in config instead of auto-disabling it
bool instancingSetting = true;

void Start()
{
    if (engine.headless)
    {
        ErrorDialog("Urho3D Editor", "Headless mode is not supported. The program will now exit.");
        engine.Exit();
        return;
    }

    if (GetPlatform() == "Windows")
        configPath = "Urho3D/Editor/";
    else
        // Unix-like platforms usually hide application configuration file
        configPath = ".Urho3D/Editor/";
    configFileName = fileSystem.userDocumentsDir + configPath + "Config.xml";

    SubscribeToEvent("Update", "HandleUpdate");
    // Enable console commands from the editor script
    script.defaultScriptFile = scriptFile;
    // Enable automatic resource reloading
    cache.autoReloadResources = true;
    // Use OS mouse without grabbing it
    input.mouseVisible = true;

    CreateScene();
    CreateUI();
    LoadConfig();
    ParseArguments();
}

void Stop()
{
    SaveConfig();
}

void ParseArguments()
{
    Array<String> arguments = GetArguments();

    // The first argument should be the editor script name. Scan for a scene to load
    for (uint i = 1; i < arguments.length; ++i)
    {
        if (arguments[i][0] != '-')
        {
            LoadScene(arguments[i]);
            break;
        }
    }
}

void HandleUpdate(StringHash eventType, VariantMap& eventData)
{
    float timeStep = eventData["TimeStep"].GetFloat();

    UpdateView(timeStep);
    UpdateStats(timeStep);
    UpdateScene(timeStep);
    UpdateGizmo();
}

void LoadConfig()
{
    if (!fileSystem.FileExists(configFileName))
        return;

    XMLFile config;
    config.Load(File(configFileName, FILE_READ));

    XMLElement configElem = config.root;
    if (configElem.isNull)
        return;

    XMLElement cameraElem = configElem.GetChild("camera");
    XMLElement objectElem = configElem.GetChild("object");
    XMLElement renderingElem = configElem.GetChild("rendering");

    if (!cameraElem.isNull)
    {
        camera.nearClip = cameraElem.GetFloat("nearclip");
        camera.farClip = cameraElem.GetFloat("farclip");
        camera.fov = cameraElem.GetFloat("fov");
        cameraBaseSpeed = cameraElem.GetFloat("speed");
    }

    if (!objectElem.isNull)
    {
        newNodeDistance = objectElem.GetFloat("newnodedistance");
        moveStep = objectElem.GetFloat("movestep");
        rotateStep = objectElem.GetFloat("rotatestep");
        scaleStep = objectElem.GetFloat("scalestep");
        moveSnap = objectElem.GetBool("movesnap");
        rotateSnap = objectElem.GetBool("rotatesnap");
        scaleSnap = objectElem.GetBool("scalesnap");
        useLocalIDs = objectElem.GetBool("uselocalids");
        generateTangents = objectElem.GetBool("generatetangents");
        pickMode = objectElem.GetInt("pickmode");
    }

    if (!renderingElem.isNull)
    {
        renderer.textureQuality = renderingElem.GetInt("texturequality");
        renderer.materialQuality = renderingElem.GetInt("materialquality");
        SetShadowResolution(renderingElem.GetInt("shadowresolution"));
        renderer.shadowQuality = renderingElem.GetInt("shadowquality");
        renderer.maxOccluderTriangles = renderingElem.GetInt("maxoccludertriangles");
        renderer.specularLighting = renderingElem.GetBool("specularlighting");
        renderer.dynamicInstancing = instancingSetting = renderingElem.GetBool("dynamicinstancing");
        engine.maxFps = renderingElem.GetBool("framelimiter") ? 200 : 0;
    }
}

void SaveConfig()
{
    CreateDir(configPath);

    XMLFile config;
    XMLElement configElem = config.CreateRoot("configuration");
    XMLElement cameraElem = configElem.CreateChild("camera");
    XMLElement objectElem = configElem.CreateChild("object");
    XMLElement renderingElem = configElem.CreateChild("rendering");
    XMLElement uiElem = configElem.CreateChild("ui");
    XMLElement attributeInspector = configElem.CreateChild("attribute-inspector");
    XMLElement textLabelColorElem = attributeInspector.CreateChild("text-label-color");

    cameraElem.SetFloat("nearclip", camera.nearClip);
    cameraElem.SetFloat("farclip", camera.farClip);
    cameraElem.SetFloat("fov", camera.fov);
    cameraElem.SetFloat("speed", cameraBaseSpeed);

    objectElem.SetFloat("newnodedistance", newNodeDistance);
    objectElem.SetFloat("movestep", moveStep);
    objectElem.SetFloat("rotatestep", rotateStep);
    objectElem.SetFloat("scalestep", scaleStep);
    objectElem.SetBool("movesnap", moveSnap);
    objectElem.SetBool("rotatesnap", rotateSnap);
    objectElem.SetBool("scalesnap", scaleSnap);
    objectElem.SetBool("uselocalids", useLocalIDs);
    objectElem.SetBool("generatetangents", generateTangents);
    objectElem.SetInt("pickmode", pickMode);

    renderingElem.SetInt("texturequality", renderer.textureQuality);
    renderingElem.SetInt("materialquality", renderer.materialQuality);
    renderingElem.SetInt("shadowresolution", GetShadowResolution());
    renderingElem.SetInt("shadowquality", renderer.shadowQuality);
    renderingElem.SetInt("maxoccludertriangles", renderer.maxOccluderTriangles);
    renderingElem.SetBool("specularlighting", renderer.specularLighting);
    renderingElem.SetBool("dynamicinstancing", graphics.sm3Support ? renderer.dynamicInstancing : instancingSetting);
    renderingElem.SetBool("framelimiter", engine.maxFps > 0);
    
    uiElem.SetFloat("min-opacity", uiMinOpacity);
    uiElem.SetFloat("max-opacity", uiMaxOpacity);
    
    textLabelColorElem.SetColor("original-attribute", normalTextColor);
    textLabelColorElem.SetColor("modified-attribute", modifiedTextColor);

    config.Save(File(configFileName, FILE_WRITE));
}

void CreateDir(const String&in pathName, const String&in baseDir = fileSystem.userDocumentsDir)
{
    Array<String> dirs = pathName.Split('/');
    String subdir = baseDir;
    for (uint i = 0; i < dirs.length; ++i)
    {
        subdir += dirs[i] + "/";
        fileSystem.CreateDir(subdir);
    }
}
