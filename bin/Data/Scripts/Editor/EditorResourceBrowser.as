UIElement@ browserWindow;
Window@ browserFilterWindow;
ListView@ browserDirList;
ListView@ browserFileList;
LineEdit@ browserSearch;
BrowserFile@ browserDragFile;
Node@ browserDragNode;
Component@ browserDragComponent;
View3D@ resourceBrowserPreview;
Scene@ resourcePreviewScene;
Node@ resourcePreviewNode;
Node@ resourcePreviewCameraNode;
Node@ resourcePreviewLightNode;
Light@ resourcePreviewLight;
int browserSearchSortMode = 0;

BrowserDir@ rootDir;
Array<BrowserFile@> browserFiles;
Dictionary browserDirs;
Array<int> activeResourceTypeFilters;
Array<int> activeResourceDirFilters;

Array<BrowserFile@> browserFilesToScan;
const uint BROWSER_WORKER_ITEMS_PER_TICK = 10;
const uint BROWSER_SEARCH_LIMIT = 50;
const int BROWSER_SORT_MODE_ALPHA = 1;
const int BROWSER_SORT_MODE_SEARCH = 2;

const int RESOURCE_TYPE_UNUSABLE = -2;
const int RESOURCE_TYPE_UNKNOWN = -1;
const int RESOURCE_TYPE_NOTSET = 0;
const int RESOURCE_TYPE_SCENE = 1;
const int RESOURCE_TYPE_SCRIPTFILE = 2;
const int RESOURCE_TYPE_MODEL = 3;
const int RESOURCE_TYPE_MATERIAL = 4;
const int RESOURCE_TYPE_ANIMATION = 5;
const int RESOURCE_TYPE_IMAGE = 6;
const int RESOURCE_TYPE_SOUND = 7;
const int RESOURCE_TYPE_TEXTURE = 8;
const int RESOURCE_TYPE_FONT = 9;
const int RESOURCE_TYPE_PREFAB = 10;
const int RESOURCE_TYPE_TECHNIQUE = 11;
const int RESOURCE_TYPE_PARTICLEEFFECT = 12;
const int RESOURCE_TYPE_UIELEMENT = 13;
const int RESOURCE_TYPE_UIELEMENTS = 14;
const int RESOURCE_TYPE_ANIMATION_SETTINGS = 15;
const int RESOURCE_TYPE_RENDERPATH = 16;
const int RESOURCE_TYPE_TEXTURE_ATLAS = 17;
const int RESOURCE_TYPE_2D_PARTICLE_EFFECT = 18;
const int RESOURCE_TYPE_TEXTURE_3D = 19;
const int RESOURCE_TYPE_CUBEMAP = 20;
const int RESOURCE_TYPE_PARTICLEEMITTER = 21;
const int RESOURCE_TYPE_2D_ANIMATION_SET = 22;

// any resource type > 0 is valid
const int NUMBER_OF_VALID_RESOURCE_TYPES = 22;

const StringHash XML_TYPE_SCENE("scene");
const StringHash XML_TYPE_NODE("node");
const StringHash XML_TYPE_MATERIAL("material");
const StringHash XML_TYPE_TECHNIQUE("technique");
const StringHash XML_TYPE_PARTICLEEFFECT("particleeffect");
const StringHash XML_TYPE_PARTICLEEMITTER("particleemitter");
const StringHash XML_TYPE_TEXTURE("texture");
const StringHash XML_TYPE_ELEMENT("element");
const StringHash XML_TYPE_ELEMENTS("elements");
const StringHash XML_TYPE_ANIMATION_SETTINGS("animation");
const StringHash XML_TYPE_RENDERPATH("renderpath");
const StringHash XML_TYPE_TEXTURE_ATLAS("TextureAtlas");
const StringHash XML_TYPE_2D_PARTICLE_EFFECT("particleEmitterConfig");
const StringHash XML_TYPE_TEXTURE_3D("texture3d");
const StringHash XML_TYPE_CUBEMAP("cubemap");
const StringHash XML_TYPE_SPRITER_DATA("spriter_data");

const StringHash JSON_TYPE_SCENE("scene");
const StringHash JSON_TYPE_NODE("node");
const StringHash JSON_TYPE_MATERIAL("material");
const StringHash JSON_TYPE_TECHNIQUE("technique");
const StringHash JSON_TYPE_PARTICLEEFFECT("particleeffect");
const StringHash JSON_TYPE_PARTICLEEMITTER("particleemitter");
const StringHash JSON_TYPE_TEXTURE("texture");
const StringHash JSON_TYPE_ELEMENT("element");
const StringHash JSON_TYPE_ELEMENTS("elements");
const StringHash JSON_TYPE_ANIMATION_SETTINGS("animation");
const StringHash JSON_TYPE_RENDERPATH("renderpath");
const StringHash JSON_TYPE_TEXTURE_ATLAS("TextureAtlas");
const StringHash JSON_TYPE_2D_PARTICLE_EFFECT("particleEmitterConfig");
const StringHash JSON_TYPE_TEXTURE_3D("texture3d");
const StringHash JSON_TYPE_CUBEMAP("cubemap");
const StringHash JSON_TYPE_SPRITER_DATA("spriter_data");

const StringHash BINARY_TYPE_SCENE("USCN");
const StringHash BINARY_TYPE_PACKAGE("UPAK");
const StringHash BINARY_TYPE_COMPRESSED_PACKAGE("ULZ4");
const StringHash BINARY_TYPE_ANGLESCRIPT("ASBC");
const StringHash BINARY_TYPE_MODEL("UMDL");
const StringHash BINARY_TYPE_SHADER("USHD");
const StringHash BINARY_TYPE_ANIMATION("UANI");

const StringHash EXTENSION_TYPE_TTF(".ttf");
const StringHash EXTENSION_TYPE_OTF(".otf");
const StringHash EXTENSION_TYPE_OGG(".ogg");
const StringHash EXTENSION_TYPE_WAV(".wav");
const StringHash EXTENSION_TYPE_DDS(".dds");
const StringHash EXTENSION_TYPE_PNG(".png");
const StringHash EXTENSION_TYPE_JPG(".jpg");
const StringHash EXTENSION_TYPE_JPEG(".jpeg");
const StringHash EXTENSION_TYPE_BMP(".bmp");
const StringHash EXTENSION_TYPE_TGA(".tga");
const StringHash EXTENSION_TYPE_KTX(".ktx");
const StringHash EXTENSION_TYPE_PVR(".pvr");
const StringHash EXTENSION_TYPE_OBJ(".obj");
const StringHash EXTENSION_TYPE_FBX(".fbx");
const StringHash EXTENSION_TYPE_COLLADA(".dae");
const StringHash EXTENSION_TYPE_BLEND(".blend");
const StringHash EXTENSION_TYPE_ANGELSCRIPT(".as");
const StringHash EXTENSION_TYPE_LUASCRIPT(".lua");
const StringHash EXTENSION_TYPE_HLSL(".hlsl");
const StringHash EXTENSION_TYPE_GLSL(".glsl");
const StringHash EXTENSION_TYPE_FRAGMENTSHADER(".frag");
const StringHash EXTENSION_TYPE_VERTEXSHADER(".vert");
const StringHash EXTENSION_TYPE_HTML(".html");

const StringHash TEXT_VAR_FILE_ID("browser_file_id");
const StringHash TEXT_VAR_DIR_ID("browser_dir_id");
const StringHash TEXT_VAR_RESOURCE_TYPE("resource_type");
const StringHash TEXT_VAR_RESOURCE_DIR_ID("resource_dir_id");

const int BROWSER_FILE_SOURCE_RESOURCE_DIR = 1;

uint browserDirIndex = 1;
uint browserFileIndex = 1;
BrowserDir@ selectedBrowserDirectory;
BrowserFile@ selectedBrowserFile;
Text@ browserStatusMessage;
Text@ browserResultsMessage;
bool ignoreRefreshBrowserResults = false;
String resourceDirsCache;

void CreateResourceBrowser()
{
    if (browserWindow !is null) return;

    CreateResourceBrowserUI();
    InitResourceBrowserPreview();
    RebuildResourceDatabase();
}

