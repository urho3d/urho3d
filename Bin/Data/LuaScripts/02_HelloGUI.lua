-- A simple 'HelloWorld' GUI created purely from code.
-- This sample demonstrates:
--     - Creation of controls and building a UI hierarchy
--     - Loading UI style from XML and applying it to controls
--     - Handling of global and per-control events

require "LuaScripts/Utilities/Sample"

local window = nil
local windowTitle = nil

function Start()
    -- Execute the common startup for samples
    SampleStart()

    -- Enable OS cursor
    local input = GetInput()
    input.mouseVisible = true

    -- Load XML file containing default UI style sheet
    local cache = GetCache()
    local style = cache:GetXMLFile("UI/DefaultStyle.xml")

    -- Set the loaded style as default style
    local ui = GetUI()
    ui.root.defaultStyle = style

    -- Initialize Window
    InitWindow()

    -- Create and add some controls to the Window
    InitControls()

    SubscribeToEvents()
end

function Stop()
end

function InitControls()
    -- Create a CheckBox
    local context = GetContext()
    local checkBox = CheckBox:new(context)
    checkBox:SetName("CheckBox")

    -- Create a Button
    local button = Button:new(context)
    button:SetName("Button")
    button.minHeight = 24

    -- Create a LineEdit
    local lineEdit = LineEdit:new(context)
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
    local context = GetContext()
    window = Window:new(context)
    local ui = GetUI()
    ui.root:AddChild(window)
    
    -- Set Window size and layout settings
    window:SetMinSize(384, 192)
    window:SetLayout(LM_VERTICAL, 6, IntRect(6, 6, 6, 6))
    window:SetAlignment(HA_CENTER, VA_CENTER)
    window:SetName("Window")
    
    -- Create Window 'titlebar' container
    local titleBar = UIElement:new(context)
    titleBar:SetMinSize(0, 24)
    titleBar.verticalAlignment = VA_TOP
    titleBar.layoutMode = LM_HORIZONTAL

    -- Create the Window title Text
    windowTitle = Text:new(context)
    windowTitle:SetName("WindowTitle")
    windowTitle:SetText("Hello GUI!")
    
    
    -- Create the Window's close button
    local buttonClose = Button:new(context)
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
    
    -- Lastly, subscribe to buttonClose release (following a 'press') events
    SubscribeToEvent(buttonClose, "Released", "HandleClosePressed")
end

function SubscribeToEvents()
    -- Subscribe handler invoked whenever a mouse click event is dispatched
    SubscribeToEvent("UIMouseClick", "HandleControlClicked")
end

function HandleClosePressed(eventType, eventData)
    local engine = GetEngine()
    engine:Exit()
end

function HandleControlClicked(eventType, eventData)
    -- Get the Text control acting as the Window's title
    --local windowTitle = window:GetChild("WindowTitle", true)
    
    -- Get control that was clicked
    -- Note difference to C++: in C++ we would call GetPtr() and cast the function pointer to UIElement, here we must specify
    -- what kind of object we are getting. Null will be returned on type mismatch
    local clicked = eventData:GetUIElement("Element")

    local name = "...?"
    if clicked ~= nil then
        -- Get the name of the control that was clicked
        name = clicked:GetName():CString()
    end

    -- Update the Window's title text
    windowTitle:SetText("Hello " .. name .. "!")
end
