// Urho3D editor user interface

XMLFile@ uiStyle;
XMLFile@ iconStyle;
UIElement@ uiMenuBar;
FileSelector@ uiFileSelector;

const ShortStringHash windowType("Window");

Array<String> uiSceneFilters = {"*.xml", "*.bin", "*.*"};
Array<String> uiAllFilters = {"*.*"};
Array<String> uiScriptFilters = {"*.as", "*.*"};
uint uiSceneFilter = 0;
uint uiNodeFilter = 0;
uint uiImportFilter = 0;
uint uiScriptFilter = 0;
String uiScenePath = fileSystem.programDir + "Data/Scenes";
String uiNodePath = fileSystem.programDir + "Data/Objects";
String uiImportPath;
String uiScriptPath = fileSystem.programDir + "Data/Scripts";

bool uiHidden = false;
float uiMinOpacity = 0.3;
float uiMaxOpacity = 0.7;

void CreateUI()
{
    uiStyle = cache.GetResource("XMLFile", "UI/DefaultStyle.xml");
    ui.root.defaultStyle = uiStyle;
    
    iconStyle = cache.GetResource("XMLFile", "UI/EditorIcons.xml");

    CreateCursor();
    CreateMenuBar();
    CreateSceneWindow();
    CreateNodeWindow();
    CreateEditorSettingsDialog();
    CreateEditorPreferencesDialog();
    CreateStatsBar();
    CreateConsole();
    CreateDebugHud();

    SubscribeToEvent("ScreenMode", "ResizeUI");
    SubscribeToEvent("MenuSelected", "HandleMenuSelected");
    SubscribeToEvent("KeyDown", "HandleKeyDown");
    SubscribeToEvent("KeyUp", "UnhideUI");
    SubscribeToEvent("MouseButtonUp", "UnhideUI");
}

void ResizeUI()
{
    // Resize menu bar
    uiMenuBar.SetFixedWidth(graphics.width);
    
    // Relayout stats bar
    Font@ font = cache.GetResource("Font", "Fonts/Anonymous Pro.ttf");
    if (graphics.width >= 1200)
    {
        SetupStatsBarText(editorModeText, font, 0, 24, HA_LEFT, VA_TOP);
        SetupStatsBarText(renderStatsText, font, 0, 24, HA_RIGHT, VA_TOP);
    }
    else
    {
        SetupStatsBarText(editorModeText, font, 0, 24, HA_LEFT, VA_TOP);
        SetupStatsBarText(renderStatsText, font, 0, 36, HA_LEFT, VA_TOP);
    }
    
    // Relayout windows
    Array<UIElement@> children = ui.root.GetChildren();
    for (uint i = 0; i < children.length; ++i)
    {
        if (children[i].type == windowType)
            AdjustPosition(children[i]);
    }
}

void AdjustPosition(Window@ window)
{
    IntVector2 position = window.position;
    IntVector2 size = window.size;
    IntVector2 extend = position + size;
    if (extend.x > graphics.width)
        position.x = Max(20, graphics.width - size.x - 20);
    if (extend.y > graphics.height)
        position.y = Max(40, graphics.height - size.y - 20);
    window.position = position;
}

void CreateCursor()
{
    Cursor@ cursor = Cursor("Cursor");
    cursor.style = uiStyle;
    cursor.SetPosition(graphics.width / 2, graphics.height / 2);
    ui.cursor = cursor;
    if (GetPlatform() == "Android" || GetPlatform() == "iOS")
        ui.cursor.visible = false;
}