void RebuildResourceDatabase()
{
    if (browserWindow is null)
        return;

    String newResourceDirsCache = Join(cache.resourceDirs, ';');
    ScanResourceDirectories();
    if (newResourceDirsCache != resourceDirsCache)
    {
        resourceDirsCache = newResourceDirsCache;
        PopulateResourceDirFilters();
    }
    PopulateBrowserDirectories();
    PopulateResourceBrowserFilesByDirectory(rootDir);
}

void ScanResourceDirectories()
{
    browserDirs.Clear();
    browserFiles.Clear();
    browserFilesToScan.Clear();

    rootDir = BrowserDir("");
    browserDirs.Set("", @rootDir);

    // collect all of the items and sort them afterwards
    for(uint i=0; i < cache.resourceDirs.length; ++i)
    {
        if (activeResourceDirFilters.Find(i) > -1)
            continue;

        ScanResourceDir(i);
    }
}

// used to stop ui from blocking while determining file types
void DoResourceBrowserWork()
{
    if (browserFilesToScan.length == 0)
        return;

    int counter = 0;
    bool updateBrowserUI = false;
    BrowserFile@ scanItem = browserFilesToScan[0];
    while(counter < BROWSER_WORKER_ITEMS_PER_TICK)
    {
        scanItem.DetermainResourceType();

        // next
        browserFilesToScan.Erase(0);
        if (browserFilesToScan.length > 0)
            @scanItem = browserFilesToScan[0];
        else
            break;
        counter++;
    }

    if (browserFilesToScan.length > 0)
        browserStatusMessage.text = localization.Get("Files left to scan: " )+ browserFilesToScan.length;
    else
        browserStatusMessage.text = localization.Get("Scan complete");

}

void CreateResourceBrowserUI()
{
    browserWindow = LoadEditorUI("UI/EditorResourceBrowser.xml");
    browserDirList = browserWindow.GetChild("DirectoryList", true);
    browserFileList = browserWindow.GetChild("FileList", true);
    browserSearch = browserWindow.GetChild("Search", true);
    browserStatusMessage = browserWindow.GetChild("StatusMessage", true);
    browserResultsMessage = browserWindow.GetChild("ResultsMessage", true);
    // browserWindow.visible = false;
    browserWindow.opacity = uiMaxOpacity;

    browserFilterWindow = LoadEditorUI("UI/EditorResourceFilterWindow.xml");
    CreateResourceFilterUI();
    HideResourceFilterWindow();

    int height = Min(ui.root.height / 4, 300);
    browserWindow.SetSize(900, height);
    browserWindow.SetPosition(35, ui.root.height - height - 25);

    CloseContextMenu();
    ui.root.AddChild(browserWindow);
    ui.root.AddChild(browserFilterWindow);

    SubscribeToEvent(browserWindow.GetChild("CloseButton", true), "Released", "HideResourceBrowserWindow");
    SubscribeToEvent(browserWindow.GetChild("RescanButton", true), "Released", "HandleRescanResourceBrowserClick");
    SubscribeToEvent(browserWindow.GetChild("FilterButton", true), "Released", "ToggleResourceFilterWindow");
    SubscribeToEvent(browserDirList, "SelectionChanged", "HandleResourceBrowserDirListSelectionChange");
    SubscribeToEvent(browserSearch, "TextChanged", "HandleResourceBrowserSearchTextChange");
    SubscribeToEvent(browserFileList, "ItemClicked", "HandleBrowserFileClick");
    SubscribeToEvent(browserFileList, "SelectionChanged", "HandleResourceBrowserFileListSelectionChange");
    SubscribeToEvent(cache, "FileChanged", "HandleFileChanged");
}

void CreateResourceFilterUI()
{
    UIElement@ options = browserFilterWindow.GetChild("TypeOptions", true);
    CheckBox@ toggleAllTypes = browserFilterWindow.GetChild("ToggleAllTypes", true);
    CheckBox@ toggleAllResourceDirs = browserFilterWindow.GetChild("ToggleAllResourceDirs", true);
    SubscribeToEvent(toggleAllTypes, "Toggled", "HandleResourceTypeFilterToggleAllTypesToggled");
    SubscribeToEvent(toggleAllResourceDirs, "Toggled", "HandleResourceDirFilterToggleAllTypesToggled");
    SubscribeToEvent(browserFilterWindow.GetChild("CloseButton", true), "Released", "HideResourceFilterWindow");

    int columns = 2;
    UIElement@ col1 = browserFilterWindow.GetChild("TypeFilterColumn1", true);
    UIElement@ col2 = browserFilterWindow.GetChild("TypeFilterColumn2", true);

    // use array to get sort of items
    Array<ResourceType@> sorted;
    for (int i=1; i <= NUMBER_OF_VALID_RESOURCE_TYPES; ++i)
        sorted.Push(ResourceType(i, ResourceTypeName(i)));
        
    // 2 unknown types are reserved for the top, the rest are alphabetized
    sorted.Sort();
    sorted.Insert(0, ResourceType(RESOURCE_TYPE_UNKNOWN, ResourceTypeName(RESOURCE_TYPE_UNKNOWN)) );
    sorted.Insert(0, ResourceType(RESOURCE_TYPE_UNUSABLE,  ResourceTypeName(RESOURCE_TYPE_UNUSABLE)) );
    int halfColumns = Ceil( float(sorted.length) / float(columns) );

    for (uint i = 0; i < sorted.length; ++i)
    {
        ResourceType@ type = sorted[i];
        UIElement@ resourceTypeHolder = UIElement();
        if (i < halfColumns)
            col1.AddChild(resourceTypeHolder);
        else
            col2.AddChild(resourceTypeHolder);

        resourceTypeHolder.layoutMode = LM_HORIZONTAL;
        resourceTypeHolder.layoutSpacing = 4;

        Text@ label = Text();
        label.style = "EditorAttributeText";
        label.text = type.name;
        CheckBox@ checkbox = CheckBox();
        checkbox.name = type.id;
        checkbox.SetStyleAuto();
        checkbox.vars[TEXT_VAR_RESOURCE_TYPE] = i;
        checkbox.checked = true;
        SubscribeToEvent(checkbox, "Toggled", "HandleResourceTypeFilterToggled");

        resourceTypeHolder.AddChild(checkbox);
        resourceTypeHolder.AddChild(label);
    }
}

void CreateDirList(BrowserDir@ dir, UIElement@ parentUI = null)
{
    Text@ dirText = Text();
    browserDirList.InsertItem(browserDirList.numItems, dirText, parentUI);
    dirText.style = "FileSelectorListText";
    dirText.text = dir.resourceKey.empty ? localization.Get("Root") : dir.name;
    dirText.name = dir.resourceKey;
    dirText.vars[TEXT_VAR_DIR_ID] = dir.resourceKey;

    // Sort directories alphetically
    browserSearchSortMode = BROWSER_SORT_MODE_ALPHA;
    dir.children.Sort();

    for(uint i=0; i<dir.children.length; ++i)
        CreateDirList(dir.children[i], dirText);
}

void CreateFileList(BrowserFile@ file)
{
    Text@ fileText = Text();
    fileText.style = "FileSelectorListText";
    fileText.layoutMode = LM_HORIZONTAL;
    browserFileList.InsertItem(browserFileList.numItems, fileText);
    file.browserFileListRow = fileText;
    InitializeBrowserFileListRow(fileText, file);
}

void InitializeBrowserFileListRow(Text@ fileText, BrowserFile@ file)
{
    fileText.RemoveAllChildren();
    VariantMap params = VariantMap();
    fileText.vars[TEXT_VAR_FILE_ID] = file.id;
    fileText.vars[TEXT_VAR_RESOURCE_TYPE] = file.resourceType;
    if (file.resourceType > 0)
        fileText.dragDropMode = DD_SOURCE;

    {
        Text@ text = Text();
        fileText.AddChild(text);
        text.style = "FileSelectorListText";
        text.text = file.fullname;
        text.name = file.resourceKey;
    }

    {
        Text@ text = Text();
        fileText.AddChild(text);
        text.style = "FileSelectorListText";
        text.text = file.ResourceTypeName();
    }

    if (file.resourceType == RESOURCE_TYPE_MATERIAL || 
            file.resourceType == RESOURCE_TYPE_MODEL ||
            file.resourceType == RESOURCE_TYPE_PARTICLEEFFECT ||
            file.resourceType == RESOURCE_TYPE_PREFAB
        )
    {
        SubscribeToEvent(fileText, "DragBegin", "HandleBrowserFileDragBegin");
        SubscribeToEvent(fileText, "DragEnd", "HandleBrowserFileDragEnd");
    }

}

