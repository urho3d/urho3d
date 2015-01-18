// Urho3D editor UI-element handling

UIElement@ editorUIElement;
XMLFile@ uiElementDefaultStyle;
Array<String> availableStyles;

UIElement@ editUIElement;
Array<Serializable@> selectedUIElements;
Array<Serializable@> editUIElements;

Array<XMLFile@> uiElementCopyBuffer;

bool suppressUIElementChanges = false;

const StringHash FILENAME_VAR("FileName");
const StringHash MODIFIED_VAR("Modified");
const StringHash CHILD_ELEMENT_FILENAME_VAR("ChildElemFileName");

void ClearUIElementSelection()
{
    editUIElement = null;
    selectedUIElements.Clear();
    editUIElements.Clear();
}

void CreateRootUIElement()
{
    // Create a root UIElement only once here, do not confuse this with ui.root itself
    editorUIElement = ui.root.CreateChild("UIElement");
    editorUIElement.name = "UI";
    editorUIElement.SetSize(graphics.width, graphics.height);
    editorUIElement.traversalMode = TM_DEPTH_FIRST;     // This is needed for root-like element to prevent artifacts
    editorUIElement.priority = -1000;   // All user-created UI elements have lowest priority so they do not cover editor's windows

    // This is needed to distinguish our own element events from Editor's UI element events
    editorUIElement.elementEventSender = true;
    SubscribeToEvent(editorUIElement, "ElementAdded", "HandleUIElementAdded");
    SubscribeToEvent(editorUIElement, "ElementRemoved", "HandleUIElementRemoved");

    // Since this root UIElement is not being handled by above handlers, update it into hierarchy list manually as another list root item
    UpdateHierarchyItem(M_MAX_UNSIGNED, editorUIElement, null);
}

bool NewUIElement(const String&in typeName)
{
    // If no edit element then parented to root
    UIElement@ parent = editUIElement !is null ? editUIElement : editorUIElement;
    UIElement@ element = parent.CreateChild(typeName);
    if (element !is null)
    {
        // Use the predefined UI style if set, otherwise use editor's own UI style
        XMLFile@ defaultStyle = uiElementDefaultStyle !is null ? uiElementDefaultStyle : uiStyle;

        if (editUIElement is null)
        {
            // If parented to root, set the internal variables
            element.vars[FILENAME_VAR] = "";
            element.vars[MODIFIED_VAR] = false;
            // set a default UI style
            element.defaultStyle = defaultStyle;
            // and position the newly created element at center
            CenterDialog(element);
        }
        // Apply the auto style
        element.style = AUTO_STYLE;
        // Do not allow UI subsystem to reorder children while editing the element in the editor
        element.sortChildren = false;

        // Create an undo action for the create
        CreateUIElementAction action;
        action.Define(element);
        SaveEditAction(action);
        SetUIElementModified(element);

        FocusUIElement(element);
    }
    return true;
}

void ResetSortChildren(UIElement@ element)
{
    element.sortChildren = false;

    // Perform the action recursively for child elements
    for (uint i = 0; i < element.numChildren; ++i)
        ResetSortChildren(element.children[i]);
}

void OpenUILayout(const String&in fileName)
{
    if (fileName.empty)
        return;

    ui.cursor.shape = CS_BUSY;

    // Check if the UI element has been opened before
    if (editorUIElement.GetChild(FILENAME_VAR, Variant(fileName)) !is null)
    {
        MessageBox("UI element is already opened.\n" + fileName);
        return;
    }

    // Always load from the filesystem, not from resource paths
    if (!fileSystem.FileExists(fileName))
    {
        MessageBox("No such file.\n" + fileName);
        return;
    }

    File file(fileName, FILE_READ);
    if (!file.open)
    {
        MessageBox("Could not open file.\n" + fileName);
        return;
    }

    // Add the UI layout's resource path in case it's necessary
    SetResourcePath(GetPath(fileName), true, true);

    XMLFile@ xmlFile = XMLFile();
    xmlFile.Load(file);

    suppressUIElementChanges = true;

    // If uiElementDefaultStyle is not set then automatically fallback to use the editor's own default style
    UIElement@ element = ui.LoadLayout(xmlFile, uiElementDefaultStyle);
    if (element !is null)
    {
        element.vars[FILENAME_VAR] = fileName;
        element.vars[MODIFIED_VAR] = false;

        // Do not allow UI subsystem to reorder children while editing the element in the editor
        ResetSortChildren(element);
        // Register variable names from the 'enriched' XMLElement, if any
        RegisterUIElementVar(xmlFile.root);

        editorUIElement.AddChild(element);

        UpdateHierarchyItem(element);
        FocusUIElement(element);

        ClearEditActions();
    }
    else
        MessageBox("Could not load UI layout successfully!\nSee Urho3D.log for more detail.");

    suppressUIElementChanges = false;
}

