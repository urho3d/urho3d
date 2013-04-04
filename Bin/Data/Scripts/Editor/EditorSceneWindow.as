// Urho3D editor hierarchy window handling

const int ITEM_NONE = 0;
const int ITEM_NODE = 1;
const int ITEM_COMPONENT = 2;
const int ITEM_UI_ELEMENT = 3;
const uint NO_ITEM = M_MAX_UNSIGNED;
const ShortStringHash SCENE_TYPE("Scene");
const ShortStringHash NODE_TYPE("Node");
const String NO_CHANGE(uint8(0));
const ShortStringHash TYPE_VAR("Type");
const ShortStringHash NODE_ID_VAR("NodeID");
const ShortStringHash COMPONENT_ID_VAR("ComponentID");
const ShortStringHash UI_ELEMENT_ID_VAR("__UIElementID");

Window@ hierarchyWindow;
ListView@ hierarchyList;

// UIElement does not have unique ID, so use a running number to generate a new ID each time an item is inserted into hierarchy list
uint uiElementNextID = 1;

void CreateHierarchyWindow()
{
    if (hierarchyWindow !is null)
        return;

    hierarchyWindow = ui.LoadLayout(cache.GetResource("XMLFile", "UI/EditorSceneWindow.xml"));
    hierarchyList = hierarchyWindow.GetChild("HierarchyList");
    ui.root.AddChild(hierarchyWindow);
    int height = Min(ui.root.height - 60, 500);
    hierarchyWindow.SetSize(300, height);
    hierarchyWindow.SetPosition(20, 40);
    hierarchyWindow.opacity = uiMaxOpacity;
    hierarchyWindow.BringToFront();

    UpdateHierarchyItem(editorScene);

    // Set drag & drop target mode on the node list background, which is used to parent nodes back to the root node
    hierarchyList.contentElement.dragDropMode = DD_TARGET;
    hierarchyList.scrollPanel.dragDropMode = DD_TARGET;

    SubscribeToEvent(hierarchyWindow.GetChild("CloseButton", true), "Released", "HideHierarchyWindow");
    SubscribeToEvent(hierarchyWindow.GetChild("ExpandButton", true), "Released", "ExpandCollapseHierarchy");
    SubscribeToEvent(hierarchyWindow.GetChild("CollapseButton", true), "Released", "ExpandCollapseHierarchy");
    SubscribeToEvent(hierarchyList, "SelectionChanged", "HandleHierarchyListSelectionChange");
    SubscribeToEvent(hierarchyList, "ItemDoubleClicked", "HandleHierarchyListItemDoubleClick");
    SubscribeToEvent("DragDropTest", "HandleDragDropTest");
    SubscribeToEvent("DragDropFinish", "HandleDragDropFinish");
    SubscribeToEvent(editorScene, "NodeAdded", "HandleNodeAdded");
    SubscribeToEvent(editorScene, "NodeRemoved", "HandleNodeRemoved");
    SubscribeToEvent(editorScene, "ComponentAdded", "HandleComponentAdded");
    SubscribeToEvent(editorScene, "ComponentRemoved", "HandleComponentRemoved");
    SubscribeToEvent(editorScene, "NodeNameChanged", "HandleNodeNameChanged");
    SubscribeToEvent(editorScene, "NodeEnabledChanged", "HandleNodeEnabledChanged");
    SubscribeToEvent(editorScene, "ComponentEnabledChanged", "HandleComponentEnabledChanged");
}

bool ShowHierarchyWindow()
{
    hierarchyWindow.visible = true;
    hierarchyWindow.BringToFront();
    return true;
}

void HideHierarchyWindow()
{
    hierarchyWindow.visible = false;
}

void ExpandCollapseHierarchy(StringHash eventType, VariantMap& eventData)
{
    Button@ button = eventData["Element"].GetUIElement();
    bool enable = button.name == "ExpandButton";
    CheckBox@ checkBox = cast<CheckBox>(hierarchyWindow.GetChild("AllCheckBox", true));
    bool all = checkBox.checked;
    checkBox.checked = false;    // Auto-reset

    Array<uint> selections = hierarchyList.selections;
    for (uint i = 0; i < selections.length; ++i)
        hierarchyList.Expand(selections[i], enable, all);
}

