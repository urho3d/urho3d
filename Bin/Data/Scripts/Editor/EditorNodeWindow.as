// Urho3D editor attribute inspector window handling
#include "Scripts/Editor/AttributeEditor.as"

Window@ attributeInspectorWindow;
UIElement@ parentContainer;
UIElement@ nodeContainer;
XMLFile@ nodeXMLResource;
XMLFile@ componentXMLResource;

bool applyMaterialList = true;
bool attributesDirty = false;

const String STRIKED_OUT = "——";   // Two unicode EM DASH (U+2014)
const ShortStringHash NODE_IDS_VAR("NodeIDs");
const ShortStringHash COMPONENT_IDS_VAR("ComponentIDs");

uint componentContainerStartIndex = 0;

void AddNodeContainer()
{
    if (nodeContainer !is null)
        return;

    uint index = parentContainer.numChildren;
    parentContainer.LoadXML(nodeXMLResource, uiStyle);
    nodeContainer = GetContainer(index);
    SubscribeToEvent(nodeContainer.GetChild("NewVarDropDown", true), "ItemSelected", "CreateNewVariable");
    SubscribeToEvent(nodeContainer.GetChild("DeleteVarButton", true), "Released", "DeleteVariable");
    ++componentContainerStartIndex;
}

void AddComponentContainer()
{
    parentContainer.LoadXML(componentXMLResource, uiStyle);
}

void DeleteAllContainers()
{
    parentContainer.RemoveAllChildren();
    nodeContainer = null;
    componentContainerStartIndex = 0;
}

UIElement@ GetContainer(uint index)
{
    return parentContainer.children[index];
}

UIElement@ GetComponentContainer(uint index)
{
    return parentContainer.children[componentContainerStartIndex + index];
}

void CreateAttributeInspectorWindow()
{
    if (attributeInspectorWindow !is null)
        return;

    InitResourcePicker();
    InitVectorStructs();

    attributeInspectorWindow = ui.LoadLayout(cache.GetResource("XMLFile", "UI/EditorNodeWindow.xml"));
    nodeXMLResource = cache.GetResource("XMLFile", "UI/EditorNode.xml");
    componentXMLResource = cache.GetResource("XMLFile", "UI/EditorComponent.xml");
    parentContainer = attributeInspectorWindow.GetChild("ParentContainer");
    ui.root.AddChild(attributeInspectorWindow);
    int height = Min(ui.root.height - 60, 500);
    attributeInspectorWindow.SetSize(300, height);
    attributeInspectorWindow.SetPosition(ui.root.width - 20 - attributeInspectorWindow.width, 40);
    attributeInspectorWindow.opacity = uiMaxOpacity;
    attributeInspectorWindow.BringToFront();
    UpdateAttributeInspector();

    SubscribeToEvent(attributeInspectorWindow.GetChild("CloseButton", true), "Released", "HideAttributeInspectorWindow");
    SubscribeToEvent(attributeInspectorWindow, "LayoutUpdated", "HandleWindowLayoutUpdated");
}

void HideAttributeInspectorWindow()
{
    attributeInspectorWindow.visible = false;
}

bool ShowAttributeInspectorWindow()
{
    attributeInspectorWindow.visible = true;
    attributeInspectorWindow.BringToFront();
    return true;
}

