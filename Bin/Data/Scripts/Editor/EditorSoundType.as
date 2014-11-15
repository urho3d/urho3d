// Urho3D Sound Type manager

Window@ soundTypeEditorWindow;
Dictionary mappings;

const uint DEFAULT_SOUND_TYPES_COUNT = 5;

class SoundTypeMapping
{
    StringHash key;
    float value;

    SoundTypeMapping()
    {
    }
    
    SoundTypeMapping(const String&in key, const float&in value)
    {
        this.key = StringHash(key);
        this.value = value;
    }
    
    SoundTypeMapping(const StringHash&in key, const float&in value)
    {
        this.key = key;
        this.value = value;
    }
    
    void Update(float value)
    {
        this.value = Clamp(value, 0.0f, 1.0f);
        audio.SetMasterGain(this.key, this.value);
    }
}

void CreateSoundTypeEditor()
{
    if (soundTypeEditorWindow !is null)
        return;
        
    soundTypeEditorWindow = ui.LoadLayout(cache.GetResource("XMLFile", "UI/EditorSoundTypeWindow.xml"));
    ui.root.AddChild(soundTypeEditorWindow);
    soundTypeEditorWindow.opacity = uiMaxOpacity;

    InitsoundTypeEditorWindow();
    RefreshSoundTypeEditorWindow();

    int height = Min(ui.root.height - 60, 750);    
    soundTypeEditorWindow.SetSize(400, 0);
    CenterDialog(soundTypeEditorWindow);

    HideSoundTypeEditor();
    
    SubscribeToEvent(soundTypeEditorWindow.GetChild("CloseButton", true), "Released", "HideSoundTypeEditor");
    SubscribeToEvent(soundTypeEditorWindow.GetChild("AddButton", true), "Released", "AddSoundTypeMapping");
    
    SubscribeToEvent(soundTypeEditorWindow.GetChild("EffectValue", true), "TextFinished", "EditGain");
    SubscribeToEvent(soundTypeEditorWindow.GetChild("AmbientValue", true), "TextFinished", "EditGain");
    SubscribeToEvent(soundTypeEditorWindow.GetChild("VoiceValue", true), "TextFinished", "EditGain");
    SubscribeToEvent(soundTypeEditorWindow.GetChild("MusicValue", true), "TextFinished", "EditGain");
    SubscribeToEvent(soundTypeEditorWindow.GetChild("MasterValue", true), "TextFinished", "EditGain");
}

void InitsoundTypeEditorWindow()
{
    mappings["Effect"] = SoundTypeMapping(GetHashFromSoundType(SOUND_EFFECT), audio.GetMasterGain(SOUND_EFFECT));
    mappings["Ambient"] = SoundTypeMapping(GetHashFromSoundType(SOUND_AMBIENT), audio.GetMasterGain(SOUND_AMBIENT));
    mappings["Voice"] = SoundTypeMapping(GetHashFromSoundType(SOUND_VOICE), audio.GetMasterGain(SOUND_VOICE));
    mappings["Music"] = SoundTypeMapping(GetHashFromSoundType(SOUND_MUSIC), audio.GetMasterGain(SOUND_MUSIC));
    mappings["Master"] = SoundTypeMapping(GetHashFromSoundType(SOUND_MASTER), audio.GetMasterGain(SOUND_MASTER));
}

void RefreshSoundTypeEditorWindow()
{
    RefreshDefaults(soundTypeEditorWindow.GetChild("DefaultsContainer"));
    RefreshUser(soundTypeEditorWindow.GetChild("UserContainer"));
}

void RefreshDefaults(UIElement@ root)
{
    UpdateMappingValue("Effect", root.GetChild("Effect", true));
    UpdateMappingValue("Ambient", root.GetChild("Ambient", true));
    UpdateMappingValue("Voice", root.GetChild("Voice", true));
    UpdateMappingValue("Music", root.GetChild("Music", true));
    UpdateMappingValue("Master", root.GetChild("Master", true));
}

void RefreshUser(UIElement@ root)
{
    for (uint i = DEFAULT_SOUND_TYPES_COUNT; i < mappings.length; i++)
    {
        String key = mappings.keys[i];  
        UpdateMappingValue(key, root.GetChild(key, true));
    }
}

void UpdateMappingValue(const String&in key, UIElement@ root)
{
    if (root !is null)
    {
        LineEdit@ value = root.GetChild(key + "Value");
        SoundTypeMapping@ mapping;
        
        if (mappings.Get(key, @mapping) && value !is null)
        {
            value.text = mapping.value;
            root.vars["DragDropContent"] = String(mapping.key.value);
        }
    }
}

void AddUserUIElements(const String&in key, const String&in gain)
{
        ListView@ container = soundTypeEditorWindow.GetChild("UserContainer", true);
        
        UIElement@ itemParent = UIElement();
        container.AddItem(itemParent);
        
        itemParent.style = "ListRow";
        itemParent.name = key;
        itemParent.layoutSpacing = 10;
        
        Text@ keyText = Text();
        LineEdit@ gainEdit = LineEdit();
        Button@ removeButton = Button();
        
        itemParent.AddChild(keyText);
        itemParent.AddChild(gainEdit);
        itemParent.AddChild(removeButton);
        itemParent.dragDropMode = DD_SOURCE;
        
        keyText.text = key;
        keyText.textAlignment = HA_LEFT;
        keyText.SetStyleAuto();
        
        gainEdit.maxLength = 4;
        gainEdit.maxWidth = 2147483647;
        gainEdit.minWidth = 100;
        gainEdit.name = key + "Value";
        gainEdit.text = gain;
        gainEdit.SetStyleAuto();

        removeButton.style = "CloseButton";
        
        SubscribeToEvent(removeButton, "Released", "DeleteSoundTypeMapping");
        SubscribeToEvent(gainEdit, "TextFinished", "EditGain");
}

void AddSoundTypeMapping(StringHash eventType, VariantMap& eventData)
{
    UIElement@ button = eventData["Element"].GetPtr();
    LineEdit@ key = button.parent.GetChild("Key");
    LineEdit@ gain = button.parent.GetChild("Gain");
    
    if (!key.text.empty && !gain.text.empty && !mappings.Exists(key.text))
    {
        AddUserUIElements(key.text,gain.text);
        mappings[key.text] = SoundTypeMapping(key.text, gain.text.ToFloat());
    }
    
    key.text = "";
    gain.text = "";
    
    RefreshSoundTypeEditorWindow();
}

void DeleteSoundTypeMapping(StringHash eventType, VariantMap& eventData)
{
    UIElement@ button = eventData["Element"].GetPtr();
    UIElement@ parent = button.parent;
    
    mappings.Erase(parent.name);
    button.parent.Remove();
}

void EditGain(StringHash eventType, VariantMap& eventData)
{
    LineEdit@ input = eventData["Element"].GetPtr();
    String key = input.parent.name;
    
    SoundTypeMapping@ mapping;
    
    if (mappings.Get(key, @mapping))
        mapping.Update(input.text.ToFloat());
        
    RefreshSoundTypeEditorWindow();
}

bool ShowSoundTypeEditor()
{
    RefreshSoundTypeEditorWindow();
    soundTypeEditorWindow.visible = true;
    soundTypeEditorWindow.BringToFront();
    return true;
}

void HideSoundTypeEditor()
{
    soundTypeEditorWindow.visible = false;
}