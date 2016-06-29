-- Ribbon trail demo.
-- This sample demonstrates how to use both trail types of RibbonTrail component.

require "LuaScripts/Utilities/Sample"

local boxNode1 = nil
local boxNode2 = nil
local swordTrail = nil
local ninjaAnimCtrl = nil
local timeStepSum = 0.0
local swordTrailStartTime = 0.2
local swordTrailEndTime = 0.46

function Start()
    -- Execute the common startup for samples
    SampleStart()

    -- Create the scene content
    CreateScene()

    -- Create the UI content
    CreateInstructions()

    -- Setup the viewport for displaying the scene
    SetupViewport()

    -- Set the mouse mode to use in the sample
    SampleInitMouseMode(MM_RELATIVE)

    -- Hook up to the frame update events
    SubscribeToEvents()
end

function CreateScene()
    scene_ = Scene()

    -- Create octree, use default volume (-1000, -1000, -1000) to (1000, 1000, 1000)
    scene_:CreateComponent("Octree")

    -- Create scene node & StaticModel component for showing a static plane
    local planeNode = scene_:CreateChild("Plane")
    planeNode.scale = Vector3(100.0, 1.0, 100.0)
    local planeObject = planeNode:CreateComponent("StaticModel")
    planeObject.model = cache:GetResource("Model", "Models/Plane.mdl")
    planeObject.material = cache:GetResource("Material", "Materials/StoneTiled.xml")

    -- Create a directional light to the world.
    local lightNode = scene_:CreateChild("DirectionalLight")
    lightNode.direction = Vector3(0.6, -1.0, 0.8) -- The direction vector does not need to be normalized
    local light = lightNode:CreateComponent("Light")
    light.lightType = LIGHT_DIRECTIONAL
    light.castShadows = true
    light.shadowBias = BiasParameters(0.00005, 0.5)
    -- Set cascade splits at 10, 50 and 200 world units, fade shadows out at 80% of maximum shadow distance
    light.shadowCascade = CascadeParameters(10.0, 50.0, 200.0, 0.0, 0.8)

    -- Create first box for face camera trail demo with 1 column.
    boxNode1 = scene_:CreateChild("Box1")
    local box1 = boxNode1:CreateComponent("StaticModel")
    box1.model = cache:GetResource("Model", "Models/Box.mdl")
    box1.castShadows = true
    local boxTrail1 = boxNode1:CreateComponent("RibbonTrail")
    boxTrail1.material = cache:GetResource("Material", "Materials/RibbonTrail.xml")
    boxTrail1.startColor = Color(1.0, 0.5, 0.0, 1.0)
    boxTrail1.endColor = Color(1.0, 1.0, 0.0, 0.0)
    boxTrail1.width = 0.5
    boxTrail1.updateInvisible = true

    -- Create second box for face camera trail demo with 4 column.
    -- This will produce less distortion than first trail.
    boxNode2 = scene_:CreateChild("Box2")
    local box2 = boxNode2:CreateComponent("StaticModel")
    box2.model = cache:GetResource("Model", "Models/Box.mdl")
    box2.castShadows = true
    local boxTrail2 = boxNode2:CreateComponent("RibbonTrail")
    boxTrail2.material = cache:GetResource("Material", "Materials/RibbonTrail.xml")
    boxTrail2.startColor = Color(1.0, 0.5, 0.0, 1.0)
    boxTrail2.endColor = Color(1.0, 1.0, 0.0, 0.0)
    boxTrail2.width = 0.5
    boxTrail2.tailColumn = 4
    boxTrail2.updateInvisible = true

    -- Load ninja animated model for bone trail demo.
    local ninjaNode = scene_:CreateChild("Ninja")
    ninjaNode.position = Vector3(5.0, 0.0, 0.0)
    ninjaNode.rotation = Quaternion(0.0, 180.0, 0.0)
    local ninja = ninjaNode:CreateComponent("AnimatedModel")
    ninja.model = cache:GetResource("Model", "Models/NinjaSnowWar/Ninja.mdl")
    ninja.material = cache:GetResource("Material", "Materials/NinjaSnowWar/Ninja.xml")
    ninja.castShadows = true

    -- Create animation controller and play attack animation.
    ninjaAnimCtrl = ninjaNode:CreateComponent("AnimationController")
    ninjaAnimCtrl:PlayExclusive("Models/NinjaSnowWar/Ninja_Attack3.ani", 0, true, 0.0)

    -- Add ribbon trail to tip of sword.
    local swordTip = ninjaNode:GetChild("Joint29", true)
    swordTrail = swordTip:CreateComponent("RibbonTrail")

    -- Set sword trail type to bone and set other parameters.
    swordTrail.trailType = TT_BONE
    swordTrail.material = cache:GetResource("Material", "Materials/SlashTrail.xml")
    swordTrail.lifetime = 0.22
    swordTrail.startColor = Color(1.0, 1.0, 1.0, 0.75)
    swordTrail.endColor = Color(0.2, 0.5, 1.0, 0.0)
    swordTrail.tailColumn = 4
    swordTrail.updateInvisible = true

    -- Add floating text for info.
    local boxTextNode1 = scene_:CreateChild("BoxText1")
    boxTextNode1.position = Vector3(-1.0, 2.0, 0.0)
    local boxText1 = boxTextNode1:CreateComponent("Text3D")
    boxText1.text = "Face Camera Trail (4 Column)"
    boxText1:SetFont(cache:GetResource("Font", "Fonts/BlueHighway.sdf"), 24)

    local boxTextNode2 = scene_:CreateChild("BoxText2")
    boxTextNode2.position = Vector3(-6.0, 2.0, 0.0)
    local boxText2 = boxTextNode2:CreateComponent("Text3D")
    boxText2.text = "Face Camera Trail (1 Column)"
    boxText2:SetFont(cache:GetResource("Font", "Fonts/BlueHighway.sdf"), 24)

    local ninjaTextNode2 = scene_:CreateChild("NinjaText")
    ninjaTextNode2.position = Vector3(4.0, 2.5, 0.0)
    local ninjaText = ninjaTextNode2:CreateComponent("Text3D")
    ninjaText.text = "Bone Trail (4 Column)"
    ninjaText:SetFont(cache:GetResource("Font", "Fonts/BlueHighway.sdf"), 24)

    -- Create the camera.
    cameraNode = scene_:CreateChild("Camera")
    cameraNode:CreateComponent("Camera")

    -- Set an initial position for the camera scene node above the plane
    cameraNode.position = Vector3(0.0, 2.0, -14.0)