bool CloseUILayout()
{
    ui.cursor.shape = CS_BUSY;

    if (messageBoxCallback is null)
    {
        for (uint i = 0; i < selectedUIElements.length; ++i)
        {
            UIElement@ element = GetTopLevelUIElement(selectedUIElements[i]);
            if (element !is null && element.vars[MODIFIED_VAR].GetBool())
            {
                MessageBox@ messageBox = MessageBox("UI layout has been modified.\nContinue to close?", "Warning");
                if (messageBox.window !is null)
                {
                    Button@ cancelButton = messageBox.window.GetChild("CancelButton", true);
                    cancelButton.visible = true;
                    cancelButton.focus = true;
                    SubscribeToEvent(messageBox, "MessageACK", "HandleMessageAcknowledgement");
                    messageBoxCallback = @CloseUILayout;
                    return false;
                }
            }
        }
    }
    else
        messageBoxCallback = null;

    suppressUIElementChanges = true;

    for (uint i = 0; i < selectedUIElements.length; ++i)
    {
        UIElement@ element = GetTopLevelUIElement(selectedUIElements[i]);
        if (element !is null)
        {
            element.Remove();
            UpdateHierarchyItem(GetListIndex(element), null, null);
        }
    }
    hierarchyList.ClearSelection();
    ClearEditActions();

    suppressUIElementChanges = false;

    return true;
}

bool CloseAllUILayouts()
{
    ui.cursor.shape = CS_BUSY;

    if (messageBoxCallback is null)
    {
        for (uint i = 0; i < editorUIElement.numChildren; ++i)
        {
            UIElement@ element = editorUIElement.children[i];
            if (element !is null && element.vars[MODIFIED_VAR].GetBool())
            {
                MessageBox@ messageBox = MessageBox("UI layout has been modified.\nContinue to close?", "Warning");
                if (messageBox.window !is null)
                {
                    Button@ cancelButton = messageBox.window.GetChild("CancelButton", true);
                    cancelButton.visible = true;
                    cancelButton.focus = true;
                    SubscribeToEvent(messageBox, "MessageACK", "HandleMessageAcknowledgement");
                    messageBoxCallback = @CloseAllUILayouts;
                    return false;
                }
            }
        }
    }
    else
        messageBoxCallback = null;

    suppressUIElementChanges = true;

    editorUIElement.RemoveAllChildren();
    UpdateHierarchyItem(editorUIElement, true);

    // Reset element ID number generator
    uiElementNextID = UI_ELEMENT_BASE_ID + 1;

    hierarchyList.ClearSelection();
    ClearEditActions();

    suppressUIElementChanges = false;

    return true;
}

bool SaveUILayout(const String&in fileName)
{
    if (fileName.empty)
        return false;

    ui.cursor.shape = CS_BUSY;

    MakeBackup(fileName);
    File file(fileName, FILE_WRITE);
    if (!file.open)
    {
        MessageBox("Could not open file.\n" + fileName);
        return false;
    }

    UIElement@ element = GetTopLevelUIElement(editUIElement);
    if (element is null)
        return false;

    XMLFile@ elementData = XMLFile();
    XMLElement rootElem = elementData.CreateRoot("element");
    bool success = element.SaveXML(rootElem);
    RemoveBackup(success, fileName);

    if (success)
    {
        FilterInternalVars(rootElem);
        success = elementData.Save(file);
        if (success)
        {
            element.vars[FILENAME_VAR] = fileName;
            SetUIElementModified(element, false);
        }
    }
    if (!success)
        MessageBox("Could not save UI layout successfully!\nSee Urho3D.log for more detail.");

    return success;
}

