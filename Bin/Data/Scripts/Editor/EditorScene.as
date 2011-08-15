// Urho3D editor scene handling

#include "Scripts/Editor/EditorSceneWindow.as"
#include "Scripts/Editor/EditorNodeWindow.as"

Scene@ editorScene;

String sceneFileName;
String sceneResourcePath;
bool sceneModified = false;
bool runPhysics = false;
bool renderingDebug = false;
bool physicsDebug = false;
bool octreeDebug = false;
bool subscribedToSceneSettingsEdits = false;

Component@ selectedComponent;
Node@ selectedNode;

void CreateScene()
{
    selectedComponent = null;
    selectedNode = null;

    // Create a scene with default values, these will be overridden when loading scenes
    editorScene = Scene("Urho3D Editor");
    Octree@ octree = editorScene.CreateComponent("Octree");
    PhysicsWorld@ physicsWorld = editorScene.CreateComponent("PhysicsWorld");
    octree.Resize(BoundingBox(-1000.0, 1000.0), 8);
    editorScene.CreateComponent("DebugRenderer");

    // Always pause the scene for now
    editorScene.active = false;

    if (sceneWindow !is null)
    {
        UpdateSceneWindow(false);
        UpdateNodeWindow();
    }

    runPhysics = false;
    sceneFileName = "";
    UpdateWindowTitle();
    CreateCamera();

    SubscribeToEvent("PostRenderUpdate", "ScenePostRenderUpdate");
    SubscribeToEvent("UIMouseClick", "SceneMouseClick");

    script.defaultScene = editorScene;
}

void SetResourcePath(String newPath)
{
    newPath = AddTrailingSlash(newPath);

    if (newPath == sceneResourcePath)
        return;

    cache.ReleaseAllResources(false);

    // Remove the old scene resource path if any. However make sure that CoreData path never gets removed
    if (!sceneResourcePath.empty && sceneResourcePath.Find("CoreData") < 0)
        cache.RemoveResourceDir(sceneResourcePath);

    cache.AddResourceDir(newPath);
    sceneResourcePath = newPath;
    
    // If scenes were not loaded yet, default load/save to the resource path
    if (uiScenePath.empty)
        uiScenePath = newPath;
}

Array<Resource@> GetSceneResources()
{
    Array<Resource@> sceneResources;
    Array<Node@> allNodes = editorScene.GetChildren(true);

    for (uint i = 0; i < allNodes.length; ++i)
    {
        for (uint j = 0; j < allNodes[i].numComponents; ++j)
        {
            Component@ comp = allNodes[i].components[j];
            for (uint k = 0; k < comp.numAttributes; ++k)
            {
                Variant attr = comp.attributes[k];
                if (attr.type == VAR_RESOURCEREF)
                {
                    ResourceRef ref = attr.GetResourceRef();
                    Resource@ resource = cache.GetResource(ref.type, ref.id);
                    if (resource !is null)
                        AddResourceIfUnique(sceneResources, resource);
                }
                else if (attr.type == VAR_RESOURCEREFLIST)
                {
                    ResourceRefList refList = attr.GetResourceRefList();
                    for (uint l = 0; l < refList.length; ++l)
                    {
                        Resource@ resource = cache.GetResource(refList.type, refList.ids[l]);
                        if (resource !is null)
                            AddResourceIfUnique(sceneResources, resource);
                    }
                }
            }
        }
    }

    return sceneResources;
}

void AddResourceIfUnique(Array<Resource@>@ sceneResources, Resource@ resource)
{
    for (uint i = 0; i < sceneResources.length; ++i)
    {
        if (sceneResources[i] is resource)
            return;
    }
    sceneResources.Push(resource);
}

void ReloadResources()
{
    Array<Resource@> sceneResources = GetSceneResources();
    for (uint i = 0; i < sceneResources.length; ++i)
    {
        // Handle material textures manually
        Material@ mat = cast<Material>(sceneResources[i]);
        if (mat !is null)
        {
            for (int j = 0; j < MAX_MATERIAL_TEXTURE_UNITS; ++j)
            {
                Texture@ tex = mat.textures[j];
                if (tex !is null)
                    AddResourceIfUnique(sceneResources, tex);
            }
        }
    }

    Print("Reloading resources");
    for (uint i = 0; i < sceneResources.length; ++i)
        cache.ReloadResource(sceneResources[i]);
}

