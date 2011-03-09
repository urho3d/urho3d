// Urho3D editor user interface

const int uiSpacing = 2;
const IntRect uiSpacingRect(uiSpacing, uiSpacing, uiSpacing, uiSpacing);

XMLFile@ uiStyle;
UIElement@ uiMenuBar;
FileSelector@ uiFileSelector;

array<string> uiSceneFilters = {"*.xml", "*.bin", "*.sav", "*.*"};
uint uiSceneFilter = 0;

void createUI()
{
    @uiStyle = cache.getResource("XMLFile", "UI/DefaultStyle.xml");

    createCursor();
    createMenuBar();
    createSceneWindow();
    createComponentWindow();
    createCameraDialog();
    
    subscribeToEvent("ScreenMode", "resizeUI");
    subscribeToEvent("MenuSelected", "handleMenuSelected");
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
    uiMenuBar.setLayout(LM_HORIZONTAL, uiSpacing, uiSpacingRect);
    uiRoot.addChild(uiMenuBar);

    {
        Menu@ fileMenu = createMenu("File");
        Window@ filePopup = fileMenu.getPopup();
        filePopup.addChild(createMenuItem("Open scene", 'O', QUAL_CTRL));
        filePopup.addChild(createMenuItem("Save scene", 'S', QUAL_CTRL));
        filePopup.addChild(createMenuItem("Save scene as", 'S', QUAL_SHIFT | QUAL_CTRL));
        filePopup.addChild(createMenuSpacer());
        filePopup.addChild(createMenuItem("Exit", 'X', QUAL_CTRL));
        uiMenuBar.addChild(fileMenu);
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

Menu@ createMenuItem(string title, int accelKey, int accelQual)
{
    Menu@ menu = Menu(title);
    menu.setStyleAuto(uiStyle);
    menu.setLayout(LM_HORIZONTAL, 0, IntRect(4, 0, 4, 0));
    if (accelKey != 0)
        menu.setAccelerator(accelKey, accelQual);

    Text@ menuText = Text(title + "_Text");
    menuText.setStyle(uiStyle, "EditorMenuText");
    menuText.setText(title);
    menu.addChild(menuText);

    return menu;
}

Menu@ createMenuSpacer()
{
    Menu@ spacer = Menu();
    spacer.setStyleAuto(uiStyle);
    spacer.setFixedHeight(2);
    // Disable input, but set permanent selection to get a nice indentation effect
    spacer.setEnabled(false);
    spacer.setSelected(true);

    return spacer;
}

Window@ createPopup(Menu@ baseMenu)
{
    Window@ popup = Window(baseMenu.getName() + "_Popup");
    popup.setStyleAuto(uiStyle);
    popup.setLayout(LM_VERTICAL, uiSpacing, uiSpacingRect);
    baseMenu.setPopup(popup);
    baseMenu.setPopupOffset(0, baseMenu.getHeight());

    return popup;
}

Menu@ createMenu(string title)
{
    Menu@ menu = createMenuItem(title, 0, 0);
    menu.setFixedWidth(menu.getWidth());
    createPopup(menu);

    return menu;
}

void createFileSelector(string title, string ok, string cancel, string initialPath, array<string>@ filters,
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

void centerDialog(UIElement@ element)
{
    IntVector2 size = element.getSize();
    element.setPosition((renderer.getWidth() - size.x) / 2, (renderer.getHeight() - size.y) / 2);
}

void updateWindowTitle()
{
    string sceneName = sceneFileName.empty() ? "Untitled" : getFileNameAndExtension(sceneFileName);
    if (sceneUnsaved)
        sceneName += "*";
    renderer.setWindowTitle("Urho3D editor - " + sceneName);
}

void handleMenuSelected(StringHash eventType, VariantMap& eventData)
{
    Menu@ menu = eventData["Element"].getUIElement();
    if (menu is null)
        return;

    string action = menu.getName();

    if (uiFileSelector is null)
    {
        if (action == "Open scene")
        {
            createFileSelector("Open scene", "Open", "Cancel", getPath(sceneFileName), uiSceneFilters, uiSceneFilter);
            subscribeToEvent(uiFileSelector, "FileSelected", "handleOpenSceneFile");
        }

        if (action == "Save scene")
        {
            ui.setFocusElement(null); // Close the menu
            saveScene(sceneFileName);
        }

        if (action == "Save scene as")
        {
            createFileSelector("Save scene as", "Save", "Cancel", getPath(sceneFileName), uiSceneFilters, uiSceneFilter);
            uiFileSelector.setFileName(getFileNameAndExtension(sceneFileName));
            subscribeToEvent(uiFileSelector, "FileSelected", "handleSaveSceneFile");
        }
    }
    
    if (action == "Scene hierarchy")
    {
        ui.setFocusElement(null); // Close the menu
        showSceneWindow();
    }
    if (action == "Component edit")
    {
        ui.setFocusElement(null); // Close the menu
        showComponentWindow();
    }
    if (action == "Camera settings")
    {
        ui.setFocusElement(null); // Close the menu
        showCameraDialog();
    }
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
