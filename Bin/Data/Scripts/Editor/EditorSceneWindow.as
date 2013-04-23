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
const ShortStringHash[] ID_VARS = { ShortStringHash(""), NODE_ID_VAR, COMPONENT_ID_VAR, UI_ELEMENT_ID_VAR };

Window@ hierarchyWindow;
ListView@ hierarchyList;

// UIElement does not have unique ID, so use a running number to generate a new ID each time an item is inserted into hierarchy list
const uint UI_ELEMENT_BASE_ID = 1;
uint uiElementNextID = UI_ELEMENT_BASE_ID;

Variant GetUIElementID(UIElement@ element)
{
    Variant elementID = element.GetVar(UI_ELEMENT_ID_VAR);
    if (elementID.empty)
    {
        // Generate new ID
        elementID = uiElementNextID++;
        // Store the generated ID
        element.vars[UI_ELEMENT_ID_VAR] = elementID;
    }

    return elementID;
}

UIElement@ GetUIElementByID(const Variant&in id)
{
    return id == UI_ELEMENT_BASE_ID ? editorUIElement : editorUIElement.GetChild(UI_ELEMENT_ID_VAR, id, true);
}

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
    CheckBox@ checkBox = hierarchyWindow.GetChild("AllCheckBox", true);
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
        sceneCopyBuffer.Clear();
        uiElementCopyBuffer.Clear();
    }

    // In case of item's parent is not found in the hierarchy list then the item will be inserted at the list root level
    Serializable@ parent;
    switch (GetType(serializable))
    {
    case ITEM_NODE:
        parent = cast<Node>(serializable).parent;
        break;

    case ITEM_COMPONENT:
        parent = cast<Component>(serializable).node;
        break;

    case ITEM_UI_ELEMENT:
        parent = cast<UIElement>(serializable).parent;
        break;

    default:
        break;
    }
    UIElement@ parentItem = hierarchyList.items[GetListIndex(parent)];
    UpdateHierarchyItem(GetListIndex(serializable), serializable, parentItem);
}

