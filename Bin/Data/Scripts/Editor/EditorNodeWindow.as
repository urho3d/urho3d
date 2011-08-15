// Urho3D editor component edit window handling

Window@ nodeWindow;

const uint ATTR_EDITOR_STRING = 0;
const uint ATTR_EDITOR_FLOAT = 1;
const uint ATTR_EDITOR_VECTOR2 = 2;
const uint ATTR_EDITOR_VECTOR3 = 3;
const uint ATTR_EDITOR_VECTOR4 = 4;
const uint ATTR_EDITOR_BOOL = 5;
const uint ATTR_EDITOR_ENUM = 64;
const uint ATTR_EDITOR_RESOURCE = 128;
const uint MAX_ATTRNAME_LENGTH = 15;

class EnumEditorData
{
    String componentType;
    String categoryName;
    String attributeName;
    Array<String>@ choices;

    EnumEditorData(const String&in componentType_, const String&in categoryName_, const String&in attributeName_, Array<String>@ choices_)
    {
        componentType = componentType_;
        categoryName = categoryName_;
        attributeName = attributeName_;
        @choices = choices_;
    }
}

class ResourceEditorData
{
    String componentType;
    String categoryName;
    String attributeName;
    String resourceType;
    String fileExtension;
    String lastPath;

    ResourceEditorData(const String&in componentType_, const String&in categoryName_, const String&in attributeName_, const String&in resourceType_, const String&in fileExtension_)
    {
        componentType = componentType_;
        categoryName = categoryName_;
        attributeName = attributeName_;
        resourceType = resourceType_;
        fileExtension = fileExtension_;
    }
}

Array<EnumEditorData@> enumEditors;
Array<ResourceEditorData@> resourceEditors;

bool inLoadAttributeEditor = false;
uint lastAttributeCount = 0;

uint resourcePickType = 0;
String resourcePickEditorName;

void CreateNodeWindow()
{
    /*
    if (nodeWindow !is null)
        return;

    @nodeWindow = ui.loadLayout(cache.getResource("XMLFile", "UI/NodeWindow.xml"), uiStyle);
    ui.root.addChild(nodeWindow);
    int height = min(ui.root.getHeight() - 60, 500);
    nodeWindow.setSize(300, height);
    nodeWindow.setPosition(ui.root.getWidth() - 20 - nodeWindow.getWidth(), 40);
    nodeWindow.setVisible(true);
    updateNodeWindow();
    
    // Fill enum & resource editor data
    Array<String> lightTypes = {"directional", "spot", "point"};
    Array<String> bodyTypes = {"static", "dynamic", "kinematic"};
    enumEditors.push(EnumEditorData("Light", "light", "type", lightTypes));
    enumEditors.push(EnumEditorData("RigidBody", "body", "mode", bodyTypes));

    resourceEditors.push(ResourceEditorData("", "material", "name", "Material", ".xml"));
    resourceEditors.push(ResourceEditorData("", "model", "name", "Model", ".mdl"));
    resourceEditors.push(ResourceEditorData("", "animation", "name", "Animation", ".ani"));
    resourceEditors.push(ResourceEditorData("RigidBody", "collision", "name", "CollisionShape", ".xml"));
    resourceEditors.push(ResourceEditorData("ScriptInstance", "script", "name", "ScriptFile", ".as"));
    resourceEditors.push(ResourceEditorData("ParticleEmitter", "emitter", "name", "XMLFile", ".xml"));

    subscribeToEvent(nodeWindow.getChild("CloseButton", true), "Released", "HideNodeWindow");
    subscribeToEvent(nodeWindow.getChild("NodeNameEdit", true), "TextFinished", "EditNodeName");
    */
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

    /*
    Text@ entityTitle = nodeWindow.getChild("EntityTitle", true);
    Text@ componentTitle = nodeWindow.getChild("ComponentTitle", true);
    LineEdit@ entityNameEdit = nodeWindow.getChild("EntityNameEdit", true);
    LineEdit@ componentNameEdit = nodeWindow.getChild("ComponentNameEdit", true);
    ListView@ list = nodeWindow.getChild("AttributeList", true);
    list.removeAllItems();
    lastAttributeCount = 0;

    if (selectedEntity is null)
    {
        entityTitle.setText("No entity");
        entityNameEdit.setText("");
        entityNameEdit.setEnabled(false);
    }
    else
    {
        uint entityID = selectedEntity.getID();
        entityTitle.setText("Entity ID " + entityID + " " + (entityID < 65536 ? "(Replicated)" : "(Local)"));
        entityNameEdit.setText(selectedEntity.getName());
        entityNameEdit.setEnabled(true);
    }

    if (selectedComponent is null)
    {
        componentTitle.setText("No component");
        componentNameEdit.setText("");
        componentNameEdit.setEnabled(false);
    }
    else
    {
        componentTitle.setText("Component " + selectedComponent.getTypeName());
        componentNameEdit.setText(selectedComponent.getName());
        componentNameEdit.setEnabled(true);
        updateComponentAttributes();
    }
    */
}

