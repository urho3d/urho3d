// Urho3D editor user interface

XMLFile@ uiStyle;
XMLFile@ iconStyle;
UIElement@ uiMenuBar;
FileSelector@ uiFileSelector;

const ShortStringHash UI_ELEMENT_TYPE("UIElement");
const ShortStringHash WINDOW_TYPE("Window");
const ShortStringHash MENU_TYPE("Menu");
const ShortStringHash TEXT_TYPE("Text");
const ShortStringHash CURSOR_TYPE("Cursor");

const String TEMP_SCENE_NAME("_tempscene_.xml");
const ShortStringHash CALLBACK_VAR("Callback");
const ShortStringHash INDENT_MODIFIED_BY_ICON_VAR("IconIndented");

const int SHOW_POPUP_INDICATOR = -1;

Array<String> uiSceneFilters = {"*.xml", "*.bin", "*.*"};
Array<String> uiElementFilters = {"*.xml"};
Array<String> uiAllFilters = {"*.*"};
Array<String> uiScriptFilters = {"*.as", "*.*"};
uint uiSceneFilter = 0;
uint uiElementFilter = 0;
uint uiNodeFilter = 0;
uint uiImportFilter = 0;
uint uiScriptFilter = 0;
String uiScenePath = fileSystem.programDir + "Data/Scenes";
String uiElementPath = fileSystem.programDir + "Data/UI";
String uiNodePath = fileSystem.programDir + "Data/Objects";
String uiImportPath;
String uiScriptPath = fileSystem.programDir + "Data/Scripts";

bool uiFaded = false;
float uiMinOpacity = 0.3;
float uiMaxOpacity = 0.7;
bool uiHidden = false;

void CreateUI()
{
    uiStyle = cache.GetResource("XMLFile", "UI/DefaultStyle.xml");
    ui.root.defaultStyle = uiStyle;

    iconStyle = cache.GetResource("XMLFile", "UI/EditorIcons.xml");

    CreateCursor();
    CreateMenuBar();
    CreateHierarchyWindow();
    CreateAttributeInspectorWindow();
    CreateEditorSettingsDialog();
    CreateEditorPreferencesDialog();
    CreateStatsBar();
    CreateConsole();
    CreateDebugHud();

    SubscribeToEvent("ScreenMode", "ResizeUI");
    SubscribeToEvent("MenuSelected", "HandleMenuSelected");
    SubscribeToEvent("KeyDown", "HandleKeyDown");
    SubscribeToEvent("KeyUp", "UnfadeUI");
    SubscribeToEvent("MouseButtonUp", "UnfadeUI");
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
        if (children[i].type == WINDOW_TYPE)
            AdjustPosition(children[i]);
    }

    // Relayout root UI element
    editorUIElement.SetSize(graphics.width, graphics.height);
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

// AngelScript does not support closures (yet), but funcdef should do just fine as a workaround for a few cases here for now
funcdef bool MENU_CALLBACK();
Array<MENU_CALLBACK@> menuCallbacks;