void InitResourceBrowserPreview()
{
    resourcePreviewScene = Scene("PreviewScene");
    resourcePreviewScene.CreateComponent("Octree");
    PhysicsWorld@ physicsWorld = resourcePreviewScene.CreateComponent("PhysicsWorld");
    physicsWorld.enabled = false;
    physicsWorld.gravity = Vector3(0.0, 0.0, 0.0);

    Node@ zoneNode = resourcePreviewScene.CreateChild("Zone");
    Zone@ zone = zoneNode.CreateComponent("Zone");
    zone.boundingBox = BoundingBox(-1000, 1000);
    zone.ambientColor = Color(0.15, 0.15, 0.15);
    zone.fogColor = Color(0, 0, 0);
    zone.fogStart = 10.0;
    zone.fogEnd = 100.0;

    resourcePreviewCameraNode = resourcePreviewScene.CreateChild("PreviewCamera");
    resourcePreviewCameraNode.position = Vector3(0, 0, -1.5);
    Camera@ camera = resourcePreviewCameraNode.CreateComponent("Camera");
    camera.nearClip = 0.1f;
    camera.farClip = 100.0f;

    resourcePreviewLightNode = resourcePreviewScene.CreateChild("PreviewLight");
    resourcePreviewLightNode.direction = Vector3(0.5, -0.5, 0.5);
    resourcePreviewLight = resourcePreviewLightNode.CreateComponent("Light");
    resourcePreviewLight.lightType = LIGHT_DIRECTIONAL;
    resourcePreviewLight.specularIntensity = 0.5;

    resourceBrowserPreview = browserWindow.GetChild("ResourceBrowserPreview", true);
    resourceBrowserPreview.SetFixedHeight(200);
    resourceBrowserPreview.SetFixedWidth(266);
    resourceBrowserPreview.SetView(resourcePreviewScene, camera);
    resourceBrowserPreview.autoUpdate = false;

    resourcePreviewNode = resourcePreviewScene.CreateChild("PreviewNodeContainer");

    SubscribeToEvent(resourceBrowserPreview, "DragMove", "RotateResourceBrowserPreview");

    RefreshBrowserPreview();
}

// Opens a contextual menu based on what resource item was actioned
void HandleBrowserFileClick(StringHash eventType, VariantMap& eventData)
{
    if (eventData["Button"].GetInt() != MOUSEB_RIGHT)
        return;

    UIElement@ uiElement = eventData["Item"].GetPtr();
    BrowserFile@ file = GetBrowserFileFromUIElement(uiElement);

    if (file is null)
        return;

    Array<UIElement@> actions;
    if (file.resourceType == RESOURCE_TYPE_MATERIAL)
    {
        actions.Push(CreateBrowserFileActionMenu("Edit", "HandleBrowserEditResource", file));
    }
    else if (file.resourceType == RESOURCE_TYPE_MODEL)
    {
        actions.Push(CreateBrowserFileActionMenu("Instance Animated Model", "HandleBrowserInstantiateAnimatedModel", file));
        actions.Push(CreateBrowserFileActionMenu("Instance Static Model", "HandleBrowserInstantiateStaticModel", file));
    }
    else if (file.resourceType == RESOURCE_TYPE_PREFAB)
    {
        actions.Push(CreateBrowserFileActionMenu("Instance Prefab", "HandleBrowserInstantiatePrefab", file));
        actions.Push(CreateBrowserFileActionMenu("Instance in Spawner", "HandleBrowserInstantiateInSpawnEditor", file));
    }
    else if (file.fileType == EXTENSION_TYPE_OBJ ||
        file.fileType == EXTENSION_TYPE_COLLADA ||
        file.fileType == EXTENSION_TYPE_FBX ||
        file.fileType == EXTENSION_TYPE_BLEND)
    {
        actions.Push(CreateBrowserFileActionMenu("Import Model", "HandleBrowserImportModel", file));
        actions.Push(CreateBrowserFileActionMenu("Import Scene", "HandleBrowserImportScene", file));
    }
    else if (file.resourceType == RESOURCE_TYPE_UIELEMENT)
    {
        actions.Push(CreateBrowserFileActionMenu("Open UI Layout", "HandleBrowserOpenUILayout", file));
    }
    else if (file.resourceType == RESOURCE_TYPE_SCENE)
    {
        actions.Push(CreateBrowserFileActionMenu("Load Scene", "HandleBrowserLoadScene", file));
    }
    else if (file.resourceType == RESOURCE_TYPE_SCRIPTFILE)
    {
        actions.Push(CreateBrowserFileActionMenu("Execute Script", "HandleBrowserRunScript", file));
    }
    else if (file.resourceType == RESOURCE_TYPE_PARTICLEEFFECT)
    {
        actions.Push(CreateBrowserFileActionMenu("Edit", "HandleBrowserEditResource", file));
    }

    actions.Push(CreateBrowserFileActionMenu("Open", "HandleBrowserOpenResource", file));

    ActivateContextMenu(actions);
}

BrowserDir@ GetBrowserDir(String path)
{
    BrowserDir@ browserDir;
    browserDirs.Get(path, @browserDir);
    return browserDir;
}

// Makes sure the entire directory tree exists and new dir is linked to parent
BrowserDir@ InitBrowserDir(String path)
{
    BrowserDir@ browserDir;
    if (browserDirs.Get(path, @browserDir))
        return browserDir;

    Array<String> parts = path.Split('/');
    Array<String> finishedParts;
    if (parts.length > 0)
    {
        BrowserDir@ parent = rootDir;
        for( uint i = 0; i < parts.length; ++i )
        {
            finishedParts.Push(parts[i]);
            String currentPath = Join(finishedParts, "/");
            if (!browserDirs.Get(currentPath, @browserDir))
            {
                browserDir = BrowserDir(currentPath);
                browserDirs.Set(currentPath, @browserDir);
                parent.children.Push(browserDir);
            }
            @parent = browserDir;
        } 
        return browserDir;
    }
    return null;
}

void ScanResourceDir(uint resourceDirIndex)
{
    String resourceDir = cache.resourceDirs[resourceDirIndex];
    ScanResourceDirFiles("", resourceDirIndex);
    Array<String> dirs = fileSystem.ScanDir(resourceDir, "*", SCAN_DIRS, true);
    for (uint i=0; i < dirs.length; ++i)
    {
        String path = dirs[i];
        if (path.EndsWith("."))
            continue;

        InitBrowserDir(path);
        ScanResourceDirFiles(path, resourceDirIndex);
    }
}

void ScanResourceDirFiles(String path, uint resourceDirIndex)
{
    String fullPath = cache.resourceDirs[resourceDirIndex] + path;
    if (!fileSystem.DirExists(fullPath))
        return;

    BrowserDir@ dir = GetBrowserDir(path);

    if (dir is null)
        return;

    // get files in directory
    Array<String> dirFiles = fileSystem.ScanDir(fullPath, "*.*", SCAN_FILES, false);

    // add new files
    for (uint x=0; x < dirFiles.length; x++)
    {
        String filename = dirFiles[x];
        BrowserFile@ browserFile = dir.AddFile(filename, resourceDirIndex, BROWSER_FILE_SOURCE_RESOURCE_DIR);
        browserFiles.Push(browserFile);
        browserFilesToScan.Push(browserFile);
    }
}

bool ToggleResourceBrowserWindow()
{
    if (browserWindow.visible == false)
        ShowResourceBrowserWindow();
    else
        HideResourceBrowserWindow();
    return true;
}

void ShowResourceBrowserWindow()
{
    browserWindow.visible = true;
    browserWindow.BringToFront();
    ui.focusElement = browserSearch;
}

void HideResourceBrowserWindow()
{
    browserWindow.visible = false;
}