void EditNodeName()
{
    if (selectedNode is null)
        return;
    /*
    LineEdit@ nameEdit = nodeWindow.getChild("EntityNameEdit", true);
    
    BeginModify(selectedNode.id);
    selectedNode.setName(nameEdit.text);
    EndModify(selectedNode.id);

    updateSceneWindowEntityOnly(selectedNode);
    */
}

void UpdateAttributes()
{
    /*
    ListView@ list = nodeWindow.getChild("AttributeList", true);

    // Save component to XML, then inspect the result
    XMLElement rootElem = componentData.createRootElement("component");
    selectedComponent.saveXML(rootElem);
    Node@ node = cast<Node>(selectedComponent);

    // Check amount of attributes. If has changed, do full refresh. Otherwise just refresh values
    XMLElement categoryElem = rootElem.getChildElement();
    uint attributeCount = 0;
    while (categoryElem.notNull())
    {
        attributeCount += categoryElem.getNumAttributes();
        categoryElem = categoryElem.getNextElement();
    }

    categoryElem = rootElem.getChildElement();
    uint index = 0;

    if (attributeCount != lastAttributeCount)
    {
        // If a resource pick was in progress, it cannot be completed now, as component structure was changed
        pickResourceCanceled();

        IntVector2 listOldPos = list.getViewPosition();

        list.removeAllItems();

        attributeCount = 0;
        while (categoryElem.notNull())
        {
            String category = categoryElem.getName();

            Text@ text = Text();
            text.setStyleAuto(uiStyle);
            text.setText(category);
            list.addItem(text);

            {
                UIElement@ spacer = UIElement();
                spacer.setFixedHeight(4);
                list.addItem(spacer);
            }

            Array<String> attrs = categoryElem.getAttributeNames();

            // Do not make the parent node reference editable. It is handled via scene window drag and drop instead
            if ((category == "parent") && (node !is null))
            {
                Node@ parentNode = node.getParent();

                Text@ attrName = Text();
                attrName.setStyle(uiStyle, "EditorAttributeText");
                if (parentNode !is null)
                    attrName.setText(" " + parentNode.getTypeName() + " in " + getEntityTitle(parentNode.getEntity()));
                else
                    attrName.setText(" No parent");

                list.addItem(attrName);
            }
            else
            {
                for (uint i = 0; i < attrs.size(); ++i)
                {
                    String name = attrs[i];
                    if (name.length() > MAX_ATTRNAME_LENGTH)
                        name.resize(MAX_ATTRNAME_LENGTH);
    
                    UIElement@ bar = UIElement();
                    bar.setLayout(LM_HORIZONTAL, 4, IntRect(0, 0, 0, 0));
                    bar.setFixedHeight(18);
                    list.addItem(bar);

                    uint type = getAttributeEditorType(selectedComponent, category, attrs[i], categoryElem.getAttribute(attrs[i]));

                    UIElement@ spacer = UIElement();
                    spacer.setFixedWidth(8);
                    bar.addChild(spacer);

                    // Do not create the name for resource editors
                    if (type < ATTR_EDITOR_RESOURCE)
                    {
                        Text@ attrName = Text();
                        attrName.setStyle(uiStyle, "EditorAttributeText");
                        attrName.setText(name);
                        attrName.setFixedWidth(110);
                        bar.addChild(attrName);
                    }

                    createAttributeEditor(bar, type, categoryElem, index, attrs[i]);
                    loadAttributeEditor(type, categoryElem, index, attrs[i]);
                }
            }

            {
                UIElement@ spacer = UIElement();
                spacer.setFixedHeight(4);
                list.addItem(spacer);
            }

            categoryElem = categoryElem.getNextElement();
            attributeCount += attrs.size();
            ++index;
        }
    
        lastAttributeCount = attributeCount;
        
        // Try to reset to old view position
        list.setViewPosition(listOldPos);
    }
    else
    {
        while (categoryElem.notNull())
        {
            Array<String> attrs = categoryElem.getAttributeNames();
        
            for (uint i = 0; i < attrs.size(); ++i)
            {
                String category = categoryElem.getName();
                uint type = getAttributeEditorType(selectedComponent, category, attrs[i], categoryElem.getAttribute(attrs[i]));
                loadAttributeEditor(type, categoryElem, index, attrs[i]);
            }

            categoryElem = categoryElem.getNextElement();
            ++index;
        }
    }
    */
}

