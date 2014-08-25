// Urho3D terrain editor

const uint TERRAIN_EDITMODE_RAISELOWERHEIGHT = 0, TERRAIN_EDITMODE_SETHEIGHT = 1, TERRAIN_EDITMODE_SMOOTHHEIGHT = 3, 
	  TERRAIN_EDITMODE_PAINTBRUSH = 4, TERRAIN_EDITMODE_PAINTTREES = 5, TERRAIN_EDITMODE_PAINTFOLIAGE = 6;

funcdef bool TerrainEditorShowCallback();

class TerrainEditor
{
	bool dirty = true;
	uint editMode = 0;

	Window@ window;
	UIElement@ toolbar;
	Text@ currentToolDescText;
	Array<Image@> brushes;
	CheckBox@ selectedBrush;
	Image@ selectedBrushImage;
	
	Array<Terrain@> terrainsEdited;
	
	Color targetColor;
	bool targetColorSelected = false;

	// Create the Terrain Editor window and initialize it
	void Create()
	{
		if (window !is null)
			return;

		window = ui.LoadLayout(cache.GetResource("XMLFile", "UI/EditorTerrainWindow.xml"));
		ui.root.AddChild(window);
		window.opacity = uiMaxOpacity;
		
		UIElement@ terrainToolsGroup = CreateGroup("TerrainToolsGroup", LM_HORIZONTAL);
		terrainToolsGroup.horizontalAlignment = HA_CENTER;
		terrainToolsGroup.AddChild(CreateToolBarToggle("RaiseLowerHeight"));
		terrainToolsGroup.AddChild(CreateToolBarToggle("SetHeight"));
		terrainToolsGroup.AddChild(CreateToolBarToggle("SmoothHeight"));
		terrainToolsGroup.AddChild(CreateToolBarToggle("PaintBrush"));
		terrainToolsGroup.AddChild(CreateToolBarToggle("PaintTrees"));
		terrainToolsGroup.AddChild(CreateToolBarToggle("PaintFoliage"));
		FinalizeGroupHorizontal(terrainToolsGroup, "ToolBarToggle");
		window.AddChild(terrainToolsGroup);

		BorderImage@ currentToolDesc = BorderImage("CurrentToolDesc");
		currentToolDesc.style = "EditorToolBar";
		currentToolDesc.SetLayout(LM_HORIZONTAL);
		currentToolDesc.layoutSpacing = 4;
		currentToolDesc.layoutBorder = IntRect(8, 4, 4, 8);
		currentToolDesc.minHeight = 64;
		currentToolDesc.maxHeight = 64;
		currentToolDesc.horizontalAlignment = HA_CENTER;
		currentToolDesc.opacity = uiMaxOpacity;
		currentToolDesc.SetPosition(0, 0);
		window.AddChild(currentToolDesc);
		
		currentToolDescText = Text("CurrentToolDescText");
		currentToolDescText.text = "Raise or lower terrain using the current brush";
		currentToolDescText.SetStyleAuto(uiStyle);
		currentToolDescText.wordwrap = true;
		currentToolDescText.color = Color(1.0f, 1.0, 1.0f, 1.0f);
		currentToolDescText.position = IntVector2(16, 16);
		currentToolDescText.SetFont(cache.GetResource("Font", "Fonts/BlueHighway.ttf"), 10);
		currentToolDesc.AddChild(currentToolDescText);
		
		Text@ brushesText = Text("BrushesText");
		brushesText.text = "Brushes";
		brushesText.SetStyleAuto(uiStyle);
		brushesText.color = Color(1.0f, 1.0, 1.0f, 1.0f);
		brushesText.SetFont(cache.GetResource("Font", "Fonts/BlueHighway.ttf"), 10);
		window.AddChild(brushesText);
		
		ListView@ brushesContainer = ListView("BrushesContainer");
		brushesContainer.defaultStyle = uiStyle;
		brushesContainer.style = "ListView";
		brushesContainer.layoutSpacing = 4;
		brushesContainer.internal = false;
		brushesContainer.layoutBorder = IntRect(8, 4, 4, 8);
		brushesContainer.opacity = uiMaxOpacity;
		brushesContainer.SetScrollBarsVisible(true, false);
		brushesContainer.contentElement.layoutMode = LM_HORIZONTAL;
		brushesContainer.SetFixedHeight(84);
		window.AddChild(brushesContainer);
		
		Text@ settingsText = Text("SettingsText");
		settingsText.text = "Settings";
		settingsText.SetStyleAuto(uiStyle);
		settingsText.color = Color(1.0f, 1.0, 1.0f, 1.0f);
		settingsText.SetFont(cache.GetResource("Font", "Fonts/BlueHighway.ttf"), 10);
		window.AddChild(settingsText);
		
		window.SetFixedWidth(300);
		window.height = 300;
		window.SetPosition(ui.root.width - 10 - window.width, attributeInspectorWindow.position.y + attributeInspectorWindow.height + 10);
		
		SubscribeToEvent(window.GetChild("RaiseLowerHeight", true), "Toggled", "EditModeRaiseLowerHeight");
		SubscribeToEvent(window.GetChild("SetHeight", true), "Toggled", "EditModeSetHeight");
		SubscribeToEvent(window.GetChild("SmoothHeight", true), "Toggled", "EditModeSmoothHeight");
		SubscribeToEvent(window.GetChild("PaintBrush", true), "Toggled", "EditModePaintBrush");
		SubscribeToEvent(window.GetChild("PaintTrees", true), "Toggled", "EditModePaintTrees");
		SubscribeToEvent(window.GetChild("PaintFoliage", true), "Toggled", "EditModePaintFoliage");
		SubscribeToEvent(window.GetChild("CloseButton", true), "Released", "Hide");
		
		LoadBrushes();
		Show();
	}
	
