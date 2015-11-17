// Urho3D editor attribute inspector window handling
#include "Scripts/Editor/AttributeEditor.as"

Window@ attributeInspectorWindow;
UIElement@ parentContainer;
UIElement@ inspectorLockButton;

bool applyMaterialList = true;
bool attributesDirty = false;
bool attributesFullDirty = false;

const String STRIKED_OUT = "——";   // Two unicode EM DASH (U+2014)
const StringHash NODE_IDS_VAR("NodeIDs");
const StringHash COMPONENT_IDS_VAR("ComponentIDs");
const StringHash UI_ELEMENT_IDS_VAR("UIElementIDs");
const int LABEL_WIDTH = 30;

// Constants for accessing xmlResources
Array<XMLFile@> xmlResources;
const uint ATTRIBUTE_RES = 0;
const uint VARIABLE_RES = 1;
const uint STYLE_RES = 2;

uint nodeContainerIndex = M_MAX_UNSIGNED;
uint componentContainerStartIndex = 0;
uint elementContainerIndex = M_MAX_UNSIGNED;

// Script Attribute session storage
VariantMap scriptAttributes;
const uint SCRIPTINSTANCE_ATTRIBUTE_IGNORE = 5;
const uint LUASCRIPTINSTANCE_ATTRIBUTE_IGNORE = 4;

// Node or UIElement hash-to-varname reverse mapping
VariantMap globalVarNames;

bool inspectorLocked = false;

void InitXMLResources()
{
    String[] resources = { "UI/EditorInspector_Attribute.xml", "UI/EditorInspector_Variable.xml", "UI/EditorInspector_Style.xml" };
    for (uint i = 0; i < resources.length; ++i)
        xmlResources.Push(cache.GetResource("XMLFile", resources[i]));
}

/// Delete all child containers in the inspector list.
void DeleteAllContainers()
{
    parentContainer.RemoveAllChildren();
    nodeContainerIndex = M_MAX_UNSIGNED;
    componentContainerStartIndex = 0;
    elementContainerIndex = M_MAX_UNSIGNED;
}

/// Get container at the specified index in the inspector list, the container must be created before.
UIElement@ GetContainer(uint index)
{
    return parentContainer.children[index];
}

/// Get node container in the inspector list, create the container if it is not yet available.
UIElement@ GetNodeContainer()
{
    if (nodeContainerIndex != M_MAX_UNSIGNED)
        return GetContainer(nodeContainerIndex);

    nodeContainerIndex = parentContainer.numChildren;
    parentContainer.LoadChildXML(xmlResources[ATTRIBUTE_RES], uiStyle);
    UIElement@ container = GetContainer(nodeContainerIndex);
    container.LoadChildXML(xmlResources[VARIABLE_RES], uiStyle);
    SubscribeToEvent(container.GetChild("ResetToDefault", true), "Released", "HandleResetToDefault");
    SubscribeToEvent(container.GetChild("NewVarDropDown", true), "ItemSelected", "CreateNodeVariable");
    SubscribeToEvent(container.GetChild("DeleteVarButton", true), "Released", "DeleteNodeVariable");
    ++componentContainerStartIndex;
    return container;
}

/// Get component container at the specified index, create the container if it is not yet available at the specified index.
UIElement@ GetComponentContainer(uint index)
{
    if (componentContainerStartIndex + index < parentContainer.numChildren)
        return GetContainer(componentContainerStartIndex + index);

    UIElement@ container;
    for (uint i = parentContainer.numChildren; i <= componentContainerStartIndex + index; ++i)
    {
        parentContainer.LoadChildXML(xmlResources[ATTRIBUTE_RES], uiStyle);
        container = GetContainer(i);
        SubscribeToEvent(container.GetChild("ResetToDefault", true), "Released", "HandleResetToDefault");
    }
    return container;
}