void EditComponentAttribute(StringHash eventType, VariantMap& eventData)
{
    /*
    // Changing elements programmatically may cause events to be sent. Stop possible infinite loop in that case.
    if ((selectedComponent is null) || (inLoadAttributeEditor))
        return;

    UIElement@ attrEdit = eventData["Element"].getUIElement();
    editComponentAttribute(attrEdit, eventType == StringHash("TextChanged"));
    */
}

void EditComponentAttribute(UIElement@ attrEdit, bool intermediateEdit)
{
    /*
    if ((selectedComponent is null) || (inLoadAttributeEditor))
        return;

    XMLElement rootElem = componentData.getRootElement();
    XMLElement categoryElem = rootElem.getChildElement();
    uint index = 0;
    while (categoryElem.notNull())
    {
        if (index == uint(attrEdit.vars["Index"].getInt()))
        {
            storeAttributeEditor(attrEdit.vars["Type"].getInt(), categoryElem, index, attrEdit.vars["Attribute"].getString());

            uint id = selectedComponent.getEntity().id;
            BeginModify(id);
            selectedComponent.loadXML(rootElem);
            selectedComponent.postLoad();
            EndModify(id);

            // If intermediate edit on a numeric field, do not refresh value back from the component to the edit field
            if (!intermediateEdit)
                updateComponentAttributes();
            return;
        }
        categoryElem = categoryElem.getNextElement();
        ++index;
    }
    */
}