void ToggleResourceFilterWindow()
{
    if (browserFilterWindow.visible)
        HideResourceFilterWindow();
    else
        ShowResourceFilterWindow();
}
void HideResourceFilterWindow()
{
    browserFilterWindow.visible = false;
}

void ShowResourceFilterWindow()
{
    int x = browserWindow.position.x + browserWindow.width - browserFilterWindow.width;
    int y = browserWindow.position.y - browserFilterWindow.height - 1;
    browserFilterWindow.position = IntVector2(x,y);
    browserFilterWindow.visible = true;
    browserFilterWindow.BringToFront();
}

void PopulateResourceDirFilters()
{
    UIElement@ resourceDirs = browserFilterWindow.GetChild("DirFilters", true);
    resourceDirs.RemoveAllChildren();
    activeResourceDirFilters.Clear();
    for (uint i=0; i < cache.resourceDirs.length; ++i)
    {
        UIElement@ resourceDirHolder = UIElement();
        resourceDirs.AddChild(resourceDirHolder);
        resourceDirHolder.layoutMode = LM_HORIZONTAL;
        resourceDirHolder.layoutSpacing = 4;
        resourceDirHolder.SetFixedHeight(16);

        Text@ label = Text();
        label.style = "EditorAttributeText";
        label.text = cache.resourceDirs[i].Replaced(fileSystem.programDir, "");
        CheckBox@ checkbox = CheckBox();
        checkbox.name = i;
        checkbox.SetStyleAuto();
        checkbox.vars[TEXT_VAR_RESOURCE_DIR_ID] = i;
        checkbox.checked = true;
        SubscribeToEvent(checkbox, "Toggled", "HandleResourceDirFilterToggled");


        resourceDirHolder.AddChild(checkbox);
        resourceDirHolder.AddChild(label);
    }

}

void PopulateBrowserDirectories()
{
    browserDirList.RemoveAllItems();
    CreateDirList(rootDir);
    browserDirList.selection = 0;
}

void PopulateResourceBrowserFilesByDirectory(BrowserDir@ dir)
{
    @selectedBrowserDirectory = dir;
    browserFileList.RemoveAllItems();
    if (dir is null) return;

    Array<BrowserFile@> files;
    for(uint x=0; x < dir.files.length; x++)
    {
        BrowserFile@ file = dir.files[x];

        if (activeResourceTypeFilters.Find(file.resourceType) == -1)
            files.Push(file);
    }

    // Sort alphetically
    browserSearchSortMode = BROWSER_SORT_MODE_ALPHA;
    files.Sort();
    PopulateResourceBrowserResults(files);
    browserResultsMessage.text = localization.Get("Showing files: ") + files.length;
}


void PopulateResourceBrowserBySearch()
{
    String query = browserSearch.text;

    Array<int> scores;
    Array<BrowserFile@> scored;
    Array<BrowserFile@> filtered;
    {
        BrowserFile@ file;
        for(uint x=0; x < browserFiles.length; x++)
        {
            @file = browserFiles[x];
            file.sortScore = -1;
            if (activeResourceTypeFilters.Find(file.resourceType) > -1)
                continue;

            if (activeResourceDirFilters.Find(file.resourceSourceIndex) > -1)
                continue;

            int find = file.fullname.Find(query, 0, false);
            if (find > -1)
            {
                int fudge = query.length - file.fullname.length;
                int score = find * int(Abs(fudge*2)) + int(Abs(fudge));
                file.sortScore = score;
                scored.Push(file);
                scores.Push(score);
            }
        }
    }

    // cut this down for a faster sort
    if (scored.length > BROWSER_SEARCH_LIMIT)
    {
        scores.Sort();
        int scoreThreshold = scores[BROWSER_SEARCH_LIMIT];
        BrowserFile@ file;
        for(uint x=0;x<scored.length;x++)
        {
            file = scored[x];
            if (file.sortScore <= scoreThreshold)
                filtered.Push(file);
        }
    }
    else
        filtered = scored;

    browserSearchSortMode = BROWSER_SORT_MODE_ALPHA;
    filtered.Sort();
    PopulateResourceBrowserResults(filtered);
    browserResultsMessage.text = "Showing top " + filtered.length + " of " + scored.length + " results";
}

void PopulateResourceBrowserResults(Array<BrowserFile@>@ files)
{
    browserFileList.RemoveAllItems();
    for(uint i=0; i < files.length; ++i)
        CreateFileList(files[i]);
}

void RefreshBrowserResults()
{
    if (browserSearch.text.empty)
    {
        browserDirList.visible = true;
        PopulateResourceBrowserFilesByDirectory(selectedBrowserDirectory);
    }
    else
    {
        browserDirList.visible = false;
        PopulateResourceBrowserBySearch();
    }
}

void HandleResourceTypeFilterToggleAllTypesToggled(StringHash eventType, VariantMap& eventData)
{
    CheckBox@ checkbox = eventData["Element"].GetPtr();
    UIElement@ filterHolder = browserFilterWindow.GetChild("TypeFilters", true);
    Array<UIElement@> children = filterHolder.GetChildren(true);

    ignoreRefreshBrowserResults = true;
    for(uint i=0; i < children.length; ++i)
    {
        CheckBox@ filter = children[i];
        if (filter !is null)
            filter.checked = checkbox.checked;
    }
    ignoreRefreshBrowserResults = false;
    RefreshBrowserResults();
}

void HandleResourceTypeFilterToggled(StringHash eventType, VariantMap& eventData)
{
    CheckBox@ checkbox = eventData["Element"].GetPtr();
    if (!checkbox.vars.Contains(TEXT_VAR_RESOURCE_TYPE))
        return;

    int resourceType = checkbox.GetVar(TEXT_VAR_RESOURCE_TYPE).GetInt();
    int find = activeResourceTypeFilters.Find(resourceType);

    if (checkbox.checked && find != -1)
        activeResourceTypeFilters.Erase(find);
    else if (!checkbox.checked && find == -1)
        activeResourceTypeFilters.Push(resourceType);

    if (ignoreRefreshBrowserResults == false)
        RefreshBrowserResults();
}

void HandleResourceDirFilterToggleAllTypesToggled(StringHash eventType, VariantMap& eventData)
{
    CheckBox@ checkbox = eventData["Element"].GetPtr();
    UIElement@ filterHolder = browserFilterWindow.GetChild("DirFilters", true);
    Array<UIElement@> children = filterHolder.GetChildren(true);

    ignoreRefreshBrowserResults = true;
    for(uint i=0; i < children.length; ++i)
    {
        CheckBox@ filter = children[i];
        if (filter !is null)
            filter.checked = checkbox.checked;
    }
    ignoreRefreshBrowserResults = false;
    RebuildResourceDatabase();
}

void HandleResourceDirFilterToggled(StringHash eventType, VariantMap& eventData)
{
    CheckBox@ checkbox = eventData["Element"].GetPtr();
    if (!checkbox.vars.Contains(TEXT_VAR_RESOURCE_DIR_ID))
        return;

    int resourceDir = checkbox.GetVar(TEXT_VAR_RESOURCE_DIR_ID).GetInt();
    int find = activeResourceDirFilters.Find(resourceDir);

    if (checkbox.checked && find != -1)
        activeResourceDirFilters.Erase(find);
    else if (!checkbox.checked && find == -1)
        activeResourceDirFilters.Push(resourceDir);

    if (ignoreRefreshBrowserResults == false)
        RebuildResourceDatabase();
}

void HandleRescanResourceBrowserClick(StringHash eventType, VariantMap& eventData)
{
    RebuildResourceDatabase();
}

void HandleResourceBrowserDirListSelectionChange(StringHash eventType, VariantMap& eventData)
{
    if (browserDirList.selection == M_MAX_UNSIGNED)
        return;

    UIElement@ uiElement = browserDirList.GetItems()[browserDirList.selection];
    BrowserDir@ dir = GetBrowserDir(uiElement.vars[TEXT_VAR_DIR_ID].GetString());
    if (dir is null)
        return;

    PopulateResourceBrowserFilesByDirectory(dir);
}