	// Save all the terrains we have edited
	void Save()
	{
		for(uint i = 0; i < terrainsEdited.length; ++i)
		{
			// Make sure its not null (it may have been deleted since last save)
			if(terrainsEdited[i] !is null)
			{
				String fileLocation = fileSystem.programDir + "Data/" + terrainsEdited[i].GetAttribute("Height Map").GetResourceRef().name;
				
				Array<String> chunks = fileLocation.Split('/');
				Array<String> parts = chunks[chunks.length - 1].Split('.');
				String fileType = parts[1];
				
				if(fileType == "png")
				{
					terrainsEdited[i].heightMap.SavePNG(fileLocation);
				}
				else if(fileType == "jpg")
				{
					// Save with the highest quality
					terrainsEdited[i].heightMap.SaveJPG(fileLocation, 100);
				}
				else if(fileType == "bmp")
				{
					terrainsEdited[i].heightMap.SaveBMP(fileLocation);
				}
				else if(fileType == "tga")
				{
					terrainsEdited[i].heightMap.SaveTGA(fileLocation);
				}
			}
		}
		// Clean up terrainsEdited array by clearing it
		// (this will remove any terrains that may have been deleted)
		terrainsEdited.Clear();
	}
	
	// Returns a brush based on its name (its filename minus the extension)
	Image@ GetBrushImage(String brushName)
	{
		for(uint i = 0; i < brushes.length; ++i)
		{
			if(brushes[i].name == brushName)
			{
				return brushes[i];
			}
		}
		
		return null;
	}
	
	// Loads all the brushes from a hard-coded folder
	void LoadBrushes()
	{
		ListView@ terrainBrushes = window.GetChild("BrushesContainer", true);
	
		String brushesFileLocation = fileSystem.programDir + "Data/Textures/Editor/TerrainBrushes";
		Array<String> files = fileSystem.ScanDir(brushesFileLocation, "*.*", SCAN_FILES, false);
		
		for(uint i = 0; i < files.length; ++i)
		{
			terrainBrushes.AddItem(CreateBrush(brushesFileLocation + "/" + files[i]));
		}
	}
	
