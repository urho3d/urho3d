// Urho3D editor component edit window handling

Window@ nodeWindow;

const uint MIN_NODE_ATTRIBUTES = 4;
const uint MAX_NODE_ATTRIBUTES = 8;

class ResourcePicker
{
    String resourceType;
    String lastPath;
    uint lastFilter;
    Array<String> filters;

    ResourcePicker(const String&in resourceType_, const String&in filter_)
    {
        resourceType = resourceType_;
        filters.Push(filter_);
        lastFilter = 0;
    }

    ResourcePicker(const String&in resourceType_, const Array<String>@ filters_)
    {
        resourceType = resourceType_;
        filters = filters_;
        lastFilter = 0;
    }
}

class VectorStruct
{
    String componentTypeName;
    String attributeName;
    Array<String> variableNames;
    uint restartIndex;

    VectorStruct(const String&in componentTypeName_, const String&in attributeName_, const Array<String>@ variableNames_, uint restartIndex_)
    {
        componentTypeName = componentTypeName_;
        attributeName = attributeName_;
        variableNames = variableNames_;
        restartIndex = restartIndex_;
    }
}

Array<ResourcePicker@> resourcePickers;
Array<VectorStruct@> vectorStructs;

bool inLoadAttributeEditor = false;
uint resourcePickID = 0;
uint resourcePickIndex = 0;
uint resourcePickSubIndex = 0;
ResourcePicker@ resourcePicker;
String resourcePickEditorName;

void CreateNodeWindow()
{
    if (nodeWindow !is null)
        return;

    // Fill resource picker data
    resourcePickers.Push(ResourcePicker("Model", "*.mdl"));
    resourcePickers.Push(ResourcePicker("Material", "*.xml"));
    Array<String> textureFilters;
    textureFilters.Push("*.dds");
    textureFilters.Push("*.jpg");
    textureFilters.Push("*.png");
    resourcePickers.Push(ResourcePicker("Texture2D", textureFilters));
    resourcePickers.Push(ResourcePicker("TextureCube", "*.xml"));
    resourcePickers.Push(ResourcePicker("Animation", "*.ani"));
    resourcePickers.Push(ResourcePicker("ScriptFile", "*.as"));
    resourcePickers.Push(ResourcePicker("XMLFile", "*.xml"));

    // Fill vector structure data
    Array<String> billboardVariables;
    billboardVariables.Push("Number Of Billboards");
    billboardVariables.Push("   Position");
    billboardVariables.Push("   Size");
    billboardVariables.Push("   UV Coordinates");
    billboardVariables.Push("   Color");
    billboardVariables.Push("   Rotation");
    billboardVariables.Push("   Is Enabled");
    vectorStructs.Push(VectorStruct("BillboardSet", "Billboards", billboardVariables, 1));

    nodeWindow = ui.LoadLayout(cache.GetResource("XMLFile", "UI/EditorNodeWindow.xml"), uiStyle);
    ui.root.AddChild(nodeWindow);
    int height = Min(ui.root.height - 60, 500);
    nodeWindow.SetSize(300, height);
    nodeWindow.SetPosition(ui.root.width - 20 - nodeWindow.width, 40);
    nodeWindow.BringToFront();
    UpdateNodeWindow();

    SubscribeToEvent(nodeWindow.GetChild("CloseButton", true), "Released", "HideNodeWindow");
    SubscribeToEvent(nodeWindow.GetChild("NewVarDropDown", true), "ItemSelected", "CreateNewVariable");
    SubscribeToEvent(nodeWindow.GetChild("DeleteVarButton", true), "Released", "DeleteVariable");
}

void HideNodeWindow()
{
    nodeWindow.visible = false;
}

void ShowNodeWindow()
{
    nodeWindow.visible = true;
    nodeWindow.BringToFront();
}

void UpdateNodeWindow()
{
    // If a resource pick was in progress, it cannot be completed now, as component was changed
    PickResourceCanceled();

    Text@ nodeTitle = nodeWindow.GetChild("NodeTitle", true);
    Text@ componentTitle = nodeWindow.GetChild("ComponentTitle", true);

    if (selectedNode is null)
        nodeTitle.text = "No node";
    else
    {
        String localText;
        if (selectedNode.id >= FIRST_LOCAL_ID)
            localText = ", Local";
        nodeTitle.text = selectedNode.typeName + " (ID " + String(selectedNode.id) + localText + ")";
    }

    if (selectedComponent is null)
        componentTitle.text = "No component";
    else
        componentTitle.text = GetComponentTitle(selectedComponent, 0);

    UpdateAttributes(true);

    if (selectedNode !is null || selectedComponent !is null)
        nodeWindow.visible = true;
}

