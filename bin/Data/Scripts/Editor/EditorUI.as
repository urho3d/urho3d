// Urho3D editor user interface

XMLFile@ uiStyle;
XMLFile@ iconStyle;
UIElement@ uiMenuBar;
UIElement@ quickMenu;
Menu@ recentSceneMenu;
Window@ mruScenesPopup;
Array<QuickMenuItem@> quickMenuItems;
FileSelector@ uiFileSelector;
String consoleCommandInterpreter;
Window@ contextMenu;
uint stepColoringGroupUpdate = 100; // ms
uint timeToNextColoringGroupUpdate = 0;

const StringHash UI_ELEMENT_TYPE("UIElement");
const StringHash WINDOW_TYPE("Window");
const StringHash MENU_TYPE("Menu");
const StringHash TEXT_TYPE("Text");
const StringHash CURSOR_TYPE("Cursor");

const String AUTO_STYLE("");    // Empty string means auto style, i.e. applying style according to UI-element's type automatically
const String TEMP_SCENE_NAME("_tempscene_.xml");
const String TEMP_BINARY_SCENE_NAME("_tempscene_.bin");
const StringHash CALLBACK_VAR("Callback");
const StringHash INDENT_MODIFIED_BY_ICON_VAR("IconIndented");

const StringHash VAR_CONTEXT_MENU_HANDLER("ContextMenuHandler");

const int SHOW_POPUP_INDICATOR = -1;
const uint MAX_QUICK_MENU_ITEMS = 10;

const uint maxRecentSceneCount = 5;

Array<String> uiSceneFilters = {"*.xml", "*.json", "*.bin", "*.*"};
Array<String> uiElementFilters = {"*.xml"};
Array<String> uiAllFilters = {"*.*"};
Array<String> uiScriptFilters = {"*.as", "*.*"};
Array<String> uiParticleFilters = {"*.xml"};
Array<String> uiRenderPathFilters = {"*.xml"};
Array<String> uiExportPathFilters = {"*.obj"};
uint uiSceneFilter = 0;
uint uiElementFilter = 0;
uint uiNodeFilter = 0;
uint uiImportFilter = 0;
uint uiScriptFilter = 0;
uint uiParticleFilter = 0;
uint uiRenderPathFilter = 0;
uint uiExportFilter = 0;
String uiScenePath = fileSystem.programDir + "Data/Scenes";
String uiElementPath = fileSystem.programDir + "Data/UI";
String uiNodePath = fileSystem.programDir + "Data/Objects";
String uiImportPath;
String uiExportPath;
String uiScriptPath = fileSystem.programDir + "Data/Scripts";
String uiParticlePath = fileSystem.programDir + "Data/Particles";
String uiRenderPathPath = fileSystem.programDir + "CoreData/RenderPaths";
Array<String> uiRecentScenes;
String screenshotDir = fileSystem.programDir + "Screenshots";

bool uiFaded = false;
float uiMinOpacity = 0.3;
float uiMaxOpacity = 0.7;
bool uiHidden = false;

void CreateUI()
{
    // Remove all existing UI content in case we are reloading the editor script
    /// \todo The console will not be properly recreated as it has already been created once
    ui.root.RemoveAllChildren();

    uiStyle = GetEditorUIXMLFile("UI/DefaultStyle.xml");
    ui.root.defaultStyle = uiStyle;
    iconStyle = GetEditorUIXMLFile("UI/EditorIcons.xml");

    CreateCursor();
    CreateMenuBar();
    CreateToolBar();
    CreateSecondaryToolBar();
    CreateQuickMenu();
    CreateContextMenu();
    CreateHierarchyWindow();
    CreateAttributeInspectorWindow();
    CreateEditorSettingsDialog();
    CreateEditorPreferencesDialog();
    CreateMaterialEditor();
    CreateParticleEffectEditor();
    CreateSpawnEditor();
    CreateSoundTypeEditor();
    CreateStatsBar();
    CreateConsole();
    CreateDebugHud();
    CreateResourceBrowser();
    CreateCamera();
    CreateLayerEditor();
    CreateColorWheel();

    SubscribeToEvent("ScreenMode", "ResizeUI");
    SubscribeToEvent("MenuSelected", "HandleMenuSelected");
    SubscribeToEvent("ChangeLanguage", "HandleChangeLanguage");

    SubscribeToEvent("WheelChangeColor", "HandleWheelChangeColor");
    SubscribeToEvent("WheelSelectColor", "HandleWheelSelectColor");
    SubscribeToEvent("WheelDiscardColor", "HandleWheelDiscardColor");
}

void ResizeUI()
{
    // Resize menu bar
    uiMenuBar.SetFixedWidth(graphics.width);

    // Resize tool bar
    toolBar.SetFixedWidth(graphics.width);

    // Resize secondary tool bar
    secondaryToolBar.SetFixedHeight(graphics.height);

    // Relayout windows
    Array<UIElement@> children = ui.root.GetChildren();
    for (uint i = 0; i < children.length; ++i)
    {
        if (children[i].type == WINDOW_TYPE)
            AdjustPosition(children[i]);
    }

    // Relayout root UI element
    editorUIElement.SetSize(graphics.width, graphics.height);

    // Set new viewport area and reset the viewport layout
    viewportArea = IntRect(0, 0, graphics.width, graphics.height);
    SetViewportMode(viewportMode);
}

void AdjustPosition(Window@ window)
{
    IntVector2 position = window.position;
    IntVector2 size = window.size;
    IntVector2 extend = position + size;
    if (extend.x > graphics.width)
        position.x = Max(10, graphics.width - size.x - 10);
    if (extend.y > graphics.height)
        position.y = Max(100, graphics.height - size.y - 10);
    window.position = position;
}

void CreateCursor()
{
    Cursor@ cursor = Cursor("Cursor");
    cursor.SetStyleAuto(uiStyle);
    cursor.SetPosition(graphics.width / 2, graphics.height / 2);
    ui.cursor = cursor;
    if (GetPlatform() == "Android" || GetPlatform() == "iOS")
        ui.cursor.visible = false;
}

// AngelScript does not support closures (yet), but funcdef should do just fine as a workaround for a few cases here for now
funcdef bool MENU_CALLBACK();
Array<MENU_CALLBACK@> menuCallbacks;
MENU_CALLBACK@ messageBoxCallback;

void HandleQuickSearchChange(StringHash eventType, VariantMap& eventData)
{
    LineEdit@ search = eventData["Element"].GetPtr();
    if (search is null)
        return;

    PerformQuickMenuSearch(search.text.ToLower().Trimmed());
}

void HandleQuickSearchFinish(StringHash eventType, VariantMap& eventData)
{
    Menu@ menu = quickMenu.GetChild("ResultsMenu", true);
    if (menu is null)
        return;

    String query = eventData["Text"].GetString();
    if (query.length <= 0)
        return;
    Array<QuickMenuItem@> filtered;
    {
        QuickMenuItem@ qi;
        for (uint x=0; x < quickMenuItems.length; x++)
        {
            @qi = quickMenuItems[x];
            int find = qi.action.Find(query, 0, false);
            if (find > -1)
            {
                qi.sortScore = find;
                filtered.Push(qi);
            }
        }
    }

    filtered.Sort();
    if (!filtered.empty)
    {
        VariantMap data;
        Menu@ item = CreateMenuItem(filtered[0].action, filtered[0].callback);
        data["Element"] = item;
        item.SendEvent("MenuSelected", data);
    }
}

void PerformQuickMenuSearch(const String&in query)
{
    Menu@ menu = quickMenu.GetChild("ResultsMenu", true);
    if (menu is null)
        return;

    menu.RemoveAllChildren();
    uint limit = 0;

    if (query.length > 0)
    {
        int lastIndex = 0;
        uint score = 0;
        int index = 0;

        Array<QuickMenuItem@> filtered;
        {
            QuickMenuItem@ qi;
            for (uint x=0; x < quickMenuItems.length; x++)
            {
                @qi = quickMenuItems[x];
                int find = qi.action.Find(query, 0, false);
                if (find > -1)
                {
                    qi.sortScore = find;
                    filtered.Push(qi);
                }
            }
        }

        filtered.Sort();

        {
            QuickMenuItem@ qi;
            limit = filtered.length > MAX_QUICK_MENU_ITEMS ? MAX_QUICK_MENU_ITEMS : filtered.length;
            for (uint x=0; x < limit; x++)
            {
                @qi = filtered[x];
                Menu@ item = CreateMenuItem(qi.action, qi.callback);
                item.SetMaxSize(1000,16);
                menu.AddChild(item);
            }
        }
    }

    menu.visible = limit > 0;
    menu.SetFixedHeight(limit * 16);
    quickMenu.BringToFront();
    quickMenu.SetFixedHeight(limit*16 + 62 + (menu.visible ? 6 : 0));
}