/// Get UI-element container, create the container if it is not yet available.
UIElement@ GetUIElementContainer()
{
    if (elementContainerIndex != M_MAX_UNSIGNED)
        return GetContainer(elementContainerIndex);

    elementContainerIndex = parentContainer.numChildren;
    parentContainer.LoadChildXML(xmlResources[ATTRIBUTE_RES], uiStyle);
    UIElement@ container = GetContainer(elementContainerIndex);
    container.LoadChildXML(xmlResources[VARIABLE_RES], uiStyle);
    container.LoadChildXML(xmlResources[STYLE_RES], uiStyle);
    DropDownList@ styleList = container.GetChild("StyleDropDown", true);
    styleList.placeholderText = STRIKED_OUT;
    styleList.parent.GetChild("StyleDropDownLabel").SetFixedWidth(LABEL_WIDTH);
    PopulateStyleList(styleList);
    SubscribeToEvent(container.GetChild("ResetToDefault", true), "Released", "HandleResetToDefault");
    SubscribeToEvent(container.GetChild("NewVarDropDown", true), "ItemSelected", "CreateUIElementVariable");
    SubscribeToEvent(container.GetChild("DeleteVarButton", true), "Released", "DeleteUIElementVariable");
    SubscribeToEvent(styleList, "ItemSelected", "HandleStyleItemSelected");
    return container;
}

void CreateAttributeInspectorWindow()
{
    if (attributeInspectorWindow !is null)
        return;

    InitResourcePicker();
    InitVectorStructs();
    InitXMLResources();

    attributeInspectorWindow = LoadEditorUI("UI/EditorInspectorWindow.xml");
    parentContainer = attributeInspectorWindow.GetChild("ParentContainer");
    ui.root.AddChild(attributeInspectorWindow);
    int height = Min(ui.root.height - 60, 500);
    attributeInspectorWindow.SetSize(344, height);
    attributeInspectorWindow.SetPosition(ui.root.width - 10 - attributeInspectorWindow.width, 100);
    attributeInspectorWindow.opacity = uiMaxOpacity;
    attributeInspectorWindow.BringToFront();
    inspectorLockButton = attributeInspectorWindow.GetChild("LockButton", true);

    UpdateAttributeInspector();

    SubscribeToEvent(inspectorLockButton, "Pressed", "ToggleInspectorLock");
    SubscribeToEvent(attributeInspectorWindow.GetChild("CloseButton", true), "Pressed", "HideAttributeInspectorWindow");
    SubscribeToEvent(attributeInspectorWindow, "LayoutUpdated", "HandleWindowLayoutUpdated");
}

void DisableInspectorLock()
{
    inspectorLocked = false;
    if (inspectorLockButton !is null)
        inspectorLockButton.style = "Button";
    UpdateAttributeInspector(true);
}

void EnableInspectorLock()
{
    inspectorLocked = true;
    if (inspectorLockButton !is null)
        inspectorLockButton.style = "ToggledButton";
}

void ToggleInspectorLock()
{
    if (inspectorLocked)
        DisableInspectorLock();
    else
        EnableInspectorLock();
}

bool ToggleAttributeInspectorWindow()
{
    if (attributeInspectorWindow.visible == false)
        ShowAttributeInspectorWindow();
    else
        HideAttributeInspectorWindow();
    return true;
}

void ShowAttributeInspectorWindow()
{
    attributeInspectorWindow.visible = true;
    attributeInspectorWindow.BringToFront();
}

void HideAttributeInspectorWindow()
{
    attributeInspectorWindow.visible = false;
}


