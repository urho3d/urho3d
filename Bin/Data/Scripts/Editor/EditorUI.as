// Urho3D editor user interface

XMLFile@ uiStyle;
UIElement@ uiMenuBar;
FileSelector@ uiFileSelector;

Array<String> uiSceneFilters = {"*.xml", "*.bin", "*.dat", "*.*"};
Array<String> uiAllFilter = {"*.*"};
uint uiSceneFilter = 0;
String uiScenePath;
String uiImportPath;

void CreateUI()
{
    @uiStyle = cache.GetResource("XMLFile", "UI/DefaultStyle.xml");

    CreateCursor();
    CreateMenuBar();                                                                              
    CreateSceneWindow();
    CreateNodeWindow();
    CreateEditorSettingsDialog();
    CreateStatsBar();
    CreateConsole();
    
    SubscribeToEvent("ScreenMode", "ResizeUI");
    SubscribeToEvent("MenuSelected", "HandleMenuSelected");
    SubscribeToEvent("KeyDown", "HandleKeyDown");
}

void ResizeUI()
{
    uiMenuBar.SetFixedWidth(graphics.width);
}

void CreateCursor()
{
    Cursor@ cursor = Cursor("Cursor");
    cursor.style = uiStyle;
    cursor.SetPosition(graphics.width / 2, graphics.height / 2);
    ui.cursor = cursor;
}

void CreateMenuBar()
{
    @uiMenuBar = BorderImage("MenuBar");
    uiMenuBar.active = true;
    uiMenuBar.SetStyle(uiStyle, "EditorMenuBar");
    uiMenuBar.SetLayout(LM_HORIZONTAL, 4, IntRect(2, 2, 2, 2));
    ui.root.AddChild(uiMenuBar);

    {
        Menu@ fileMenu = CreateMenu("File");
        Window@ filePopup = fileMenu.popup;
        filePopup.AddChild(CreateMenuItem("New scene", 0, 0));
        filePopup.AddChild(CreateMenuItem("Open scene", 'O', QUAL_CTRL));
        filePopup.AddChild(CreateMenuItem("Save scene", 'S', QUAL_CTRL));
        filePopup.AddChild(CreateMenuItem("Save scene as", 'S', QUAL_SHIFT | QUAL_CTRL));
        filePopup.AddChild(CreateMenuDivider());
        filePopup.AddChild(CreateMenuItem("Import model", 0, 0));
        filePopup.AddChild(CreateMenuItem("Import scene", 0, 0));
        filePopup.AddChild(CreateMenuDivider());
        filePopup.AddChild(CreateMenuItem("Set resource path", 0, 0));
        filePopup.AddChild(CreateMenuItem("Reload resources", 'R', QUAL_CTRL));
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
        editPopup.AddChild(CreateMenuItem("Delete", KEY_DELETE, 0));
        editPopup.AddChild(CreateMenuDivider());
        editPopup.AddChild(CreateMenuItem("Toggle physics", 'P', QUAL_CTRL));
        uiMenuBar.AddChild(editMenu);
    }
    
    {
        Menu@ fileMenu = CreateMenu("View");
        Window@ filePopup = fileMenu.popup;
        filePopup.AddChild(CreateMenuItem("Scene hierarchy", 'H', QUAL_CTRL));
        filePopup.AddChild(CreateMenuItem("Entity / component edit", 'E', QUAL_CTRL));
        filePopup.AddChild(CreateMenuItem("Editor settings", 0, 0));
        uiMenuBar.AddChild(fileMenu);
    }

    UIElement@ spacer = UIElement("MenuBarSpacer");
    uiMenuBar.AddChild(spacer);

    ResizeUI();
}

Menu@ CreateMenuItem(const String&in title, int accelKey, int accelQual)
{
    Menu@ menu = Menu(title);
    menu.style = uiStyle;
    menu.SetLayout(LM_HORIZONTAL, 0, IntRect(4, 0, 4, 0));
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
    divider.SetFixedHeight(4);

    return divider;
}

Window@ CreatePopup(Menu@ baseMenu)
{
    Window@ popup = Window();
    popup.style = uiStyle;
    popup.SetLayout(LM_VERTICAL, 4, IntRect(4, 4, 4, 4));
    baseMenu.popup = popup;
    baseMenu.popupOffset = IntVector2(0, baseMenu.height);

    return popup;
}

Menu@ CreateMenu(const String&in title)
{
    Menu@ menu = CreateMenuItem(title, 0, 0);
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
    @uiFileSelector = FileSelector();
    uiFileSelector.style = uiStyle;
    uiFileSelector.title = title;
    uiFileSelector.path = initialPath;
    uiFileSelector.SetButtonTexts(ok, cancel);
    uiFileSelector.SetFilters(filters, initialFilter);

    CenterDialog(uiFileSelector.window);
}

void CloseFileSelector()
{
    @uiFileSelector = null;
}

