local logoSprite = nil

local cache = GetCache()
local engine = GetEngine()
local ui = GetUI()

function SampleStart()
    CreateLogo()
    CreateConsoleAndDebugHud()
end

function SampleStop()
    logoSprite = nil
end

function CreateLogo()
    local logoTexture = cache:GetTexture2D("Textures/LogoLarge.png")
    if logoTexture == nil then
        return
    end    
    
    logoSprite = ui.root:CreateSprite()
    logoSprite.texture = logoTexture
    local textureWidth = logoTexture.width
    local textureHeight = logoTexture.height
    
    logoSprite:SetScale(256 / textureWidth)
    logoSprite.size = IntVector2(textureWidth, textureHeight)
    logoSprite.hotSpot = IntVector2(0, textureHeight)

    logoSprite:SetAlignment(HA_LEFT, VA_BOTTOM);
end

function CreateConsoleAndDebugHud()
    local uiStyle = cache:GetXMLFile("UI/DefaultStyle.xml")
    if uiStyle == nil then
        return
    end
    
    local console = engine:CreateConsole()
    console.defaultStyle = uiStyle
    
    local debugHud = engine:CreateDebugHud()
    debugHud.defaultStyle = uiStyle
    
    SubscribeToEvent("KeyDown", "HandleKeyDownEventForSample")
end

function HandleKeyDownEventForSample(eventType, eventData)
    local key = eventData:GetInt("Key")
    
    if key == KEY_ESC then
        if ui:GetFocusElement() == nil then
            engine:Exit()
        else
            local console = GetConsole()
            console:SetVisible(false)
        end
    end
    
    if key == KEY_F1 then
        local console = GetConsole()
        console:Toggle()
    end
    
    if key == KEY_F2 then
        local debugHud = GetDebugHud()
        debugHud:ToggleAll()
    end
end
