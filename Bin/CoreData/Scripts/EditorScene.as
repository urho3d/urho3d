// Urho3D editor scene handling

#include "Scripts/EditorSceneWindow.as"
#include "Scripts/EditorComponentWindow.as"

Scene@ editorScene;
string sceneFileName;
string sceneResourcePath;
bool sceneModified = false;

Component@ selectedComponent;
Entity@ selectedEntity;

void createScene()
{
    // Create a scene with default values, these will be overridden when loading scenes
    @editorScene = engine.createScene("GraphicsTest", BoundingBox(-1000.0, 1000.0), 8, true);
    
    // Always pause the scene for now
    editorScene.setPaused(true);
    
    subscribeToEvent("PostRenderUpdate", "sceneRaycast");
}

void setResourcePath(string newPath)
{
    if (newPath == sceneResourcePath)
        return;

    cache.releaseAllResources(false);

    // Remove the old scene resource path if any. However make sure that CoreData path never gets removed
    if ((!sceneResourcePath.empty()) && (sceneResourcePath.find("CoreData") < 0))
        cache.removeResourcePath(sceneResourcePath);

    cache.addResourcePath(newPath);
    sceneResourcePath = newPath;
}

void loadScene(string fileName)
{
    // Always load the scene from the filesystem, not from resource paths
    if (!fileExists(fileName))
    {
        logError("No such scene " + fileName);
        return;
    }

    // Clear the old scene
    @selectedComponent = null;
    @selectedEntity = null;
    editorScene.removeAllEntities();

    // Add the new resource path
    setResourcePath(getPath(fileName));

    File file(fileName, FILE_READ);
    string extension = getExtension(fileName);
    if ((extension == ".bin") || (extension == ".sav"))
        editorScene.load(file);
    else
        editorScene.loadXML(file);
        
    sceneFileName = fileName;
    sceneModified = false;
    updateWindowTitle();
    updateSceneWindow(false);
    resetCamera();
}

void saveScene(string fileName)
{
    if ((fileName.empty()) || (getFileName(fileName).empty()))
        return;

    File file(fileName, FILE_WRITE);
    string extension = getExtension(fileName);
    if ((extension == ".bin") || (extension == ".sav"))
        editorScene.save(file);
    else
        editorScene.saveXML(file);

    sceneFileName = fileName;
    sceneModified = false;
    updateWindowTitle();
}

void beginModify(uint entityID)
{
    // Undo/Redo can be implemented here
}

void endModify(uint entityID)
{
    // Undo/Redo can be implemented here

    if (!sceneModified)
    {
        sceneModified = true;
        updateWindowTitle();
    }
}

string getEntityTitle(Entity@ entity)
{
    string name = entity.getName();
    if (name.empty())
        return "Entity (" + entity.getID() + ")";
    else
        return name + " (" + entity.getID() + ")";
}

string getComponentTitle(Component@ component, int indent)
{
    string indentStr;
    indentStr.resize(indent);
    for (int i = 0; i < indent; ++i)
        indentStr[i] = ' ';

    string name = component.getName();
    if (name.empty())
        return indentStr + component.getTypeName();
    else
        return indentStr + component.getTypeName() + " (" + name + ")";
}

void sceneRaycast()
{
    DebugRenderer@ debug = editorScene.getDebugRenderer();
    IntVector2 pos = ui.getCursorPosition();

    // Visualize current selection (either renderables or rigidbodies can be visualized)
    if (selectedComponent !is null)
    {
        VolumeNode@ node = cast<VolumeNode>(selectedComponent);
        if (node !is null)
            node.drawDebugGeometry(debug, false);
        else
        {
            RigidBody@ body = cast<RigidBody>(selectedComponent);
            if (body !is null)
                body.drawDebugGeometry(debug, false);
        }
    }

    //! \todo allow to switch between renderer and physics raycast
    if (ui.getElementAt(pos, true) is null)
    {
        Ray cameraRay = camera.getScreenRay(float(pos.x) / renderer.getWidth(), float(pos.y) / renderer.getHeight());
        array<RayQueryResult> result = editorScene.getOctree().raycast(cameraRay, NODE_GEOMETRY, camera.getFarClip(), RAY_TRIANGLE);
        GeometryNode@ node;
        if (!result.empty())
        {
            @node = result[0].node;
            node.drawDebugGeometry(debug, false);
        }
        if (input.getMouseButtonPress(MOUSEB_LEFT))
            selectComponent(node);
    }
}