void EnableExpandCollapseButtons(bool enable)
{
    String[] buttons = { "ExpandButton", "CollapseButton", "AllCheckBox" };
    for (uint i = 0; i < buttons.length; ++i)
    {
        UIElement@ element = hierarchyWindow.GetChild(buttons[i], true);
        element.enabled = enable;
        element.children[0].color = enable ? normalTextColor : nonEditableTextColor;
    }
}

void UpdateHierarchyItem(Serializable@ serializable, bool clear = false)
{
    if (clear)
    {
        // Remove the current selection before updating the list item (in turn trigger an update on the attribute editor)
        hierarchyList.ClearSelection();

        // Clear copybuffer when whole window refreshed
        copyBuffer.Clear();
    }

    // In case of item's parent is not found in the hierarchy list then the item will be inserted at the list root level
    Serializable@ parent;
    if (serializable.type == NODE_TYPE || serializable.type == SCENE_TYPE)
        parent = cast<Node>(serializable).parent;
    else if (serializable !is editorUIElement)
        parent = cast<UIElement>(serializable).parent;
    UIElement@ parentItem = hierarchyList.items[GetListIndex(parent)];
    UpdateHierarchyItem(GetListIndex(serializable), serializable, parentItem);
}

uint UpdateHierarchyItem(uint itemIndex, Serializable@ serializable, UIElement@ parentItem)
{
    // Whenever we're updating, disable layout update to optimize speed
    hierarchyList.contentElement.DisableLayoutUpdate();

    ShortStringHash idVar;
    Variant id;
    int itemType = ITEM_NONE;
    if (serializable !is null)
        GetID(serializable, idVar, id, itemType);

    // Remove old item if exists
    if (itemIndex < hierarchyList.numItems && (serializable is null || MatchID(hierarchyList.items[itemIndex], idVar, id, itemType)))
        hierarchyList.RemoveItem(itemIndex);
    if (serializable is null)
    {
        hierarchyList.contentElement.EnableLayoutUpdate();
        hierarchyList.contentElement.UpdateLayout();
        return itemIndex;
    }

    Text@ text = Text();
    text.SetStyle(uiStyle, "FileSelectorListText");
    SetID(text, serializable);

    // The root node (scene) and editor's root UIElement cannot be moved by drag and drop.
    if (serializable.type == SCENE_TYPE || serializable is editorUIElement)
        text.dragDropMode = DD_TARGET;
    else
        text.dragDropMode = DD_SOURCE_AND_TARGET;

    hierarchyList.InsertItem(itemIndex, text, parentItem);

    // Advance the index for the child items
    if (itemIndex == M_MAX_UNSIGNED)
        itemIndex = hierarchyList.numItems;
    else
        ++itemIndex;

    String iconType = serializable.typeName;
    if (serializable is editorUIElement)
        iconType = "Root" + iconType;
    IconizeUIElement(text, iconType);

    if (serializable.type == NODE_TYPE || serializable.type == SCENE_TYPE)
    {
        Node@ node = cast<Node>(serializable);

        text.text = GetNodeTitle(node);
        SetIconEnabledColor(text, node.enabled);

        // Update components first
        for (uint i = 0; i < node.numComponents; ++i)
        {
            Component@ component = node.components[i];
            AddComponentItem(itemIndex++, component, text);
        }

        // Then update child nodes recursively
        for (uint i = 0; i < node.numChildren; ++i)
        {
            Node@ childNode = node.children[i];
            itemIndex = UpdateHierarchyItem(itemIndex, childNode, text);
        }
    }
    else
    {
        UIElement@ element = cast<UIElement>(serializable);

        text.text = GetUIElementTitle(element);
        SetIconEnabledColor(text, element.visible);

        // Then update child elements recursively
        for (uint i = 0; i < element.numChildren; ++i)
        {
            UIElement@ childElement = element.children[i];
            itemIndex = UpdateHierarchyItem(itemIndex, childElement, text);
        }
    }

    // Re-enable layout update (and do manual layout) now
    hierarchyList.contentElement.EnableLayoutUpdate();
    hierarchyList.contentElement.UpdateLayout();

    return itemIndex;
}

void UpdateHierarchyItemText(uint itemIndex, bool iconEnabled, const String&in textTitle = NO_CHANGE)
{
    Text@ text = hierarchyList.items[itemIndex];
    if (text is null)
        return;

    SetIconEnabledColor(text, iconEnabled);

    if (textTitle != NO_CHANGE)
        text.text = textTitle;
}