void HandleResourceBrowserFileListSelectionChange(StringHash eventType, VariantMap& eventData)
{
    if (browserFileList.selection == M_MAX_UNSIGNED)
        return;

    UIElement@ uiElement = browserFileList.GetItems()[browserFileList.selection];
    BrowserFile@ file = GetBrowserFileFromUIElement(uiElement);
    if (file is null)
        return;

    if (resourcePreviewNode !is null)
        resourcePreviewNode.Remove();

    resourcePreviewNode = resourcePreviewScene.CreateChild("PreviewNodeContainer");
    CreateResourcePreview(file.GetFullPath(), resourcePreviewNode);

    if (resourcePreviewNode !is null)
    {
        Array<BoundingBox> boxes;
        Array<Component@> staticModels = resourcePreviewNode.GetComponents("StaticModel", true);
        Array<Component@> animatedModels = resourcePreviewNode.GetComponents("AnimatedModel", true);

        for (uint i = 0; i < staticModels.length; ++i)
            boxes.Push(cast<StaticModel>(staticModels[i]).worldBoundingBox);

        for (uint i = 0; i < animatedModels.length; ++i)
            boxes.Push(cast<AnimatedModel>(animatedModels[i]).worldBoundingBox);

        if (boxes.length > 0)
        {
            Vector3 camPosition = Vector3(0.0, 0.0, -1.2);
            BoundingBox biggestBox = boxes[0];
            for (uint i = 1; i < boxes.length; ++i)
            {
                if (boxes[i].size.length > biggestBox.size.length)
                    biggestBox = boxes[i];
            }
            resourcePreviewCameraNode.position = biggestBox.center + camPosition * biggestBox.size.length;
        }

        resourcePreviewScene.AddChild(resourcePreviewNode);
        RefreshBrowserPreview();
    }
}

void HandleResourceBrowserSearchTextChange(StringHash eventType, VariantMap& eventData)
{
    RefreshBrowserResults();
}

BrowserFile@ GetBrowserFileFromId(uint id)
{
    if (id == 0)
        return null;

    BrowserFile@ file;
    for(uint i=0; i<browserFiles.length; ++i)
    {
        @file = @browserFiles[i];
        if (file.id == id) return file;
    }
    return null;
}

BrowserFile@ GetBrowserFileFromUIElement(UIElement@ element)
{
    if (element is null || !element.vars.Contains(TEXT_VAR_FILE_ID))
        return null;
    return GetBrowserFileFromId(element.vars[TEXT_VAR_FILE_ID].GetUInt());
}

BrowserFile@ GetBrowserFileFromPath(String path)
{
    for (uint i=0; i < browserFiles.length; ++i)
    {
        BrowserFile@ file = browserFiles[i];
        if (path == file.GetFullPath())
            return file;
    }
    return null;
}

void HandleBrowserEditResource(StringHash eventType, VariantMap& eventData)
{
    UIElement@ element = eventData["Element"].GetPtr();
    BrowserFile@ file = GetBrowserFileFromUIElement(element);
    if (file is null)
        return;

    if (file.resourceType == RESOURCE_TYPE_MATERIAL)
    {
        Material@ material = cache.GetResource("Material", file.resourceKey);
        if (material !is null)
            EditMaterial(material);
    }

    if (file.resourceType == RESOURCE_TYPE_PARTICLEEFFECT)
    {
        ParticleEffect@ particleEffect = cache.GetResource("ParticleEffect", file.resourceKey);
        if (particleEffect !is null)
            EditParticleEffect(particleEffect);
    }
}

void HandleBrowserOpenResource(StringHash eventType, VariantMap& eventData)
{
    UIElement@ element = eventData["Element"].GetPtr();
    BrowserFile@ file = GetBrowserFileFromUIElement(element);
    if (file !is null)
        OpenResource(file.resourceKey);
}

void HandleBrowserImportScene(StringHash eventType, VariantMap& eventData)
{
    UIElement@ element = eventData["Element"].GetPtr();
    BrowserFile@ file = GetBrowserFileFromUIElement(element);
    if (file !is null)
        ImportScene(file.GetFullPath());
}

void HandleBrowserImportModel(StringHash eventType, VariantMap& eventData)
{
    UIElement@ element = eventData["Element"].GetPtr();
    BrowserFile@ file = GetBrowserFileFromUIElement(element);
    if (file !is null)
        ImportModel(file.GetFullPath());
}

void HandleBrowserOpenUILayout(StringHash eventType, VariantMap& eventData)
{
    UIElement@ element = eventData["Element"].GetPtr();
    BrowserFile@ file = GetBrowserFileFromUIElement(element);
    if (file !is null)
        OpenUILayout(file.GetFullPath());
}

void HandleBrowserInstantiateStaticModel(StringHash eventType, VariantMap& eventData)
{
    UIElement@ element = eventData["Element"].GetPtr();
    BrowserFile@ file = GetBrowserFileFromUIElement(element);
    if (file !is null)
        CreateModelWithStaticModel(file.resourceKey, editNode);
}

void HandleBrowserInstantiateAnimatedModel(StringHash eventType, VariantMap& eventData)
{
    UIElement@ element = eventData["Element"].GetPtr();
    BrowserFile@ file = GetBrowserFileFromUIElement(element);
    if (file !is null)
        CreateModelWithAnimatedModel(file.resourceKey, editNode);
}

void HandleBrowserInstantiatePrefab(StringHash eventType, VariantMap& eventData)
{
    UIElement@ element = eventData["Element"].GetPtr();
    BrowserFile@ file = GetBrowserFileFromUIElement(element);
    if (file !is null)
        LoadNode(file.GetFullPath());
}

void HandleBrowserInstantiateInSpawnEditor(StringHash eventType, VariantMap& eventData)
{
    UIElement@ element = eventData["Element"].GetPtr();
    BrowserFile@ file = GetBrowserFileFromUIElement(element);
    if (file !is null)
    {
        spawnedObjectsNames.Resize(1);
        spawnedObjectsNames[0] = VerifySpawnedObjectFile(file.GetPath());
        RefreshPickedObjects();
        ShowSpawnEditor();
    }
}

void HandleBrowserLoadScene(StringHash eventType, VariantMap& eventData)
{
    UIElement@ element = eventData["Element"].GetPtr();
    BrowserFile@ file = GetBrowserFileFromUIElement(element);
    if (file !is null)
        LoadScene(file.GetFullPath());
}

void HandleBrowserRunScript(StringHash eventType, VariantMap& eventData)
{
    UIElement@ element = eventData["Element"].GetPtr();
    BrowserFile@ file = GetBrowserFileFromUIElement(element);
    if (file !is null)
        ExecuteScript(ExtractFileName(eventData));
}

void HandleBrowserFileDragBegin(StringHash eventType, VariantMap& eventData)
{
    UIElement@ uiElement = eventData["Element"].GetPtr();
    @browserDragFile = GetBrowserFileFromUIElement(uiElement);
}

void HandleBrowserFileDragEnd(StringHash eventType, VariantMap& eventData)
{
    if (@browserDragFile is null)
        return;

    UIElement@ element = ui.GetElementAt(ui.cursor.screenPosition);
    if (element !is null)
        return;

    if (browserDragFile.resourceType == RESOURCE_TYPE_MATERIAL)
    {
        StaticModel@ model = cast<StaticModel>(GetDrawableAtMousePostion());
        if (model !is null)
        {
            AssignMaterial(model, browserDragFile.resourceKey);
        }
    }

    browserDragFile = null;
    browserDragComponent = null;
    browserDragNode = null;
}

void HandleFileChanged(StringHash eventType, VariantMap& eventData)
{
    String filename = eventData["FileName"].GetString();
    BrowserFile@ file = GetBrowserFileFromPath(filename);
    
    if (file is null)
    {
        // TODO: new file logic when watchers are supported 
        return;
    }
    else
    {
        file.FileChanged();
    }
}

Menu@ CreateBrowserFileActionMenu(String text, String handler, BrowserFile@ browserFile = null)
{
    Menu@ menu = CreateContextMenuItem(text, handler);
    if (browserFile !is null)
        menu.vars[TEXT_VAR_FILE_ID] = browserFile.id;

    return menu;
}

int GetResourceType(String path)
{
    StringHash fileType;
    return GetResourceType(path, fileType);
}

