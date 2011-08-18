// Urho3D editor scene hierarchy window handling

const int ITEM_NONE = 0;
const int ITEM_NODE = 1;
const int ITEM_COMPONENT = 2;
const uint NO_ITEM = 0xffffffff;

Window@ sceneWindow;
uint copyBufferNodeID = 0;
XMLFile copyBuffer;

void CreateSceneWindow()
{
    if (sceneWindow !is null)
        return;

    @sceneWindow = ui.LoadLayout(cache.GetResource("XMLFile", "UI/SceneWindow.xml"), uiStyle);
    ui.root.AddChild(sceneWindow);
    int height = Min(ui.root.height - 60, 500);
    sceneWindow.SetSize(300, height);
    sceneWindow.SetPosition(20, 40);
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
    list.contentElement.DisableLayoutUpdate();
    list.RemoveAllItems();

    UpdateSceneWindowNode(0, editorScene);

    list.contentElement.EnableLayoutUpdate();
    list.contentElement.UpdateLayout();

    // Clear copybuffer when whole window refreshed
    copyBuffer.CreateRoot("none");
}

uint UpdateSceneWindowNode(uint itemIndex, Node@ node)
{
    ListView@ list = sceneWindow.GetChild("NodeList", true);

    // Remove old item if exists
    if (itemIndex < list.numItems && list.items[itemIndex].vars["NodeID"].GetUInt() == node.id)
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
        if (item.vars["Type"].GetInt() == ITEM_NODE && item.vars["NodeID"].GetInt() == int(nodeID))
            return i;
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

    return editorScene.GetNodeByID(item.vars["NodeID"].GetUInt());
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

    return editorScene.GetComponentByID(item.vars["ComponentID"].GetUInt());
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

    if ((nodeItem < numItems) && (componentItem < numItems))
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

    Node@ sourceNode = editorScene.GetNodeByID(source.vars["NodeID"].GetUInt());
    Node@ targetNode = editorScene.GetNodeByID(target.vars["NodeID"].GetUInt());

    // Perform the reparenting
    // Set transform so that the world transform stays through the parent change
    BeginModify(sourceNode.id);
    BeginModify(targetNode.id);

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
    list.contentElement.DisableLayoutUpdate();

    uint sourceIndex = GetNodeListIndex(sourceNode);
    list.RemoveItem(sourceIndex);
    UpdateSceneWindowNode(targetNode);

    list.contentElement.EnableLayoutUpdate();
    list.contentElement.UpdateLayout();
}

bool TestSceneWindowElements(UIElement@ source, UIElement@ target)
{
    // Test for validity of reparenting by drag and drop
    Node@ sourceNode = editorScene.GetNodeByID(source.vars["NodeID"].GetUInt());
    Node@ targetNode = editorScene.GetNodeByID(target.vars["NodeID"].GetUInt());

    if (sourceNode is null || targetNode is null)
        return false;
    if (sourceNode is targetNode)
        return false;
    if (sourceNode.parent is targetNode)
        return false;
    if (targetNode.parent is sourceNode)
        return false;
    
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
    Print("CreateNode");
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

    // For now, make a local node's all components local
    /// \todo Allow to specify the createmode
    Component@ newComponent = selectedNode.CreateComponent(text.text, selectedNode.id < FIRST_LOCAL_ID ? REPLICATED : LOCAL);

    UpdateAndFocusComponent(newComponent);
}

bool CheckSceneWindowFocus(bool allowNoElement)
{
    ListView@ list = sceneWindow.GetChild("NodeList", true);
    UIElement@ focusElement = ui.focusElement;
    if (focusElement is list)
        return true;
    if (focusElement !is null)
        return false;
    return allowNoElement;
}

