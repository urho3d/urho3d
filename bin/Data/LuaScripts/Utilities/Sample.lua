-- Common sample initialization as a framework for all samples.
--    - Create Urho3D logo at screen
--    - Set custom window title and icon
--    - Create Console and Debug HUD, and use F1 and F2 key to toggle them
--    - Toggle rendering options from the keys 1-8
--    - Take screenshots with key 9
--    - Handle Esc key down to hide Console or exit application
--    - Init touch input on mobile platform using screen joysticks (patched for each individual sample)

local logoSprite = nil
scene_ = nil -- Scene
screenJoystickIndex = M_MAX_UNSIGNED -- Screen joystick index for navigational controls (mobile platforms only)
screenJoystickSettingsIndex = M_MAX_UNSIGNED -- Screen joystick index for settings (mobile platforms only)
touchEnabled = false -- Flag to indicate whether touch input has been enabled
paused = false -- Pause flag
drawDebug = false -- Draw debug geometry flag
cameraNode = nil -- Camera scene node
yaw = 0 -- Camera yaw angle
pitch = 0 -- Camera pitch angle
TOUCH_SENSITIVITY = 2
debugHudMode = 0
useMouseMode_ = MM_ABSOLUTE

function SampleStart()
    if GetPlatform() == "Android" or GetPlatform() == "iOS" or input.touchEmulation then
        -- On mobile platform, enable touch by adding a screen joystick
        InitTouchInput()
    elseif input:GetNumJoysticks() == 0 then
        -- On desktop platform, do not detect touch when we already got a joystick
        SubscribeToEvent("TouchBegin", "HandleTouchBegin")
    end
    -- Create logo
    CreateLogo()

    -- Set custom window Title & Icon
    SetWindowTitleAndIcon()

    -- Create console and debug HUD
    CreateConsoleAndDebugHud()

    -- Subscribe key down event
    SubscribeToEvent("KeyDown", "HandleKeyDown")

    -- Subscribe key up event
    SubscribeToEvent("KeyUp", "HandleKeyUp")

    -- Subscribe scene update event
    SubscribeToEvent("SceneUpdate", "HandleSceneUpdate")
end

function InitTouchInput()
    touchEnabled = true
    local layout = cache:GetResource("XMLFile", "UI/ScreenJoystick_Samples.xml")
    local patchString = GetScreenJoystickPatchString()
    if patchString ~= "" then
        -- Patch the screen joystick layout further on demand
        local patchFile = XMLFile()
        if patchFile:FromString(patchString) then layout:Patch(patchFile) end
    end
    screenJoystickIndex = input:AddScreenJoystick(layout, cache:GetResource("XMLFile", "UI/DefaultStyle.xml"))
    input:SetScreenJoystickVisible(screenJoystickSettingsIndex, true)
end

function SampleInitMouseMode(mode)
    useMouseMode_ = mode
    if GetPlatform() ~= "Web" then
        if useMouseMode_ == MM_FREE then
            input.mouseVisible = true
        end

        if useMouseMode_ ~= MM_ABSOLUTE then
            input.mouseMode = useMouseMode_

            if console ~= nil and console.visible then
                input:SetMouseMode(MM_ABSOLUTE, true)
            end
        end
    else
        input.mouseVisible = true
        SubscribeToEvent("MouseButtonDown", "HandleMouseModeRequest")
        SubscribeToEvent("MouseModeChanged", "HandleMouseModeChange")
    end
end

function SetLogoVisible(enable)
    if logoSprite ~= nil then
        logoSprite.visible = enable
    end
end

function CreateLogo()
    -- Get logo texture
    local logoTexture = cache:GetResource("Texture2D", "Textures/LogoLarge.png")
    if logoTexture == nil then
        return
    end

    -- Create logo sprite and add to the UI layout
    logoSprite = ui.root:CreateChild("Sprite")

    -- Set logo sprite texture
    logoSprite:SetTexture(logoTexture)

    local textureWidth = logoTexture.width
    local textureHeight = logoTexture.height

    -- Set logo sprite scale
    logoSprite:SetScale(256 / textureWidth)

    -- Set logo sprite size
    logoSprite:SetSize(textureWidth, textureHeight)

    -- Set logo sprite hot spot
    logoSprite.hotSpot = IntVector2(0, textureHeight)

    -- Set logo sprite alignment
    logoSprite:SetAlignment(HA_LEFT, VA_BOTTOM);

    -- Make logo not fully opaque to show the scene underneath
    logoSprite.opacity = 0.75

    -- Set a low priority for the logo so that other UI elements can be drawn on top
    logoSprite.priority = -100
end

function SetWindowTitleAndIcon()
    local icon = cache:GetResource("Image", "Textures/UrhoIcon.png")
    graphics:SetWindowIcon(icon)
    graphics.windowTitle = "Urho3D Sample"
end

function CreateConsoleAndDebugHud()
    -- Get default style
    local uiStyle = cache:GetResource("XMLFile", "UI/DefaultStyle.xml")
    if uiStyle == nil then
        return
    end

    -- Create console
    engine:CreateConsole()
    console.defaultStyle = uiStyle
    console.background.opacity = 0.8

    -- Create debug HUD
    engine:CreateDebugHud()
    debugHud.defaultStyle = uiStyle
end

function HandleKeyUp(eventType, eventData)
    local key = eventData["Key"]:GetInt()
    -- Close console (if open) or exit when ESC is pressed
    if key == KEY_ESC then
        if console:IsVisible() then
            console:SetVisible(false)
        else
            if GetPlatform() == "Web" then
                input.mouseVisible = true;
                if (useMouseMode_ ~= MM_ABSOLUTE) then
                    input.mouseMode = MM_FREE;
                end
            else
                engine:Exit();
            end
        end
    end