void CreateMenuBar()
{
    uiMenuBar = BorderImage("MenuBar");
    uiMenuBar.enabled = true;
    uiMenuBar.SetStyle(uiStyle, "EditorMenuBar");
    uiMenuBar.SetLayout(LM_HORIZONTAL);
    uiMenuBar.opacity = uiMaxOpacity;
    uiMenuBar.SetFixedWidth(graphics.width);

    ui.root.AddChild(uiMenuBar);

    {
        Menu@ menu = CreateMenu("File");
        Window@ popup = menu.popup;
        popup.AddChild(CreateMenuItem("New scene", @ResetScene, 'N', QUAL_SHIFT | QUAL_CTRL));
        popup.AddChild(CreateMenuItem("Open scene...", @PickFile, 'O', QUAL_CTRL));
        popup.AddChild(CreateMenuItem("Save scene", @SaveSceneWithExistingName, 'S', QUAL_CTRL));
        popup.AddChild(CreateMenuItem("Save scene as...", @PickFile, 'S', QUAL_SHIFT | QUAL_CTRL));
        popup.AddChild(CreateMenuDivider());

        Menu@ childMenu = CreateMenuItem("Load node", null, SHOW_POPUP_INDICATOR);
        Window@ childPopup = CreatePopup(childMenu);
        childPopup.AddChild(CreateMenuItem("As replicated...", @PickFile));
        childPopup.AddChild(CreateMenuItem("As local...", @PickFile));
        popup.AddChild(childMenu);

        popup.AddChild(CreateMenuItem("Save node as...", @PickFile));
        popup.AddChild(CreateMenuDivider());
        popup.AddChild(CreateMenuItem("Import model...", @PickFile));
        popup.AddChild(CreateMenuItem("Import scene...", @PickFile));
        popup.AddChild(CreateMenuDivider());
        popup.AddChild(CreateMenuItem("Run script...", @PickFile));
        popup.AddChild(CreateMenuItem("Set resource path...", @PickFile));
        popup.AddChild(CreateMenuDivider());
        popup.AddChild(CreateMenuItem("Exit", @Exit));
        FinalizedPopupMenu(popup);
        uiMenuBar.AddChild(menu);
    }

    {
        Menu@ menu = CreateMenu("Edit");
        Window@ popup = menu.popup;
        popup.AddChild(CreateMenuItem("Undo", @Undo, 'Z', QUAL_CTRL));
        popup.AddChild(CreateMenuItem("Redo", @Redo, 'Y', QUAL_CTRL));
        popup.AddChild(CreateMenuDivider());
        popup.AddChild(CreateMenuItem("Cut", @Cut, 'X', QUAL_CTRL));
        popup.AddChild(CreateMenuItem("Copy", @Copy, 'C', QUAL_CTRL));
        popup.AddChild(CreateMenuItem("Paste", @Paste, 'V', QUAL_CTRL));
        popup.AddChild(CreateMenuItem("Delete", @Delete, KEY_DELETE, QUAL_ANY));
        popup.AddChild(CreateMenuItem("Select all", @SelectAll, 'A', QUAL_CTRL));
        popup.AddChild(CreateMenuDivider());
        popup.AddChild(CreateMenuItem("Reset position", @SceneResetPosition));
        popup.AddChild(CreateMenuItem("Reset rotation", @SceneResetRotation));
        popup.AddChild(CreateMenuItem("Reset scale", @SceneResetScale));
        popup.AddChild(CreateMenuItem("Enable/disable", @SceneToggleEnable, 'E', QUAL_CTRL));
        popup.AddChild(CreateMenuItem("Unparent", @SceneUnparent, 'U', QUAL_CTRL));
        popup.AddChild(CreateMenuDivider());
        popup.AddChild(CreateMenuItem("Toggle update", @ToggleUpdate, 'P', QUAL_CTRL));
        popup.AddChild(CreateMenuDivider());
        popup.AddChild(CreateMenuItem("Rebuild navigation data", @SceneRebuildNavigation));
        FinalizedPopupMenu(popup);
        uiMenuBar.AddChild(menu);
    }

    {
        Menu@ menu = CreateMenu("Create");
        Window@ popup = menu.popup;
        popup.AddChild(CreateMenuItem("Replicated node", @PickNode));
        popup.AddChild(CreateMenuItem("Local node", @PickNode));
        popup.AddChild(CreateMenuDivider());

        Menu@ childMenu = CreateMenuItem("Component", null, SHOW_POPUP_INDICATOR);
        Window@ childPopup = CreatePopup(childMenu);
        String[] componentTypes = GetAvailableComponents();
        for (uint i = 0; i < componentTypes.length; ++i)
            childPopup.AddChild(CreateIconizedMenuItem(componentTypes[i], @PickComponent));
        popup.AddChild(childMenu);

        childMenu = CreateMenuItem("Builtin object", null, SHOW_POPUP_INDICATOR);
        childPopup = CreatePopup(childMenu);
        String[] objects = { "Box", "Cone", "Cylinder", "Plane", "Pyramid", "Sphere" };
        for (uint i = 0; i < objects.length; ++i)
            childPopup.AddChild(CreateIconizedMenuItem(objects[i], @PickBuiltinObject, 0, 0, "Node"));
        popup.AddChild(childMenu);
        popup.AddChild(CreateMenuDivider());

        childMenu = CreateMenuItem("New UI-element", null, SHOW_POPUP_INDICATOR);
        childPopup = CreatePopup(childMenu);
        String[] typeNames = { "BorderImage", "Button", "CheckBox", "DropDownList", "LineEdit", "ListView", "Menu", "ScrollBar", "ScrollView", "Slider", "Sprite", "Text", "Window" };
        for (uint i = 0; i < typeNames.length; ++i)
            childPopup.AddChild(CreateIconizedMenuItem(typeNames[i], @PickUIElement));
        childPopup.AddChild(CreateMenuDivider());
        childPopup.AddChild(CreateIconizedMenuItem("UIElement", @PickUIElement));
        popup.AddChild(childMenu);

        FinalizedPopupMenu(popup);
        uiMenuBar.AddChild(menu);
    }

    {
        Menu@ menu = CreateMenu("UI-element");
        Window@ popup = menu.popup;
        popup.AddChild(CreateMenuItem("Open UI-element...", @PickFile, 'O', QUAL_ALT));
        popup.AddChild(CreateMenuItem("Save UI-element", @SaveUIElementWithExistingName, 'S', QUAL_ALT));
        popup.AddChild(CreateMenuItem("Save UI-element as...", @PickFile));
        popup.AddChild(CreateMenuDivider());
        popup.AddChild(CreateMenuItem("Close UI-element", @CloseUIElement, 'C', QUAL_ALT));
        popup.AddChild(CreateMenuItem("Close all UI-elements", @CloseAllUIElements));
        popup.AddChild(CreateMenuDivider());
        popup.AddChild(CreateMenuItem("Load child element...", @PickFile));
        popup.AddChild(CreateMenuItem("Save child element as...", @PickFile));
        popup.AddChild(CreateMenuDivider());
        popup.AddChild(CreateMenuItem("Set default style...", @PickFile));
        FinalizedPopupMenu(popup);
        uiMenuBar.AddChild(menu);
    }

    {
        Menu@ menu = CreateMenu("View");
        Window@ popup = menu.popup;
        popup.AddChild(CreateMenuItem("Hierarchy", @ShowHierarchyWindow, 'H', QUAL_CTRL));
        popup.AddChild(CreateMenuItem("Attribute inspector", @ShowAttributeInspectorWindow, 'I', QUAL_CTRL));
        popup.AddChild(CreateMenuItem("Editor settings", @ShowEditorSettingsDialog));
        popup.AddChild(CreateMenuItem("Editor preferences", @ShowEditorPreferencesDialog));
        popup.AddChild(CreateMenuDivider());
        popup.AddChild(CreateMenuItem("Hide editor", @ToggleUI, KEY_F12, QUAL_ANY));
        FinalizedPopupMenu(popup);
        uiMenuBar.AddChild(menu);
    }

    BorderImage@ spacer = BorderImage("MenuBarSpacer");
    spacer.SetStyle(uiStyle, "EditorMenuBar");
    uiMenuBar.AddChild(spacer);

    BorderImage@ logo = BorderImage("Logo");
    logo.texture = cache.GetResource("Texture2D", "Textures/Logo.png");
    logo.SetFixedWidth(50);
    uiMenuBar.AddChild(logo);
}

