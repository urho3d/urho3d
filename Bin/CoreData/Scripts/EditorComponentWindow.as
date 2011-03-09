// Urho3D editor component edit window handling

Window@ componentWindow;

XMLFile componentData;

const uint ATTR_EDITOR_STRING = 0;
const uint ATTR_EDITOR_BOOL = 1;
const uint ATTR_EDITOR_VECTOR2 = 2;
const uint ATTR_EDITOR_VECTOR3 = 3;
const uint ATTR_EDITOR_VECTOR4 = 4;
const uint MAX_ATTRNAME_LENGTH = 15;

bool inReadAttributeEditor = false;
uint lastAttributeCount = 0;

void createComponentWindow()
{
    if (componentWindow !is null)
        return;

    @componentWindow = ui.loadLayout(cache.getResource("XMLFile", "UI/ComponentWindow.xml"), uiStyle);
    uiRoot.addChild(componentWindow);
    componentWindow.setPosition(400, 50);
    componentWindow.setSize(350, 400);
    componentWindow.setVisible(false);
    
    subscribeToEvent(componentWindow.getChild("CloseButton", true), "Released", "hideComponentWindow");
    subscribeToEvent(componentWindow.getChild("NameEdit", true), "TextFinished", "editComponentName");
}

void hideComponentWindow()
{
    componentWindow.setVisible(false);
}

void showComponentWindow()
{
    componentWindow.setVisible(true);
}

void updateComponentWindow()
{
    Text@ title = componentWindow.getChild("WindowTitle", true);
    LineEdit@ nameEdit = componentWindow.getChild("NameEdit", true);
    ListView@ list = componentWindow.getChild("AttributeList", true);
    list.removeAllItems();
    lastAttributeCount = 0;

    if ((selectedComponent is null) || (selectedEntity is null))
    {
        title.setText("No component");
        nameEdit.setText("");
        nameEdit.setEnabled(false);
        return;
    }

    title.setText(selectedComponent.getTypeName() + " in " + getEntityTitle(selectedEntity));
    nameEdit.setText(selectedComponent.getName());
    nameEdit.setEnabled(true);
    
    updateComponentAttributes();
    showComponentWindow();
}

void editComponentName()
{
    if ((selectedComponent is null) || (selectedEntity is null))
        return;

    LineEdit@ nameEdit = componentWindow.getChild("NameEdit", true);
    selectedComponent.setName(nameEdit.getText());
    updateSceneWindowEntity(selectedEntity);
}

void updateComponentAttributes()
{
    ListView@ list = componentWindow.getChild("AttributeList", true);

    // Save component to XML, then inspect the result
    XMLElement rootElem = componentData.createRootElement("component");
    selectedComponent.saveXML(rootElem);

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

            for (uint i = 0; i < attrs.size(); ++i)
            {
                string name = attrs[i];
                if (name.length() > MAX_ATTRNAME_LENGTH)
                    name.resize(MAX_ATTRNAME_LENGTH);

                UIElement@ bar = UIElement();
                bar.setLayout(LM_HORIZONTAL, 4, IntRect(0, 0, 0, 0));
                bar.setFixedHeight(18);
                list.addItem(bar);

                Text@ attrName = Text();
                attrName.setStyle(uiStyle, "EditorAttributeText");
                attrName.setText(" " + name);
                attrName.setFixedWidth(120);
                bar.addChild(attrName);

                uint type = getAttributeEditorType(selectedComponent, category, attrs[i], categoryElem.getAttribute(attrs[i]));
                createAttributeEditor(bar, type, categoryElem, index, attrs[i]);
                readAttributeEditor(type, categoryElem, index, attrs[i]);
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
                readAttributeEditor(type, categoryElem, index, attrs[i]);
            }
        
            categoryElem = categoryElem.getNextElement();
            ++index;
        }
    }
}

void editComponentAttribute(StringHash eventType, VariantMap& eventData)
{
    if (selectedComponent is null)
        return;
        
    // Changing elements programmatically may cause events to be sent. Stop possible infinite loop in that case.
    if (inReadAttributeEditor)
        return;

    UIElement@ attrEdit = eventData["Element"].getUIElement();
    XMLElement rootElem = componentData.getRootElement();
    XMLElement categoryElem = rootElem.getChildElement();
    uint index = 0;
    while (categoryElem.notNull())
    {
        if (index == uint(attrEdit.userData["Index"].getInt()))
        {
            writeAttributeEditor(attrEdit.userData["Type"].getInt(), categoryElem, index, attrEdit.userData["Attribute"].getString());
            selectedComponent.loadXML(rootElem);
            selectedComponent.postLoad();
            updateComponentAttributes();
            return;
        }
        categoryElem = categoryElem.getNextElement();
        ++index;
    }
}