int GetResourceType(String path, StringHash &out fileType, bool useCache = false)
{
    if (GetExtensionType(path, fileType) || GetBinaryType(path, fileType, useCache) || GetXmlType(path, fileType, useCache))
        return GetResourceType(fileType);

    return RESOURCE_TYPE_UNKNOWN;
}


int GetResourceType(StringHash fileType)
{
    // binary fileTypes
    if (fileType == BINARY_TYPE_SCENE)
        return RESOURCE_TYPE_SCENE;
    else if (fileType == BINARY_TYPE_PACKAGE)
        return RESOURCE_TYPE_UNUSABLE;
    else if (fileType == BINARY_TYPE_COMPRESSED_PACKAGE)
        return RESOURCE_TYPE_UNUSABLE;
    else if (fileType == BINARY_TYPE_ANGLESCRIPT)
        return RESOURCE_TYPE_SCRIPTFILE;
    else if (fileType == BINARY_TYPE_MODEL)
        return RESOURCE_TYPE_MODEL;
    else if (fileType == BINARY_TYPE_SHADER)
        return RESOURCE_TYPE_UNUSABLE;
    else if (fileType == BINARY_TYPE_ANIMATION)
        return RESOURCE_TYPE_ANIMATION;

    // xml fileTypes
    else if (fileType == XML_TYPE_SCENE)
        return RESOURCE_TYPE_SCENE;
    else if (fileType == XML_TYPE_NODE)
        return RESOURCE_TYPE_PREFAB;
    else if(fileType == XML_TYPE_MATERIAL)
        return RESOURCE_TYPE_MATERIAL;
    else if(fileType == XML_TYPE_TECHNIQUE)
        return RESOURCE_TYPE_TECHNIQUE;
    else if(fileType == XML_TYPE_PARTICLEEFFECT)
        return RESOURCE_TYPE_PARTICLEEFFECT;
    else if(fileType == XML_TYPE_PARTICLEEMITTER)
        return RESOURCE_TYPE_PARTICLEEMITTER;
    else if(fileType == XML_TYPE_TEXTURE)
        return RESOURCE_TYPE_TEXTURE;
    else if(fileType == XML_TYPE_ELEMENT)
        return RESOURCE_TYPE_UIELEMENT;
    else if(fileType == XML_TYPE_ELEMENTS)
        return RESOURCE_TYPE_UIELEMENTS;
    else if (fileType == XML_TYPE_ANIMATION_SETTINGS)
        return RESOURCE_TYPE_ANIMATION_SETTINGS;
    else if (fileType == XML_TYPE_RENDERPATH)
        return RESOURCE_TYPE_RENDERPATH;
    else if (fileType == XML_TYPE_TEXTURE_ATLAS)
        return RESOURCE_TYPE_TEXTURE_ATLAS;
    else if (fileType == XML_TYPE_2D_PARTICLE_EFFECT)
        return RESOURCE_TYPE_2D_PARTICLE_EFFECT;
    else if (fileType == XML_TYPE_TEXTURE_3D)
        return RESOURCE_TYPE_TEXTURE_3D;
    else if (fileType == XML_TYPE_CUBEMAP)
        return RESOURCE_TYPE_CUBEMAP;
    else if (fileType == XML_TYPE_SPRITER_DATA)
        return RESOURCE_TYPE_2D_ANIMATION_SET;
   
    // JSON fileTypes
    else if (fileType == JSON_TYPE_SCENE)
        return RESOURCE_TYPE_SCENE;
    else if (fileType == JSON_TYPE_NODE)
        return RESOURCE_TYPE_PREFAB;
    else if(fileType == JSON_TYPE_MATERIAL)
        return RESOURCE_TYPE_MATERIAL;
    else if(fileType == JSON_TYPE_TECHNIQUE)
        return RESOURCE_TYPE_TECHNIQUE;
    else if(fileType == JSON_TYPE_PARTICLEEFFECT)
        return RESOURCE_TYPE_PARTICLEEFFECT;
    else if(fileType == JSON_TYPE_PARTICLEEMITTER)
        return RESOURCE_TYPE_PARTICLEEMITTER;
    else if(fileType == JSON_TYPE_TEXTURE)
        return RESOURCE_TYPE_TEXTURE;
    else if(fileType == JSON_TYPE_ELEMENT)
        return RESOURCE_TYPE_UIELEMENT;
    else if(fileType == JSON_TYPE_ELEMENTS)
        return RESOURCE_TYPE_UIELEMENTS;
    else if (fileType == JSON_TYPE_ANIMATION_SETTINGS)
        return RESOURCE_TYPE_ANIMATION_SETTINGS;
    else if (fileType == JSON_TYPE_RENDERPATH)
        return RESOURCE_TYPE_RENDERPATH;
    else if (fileType == JSON_TYPE_TEXTURE_ATLAS)
        return RESOURCE_TYPE_TEXTURE_ATLAS;
    else if (fileType == JSON_TYPE_2D_PARTICLE_EFFECT)
        return RESOURCE_TYPE_2D_PARTICLE_EFFECT;
    else if (fileType == JSON_TYPE_TEXTURE_3D)
        return RESOURCE_TYPE_TEXTURE_3D;
    else if (fileType == JSON_TYPE_CUBEMAP)
        return RESOURCE_TYPE_CUBEMAP;
    else if (fileType == JSON_TYPE_SPRITER_DATA)
        return RESOURCE_TYPE_2D_ANIMATION_SET;

    // extension fileTypes
    else if (fileType == EXTENSION_TYPE_TTF)
        return RESOURCE_TYPE_FONT;
    else if (fileType == EXTENSION_TYPE_OTF)
        return RESOURCE_TYPE_FONT;
    else if (fileType == EXTENSION_TYPE_OGG)
        return RESOURCE_TYPE_SOUND;
    else if(fileType == EXTENSION_TYPE_WAV)
        return RESOURCE_TYPE_SOUND;
    else if(fileType == EXTENSION_TYPE_DDS)
        return RESOURCE_TYPE_IMAGE;
    else if(fileType == EXTENSION_TYPE_PNG)
        return RESOURCE_TYPE_IMAGE;
    else if(fileType == EXTENSION_TYPE_JPG)
        return RESOURCE_TYPE_IMAGE;
    else if(fileType == EXTENSION_TYPE_JPEG)
        return RESOURCE_TYPE_IMAGE;
    else if(fileType == EXTENSION_TYPE_BMP)
        return RESOURCE_TYPE_IMAGE;
    else if(fileType == EXTENSION_TYPE_TGA)
        return RESOURCE_TYPE_IMAGE;
    else if(fileType == EXTENSION_TYPE_KTX)
        return RESOURCE_TYPE_IMAGE;
    else if(fileType == EXTENSION_TYPE_PVR)
        return RESOURCE_TYPE_IMAGE;
    else if(fileType == EXTENSION_TYPE_OBJ)
        return RESOURCE_TYPE_UNUSABLE;
    else if(fileType == EXTENSION_TYPE_FBX)
        return RESOURCE_TYPE_UNUSABLE;
    else if(fileType == EXTENSION_TYPE_COLLADA)
        return RESOURCE_TYPE_UNUSABLE;
    else if(fileType == EXTENSION_TYPE_BLEND)
        return RESOURCE_TYPE_UNUSABLE;
    else if(fileType == EXTENSION_TYPE_ANGELSCRIPT)
        return RESOURCE_TYPE_SCRIPTFILE;
    else if(fileType == EXTENSION_TYPE_LUASCRIPT)
        return RESOURCE_TYPE_SCRIPTFILE;
    else if(fileType == EXTENSION_TYPE_HLSL)
        return RESOURCE_TYPE_UNUSABLE;
    else if(fileType == EXTENSION_TYPE_GLSL)
        return RESOURCE_TYPE_UNUSABLE;
    else if(fileType == EXTENSION_TYPE_FRAGMENTSHADER)
        return RESOURCE_TYPE_UNUSABLE;
    else if(fileType == EXTENSION_TYPE_VERTEXSHADER)
        return RESOURCE_TYPE_UNUSABLE;
    else if(fileType == EXTENSION_TYPE_HTML)
        return RESOURCE_TYPE_UNUSABLE;

    return RESOURCE_TYPE_UNKNOWN;
}

