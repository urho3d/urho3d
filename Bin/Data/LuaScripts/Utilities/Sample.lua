Sample = {}

function Sample:Start()
    self.logoSprite = nil
    self:CreateLogo()
    self:CreateConsoleAndDebugHud()
end

function Sample:Stop()
    self.logoSprite = nil
end

function Sample:CreateLogo()
    local cache = GetCache()
    local logoTexture = cache:GetTexture2D("Textures/LogoLarge.png")
    if logoTexture == nil then
        return
    end
    
    local ui = GetUI()
    self.logoSprite = ui.root:CreateSprite()
    --self.logoSprite.texture = logoTexture
    self.logoSprite:SetTexture(logoTexture)
    
    
    local textureWidth = logoTexture.width
    local textureHeight = logoTexture.height
    
    self.logoSprite:SetScale(256 / textureWidth)
    --self.logoSprite.size = IntVector2(textureWidth, textureHeight)
    self.logoSprite:SetSize(textureWidth, textureHeight)
    self.logoSprite.hotSpot = IntVector2(0, textureHeight)
    
    self.logoSprite:SetAlignment(HA_LEFT, VA_BOTTOM);
end

function Sample:CreateConsoleAndDebugHud()
    local cache = GetCache()
    local uiStyle = cache:GetXMLFile("UI/DefaultStyle.xml")
    if uiStyle == nil then
        return
    end
    
    local engine = GetEngine()
    local console = engine:CreateConsole()
    console.defaultStyle = uiStyle
    
    local debugHud = engine:CreateDebugHud()
    debugHud.defaultStyle = uiStyle
    
    SubscribeToEvent("KeyDown", "Sample.HandleKeyDownEvent")
end

function Sample.HandleKeyDownEvent(eventType, eventData)
    local key = eventData:GetInt("Key")
    
    if key == KEY_ESC then
        local ui = GetUI()
        if ui:GetFocusElement() == nil then
            local engine = GetEngine()
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
