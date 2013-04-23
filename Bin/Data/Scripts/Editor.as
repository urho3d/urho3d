// Urho3D editor

#include "Scripts/Editor/EditorView.as"
#include "Scripts/Editor/EditorScene.as"
#include "Scripts/Editor/EditorActions.as"
#include "Scripts/Editor/EditorUIElement.as"
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
    // Assign the value ASAP because configFileName is needed on exit, including exit on error
    if (GetPlatform() == "Windows")
        configPath = "Urho3D/Editor/";
    else
        // Unix-like platforms usually hide application configuration file
        configPath = ".Urho3D/Editor/";
    configFileName = fileSystem.userDocumentsDir + configPath + "Config.xml";

    if (engine.headless)
    {
        ErrorDialog("Urho3D Editor", "Headless mode is not supported. The program will now exit.");
        engine.Exit();
        return;
    }

    SubscribeToEvent("Update", "HandleUpdate");

    // Enable console commands from the editor script
    script.defaultScriptFile = scriptFile;
    // Enable automatic resource reloading
    cache.autoReloadResources = true;
    // Use OS mouse without grabbing it
    input.mouseVisible = true;

    // Create root scene node
    CreateScene();
    // Load editor settings and preferences
    LoadConfig();
    // Create user interface for the editor
    CreateUI();
    // Create root UI element where all 'editable' UI elements would be parented to
    CreateRootUIElement();
    // Load the initial scene if provided
    ParseArguments();
}

void Stop()
{
    SaveConfig();
}

void ParseArguments()
{
    Array<String> arguments = GetArguments();
    bool loaded = false;

    // The first argument should be the editor script name. Scan for a scene to load
    for (uint i = 1; i < arguments.length; ++i)
    {
        if (arguments[i][0] != '-')
        {
            loaded = LoadScene(arguments[i]);
            break;
        }
    }

    if (!loaded)
        ResetScene();
}