/// Handle main window layout updated event by positioning elements that needs manually-positioning (elements that are children of UI-element container with "Free" layout-mode).
void HandleWindowLayoutUpdated()
{
    // When window resize and so the list's width is changed, adjust the 'Is enabled' container width and icon panel width so that their children stay at the right most position
    for (uint i = 0; i < parentContainer.numChildren; ++i)
    {
        UIElement@ container = GetContainer(i);
        ListView@ list = container.GetChild("AttributeList");
        if (list is null)
            continue;

        int width = list.width;

        // Adjust the icon panel's width
        UIElement@ panel = container.GetChild("IconsPanel", true);
        if (panel !is null)
            panel.width = width;

        // At the moment, only 'Is Enabled' container (place-holder + check box) is being created as child of the list view instead of as list item
        for (uint j = 0; j < list.numChildren; ++j)
        {
            UIElement@ element = list.children[j];
            if (!element.internal)
            {
                element.SetFixedWidth(width);
                UIElement@ title = container.GetChild("TitleText");
                element.position = IntVector2(0, (title.screenPosition - list.screenPosition).y);

                // Adjust icon panel's width one more time to cater for the space occupied by 'Is Enabled' check box
                if (panel !is null)
                    panel.width = width - element.children[1].width - panel.layoutSpacing;

                break;
            }
        }
    }
}

Array<Serializable@> ToSerializableArray(Array<Node@> nodes)
{
    Array<Serializable@> serializables;
    for (uint i = 0; i < nodes.length; ++i)
        serializables.Push(nodes[i]);
    return serializables;
}