void CreateMenuBar()
{
    uiMenuBar = BorderImage("MenuBar");
    uiMenuBar.active = true;
    uiMenuBar.SetStyle(uiStyle, "EditorMenuBar");
    uiMenuBar.SetLayout(LM_HORIZONTAL);
    uiMenuBar.opacity = uiMaxOpacity;
    uiMenuBar.SetFixedWidth(graphics.width);
    ui.root.AddChild(uiMenuBar);

    {
        Menu@ fileMenu = CreateMenu("File");
        Window@ filePopup = fileMenu.popup;
        filePopup.AddChild(CreateMenuItem("New scene", 0, 0));
        filePopup.AddChild(CreateMenuItem("Open scene...", 'O', QUAL_CTRL));
        filePopup.AddChild(CreateMenuItem("Save scene", 'S', QUAL_CTRL));
        filePopup.AddChild(CreateMenuItem("Save scene as...", 'S', QUAL_SHIFT | QUAL_CTRL));
        filePopup.AddChild(CreateMenuDivider());

        Menu@ loadNodeMenu = CreateMenuItem("Load node", 0, 0);
        Window@ loadNodePopup = CreatePopup(loadNodeMenu);
        loadNodeMenu.popupOffset = IntVector2(loadNodeMenu.width, 0);
        loadNodePopup.AddChild(CreateMenuItem("As replicated...", 0, 0));
        loadNodePopup.AddChild(CreateMenuItem("As local...", 0, 0));
        filePopup.AddChild(loadNodeMenu);
        
        filePopup.AddChild(CreateMenuItem("Save node as...", 0, 0));
        filePopup.AddChild(CreateMenuDivider());
        filePopup.AddChild(CreateMenuItem("Import model...", 0, 0));
        filePopup.AddChild(CreateMenuItem("Import scene...", 0, 0));
        filePopup.AddChild(CreateMenuItem("Run script...", 0, 0));
        filePopup.AddChild(CreateMenuDivider());
        filePopup.AddChild(CreateMenuItem("Set resource path...", 0, 0));
        filePopup.AddChild(CreateMenuDivider());
        filePopup.AddChild(CreateMenuItem("Exit", 0, 0));
        uiMenuBar.AddChild(fileMenu);
    }

    {
        Menu@ editMenu = CreateMenu("Edit");
        Window@ editPopup = editMenu.popup;
        editPopup.AddChild(CreateMenuItem("Cut", 'X', QUAL_CTRL));
        editPopup.AddChild(CreateMenuItem("Copy", 'C', QUAL_CTRL));
        editPopup.AddChild(CreateMenuItem("Paste", 'V', QUAL_CTRL));
        editPopup.AddChild(CreateMenuItem("Delete", KEY_DELETE, QUAL_ANY));
        editPopup.AddChild(CreateMenuItem("Select all", 'A', QUAL_CTRL));
        editPopup.AddChild(CreateMenuDivider());
        editPopup.AddChild(CreateMenuItem("Reset position", 0, 0));
        editPopup.AddChild(CreateMenuItem("Reset rotation", 0, 0));
        editPopup.AddChild(CreateMenuItem("Reset scale", 0, 0));
        editPopup.AddChild(CreateMenuItem("Unparent", 'U', QUAL_CTRL));
        editPopup.AddChild(CreateMenuDivider());
        editPopup.AddChild(CreateMenuItem("Toggle update", 'P', QUAL_CTRL));
        uiMenuBar.AddChild(editMenu);
    }

    {
        Menu@ createMenu = CreateMenu("Create");
        Window@ createPopup = createMenu.popup;
        createPopup.AddChild(CreateMenuItem("Box", 0, 0));
        createPopup.AddChild(CreateMenuItem("Cone", 0, 0));
        createPopup.AddChild(CreateMenuItem("Cylinder", 0, 0));
        createPopup.AddChild(CreateMenuItem("Plane", 0, 0));
        createPopup.AddChild(CreateMenuItem("Pyramid", 0, 0));
        createPopup.AddChild(CreateMenuItem("Sphere", 0, 0));
        uiMenuBar.AddChild(createMenu);
    }

    {
        Menu@ fileMenu = CreateMenu("View");
        Window@ filePopup = fileMenu.popup;
        filePopup.AddChild(CreateMenuItem("Hierarchy", 'H', QUAL_CTRL));
        filePopup.AddChild(CreateMenuItem("Attribute inspector", 'N', QUAL_CTRL));
        filePopup.AddChild(CreateMenuItem("Editor settings", 0, 0));
        filePopup.AddChild(CreateMenuItem("Editor preferences", 0, 0));
        uiMenuBar.AddChild(fileMenu);
    }

    BorderImage@ spacer = BorderImage("MenuBarSpacer");
    spacer.SetStyle(uiStyle, "EditorMenuBar");
    uiMenuBar.AddChild(spacer);
}

Menu@ CreateMenuItem(const String&in title, int accelKey, int accelQual, int padding = 16)
{
    Menu@ menu = Menu(title);
    menu.style = uiStyle;
    menu.SetLayout(LM_HORIZONTAL, 0, IntRect(padding, 2, padding, 2));
    if (accelKey != 0)
        menu.SetAccelerator(accelKey, accelQual);

    Text@ menuText = Text();
    menuText.SetStyle(uiStyle, "EditorMenuText");
    menuText.text = title;
    menu.AddChild(menuText);

    return menu;
}