void CreateConsole()
{
    Console@ console = engine.CreateConsole();
    console.style = uiStyle;
    console.numRows = 16;
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

void HandleMenuSelected(StringHash eventType, VariantMap& eventData)
{
    Menu@ menu = eventData["Element"].GetUIElement();
    if (menu is null)
        return;

    String action = menu.name;
    if (action.empty)
        return;
        
    // Close the menu now
    UIElement@ menuParent = menu.parent;
    Menu@ topLevelMenu = menuParent.vars["Origin"].GetUIElement();
    if (topLevelMenu !is null)
        topLevelMenu.showPopup = false;

    if (uiFileSelector is null)
    {
        if (action == "New scene")
            CreateScene();
            
        if (action == "Open scene")
        {
            CreateFileSelector("Open scene", "Open", "Cancel", uiScenePath, uiSceneFilters, uiSceneFilter);
            SubscribeToEvent(uiFileSelector, "FileSelected", "HandleOpenSceneFile");
        }

        if (action == "Save scene")
            SaveScene(sceneFileName);

        if (action == "Save scene as")
        {
            CreateFileSelector("Save scene as", "Save", "Cancel", uiScenePath, uiSceneFilters, uiSceneFilter);
            uiFileSelector.fileName = GetFileNameAndExtension(sceneFileName);
            SubscribeToEvent(uiFileSelector, "FileSelected", "HandleSaveSceneFile");
        }

        if (action == "Import model")
        {
            CreateFileSelector("Import model", "Import", "Cancel", uiImportPath, uiAllFilter, 0);
            SubscribeToEvent(uiFileSelector, "FileSelected", "HandleImportModel");
        }

        if (action == "Import scene")
        {
            CreateFileSelector("Import scene", "Import", "Cancel", uiImportPath, uiAllFilter, 0);
            SubscribeToEvent(uiFileSelector, "FileSelected", "HandleImportScene");
        }
        
        if (action == "Set resource path")
        {
            CreateFileSelector("Set resource path", "Set", "Cancel", sceneResourcePath, uiAllFilter, 0);
            uiFileSelector.directoryMode = true;
            SubscribeToEvent(uiFileSelector, "FileSelected", "HandleResourcePath");
        }
    }

    if (action == "Reload resources")
        ReloadResources();

    if (action == "Scene hierarchy")
        ShowSceneWindow();

    if (action == "Entity / component edit")
        ShowNodeWindow();

    if (action == "Editor settings")
        ShowEditorSettingsDialog();
    
    if (action == "Cut")
        SceneCut();
    
    if (action == "Copy")
        SceneCopy();
    
    if (action == "Paste")
        ScenePaste();
    
    if (action == "Delete")
        SceneDelete();
    
    if (action == "Toggle physics")
        TogglePhysics();
    
    if (action == "Exit")
        engine.Exit();
}

void HandleOpenSceneFile(StringHash eventType, VariantMap& eventData)
{
    // Save filter & path for next time
    uiSceneFilter = uiFileSelector.filterIndex;
    uiScenePath = uiFileSelector.path;
    CloseFileSelector();

    // Check for cancel
    if (!eventData["OK"].GetBool())
        return;

    String fileName = eventData["FileName"].GetString();
    LoadScene(fileName);
}

void HandleSaveSceneFile(StringHash eventType, VariantMap& eventData)
{
    // Save filter for next time
    uiSceneFilter = uiFileSelector.filterIndex;
    uiScenePath = uiFileSelector.path;
    CloseFileSelector();

    // Check for cancel
    if (!eventData["OK"].GetBool())
        return;

    String fileName = eventData["FileName"].GetString();
    SaveScene(fileName);
}

void HandleImportModel(StringHash eventType, VariantMap& eventData)
{
    // Save path for next time
    uiImportPath = uiFileSelector.path;
    CloseFileSelector();

    // Check for cancel
    if (!eventData["OK"].GetBool())
        return;

    String fileName = eventData["FileName"].GetString();
    ImportModel(fileName);
}

void HandleImportScene(StringHash eventType, VariantMap& eventData)
{
    // Save path for next time
    uiImportPath = uiFileSelector.path;
    CloseFileSelector();

    // Check for cancel
    if (!eventData["OK"].GetBool())
        return;

    String fileName = eventData["FileName"].GetString();
    ImportScene(fileName);
}

void HandleResourcePath(StringHash eventType, VariantMap& eventData)
{
    CloseFileSelector();

    // Check for cancel
    if (!eventData["OK"].GetBool())
        return;

    SetResourcePath(eventData["FileName"].GetString());
}

void HandleKeyDown(StringHash eventType, VariantMap& eventData)
{
    int key = eventData["Key"].GetInt();
    
    if (key == KEY_F1)
    {
        console.Toggle();
        input.SuppressNextChar();
    }
    if (key == KEY_ESC)
    {
        UIElement@ front = ui.frontElement;
        if (uiFileSelector !is null && front is uiFileSelector.window)
            CloseFileSelector();
        else if (front is editorSettingsDialog || front is sceneWindow || front is nodeWindow)
            front.visible = false;
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
            moveMode = OBJ_MOVE;
        else if (key == '2')
            moveMode = OBJ_ROTATE;
        else if (key == '3')
            moveMode = OBJ_SCALE;
        else
            SteppedObjectManipulation(key);
    }
}