/// Update the whole attribute inspector window, when fullUpdate flag is set to true then first delete all the containers and repopulate them again from scratch.
/// The fullUpdate flag is usually set to true when the structure of the attributes are different than the existing attributes in the list.
void UpdateAttributeInspector(bool fullUpdate = true)
{
    if (inspectorLocked)
        return;

    attributesDirty = false;
    if (fullUpdate)
        attributesFullDirty = false;

    // If full update delete all containers and add them back as necessary
    if (fullUpdate)
        DeleteAllContainers();

    // Update all ScriptInstances/LuaScriptInstances
    UpdateScriptInstances();

    if (!editNodes.empty)
    {
        UIElement@ container = GetNodeContainer();

        Text@ nodeTitle = container.GetChild("TitleText");
        String nodeType;

        if (editNode !is null)
        {
            String idStr;
            if (editNode.id >= FIRST_LOCAL_ID)
                idStr = " (Local ID " + String(editNode.id) + ")";
            else
                idStr = " (ID " + String(editNode.id) + ")";
            nodeType = editNode.typeName;
            nodeTitle.text = nodeType + idStr;
        }
        else
        {
            nodeType = editNodes[0].typeName;
            nodeTitle.text = nodeType + " (ID " + STRIKED_OUT + " : " + editNodes.length + "x)";
        }
        IconizeUIElement(nodeTitle, nodeType);

        ListView@ list = container.GetChild("AttributeList");
        Array<Serializable@> nodes = ToSerializableArray(editNodes);
        UpdateAttributes(nodes, list, fullUpdate);

        if (fullUpdate)
        {
            //\todo Avoid hardcoding
            // Resize the node editor according to the number of variables, up to a certain maximum
            uint maxAttrs = Clamp(list.contentElement.numChildren, MIN_NODE_ATTRIBUTES, MAX_NODE_ATTRIBUTES);
            list.SetFixedHeight(maxAttrs * ATTR_HEIGHT + 2);
            container.SetFixedHeight(maxAttrs * ATTR_HEIGHT + 58);
        }

        // Set icon's target in the icon panel
        SetAttributeEditorID(container.GetChild("ResetToDefault", true), nodes);
    }

    if (!editComponents.empty)
    {
        uint numEditableComponents = editComponents.length / numEditableComponentsPerNode;
        String multiplierText;
        if (numEditableComponents > 1)
            multiplierText = " (" + numEditableComponents + "x)";

        for (uint j = 0; j < numEditableComponentsPerNode; ++j)
        {
            UIElement@ container = GetComponentContainer(j);
            Text@ componentTitle = container.GetChild("TitleText");
            componentTitle.text = GetComponentTitle(editComponents[j * numEditableComponents]) + multiplierText;
            IconizeUIElement(componentTitle, editComponents[j * numEditableComponents].typeName);
            SetIconEnabledColor(componentTitle, editComponents[j * numEditableComponents].enabledEffective);

            Array<Serializable@> components;
            for (uint i = 0; i < numEditableComponents; ++i)
            {
                Component@ component = editComponents[j * numEditableComponents + i];
                components.Push(component);
            }

            UpdateAttributes(components, container.GetChild("AttributeList"), fullUpdate);
            SetAttributeEditorID(container.GetChild("ResetToDefault", true), components);
        }
    }

    if (!editUIElements.empty)
    {
        UIElement@ container = GetUIElementContainer();

        Text@ titleText = container.GetChild("TitleText");
        DropDownList@ styleList = container.GetChild("StyleDropDown", true);
        String elementType;

        if (editUIElement !is null)
        {
            elementType = editUIElement.typeName;
            titleText.text = elementType + " [ID " + GetUIElementID(editUIElement).ToString() + "]";
            SetStyleListSelection(styleList, editUIElement.style);
        }
        else
        {
            elementType = editUIElements[0].typeName;
            String appliedStyle = cast<UIElement>(editUIElements[0]).style;

            bool sameType = true;
            bool sameStyle = true;
            for (uint i = 1; i < editUIElements.length; ++i)
            {
                if (editUIElements[i].typeName != elementType)
                {
                    sameType = false;
                    sameStyle = false;
                    break;
                }

                if (sameStyle && cast<UIElement>(editUIElements[i]).style != appliedStyle)
                    sameStyle = false;
            }
            titleText.text = (sameType ? elementType : "Mixed type") + " [ID " + STRIKED_OUT + " : " + editUIElements.length + "x]";
            SetStyleListSelection(SetEditable(styleList, sameStyle), sameStyle ? appliedStyle : STRIKED_OUT);
            if (!sameType)
                elementType.Clear();   // No icon
        }
        IconizeUIElement(titleText, elementType);

        UpdateAttributes(editUIElements, container.GetChild("AttributeList"), fullUpdate);
        SetAttributeEditorID(container.GetChild("ResetToDefault", true), editUIElements);
    }

    if (parentContainer.numChildren > 0)
        UpdateAttributeInspectorIcons();
    else
    {
        // No editables, insert a dummy component container to show the information
        Text@ titleText = GetComponentContainer(0).GetChild("TitleText");
        titleText.text = "Select editable objects";
        titleText.autoLocalizable = true;
        UIElement@ panel = titleText.GetChild("IconsPanel");
        panel.visible = false;
    }

    // Adjust size and position of manual-layout UI-elements, e.g. icons panel
    if (fullUpdate)
        HandleWindowLayoutUpdated();
}

void UpdateScriptInstances()
{
    Array<Component@>@ components = scene.GetComponents("ScriptInstance", true);
    for (uint i = 0; i < components.length; i++)
        UpdateScriptAttributes(components[i]);

    components = scene.GetComponents("LuaScriptInstance", true);
    for (uint i = 0; i < components.length; i++)
        UpdateScriptAttributes(components[i]);
}

String GetComponentAttributeHash(Component@ component, uint index)
{
    // We won't consider the main attributes, as they won't reset when an error occurs.
    if (component.typeName == "ScriptInstance")
    {
        if (index <= SCRIPTINSTANCE_ATTRIBUTE_IGNORE)
            return "";
    }
    else
    {
        if (index <= LUASCRIPTINSTANCE_ATTRIBUTE_IGNORE)
            return "";
    }
    AttributeInfo attributeInfo = component.attributeInfos[index];
    Variant attribute = component.attributes[index];
    return String(component.id) + "-" + attributeInfo.name + "-" + attribute.typeName;
}

