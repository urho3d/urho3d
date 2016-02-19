// Urho3D editor preferences dialog

bool subscribedToEditorPreferences = false;
Window@ preferencesDialog;

LineEdit@ nodeItemTextColorEditR;
LineEdit@ nodeItemTextColorEditG;
LineEdit@ nodeItemTextColorEditB;
LineEdit@ componentItemTextColorEditR;
LineEdit@ componentItemTextColorEditG;
LineEdit@ componentItemTextColorEditB;

LineEdit@ originalAttributeTextColorEditR;
LineEdit@ originalAttributeTextColorEditG;
LineEdit@ originalAttributeTextColorEditB;
LineEdit@ modifiedAttributeTextColorEditR;
LineEdit@ modifiedAttributeTextColorEditG;
LineEdit@ modifiedAttributeTextColorEditB;
LineEdit@ nonEditableAttributeTextColorEditR;
LineEdit@ nonEditableAttributeTextColorEditG;
LineEdit@ nonEditableAttributeTextColorEditB;

LineEdit@ defaultZoneAmbientColorEditR;
LineEdit@ defaultZoneAmbientColorEditG;
LineEdit@ defaultZoneAmbientColorEditB;
LineEdit@ defaultZoneFogColorEditR;
LineEdit@ defaultZoneFogColorEditG;
LineEdit@ defaultZoneFogColorEditB;

LineEdit@ gridColorEditR;
LineEdit@ gridColorEditG;
LineEdit@ gridColorEditB;
LineEdit@ gridSubdivisionColorEditR;
LineEdit@ gridSubdivisionColorEditG;
LineEdit@ gridSubdivisionColorEditB;

void CreateEditorPreferencesDialog()
{
    if (preferencesDialog !is null)
        return;

    preferencesDialog = LoadEditorUI("UI/EditorPreferencesDialog.xml");
    ui.root.AddChild(preferencesDialog);
    preferencesDialog.opacity = uiMaxOpacity;
    preferencesDialog.height = 440;
    CenterDialog(preferencesDialog);

    DropDownList@ languageSelector = preferencesDialog.GetChild("LanguageSelector", true);
    for (int i = 0; i < localization.numLanguages; i++)
    {
        Text@ choice = Text();
        languageSelector.AddItem(choice);
        choice.style = "FileSelectorFilterText";
        choice.text = localization.GetLanguage(i);
    }
    
    nodeItemTextColorEditR = preferencesDialog.GetChild("NodeItemTextColor.r", true);
    nodeItemTextColorEditG = preferencesDialog.GetChild("NodeItemTextColor.g", true);
    nodeItemTextColorEditB = preferencesDialog.GetChild("NodeItemTextColor.b", true);
    componentItemTextColorEditR = preferencesDialog.GetChild("ComponentItemTextColor.r", true);
    componentItemTextColorEditG = preferencesDialog.GetChild("ComponentItemTextColor.g", true);
    componentItemTextColorEditB = preferencesDialog.GetChild("ComponentItemTextColor.b", true);

    originalAttributeTextColorEditR = preferencesDialog.GetChild("OriginalAttributeTextColor.r", true);
    originalAttributeTextColorEditG = preferencesDialog.GetChild("OriginalAttributeTextColor.g", true);
    originalAttributeTextColorEditB = preferencesDialog.GetChild("OriginalAttributeTextColor.b", true);
    modifiedAttributeTextColorEditR = preferencesDialog.GetChild("ModifiedAttributeTextColor.r", true);
    modifiedAttributeTextColorEditG = preferencesDialog.GetChild("ModifiedAttributeTextColor.g", true);
    modifiedAttributeTextColorEditB = preferencesDialog.GetChild("ModifiedAttributeTextColor.b", true);
    nonEditableAttributeTextColorEditR = preferencesDialog.GetChild("NonEditableAttributeTextColor.r", true);
    nonEditableAttributeTextColorEditG = preferencesDialog.GetChild("NonEditableAttributeTextColor.g", true);
    nonEditableAttributeTextColorEditB = preferencesDialog.GetChild("NonEditableAttributeTextColor.b", true);

    defaultZoneAmbientColorEditR = preferencesDialog.GetChild("DefaultZoneAmbientColor.r", true);
    defaultZoneAmbientColorEditG = preferencesDialog.GetChild("DefaultZoneAmbientColor.g", true);
    defaultZoneAmbientColorEditB = preferencesDialog.GetChild("DefaultZoneAmbientColor.b", true);
    defaultZoneFogColorEditR = preferencesDialog.GetChild("DefaultZoneFogColor.r", true);
    defaultZoneFogColorEditG = preferencesDialog.GetChild("DefaultZoneFogColor.g", true);
    defaultZoneFogColorEditB = preferencesDialog.GetChild("DefaultZoneFogColor.b", true);

    gridColorEditR = preferencesDialog.GetChild("GridColor.r", true);
    gridColorEditG = preferencesDialog.GetChild("GridColor.g", true);
    gridColorEditB = preferencesDialog.GetChild("GridColor.b", true);
    gridSubdivisionColorEditR = preferencesDialog.GetChild("GridSubdivisionColor.r", true);
    gridSubdivisionColorEditG = preferencesDialog.GetChild("GridSubdivisionColor.g", true);
    gridSubdivisionColorEditB = preferencesDialog.GetChild("GridSubdivisionColor.b", true);

    UpdateEditorPreferencesDialog();
    HideEditorPreferencesDialog();
}