void UpdateAttributes(bool fullUpdate)
{
    if (nodeWindow !is null)
    {
        UpdateAttributes(selectedNode, nodeWindow.GetChild("NodeAttributeList", true), fullUpdate);
        UpdateAttributes(selectedComponent, nodeWindow.GetChild("ComponentAttributeList", true), fullUpdate);
    }
}

void UpdateAttributes(Serializable@ serializable, ListView@ list, bool fullUpdate)
{
    // If attributes have changed structurally, do a full update
    uint count = GetAttributeEditorCount(serializable);
    if (fullUpdate == false)
    {
        if (list.contentElement.numChildren != count)
            fullUpdate = true;
    }

    // Remember the old scroll position so that a full update does not feel as jarring
    IntVector2 oldViewPos = list.viewPosition;

    if (fullUpdate)
    {
        list.RemoveAllItems();

        // Resize the node editor according to the number of variables, up to a certain maximum
        if (list.name == "NodeAttributeList")
        {
            uint maxAttrs = Clamp(count, MIN_NODE_ATTRIBUTES, MAX_NODE_ATTRIBUTES);
            list.SetFixedHeight(maxAttrs * 18 + 2);
        }
    }

    if (serializable is null)
        return;

    for (uint i = 0; i < serializable.numAttributes; ++i)
    {
        AttributeInfo info = serializable.attributeInfos[i];
        if (info.mode & AM_NOEDIT != 0)
            continue;

        if (fullUpdate)
            CreateAttributeEditor(list, serializable, i);

        LoadAttributeEditor(list, serializable, i);
    }
    
    if (fullUpdate)
        list.viewPosition = oldViewPos;
}

void EditAttribute(StringHash eventType, VariantMap& eventData)
{
    // Changing elements programmatically may cause events to be sent. Stop possible infinite loop in that case.
    if (inLoadAttributeEditor)
        return;

    UIElement@ attrEdit = eventData["Element"].GetUIElement();
    UIElement@ parent = attrEdit.parent;
    Serializable@ serializable = GetAttributeEditorTarget(attrEdit);
    if (serializable is null)
        return;

    uint index = attrEdit.vars["Index"].GetUInt();
    uint subIndex = attrEdit.vars["SubIndex"].GetUInt();
    bool intermediateEdit = eventType == StringHash("TextChanged");

    StoreAttributeEditor(parent, serializable, index, subIndex);
    // Some attributes need the finish step to take effect. This is often to avoid some expensive operation,
    // but while editing every change should happen instantly
    serializable.FinishUpdate();

    // If not an intermediate edit, reload the editor fields with validated values
    // (attributes may have interactions; therefore we load everything, not just the value being edited)
    if (!intermediateEdit)
        UpdateAttributes(false);

    // If node changed, update it in the scene window also
    if (cast<Node>(serializable) !is null)
        UpdateSceneWindowNodeOnly(selectedNode);
}

uint GetAttributeEditorCount(Serializable@ serializable)
{
    uint count = 0;

    if (serializable !is null)
    {
        for (uint i = 0; i < serializable.numAttributes; ++i)
        {
            AttributeInfo info = serializable.attributeInfos[i];
            if (info.mode & AM_NOEDIT != 0)
                continue;
            // Resource editors have the title + the editor row itself, so count 2
            if (info.type == VAR_RESOURCEREF)
                count += 2;
            else if (info.type == VAR_RESOURCEREFLIST)
                count += 2 * serializable.attributes[i].GetResourceRefList().length;
            else if (info.type == VAR_VARIANTVECTOR && GetVectorStruct(serializable, i) !is null)
                count += serializable.attributes[i].GetVariantVector().length;
            else if (info.type == VAR_VARIANTMAP)
                count += serializable.attributes[i].GetVariantMap().length;
            else
                ++count;
        }
    }

    return count;
}

UIElement@ CreateAttributeEditorParentTitle(ListView@ list, String name)
{
    UIElement@ editorParent = UIElement();
    editorParent.SetLayout(LM_HORIZONTAL);
    editorParent.SetFixedHeight(18);
    list.AddItem(editorParent);

    Text@ attrNameText = Text();
    attrNameText.SetStyle(uiStyle, "EditorAttributeText");
    attrNameText.text = name;
    editorParent.AddChild(attrNameText);

    return editorParent;
}

