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

Array<Node@> selectedNodes;
Array<Component@> selectedComponents;
Node@ editNode;
Array<Node@> editNodes;
Array<Component@> editComponents;

Array<XMLFile@> copyBuffer;
bool copyBufferLocal = false;
bool copyBufferExpanded = false;

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

bool SceneDelete()
{
    if (!CheckSceneWindowFocus() || (selectedComponents.empty && selectedNodes.empty))
        return false;

    ListView@ list = sceneWindow.GetChild("NodeList", true);

    // Remove components first
    for (uint i = 0; i < selectedComponents.length; ++i)
    {
        // Do not allow to remove the Octree, PhysicsWorld or DebugRenderer from the root node
        Component@ component = selectedComponents[i];
        Node@ node = component.node;
        
        uint index = GetComponentListIndex(component);
        uint nodeIndex = GetNodeListIndex(node);
        if (index == NO_ITEM || nodeIndex == NO_ITEM)
            continue;

        if (node is editorScene && (component.typeName == "Octree" || component.typeName == "PhysicsWorld" ||
            component.typeName == "DebugRenderer"))
            continue;

        uint id = node.id;
        BeginModify(id);
        node.RemoveComponent(component);
        EndModify(id);

        UpdateSceneWindowNode(nodeIndex, node);

        // If deleting only one component, select the next item in the same index
        if (selectedComponents.length == 1 && selectedNodes.empty)
        {
            list.selection = index;
            return true;
        }
    }

    // Remove (parented) nodes last
    for (uint i = 0; i < selectedNodes.length; ++i)
    {
        Node@ node = selectedNodes[i];
        if (node.parent is null)
            continue;

        uint id = node.id;
        uint nodeIndex = GetNodeListIndex(node);

        BeginModify(id);
        node.Remove();
        EndModify(id);

        UpdateSceneWindowNode(nodeIndex, null);

        // Select the next item in the same index

        // If deleting only one node, select the next item in the same index
        if (selectedNodes.length == 1 && selectedComponents.empty)
        {
            list.selection = nodeIndex;
            return true;
        }
    }

    // If any kind of multi-delete was performed, the list selection should be clear now.
    // Unfortunately that also means we did not get selection change events, so must update the selection arrays manually.
    // Otherwise nodes/components may be left in the scene even after delete, as the selection arrays keep them alive.
    HandleNodeListSelectionChange();
    return true;
}

bool SceneCut()
{
    if (SceneCopy())
        return SceneDelete();
    else
        return false;
}

bool SceneCopy()
{
    if ((selectedNodes.empty && selectedComponents.empty) || !CheckSceneWindowFocus())
        return false;

    // Must have either only components, or only nodes
    if (!selectedNodes.empty && !selectedComponents.empty)
        return false;

    ListView@ list = sceneWindow.GetChild("NodeList", true);
    copyBuffer.Clear();

    // Copy components
    if (!selectedComponents.empty)
    {
        for (uint i = 0; i < selectedComponents.length; ++i)
        {
            XMLFile@ xml = XMLFile();
            XMLElement rootElem = xml.CreateRoot("component");
            selectedComponents[i].SaveXML(rootElem);
            // Note: component type has to be saved manually
            rootElem.SetString("type", selectedComponents[i].typeName);
            rootElem.SetBool("local", selectedComponents[i].id >= FIRST_LOCAL_ID);
            copyBuffer.Push(xml);
        }
        return true;
    }
    // Copy node. The root node can not be copied
    else
    {
        for (uint i = 0; i < selectedNodes.length; ++i)
        {
            if (selectedNodes[i] is editorScene)
                return false;
        }

        for (uint i = 0; i < selectedNodes.length; ++i)
        {
            XMLFile@ xml = XMLFile();
            XMLElement rootElem = xml.CreateRoot("node");
            selectedNodes[i].SaveXML(rootElem);
            rootElem.SetBool("local", selectedNodes[i].id >= FIRST_LOCAL_ID);
            copyBuffer.Push(xml);
        }

        copyBufferExpanded = SaveExpandedStatus(GetNodeListIndex(selectedNodes[0]));
        return true;
    }
}

bool ScenePaste()
{
    if (editNode is null || !CheckSceneWindowFocus() || copyBuffer.empty)
        return false;

    ListView@ list = sceneWindow.GetChild("NodeList", true);
    bool pasteComponents = false;

    for (uint i = 0; i < copyBuffer.length; ++i)
    {
        XMLElement rootElem = copyBuffer[i].root;
        String mode = rootElem.name;
        if (mode == "component")
        {
            pasteComponents = true;

            // If this is the root node, do not allow to create duplicate scene-global components
            if (editNode is editorScene && CheckForExistingGlobalComponent(editNode, rootElem.GetAttribute("type")))
                return false;

            BeginModify(editNode.id);

            // If copied component was local, make the new local too
            Component@ newComponent = editNode.CreateComponent(rootElem.GetAttribute("type"), rootElem.GetBool("local") ? LOCAL :
                REPLICATED);
            if (newComponent is null)
            {
                EndModify(editNode.id);
                return false;
            }
            newComponent.LoadXML(rootElem);
            newComponent.ApplyAttributes();
            EndModify(editNode.id);
        }
        else if (mode == "node")
        {
            // Make the paste go always to the root node, no matter of the selected node
            BeginModify(editorScene.id);
            // If copied node was local, make the new local too
            Node@ newNode = editorScene.CreateChild("", rootElem.GetBool("local") ? LOCAL : REPLICATED);
            BeginModify(newNode.id);
            newNode.LoadXML(rootElem);
            newNode.ApplyAttributes();
            EndModify(newNode.id);
            EndModify(editorScene.id);

            uint addIndex = GetParentAddIndex(newNode);
            UpdateSceneWindowNode(addIndex, newNode);
            RestoreExpandedStatus(addIndex, copyBufferExpanded);
        }
    }

    if (pasteComponents)
        UpdateSceneWindowNode(editNode);

    return true;
}

void CalculateNewTransform(Node@ source, Node@ target, Vector3& pos, Quaternion& rot, Vector3& scale)
{
    Vector3 sourceWorldPos = source.worldPosition;
    Quaternion sourceWorldRot = source.worldRotation;
    Vector3 sourceWorldScale = source.worldScale;

    Quaternion inverseTargetWorldRot = target.worldRotation.Inverse();
    Vector3 inverseTargetWorldScale = Vector3(1, 1, 1) / target.worldScale;
    scale = inverseTargetWorldScale * sourceWorldScale;
    rot = inverseTargetWorldRot * sourceWorldRot;
    pos = inverseTargetWorldScale * (inverseTargetWorldRot * (sourceWorldPos - target.worldPosition));
}
