// Urho3D editor

#include "Scripts/Editor/EditorCamera.as"
#include "Scripts/Editor/EditorScene.as"
#include "Scripts/Editor/EditorUI.as"
#include "Scripts/Editor/EditorImport.as"

String configFileName;

void Start()
{
    if (engine.headless)
    {
        ErrorDialog("Urho3D Editor", "Headless mode is not supported. The program will now exit.");
        engine.Exit();
        return;
    }

    configFileName = fileSystem.userDocumentsDir + "Urho3D/Editor/Config.xml";

    // Enable console commands from the editor script
    script.defaultScriptFile = scriptFile;

    SubscribeToEvent("Update", "HandleUpdate");

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

    MoveCamera(timeStep);
    UpdateStats(timeStep);
    UpdateScene(timeStep);
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
    if (cameraElem.isNull || objectElem.isNull)
        return;

    camera.nearClip = cameraElem.GetFloat("nearclip");
    camera.farClip = cameraElem.GetFloat("farclip");
    camera.fov = cameraElem.GetFloat("fov");
    cameraBaseSpeed = cameraElem.GetFloat("speed");

    newNodeDistance = objectElem.GetFloat("newnodedistance");
    moveStep = objectElem.GetFloat("movestep");
    rotateStep = objectElem.GetFloat("rotatestep");
    scaleStep = objectElem.GetFloat("scalestep");
    moveSnap = objectElem.GetBool("movesnap");
    rotateSnap = objectElem.GetBool("rotatesnap");
    scaleSnap = objectElem.GetBool("scalesnap");
    useLocalIDs = objectElem.GetBool("uselocalids");
}

void SaveConfig()
{
    fileSystem.CreateDir(fileSystem.userDocumentsDir + "Urho3D");
    fileSystem.CreateDir(fileSystem.userDocumentsDir + "Urho3D/Editor");

    XMLFile config;
    XMLElement configElem = config.CreateRoot("configuration");
    XMLElement cameraElem = configElem.CreateChild("camera");
    XMLElement objectElem = configElem.CreateChild("object");

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

    config.Save(File(configFileName, FILE_WRITE));
}