UIElement@ CreateAttributeEditorParent(ListView@ list, String name, uint index, uint subIndex)
{
    UIElement@ editorParent = UIElement("Edit" + String(index) + "_" + String(subIndex));
    editorParent.vars["Index"] = index;
    editorParent.vars["SubIndex"] = subIndex;
    editorParent.SetLayout(LM_HORIZONTAL);
    editorParent.SetFixedHeight(18);
    list.AddItem(editorParent);

    if (!name.empty)
    {
        Text@ attrNameText = Text();
        attrNameText.SetStyle(uiStyle, "EditorAttributeText");
        attrNameText.text = name;
        attrNameText.SetFixedWidth(125);
        editorParent.AddChild(attrNameText);
    }

    return editorParent;
}

LineEdit@ CreateAttributeLineEdit(UIElement@ parent, Serializable@ serializable, uint index, uint subIndex)
{
    LineEdit@ attrEdit = LineEdit();
    attrEdit.SetStyle(uiStyle, "EditorAttributeEdit");
    attrEdit.SetFixedHeight(16);
    attrEdit.vars["Index"] = index;
    attrEdit.vars["SubIndex"] = subIndex;
    SetAttributeEditorID(attrEdit, serializable);
    parent.AddChild(attrEdit);
    return attrEdit;
}

void SetAttributeEditorID(UIElement@ attrEdit, Serializable@ serializable)
{
    // Serializable does not expose the ID, so must cast into both Node & Component
    Node@ node = cast<Node>(serializable);
    Component@ component = cast<Component>(serializable);
    if (node !is null)
        attrEdit.vars["NodeID"] = node.id;
    else if (component !is null)
        attrEdit.vars["ComponentID"] = component.id;
}

Serializable@ GetAttributeEditorTarget(UIElement@ attrEdit)
{
    if (attrEdit.vars.Contains("NodeID"))
        return editorScene.GetNodeByID(attrEdit.vars["NodeID"].GetUInt());
    else if (attrEdit.vars.Contains("ComponentID"))
        return editorScene.GetComponentByID(attrEdit.vars["ComponentID"].GetUInt());
    else
        return null;
}

UIElement@ GetAttributeEditorParent(UIElement@ parent, uint index, uint subIndex)
{
    return parent.GetChild("Edit" + String(index) + "_" + String(subIndex), true);
}

VectorStruct@ GetVectorStruct(Serializable@ serializable, uint index)
{
    AttributeInfo info = serializable.attributeInfos[index];
    for (uint i = 0; i < vectorStructs.length; ++i)
    {
        if (vectorStructs[i].componentTypeName == serializable.typeName && vectorStructs[i].attributeName ==
            info.name)
            return vectorStructs[i];
    }
    return null;
}

void CreateAttributeEditor(ListView@ list, Serializable@ serializable, uint index)
{
    AttributeInfo info = serializable.attributeInfos[index];
    CreateAttributeEditor(list, serializable, info.name, info.type, info.enumNames, index, 0);
}

