// Urho3D editor scene hierarchy window handling

const int ITEM_NONE = 0;
const int ITEM_NODE = 1;
const int ITEM_COMPONENT = 2;
const uint NO_ITEM = 0xffffffff;

Window@ sceneWindow;
XMLFile copyBuffer;
bool copyBufferLocal = false;
bool copyBufferExpanded = false;
bool pickComponents = false;
bool pickUsingPhysics = false;

void CreateSceneWindow()
{
    if (sceneWindow !is null)
        return;

    @sceneWindow = ui.LoadLayout(cache.GetResource("XMLFile", "UI/EditorSceneWindow.xml"), uiStyle);
    ui.root.AddChild(sceneWindow);
    int height = Min(ui.root.height - 60, 500);
    sceneWindow.SetSize(300, height);
    sceneWindow.SetPosition(20, 40);
    sceneWindow.BringToFront();
    UpdateSceneWindow();

    DropDownList@ newNodeList = sceneWindow.GetChild("NewNodeList", true);
    Array<String> newNodeChoices = {"Replicated", "Local"};
    for (uint i = 0; i < newNodeChoices.length; ++i)
    {
        Text@ choice = Text();
        choice.SetStyle(uiStyle, "FileSelectorFilterText");
        choice.text = newNodeChoices[i];
        newNodeList.AddItem(choice);
    }

    DropDownList@ newComponentList = sceneWindow.GetChild("NewComponentList", true);
    Array<String> componentTypes = GetAvailableComponents();
    for (uint i = 0; i < componentTypes.length; ++i)
    {
        Text@ choice = Text();
        choice.SetStyle(uiStyle, "FileSelectorFilterText");
        choice.text = componentTypes[i];
        newComponentList.AddItem(choice);
    }

    // Set drag & drop target mode on the node list background, which is used to parent
    // nodes back to the root node
    ListView@ list = sceneWindow.GetChild("NodeList");
    list.contentElement.dragDropMode = DD_TARGET;
    list.scrollPanel.dragDropMode = DD_TARGET;

    SubscribeToEvent(sceneWindow.GetChild("CloseButton", true), "Released", "HideSceneWindow");
    SubscribeToEvent(sceneWindow.GetChild("ExpandAllButton", true), "Released", "ExpandSceneHierarchy");
    SubscribeToEvent(sceneWindow.GetChild("CollapseAllButton", true), "Released", "CollapseSceneHierarchy");
    SubscribeToEvent(sceneWindow.GetChild("NodeList", true), "ItemSelected", "HandleNodeListSelectionChange");
    SubscribeToEvent(sceneWindow.GetChild("NodeList", true), "ItemDeselected", "HandleNodeListSelectionChange");
    SubscribeToEvent(sceneWindow.GetChild("NodeList", true), "ItemDoubleClicked", "HandleNodeListItemDoubleClick");
    SubscribeToEvent(sceneWindow.GetChild("NodeList", true), "UnhandledKey", "HandleNodeListKey");
    SubscribeToEvent(newNodeList, "ItemSelected", "HandleCreateNode");
    SubscribeToEvent(newComponentList, "ItemSelected", "HandleCreateComponent");
    SubscribeToEvent("DragDropTest", "HandleDragDropTest");
    SubscribeToEvent("DragDropFinish", "HandleDragDropFinish");
}

void ShowSceneWindow()
{
    sceneWindow.visible = true;
    sceneWindow.BringToFront();
}

void HideSceneWindow()
{
    sceneWindow.visible = false;
}

void ExpandSceneHierarchy()
{
    ListView@ list = sceneWindow.GetChild("NodeList", true);
    list.SetChildItemsVisible(true);
}

void CollapseSceneHierarchy()
{
    ListView@ list = sceneWindow.GetChild("NodeList", true);
    list.contentElement.DisableLayoutUpdate();
    // Show root-level nodes, but no components
    for (uint i = 0; i < list.numItems; ++i)
    {
        UIElement@ item = list.items[i];
        int indent = item.vars["Indent"].GetInt();
        int type = item.vars["Type"].GetInt();
        if (type == ITEM_COMPONENT || indent > 1)
            item.visible = false;
        else
            item.visible = true;
    }
    list.contentElement.EnableLayoutUpdate();
    list.contentElement.UpdateLayout();
}

