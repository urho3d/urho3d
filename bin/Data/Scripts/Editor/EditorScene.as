/// Urho3D editor scene handling

#include "Scripts/Editor/EditorHierarchyWindow.as"
#include "Scripts/Editor/EditorInspectorWindow.as"
#include "Scripts/Editor/EditorCubeCapture.as"

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
bool skipMruScene = false;

Array<EditActionGroup> undoStack;
uint undoStackPos = 0;

bool revertOnPause = false;
XMLFile@ revertData;

Vector3 lastOffsetForSmartDuplicate;

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
    editorScene = Scene();

    // Allow access to the scene from the console
    script.defaultScene = editorScene;

    // Always pause the scene, and do updates manually
    editorScene.updateEnabled = false;
}

bool ResetScene()
{
    ui.cursor.shape = CS_BUSY;

    if (messageBoxCallback is null && sceneModified)
    {
        MessageBox@ messageBox = MessageBox("Scene has been modified.\nContinue to reset?", "Warning");
        if (messageBox.window !is null)
        {
            Button@ cancelButton = messageBox.window.GetChild("CancelButton", true);
            cancelButton.visible = true;
            cancelButton.focus = true;
            SubscribeToEvent(messageBox, "MessageACK", "HandleMessageAcknowledgement");
            messageBoxCallback = @ResetScene;
            return false;
        }
    }
    else
        messageBoxCallback = null;

    suppressSceneChanges = true;

    // Create a scene with default values, these will be overridden when loading scenes
    editorScene.Clear();
    editorScene.CreateComponent("Octree");
    editorScene.CreateComponent("DebugRenderer");

    // Release resources that became unused after the scene clear
    cache.ReleaseAllResources(false);

    sceneModified = false;
    revertData = null;
    StopSceneUpdate();

    UpdateWindowTitle();
    DisableInspectorLock();
    UpdateHierarchyItem(editorScene, true);
    ClearEditActions();

    suppressSceneChanges = false;

    ResetCamera();
    CreateGizmo();
    CreateGrid();
    SetActiveViewport(viewports[0]);

    return true;
}

void SetResourcePath(String newPath, bool usePreferredDir = true, bool additive = false)
{
    if (newPath.empty)
        return;
    if (!IsAbsolutePath(newPath))
        newPath = fileSystem.currentDir + newPath;

    if (usePreferredDir)
        newPath = AddTrailingSlash(cache.GetPreferredResourceDir(newPath));
    else
        newPath = AddTrailingSlash(newPath);

    if (newPath == sceneResourcePath)
        return;

    // Remove the old scene resource path if any. However make sure that the default data paths do not get removed
    if (!additive)
    {
        cache.ReleaseAllResources(false);
        renderer.ReloadShaders();

        String check = AddTrailingSlash(sceneResourcePath);
        bool isDefaultResourcePath = check.Compare(fileSystem.programDir + "Data/", false) == 0 ||
            check.Compare(fileSystem.programDir + "CoreData/", false) == 0;

        if (!sceneResourcePath.empty && !isDefaultResourcePath)
            cache.RemoveResourceDir(sceneResourcePath);
    }
    else
    {
        // If additive (path of a loaded prefab) check that the new path isn't already part of an old path
        Array<String>@ resourceDirs = cache.resourceDirs;

        for (uint i = 0; i < resourceDirs.length; ++i)
        {
            if (newPath.StartsWith(resourceDirs[i], false))
                return;
        }
    }

    // Add resource path as first priority so that it takes precedence over the default data paths
    cache.AddResourceDir(newPath, 0);
    RebuildResourceDatabase();

    if (!additive)
    {
        sceneResourcePath = newPath;
        uiScenePath = GetResourceSubPath(newPath, "Scenes");
        uiElementPath = GetResourceSubPath(newPath, "UI");
        uiNodePath = GetResourceSubPath(newPath, "Objects");
        uiScriptPath = GetResourceSubPath(newPath, "Scripts");
        uiParticlePath = GetResourceSubPath(newPath, "Particle");
    }
}