UIElement@ CreateAttributeEditor(ListView@ list, Serializable@ serializable, const String&in name, VariantType type, Array<String>@ enumNames, uint index, uint subIndex)
{
    UIElement@ parent;

    if (type == VAR_STRING)
    {
        parent = CreateAttributeEditorParent(list, name, index, subIndex);
        LineEdit@ attrEdit = CreateAttributeLineEdit(parent, serializable, index, subIndex);
        SubscribeToEvent(attrEdit, "TextChanged", "EditAttribute");
        SubscribeToEvent(attrEdit, "TextFinished", "EditAttribute");
    }
    if (type == VAR_BOOL)
    {
        parent = CreateAttributeEditorParent(list, name, index, subIndex);
        CheckBox@ attrEdit = CheckBox();
        attrEdit.style = uiStyle;
        attrEdit.SetFixedSize(16, 16);
        attrEdit.vars["Index"] = index;
        attrEdit.vars["SubIndex"] = subIndex;
        SetAttributeEditorID(attrEdit, serializable);
        parent.AddChild(attrEdit);
        SubscribeToEvent(attrEdit, "Toggled", "EditAttribute");
    }
    if ((type >= VAR_FLOAT && type <= VAR_VECTOR4) || type == VAR_QUATERNION || type == VAR_COLOR)
    {
        parent = CreateAttributeEditorParent(list, name, index, subIndex);
        uint numCoords = type - VAR_FLOAT + 1;
        if (type == VAR_QUATERNION)
            numCoords = 3;
        if (type == VAR_COLOR)
            numCoords = 4;

        for (uint i = 0; i < numCoords; ++i)
        {
            LineEdit@ attrEdit = CreateAttributeLineEdit(parent, serializable, index, subIndex);
            SubscribeToEvent(attrEdit, "TextChanged", "EditAttribute");
            SubscribeToEvent(attrEdit, "TextFinished", "EditAttribute");
        }
    }
    if (type == VAR_INT)
    {
        parent = CreateAttributeEditorParent(list, name, index, subIndex);
        // Check for enums
        if (enumNames is null || enumNames.empty)
        {
            // No enums, create a numeric editor
            LineEdit@ attrEdit = CreateAttributeLineEdit(parent, serializable, index, subIndex);
            SubscribeToEvent(attrEdit, "TextChanged", "EditAttribute");
            SubscribeToEvent(attrEdit, "TextFinished", "EditAttribute");
        }
        else
        {
            DropDownList@ attrEdit = DropDownList();
            attrEdit.style = uiStyle;
            attrEdit.SetFixedHeight(16);
            attrEdit.resizePopup = true;
            attrEdit.vars["Index"] = index;
            attrEdit.vars["SubIndex"] = subIndex;
            SetAttributeEditorID(attrEdit, serializable);

            for (uint i = 0; i < enumNames.length; ++i)
            {
                // Hack: check for certain internal enums and break
                if (enumNames[i] == "Master" || enumNames[i] == "SplitPoint")
                    break;
                Text@ choice = Text();
                choice.SetStyle(uiStyle, "EditorEnumAttributeText");
                choice.text = enumNames[i];
                attrEdit.AddItem(choice);
            }
            parent.AddChild(attrEdit);
            SubscribeToEvent(attrEdit, "ItemSelected", "EditAttribute");
        }
    }
    if (type == VAR_RESOURCEREF)
    {
        ShortStringHash resourceType = serializable.attributeInfos[index].type == VAR_RESOURCEREF ?
            serializable.attributes[index].GetResourceRef().type : serializable.attributes[index].GetResourceRefList().type;

        // Create the resource name on a separate non-interactive line to allow for more space
        CreateAttributeEditorParentTitle(list, name);

        parent = CreateAttributeEditorParent(list, "", index, subIndex);

        UIElement@ spacer = UIElement();
        spacer.SetFixedSize(10, 16);
        parent.AddChild(spacer);

        LineEdit@ attrEdit = CreateAttributeLineEdit(parent, serializable, index, subIndex);
        attrEdit.vars["Type"] = resourceType.value;
        SubscribeToEvent(attrEdit, "TextFinished", "EditAttribute");

        UIElement@ spacer2 = UIElement();
        spacer2.SetFixedSize(4, 16);
        parent.AddChild(spacer2);

        Button@ pickButton = Button();
        pickButton.style = uiStyle;
        pickButton.SetFixedSize(36, 16);
        pickButton.vars["Index"] = index;
        pickButton.vars["SubIndex"] = subIndex;
        SetAttributeEditorID(pickButton, serializable);

        Text@ pickButtonText = Text();
        pickButtonText.SetStyle(uiStyle, "EditorAttributeText");
        pickButtonText.SetAlignment(HA_CENTER, VA_CENTER);
        pickButtonText.text = "Pick";
        pickButton.AddChild(pickButtonText);
        parent.AddChild(pickButton);
        SubscribeToEvent(pickButton, "Released", "PickResource");

        UIElement@ spacer3 = UIElement();
        spacer3.SetFixedSize(4, 16);
        parent.AddChild(spacer3);

        Button@ openButton = Button();
        openButton.style = uiStyle;
        openButton.SetFixedSize(36, 16);
        openButton.vars["Index"] = index;
        openButton.vars["SubIndex"] = subIndex;
        SetAttributeEditorID(openButton, serializable);

        Text@ openButtonText = Text();
        openButtonText.SetStyle(uiStyle, "EditorAttributeText");
        openButtonText.SetAlignment(HA_CENTER, VA_CENTER);
        openButtonText.text = "Open";
        openButton.AddChild(openButtonText);
        parent.AddChild(openButton);
        SubscribeToEvent(openButton, "Released", "OpenResource");
    }
    if (type == VAR_RESOURCEREFLIST)
    {
        uint numRefs = serializable.attributes[index].GetResourceRefList().length;
        for (uint i = 0; i < numRefs; ++i)
            CreateAttributeEditor(list, serializable, name, VAR_RESOURCEREF, null, index, i);
    }
    if (type == VAR_VARIANTVECTOR)
    {
        VectorStruct@ vectorStruct = GetVectorStruct(serializable, index);
        if (vectorStruct is null)
            return null;
        uint nameIndex = 0;

        Array<Variant>@ vector = serializable.attributes[index].GetVariantVector();
        for (uint i = 0; i < vector.length; ++i)
        {
            CreateAttributeEditor(list, serializable, vectorStruct.variableNames[nameIndex], vector[i].type, null, index, i);
            ++nameIndex;
            if (nameIndex >= vectorStruct.variableNames.length)
                nameIndex = vectorStruct.restartIndex;
        }
    }
    if (type == VAR_VARIANTMAP)
    {
        VariantMap map = serializable.attributes[index].GetVariantMap();
        Array<ShortStringHash>@ keys = map.keys;
        for (uint i = 0; i < keys.length; ++i)
        {
            Variant value = map[keys[i]];
            parent = CreateAttributeEditor(list, serializable, editorScene.GetVarName(keys[i]) + " (Var)", value.type, null, index, i);
            // Add the variant key to the parent
            parent.vars["Key"] = keys[i].value;
        }
    }

    return parent;
}