end

function HandleKeyDown(eventType, eventData)
    local key = eventData["Key"]:GetInt()

    if key == KEY_F1 then
        console:Toggle()
    elseif key == KEY_F2 then
        if debugHud:GetMode() == DEBUGHUD_SHOW_ALL_MEMORY or debugHud:GetMode() == 0 then
            debugHud:SetMode(DEBUGHUD_SHOW_ALL)
        else
            debugHud:SetMode(0)
        end
    elseif key == KEY_F3 then
        if debugHud:GetMode() == DEBUGHUD_SHOW_ALL or debugHud:GetMode() == 0 then
            debugHud:SetMode(DEBUGHUD_SHOW_ALL_MEMORY)
        else
            debugHud:SetMode(0)
        end
    end

    if ui.focusElement == nil then
        -- Preferences / Pause
        if key == KEY_SELECT and touchEnabled then
            paused = not paused
            if screenJoystickSettingsIndex == M_MAX_UNSIGNED then
                -- Lazy initialization
                screenJoystickSettingsIndex = input:AddScreenJoystick(cache:GetResource("XMLFile", "UI/ScreenJoystickSettings_Samples.xml"), cache:GetResource("XMLFile", "UI/DefaultStyle.xml"))
            else
                input:SetScreenJoystickVisible(screenJoystickSettingsIndex, paused)
            end

        -- Texture quality
        elseif key == KEY_1 then
            local quality = renderer.textureQuality
            quality = quality + 1
            if quality > QUALITY_HIGH then
                quality = QUALITY_LOW
            end
            renderer.textureQuality = quality

        -- Material quality
        elseif key == KEY_2 then
            local quality = renderer.materialQuality
            quality = quality + 1
            if quality > QUALITY_HIGH then
                quality = QUALITY_LOW
            end
            renderer.materialQuality = quality

        -- Specular lighting
        elseif key == KEY_3 then
            renderer.specularLighting = not renderer.specularLighting

        -- Shadow rendering
        elseif key == KEY_4 then
            renderer.drawShadows = not renderer.drawShadows

        -- Shadow map resolution
        elseif key == KEY_5 then
            local shadowMapSize = renderer.shadowMapSize
            shadowMapSize = shadowMapSize * 2
            if shadowMapSize > 2048 then
                shadowMapSize = 512
            end
            renderer.shadowMapSize = shadowMapSize

        -- Shadow depth and filtering quality
        elseif key == KEY_6 then
            local quality = renderer.shadowQuality
            quality = quality + 1
            if quality > SHADOWQUALITY_BLUR_VSM then
                quality = SHADOWQUALITY_SIMPLE_16BIT
            end
            renderer.shadowQuality = quality

        -- Occlusion culling
        elseif key == KEY_7 then
            local occlusion = renderer.maxOccluderTriangles > 0
            occlusion = not occlusion
            if occlusion then
                renderer.maxOccluderTriangles = 5000
            else
                renderer.maxOccluderTriangles = 0
            end

        -- Instancing
        elseif key == KEY_8 then
            renderer.dynamicInstancing = not renderer.dynamicInstancing

        -- Take screenshot
        elseif key == KEY_9 then
            local screenshot = Image()
            graphics:TakeScreenShot(screenshot)
            local timeStamp = Time:GetTimeStamp()
            timeStamp = string.gsub(timeStamp, "[:. ]", "_")
            -- Here we save in the Data folder with date and time appended
            screenshot:SavePNG(fileSystem:GetProgramDir() .. "Data/Screenshot_" .. timeStamp .. ".png")
        end
    end
end

function HandleSceneUpdate(eventType, eventData)
    -- Move the camera by touch, if the camera node is initialized by descendant sample class
    if touchEnabled and cameraNode then
        for i=0, input:GetNumTouches()-1 do
            local state = input:GetTouch(i)
            if not state.touchedElement then -- Touch on empty space
                if state.delta.x or state.delta.y then
                    local camera = cameraNode:GetComponent("Camera")
                    if not camera then return end

                    yaw = yaw + TOUCH_SENSITIVITY * camera.fov / graphics.height * state.delta.x
                    pitch = pitch + TOUCH_SENSITIVITY * camera.fov / graphics.height * state.delta.y

                    -- Construct new orientation for the camera scene node from yaw and pitch; roll is fixed to zero
                    cameraNode:SetRotation(Quaternion(pitch, yaw, 0))
                else
                    -- Move the cursor to the touch position
                    local cursor = ui:GetCursor()
                    if cursor and cursor:IsVisible() then cursor:SetPosition(state.position) end
                end
            end
        end
    end
end

function HandleTouchBegin(eventType, eventData)
    -- On some platforms like Windows the presence of touch input can only be detected dynamically
    InitTouchInput()
    UnsubscribeFromEvent("TouchBegin")
end

-- If the user clicks the canvas, attempt to switch to relative mouse mode on web platform
function HandleMouseModeRequest(eventType, eventData)
    if console ~= nil and console.visible then
        return
    end

    if input.mouseMode == MM_ABSOLUTE then
        input.mouseVisible = false
    elseif useMouseMode_ == MM_FREE then
        input.mouseVisible = true
    end

    input.mouseMode = useMouseMode_
end

-- If the user clicks the canvas, attempt to switch to relative mouse mode on web platform
function HandleMouseModeChange(eventType, eventData)
    mouseLocked = eventData["MouseLocked"]:GetBool()
    input.mouseVisible = not mouseLocked;
end

-- Create empty XML patch instructions for screen joystick layout if none defined
function GetScreenJoystickPatchString()
    return ""
end
