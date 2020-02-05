
// Urho3D terrain editor

const uint TERRAIN_EDITMODE_RAISELOWERHEIGHT = 0, TERRAIN_EDITMODE_SETHEIGHT = 1, TERRAIN_EDITMODE_SMOOTHHEIGHT = 3,
      TERRAIN_EDITMODE_PAINTBRUSH = 4, TERRAIN_EDITMODE_PAINTTREES = 5, TERRAIN_EDITMODE_PAINTFOLIAGE = 6;

funcdef bool TerrainEditorShowCallback();

class TerrainEditorUpdateChanges {
    IntVector2 offset;
    Image@ oldImage;
    Image@ newImage;
}

class TerrainEditorBrushVisualizer
{
    Node@ node;
    CustomGeometry@ customGeometry;
    private bool addedToOctree = false;

    void Create()
    {
        node = Node();
        customGeometry = node.CreateComponent("CustomGeometry");
        customGeometry.numGeometries = 1;
        customGeometry.material = cache.GetResource("Material", "Materials/VColUnlit.xml");
        customGeometry.occludee = false;
        customGeometry.enabled = true;
    }

    void Hide()
    {
        node.enabled = false;
        addedToOctree = false;
    }

    void Update(Terrain@ terrainComponent, Vector3 position, float radius)
    {
        node.enabled = true;
        node.position = Vector3(position.x, 0, position.z);

        // Generate the circle
        customGeometry.BeginGeometry(0, LINE_STRIP);
        for (uint i = 0; i < 364; i += 4)
        {
            float angle = i * M_PI / 180;
            float x = radius * Cos(angle / 0.0174532925);
            float z = radius * Sin(angle / 0.0174532925);
            float y = terrainComponent.GetHeight(Vector3(position.x + x, 0, position.z + z));
            customGeometry.DefineVertex(Vector3(x, y + 0.25, z));
            customGeometry.DefineColor(Color(0, 1, 0));
        }
        customGeometry.Commit();

        if (editorScene.octree !is null && addedToOctree == false)
        {
            editorScene.octree.AddManualDrawable(customGeometry);
            addedToOctree = true;
        }
    }
}

class TerrainEditor
{
    private bool dirty = true;
    private uint editMode = 0;

    private Window@ window;
    private UIElement@ toolbar;
    private Text@ currentToolDescText;
    private Array<Image@> brushes;
    private CheckBox@ selectedBrush;
    private Image@ selectedBrushImage;
    private Image@ scaledSelectedBrushImage;
    private Slider@ brushSizeSlider;
    private Slider@ brushOpacitySlider;
    private Slider@ brushHeightSlider;
    private TerrainEditorBrushVisualizer brushVisualizer;

    private Array<Terrain@> terrainsEdited;

    private Color targetColor;
    bool targetColorSelected = false;