void LoadAttributeEditor(ListView@ list, Serializable@ serializable, uint index)
{
    UIElement@ parent = GetAttributeEditorParent(list, index, 0);
    if (parent is null)
        return;

    inLoadAttributeEditor = true;

    AttributeInfo info = serializable.attributeInfos[index];
    Variant value = serializable.attributes[index];
    LoadAttributeEditor(parent, value, value.type, info.enumNames);

    inLoadAttributeEditor = false;
}

void LoadAttributeEditor(UIElement@ parent, Variant value, VariantType type, Array<String>@ enumNames)
{
    uint index = parent.vars["Index"].GetUInt();
    
    if (type == VAR_STRING)
    {
        LineEdit@ attrEdit = parent.children[1];
        attrEdit.text = value.GetString();
    }
    if (type == VAR_BOOL)
    {
        CheckBox@ attrEdit = parent.children[1];
        attrEdit.checked = value.GetBool();
    }
    if (type == VAR_FLOAT)
    {
        LineEdit@ attrEdit = parent.children[1];
        attrEdit.text = String(value.GetFloat());
    }
    if (type == VAR_VECTOR2)
    {
        Vector2 vec = value.GetVector2();
        LineEdit@ attrEditX = parent.children[1];
        LineEdit@ attrEditY = parent.children[2];
        attrEditX.text = String(vec.x);
        attrEditY.text = String(vec.y);
        attrEditX.cursorPosition = 0;
        attrEditY.cursorPosition = 0;
    }
    if (type == VAR_VECTOR3)
    {
        Vector3 vec = value.GetVector3();
        LineEdit@ attrEditX = parent.children[1];
        LineEdit@ attrEditY = parent.children[2];
        LineEdit@ attrEditZ = parent.children[3];
        attrEditX.text = String(vec.x);
        attrEditY.text = String(vec.y);
        attrEditZ.text = String(vec.z);
        attrEditX.cursorPosition = 0;
        attrEditY.cursorPosition = 0;
        attrEditZ.cursorPosition = 0;     
    }
    if (type == VAR_VECTOR4)
    {
        Vector4 vec = value.GetVector4();
        LineEdit@ attrEditX = parent.children[1];
        LineEdit@ attrEditY = parent.children[2];
        LineEdit@ attrEditZ = parent.children[3];
        LineEdit@ attrEditW = parent.children[4];
        attrEditX.text = String(vec.x);
        attrEditY.text = String(vec.y);
        attrEditZ.text = String(vec.z);
        attrEditW.text = String(vec.w);
        attrEditX.cursorPosition = 0;
        attrEditY.cursorPosition = 0;
        attrEditZ.cursorPosition = 0;
        attrEditW.cursorPosition = 0;      
    }
    if (type == VAR_COLOR)
    {
        Color col = value.GetColor();
        LineEdit@ attrEditR = parent.children[1];
        LineEdit@ attrEditG = parent.children[2];
        LineEdit@ attrEditB = parent.children[3];
        LineEdit@ attrEditA = parent.children[4];
        attrEditR.text = String(col.r);
        attrEditG.text = String(col.g);
        attrEditB.text = String(col.b);
        attrEditA.text = String(col.a);
    }
    if (type == VAR_QUATERNION)
    {
        Vector3 vec = value.GetQuaternion().eulerAngles;
        LineEdit@ attrEditX = parent.children[1];
        LineEdit@ attrEditY = parent.children[2];
        LineEdit@ attrEditZ = parent.children[3];
        attrEditX.text = String(vec.x);
        attrEditY.text = String(vec.y);
        attrEditZ.text = String(vec.z);
        attrEditX.cursorPosition = 0;
        attrEditY.cursorPosition = 0;
        attrEditZ.cursorPosition = 0;
    }
    if (type == VAR_INT)
    {
        if (enumNames is null || enumNames.empty)
        {
            LineEdit@ attrEdit = parent.children[1];
            attrEdit.text = String(value.GetInt());
        }
        else
        {
            DropDownList@ attrEdit = parent.children[1];
            attrEdit.selection = value.GetInt();
        }
    }
    if (type == VAR_RESOURCEREF)
    {
        LineEdit@ attrEdit = parent.children[1];
        attrEdit.text = cache.GetResourceName(value.GetResourceRef().id);
        attrEdit.cursorPosition = 0;
    }
    if (type == VAR_RESOURCEREFLIST)
    {
        UIElement@ list = parent.parent;
        ResourceRefList refList = value.GetResourceRefList();
        for (uint subIndex = 0; subIndex < refList.length; ++subIndex)
        {
            parent = GetAttributeEditorParent(list, index, subIndex);
            if (parent is null)
                break;
            LineEdit@ attrEdit = parent.children[1];
            attrEdit.text = cache.GetResourceName(refList.ids[subIndex]);
            attrEdit.cursorPosition = 0;
        }
    }
    if (type == VAR_VARIANTVECTOR)
    {
        UIElement@ list = parent.parent;
        Array<Variant>@ vector = value.GetVariantVector();
        for (uint i = 0; i < vector.length; ++i)
        {
            parent = GetAttributeEditorParent(list, index, i);
            if (parent is null)
                break;
            LoadAttributeEditor(parent, vector[i], vector[i].type, null);
        }
    }
    if (type == VAR_VARIANTMAP)
    {
        UIElement@ list = parent.parent;
        VariantMap map = value.GetVariantMap();
        Array<ShortStringHash>@ keys = map.keys;
        for (uint i = 0; i < keys.length; ++i)
        {
            parent = GetAttributeEditorParent(list, index, i);
            if (parent is null)
                break;
            Variant value = map[keys[i]];
            LoadAttributeEditor(parent, value, value.type, null);
        }
    }
}

