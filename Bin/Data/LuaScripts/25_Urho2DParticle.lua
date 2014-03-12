-- Urho2D particle example.
-- This sample demonstrates:
--     - Creating a 2D scene with particle
--     - Displaying the scene using the Renderer subsystem
--     - Handling mouse move to move particle

require "LuaScripts/Utilities/Sample"

local scene_ = nil
local cameraNode = nil
local particleNode = nil

function Start()
    -- Execute the common startup for samples
    SampleStart()

    -- Set mouse visible
    input.mouseVisible = true

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
    camera:SetOrthoSize(Vector2(graphics.width, graphics.height) * PIXEL_SIZE)

    local particleModel = cache:GetResource("ParticleModel2D", "Urho2D/LavaFlow.plist")
    if particleModel == nil then
        return
    end

    particleNode = scene_:CreateChild("ParticleEmitter2D")
    local particleEmitter = particleNode:CreateComponent("ParticleEmitter2D")
    particleEmitter.model = particleModel
end

function CreateInstructions()
    -- Construct new Text object, set string to display and font to use
    local instructionText = ui.root:CreateChild("Text")
    instructionText:SetText("Use mouse to move the particle.")
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

function SubscribeToEvents()
    SubscribeToEvent("MouseMove", "HandleMouseMove")
end

function HandleMouseMove(eventType, eventData)
    if particleNode ~= nil then
        local x = eventData:GetInt("x")
        local y = eventData:GetInt("y")
        local camera = cameraNode:GetComponent("Camera")
        particleNode.position = camera:ScreenToWorldPoint(Vector3(x / graphics.width, y / graphics.height, 10.0))
    end
end