bool SaveUILayoutWithExistingName()
{
    ui.cursor.shape = CS_BUSY;

    UIElement@ element = GetTopLevelUIElement(editUIElement);
    if (element is null)
        return false;

    String fileName = element.GetVar(FILENAME_VAR).GetString();
    if (fileName.empty)
        return PickFile();  // No name yet, so pick one
    else
        return SaveUILayout(fileName);
}

void LoadChildUIElement(const String&in fileName)
{
    if (fileName.empty)
        return;

    ui.cursor.shape = CS_BUSY;

    if (!fileSystem.FileExists(fileName))
    {
        MessageBox("No such file.\n" + fileName);
        return;
    }

    File file(fileName, FILE_READ);
    if (!file.open)
    {
        MessageBox("Could not open file.\n" + fileName);
        return;
    }

    XMLFile@ xmlFile = XMLFile();
    xmlFile.Load(file);

    suppressUIElementChanges = true;

    if (editUIElement.LoadChildXML(xmlFile, uiElementDefaultStyle !is null ? uiElementDefaultStyle : uiStyle))
    {
        XMLElement rootElem = xmlFile.root;
        uint index = rootElem.HasAttribute("index") ? rootElem.GetUInt("index") : editUIElement.numChildren - 1;
        UIElement@ element = editUIElement.children[index];
        ResetSortChildren(element);
        RegisterUIElementVar(xmlFile.root);
        element.vars[CHILD_ELEMENT_FILENAME_VAR] = fileName;
        if (index == editUIElement.numChildren - 1)
            UpdateHierarchyItem(element);
        else
            // If not last child, find the list index of the next sibling as the insertion index
            UpdateHierarchyItem(GetListIndex(editUIElement.children[index + 1]), element, hierarchyList.items[GetListIndex(editUIElement)]);
        SetUIElementModified(element);

        // Create an undo action for the load
        CreateUIElementAction action;
        action.Define(element);
        SaveEditAction(action);

        FocusUIElement(element);
    }

    suppressUIElementChanges = false;
}

bool SaveChildUIElement(const String&in fileName)
{
    if (fileName.empty)
        return false;

    ui.cursor.shape = CS_BUSY;

    MakeBackup(fileName);
    File file(fileName, FILE_WRITE);
    if (!file.open)
    {
        MessageBox("Could not open file.\n" + fileName);
        return false;
    }

    XMLFile@ elementData = XMLFile();
    XMLElement rootElem = elementData.CreateRoot("element");
    bool success = editUIElement.SaveXML(rootElem);
    RemoveBackup(success, fileName);
    
    if (success)
    {
        FilterInternalVars(rootElem);
        success = elementData.Save(file);
        if (success)
            editUIElement.vars[CHILD_ELEMENT_FILENAME_VAR] = fileName;
    }
    if (!success)
        MessageBox("Could not save child UI element successfully!\nSee Urho3D.log for more detail.");

    return success;
}

void SetUIElementDefaultStyle(const String&in fileName)
{
    if (fileName.empty)
        return;

    ui.cursor.shape = CS_BUSY;

    // Always load from the filesystem, not from resource paths
    if (!fileSystem.FileExists(fileName))
    {
        MessageBox("No such file.\n" + fileName);
        return;
    }

    File file(fileName, FILE_READ);
    if (!file.open)
    {
        MessageBox("Could not open file.\n" + fileName);
        return;
    }

    uiElementDefaultStyle = XMLFile();
    uiElementDefaultStyle.Load(file);

    // Remove the existing style list to ensure it gets repopulated again with the new default style file
    availableStyles.Clear();

    // Refresh Attribute Inspector when it is currently showing attributes of UI-element item type as the existing styles in the style drop down list are not valid anymore
    if (!editUIElements.empty)
        attributesFullDirty = true;
}