void UpdateScriptAttributes(Component@ component)
{
    for (uint i = Min(SCRIPTINSTANCE_ATTRIBUTE_IGNORE, LUASCRIPTINSTANCE_ATTRIBUTE_IGNORE) + 1; i < component.numAttributes; i++)
    {
        Variant attribute = component.attributes[i];
        // Component/node ID's are always unique within a scene, based on a simple increment.
        // This makes for a simple method of mapping a components attributes unique and consistent.
        // We will also use the type name in the hash to be able to recall and differentiate type changes.
        String hash = GetComponentAttributeHash(component, i);
        if (hash.empty)
            continue;

        if (!scriptAttributes.Contains(hash))
        {
            // set the initial value to the default value.
            scriptAttributes[hash] = attribute;
        }
        else
        {
            // recall the previously stored value
            component.attributes[i] = scriptAttributes[hash];
        }
    }
    component.ApplyAttributes();
}

/// Update the attribute list of the node container.
void UpdateNodeAttributes()
{
    bool fullUpdate = false;
    UpdateAttributes(ToSerializableArray(editNodes), GetNodeContainer().GetChild("AttributeList"), fullUpdate);
}

/// Update the icons enabled color based on the internal state of the objects.
/// For node and component, based on "enabled" property.
/// For ui-element, based on "visible" property.
void UpdateAttributeInspectorIcons()
{
    if (!editNodes.empty)
    {
        Text@ nodeTitle = GetNodeContainer().GetChild("TitleText");
        if (editNode !is null)
            SetIconEnabledColor(nodeTitle, editNode.enabled);
        else if (editNodes.length > 0)
        {
            bool hasSameEnabledState = true;

            for (uint i = 1; i < editNodes.length; ++i)
            {
                if (editNodes[i].enabled != editNodes[0].enabled)
                {
                    hasSameEnabledState = false;
                    break;
                }
            }

            SetIconEnabledColor(nodeTitle, editNodes[0].enabled, !hasSameEnabledState);
        }
    }

    if (!editComponents.empty)
    {
        uint numEditableComponents = editComponents.length / numEditableComponentsPerNode;

        for (uint j = 0; j < numEditableComponentsPerNode; ++j)
        {
            Text@ componentTitle = GetComponentContainer(j).GetChild("TitleText");

            bool enabledEffective = editComponents[j * numEditableComponents].enabledEffective;
            bool hasSameEnabledState = true;
            for (uint i = 1; i < numEditableComponents; ++i)
            {
                if (editComponents[j * numEditableComponents + i].enabledEffective != enabledEffective)
                {
                    hasSameEnabledState = false;
                    break;
                }
            }

            SetIconEnabledColor(componentTitle, enabledEffective, !hasSameEnabledState);
        }
    }
    
    if (!editUIElements.empty)
    {
        Text@ elementTitle = GetUIElementContainer().GetChild("TitleText");
        if (editUIElement !is null)
            SetIconEnabledColor(elementTitle, editUIElement.visible);
        else if (editUIElements.length > 0)
        {
            bool hasSameVisibleState = true;
            bool visible = cast<UIElement>(editUIElements[0]).visible;

            for (uint i = 1; i < editUIElements.length; ++i)
            {
                if (cast<UIElement>(editUIElements[i]).visible != visible)
                {
                    hasSameVisibleState = false;
                    break;
                }
            }

            SetIconEnabledColor(elementTitle, visible, !hasSameVisibleState);
        }
    }
}

/// Return true if the edit attribute action should continue.
bool PreEditAttribute(Array<Serializable@>@ serializables, uint index)
{
    return true;
}

