-- Urho3D UI Drag Example:
-- This sample demonstrates:
--     - Creating GUI elements from AngelScript
--     - Loading GUI Style from xml
--     - Subscribing to GUI drag events and handling them
--     - Working with GUI elements with specific tags.

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

    -- Set the mouse mode to use in the sample
    SampleInitMouseMode(MM_FREE)

    -- Hook up to the frame update events
    SubscribeToEvents()
end

function CreateInstructions()
    -- Construct new Text object, set string to display and font to use
    local instructionText = ui.root:CreateChild("Text")
    instructionText:SetText("Drag on the buttons to move them around.\n"..
                            "Touch input allows also multi-drag.\n"..
                            "Press SPACE to show/hide tagged UI elements.")
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
        b:SetStyleAuto()
        b.minWidth = 250
        b:SetPosition(IntVector2(50*i, 50*i))

        -- Enable the bring-to-front flag and set the initial priority
        b.bringToFront = true
        b.priority = i

        -- Set the layout mode to make the child text elements aligned vertically
        b:SetLayout(LM_VERTICAL, 20, IntRect(40, 40, 40, 40))
        local dragInfos = {"Num Touch", "Text", "Event Touch"}
        for j=1, table.getn(dragInfos) do
            b:CreateChild("Text", dragInfos[j]):SetStyleAuto()
        end

        if i % 2 == 0 then
             b:AddTag("SomeTag")
        end

        SubscribeToEvent(b, "Click", "HandleClick")
        SubscribeToEvent(b, "DragMove", "HandleDragMove")
        SubscribeToEvent(b, "DragBegin", "HandleDragBegin")
        SubscribeToEvent(b, "DragCancel", "HandleDragCancel")
    end

    for i = 0, 9, 1 do
        local t = Text:new()
        ui.root:AddChild(t)
        t:SetStyleAuto()
        t:SetName("Touch " .. i)
        t.visible = false
        t.priority = 100    -- Make sure it has higher priority than the buttons
    end
end

function SubscribeToEvents()
    -- Subscribe HandleUpdate() function for processing update events
    SubscribeToEvent("Update", "HandleUpdate")
end

function HandleClick(eventType, eventData)
    local element = eventData["Element"]:GetPtr("UIElement")
    element:BringToFront()
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

    element:GetChild("Text").text = "Drag Begin Buttons: " .. buttons

    element:GetChild("Num Touch").text = "Number of buttons: " .. eventData["NumButtons"]:GetInt()
end

function HandleDragMove(eventType, eventData)
    local element = eventData["Element"]:GetPtr("UIElement")
    local buttons = eventData["Buttons"]:GetInt()
    local d = element:GetVar(VAR_DELTA):GetVector2()
    local X = eventData["X"]:GetInt() + d.x
    local Y = eventData["Y"]:GetInt() + d.y
    local BUTTONS = element:GetVar(VAR_BUTTONS):GetInt()

    element:GetChild("Event Touch").text = "Drag Move Buttons: " .. buttons

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

    if input:GetKeyPress(KEY_SPACE) then
        elements = ui.root:GetChildrenWithTag("SomeTag")
        for i, element in ipairs(elements) do
            element.visible = not element.visible
        end
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