void UpdateSceneWindow()
{
    ListView@ list = sceneWindow.GetChild("NodeList", true);
    list.RemoveAllItems();

    UpdateSceneWindowNode(0, editorScene);

    // Clear copybuffer when whole window refreshed
    copyBuffer.CreateRoot("none");
}

uint UpdateSceneWindowNode(uint itemIndex, Node@ node)
{
    ListView@ list = sceneWindow.GetChild("NodeList", true);

    // Whenever we're updating the root, disable layout update to optimize speed
    if (node is editorScene)
        list.contentElement.DisableLayoutUpdate();

    // Remove old item if exists
    if (itemIndex < list.numItems && (node is null || (list.items[itemIndex].vars["Type"].GetInt() == ITEM_NODE &&
        list.items[itemIndex].vars["NodeID"].GetUInt() == node.id)))
        list.RemoveItem(itemIndex);
    if (node is null)
        return itemIndex;

    int indent = GetNodeIndent(node);

    Text@ text = Text();
    text.SetStyle(uiStyle, "FileSelectorListText");
    text.vars["Type"] = ITEM_NODE;
    text.vars["NodeID"] = node.id;
    text.vars["Indent"] = indent;
    text.text = GetNodeTitle(node, indent);
    // Nodes can be moved by drag and drop. The root node (scene) can not.
    if (node.typeName == "Node")
        text.dragDropMode = DD_SOURCE_AND_TARGET;
    else
        text.dragDropMode = DD_TARGET;

    list.InsertItem(itemIndex, text);

    ++itemIndex;

    // Update components first
    for (uint j = 0; j < node.numComponents; ++j)
    {
        Component@ component = node.components[j];
        AddComponentToSceneWindow(component, indent + 1, itemIndex);
        ++itemIndex;
    }

    // Then update child nodes recursively
    for (uint i = 0; i < node.numChildren; ++i)
    {
        Node@ childNode = node.children[i];
        itemIndex = UpdateSceneWindowNode(itemIndex, childNode);
    }

    // Re-enable layout update (and do manual layout) now
    if (node is editorScene)
    {
        list.contentElement.EnableLayoutUpdate();
        list.contentElement.UpdateLayout();
    }

    return itemIndex;
}

void UpdateSceneWindowNodeOnly(uint itemIndex, Node@ node)
{
    ListView@ list = sceneWindow.GetChild("NodeList", true);

    int indent = GetNodeIndent(node);

    Text@ text = list.items[itemIndex];
    if (text is null)
        return;
    text.text = GetNodeTitle(node, indent);
}

void UpdateSceneWindowNode(Node@ node)
{
    uint index = GetNodeListIndex(node);
    UpdateSceneWindowNode(index, node);
}

void UpdateSceneWindowNodeOnly(Node@ node)
{
    uint index = GetNodeListIndex(node);
    UpdateSceneWindowNodeOnly(index, node);
}

void AddComponentToSceneWindow(Component@ component, int indent, uint compItemIndex)
{
    ListView@ list = sceneWindow.GetChild("NodeList", true);

    Text@ text = Text();
    text.SetStyle(uiStyle, "FileSelectorListText");
    text.vars["Type"] = ITEM_COMPONENT;
    text.vars["NodeID"] = component.node.id;
    text.vars["ComponentID"] = component.id;
    text.vars["Indent"] = indent;
    text.text = GetComponentTitle(component, indent);
    list.InsertItem(compItemIndex, text);
}

uint GetNodeListIndex(Node@ node)
{
    if (node is null)
        return NO_ITEM;

    ListView@ list = sceneWindow.GetChild("NodeList", true);
    uint numItems = list.numItems;
    uint nodeID = node.id;

    for (uint i = 0; i < numItems; ++i)
    {
        UIElement@ item = list.items[i];
        if (item.vars["Type"].GetInt() == ITEM_NODE && item.vars["NodeID"].GetUInt() == nodeID)
            return i;
    }

    return NO_ITEM;
}

