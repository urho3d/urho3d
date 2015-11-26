// Urho3D editor

#include "Scripts/Editor/EditorHierarchyWindow.as"
#include "Scripts/Editor/EditorView.as"
#include "Scripts/Editor/EditorScene.as"
#include "Scripts/Editor/EditorActions.as"
#include "Scripts/Editor/EditorUIElement.as"
#include "Scripts/Editor/EditorGizmo.as"
#include "Scripts/Editor/EditorMaterial.as"
#include "Scripts/Editor/EditorParticleEffect.as"
#include "Scripts/Editor/EditorSettings.as"
#include "Scripts/Editor/EditorPreferences.as"
#include "Scripts/Editor/EditorToolBar.as"
#include "Scripts/Editor/EditorSecondaryToolbar.as"
#include "Scripts/Editor/EditorUI.as"
#include "Scripts/Editor/EditorImport.as"
#include "Scripts/Editor/EditorExport.as"
#include "Scripts/Editor/EditorResourceBrowser.as"
#include "Scripts/Editor/EditorSpawn.as"
#include "Scripts/Editor/EditorSoundType.as"
#include "Scripts/Editor/EditorLayers.as"
#include "Scripts/Editor/EditorColorWheel.as"
#include "Scripts/Editor/EditorEventsHandlers.as"
#include "Scripts/Editor/EditorViewDebugIcons.as"

String configFileName;

void Start()
{
    // Assign the value ASAP because configFileName is needed on exit, including exit on error
    configFileName = fileSystem.GetAppPreferencesDir("urho3d", "Editor") + "Config.xml";
    localization.LoadJSONFile("EditorStrings.json");

    if (engine.headless)
    {
        ErrorDialog("Urho3D Editor", "Headless mode is not supported. The program will now exit.");
        engine.Exit();
        return;
    }

    // Use the first frame to setup when the resolution is initialized
    SubscribeToEvent("Update", "FirstFrame");

    SubscribeToEvent(input, "ExitRequested", "HandleExitRequested");

    // Disable Editor auto exit, check first if it is OK to exit
    engine.autoExit = false;
    // Enable console commands from the editor script
    script.defaultScriptFile = scriptFile;
    // Enable automatic resource reloading
    cache.autoReloadResources = true;
    // Return resources which exist but failed to load due to error, so that we will not lose resource refs
    cache.returnFailedResources = true;
    // Use OS mouse without grabbing it
    input.mouseVisible = true;
    // Use system clipboard to allow transport of text in & out from the editor
    ui.useSystemClipboard = true;
}