void UpdateEditorPreferencesDialog()
{
    if (preferencesDialog is null)
        return;
    
    DropDownList@ languageSelector = preferencesDialog.GetChild("LanguageSelector", true);
    languageSelector.selection = localization.languageIndex;

    LineEdit@ uiMinOpacityEdit = preferencesDialog.GetChild("UIMinOpacity", true);
    uiMinOpacityEdit.text = String(uiMinOpacity);

    LineEdit@ uiMaxOpacityEdit = preferencesDialog.GetChild("UIMaxOpacity", true);
    uiMaxOpacityEdit.text = String(uiMaxOpacity);

    CheckBox@ showInternalUIElementToggle = preferencesDialog.GetChild("ShowInternalUIElement", true);
    showInternalUIElementToggle.checked = showInternalUIElement;

    CheckBox@ showTemporaryObjectToggle = preferencesDialog.GetChild("ShowTemporaryObject", true);
    showTemporaryObjectToggle.checked = showTemporaryObject;

    nodeItemTextColorEditR.text = String(nodeTextColor.r);
    nodeItemTextColorEditG.text = String(nodeTextColor.g);
    nodeItemTextColorEditB.text = String(nodeTextColor.b);

    componentItemTextColorEditR.text = String(componentTextColor.r);
    componentItemTextColorEditG.text = String(componentTextColor.g);
    componentItemTextColorEditB.text = String(componentTextColor.b);

    CheckBox@ showNonEditableAttributeToggle = preferencesDialog.GetChild("ShowNonEditableAttribute", true);
    showNonEditableAttributeToggle.checked = showNonEditableAttribute;

    originalAttributeTextColorEditR.text = String(normalTextColor.r);
    originalAttributeTextColorEditG.text = String(normalTextColor.g);
    originalAttributeTextColorEditB.text = String(normalTextColor.b);

    modifiedAttributeTextColorEditR.text = String(modifiedTextColor.r);
    modifiedAttributeTextColorEditG.text = String(modifiedTextColor.g);
    modifiedAttributeTextColorEditB.text = String(modifiedTextColor.b);

    nonEditableAttributeTextColorEditR.text = String(nonEditableTextColor.r);
    nonEditableAttributeTextColorEditG.text = String(nonEditableTextColor.g);
    nonEditableAttributeTextColorEditB.text = String(nonEditableTextColor.b);

    defaultZoneAmbientColorEditR.text = String(renderer.defaultZone.ambientColor.r);
    defaultZoneAmbientColorEditG.text = String(renderer.defaultZone.ambientColor.g);
    defaultZoneAmbientColorEditB.text = String(renderer.defaultZone.ambientColor.b);

    defaultZoneFogColorEditR.text = String(renderer.defaultZone.fogColor.r);
    defaultZoneFogColorEditG.text = String(renderer.defaultZone.fogColor.g);
    defaultZoneFogColorEditB.text = String(renderer.defaultZone.fogColor.b);

    LineEdit@ defaultZoneFogStartEdit = preferencesDialog.GetChild("DefaultZoneFogStart", true);
    defaultZoneFogStartEdit.text = String(renderer.defaultZone.fogStart);
    LineEdit@ defaultZoneFogEndEdit = preferencesDialog.GetChild("DefaultZoneFogEnd", true);
    defaultZoneFogEndEdit.text = String(renderer.defaultZone.fogEnd);

    CheckBox@ showGridToggle = preferencesDialog.GetChild("ShowGrid", true);
    showGridToggle.checked = showGrid;
    
    CheckBox@ grid2DModeToggle = preferencesDialog.GetChild("Grid2DMode", true);
    grid2DModeToggle.checked = grid2DMode;

    LineEdit@ gridSizeEdit = preferencesDialog.GetChild("GridSize", true);
    gridSizeEdit.text = String(gridSize);
    
    LineEdit@ gridSubdivisionsEdit = preferencesDialog.GetChild("GridSubdivisions", true);
    gridSubdivisionsEdit.text = String(gridSubdivisions);
    
    LineEdit@ gridScaleEdit = preferencesDialog.GetChild("GridScale", true);
    gridScaleEdit.text = String(gridScale);

    gridColorEditR.text = String(gridColor.r);
    gridColorEditG.text = String(gridColor.g);
    gridColorEditB.text = String(gridColor.b);
    gridSubdivisionColorEditR.text = String(gridSubdivisionColor.r);
    gridSubdivisionColorEditG.text = String(gridSubdivisionColor.g);
    gridSubdivisionColorEditB.text = String(gridSubdivisionColor.b);

    if (!subscribedToEditorPreferences)
    {
        SubscribeToEvent(uiMinOpacityEdit, "TextFinished", "EditUIMinOpacity");
        SubscribeToEvent(uiMaxOpacityEdit, "TextFinished", "EditUIMaxOpacity");
        SubscribeToEvent(showInternalUIElementToggle, "Toggled", "ToggleShowInternalUIElement");
        SubscribeToEvent(showTemporaryObjectToggle, "Toggled", "ToggleShowTemporaryObject");
        SubscribeToEvent(nodeItemTextColorEditR, "TextFinished", "EditNodeTextColor");
        SubscribeToEvent(nodeItemTextColorEditG, "TextFinished", "EditNodeTextColor");
        SubscribeToEvent(nodeItemTextColorEditB, "TextFinished", "EditNodeTextColor");
        SubscribeToEvent(componentItemTextColorEditR, "TextFinished", "EditComponentTextColor");
        SubscribeToEvent(componentItemTextColorEditG, "TextFinished", "EditComponentTextColor");
        SubscribeToEvent(componentItemTextColorEditB, "TextFinished", "EditComponentTextColor");
        SubscribeToEvent(showNonEditableAttributeToggle, "Toggled", "ToggleShowNonEditableAttribute");
        SubscribeToEvent(originalAttributeTextColorEditR, "TextFinished", "EditOriginalAttributeTextColor");
        SubscribeToEvent(originalAttributeTextColorEditG, "TextFinished", "EditOriginalAttributeTextColor");
        SubscribeToEvent(originalAttributeTextColorEditB, "TextFinished", "EditOriginalAttributeTextColor");
        SubscribeToEvent(modifiedAttributeTextColorEditR, "TextFinished", "EditModifiedAttributeTextColor");
        SubscribeToEvent(modifiedAttributeTextColorEditG, "TextFinished", "EditModifiedAttributeTextColor");
        SubscribeToEvent(modifiedAttributeTextColorEditB, "TextFinished", "EditModifiedAttributeTextColor");
        SubscribeToEvent(nonEditableAttributeTextColorEditR, "TextFinished", "EditNonEditableAttributeTextColor");
        SubscribeToEvent(nonEditableAttributeTextColorEditG, "TextFinished", "EditNonEditableAttributeTextColor");
        SubscribeToEvent(nonEditableAttributeTextColorEditB, "TextFinished", "EditNonEditableAttributeTextColor");
        SubscribeToEvent(defaultZoneAmbientColorEditR, "TextFinished", "EditDefaultZoneAmbientColor");
        SubscribeToEvent(defaultZoneAmbientColorEditG, "TextFinished", "EditDefaultZoneAmbientColor");
        SubscribeToEvent(defaultZoneAmbientColorEditB, "TextFinished", "EditDefaultZoneAmbientColor");
        SubscribeToEvent(defaultZoneFogColorEditR, "TextFinished", "EditDefaultZoneFogColor");
        SubscribeToEvent(defaultZoneFogColorEditG, "TextFinished", "EditDefaultZoneFogColor");
        SubscribeToEvent(defaultZoneFogColorEditB, "TextFinished", "EditDefaultZoneFogColor");
        SubscribeToEvent(defaultZoneFogStartEdit, "TextFinished", "EditDefaultZoneFogStart");
        SubscribeToEvent(defaultZoneFogEndEdit, "TextFinished", "EditDefaultZoneFogEnd");
        SubscribeToEvent(showGridToggle, "Toggled", "ToggleShowGrid");
        SubscribeToEvent(grid2DModeToggle, "Toggled", "ToggleGrid2DMode");
        SubscribeToEvent(gridSizeEdit, "TextFinished", "EditGridSize");
        SubscribeToEvent(gridSubdivisionsEdit, "TextFinished", "EditGridSubdivisions");
        SubscribeToEvent(gridScaleEdit, "TextFinished", "EditGridScale");
        SubscribeToEvent(gridColorEditR, "TextFinished", "EditGridColor");
        SubscribeToEvent(gridColorEditG, "TextFinished", "EditGridColor");
        SubscribeToEvent(gridColorEditB, "TextFinished", "EditGridColor");
        SubscribeToEvent(languageSelector, "ItemSelected", "EditLanguageSelector");
        SubscribeToEvent(gridSubdivisionColorEditR, "TextFinished", "EditGridSubdivisionColor");
        SubscribeToEvent(gridSubdivisionColorEditG, "TextFinished", "EditGridSubdivisionColor");
        SubscribeToEvent(gridSubdivisionColorEditB, "TextFinished", "EditGridSubdivisionColor");
        SubscribeToEvent(preferencesDialog.GetChild("CloseButton", true), "Released", "HideEditorPreferencesDialog");
        subscribedToEditorPreferences = true;
    }
}

