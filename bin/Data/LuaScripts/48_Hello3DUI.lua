-- A 3D UI demonstration based on the HelloGUI sample. Renders UI alternatively
-- either to a 3D scene object using UIComponent, or directly to the backbuffer.

require "LuaScripts/Utilities/Sample"

local window = nil
local dragBeginPosition = IntVector2(0, 0)
local textureRoot = nil
local current = nil
local renderOnCube = false
local drawDebug = false
local animateCube = true

function Start()
    -- Execute the common startup for samples
    SampleStart()

    -- Enable OS cursor
    input.mouseVisible = true

    -- Load XML file containing default UI style sheet
    local style = cache:GetResource("XMLFile", "UI/DefaultStyle.xml")

    -- Set the loaded style as default style
    ui.root.defaultStyle = style

    -- Initialize Scene
    InitScene()

    -- Initialize Window
    InitWindow()

    -- Create and add some controls to the Window
    InitControls()

    -- Create a draggable Fish
    CreateDraggableFish()

    -- Create 3D UI rendered on a cube.
    Init3DUI()

    -- Set the mouse mode to use in the sample
    SampleInitMouseMode(MM_FREE)
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
    
    local instructions = Text:new()
    instructions:SetStyleAuto()
    instructions.text = "[TAB]   - toggle between rendering on screen or cube.\n"..
                        "[Space] - toggle cube rotation."
    ui.root:AddChild(instructions)
end

function InitScene()
    scene_ = Scene()

    scene_:CreateComponent("Octree")
    local zone = scene_:CreateComponent("Zone")
    zone.boundingBox = BoundingBox(-1000.0, 1000.0)
    zone.fogColor = Color(0.5, 0.5, 0.5)
    zone.fogStart = 100.0
    zone.fogEnd = 300.0

    -- Create a child scene node (at world origin) and a StaticModel component into it.
    local boxNode = scene_:CreateChild("Box")
    boxNode.scale = Vector3(5.0, 5.0, 5.0)
    boxNode.rotation = Quaternion(90, Vector3(1, 0, 0))

    -- Create a box model and hide it initially.
    local boxModel = boxNode:CreateComponent("StaticModel")
    boxModel.model = cache:GetResource("Model", "Models/Box.mdl")
    boxNode.enabled = false

    -- Create a camera.
    cameraNode = scene_:CreateChild("Camera")
    cameraNode:CreateComponent("Camera")

    -- Set an initial position for the camera scene node.
    cameraNode.position = Vector3(0.0, 0.0, -10.0)

    -- Set up a viewport so 3D scene can be visible.
    local viewport = Viewport:new(scene_, cameraNode:GetComponent("Camera"))
    renderer:SetViewport(0, viewport)

    -- Subscribe to update event and animate cube and handle input.
    SubscribeToEvent("Update", "HandleUpdate")
end

function InitWindow()
    -- Create the Window and add it to the UI's root node
    window = Window:new()
    ui.root:AddChild(window)

    -- Set Window size and layout settings
    window.minWidth = 384
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

    -- Create a list.
    local list = window:CreateChild("ListView")
    list.selectOnClickEnd = true
    list.highlightMode = HM_ALWAYS
    list.minHeight = 200

    for i = 0, 31 do
        local text = Text:new()
        text:SetStyleAuto()
        text.text = "List item " .. i
        text.name = "Item " .. i
        list:AddItem(text)
    end

    -- Apply styles
    window:SetStyleAuto()
    list:SetStyleAuto()
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
            -- Get UIElement relative position where input (touch or click) occurred (top-left = IntVector2(0,0))
            dragBeginPosition = IntVector2(eventData["ElementX"]:GetInt(), eventData["ElementY"]:GetInt())
        end)

    SubscribeToEvent(draggableFish, "DragMove",
        function (eventType, eventData)
            local dragCurrentPosition = IntVector2(eventData["X"]:GetInt(), eventData["Y"]:GetInt())
            -- Get the dragged fish element
            -- Note difference to C++: in C++ we would call GetPtr() and cast the pointer to UIElement, here we must specify
            -- what kind of object we are getting. Null will be returned on type mismatch
            local draggedElement = eventData["Element"]:GetPtr("UIElement")
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
    local clicked = eventData["Element"]:GetPtr("UIElement")
    local name = "...?"
    if clicked ~= nil then
        -- Get the name of the control that was clicked
        name = clicked.name
    end

    -- Update the Window's title text
    windowTitle.text = "Hello " .. name .. "!"
end

function Init3DUI()
    -- Node that will get UI rendered on it.
    local boxNode = scene_:GetChild("Box")
    -- Create a component that sets up UI rendering. It sets material to StaticModel of the node.
    local component = boxNode:CreateComponent("UIComponent")
    -- Optionally modify material. Technique is changed so object is visible without any lights.
    component.material:SetTechnique(0, cache:GetResource("Technique", "Techniques/DiffUnlit.xml"))
    -- Save root element of texture UI for later use.
    textureRoot = component.root
    -- Set size of root element. This is size of texture as well.
    textureRoot:SetSize(512, 512)
end

function HandleUpdate(eventType, eventData)
    local timeStep = eventData["TimeStep"]:GetFloat()
    local node = scene_:GetChild("Box")

    if current ~= nil and drawDebug then
        ui:DebugDraw(current)
    end

    if input:GetMouseButtonPress(MOUSEB_LEFT) then
        current = ui:GetElementAt(input.mousePosition)
    end

    if input:GetKeyPress(KEY_TAB) then
        renderOnCube = not renderOnCube
        -- Toggle between rendering on screen or to texture.
        if renderOnCube then
            node.enabled = true
            textureRoot:AddChild(window)
        else
            node.enabled = false
            ui.root:AddChild(window)
        end
    end

    if input:GetKeyPress(KEY_SPACE) then
        animateCube = not animateCube
    end

    if input:GetKeyPress(KEY_F2) then
        drawDebug = not drawDebug
    end

    if animateCube then
        node:Yaw(6.0 * timeStep * 1.5)
        node:Roll(-6.0 * timeStep * 1.5)
        node:Pitch(-6.0 * timeStep * 1.5)
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