class QuickMenuItem
{
    String action;
    MENU_CALLBACK@ callback;
    uint sortScore = 0;
    QuickMenuItem(){}
    QuickMenuItem(String action, MENU_CALLBACK@ callback)
    {
        this.action = action;
        this.callback = callback;
    }
    int opCmp(QuickMenuItem@ b)
    {
        return sortScore - b.sortScore;
    }
}

/// Create popup search menu.
void CreateQuickMenu()
{
    if (quickMenu !is null)
        return;

    quickMenu = LoadEditorUI("UI/EditorQuickMenu.xml");
    quickMenu.enabled = false;
    quickMenu.visible = false;
    quickMenu.opacity = uiMaxOpacity;

    // Handle a dummy search in the quick menu to finalize its initial size to empty
    PerformQuickMenuSearch("");

    ui.root.AddChild(quickMenu);
    LineEdit@ search = quickMenu.GetChild("Search", true);
    SubscribeToEvent(search, "TextChanged", "HandleQuickSearchChange");
    SubscribeToEvent(search, "TextFinished", "HandleQuickSearchFinish");
    UIElement@ closeButton = quickMenu.GetChild("CloseButton", true);
    SubscribeToEvent(closeButton, "Pressed", "ToggleQuickMenu");
}

void ToggleQuickMenu()
{
    quickMenu.enabled = !quickMenu.enabled && ui.cursor.visible;
    quickMenu.visible = quickMenu.enabled;
    if (quickMenu.enabled)
    {
        quickMenu.position = ui.cursorPosition - IntVector2(20,70);
        LineEdit@ search = quickMenu.GetChild("Search", true);
        search.text = "";
        search.focus = true;
    }
}