void EditLanguageSelector(StringHash eventType, VariantMap& eventData)
{
    DropDownList@ edit = eventData["Element"].GetPtr();
    localization.SetLanguage(edit.selection);
}

bool ToggleEditorPreferencesDialog()
{
    if (preferencesDialog.visible == false)
        ShowEditorPreferencesDialog();
    else
        HideEditorPreferencesDialog();
    return true;
}

void ShowEditorPreferencesDialog()
{
    UpdateEditorPreferencesDialog();
    preferencesDialog.visible = true;
    preferencesDialog.BringToFront();
}

void HideEditorPreferencesDialog()
{
    preferencesDialog.visible = false;
}

void EditUIMinOpacity(StringHash eventType, VariantMap& eventData)
{
    LineEdit@ edit = eventData["Element"].GetPtr();
    uiMinOpacity = edit.text.ToFloat();
    edit.text = String(uiMinOpacity);
    FadeUI();
    UnfadeUI();
}

void EditUIMaxOpacity(StringHash eventType, VariantMap& eventData)
{
    LineEdit@ edit = eventData["Element"].GetPtr();
    uiMaxOpacity = edit.text.ToFloat();
    edit.text = String(uiMaxOpacity);
    FadeUI();
    UnfadeUI();
}

void ToggleShowInternalUIElement(StringHash eventType, VariantMap& eventData)
{
    showInternalUIElement = cast<CheckBox>(eventData["Element"].GetPtr()).checked;
    UpdateHierarchyItem(editorUIElement, true);
}