bool GetExtensionType(String path, StringHash &out fileType)
{
    StringHash type = StringHash(GetExtension(path));
    if (type == EXTENSION_TYPE_TTF)
        fileType = EXTENSION_TYPE_TTF;
    else if (type == EXTENSION_TYPE_OTF)
        fileType = EXTENSION_TYPE_OTF;
    else if (type == EXTENSION_TYPE_OGG)
        fileType = EXTENSION_TYPE_OGG;
    else if(type == EXTENSION_TYPE_WAV)
        fileType = EXTENSION_TYPE_WAV;
    else if(type == EXTENSION_TYPE_DDS)
        fileType = EXTENSION_TYPE_DDS;
    else if(type == EXTENSION_TYPE_PNG)
        fileType = EXTENSION_TYPE_PNG;
    else if(type == EXTENSION_TYPE_JPG)
        fileType = EXTENSION_TYPE_JPG;
    else if(type == EXTENSION_TYPE_JPEG)
        fileType = EXTENSION_TYPE_JPEG;
    else if(type == EXTENSION_TYPE_BMP)
        fileType = EXTENSION_TYPE_BMP;
    else if(type == EXTENSION_TYPE_TGA)
        fileType = EXTENSION_TYPE_TGA;
    else if(type == EXTENSION_TYPE_KTX)
        fileType = EXTENSION_TYPE_KTX;
    else if(type == EXTENSION_TYPE_PVR)
        fileType = EXTENSION_TYPE_PVR;
    else if(type == EXTENSION_TYPE_OBJ)
        fileType = EXTENSION_TYPE_OBJ;
    else if(type == EXTENSION_TYPE_FBX)
        fileType = EXTENSION_TYPE_FBX;
    else if(type == EXTENSION_TYPE_COLLADA)
        fileType = EXTENSION_TYPE_COLLADA;
    else if(type == EXTENSION_TYPE_BLEND)
        fileType = EXTENSION_TYPE_BLEND;
    else if(type == EXTENSION_TYPE_ANGELSCRIPT)
        fileType = EXTENSION_TYPE_ANGELSCRIPT;
    else if(type == EXTENSION_TYPE_LUASCRIPT)
        fileType = EXTENSION_TYPE_LUASCRIPT;
    else if(type == EXTENSION_TYPE_HLSL)
        fileType = EXTENSION_TYPE_HLSL;
    else if(type == EXTENSION_TYPE_GLSL)
        fileType = EXTENSION_TYPE_GLSL;
    else if(type == EXTENSION_TYPE_FRAGMENTSHADER)
        fileType = EXTENSION_TYPE_FRAGMENTSHADER;
    else if(type == EXTENSION_TYPE_VERTEXSHADER)
        fileType = EXTENSION_TYPE_VERTEXSHADER;
    else if(type == EXTENSION_TYPE_HTML)
        fileType = EXTENSION_TYPE_HTML;
    else
        return false;

    return true;
}

bool GetBinaryType(String path, StringHash &out fileType, bool useCache = false)
{   
    StringHash type;
    if (useCache)
    {
        File@ file = cache.GetFile(path);
        if (file is null)
            return false;

        if (file.size == 0)
            return false;

        type = StringHash(file.ReadFileID());
    }
    else
    {
        File@ file = File();
        if (!file.Open(path))
            return false;

        if (file.size == 0)
            return false;

        type = StringHash(file.ReadFileID());
    }

    if (type == BINARY_TYPE_SCENE)
        fileType = BINARY_TYPE_SCENE;
    else if (type == BINARY_TYPE_PACKAGE)
        fileType = BINARY_TYPE_PACKAGE;
    else if (type == BINARY_TYPE_COMPRESSED_PACKAGE)
        fileType = BINARY_TYPE_COMPRESSED_PACKAGE;
    else if (type == BINARY_TYPE_ANGLESCRIPT)
        fileType = BINARY_TYPE_ANGLESCRIPT;
    else if (type == BINARY_TYPE_MODEL)
        fileType = BINARY_TYPE_MODEL;
    else if (type == BINARY_TYPE_SHADER)
        fileType = BINARY_TYPE_SHADER;
    else if (type == BINARY_TYPE_ANIMATION)
        fileType = BINARY_TYPE_ANIMATION;
    else
        return false;

    return true;
}

bool GetXmlType(String path, StringHash &out fileType, bool useCache = false)
{
    String extension = GetExtension(path);
    if (extension == ".txt" || extension == ".json" || extension == ".icns" || extension == ".atlas")
        return false;

    String name;
    if (useCache)
    {
        XMLFile@ xml = cache.GetResource("XMLFile", path);
        if (xml is null)
            return false;

        name = xml.root.name;
    }
    else
    {
        File@ file = File();
        if (!file.Open(path))
            return false;

        if (file.size == 0)
            return false;

        XMLFile@ xml = XMLFile();
        if (xml.Load(file))
            name = xml.root.name;
        else
            return false;
    }

    bool found = false;
    if (!name.empty)
    {
        found = true;
        StringHash type = StringHash(name);
        if (type == XML_TYPE_SCENE)
            fileType = XML_TYPE_SCENE;
        else if (type == XML_TYPE_NODE)
            fileType = XML_TYPE_NODE;
        else if(type == XML_TYPE_MATERIAL)
            fileType = XML_TYPE_MATERIAL;
        else if(type == XML_TYPE_TECHNIQUE)
            fileType = XML_TYPE_TECHNIQUE;
        else if(type == XML_TYPE_PARTICLEEFFECT)
            fileType = XML_TYPE_PARTICLEEFFECT;
        else if(type == XML_TYPE_PARTICLEEMITTER)
            fileType = XML_TYPE_PARTICLEEMITTER;
        else if(type == XML_TYPE_TEXTURE)
            fileType = XML_TYPE_TEXTURE;
        else if(type == XML_TYPE_ELEMENT)
            fileType = XML_TYPE_ELEMENT;
        else if(type == XML_TYPE_ELEMENTS)
            fileType = XML_TYPE_ELEMENTS;
        else if (type == XML_TYPE_ANIMATION_SETTINGS)
            fileType = XML_TYPE_ANIMATION_SETTINGS;
        else if (type == XML_TYPE_RENDERPATH)
            fileType = XML_TYPE_RENDERPATH;
        else if (type == XML_TYPE_TEXTURE_ATLAS)
            fileType = XML_TYPE_TEXTURE_ATLAS;
        else if (type == XML_TYPE_2D_PARTICLE_EFFECT)
            fileType = XML_TYPE_2D_PARTICLE_EFFECT;
        else if (type == XML_TYPE_TEXTURE_3D)
            fileType = XML_TYPE_TEXTURE_3D;
        else if (type == XML_TYPE_CUBEMAP)
            fileType = XML_TYPE_CUBEMAP;
        else if (type == XML_TYPE_SPRITER_DATA)
            fileType = XML_TYPE_SPRITER_DATA;
        else
            found = false;
    }
    return found;
}

