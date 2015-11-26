-- Urho3D UI Drag Example:
-- This sample demonstrates:
--     - Creating GUI elements from AngelScript
--     - Loading GUI Style from xml
--     - Subscribing to GUI drag events and handling them.

require "LuaScripts/Utilities/Sample"
VAR_BUTTONS = StringHash("BUTTONS")
VAR_START = StringHash("START")
VAR_DELTA = StringHash("DELTA")

function Start()
    -- Execute base class startup
    SampleStart()

    -- Set mouse visible
    local platform = GetPlatform()
    if platform ~= "Android" and platform ~= "iOS" then
        input.mouseVisible = true
    end

    -- Create the UI content
    CreateGUI()
    CreateInstructions()

    -- Hook up to the frame update events
    SubscribeToEvents()
end

function CreateInstructions()
    -- Construct new Text object, set string to display and font to use
    local instructionText = ui.root:CreateChild("Text")
    instructionText:SetText("Drag on the buttons to move them around.\nTouch input allows also multi-drag.")
    instructionText:SetFont(cache:GetResource("Font", "Fonts/Anonymous Pro.ttf"), 15)
    instructionText.textAlignment = HA_CENTER

    -- Position the text relative to the screen center
    instructionText.horizontalAlignment = HA_CENTER
    instructionText.verticalAlignment = VA_CENTER
    instructionText:SetPosition(0, ui.root.height / 4)
end

function CreateGUI()
    -- Load the style sheet from xml
    ui.root.defaultStyle = cache:GetResource("XMLFile", "UI/DefaultStyle.xml")

    for i=0, 9, 1 do
        local b = Button:new()
        ui.root:AddChild(b)
        -- Reference a style from the style sheet loaded earlier:
        b:SetStyle("Button")
        b:SetMinSize(IntVector2(300, 100))
        b:SetPosition(IntVector2(50*i, 50*i))

        SubscribeToEvent(b, "DragMove", "HandleDragMove")
        SubscribeToEvent(b, "DragBegin", "HandleDragBegin")
        SubscribeToEvent(b, "DragCancel", "HandleDragCancel")

        local t = Text:new()
        b:AddChild(t)
        t:SetStyle("Text")
        t:SetHorizontalAlignment(HA_CENTER)
        t:SetVerticalAlignment(VA_CENTER)
        t:SetName("Text")

        t = Text:new()
        b:AddChild(t)
        t:SetStyle("Text")
        t:SetName("Event Touch")
        t:SetHorizontalAlignment(HA_CENTER)
        t:SetVerticalAlignment(VA_BOTTOM)

        t = Text:new()
        b:AddChild(t)
        t:SetStyle("Text")
        t:SetName("Num Touch")
        t:SetHorizontalAlignment(HA_CENTER)
        t:SetVerticalAlignment(VA_TOP)
    end

    for i = 0, 9, 1 do
        local t = Text:new()
        ui.root:AddChild(t)
        t:SetStyle("Text")
        t:SetName("Touch " .. i)
        t:SetVisible(false)
    end
end

function SubscribeToEvents()
    -- Subscribe HandleUpdate() function for processing update events
    SubscribeToEvent("Update", "HandleUpdate")
end

function HandleDragBegin(eventType, eventData)
    local element = eventData["Element"]:GetPtr("UIElement")

    local lx = eventData["X"]:GetInt()
    local ly = eventData["Y"]:GetInt()

    local p = element.position
    element:SetVar(VAR_START, Variant(p))
    element:SetVar(VAR_DELTA, Variant(Vector2(p.x - lx, p.y - ly)))

    local buttons = eventData["Buttons"]:GetInt()
    element:SetVar(VAR_BUTTONS, Variant(buttons))

    local t = tolua.cast(element:GetChild("Text"), 'Text')
    t:SetText("Drag Begin Buttons: " .. buttons)

    t = tolua.cast(element:GetChild("Num Touch"), 'Text')
    t:SetText("Number of buttons: " .. eventData["NumButtons"]:GetInt())
end

function HandleDragMove(eventType, eventData)
    local element = eventData["Element"]:GetPtr("UIElement")
    local buttons = eventData["Buttons"]:GetInt()
    local d = element:GetVar(VAR_DELTA):GetVector2()
    local X = eventData["X"]:GetInt() + d.x
    local Y = eventData["Y"]:GetInt() + d.y
    local BUTTONS = element:GetVar(VAR_BUTTONS):GetInt()

    local t = tolua.cast(element:GetChild("Event Touch"), 'Text')
    t:SetText("Drag Move Buttons: " .. buttons)

    element:SetPosition(IntVector2(X, Y))
end

function HandleDragCancel(eventType, eventData)
    local element = eventData["Element"]:GetPtr("UIElement")
    local P = element:GetVar(VAR_START):GetIntVector2()
    element:SetPosition(P)
end

function HandleUpdate(eventType, eventData)
    local n = input:GetNumTouches()
    local i = 0
    while i < n do
        local t = tolua.cast(ui.root:GetChild("Touch " .. i), 'Text')
        local ts = input:GetTouch(i)
        t:SetText("Touch " .. ts.touchID)

        local pos = IntVector2(ts.position)
        pos.y = pos.y - 30

        t:SetPosition(pos)
        t:SetVisible(true)

        i = i + 1
    end

    i = n
    while i < 10 do
        local t = tolua.cast(ui.root:GetChild("Touch " .. i), 'Text')
        t:SetVisible(false)
        i = i + 1
    end
end

-- Create XML patch instructions for screen joystick layout specific to this sample app
function GetScreenJoystickPatchString()
    return "<patch>" ..
        "    <add sel=\"/element/element[./attribute[@name='Name' and @value='Hat0']]\">" ..
        "        <attribute name=\"Is Visible\" value=\"false\" />" ..
        "    </add>" ..
        "</patch>"

end
