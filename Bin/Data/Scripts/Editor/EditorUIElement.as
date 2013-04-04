// Urho3D editor UI-element handling

UIElement@ editorUIElement;
XMLFile@ uiElementDefaultStyle;

String childElementFileName;

UIElement@ editUIElement;
Array<Serializable@> selectedUIElements;
Array<Serializable@> editUIElements;

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

    // Since this root UIElement is not being handled by above handlers, update it into hierarchy list manually
    UpdateHierarchyItem(editorUIElement);
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
        }
        element.style = uiElementDefaultStyle !is null ? uiElementDefaultStyle : uiStyle;

        // Create an undo action for the create
        CreateUIElementAction action;
        action.Define(element);
        SaveEditAction(action);

        FocusUIElement(element);
    }
    return true;
}

void OpenUIElement(const String&in fileName)
{
    if (fileName.empty)
        return;

    ui.cursor.shape = CS_BUSY;

    // Check if the UI element has been opened before
    for (uint i = 0; i < editorUIElement.numChildren; ++i)
    {
        if (editorUIElement.children[i].vars[FILENAME_VAR] == fileName)
        {
            log.Warning("UI element is already opened: " + fileName);
            return;
        }
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

        // \todo: should not always centered
        CenterDialog(element);
        editorUIElement.AddChild(element);
        UpdateHierarchyItem(element);
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
    uiElementNextID = 2;

    hierarchyList.ClearSelection();
    ClearEditActions();

    suppressUIElementChanges = false;

    return true;
}

bool SaveUIElement(const String&in fileName)
{
    // TODO
    return true;
}

bool SaveUIElementWithExistingName()
{
    if (editUIElement is null || editUIElement.vars[FILENAME_VAR].GetString().empty)
        return PickFile();
    else
        return SaveUIElement(editUIElement.vars[FILENAME_VAR].GetString());
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
        UpdateHierarchyItem(element);
        
        // Create an undo action for the load
        CreateUIElementAction action;
        action.Define(element);
        SaveEditAction(action);
        
        FocusUIElement(element);
    }

    suppressUIElementChanges = false;
}

void SaveChildUIElement(const String&in fileName)
{
    // TODO
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