void AddComponentItem(uint compItemIndex, Component@ component, UIElement@ parentItem)
{
    Text@ text = Text();
    text.SetStyle(uiStyle, "FileSelectorListText");
    text.vars[TYPE_VAR] = ITEM_COMPONENT;
    text.vars[NODE_ID_VAR] = component.node.id;
    text.vars[COMPONENT_ID_VAR] = component.id;
    text.text = GetComponentTitle(component);

    hierarchyList.InsertItem(compItemIndex, text, parentItem);
    IconizeUIElement(text, component.typeName);
    SetIconEnabledColor(text, component.enabledEffective);
}

void SetID(Text@ text, Serializable@ serializable)
{
    if (serializable.type == NODE_TYPE || serializable.type == SCENE_TYPE)
    {
        text.vars[TYPE_VAR] = ITEM_NODE;
        text.vars[NODE_ID_VAR] = cast<Node>(serializable).id;
    }
    else
    {
        UIElement@ element = cast<UIElement>(serializable);
        Variant elementID = element.GetVar(UI_ELEMENT_ID_VAR);
        if (elementID.empty)
        {
            // Generate new ID
            elementID = uiElementNextID++;
            // Store the generated ID into the variant map of the actual serializable object
            element.vars[UI_ELEMENT_ID_VAR] = elementID;
        }

        text.vars[TYPE_VAR] = ITEM_UI_ELEMENT;
        text.vars[UI_ELEMENT_ID_VAR] = elementID;

        // Subscribe to name and visibility changed events
        SubscribeToEvent(serializable, "NameChanged", "HandleElementNameChanged");
        SubscribeToEvent(serializable, "VisibleChanged", "HandleElementVisibilityChanged");
    }
}

void GetID(Serializable@ serializable, ShortStringHash& idVar, Variant& id, int& itemType)
{
    if (serializable.type == NODE_TYPE || serializable.type == SCENE_TYPE)
    {
        idVar = NODE_ID_VAR;
        id = Variant(cast<Node>(serializable).id);
        itemType = ITEM_NODE;
    }
    else
    {
        idVar = UI_ELEMENT_ID_VAR;
        id = cast<UIElement>(serializable).vars[UI_ELEMENT_ID_VAR];
        itemType = ITEM_UI_ELEMENT;
    }
}

bool MatchID(UIElement@ element, const ShortStringHash&in idVar, const Variant&in id, int itemType)
{
    return element.vars[TYPE_VAR].GetInt() == itemType && element.vars[idVar] == id;
}

uint GetListIndex(Serializable@ serializable)
{
    if (serializable is null)
        return NO_ITEM;

    uint numItems = hierarchyList.numItems;

    ShortStringHash idVar;
    Variant id;
    int itemType = ITEM_NONE;
    GetID(serializable, idVar, id, itemType);

    for (uint i = 0; i < numItems; ++i)
    {
        UIElement@ item = hierarchyList.items[i];
        if (MatchID(item, idVar, id, itemType))
            return i;
    }

    return NO_ITEM;
}

UIElement@ GetListUIElement(uint index)
{
    UIElement@ item = hierarchyList.items[index];
    if (item is null)
        return null;

    return editorUIElement.GetChild(UI_ELEMENT_ID_VAR, item.vars[UI_ELEMENT_ID_VAR], true);
}

Node@ GetListNode(uint index)
{
    UIElement@ item = hierarchyList.items[index];
    if (item is null)
        return null;

    return editorScene.GetNode(item.vars[NODE_ID_VAR].GetUInt());
}

Component@ GetListComponent(uint index)
{
    UIElement@ item = hierarchyList.items[index];
    return GetListComponent(item);
}

Component@ GetListComponent(UIElement@ item)
{
    if (item is null)
        return null;

    if (item.vars[TYPE_VAR].GetInt() != ITEM_COMPONENT)
        return null;

    return editorScene.GetComponent(item.vars[COMPONENT_ID_VAR].GetUInt());
}

uint GetComponentListIndex(Component@ component)
{
    if (component is null)
        return NO_ITEM;

    uint numItems = hierarchyList.numItems;
    for (uint i = 0; i < numItems; ++i)
    {
        UIElement@ item = hierarchyList.items[i];
        if (item.vars[TYPE_VAR].GetInt() == ITEM_COMPONENT && item.vars[COMPONENT_ID_VAR].GetUInt() == component.id)
            return i;
    }

    return NO_ITEM;
}

