// Urho3D editor component edit window handling

Window@ componentWindow;

XMLFile componentData;

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
    string componentType;
    string categoryName;
    string attributeName;
    array<string>@ choices;

    EnumEditorData(const string& in componentType_, const string& in categoryName_, const string& in attributeName_, array<string>@ choices_)
    {
        componentType = componentType_;
        categoryName = categoryName_;
        attributeName = attributeName_;
        @choices = choices_;
    }
}

class ResourceEditorData
{
    string componentType;
    string categoryName;
    string attributeName;
    string resourceType;
    string fileExtension;
    string lastPath;

    ResourceEditorData(const string& in componentType_, const string& in categoryName_, const string& in attributeName_, const string& in resourceType_, const string& in fileExtension_)
    {
        componentType = componentType_;
        categoryName = categoryName_;
        attributeName = attributeName_;
        resourceType = resourceType_;
        fileExtension = fileExtension_;
    }
}

array<EnumEditorData@> enumEditors;
array<ResourceEditorData@> resourceEditors;

bool inLoadAttributeEditor = false;
uint lastAttributeCount = 0;

uint resourcePickType = 0;
string resourcePickEditorName;

void createComponentWindow()
{
    if (componentWindow !is null)
        return;

    @componentWindow = ui.loadLayout(cache.getResource("XMLFile", "UI/ComponentWindow.xml"), uiStyle);
    uiRoot.addChild(componentWindow);
    int height = min(uiRoot.getHeight() - 60, 500);
    componentWindow.setSize(300, height);
    componentWindow.setPosition(uiRoot.getWidth() - 20 - componentWindow.getWidth(), 40);
    componentWindow.setVisible(true);
    updateComponentWindow();
    
    // Fill enum & resource editor data
    array<string> lightTypes = {"directional", "spot", "point"};
    array<string> bodyTypes = {"static", "dynamic", "kinematic"};
    enumEditors.push(EnumEditorData("Light", "light", "type", lightTypes));
    enumEditors.push(EnumEditorData("RigidBody", "body", "mode", bodyTypes));

    resourceEditors.push(ResourceEditorData("", "material", "name", "Material", ".xml"));
    resourceEditors.push(ResourceEditorData("", "model", "name", "Model", ".mdl"));
    resourceEditors.push(ResourceEditorData("", "animation", "name", "Animation", ".ani"));
    resourceEditors.push(ResourceEditorData("RigidBody", "collision", "name", "CollisionShape", ".xml"));
    resourceEditors.push(ResourceEditorData("ScriptInstance", "script", "name", "ScriptFile", ".as"));
    resourceEditors.push(ResourceEditorData("ParticleEmitter", "emitter", "name", "XMLFile", ".xml"));

    subscribeToEvent(componentWindow.getChild("CloseButton", true), "Released", "hideComponentWindow");
    subscribeToEvent(componentWindow.getChild("EntityNameEdit", true), "TextFinished", "editEntityName");
    subscribeToEvent(componentWindow.getChild("ComponentNameEdit", true), "TextFinished", "editComponentName");
}

void hideComponentWindow()
{
    componentWindow.setVisible(false);
}

void showComponentWindow()
{
    componentWindow.setVisible(true);
    componentWindow.bringToFront();
}

void updateComponentWindow()
{
    // If a resource pick was in progress, it cannot be completed now, as component was changed
    pickResourceCanceled();

    Text@ entityTitle = componentWindow.getChild("EntityTitle", true);
    Text@ componentTitle = componentWindow.getChild("ComponentTitle", true);
    LineEdit@ entityNameEdit = componentWindow.getChild("EntityNameEdit", true);
    LineEdit@ componentNameEdit = componentWindow.getChild("ComponentNameEdit", true);
    ListView@ list = componentWindow.getChild("AttributeList", true);
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
}

void editEntityName()
{
    if (selectedEntity is null)
        return;

    LineEdit@ nameEdit = componentWindow.getChild("EntityNameEdit", true);
    selectedEntity.setName(nameEdit.getText());
    updateSceneWindowEntity(selectedEntity);
}

void editComponentName()
{
    if (selectedComponent is null)
        return;

    LineEdit@ nameEdit = componentWindow.getChild("ComponentNameEdit", true);
    selectedComponent.setName(nameEdit.getText());
    updateSceneWindowEntity(selectedComponent.getEntity());
}