void StoreAttributeEditor(UIElement@ parent, Serializable@ serializable, uint index, uint subIndex)
{
    AttributeInfo info = serializable.attributeInfos[index];

    if (info.type == VAR_RESOURCEREFLIST)
    {
        ResourceRefList refList = serializable.attributes[index].GetResourceRefList();
        Variant newValue = GetEditorValue(parent, VAR_RESOURCEREF, null);
        ResourceRef ref = newValue.GetResourceRef();
        refList.ids[subIndex] = ref.id;
        serializable.attributes[index] = Variant(refList);
    }
    else if (info.type == VAR_VARIANTVECTOR)
    {
        Array<Variant>@ vector = serializable.attributes[index].GetVariantVector();
        Variant newValue = GetEditorValue(parent, vector[subIndex].type, null);
        vector[subIndex] = newValue;
        serializable.attributes[index] = Variant(vector);
    }
    else if (info.type == VAR_VARIANTMAP)
    {
        VariantMap map = serializable.attributes[index].GetVariantMap();
        ShortStringHash key(parent.vars["Key"].GetUInt());
        Variant newValue = GetEditorValue(parent, map[key].type, null);
        map[key] = newValue;
        serializable.attributes[index] = Variant(map);
    }
    else
    {
        Variant newValue = GetEditorValue(parent, info.type, info.enumNames);
        serializable.attributes[index] = newValue;
    }
}