uint UpdateHierarchyItem(uint itemIndex, Serializable@ serializable, UIElement@ parentItem)
{
    // Whenever we're updating, disable layout update to optimize speed
    hierarchyList.contentElement.DisableLayoutUpdate();

    if (serializable is null)
    {
        hierarchyList.RemoveItem(itemIndex);
        hierarchyList.contentElement.EnableLayoutUpdate();
        hierarchyList.contentElement.UpdateLayout();
        return itemIndex;
    }

    int itemType = GetType(serializable);
    Variant id = GetID(serializable, itemType);

    // Remove old item if exists
    if (itemIndex < hierarchyList.numItems && MatchID(hierarchyList.items[itemIndex], id, itemType))
        hierarchyList.RemoveItem(itemIndex);

    Text@ text = Text();
    text.SetStyle(uiStyle, "FileSelectorListText");

    if (serializable.type == SCENE_TYPE || serializable is editorUIElement)
        // The root node (scene) and editor's root UIElement cannot be moved by drag and drop
        text.dragDropMode = DD_TARGET;
    else
        // Internal UIElement is not able to participate in drag and drop action
        text.dragDropMode = itemType == ITEM_UI_ELEMENT && cast<UIElement>(serializable).internal ? DD_DISABLED : DD_SOURCE_AND_TARGET;

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

    SetID(text, serializable, itemType);
    switch (itemType)
    {
    case ITEM_NODE:
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

            break;
        }

    case ITEM_COMPONENT:
        {
            Component@ component = cast<Component>(serializable);
            text.text = GetComponentTitle(component);
            SetIconEnabledColor(text, component.enabledEffective);
            break;
        }

    case ITEM_UI_ELEMENT:
        {
            UIElement@ element = cast<UIElement>(serializable);

            text.text = GetUIElementTitle(element);
            SetIconEnabledColor(text, element.visible);

            // update child elements recursively
            for (uint i = 0; i < element.numChildren; ++i)
            {
                UIElement@ childElement = element.children[i];
                itemIndex = UpdateHierarchyItem(itemIndex, childElement, text);
            }

            break;
        }

    default:
        break;
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

int GetType(Serializable@ serializable)
{
    if (cast<Node>(serializable) !is null)
        return ITEM_NODE;
    else if (cast<Component>(serializable) !is null)
        return ITEM_COMPONENT;
    else if (cast<UIElement>(serializable) !is null)
        return ITEM_UI_ELEMENT;
    else
        return ITEM_NONE;
}

void SetID(Text@ text, Serializable@ serializable, int itemType = ITEM_NONE)
{
    // If item type is not provided, auto detect it
    if (itemType == ITEM_NONE)
        itemType = GetType(serializable);

    text.vars[TYPE_VAR] = itemType;
    text.vars[ID_VARS[itemType]] = GetID(serializable, itemType);

    switch (itemType)
    {
    case ITEM_COMPONENT:
        text.vars[NODE_ID_VAR] = cast<Component>(serializable).node.id;
        break;

    case ITEM_UI_ELEMENT:
        // Subscribe to UI-element events
        SubscribeToEvent(serializable, "NameChanged", "HandleElementNameChanged");
        SubscribeToEvent(serializable, "VisibleChanged", "HandleElementVisibilityChanged");
        SubscribeToEvent(serializable, "Resized", "HandleElementAttributeChanged");
        SubscribeToEvent(serializable, "Positioned", "HandleElementAttributeChanged");
        break;

    default:
        break;
    }
}

uint GetID(Serializable@ serializable, int itemType = ITEM_NONE)
{
    // If item type is not provided, auto detect it
    if (itemType == ITEM_NONE)
        itemType = GetType(serializable);

    switch (itemType)
    {
    case ITEM_NODE:
        return cast<Node>(serializable).id;

    case ITEM_COMPONENT:
        return cast<Component>(serializable).id;

    case ITEM_UI_ELEMENT:
        return GetUIElementID(cast<UIElement>(serializable)).GetUInt();
    }

    return M_MAX_UNSIGNED;
}

bool MatchID(UIElement@ element, const Variant&in id, int itemType)
{
    return element.GetVar(TYPE_VAR).GetInt() == itemType && element.GetVar(ID_VARS[itemType]) == id;
}

uint GetListIndex(Serializable@ serializable)
{
    if (serializable is null)
        return NO_ITEM;

    int itemType = GetType(serializable);
    Variant id = GetID(serializable, itemType);

    uint numItems = hierarchyList.numItems;
    for (uint i = 0; i < numItems; ++i)
    {
        if (MatchID(hierarchyList.items[i], id, itemType))
            return i;
    }

    return NO_ITEM;
}

UIElement@ GetListUIElement(uint index)
{
    UIElement@ item = hierarchyList.items[index];
    if (item is null)
        return null;

    // Get the text item's ID and use it to retrieve the actual UIElement the text item is associated to
    return GetUIElementByID(GetUIElementID(item));
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
    return (element.name.empty ? element.typeName : element.name) + " [" + GetUIElementID(element).ToString() + "]";
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

    uint index = GetListIndex(node);
    uint numItems = hierarchyList.numItems;

    if (index < numItems)
    {
        // Expand the node chain now
        if (!multiselect || !hierarchyList.IsSelected(index))
        {
            // Go in the parent chain up to make sure the chain is expanded
            for (;;)
            {
                Node@ parent = node.parent;
                if (node is editorScene || parent is null)
                    break;
                node = parent;
            }
            uint parentIndex = GetListIndex(node);
            if (parentIndex < numItems)
                hierarchyList.Expand(parentIndex, true);

            hierarchyList.Expand(index, true);
        }

        // This causes an event to be sent, in response we set the node/component selections, and refresh editors
        if (!multiselect)
            hierarchyList.selection = index;
        else
            hierarchyList.ToggleSelection(index);
    }
    else if (!multiselect)
        hierarchyList.ClearSelection();
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

    uint nodeIndex = GetListIndex(node);
    uint componentIndex = GetComponentListIndex(component);
    uint numItems = hierarchyList.numItems;

    if (nodeIndex < numItems && componentIndex < numItems)
    {
        // Expand the node chain now
        if (!multiselect || !hierarchyList.IsSelected(componentIndex))
        {
            // Go in the parent chain up to make sure the chain is expanded
            for (;;)
            {
                Node@ parent = node.parent;
                if (node is editorScene || parent is null)
                    break;
                node = parent;
            }
            uint parentNodeIndex = GetListIndex(node);
            if (parentNodeIndex < numItems)
                hierarchyList.Expand(parentNodeIndex, true);
            else if (!multiselect)
            {
                hierarchyList.ClearSelection();
                return;
            }

            hierarchyList.Expand(nodeIndex, true);
        }
        // This causes an event to be sent, in response we set the node/component selections, and refresh editors
        if (!multiselect)
            hierarchyList.selection = componentIndex;
        else
            hierarchyList.ToggleSelection(componentIndex);
    }
    else if (!multiselect)
        hierarchyList.ClearSelection();
}

void SelectUIElement(UIElement@ element, bool multiselect)
{
    uint index = GetListIndex(element);
    uint numItems = hierarchyList.numItems;

    if (index < numItems)
    {
        // Expand the node chain now
        if (!multiselect || !hierarchyList.IsSelected(index))
        {
            // Go in the parent chain up to make sure the chain is expanded
            for (;;)
            {
                UIElement@ parent = element.parent;
                if (element is editorUIElement || parent is null)
                    break;
                element = parent;
            }
            uint parentIndex = GetListIndex(element);
            if (parentIndex < numItems)
                hierarchyList.Expand(parentIndex, true);

            hierarchyList.Expand(index, true);
        }

        if (!multiselect)
            hierarchyList.selection = index;
        else
            hierarchyList.ToggleSelection(index);
    }
    else if (!multiselect)
        hierarchyList.ClearSelection();
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
    int itemType;
    eventData["Accept"] = TestDragDrop(source, target, itemType);
}

void HandleDragDropFinish(StringHash eventType, VariantMap& eventData)
{
    UIElement@ source = eventData["Source"].GetUIElement();
    UIElement@ target = eventData["Target"].GetUIElement();
    int itemType;
    bool accept =  TestDragDrop(source, target, itemType);
    eventData["Accept"] = accept;
    if (!accept)
        return;

    if (itemType == ITEM_NODE)
    {
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
    else if (itemType == ITEM_UI_ELEMENT)
    {
        UIElement@ sourceElement = GetUIElementByID(source.vars[UI_ELEMENT_ID_VAR].GetUInt());
        UIElement@ targetElement = GetUIElementByID(target.vars[UI_ELEMENT_ID_VAR].GetUInt());

        // If target is null, cannot proceed
        if (targetElement is null)
            return;

        // Perform the reparenting
        if (!UIElementChangeParent(sourceElement, targetElement))
            return;

        // Focus the element at its new position in the list which in turn should trigger a refresh in attribute inspector
        FocusUIElement(sourceElement);
    }
}

bool TestDragDrop(UIElement@ source, UIElement@ target, int& itemType)
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

    UIElement@ sourceElement;
    UIElement@ targetElement;
    variant = source.GetVar(UI_ELEMENT_ID_VAR);
    if (!variant.empty)
        sourceElement = GetUIElementByID(variant.GetUInt());
    variant = target.GetVar(UI_ELEMENT_ID_VAR);
    if (!variant.empty)
        targetElement = GetUIElementByID(variant.GetUInt());

    if (sourceNode !is null && targetNode !is null)
    {
        itemType = ITEM_NODE;
        
        if (sourceNode.parent is targetNode)
            return false;
        if (targetNode.parent is sourceNode)
            return false;
    }
    else if (sourceElement !is null && targetElement !is null)
    {
        itemType = ITEM_UI_ELEMENT;
        
        if (sourceElement.parent is targetElement)
            return false;
        if (targetElement.parent is sourceElement)
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
    // When we do edit operations based on key shortcuts, make sure the hierarchy list is focused
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

    // Insert the newly added component at last component position but before the first child node position of the parent node
    Node@ node = eventData["Node"].GetNode();
    Component@ component = eventData["Component"].GetComponent();
    uint index = node.numChildren > 0 ? GetListIndex(node.children[0]) : M_MAX_UNSIGNED;
    UpdateHierarchyItem(index, component, hierarchyList.items[GetListIndex(node)]);
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

void HandleElementAttributeChanged(StringHash eventType, VariantMap& eventData)
{
    // Do not refresh the attribute inspector while the attribute is being edited via the attribute-editors
    if (suppressUIElementChanges || inEditAttribute)
        return;

    UIElement@ element = eventData["Element"].GetUIElement();
    for (uint i = 0; i < editUIElements.length; ++i)
    {
        if (editUIElements[i] is element)
            attributesDirty = true;
    }
}

// Hierarchy window edit functions
bool Undo()
{
    if (undoStackPos > 0)
    {
        --undoStackPos;
        // Undo commands in reverse order
        for (int i = int(undoStack[undoStackPos].actions.length - 1); i >= 0; --i)
            undoStack[undoStackPos].actions[i].Undo();
    }

    return true;
}

bool Redo()
{
    if (undoStackPos < undoStack.length)
    {
        // Redo commands in same order as stored
        for (uint i = 0; i < undoStack[undoStackPos].actions.length; ++i)
            undoStack[undoStackPos].actions[i].Redo();
        ++undoStackPos;
    }

    return true;
}

bool Cut()
{
    if (CheckHierarchyWindowFocus())
    {
        bool ret = true;
        if (!selectedNodes.empty || !selectedComponents.empty)
            ret = ret && SceneCut();
        // Not mutually exclusive
        if (!selectedUIElements.empty)
            ret = ret && UIElementCut();
        return ret;
    }

    return false;
}

bool Copy()
{
    if (CheckHierarchyWindowFocus())
    {
        bool ret = true;
        if (!selectedNodes.empty || !selectedComponents.empty)
            ret = ret && (selectedNodes.empty || selectedComponents.empty ? SceneCopy() : false);   // Node and component is mutually exclusive for copy action
        // Not mutually exclusive
        if (!selectedUIElements.empty)
            ret = ret && UIElementCopy();
        return ret;
    }

    return false;
}

bool Paste()
{
    if (CheckHierarchyWindowFocus())
    {
        bool ret = true;
        if (editNode !is null && !sceneCopyBuffer.empty)
            ret = ret && ScenePaste();
        // Not mutually exclusive
        if (editUIElement !is null && !uiElementCopyBuffer.empty)
            ret = ret && UIElementPaste();
        return ret;
    }

    return false;
}

bool Delete()
{
    if (CheckHierarchyWindowFocus())
    {
        bool ret = true;
        if (!selectedNodes.empty || !selectedComponents.empty)
            ret = ret && SceneDelete();
        // Not mutually exclusive
        if (!selectedUIElements.empty)
            ret = ret && UIElementDelete();
        return ret;
    }

    return false;
}

bool SelectAll()
{
    if (CheckHierarchyWindowFocus())
    {
        if (!selectedNodes.empty || !selectedComponents.empty)
            return SceneSelectAll();
        else if (!selectedUIElements.empty || hierarchyList.items[GetListIndex(editorUIElement)].selected)
            return UIElementSelectAll();
        else
            return SceneSelectAll();    // If nothing is selected yet, fall back to scene select all
    }

    return false;
}

bool ResetToDefault()
{
    if (CheckHierarchyWindowFocus())
    {
        bool ret = true;
        if (!selectedNodes.empty || !selectedComponents.empty)
            ret = ret && (selectedNodes.empty || selectedComponents.empty ? SceneResetToDefault() : false);   // Node and component is mutually exclusive for reset-to-default action
        // Not mutually exclusive
        if (!selectedUIElements.empty)
            ret = ret && UIElementResetToDefault();
        return ret;
    }

    return false;
}

void ClearEditActions()
{
    undoStack.Clear();
    undoStackPos = 0;
}

void SaveEditAction(EditAction@ action)
{
    // Create a group with 1 action
    EditActionGroup group;
    group.actions.Push(action);
    SaveEditActionGroup(group);
}

void SaveEditActionGroup(EditActionGroup@ group)
{
    if (group.actions.empty)
        return;

    // Truncate the stack first to current pos
    undoStack.Resize(undoStackPos);
    undoStack.Push(group);
    ++undoStackPos;

    // Limit maximum undo steps
    if (undoStack.length > MAX_UNDOSTACK_SIZE)
    {
        undoStack.Erase(0);
        --undoStackPos;
    }

    SetSceneModified();
}

void BeginSelectionModify()
{
    // A large operation on selected nodes is about to begin. Disable intermediate selection updates
    inSelectionModify = true;

    // Cursor shape reverts back to normal automatically after the large operation is completed
    ui.cursor.shape = CS_BUSY;
}

void EndSelectionModify()
{
    // The large operation on selected nodes has ended. Update node/component selection now
    inSelectionModify = false;
    HandleHierarchyListSelectionChange();
}
