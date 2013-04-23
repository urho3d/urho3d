// Urho3D editor preferences dialog

bool subscribedToEditorPreferences = false;
Window@ preferencesDialog;

LineEdit@ originalAttributeTextColorEditR;
LineEdit@ originalAttributeTextColorEditG;
LineEdit@ originalAttributeTextColorEditB;
LineEdit@ modifiedAttributeTextColorEditR;
LineEdit@ modifiedAttributeTextColorEditG;
LineEdit@ modifiedAttributeTextColorEditB;
LineEdit@ nonEditableAttributeTextColorEditR;
LineEdit@ nonEditableAttributeTextColorEditG;
LineEdit@ nonEditableAttributeTextColorEditB;

void CreateEditorPreferencesDialog()
{
    if (preferencesDialog !is null)
        return;

    preferencesDialog = ui.LoadLayout(cache.GetResource("XMLFile", "UI/EditorPreferencesDialog.xml"));
    ui.root.AddChild(preferencesDialog);
    preferencesDialog.opacity = uiMaxOpacity;
    CenterDialog(preferencesDialog);

    originalAttributeTextColorEditR = preferencesDialog.GetChild("OriginalAttributeTextColor.r", true);
    originalAttributeTextColorEditG = preferencesDialog.GetChild("OriginalAttributeTextColor.g", true);
    originalAttributeTextColorEditB = preferencesDialog.GetChild("OriginalAttributeTextColor.b", true);
    modifiedAttributeTextColorEditR = preferencesDialog.GetChild("ModifiedAttributeTextColor.r", true);
    modifiedAttributeTextColorEditG = preferencesDialog.GetChild("ModifiedAttributeTextColor.g", true);
    modifiedAttributeTextColorEditB = preferencesDialog.GetChild("ModifiedAttributeTextColor.b", true);
    nonEditableAttributeTextColorEditR = preferencesDialog.GetChild("NonEditableAttributeTextColor.r", true);
    nonEditableAttributeTextColorEditG = preferencesDialog.GetChild("NonEditableAttributeTextColor.g", true);
    nonEditableAttributeTextColorEditB = preferencesDialog.GetChild("NonEditableAttributeTextColor.b", true);

    UpdateEditorPreferencesDialog();
    HideEditorPreferencesDialog();
}

void UpdateEditorPreferencesDialog()
{
    if (preferencesDialog is null)
        return;

    LineEdit@ uiMinOpacityEdit = preferencesDialog.GetChild("UIMinOpacity", true);
    uiMinOpacityEdit.text = String(uiMinOpacity);

    LineEdit@ uiMaxOpacityEdit = preferencesDialog.GetChild("UIMaxOpacity", true);
    uiMaxOpacityEdit.text = String(uiMaxOpacity);

    CheckBox@ showInternalUIElementToggle = preferencesDialog.GetChild("ShowInternalUIElement", true);
    showInternalUIElementToggle.checked = showInternalUIElement;

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

    if (!subscribedToEditorPreferences)
    {
        SubscribeToEvent(uiMinOpacityEdit, "TextFinished", "EditUIMinOpacity");
        SubscribeToEvent(uiMaxOpacityEdit, "TextFinished", "EditUIMaxOpacity");
        SubscribeToEvent(showInternalUIElementToggle, "Toggled", "ToggleShowInternalUIElement");
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
        SubscribeToEvent(preferencesDialog.GetChild("CloseButton", true), "Released", "HideEditorPreferencesDialog");
        subscribedToEditorPreferences = true;
    }
}

bool ShowEditorPreferencesDialog()
{
    UpdateEditorPreferencesDialog();
    preferencesDialog.visible = true;
    preferencesDialog.BringToFront();
    return true;
}

void HideEditorPreferencesDialog()
{
    preferencesDialog.visible = false;
}

void EditUIMinOpacity(StringHash eventType, VariantMap& eventData)
{
    LineEdit@ edit = eventData["Element"].GetUIElement();
    uiMinOpacity = edit.text.ToFloat();
    edit.text = String(uiMinOpacity);
    FadeUI();
    UnfadeUI();
}

void EditUIMaxOpacity(StringHash eventType, VariantMap& eventData)
{
    LineEdit@ edit = eventData["Element"].GetUIElement();
    uiMaxOpacity = edit.text.ToFloat();
    edit.text = String(uiMaxOpacity);
    FadeUI();
    UnfadeUI();
}

void ToggleShowInternalUIElement(StringHash eventType, VariantMap& eventData)
{
    showInternalUIElement = cast<CheckBox>(eventData["Element"].GetUIElement()).checked;
    UpdateHierarchyItem(editorUIElement, true);
}

void ToggleShowNonEditableAttribute(StringHash eventType, VariantMap& eventData)
{
    showNonEditableAttribute = cast<CheckBox>(eventData["Element"].GetUIElement()).checked;
    UpdateAttributeInspector(true);
}

void EditOriginalAttributeTextColor(StringHash eventType, VariantMap& eventData)
{
    LineEdit@ edit = eventData["Element"].GetUIElement();
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
    LineEdit@ edit = eventData["Element"].GetUIElement();
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
    LineEdit@ edit = eventData["Element"].GetUIElement();
    nonEditableTextColor = Color(nonEditableAttributeTextColorEditR.text.ToFloat(), nonEditableAttributeTextColorEditG.text.ToFloat(), nonEditableAttributeTextColorEditB.text.ToFloat());
    if (edit.name == "NonEditableAttributeTextColor.r")
        edit.text = String(nonEditableTextColor.r);
    else if (edit.name == "NonEditableAttributeTextColor.g")
        edit.text = String(nonEditableTextColor.g);
    else if (edit.name == "NonEditableAttributeTextColor.b")
        edit.text = String(nonEditableTextColor.b);
    UpdateAttributeInspector(false);
}
