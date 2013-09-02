-- Common sample initialization as a framework for all samples.
--    - Create Urho3D logo at screen
--    - Create Console and Debug HUD, and use F1 and F2 key to toggle them
--    - Toggle rendering options from the keys 1-8
--    - Handle Esc key down to hide Console or exit application

local logoSprite = nil

function SampleStart()
    -- Create logo
    CreateLogo()
    
    -- Create console and debug HUD
    CreateConsoleAndDebugHud()

    -- Subscribe key down event
    SubscribeToEvent("KeyDown", "HandleKeyDown")
end

function SetLogoVisible(enable)
    if logoSprite ~= nil then
        logoSprite.visible = enable
    end
end

function CreateLogo()
    -- Get logo texture
    local cache = GetCache()
    local logoTexture = cache:GetTexture2D("Textures/LogoLarge.png")
    if logoTexture == nil then
        return
    end
    
    -- Create logo sprite and add to the UI layout
    local ui = GetUI()
    logoSprite = ui.root:CreateSprite()
    
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

function CreateConsoleAndDebugHud()
    -- Get default style
    local cache = GetCache()
    local uiStyle = cache:GetXMLFile("UI/DefaultStyle.xml")
    if uiStyle == nil then
        return
    end
    
    -- Create console
    local engine = GetEngine()
    local console = engine:CreateConsole()
    console.defaultStyle = uiStyle
    
    -- Create debug HUD
    local debugHud = engine:CreateDebugHud()
    debugHud.defaultStyle = uiStyle
end

function HandleKeyDown(eventType, eventData)
    local key = eventData:GetInt("Key")
    -- Close console (if open) or exit when ESC is pressed
    if key == KEY_ESC then
        local ui = GetUI()
        if ui:GetFocusElement() == nil then
            local engine = GetEngine()
            engine:Exit()
        else
            local console = GetConsole()
            console:SetVisible(false)
        end

    elseif key == KEY_F1 then
        local console = GetConsole()
        console:Toggle()

    elseif key == KEY_F2 then
        local debugHud = GetDebugHud()
        debugHud:ToggleAll()
    end

    local ui = GetUI()
    if ui.focusElement == nil then
        local renderer = GetRenderer()
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
        end
    end
end