    // Create the Terrain Editor window and initialize it
    void Create()
    {
        if (window !is null)
            return;

        window = LoadEditorUI("UI/EditorTerrainWindow.xml");
        ui.root.AddChild(window);
        window.opacity = uiMaxOpacity;

        BorderImage@ currentToolDesc = window.GetChild("CurrentToolDesc", true);
        currentToolDesc.layoutBorder = IntRect(8, 8, 8, 8);

        currentToolDescText = window.GetChild("CurrentToolDescText", true);

        ListView@ brushesContainer = window.GetChild("BrushesContainer", true);
        brushesContainer.SetScrollBarsVisible(true, false);
        brushesContainer.contentElement.layoutMode = LM_HORIZONTAL;
        brushesContainer.SetFixedHeight(84);

        BorderImage@ settingsArea = window.GetChild("SettingsArea", true);
        settingsArea.layoutBorder = IntRect(8, 8, 8, 8);

        LineEdit@ createTerrainValue = window.GetChild("CreateTerrainValue", true);
        createTerrainValue.text = "1024";

        brushSizeSlider = window.GetChild("BrushSize", true);
        brushOpacitySlider = window.GetChild("BrushOpacity", true);
        brushHeightSlider = window.GetChild("BrushHeight", true);

        window.height = 300;
        window.SetPosition(ui.root.width - 10 - window.width, attributeInspectorWindow.position.y + attributeInspectorWindow.height + 10);

        SubscribeToEvent(window.GetChild("RaiseLowerHeight", true), "Toggled", "OnEditModeSelected");
        SubscribeToEvent(window.GetChild("SetHeight", true), "Toggled", "OnEditModeSelected");
        SubscribeToEvent(window.GetChild("SmoothHeight", true), "Toggled", "OnEditModeSelected");
        //SubscribeToEvent(window.GetChild("PaintBrush", true), "Toggled", "OnEditModeSelected");
        //SubscribeToEvent(window.GetChild("PaintTrees", true), "Toggled", "OnEditModeSelected");
        //SubscribeToEvent(window.GetChild("PaintFoliage", true), "Toggled", "OnEditModeSelected");
        SubscribeToEvent(window.GetChild("CloseButton", true), "Released", "Hide");
        SubscribeToEvent(window.GetChild("CreateTerrainButton", true), "Released", "CreateTerrain");
        SubscribeToEvent(window.GetChild("ResetButton", true), "Released", "ResetWindow");
        SubscribeToEvent(brushSizeSlider, "DragEnd", "UpdateScaledBrush");

        LoadBrushes();
        Show();

        brushVisualizer.Create();
    }

    void ResetWindow()
    {
        // Reset edit mode to default
        SetEditMode(TERRAIN_EDITMODE_RAISELOWERHEIGHT, "Raise or lower terrain");

        // Clear selected brush
        ClearSelectedBrush();
    }

    void ClearSelectedBrush()
    {
        selectedBrush = null;
        selectedBrushImage = null;
        scaledSelectedBrushImage = null;

        ListView@ terrainBrushes = window.GetChild("BrushesContainer", true);

        for (uint i = 0; i < terrainBrushes.numItems; ++i)
        {
            CheckBox@ checkbox = cast<CheckBox>(terrainBrushes.items[i]);
            checkbox.checked = false;
            checkbox.enabled = true;
        }
    }
	
    // Hide the window
    void Hide()
    {
        ClearSelectedBrush();
        window.visible = false;
    }

    void HideBrushVisualizer()
    {
        brushVisualizer.Hide();
    }

    void UpdateBrushVisualizer(Terrain@ terrainComponent, Vector3 position)
    {
        if (scaledSelectedBrushImage is null)
        {
            brushVisualizer.Hide();
            return;
        }

        if (window.visible == true)
            brushVisualizer.Update(terrainComponent, position, scaledSelectedBrushImage.width / 2);
    }

    // Save all the terrains we have edited
    void Save()
    {
        for (uint i = 0; i < terrainsEdited.length; ++i)
        {
            // Make sure its not null (it may have been deleted since last save)
            if (terrainsEdited[i] !is null)
            {
                String fileLocation = sceneResourcePath + terrainsEdited[i].GetAttribute("Height Map").GetResourceRef().name;

                Array<String> chunks = fileLocation.Split('/');
                Array<String> parts = chunks[chunks.length - 1].Split('.');
                String fileType = parts[1];

                if (fileType == "png")
                {
                    terrainsEdited[i].heightMap.SavePNG(fileLocation);
                }
                else if (fileType == "jpg")
                {
                    // Save with the highest quality
                    terrainsEdited[i].heightMap.SaveJPG(fileLocation, 100);
                }
                else if (fileType == "bmp")
                {
                    terrainsEdited[i].heightMap.SaveBMP(fileLocation);
                }
                else if (fileType == "tga")
                {
                    terrainsEdited[i].heightMap.SaveTGA(fileLocation);
                }
            }
        }
        // Clean up terrainsEdited array by clearing it
        // (this will remove any terrains that may have been deleted)
        terrainsEdited.Clear();
    }

