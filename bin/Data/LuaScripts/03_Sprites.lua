-- Moving sprites example.
-- This sample demonstrates:
--     - Adding Sprite elements to the UI
--     - Storing custom data (sprite velocity) inside UI elements
--     - Handling frame update events in which the sprites are moved

require "LuaScripts/Utilities/Sample"

local numSprites = 100
local sprites = {}

-- Custom variable identifier for storing sprite velocity within the UI element
local VAR_VELOCITY = StringHash("Velocity")

function Start()
    -- Execute the common startup for samples
    SampleStart()

    -- Create the sprites to the user interface
    CreateSprites()

    -- Hook up to the frame update events
    SubscribeToEvents()
end

function CreateSprites()
    local decalTex = cache:GetResource("Texture2D", "Textures/UrhoDecal.dds")

    local width = graphics.width
    local height = graphics.height

    for i = 1, numSprites do
        -- Create a new sprite, set it to use the texture
        local sprite = Sprite:new()
        sprite.texture = decalTex
        sprite:SetFullImageRect()

        -- The UI root element is as big as the rendering window, set random position within it
        sprite.position = Vector2(Random(width), Random(height))

        -- Set sprite size & hotspot in its center
        sprite:SetSize(128, 128)
        sprite.hotSpot = IntVector2(64, 64)

        -- Set random rotation in degrees and random scale
        sprite.rotation = Random(360.0)
        sprite.scale = Vector2(1.0, 1.0) * (Random(1.0) + 0.5)

        -- Set random color and additive blending mode
        sprite:SetColor(Color(Random(0.5) + 0.5, Random(0.5) + 0.5, Random(0.5) + 0.5, 1.0))
        sprite.blendMode = BLEND_ADD

        -- Add as a child of the root UI element
        ui.root:AddChild(sprite)

        -- Store sprite's velocity as a custom variable
        sprite:SetVar(VAR_VELOCITY, Variant(Vector2(Random(200.0) - 100.0, Random(200.0) - 100.0)))

        table.insert(sprites, sprite)
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
        newPos = newPos + sprite:GetVar(VAR_VELOCITY):GetVector2() * timeStep

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

-- Create XML patch instructions for screen joystick layout specific to this sample app
function GetScreenJoystickPatchString()
    return
        "<patch>" ..
        "    <add sel=\"/element/element[./attribute[@name='Name' and @value='Hat0']]\">" ..
        "        <attribute name=\"Is Visible\" value=\"false\" />" ..
        "    </add>" ..
        "</patch>"
end