void updateComponentAttributes()
{
    ListView@ list = componentWindow.getChild("AttributeList", true);

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
            string category = categoryElem.getName();

            Text@ text = Text();
            text.setStyleAuto(uiStyle);
            text.setText(category);
            list.addItem(text);

            {
                UIElement@ spacer = UIElement();
                spacer.setFixedHeight(4);
                list.addItem(spacer);
            }

            array<string> attrs = categoryElem.getAttributeNames();

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
                    string name = attrs[i];
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
            array<string> attrs = categoryElem.getAttributeNames();
        
            for (uint i = 0; i < attrs.size(); ++i)
            {
                string category = categoryElem.getName();
                uint type = getAttributeEditorType(selectedComponent, category, attrs[i], categoryElem.getAttribute(attrs[i]));
                loadAttributeEditor(type, categoryElem, index, attrs[i]);
            }

            categoryElem = categoryElem.getNextElement();
            ++index;
        }
    }
}

void editComponentAttribute(StringHash eventType, VariantMap& eventData)
{
    // Changing elements programmatically may cause events to be sent. Stop possible infinite loop in that case.
    if ((selectedComponent is null) || (inLoadAttributeEditor))
        return;

    UIElement@ attrEdit = eventData["Element"].getUIElement();
    editComponentAttribute(attrEdit, eventType == StringHash("TextChanged"));
}

void editComponentAttribute(UIElement@ attrEdit, bool intermediateEdit)
{
    if ((selectedComponent is null) || (inLoadAttributeEditor))
        return;

    XMLElement rootElem = componentData.getRootElement();
    XMLElement categoryElem = rootElem.getChildElement();
    uint index = 0;
    while (categoryElem.notNull())
    {
        if (index == uint(attrEdit.userData["Index"].getInt()))
        {
            storeAttributeEditor(attrEdit.userData["Type"].getInt(), categoryElem, index, attrEdit.userData["Attribute"].getString());

            uint id = selectedComponent.getEntity().getID();
            beginModify(id);
            selectedComponent.loadXML(rootElem);
            selectedComponent.postLoad();
            endModify(id);

            // If intermediate edit on a numeric field, do not refresh value back from the component to the edit field
            if (!intermediateEdit)
                updateComponentAttributes();
            return;
        }
        categoryElem = categoryElem.getNextElement();
        ++index;
    }
}

void pickResource(StringHash eventType, VariantMap& eventData)
{
    if (uiFileSelector !is null)
        return;

    UIElement@ button = eventData["Element"].getUIElement();
    LineEdit@ attrEdit = button.getParent().getChild(1);
    uint type = uint(attrEdit.userData["Type"].getInt());

    ResourceEditorData@ data = resourceEditors[type - ATTR_EDITOR_RESOURCE];

    array<string> filters;
    filters.push("*" + data.fileExtension);
    string lastPath = data.lastPath;
    if (lastPath.empty())
        lastPath = sceneResourcePath;
    createFileSelector("Pick " + data.resourceType, "OK", "Cancel", lastPath, filters, 0);
    subscribeToEvent(uiFileSelector, "FileSelected", "pickResourceDone");

    resourcePickType = type;
    resourcePickEditorName = attrEdit.getName();
}

void openResource(StringHash eventType, VariantMap& eventData)
{
    UIElement@ button = eventData["Element"].getUIElement();
    LineEdit@ attrEdit = button.getParent().getChild(1);
    systemOpenFile(sceneResourcePath + attrEdit.getText(), "edit");
}

void pickResourceDone(StringHash eventType, VariantMap& eventData)
{
    closeFileSelector();

    if (!eventData["OK"].getBool())
    {
        resourcePickType = 0;
        return;
    }

    // Check if another component was selected in the meanwhile
    if (resourcePickType == 0)
        return;

    ResourceEditorData@ data = resourceEditors[resourcePickType - ATTR_EDITOR_RESOURCE];
    resourcePickType = 0;

    ListView@ list = componentWindow.getChild("AttributeList", true);
    LineEdit@ attrEdit = list.getChild(resourcePickEditorName, true);
    if (attrEdit is null)
        return;

    // Validate the resource. It must come from within the scene resource directory, and be loaded successfully
    string resourceName = eventData["FileName"].getString();
    if (resourceName.find(sceneResourcePath) != 0)
        return;
    data.lastPath = getPath(resourceName);

    resourceName = resourceName.substr(sceneResourcePath.length());

    Resource@ res = cache.getResource(data.resourceType, resourceName);
    if (res is null)
        return;

    attrEdit.setText(resourceName);
    editComponentAttribute(attrEdit, false);
}

