// Urho3D editor scene handling

#include "Scripts/Editor/EditorSceneWindow.as"
#include "Scripts/Editor/EditorNodeWindow.as"

const int PICK_GEOMETRIES = 0;
const int PICK_LIGHTS = 1;
const int PICK_ZONES = 2;
const int PICK_RIGIDBODIES = 3;
const int PICK_UI_ELEMENTS = 4;
const int MAX_PICK_MODES = 5;
const int MAX_UNDOSTACK_SIZE = 256;

Scene@ editorScene;

String instantiateFileName;
CreateMode instantiateMode = REPLICATED;
bool sceneModified = false;
bool runUpdate = false;

Array<Node@> selectedNodes;
Array<Component@> selectedComponents;
Node@ editNode;
Array<Node@> editNodes;
Array<Component@> editComponents;
uint numEditableComponentsPerNode = 1;

Array<XMLFile@> sceneCopyBuffer;

bool suppressSceneChanges = false;
bool inSelectionModify = false;

Array<EditActionGroup> undoStack;
uint undoStackPos = 0;

void ClearSceneSelection()
{
    selectedNodes.Clear();
    selectedComponents.Clear();
    editNode = null;
    editNodes.Clear();
    editComponents.Clear();
    numEditableComponentsPerNode = 1;

    HideGizmo();
}

void CreateScene()
{
    // Create a scene only once here
    editorScene = Scene("");

    // Allow access to the scene from the console
    script.defaultScene = editorScene;

    // Always pause the scene, and do updates manually
    editorScene.updateEnabled = false;

    // Camera is not bounded to a scene but still need to be created once here
    CreateCamera();
}

bool ResetScene()
{
    ui.cursor.shape = CS_BUSY;

    suppressSceneChanges = true;

    // Create a scene with default values, these will be overridden when loading scenes
    editorScene.Clear();
    Octree@ octree = editorScene.CreateComponent("Octree");
    PhysicsWorld@ physicsWorld = editorScene.CreateComponent("PhysicsWorld");
    octree.Resize(BoundingBox(-1000.0, 1000.0), 8);
    editorScene.CreateComponent("DebugRenderer");

    sceneModified = false;
    runUpdate = false;

    UpdateWindowTitle();
    UpdateHierarchyItem(editorScene, true);
    ClearEditActions();

    suppressSceneChanges = false;

    ResetCamera();
    CreateGizmo();

    return true;
}

void SetResourcePath(String newPath, bool usePreferredDir = true)
{
    if (newPath.empty)
        return;

    if (usePreferredDir)
        newPath = AddTrailingSlash(cache.GetPreferredResourceDir(newPath));
    else
        newPath = AddTrailingSlash(newPath);

    if (newPath == sceneResourcePath)
        return;

    cache.ReleaseAllResources(false);
    renderer.ReloadShaders();

    // Remove the old scene resource path if any. However make sure that the default data paths do not get removed
    if (!sceneResourcePath.empty && !sceneResourcePath.Contains(fileSystem.programDir))
        cache.RemoveResourceDir(sceneResourcePath);

    cache.AddResourceDir(newPath);
    sceneResourcePath = newPath;
}

bool LoadScene(const String&in fileName)
{
    if (fileName.empty)
        return false;

    ui.cursor.shape = CS_BUSY;

    // Always load the scene from the filesystem, not from resource paths
    if (!fileSystem.FileExists(fileName))
    {
        log.Error("No such scene: " + fileName);
        return false;
    }

    File file(fileName, FILE_READ);
    if (!file.open)
        return false;

    // Add the new resource path
    SetResourcePath(GetPath(fileName));

    suppressSceneChanges = true;

    String extension = GetExtension(fileName);
    bool loaded;
    if (extension != ".xml")
        loaded = editorScene.Load(file);
    else
        loaded = editorScene.LoadXML(file);

    // Always pause the scene, and do updates manually
    editorScene.updateEnabled = false;

    sceneModified = false;
    runUpdate = false;

    UpdateWindowTitle();
    UpdateHierarchyItem(editorScene, true);
    ClearEditActions();

    suppressSceneChanges = false;

    ResetCamera();
    CreateGizmo();

    return loaded;
}

bool SaveScene(const String&in fileName)
{
    if (fileName.empty)
        return false;

    ui.cursor.shape = CS_BUSY;

    // Unpause when saving so that the scene will work properly when loaded outside the editor
    editorScene.updateEnabled = true;

    File file(fileName, FILE_WRITE);
    String extension = GetExtension(fileName);
    bool success = (extension != ".xml" ? editorScene.Save(file) : editorScene.SaveXML(file));

    editorScene.updateEnabled = false;

    if (success)
    {
        sceneModified = false;
        UpdateWindowTitle();
    }

    return success;
}

