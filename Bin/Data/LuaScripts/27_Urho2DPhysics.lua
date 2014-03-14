-- Urho2D physics sample.
-- This sample demonstrates:
--     - Creating both static and moving 2D physics objects to a scene
--     - Displaying physics debug geometry

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
    scene_:CreateComponent("DebugRenderer")

    -- Create a scene node for the camera, which we will move around
    -- The camera will use default settings (1000 far clip distance, 45 degrees FOV, set aspect ratio automatically)
    cameraNode = scene_:CreateChild("Camera")
    -- Set an initial position for the camera scene node above the plane
    cameraNode.position = Vector3(0.0, 0.0, -10.0)
    local camera = cameraNode:CreateComponent("Camera")
    camera.orthographic = true

    local width = graphics.width * PIXEL_SIZE
    local height = graphics.height * PIXEL_SIZE
    camera:SetOrthoSize(Vector2(width, height))

    -- Create 2D physics world component
    scene_:CreateComponent("PhysicsWorld2D")
    
    local boxSprite = cache:GetResource("Sprite2D", "Urho2D/Box.png")
    local ballSprite = cache:GetResource("Sprite2D", "Urho2D/Ball.png")

    -- Create ground.
    local groundNode = scene_:CreateChild("Ground")
    groundNode.position = Vector3(0.0, -3.0, 0.0)
    groundNode.scale = Vector3(200.0, 1.0, 0.0)
    
    -- Create 2D rigid body for gound
    local groundBody = groundNode:CreateComponent("RigidBody2D")

    local groundSprite = groundNode:CreateComponent("StaticSprite2D")
    groundSprite.sprite = boxSprite

    -- Create box collider for ground
    local groundShape = groundNode:CreateComponent("CollisionBox2D")
    -- Set box size
    groundShape.size = Vector2(0.32, 0.32)
    -- Set friction
    groundShape.friction = 0.5
    
    local NUM_OBJECTS = 100
    for i = 1, NUM_OBJECTS do
        local node  = scene_:CreateChild("RigidBody")
        node.position = Vector3(Random(-0.1, 0.1), 5.0 + i * 0.4, 0.0)

        -- Create rigid body
        local body = node:CreateComponent("RigidBody2D")
        body.bodyType = BT_DYNAMIC

        local staticSprite = node:CreateComponent("StaticSprite2D")
        local shape = nil
        if i % 2 == 0 then
            staticSprite.sprite = boxSprite
            -- Create box
            shape = node:CreateComponent("CollisionBox2D")
            -- Set size
            shape.size = Vector2(0.32, 0.32)
        else
            staticSprite.sprite = ballSprite
            -- Create circle
            shape = node:CreateComponent("CollisionCircle2D")
            -- Set radius
            shape.radius = 0.16
        end
        -- Set density
        shape.density = 1.0
        -- Set friction
        shape.friction = 0.5
        -- Set restitution
        shape.restitution = 0.1
    end
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