void HandleWindowLayoutUpdated()
{
    for (uint i = 0; i < parentContainer.numChildren; ++i)
    {
        ListView@ list = GetContainer(i).GetChild("AttributeList");

        // At the moment, only 'Is Enabled' container (place-holder + check box) is being created as child of the list view instead of as list item
        // When window resize and so the list's width is changed, adjust the 'Is enabled' container width so that check box stays at the right most position
        int width = list.width;
        for (uint i = 0; i < list.numChildren; ++i)
        {
            UIElement@ element = list.children[i];
            if (!element.internal)
                element.SetFixedWidth(width);
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

void UpdateAttributeInspector(bool fullUpdate = true)
{
    attributesDirty = false;

    // If full update delete all containers and added them back as necessary
    if (fullUpdate)
    {
        DeleteAllContainers();
        AddNodeContainer();
        AddComponentContainer();
    }

    Text@ nodeTitle = nodeContainer.GetChild("TitleText");
    String nodeType;
    if (editNodes.length == 0)
        nodeTitle.text = "No node";
    else if (editNode !is null)
    {
        String idStr;
        if (editNode.id >= FIRST_LOCAL_ID)
            idStr = " Local ID " + String(editNode.id - FIRST_LOCAL_ID);
        else
            idStr = " ID " + String(editNode.id);
        nodeType = editNode.typeName;
        nodeTitle.text = nodeType + idStr;
    }
    else
    {
        nodeType = editNodes[0].typeName;
        nodeTitle.text = nodeType + " ID " + STRIKED_OUT + " (" + editNodes.length + "x)";
    }
    IconizeUIElement(nodeTitle, nodeType);

    ListView@ list = nodeContainer.GetChild("AttributeList");
    UpdateAttributes(ToSerializableArray(editNodes), list, fullUpdate);

    if (fullUpdate)
    {
        //\TODO Avoid hardcoding
        // Resize the node editor according to the number of variables, up to a certain maximum
        uint maxAttrs = Clamp(list.contentElement.numChildren, MIN_NODE_ATTRIBUTES, MAX_NODE_ATTRIBUTES);
        list.SetFixedHeight(maxAttrs * ATTR_HEIGHT + 2);
        nodeContainer.SetFixedHeight(maxAttrs * ATTR_HEIGHT + 60);
    }

    if (editComponents.empty)
    {
        Text@ componentTitle = GetComponentContainer(0).GetChild("TitleText");
        if (selectedComponents.length <= 1)
            componentTitle.text = "No component";
        else
            componentTitle.text = selectedComponents.length + " components";

        // Ensure there is no icon
        IconizeUIElement(componentTitle, "");
    }
    else
    {
        uint numEditableComponents = editComponents.length / numEditableComponentsPerNode;
        String multiplierText;
        if (numEditableComponents > 1)
            multiplierText = " (" + numEditableComponents + "x)";

        for (uint j = 0; j < numEditableComponentsPerNode; ++j)
        {
            if (j >= parentContainer.numChildren - componentContainerStartIndex)
                AddComponentContainer();

            Text@ componentTitle = GetComponentContainer(j).GetChild("TitleText");
            componentTitle.text = GetComponentTitle(editComponents[j * numEditableComponents]) + multiplierText;
            IconizeUIElement(componentTitle, editComponents[j * numEditableComponents].typeName);
            SetIconEnabledColor(componentTitle, editComponents[j * numEditableComponents].enabledEffective);

            Array<Serializable@> components;
            for (uint i = 0; i < numEditableComponents; ++i)
                components.Push(editComponents[j * numEditableComponents + i]);

            UpdateAttributes(components, GetComponentContainer(j).GetChild("AttributeList"), fullUpdate);
        }
    }

    UpdateAttributeInspectorIcons();
}

void UpdateNodeAttributes()
{
    UpdateAttributes(ToSerializableArray(editNodes), nodeContainer.GetChild("AttributeList"), false);
}

void UpdateAttributeInspectorIcons()
{
    Text@ nodeTitle = nodeContainer.GetChild("TitleText");
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
}

void PostEditAttribute(Array<Serializable@>@ serializables, uint index)
{
    // If a StaticModel/AnimatedModel/Skybox model was changed, apply a possibly different material list
    if (applyMaterialList && serializables[0].attributeInfos[index].name == "Model")
    {
        for (uint i = 0; i < serializables.length; ++i)
        {
            StaticModel@ staticModel = cast<StaticModel>(serializables[i]);
            if (staticModel !is null)
                ApplyMaterialList(staticModel);
        }
    }

    SetSceneModified();
}

void SetAttributeEditorID(UIElement@ attrEdit, Array<Serializable@>@ serializables)
{
    // All target serializables must be either nodes or components, so can check the first for the type
    Node@ node = cast<Node>(serializables[0]);
    Array<Variant> ids;
    if (node !is null)
    {
        for (uint i = 0; i < serializables.length; ++i)
            ids.Push(Variant(cast<Node>(serializables[i]).id));
        attrEdit.vars[NODE_IDS_VAR] = ids;
    }
    else
    {
        for (uint i = 0; i < serializables.length; ++i)
            ids.Push(Variant(cast<Component>(serializables[i]).id));
        attrEdit.vars[COMPONENT_IDS_VAR] = ids;
    }
}

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
    }

    return ret;
}

void CreateNewVariable(StringHash eventType, VariantMap& eventData)
{
    if (editNodes.length == 0)
        return;

    DropDownList@ dropDown = eventData["Element"].GetUIElement();
    LineEdit@ nameEdit = attributeInspectorWindow.GetChild("VarNameEdit", true);
    String sanitatedVarName = nameEdit.text.Trimmed().Replaced(";", "");
    if (sanitatedVarName.empty)
        return;

    editorScene.RegisterVar(sanitatedVarName);

    Variant newValue;
    switch (dropDown.selection)
    {
    case 0:
        newValue = int(0);
        break;
    case 1:
        newValue = false;
        break;
    case 2:
        newValue = float(0.0);
        break;
    case 3:
        newValue = String();
        break;
    case 4:
        newValue = Vector3();
        break;
    case 5:
        newValue = Color();
        break;
    }

    // If we overwrite an existing variable, must recreate the attribute-editor(s) for the correct type
    bool overwrite = false;
    for (uint i = 0; i < editNodes.length; ++i)
    {
        overwrite = overwrite || editNodes[i].vars.Contains(sanitatedVarName);
        editNodes[i].vars[sanitatedVarName] = newValue;
    }
    UpdateAttributeInspector(overwrite);
}

void DeleteVariable(StringHash eventType, VariantMap& eventData)
{
    if (editNodes.length == 0)
        return;

    LineEdit@ nameEdit = attributeInspectorWindow.GetChild("VarNameEdit", true);
    String sanitatedVarName = nameEdit.text.Trimmed().Replaced(";", "");
    if (sanitatedVarName.empty)
        return;

    bool erased = false;
    for (uint i = 0; i < editNodes.length; ++i)
    {
        // \todo Should first check whether var in question is editable
        erased = editNodes[i].vars.Erase(sanitatedVarName) || erased;
    }
    if (erased)
        UpdateAttributeInspector(false);
}