bool SaveSceneWithExistingName()
{
    if (editorScene.fileName.empty || editorScene.fileName == TEMP_SCENE_NAME)
        return PickFile();
    else
        return SaveScene(editorScene.fileName);
}

void CreateNode(CreateMode mode)
{
    Node@ newNode = editorScene.CreateChild("", mode);
    // Set the new node a certain distance from the camera
    newNode.position = GetNewNodePosition();

    // Create an undo action for the create
    CreateNodeAction action;
    action.Define(newNode);
    SaveEditAction(action);

    FocusNode(newNode);
}

void CreateComponent(const String&in componentType)
{
    // If this is the root node, do not allow to create duplicate scene-global components
    if (editNode is editorScene && CheckForExistingGlobalComponent(editNode, componentType))
        return;

    // Group for storing undo actions
    EditActionGroup group;

    // For now, make a local node's all components local
    /// \todo Allow to specify the createmode
    for (uint i = 0; i < editNodes.length; ++i)
    {
        Component@ newComponent = editNodes[i].CreateComponent(componentType, editNodes[i].id < FIRST_LOCAL_ID ? REPLICATED : LOCAL);
        if (newComponent !is null)
        {
            // Some components such as CollisionShape do not create their internal object before the first call to ApplyAttributes()
            // to prevent unnecessary initialization with default values. Call now
            newComponent.ApplyAttributes();

            CreateComponentAction action;
            action.Define(newComponent);
            group.actions.Push(action);
        }
    }

    SaveEditActionGroup(group);
    SetSceneModified();

    // Although the edit nodes selection are not changed, call to ensure attribute inspector notices new components of the edit nodes
    HandleHierarchyListSelectionChange();
}

void LoadNode(const String&in fileName)
{
    if (fileName.empty)
        return;

    if (!fileSystem.FileExists(fileName))
    {
        log.Error("No such node file " + fileName);
        return;
    }

    File file(fileName, FILE_READ);
    if (!file.open)
        return;

    ui.cursor.shape = CS_BUSY;

    // Before instantiating, set resource path if empty
    if (sceneResourcePath.empty)
        SetResourcePath(GetPath(fileName));

    Vector3 position = GetNewNodePosition();
    Node@ newNode;

    String extension = GetExtension(fileName);
    if (extension != ".xml")
        newNode = editorScene.Instantiate(file, position, Quaternion(), instantiateMode);
    else
        newNode = editorScene.InstantiateXML(file, position, Quaternion(), instantiateMode);

    if (newNode !is null)
    {
        // Create an undo action for the load
        CreateNodeAction action;
        action.Define(newNode);
        SaveEditAction(action);

        FocusNode(newNode);
        instantiateFileName = fileName;
    }
}

bool SaveNode(const String&in fileName)
{
    if (fileName.empty)
        return false;

    ui.cursor.shape = CS_BUSY;

    File file(fileName, FILE_WRITE);
    if (!file.open)
        return false;

    String extension = GetExtension(fileName);
    bool success = (extension != ".xml" ? editNode.Save(file) : editNode.SaveXML(file));
    if (success)
        instantiateFileName = fileName;

    return success;
}

void UpdateScene(float timeStep)
{
    if (runUpdate)
        editorScene.Update(timeStep);
}

void SetSceneModified()
{
    if (!sceneModified)
    {
        sceneModified = true;
        UpdateWindowTitle();
    }
}

bool SceneDelete()
{
    ui.cursor.shape = CS_BUSY;

    BeginSelectionModify();

    // Clear the selection now to prevent repopulation of selectedNodes and selectedComponents combo
    hierarchyList.ClearSelection();

    // Group for storing undo actions
    EditActionGroup group;

    // Remove nodes
    for (uint i = 0; i < selectedNodes.length; ++i)
    {
        Node@ node = selectedNodes[i];
        if (node.parent is null || node.scene is null)
            continue; // Root or already deleted

        uint nodeIndex = GetListIndex(node);

        // Create undo action
        DeleteNodeAction action;
        action.Define(node);
        group.actions.Push(action);

        node.Remove();
        SetSceneModified();

        // If deleting only one node, select the next item in the same index
        if (selectedNodes.length == 1 && selectedComponents.empty)
            hierarchyList.selection = nodeIndex;
    }

    // Then remove components, if they still remain
    for (uint i = 0; i < selectedComponents.length; ++i)
    {
        Component@ component = selectedComponents[i];
        Node@ node = component.node;
        if (node is null)
            continue; // Already deleted

        uint index = GetComponentListIndex(component);
        uint nodeIndex = GetListIndex(node);
        if (index == NO_ITEM || nodeIndex == NO_ITEM)
            continue;

        // Do not allow to remove the Octree, PhysicsWorld or DebugRenderer from the root node
        if (node is editorScene && (component.typeName == "Octree" || component.typeName == "PhysicsWorld" ||
            component.typeName == "DebugRenderer"))
            continue;

        // Create undo action
        DeleteComponentAction action;
        action.Define(component);
        group.actions.Push(action);

        node.RemoveComponent(component);
        SetSceneModified();

        // If deleting only one component, select the next item in the same index
        if (selectedComponents.length == 1 && selectedNodes.empty)
            hierarchyList.selection = index;
    }

    SaveEditActionGroup(group);

    EndSelectionModify();
    return true;
}