	// Creates a brush element
	UIElement@ CreateBrush(String fileLocation)
	{
		Array<String> chunks = fileLocation.Split('/');
		Array<String> parts = chunks[chunks.length - 1].Split('.');
	
		// We use this when editing the terrain
		Image@ image = cache.GetResource("Image", fileLocation);
		image.name = parts[0];
		brushes.Push(image);
		
		// This is for the brush icon
		Texture2D@ texture = cache.GetResource("Texture2D", fileLocation);
		
		CheckBox@ brush = CheckBox(parts[0]);
		brush.defaultStyle = uiStyle;
		brush.style = "TerrainEditorCheckbox";
		brush.SetFixedSize(64, 64);
		SubscribeToEvent(brush, "Toggled", "BrushSelected");
	
		BorderImage@ icon = BorderImage("Icon");
		icon.defaultStyle = iconStyle;
		icon.texture = texture;
		icon.imageRect = IntRect(0, 0, texture.width, texture.height);
		icon.SetFixedSize(64, 64);
		brush.AddChild(icon);
		
		return brush;
	}
	
	// Show the window
	bool Show()
	{
		window.visible = true;
		window.BringToFront();
		return true;
	}
	
	// Hide the window
	void Hide()
	{
		window.visible = false;
	}
	
	// This gets called when we want to do something to a terrain
	void Work(Terrain@ terrainComponent, Image@ terrainImage, IntVector2 position)
	{
		SetSceneModified();
	
		// Add that terrain to the terrainsEdited if its not already in there
		if(terrainsEdited.FindByRef(terrainComponent) == -1)
			terrainsEdited.Push(terrainComponent);
		
		// Only work if a brush is selected
		if(selectedBrushImage !is null){
			uint brushImageWidth = selectedBrushImage.width;
			uint brushImageHeight = selectedBrushImage.height;
		
			switch(editMode)
			{
				case TERRAIN_EDITMODE_RAISELOWERHEIGHT: {
					// Iterate over the entire brush image
					for(int y = 0; y < brushImageHeight; ++y)
					{
						for(int x = 0; x < brushImageWidth; ++x)
						{
							// Get the current terrain height at that position (centred to the brush's size)
							IntVector2 pos = IntVector2(position.x + x - (brushImageWidth / 2), position.y + y - (brushImageHeight / 2));
							Color newColor = terrainImage.GetPixel(pos.x, pos.y);
							Color brushColor = selectedBrushImage.GetPixel(x, y);
							
							// lower or raise (respectively)
							float modifer = (input.keyDown[KEY_SHIFT]) ? -0.01f : 0.01f;
							
							// Now apply the brush to the terrain (we only use the alpha)
							newColor.r += brushColor.a * modifer;
							newColor.g += brushColor.a * modifer;
							newColor.b += brushColor.a * modifer;
							
							terrainImage.SetPixel(pos.x, pos.y, newColor);
						}
					}
				} break;
				
				case TERRAIN_EDITMODE_SETHEIGHT: {
					// The color we want to set the height to (this stays the same until targetColorSelected is false again)
					if(targetColorSelected == false)
					{ 
						targetColor = terrainImage.GetPixel(position.x, position.y);
						targetColorSelected = true;
					}
				
					// Iterate over the entire brush image
					for(int y = 0; y < brushImageHeight; ++y)
					{
						for(int x = 0; x < brushImageWidth; ++x)
						{
							// Get the current terrain height at that position (centred to the brush's size)
							IntVector2 pos = IntVector2(position.x + x - (brushImageWidth / 2), position.y + y - (brushImageHeight / 2));
							Color newColor = terrainImage.GetPixel(pos.x, pos.y);
							Color brushColor = selectedBrushImage.GetPixel(x, y);
							
							// Ease the height to the target height (using the brush alpha as the 'speed'), making sure the alpha isn't 0
							newColor.r += (targetColor.r - newColor.r) * brushColor.a;
							newColor.g += (targetColor.g - newColor.g) * brushColor.a;
							newColor.b += (targetColor.b - newColor.b) * brushColor.a;
							
							// Set it to target if its close enough
							if(Difference(targetColor.r, newColor.r) < 0.01f) newColor.r = targetColor.r;
							if(Difference(targetColor.g, newColor.g) < 0.01f) newColor.g = targetColor.g;
							if(Difference(targetColor.b, newColor.b) < 0.01f) newColor.b = targetColor.b;
							
							terrainImage.SetPixel(pos.x, pos.y, newColor);
						}
					}
				} break;
				
				case TERRAIN_EDITMODE_SMOOTHHEIGHT: {
					IntRect rect = IntRect(position.x - (brushImageWidth / 2), position.y - (brushImageHeight / 2), 
						position.x - (brushImageWidth / 2) + brushImageWidth, position.y - (brushImageHeight / 2) + brushImageHeight);
					Image@ subImage = terrainImage.GetSubimage(rect);
				
					// Iterate over the entire brush image
					for(int y = 0; y < brushImageHeight; ++y)
					{
						for(int x = 0; x < brushImageWidth; ++x)
						{
							// Get the current terrain height at that position (centred to the brush's size)
							IntVector2 pos = IntVector2(position.x + x - (brushImageWidth / 2), position.y + y - (brushImageHeight / 2));
							
							// Make sure the pixel we're working on is atleast one pixel inside the terrainImage
							// as we need an adjacent pixel on all sides for the smoothing algorithm to work
							if(pos.x > 0 && pos.y > 0 && pos.x < terrainImage.width - 1 && pos.y < terrainImage.height - 1)
							{
								Color newColor = terrainImage.GetPixel(pos.x, pos.y);
								Color brushColor = selectedBrushImage.GetPixel(x, y);
								
								Array<Color> adjacentColors;
								
								adjacentColors.Push(terrainImage.GetPixel(pos.x + 1, pos.y + 1));
								adjacentColors.Push(terrainImage.GetPixel(pos.x + 1, pos.y));
								adjacentColors.Push(terrainImage.GetPixel(pos.x + 1, pos.y - 1));
								adjacentColors.Push(terrainImage.GetPixel(pos.x - 1, pos.y + 1));
								adjacentColors.Push(terrainImage.GetPixel(pos.x - 1, pos.y));
								adjacentColors.Push(terrainImage.GetPixel(pos.x - 1, pos.y - 1));
								adjacentColors.Push(terrainImage.GetPixel(pos.x, pos.y + 1));
								adjacentColors.Push(terrainImage.GetPixel(pos.x, pos.y));
								adjacentColors.Push(terrainImage.GetPixel(pos.x, pos.y - 1));
								
								float avgR = 0.0f;
								float avgG = 0.0f;
								float avgB = 0.0f;
								
								// Get the average of those pixels
								for(uint i = 0; i < adjacentColors.length; ++i)
								{
									avgR += adjacentColors[i].r;
									avgG += adjacentColors[i].g;
									avgB += adjacentColors[i].b;
								}
								
								newColor.r = avgR / adjacentColors.length;
								newColor.g = avgG / adjacentColors.length;
								newColor.b = avgB / adjacentColors.length;
								
								Color originalColor = terrainImage.GetPixel(pos.x, pos.y);
								
								newColor.r = (Difference(originalColor.r, newColor.r) * brushColor.a) + Smaller(originalColor.r, newColor.r);
								newColor.g = (Difference(originalColor.g, newColor.g) * brushColor.a) + Smaller(originalColor.g, newColor.g);
								newColor.b = (Difference(originalColor.b, newColor.b) * brushColor.a) + Smaller(originalColor.b, newColor.b);
								
								subImage.SetPixel(x, y, newColor);
							}
						}
					}
					
					// Apply our changes to that actual terrain
					for(int y = 0; y < subImage.height; ++y)
					{
						for(int x = 0; x < subImage.width; ++x)
						{
							terrainImage.SetPixel(position.x + x - (brushImageWidth / 2), position.y + y - (brushImageHeight / 2), subImage.GetPixel(x, y));
						}
					}
					
				} break;
			}
			
			// Apply our changes
			terrainComponent.ApplyHeightMap();
		}
	}
	
