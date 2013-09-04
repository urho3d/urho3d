-- Moving sprites example.
-- This sample demonstrates:
--     - Adding Sprite elements to the UI;
--     - Storing custom data (sprite velocity) inside UI elements;
--     - Handling frame update events in which the sprites are moved;

require "LuaScripts/Utilities/Sample"

local numSprites = 100
local sprites = {}
local speeds = {}

local context = GetContext()

local cache = GetCache()
local engine = GetEngine()
local graphics = GetGraphics()
local ui = GetUI()

function Start()
    -- Execute the common startup for samples
    SampleStart()
    
    -- Create the sprites to the user interface
    CreateSprites();

    -- Hook up to the frame update events
    SubscribeToEvents();
end

function Stop()
end

function CreateSprites()
    local decalTex = cache:GetResource("Texture2D", "Textures/UrhoDecal.dds")
    
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

function SubscribeToEvents()
    -- Subscribe HandleUpdate() function for processing update events
    SubscribeToEvent("Update", "HandleUpdate")
end

function MoveSprites(timeStep)
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

function HandleUpdate(eventType, eventData)
    local timeStep = eventData:GetFloat("TimeStep")

    MoveSprites(timeStep)
end