String GetResourceSubPath(String basePath, const String&in subPath)
{
    basePath = AddTrailingSlash(basePath);
    if (fileSystem.DirExists(basePath + subPath))
        return AddTrailingSlash(basePath + subPath);
    else
        return basePath;
}

bool LoadScene(const String&in fileName)
{
    if (fileName.empty)
        return false;

    ui.cursor.shape = CS_BUSY;

    // Always load the scene from the filesystem, not from resource paths
    if (!fileSystem.FileExists(fileName))
    {
        MessageBox("No such scene.\n" + fileName);
        return false;
    }

    File file(fileName, FILE_READ);
    if (!file.open)
    {
        MessageBox("Could not open file.\n" + fileName);
        return false;
    }

    // Add the scene's resource path in case it's necessary
    String newScenePath = GetPath(fileName);
    if (!rememberResourcePath || !sceneResourcePath.StartsWith(newScenePath, false))
        SetResourcePath(newScenePath);

    suppressSceneChanges = true;
    sceneModified = false;
    revertData = null;
    StopSceneUpdate();

    String extension = GetExtension(fileName);
    bool loaded;
    if (extension == ".xml")
        loaded = editorScene.LoadXML(file);
    else if (extension == ".json")
        loaded = editorScene.LoadJSON(file);
    else
        loaded = editorScene.Load(file);

    // Release resources which are not used by the new scene
    cache.ReleaseAllResources(false);

    // Always pause the scene, and do updates manually
    editorScene.updateEnabled = false;

    UpdateWindowTitle();
    DisableInspectorLock();
    UpdateHierarchyItem(editorScene, true);
    CollapseHierarchy();
    ClearEditActions();

    suppressSceneChanges = false;

    // global variable to mostly bypass adding mru upon importing tempscene
    if (!skipMruScene)
        UpdateSceneMru(fileName);

    skipMruScene = false;

    ResetCamera();
    CreateGizmo();
    CreateGrid();
    SetActiveViewport(viewports[0]);

    return loaded;
}

bool SaveScene(const String&in fileName)
{
    if (fileName.empty)
        return false;

    ui.cursor.shape = CS_BUSY;

    // Unpause when saving so that the scene will work properly when loaded outside the editor
    editorScene.updateEnabled = true;

    MakeBackup(fileName);
    File file(fileName, FILE_WRITE);
    String extension = GetExtension(fileName);
    bool success;
    if (extension == ".xml")
        success = editorScene.SaveXML(file);
    else if (extension == ".json")
        success = editorScene.SaveJSON(file);
    else
        success = editorScene.Save(file);
    RemoveBackup(success, fileName);

    editorScene.updateEnabled = false;

    if (success)
    {
        UpdateSceneMru(fileName);
        sceneModified = false;
        UpdateWindowTitle();
    }
    else
        MessageBox("Could not save scene successfully!\nSee Urho3D.log for more detail.");

    return success;
}

bool SaveSceneWithExistingName()
{
    if (editorScene.fileName.empty || editorScene.fileName == TEMP_SCENE_NAME)
        return PickFile();
    else
        return SaveScene(editorScene.fileName);
}