	// Utility function, returns the smaller of the two numbers
	float Smaller(float a, float b)
	{
		return (a > b) ? b : a;
	}
	
	// Utility function, returns the difference of the two numbers
	float Difference(float a, float b)
	{
		return (a > b) ? a - b : b - a;
	}
	
	// Update the UI
	void UpdateDirty()
	{
		if(!dirty)
			return;
	
		CheckBox@ raiseLowerHeight = window.GetChild("RaiseLowerHeight", true);
		CheckBox@ setHeight = window.GetChild("SetHeight", true);
		CheckBox@ smoothHeight = window.GetChild("SmoothHeight", true);
		CheckBox@ paintBrush = window.GetChild("PaintBrush", true);
		CheckBox@ paintTrees = window.GetChild("PaintTrees", true);
		CheckBox@ paintFoliage = window.GetChild("PaintFoliage", true);
		
		raiseLowerHeight.checked = (editMode == TERRAIN_EDITMODE_RAISELOWERHEIGHT) ? true : false;
		setHeight.checked = (editMode == TERRAIN_EDITMODE_SETHEIGHT) ? true : false;
		smoothHeight.checked = (editMode == TERRAIN_EDITMODE_SMOOTHHEIGHT) ? true : false;
		paintBrush.checked = (editMode == TERRAIN_EDITMODE_PAINTBRUSH) ? true : false;
		paintTrees.checked = (editMode == TERRAIN_EDITMODE_PAINTTREES) ? true : false;
		paintFoliage.checked = (editMode == TERRAIN_EDITMODE_PAINTFOLIAGE) ? true : false;
		
		ListView@ terrainBrushes = window.GetChild("BrushesContainer", true);
	
		for(uint i = 0; i < terrainBrushes.numItems; ++i)
		{
			if(terrainBrushes.items[i] !is selectedBrush)
			{
				CheckBox@ checkbox = cast<CheckBox>(terrainBrushes.items[i]);
				checkbox.checked = false;
			}
		}
		
		dirty = false;
	}
	
