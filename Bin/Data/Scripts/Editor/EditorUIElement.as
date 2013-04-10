// Urho3D editor UI-element handling

UIElement@ editorUIElement;
XMLFile@ uiElementDefaultStyle;

String childElementFileName;

UIElement@ editUIElement;
Array<Serializable@> selectedUIElements;
Array<Serializable@> editUIElements;

Array<XMLFile@> uiElementCopyBuffer;

bool suppressUIElementChanges = false;

const ShortStringHash FILENAME_VAR("__FileName");
const ShortStringHash MODIFIED_VAR("__Modified");

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
        if (editUIElement is null)
        {
            // If parented to root, set the internal variables
            element.vars[FILENAME_VAR] = "";
            element.vars[MODIFIED_VAR] = false;
            // and position the newly created element at center
            CenterDialog(element);
        }
        // Use the predefined UI style if set, otherwise use editor's own UI style
        element.style = uiElementDefaultStyle !is null ? uiElementDefaultStyle : uiStyle;
        // Do not allow UI subsystem to reorder children while editing the element in the editor
        element.sortChildren = false;

        // Create an undo action for the create
        CreateUIElementAction action;
        action.Define(element);
        SaveEditAction(action);

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

void OpenUIElement(const String&in fileName)
{
    if (fileName.empty)
        return;

    ui.cursor.shape = CS_BUSY;

    // Check if the UI element has been opened before
    if (editorUIElement.GetChild(FILENAME_VAR, Variant(fileName)) !is null)
    {
        log.Warning("UI element is already opened: " + fileName);
        return;
    }

    // Always load from the filesystem, not from resource paths
    if (!fileSystem.FileExists(fileName))
    {
        log.Error("No such file: " + fileName);
        return;
    }

    File file(fileName, FILE_READ);
    if (!file.open)
        return;

    // Add the new resource path
    SetResourcePath(GetPath(fileName));

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

        editorUIElement.AddChild(element);

        UpdateHierarchyItem(element);
        FocusUIElement(element);

        ClearEditActions();
    }

    suppressUIElementChanges = false;
}

bool CloseUIElement()
{
    ui.cursor.shape = CS_BUSY;

    suppressUIElementChanges = true;

    for (uint i = 0; i < selectedUIElements.length; ++i)
    {
        UIElement@ element = selectedUIElements[i];
        while (element !is null && !element.vars.Contains(FILENAME_VAR))
            element = element.parent;
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

bool CloseAllUIElements()
{
    ui.cursor.shape = CS_BUSY;

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

bool SaveUIElement(const String&in fileName)
{
    if (fileName.empty)
        return false;

    ui.cursor.shape = CS_BUSY;

    File file(fileName, FILE_WRITE);
    if (!file.open)
        return false;

    XMLFile@ elementData = XMLFile();
    XMLElement rootElem = elementData.CreateRoot("element");
    bool success = editUIElement.SaveXML(rootElem);
    if (success)
    {
        FilterInternalVars(rootElem);
        success = elementData.Save(file);
    }
    if (success)
    {
        editUIElement.vars[FILENAME_VAR] = fileName;
        editUIElement.vars[MODIFIED_VAR] = false;

        sceneModified = false;
        UpdateWindowTitle();
    }

    return success;
}

bool SaveUIElementWithExistingName()
{
    if (editUIElement is null)
        return false;

    Variant fileNameVar = editUIElement.GetVar(FILENAME_VAR);
    if (fileNameVar.empty)  // Only top level UI-element has this variable
        return false;

    if (fileNameVar.GetString().empty)
        return PickFile();  // No name yet, so pick one
    else
        return SaveUIElement(fileNameVar.GetString());
}

void LoadChildUIElement(const String&in fileName)
{
    if (fileName.empty)
        return;

    ui.cursor.shape = CS_BUSY;

    if (!fileSystem.FileExists(fileName))
    {
        log.Error("No such file: " + fileName);
        return;
    }

    File file(fileName, FILE_READ);
    if (!file.open)
        return;

    XMLFile@ xmlFile = XMLFile();
    xmlFile.Load(file);

    suppressUIElementChanges = true;

    if (editUIElement.LoadXML(xmlFile, uiElementDefaultStyle !is null ? uiElementDefaultStyle : uiStyle))
    {
        UIElement@ element = editUIElement.children[editUIElement.numChildren - 1];
        ResetSortChildren(element);
        UpdateHierarchyItem(element);

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

    File file(fileName, FILE_WRITE);
    if (!file.open)
        return false;

    XMLFile@ elementData = XMLFile();
    XMLElement rootElem = elementData.CreateRoot("element");
    // Need another nested element tag otherwise the LoadXML() does not work as expected
    XMLElement childElem = rootElem.CreateChild("element");
    bool success = editUIElement.SaveXML(childElem);
    if (success)
    {
        FilterInternalVars(childElem);
        success = elementData.Save(file);
    }

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
        log.Error("No such file: " + fileName);
        return;
    }

    File file(fileName, FILE_READ);
    if (!file.open)
        return;

    uiElementDefaultStyle = XMLFile();
    uiElementDefaultStyle.Load(file);
}

void FilterInternalVars(XMLElement source)
{
    // Remove unregistered var for each 'attribute' tag
    XMLElement childElem = source.GetChild("attribute");
    while (childElem.notNull)
    {
        if (childElem.GetAttribute("name") == "Variables")
        {
            XMLElement variantElem = childElem.GetChild("variant");
            while (variantElem.notNull)
            {
                // If variable name is empty (unregistered) then it is an internal variable
                bool removed = scene.GetVarName(variantElem.GetUInt("hash")).empty && childElem.RemoveChild(variantElem);
                variantElem = removed ? childElem.GetChild("variant") : childElem.GetNext("variant");
            }
        }
        childElem = childElem.GetNext("attribute");
    }

    // Perform the action recursively for each 'element' tag
    childElem = source.GetChild("element");
    while (childElem.notNull)
    {
        FilterInternalVars(childElem);
        childElem = childElem.GetNext("element");
    }
}

bool UIElementCut()
{
    if (UIElementCopy())
        return UIElementDelete();
    else
        return false;
}

bool UIElementCopy()
{
    ui.cursor.shape = CS_BUSY;

    uiElementCopyBuffer.Clear();

    for (uint i = 0; i < selectedUIElements.length; ++i)
    {
        XMLFile@ xml = XMLFile();
        XMLElement rootElem = xml.CreateRoot("element");
        XMLElement childElem = rootElem.CreateChild("element");
        selectedUIElements[i].SaveXML(childElem);
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

bool UIElementPaste()
{
    ui.cursor.shape = CS_BUSY;

    // Group for storing undo actions
    EditActionGroup group;

    // Have to update manually because the element ID var is not set yet when the E_ELEMENTADDED event is sent
    suppressUIElementChanges = true;

    for (uint i = 0; i < uiElementCopyBuffer.length; ++i)
    {
        XMLElement rootElem = uiElementCopyBuffer[i].root;
        if (editUIElement.LoadXML(rootElem))
        {
            UIElement@ element = editUIElement.children[editUIElement.numChildren - 1];
            ResetDuplicateID(element);
            UpdateHierarchyItem(element);

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

bool UIElementDelete()
{
    BeginSelectionModify();

    // Clear the selection now to prevent repopulation of selectedNodes and selectedComponents combo
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

        element.Remove();
        SetSceneModified();

        // If deleting only one node, select the next item in the same index
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