Node@ CreateNode(CreateMode mode, bool raycastToMouse = false)
{
    Node@ newNode = null;
    if (editNode !is null)
        newNode = editNode.CreateChild("", mode);
    else
        newNode = editorScene.CreateChild("", mode);
    newNode.worldPosition = GetNewNodePosition(raycastToMouse);

    // Create an undo action for the create
    CreateNodeAction action;
    action.Define(newNode);
    SaveEditAction(action);
    SetSceneModified();

    FocusNode(newNode);

    return newNode;
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

void CreateLoadedComponent(Component@ component)
{
    if (component is null) return;
    CreateComponentAction action;
    action.Define(component);
    SaveEditAction(action);
    SetSceneModified();
    FocusComponent(component);
}

Node@ LoadNode(const String&in fileName, Node@ parent = null, bool raycastToMouse = false)
{
    if (fileName.empty)
        return null;

    if (!fileSystem.FileExists(fileName))
    {
        MessageBox("No such node file.\n" + fileName);
        return null;
    }

    File file(fileName, FILE_READ);
    if (!file.open)
    {
        MessageBox("Could not open file.\n" + fileName);
        return null;
    }

    ui.cursor.shape = CS_BUSY;

    // Before instantiating, add object's resource path if necessary
    SetResourcePath(GetPath(fileName), true, true);

    Node@ newNode = InstantiateNodeFromFile(file, GetNewNodePosition(raycastToMouse), Quaternion(), 1, parent, instantiateMode);
    if (newNode !is null)
    {
        FocusNode(newNode);
        instantiateFileName = fileName;
    }
    return newNode;
}

Node@ InstantiateNodeFromFile(File@ file, const Vector3& position, const Quaternion& rotation, float scaleMod = 1.0f, Node@ parent = null, CreateMode mode = REPLICATED)
{
    if (file is null)
        return null;

    Node@ newNode;
    uint numSceneComponent = editorScene.numComponents;

    suppressSceneChanges = true;

    String extension = GetExtension(file.name);
    if (extension == ".xml")
        newNode = editorScene.InstantiateXML(file, position, rotation, mode);
    else if (extension == ".json")
        newNode = editorScene.InstantiateJSON(file, position, rotation, mode);
    else
        newNode = editorScene.Instantiate(file, position, rotation, mode);

    suppressSceneChanges = false;

    if (parent !is null)
        newNode.parent = parent;
        
    if (newNode !is null)
    {
        newNode.scale = newNode.scale * scaleMod;
        
        AdjustNodePositionByAABB(newNode);

        // Create an undo action for the load
        CreateNodeAction action;
        action.Define(newNode);
        SaveEditAction(action);
        SetSceneModified();

        if (numSceneComponent != editorScene.numComponents)
            UpdateHierarchyItem(editorScene);
        else
            UpdateHierarchyItem(newNode);
    }

    return newNode;
}

void AdjustNodePositionByAABB(Node@ newNode)
{
    if (alignToAABBBottom)
    {
        Drawable@ drawable = GetFirstDrawable(newNode);
        if (drawable !is null)
        {
            BoundingBox aabb = drawable.worldBoundingBox;
            Vector3 aabbBottomCenter(aabb.center.x, aabb.min.y, aabb.center.z);
            Vector3 offset = aabbBottomCenter - newNode.worldPosition;
            newNode.worldPosition = newNode.worldPosition - offset;
        }
    }
}

bool SaveNode(const String&in fileName)
{
    if (fileName.empty)
        return false;

    ui.cursor.shape = CS_BUSY;

    MakeBackup(fileName);
    File file(fileName, FILE_WRITE);
    if (!file.open)
    {
        MessageBox("Could not open file.\n" + fileName);
        return false;
    }

    String extension = GetExtension(fileName);
    bool success;
    if (extension == ".xml")
        success = editNode.SaveXML(file);
    else if (extension == ".json")
        success = editNode.SaveJSON(file);
    else
        success = editNode.Save(file);
    RemoveBackup(success, fileName);

    if (success)
        instantiateFileName = fileName;
    else
        MessageBox("Could not save node successfully!\nSee Urho3D.log for more detail.");

    return success;
}

void UpdateScene(float timeStep)
{
    if (runUpdate)
        editorScene.Update(timeStep);
}

void StopSceneUpdate()
{
    runUpdate = false;
    audio.Stop();
    toolBarDirty = true;

    // If scene should revert on update stop, load saved data now
    if (revertOnPause && revertData !is null)
    {
        suppressSceneChanges = true;
        editorScene.Clear();
        editorScene.LoadXML(revertData.root);
        CreateGrid();
        UpdateHierarchyItem(editorScene, true);
        ClearEditActions();
        suppressSceneChanges = false;
    }

    revertData = null;
}

void StartSceneUpdate()
{
    runUpdate = true;
    // Run audio playback only when scene is updating, so that audio components' time-dependent attributes stay constant when
    // paused (similar to physics)
    audio.Play();
    toolBarDirty = true;

    // Save scene data for reverting if enabled
    if (revertOnPause)
    {
        revertData = XMLFile();
        XMLElement root = revertData.CreateRoot("scene");
        editorScene.SaveXML(root);
    }
    else
        revertData = null;
}

bool ToggleSceneUpdate()
{
    if (!runUpdate)
        StartSceneUpdate();
    else
        StopSceneUpdate();
    return true;
}

bool ShowLayerMover()
{
    if (ui.focusElement is null)
        return ShowLayerEditor();
    else
        return false;
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

        // Do not allow to remove the Octree, DebugRenderer or MaterialCache2D or DrawableProxy2D from the root node
        if (node is editorScene && (component.typeName == "Octree" || component.typeName == "DebugRenderer" ||
            component.typeName == "MaterialCache2D" || component.typeName == "DrawableProxy2D"))
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
    // Copy nodes
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

bool ScenePaste(bool pasteRoot = false, bool duplication = false)
{
    ui.cursor.shape = CS_BUSY;

    // Group for storing undo actions
    EditActionGroup group;

    for (uint i = 0; i < sceneCopyBuffer.length; ++i)
    {
        XMLElement rootElem = sceneCopyBuffer[i].root;
        String mode = rootElem.name;
        if (mode == "component" && editNode !is null)
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
            // If copied node was local, make the new local too
            Node@ newNode;
            // Are we pasting into the root node?
            if (pasteRoot)
                newNode = editorScene.CreateChild("", rootElem.GetBool("local") ? LOCAL : REPLICATED);
            else
            {
                // If we are duplicating or have the original node selected, paste into the selected nodes parent
                if (duplication || editNode is null || editNode.id == rootElem.GetUInt("id"))
                {
                    if (editNode !is null && editNode.parent !is null)
                        newNode = editNode.parent.CreateChild("", rootElem.GetBool("local") ? LOCAL : REPLICATED);
                    else
                        newNode = editorScene.CreateChild("", rootElem.GetBool("local") ? LOCAL : REPLICATED);
                }
                // If we aren't duplicating, paste into the selected node
                else
                {
                    newNode = editNode.CreateChild("", rootElem.GetBool("local") ? LOCAL : REPLICATED);
                }
            }

            newNode.LoadXML(rootElem);

            // Create an undo action
            CreateNodeAction action;
            action.Define(newNode);
            group.actions.Push(action);
        }
    }

    SaveEditActionGroup(group);
    SetSceneModified();
    return true;
}

bool SceneDuplicate()
{
    Array<XMLFile@> copy = sceneCopyBuffer;

    if (!SceneCopy())
    {
        sceneCopyBuffer = copy;
        return false;
    }
    if (!ScenePaste(false, true))
    {
        sceneCopyBuffer = copy;
        return false;
    }

    sceneCopyBuffer = copy;
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
    SetSceneModified();

    return true;
}

bool NodesParentToLastSelected()
{
    if (lastSelectedNode.Get() is null)
        return false;
        
    if (!CheckHierarchyWindowFocus() || !selectedComponents.empty || selectedNodes.empty)
        return false;

    ui.cursor.shape = CS_BUSY;

    // Group for storing undo actions
    EditActionGroup group;

    // Parent selected nodes to root
    Array<Node@> changedNodes;
    
    // Find new parent node it selected last
    Node@ lastNode = lastSelectedNode.Get(); //GetListNode(hierarchyList.selection);
    
    for (uint i = 0; i < selectedNodes.length; ++i)
    {
        
        Node@ sourceNode = selectedNodes[i];
        if ( sourceNode.id == lastNode.id)
            continue; // Skip last node it is parent
        
        if (sourceNode.parent.id == lastNode.id)
            continue; // Root or already parented to root

        // Perform the reparenting, continue loop even if action fails
        ReparentNodeAction action;
        action.Define(sourceNode, lastNode);
        group.actions.Push(action);

        SceneChangeParent(sourceNode, lastNode, false);
        changedNodes.Push(sourceNode);
    }

    // Reselect the changed nodes at their new position in the list
    for (uint i = 0; i < changedNodes.length; ++i)
        hierarchyList.AddSelection(GetListIndex(changedNodes[i]));

    SaveEditActionGroup(group);
    SetSceneModified();

    return true;
}

bool SceneSmartDuplicateNode() 
{       
    const float minOffset = 0.1;
    
    if (!CheckHierarchyWindowFocus() || !selectedComponents.empty 
        || selectedNodes.empty || lastSelectedNode.Get() is null)
        return false;
    
    
    Node@ node = lastSelectedNode.Get();
    Node@ parent = node.parent;
    Vector3 offset = Vector3(1,0,0); // default offset
    
    if (parent is editorScene) // if parent of selected node is Scene make empty parent for it and place in same position; 
    {
        parent = CreateNode(LOCAL);
        SceneChangeParent(parent, editorScene, false);
        parent.worldPosition = node.worldPosition;
        parent.name = node.name + "Group";
        node.name = parent.name + "Instance" + String(parent.numChildren);
        SceneChangeParent(node, parent, false);
        parent = node.parent;
        SelectNode(node, false);
    } 
    
    Vector3 size;
    BoundingBox bb;
    
    // get bb for offset  
    Drawable@ drawable = GetFirstDrawable(node);
    if (drawable !is null) 
    {
        bb = drawable.boundingBox;
        size =  bb.size * drawable.node.worldScale;
        offset = Vector3(size.x, 0, 0); 
    } 
    
    // make offset on axis that select user by mouse
    if (gizmoAxisX.selected)
    {
        if (size.x < minOffset) size.x = minOffset;
        offset = node.worldRotation * Vector3(size.x,0,0);
    }
    else if (gizmoAxisY.selected)
    {
        if (size.y < minOffset) size.y = minOffset;
        offset = node.worldRotation * Vector3(0,size.y,0);
    }
    else if (gizmoAxisZ.selected)
    {
        if (size.z < minOffset) size.z = minOffset;
        offset = node.worldRotation * Vector3(0,0,size.z);
    }
    else
        offset = lastOffsetForSmartDuplicate;    
    
    Vector3 lastInstancePosition = node.worldPosition;
    
    SelectNode(node, false);
    SceneDuplicate();
    Node@ newInstance = parent.children[parent.numChildren-1];
    SelectNode(newInstance, false);
    newInstance.worldPosition = lastInstancePosition;
    newInstance.Translate(offset, TS_WORLD);
    newInstance.name = parent.name + "Instance" + String(parent.numChildren-1);
    
    lastOffsetForSmartDuplicate = offset;
    UpdateNodeAttributes();
    return true;
}

bool ViewCloser()
{
    return (viewCloser = true);
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
            selectedNodes[i].SetEnabledRecursive(!oldEnabled);

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
    SetSceneModified();

    return true;
}

bool SceneEnableAllNodes()
{
    if (!CheckHierarchyWindowFocus())
        return false;

    ui.cursor.shape = CS_BUSY;

    EditActionGroup group;

    // Toggle enabled state of nodes recursively
    Array<Node@> allNodes;
    allNodes = editorScene.GetChildren(true);
    
    for (uint i = 0; i < allNodes.length; ++i)
    {
        // Do not attempt to disable the Scene
        if (allNodes[i].typeName == "Node")
        {
            bool oldEnabled = allNodes[i].enabled;
            if (oldEnabled == false)
              allNodes[i].SetEnabledRecursive(true);

            // Create undo action
            ToggleNodeEnabledAction action;
            action.Define(allNodes[i], oldEnabled);
            group.actions.Push(action);
        }
    }
    
    Array<Component@> allComponents;
    allComponents = editorScene.GetComponents();
    
    for (uint i = 0; i < allComponents.length; ++i)
    {
        // Some components purposefully do not expose the Enabled attribute, and it does not affect them in any way
        // (Octree, PhysicsWorld). Check that the first attribute is in fact called "Is Enabled"
        if (allComponents[i].numAttributes > 0 && allComponents[i].attributeInfos[0].name == "Is Enabled")
        {
            bool oldEnabled = allComponents[i].enabled;
            allComponents[i].enabled = true;

            // Create undo action
            EditAttributeAction action;
            action.Define(allComponents[i], 0, Variant(oldEnabled));
            group.actions.Push(action);
        }
    }

    SaveEditActionGroup(group);
    SetSceneModified();

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
    SetSceneModified();

    // Return true if success
    if (sourceNode.parent is targetNode)
    {
        UpdateNodeAttributes(); // Parent change may have changed local transform
        return true;
    }
    else
        return false;
}

bool SceneChangeParent(Node@ sourceNode, Array<Node@> sourceNodes, Node@ targetNode, bool createUndoAction = true)
{
    // Create undo action if requested
    if (createUndoAction)
    {
        ReparentNodeAction action;
        action.Define(sourceNodes, targetNode);
        SaveEditAction(action);
    }

    for (uint i = 0; i < sourceNodes.length; ++i)
    {
        Node@ node = sourceNodes[i];
        node.parent = targetNode;
    }
    SetSceneModified();

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
        SetSceneModified();

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
        SetSceneModified();

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
        SetSceneModified();

        UpdateNodeAttributes();
        return true;
    }
    else
        return false;
}