void ToggleShowTemporaryObject(StringHash eventType, VariantMap& eventData)
{
    showTemporaryObject = cast<CheckBox>(eventData["Element"].GetPtr()).checked;
    UpdateHierarchyItem(editorScene, true);
    UpdateHierarchyItem(editorUIElement, true);
}

void EditNodeTextColor(StringHash eventType, VariantMap& eventData)
{
    LineEdit@ edit = eventData["Element"].GetPtr();
    nodeTextColor = Color(nodeItemTextColorEditR.text.ToFloat(), nodeItemTextColorEditG.text.ToFloat(), nodeItemTextColorEditB.text.ToFloat());
    if (edit.name == "NodeItemTextColor.r")
        edit.text = String(normalTextColor.r);
    else if (edit.name == "NodeItemTextColor.g")
        edit.text = String(normalTextColor.g);
    else if (edit.name == "NodeItemTextColor.b")
        edit.text = String(normalTextColor.b);
    UpdateHierarchyItem(editorScene);
}

void EditComponentTextColor(StringHash eventType, VariantMap& eventData)
{
    LineEdit@ edit = eventData["Element"].GetPtr();
    componentTextColor = Color(componentItemTextColorEditR.text.ToFloat(), componentItemTextColorEditG.text.ToFloat(), componentItemTextColorEditB.text.ToFloat());
    if (edit.name == "ComponentItemTextColor.r")
        edit.text = String(normalTextColor.r);
    else if (edit.name == "ComponentItemTextColor.g")
        edit.text = String(normalTextColor.g);
    else if (edit.name == "ComponentItemTextColor.b")
        edit.text = String(normalTextColor.b);
    UpdateHierarchyItem(editorScene);
}