BorderImage@ CreateMenuDivider()
{
    BorderImage@ divider = BorderImage();
    divider.SetStyle(uiStyle, "EditorDivider");

    return divider;
}

Window@ CreatePopup(Menu@ baseMenu)
{
    Window@ popup = Window();
    popup.style = uiStyle;
    popup.SetLayout(LM_VERTICAL, 1, IntRect(2, 6, 2, 6));
    baseMenu.popup = popup;
    baseMenu.popupOffset = IntVector2(0, baseMenu.height);

    return popup;
}

Menu@ CreateMenu(const String&in title)
{
    Menu@ menu = CreateMenuItem(title, 0, 0, 8);
    menu.name = "";
    menu.SetFixedWidth(menu.width);
    CreatePopup(menu);

    return menu;
}

void CreateFileSelector(const String&in title, const String&in ok, const String&in cancel, const String&in initialPath, Array<String>@ filters,
    uint initialFilter)
{
    // Within the editor UI, the file selector is a kind of a "singleton". When the previous one is overwritten, also
    // the events subscribed from it are disconnected, so new ones are safe to subscribe.
    uiFileSelector = FileSelector();
    uiFileSelector.style = uiStyle;
    uiFileSelector.title = title;
    uiFileSelector.path = initialPath;
    uiFileSelector.SetButtonTexts(ok, cancel);
    uiFileSelector.SetFilters(filters, initialFilter);

    CenterDialog(uiFileSelector.window);
}

void CloseFileSelector(uint&out filterIndex, String&out path)
{
    // Save filter & path for next time
    filterIndex = uiFileSelector.filterIndex;
    path = uiFileSelector.path;
    
    uiFileSelector = null;
}

void CloseFileSelector()
{
    uiFileSelector = null;
}

void CreateConsole()
{
    Console@ console = engine.CreateConsole();
    console.style = uiStyle;
    console.numRows = 16;
}

void CreateDebugHud()
{
    engine.CreateDebugHud();
    debugHud.style = uiStyle;
    debugHud.mode = DEBUGHUD_SHOW_NONE;
}

void CenterDialog(UIElement@ element)
{
    IntVector2 size = element.size;
    element.SetPosition((graphics.width - size.x) / 2, (graphics.height - size.y) / 2);
}

void UpdateWindowTitle()
{
    String sceneName = GetFileNameAndExtension(sceneFileName);
    if (sceneName.empty)
        sceneName = "Untitled";
    if (sceneModified)
        sceneName += "*";

    graphics.windowTitle = "Urho3D editor - " + sceneName;
}

void HandlePopup(Menu@ menu)
{
    // Close the top level menu now unless the selected menu item has another popup
    if (menu.popup !is null)
        return;
    
    for (;;)
    {
        UIElement@ menuParent = menu.parent;
        if (menuParent is null)
            break;

        Menu@ nextMenu = menuParent.vars["Origin"].GetUIElement();
        if (nextMenu is null)
            break;
        else
            menu = nextMenu;
    }

    if (menu.parent is uiMenuBar)
        menu.showPopup = false;
}

