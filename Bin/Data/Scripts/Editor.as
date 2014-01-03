// Urho3D editor

#include "Scripts/Editor/EditorHierarchyWindow.as"
#include "Scripts/Editor/EditorView.as"
#include "Scripts/Editor/EditorScene.as"
#include "Scripts/Editor/EditorActions.as"
#include "Scripts/Editor/EditorUIElement.as"
#include "Scripts/Editor/EditorGizmo.as"
#include "Scripts/Editor/EditorMaterial.as"
#include "Scripts/Editor/EditorSettings.as"
#include "Scripts/Editor/EditorPreferences.as"
#include "Scripts/Editor/EditorToolBar.as"
#include "Scripts/Editor/EditorSecondaryToolbar.as"
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
    // Disable Editor auto exit, check first if it is OK to exit
    engine.autoExit = false;
    SubscribeToEvent(input, "ExitRequested", "HandleExitRequested");

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

    // Scan for a scene to load
    for (uint i = 1; i < arguments.length; ++i)
    {
        if (arguments[i].ToLower() == "-scene")
        {
            if (++i < arguments.length)
            {
                loaded = LoadScene(arguments[i]);
                break;
            }
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
    UpdateTestAnimation(timeStep);
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
    XMLElement viewElem = configElem.GetChild("view");
    XMLElement resourcesElem = configElem.GetChild("resources");

    if (!cameraElem.isNull)
    {
        if (cameraElem.HasAttribute("nearclip")) camera.nearClip = cameraElem.GetFloat("nearclip");
        if (cameraElem.HasAttribute("farclip")) camera.farClip = cameraElem.GetFloat("farclip");
        if (cameraElem.HasAttribute("fov")) camera.fov = cameraElem.GetFloat("fov");
        if (cameraElem.HasAttribute("speed")) cameraBaseSpeed = cameraElem.GetFloat("speed");
        if (cameraElem.HasAttribute("limitrotation")) limitRotation = cameraElem.GetBool("limitrotation");
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
        if (objectElem.HasAttribute("applymateriallist")) applyMaterialList = objectElem.GetBool("applymateriallist");
        if (objectElem.HasAttribute("importoptions")) importOptions = objectElem.GetAttribute("importoptions");
        if (objectElem.HasAttribute("pickmode")) pickMode = objectElem.GetInt("pickmode");
    }

    if (!resourcesElem.isNull)
    {
        if (resourcesElem.HasAttribute("rememberresourcepath")) rememberResourcePath = resourcesElem.GetBool("rememberresourcepath");
        if (rememberResourcePath && resourcesElem.HasAttribute("resourcepath"))
        {
            String newResourcePath = resourcesElem.GetAttribute("resourcepath");
            if (fileSystem.DirExists(newResourcePath))
                SetResourcePath(resourcesElem.GetAttribute("resourcepath"), false);
        }
        if (resourcesElem.HasAttribute("importpath"))
        {
            String newImportPath = resourcesElem.GetAttribute("importpath");
            if (fileSystem.DirExists(newImportPath))
                uiImportPath = newImportPath;
        }
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
        if (hierarchyElem.HasAttribute("showtemporaryobject")) showTemporaryObject = hierarchyElem.GetBool("showtemporaryobject");
        if (inspectorElem.HasAttribute("nodecolor")) nodeTextColor = inspectorElem.GetColor("nodecolor");
        if (inspectorElem.HasAttribute("componentcolor")) componentTextColor = inspectorElem.GetColor("componentcolor");
    }

    if (!inspectorElem.isNull)
    {
        if (inspectorElem.HasAttribute("originalcolor")) normalTextColor = inspectorElem.GetColor("originalcolor");
        if (inspectorElem.HasAttribute("modifiedcolor")) modifiedTextColor = inspectorElem.GetColor("modifiedcolor");
        if (inspectorElem.HasAttribute("noneditablecolor")) nonEditableTextColor = inspectorElem.GetColor("noneditablecolor");
        if (inspectorElem.HasAttribute("shownoneditable")) showNonEditableAttribute = inspectorElem.GetBool("shownoneditable");
    }

    if (!viewElem.isNull)
    {
        if (viewElem.HasAttribute("defaultzoneambientcolor")) renderer.defaultZone.ambientColor = viewElem.GetColor("defaultzoneambientcolor");
        if (viewElem.HasAttribute("defaultzonefogcolor")) renderer.defaultZone.fogColor = viewElem.GetColor("defaultzonefogcolor");
        if (viewElem.HasAttribute("defaultzonefogstart")) renderer.defaultZone.fogStart = viewElem.GetInt("defaultzonefogstart");
        if (viewElem.HasAttribute("defaultzonefogend")) renderer.defaultZone.fogEnd = viewElem.GetInt("defaultzonefogend");
        if (viewElem.HasAttribute("showgrid")) showGrid = viewElem.GetBool("showgrid");
        if (viewElem.HasAttribute("grid2dmode")) grid2DMode = viewElem.GetBool("grid2dmode");
        if (viewElem.HasAttribute("gridsize")) gridSize = viewElem.GetInt("gridsize");
        if (viewElem.HasAttribute("gridsubdivisions")) gridSubdivisions = viewElem.GetInt("gridsubdivisions");
        if (viewElem.HasAttribute("gridscale")) gridScale = viewElem.GetFloat("gridscale");
        if (viewElem.HasAttribute("gridcolor")) gridColor = viewElem.GetColor("gridcolor");
        if (viewElem.HasAttribute("gridsubdivisioncolor")) gridSubdivisionColor = viewElem.GetColor("gridsubdivisioncolor");
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
    XMLElement viewElem = configElem.CreateChild("view");
    XMLElement resourcesElem = configElem.CreateChild("resources");

    // The save config may be called on error exit so some of the objects below could still be null
    if (camera !is null)
    {
        cameraElem.SetFloat("nearclip", camera.nearClip);
        cameraElem.SetFloat("farclip", camera.farClip);
        cameraElem.SetFloat("fov", camera.fov);
        cameraElem.SetFloat("speed", cameraBaseSpeed);
        cameraElem.SetBool("limitrotation", limitRotation);
    }

    objectElem.SetFloat("newnodedistance", newNodeDistance);
    objectElem.SetFloat("movestep", moveStep);
    objectElem.SetFloat("rotatestep", rotateStep);
    objectElem.SetFloat("scalestep", scaleStep);
    objectElem.SetBool("movesnap", moveSnap);
    objectElem.SetBool("rotatesnap", rotateSnap);
    objectElem.SetBool("scalesnap", scaleSnap);
    objectElem.SetBool("applymateriallist", applyMaterialList);
    objectElem.SetAttribute("importoptions", importOptions);
    objectElem.SetInt("pickmode", pickMode);

    resourcesElem.SetBool("rememberresourcepath", rememberResourcePath);
    resourcesElem.SetAttribute("resourcepath", sceneResourcePath);
    resourcesElem.SetAttribute("importpath", uiImportPath);

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
    hierarchyElem.SetBool("showtemporaryobject", showTemporaryObject);
    inspectorElem.SetColor("nodecolor", nodeTextColor);
    inspectorElem.SetColor("componentcolor", componentTextColor);

    inspectorElem.SetColor("originalcolor", normalTextColor);
    inspectorElem.SetColor("modifiedcolor", modifiedTextColor);
    inspectorElem.SetColor("noneditablecolor", nonEditableTextColor);
    inspectorElem.SetBool("shownoneditable", showNonEditableAttribute);

    viewElem.SetBool("showgrid", showGrid);
    viewElem.SetBool("grid2dmode", grid2DMode);
    viewElem.SetColor("defaultzoneambientcolor", renderer.defaultZone.ambientColor);
    viewElem.SetColor("defaultzonefogcolor", renderer.defaultZone.fogColor);
    viewElem.SetFloat("defaultzonefogstart", renderer.defaultZone.fogStart);
    viewElem.SetFloat("defaultzonefogend", renderer.defaultZone.fogEnd);
    viewElem.SetInt("gridsize", gridSize);
    viewElem.SetInt("gridsubdivisions", gridSubdivisions);
    viewElem.SetFloat("gridscale", gridScale);
    viewElem.SetColor("gridcolor", gridColor);
    viewElem.SetColor("gridsubdivisioncolor", gridSubdivisionColor);

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
