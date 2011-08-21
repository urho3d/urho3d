// Urho3D editor component edit window handling

Window@ nodeWindow;

const uint MAX_ATTRNAME_LENGTH = 28;

class ResourceEditorData
{
    String resourceType;
    String lastPath;
    Array<String> filters;

    ResourceEditorData(const String&in resourceType_, const String&in filter_)
    {
        resourceType = resourceType_;
        filters.Push(filter_);
    }

    ResourceEditorData(const String&in resourceType_, const Array<String>@ filters_)
    {
        resourceType = resourceType_;
        filters = filters_;
    }
}

Array<ResourceEditorData@> resourceEditors;

bool inLoadAttributeEditor = false;
uint resourcePickType = 0;
String resourcePickEditorName;

void CreateNodeWindow()
{
    if (nodeWindow !is null)
        return;

    // Fill resource editor data
    resourceEditors.Push(ResourceEditorData("Model", "*.mdl"));
    resourceEditors.Push(ResourceEditorData("Material", "*.xml"));
    Array<String> textureFilters;
    textureFilters.Push("*.dds");
    textureFilters.Push("*.jpg");
    textureFilters.Push("*.png");
    resourceEditors.Push(ResourceEditorData("Texture2D", textureFilters));
    resourceEditors.Push(ResourceEditorData("TextureCube", "*.xml"));
    resourceEditors.Push(ResourceEditorData("Animation", "*.ani"));
    resourceEditors.Push(ResourceEditorData("ScriptFile", "*.as"));
    resourceEditors.Push(ResourceEditorData("XMLFile", "*.xml"));

    nodeWindow = ui.LoadLayout(cache.GetResource("XMLFile", "UI/EditorNodeWindow.xml"), uiStyle);
    ui.root.AddChild(nodeWindow);
    int height = Min(ui.root.height - 60, 500);
    nodeWindow.SetSize(300, height);
    nodeWindow.SetPosition(ui.root.width - 20 - nodeWindow.width, 40);
    nodeWindow.visible = true;
    UpdateNodeWindow();

    SubscribeToEvent(nodeWindow.GetChild("CloseButton", true), "Released", "HideNodeWindow");
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
    if (fullUpdate == false)
    {
        uint count = GetAttributeEditorCount(serializable);
        if (list.contentElement.numChildren != count)
            fullUpdate = true;
    }
    
    if (fullUpdate)
        list.RemoveAllItems();

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
    bool intermediateEdit = eventType == StringHash("TextChanged");

    StoreAttributeEditorDirect(parent, serializable, index);
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

void PickResource(StringHash eventType, VariantMap& eventData)
{
    if (uiFileSelector !is null)
        return;

    /*
    UIElement@ button = eventData["Element"].GetUIElement();
    LineEdit@ attrEdit = button.parent.children[1];
    uint type = uint(attrEdit.vars["Type"].GetInt());

    ResourceEditorData@ data = resourceEditors[type - ATTR_EDITOR_RESOURCE];

    Array<String> filters;
    filters.Push("*" + data.fileExtension);
    String lastPath = data.lastPath;
    if (lastPath.empty)
        lastPath = sceneResourcePath;
    CreateFileSelector("Pick " + data.resourceType, "OK", "Cancel", lastPath, filters, 0);
    SubscribeToEvent(uiFileSelector, "FileSelected", "PickResourceDone");

    resourcePickType = type;
    resourcePickEditorName = attrEdit.name;
    */
}

void OpenResource(StringHash eventType, VariantMap& eventData)
{
    UIElement@ button = eventData["Element"].GetUIElement();
    LineEdit@ attrEdit = button.parent.children[1];
    fileSystem.SystemOpen(sceneResourcePath + attrEdit.text, "");
}

void PickResourceDone(StringHash eventType, VariantMap& eventData)
{
    CloseFileSelector();

    if (!eventData["OK"].GetBool())
    {
        resourcePickType = 0;
        return;
    }

    // Check if another component was selected in the meanwhile
    if (resourcePickType == 0)
        return;

    /*
    ResourceEditorData@ data = resourceEditors[resourcePickType - ATTR_EDITOR_RESOURCE];
    resourcePickType = 0;

    ListView@ list = nodeWindow.GetChild("AttributeList", true);
    LineEdit@ attrEdit = list.GetChild(resourcePickEditorName, true);
    if (attrEdit is null)
        return;

    // Validate the resource. It must come from within the scene resource directory, and be loaded successfully
    String resourceName = eventData["FileName"].GetString();
    if (resourceName.find(sceneResourcePath) != 0)
        return;
    data.lastPath = GetPath(resourceName);

    resourceName = resourceName.substr(sceneResourcePath.length());

    Resource@ res = cache.GetResource(data.resourceType, resourceName);
    if (res is null)
        return;

    attrEdit.SetText(resourceName);
    editComponentAttribute(attrEdit, false);
    */
}

void PickResourceCanceled()
{
    if (resourcePickType != 0)
    {
        resourcePickType = 0;
        CloseFileSelector();
    }
}

uint GetAttributeEditorCount(Serializable@ serializable)
{
    uint count = 0;

    if (serializable !is null)
    {
        for (uint i = 0; i < serializable.numAttributes; ++i)
        {
            // Resource editors have the title + the editor row itself, so count 2
            if (serializable.attributeInfos[i].type == VAR_RESOURCEREF)
                count += 2;
            else if (serializable.attributeInfos[i].type == VAR_RESOURCEREFLIST)
                count += 2 * serializable.attributes[i].GetResourceRefList().length;
            else
                ++count;
        }
    }

    return count;
}

UIElement@ CreateAttributeEditorTextBar(ListView@ list, String name)
{
    UIElement@ editorBar = UIElement();
    editorBar.SetLayout(LM_HORIZONTAL);
    editorBar.SetFixedHeight(18);
    list.AddItem(editorBar);

    Text@ attrNameText = Text();
    attrNameText.SetStyle(uiStyle, "EditorAttributeText");
    attrNameText.text = name;
    editorBar.AddChild(attrNameText);

    return editorBar;
}

UIElement@ CreateAttributeEditorBar(ListView@ list, String name, uint index, uint subIndex)
{
    if (name.length > MAX_ATTRNAME_LENGTH)
        name.Resize(MAX_ATTRNAME_LENGTH);

    UIElement@ editorBar = UIElement("Edit" + String(index) + "_" + String(subIndex));
    editorBar.SetLayout(LM_HORIZONTAL);
    editorBar.SetFixedHeight(18);
    list.AddItem(editorBar);

    if (!name.empty)
    {
        Text@ attrNameText = Text();
        attrNameText.SetStyle(uiStyle, "EditorAttributeText");
        attrNameText.text = name;
        attrNameText.SetFixedWidth(125);
        editorBar.AddChild(attrNameText);
    }

    return editorBar;
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

UIElement@ GetAttributeEditorBar(ListView@ list, uint index, uint subIndex)
{
    return list.GetChild("Edit" + String(index) + "_" + String(subIndex), true);
}

void CreateAttributeEditor(ListView@ list, Serializable@ serializable, uint index)
{
    AttributeInfo info = serializable.attributeInfos[index];

    if (info.type == VAR_STRING)
    {
        UIElement@ parent = CreateAttributeEditorBar(list, info.name, index, 0);

        LineEdit@ attrEdit = LineEdit();
        attrEdit.SetStyle(uiStyle, "EditorAttributeEdit");
        attrEdit.SetFixedHeight(16);
        attrEdit.vars["Index"] = index;
        SetAttributeEditorID(attrEdit, serializable);
        parent.AddChild(attrEdit);
        SubscribeToEvent(attrEdit, "TextChanged", "EditAttribute");
        SubscribeToEvent(attrEdit, "TextFinished", "EditAttribute");
    }

    if (info.type == VAR_BOOL)
    {
        UIElement@ parent = CreateAttributeEditorBar(list, info.name, index, 0);

        CheckBox@ attrEdit = CheckBox();
        attrEdit.style = uiStyle;
        attrEdit.SetFixedSize(16, 16);
        attrEdit.vars["Index"] = index;
        SetAttributeEditorID(attrEdit, serializable);
        parent.AddChild(attrEdit);
        SubscribeToEvent(attrEdit, "Toggled", "EditAttribute");
    }

    if ((info.type >= VAR_FLOAT && info.type <= VAR_VECTOR4) || info.type == VAR_QUATERNION || info.type == VAR_COLOR)
    {
        UIElement@ parent = CreateAttributeEditorBar(list, info.name, index, 0);

        uint numCoords = info.type - VAR_FLOAT + 1;
        if (info.type == VAR_QUATERNION)
            numCoords = 3;
        if (info.type == VAR_COLOR)
            numCoords = 4;

        for (uint i = 0; i < numCoords; ++i)
        {
            LineEdit@ attrEdit = LineEdit();
            attrEdit.SetStyle(uiStyle, "EditorAttributeEdit");
            attrEdit.SetFixedHeight(16);
            attrEdit.vars["Index"] = index;
            attrEdit.vars["Coord"] = i;
            SetAttributeEditorID(attrEdit, serializable);
            parent.AddChild(attrEdit);
            SubscribeToEvent(attrEdit, "TextChanged", "EditAttribute");
            SubscribeToEvent(attrEdit, "TextFinished", "EditAttribute");
        }
    }

    if (info.type == VAR_INT)
    {
        UIElement@ parent = CreateAttributeEditorBar(list, info.name, index, 0);

        // Check for enums
        Array<String>@ enumNames = info.enumNames;
        if (enumNames.empty)
        {
            // No enums, create a numeric editor
            LineEdit@ attrEdit = LineEdit();
            attrEdit.SetStyle(uiStyle, "EditorAttributeEdit");
            attrEdit.SetFixedHeight(16);
            attrEdit.vars["Index"] = index;
            SetAttributeEditorID(attrEdit, serializable);
            parent.AddChild(attrEdit);
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
            SetAttributeEditorID(attrEdit, serializable);

            for (uint i = 0; i < enumNames.length; ++i)
            {
                // Check for certain internal enums and break
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

    if (info.type == VAR_RESOURCEREF || info.type == VAR_RESOURCEREFLIST)
    {
        uint numRefs = 1;
        // Otherwise we do not yet query the attribute values at this point, but for reflist we must know
        // the number of resources
        if (info.type == VAR_RESOURCEREFLIST)
            numRefs = serializable.attributes[index].GetResourceRefList().length;

        for (uint i = 0; i < numRefs; ++i)
        {
            // Create the resource name on a separate non-interactive line to allow for more space
            if (numRefs == 1)
                CreateAttributeEditorTextBar(list, info.name);
            else
                CreateAttributeEditorTextBar(list, info.name + " " + String(i + 1));

            UIElement@ parent = CreateAttributeEditorBar(list, "", index, i);

            UIElement@ spacer = UIElement();
            spacer.SetFixedSize(12, 16);
            parent.AddChild(spacer);

            LineEdit@ attrEdit = LineEdit();
            attrEdit.SetStyle(uiStyle, "EditorAttributeEdit");
            attrEdit.SetFixedHeight(16);
            attrEdit.vars["Index"] = index;
            attrEdit.vars["SubIndex"] = i;
            SetAttributeEditorID(attrEdit, serializable);
            parent.AddChild(attrEdit);
            SubscribeToEvent(attrEdit, "TextFinished", "EditAttribute");

            UIElement@ spacer2 = UIElement();
            spacer2.SetFixedSize(4, 16);
            parent.AddChild(spacer2);

            Button@ pickButton = Button();
            pickButton.style = uiStyle;
            pickButton.SetFixedSize(36, 16);
            pickButton.vars["Index"] = index;
            pickButton.vars["SubIndex"] = i;
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
            openButton.vars["SubIndex"] = i;
            SetAttributeEditorID(openButton, serializable);
    
            Text@ openButtonText = Text();
            openButtonText.SetStyle(uiStyle, "EditorAttributeText");
            openButtonText.SetAlignment(HA_CENTER, VA_CENTER);
            openButtonText.text = "Open";
            openButton.AddChild(openButtonText);
            parent.AddChild(openButton);
            SubscribeToEvent(openButton, "Released", "OpenResource");
        }
    }
}

void LoadAttributeEditor(ListView@ list, Serializable@ serializable, uint index)
{
    UIElement@ parent = GetAttributeEditorBar(list, index, 0);
    if (parent is null)
        return;

    inLoadAttributeEditor = true;

    AttributeInfo info = serializable.attributeInfos[index];
    Variant value = serializable.attributes[index];

    if (info.type == VAR_STRING)
    {
        LineEdit@ attrEdit = parent.children[1];
        attrEdit.text = value.GetString();
        attrEdit.cursorPosition = 0;
    }
    if (info.type == VAR_BOOL)
    {
        CheckBox@ attrEdit = parent.children[1];
        attrEdit.checked = value.GetBool();
    }
    if (info.type == VAR_FLOAT)
    {
        LineEdit@ attrEdit = parent.children[1];
        attrEdit.text = String(value.GetFloat());
        attrEdit.cursorPosition = 0;
    }
    if (info.type == VAR_VECTOR2)
    {
        Vector2 vec = value.GetVector2();
        LineEdit@ attrEditX = parent.children[1];
        LineEdit@ attrEditY = parent.children[2];
        attrEditX.text = String(vec.x);
        attrEditY.text = String(vec.y);
        attrEditX.cursorPosition = 0;
        attrEditY.cursorPosition = 0;
    }
    if (info.type == VAR_VECTOR3)
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
    if (info.type == VAR_VECTOR4)
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
    if (info.type == VAR_COLOR)
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
        attrEditR.cursorPosition = 0;
        attrEditG.cursorPosition = 0;
        attrEditB.cursorPosition = 0;
        attrEditA.cursorPosition = 0;
    }
    if (info.type == VAR_QUATERNION)
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
    if (info.type == VAR_INT)
    {
        Array<String>@ enumNames = info.enumNames;
        if (enumNames.empty)
        {
            LineEdit@ attrEdit = parent.children[1];
            attrEdit.text = String(value.GetInt());
            attrEdit.cursorPosition = 0;
        }
        else
        {
            DropDownList@ attrEdit = parent.children[1];
            attrEdit.selection = value.GetInt();
        }
    }
    if (info.type == VAR_RESOURCEREF)
    {
        LineEdit@ attrEdit = parent.children[1];
        attrEdit.text = cache.GetResourceName(value.GetResourceRef().id);
        attrEdit.cursorPosition = 0;
    }
    if (info.type == VAR_RESOURCEREFLIST)
    {
        ResourceRefList refList = value.GetResourceRefList();
        for (uint subIndex = 0; subIndex < refList.length; ++subIndex)
        {
            parent = GetAttributeEditorBar(list, index, subIndex);
            if (parent is null)
                break;
            LineEdit@ attrEdit = parent.children[1];
            attrEdit.text = cache.GetResourceName(refList.ids[subIndex]);
            attrEdit.cursorPosition = 0;
        }
    }

    inLoadAttributeEditor = false;
}

void StoreAttributeEditor(ListView@ list, Serializable@ serializable, uint index)
{
    UIElement@ parent = GetAttributeEditorBar(list, index, 0);
    if (parent is null)
        return;
    StoreAttributeEditorDirect(parent, serializable, index);
}

void StoreAttributeEditorDirect(UIElement@ parent, Serializable@ serializable, uint index)
{
    AttributeInfo info = serializable.attributeInfos[index];
    
    if (info.type == VAR_STRING)
    {
        LineEdit@ attrEdit = parent.children[1];
        serializable.attributes[index] = Variant(attrEdit.text.Trimmed());
    }
    if (info.type == VAR_BOOL)
    {
        CheckBox@ attrEdit = parent.children[1];
        serializable.attributes[index] = Variant(attrEdit.checked);
    }
    if (info.type == VAR_FLOAT)
    {
        LineEdit@ attrEdit = parent.children[1];
        serializable.attributes[index] = Variant(attrEdit.text.ToFloat());
    }
    if (info.type == VAR_VECTOR2)
    {
        LineEdit@ attrEditX = parent.children[1];
        LineEdit@ attrEditY = parent.children[2];
        Vector2 vec(attrEditX.text.ToFloat(), attrEditY.text.ToFloat());
        serializable.attributes[index] = Variant(vec);
    }
    if (info.type == VAR_VECTOR3)
    {
        LineEdit@ attrEditX = parent.children[1];
        LineEdit@ attrEditY = parent.children[2];
        LineEdit@ attrEditZ = parent.children[3];
        Vector3 vec(attrEditX.text.ToFloat(), attrEditY.text.ToFloat(), attrEditZ.text.ToFloat());
        serializable.attributes[index] = Variant(vec);
    }
    if (info.type == VAR_VECTOR4)
    {
        LineEdit@ attrEditX = parent.children[1];
        LineEdit@ attrEditY = parent.children[2];
        LineEdit@ attrEditZ = parent.children[3];
        LineEdit@ attrEditW = parent.children[4];
        Vector4 vec(attrEditX.text.ToFloat(), attrEditY.text.ToFloat(), attrEditZ.text.ToFloat(), attrEditW.text.ToFloat());
        serializable.attributes[index] = Variant(vec);
    }
    if (info.type == VAR_COLOR)
    {
        LineEdit@ attrEditR = parent.children[1];
        LineEdit@ attrEditG = parent.children[2];
        LineEdit@ attrEditB = parent.children[3];
        LineEdit@ attrEditA = parent.children[4];
        Color col(attrEditR.text.ToFloat(), attrEditG.text.ToFloat(), attrEditB.text.ToFloat(), attrEditA.text.ToFloat());
        serializable.attributes[index] = Variant(col);
    }
    if (info.type == VAR_QUATERNION)
    {
        LineEdit@ attrEditX = parent.children[1];
        LineEdit@ attrEditY = parent.children[2];
        LineEdit@ attrEditZ = parent.children[3];
        Vector3 vec(attrEditX.text.ToFloat(), attrEditY.text.ToFloat(), attrEditZ.text.ToFloat());
        serializable.attributes[index] = Variant(Quaternion(vec));
    }
    if (info.type == VAR_INT)
    {
        if (info.enumNames.empty)
        {
            LineEdit@ attrEdit = parent.children[1];
            serializable.attributes[index] = Variant(attrEdit.text.ToInt());
        }
        else
        {
            DropDownList@ attrEdit = parent.children[1];
            serializable.attributes[index] = Variant(attrEdit.selection);
        }
    }
    if (info.type == VAR_RESOURCEREF)
    {
        LineEdit@ attrEdit = parent.children[1];
        ResourceRef ref = serializable.attributes[index].GetResourceRef();
        ref.id = StringHash(attrEdit.text.Trimmed());
        serializable.attributes[index] = Variant(ref);
    }
    if (info.type == VAR_RESOURCEREFLIST)
    {
        LineEdit@ attrEdit = parent.children[1];
        uint subIndex = attrEdit.vars["SubIndex"].GetUInt();
        ResourceRefList refList = serializable.attributes[index].GetResourceRefList();
        refList.ids[subIndex] = StringHash(attrEdit.text.Trimmed());
        serializable.attributes[index] = Variant(refList);
    }
}

