// Urho3D editor preferences dialog

bool subscribedToEditorPreferences = false;
Window@ preferencesDialog;

LineEdit@ originalAttributeTextColorEditR;
LineEdit@ originalAttributeTextColorEditG;
LineEdit@ originalAttributeTextColorEditB;
LineEdit@ modifiedAttributeTextColorEditR;
LineEdit@ modifiedAttributeTextColorEditG;
LineEdit@ modifiedAttributeTextColorEditB;

void CreateEditorPreferencesDialog()
{
    if (preferencesDialog !is null)
        return;
    
    preferencesDialog = ui.LoadLayout(cache.GetResource("XMLFile", "UI/EditorPreferencesDialog.xml"), uiStyle);
    ui.root.AddChild(preferencesDialog);
    CenterDialog(preferencesDialog);

    originalAttributeTextColorEditR = preferencesDialog.GetChild("OriginalAttributeTextColor.r", true);
    originalAttributeTextColorEditG = preferencesDialog.GetChild("OriginalAttributeTextColor.g", true);
    originalAttributeTextColorEditB = preferencesDialog.GetChild("OriginalAttributeTextColor.b", true);
    modifiedAttributeTextColorEditR = preferencesDialog.GetChild("ModifiedAttributeTextColor.r", true);
    modifiedAttributeTextColorEditG = preferencesDialog.GetChild("ModifiedAttributeTextColor.g", true);
    modifiedAttributeTextColorEditB = preferencesDialog.GetChild("ModifiedAttributeTextColor.b", true);

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
    
    originalAttributeTextColorEditR.text = String(normalTextColor.r);
    originalAttributeTextColorEditG.text = String(normalTextColor.g);
    originalAttributeTextColorEditB.text = String(normalTextColor.b);
    
    modifiedAttributeTextColorEditR.text = String(modifiedTextColor.r);
    modifiedAttributeTextColorEditG.text = String(modifiedTextColor.g);
    modifiedAttributeTextColorEditB.text = String(modifiedTextColor.b);
    
    if (!subscribedToEditorPreferences)
    {
        SubscribeToEvent(uiMinOpacityEdit, "TextChanged", "EditUIMinOpacity");
        SubscribeToEvent(uiMinOpacityEdit, "TextFinished", "EditUIMinOpacity");
        SubscribeToEvent(uiMaxOpacityEdit, "TextChanged", "EditUIMaxOpacity");
        SubscribeToEvent(uiMaxOpacityEdit, "TextFinished", "EditUIMaxOpacity");
        SubscribeToEvent(originalAttributeTextColorEditR, "TextChanged", "EditOriginalAttributeTextColor");
        SubscribeToEvent(originalAttributeTextColorEditR, "TextFinished", "EditOriginalAttributeTextColor");
        SubscribeToEvent(originalAttributeTextColorEditG, "TextChanged", "EditOriginalAttributeTextColor");
        SubscribeToEvent(originalAttributeTextColorEditG, "TextFinished", "EditOriginalAttributeTextColor");
        SubscribeToEvent(originalAttributeTextColorEditB, "TextChanged", "EditOriginalAttributeTextColor");
        SubscribeToEvent(originalAttributeTextColorEditB, "TextFinished", "EditOriginalAttributeTextColor");
        SubscribeToEvent(modifiedAttributeTextColorEditR, "TextChanged", "EditModifiedAttributeTextColor");
        SubscribeToEvent(modifiedAttributeTextColorEditR, "TextFinished", "EditModifiedAttributeTextColor");
        SubscribeToEvent(modifiedAttributeTextColorEditG, "TextChanged", "EditModifiedAttributeTextColor");
        SubscribeToEvent(modifiedAttributeTextColorEditG, "TextFinished", "EditModifiedAttributeTextColor");
        SubscribeToEvent(modifiedAttributeTextColorEditB, "TextChanged", "EditModifiedAttributeTextColor");
        SubscribeToEvent(modifiedAttributeTextColorEditB, "TextFinished", "EditModifiedAttributeTextColor");
        SubscribeToEvent(preferencesDialog.GetChild("CloseButton", true), "Released", "HideEditorPreferencesDialog");
        subscribedToEditorPreferences = true;
    }
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
    LineEdit@ edit = eventData["Element"].GetUIElement();
    uiMinOpacity = edit.text.ToFloat();
    if (eventType == StringHash("TextFinished"))
    {
        edit.text = String(uiMinOpacity);
        HideUI();
        UnhideUI();
    }
}

void EditUIMaxOpacity(StringHash eventType, VariantMap& eventData)
{
    LineEdit@ edit = eventData["Element"].GetUIElement();
    uiMaxOpacity = edit.text.ToFloat();
    if (eventType == StringHash("TextFinished"))
    {
        edit.text = String(uiMaxOpacity);
        HideUI();
        UnhideUI();
    }
}

void EditOriginalAttributeTextColor(StringHash eventType, VariantMap& eventData)
{
    LineEdit@ edit = eventData["Element"].GetUIElement();
    normalTextColor = Color(originalAttributeTextColorEditR.text.ToFloat(), originalAttributeTextColorEditG.text.ToFloat(), originalAttributeTextColorEditB.text.ToFloat());
    if (eventType == StringHash("TextFinished"))
    {
        if (edit.name == "OriginalAttributeTextColor.r")
            edit.text = String(normalTextColor.r);
        else if (edit.name == "OriginalAttributeTextColor.g")
            edit.text = String(normalTextColor.g);
        else if (edit.name == "OriginalAttributeTextColor.b")
            edit.text = String(normalTextColor.b);
        UpdateAttributes(false);
    }
}

void EditModifiedAttributeTextColor(StringHash eventType, VariantMap& eventData)
{
    LineEdit@ edit = eventData["Element"].GetUIElement();
    modifiedTextColor = Color(modifiedAttributeTextColorEditR.text.ToFloat(), modifiedAttributeTextColorEditG.text.ToFloat(), modifiedAttributeTextColorEditB.text.ToFloat());
    if (eventType == StringHash("TextFinished"))
    {
        if (edit.name == "ModifiedAttributeTextColor.r")
            edit.text = String(modifiedTextColor.r);
        else if (edit.name == "ModifiedAttributeTextColor.g")
            edit.text = String(modifiedTextColor.g);
        else if (edit.name == "ModifiedAttributeTextColor.b")
            edit.text = String(modifiedTextColor.b);
        UpdateAttributes(false);
    }
}
