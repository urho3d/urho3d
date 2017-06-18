// Text rendering example.
// Displays text at various sizes, with checkboxes to change the rendering parameters.

#include "Scripts/Utilities/Sample.as"

// Tag used to find all Text elements
String TEXT_TAG = "Typography_text_tag";

// Top-level container for this sample's UI
UIElement@ uielement;

void Start()
{
    // Execute the common startup for samples
    SampleStart();

    // Enable OS cursor
    input.mouseVisible = true;

    // Load XML file containing default UI style sheet
    XMLFile@ style = cache.GetResource("XMLFile", "UI/DefaultStyle.xml");

    // Set the loaded style as default style
    ui.root.defaultStyle = style;

    // Create a UIElement to hold all our content
    // (Don't modify the root directly, as the base Sample class uses it)
    uielement = UIElement();
    uielement.SetAlignment(HA_CENTER, VA_CENTER);
    uielement.SetLayout(LM_VERTICAL, 20, IntRect(20, 40, 20, 40));
    ui.root.AddChild(uielement);
    
    // Add some sample text
    CreateText();

    // Add a checkbox to toggle the background color.
    CreateCheckbox("White background", "HandleWhiteBackground")
        .checked = false;

    // Add a checkbox for the global ForceAutoHint setting. This affects character spacing.
    CreateCheckbox("UI::SetForceAutoHint", "HandleForceAutoHint")
        .checked = ui.forceAutoHint;

    // Add a checkbox to toggle SRGB output conversion (if available).
    // This will give more correct text output for FreeType fonts, as the FreeType rasterizer
    // outputs linear coverage values rather than SRGB values. However, this feature isn't
    // available on all platforms.
    CreateCheckbox("Graphics::SetSRGB", "HandleSRGB")
        .checked = graphics.sRGB;

    // Add a drop-down menu to control the font hinting level.
    Array<String> items = {
        "FONT_HINT_LEVEL_NONE",
        "FONT_HINT_LEVEL_LIGHT",
        "FONT_HINT_LEVEL_NORMAL"
    };
    CreateMenu("UI::SetFontHintLevel", items, "HandleFontHintLevel")
        .selection = ui.fontHintLevel;

    // Set the mouse mode to use in the sample
    SampleInitMouseMode(MM_FREE);
}

void CreateText()
{
    UIElement@ container = UIElement();
    container.SetAlignment(HA_LEFT, VA_TOP);
    container.SetLayout(LM_VERTICAL);
    uielement.AddChild(container);
    
    Font@ font = cache.GetResource("Font", "Fonts/BlueHighway.ttf");
    
    for (int size = 1; size <= 24; ++size)
    {
        Text@ text = Text();
        text.text = "The quick brown fox jumps over the lazy dog (" + size + "pt)";
        text.SetFont(font, size);
        text.AddTag(TEXT_TAG);
        container.AddChild(text);
    }
}

CheckBox@ CreateCheckbox(String label, String handler)
{
    UIElement@ container = UIElement();
    container.SetAlignment(HA_LEFT, VA_TOP);
    container.SetLayout(LM_HORIZONTAL, 8);
    uielement.AddChild(container);
    
    CheckBox@ box = CheckBox();
    container.AddChild(box);
    box.SetStyleAuto();
    
    Text@ text = Text();
    container.AddChild(text);
    text.text = label;
    text.SetStyleAuto();
    text.AddTag(TEXT_TAG);

    SubscribeToEvent(box, "Toggled", handler);
    return box;
}

DropDownList@ CreateMenu(String label, Array<String> items, String handler)
{
    UIElement@ container = UIElement();
    container.SetAlignment(HA_LEFT, VA_TOP);
    container.SetLayout(LM_HORIZONTAL, 8);
    uielement.AddChild(container);

    Text@ text = Text();
    container.AddChild(text);
    text.text = label;
    text.SetStyleAuto();
    text.AddTag(TEXT_TAG);

    DropDownList@ list = DropDownList();
    container.AddChild(list);
    list.SetStyleAuto();
    
    for (int i = 0; i < items.length; ++i)
    {
        Text@ t = Text();
        list.AddItem(t);
        t.text = items[i];
        t.SetStyleAuto();
        t.AddTag(TEXT_TAG);
    }
    
    text.maxWidth = text.rowWidths[0];
    list.maxWidth = text.rowWidths[0] * 1.5;
    
    SubscribeToEvent(list, "ItemSelected", handler);
    return list;
}

void HandleWhiteBackground(StringHash eventType, VariantMap& eventData)
{
    CheckBox@ box = eventData["Element"].GetPtr();
    bool checked = box.checked;

    Color fg = checked ? BLACK : WHITE;
    Color bg = checked ? WHITE : BLACK;
    
    renderer.defaultZone.fogColor = bg;

    Array<UIElement@>@ elements = uielement.GetChildrenWithTag(TEXT_TAG, true);
    for (int i = 0; i < elements.length; ++i)
    {
        elements[i].color = fg;
    }
}

void HandleForceAutoHint(StringHash eventType, VariantMap& eventData)
{
    CheckBox@ box = eventData["Element"].GetPtr();
    bool checked = box.checked;

    ui.forceAutoHint = checked;
}

void HandleSRGB(StringHash eventType, VariantMap& eventData)
{
    CheckBox@ box = eventData["Element"].GetPtr();
    bool checked = box.checked;

    if (graphics.sRGBWriteSupport)
    {
        graphics.sRGB = checked;
    }
    else
    {
        log.Warning("graphics.sRGBWriteSupport is false");
    }
}

void HandleFontHintLevel(StringHash eventType, VariantMap& eventData)
{
    DropDownList@ list = eventData["Element"].GetPtr();
    int i = list.selection;

    ui.fontHintLevel = FontHintLevel(i);    
}

// Create XML patch instructions for screen joystick layout specific to this sample app
String patchInstructions =
        "<patch>" +
        "    <add sel=\"/element/element[./attribute[@name='Name' and @value='Hat0']]\">" +
        "        <attribute name=\"Is Visible\" value=\"false\" />" +
        "    </add>" +
        "</patch>";