// Prepare XPath query object only once and use it multiple times
XPathQuery filterInternalVarsQuery("//attribute[@name='Variables']/variant");

void FilterInternalVars(XMLElement source)
{
    XPathResultSet resultSet = filterInternalVarsQuery.Evaluate(source);
    XMLElement resultElem = resultSet.firstResult;
    while (resultElem.notNull)
    {
        String name = GetVarName(resultElem.GetUInt("hash"));
        if (name.empty)
        {
            XMLElement parent = resultElem.parent;

            // If variable name is empty (or unregistered) then it is an internal variable and should be removed
            if (parent.RemoveChild(resultElem))
            {
                // If parent does not have any children anymore then remove the parent also
                if (!parent.HasChild("variant"))
                    parent.parent.RemoveChild(parent);
            }
        }
        else
            // If it is registered then it is a user-defined variable, so 'enrich' the XMLElement to store the variable name in plaintext
            resultElem.SetAttribute("name", name);
        resultElem = resultElem.nextResult;
    }
}

XPathQuery registerUIElemenVarsQuery("//attribute[@name='Variables']/variant/@name");

void RegisterUIElementVar(XMLElement source)
{
    XPathResultSet resultSet = registerUIElemenVarsQuery.Evaluate(source);
    XMLElement resultAttr = resultSet.firstResult;  // Since we are selecting attribute, the resultset is in attribute context
    while (resultAttr.notNull)
    {
        String name = resultAttr.GetAttribute();
        globalVarNames[name] = name;
        resultAttr = resultAttr.nextResult;
    }
}

UIElement@ GetTopLevelUIElement(UIElement@ element)
{
    // Only top level UI-element contains the FILENAME_VAR
    while (element !is null && !element.vars.Contains(FILENAME_VAR))
        element = element.parent;
    return element;
}

void SetUIElementModified(UIElement@ element, bool flag = true)
{
    element = GetTopLevelUIElement(element);
    if (element !is null && element.GetVar(MODIFIED_VAR).GetBool() != flag)
    {
        element.vars[MODIFIED_VAR] = flag;
        UpdateHierarchyItemText(GetListIndex(element), element.visible, GetUIElementTitle(element));
    }
}

XPathQuery availableStylesXPathQuery("/elements/element[@auto='false']/@type");

void GetAvailableStyles()
{
    // Use the predefined UI style if set, otherwise use editor's own UI style
    XMLFile@ defaultStyle = uiElementDefaultStyle !is null ? uiElementDefaultStyle : uiStyle;
    XMLElement rootElem = defaultStyle.root;
    XPathResultSet resultSet = availableStylesXPathQuery.Evaluate(rootElem);
    XMLElement resultElem = resultSet.firstResult;
    while (resultElem.notNull)
    {
        availableStyles.Push(resultElem.GetAttribute());
        resultElem = resultElem.nextResult;
    }

    availableStyles.Sort();
}

void PopulateStyleList(DropDownList@ styleList)
{
    if (availableStyles.empty)
        GetAvailableStyles();

    for (uint i = 0; i < availableStyles.length; ++i)
    {
        Text@ choice = Text();
        styleList.AddItem(choice);
        choice.style = "EditorEnumAttributeText";
        choice.text = availableStyles[i];
    }
}

bool UIElementCut()
{
    return UIElementCopy() && UIElementDelete();
}

bool UIElementCopy()
{
    ui.cursor.shape = CS_BUSY;

    uiElementCopyBuffer.Clear();

    for (uint i = 0; i < selectedUIElements.length; ++i)
    {
        XMLFile@ xml = XMLFile();
        XMLElement rootElem = xml.CreateRoot("element");
        selectedUIElements[i].SaveXML(rootElem);
        uiElementCopyBuffer.Push(xml);
    }

    return true;
}

void ResetDuplicateID(UIElement@ element)
{
    // If it is a duplicate copy then the element ID need to be regenerated by resetting it now to empty
    if (GetListIndex(element) != NO_ITEM)
        element.vars[UI_ELEMENT_ID_VAR] = Variant();

    // Perform the action recursively for child elements
    for (uint i = 0; i < element.numChildren; ++i)
        ResetDuplicateID(element.children[i]);
}