/// Call after the attribute values in the target serializables have been edited. 
void PostEditAttribute(Array<Serializable@>@ serializables, uint index, const Array<Variant>& oldValues)
{
    // Create undo actions for the edits
    EditActionGroup group;
    for (uint i = 0; i < serializables.length; ++i)
    {
        EditAttributeAction action;
        action.Define(serializables[i], index, oldValues[i]);
        group.actions.Push(action);
    }
    SaveEditActionGroup(group);

    // If a UI-element changing its 'Is Modal' attribute, clear the hierarchy list selection
    int itemType = GetType(serializables[0]);
    if (itemType == ITEM_UI_ELEMENT && serializables[0].attributeInfos[index].name == "Is Modal")
        hierarchyList.ClearSelection();

    for (uint i = 0; i < serializables.length; ++i)
    {
        PostEditAttribute(serializables[i], index);
        if (itemType == ITEM_UI_ELEMENT)
            SetUIElementModified(serializables[i]);
    }

    if (itemType != ITEM_UI_ELEMENT)
        SetSceneModified();
}

/// Call after the attribute values in the target serializables have been edited. 
void PostEditAttribute(Serializable@ serializable, uint index)
{
    // If a StaticModel/AnimatedModel/Skybox model was changed, apply a possibly different material list
    if (applyMaterialList && serializable.attributeInfos[index].name == "Model")
    {
        StaticModel@ staticModel = cast<StaticModel>(serializable);
        if (staticModel !is null)
            staticModel.ApplyMaterialList();
    }
    
    // If a CollisionShape changed the shape type to trimesh or convex, and a collision model is not set,
    // try to get it from a StaticModel in the same node
    if (serializable.typeName == "CollisionShape" && serializable.attributeInfos[index].name == "Shape Type")
    {
        int shapeType = serializable.GetAttribute("Shape Type").GetInt();
        if ((shapeType == 6 || shapeType == 7) && serializable.GetAttribute("CustomGeometry ComponentID").GetInt() == 0 &&
            serializable.GetAttribute("Model").GetResourceRef().name.Trimmed().length == 0)
        {
            Node@ ownerNode = cast<Component>(serializable).node;
            if (ownerNode !is null)
            {
                StaticModel@ staticModel = ownerNode.GetComponent("StaticModel");
                if (staticModel !is null)
                {
                    serializable.SetAttribute("Model", staticModel.GetAttribute("Model"));
                    serializable.ApplyAttributes();
                }
            }
        }
    }

}

/// Store the IDs of the actual serializable objects into user-defined variable of the 'attribute editor' (e.g. line-edit, drop-down-list, etc).
void SetAttributeEditorID(UIElement@ attrEdit, Array<Serializable@>@ serializables)
{
    if (serializables is null || serializables.length == 0)
        return;

    // All target serializables must be either nodes, ui-elements, or components
    Array<Variant> ids;
    switch (GetType(serializables[0]))
    {
    case ITEM_NODE:
        for (uint i = 0; i < serializables.length; ++i)
            ids.Push(cast<Node>(serializables[i]).id);
        attrEdit.vars[NODE_IDS_VAR] = ids;
        break;

    case ITEM_COMPONENT:
        for (uint i = 0; i < serializables.length; ++i)
            ids.Push(cast<Component>(serializables[i]).id);
        attrEdit.vars[COMPONENT_IDS_VAR] = ids;
        break;

    case ITEM_UI_ELEMENT:
        for (uint i = 0; i < serializables.length; ++i)
            ids.Push(GetUIElementID(cast<UIElement>(serializables[i])));
        attrEdit.vars[UI_ELEMENT_IDS_VAR] = ids;
        break;

    default:
        break;
    }
}