void HandleMenuSelected(StringHash eventType, VariantMap& eventData)
{
    Menu@ menu = eventData["Element"].GetUIElement();
    if (menu is null)
        return;

    String action = menu.name;
    if (action.empty)
        return;

    HandlePopup(menu);

    if (uiFileSelector is null)
    {
        if (action == "New scene")
            ResetScene();
        else if (action == "Open scene...")
        {
            CreateFileSelector("Open scene", "Open", "Cancel", uiScenePath, uiSceneFilters, uiSceneFilter);
            SubscribeToEvent(uiFileSelector, "FileSelected", "HandleOpenSceneFile");
        }
        else if (action == "Save scene" && !sceneFileName.empty)
            SaveScene(sceneFileName);
        else if (action == "Save scene as..." || action == "Save scene")
        {
            CreateFileSelector("Save scene as", "Save", "Cancel", uiScenePath, uiSceneFilters, uiSceneFilter);
            uiFileSelector.fileName = GetFileNameAndExtension(sceneFileName);
            SubscribeToEvent(uiFileSelector, "FileSelected", "HandleSaveSceneFile");
        }
        else if (action == "As replicated...")
        {
            instantiateMode = REPLICATED;
            CreateFileSelector("Load node", "Load", "Cancel", uiNodePath, uiSceneFilters, uiNodeFilter);
            SubscribeToEvent(uiFileSelector, "FileSelected", "HandleLoadNodeFile");
        }
        else if (action == "As local...")
        {
            instantiateMode = LOCAL;
            CreateFileSelector("Load node", "Load", "Cancel", uiNodePath, uiSceneFilters, uiNodeFilter);
            SubscribeToEvent(uiFileSelector, "FileSelected", "HandleLoadNodeFile");
        }
        else if (action == "Save node as...")
        {
            if (selectedNodes.length == 1 && selectedNodes[0] !is editorScene)
            {
                CreateFileSelector("Save node", "Save", "Cancel", uiNodePath, uiSceneFilters, uiNodeFilter);
                uiFileSelector.fileName = GetFileNameAndExtension(instantiateFileName);
                SubscribeToEvent(uiFileSelector, "FileSelected", "HandleSaveNodeFile");
            }
        }
        else if (action == "Import model...")
        {
            CreateFileSelector("Import model", "Import", "Cancel", uiImportPath, uiAllFilters, uiImportFilter);
            SubscribeToEvent(uiFileSelector, "FileSelected", "HandleImportModel");
        }
        else if (action == "Import scene...")
        {
            CreateFileSelector("Import scene", "Import", "Cancel", uiImportPath, uiAllFilters, uiImportFilter);
            SubscribeToEvent(uiFileSelector, "FileSelected", "HandleImportScene");
        }
        else if (action == "Run script...")
        {
            CreateFileSelector("Run script", "Run", "Cancel", uiScriptPath, uiScriptFilters, uiScriptFilter);
            SubscribeToEvent(uiFileSelector, "FileSelected", "HandleRunScript");
        }
        else if (action == "Set resource path...")
        {
            CreateFileSelector("Set resource path", "Set", "Cancel", sceneResourcePath, uiAllFilters, 0);
            uiFileSelector.directoryMode = true;
            SubscribeToEvent(uiFileSelector, "FileSelected", "HandleResourcePath");
        }
    }

    if (action == "Hierarchy")
        ShowSceneWindow();
    else if (action == "Attribute inspector")
        ShowNodeWindow();
    else if (action == "Editor settings")
        ShowEditorSettingsDialog();
    else if (action == "Editor preferences")
        ShowEditorPreferencesDialog();
    else if (action == "Cut")
        SceneCut();
    else if (action == "Copy")
        SceneCopy();
    else if (action == "Paste")
        ScenePaste();
    else if (action == "Delete")
        SceneDelete();
    else if (action == "Reset position")
        SceneResetPosition();
    else if (action == "Reset rotation")
        SceneResetRotation();
    else if (action == "Reset scale")
        SceneResetScale();
    else if (action == "Unparent")
        SceneUnparent();
    else if (action == "Select all")
        SceneSelectAll();
    else if (action == "Toggle update")
        ToggleUpdate();
    else if (action == "Box" || action == "Cone" || action == "Cylinder" || action == "Plane" ||
        action == "Pyramid" || action == "Sphere")
        CreateBuiltinObject(action);
    else if (action == "Exit")
        engine.Exit();
}

String ExtractFileName(VariantMap& eventData)
{
    String fileName;
    
    // Check for OK
    if (eventData["OK"].GetBool())
        fileName = eventData["FileName"].GetString();
    
    return fileName;
}

void HandleOpenSceneFile(StringHash eventType, VariantMap& eventData)
{
    CloseFileSelector(uiSceneFilter, uiScenePath);
    LoadScene(ExtractFileName(eventData));
}

void HandleSaveSceneFile(StringHash eventType, VariantMap& eventData)
{
    CloseFileSelector(uiSceneFilter, uiScenePath);
    SaveScene(ExtractFileName(eventData));
}

void HandleLoadNodeFile(StringHash eventType, VariantMap& eventData)
{
    CloseFileSelector(uiNodeFilter, uiNodePath);
    LoadNode(ExtractFileName(eventData));
}

void HandleSaveNodeFile(StringHash eventType, VariantMap& eventData)
{
    CloseFileSelector(uiNodeFilter, uiNodePath);
    SaveNode(ExtractFileName(eventData));
}

void HandleImportModel(StringHash eventType, VariantMap& eventData)
{
    CloseFileSelector(uiImportFilter, uiImportPath);
    ImportModel(ExtractFileName(eventData));
}

void HandleImportScene(StringHash eventType, VariantMap& eventData)
{
    CloseFileSelector(uiImportFilter, uiImportPath);
    ImportScene(ExtractFileName(eventData));
}