String GetUIElementTitle(UIElement@ element)
{
    String elementID = element.vars[UI_ELEMENT_ID_VAR].ToString();
    return (element.name.empty ? element.typeName : element.name) + " [" + elementID + "]";
}

String GetNodeTitle(Node@ node)
{
    String idStr;
    if (node.id >= FIRST_LOCAL_ID)
        idStr = "Local " + String(node.id - FIRST_LOCAL_ID);
    else
        idStr = String(node.id);

    if (node.name.empty)
        return node.typeName + " (" + idStr + ")";
    else
        return node.name + " (" + idStr + ")";
}

String GetComponentTitle(Component@ component)
{
    String localStr;
    if (component.id >= FIRST_LOCAL_ID)
        localStr = " (Local)";

    return component.typeName + localStr;
}

void SelectNode(Node@ node, bool multiselect)
{
    if (node is null && !multiselect)
    {
        hierarchyList.ClearSelection();
        return;
    }

    uint nodeItem = GetListIndex(node);

    // Go in the parent chain up to make sure the chain is expanded
    for (;;)
    {
        Node@ parent = node.parent;
        if (node is editorScene || parent is null)
            break;
        node = parent;
    }

    uint numItems = hierarchyList.numItems;
    uint parentItem = GetListIndex(node);

    if (nodeItem < numItems)
    {
        // Expand the node chain now
        if (!multiselect || !hierarchyList.IsSelected(nodeItem))
        {
            if (parentItem < numItems)
                hierarchyList.Expand(parentItem, true);
            hierarchyList.Expand(nodeItem, true);
        }
        // This causes an event to be sent, in response we set the node/component selections, and refresh editors
        if (!multiselect)
            hierarchyList.selection = nodeItem;
        else
            hierarchyList.ToggleSelection(nodeItem);
    }
    else
    {
        if (!multiselect)
            hierarchyList.ClearSelection();
    }
}

void SelectComponent(Component@ component, bool multiselect)
{
    if (component is null && !multiselect)
    {
        hierarchyList.ClearSelection();
        return;
    }

    Node@ node = component.node;
    if (node is null && !multiselect)
    {
        hierarchyList.ClearSelection();
        return;
    }

    uint nodeItem = GetListIndex(node);
    uint componentItem = GetComponentListIndex(component);

    // Go in the parent chain up to make sure the chain is expanded
    for (;;)
    {
        Node@ parent = node.parent;
        if (node is editorScene || parent is null)
            break;
        node = parent;
    }

    uint numItems = hierarchyList.numItems;
    uint parentItem = GetListIndex(node);

    if (parentItem >= hierarchyList.numItems && !multiselect)
    {
        hierarchyList.ClearSelection();
        return;
    }

    if (nodeItem < numItems && componentItem < numItems)
    {
        // Expand the node chain now
        if (!multiselect || !hierarchyList.IsSelected(componentItem))
        {
            if (parentItem < numItems)
                hierarchyList.Expand(parentItem, true);
            hierarchyList.Expand(nodeItem, true);
        }
        // This causes an event to be sent, in response we set the node/component selections, and refresh editors
        if (!multiselect)
            hierarchyList.selection = componentItem;
        else
            hierarchyList.ToggleSelection(componentItem);
    }
    else
    {
        if (!multiselect)
            hierarchyList.ClearSelection();
    }
}