    // Show the window
    bool Show()
    {
        window.visible = true;
        window.BringToFront();
        return true;
    }

    // Update the UI
    void UpdateDirty()
    {
        if (!dirty)
            return;

        CheckBox@ raiseLowerHeight = window.GetChild("RaiseLowerHeight", true);
        CheckBox@ setHeight = window.GetChild("SetHeight", true);
        CheckBox@ smoothHeight = window.GetChild("SmoothHeight", true);
        //CheckBox@ paintBrush = window.GetChild("PaintBrush", true);
        //CheckBox@ paintTrees = window.GetChild("PaintTrees", true);
        //CheckBox@ paintFoliage = window.GetChild("PaintFoliage", true);

        raiseLowerHeight.checked = (editMode == TERRAIN_EDITMODE_RAISELOWERHEIGHT) ? true : false;
        setHeight.checked = (editMode == TERRAIN_EDITMODE_SETHEIGHT) ? true : false;
        smoothHeight.checked = (editMode == TERRAIN_EDITMODE_SMOOTHHEIGHT) ? true : false;
        //paintBrush.checked = (editMode == TERRAIN_EDITMODE_PAINTBRUSH) ? true : false;
        //paintTrees.checked = (editMode == TERRAIN_EDITMODE_PAINTTREES) ? true : false;
        //paintFoliage.checked = (editMode == TERRAIN_EDITMODE_PAINTFOLIAGE) ? true : false;

        raiseLowerHeight.enabled = !raiseLowerHeight.checked;
        setHeight.enabled = !setHeight.checked;
        smoothHeight.enabled = !smoothHeight.checked;

        ListView@ terrainBrushes = window.GetChild("BrushesContainer", true);

        for (uint i = 0; i < terrainBrushes.numItems; ++i)
        {
            CheckBox@ checkbox = cast<CheckBox>(terrainBrushes.items[i]);
            checkbox.checked = terrainBrushes.items[i] is selectedBrush;
            checkbox.enabled = !checkbox.checked;
        }

        dirty = false;
    }

    // This gets called when we want to do something to a terrain
    void Work(Terrain@ terrainComponent, Vector3 position)
    {
        // Only work if a brush is selected
        if (selectedBrushImage is null || scaledSelectedBrushImage is null || window.visible == false)
            return;

        SetSceneModified();

        // Add that terrain to the terrainsEdited if its not already in there
        if (terrainsEdited.FindByRef(terrainComponent) == -1)
            terrainsEdited.Push(terrainComponent);

        TerrainEditorUpdateChanges@ updateChanges = TerrainEditorUpdateChanges();

        IntVector2 pos = terrainComponent.WorldToHeightMap(position);

        switch (editMode)
        {
        case TERRAIN_EDITMODE_RAISELOWERHEIGHT:
            UpdateTerrainRaiseLower(terrainComponent.heightMap, pos, updateChanges);
            break;
        case TERRAIN_EDITMODE_SETHEIGHT:
            UpdateTerrainSetHeight(terrainComponent.heightMap, pos, updateChanges);
            break;
        case TERRAIN_EDITMODE_SMOOTHHEIGHT:
            UpdateTerrainSmooth(terrainComponent.heightMap, pos, updateChanges);
            break;
        }

        terrainComponent.ApplyHeightMap();

        UpdateBrushVisualizer(terrainComponent, position);

        ModifyTerrainAction action;
        action.Define(terrainComponent, updateChanges.offset, updateChanges.oldImage, updateChanges.newImage);
        SaveEditAction(action);
    }

    private uint NearestPowerOf2(uint value) {
        if (value < 2)
            return 2;

        for (uint i = 1; i <= 2048; i *= 2)
        {
            if (value == i)
                return i;

            if (value < i || value > i * 2)
                continue;

            return value < (i + (i / 2)) ? i : i * 2;
        }

        return 2048;
    }

