// Urho3D editor user interface

XMLFile@ uiStyle;
UIElement@ uiMenuBar;
FileSelector@ uiFileSelector;

array<string> uiSceneFilters = {"*.xml", "*.bin", "*.sav", "*.*"};
array<string> uiAllFilter = {"*.*"};
uint uiSceneFilter = 0;

void createUI()
{
    @uiStyle = cache.getResource("XMLFile", "UI/DefaultStyle.xml");

    createCursor();
    createMenuBar();
    createSceneWindow();
    createComponentWindow();
    createCameraDialog();
    createConsole();
    
    subscribeToEvent("ScreenMode", "resizeUI");
    subscribeToEvent("MenuSelected", "handleMenuSelected");
	subscribeToEvent("KeyDown", "handleKeyDown");
}

void resizeUI()
{
    uiMenuBar.setFixedWidth(renderer.getWidth());
}

void createCursor()
{
    Cursor@ cursor = Cursor("Cursor");
    cursor.setStyleAuto(uiStyle);
    cursor.setPosition(input.getMousePosition());
    ui.setCursor(cursor);
}

void createMenuBar()
{
    @uiMenuBar = BorderImage("MenuBar");
    uiMenuBar.setStyle(uiStyle, "EditorMenuBar");
    uiMenuBar.setLayout(LM_HORIZONTAL, 2, IntRect(2, 2, 2, 2));
    uiRoot.addChild(uiMenuBar);

    {
        Menu@ fileMenu = createMenu("File");
        Window@ filePopup = fileMenu.getPopup();
        filePopup.addChild(createMenuItem("New scene", 0, 0));
        filePopup.addChild(createMenuItem("Open scene", 'O', QUAL_CTRL));
        filePopup.addChild(createMenuItem("Save scene", 'S', QUAL_CTRL));
        filePopup.addChild(createMenuItem("Save scene as", 'S', QUAL_SHIFT | QUAL_CTRL));
        filePopup.addChild(createMenuDivider());
        filePopup.addChild(createMenuItem("Set resource path", 0, 0));
        filePopup.addChild(createMenuItem("Reload resources", 'R', QUAL_CTRL));
        filePopup.addChild(createMenuDivider());
        filePopup.addChild(createMenuItem("Exit", 'X', QUAL_CTRL));
        uiMenuBar.addChild(fileMenu);
    }

    {
        Menu@ editMenu = createMenu("Edit");
        Window@ editPopup = editMenu.getPopup();
        editPopup.addChild(createMenuItem("Cut", 'X', QUAL_CTRL));
        editPopup.addChild(createMenuItem("Copy", 'C', QUAL_CTRL));
        editPopup.addChild(createMenuItem("Paste", 'V', QUAL_CTRL));
        editPopup.addChild(createMenuItem("Delete", KEY_DELETE, 0));
        uiMenuBar.addChild(editMenu);
    }
    
    {
        Menu@ fileMenu = createMenu("View");
        Window@ filePopup = fileMenu.getPopup();
        filePopup.addChild(createMenuItem("Scene hierarchy", 0, 0));
        filePopup.addChild(createMenuItem("Component edit", 0, 0));
        filePopup.addChild(createMenuItem("Camera settings", 0, 0));
        uiMenuBar.addChild(fileMenu);
    }

    UIElement@ spacer = UIElement("MenuBarSpacer");
    uiMenuBar.addChild(spacer);

    resizeUI();
}

Menu@ createMenuItem(const string& in title, int accelKey, int accelQual)
{
    Menu@ menu = Menu(title);
    menu.setStyleAuto(uiStyle);
    menu.setLayout(LM_HORIZONTAL, 0, IntRect(4, 0, 4, 0));
    if (accelKey != 0)
        menu.setAccelerator(accelKey, accelQual);

    Text@ menuText = Text();
    menuText.setStyle(uiStyle, "EditorMenuText");
    menuText.setText(title);
    menu.addChild(menuText);

    return menu;
}

BorderImage@ createMenuDivider()
{
    BorderImage@ divider = BorderImage();
    divider.setStyle(uiStyle, "EditorDivider");
    divider.setFixedHeight(4);

    return divider;
}

Window@ createPopup(Menu@ baseMenu)
{
    Window@ popup = Window();
    popup.setStyleAuto(uiStyle);
    popup.setLayout(LM_VERTICAL, 4, IntRect(4, 4, 4, 4));
    baseMenu.setPopup(popup);
    baseMenu.setPopupOffset(0, baseMenu.getHeight());

    return popup;
}

Menu@ createMenu(const string& in title)
{
    Menu@ menu = createMenuItem(title, 0, 0);
    menu.setName("");
    menu.setFixedWidth(menu.getWidth());
    createPopup(menu);

    return menu;
}