uint GetParentAddIndex(Node@ node)
{
    if (node is null || node.parent is null)
        return NO_ITEM;

    ListView@ list = sceneWindow.GetChild("NodeList", true);
    uint numItems = list.numItems;
    uint parentID = node.parent.id;

    for (uint i = 0; i < numItems; ++i)
    {
        UIElement@ item = list.items[i];
        if (item.vars["Type"].GetInt() == ITEM_NODE && item.vars["NodeID"].GetUInt() == parentID)
        {
            int indent = item.vars["Indent"].GetInt();
            for (uint j = i + 1; j < numItems; ++j)
            {
                // Scan for the next node on this or lower level; that is the place to insert the new child node
                if (list.items[j].vars["Indent"].GetInt() <= indent)
                    return j;
            }
            return numItems;
        }
    }

    return NO_ITEM;
}

uint GetNodeListIndex(Node@ node, uint startPos)
{
    if (node is null)
        return NO_ITEM;

    ListView@ list = sceneWindow.GetChild("NodeList", true);
    uint numItems = list.numItems;
    uint nodeID = node.id;

    for (uint i = startPos; i < numItems; --i)
    {
        UIElement@ item = list.items[i];
        if (item.vars["Type"].GetInt() == ITEM_NODE && item.vars["NodeID"].GetInt() == int(nodeID))
            return i;
    }

    return NO_ITEM;
}

Node@ GetListNode(uint index)
{
    ListView@ list = sceneWindow.GetChild("NodeList", true);
    UIElement@ item = list.items[index];
    if (item is null)
        return null;

    return editorScene.GetNode(item.vars["NodeID"].GetUInt());
}

Component@ GetListComponent(uint index)
{
    ListView@ list = sceneWindow.GetChild("NodeList", true);
    UIElement@ item = list.items[index];
    return GetListComponent(item);
}

Component@ GetListComponent(UIElement@ item)
{
    if (item is null)
        return null;

    if (item.vars["Type"].GetInt() != ITEM_COMPONENT)
        return null;

    return editorScene.GetComponent(item.vars["ComponentID"].GetUInt());
}

uint GetComponentListIndex(Component@ component)
{
    if (component is null)
        return NO_ITEM;

    ListView@ list = sceneWindow.GetChild("NodeList", true);
    uint numItems = list.numItems;

    for (uint i = 0; i < numItems; ++i)
    {
        UIElement@ item = list.items[i];
        if (item.vars["Type"].GetInt() == ITEM_COMPONENT && item.vars["ComponentID"].GetUInt() == component.id)
            return i;
    }

    return NO_ITEM;
}

int GetNodeIndent(Node@ node)
{
    int indent = 0;
    for (;;)
    {
        if (node.parent is null)
            break;
        ++indent;
        node = node.parent;
    }
    return indent;
}

String GetNodeTitle(Node@ node, int indent)
{
    String indentStr;
    String localStr;
    indentStr.Resize(indent);
    for (int i = 0; i < indent; ++i)
        indentStr[i] = ' ';

    if (node.id >= FIRST_LOCAL_ID)
        localStr = ", Local";

    if (node.name.empty)
        return indentStr + node.typeName + " (" + node.id + localStr + ")";
    else
        return indentStr + node.name + " (" + node.id + localStr + ")";
}

String GetComponentTitle(Component@ component, int indent)
{
    String indentStr;
    String localStr;
    indentStr.Resize(indent);
    for (int i = 0; i < indent; ++i)
        indentStr[i] = ' ';
    
    if (component.id >= FIRST_LOCAL_ID)
        localStr = " (Local)";

    return indentStr + component.typeName + localStr;
}

void SelectNode(Node@ node)
{
    ListView@ list = sceneWindow.GetChild("NodeList", true);

    if (node is null)
    {
        list.ClearSelection();
        return;
    }
                                
    uint nodeItem = GetNodeListIndex(node);

    // Go in the parent chain up to the first non-root level to make sure the chain is expanded
    for (;;)
    {
        Node@ parent = node.parent;
        if (node is editorScene || parent is editorScene || parent is null)
            break;
        node = parent;
    }
    
    uint numItems = list.numItems;
    uint parentItem = GetNodeListIndex(node);

    if (nodeItem < numItems)
    {
        // Expand the node chain now, but do not expand the whole scene in case the component was in the root
        list.items[nodeItem].visible = true;
        if (parentItem != 0 && parentItem < numItems)
            list.SetChildItemsVisible(parentItem, true);
        // This causes an event to be sent, in response we set selectedComponent & selectedNode, and refresh editors
        list.selection = nodeItem;
    }
    else
        list.ClearSelection();
}

