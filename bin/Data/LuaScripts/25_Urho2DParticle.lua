-- Urho2D particle example.
-- This sample demonstrates:
--     - Creating a 2D scene with particle
--     - Displaying the scene using the Renderer subsystem
--     - Handling mouse move to move particle

require "LuaScripts/Utilities/Sample"

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

    -- Set the mouse mode to use in the sample
    SampleInitMouseMode(MM_FREE)

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
    camera.orthoSize = graphics.height * PIXEL_SIZE
    camera.zoom = 1.2 * Min(graphics.width / 1280, graphics.height / 800) -- Set zoom according to user's resolution to ensure full visibility (initial zoom (1.2) is set for full visibility at 1280x800 resolution)

    local particleEffect = cache:GetResource("ParticleEffect2D", "Urho2D/sun.pex")
    if particleEffect == nil then
        return
    end

    particleNode = scene_:CreateChild("ParticleEmitter2D")
    local particleEmitter = particleNode:CreateComponent("ParticleEmitter2D")
    particleEmitter.effect = particleEffect

    local greenSpiralEffect = cache:GetResource("ParticleEffect2D", "Urho2D/greenspiral.pex")
    if greenSpiralEffect == nil then
        return
    end

    greenSpiralNode = scene_:CreateChild("GreenSpiral")
    local greenSpiralEmitter = greenSpiralNode:CreateComponent("ParticleEmitter2D")
    greenSpiralEmitter.effect = greenSpiralEffect
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
    -- Subscribe HandleMouseMove() function for tracking mouse/touch move events
    SubscribeToEvent("MouseMove", "HandleMouseMove")
    if touchEnabled then SubscribeToEvent("TouchMove", "HandleMouseMove") end

    -- Unsubscribe the SceneUpdate event from base class to prevent camera pitch and yaw in 2D sample
    UnsubscribeFromEvent("SceneUpdate")
end

function HandleMouseMove(eventType, eventData)
    if particleNode ~= nil then
        local x = eventData["x"]:GetInt()
        local y = eventData["y"]:GetInt()
        local camera = cameraNode:GetComponent("Camera")
        particleNode.position = camera:ScreenToWorldPoint(Vector3(x / graphics.width, y / graphics.height, 10.0))
    end
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
