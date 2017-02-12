-- Localization example.
-- This sample demonstrates:
--     - Loading a collection of strings from JSON-files
--     - Creating text elements that automatically translates itself by changing the language
--     - The manually reaction to change language

require "LuaScripts/Utilities/Sample"

function Start()
    -- Execute the common startup for samples
    SampleStart()

    -- Enable OS cursor
    input.mouseVisible = true

    -- Load strings from JSON files and subscribe to the change language event
    InitLocalizationSystem()

    -- Init the 3D space
    CreateScene()

    -- Init the user interface
    CreateGUI()

    -- Set the mouse mode to use in the sample
    SampleInitMouseMode(MM_FREE)
end

function InitLocalizationSystem()
    -- JSON files must be in UTF8 encoding without BOM
    -- The first found language will be set as current
    localization:LoadJSONFile("StringsEnRu.json")
    -- You can load multiple files
    localization:LoadJSONFile("StringsDe.json")
    -- Hook up to the change language
    SubscribeToEvent("ChangeLanguage", "HandleChangeLanguage")
end

function CreateGUI()
    ui.root.defaultStyle = cache:GetResource("XMLFile", "UI/DefaultStyle.xml")

    local window = Window:new()
    ui.root:AddChild(window)
    window:SetMinSize(384, 192)
    window:SetLayout(LM_VERTICAL, 6, IntRect(6, 6, 6, 6))
    window:SetAlignment(HA_CENTER, VA_CENTER)
    window:SetStyleAuto()

    local windowTitle = Text:new()
    windowTitle.name = "WindowTitle"
    windowTitle:SetStyleAuto()
    window:AddChild(windowTitle)

    -- In this place the current language is "en" because it was found first when loading the JSON files
    local langName = localization.language
    -- Languages are numbered in the loading order
    local langIndex = localization.languageIndex -- == 0 at the beginning
    -- Get string with identifier "title" in the current language
    local localizedString = localization:Get("title")
    -- Localization:Get returns String.EMPTY if the id is empty.
    -- Localization:Get returns the id if translation is not found and will be added a warning into the log.

    windowTitle.text = localizedString .. " (" .. langIndex .. " " .. langName .. ")"

    local b = Button:new()
    window:AddChild(b)
    b:SetStyle("Button")
    b.minHeight = 24

    local t = b:CreateChild("Text", "ButtonTextChangeLang")
    -- The showing text value will automatically change when language is changed
    t.autoLocalizable = true
    -- The text value used as a string identifier in this mode.
    -- Remember that a letter case of the id and of the lang name is important.
    t.text = "Press this button"

    t:SetAlignment(HA_CENTER, VA_CENTER)
    t:SetStyle("Text")
    SubscribeToEvent(b, "Released", "HandleChangeLangButtonPressed")

    b = Button:new()
    window:AddChild(b)
    b:SetStyle("Button")
    b.minHeight = 24
    t = b:CreateChild("Text", "ButtonTextQuit")
    t:SetAlignment(HA_CENTER, VA_CENTER)
    t:SetStyle("Text")

    -- Manually set text in the current language
    t.text = localization:Get("quit")

    SubscribeToEvent(b, "Released", "HandleQuitButtonPressed")
end

function CreateScene()
    scene_ = Scene:new()
    scene_:CreateComponent("Octree")

    local zone = scene_:CreateComponent("Zone")
    zone.boundingBox = BoundingBox:new(-1000.0, 1000.0)
    zone.ambientColor = Color:new(0.5, 0.5, 0.5)
    zone.fogColor = Color:new(0.4, 0.5, 0.8)
    zone.fogStart = 1.0
    zone.fogEnd = 100.0

    local planeNode = scene_:CreateChild("Plane")
    planeNode.scale = Vector3:new(300.0, 1.0, 300.0)
    local planeObject = planeNode:CreateComponent("StaticModel")
    planeObject.model = cache:GetResource("Model", "Models/Plane.mdl")
    planeObject.material = cache:GetResource("Material", "Materials/StoneTiled.xml")

    local lightNode = scene_:CreateChild("DirectionalLight")
    lightNode.direction = Vector3:new(0.6, -1.0, 0.8)
    local light = lightNode:CreateComponent("Light")
    light.lightType = LIGHT_DIRECTIONAL
    light.color = Color:new(0.8, 0.8, 0.8)

    cameraNode = scene_:CreateChild("Camera")
    cameraNode:CreateComponent("Camera")
    cameraNode.position = Vector3:new(0.0, 10.0, -30.0)

    local text3DNode = scene_:CreateChild("Text3D")
    text3DNode.position = Vector3:new(0.0, 0.1, 30.0)
    text3DNode:SetScale(15)
    local text3D = text3DNode:CreateComponent("Text3D")

    -- Manually set text in the current language.
    text3D.text = localization:Get("lang")

    text3D:SetFont(cache:GetResource("Font", "Fonts/Anonymous Pro.ttf"), 30)
    text3D.color = Color.BLACK
    text3D:SetAlignment(HA_CENTER, VA_BOTTOM)

    local viewport = Viewport:new(scene_, cameraNode:GetComponent("Camera"))
    renderer:SetViewport(0, viewport)

    SubscribeToEvent("Update", "HandleUpdate")
end

function HandleUpdate(eventType, eventData)
    local timeStep = eventData["TimeStep"]:GetFloat()
    local MOUSE_SENSITIVITY = 0.1
    local mouseMove = input.mouseMove
    yaw = yaw + MOUSE_SENSITIVITY * mouseMove.x
    pitch = pitch + MOUSE_SENSITIVITY * mouseMove.y
    pitch = Clamp(pitch, -90.0, 90.0)
    cameraNode.rotation = Quaternion(pitch, yaw, 0.0)
end

function HandleChangeLangButtonPressed(eventType, eventData)
    -- Languages are numbered in the loading order
    local lang = localization.languageIndex
    lang = lang + 1
    if lang >= localization.numLanguages then
        lang = 0
    end
    localization:SetLanguage(lang)
end

function HandleQuitButtonPressed(eventType, eventData)
    engine:Exit()
end

-- You can manually change texts, sprites and other aspects of the game when language is changed
function HandleChangeLanguage(eventType, eventData)
    local windowTitle = ui.root:GetChild("WindowTitle", true);
    windowTitle.text = localization:Get("title") .. " (" ..
                           localization.languageIndex .. " " ..
                           localization.language .. ")"

    local buttonText = ui.root:GetChild("ButtonTextQuit", true)
    buttonText.text = localization:Get("quit")

    local text3D = scene_:GetChild("Text3D"):GetComponent("Text3D")
    text3D.text = localization:Get("lang")

    -- A text on the button "Press this button" changes automatically
end