void SelectComponent(Component@ component)
{
    ListView@ list = sceneWindow.GetChild("NodeList", true);

    if (component is null)
    {
        list.ClearSelection();
        return;
    }
    Node@ node = component.node;
    if (node is null)
    {
        list.ClearSelection();
        return;
    }

    // Go in the parent chain up to the first non-root level to make sure the chain is expanded
    for (;;)
    {
        Node@ parent = node.parent;
        if (node is editorScene || parent is editorScene || parent is null)
            break;
        node = parent;
    }

    uint numItems = list.numItems;
    uint nodeItem = GetNodeListIndex(node);
    uint componentItem = GetComponentListIndex(component);

    if (nodeItem < numItems && componentItem < numItems)
    {
        // Expand the node chain now, but do not expand the whole scene in case the component was in the root
        list.items[nodeItem].visible = true;
        if (nodeItem != 0)
            list.SetChildItemsVisible(nodeItem, true);
        list.items[componentItem].visible = true;
        // This causes an event to be sent, in response we set selectedComponent & selectedNode, and refresh editors
        list.selection = componentItem;
    }
    else
        list.ClearSelection();
}

void HandleNodeListSelectionChange()
{
    ListView@ list = sceneWindow.GetChild("NodeList", true);

    uint index = list.selection;
    selectedNode = GetListNode(index);
    selectedComponent = GetListComponent(index);

    UpdateNodeWindow();
}

void HandleNodeListItemDoubleClick(StringHash eventType, VariantMap& eventData)
{
    ListView@ list = sceneWindow.GetChild("NodeList", true);

    uint index = eventData["Selection"].GetUInt();
    if (index == 0)
    {
        if (list.numItems > 1 && list.items[1].visible == true)
            CollapseSceneHierarchy();
        else
            list.ToggleChildItemsVisible(index);
    }
    else
        list.ToggleChildItemsVisible(index);
}

void HandleNodeListKey(StringHash eventType, VariantMap& eventData)
{
    int key = eventData["Key"].GetInt();

    /// \todo Add required functionality
}

void HandleDragDropTest(StringHash eventType, VariantMap& eventData)
{
    UIElement@ source = eventData["Source"].GetUIElement();
    UIElement@ target = eventData["Target"].GetUIElement();
    eventData["Accept"] = TestSceneWindowElements(source, target);
}

void HandleDragDropFinish(StringHash eventType, VariantMap& eventData)
{
    UIElement@ source = eventData["Source"].GetUIElement();
    UIElement@ target = eventData["Target"].GetUIElement();
    bool accept =  TestSceneWindowElements(source, target);
    eventData["Accept"] = accept;
    if (!accept)
        return;

    Node@ sourceNode = editorScene.GetNode(source.vars["NodeID"].GetUInt());
    Node@ targetNode = editorScene.GetNode(target.vars["NodeID"].GetUInt());

    // If target is null, parent to scene
    if (targetNode is null)
        targetNode = editorScene;

    // Perform the reparenting
    // Set transform so that the world transform stays through the parent change
    BeginModify(targetNode.id);
    BeginModify(sourceNode.id);

    Vector3 newPos;
    Quaternion newRot;
    Vector3 newScale;
    CalculateNewTransform(sourceNode, targetNode, newPos, newRot, newScale);
    sourceNode.parent = targetNode;

    // Verify success
    if (sourceNode.parent !is targetNode)
    {
        EndModify(sourceNode.id);
        EndModify(targetNode.id);
        return;
    }

    sourceNode.SetTransform(newPos, newRot, newScale);

    EndModify(sourceNode.id);
    EndModify(targetNode.id);

    // Update the node list now. If a node was moved into the root, this potentially refreshes the whole scene window.
    // Therefore disable layout update first
    ListView@ list = sceneWindow.GetChild("NodeList", true);

    uint sourceIndex = GetNodeListIndex(sourceNode);
    bool expanded = SaveExpandedStatus(sourceIndex);
    list.RemoveItem(sourceIndex);
    uint addIndex = GetParentAddIndex(sourceNode);
    UpdateSceneWindowNode(addIndex, sourceNode);
    RestoreExpandedStatus(addIndex, expanded);
}