void ToggleShowNonEditableAttribute(StringHash eventType, VariantMap& eventData)
{
    showNonEditableAttribute = cast<CheckBox>(eventData["Element"].GetPtr()).checked;
    UpdateAttributeInspector(true);
}

void EditOriginalAttributeTextColor(StringHash eventType, VariantMap& eventData)
{
    LineEdit@ edit = eventData["Element"].GetPtr();
    normalTextColor = Color(originalAttributeTextColorEditR.text.ToFloat(), originalAttributeTextColorEditG.text.ToFloat(), originalAttributeTextColorEditB.text.ToFloat());
    if (edit.name == "OriginalAttributeTextColor.r")
        edit.text = String(normalTextColor.r);
    else if (edit.name == "OriginalAttributeTextColor.g")
        edit.text = String(normalTextColor.g);
    else if (edit.name == "OriginalAttributeTextColor.b")
        edit.text = String(normalTextColor.b);
    UpdateAttributeInspector(false);
}

void EditModifiedAttributeTextColor(StringHash eventType, VariantMap& eventData)
{
    LineEdit@ edit = eventData["Element"].GetPtr();
    modifiedTextColor = Color(modifiedAttributeTextColorEditR.text.ToFloat(), modifiedAttributeTextColorEditG.text.ToFloat(), modifiedAttributeTextColorEditB.text.ToFloat());
    if (edit.name == "ModifiedAttributeTextColor.r")
        edit.text = String(modifiedTextColor.r);
    else if (edit.name == "ModifiedAttributeTextColor.g")
        edit.text = String(modifiedTextColor.g);
    else if (edit.name == "ModifiedAttributeTextColor.b")
        edit.text = String(modifiedTextColor.b);
    UpdateAttributeInspector(false);
}

void EditNonEditableAttributeTextColor(StringHash eventType, VariantMap& eventData)
{
    LineEdit@ edit = eventData["Element"].GetPtr();
    nonEditableTextColor = Color(nonEditableAttributeTextColorEditR.text.ToFloat(), nonEditableAttributeTextColorEditG.text.ToFloat(), nonEditableAttributeTextColorEditB.text.ToFloat());
    if (edit.name == "NonEditableAttributeTextColor.r")
        edit.text = String(nonEditableTextColor.r);
    else if (edit.name == "NonEditableAttributeTextColor.g")
        edit.text = String(nonEditableTextColor.g);
    else if (edit.name == "NonEditableAttributeTextColor.b")
        edit.text = String(nonEditableTextColor.b);
    UpdateAttributeInspector(false);
}

void EditDefaultZoneAmbientColor(StringHash eventType, VariantMap& eventData)
{
    LineEdit@ edit = eventData["Element"].GetPtr();
    renderer.defaultZone.ambientColor = Color(defaultZoneAmbientColorEditR.text.ToFloat(), defaultZoneAmbientColorEditG.text.ToFloat(), defaultZoneAmbientColorEditB.text.ToFloat());
    if (edit.name == "DefaultZoneAmbientColor.r")
        edit.text = String(renderer.defaultZone.ambientColor.r);
    else if (edit.name == "DefaultZoneAmbientColor.g")
        edit.text = String(renderer.defaultZone.ambientColor.g);
    else if (edit.name == "DefaultZoneAmbientColor.b")
        edit.text = String(renderer.defaultZone.ambientColor.b);
}