bool SceneCut()
{
    return SceneCopy() && SceneDelete();
}

bool SceneCopy()
{
    ui.cursor.shape = CS_BUSY;

    sceneCopyBuffer.Clear();

    // Copy components
    if (!selectedComponents.empty)
    {
        for (uint i = 0; i < selectedComponents.length; ++i)
        {
            XMLFile@ xml = XMLFile();
            XMLElement rootElem = xml.CreateRoot("component");
            selectedComponents[i].SaveXML(rootElem);
            rootElem.SetBool("local", selectedComponents[i].id >= FIRST_LOCAL_ID);
            sceneCopyBuffer.Push(xml);
        }
    }
    // Copy nodes.
    else
    {
        for (uint i = 0; i < selectedNodes.length; ++i)
        {
            // Skip the root scene node as it cannot be copied
            if (selectedNodes[i] is editorScene)
                continue;

            XMLFile@ xml = XMLFile();
            XMLElement rootElem = xml.CreateRoot("node");
            selectedNodes[i].SaveXML(rootElem);
            rootElem.SetBool("local", selectedNodes[i].id >= FIRST_LOCAL_ID);
            sceneCopyBuffer.Push(xml);
        }
    }

    return true;
}

bool ScenePaste()
{
    ui.cursor.shape = CS_BUSY;

    // Group for storing undo actions
    EditActionGroup group;

    for (uint i = 0; i < sceneCopyBuffer.length; ++i)
    {
        XMLElement rootElem = sceneCopyBuffer[i].root;
        String mode = rootElem.name;
        if (mode == "component")
        {
            // If this is the root node, do not allow to create duplicate scene-global components
            if (editNode is editorScene && CheckForExistingGlobalComponent(editNode, rootElem.GetAttribute("type")))
                return false;

            // If copied component was local, make the new local too
            Component@ newComponent = editNode.CreateComponent(rootElem.GetAttribute("type"), rootElem.GetBool("local") ? LOCAL :
                REPLICATED);
            if (newComponent is null)
                return false;

            newComponent.LoadXML(rootElem);
            newComponent.ApplyAttributes();

            // Create an undo action
            CreateComponentAction action;
            action.Define(newComponent);
            group.actions.Push(action);
        }
        else if (mode == "node")
        {
            // Make the paste go always to the root node, no matter of the selected node
            // If copied node was local, make the new local too
            Node@ newNode = editorScene.CreateChild("", rootElem.GetBool("local") ? LOCAL : REPLICATED);
            newNode.LoadXML(rootElem);

            // Create an undo action
            CreateNodeAction action;
            action.Define(newNode);
            group.actions.Push(action);
        }
    }

    SaveEditActionGroup(group);
    return true;
}

bool SceneUnparent()
{
    if (!CheckHierarchyWindowFocus() || !selectedComponents.empty || selectedNodes.empty)
        return false;

    ui.cursor.shape = CS_BUSY;

    // Group for storing undo actions
    EditActionGroup group;

    // Parent selected nodes to root
    Array<Node@> changedNodes;
    for (uint i = 0; i < selectedNodes.length; ++i)
    {
        Node@ sourceNode = selectedNodes[i];
        if (sourceNode.parent is null || sourceNode.parent is editorScene)
            continue; // Root or already parented to root

        // Perform the reparenting, continue loop even if action fails
        ReparentNodeAction action;
        action.Define(sourceNode, editorScene);
        group.actions.Push(action);

        SceneChangeParent(sourceNode, editorScene, false);
        changedNodes.Push(sourceNode);
    }

    // Reselect the changed nodes at their new position in the list
    for (uint i = 0; i < changedNodes.length; ++i)
        hierarchyList.AddSelection(GetListIndex(changedNodes[i]));

    SaveEditActionGroup(group);

    return true;
}