void FirstFrame()
{
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
    // Switch to real frame handler after initialization
    SubscribeToEvent("Update", "HandleUpdate");
    SubscribeToEvent("ReloadFinished", "HandleReloadFinished");
    SubscribeToEvent("ReloadFailed", "HandleReloadFailed");
    EditorSubscribeToEvents();
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
        if (arguments[i].ToLower() == "-language")
        {
            if (++i < arguments.length)
            {
                localization.SetLanguage(arguments[i]);
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

    DoResourceBrowserWork();
    UpdateView(timeStep);
    UpdateViewports(timeStep);
    UpdateStats(timeStep);
    UpdateScene(timeStep);
    UpdateTestAnimation(timeStep);
    UpdateGizmo();
    UpdateDirtyUI();
    UpdateViewDebugIcons();

    // Handle Particle Editor looping.
    if (particleEffectWindow !is null and particleEffectWindow.visible)
    {
        if (!particleEffectEmitter.emitting)
        {
            if (particleResetTimer == 0.0f)
                particleResetTimer = editParticleEffect.maxTimeToLive + 0.2f;
            else
            {
                particleResetTimer = Max(particleResetTimer - timeStep, 0.0f);
                if (particleResetTimer <= 0.0001f)
                {
                    particleEffectEmitter.Reset();
                    particleResetTimer = 0.0f;
                }
            }
        }
    }
}

void HandleReloadFinished(StringHash eventType, VariantMap& eventData)
{
    attributesFullDirty = true;
}

void HandleReloadFailed(StringHash eventType, VariantMap& eventData)
{
    attributesFullDirty = true;
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
    XMLElement consoleElem = configElem.GetChild("console");
    XMLElement varNamesElem = configElem.GetChild("varnames");
    XMLElement soundTypesElem = configElem.GetChild("soundtypes");
    XMLElement cubeMapElem = configElem.GetChild("cubegen");

    if (!cameraElem.isNull)
    {
        if (cameraElem.HasAttribute("nearclip")) viewNearClip = cameraElem.GetFloat("nearclip");
        if (cameraElem.HasAttribute("farclip")) viewFarClip = cameraElem.GetFloat("farclip");
        if (cameraElem.HasAttribute("fov")) viewFov = cameraElem.GetFloat("fov");
        if (cameraElem.HasAttribute("speed")) cameraBaseSpeed = cameraElem.GetFloat("speed");
        if (cameraElem.HasAttribute("limitrotation")) limitRotation = cameraElem.GetBool("limitrotation");
        if (cameraElem.HasAttribute("mousewheelcameraposition")) mouseWheelCameraPosition = cameraElem.GetBool("mousewheelcameraposition");
        if (cameraElem.HasAttribute("viewportmode")) viewportMode = cameraElem.GetUInt("viewportmode");
        if (cameraElem.HasAttribute("mouseorbitmode")) mouseOrbitMode = cameraElem.GetInt("mouseorbitmode");
        if (cameraElem.HasAttribute("mmbpan")) mmbPanMode = cameraElem.GetBool("mmbpan");
        UpdateViewParameters();
    }

    if (!objectElem.isNull)
    {
        if (objectElem.HasAttribute("cameraflymode")) cameraFlyMode = objectElem.GetBool("cameraflymode");
        if (objectElem.HasAttribute("hotkeymode")) hotKeyMode = objectElem.GetInt("hotkeymode");
        if (objectElem.HasAttribute("newnodemode")) newNodeMode = objectElem.GetInt("newnodemode");
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
        if (objectElem.HasAttribute("axismode")) axisMode = AxisMode(objectElem.GetInt("axismode"));
        if (objectElem.HasAttribute("revertonpause")) revertOnPause = objectElem.GetBool("revertonpause");
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
        if (resourcesElem.HasAttribute("recentscenes"))
        {
            uiRecentScenes = resourcesElem.GetAttribute("recentscenes").Split(';');
        }
    }

    if (!renderingElem.isNull)
    {
        if (renderingElem.HasAttribute("renderpath")) renderPathName = renderingElem.GetAttribute("renderpath");
        if (renderingElem.HasAttribute("texturequality")) renderer.textureQuality = renderingElem.GetInt("texturequality");
        if (renderingElem.HasAttribute("materialquality")) renderer.materialQuality = renderingElem.GetInt("materialquality");
        if (renderingElem.HasAttribute("shadowresolution")) SetShadowResolution(renderingElem.GetInt("shadowresolution"));
        if (renderingElem.HasAttribute("shadowquality")) renderer.shadowQuality = renderingElem.GetInt("shadowquality");
        if (renderingElem.HasAttribute("maxoccludertriangles")) renderer.maxOccluderTriangles = renderingElem.GetInt("maxoccludertriangles");
        if (renderingElem.HasAttribute("specularlighting")) renderer.specularLighting = renderingElem.GetBool("specularlighting");
        if (renderingElem.HasAttribute("dynamicinstancing")) renderer.dynamicInstancing = renderingElem.GetBool("dynamicinstancing");
        if (renderingElem.HasAttribute("framelimiter")) engine.maxFps = renderingElem.GetBool("framelimiter") ? 200 : 0;
    }

    if (!uiElem.isNull)
    {
        if (uiElem.HasAttribute("minopacity")) uiMinOpacity = uiElem.GetFloat("minopacity");
        if (uiElem.HasAttribute("maxopacity")) uiMaxOpacity = uiElem.GetFloat("maxopacity");
        if (uiElem.HasAttribute("languageindex")) localization.SetLanguage(uiElem.GetInt("languageindex"));
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

    if (!consoleElem.isNull)
    {
        // Console does not exist yet at this point, so store the string in a global variable
        if (consoleElem.HasAttribute("commandinterpreter")) consoleCommandInterpreter = consoleElem.GetAttribute("commandinterpreter");
    }

    if (!varNamesElem.isNull)
        globalVarNames = varNamesElem.GetVariantMap();

    if (!soundTypesElem.isNull)
        LoadSoundTypes(soundTypesElem);

    if (!cubeMapElem.isNull)
    {
        cubeMapGen_Name = cubeMapElem.HasAttribute("name") ? cubeMapElem.GetAttribute("name") : "";
        cubeMapGen_Path = cubeMapElem.HasAttribute("path") ? cubeMapElem.GetAttribute("path") : cubemapDefaultOutputPath;
        cubeMapGen_Size = cubeMapElem.HasAttribute("size") ? cubeMapElem.GetInt("size") : 128;
    }
    else
    {
        cubeMapGen_Name = "";
        cubeMapGen_Path = cubemapDefaultOutputPath;
        cubeMapGen_Size = 128;
    }
}

void SaveConfig()
{
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
    XMLElement consoleElem = configElem.CreateChild("console");
    XMLElement varNamesElem = configElem.CreateChild("varnames");
    XMLElement soundTypesElem = configElem.CreateChild("soundtypes");
    XMLElement cubeGenElem = configElem.CreateChild("cubegen");

    cameraElem.SetFloat("nearclip", viewNearClip);
    cameraElem.SetFloat("farclip", viewFarClip);
    cameraElem.SetFloat("fov", viewFov);
    cameraElem.SetFloat("speed", cameraBaseSpeed);
    cameraElem.SetBool("limitrotation", limitRotation);
    cameraElem.SetBool("mousewheelcameraposition", mouseWheelCameraPosition);
    cameraElem.SetUInt("viewportmode", viewportMode);
    cameraElem.SetInt("mouseorbitmode", mouseOrbitMode);
    cameraElem.SetBool("mmbpan", mmbPanMode);

    objectElem.SetBool("cameraflymode", cameraFlyMode);
    objectElem.SetInt("hotkeymode", hotKeyMode);
    objectElem.SetInt("newnodemode", newNodeMode);
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
    objectElem.SetInt("axismode", axisMode);
    objectElem.SetBool("revertonpause", revertOnPause);

    resourcesElem.SetBool("rememberresourcepath", rememberResourcePath);
    resourcesElem.SetAttribute("resourcepath", sceneResourcePath);
    resourcesElem.SetAttribute("importpath", uiImportPath);
    resourcesElem.SetAttribute("recentscenes", Join(uiRecentScenes, ";"));

    if (renderer !is null && graphics !is null)
    {
        renderingElem.SetAttribute("renderpath", renderPathName);
        renderingElem.SetInt("texturequality", renderer.textureQuality);
        renderingElem.SetInt("materialquality", renderer.materialQuality);
        renderingElem.SetInt("shadowresolution", GetShadowResolution());
        renderingElem.SetInt("maxoccludertriangles", renderer.maxOccluderTriangles);
        renderingElem.SetBool("specularlighting", renderer.specularLighting);
        renderingElem.SetInt("shadowquality", renderer.shadowQuality);
        renderingElem.SetBool("dynamicinstancing", renderer.dynamicInstancing);
    }

    renderingElem.SetBool("framelimiter", engine.maxFps > 0);

    uiElem.SetFloat("minopacity", uiMinOpacity);
    uiElem.SetFloat("maxopacity", uiMaxOpacity);
    uiElem.SetInt("languageindex", localization.languageIndex);

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

    consoleElem.SetAttribute("commandinterpreter", console.commandInterpreter);

    varNamesElem.SetVariantMap(globalVarNames);
    
    cubeGenElem.SetAttribute("name", cubeMapGen_Name);
    cubeGenElem.SetAttribute("path", cubeMapGen_Path);
    cubeGenElem.SetAttribute("size", cubeMapGen_Size);

    SaveSoundTypes(soundTypesElem);

    config.Save(File(configFileName, FILE_WRITE));
}

void MakeBackup(const String&in fileName)
{
    fileSystem.Rename(fileName, fileName + ".old");
}

void RemoveBackup(bool success, const String&in fileName)
{
    if (success)
        fileSystem.Delete(fileName + ".old");
}