void LoadScene(const String&in fileName)
{
    // Always load the scene from the filesystem, not from resource paths
    if (!fileSystem.FileExists(fileName))
    {
        log.Error("No such scene " + fileName);
        return;
    }

    File file(fileName, FILE_READ);
    if (!file.open)
        return;

    // Clear the old scene
    selectedComponent = null;
    selectedNode = null;
    editorScene.Clear();

    // Add the new resource path
    SetResourcePath(cache.GetPreferredResourceDir(GetPath(fileName)));

    String extension = GetExtension(fileName);
    if (extension != ".xml")
        editorScene.Load(file);
    else
        editorScene.LoadXML(file);

    sceneFileName = fileName;
    sceneModified = false;
    runPhysics = false;
    UpdateWindowTitle();
    UpdateSceneWindow(false);
    UpdateNodeWindow();
    ResetCamera();
}

void SaveScene(const String&in fileName)
{
    if (fileName.empty || GetFileName(fileName).empty)
        return;

    editorScene.name = GetFileName(fileName);

    File file(fileName, FILE_WRITE);
    String extension = GetExtension(fileName);
    if (extension != ".xml")
        editorScene.Save(file);
    else
        editorScene.SaveXML(file);

    sceneFileName = fileName;
    sceneModified = false;
    UpdateWindowTitle();
}

void BeginModify(uint nodeID)
{
    // Undo/Redo can be implemented here
}

void EndModify(uint nodeID)
{
    // Undo/Redo can be implemented here

    if (!sceneModified)
    {
        sceneModified = true;
        UpdateWindowTitle();
    }
}

String GetNodeTitle(Node@ node, int indent)
{
    String indentStr;
    String localStr;
    indentStr.Resize(indent);
    for (int i = 0; i < indent; ++i)
        indentStr[i] = ' ';
    
    if (node.id >= FIRST_LOCAL_ID)
        localStr = " (LOCAL)";

    if (node.name.empty)
        return indentStr + "Node " + node.id + localStr;
    else
        return indentStr + node.name + localStr;
}

String GetComponentTitle(Component@ component, int indent)
{
    String indentStr;
    String localStr;
    indentStr.Resize(indent);
    for (int i = 0; i < indent; ++i)
        indentStr[i] = ' ';
    
    if (node.id >= FIRST_LOCAL_ID)
        localStr = " (LOCAL)";

    return indentStr + component.typeName + localStr;
}

void ScenePostRenderUpdate()
{
    DebugRenderer@ debug = editorScene.debugRenderer;
    
    // Visualize current selection (either drawables or collisionshapes can be visualized)
    if (selectedComponent !is null)
    {
        Drawable@ drawable = cast<Drawable>(selectedComponent);
        if (drawable !is null)
            drawable.DrawDebugGeometry(debug, false);
        else
        {
            CollisionShape@ shape = cast<CollisionShape>(selectedComponent);
            if (shape !is null)
                shape.DrawDebugGeometry(debug, false);
        }
    }
    
    if (renderingDebug)
        renderer.DrawDebugGeometry(false);
    if (physicsDebug)
        editorScene.physicsWorld.DrawDebugGeometry(true);
    if (octreeDebug)
        editorScene.octree.DrawDebugGeometry(true);
    
    SceneRaycast(false);
}

void SceneMouseClick()
{
    SceneRaycast(true);
}

void SceneRaycast(bool mouseClick)
{
    DebugRenderer@ debug = editorScene.debugRenderer;
    IntVector2 pos = ui.cursorPosition;

    /// \todo allow to switch between renderer and physics raycast
    if (ui.GetElementAt(pos, true) is null)
    {
        Ray cameraRay = camera.GetScreenRay(float(pos.x) / graphics.width, float(pos.y) / graphics.height);
        Array<RayQueryResult> result = editorScene.octree.Raycast(cameraRay, RAY_TRIANGLE, camera.farClip, DRAWABLE_GEOMETRY);
        Drawable@ drawable;
        if (!result.empty)
        {
            drawable = result[0].drawable;
            drawable.DrawDebugGeometry(debug, false);
        }
        if (mouseClick && input.mouseButtonPress[MOUSEB_LEFT])
            SelectComponent(drawable);
    }
}

void ToggleRenderingDebug()
{
    renderingDebug = !renderingDebug;
}

void TogglePhysicsDebug()
{
    physicsDebug = !physicsDebug;
}

void ToggleOctreeDebug()
{
    octreeDebug = !octreeDebug;
}

void TogglePhysics()
{
    runPhysics = !runPhysics;
}