void ExecuteScript(const String&in fileName)
{
    if (fileName.empty)
        return;
    
    File@ file = File(fileName, FILE_READ);
    if (file.open)
    {
        String scriptCode;
        while (!file.eof)
            scriptCode += file.ReadLine() + "\n";
        file.Close();
        
        if (script.Execute(scriptCode))
            log.Info("Script " + fileName + " ran successfully");
    }
}

void HandleRunScript(StringHash eventType, VariantMap& eventData)
{
    CloseFileSelector(uiScriptFilter, uiScriptPath);
    ExecuteScript(ExtractFileName(eventData));
}

void HandleResourcePath(StringHash eventType, VariantMap& eventData)
{
    CloseFileSelector();
    SetResourcePath(ExtractFileName(eventData), false);
}

void HandleKeyDown(StringHash eventType, VariantMap& eventData)
{
    int key = eventData["Key"].GetInt();
    
    if (key == KEY_F1)
        console.Toggle();

    if (key == KEY_ESC)
    {
        UIElement@ front = ui.frontElement;
        if (console.visible)
            console.visible = false;
        else if (uiFileSelector !is null && front is uiFileSelector.window)
            CloseFileSelector();
        else if (front is settingsDialog)
        {
            ui.focusElement = null;
            front.visible = false;
        }
    }

    if (key == KEY_F2)
        ToggleRenderingDebug();
    if (key == KEY_F3)
        TogglePhysicsDebug();
    if (key == KEY_F4)
        ToggleOctreeDebug();

    if (eventData["Qualifiers"].GetInt() == QUAL_CTRL)
    {
        if (key == '1')
            editMode = EDIT_MOVE;
        else if (key == '2')
            editMode = EDIT_ROTATE;
        else if (key == '3')
            editMode = EDIT_SCALE;
        if (key == '4')
            editMode = EDIT_SELECT;
        else if (key == '5')
            axisMode = AxisMode(axisMode ^ AXIS_LOCAL);
        else if (key == '6')
        {
            --pickMode;
            if (pickMode < PICK_GEOMETRIES)
                pickMode = MAX_PICK_MODES - 1;
        }
        else if (key == '7')
        {
            ++pickMode;
            if (pickMode >= MAX_PICK_MODES)
                pickMode = PICK_GEOMETRIES;
        }
        else if (key == 'W')
        {
            fillMode = FillMode(fillMode + 1);
            if (fillMode > FILL_POINT)
                fillMode = FILL_SOLID;

            // Update camera fill mode
            camera.fillMode = fillMode;
        }
        else
            SteppedObjectManipulation(key);
    }
}

void UnhideUI()
{
    HideUI(false);
}

void HideUI(bool hide = true)
{
    if (uiHidden == hide)
        return;
    
    float opacity = (uiHidden = hide) ? uiMinOpacity : uiMaxOpacity;
    Array<UIElement@> children = ui.root.GetChildren();
    for (uint i = 0; i < children.length; ++i)
    {
        if (children[i].type != textType)
            children[i].opacity = opacity;
    }
}

void IconizeUIElement(UIElement@ element, const String&in iconType)
{
    // Check if the icon has been created before
    BorderImage@ icon = element.GetChild("Icon");

    // If iconType is empty, it is a request to remove the existing icon 
    if (iconType.empty)
    {
        // Remove the icon if it exists
        if (icon !is null)
            icon.Remove();
        
        // Revert back the indent but only if it is indented by this function
        if (element.vars["IconIndented"].GetBool())
            element.indent = 0;
        
        return;
    }
    
    // The UI element must itself has been indented to reserve the space for the icon
    if (element.indent == 0)
    {
        element.indent = 1;
        element.vars["IconIndented"] = true; 
    }

    // If no icon yet then create one with the correct indent and size in respect to the UI element
    if (icon is null)
    {
        // The icon is placed at one indent level less than the UI element
        icon = BorderImage("Icon");
        icon.indent = element.indent - 1;
        icon.SetFixedSize(element.indentWidth - 2, 14);
        element.AddChild(icon);
    }

    // Set the icon type
    icon.SetStyle(iconStyle, iconType);
    icon.color = Color(1,1,1,1); // Reset to enabled color
}

void SetIconEnabledColor(UIElement@ element, bool enabled)
{
    BorderImage@ icon = element.GetChild("Icon");
    if (icon !is null)
        icon.color = enabled ? Color(1,1,1,1) : Color(1,0,0,1);
}