void EditDefaultZoneFogColor(StringHash eventType, VariantMap& eventData)
{
    LineEdit@ edit = eventData["Element"].GetPtr();
    renderer.defaultZone.fogColor = Color(defaultZoneFogColorEditR.text.ToFloat(), defaultZoneFogColorEditG.text.ToFloat(), defaultZoneFogColorEditB.text.ToFloat());
    if (edit.name == "DefaultZoneFogColor.r")
        edit.text = String(renderer.defaultZone.fogColor.r);
    else if (edit.name == "DefaultZoneFogColor.g")
        edit.text = String(renderer.defaultZone.fogColor.g);
    else if (edit.name == "DefaultZoneFogColor.b")
        edit.text = String(renderer.defaultZone.fogColor.b);
}

void EditDefaultZoneFogStart(StringHash eventType, VariantMap& eventData)
{
    LineEdit@ edit = eventData["Element"].GetPtr();
    renderer.defaultZone.fogStart = edit.text.ToFloat();
    edit.text = String(renderer.defaultZone.fogStart);
}

void EditDefaultZoneFogEnd(StringHash eventType, VariantMap& eventData)
{
    LineEdit@ edit = eventData["Element"].GetPtr();
    renderer.defaultZone.fogEnd = edit.text.ToFloat();
    edit.text = String(renderer.defaultZone.fogEnd);
}

void ToggleShowGrid(StringHash eventType, VariantMap& eventData)
{
    showGrid = cast<CheckBox>(eventData["Element"].GetPtr()).checked;
    UpdateGrid(false);
}

void ToggleGrid2DMode(StringHash eventType, VariantMap& eventData)
{
    grid2DMode = cast<CheckBox>(eventData["Element"].GetPtr()).checked;
    UpdateGrid();
}

void EditGridSize(StringHash eventType, VariantMap& eventData)
{
    LineEdit@ edit = eventData["Element"].GetPtr();
    gridSize = edit.text.ToInt();
    edit.text = String(gridSize);
    UpdateGrid();
}

void EditGridSubdivisions(StringHash eventType, VariantMap& eventData)
{
    LineEdit@ edit = eventData["Element"].GetPtr();
    gridSubdivisions = edit.text.ToInt();
    edit.text = String(gridSubdivisions);
    UpdateGrid();
}

void EditGridScale(StringHash eventType, VariantMap& eventData)
{
    LineEdit@ edit = eventData["Element"].GetPtr();
    gridScale = edit.text.ToFloat();
    edit.text = String(gridScale);
    UpdateGrid(false);
}

void EditGridColor(StringHash eventType, VariantMap& eventData)
{
    LineEdit@ edit = eventData["Element"].GetPtr();
    gridColor = Color(gridColorEditR.text.ToFloat(), gridColorEditG.text.ToFloat(), gridColorEditB.text.ToFloat());
    if (edit.name == "GridColor.r")
        edit.text = String(gridColor.r);
    else if (edit.name == "GridColor.g")
        edit.text = String(gridColor.g);
    else if (edit.name == "GridColor.b")
        edit.text = String(gridColor.b);
    UpdateGrid();
}

void EditGridSubdivisionColor(StringHash eventType, VariantMap& eventData)
{
    LineEdit@ edit = eventData["Element"].GetPtr();
    gridSubdivisionColor = Color(gridSubdivisionColorEditR.text.ToFloat(), gridSubdivisionColorEditG.text.ToFloat(), gridSubdivisionColorEditB.text.ToFloat());
    if (edit.name == "GridSubdivisionColor.r")
        edit.text = String(gridSubdivisionColor.r);
    else if (edit.name == "GridSubdivisionColor.g")
        edit.text = String(gridSubdivisionColor.g);
    else if (edit.name == "GridSubdivisionColor.b")
        edit.text = String(gridSubdivisionColor.b);
    UpdateGrid();
}