Variant GetEditorValue(UIElement@ parent, VariantType type, Array<String>@ enumNames)
{
    if (type == VAR_STRING)
    {
        LineEdit@ attrEdit = parent.children[1];
        return Variant(attrEdit.text.Trimmed());
    }
    if (type == VAR_BOOL)
    {
        CheckBox@ attrEdit = parent.children[1];
        return Variant(attrEdit.checked);
    }
    if (type == VAR_FLOAT)
    {
        LineEdit@ attrEdit = parent.children[1];
        return Variant(attrEdit.text.ToFloat());
    }
    if (type == VAR_VECTOR2)
    {
        LineEdit@ attrEditX = parent.children[1];
        LineEdit@ attrEditY = parent.children[2];
        Vector2 vec(attrEditX.text.ToFloat(), attrEditY.text.ToFloat());
        return Variant(vec);
    }
    if (type == VAR_VECTOR3)
    {
        LineEdit@ attrEditX = parent.children[1];
        LineEdit@ attrEditY = parent.children[2];
        LineEdit@ attrEditZ = parent.children[3];
        Vector3 vec(attrEditX.text.ToFloat(), attrEditY.text.ToFloat(), attrEditZ.text.ToFloat());
        return Variant(vec);
    }
    if (type == VAR_VECTOR4)
    {
        LineEdit@ attrEditX = parent.children[1];
        LineEdit@ attrEditY = parent.children[2];
        LineEdit@ attrEditZ = parent.children[3];
        LineEdit@ attrEditW = parent.children[4];
        Vector4 vec(attrEditX.text.ToFloat(), attrEditY.text.ToFloat(), attrEditZ.text.ToFloat(), attrEditW.text.ToFloat());
        return Variant(vec);
    }
    if (type == VAR_COLOR)
    {
        LineEdit@ attrEditR = parent.children[1];
        LineEdit@ attrEditG = parent.children[2];
        LineEdit@ attrEditB = parent.children[3];
        LineEdit@ attrEditA = parent.children[4];
        Color col(attrEditR.text.ToFloat(), attrEditG.text.ToFloat(), attrEditB.text.ToFloat(), attrEditA.text.ToFloat());
        return Variant(col);
    }
    if (type == VAR_QUATERNION)
    {
        LineEdit@ attrEditX = parent.children[1];
        LineEdit@ attrEditY = parent.children[2];
        LineEdit@ attrEditZ = parent.children[3];
        Vector3 vec(attrEditX.text.ToFloat(), attrEditY.text.ToFloat(), attrEditZ.text.ToFloat());
        return Variant(Quaternion(vec));
    }
    if (type == VAR_INT)
    {
        if (enumNames is null || enumNames.empty)
        {
            LineEdit@ attrEdit = parent.children[1];
            return Variant(attrEdit.text.ToInt());
        }
        else
        {
            DropDownList@ attrEdit = parent.children[1];
            return Variant(attrEdit.selection);
        }
    }
    if (type == VAR_RESOURCEREF)
    {
        LineEdit@ attrEdit = parent.children[1];
        ResourceRef ref;
        ref.id = StringHash(attrEdit.text.Trimmed());
        ref.type = ShortStringHash(attrEdit.vars["Type"].GetUInt());
        return Variant(ref);
    }
    
    return Variant();
}

ResourcePicker@ GetResourcePicker(const String&in resourceType)
{
    for (uint i = 0; i < resourcePickers.length; ++i)
    {
        if (resourcePickers[i].resourceType.Compare(resourceType, false) == 0)
            return resourcePickers[i];
    }

    return null;
}

void PickResource(StringHash eventType, VariantMap& eventData)
{
    if (uiFileSelector !is null)
        return;

    UIElement@ button = eventData["Element"].GetUIElement();
    LineEdit@ attrEdit = button.parent.children[1];
    // Note: nodes never contain resources. Therefore can assume the target is always a component
    Component@ target = GetAttributeEditorTarget(attrEdit);
    if (target is null)
        return;

    resourcePickIndex = attrEdit.vars["Index"].GetUInt();
    resourcePickSubIndex = attrEdit.vars["SubIndex"].GetUInt();
    AttributeInfo info = target.attributeInfos[resourcePickIndex];

    if (info.type == VAR_RESOURCEREF)
    {
        String resourceType = GetTypeName(target.attributes[resourcePickIndex].GetResourceRef().type);
        // Hack: if the resource is a light's shape texture, change resource type according to light type
        // (TextureCube for point light)
        if (info.name == "Light Shape Texture" && cast<Light>(target).lightType == LIGHT_POINT)
            resourceType = "TextureCube";
        @resourcePicker = GetResourcePicker(resourceType);
    }
    else if (info.type == VAR_RESOURCEREFLIST)
    {
        String resourceType = GetTypeName(target.attributes[resourcePickIndex].GetResourceRefList().type);
        @resourcePicker = GetResourcePicker(resourceType);
    }
    else
        @resourcePicker = null;

    if (resourcePicker is null)
        return;

    resourcePickID = target.id;
    String lastPath = resourcePicker.lastPath;
    if (lastPath.empty)
        lastPath = sceneResourcePath;
    CreateFileSelector("Pick " + resourcePicker.resourceType, "OK", "Cancel", lastPath, resourcePicker.filters, resourcePicker.lastFilter);
    SubscribeToEvent(uiFileSelector, "FileSelected", "PickResourceDone");
}

