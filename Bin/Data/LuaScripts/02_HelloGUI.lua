-- A simple 'HelloWorld' GUI created purely from code.
-- This sample demonstrates:
--     - Creation of controls and building a UI hierarchy
--     - Loading UI style from XML and applying it to controls
--     - Handling of global and per-control events
-- For more advanced users (beginners can skip this section):
--     - Dragging UIElements
--     - Displaying tooltips
--     - Accessing available Events data (eventData)

require "LuaScripts/Utilities/Sample"

local window = nil
local dragBeginPosition = IntVector2(0, 0)

function Start()
    -- Execute the common startup for samples
    SampleStart()

    -- Enable OS cursor
    input.mouseVisible = true

    -- Load XML file containing default UI style sheet
    local style = cache:GetResource("XMLFile", "UI/DefaultStyle.xml")

    -- Set the loaded style as default style
    ui.root.defaultStyle = style

    -- Initialize Window
    InitWindow()

    -- Create and add some controls to the Window
    InitControls()

    -- Create a draggable Fish
    CreateDraggableFish()
end

function InitControls()
    -- Create a CheckBox
    local checkBox = CheckBox:new()
    checkBox:SetName("CheckBox")

    -- Create a Button
    local button = Button:new()
    button:SetName("Button")
    button.minHeight = 24

    -- Create a LineEdit
    local lineEdit = LineEdit:new()
    lineEdit:SetName("LineEdit")
    lineEdit.minHeight = 24

    -- Add controls to Window
    window:AddChild(checkBox)
    window:AddChild(button)
    window:AddChild(lineEdit)

    -- Apply previously set default style
    checkBox:SetStyleAuto()
    button:SetStyleAuto()
    lineEdit:SetStyleAuto()
end

function InitWindow()
    -- Create the Window and add it to the UI's root node
    window = Window:new()
    ui.root:AddChild(window)

    -- Set Window size and layout settings
    window:SetMinSize(384, 192)
    window:SetLayout(LM_VERTICAL, 6, IntRect(6, 6, 6, 6))
    window:SetAlignment(HA_CENTER, VA_CENTER)
    window:SetName("Window")

    -- Create Window 'titlebar' container
    local titleBar = UIElement:new()
    titleBar:SetMinSize(0, 24)
    titleBar.verticalAlignment = VA_TOP
    titleBar.layoutMode = LM_HORIZONTAL

    -- Create the Window title Text
    local windowTitle = Text:new()
    windowTitle.name = "WindowTitle"
    windowTitle.text = "Hello GUI!"


    -- Create the Window's close button
    local buttonClose = Button:new()
    buttonClose:SetName("CloseButton")

    -- Add the controls to the title bar
    titleBar:AddChild(windowTitle)
    titleBar:AddChild(buttonClose)

    -- Add the title bar to the Window
    window:AddChild(titleBar)


    -- Apply styles
    window:SetStyleAuto()
    windowTitle:SetStyleAuto()
    buttonClose:SetStyle("CloseButton")

    -- Subscribe to buttonClose release (following a 'press') events
    SubscribeToEvent(buttonClose, "Released", 
        function (eventType, eventData)
            engine:Exit()
        end)

    -- Subscribe also to all UI mouse clicks just to see where we have clicked
    SubscribeToEvent("UIMouseClick", HandleControlClicked)
end

function CreateDraggableFish()
    -- Create a draggable Fish button
    local draggableFish = ui.root:CreateChild("Button", "Fish")
    draggableFish.texture = cache:GetResource("Texture2D", "Textures/UrhoDecal.dds") -- Set texture
    draggableFish.blendMode = BLEND_ADD
    draggableFish:SetSize(128, 128)
    draggableFish:SetPosition((GetGraphics().width - draggableFish.width) / 2, 200)

    -- Add a tooltip to Fish button
    local toolTip = draggableFish:CreateChild("ToolTip")
    toolTip.position = IntVector2(draggableFish.width + 5, draggableFish.width/2) -- Slightly offset from fish
    local textHolder = toolTip:CreateChild("BorderImage")
    textHolder:SetStyle("ToolTipBorderImage")
    local toolTipText = textHolder:CreateChild("Text")
    toolTipText:SetStyle("ToolTipText")
    toolTipText.text = "Please drag me!"

    -- Subscribe draggableFish to Drag Events (in order to make it draggable)
    -- See "Event list" in documentation's Main Page for reference on available Events and their eventData
    SubscribeToEvent(draggableFish, "DragBegin", 
        function (eventType, eventData)
            -- Get UIElement relative position where input (touch or click) occured (top-left = IntVector2(0,0))
            dragBeginPosition = IntVector2(eventData:GetInt("ElementX"), eventData:GetInt("ElementY"))
        end)

    SubscribeToEvent(draggableFish, "DragMove", 
        function (eventType, eventData)
            local dragCurrentPosition = IntVector2(eventData:GetInt("X"), eventData:GetInt("Y"))
            -- Get the dragged fish element
            -- Note difference to C++: in C++ we would call GetPtr() and cast the pointer to UIElement, here we must specify
            -- what kind of object we are getting. Null will be returned on type mismatch
            local draggedElement = eventData:GetPtr("UIElement", "Element")
            draggedElement:SetPosition(dragCurrentPosition - dragBeginPosition)
        end)
    
    SubscribeToEvent(draggableFish, "DragEnd", 
        function (eventType, eventData)
        end)
end

function HandleControlClicked(eventType, eventData)
    -- Get the Text control acting as the Window's title
    local element = window:GetChild("WindowTitle", true)
    local windowTitle = tolua.cast(element, 'Text')

    -- Get control that was clicked
    local clicked = eventData:GetPtr("UIElement", "Element")
    local name = "...?"
    if clicked ~= nil then
        -- Get the name of the control that was clicked
        name = clicked.name
    end

    -- Update the Window's title text
    windowTitle.text = "Hello " .. name .. "!"
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