void createFileSelector(const string& in title, const string& in ok, const string& in cancel, const string& in initialPath, array<string>@ filters,
    uint initialFilter)
{
    // Within the editor UI, the file selector is a kind of a "singleton". When the previous one is overwritten, also 
    // the events subscribed from it are disconnected, so new ones are safe to subscribe.
    @uiFileSelector = FileSelector();
    uiFileSelector.setStyle(uiStyle);
    uiFileSelector.setTitle(title);
    uiFileSelector.setButtonTexts(ok, cancel);
    uiFileSelector.setPath(initialPath);
    uiFileSelector.setFilters(filters, initialFilter);
    
    Window@ window = uiFileSelector.getWindow();
    centerDialog(window);
}

void closeFileSelector()
{
    @uiFileSelector = null;
}

void createConsole()
{
    Console@ console = engine.createConsole();
    console.setStyle(uiStyle);
    console.setNumRows(16);
}

void centerDialog(UIElement@ element)
{
    IntVector2 size = element.getSize();
    element.setPosition((renderer.getWidth() - size.x) / 2, (renderer.getHeight() - size.y) / 2);
}

void updateWindowTitle()
{
    string sceneName = sceneFileName.empty() ? "Untitled" : getFileNameAndExtension(sceneFileName);
    if (sceneModified)
        sceneName += "*";
    renderer.setWindowTitle("Urho3D editor - " + sceneName);
}

void handleMenuSelected(StringHash eventType, VariantMap& eventData)
{
    Menu@ menu = eventData["Element"].getUIElement();
    if (menu is null)
        return;

    string action = menu.getName();
    if (action.empty())
        return;
        
    // Close the menu now
    UIElement@ menuParent = menu.getParent();
    Menu@ topLevelMenu = menuParent.userData["Origin"].getUIElement();
    if (topLevelMenu !is null)
        topLevelMenu.showPopup(false);

    if (uiFileSelector is null)
    {
        if (action == "New scene")
            createScene();
            
        if (action == "Open scene")
        {
            createFileSelector("Open scene", "Open", "Cancel", getPath(sceneFileName), uiSceneFilters, uiSceneFilter);
            subscribeToEvent(uiFileSelector, "FileSelected", "handleOpenSceneFile");
        }

        if (action == "Save scene")
            saveScene(sceneFileName);

        if (action == "Save scene as")
        {
            createFileSelector("Save scene as", "Save", "Cancel", getPath(sceneFileName), uiSceneFilters, uiSceneFilter);
            uiFileSelector.setFileName(getFileNameAndExtension(sceneFileName));
            subscribeToEvent(uiFileSelector, "FileSelected", "handleSaveSceneFile");
        }

        if (action == "Set resource path")
        {
            createFileSelector("Set resource path", "Set", "Cancel", sceneResourcePath, uiAllFilter, 0);
            uiFileSelector.setDirectoryMode(true);
            subscribeToEvent(uiFileSelector, "FileSelected", "handleResourcePath");
        }
    }

    if (action == "Reload resources")
        reloadResources();

    if (action == "Scene hierarchy")
        showSceneWindow();

    if (action == "Component edit")
        showComponentWindow();

    if (action == "Camera settings")
        showCameraDialog();
    
    if (action == "Cut")
        sceneCut();
    
    if (action == "Copy")
        sceneCopy();
    
    if (action == "Paste")
        scenePaste();
    
    if (action == "Delete")
        sceneDelete();
    
    if (menu.getName() == "Exit")
        engine.exit();
}

void handleOpenSceneFile(StringHash eventType, VariantMap& eventData)
{
    // Save filter for next time
    uiSceneFilter = uiFileSelector.getFilterIndex();
    closeFileSelector();

    // Check for cancel
    if (!eventData["OK"].getBool())
        return;

    string fileName = eventData["FileName"].getString();
    loadScene(fileName);
}

void handleSaveSceneFile(StringHash eventType, VariantMap& eventData)
{
    // Save filter for next time
    uiSceneFilter = uiFileSelector.getFilterIndex();
    closeFileSelector();

    // Check for cancel
    if (!eventData["OK"].getBool())
        return;

    string fileName = eventData["FileName"].getString();
    saveScene(fileName);
}

void handleResourcePath(StringHash eventType, VariantMap& eventData)
{
    closeFileSelector();
 
    // Check for cancel
    if (!eventData["OK"].getBool())
        return;

    setResourcePath(eventData["FileName"].getString());
}

void handleKeyDown(StringHash eventType, VariantMap& eventData)
{
    // Check for toggling the console
    if (eventData["Key"].getInt() == 220)
    {
        console.toggle();
        input.suppressNextChar();
    }
}