void PickResourceDone(StringHash eventType, VariantMap& eventData)
{
    // Store filter and directory for next time
    if (resourcePicker !is null)
    {
        resourcePicker.lastPath = uiFileSelector.path;
        resourcePicker.lastFilter = uiFileSelector.filterIndex;
    }

    CloseFileSelector();

    if (!eventData["OK"].GetBool())
    {
        resourcePickID = 0;
        @resourcePicker = null;
        return;
    }

    Component@ target = editorScene.GetComponentByID(resourcePickID);
    if (target is null || resourcePicker is null)
        return;

    // Validate the resource. It must come from within a registered resource directory, and be loaded successfully
    String resourceName = eventData["FileName"].GetString();
    Array<String>@ resourceDirs = cache.resourceDirs;
    Resource@ res;
    for (uint i = 0; i < resourceDirs.length; ++i)
    {
        if (!resourceName.ToLower().StartsWith(resourceDirs[i].ToLower()))
            continue;
        resourceName = resourceName.Substring(resourceDirs[i].length);
        res = cache.GetResource(resourcePicker.resourceType, resourceName);
        break;
    }
    if (res is null)
        return;

    AttributeInfo info = target.attributeInfos[resourcePickIndex];
    if (info.type == VAR_RESOURCEREF)
    {
        ResourceRef ref = target.attributes[resourcePickIndex].GetResourceRef();
        ref.type = ShortStringHash(resourcePicker.resourceType);
        ref.id = StringHash(resourceName);
        target.attributes[resourcePickIndex] = Variant(ref);
        target.FinishUpdate();
    }
    else if (info.type == VAR_RESOURCEREFLIST)
    {
        ResourceRefList refList = target.attributes[resourcePickIndex].GetResourceRefList();
        if (resourcePickSubIndex < refList.length)
        {
            refList.ids[resourcePickSubIndex] = StringHash(resourceName);
            target.attributes[resourcePickIndex] = Variant(refList);
            target.FinishUpdate();
        }
    }

    UpdateAttributes(false);

    resourcePickID = 0;
    @resourcePicker = null;
}

void PickResourceCanceled()
{
    if (resourcePickID != 0)
    {
        resourcePickID = 0;
        @resourcePicker = null;
        CloseFileSelector();
    }
}

void OpenResource(StringHash eventType, VariantMap& eventData)
{
    UIElement@ button = eventData["Element"].GetUIElement();
    LineEdit@ attrEdit = button.parent.children[1];
    
    String fileName = attrEdit.text.Trimmed();
    if (fileName.empty)
        return;

    Array<String>@ resourceDirs = cache.resourceDirs;
    for (uint i = 0; i < resourceDirs.length; ++i)
    {
        String fullPath = resourceDirs[i] + fileName;
        if (fileSystem.FileExists(fullPath))
        {
            fileSystem.SystemOpen(fullPath, "");
            return;
        }
    }
}

void CreateNewVariable(StringHash eventType, VariantMap& eventData)
{
    if (selectedNode is null)
        return;

    DropDownList@ dropDown = eventData["Element"].GetUIElement();
    LineEdit@ nameEdit = nodeWindow.GetChild("VarNameEdit", true);
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

    // If we overwrite an existing variable, must recreate the editor(s) for the correct type
    bool overwrite = selectedNode.vars.Contains(sanitatedVarName);
    selectedNode.vars[sanitatedVarName] = newValue;
    UpdateAttributes(overwrite);
}

void DeleteVariable(StringHash eventType, VariantMap& eventData)
{
    if (selectedNode is null)
        return;

    LineEdit@ nameEdit = nodeWindow.GetChild("VarNameEdit", true);
    String sanitatedVarName = nameEdit.text.Trimmed().Replaced(";", "");
    if (sanitatedVarName.empty)
        return;

    selectedNode.vars.Erase(sanitatedVarName);
    UpdateAttributes(false);
}