bool SceneToggleEnable()
{
    if (!CheckHierarchyWindowFocus())
        return false;

    ui.cursor.shape = CS_BUSY;

    EditActionGroup group;

    // Toggle enabled state of nodes recursively
    for (uint i = 0; i < selectedNodes.length; ++i)
    {
        // Do not attempt to disable the Scene
        if (selectedNodes[i].typeName == "Node")
        {
            bool oldEnabled = selectedNodes[i].enabled;
            selectedNodes[i].SetEnabled(!oldEnabled, true);

            // Create undo action
            ToggleNodeEnabledAction action;
            action.Define(selectedNodes[i], oldEnabled);
            group.actions.Push(action);
        }
    }
    for (uint i = 0; i < selectedComponents.length; ++i)
    {
        // Some components purposefully do not expose the Enabled attribute, and it does not affect them in any way
        // (Octree, PhysicsWorld). Check that the first attribute is in fact called "Is Enabled"
        if (selectedComponents[i].numAttributes > 0 && selectedComponents[i].attributeInfos[0].name == "Is Enabled")
        {
            bool oldEnabled = selectedComponents[i].enabled;
            selectedComponents[i].enabled = !oldEnabled;

            // Create undo action
            EditAttributeAction action;
            action.Define(selectedComponents[i], 0, Variant(oldEnabled));
            group.actions.Push(action);
        }
    }

    SaveEditActionGroup(group);

    return true;
}

bool SceneChangeParent(Node@ sourceNode, Node@ targetNode, bool createUndoAction = true)
{
    // Create undo action if requested
    if (createUndoAction)
    {
        ReparentNodeAction action;
        action.Define(sourceNode, targetNode);
        SaveEditAction(action);
    }

    sourceNode.parent = targetNode;

    // Return true if success
    if (sourceNode.parent is targetNode)
    {
        UpdateNodeAttributes(); // Parent change may have changed local transform
        return true;
    }
    else
        return false;
}

bool SceneResetPosition()
{
    if (editNode !is null)
    {
        Transform oldTransform;
        oldTransform.Define(editNode);

        editNode.position = Vector3(0.0, 0.0, 0.0);

        // Create undo action
        EditNodeTransformAction action;
        action.Define(editNode, oldTransform);
        SaveEditAction(action);

        UpdateNodeAttributes();
        return true;
    }
    else
        return false;
}

bool SceneResetRotation()
{
    if (editNode !is null)
    {
        Transform oldTransform;
        oldTransform.Define(editNode);

        editNode.rotation = Quaternion();

        // Create undo action
        EditNodeTransformAction action;
        action.Define(editNode, oldTransform);
        SaveEditAction(action);

        UpdateNodeAttributes();
        return true;
    }
    else
        return false;
}

bool SceneResetScale()
{
    if (editNode !is null)
    {
        Transform oldTransform;
        oldTransform.Define(editNode);

        editNode.scale = Vector3(1.0, 1.0, 1.0);

        // Create undo action
        EditNodeTransformAction action;
        action.Define(editNode, oldTransform);
        SaveEditAction(action);

        UpdateNodeAttributes();
        return true;
    }
    else
        return false;
}

bool SceneSelectAll()
{
    BeginSelectionModify();
    Array<Node@> rootLevelNodes = editorScene.GetChildren();
    Array<uint> indices;
    for (uint i = 0; i < rootLevelNodes.length; ++i)
        indices.Push(GetListIndex(rootLevelNodes[i]));
    hierarchyList.SetSelections(indices);
    EndSelectionModify();

    return true;
}

bool SceneResetToDefault()
{
    ui.cursor.shape = CS_BUSY;

    // Group for storing undo actions
    EditActionGroup group;

    // Reset selected component to their default
    if (!selectedComponents.empty)
    {
        for (uint i = 0; i < selectedComponents.length; ++i)
        {
            Component@ component = selectedComponents[i];

            ResetAttributesAction action;
            action.Define(component);
            group.actions.Push(action);

            component.ResetToDefault();
            component.ApplyAttributes();
            for (uint j = 0; j < component.numAttributes; ++j)
                PostEditAttribute(component, j);
        }
    }
    // OR reset selected nodes to their default
    else
    {
        for (uint i = 0; i < selectedNodes.length; ++i)
        {
            Node@ node = selectedNodes[i];

            ResetAttributesAction action;
            action.Define(node);
            group.actions.Push(action);

            node.ResetToDefault();
            node.ApplyAttributes();
            for (uint j = 0; j < node.numAttributes; ++j)
                PostEditAttribute(node, j);
        }
    }

    SaveEditActionGroup(group);
    SetSceneModified();
    attributesFullDirty = true;

    return true;
}

bool SceneRebuildNavigation()
{
    ui.cursor.shape = CS_BUSY;

    Array<Component@>@ navMeshes = editorScene.GetComponents("NavigationMesh");
    bool success = true;
    for (uint i = 0; i < navMeshes.length; ++i)
    {
        NavigationMesh@ navMesh = navMeshes[i];
        if (!navMesh.Build())
            success = false;
    }

    return success;
}