    private void CreateTerrain()
    {
        String fileName = "Textures/heightmap-" + time.timeSinceEpoch  + ".png";
        String fileLocation = sceneResourcePath + fileName;

        Node@ node = CreateNode(LOCAL);
        node.position = Vector3(0, 0, 0);

        LineEdit@ lineEdit = window.GetChild("CreateTerrainValue", true);

        uint lineEditLength = lineEdit.text.Trimmed().ToUInt();

        // The parse failed, so use a decent default
        if (lineEditLength == 0)
            lineEditLength = 1024;

        Image@ image = Image();
        uint length = NearestPowerOf2(lineEditLength) + 1;
        image.SetSize(length, length, 3);

        UpdateTerrainSetConstantHeight(image, 0);

        if (!fileSystem.DirExists(GetPath(fileLocation)))
            fileSystem.CreateDir(GetPath(fileLocation));
        image.SavePNG(fileLocation);

        Terrain@ terrain = node.CreateComponent("Terrain");
        terrain.heightMap = image;

        Resource@ res = cache.GetResource("Image", fileLocation);

        ResourceRef ref = ResourceRef();
        ref.type = res.type;
        ref.name = fileName;
        terrain.SetAttribute("Height Map", Variant(ref));
        terrain.ApplyAttributes();

        SelectComponent(terrain, false);
    }

    // Utility function, returns the difference of the two numbers
    private float Difference(float a, float b)
    {
        return (a > b) ? a - b : b - a;
    }

    // Returns a brush based on its name (its filename minus the extension)
    private Image@ GetBrushImage(String brushName)
    {
        for (uint i = 0; i < brushes.length; ++i)
        {
            if (brushes[i].name == brushName)
            {
                return brushes[i];
            }
        }

        return null;
    }

    // Creates a brush element
    private UIElement@ LoadBrush(String fileLocation)
    {
        Array<String> chunks = fileLocation.Split('/');
        Array<String> parts = chunks[chunks.length - 1].Split('.');

        // We use this when editing the terrain
        Image@ image = cache.GetResource("Image", fileLocation);
        if (image is null)
            return null;

        image.name = parts[0];
        brushes.Push(image);

        // This is for the brush icon
        Texture2D@ texture = cache.GetResource("Texture2D", fileLocation);

        CheckBox@ brush = CheckBox(parts[0]);
        brush.defaultStyle = uiStyle;
        brush.style = "TerrainEditorCheckbox";
        brush.SetFixedSize(64, 64);
        SubscribeToEvent(brush, "Toggled", "OnBrushSelected");

        BorderImage@ icon = BorderImage("Icon");
        icon.defaultStyle = iconStyle;
        icon.texture = texture;
        icon.imageRect = IntRect(0, 0, texture.width, texture.height);
        icon.SetFixedSize(64, 64);
        brush.AddChild(icon);

        return brush;
    }

    // Loads all the brushes from a hard-coded folder
    private void LoadBrushes()
    {
        ListView@ terrainBrushes = window.GetChild("BrushesContainer", true);
        String brushPath = "Textures/Editor/TerrainBrushes/";

        Array<String>@ resourceDirs = cache.resourceDirs;
        String brushesFileLocation;

        for (uint i = 0; i < resourceDirs.length; ++i)
        {
            brushesFileLocation = resourceDirs[i] + brushPath;
            if (fileSystem.DirExists(brushesFileLocation))
                break;
        }

        if (brushesFileLocation.empty)
            return;

        Array<String> files = fileSystem.ScanDir(brushesFileLocation, "*.*", SCAN_FILES, false);

        for (uint i = 0; i < files.length; ++i)
        {
            UIElement@ brush = LoadBrush(brushPath + files[i]);
            if (brush !is null)
                terrainBrushes.AddItem(brush);
        }
    }