/// Create top menu bar.
void CreateMenuBar()
{
    uiMenuBar = BorderImage("MenuBar");
    ui.root.AddChild(uiMenuBar);
    uiMenuBar.enabled = true;
    uiMenuBar.style = "EditorMenuBar";
    uiMenuBar.SetLayout(LM_HORIZONTAL);
    uiMenuBar.opacity = uiMaxOpacity;
    uiMenuBar.SetFixedWidth(graphics.width);

    {
        Menu@ menu = CreateMenu("File");
        Window@ popup = menu.popup;
        popup.AddChild(CreateMenuItem("New scene", @ResetScene, 'N', QUAL_SHIFT | QUAL_CTRL));
        popup.AddChild(CreateMenuItem("Open scene...", @PickFile, 'O', QUAL_CTRL));
        popup.AddChild(CreateMenuItem("Save scene", @SaveSceneWithExistingName, 'S', QUAL_CTRL));
        popup.AddChild(CreateMenuItem("Save scene as...", @PickFile, 'S', QUAL_SHIFT | QUAL_CTRL));
        recentSceneMenu = CreateMenuItem("Open recent scene", null, SHOW_POPUP_INDICATOR);
        popup.AddChild(recentSceneMenu);
        mruScenesPopup = CreatePopup(recentSceneMenu);
        PopulateMruScenes();
        CreateChildDivider(popup);

        Menu@ childMenu = CreateMenuItem("menu Load node", null, SHOW_POPUP_INDICATOR);
        Window@ childPopup = CreatePopup(childMenu);
        childPopup.AddChild(CreateMenuItem("As replicated...", @PickFile, 0, 0, true, "Load node as replicated..."));
        childPopup.AddChild(CreateMenuItem("As local...", @PickFile, 0, 0, true, "Load node as local..."));
        popup.AddChild(childMenu);

        popup.AddChild(CreateMenuItem("Save node as...", @PickFile));
        CreateChildDivider(popup);
        popup.AddChild(CreateMenuItem("Import model...", @PickFile));
        popup.AddChild(CreateMenuItem("Import scene...", @PickFile));
        popup.AddChild(CreateMenuItem("Import animation...", @PickFile));
        CreateChildDivider(popup);
        popup.AddChild(CreateMenuItem("Export scene to OBJ...", @PickFile));
        popup.AddChild(CreateMenuItem("Export selected to OBJ...", @PickFile));
        CreateChildDivider(popup);
        popup.AddChild(CreateMenuItem("Run script...", @PickFile));
        popup.AddChild(CreateMenuItem("Set resource path...", @PickFile));
        CreateChildDivider(popup);
        popup.AddChild(CreateMenuItem("Exit", @Exit));
        FinalizedPopupMenu(popup);
        uiMenuBar.AddChild(menu);
    }

    {
        Menu@ menu = CreateMenu("Edit");
        Window@ popup = menu.popup;
        popup.AddChild(CreateMenuItem("Undo", @Undo, 'Z', QUAL_CTRL));
        popup.AddChild(CreateMenuItem("Redo", @Redo, 'Y', QUAL_CTRL));
        CreateChildDivider(popup);
        popup.AddChild(CreateMenuItem("Cut", @Cut, 'X', QUAL_CTRL));

        if (hotKeyMode == HOTKEYS_MODE_STANDARD)
            popup.AddChild(CreateMenuItem("Duplicate", @Duplicate, 'D', QUAL_CTRL));
        else if (hotKeyMode == HOTKEYS_MODE_BLENDER)
            popup.AddChild(CreateMenuItem("Duplicate", @Duplicate, 'D', QUAL_SHIFT));

        popup.AddChild(CreateMenuItem("Copy", @Copy, 'C', QUAL_CTRL));
        popup.AddChild(CreateMenuItem("Paste", @Paste, 'V', QUAL_CTRL));

        if (hotKeyMode == HOTKEYS_MODE_STANDARD)
            popup.AddChild(CreateMenuItem("Delete", @Delete, KEY_DELETE, QUAL_ANY));
        else if (hotKeyMode == HOTKEYS_MODE_BLENDER)
            popup.AddChild(CreateMenuItem("Delete", @BlenderModeDelete, 'X', QUAL_ANY));

        popup.AddChild(CreateMenuItem("Select all", @SelectAll, 'A', QUAL_CTRL));
        popup.AddChild(CreateMenuItem("Deselect all", @DeselectAll, 'A', QUAL_SHIFT | QUAL_CTRL));

        CreateChildDivider(popup);
        popup.AddChild(CreateMenuItem("Reset to default", @ResetToDefault));
        CreateChildDivider(popup);

        if (hotKeyMode == HOTKEYS_MODE_STANDARD)
        {
            popup.AddChild(CreateMenuItem("Reset position", @SceneResetPosition, '1' , QUAL_ALT));
            popup.AddChild(CreateMenuItem("Reset rotation", @SceneResetRotation, '2' , QUAL_ALT));
            popup.AddChild(CreateMenuItem("Reset scale", @SceneResetScale, '3' , QUAL_ALT));
            popup.AddChild(CreateMenuItem("Reset transform", @SceneResetTransform, 'Q' , QUAL_ALT));
        }
        else if (hotKeyMode == HOTKEYS_MODE_BLENDER)
        {
            popup.AddChild(CreateMenuItem("Reset position", @SceneResetPosition, 'G' , QUAL_ALT));
            popup.AddChild(CreateMenuItem("Reset rotation", @SceneResetRotation, 'R', QUAL_ALT));
            popup.AddChild(CreateMenuItem("Reset scale", @SceneResetScale, 'S', QUAL_ALT));
            popup.AddChild(CreateMenuItem("Reset transform", @SceneResetTransform, 'Q' , QUAL_ALT));
        }

        if (hotKeyMode == HOTKEYS_MODE_STANDARD)
        {
            popup.AddChild(CreateMenuItem("Enable/disable", @SceneToggleEnable, 'E', QUAL_CTRL));
            popup.AddChild(CreateMenuItem("Enable all", @SceneEnableAllNodes, 'E', QUAL_ALT));
        }
        else if (hotKeyMode == HOTKEYS_MODE_BLENDER)
        {
            popup.AddChild(CreateMenuItem("Enable/disable", @SceneToggleEnable, 'H'));
            popup.AddChild(CreateMenuItem("Enable all", @SceneEnableAllNodes, 'H', QUAL_ALT));
        }

        if (hotKeyMode == HOTKEYS_MODE_STANDARD)
            popup.AddChild(CreateMenuItem("Unparent", @SceneUnparent, 'U', QUAL_CTRL));
        else if (hotKeyMode == HOTKEYS_MODE_BLENDER)
            popup.AddChild(CreateMenuItem("Unparent", @SceneUnparent, 'P', QUAL_ALT));

        if (hotKeyMode == HOTKEYS_MODE_STANDARD)
            popup.AddChild(CreateMenuItem("Parent to last", @NodesParentToLastSelected, 'U'));
        else if (hotKeyMode == HOTKEYS_MODE_BLENDER)
            popup.AddChild(CreateMenuItem("Parent to last", @NodesParentToLastSelected, 'P', QUAL_CTRL));

        CreateChildDivider(popup);

        if (hotKeyMode == HOTKEYS_MODE_STANDARD)
            popup.AddChild(CreateMenuItem("Toggle update", @ToggleSceneUpdate, 'P', QUAL_CTRL));
        //else if (hotKeyMode == HOT_KEYS_MODE_BLENDER)
        //    popup.AddChild(CreateMenuItem("Toggle update", @ToggleSceneUpdate, 'P', QUAL_CTRL));

        if (hotKeyMode == HOTKEYS_MODE_BLENDER)
        {
             popup.AddChild(CreateMenuItem("Move to layer", @ShowLayerMover, 'M'));
             popup.AddChild(CreateMenuItem("Smart Duplicate", @SceneSmartDuplicateNode, 'D', QUAL_ALT));
             popup.AddChild(CreateMenuItem("View closer", @ViewCloser, KEY_KP_PERIOD));
        }
        popup.AddChild(CreateMenuItem("Color wheel", @ColorWheelBuildMenuSelectTypeColor, 'W', QUAL_ALT));
        popup.AddChild(CreateMenuItem("Show components icons", @ViewDebugIcons, 'I', QUAL_ALT));

        CreateChildDivider(popup);

        popup.AddChild(CreateMenuItem("Stop test animation", @StopTestAnimation));
        CreateChildDivider(popup);
        popup.AddChild(CreateMenuItem("Rebuild navigation data", @SceneRebuildNavigation));
        popup.AddChild(CreateMenuItem("Render Zone Cubemap", @SceneRenderZoneCubemaps));
        popup.AddChild(CreateMenuItem("Add children to SM-group", @SceneAddChildrenStaticModelGroup));
        Menu@ childMenu = CreateMenuItem("Set children as spline path", null, SHOW_POPUP_INDICATOR);
        Window@ childPopup = CreatePopup(childMenu);
        childPopup.AddChild(CreateMenuItem("Non-cyclic", @SetSplinePath, 0, 0, true, "Set non-cyclic spline path"));
        childPopup.AddChild(CreateMenuItem("Cyclic", @SetSplinePath, 0, 0, true, "Set cyclic spline path"));
        popup.AddChild(childMenu);
        FinalizedPopupMenu(popup);
        uiMenuBar.AddChild(menu);
    }

    {
        Menu@ menu = CreateMenu("Create");
        Window@ popup = menu.popup;
        popup.AddChild(CreateMenuItem("Replicated node", @PickNode, 0, 0, true, "Create Replicated node"));
        popup.AddChild(CreateMenuItem("Local node", @PickNode, 0, 0, true, "Create Local node"));
        CreateChildDivider(popup);

        Menu@ childMenu = CreateMenuItem("Component", null, SHOW_POPUP_INDICATOR);
        Window@ childPopup = CreatePopup(childMenu);
        String[] objectCategories = GetObjectCategories();
        for (uint i = 0; i < objectCategories.length; ++i)
        {
            // Skip the UI category for the component menus
            if (objectCategories[i] == "UI")
                continue;

            Menu@ m = CreateMenuItem(objectCategories[i], null, SHOW_POPUP_INDICATOR);
            Window@ p = CreatePopup(m);
            String[] componentTypes = GetObjectsByCategory(objectCategories[i]);
            for (uint j = 0; j < componentTypes.length; ++j)
                p.AddChild(CreateIconizedMenuItem(componentTypes[j], @PickComponent, 0, 0, "", true, "Create " + componentTypes[j]));
            childPopup.AddChild(m);
        }
        FinalizedPopupMenu(childPopup);
        popup.AddChild(childMenu);

        childMenu = CreateMenuItem("Builtin object", null, SHOW_POPUP_INDICATOR);
        childPopup = CreatePopup(childMenu);
        String[] objects = { "Box", "Cone", "Cylinder", "Plane", "Pyramid", "Sphere", "TeaPot", "Torus" };
        for (uint i = 0; i < objects.length; ++i)
            childPopup.AddChild(CreateIconizedMenuItem(objects[i], @PickBuiltinObject, 0, 0, "Node", true, "Create " + objects[i]));
        popup.AddChild(childMenu);
        CreateChildDivider(popup);

        childMenu = CreateMenuItem("UI-element", null, SHOW_POPUP_INDICATOR);
        childPopup = CreatePopup(childMenu);
        String[] uiElementTypes = GetObjectsByCategory("UI");
        for (uint i = 0; i < uiElementTypes.length; ++i)
        {
            if (uiElementTypes[i] != "UIElement")
                childPopup.AddChild(CreateIconizedMenuItem(uiElementTypes[i], @PickUIElement, 0, 0, "", true, "Create " + uiElementTypes[i]));
        }
        CreateChildDivider(childPopup);
        childPopup.AddChild(CreateIconizedMenuItem("UIElement", @PickUIElement));
        popup.AddChild(childMenu);

        FinalizedPopupMenu(popup);
        uiMenuBar.AddChild(menu);
    }

    {
        Menu@ menu = CreateMenu("UI-layout");
        Window@ popup = menu.popup;
        popup.AddChild(CreateMenuItem("Open UI-layout...", @PickFile, 'O', QUAL_ALT));
        popup.AddChild(CreateMenuItem("Save UI-layout", @SaveUILayoutWithExistingName, 'S', QUAL_ALT));
        popup.AddChild(CreateMenuItem("Save UI-layout as...", @PickFile));
        CreateChildDivider(popup);
        popup.AddChild(CreateMenuItem("Close UI-layout", @CloseUILayout, 'C', QUAL_ALT));
        popup.AddChild(CreateMenuItem("Close all UI-layouts", @CloseAllUILayouts));
        CreateChildDivider(popup);
        popup.AddChild(CreateMenuItem("Load child element...", @PickFile));
        popup.AddChild(CreateMenuItem("Save child element as...", @PickFile));
        CreateChildDivider(popup);
        popup.AddChild(CreateMenuItem("Set default style...", @PickFile));
        FinalizedPopupMenu(popup);
        uiMenuBar.AddChild(menu);
    }

    {
        Menu@ menu = CreateMenu("View");
        Window@ popup = menu.popup;
        popup.AddChild(CreateMenuItem("Hierarchy", @ToggleHierarchyWindow, 'H', QUAL_CTRL));
        popup.AddChild(CreateMenuItem("Attribute inspector", @ToggleAttributeInspectorWindow, 'I', QUAL_CTRL));
        popup.AddChild(CreateMenuItem("Resource browser", @ToggleResourceBrowserWindow, 'B', QUAL_CTRL));
        popup.AddChild(CreateMenuItem("Material editor", @ToggleMaterialEditor));
        popup.AddChild(CreateMenuItem("Particle editor", @ToggleParticleEffectEditor));
        popup.AddChild(CreateMenuItem("Spawn editor", @ToggleSpawnEditor));
        popup.AddChild(CreateMenuItem("Sound Type editor", @ToggleSoundTypeEditor));
        popup.AddChild(CreateMenuItem("Editor settings", @ToggleEditorSettingsDialog));
        popup.AddChild(CreateMenuItem("Editor preferences", @ToggleEditorPreferencesDialog));
        CreateChildDivider(popup);
        popup.AddChild(CreateMenuItem("Hide editor", @ToggleUI, KEY_F12, QUAL_ANY));
        FinalizedPopupMenu(popup);
        uiMenuBar.AddChild(menu);
    }

    BorderImage@ spacer = BorderImage("MenuBarSpacer");
    uiMenuBar.AddChild(spacer);
    spacer.style = "EditorMenuBar";

    BorderImage@ logo = BorderImage("Logo");
    logo.texture = cache.GetResource("Texture2D", "Textures/Logo.png");
    logo.SetFixedWidth(64);
    uiMenuBar.AddChild(logo);
}

