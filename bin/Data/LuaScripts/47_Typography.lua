-- Text rendering example.
-- Displays text at various sizes, with checkboxes to change the rendering parameters.

require "LuaScripts/Utilities/Sample"

-- Tag used to find all Text elements
local TEXT_TAG = "Typography_text_tag"

-- Top-level container for this sample's UI
local uielement = nil

function Start()
    -- Execute the common startup for samples
    SampleStart()

    -- Enable OS cursor
    input.mouseVisible = true

    -- Load XML file containing default UI style sheet
    local style = cache:GetResource("XMLFile", "UI/DefaultStyle.xml")

    -- Set the loaded style as default style
    ui.root.defaultStyle = style

    -- Create a UIElement to hold all our content
    -- (Don't modify the root directly, as the base Sample class uses it)
    uielement = UIElement:new()
    uielement:SetAlignment(HA_CENTER, VA_CENTER)
    uielement:SetLayout(LM_VERTICAL, 20, IntRect(20, 40, 20, 40))
    ui.root:AddChild(uielement)

    -- Add some sample text
    CreateText()

    -- Add a checkbox to toggle the background color.
    CreateCheckbox("White background", "HandleWhiteBackground")

    -- Add a checkbox for the global ForceAutoHint setting. This affects character spacing.
    CreateCheckbox("UI::SetForceAutoHint", "HandleForceAutoHint")

    -- Add a checkbox to toggle SRGB output conversion (if available).
    -- This will give more correct text output for FreeType fonts, as the FreeType rasterizer
    -- outputs linear coverage values rather than SRGB values. However, this feature isn't
    -- available on all platforms.
    CreateCheckbox("Graphics::SetSRGB", "HandleSRGB")

    -- Set the mouse mode to use in the sample
    SampleInitMouseMode(MM_FREE)
end

function CreateText()
    local container = UIElement:new()
    container:SetAlignment(HA_LEFT, VA_TOP)
    container:SetLayout(LM_VERTICAL)
    uielement:AddChild(container)

    local font = cache:GetResource("Font", "Fonts/BlueHighway.ttf")

    for size = 1, 24 do
        local text = Text:new()
        text.text = "The quick brown fox jumps over the lazy dog (" .. size .. "pt)"
        text:SetFont(font, size)
        text:AddTag(TEXT_TAG)
        container:AddChild(text)
    end
end

function CreateCheckbox(label, handler)
    local container = UIElement:new()
    container:SetAlignment(HA_LEFT, VA_TOP)
    container:SetLayout(LM_HORIZONTAL, 8)
    uielement:AddChild(container)
    
    local box = CheckBox:new()
    container:AddChild(box)
    box:SetStyleAuto()
    
    local text = Text:new()
    container:AddChild(text)
    text.text = label
    text:SetStyleAuto()
    text:AddTag(TEXT_TAG)

    SubscribeToEvent(box, "Toggled", handler)
end

function HandleWhiteBackground(eventType, eventData)
    local box = eventData["Element"]:GetPtr("CheckBox")
    local checked = box:IsChecked()

    local fg = checked and Color.BLACK or Color.WHITE
    local bg = checked and Color.WHITE or Color.BLACK
    
    renderer.defaultZone.fogColor = bg

    local elements = uielement:GetChildrenWithTag(TEXT_TAG, true)
    for i, element in ipairs(elements) do
        element.color = fg
    end
end

function HandleForceAutoHint(eventType, eventData)
    local box = eventData["Element"]:GetPtr("CheckBox")
    local checked = box:IsChecked()

    ui:SetForceAutoHint(checked)
end

function HandleSRGB(eventType, eventData)
    local box = eventData["Element"]:GetPtr("CheckBox")
    local checked = box:IsChecked()

    if graphics:GetSRGBWriteSupport() then
        graphics:SetSRGB(checked)
    else
        log:Write(LOG_WARNING, "graphics:GetSRGBWriteSupport returned false")
    end
end

-- Create XML patch instructions for screen joystick layout specific to this sample app
function GetScreenJoystickPatchString()
    return
        "<patch>" ..
        "    <add sel=\"/element/element[./attribute[@name='Name' and @value='Hat0']]\">" ..
        "        <attribute name=\"Is Visible\" value=\"false\" />" ..
        "    </add>" ..
        "</patch>"
end