    private void OnEditModeSelected(StringHash eventType, VariantMap& eventData)
    {
        CheckBox@ edit = eventData["Element"].GetPtr();

        if (!edit.checked)
            return;

        if (edit.name == "RaiseLowerHeight")
            SetEditMode(TERRAIN_EDITMODE_RAISELOWERHEIGHT, "Raise or lower terrain");

        else if (edit.name == "SetHeight")
            SetEditMode(TERRAIN_EDITMODE_SETHEIGHT, "Set height to specified height");

        else if (edit.name == "SmoothHeight")
            SetEditMode(TERRAIN_EDITMODE_SMOOTHHEIGHT, "Smooth the terrain");

        else if (edit.name == "PaintBrush")
            SetEditMode(TERRAIN_EDITMODE_PAINTBRUSH, "Paint textures onto the terrain");

        else if (edit.name == "PaintTrees")
            SetEditMode(TERRAIN_EDITMODE_PAINTTREES, "Paint trees onto the terrain");

        else if (edit.name == "PaintFoliage")
            SetEditMode(TERRAIN_EDITMODE_PAINTFOLIAGE, "Paint foliage onto the terrain");
    }

    private void OnBrushSelected(StringHash eventType, VariantMap& eventData)
    {
        CheckBox@ checkbox = cast<CheckBox>(eventData["Element"].GetPtr());
        if (checkbox.checked == false)
            return;
        selectedBrush = checkbox;
        selectedBrushImage = GetBrushImage(selectedBrush.name);
        UpdateScaledBrush();
        dirty = true;
    }

    private void SetEditMode(uint mode, String description)
    {
        window.GetChild("BrushOpacityLabel", true).visible = (mode == TERRAIN_EDITMODE_RAISELOWERHEIGHT);
        window.GetChild("BrushHeightLabel", true).visible = (mode == TERRAIN_EDITMODE_SETHEIGHT);

        window.GetChild("BrushOpacity", true).visible = (mode == TERRAIN_EDITMODE_RAISELOWERHEIGHT);
        window.GetChild("BrushHeight", true).visible = (mode == TERRAIN_EDITMODE_SETHEIGHT);

        editMode = mode;
        currentToolDescText.text = description;
        dirty = true;

        // force the window to resize its height to fit its children
        window.height = 0;
    }

    // Utility function, returns the smaller of the two numbers
    private float Smaller(float a, float b)
    {
        return (a > b) ? b : a;
    }

    private void UpdateScaledBrush()
    {
        if (selectedBrushImage is null)
            return;
        float size = (brushSizeSlider.value / 25) + 0.5;
        scaledSelectedBrushImage = selectedBrushImage.GetSubimage(IntRect(0, 0, selectedBrushImage.width, selectedBrushImage.height));
        scaledSelectedBrushImage.Resize(int(selectedBrushImage.width * size), int(selectedBrushImage.height * size));
    }

    private void UpdateTerrainRaiseLower(Image@ terrainImage, IntVector2 position, TerrainEditorUpdateChanges@ updateChanges)
    {
        uint brushImageWidth = scaledSelectedBrushImage.width;
        uint brushImageHeight = scaledSelectedBrushImage.height;

        updateChanges.offset = IntVector2(position.x - (brushImageWidth / 2), position.y - (brushImageHeight / 2));
        if (updateChanges.offset.x < 0) updateChanges.offset.x = 0;
        if (updateChanges.offset.y < 0) updateChanges.offset.y = 0;

        IntRect boundsRect = IntRect(updateChanges.offset.x, updateChanges.offset.y, updateChanges.offset.x + brushImageWidth, updateChanges.offset.y + brushImageHeight);
        boundsRect = ClipIntRectToHeightmapBounds(terrainImage, boundsRect);

        updateChanges.oldImage = terrainImage.GetSubimage(boundsRect);

        // lower or raise (respectively), multiply this by the brush opacity
        float opacity = brushOpacitySlider.value / 25;
        float modifier = (input.keyDown[KEY_SHIFT] ? -opacity : opacity) * 0.05;

        // Iterate over the entire brush image
        for (int y = 0; y < brushImageHeight; ++y)
        {
            for (int x = 0; x < brushImageWidth; ++x)
            {
                // Get the current terrain height at that position (centred to the brush's size)
                IntVector2 pos = IntVector2(position.x + x - (brushImageWidth / 2), position.y + y - (brushImageHeight / 2));
                Color newColor = terrainImage.GetPixel(pos.x, pos.y);
                Color brushColor = scaledSelectedBrushImage.GetPixel(x, y);
                // Now apply the brush to the terrain (we only use the alpha)
                newColor.r += brushColor.a * modifier;
                newColor.g += brushColor.a * modifier;
                newColor.b += brushColor.a * modifier;
                terrainImage.SetPixel(pos.x, pos.y, newColor);
            }
        }

        // Smooth the terrain a bit
        TerrainEditorUpdateChanges@ smoothUpdateChanges = TerrainEditorUpdateChanges();
        UpdateTerrainSmooth(terrainImage, position, smoothUpdateChanges);

        updateChanges.newImage = smoothUpdateChanges.newImage;
    }