bool SceneResetTransform()
{
    if (editNode !is null)
    {
        Transform oldTransform;
        oldTransform.Define(editNode);

        editNode.position = Vector3(0.0, 0.0, 0.0);
        editNode.rotation = Quaternion();
        editNode.scale = Vector3(1.0, 1.0, 1.0);

        // Create undo action
        EditNodeTransformAction action;
        action.Define(editNode, oldTransform);
        SaveEditAction(action);
        SetSceneModified();

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

    Array<Component@>@ navMeshes = editorScene.GetComponents("NavigationMesh", true);
    if (navMeshes.empty)
    {
        @navMeshes = editorScene.GetComponents("DynamicNavigationMesh", true);
        if (navMeshes.empty)
        {
            MessageBox("No NavigationMesh components in the scene, nothing to rebuild.");
            return false;
        }
    }

    bool success = true;
    for (uint i = 0; i < navMeshes.length; ++i)
    {
        NavigationMesh@ navMesh = navMeshes[i];
        if (!navMesh.Build())
            success = false;
    }

    return success;
}

bool SceneRenderZoneCubemaps()
{
    bool success = false;
    Array<Zone@> capturedThisCall;
    bool alreadyCapturing = activeCubeCapture.length > 0; // May have managed to quickly queue up a second round of zones to render cubemaps for
    
    for (uint i = 0; i < selectedNodes.length; ++i)
    {
        Array<Component@>@ zones = selectedNodes[i].GetComponents("Zone", true);
        for (uint z = 0; z < zones.length; ++z)
        {
            Zone@ zone = cast<Zone>(zones[z]);
            if (zone !is null)
            {
                activeCubeCapture.Push(EditorCubeCapture(zone));
                capturedThisCall.Push(zone);
            }
        }
    }
    
    for (uint i = 0; i < selectedComponents.length; ++i)
    {
        Zone@ zone = cast<Zone>(selectedComponents[i]);
        if (zone !is null)
        {
            if (capturedThisCall.FindByRef(zone) < 0)
            {
                activeCubeCapture.Push(EditorCubeCapture(zone));
                capturedThisCall.Push(zone);
            }
        }
    }
    
    // Start rendering cubemaps if there are any to render and the queue isn't already running
    if (activeCubeCapture.length > 0 && !alreadyCapturing)
        activeCubeCapture[0].Start();

    if (capturedThisCall.length <= 0)
    {
        MessageBox("No zones selected to render cubemaps for/");
    }
    return capturedThisCall.length > 0;
}

bool SceneAddChildrenStaticModelGroup()
{
    StaticModelGroup@ smg = cast<StaticModelGroup>(editComponents.length > 0 ? editComponents[0] : null);
    if (smg is null && editNode !is null)
        smg = editNode.GetComponent("StaticModelGroup");

    if (smg is null)
    {
        MessageBox("Must have a StaticModelGroup component selected.");
        return false;
    }

    uint attrIndex = GetAttributeIndex(smg, "Instance Nodes");
    Variant oldValue = smg.attributes[attrIndex];

    Array<Node@> children = smg.node.GetChildren(true);
    for (uint i = 0; i < children.length; ++i)
        smg.AddInstanceNode(children[i]);

    EditAttributeAction action;
    action.Define(smg, attrIndex, oldValue);
    SaveEditAction(action);
    SetSceneModified();
    FocusComponent(smg);
    
    return true;
}

bool SceneSetChildrenSplinePath(bool makeCycle)
{
    SplinePath@ sp = cast<SplinePath>(editComponents.length > 0 ? editComponents[0] : null);
    if (sp is null && editNode !is null)
        sp = editNode.GetComponent("SplinePath");

    if (sp is null)
    {
        MessageBox("Must have a SplinePath component selected.");
        return false;
    }

    uint attrIndex = GetAttributeIndex(sp, "Control Points");
    Variant oldValue = sp.attributes[attrIndex];

    Array<Node@> children = sp.node.GetChildren(true);
    if (children.length >= 2)
    {
        sp.ClearControlPoints();
        for (uint i = 0; i < children.length; ++i)
            sp.AddControlPoint(children[i]);
    }
    else
    {
        MessageBox("You must have a minimum two children Nodes in selected Node.");
        return false;
    }

    if (makeCycle)
        sp.AddControlPoint(children[0]);

    EditAttributeAction action;
    action.Define(sp, attrIndex, oldValue);
    SaveEditAction(action);
    SetSceneModified();
    FocusComponent(sp);
    
    return true;
}

void AssignMaterial(StaticModel@ model, String materialPath)
{
    Material@ material = cache.GetResource("Material", materialPath);
    if (material is null)
        return;

    ResourceRefList materials = model.GetAttribute("Material").GetResourceRefList();
    Array<String> oldMaterials;
    for(uint i = 0; i < materials.length; ++i)
        oldMaterials.Push(materials.names[i]);

    model.material = material;

    AssignMaterialAction action;
    action.Define(model, oldMaterials, material);
    SaveEditAction(action);
    SetSceneModified();
    FocusComponent(model);
}

void UpdateSceneMru(String filename)
{
    while (uiRecentScenes.Find(filename) > -1)
        uiRecentScenes.Erase(uiRecentScenes.Find(filename));

    uiRecentScenes.Insert(0, filename);

    for (uint i = uiRecentScenes.length - 1; i >= maxRecentSceneCount; i--)
        uiRecentScenes.Erase(i);

    PopulateMruScenes();
}

Drawable@ GetFirstDrawable(Node@ node)
{
    Array<Node@> nodes = node.GetChildren(true);
    nodes.Insert(0, node);

    for (uint i = 0; i < nodes.length; ++i)
    {
        Array<Component@> components = nodes[i].GetComponents();
        for (uint j = 0; j < components.length; ++j)
        {
            Drawable@ drawable = cast<Drawable>(components[j]);
            if (drawable !is null)
                return drawable;
        }
    }
    
    return null;
}

void AssignModel(StaticModel@ assignee, String modelPath)
{
    Model@ model = cache.GetResource("Model", modelPath);
    if (model is null)
        return;

    Model@ oldModel = assignee.model;
    assignee.model = model;

    AssignModelAction action;
    action.Define(assignee, oldModel, model);
    SaveEditAction(action);
    SetSceneModified();
    FocusComponent(assignee); 
}

void CreateModelWithStaticModel(String filepath, Node@ parent)
{
    if (parent is null)
        return;
    /// \todo should be able to specify the createmode
    if (parent is editorScene)
        parent = CreateNode(REPLICATED);

    Model@ model = cache.GetResource("Model", filepath);
    if (model is null)
        return;

    StaticModel@ staticModel = parent.GetOrCreateComponent("StaticModel");
    staticModel.model = model;
    if (applyMaterialList)
        staticModel.ApplyMaterialList();
    CreateLoadedComponent(staticModel);
}

void CreateModelWithAnimatedModel(String filepath, Node@ parent)
{
    if (parent is null)
        return;
    /// \todo should be able to specify the createmode
    if (parent is editorScene)
        parent = CreateNode(REPLICATED);

    Model@ model = cache.GetResource("Model", filepath);
    if (model is null)
        return;

    AnimatedModel@ animatedModel = parent.GetOrCreateComponent("AnimatedModel");
    animatedModel.model = model;
    if (applyMaterialList)
        animatedModel.ApplyMaterialList();
    CreateLoadedComponent(animatedModel);
}

bool ColorWheelSetupBehaviorForColoring()
{    
    Menu@ menu = GetEventSender();
    if (menu is null)
        return false;
    
    coloringPropertyName = menu.name;
    
    if (coloringPropertyName == "menuCancel") return false;
    
    if (coloringComponent.typeName == "Light") 
    {
        Light@ light = cast<Light>(coloringComponent);
        if (light !is null) 
        {          
            if (coloringPropertyName == "menuLightColor")
            {
                coloringOldColor = light.color;
                ShowColorWheelWithColor(coloringOldColor);
            }
            else if (coloringPropertyName == "menuSpecularIntensity")
            {
               // ColorWheel have only 0-1 range output of V-value(BW), and for huge-range values we devide in and multiply out 
               float scaledSpecular = light.specularIntensity * 0.1f; 
               coloringOldScalar = scaledSpecular;
               ShowColorWheelWithColor(Color(scaledSpecular,scaledSpecular,scaledSpecular));

            }
            else if (coloringPropertyName == "menuBrightnessMultiplier")
            { 
               float scaledBrightness = light.brightness * 0.1f;
               coloringOldScalar = scaledBrightness;
               ShowColorWheelWithColor(Color(scaledBrightness,scaledBrightness,scaledBrightness));
            }   
        }      
    }
    else if (coloringComponent.typeName == "StaticModel") 
    {
        StaticModel@ model  = cast<StaticModel>(coloringComponent);
        if (model !is null) 
        {            
            Material@ mat = model.materials[0];
            if (mat !is null) 
            { 
                if (coloringPropertyName == "menuDiffuseColor")
                {
                    Variant oldValue = mat.shaderParameters["MatDiffColor"];
                    Array<String> values = oldValue.ToString().Split(' ');
                    coloringOldColor = Color(values[0].ToFloat(),values[1].ToFloat(),values[2].ToFloat(),values[3].ToFloat()); //RGBA
                    ShowColorWheelWithColor(coloringOldColor);
                }
                else if (coloringPropertyName == "menuSpecularColor")
                {
                    Variant oldValue = mat.shaderParameters["MatSpecColor"];
                    Array<String> values = oldValue.ToString().Split(' ');
                    coloringOldColor = Color(values[0].ToFloat(),values[1].ToFloat(),values[2].ToFloat());
                    coloringOldScalar = values[3].ToFloat();
                    ShowColorWheelWithColor(Color(coloringOldColor.r, coloringOldColor.g, coloringOldColor.b, coloringOldScalar/128.0f)); //RGB + shine
                }
                else if (coloringPropertyName == "menuEmissiveColor")
                {
                    Variant oldValue = mat.shaderParameters["MatEmissiveColor"];
                    Array<String> values = oldValue.ToString().Split(' ');
                    coloringOldColor = Color(values[0].ToFloat(),values[1].ToFloat(),values[2].ToFloat()); // RGB
                    
                    
                    ShowColorWheelWithColor(coloringOldColor);
                }
                else if (coloringPropertyName == "menuEnvironmentMapColor")
                {   
                    Variant oldValue = mat.shaderParameters["MatEnvMapColor"];
                    Array<String> values = oldValue.ToString().Split(' ');
                    coloringOldColor = Color(values[0].ToFloat(),values[1].ToFloat(),values[2].ToFloat()); //RGB
                    
                    ShowColorWheelWithColor(coloringOldColor);
                }      
            }
        }
    }
    else if (coloringComponent.typeName == "Zone") 
    {
        Zone@ zone  = cast<Zone>(coloringComponent);
        if (zone !is null) 
        {
            if (coloringPropertyName == "menuAmbientColor")
            {
                coloringOldColor = zone.ambientColor;
            }
            else if (coloringPropertyName == "menuFogColor") 
            {
                coloringOldColor = zone.fogColor;
            }
            
            ShowColorWheelWithColor(coloringOldColor);
        }
    }
          
    return true;
}

