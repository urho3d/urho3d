local numSprites = 100
local sprites = {}
local speeds = {}

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
	sprites = nil
	speeds = nil
end

function InitUI()
	local uiStyle = cache:GetXMLFile("UI/DefaultStyle.xml")
	
	local debugHud = engine:CreateDebugHud()
    debugHud:SetDefaultStyle(uiStyle)
    debugHud:SetMode(DEBUGHUD_SHOW_ALL)
	
	local console = engine:CreateConsole()
    console:SetDefaultStyle(uiStyle)
	
	local cursor = Cursor()	
    cursor:SetStyleAuto(uiStyle)	
	cursor:SetPosition(graphics:GetWidth() / 2, graphics:GetHeight() / 2)
	ui:SetCursor(cursor)
	
	if (GetPlatform() == "Android" or GetPlatform() == "iOS") then
        ui:GetCursor():SetVisible(false)
	end
end

function InitSprites()
	local decalTex = cache:GetTexture2D("Textures/UrhoDecal.dds")
	
	local width = graphics:GetWidth()
	local height = graphics:GetHeight()
	
	for i = 1, numSprites do
        local sprite = Sprite()
        sprite:SetTexture(decalTex)
        sprite:SetFullImageRect()
        sprite:SetPosition(Random(width), Random(height))
		sprite:SetSize(128, 128)		
		sprite:SetHotSpot(64, 64)		
		sprite:SetRotation(Random(360))		
        sprite:SetScale(Random(1) + 0.5)
		
		sprite:SetColor(Color(Random(0.5) + 0.5, Random(0.5) + 0.5, Random(0.5) + 0.5, 1.0))		
        sprite:SetBlendMode(BLEND_ADD)
		
		ui:GetRoot():AddChild(sprite)
		
		table.insert(sprites, sprite)
		table.insert(speeds, Vector2(Random(200) - 100, Random(200) - 100))		
    end
end

function HandleUpdate(eventType, eventData)
	local timeStep = eventData:GetFloat("TimeStep")
	
	local width = graphics:GetWidth()
	local height = graphics:GetHeight()
	
	for i = 1, numSprites do		
		local sprite = sprites[i]
		sprite:SetRotation(sprite:GetRotation() + timeStep * 30)
		
        local newPos = sprite:GetPosition()
		
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
		sprite:SetPosition(newPos)
	end
end

function HandleKeyDown(eventType, eventData)
	local key = eventData:GetInt("Key")
	
	if key == KEY_ESC then
		if ui:GetFocusElement() == nil then
			engine:Exit();
        else
            GetConsole():SetVisible(false)
		end
	end
	
    if key == KEY_F1 then
        GetConsole():Toggle()
	end
	
    if key == KEY_T then
		GetDebugHud():Toggle(DEBUGHUD_SHOW_PROFILER)
	end
end