    private void UpdateTerrainSmooth(Image@ terrainImage, IntVector2 position, TerrainEditorUpdateChanges@ updateChanges)
    {
        uint brushImageWidth = scaledSelectedBrushImage.width;
        uint brushImageHeight = scaledSelectedBrushImage.height;

        updateChanges.offset = IntVector2(position.x - (brushImageWidth / 2), position.y - (brushImageHeight / 2));
        if (updateChanges.offset.x < 0) updateChanges.offset.x = 0;
        if (updateChanges.offset.y < 0) updateChanges.offset.y = 0;

        IntRect boundsRect = IntRect(updateChanges.offset.x, updateChanges.offset.y, updateChanges.offset.x + brushImageWidth, updateChanges.offset.y + brushImageHeight);
        boundsRect = ClipIntRectToHeightmapBounds(terrainImage, boundsRect);

        updateChanges.oldImage = terrainImage.GetSubimage(boundsRect);

        // Iterate over the entire brush image
        for (int y = 0; y < brushImageHeight; ++y)
        {
            for (int x = 0; x < brushImageWidth; ++x)
            {
                Color brushColor = scaledSelectedBrushImage.GetPixel(x, y);

                // Only take opaque pixels into consideration for now
                if (brushColor.a == 0)
                    continue;

                // Get the current terrain height at that position (centred to the brush's size)
                IntVector2 pos = IntVector2(position.x + x - (brushImageWidth / 2), position.y + y - (brushImageHeight / 2));

                // Make sure the pixel we're working on is atleast one pixel inside the terrainImage
                // as we need an adjacent pixel on all sides for the smoothing algorithm to work
                if (pos.x < 0 || pos.y < 0 || pos.x > terrainImage.width - 1 || pos.y > terrainImage.height - 1)
                    continue;

                Color brp = terrainImage.GetPixel(pos.x + 1, pos.y + 1); // bottomRightPixel
                Color rp = terrainImage.GetPixel(pos.x + 1, pos.y);      // rightPixel
                Color trp = terrainImage.GetPixel(pos.x + 1, pos.y - 1); // topRightPixel
                Color blp = terrainImage.GetPixel(pos.x - 1, pos.y + 1); // bottomLeftPixel
                Color lp = terrainImage.GetPixel(pos.x - 1, pos.y);      // leftPixel
                Color tlp = terrainImage.GetPixel(pos.x - 1, pos.y - 1); // topLeftPixel
                Color bp = terrainImage.GetPixel(pos.x, pos.y + 1);      // bottomPixel
                Color cp = terrainImage.GetPixel(pos.x, pos.y);          // centerPixel
                Color tp = terrainImage.GetPixel(pos.x, pos.y - 1);      // topPixel

                Color avgColor = Color(
                    ((brp.r + rp.r + trp.r + blp.r + lp.r + tlp.r + bp.r + cp.r + tp.r) / 9),
                    ((brp.g + rp.g + trp.g + blp.g + lp.g + tlp.g + bp.g + cp.g + tp.g) / 9),
                    ((brp.b + rp.b + trp.b + blp.b + lp.b + tlp.b + bp.b + cp.b + tp.b) / 9)
                );

                Color newColor = Color(
                    (Difference(cp.r, avgColor.r) * brushColor.a) + Smaller(cp.r, avgColor.r),
                    (Difference(cp.g, avgColor.g) * brushColor.a) + Smaller(cp.g, avgColor.g),
                    (Difference(cp.b, avgColor.b) * brushColor.a) + Smaller(cp.b, avgColor.b)
                );

                terrainImage.SetPixel(position.x + x - (brushImageWidth / 2), position.y + y - (brushImageHeight / 2), avgColor);
            }
        }

        updateChanges.newImage = terrainImage.GetSubimage(boundsRect);
    }