bool Exit()
{
    ui.cursor.shape = CS_BUSY;

    if (messageBoxCallback is null)
    {
        String message;
        if (sceneModified)
            message = "Scene has been modified.\n";

        bool uiLayoutModified = false;
        for (uint i = 0; i < editorUIElement.numChildren; ++i)
        {
            UIElement@ element = editorUIElement.children[i];
            if (element !is null && element.vars[MODIFIED_VAR].GetBool())
            {
                uiLayoutModified = true;
                message += "UI layout has been modified.\n";
                break;
            }
        }

        if (sceneModified || uiLayoutModified)
        {
            MessageBox@ messageBox = MessageBox(message + "Continue to exit?", "Warning");
            if (messageBox.window !is null)
            {
                Button@ cancelButton = messageBox.window.GetChild("CancelButton", true);
                cancelButton.visible = true;
                cancelButton.focus = true;
                SubscribeToEvent(messageBox, "MessageACK", "HandleMessageAcknowledgement");
                messageBoxCallback = @Exit;
                return false;
            }
        }
    }
    else
        messageBoxCallback = null;

    engine.Exit();
    return true;
}

void HandleExitRequested()
{
    if (!ui.HasModalElement())
        Exit();
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
    else if (action == "As replicated..." || action == "Load node as replicated...")
    {
        instantiateMode = REPLICATED;
        CreateFileSelector("fileSelector Load node", "Load", "Cancel", uiNodePath, uiSceneFilters, uiNodeFilter);
        SubscribeToEvent(uiFileSelector, "FileSelected", "HandleLoadNodeFile");
    }
    else if (action == "As local..." || action == "Load node as local...")
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
    else if (action == "Import animation...")
    {
        CreateFileSelector("Import animation", "Import", "Cancel", uiImportPath, uiAllFilters, uiImportFilter);
        SubscribeToEvent(uiFileSelector, "FileSelected", "HandleImportAnimation");
    }
    else if (action == "Import scene...")
    {
        CreateFileSelector("Import scene", "Import", "Cancel", uiImportPath, uiAllFilters, uiImportFilter);
        SubscribeToEvent(uiFileSelector, "FileSelected", "HandleImportScene");
    }
    else if (action == "Export scene to OBJ..." || action == "Export selected to OBJ...")
    {
        // Set these up together to share the "export settings" options
        if (action == "Export scene to OBJ...")
        {
            CreateFileSelector("Export scene to OBJ", "Save", "Cancel", uiExportPath, uiExportPathFilters, uiExportFilter);
            SubscribeToEvent(uiFileSelector, "FileSelected", "HandleExportSceneOBJ");
        }
        else if (action == "Export selected to OBJ...")
        {
            CreateFileSelector("Export selected to OBJ", "Save", "Cancel", uiExportPath, uiExportPathFilters, uiExportFilter);
            SubscribeToEvent(uiFileSelector, "FileSelected", "HandleExportSelectedOBJ");
        }

        Window@ window = uiFileSelector.window;

            UIElement@ optionsGroup = UIElement();
            optionsGroup.maxHeight = 30;
            optionsGroup.layoutMode = LM_HORIZONTAL;
            window.defaultStyle = uiStyle;
            window.style = AUTO_STYLE;

                CheckBox@ checkRightHanded = CheckBox();
                checkRightHanded.checked = objExportRightHanded_;
                checkRightHanded.defaultStyle = uiStyle;
                checkRightHanded.style = AUTO_STYLE;
                SubscribeToEvent(checkRightHanded, "Toggled", "HandleOBJRightHandedChanged");
                optionsGroup.AddChild(checkRightHanded);

                    Text@ lblRightHanded = Text();
                    lblRightHanded.defaultStyle = uiStyle;
                    lblRightHanded.style = AUTO_STYLE;
                    lblRightHanded.text = "  Right handed";
                    optionsGroup.AddChild(lblRightHanded);

                CheckBox@ checkZUp = CheckBox();
                checkZUp.checked = objExportZUp_;
                checkZUp.defaultStyle = uiStyle;
                checkZUp.style = AUTO_STYLE;
                SubscribeToEvent(checkZUp, "Toggled", "HandleOBJZUpChanged");
                optionsGroup.AddChild(checkZUp);

                    Text@ lblZUp = Text();
                    lblZUp.defaultStyle = uiStyle;
                    lblZUp.style = AUTO_STYLE;
                    lblZUp.text = " Z Axis Up";
                    optionsGroup.AddChild(lblZUp);

            window.AddChild(optionsGroup);
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
    else if (action == "Open UI-layout...")
    {
        CreateFileSelector("Open UI-layout", "Open", "Cancel", uiElementPath, uiElementFilters, uiElementFilter);
        SubscribeToEvent(uiFileSelector, "FileSelected", "HandleOpenUILayoutFile");
    }
    else if (action == "Save UI-layout as..." || action == "Save UI-layout")
    {
        if (editUIElement !is null)
        {
            UIElement@ element = GetTopLevelUIElement(editUIElement);
            if (element is null)
                return false;

            CreateFileSelector("Save UI-layout as", "Save", "Cancel", uiElementPath, uiElementFilters, uiElementFilter);
            uiFileSelector.fileName = GetFileNameAndExtension(element.GetVar(FILENAME_VAR).GetString());
            SubscribeToEvent(uiFileSelector, "FileSelected", "HandleSaveUILayoutFile");
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
            uiFileSelector.fileName = GetFileNameAndExtension(editUIElement.GetVar(CHILD_ELEMENT_FILENAME_VAR).GetString());
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

    String action = GetActionName(menu.name);
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

    String action = GetActionName(menu.name);
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

    String action = GetActionName(menu.name);
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

    String action = GetActionName(menu.name);
    if (action.empty)
        return false;

    return NewUIElement(action);
}

// When calling items from the quick menu, they have "Create" prepended for clarity. Strip that now to get the object name to create
String GetActionName(const String&in name)
{
    if (name.StartsWith("Create"))
        return name.Substring(7);
    else
        return name;
}

void HandleMenuSelected(StringHash eventType, VariantMap& eventData)
{
    Menu@ menu = eventData["Element"].GetPtr();
    if (menu is null)
        return;

    HandlePopup(menu);

    quickMenu.visible = false;
    quickMenu.enabled = false;

    // Execute the callback if available
    Variant variant = menu.GetVar(CALLBACK_VAR);
    if (!variant.empty)
        menuCallbacks[variant.GetUInt()]();
}

Menu@ CreateMenuItem(const String&in title, MENU_CALLBACK@ callback = null, int accelKey = 0, int accelQual = 0, bool addToQuickMenu = true, String quickMenuText="", bool autoLocalize = true)
{
    Menu@ menu = Menu(title);
    menu.defaultStyle = uiStyle;
    menu.style = AUTO_STYLE;
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
    menuText.style = "EditorMenuText";
    menuText.text = title;
    menuText.autoLocalizable = autoLocalize;

    if (addToQuickMenu)
        AddQuickMenuItem(callback, quickMenuText.empty ? title : quickMenuText);

    if (accelKey != 0)
    {
        UIElement@ spacer = UIElement();
        spacer.minWidth = menuText.indentSpacing;
        spacer.height = menuText.height;
        menu.AddChild(spacer);
        menu.AddChild(CreateAccelKeyText(accelKey, accelQual));
    }

    return menu;
}

void AddQuickMenuItem(MENU_CALLBACK@ callback, String text)
{
    if (callback is null)
        return;

    bool exists = false;
    for (uint i=0;i<quickMenuItems.length;++i)
    {
        if (quickMenuItems[i].action == text)
        {
            exists = true;
            break;
        }
    }
    if (!exists)
        quickMenuItems.Push(QuickMenuItem(text, callback));
}

Menu@ CreateIconizedMenuItem(const String&in title, MENU_CALLBACK@ callback = null, int accelKey = 0, int accelQual = 0, const String&in iconType = "", bool addToQuickMenu=true, String quickMenuText="")
{
    Menu@ menu = Menu(title);
    menu.defaultStyle = uiStyle;
    menu.style = AUTO_STYLE;
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
    menuText.style = "EditorMenuText";
    menuText.text = title;
    // If icon type is not provided, use the title instead
    IconizeUIElement(menuText, iconType.empty ? title : iconType);

    if (addToQuickMenu)
        AddQuickMenuItem(callback, quickMenuText.empty ? title : quickMenuText);

    if (accelKey != 0)
    {
        menuText.layoutMode = LM_HORIZONTAL;
        menuText.AddChild(CreateAccelKeyText(accelKey, accelQual));
    }

    return menu;
}

/// Create a child divider in parent with vertical layout mode. It works on other parent element as well, not just parent menu.
void CreateChildDivider(UIElement@ parent)
{
    BorderImage@ divider = parent.CreateChild("BorderImage", "Divider");
    divider.style = "EditorDivider";
}

Window@ CreatePopup(Menu@ baseMenu)
{
    Window@ popup = Window();
    popup.defaultStyle = uiStyle;
    popup.style = AUTO_STYLE;
    popup.SetLayout(LM_VERTICAL, 1, IntRect(2, 6, 2, 6));
    baseMenu.popup = popup;
    baseMenu.popupOffset = IntVector2(0, baseMenu.height);

    return popup;
}

Menu@ CreateMenu(const String&in title)
{
    Menu@ menu = CreateMenuItem(title);
    Text@ text = menu.children[0];
    menu.maxWidth = text.width + 20;
    CreatePopup(menu);

    return menu;
}

void HandleChangeLanguage(StringHash eventType, VariantMap& eventData)
{
    Array<UIElement@> children = uiMenuBar.GetChildren();

    for (uint i = 0; i < children.length - 2; ++i) // last 2 elements is not menu
    {
        // dirty hack: force recalc text size
        children[i].maxWidth = 1000;
        Text@ text = children[i].children[0];
        text.minWidth = 0;
        text.maxWidth = 1;
        text.ApplyAttributes();
        children[i].maxWidth = text.width + 20;
    }

    RebuildResourceDatabase();
}

Text@ CreateAccelKeyText(int accelKey, int accelQual)
{
    Text@ accelKeyText = Text();
    accelKeyText.defaultStyle = uiStyle;
    accelKeyText.style = "EditorMenuText";
    accelKeyText.textAlignment = HA_RIGHT;

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
    uint initialFilter, bool autoLocalizeTitle = true)
{
    // Within the editor UI, the file selector is a kind of a "singleton". When the previous one is overwritten, also
    // the events subscribed from it are disconnected, so new ones are safe to subscribe.
    uiFileSelector = FileSelector();
    uiFileSelector.defaultStyle = uiStyle;
    uiFileSelector.title = title;
    uiFileSelector.titleText.autoLocalizable = autoLocalizeTitle;
    uiFileSelector.path = initialPath;
    uiFileSelector.SetButtonTexts(ok, cancel);
    Text@ okText = cast<Text>(uiFileSelector.okButton.children[0]);
    okText.autoLocalizable = true;
    Text@ cancelText = cast<Text>(uiFileSelector.cancelButton.children[0]);
    cancelText.autoLocalizable = true;
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
    console.defaultStyle = uiStyle;
    console.commandInterpreter = consoleCommandInterpreter;
    console.numBufferedRows = 100;
    console.autoVisibleOnError = true;
}

void CreateDebugHud()
{
    engine.CreateDebugHud();
    debugHud.defaultStyle = uiStyle;
    debugHud.mode = DEBUGHUD_SHOW_NONE;
}

void CenterDialog(UIElement@ element)
{
    IntVector2 size = element.size;
    element.SetPosition((graphics.width - size.x) / 2, (graphics.height - size.y) / 2);
}

void CreateContextMenu()
{
    contextMenu = LoadEditorUI("UI/EditorContextMenu.xml");
    ui.root.AddChild(contextMenu);
}

void UpdateWindowTitle()
{
    String sceneName = GetFileNameAndExtension(editorScene.fileName);
    if (sceneName.empty || sceneName == TEMP_SCENE_NAME || sceneName == TEMP_BINARY_SCENE_NAME)
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

        Menu@ nextMenu = menuParent.vars["Origin"].GetPtr();
        if (nextMenu is null)
            break;
        else
            menu = nextMenu;
    }

    if (menu.parent is uiMenuBar)
        menu.showPopup = false;
}

String ExtractFileName(VariantMap& eventData, bool forSave = false)
{
    String fileName;

    // Check for OK
    if (eventData["OK"].GetBool())
    {
        String filter = eventData["Filter"].GetString();
        fileName = eventData["FileName"].GetString();
        // Add default extension for saving if not specified
        if (GetExtension(fileName).empty && forSave && filter != "*.*")
            fileName = fileName + filter.Substring(1);
    }
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
    SaveScene(ExtractFileName(eventData, true));
}

void HandleLoadNodeFile(StringHash eventType, VariantMap& eventData)
{
    CloseFileSelector(uiNodeFilter, uiNodePath);
    LoadNode(ExtractFileName(eventData));
}

void HandleSaveNodeFile(StringHash eventType, VariantMap& eventData)
{
    CloseFileSelector(uiNodeFilter, uiNodePath);
    SaveNode(ExtractFileName(eventData, true));
}

void HandleImportModel(StringHash eventType, VariantMap& eventData)
{
    CloseFileSelector(uiImportFilter, uiImportPath);
    ImportModel(ExtractFileName(eventData));
}
void HandleImportAnimation(StringHash eventType, VariantMap& eventData)
{
    CloseFileSelector(uiImportFilter, uiImportPath);
    ImportAnimation(ExtractFileName(eventData));
}

void HandleImportScene(StringHash eventType, VariantMap& eventData)
{
    CloseFileSelector(uiImportFilter, uiImportPath);
    ImportScene(ExtractFileName(eventData));
}

void HandleExportSceneOBJ(StringHash eventType, VariantMap& eventData)
{
    CloseFileSelector(uiExportFilter, uiExportPath);
    ExportSceneToOBJ(ExtractFileName(eventData));
}

void HandleExportSelectedOBJ(StringHash eventType, VariantMap& eventData)
{
    CloseFileSelector(uiExportFilter, uiExportPath);
    ExportSelectedToOBJ(ExtractFileName(eventData));
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
    String pathName = uiFileSelector.path;
    CloseFileSelector();
    if (eventData["OK"].GetBool())
        SetResourcePath(pathName, false);
}

void HandleOpenUILayoutFile(StringHash eventType, VariantMap& eventData)
{
    CloseFileSelector(uiElementFilter, uiElementPath);
    OpenUILayout(ExtractFileName(eventData));
}

void HandleSaveUILayoutFile(StringHash eventType, VariantMap& eventData)
{
    CloseFileSelector(uiElementFilter, uiElementPath);
    SaveUILayout(ExtractFileName(eventData, true));
}

void HandleLoadChildUIElementFile(StringHash eventType, VariantMap& eventData)
{
    CloseFileSelector(uiElementFilter, uiElementPath);
    LoadChildUIElement(ExtractFileName(eventData));
}

void HandleSaveChildUIElementFile(StringHash eventType, VariantMap& eventData)
{
    CloseFileSelector(uiElementFilter, uiElementPath);
    SaveChildUIElement(ExtractFileName(eventData, true));
}

void HandleUIElementDefaultStyle(StringHash eventType, VariantMap& eventData)
{
    CloseFileSelector(uiElementFilter, uiElementPath);
    SetUIElementDefaultStyle(ExtractFileName(eventData));
}

void HandleHotKeysBlender( VariantMap& eventData)
{
    int key = eventData["Key"].GetInt();
    int viewDirection = eventData["Qualifiers"].GetInt() == QUAL_CTRL ? -1 : 1;

    if (key == KEY_ESC)
    {
        if (uiHidden)
            UnhideUI();
        else if (console.visible)
            console.visible = false;
        else if (contextMenu.visible)
            CloseContextMenu();
        else if (quickMenu.visible)
        {
            quickMenu.visible = false;
            quickMenu.enabled = false;
        }
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
    else if (key == KEY_F11)
    {
        Image@ screenshot = Image();
        graphics.TakeScreenShot(screenshot);
        if (!fileSystem.DirExists(screenshotDir))
            fileSystem.CreateDir(screenshotDir);
        screenshot.SavePNG(screenshotDir + "/Screenshot_" +
                time.timeStamp.Replaced(':', '_').Replaced('.', '_').Replaced(' ', '_') + ".png");
    }
    else if (key == KEY_KP_1 && ui.focusElement is null) // Front view
    {
        Vector3 center = Vector3(0,0,0);
        if (selectedNodes.length > 0 || selectedComponents.length > 0)
            center = SelectedNodesCenterPoint();

        Vector3 pos = cameraNode.worldPosition - center;
        cameraNode.worldPosition = center - Vector3(0.0, 0.0, pos.length * viewDirection);
        cameraNode.direction = Vector3(0, 0, viewDirection);
        ReacquireCameraYawPitch();
    }

    else if (key == KEY_KP_3 && ui.focusElement is null) // Side view
    {
        Vector3 center = Vector3(0,0,0);
        if (selectedNodes.length > 0 || selectedComponents.length > 0)
            center = SelectedNodesCenterPoint();

        Vector3 pos = cameraNode.worldPosition - center;
        cameraNode.worldPosition = center - Vector3(pos.length * -viewDirection, 0.0, 0.0);
        cameraNode.direction = Vector3(-viewDirection, 0, 0);
        ReacquireCameraYawPitch();
    }

    else if (key == KEY_KP_7 && ui.focusElement is null) // Top view
    {
        Vector3 center = Vector3(0,0,0);
        if (selectedNodes.length > 0 || selectedComponents.length > 0)
            center = SelectedNodesCenterPoint();

        Vector3 pos = cameraNode.worldPosition - center;
        cameraNode.worldPosition = center - Vector3(0.0, pos.length * -viewDirection, 0.0);
        cameraNode.direction = Vector3(0, -viewDirection, 0);
        ReacquireCameraYawPitch();
    }
    else if (key == KEY_KP_5 && ui.focusElement is null)
    {
        activeViewport.camera.zoom = 1;
        activeViewport.ToggleOrthographic();
    }
    else if (key == '4' && ui.focusElement is null)
        editMode = EDIT_SELECT;
    else if (key == '5' && ui.focusElement is null)
        axisMode = AxisMode(axisMode ^ AXIS_LOCAL);
    else if (key == '6' && ui.focusElement is null)
    {
        --pickMode;
        if (pickMode < PICK_GEOMETRIES)
                pickMode = MAX_PICK_MODES - 1;
    }
    else if (key == '7' && ui.focusElement is null)
    {
        ++pickMode;
        if (pickMode >= MAX_PICK_MODES)
            pickMode = PICK_GEOMETRIES;
    }
    else if (key == 'Z' && eventData["Qualifiers"].GetInt() != QUAL_CTRL)
    {
        if (ui.focusElement is null)
        {
            fillMode = FillMode(fillMode + 1);
            if (fillMode > FILL_POINT)
                fillMode = FILL_SOLID;

            // Update camera fill mode
            SetFillMode(fillMode);
        }
    }
    else if (key == KEY_SPACE)
    {
        if (ui.cursor.visible && ui.focusElement is null)
            ToggleQuickMenu();
    }
    else
    {
        SteppedObjectManipulation(key);
    }

    if ((ui.focusElement is null) && (selectedNodes.length > 0) && !cameraFlyMode)
    {
         if (eventData["Qualifiers"].GetInt() == QUAL_ALT) // reset transformations
         {
            if (key == KEY_G)
                SceneResetPosition();
            else if (key == KEY_R)
                SceneResetRotation();
            else if (key == KEY_S)
                SceneResetScale();
            else if (key == KEY_F)
            {
                 Vector3 center = Vector3(0,0,0);

                 if (selectedNodes.length > 0)
                    center = SelectedNodesCenterPoint();

                 cameraNode.LookAt(center);
                 ReacquireCameraYawPitch();
            }
         }
         else if (eventData["Qualifiers"].GetInt() != QUAL_CTRL) // set transformations
         {
                if (key == KEY_G)
                {
                    editMode = EDIT_MOVE;
                    axisMode = AxisMode(axisMode ^ AXIS_LOCAL);

                }
                else if (key == KEY_R)
                {
                    editMode = EDIT_ROTATE;
                    axisMode = AxisMode(axisMode ^ AXIS_LOCAL);

                }
                else if (key == KEY_S)
                {
                    editMode = EDIT_SCALE;
                    axisMode = AxisMode(axisMode ^ AXIS_LOCAL);
                }
                else if (key == KEY_F)
                {
                    if (camera.orthographic)
                    {
                        viewCloser = true;
                    }
                    else
                    {
                        Vector3 center = Vector3(0,0,0);

                        if (selectedNodes.length > 0)
                            center = SelectedNodesCenterPoint();

                        cameraNode.LookAt(center);
                        ReacquireCameraYawPitch();
                    }
                }
         }
    }

    toolBarDirty = true;
}

void HandleHotKeysStandard(VariantMap& eventData)
{
    int key = eventData["Key"].GetInt();
    int viewDirection = eventData["Qualifiers"].GetInt() == QUAL_CTRL ? -1 : 1;

    if (key == KEY_ESC)
    {
        if (uiHidden)
            UnhideUI();
        else if (console.visible)
            console.visible = false;
        else if (contextMenu.visible)
            CloseContextMenu();
        else if (quickMenu.visible)
        {
            quickMenu.visible = false;
            quickMenu.enabled = false;
        }
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
    else if (key == KEY_F11)
    {
        Image@ screenshot = Image();
        graphics.TakeScreenShot(screenshot);
        if (!fileSystem.DirExists(screenshotDir))
            fileSystem.CreateDir(screenshotDir);
        screenshot.SavePNG(screenshotDir + "/Screenshot_" +
                time.timeStamp.Replaced(':', '_').Replaced('.', '_').Replaced(' ', '_') + ".png");
    }
    else if (key == KEY_KP_1 && ui.focusElement is null) // Front view
    {
        Vector3 center = Vector3(0,0,0);
        if (selectedNodes.length > 0 || selectedComponents.length > 0)
            center = SelectedNodesCenterPoint();

        Vector3 pos = cameraNode.worldPosition - center;
        cameraNode.worldPosition = center - Vector3(0.0, 0.0, pos.length * viewDirection);
        cameraNode.direction = Vector3(0, 0, viewDirection);
        ReacquireCameraYawPitch();
    }

    else if (key == KEY_KP_3 && ui.focusElement is null) // Side view
    {
        Vector3 center = Vector3(0,0,0);
        if (selectedNodes.length > 0 || selectedComponents.length > 0)
            center = SelectedNodesCenterPoint();

        Vector3 pos = cameraNode.worldPosition - center;
        cameraNode.worldPosition = center - Vector3(pos.length * -viewDirection, 0.0, 0.0);
        cameraNode.direction = Vector3(-viewDirection, 0, 0);
        ReacquireCameraYawPitch();
    }

    else if (key == KEY_KP_7 && ui.focusElement is null) // Top view
    {
        Vector3 center = Vector3(0,0,0);
        if (selectedNodes.length > 0 || selectedComponents.length > 0)
            center = SelectedNodesCenterPoint();

        Vector3 pos = cameraNode.worldPosition - center;
        cameraNode.worldPosition = center - Vector3(0.0, pos.length * -viewDirection, 0.0);
        cameraNode.direction = Vector3(0, -viewDirection, 0);
        ReacquireCameraYawPitch();
    }

    else if (key == KEY_KP_5 && ui.focusElement is null)
    {
        activeViewport.ToggleOrthographic();
    }
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
            SetFillMode(fillMode);
        }
        else if (key == KEY_SPACE)
        {
            if (ui.cursor.visible)
                ToggleQuickMenu();
        }
        else
            SteppedObjectManipulation(key);

        toolBarDirty = true;
    }
}

void HandleKeyDown(StringHash eventType, VariantMap& eventData)
{
    if (hotKeyMode == HOTKEYS_MODE_STANDARD)
    {
        HandleHotKeysStandard(eventData);
    }
    else if( hotKeyMode == HOTKEYS_MODE_BLENDER)
    {
        HandleHotKeysBlender(eventData);
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

    // Note: we could set ui.root.visible = false and it would hide the whole hierarchy.
    // However in this case we need the editorUIElement to stay visible
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
        element.InsertChild(0, icon);   // Ensure icon is added as the first child
    }

    // Set the icon type
    if (!icon.SetStyle(iconType, iconStyle))
        icon.SetStyle("Unknown", iconStyle);    // If fails then use an 'unknown' icon type
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
    UpdateDirtyToolBar();

    // Perform hierarchy selection latently after the new selections are finalized (used in undo/redo action)
    if (!hierarchyUpdateSelections.empty)
    {
        hierarchyList.SetSelections(hierarchyUpdateSelections);
        hierarchyUpdateSelections.Clear();
    }

    // Perform some event-triggered updates latently in case a large hierarchy was changed
    if (attributesFullDirty || attributesDirty)
        UpdateAttributeInspector(attributesFullDirty);
}

void HandleMessageAcknowledgement(StringHash eventType, VariantMap& eventData)
{
    if (eventData["Ok"].GetBool())
        messageBoxCallback();
    else
        messageBoxCallback = null;
}

void PopulateMruScenes()
{
    mruScenesPopup.RemoveAllChildren();
    if (uiRecentScenes.length > 0)
    {
        recentSceneMenu.enabled = true;
        for (uint i=0; i < uiRecentScenes.length; ++i)
            mruScenesPopup.AddChild(CreateMenuItem(uiRecentScenes[i], @LoadMostRecentScene, 0, 0, false, "", false));
    }
    else
        recentSceneMenu.enabled = false;

}

bool LoadMostRecentScene()
{
    Menu@ menu = GetEventSender();
    if (menu is null)
        return false;

    Text@ text = menu.GetChildren()[0];
    if (text is null)
        return false;

    return LoadScene(text.text);
}

// Set from click to false if opening menu procedurally.
void OpenContextMenu(bool fromClick=true)
{
    if (contextMenu is null)
        return;

    contextMenu.enabled = true;
    contextMenu.visible = true;
    contextMenu.BringToFront();
    if (fromClick)
        contextMenuActionWaitFrame=true;
}

void CloseContextMenu()
{
    if (contextMenu is null)
        return;

    contextMenu.enabled = false;
    contextMenu.visible = false;
}

void ActivateContextMenu(Array<UIElement@> actions)
{
    contextMenu.RemoveAllChildren();
    for (uint i=0; i< actions.length; ++i)
    {
        contextMenu.AddChild(actions[i]);
    }
    contextMenu.SetFixedHeight(24*actions.length+6);
    contextMenu.position = ui.cursor.screenPosition + IntVector2(10,-10);
    OpenContextMenu();
}

Menu@ CreateContextMenuItem(String text, String handler, String menuName = "", bool autoLocalize = true)
{
    Menu@ menu = Menu();
    menu.defaultStyle = uiStyle;
    menu.style = AUTO_STYLE;
    menu.name = menuName;
    menu.SetLayout(LM_HORIZONTAL, 0, IntRect(8, 2, 8, 2));
    Text@ menuText = Text();
    menuText.style = "EditorMenuText";
    menu.AddChild(menuText);
    menuText.text = text;
    menuText.autoLocalizable = autoLocalize;
    menu.vars[VAR_CONTEXT_MENU_HANDLER] = handler;
    SubscribeToEvent(menu, "Released", "ContextMenuEventWrapper");
    return menu;
}

void ContextMenuEventWrapper(StringHash eventType, VariantMap& eventData)
{
    UIElement@ uiElement = eventData["Element"].GetPtr();
    if (uiElement is null)
        return;

    String handler = uiElement.vars[VAR_CONTEXT_MENU_HANDLER].GetString();
    if (!handler.empty)
    {
        SubscribeToEvent(uiElement, "Released", handler);
        uiElement.SendEvent("Released", eventData);
    }
    CloseContextMenu();
}

/// Load a UI XML file used by the editor
XMLFile@ GetEditorUIXMLFile(const String&in fileName)
{
    // Prefer the executable path to avoid using the user's resource path, which may point
    // to an outdated Urho installation
    String fullFileName = fileSystem.programDir + "Data/" + fileName;
    if (fileSystem.FileExists(fullFileName))
    {
        File@ file = File(fullFileName, FILE_READ);
        XMLFile@ xml = XMLFile();
        xml.name = fileName;
        if (xml.Load(file))
            return xml;
    }

    // Fallback to resource system
    return cache.GetResource("XMLFile", fileName);
}


/// Load an UI layout used by the editor
UIElement@ LoadEditorUI(const String&in fileName)
{
    return ui.LoadLayout(GetEditorUIXMLFile(fileName));
}

/// Set node children as a spline path, either cyclic or non-cyclic
bool SetSplinePath()
{
    Menu@ menu = GetEventSender();
    if (menu is null)
        return false;

    return SceneSetChildrenSplinePath(menu.name == "Cyclic");
}

bool ColorWheelBuildMenuSelectTypeColor()
{
    if (selectedNodes.empty && selectedComponents.empty) return false;
    editMode = EDIT_SELECT;

    // do coloring only for single selected object
    // start with trying to find single component
    if (selectedComponents.length == 1)
    {
        coloringComponent = selectedComponents[0];
    }
    // else try to get first component from selected node
    else if (selectedNodes.length == 1)
    {
        Array<Component@> components = selectedNodes[0].GetComponents();
        if (components.length > 0)
        {
            coloringComponent = components[0];
        }
    }
    else
        return false;

    if (coloringComponent is null) return false;

    Array<UIElement@> actions;

    if (coloringComponent.typeName == "Light")
    {
        actions.Push(CreateContextMenuItem("Light color", "HandleColorWheelMenu", "menuLightColor"));
        actions.Push(CreateContextMenuItem("Specular intensity", "HandleColorWheelMenu", "menuSpecularIntensity"));
        actions.Push(CreateContextMenuItem("Brightness multiplier", "HandleColorWheelMenu", "menuBrightnessMultiplier"));

        actions.Push(CreateContextMenuItem("Cancel", "HandleColorWheelMenu", "menuCancel"));

    }
    else if (coloringComponent.typeName == "StaticModel")
    {
        actions.Push(CreateContextMenuItem("Diffuse color", "HandleColorWheelMenu", "menuDiffuseColor"));
        actions.Push(CreateContextMenuItem("Specular color", "HandleColorWheelMenu", "menuSpecularColor"));
        actions.Push(CreateContextMenuItem("Emissive color", "HandleColorWheelMenu", "menuEmissiveColor"));
        actions.Push(CreateContextMenuItem("Environment map color", "HandleColorWheelMenu", "menuEnvironmentMapColor"));

        actions.Push(CreateContextMenuItem("Cancel", "HandleColorWheelMenu", "menuCancel"));
    }
    else if (coloringComponent.typeName == "Zone")
    {
        actions.Push(CreateContextMenuItem("Ambient color", "HandleColorWheelMenu", "menuAmbientColor"));
        actions.Push(CreateContextMenuItem("Fog color", "HandleColorWheelMenu", "menuFogColor"));

        actions.Push(CreateContextMenuItem("Cancel", "HandleColorWheelMenu", "menuCancel"));
    }

    if (actions.length > 0) {
        ActivateContextMenu(actions);
        return true;
    }

    return false;
}

void HandleColorWheelMenu()
{
    ColorWheelSetupBehaviorForColoring();
}

// color was changed, update color of all colorGroup for immediate preview;
void HandleWheelChangeColor(StringHash eventType, VariantMap& eventData)
{
    if (timeToNextColoringGroupUpdate > time.systemTime) return;

    if (coloringComponent !is null)
    {
        Color c = eventData["Color"].GetColor();  // current ColorWheel
        // preview new color
        if (coloringComponent.typeName == "Light")
        {
            Light@ light = cast<Light>(coloringComponent);
            if (light !is null)
            {
                if (coloringPropertyName == "menuLightColor")
                {
                    light.color = c;
                }
                else if (coloringPropertyName == "menuSpecularIntensity")
                {
                   // multiply out
                   light.specularIntensity = c.Value() * 10.0f;

                }
                else if (coloringPropertyName == "menuBrightnessMultiplier")
                {
                   light.brightness = c.Value() * 10.0f;

                }

                attributesDirty = true;
            }
        }
        else if (coloringComponent.typeName == "StaticModel")
        {
            StaticModel@ model  = cast<StaticModel>(coloringComponent);
            if (model !is null)
            {
                Material@ mat = model.materials[0];
                if (mat !is null)
                {
                    if (coloringPropertyName == "menuDiffuseColor")
                    {
                        Variant oldValue = mat.shaderParameters["MatDiffColor"];
                        Variant newValue;
                        String valueString;
                        valueString += String(c.r).Substring(0,5);
                        valueString += " ";
                        valueString += String(c.g).Substring(0,5);
                        valueString += " ";
                        valueString += String(c.b).Substring(0,5);
                        valueString += " ";
                        valueString += String(c.a).Substring(0,5);
                        newValue.FromString(oldValue.type, valueString);
                        mat.shaderParameters["MatDiffColor"] = newValue;
                    }
                    else if (coloringPropertyName == "menuSpecularColor")
                    {
                        Variant oldValue = mat.shaderParameters["MatSpecColor"];
                        Variant newValue;
                        String valueString;
                        valueString += String(c.r).Substring(0,5);
                        valueString += " ";
                        valueString += String(c.g).Substring(0,5);
                        valueString += " ";
                        valueString += String(c.b).Substring(0,5);
                        valueString += " ";
                        valueString += String(c.a * 128).Substring(0,5);
                        newValue.FromString(oldValue.type, valueString);
                        mat.shaderParameters["MatSpecColor"] = newValue;
                    }
                    else if (coloringPropertyName == "menuEmissiveColor")
                    {
                        Variant oldValue = mat.shaderParameters["MatEmissiveColor"];
                        Variant newValue;
                        String valueString;
                        valueString += String(c.r).Substring(0,5);
                        valueString += " ";
                        valueString += String(c.g).Substring(0,5);
                        valueString += " ";
                        valueString += String(c.b).Substring(0,5);
                        valueString += " ";
                        valueString += String(c.a).Substring(0,5);
                        newValue.FromString(oldValue.type, valueString);
                        mat.shaderParameters["MatEmissiveColor"] = newValue;
                    }
                    else if (coloringPropertyName == "menuEnvironmentMapColor")
                    {
                        Variant oldValue = mat.shaderParameters["MatEnvMapColor"];
                        Variant newValue;
                        String valueString;
                        valueString += String(c.r).Substring(0,5);
                        valueString += " ";
                        valueString += String(c.g).Substring(0,5);
                        valueString += " ";
                        valueString += String(c.b).Substring(0,5);
                        valueString += " ";
                        valueString += String(c.a).Substring(0,5);
                        newValue.FromString(oldValue.type, valueString);
                        mat.shaderParameters["MatEnvMapColor"] = newValue;
                    }
                }
            }
        }
        else if (coloringComponent.typeName == "Zone")
        {
            Zone@ zone  = cast<Zone>(coloringComponent);
            if (zone !is null)
            {
                if (coloringPropertyName == "menuAmbientColor")
                {
                    zone.ambientColor = c;
                }
                else if (coloringPropertyName == "menuFogColor")
                {
                    zone.fogColor = c;
                }

                attributesDirty = true;
            }
        }
    }

    timeToNextColoringGroupUpdate = time.systemTime + stepColoringGroupUpdate;
}

// Return old colors, wheel was closed or color discarded
void HandleWheelDiscardColor(StringHash eventType, VariantMap& eventData)
{
    if (coloringComponent !is null)
    {
        //Color oldColor = eventData["Color"].GetColor(); //Old color from ColorWheel from ShowColorWheelWithColor(old)
        Color oldColor = coloringOldColor;

        // preview new color
        if (coloringComponent.typeName == "Light")
        {
            Light@ light = cast<Light>(coloringComponent);
            if (light !is null)
            {
                if (coloringPropertyName == "menuLightColor")
                {
                    light.color = oldColor;
                }
                else if (coloringPropertyName == "menuSpecularIntensity")
                {
                   light.specularIntensity = coloringOldScalar * 10.0f;

                }
                else if (coloringPropertyName == "menuBrightnessMultiplier")
                {
                   light.brightness = coloringOldScalar * 10.0f;

                }

                attributesDirty = true;
            }
        }
        else if (coloringComponent.typeName == "StaticModel")
        {
            StaticModel@ model  = cast<StaticModel>(coloringComponent);
            if (model !is null)
            {
                Material@ mat = model.materials[0];
                if (mat !is null)
                {
                    if (coloringPropertyName == "menuDiffuseColor")
                    {
                        Variant oldValue = mat.shaderParameters["MatDiffColor"];
                        Variant newValue;
                        String valueString;
                        valueString += String(oldColor.r).Substring(0,5);
                        valueString += " ";
                        valueString += String(oldColor.g).Substring(0,5);
                        valueString += " ";
                        valueString += String(oldColor.b).Substring(0,5);
                        valueString += " ";
                        valueString += String(oldColor.a).Substring(0,5);
                        newValue.FromString(oldValue.type, valueString);
                        mat.shaderParameters["MatDiffColor"] = newValue;
                    }
                    else if (coloringPropertyName == "menuSpecularColor")
                    {
                        Variant oldValue = mat.shaderParameters["MatSpecColor"];
                        Variant newValue;
                        String valueString;
                        valueString += String(oldColor.r).Substring(0,5);
                        valueString += " ";
                        valueString += String(oldColor.g).Substring(0,5);
                        valueString += " ";
                        valueString += String(oldColor.b).Substring(0,5);
                        valueString += " ";
                        valueString += String(coloringOldScalar).Substring(0,5);
                        newValue.FromString(oldValue.type, valueString);
                        mat.shaderParameters["MatSpecColor"] = newValue;
                    }
                    else if (coloringPropertyName == "menuEmissiveColor")
                    {
                        Variant oldValue = mat.shaderParameters["MatEmissiveColor"];
                        Variant newValue;
                        String valueString;
                        valueString += String(oldColor.r).Substring(0,5);
                        valueString += " ";
                        valueString += String(oldColor.g).Substring(0,5);
                        valueString += " ";
                        valueString += String(oldColor.b).Substring(0,5);
                        valueString += " ";
                        valueString += String(oldColor.a).Substring(0,5);
                        newValue.FromString(oldValue.type, valueString);
                        mat.shaderParameters["MatEmissiveColor"] = newValue;
                    }
                    else if (coloringPropertyName == "menuEnvironmentMapColor")
                    {
                        Variant oldValue = mat.shaderParameters["MatEnvMapColor"];
                        Variant newValue;
                        String valueString;
                        valueString += String(oldColor.r).Substring(0,5);
                        valueString += " ";
                        valueString += String(oldColor.g).Substring(0,5);
                        valueString += " ";
                        valueString += String(oldColor.b).Substring(0,5);
                        valueString += " ";
                        valueString += String(oldColor.a).Substring(0,5);
                        newValue.FromString(oldValue.type, valueString);
                        mat.shaderParameters["MatEnvMapColor"] = newValue;
                    }
                }
            }
        }
        else if (coloringComponent.typeName == "Zone")
        {
            Zone@ zone  = cast<Zone>(coloringComponent);
            if (zone !is null)
            {
                if (coloringPropertyName == "menuAmbientColor")
                {
                    zone.ambientColor = oldColor;
                }
                else if (coloringPropertyName == "menuFogColor")
                {
                    zone.fogColor = oldColor;
                }

                attributesDirty = true;
            }
        }
    }
}

// Applying color wheel changes to material
void HandleWheelSelectColor(StringHash eventType, VariantMap& eventData)
{
    if (coloringComponent !is null)
    if (coloringComponent.typeName == "StaticModel")
    {
        Color c = eventData["Color"].GetColor(); //Selected color from ColorWheel
        StaticModel@ model  = cast<StaticModel>(coloringComponent);
        if (model !is null)
        {
            Material@ mat = model.materials[0];
            if (mat !is null)
            {
                editMaterial = mat;
                SaveMaterial();
            }
        }
    }
}

bool ViewDebugIcons()
{
    debugIconsShow = !debugIconsShow;
    return true;
}