void HandleUpdate(StringHash eventType, VariantMap& eventData)
{
    float timeStep = eventData["TimeStep"].GetFloat();

    UpdateView(timeStep);
    UpdateStats(timeStep);
    UpdateScene(timeStep);
    UpdateGizmo();
    UpdateDirtyUI();
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
    XMLElement uiElem = configElem.GetChild("ui");
    XMLElement hierarchyElem = configElem.GetChild("hierarchy");
    XMLElement inspectorElem = configElem.GetChild("attributeinspector");

    if (!cameraElem.isNull)
    {
        if (cameraElem.HasAttribute("nearclip")) camera.nearClip = cameraElem.GetFloat("nearclip");
        if (cameraElem.HasAttribute("farclip")) camera.farClip = cameraElem.GetFloat("farclip");
        if (cameraElem.HasAttribute("fov")) camera.fov = cameraElem.GetFloat("fov");
        if (cameraElem.HasAttribute("speed")) cameraBaseSpeed = cameraElem.GetFloat("speed");
    }

    if (!objectElem.isNull)
    {
        if (objectElem.HasAttribute("newnodedistance")) newNodeDistance = objectElem.GetFloat("newnodedistance");
        if (objectElem.HasAttribute("movestep")) moveStep = objectElem.GetFloat("movestep");
        if (objectElem.HasAttribute("rotatestep")) rotateStep = objectElem.GetFloat("rotatestep");
        if (objectElem.HasAttribute("scalestep")) scaleStep = objectElem.GetFloat("scalestep");
        if (objectElem.HasAttribute("movesnap")) moveSnap = objectElem.GetBool("movesnap");
        if (objectElem.HasAttribute("rotatesnap")) rotateSnap = objectElem.GetBool("rotatesnap");
        if (objectElem.HasAttribute("scalesnap")) scaleSnap = objectElem.GetBool("scalesnap");
        if (objectElem.HasAttribute("uselocalids")) useLocalIDs = objectElem.GetBool("uselocalids");
        if (objectElem.HasAttribute("applymateriallist")) applyMaterialList = objectElem.GetBool("applymateriallist");
        if (objectElem.HasAttribute("importoptions")) importOptions = objectElem.GetAttribute("importoptions");
        if (objectElem.HasAttribute("pickmode")) pickMode = objectElem.GetInt("pickmode");
    }

    if (!renderingElem.isNull)
    {
        if (renderingElem.HasAttribute("texturequality")) renderer.textureQuality = renderingElem.GetInt("texturequality");
        if (renderingElem.HasAttribute("materialquality")) renderer.materialQuality = renderingElem.GetInt("materialquality");
        if (renderingElem.HasAttribute("shadowresolution")) SetShadowResolution(renderingElem.GetInt("shadowresolution"));
        if (renderingElem.HasAttribute("shadowquality")) renderer.shadowQuality = renderingElem.GetInt("shadowquality");
        if (renderingElem.HasAttribute("maxoccludertriangles")) renderer.maxOccluderTriangles = renderingElem.GetInt("maxoccludertriangles");
        if (renderingElem.HasAttribute("specularlighting")) renderer.specularLighting = renderingElem.GetBool("specularlighting");
        if (renderingElem.HasAttribute("dynamicinstancing")) renderer.dynamicInstancing = instancingSetting = renderingElem.GetBool("dynamicinstancing");
        if (renderingElem.HasAttribute("framelimiter")) engine.maxFps = renderingElem.GetBool("framelimiter") ? 200 : 0;
    }

    if (!uiElem.isNull)
    {
        if (uiElem.HasAttribute("minopacity")) uiMinOpacity = uiElem.GetFloat("minopacity");
        if (uiElem.HasAttribute("maxopacity")) uiMaxOpacity = uiElem.GetFloat("maxopacity");
    }

    if (!hierarchyElem.isNull)
    {
        if (hierarchyElem.HasAttribute("showinternaluielement")) showInternalUIElement = hierarchyElem.GetBool("showinternaluielement");
    }

    if (!inspectorElem.isNull)
    {
        if (inspectorElem.HasAttribute("originalcolor")) normalTextColor = inspectorElem.GetColor("originalcolor");
        if (inspectorElem.HasAttribute("modifiedcolor")) modifiedTextColor = inspectorElem.GetColor("modifiedcolor");
        if (inspectorElem.HasAttribute("noneditablecolor")) nonEditableTextColor = inspectorElem.GetColor("noneditablecolor");
        if (inspectorElem.HasAttribute("shownoneditable")) showNonEditableAttribute = inspectorElem.GetBool("shownoneditable");
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
    XMLElement hierarchyElem = configElem.CreateChild("hierarchy");
    XMLElement inspectorElem = configElem.CreateChild("attributeinspector");

    // The save config may be called on error exit so some of the objects below could still be null
    if (camera !is null)
    {
        cameraElem.SetFloat("nearclip", camera.nearClip);
        cameraElem.SetFloat("farclip", camera.farClip);
        cameraElem.SetFloat("fov", camera.fov);
        cameraElem.SetFloat("speed", cameraBaseSpeed);
    }

    objectElem.SetFloat("newnodedistance", newNodeDistance);
    objectElem.SetFloat("movestep", moveStep);
    objectElem.SetFloat("rotatestep", rotateStep);
    objectElem.SetFloat("scalestep", scaleStep);
    objectElem.SetBool("movesnap", moveSnap);
    objectElem.SetBool("rotatesnap", rotateSnap);
    objectElem.SetBool("scalesnap", scaleSnap);
    objectElem.SetBool("uselocalids", useLocalIDs);
    objectElem.SetBool("applymateriallist", applyMaterialList);
    objectElem.SetAttribute("importoptions", importOptions);
    objectElem.SetInt("pickmode", pickMode);

    if (renderer !is null)
    {
        renderingElem.SetInt("texturequality", renderer.textureQuality);
        renderingElem.SetInt("materialquality", renderer.materialQuality);
        renderingElem.SetInt("shadowresolution", GetShadowResolution());
        renderingElem.SetInt("shadowquality", renderer.shadowQuality);
        renderingElem.SetInt("maxoccludertriangles", renderer.maxOccluderTriangles);
        renderingElem.SetBool("specularlighting", renderer.specularLighting);
    }

    if (graphics !is null)
        renderingElem.SetBool("dynamicinstancing", graphics.sm3Support ? renderer.dynamicInstancing : instancingSetting);

    renderingElem.SetBool("framelimiter", engine.maxFps > 0);

    uiElem.SetFloat("minopacity", uiMinOpacity);
    uiElem.SetFloat("maxopacity", uiMaxOpacity);

    hierarchyElem.SetBool("showinternaluielement", showInternalUIElement);

    inspectorElem.SetColor("originalcolor", normalTextColor);
    inspectorElem.SetColor("modifiedcolor", modifiedTextColor);
    inspectorElem.SetColor("noneditablecolor", nonEditableTextColor);
    inspectorElem.SetBool("shownoneditable", showNonEditableAttribute);

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