String ResourceTypeName(int resourceType)
{
    if (resourceType == RESOURCE_TYPE_UNUSABLE)
        return "Unusable";
    else if (resourceType == RESOURCE_TYPE_UNKNOWN)
        return "Unknown";
    else if (resourceType == RESOURCE_TYPE_NOTSET)
        return "Uninitialized";
    else if (resourceType == RESOURCE_TYPE_SCENE)
        return "Scene";
    else if (resourceType == RESOURCE_TYPE_SCRIPTFILE)
        return "Script File";
    else if (resourceType == RESOURCE_TYPE_MODEL)
        return "Model";
    else if (resourceType == RESOURCE_TYPE_MATERIAL)
        return "Material";
    else if (resourceType == RESOURCE_TYPE_ANIMATION)
        return "Animation";
    else if (resourceType == RESOURCE_TYPE_IMAGE)
        return "Image";
    else if (resourceType == RESOURCE_TYPE_SOUND)
        return "Sound";
    else if (resourceType == RESOURCE_TYPE_TEXTURE)
        return "Texture";
    else if (resourceType == RESOURCE_TYPE_FONT)
        return "Font";
    else if (resourceType == RESOURCE_TYPE_PREFAB)
        return "Prefab";
    else if (resourceType == RESOURCE_TYPE_TECHNIQUE)
        return "Render Technique";
    else if (resourceType == RESOURCE_TYPE_PARTICLEEFFECT)
        return "Particle Effect";
    else if (resourceType == RESOURCE_TYPE_PARTICLEEMITTER)
        return "Particle Emitter";
    else if (resourceType == RESOURCE_TYPE_UIELEMENT)
        return "UI Element";
    else if (resourceType == RESOURCE_TYPE_UIELEMENTS)
        return "UI Elements";
    else if (resourceType == RESOURCE_TYPE_ANIMATION_SETTINGS)
        return "Animation Settings";
    else if (resourceType == RESOURCE_TYPE_RENDERPATH)
        return "Render Path";
    else if (resourceType == RESOURCE_TYPE_TEXTURE_ATLAS)
        return "Texture Atlas";
    else if (resourceType == RESOURCE_TYPE_2D_PARTICLE_EFFECT)
        return "2D Particle Effect";
    else if (resourceType == RESOURCE_TYPE_TEXTURE_3D)
        return "Texture 3D";
    else if (resourceType == RESOURCE_TYPE_CUBEMAP)
        return "Cubemap";
    else if (resourceType == RESOURCE_TYPE_2D_ANIMATION_SET)
        return "2D Animation Set";
    else
        return "";
}

class BrowserDir
{
    uint id;
    String resourceKey;
    String name;
    Array<BrowserDir@> children;
    Array<BrowserFile@> files;

    BrowserDir(String path_)
    {
        resourceKey = path_;
        String parent = GetParentPath(path_);
        name = path_;
        name.Replace(parent, "");
        id = browserDirIndex++;
    }

    int opCmp(BrowserDir@ b)
    {
        return name.opCmp(b.name);
    }

    BrowserFile@ AddFile(String name, uint resourceSourceIndex, uint sourceType)
    {
        String path = resourceKey + "/" + name;
        BrowserFile@ file = BrowserFile(path, resourceSourceIndex, sourceType);
        files.Push(file);
        return file;
    }

}

class BrowserFile
{
    uint id;
    uint resourceSourceIndex;
    String resourceKey;
    String name;
    String fullname;
    String extension;
    StringHash fileType;
    int resourceType = 0;
    int sourceType = 0;
    int sortScore = 0;
    WeakHandle browserFileListRow;

    BrowserFile(String path_, uint resourceSourceIndex_, int sourceType_)
    {
        sourceType = sourceType_;
        resourceSourceIndex = resourceSourceIndex_;
        resourceKey = path_;
        name = GetFileName(path_);
        extension = GetExtension(path_);
        fullname = GetFileNameAndExtension(path_);
        id = browserFileIndex++;
    }

    int opCmp(BrowserFile@ b)
    {
        if (browserSearchSortMode == 1)
            return fullname.opCmp(b.fullname);
        else
            return sortScore - b.sortScore;
    }

    String GetResourceSource()
    {
        if (sourceType == BROWSER_FILE_SOURCE_RESOURCE_DIR)
            return cache.resourceDirs[resourceSourceIndex];
        else
            return "Unknown";
    }

    String GetFullPath()
    {
        return String(cache.resourceDirs[resourceSourceIndex] + resourceKey);
    }

    String GetPath()
    {
        return resourceKey;
    }

    void DetermainResourceType()
    {
        resourceType = GetResourceType(GetFullPath(), fileType, false);
        Text@ browserFileListRow_ = browserFileListRow.Get();
        if (browserFileListRow_ !is null)
        {
            InitializeBrowserFileListRow(browserFileListRow_, this);
        }
    }
    
    String ResourceTypeName()
    {
        return ::ResourceTypeName(resourceType);
    }

    void FileChanged()
    {
        if (!fileSystem.FileExists(GetFullPath()))
        {
        }
        else
        {
        }
    }
}

void CreateResourcePreview(String path, Node@ previewNode)
{
    resourceBrowserPreview.autoUpdate = false;
    int resourceType = GetResourceType(path); 
    if (resourceType > 0)
    {
        File file;
        file.Open(path);

        if (resourceType == RESOURCE_TYPE_MODEL)
        {
            Model@ model = Model();
            if (model.Load(file))
            {
                StaticModel@ staticModel = previewNode.CreateComponent("StaticModel");
                staticModel.model = model;
                return;
            }
        }
        else if (resourceType == RESOURCE_TYPE_MATERIAL)
        {
            Material@ material = Material();
            if (material.Load(file))
            {
                StaticModel@ staticModel = previewNode.CreateComponent("StaticModel");
                staticModel.model = cache.GetResource("Model", "Models/Sphere.mdl");
                staticModel.material = material;
                return;
            }
        }
        else if (resourceType == RESOURCE_TYPE_IMAGE)
        {
            Image@ image = Image();
            if (image.Load(file))
            {
                StaticModel@ staticModel = previewNode.CreateComponent("StaticModel");
                staticModel.model = cache.GetResource("Model", "Models/Editor/ImagePlane.mdl");
                Material@ material =  cache.GetResource("Material", "Materials/Editor/TexturedUnlit.xml");
                Texture2D@ texture = Texture2D();
                texture.SetData(@image, true);
                material.textures[0] = texture;
                staticModel.material = material;
                return;
            }
        }
        else if (resourceType == RESOURCE_TYPE_PREFAB)
        {
            if (GetExtension(path) == ".xml")
            {
                XMLFile xmlFile;
                if(xmlFile.Load(file))
                    if(previewNode.LoadXML(xmlFile.root, true) && (previewNode.GetComponents("StaticModel", true).length > 0 || previewNode.GetComponents("AnimatedModel", true).length > 0))
                    {
                        return;
                    }
            }
            else if(previewNode.Load(file, true) && (previewNode.GetComponents("StaticModel", true).length > 0 || previewNode.GetComponents("AnimatedModel", true).length > 0))
                return;

            previewNode.RemoveAllChildren();
            previewNode.RemoveAllComponents();
        }
        else if (resourceType == RESOURCE_TYPE_PARTICLEEFFECT)
        {
            ParticleEffect@ particleEffect = ParticleEffect();
            if (particleEffect.Load(file))
            {
                ParticleEmitter@ particleEmitter = previewNode.CreateComponent("ParticleEmitter");
                particleEmitter.effect = particleEffect;
                particleEffect.activeTime = 0.0;
                particleEmitter.Reset();
                resourceBrowserPreview.autoUpdate = true;
                return;
            }
        }
    }

    StaticModel@ staticModel = previewNode.CreateComponent("StaticModel");
    staticModel.model = cache.GetResource("Model", "Models/Editor/ImagePlane.mdl");
    Material@ material =  cache.GetResource("Material", "Materials/Editor/TexturedUnlit.xml");
    Texture2D@ texture = Texture2D();
    Image@ noPreviewImage = cache.GetResource("Image", "Textures/Editor/NoPreviewAvailable.png");
    texture.SetData(noPreviewImage, false);
    material.textures[0] = texture;
    staticModel.material = material;

    return;
}

void RotateResourceBrowserPreview(StringHash eventType, VariantMap& eventData)
{
    int elemX = eventData["ElementX"].GetInt();
    int elemY = eventData["ElementY"].GetInt();
    
    if (resourceBrowserPreview.height > 0 && resourceBrowserPreview.width > 0)
    {
        float yaw = ((resourceBrowserPreview.height / 2) - elemY) * (90.0 / resourceBrowserPreview.height);
        float pitch = ((resourceBrowserPreview.width / 2) - elemX) * (90.0 / resourceBrowserPreview.width);

        resourcePreviewNode.rotation = resourcePreviewNode.rotation.Slerp(Quaternion(yaw, pitch, 0), 0.1);
        RefreshBrowserPreview();
    }
}

void RefreshBrowserPreview()
{
    resourceBrowserPreview.QueueUpdate();
}

class ResourceType
{
    int id;
    String name;
    ResourceType(int id_, String name_)
    {
        id = id_;
        name = name_;
    }
    int opCmp(ResourceType@ b)
    {
        return name.opCmp(b.name);
    }
}