void pickResourceCanceled()
{
    if (resourcePickType != 0)
    {
        resourcePickType = 0;
        closeFileSelector();
    }
}

int getAttributeEditorType(Component@ component, const string& in category, const string& in attribute, const string& in value)
{
    for (uint i = 0; i < enumEditors.size(); ++i)
    {
        if ((category == enumEditors[i].categoryName) && (attribute == enumEditors[i].attributeName) && ((enumEditors[i].componentType.empty())
            || (component.getTypeName() == enumEditors[i].componentType)))
            return ATTR_EDITOR_ENUM + i;
    }

    for (uint i = 0; i < resourceEditors.size(); ++i)
    {
        if ((category == resourceEditors[i].categoryName) && (attribute == resourceEditors[i].attributeName) && 
            ((resourceEditors[i].componentType.empty()) || (component.getTypeName() == resourceEditors[i].componentType)))
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
    
    return ATTR_EDITOR_STRING;
}

string getAttributeEditorName(uint index, const string& in attribute)
{
    return "Attr_" + toString(index) + "_" + attribute;
}

void createAttributeEditor(UIElement@ bar, uint type, XMLElement categoryElem, uint index, const string& in attribute)
{
    if (type == ATTR_EDITOR_STRING)
    {
        LineEdit@ attrEdit = LineEdit(getAttributeEditorName(index, attribute));
        attrEdit.setStyle(uiStyle, "EditorAttributeEdit");
        attrEdit.userData["Type"] = type;
        attrEdit.userData["Index"] = index;
        attrEdit.userData["Attribute"] = attribute;
        attrEdit.setFixedHeight(16);
        bar.addChild(attrEdit);
        subscribeToEvent(attrEdit, "TextFinished", "editComponentAttribute");
    }

    if (type == ATTR_EDITOR_BOOL)
    {
        CheckBox@ attrEdit = CheckBox(getAttributeEditorName(index, attribute));
        attrEdit.setStyleAuto(uiStyle);
        attrEdit.userData["Type"] = type;
        attrEdit.userData["Index"] = index;
        attrEdit.userData["Attribute"] = attribute;
        attrEdit.setFixedSize(16, 16);
        bar.addChild(attrEdit);
        subscribeToEvent(attrEdit, "Toggled", "editComponentAttribute");
    }

    if ((type >= ATTR_EDITOR_FLOAT) && (type <= ATTR_EDITOR_VECTOR4))
    {
        for (uint i = 0; i < type; ++i)
        {
            LineEdit@ attrEdit = LineEdit(getAttributeEditorName(index, attribute) + "_" + toString(i));
            attrEdit.setStyle(uiStyle, "EditorAttributeEdit");
            attrEdit.userData["Type"] = type;
            attrEdit.userData["Index"] = index;
            attrEdit.userData["Attribute"] = attribute;
            attrEdit.setFixedHeight(16);
            bar.addChild(attrEdit);
            // For the numeric style editors, subscribe to every change
            subscribeToEvent(attrEdit, "TextChanged", "editComponentAttribute");
            subscribeToEvent(attrEdit, "TextFinished", "editComponentAttribute");
        }
    }
    
    if ((type >= ATTR_EDITOR_ENUM) && (type < ATTR_EDITOR_RESOURCE))
    {
        DropDownList@ attrEdit = DropDownList(getAttributeEditorName(index, attribute));
        attrEdit.setStyleAuto(uiStyle);
        attrEdit.userData["Type"] = type;
        attrEdit.userData["Index"] = index;
        attrEdit.userData["Attribute"] = attribute;
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
        LineEdit@ attrEdit = LineEdit(getAttributeEditorName(index, attribute));
        attrEdit.setStyle(uiStyle, "EditorAttributeEdit");
        attrEdit.userData["Type"] = type;
        attrEdit.userData["Index"] = index;
        attrEdit.userData["Attribute"] = attribute;
        attrEdit.setFixedHeight(16);
        bar.addChild(attrEdit);
        subscribeToEvent(attrEdit, "TextFinished", "editComponentAttribute");

        Button@ pickButton = Button(getAttributeEditorName(index, attribute) + "_Pick");
        pickButton.setStyleAuto(uiStyle);
        pickButton.userData["Type"] = type;
        pickButton.userData["Index"] = index;
        pickButton.userData["Attribute"] = attribute;
        pickButton.setFixedSize(36, 16);
        Text@ pickButtonText = Text();
        pickButtonText.setStyle(uiStyle, "EditorAttributeText");
        pickButtonText.setAlignment(HA_CENTER, VA_CENTER);
        pickButtonText.setText("Pick");
        pickButton.addChild(pickButtonText);
        bar.addChild(pickButton);
        subscribeToEvent(pickButton, "Released", "pickResource");

        Button@ openButton = Button(getAttributeEditorName(index, attribute) + "_Edit");
        openButton.setStyleAuto(uiStyle);
        openButton.userData["Type"] = type;
        openButton.userData["Index"] = index;
        openButton.userData["Attribute"] = attribute;
        openButton.setFixedSize(36, 16);
        Text@ openButtonText = Text();
        openButtonText.setStyle(uiStyle, "EditorAttributeText");
        openButtonText.setAlignment(HA_CENTER, VA_CENTER);
        openButtonText.setText("Open");
        openButton.addChild(openButtonText);
        bar.addChild(openButton);
        subscribeToEvent(openButton, "Released", "openResource");
    }
}

void loadAttributeEditor(uint type, XMLElement categoryElem, int index, const string& in attribute)
{
    inLoadAttributeEditor = true;

    ListView@ list = componentWindow.getChild("AttributeList", true);
    string value = categoryElem.getAttribute(attribute);

    if ((type == ATTR_EDITOR_STRING) || (type >= ATTR_EDITOR_RESOURCE))
    {
        LineEdit@ attrEdit = list.getChild(getAttributeEditorName(index, attribute), true);
        if (attrEdit is null)
            return;
        attrEdit.setText(value);
    }

    if (type == ATTR_EDITOR_BOOL)
    {
        CheckBox@ attrEdit = list.getChild(getAttributeEditorName(index, attribute), true);
        if (attrEdit is null)
            return;
        attrEdit.setChecked(value.toBool());
    }

    if ((type >= ATTR_EDITOR_FLOAT) && (type <= ATTR_EDITOR_VECTOR4))
    {
        string baseName = getAttributeEditorName(index, attribute);
        array<string> coords = value.split(' ');
        for (uint i = 0; (i < coords.size()) && (i < type); ++i)
        {
            LineEdit@ attrEdit = list.getChild(baseName + "_" + toString(i), true);
            if (attrEdit !is null)
                attrEdit.setText(coords[i]);
            else
                break;
        }
    }

    if ((type >= ATTR_EDITOR_ENUM) && (type < ATTR_EDITOR_RESOURCE))
    {
        DropDownList@ attrEdit = list.getChild(getAttributeEditorName(index, attribute), true);
        if (attrEdit is null)
            return;
        EnumEditorData@ data = enumEditors[type - ATTR_EDITOR_ENUM];
        string value = categoryElem.getAttribute(attribute);
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
}

void storeAttributeEditor(uint type, XMLElement categoryElem, int index, const string& in attribute)
{
    ListView@ list = componentWindow.getChild("AttributeList", true);

    if ((type == ATTR_EDITOR_STRING) || (type >= ATTR_EDITOR_RESOURCE))
    {
        LineEdit@ attrEdit = list.getChild(getAttributeEditorName(index, attribute), true);
        categoryElem.setAttribute(attribute, attrEdit.getText());
    }

    if (type == ATTR_EDITOR_BOOL)
    {
        CheckBox@ attrEdit = list.getChild(getAttributeEditorName(index, attribute), true);
        categoryElem.setAttribute(attribute, toString(attrEdit.isChecked()));
    }

    if ((type >= ATTR_EDITOR_FLOAT) && (type <= ATTR_EDITOR_VECTOR4))
    {
        string baseName = getAttributeEditorName(index, attribute);
        string value;
        for (uint i = 0; i < type; ++i)
        {
            LineEdit@ attrEdit = list.getChild(baseName + "_" + toString(i), true);
            if (attrEdit is null)
                break;
            if (i != 0)
                value += " ";
            value += attrEdit.getText();
        }
        categoryElem.setAttribute(attribute, value);
    }
    
    if ((type >= ATTR_EDITOR_ENUM) && (type < ATTR_EDITOR_RESOURCE))
    {
        DropDownList@ attrEdit = list.getChild(getAttributeEditorName(index, attribute), true);
        EnumEditorData@ data = enumEditors[type - ATTR_EDITOR_ENUM];
        categoryElem.setAttribute(attribute, data.choices[attrEdit.getSelection()]);
    }
}