bool Exit()
{
    engine.Exit();
    return true;
}

bool PickFile()
{
    Menu@ menu = GetEventSender();
    if (menu is null)
        return false;

    String action = menu.name;
    if (action.empty)
        return false;

    // File (Scene related)
    if (action == "Open scene...")
    {
        CreateFileSelector("Open scene", "Open", "Cancel", uiScenePath, uiSceneFilters, uiSceneFilter);
        SubscribeToEvent(uiFileSelector, "FileSelected", "HandleOpenSceneFile");
    }
    else if (action == "Save scene as..." || action == "Save scene")
    {
        CreateFileSelector("Save scene as", "Save", "Cancel", uiScenePath, uiSceneFilters, uiSceneFilter);
        uiFileSelector.fileName = GetFileNameAndExtension(editorScene.fileName);
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
        if (editNode !is null && editNode !is editorScene)
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
    // UI-element
    else if (action == "Open UI-element...")
    {
        CreateFileSelector("Open UI-element", "Open", "Cancel", uiElementPath, uiElementFilters, uiElementFilter);
        SubscribeToEvent(uiFileSelector, "FileSelected", "HandleOpenUIElementFile");
    }
    else if (action == "Save UI-element as..." || action == "Save UI-element")
    {
        if (editUIElement !is null)
        {
            UIElement@ element = GetTopLevelUIElement(editUIElement);
            if (element is null)
                return false;

            CreateFileSelector("Save UI-element as", "Save", "Cancel", uiElementPath, uiElementFilters, uiElementFilter);
            uiFileSelector.fileName = GetFileNameAndExtension(element.GetVar(FILENAME_VAR).GetString());
            SubscribeToEvent(uiFileSelector, "FileSelected", "HandleSaveUIElementFile");
        }
    }
    else if (action == "Load child element...")
    {
        if (editUIElement !is null)
        {
            CreateFileSelector("Load child element", "Load", "Cancel", uiElementPath, uiElementFilters, uiElementFilter);
            SubscribeToEvent(uiFileSelector, "FileSelected", "HandleLoadChildUIElementFile");
        }
    }
    else if (action == "Save child element as...")
    {
        if (editUIElement !is null)
        {
            CreateFileSelector("Save child element", "Save", "Cancel", uiElementPath, uiElementFilters, uiElementFilter);
            uiFileSelector.fileName = GetFileNameAndExtension(childElementFileName);
            SubscribeToEvent(uiFileSelector, "FileSelected", "HandleSaveChildUIElementFile");
        }
    }
    else if (action == "Set default style...")
    {
        CreateFileSelector("Set default style", "Set", "Cancel", uiElementPath, uiElementFilters, uiElementFilter);
        SubscribeToEvent(uiFileSelector, "FileSelected", "HandleUIElementDefaultStyle");
    }

    return true;
}

bool PickNode()
{
    Menu@ menu = GetEventSender();
    if (menu is null)
        return false;

    String action = menu.name;
    if (action.empty)
        return false;

    CreateNode(action == "Replicated node" ? REPLICATED : LOCAL);
    return true;
}

bool PickComponent()
{
    if (editNodes.empty)
        return false;

    Menu@ menu = GetEventSender();
    if (menu is null)
        return false;

    String action = menu.name;
    if (action.empty)
        return false;

    CreateComponent(action);
    return true;
}

bool PickBuiltinObject()
{
    Menu@ menu = GetEventSender();
    if (menu is null)
        return false;

    String action = menu.name;
    if (action.empty)
        return false;

    CreateBuiltinObject(action);
    return true;
}

bool PickUIElement()
{
    Menu@ menu = GetEventSender();
    if (menu is null)
        return false;

    String action = menu.name;
    if (action.empty)
        return false;

    return NewUIElement(action);
}

void HandleMenuSelected(StringHash eventType, VariantMap& eventData)
{
    Menu@ menu = eventData["Element"].GetUIElement();
    if (menu is null)
        return;

    HandlePopup(menu);

    // Execute the callback if available
    Variant variant = menu.GetVar(CALLBACK_VAR);
    if (!variant.empty)
        menuCallbacks[variant.GetUInt()]();
}

Menu@ CreateMenuItem(const String&in title, MENU_CALLBACK@ callback = null, int accelKey = 0, int accelQual = 0)
{
    Menu@ menu = Menu(title);
    menu.defaultStyle = uiStyle;
    menu.style = uiStyle;
    menu.SetLayout(LM_HORIZONTAL, 0, IntRect(8, 2, 8, 2));
    if (accelKey > 0)
        menu.SetAccelerator(accelKey, accelQual);
    if (callback !is null)
    {
        menu.vars[CALLBACK_VAR] = menuCallbacks.length;
        menuCallbacks.Push(callback);
    }

    Text@ menuText = Text();
    menu.AddChild(menuText);
    menuText.SetStyle(uiStyle, "EditorMenuText");
    menuText.text = title;

    if (accelKey != 0)
    {
        menuText.layoutMode = LM_HORIZONTAL;
        menuText.AddChild(CreateAccelKeyText(accelKey, accelQual));
    }

    return menu;
}

Menu@ CreateIconizedMenuItem(const String&in title, MENU_CALLBACK@ callback = null, int accelKey = 0, int accelQual = 0, const String&in iconType = "")
{
    Menu@ menu = Menu(title);
    menu.defaultStyle = uiStyle;
    menu.style = uiStyle;
    menu.SetLayout(LM_VERTICAL, 0, IntRect(8, 2, 8, 2));
    if (accelKey > 0)
        menu.SetAccelerator(accelKey, accelQual);
    if (callback !is null)
    {
        menu.vars[CALLBACK_VAR] = menuCallbacks.length;
        menuCallbacks.Push(callback);
    }

    Text@ menuText = Text();
    menu.AddChild(menuText);
    menuText.SetStyle(uiStyle, "EditorMenuText");
    menuText.text = title;
    // If icon type is not provided, use the title instead
    IconizeUIElement(menuText, iconType.empty ? title : iconType);

    if (accelKey != 0)
    {
        menuText.layoutMode = LM_HORIZONTAL;
        menuText.AddChild(CreateAccelKeyText(accelKey, accelQual));
    }

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
    Menu@ menu = CreateMenuItem(title);
    menu.SetFixedWidth(menu.width);
    CreatePopup(menu);

    return menu;
}

Text@ CreateAccelKeyText(int accelKey, int accelQual)
{
    Text@ accelKeyText = Text();
    accelKeyText.defaultStyle = uiStyle;
    accelKeyText.SetStyle(uiStyle, "EditorMenuText");
    accelKeyText.horizontalAlignment = HA_RIGHT;
    accelKeyText.indent = 1;

    String text;
    if (accelKey == KEY_DELETE)
        text = "Del";
    else if (accelKey == KEY_SPACE)
        text = "Space";
    // Cannot use range as the key constants below do not appear to be in sequence
    else if (accelKey == KEY_F1)
        text = "F1";
    else if (accelKey == KEY_F2)
        text = "F2";
    else if (accelKey == KEY_F3)
        text = "F3";
    else if (accelKey == KEY_F4)
        text = "F4";
    else if (accelKey == KEY_F5)
        text = "F5";
    else if (accelKey == KEY_F6)
        text = "F6";
    else if (accelKey == KEY_F7)
        text = "F7";
    else if (accelKey == KEY_F8)
        text = "F8";
    else if (accelKey == KEY_F9)
        text = "F9";
    else if (accelKey == KEY_F10)
        text = "F10";
    else if (accelKey == KEY_F11)
        text = "F11";
    else if (accelKey == KEY_F12)
        text = "F12";
    else if (accelKey == SHOW_POPUP_INDICATOR)
        text = ">";
    else
        text.AppendUTF8(accelKey);
    if (accelQual & QUAL_ALT > 0)
        text = "Alt+" + text;
    if (accelQual & QUAL_SHIFT > 0)
        text = "Shift+" + text;
    if (accelQual & QUAL_CTRL > 0)
        text = "Ctrl+" + text;
    accelKeyText.text = text;

    return accelKeyText;
}

void FinalizedPopupMenu(Window@ popup)
{
    // Find the maximum menu text width
    Array<UIElement@> children = popup.GetChildren();
    int maxWidth = 0;
    for (uint i = 0; i < children.length; ++i)
    {
        UIElement@ element = children[i];
        if (element.type != MENU_TYPE)    // Skip if not menu item
            continue;

        int width = element.children[0].width;
        if (width > maxWidth)
            maxWidth = width;
    }

    // Adjust the indent spacing to slightly wider than the maximum width
    maxWidth += 20;
    for (uint i = 0; i < children.length; ++i)
    {
        UIElement@ element = children[i];
        if (element.type != MENU_TYPE)
            continue;
        Menu@ menu = element;

        Text@ menuText = menu.children[0];
        if (menuText.numChildren == 1)    // Skip if menu text does not have accel
            menuText.children[0].indentSpacing = maxWidth;

        // Adjust the popup offset taking the indentation into effect
        if (menu.popup !is null)
            menu.popupOffset = IntVector2(menu.width, 0);
    }
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
    uiFileSelector.window.priority = 1000;    // Ensure when it is visible then it has the highest priority (in front of all others UI)
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
    String sceneName = GetFileNameAndExtension(editorScene.fileName);
    if (sceneName.empty || sceneName == TEMP_SCENE_NAME)
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

void HandleOpenUIElementFile(StringHash eventType, VariantMap& eventData)
{
    CloseFileSelector(uiElementFilter, uiElementPath);
    OpenUIElement(ExtractFileName(eventData));
}

void HandleSaveUIElementFile(StringHash eventType, VariantMap& eventData)
{
    CloseFileSelector(uiElementFilter, uiElementPath);
    SaveUIElement(ExtractFileName(eventData));
}

void HandleLoadChildUIElementFile(StringHash eventType, VariantMap& eventData)
{
    CloseFileSelector(uiElementFilter, uiElementPath);
    LoadChildUIElement(ExtractFileName(eventData));
}

void HandleSaveChildUIElementFile(StringHash eventType, VariantMap& eventData)
{
    CloseFileSelector(uiElementFilter, uiElementPath);
    SaveChildUIElement(ExtractFileName(eventData));
}

void HandleUIElementDefaultStyle(StringHash eventType, VariantMap& eventData)
{
    CloseFileSelector(uiElementFilter, uiElementPath);
    SetUIElementDefaultStyle(ExtractFileName(eventData));
}

void HandleKeyDown(StringHash eventType, VariantMap& eventData)
{
    int key = eventData["Key"].GetInt();

    if (key == KEY_ESC)
    {
        if (uiHidden)
            UnhideUI();
        else if (console.visible)
            console.visible = false;
        else
        {
            UIElement@ front = ui.frontElement;
            if (front is settingsDialog || front is preferencesDialog)
            {
                ui.focusElement = null;
                front.visible = false;
            }
        }
    }

    // Ignore other keys when UI has a modal element
    else if (ui.HasModalElement())
        return;

    else if (key == KEY_F1)
        console.Toggle();
    else if (key == KEY_F2)
        ToggleRenderingDebug();
    else if (key == KEY_F3)
        TogglePhysicsDebug();
    else if (key == KEY_F4)
        ToggleOctreeDebug();

    else if (eventData["Qualifiers"].GetInt() == QUAL_CTRL)
    {
        if (key == '1')
            editMode = EDIT_MOVE;
        else if (key == '2')
            editMode = EDIT_ROTATE;
        else if (key == '3')
            editMode = EDIT_SCALE;
        else if (key == '4')
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

void UnfadeUI()
{
    FadeUI(false);
}

void FadeUI(bool fade = true)
{
    if (uiHidden || uiFaded == fade)
        return;

    float opacity = (uiFaded = fade) ? uiMinOpacity : uiMaxOpacity;
    Array<UIElement@> children = ui.root.GetChildren();
    for (uint i = 0; i < children.length; ++i)
    {
        // Texts, popup&modal windows (which are anyway only in ui.modalRoot), and editorUIElement are excluded
        if (children[i].type != TEXT_TYPE && children[i] !is editorUIElement)
            children[i].opacity = opacity;
    }
}

bool ToggleUI()
{
    HideUI(!uiHidden);
    return true;
}

void UnhideUI()
{
    HideUI(false);
}

void HideUI(bool hide = true)
{
    if (uiHidden == hide)
        return;

    bool visible = !(uiHidden = hide);
    Array<UIElement@> children = ui.root.GetChildren();
    for (uint i = 0; i < children.length; ++i)
    {
        // Cursor and editorUIElement are excluded
        if (children[i].type != CURSOR_TYPE && children[i] !is editorUIElement)
        {
            if (visible)
            {
                if (!children[i].visible)
                    children[i].visible = children[i].vars["HideUI"].GetBool();
            }
            else
            {
                children[i].vars["HideUI"] = children[i].visible;
                children[i].visible = false;
            }
        }
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
        if (element.vars[INDENT_MODIFIED_BY_ICON_VAR].GetBool())
            element.indent = 0;

        return;
    }

    // The UI element must itself has been indented to reserve the space for the icon
    if (element.indent == 0)
    {
        element.indent = 1;
        element.vars[INDENT_MODIFIED_BY_ICON_VAR] = true;
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

void SetIconEnabledColor(UIElement@ element, bool enabled, bool partial = false)
{
    BorderImage@ icon = element.GetChild("Icon");
    if (icon !is null)
    {
        if (partial)
        {
            icon.colors[C_TOPLEFT] = Color(1,1,1,1);
            icon.colors[C_BOTTOMLEFT] = Color(1,1,1,1);
            icon.colors[C_TOPRIGHT] = Color(1,0,0,1);
            icon.colors[C_BOTTOMRIGHT] = Color(1,0,0,1);
        }
        else
            icon.color = enabled ? Color(1,1,1,1) : Color(1,0,0,1);
    }
}

void UpdateDirtyUI()
{
    // Perform some event-triggered updates latently in case a large hierarchy was changed
    if (attributesFullDirty || attributesDirty)
        UpdateAttributeInspector(attributesFullDirty);
}