void HandleHierarchyListSelectionChange()
{
    if (inSelectionModify)
        return;

    ClearSceneSelection();
    ClearUIElementSelection();

    Array<uint> indices = hierarchyList.selections;

    // Enable Expand/Collapse button when there is selection
    EnableExpandCollapseButtons(indices.length > 0);

    for (uint i = 0; i < indices.length; ++i)
    {
        uint index = indices[i];
        UIElement@ item = hierarchyList.items[index];
        int type = item.vars[TYPE_VAR].GetInt();
        if (type == ITEM_COMPONENT)
        {
            Component@ comp = GetListComponent(index);
            if (comp !is null)
                selectedComponents.Push(comp);
        }
        else if (type == ITEM_NODE)
        {
            Node@ node = GetListNode(index);
            if (node !is null)
                selectedNodes.Push(node);
        }
        else if (type == ITEM_UI_ELEMENT)
        {
            UIElement@ element = GetListUIElement(index);
            if (element !is null && element !is editorUIElement)
                selectedUIElements.Push(element);
        }
    }

    // If only one node/UIElement selected, use it for editing
    if (selectedNodes.length == 1)
        editNode = selectedNodes[0];
    if (selectedUIElements.length == 1)
        editUIElement = selectedUIElements[0];

    // If selection contains only components, and they have a common node, use it for editing
    if (selectedNodes.empty && !selectedComponents.empty)
    {
        Node@ commonNode;
        for (uint i = 0; i < selectedComponents.length; ++i)
        {
            if (i == 0)
                commonNode = selectedComponents[i].node;
            else
            {
                if (selectedComponents[i].node !is commonNode)
                    commonNode = null;
            }
        }
        editNode = commonNode;
    }

    // Now check if the component(s) can be edited. If many selected, must have same type or have same edit node
    if (!selectedComponents.empty)
    {
        if (editNode is null)
        {
            ShortStringHash compType = selectedComponents[0].type;
            bool sameType = true;
            for (uint i = 1; i < selectedComponents.length; ++i)
            {
                if (selectedComponents[i].type != compType)
                {
                    sameType = false;
                    break;
                }
            }
            if (sameType)
                editComponents = selectedComponents;
        }
        else
        {
            editComponents = selectedComponents;
            numEditableComponentsPerNode = selectedComponents.length;
        }
    }

    // If just nodes selected, and no components, show as many matching components for editing as possible
    if (!selectedNodes.empty && selectedComponents.empty && selectedNodes[0].numComponents > 0)
    {
        uint count = 0;
        for (uint j = 0; j < selectedNodes[0].numComponents; ++j)
        {
            ShortStringHash compType = selectedNodes[0].components[j].type;
            bool sameType = true;
            for (uint i = 1; i < selectedNodes.length; ++i)
            {
                if (selectedNodes[i].numComponents <= j || selectedNodes[i].components[j].type != compType)
                {
                    sameType = false;
                    break;
                }
            }

            if (sameType)
            {
                ++count;
                for (uint i = 0; i < selectedNodes.length; ++i)
                    editComponents.Push(selectedNodes[i].components[j]);
            }
        }
        if (count > 1)
            numEditableComponentsPerNode = count;
    }

    if (selectedNodes.empty && editNode !is null)
        editNodes.Push(editNode);
    else
    {
        editNodes = selectedNodes;

        // Cannot multi-edit on scene and node(s) together as scene and node do not share identical attributes,
        // editing via gizmo does not make too much sense either
        if (editNodes.length > 1 && editNodes[0] is editorScene)
            editNodes.Erase(0);
    }

    if (selectedUIElements.empty && editUIElement !is null)
        editUIElements.Push(editUIElement);
    else
        editUIElements = selectedUIElements;

    PositionGizmo();
    UpdateAttributeInspector();
}

void HandleHierarchyListItemDoubleClick(StringHash eventType, VariantMap& eventData)
{
    uint index = eventData["Selection"].GetUInt();
    hierarchyList.ToggleExpand(index);
}

void HandleDragDropTest(StringHash eventType, VariantMap& eventData)
{
    UIElement@ source = eventData["Source"].GetUIElement();
    UIElement@ target = eventData["Target"].GetUIElement();
    eventData["Accept"] = TestDragDrop(source, target);
}

void HandleDragDropFinish(StringHash eventType, VariantMap& eventData)
{
    UIElement@ source = eventData["Source"].GetUIElement();
    UIElement@ target = eventData["Target"].GetUIElement();
    bool accept =  TestDragDrop(source, target);
    eventData["Accept"] = accept;
    if (!accept)
        return;

    Node@ sourceNode = editorScene.GetNode(source.vars[NODE_ID_VAR].GetUInt());
    Node@ targetNode = editorScene.GetNode(target.vars[NODE_ID_VAR].GetUInt());

    // If target is null, parent to scene
    if (targetNode is null)
        targetNode = editorScene;

    // Perform the reparenting
    if (!SceneChangeParent(sourceNode, targetNode))
        return;

    // Focus the node at its new position in the list which in turn should trigger a refresh in attribute inspector
    FocusNode(sourceNode);
}