    private void UpdateTerrainSetHeight(Image@ terrainImage, IntVector2 position, TerrainEditorUpdateChanges@ updateChanges)
    {
        uint brushImageWidth = scaledSelectedBrushImage.width;
        uint brushImageHeight = scaledSelectedBrushImage.height;

        updateChanges.offset = IntVector2(position.x - (brushImageWidth / 2), position.y - (brushImageHeight / 2));
        if (updateChanges.offset.x < 0) updateChanges.offset.x = 0;
        if (updateChanges.offset.y < 0) updateChanges.offset.y = 0;

        IntRect boundsRect = IntRect(updateChanges.offset.x, updateChanges.offset.y, updateChanges.offset.x + brushImageWidth, updateChanges.offset.y + brushImageHeight);
        boundsRect = ClipIntRectToHeightmapBounds(terrainImage, boundsRect);

        updateChanges.oldImage = terrainImage.GetSubimage(boundsRect);

        float targetHeight = brushHeightSlider.value / 25;

        // Iterate over the entire brush image
        for (int y = 0; y < brushImageHeight; ++y)
        {
            for (int x = 0; x < brushImageWidth; ++x)
            {
                // Get the current terrain height at that position (centred to the brush's size)
                IntVector2 pos = IntVector2(position.x + x - (brushImageWidth / 2), position.y + y - (brushImageHeight / 2));
                Color newColor = terrainImage.GetPixel(pos.x, pos.y);
                Color brushColor = scaledSelectedBrushImage.GetPixel(x, y);
                // Ease the height to the target height (using the brush alpha as the 'speed'), making sure the alpha isn't 0
                newColor.r += (targetHeight - newColor.r) * brushColor.a;
                newColor.g += (targetHeight - newColor.g) * brushColor.a;
                newColor.b += (targetHeight - newColor.b) * brushColor.a;
                // Set it to target if its close enough
                if (Difference(targetHeight, newColor.r) < 0.01f) newColor.r = targetHeight;
                if (Difference(targetHeight, newColor.g) < 0.01f) newColor.g = targetHeight;
                if (Difference(targetHeight, newColor.b) < 0.01f) newColor.b = targetHeight;
                terrainImage.SetPixel(pos.x, pos.y, newColor);
            }
        }

        updateChanges.newImage = terrainImage.GetSubimage(boundsRect);
    }

    private void UpdateTerrainSetConstantHeight(Image@ terrainImage, float height)
    {
        height = Clamp(height, 0.0, 1.0);
        Color newColor = Color(height, height, height);
        // Iterate over the entire brush image
        for (int y = 0; y < terrainImage.height; ++y)
        {
            for (int x = 0; x < terrainImage.width; ++x)
            {
                terrainImage.SetPixel(x, y, newColor);
            }
        }
    }

    private IntRect ClipIntRectToHeightmapBounds(Image@ terrainImage, IntRect intRect) {
        if (intRect.left > terrainImage.width)
            intRect.left = terrainImage.width;

        if (intRect.right > terrainImage.width)
            intRect.right = terrainImage.width;

        if (intRect.top > terrainImage.height)
            intRect.top = terrainImage.height;

        if (intRect.bottom > terrainImage.height)
            intRect.bottom = terrainImage.height;

        return intRect;
    }
}
