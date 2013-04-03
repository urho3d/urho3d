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
    editorUIElement.traversalMode = TM_DEPTH_FIRST;     // This is needed for root element to prevent artifacts

    UpdateHierarchyItem(editorUIElement);
}

bool NewUIElement()
{
    // TODO
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
    }

    UpdateHierarchyItem(element, true);

    suppressUIElementChanges = false;
}

bool CloseUIElement()
{
    suppressUIElementChanges = true;

    for (uint i = 0; i < selectedUIElements.length; ++i)
    {
        UIElement@ element = selectedUIElements[i];
        while (!element.vars.Contains(FILENAME_VAR))
            element = element.parent;
        element.Remove();
    }
    UpdateHierarchyItem(editorUIElement, true);

    suppressUIElementChanges = false;

    return true;
}

bool CloseAllUIElements()
{
    suppressUIElementChanges = true;

    editorUIElement.RemoveAllChildren();
    UpdateHierarchyItem(editorUIElement, true);

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
    // TODO
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