/// Return the actual serializable objects based on the IDs stored in the user-defined variable of the 'attribute editor'.
Array<Serializable@>@ GetAttributeEditorTargets(UIElement@ attrEdit)
{
    Array<Serializable@> ret;
    Variant variant = attrEdit.GetVar(NODE_IDS_VAR);
    if (!variant.empty)
    {
        Array<Variant>@ ids = variant.GetVariantVector();
        for (uint i = 0; i < ids.length; ++i)
        {
            Node@ node = editorScene.GetNode(ids[i].GetUInt());
            if (node !is null)
                ret.Push(node);
        }
    }
    else
    {
        variant = attrEdit.GetVar(COMPONENT_IDS_VAR);
        if (!variant.empty)
        {
            Array<Variant>@ ids = variant.GetVariantVector();
            for (uint i = 0; i < ids.length; ++i)
            {
                Component@ component = editorScene.GetComponent(ids[i].GetUInt());
                if (component !is null)
                    ret.Push(component);
            }
        }
        else
        {
            variant = attrEdit.GetVar(UI_ELEMENT_IDS_VAR);
            if (!variant.empty)
            {
                Array<Variant>@ ids = variant.GetVariantVector();
                for (uint i = 0; i < ids.length; ++i)
                {
                    UIElement@ element = editorUIElement.GetChild(UI_ELEMENT_ID_VAR, ids[i], true);
                    if (element !is null)
                        ret.Push(element);
                }
            }
        }
    }

    return ret;
}

/// Handle reset to default event, sent when reset icon in the icon-panel is clicked.
void HandleResetToDefault(StringHash eventType, VariantMap& eventData)
{
    ui.cursor.shape = CS_BUSY;

    UIElement@ button = eventData["Element"].GetPtr();
    Array<Serializable@>@ serializables = GetAttributeEditorTargets(button);
    if (serializables.empty)
        return;

    // Group for storing undo actions
    EditActionGroup group;

    // Reset target serializables to their default values
    for (uint i = 0; i < serializables.length; ++i)
    {
        Serializable@ target = serializables[i];

        ResetAttributesAction action;
        action.Define(target);
        group.actions.Push(action);

        target.ResetToDefault();
        if (action.targetType == ITEM_UI_ELEMENT)
        {
            action.SetInternalVars(target);
            SetUIElementModified(target);
        }
        target.ApplyAttributes();
        for (uint j = 0; j < target.numAttributes; ++j)
            PostEditAttribute(target, j);
    }

    SaveEditActionGroup(group);
    if (GetType(serializables[0]) != ITEM_UI_ELEMENT)
        SetSceneModified();
    attributesFullDirty = true;
}

/// Handle create new user-defined variable event for node target. 
void CreateNodeVariable(StringHash eventType, VariantMap& eventData)
{
    if (editNodes.empty)
        return;

    String newName = ExtractVariableName(eventData);
    if (newName.empty)
        return;

    // Create scene variable
    editorScene.RegisterVar(newName);
    globalVarNames[newName] = newName;

    Variant newValue = ExtractVariantType(eventData);

    // If we overwrite an existing variable, must recreate the attribute-editor(s) for the correct type
    bool overwrite = false;
    for (uint i = 0; i < editNodes.length; ++i)
    {
        overwrite = overwrite || editNodes[i].vars.Contains(newName);
        editNodes[i].vars[newName] = newValue;
    }
    if (overwrite)
        attributesFullDirty = true;
    else
        attributesDirty = true;
}

/// Handle delete existing user-defined variable event for node target.
void DeleteNodeVariable(StringHash eventType, VariantMap& eventData)
{
    if (editNodes.empty)
        return;

    String delName = ExtractVariableName(eventData);
    if (delName.empty)
        return;

    // Note: intentionally do not unregister the variable name here as the same variable name may still be used by other attribute list

    bool erased = false;
    for (uint i = 0; i < editNodes.length; ++i)
    {
        // \todo Should first check whether var in question is editable
        erased = editNodes[i].vars.Erase(delName) || erased;
    }
    if (erased)
        attributesDirty = true;
}