void PickResource(StringHash eventType, VariantMap& eventData)
{
    if (uiFileSelector !is null)
        return;

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

    attrEdit.setText(resourceName);
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

int GetAttributeEditorType(Component@ component, const String& in category, const String& in attribute, const String& in value)
{
    /*
    for (uint i = 0; i < enumEditors.size(); ++i)
    {
        if ((category == enumEditors[i].categoryName) && (attribute == enumEditors[i].attributeName) && ((enumEditors[i].componentType.empty())
            || (component.GetTypeName() == enumEditors[i].componentType)))
            return ATTR_EDITOR_ENUM + i;
    }

    for (uint i = 0; i < resourceEditors.size(); ++i)
    {
        if ((category == resourceEditors[i].categoryName) && (attribute == resourceEditors[i].attributeName) && 
            ((resourceEditors[i].componentType.empty()) || (component.GetTypeName() == resourceEditors[i].componentType)))
            return ATTR_EDITOR_RESOURCE + i;
    }

    // Note: we always use valid, ie. just serialized data for this, not own edited values
    if ((category == "animation") && (attribute == "startbone"))
        return ATTR_EDITOR_STRING;
    else if ((category == "script") && (attribute == "class"))
        return ATTR_EDITOR_STRING;
    else if ((value == "true") || (value == "false"))
        return ATTR_EDITOR_BOOL;

    uint coords = value.split(' ').size();
    if (coords == 1)
        return ATTR_EDITOR_FLOAT;
    if (coords == 2)
        return ATTR_EDITOR_VECTOR2;
    else if (coords == 3)
        return ATTR_EDITOR_VECTOR3;
    else if (coords == 4)
        return ATTR_EDITOR_VECTOR4;
    */
    return ATTR_EDITOR_STRING;
}

String GetAttributeEditorName(uint index, const String& in attribute)
{
    return "Attr_" + index + "_" + attribute;
}

void CreateAttributeEditor(UIElement@ bar, uint type, XMLElement categoryElem, uint index, const String& in attribute)
{
    /*
    if (type == ATTR_EDITOR_STRING)
    {
        LineEdit@ attrEdit = LineEdit.GetAttributeEditorName(index, attribute));
        attrEdit.setStyle(uiStyle, "EditorAttributeEdit");
        attrEdit.vars["Type"] = type;
        attrEdit.vars["Index"] = index;
        attrEdit.vars["Attribute"] = attribute;
        attrEdit.setFixedHeight(16);
        bar.addChild(attrEdit);
        subscribeToEvent(attrEdit, "TextFinished", "editComponentAttribute");
    }

    if (type == ATTR_EDITOR_BOOL)
    {
        CheckBox@ attrEdit = CheckBox.GetAttributeEditorName(index, attribute));
        attrEdit.setStyleAuto(uiStyle);
        attrEdit.vars["Type"] = type;
        attrEdit.vars["Index"] = index;
        attrEdit.vars["Attribute"] = attribute;
        attrEdit.setFixedSize(16, 16);
        bar.addChild(attrEdit);
        subscribeToEvent(attrEdit, "Toggled", "editComponentAttribute");
    }

    if ((type >= ATTR_EDITOR_FLOAT) && (type <= ATTR_EDITOR_VECTOR4))
    {
        for (uint i = 0; i < type; ++i)
        {
            LineEdit@ attrEdit = LineEdit.GetAttributeEditorName(index, attribute) + "_" + toString(i));
            attrEdit.setStyle(uiStyle, "EditorAttributeEdit");
            attrEdit.vars["Type"] = type;
            attrEdit.vars["Index"] = index;
            attrEdit.vars["Attribute"] = attribute;
            attrEdit.setFixedHeight(16);
            bar.addChild(attrEdit);
            // For the numeric style editors, subscribe to every change
            subscribeToEvent(attrEdit, "TextChanged", "editComponentAttribute");
            subscribeToEvent(attrEdit, "TextFinished", "editComponentAttribute");
        }
    }
    
    if ((type >= ATTR_EDITOR_ENUM) && (type < ATTR_EDITOR_RESOURCE))
    {
        DropDownList@ attrEdit = DropDownList.GetAttributeEditorName(index, attribute));
        attrEdit.setStyleAuto(uiStyle);
        attrEdit.vars["Type"] = type;
        attrEdit.vars["Index"] = index;
        attrEdit.vars["Attribute"] = attribute;
        attrEdit.setFixedHeight(16);
        attrEdit.setResizePopup(true);
        
        EnumEditorData@ data = enumEditors[type - ATTR_EDITOR_ENUM];
        for (uint i = 0; i < data.choices.size(); ++i)
        {
            Text@ choice = Text();
            choice.setStyle(uiStyle, "EditorEnumAttributeText");
            choice.setText(data.choices[i]);
            attrEdit.addItem(choice);
        }
        bar.addChild(attrEdit);
        
        subscribeToEvent(attrEdit, "ItemSelected", "editComponentAttribute");
    }
    
    if (type >= ATTR_EDITOR_RESOURCE)
    {
        LineEdit@ attrEdit = LineEdit.GetAttributeEditorName(index, attribute));
        attrEdit.setStyle(uiStyle, "EditorAttributeEdit");
        attrEdit.vars["Type"] = type;
        attrEdit.vars["Index"] = index;
        attrEdit.vars["Attribute"] = attribute;
        attrEdit.setFixedHeight(16);
        bar.addChild(attrEdit);
        subscribeToEvent(attrEdit, "TextFinished", "editComponentAttribute");

        Button@ pickButton = Button.GetAttributeEditorName(index, attribute) + "_Pick");
        pickButton.setStyleAuto(uiStyle);
        pickButton.vars["Type"] = type;
        pickButton.vars["Index"] = index;
        pickButton.vars["Attribute"] = attribute;
        pickButton.setFixedSize(36, 16);
        Text@ pickButtonText = Text();
        pickButtonText.setStyle(uiStyle, "EditorAttributeText");
        pickButtonText.setAlignment(HA_CENTER, VA_CENTER);
        pickButtonText.setText("Pick");
        pickButton.addChild(pickButtonText);
        bar.addChild(pickButton);
        subscribeToEvent(pickButton, "Released", "pickResource");

        Button@ openButton = Button.GetAttributeEditorName(index, attribute) + "_Edit");
        openButton.setStyleAuto(uiStyle);
        openButton.vars["Type"] = type;
        openButton.vars["Index"] = index;
        openButton.vars["Attribute"] = attribute;
        openButton.setFixedSize(36, 16);
        Text@ openButtonText = Text();
        openButtonText.setStyle(uiStyle, "EditorAttributeText");
        openButtonText.setAlignment(HA_CENTER, VA_CENTER);
        openButtonText.setText("Open");
        openButton.addChild(openButtonText);
        bar.addChild(openButton);
        subscribeToEvent(openButton, "Released", "openResource");
    }
    */
}

void LoadAttributeEditor(uint type, XMLElement categoryElem, int index, const String& in attribute)
{
    /*
    inLoadAttributeEditor = true;

    ListView@ list = nodeWindow.GetChild("AttributeList", true);
    String value = categoryElem.GetAttribute(attribute);

    if ((type == ATTR_EDITOR_STRING) || (type >= ATTR_EDITOR_RESOURCE))
    {
        LineEdit@ attrEdit = list.GetChild.GetAttributeEditorName(index, attribute), true);
        if (attrEdit is null)
            return;
        attrEdit.setText(value);
    }

    if (type == ATTR_EDITOR_BOOL)
    {
        CheckBox@ attrEdit = list.GetChild.GetAttributeEditorName(index, attribute), true);
        if (attrEdit is null)
            return;
        attrEdit.setChecked(value.toBool());
    }

    if ((type >= ATTR_EDITOR_FLOAT) && (type <= ATTR_EDITOR_VECTOR4))
    {
        String baseName =.GetAttributeEditorName(index, attribute);
        Array<String> coords = value.split(' ');
        for (uint i = 0; (i < coords.size()) && (i < type); ++i)
        {
            LineEdit@ attrEdit = list.GetChild(baseName + "_" + toString(i), true);
            if (attrEdit !is null)
                attrEdit.setText(coords[i]);
            else
                break;
        }
    }

    if ((type >= ATTR_EDITOR_ENUM) && (type < ATTR_EDITOR_RESOURCE))
    {
        DropDownList@ attrEdit = list.GetChild.GetAttributeEditorName(index, attribute), true);
        if (attrEdit is null)
            return;
        EnumEditorData@ data = enumEditors[type - ATTR_EDITOR_ENUM];
        String value = categoryElem.GetAttribute(attribute);
        for (uint i = 0; i < data.choices.size(); ++i)
        {
            if (value.toLower() == data.choices[i])
            {
                attrEdit.setSelection(i);
                break;
            }
        }
    }

    inLoadAttributeEditor = false;
    */
}

void StoreAttributeEditor(uint type, XMLElement categoryElem, int index, const String& in attribute)
{
    /*
    ListView@ list = nodeWindow.GetChild("AttributeList", true);

    if ((type == ATTR_EDITOR_STRING) || (type >= ATTR_EDITOR_RESOURCE))
    {
        LineEdit@ attrEdit = list.GetChild.GetAttributeEditorName(index, attribute), true);
        categoryElem.setAttribute(attribute, attrEdit.text);
    }

    if (type == ATTR_EDITOR_BOOL)
    {
        CheckBox@ attrEdit = list.GetChild.GetAttributeEditorName(index, attribute), true);
        categoryElem.setAttribute(attribute, toString(attrEdit.isChecked()));
    }

    if ((type >= ATTR_EDITOR_FLOAT) && (type <= ATTR_EDITOR_VECTOR4))
    {
        String baseName =.GetAttributeEditorName(index, attribute);
        String value;
        for (uint i = 0; i < type; ++i)
        {
            LineEdit@ attrEdit = list.GetChild(baseName + "_" + toString(i), true);
            if (attrEdit is null)
                break;
            if (i != 0)
                value += " ";
            value += attrEdit.text;
        }
        categoryElem.setAttribute(attribute, value);
    }
    
    if ((type >= ATTR_EDITOR_ENUM) && (type < ATTR_EDITOR_RESOURCE))
    {
        DropDownList@ attrEdit = list.GetChild.GetAttributeEditorName(index, attribute), true);
        EnumEditorData@ data = enumEditors[type - ATTR_EDITOR_ENUM];
        categoryElem.setAttribute(attribute, data.choices[attrEdit.GetSelection()]);
    }
    */
}