bool TestSceneWindowElements(UIElement@ source, UIElement@ target)
{
    // Test for validity of reparenting by drag and drop
    Node@ sourceNode;
    Node@ targetNode;
    if (source.vars.Contains("NodeID"))
        sourceNode = editorScene.GetNode(source.vars["NodeID"].GetUInt());
    if (target.vars.Contains("NodeID"))
        editorScene.GetNode(target.vars["NodeID"].GetUInt());

    if (sourceNode is null)
        return false;
    if (sourceNode is editorScene)
        return false;
    if (targetNode !is null)
    {
        if (sourceNode.parent is targetNode)
            return false;
        if (targetNode.parent is sourceNode)
            return false;
    }
    
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

void UpdateAndFocusNode(Node@ node)
{
    UpdateSceneWindowNode(node);
    uint index = GetNodeListIndex(node);
    ListView@ list = sceneWindow.GetChild("NodeList", true);
    list.selection = index;
}

void UpdateAndFocusComponent(Component@ component)
{
    UpdateSceneWindowNode(component.node);
    uint index = GetComponentListIndex(component);
    ListView@ list = sceneWindow.GetChild("NodeList", true);
    list.selection = index;
}

void HandleCreateNode(StringHash eventType, VariantMap& eventData)
{
    DropDownList@ list = eventData["Element"].GetUIElement();
    uint mode = list.selection;
    if (mode >= list.numItems)
        return;

    Node@ newNode = editorScene.CreateChild("", mode == 0 ? REPLICATED : LOCAL);
    // Set the new node a certain distance from the camera
    newNode.position = GetNewNodePosition();

    UpdateAndFocusNode(newNode);
}

void HandleCreateComponent(StringHash eventType, VariantMap& eventData)
{
    if (selectedNode is null)
        return;

    DropDownList@ list = eventData["Element"].GetUIElement();
    Text@ text = list.selectedItem;
    if (text is null)
        return;

    // If this is the root node, do not allow to create duplicate scene-global components
    if (selectedNode is editorScene && CheckForExistingGlobalComponent(selectedNode, text.text))
        return;

    // For now, make a local node's all components local
    /// \todo Allow to specify the createmode
    Component@ newComponent = selectedNode.CreateComponent(text.text, selectedNode.id < FIRST_LOCAL_ID ? REPLICATED : LOCAL);

    UpdateAndFocusComponent(newComponent);
}

bool CheckSceneWindowFocus()
{
    // When we do scene operations based on key shortcuts, make sure either the 3D scene or the node list is focused,
    // not for example a file selector
    ListView@ list = sceneWindow.GetChild("NodeList", true);
    if (ui.focusElement is list || ui.focusElement is null)
        return true;
    else
        return false;
}

bool CheckForExistingGlobalComponent(Node@ node, const String&in typeName)
{
    if (typeName != "Octree" && typeName != "PhysicsWorld" && typeName != "DebugRenderer")
        return false;
    else
        return node.HasComponent(typeName);
}

void SceneDelete()
{
    if (selectedNode is null || !CheckSceneWindowFocus())
        return;

    ListView@ list = sceneWindow.GetChild("NodeList", true);
    uint index = list.selection;
    uint nodeIndex = GetNodeListIndex(selectedNode);

    // Remove component
    if (selectedComponent !is null)
    {
        // Do not allow to remove the Octree, PhysicsWorld or DebugRenderer from the root node
        if (selectedNode is editorScene && (selectedComponent.typeName == "Octree" || selectedComponent.typeName == 
            "PhysicsWorld" || selectedComponent.typeName == "DebugRenderer"))
            return;

        uint id = selectedNode.id;
        BeginModify(id);
        selectedNode.RemoveComponent(selectedComponent);
        EndModify(id);

        UpdateSceneWindowNode(nodeIndex, selectedNode);

        // Select the next item in the same index
        list.selection = index;
    }
    // Remove (parented) node
    else
    {
        if (selectedNode.parent is null)
            return;

        uint id = selectedNode.id;

        BeginModify(id);
        selectedNode.Remove();
        EndModify(id);

        selectedComponent = null;
        selectedNode = null;

        UpdateSceneWindowNode(nodeIndex, null);

        // Select the next item in the same index
        list.selection = index;
    }
}

void SceneCut()
{
    SceneCopy();
    SceneDelete();
}

void SceneCopy()
{
    if (selectedNode is null || !CheckSceneWindowFocus())
        return;

    ListView@ list = sceneWindow.GetChild("NodeList", true);

    // Copy component
    if (selectedNode !is null && selectedComponent !is null)
    {
        XMLElement rootElem = copyBuffer.CreateRoot("component");
        selectedComponent.SaveXML(rootElem);
        // Note: component type has to be saved manually
        rootElem.SetString("type", selectedComponent.typeName);
        copyBufferLocal = selectedComponent.id >= FIRST_LOCAL_ID;
    }
    // Copy node. The root node can not be copied
    else if (selectedNode !is null && selectedComponent is null && selectedNode !is editorScene)
    {
        XMLElement rootElem = copyBuffer.CreateRoot("node");
        selectedNode.SaveXML(rootElem);
        copyBufferLocal = selectedNode.id >= FIRST_LOCAL_ID;
        copyBufferExpanded = SaveExpandedStatus(GetNodeListIndex(selectedNode));
    }
}

void ScenePaste()
{
    if (selectedNode is null || !CheckSceneWindowFocus())
        return;

    ListView@ list = sceneWindow.GetChild("NodeList", true);
    XMLElement rootElem = copyBuffer.root;
    String mode = rootElem.name;

    if (mode == "component")
    {
        BeginModify(selectedNode.id);

        // If this is the root node, do not allow to create duplicate scene-global components
        if (selectedNode is editorScene && CheckForExistingGlobalComponent(selectedNode, rootElem.GetAttribute("type")))
            return;

        // If copied component was local, make the new local too
        Component@ newComponent = selectedNode.CreateComponent(rootElem.GetAttribute("type"), copyBufferLocal ? LOCAL :
            REPLICATED);
        if (newComponent is null)
        {
            EndModify(selectedNode.id);
            return;
        }
        newComponent.LoadXML(rootElem);
        newComponent.ApplyAttributes();
        EndModify(selectedNode.id);

        UpdateSceneWindowNode(selectedNode);
        list.selection = GetComponentListIndex(newComponent);
    }
    else if (mode == "node")
    {
        // Make the paste go always to the root node, no matter of the selected node
        BeginModify(editorScene.id);
        // If copied node was local, make the new local too
        Node@ newNode = editorScene.CreateChild("", copyBufferLocal ? LOCAL : REPLICATED);
        BeginModify(newNode.id);
        newNode.LoadXML(rootElem);
        newNode.ApplyAttributes();
        EndModify(newNode.id);
        EndModify(editorScene.id);

        uint addIndex = GetParentAddIndex(newNode);
        UpdateSceneWindowNode(addIndex, newNode);
        RestoreExpandedStatus(addIndex, copyBufferExpanded);
        list.selection = addIndex;
    }
}

bool SaveExpandedStatus(uint itemIndex)
{
    ListView@ list = sceneWindow.GetChild("NodeList", true);
    uint nextIndex = itemIndex + 1;
    if (nextIndex < list.numItems && list.items[nextIndex].vars["Indent"].GetInt() > list.items[itemIndex].vars["Indent"].GetInt()
        && list.items[nextIndex].visible == false)
        return false;
    else
        return true;
}

void RestoreExpandedStatus(uint itemIndex, bool expanded)
{
    ListView@ list = sceneWindow.GetChild("NodeList", true);
    list.SetChildItemsVisible(itemIndex, expanded);
}