/// Handle create new user-defined variable event for ui-element target.
void CreateUIElementVariable(StringHash eventType, VariantMap& eventData)
{
    if (editUIElements.empty)
        return;

    String newName = ExtractVariableName(eventData);
    if (newName.empty)
        return;

    // Create UIElement variable
    globalVarNames[newName] = newName;

    Variant newValue = ExtractVariantType(eventData);

    // If we overwrite an existing variable, must recreate the attribute-editor(s) for the correct type
    bool overwrite = false;
    for (uint i = 0; i < editUIElements.length; ++i)
    {
        UIElement@ element = cast<UIElement>(editUIElements[i]);
        overwrite = overwrite || element.vars.Contains(newName);
        element.vars[newName] = newValue;
    }
    if (overwrite)
        attributesFullDirty = true;
    else
        attributesDirty = true;
}

/// Handle delete existing user-defined variable event for ui-element target.
void DeleteUIElementVariable(StringHash eventType, VariantMap& eventData)
{
    if (editUIElements.empty)
        return;

    String delName = ExtractVariableName(eventData);
    if (delName.empty)
        return;

    // Note: intentionally do not unregister the variable name here as the same variable name may still be used by other attribute list

    bool erased = false;
    for (uint i = 0; i < editUIElements.length; ++i)
    {
        // \todo Should first check whether var in question is editable
        erased = cast<UIElement>(editUIElements[i]).vars.Erase(delName) || erased;
    }
    if (erased)
        attributesDirty = true;
}

String ExtractVariableName(VariantMap& eventData)
{
    UIElement@ element = eventData["Element"].GetPtr();
    LineEdit@ nameEdit = element.parent.GetChild("VarNameEdit");
    return nameEdit.text.Trimmed();
}

Variant ExtractVariantType(VariantMap& eventData)
{
    DropDownList@ dropDown = eventData["Element"].GetPtr();
    switch (dropDown.selection)
    {
    case 0:
        return int(0);
    case 1:
        return false;
    case 2:
        return float(0.0);
    case 3:
        return Variant(String());
    case 4:
        return Variant(Vector3());
    case 5:
        return Variant(Color());
    }

    return Variant();   // This should not happen
}

/// Get back the human-readable variable name from the StringHash.
String GetVarName(StringHash hash)
{
    // First try to get it from scene
    String name = editorScene.GetVarName(hash);
    // Then from the global variable reverse mappings
    if (name.empty && globalVarNames.Contains(hash))
        name = globalVarNames[hash].ToString();
    return name;
}

bool inSetStyleListSelection = false;

/// Select/highlight the matching style in the style drop-down-list based on specified style. 
void SetStyleListSelection(DropDownList@ styleList, const String&in style)
{
    // Prevent infinite loop upon initial style selection
    inSetStyleListSelection = true;

    uint selection = M_MAX_UNSIGNED;
    String styleName = style.empty ? "auto" : style;
    Array<UIElement@> items = styleList.GetItems();
    for (uint i = 0; i < items.length; ++i)
    {
        Text@ element = cast<Text>(items[i]);
        if (element is null)
            continue;   // It may be a divider
        if (element.text == styleName)
        {
            selection = i;
            break;
        }
    }
    styleList.selection = selection;

    inSetStyleListSelection = false;
}

/// Handle the style change of the target ui-elements event when a new style is picked from the style drop-down-list.
void HandleStyleItemSelected(StringHash eventType, VariantMap& eventData)
{
    if (inSetStyleListSelection || editUIElements.empty)
        return;

    ui.cursor.shape = CS_BUSY;

    DropDownList@ styleList = eventData["Element"].GetPtr();
    Text@ text = cast<Text>(styleList.selectedItem);
    if (text is null)
        return;
    String newStyle = text.text;
    if (newStyle == "auto")
        newStyle.Clear();

    // Group for storing undo actions
    EditActionGroup group;

    // Apply new style to selected UI-elements
    for (uint i = 0; i < editUIElements.length; ++i)
    {
        UIElement@ element = editUIElements[i];

        ApplyUIElementStyleAction action;
        action.Define(element, newStyle);
        group.actions.Push(action);

        // Use the Redo() to actually do the action
        action.Redo();
    }

    SaveEditActionGroup(group);
}
