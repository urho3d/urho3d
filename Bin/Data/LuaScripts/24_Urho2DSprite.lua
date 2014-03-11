-- Urho2D sprite example.
-- This sample demonstrates:
--     - Creating a 2D scene with sprite
--     - Displaying the scene using the Renderer subsystem
--     - Handling keyboard to move and zoom 2D camera
--     - Usage of Lua Closure to update scene

require "LuaScripts/Utilities/Sample"

local scene_ = nil
local cameraNode = nil

function Start()
    -- Execute the common startup for samples
    SampleStart()

    -- Create the scene content
    CreateScene()

    -- Create the UI content
    CreateInstructions()

    -- Setup the viewport for displaying the scene
    SetupViewport()

    -- Hook up to the frame update events
    SubscribeToEvents()
end

function CreateScene()
    scene_ = Scene()

    -- Create the Octree component to the scene. This is required before adding any drawable components, or else nothing will
    -- show up. The default octree volume will be from (-1000, -1000, -1000) to (1000, 1000, 1000) in world coordinates it
    -- is also legal to place objects outside the volume but their visibility can then not be checked in a hierarchically
    -- optimizing manner
    scene_:CreateComponent("Octree")

    -- Create a scene node for the camera, which we will move around
    -- The camera will use default settings (1000 far clip distance, 45 degrees FOV, set aspect ratio automatically)
    cameraNode = scene_:CreateChild("Camera")
    -- Set an initial position for the camera scene node above the plane
    cameraNode.position = Vector3(0.0, 0.0, -10.0)
    local camera = cameraNode:CreateComponent("Camera")
    camera.orthographic = true

    local width = graphics.width / scene_.pixelsPerUnit
    local height = graphics.height / scene_.pixelsPerUnit
    camera:SetOrthoSize(Vector2(width, height))

    local sprite = cache:GetResource("Sprite2D", "Urho2D/Aster.png")
    if sprite == nil then
        return
    end

    local spriteNodes = {}
    local NUM_SPRITES = 200
    local halfWidth = width * 0.5
    local halfHeight = height * 0.5
    for i = 1, NUM_SPRITES do
        local spriteNode = scene_:CreateChild("StaticSprite2D")
        spriteNode.position = Vector3(Random(-halfWidth, halfWidth), Random(-halfHeight, halfHeight), 0.0)
        
        local staticSprite = spriteNode:CreateComponent("StaticSprite2D")
        -- Set color
        staticSprite.color = Color(Random(1.0), Random(1.0), Random(1.0), 1.0)
        -- Set blend mode
        staticSprite.blendMode = BLEND_ALPHA
        -- Set sprite
        staticSprite.sprite = sprite

        -- Set move speed
        spriteNode.moveSpeed = Vector3(Random(-2.0, 2.0), Random(-2.0, 2.0), 0.0)
        -- Set rotate speed
        spriteNode.rotateSpeed = Random(-90.0, 90.0)

        table.insert(spriteNodes, spriteNode)
    end

    scene_.Update = function(self, timeStep)
        for _, spriteNode in ipairs(spriteNodes) do
            local position = spriteNode.position
            local moveSpeed = spriteNode.moveSpeed
            local newPosition = position + moveSpeed * timeStep

            if newPosition.x < -halfWidth or newPosition.x > halfWidth then
                newPosition.x = position.x
                moveSpeed.x = -moveSpeed.x
            end

            if newPosition.y < -halfHeight or newPosition.y > halfHeight then
                newPosition.y = position.y
                moveSpeed.y = -moveSpeed.y
            end

            spriteNode.position = newPosition
            spriteNode:Roll(spriteNode.rotateSpeed * timeStep)
        end
    end

    local animation = cache:GetResource("Animation2D", "Urho2D/GoldIcon.anm")
    if animation == nil then
        return
    end

    local spriteNode = scene_:CreateChild("AnimatedSprite2D")
    spriteNode.position = Vector3(0.0, 0.0, -1.0)
    
    local animatedSprite = spriteNode:CreateComponent("AnimatedSprite2D")
    -- Set animation
    animatedSprite.animation = animation
    -- Set blend mode
    animatedSprite.blendMode = BLEND_ALPHA
end

function CreateInstructions()
    -- Construct new Text object, set string to display and font to use
    local instructionText = ui.root:CreateChild("Text")
    instructionText:SetText("Use WASD keys and mouse to move, Use PageUp PageDown to zoom.")
    instructionText:SetFont(cache:GetResource("Font", "Fonts/Anonymous Pro.ttf"), 15)

    -- Position the text relative to the screen center
    instructionText.horizontalAlignment = HA_CENTER
    instructionText.verticalAlignment = VA_CENTER
    instructionText:SetPosition(0, ui.root.height / 4)
end

function SetupViewport()
    -- Set up a viewport to the Renderer subsystem so that the 3D scene can be seen. We need to define the scene and the camera
    -- at minimum. Additionally we could configure the viewport screen size and the rendering path (eg. forward / deferred) to
    -- use, but now we just use full screen and default render path configured in the engine command line options
    local viewport = Viewport:new(scene_, cameraNode:GetComponent("Camera"))
    renderer:SetViewport(0, viewport)
end

function MoveCamera(timeStep)
    -- Do not move if the UI has a focused element (the console)
    if ui.focusElement ~= nil then
        return
    end

    -- Movement speed as world units per second
    local MOVE_SPEED = 4.0

    -- Read WASD keys and move the camera scene node to the corresponding direction if they are pressed
    -- Use the TranslateRelative() function to move relative to the node's orientation. Alternatively we could
    -- multiply the desired direction with the node's orientation quaternion, and use just Translate()
    if input:GetKeyDown(KEY_W) then
        cameraNode:TranslateRelative(Vector3.UP * MOVE_SPEED * timeStep)
    end
    if input:GetKeyDown(KEY_S) then
        cameraNode:TranslateRelative(Vector3.DOWN * MOVE_SPEED * timeStep)
    end
    if input:GetKeyDown(KEY_A) then
        cameraNode:TranslateRelative(Vector3.LEFT * MOVE_SPEED * timeStep)
    end
    if input:GetKeyDown(KEY_D) then
        cameraNode:TranslateRelative(Vector3.RIGHT * MOVE_SPEED * timeStep)
    end

    if input:GetKeyDown(KEY_PAGEUP) then
        local camera = cameraNode:GetComponent("Camera")
        camera.zoom = camera.zoom * 1.01
    end

    if input:GetKeyDown(KEY_PAGEDOWN) then
        local camera = cameraNode:GetComponent("Camera")
        camera.zoom = camera.zoom * 0.99
    end
end

function SubscribeToEvents()
    -- Subscribe HandleUpdate() function for processing update events
    SubscribeToEvent("Update", "HandleUpdate")
end

function HandleUpdate(eventType, eventData)
    -- Take the frame time step, which is stored as a float
    local timeStep = eventData:GetFloat("TimeStep")

    -- Move the camera, scale movement with time step
    MoveCamera(timeStep)

    -- Update scene
    scene_:Update(timeStep)
end