int getAttributeEditorType(Component@ component, const string& in category, const string& in attribute, const string& in value)
{
    // Note: we always use valid, ie. just serialized data for this
    if (cast<Node>(component) !is null)
    {
        if (attribute.find("name") >= 0)
            return ATTR_EDITOR_STRING;
        else if ((category == "animation") && (attribute == "startbone"))
            return ATTR_EDITOR_STRING;
        else if (category == "parent")
            return ATTR_EDITOR_STRING; //! \todo Parent node selector needs to be done separately
        else if ((value == "true") || (value == "false"))
            return ATTR_EDITOR_BOOL;

        uint coords = value.split(' ').size();
        if (coords == 2)
            return ATTR_EDITOR_VECTOR2;
        else if (coords == 3)
            return ATTR_EDITOR_VECTOR3;
        else if (coords == 4)
            return ATTR_EDITOR_VECTOR4;
    }

    return ATTR_EDITOR_STRING;
}

string getAttributeEditorName(uint index, const string& in attribute)
{
    return "Attr_" + toString(index) + "_" + attribute;
}

void createAttributeEditor(UIElement@ bar, uint type, XMLElement categoryElem, uint index, const string& in attribute)
{
    switch (type)
    {
    case ATTR_EDITOR_STRING:
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
        break;

    case ATTR_EDITOR_BOOL:
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
        break;

    case ATTR_EDITOR_VECTOR2:
    case ATTR_EDITOR_VECTOR3:
    case ATTR_EDITOR_VECTOR4:
        for (uint i = 0; i < type; ++i)
        {
            LineEdit@ attrEdit = LineEdit(getAttributeEditorName(index, attribute) + "_" + toString(i));
            attrEdit.setStyle(uiStyle, "EditorAttributeEdit");
            attrEdit.userData["Type"] = type;
            attrEdit.userData["Index"] = index;
            attrEdit.userData["Attribute"] = attribute;
            attrEdit.setFixedHeight(16);
            bar.addChild(attrEdit);
            subscribeToEvent(attrEdit, "TextFinished", "editComponentAttribute");
        }
        break;
    }
}

void readAttributeEditor(uint type, XMLElement categoryElem, int index, const string& in attribute)
{
    inReadAttributeEditor = true;

    ListView@ list = componentWindow.getChild("AttributeList", true);
    
    switch (type)
    {
    case ATTR_EDITOR_STRING:
        {
            LineEdit@ attrEdit = list.getChild(getAttributeEditorName(index, attribute), true);
            attrEdit.setText(categoryElem.getAttribute(attribute));
        }
        break;

    case ATTR_EDITOR_BOOL:
        {
            CheckBox@ attrEdit = list.getChild(getAttributeEditorName(index, attribute), true);
            attrEdit.setChecked(categoryElem.getAttribute(attribute).toBool());
        }
        break;

    case ATTR_EDITOR_VECTOR2:
    case ATTR_EDITOR_VECTOR3:
    case ATTR_EDITOR_VECTOR4:
        {
            string baseName = getAttributeEditorName(index, attribute);
            array<string> coords = categoryElem.getAttribute(attribute).split(' ');
            for (uint i = 0; (i < coords.size()) && (i < type); ++i)
            {
                LineEdit@ attrEdit = list.getChild(baseName + "_" + toString(i), true);
                if (attrEdit !is null)
                    attrEdit.setText(coords[i]);
                else
                    break;
            }
        }
        break;
    }
    
    inReadAttributeEditor = false;
}

void writeAttributeEditor(uint type, XMLElement categoryElem, int index, const string& in attribute)
{
    ListView@ list = componentWindow.getChild("AttributeList", true);
    
    switch (type)
    {
    case ATTR_EDITOR_STRING:
        {
            LineEdit@ attrEdit = list.getChild(getAttributeEditorName(index, attribute), true);
            categoryElem.setAttribute(attribute, attrEdit.getText());
        }
        break;

    case ATTR_EDITOR_BOOL:
        {
            CheckBox@ attrEdit = list.getChild(getAttributeEditorName(index, attribute), true);
            categoryElem.setAttribute(attribute, toString(attrEdit.isChecked()));
        }
        break;

    case ATTR_EDITOR_VECTOR2:
    case ATTR_EDITOR_VECTOR3:
    case ATTR_EDITOR_VECTOR4:
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
        break;
    }
}