bool TestDragDrop(UIElement@ source, UIElement@ target)
{
    // Test for validity of reparenting by drag and drop
    Node@ sourceNode;
    Node@ targetNode;
    Variant variant = source.GetVar(NODE_ID_VAR);
    if (!variant.empty)
        sourceNode = editorScene.GetNode(variant.GetUInt());
    variant = target.GetVar(NODE_ID_VAR);
    if (!variant.empty)
        targetNode = editorScene.GetNode(variant.GetUInt());

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

void FocusNode(Node@ node)
{
    uint index = GetListIndex(node);
    hierarchyList.selection = index;
}

void FocusComponent(Component@ component)
{
    uint index = GetComponentListIndex(component);
    hierarchyList.selection = index;
}

void FocusUIElement(UIElement@ element)
{
    uint index = GetListIndex(element);
    hierarchyList.selection = index;
}

void CreateBuiltinObject(const String& name)
{
    Node@ newNode = editorScene.CreateChild(name, REPLICATED);
    // Set the new node a certain distance from the camera
    newNode.position = GetNewNodePosition();

    StaticModel@ object = newNode.CreateComponent("StaticModel");
    object.model = cache.GetResource("Model", "Models/" + name + ".mdl");

    // Create an undo action for the create
    CreateNodeAction action;
    action.Define(newNode);
    SaveEditAction(action);

    FocusNode(newNode);
}

bool CheckHierarchyWindowFocus()
{
    // When we do edit operations based on key shortcuts, make sure the hierarchy list is focused, not for example a file selector
    return ui.focusElement is hierarchyList || ui.focusElement is null;
}

bool CheckForExistingGlobalComponent(Node@ node, const String&in typeName)
{
    if (typeName != "Octree" && typeName != "PhysicsWorld" && typeName != "DebugRenderer")
        return false;
    else
        return node.HasComponent(typeName);
}

void HandleNodeAdded(StringHash eventType, VariantMap& eventData)
{
    if (suppressSceneChanges)
        return;

    Node@ node = eventData["Node"].GetNode();
    UpdateHierarchyItem(node);
}

void HandleNodeRemoved(StringHash eventType, VariantMap& eventData)
{
    if (suppressSceneChanges)
        return;

    Node@ node = eventData["Node"].GetNode();
    uint index = GetListIndex(node);
    UpdateHierarchyItem(index, null, null);
}

void HandleComponentAdded(StringHash eventType, VariantMap& eventData)
{
    if (suppressSceneChanges)
        return;

    Node@ node = eventData["Node"].GetNode();
    UpdateHierarchyItem(node);
}

void HandleComponentRemoved(StringHash eventType, VariantMap& eventData)
{
    if (suppressSceneChanges)
        return;

    Component@ component = eventData["Component"].GetComponent();
    uint index = GetComponentListIndex(component);
    if (index != NO_ITEM)
        hierarchyList.RemoveItem(index);
}

void HandleNodeNameChanged(StringHash eventType, VariantMap& eventData)
{
    if (suppressSceneChanges)
        return;

    Node@ node = eventData["Node"].GetNode();
    UpdateHierarchyItemText(GetListIndex(node), node.enabled, GetNodeTitle(node));
}

void HandleNodeEnabledChanged(StringHash eventType, VariantMap& eventData)
{
    if (suppressSceneChanges)
        return;

    Node@ node = eventData["Node"].GetNode();
    UpdateHierarchyItemText(GetListIndex(node), node.enabled);
    attributesDirty = true;
}

void HandleComponentEnabledChanged(StringHash eventType, VariantMap& eventData)
{
    if (suppressSceneChanges)
        return;

    Component@ component = eventData["Component"].GetComponent();
    UpdateHierarchyItemText(GetComponentListIndex(component), component.enabledEffective);
    attributesDirty = true;
}

void HandleUIElementAdded(StringHash eventType, VariantMap& eventData)
{
    if (suppressUIElementChanges)
        return;

    UIElement@ element = eventData["Element"].GetUIElement();
    UpdateHierarchyItem(element);
}

void HandleUIElementRemoved(StringHash eventType, VariantMap& eventData)
{
    if (suppressUIElementChanges)
        return;

    UIElement@ element = eventData["Element"].GetUIElement();
    UpdateHierarchyItem(GetListIndex(element), null, null);
}

void HandleElementNameChanged(StringHash eventType, VariantMap& eventData)
{
    if (suppressUIElementChanges)
        return;

    UIElement@ element = eventData["Element"].GetUIElement();
    UpdateHierarchyItemText(GetListIndex(element), element.visible, GetUIElementTitle(element));
}

void HandleElementVisibilityChanged(StringHash eventType, VariantMap& eventData)
{
    if (suppressUIElementChanges)
        return;

    UIElement@ element = eventData["Element"].GetUIElement();
    UpdateHierarchyItemText(GetListIndex(element), element.visible);
}
