// Urho3D editor

#include "Scripts/EditorCamera.as"
#include "Scripts/EditorScene.as"
#include "Scripts/EditorUI.as"
#include "Scripts/EditorImport.as"

string configFileName;

void start()
{
    if (engine.isHeadless())
    {
        errorDialog("Urho3D Editor", "Headless mode is not supported. The program will now exit.");
        engine.exit();
        return;
    }

    configFileName = getUserDocumentsDirectory() + "Urho3D/Editor/Config.xml";

    // Free the mouse cursor
    input.setClipCursor(false);

    // Enable console commands from the editor script
    engine.setDefaultScriptFile(scriptFile);
    
    subscribeToEvent("Update", "handleUpdate");

    createScene();
    createUI();
    loadConfig();
    parseArguments();
}

void stop()
{
    saveConfig();
}

void parseArguments()
{
    array<string> arguments = getArguments();

    // The first argument should be the editor script name. Scan for a scene to load
    for (uint i = 1; i < arguments.size(); ++i)
    {
        if (arguments[i][0] != '-')
        {
            loadScene(getAbsoluteFileName(arguments[i]));
            break;
        }
    }
}

void handleUpdate(StringHash eventType, VariantMap& eventData)
{
    float timeStep = eventData["TimeStep"].getFloat();

    moveCamera(timeStep);
    updateStats(timeStep);

    if (runPhysics)
        editorScene.getPhysicsWorld().update(timeStep);
}

void loadConfig()
{
    if (!fileExists(configFileName))
        return;

    XMLFile config;
    config.load(File(configFileName, FILE_READ));

    XMLElement configElem = config.getRootElement("configuration");
    if (configElem.isNull())
        return;

    XMLElement cameraElem = configElem.getChildElement("camera");
    XMLElement objectElem = configElem.getChildElement("object");
    if ((cameraElem.isNull()) || (objectElem.isNull()))
        return;

    camera.setNearClip(cameraElem.getFloat("nearclip"));
    camera.setFarClip(cameraElem.getFloat("farclip"));
    camera.setFov(cameraElem.getFloat("fov"));
    cameraBaseSpeed = cameraElem.getFloat("speed");

    newNodeDistance = objectElem.getFloat("newnodedistance");
    moveStep = objectElem.getFloat("movestep");
    rotateStep = objectElem.getFloat("rotatestep");
    scaleStep = objectElem.getFloat("scalestep");
    moveSnap = objectElem.getBool("movesnap");
    rotateSnap = objectElem.getBool("rotatesnap");
    scaleSnap = objectElem.getBool("scalesnap");
    useLocalIDs = objectElem.getBool("uselocalids");
}

void saveConfig()
{
    if (configFileName.empty())
        return;

    createDirectory(getUserDocumentsDirectory() + "Urho3D/Editor");

    XMLFile config;
    XMLElement configElem = config.createRootElement("configuration");
    XMLElement cameraElem = configElem.createChildElement("camera");
    XMLElement objectElem = configElem.createChildElement("object");

    cameraElem.setFloat("nearclip", camera.getNearClip());
    cameraElem.setFloat("farclip", camera.getFarClip());
    cameraElem.setFloat("fov", camera.getFov());
    cameraElem.setFloat("speed", cameraBaseSpeed);

    objectElem.setFloat("newnodedistance", newNodeDistance);
    objectElem.setFloat("movestep", moveStep);
    objectElem.setFloat("rotatestep", rotateStep);
    objectElem.setFloat("scalestep", scaleStep);
    objectElem.setBool("movesnap", moveSnap);
    objectElem.setBool("rotatesnap", rotateSnap);
    objectElem.setBool("scalesnap", scaleSnap);
    objectElem.setBool("uselocalids", useLocalIDs);

    config.save(File(configFileName, FILE_WRITE));
}