	// The next 7 functions are callbacks for the Terrain Editors UI
	
	void EditModeRaiseLowerHeight(StringHash eventType, VariantMap& eventData)
	{
		CheckBox@ edit = eventData["Element"].GetPtr();
		if (edit.checked){
			editMode = TERRAIN_EDITMODE_RAISELOWERHEIGHT;
			currentToolDescText.text = "Raise or lower terrain";
		}
		dirty = true;
	}
	
	void EditModeSetHeight(StringHash eventType, VariantMap& eventData)
	{
		CheckBox@ edit = eventData["Element"].GetPtr();
		if (edit.checked){
			editMode = TERRAIN_EDITMODE_SETHEIGHT;
			currentToolDescText.text = "Set height to specified height";
		}
		dirty = true;
	}
	
	void EditModeSmoothHeight(StringHash eventType, VariantMap& eventData)
	{
		CheckBox@ edit = eventData["Element"].GetPtr();
		if (edit.checked){
			editMode = TERRAIN_EDITMODE_SMOOTHHEIGHT;
			currentToolDescText.text = "Smooth the terrain";
		}
		dirty = true;
	}
	
	void EditModePaintBrush(StringHash eventType, VariantMap& eventData)
	{
		CheckBox@ edit = eventData["Element"].GetPtr();
		if (edit.checked){
			editMode = TERRAIN_EDITMODE_PAINTBRUSH;
			currentToolDescText.text = "Paint textures onto the terrain";
		}
		dirty = true;
	}
	
	void EditModePaintTrees(StringHash eventType, VariantMap& eventData)
	{
		CheckBox@ edit = eventData["Element"].GetPtr();
		if (edit.checked){
			editMode = TERRAIN_EDITMODE_PAINTTREES;
			currentToolDescText.text = "Paint trees onto the terrain";
		}
		dirty = true;
	}
	
	void EditModePaintFoliage(StringHash eventType, VariantMap& eventData)
	{
		CheckBox@ edit = eventData["Element"].GetPtr();
		if (edit.checked){
			editMode = TERRAIN_EDITMODE_PAINTFOLIAGE;
			currentToolDescText.text = "Paint foliage onto the terrain";
		}
		dirty = true;
	}
	
	void BrushSelected(StringHash eventType, VariantMap& eventData)
	{
		CheckBox@ checkbox = cast<CheckBox>(eventData["Element"].GetPtr());
		if(checkbox.checked == false) 
			return;
		selectedBrush = checkbox;
		selectedBrushImage = GetBrushImage(selectedBrush.name);
		Print("Selected Brush: " + selectedBrush.name);
		dirty = true;
	}
}