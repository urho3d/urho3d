local numSprites = 100
local sprites = {}
local speeds = {}

local context = GetContext()

local cache = GetCache()
local engine = GetEngine()
local graphics = GetGraphics()
local ui = GetUI()

function Start()
    if engine.headless then
        ErrorDialog("SpriteTest", "Headless mode is not supported. The program will now exit.")
        engine:Exit()
        return
    end
    
    InitUI()
    InitSprites()
    
    SubscribeToEvent("Update", "HandleUpdate")
    SubscribeToEvent("KeyDown", "HandleKeyDown")
end

function Stop()
end

function InitUI()
    local uiStyle = cache:GetXMLFile("UI/DefaultStyle.xml")
    
    local debugHud = engine:CreateDebugHud()
    debugHud.defaultStyle = uiStyle
    debugHud.mode = DEBUGHUD_SHOW_ALL
    
    local console = engine:CreateConsole()
    console.defaultStyle = uiStyle
    
    local cursor = Cursor:new(context)
    cursor.styleAuto = uiStyle
    cursor.position = IntVector2(graphics:GetWidth() / 2, graphics:GetHeight() / 2)
    ui.cursor = cursor
    
    if GetPlatform() == "Android" or GetPlatform() == "iOS" then
        ui.cursor.visible = false
    end
end

function InitSprites()
    local decalTex = cache:GetTexture2D("Textures/UrhoDecal.dds")
    
    local width = graphics.width
    local height = graphics.height
    
    for i = 1, numSprites do
        local sprite = Sprite:new(context)
        sprite.texture = decalTex
        sprite:SetFullImageRect()
        sprite.position = Vector2(Random(width), Random(height))
        sprite:SetSize(128, 128)
        sprite.hotSpot = IntVector2(64, 64)
        sprite.rotation = Random(360)
        sprite.scale = Vector2(1, 1) * (Random(1) + 0.5)
        
        sprite:SetColor(Color(Random(0.5) + 0.5, Random(0.5) + 0.5, Random(0.5) + 0.5, 1.0))
        sprite.blendMode = BLEND_ADD
        
        ui.root:AddChild(sprite)
        
        table.insert(sprites, sprite)
        table.insert(speeds, Vector2(Random(200) - 100, Random(200) - 100))        
    end
end

function HandleUpdate(eventType, eventData)
    local timeStep = eventData:GetFloat("TimeStep")
    
    local width = graphics.width
    local height = graphics.height
    
    for i = 1, numSprites do
        local sprite = sprites[i]
        sprite.rotation = sprite.rotation + timeStep * 30
        
        local newPos = sprite.position
        newPos = newPos + speeds[i] * timeStep
        
        if newPos.x >= width then
            newPos.x = newPos.x - width
        elseif newPos.x < 0 then
            newPos.x = newPos.x + width
        end
        if newPos.y >= height then
            newPos.y = newPos.y - height
        elseif newPos.y < 0 then
            newPos.y = newPos.y + height
        end
        sprite.position = newPos
    end
end

function HandleKeyDown(eventType, eventData)
    local key = eventData:GetInt("Key")
    
    if key == KEY_ESC then
        if ui.focusElement == nil then
            engine:Exit();
        else
            local console = GetConsole()
            console.visible = false
        end
    end
    
    if key == KEY_F1 then
        GetConsole():Toggle()
    end
    
    if key == KEY_T then
        GetDebugHud():Toggle(DEBUGHUD_SHOW_PROFILER)
    end
end