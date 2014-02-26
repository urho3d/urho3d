-- Common sample initialization as a framework for all samples.
--    - Create Urho3D logo at screen
--    - Set custom window title and icon
--    - Create Console and Debug HUD, and use F1 and F2 key to toggle them
--    - Toggle rendering options from the keys 1-8
--    - Take screenshots with key 9
--    - Handle Esc key down to hide Console or exit application
--    - Display a splash screen during loading time (activated by default for mobiles)

local logoSprite = nil

function SampleStart()
    -- Display splash screen (comment to disable)
    if GetPlatform() == "Android" or GetPlatform() == "iOS" then SplashScreen() end

    -- Create logo
    CreateLogo()

    -- Set custom window Title & Icon
    SetWindowTitleAndIcon()

    -- Create console and debug HUD
    CreateConsoleAndDebugHud()

    -- Subscribe key down event
    SubscribeToEvent("KeyDown", "HandleKeyDown")
end

function SplashScreen()
    local splashUI = ui.root:CreateChild("BorderImage", "Splash")
    local texture = cache:GetResource("Texture2D", "Textures/LogoLarge.png") -- Get texture
    splashUI.texture = texture -- Set texture
    splashUI:SetSize(texture.width, texture.height)
    splashUI:SetAlignment(HA_CENTER, VA_CENTER)
    engine:RunFrame() -- Render Splash immediately
    SubscribeToEvent("EndRendering", "HandleSplash") -- Keep visible until rendering of the scene
end

function HandleSplash(eventType, eventData)
    -- Remove splash screen when the scene gets rendered
    if ui.root:GetChild("Splash") ~= nil then ui.root:GetChild("Splash"):Remove() end
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
    logoSprite:SetAlignment(HA_LEFT, VA_BOTTOM)

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

    -- Create debug HUD
    engine:CreateDebugHud()
    debugHud.defaultStyle = uiStyle
end

function HandleKeyDown(eventType, eventData)
    local key = eventData:GetInt("Key")
    -- Close console (if open) or exit when ESC is pressed
    if key == KEY_ESC then
        if not console:IsVisible() then
            engine:Exit()
        else
            console:SetVisible(false)
        end

    elseif key == KEY_F1 then
        console:Toggle()

    elseif key == KEY_F2 then
        debugHud:ToggleAll()
    end

    if ui.focusElement == nil then
        -- Texture quality
        if key == KEY_1 then
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
            if quality > SHADOWQUALITY_HIGH_24BIT then
                quality = SHADOWQUALITY_LOW_16BIT
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
