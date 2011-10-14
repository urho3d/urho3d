// Urho3D editor scene handling

#include "Scripts/Editor/EditorSceneWindow.as"
#include "Scripts/Editor/EditorNodeWindow.as"

const int PICK_GEOMETRIES = 0;
const int PICK_LIGHTS = 1;
const int PICK_ZONES = 2;
const int PICK_COLLISIONSHAPES = 3;
const int MAX_PICK_MODES = 4;

Scene@ editorScene;

String sceneFileName;
String sceneResourcePath;
bool sceneModified = false;
bool runUpdate = false;
bool renderingDebug = false;
bool physicsDebug = false;
bool octreeDebug = false;
int pickMode = PICK_GEOMETRIES;

Array<Node@> selectedNodes;
Array<Component@> selectedComponents;
Node@ editNode;
Array<Node@> editNodes;
Array<Component@> editComponents;

Array<int> pickModeDrawableFlags = {
    DRAWABLE_GEOMETRY,
    DRAWABLE_LIGHT,
    DRAWABLE_ZONE
};

void ClearSelection()
{
    selectedNodes.Clear();
    selectedComponents.Clear();
    editNode = null;
    editNodes.Clear();
    editComponents.Clear();
}

void CreateScene()
{
    ClearSelection();

    // Create a scene with default values, these will be overridden when loading scenes
    editorScene = Scene("");
    Octree@ octree = editorScene.CreateComponent("Octree");
    PhysicsWorld@ physicsWorld = editorScene.CreateComponent("PhysicsWorld");
    octree.Resize(BoundingBox(-1000.0, 1000.0), 8);
    editorScene.CreateComponent("DebugRenderer");

    // Always pause the scene, and do updates manually
    editorScene.active = false;

    if (sceneWindow !is null)
    {
        UpdateSceneWindow();
        UpdateNodeWindow();
    }

    runUpdate = false;
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

    // Remove the old scene resource path if any. However make sure that the default data paths do not get removed
    if (!sceneResourcePath.empty && sceneResourcePath.Find(fileSystem.programDir) < 0)
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
                else if (attr.type == VAR_VARIANTVECTOR)
                {
                    Array<Variant>@ variants = attr.GetVariantVector();
                    for (uint l = 0; l < variants.length; ++l)
                    {
                        if (variants[l].type == VAR_RESOURCEREF)
                        {
                            ResourceRef ref = variants[l].GetResourceRef();
                            Resource@ resource = cache.GetResource(ref.type, ref.id);
                            if (resource !is null)
                                AddResourceIfUnique(sceneResources, resource);
                        }
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
    ClearSelection();
    ClearSceneWindow();
    editorScene.Clear();

    // Add the new resource path
    SetResourcePath(cache.GetPreferredResourceDir(GetPath(fileName)));

    String extension = GetExtension(fileName);
    if (extension != ".xml")
        editorScene.Load(file);
    else
        editorScene.LoadXML(file);

    // Always pause the scene, and do updates manually
    editorScene.active = false;

    sceneFileName = fileName;
    sceneModified = false;
    runUpdate = false;
    UpdateWindowTitle();
    UpdateSceneWindow();
    UpdateNodeWindow();
    ResetCamera();
}

void SaveScene(const String&in fileName)
{
    if (fileName.empty || GetFileName(fileName).empty)
        return;

    // Unpause when saving so that there are no surprises when trying to use the scene
    editorScene.active = true;

    File file(fileName, FILE_WRITE);
    String extension = GetExtension(fileName);
    if (extension != ".xml")
        editorScene.Save(file);
    else
        editorScene.SaveXML(file);

    editorScene.active = false;

    sceneFileName = fileName;
    sceneModified = false;
    UpdateWindowTitle();
}

void UpdateScene(float timeStep)
{
    if (runUpdate)
        editorScene.Update(timeStep);
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

void ScenePostRenderUpdate()
{
    DebugRenderer@ debug = editorScene.debugRenderer;
    if (debug is null)
        return;

    // Visualize the currently selected nodes as their local axes + the first drawable component
    for (uint i = 0; i < selectedNodes.length; ++i)
    {
        Node@ node = selectedNodes[i];
        debug.AddNode(node, false);
        for (uint j = 0; j < node.numComponents; ++j)
        {
            Drawable@ drawable = cast<Drawable>(node.components[j]);
            if (drawable !is null)
            {
                drawable.DrawDebugGeometry(debug, false);
                break;
            }
        }
    }

    // Visualize the currently selected components
    for (uint i = 0; i < selectedComponents.length; ++i)
    {
        Drawable@ drawable = cast<Drawable>(selectedComponents[i]);
        if (drawable !is null)
            drawable.DrawDebugGeometry(debug, false);
        else
        {
            CollisionShape@ shape = cast<CollisionShape>(selectedComponents[i]);
            if (shape !is null)
                shape.DrawDebugGeometry(debug, false);
        }
    }

    if (renderingDebug)
        renderer.DrawDebugGeometry(false);
    if (physicsDebug && editorScene.physicsWorld !is null)
        editorScene.physicsWorld.DrawDebugGeometry(true);
    if (octreeDebug && editorScene.octree !is null)
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
    Component@ selected;

    if (ui.GetElementAt(pos, true) is null)
    {
        Ray cameraRay = camera.GetScreenRay(float(pos.x) / graphics.width, float(pos.y) / graphics.height);

        if (pickMode != PICK_COLLISIONSHAPES)
        {
            if (editorScene.octree is null)
                return;

            Array<RayQueryResult> result = editorScene.octree.Raycast(cameraRay, RAY_TRIANGLE, camera.farClip,
                pickModeDrawableFlags[pickMode]);
            if (!result.empty)
            {
                for (uint i = 0; i < result.length; ++i)
                {
                    Drawable@ drawable = result[i].drawable;
                    // Skip directional lights, which always block other selections
                    Light@ light = cast<Light>(drawable);
                    if (light !is null && light.lightType == LIGHT_DIRECTIONAL)
                        continue;
                    if (debug !is null)
                    {
                        debug.AddNode(drawable.node, false);
                        drawable.DrawDebugGeometry(debug, false);
                    }
                    selected = drawable;
                    break;
                }
            }
        }
        else
        {
            if (editorScene.physicsWorld is null)
                return;

            Array<PhysicsRaycastResult> result = editorScene.physicsWorld.Raycast(cameraRay, camera.farClip);
            if (!result.empty)
            {
                CollisionShape@ shape = result[0].collisionShape;
                if (debug !is null)
                {
                    debug.AddNode(shape.node, false);
                    shape.DrawDebugGeometry(debug, false);
                }
                selected = shape;
            }
        }
    }
    
    if (selected !is null && mouseClick && input.mouseButtonPress[MOUSEB_LEFT])
    {
        bool multiselect = input.qualifierDown[QUAL_CTRL];
        if (input.qualifierDown[QUAL_SHIFT])
        {
            // If we are selecting components, but have nodes in existing selection, do not multiselect to prevent confusion
            if (!selectedNodes.empty)
                multiselect = false;
            SelectComponent(selected, multiselect);
        }
        else
        {
            // If we are selecting nodes, but have components in existing selection, do not multiselect to prevent confusion
            if (!selectedComponents.empty)
                multiselect = false;
            SelectNode(selected.node, multiselect);
        }
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

void ToggleUpdate()
{
    runUpdate  = !runUpdate;
}