bool UIElementPaste(bool duplication = false)
{
    ui.cursor.shape = CS_BUSY;

    // Group for storing undo actions
    EditActionGroup group;

    // Have to update manually because the element ID var is not set yet when the E_ELEMENTADDED event is sent
    suppressUIElementChanges = true;

    for (uint i = 0; i < uiElementCopyBuffer.length; ++i)
    {
        XMLElement rootElem = uiElementCopyBuffer[i].root;

        UIElement@ pasteElement;

        if (!duplication)
            pasteElement = editUIElement;
        else
        {
            if (editUIElement.parent !is null)
                pasteElement = editUIElement.parent;
            else
                pasteElement = editUIElement;
        }

        if (pasteElement.LoadChildXML(rootElem, null))
        {
            UIElement@ element = pasteElement.children[pasteElement.numChildren - 1];

            ResetDuplicateID(element);
            UpdateHierarchyItem(element);
            SetUIElementModified(pasteElement);

            // Create an undo action
            CreateUIElementAction action;
            action.Define(element);
            group.actions.Push(action);
        }
    }

    SaveEditActionGroup(group);

    suppressUIElementChanges = false;

    return true;
}

bool UIElementDuplicate()
{
    ui.cursor.shape = CS_BUSY;

    Array<XMLFile@> copy = uiElementCopyBuffer;
    UIElementCopy();
    UIElementPaste(true);
    uiElementCopyBuffer = copy;

    return true;
}

bool UIElementDelete()
{
    ui.cursor.shape = CS_BUSY;

    BeginSelectionModify();

    // Clear the selection now to prevent deleted elements from being reselected
    hierarchyList.ClearSelection();

    // Group for storing undo actions
    EditActionGroup group;

    for (uint i = 0; i < selectedUIElements.length; ++i)
    {
        UIElement@ element = selectedUIElements[i];
        if (element.parent is null)
            continue; // Already deleted

        uint index = GetListIndex(element);

        // Create undo action
        DeleteUIElementAction action;
        action.Define(element);
        group.actions.Push(action);

        SetUIElementModified(element);
        element.Remove();

        // If deleting only one element, select the next item in the same index
        if (selectedUIElements.length == 1)
            hierarchyList.selection = index;
    }

    SaveEditActionGroup(group);

    EndSelectionModify();
    return true;
}

bool UIElementSelectAll()
{
    BeginSelectionModify();
    Array<uint> indices;
    uint baseIndex = GetListIndex(editorUIElement);
    indices.Push(baseIndex);
    int baseIndent = hierarchyList.items[baseIndex].indent;
    for (uint i = baseIndex + 1; i < hierarchyList.numItems; ++i)
    {
        if (hierarchyList.items[i].indent <= baseIndent)
            break;
        indices.Push(i);
    }
    hierarchyList.SetSelections(indices);
    EndSelectionModify();

    return true;
}

bool UIElementResetToDefault()
{
    ui.cursor.shape = CS_BUSY;

    // Group for storing undo actions
    EditActionGroup group;

    // Reset selected elements to their default values
    for (uint i = 0; i < selectedUIElements.length; ++i)
    {
        UIElement@ element = selectedUIElements[i];

        ResetAttributesAction action;
        action.Define(element);
        group.actions.Push(action);

        element.ResetToDefault();
        action.SetInternalVars(element);
        element.ApplyAttributes();
        for (uint j = 0; j < element.numAttributes; ++j)
            PostEditAttribute(element, j);
        SetUIElementModified(element);
    }

    SaveEditActionGroup(group);
    attributesFullDirty = true;

    return true;
}

bool UIElementChangeParent(UIElement@ sourceElement, UIElement@ targetElement)
{
    ReparentUIElementAction action;
    action.Define(sourceElement, targetElement);
    SaveEditAction(action);

    sourceElement.parent = targetElement;
    SetUIElementModified(targetElement);
    return sourceElement.parent is targetElement;
}
