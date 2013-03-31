// Urho3D editor UI-element handling

UIElement@ editorUIElement;
XMLFile@ uiElementDefaultStyle;

String childElementFileName;

UIElement@ editUIElement;
Array<UIElement@> selectedUIElements;
Array<UIElement@> editUIElements;

bool suppressUIElementChanges = false;

const String FILENAME_VAR("__fileName");
const String MODIFIED_VAR("__modified");

void ClearUIElementSelection()
{
    editUIElement = null;
    selectedUIElements.Clear();
    editUIElements.Clear();
}

void CreateUIElement()
{
    // Create a root UIElement only once here, do not confuse this with ui.root itself
    editorUIElement = ui.root.CreateChild("UIElement");
    editorUIElement.name = "UI";
    editorUIElement.SetSize(graphics.width, graphics.height);
    editorUIElement.traversalMode = TM_DEPTH_FIRST;
    
    UpdateHierarchyWindowItem(editorUIElement);
}

void NewUIElement()
{
    // TODO
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

    // If uiElementDefaultStyle is not set then use the editor's own default style
    UIElement@ element = ui.LoadLayout(xmlFile, uiElementDefaultStyle);
    if (element !is null)
    {
        element.vars[FILENAME_VAR] = fileName;
        element.vars[MODIFIED_VAR] = false;
        CenterDialog(element);
        editorUIElement.AddChild(element);
    }
    
    UpdateHierarchyWindowItem(element, true);
    UpdateNodeWindow();

    suppressSceneChanges = false;
}

void CloseUIElement(bool all = false)
{
    suppressUIElementChanges = true;

    if (all)
        editorUIElement.RemoveAllChildren();
    else
    {
        for (uint i = 0; i < selectedUIElements.length; ++i)
        {
            UIElement@ element = selectedUIElements[i];
            while (!element.vars.Contains("FILENAME_VAR"))
                element = element.parent;
            element.Remove();
        }
    }
    
    UpdateHierarchyWindowItem(editorUIElement, true);
    UpdateNodeWindow();
    
    suppressUIElementChanges = false;
}

void SaveUIElement(const String&in fileName)
{
    // TODO
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