end

function CreateInstructions()
    -- Construct new Text object, set string to display and font to use
    local instructionText = ui.root:CreateChild("Text")
    instructionText:SetText("Use WASD keys and mouse to move")
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
    local MOVE_SPEED = 20.0
    -- Mouse sensitivity as degrees per pixel
    local MOUSE_SENSITIVITY = 0.1

    -- Use this frame's mouse motion to adjust camera node yaw and pitch. Clamp the pitch between -90 and 90 degrees
    local mouseMove = input.mouseMove
    yaw = yaw +MOUSE_SENSITIVITY * mouseMove.x
    pitch = pitch + MOUSE_SENSITIVITY * mouseMove.y
    pitch = Clamp(pitch, -90.0, 90.0)

    -- Construct new orientation for the camera scene node from yaw and pitch. Roll is fixed to zero
    cameraNode.rotation = Quaternion(pitch, yaw, 0.0)

    -- Read WASD keys and move the camera scene node to the corresponding direction if they are pressed
    -- Use the Translate() function (default local space) to move relative to the node's orientation.
    if input:GetKeyDown(KEY_W) then
        cameraNode:Translate(Vector3(0.0, 0.0, 1.0) * MOVE_SPEED * timeStep)
    end
    if input:GetKeyDown(KEY_S) then
        cameraNode:Translate(Vector3(0.0, 0.0, -1.0) * MOVE_SPEED * timeStep)
    end
    if input:GetKeyDown(KEY_A) then
        cameraNode:Translate(Vector3(-1.0, 0.0, 0.0) * MOVE_SPEED * timeStep)
    end
    if input:GetKeyDown(KEY_D) then
        cameraNode:Translate(Vector3(1.0, 0.0, 0.0) * MOVE_SPEED * timeStep)
    end
end

function SubscribeToEvents()
    -- Subscribe HandleUpdate() function for processing update events
    SubscribeToEvent("Update", "HandleUpdate")
end

function HandleUpdate(eventType, eventData)
    -- Take the frame time step, which is stored as a float
    local timeStep = eventData["TimeStep"]:GetFloat()

    -- Move the camera, scale movement with time step
    MoveCamera(timeStep)

    -- Sum of timesteps.
    timeStepSum = timeStepSum + timeStep

    -- Move first box with pattern.
    boxNode1:SetTransform(Vector3(-4.0 + 3.0 * Cos(100.0 * timeStepSum), 0.5, -2.0 * Cos(400.0 * timeStepSum)), Quaternion())

    -- Move second box with pattern.
    boxNode2:SetTransform(Vector3(0.0 + 3.0 * Cos(100.0 * timeStepSum), 0.5, -2.0 * Cos(400.0 * timeStepSum)), Quaternion())

    -- Get elapsed attack animation time.
    local swordAnimTime = ninjaAnimCtrl:GetAnimationState("Models/NinjaSnowWar/Ninja_Attack3.ani").time

    -- Stop emitting trail when sword is finished slashing.
    if not swordTrail.emitting and swordAnimTime > swordTrailStartTime and swordAnimTime < swordTrailEndTime then
        swordTrail.emitting = true
    elseif swordTrail.emitting and swordAnimTime >= swordTrailEndTime then
        swordTrail.emitting = false
    end
end