void SceneDelete()
{
    ListView@ list = sceneWindow.GetChild("NodeList", true);
    uint index = list.selection;
    uint nodeIndex = GetNodeListIndex(selectedNode);
    
    // Remove component
    if (selectedNode !is null && selectedComponent !is null)
    {
        if (!CheckSceneWindowFocus(true))
            return;

        // For the sake of sanity, do not allow to delete the octree from the scene
        if (selectedNode is editorScene && selectedComponent.typeName == "Octree" && selectedComponent is selectedNode.GetComponents("Octree")[0])
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
    else if (selectedNode !is null && selectedComponent is null)
    {
        // Require the scene hierarchy to be focused
        if (!CheckSceneWindowFocus(false))
            return;
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
    /*
    // Copy component
    if ((selectedNode !is null) && (selectedComponent !is null))
    {
        if (!checkSceneWindowFocus(true))
            return;
        
        XMLElement rootElem = copyBuffer.createRootElement("component");
        selectedComponent.saveXML(rootElem);
        
        // If component is a node, save the world transform instead, and delete the parent reference
        Node@ node = cast<Node>(selectedComponent);
        if (node !is null)
        {
            XMLElement transformElem = rootElem.GetChildElement("transform");
            transformElem.SetVector3("pos", node.worldPosition);
            transformElem.SetVector3("rot", node.worldRotation.GetEulerAngles());
            transformElem.SetVector3("scale", node.worldScale);
            rootElem.removeChildElement("parent", false);
        }
        
        copyBufferNodeID = selectedNode.id;
    }
    // Copy node
    else if ((selectedNode !is null) && (selectedComponent is null))
    {
        if (!checkSceneWindowFocus(false))
            return;
        
        XMLElement rootElem = copyBuffer.createRootElement("node");
        selectedNode.saveXML(rootElem);
        copyBufferNodeID = selectedNode.id;
    }
    */
}

void ScenePaste()
{
    /*
    XMLElement rootElem = copyBuffer.GetRootElement();
    String mode = rootElem.GetName();
    
    if ((mode == "component") && (selectedNode !is null))
    {
        if (!checkSceneWindowFocus(true))
            return;
        
        beginModify(selectedNode.id);
        
        Component@ newComponent = selectedNode.createComponent(rootElem.GetAttribute("type"), rootElem.GetAttribute("name"));
        if (newComponent is null)
            return;
        newComponent.loadXML(rootElem);
        newComponent.postLoad();
        
        // If component is a scene node, parent it to the selected component if exists
        Node@ selectedNode = cast<Node>(selectedComponent);
        Node@ newNode = cast<Node>(newComponent);
        if ((newNode !is null) && (selectedNode !is null))
        {
            Vector3 pos;
            Quaternion rot;
            Vector3 scale;
            calculateNewTransform(newNode, selectedNode, pos, rot, scale);
            newNode.SetTransform(pos, rot, scale);
            selectedNode.addChild(newNode);
        }
        
        endModify(selectedNode.id);
        
        updateSceneWindowNode(selectedNode);
    }
    else if (mode == "node")
    {
        if (!checkSceneWindowFocus(false))
            return;
        
        // If copied node was local, make the new local too
        Node@ newNode = editorScene.createNode(rootElem.GetAttribute("name"), copyBufferNodeID >= 65536);
        uint newNodeID = newNode.id;
        
        beginModify(newNodeID);

        // Before loading, rewrite scene node references to the copied node
        XMLElement compElem = rootElem.GetChildElement("component");
        bool rewrite = false;
        while (compElem.notNull())
        {
            XMLElement parentElem = compElem.GetChildElement("parent");
            if ((parentElem.notNull()) && (uint(parentElem.GetInt("id")) == copyBufferNodeID))
            {
                parentElem.SetInt("id", newNodeID);
                rewrite = true;
            }
            compElem = compElem.GetNextElement("component");
        }
        
        // If we modified the copybuffer, change the "stored ID" value to reflect the change
        if (rewrite)
            copyBufferNodeID = newNode.id;
        
        newNode.loadXML(rootElem);
        newNode.postLoad();
        
        endModify(newNodeID);
        
        updateAndFocusNode(newNode);
    }
    */
}

