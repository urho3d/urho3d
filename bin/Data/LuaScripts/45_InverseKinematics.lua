-- Ribbon trail demo.
-- This sample demonstrates how to use both trail types of RibbonTrail component.

require "LuaScripts/Utilities/Sample"

local jackAnimCtrl_
local cameraRotateNode_
local floorNode_
local leftFoot_
local rightFoot_
local leftEffector_
local rightEffector_
local solver_
local floorPitch_ = 0.0
local floorRoll_ = 0.0
local drawDebug_ = false

function Start()
    cache.autoReloadResources = true

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
    scene_:CreateComponent("DebugRenderer")
    scene_:CreateComponent("PhysicsWorld")

    -- Create scene node & StaticModel component for showing a static plane
    floorNode_ = scene_:CreateChild("Plane")
    floorNode_.scale = Vector3(50.0, 1.0, 50.0)
    local planeObject = floorNode_:CreateComponent("StaticModel")
    planeObject.model = cache:GetResource("Model", "Models/Plane.mdl")
    planeObject.material = cache:GetResource("Material", "Materials/StoneTiled.xml")

    -- Set up collision, we need to raycast to determine foot height
    floorNode_:CreateComponent("RigidBody")
    local col = floorNode_:CreateComponent("CollisionShape")
    col:SetBox(Vector3(1, 0, 1))

    -- Create a directional light to the world.
    local lightNode = scene_:CreateChild("DirectionalLight")
    lightNode.direction = Vector3(0.6, -1.0, 0.8) -- The direction vector does not need to be normalized
    local light = lightNode:CreateComponent("Light")
    light.lightType = LIGHT_DIRECTIONAL
    light.castShadows = true
    light.shadowBias = BiasParameters(0.00005, 0.5)
    -- Set cascade splits at 10, 50 and 200 world units, fade shadows out at 80% of maximum shadow distance
    light.shadowCascade = CascadeParameters(10.0, 50.0, 200.0, 0.0, 0.8)

    -- Load Jack animated model
    jackNode_ = scene_:CreateChild("Jack")
    jackNode_.rotation = Quaternion(0.0, 270.0, 0.0)
    jack = jackNode_:CreateComponent("AnimatedModel")
    jack.model = cache:GetResource("Model", "Models/Jack.mdl")
    jack.material = cache:GetResource("Material", "Materials/Jack.xml")
    jack.castShadows = true

    -- Create animation controller and play walk animation
    jackAnimCtrl_ = jackNode_:CreateComponent("AnimationController")
    jackAnimCtrl_:PlayExclusive("Models/Jack_Walk.ani", 0, true, 0.0)

    -- We need to attach two inverse kinematic effectors to Jack's feet to
    -- control the grounding.
    leftFoot_  = jackNode_:GetChild("Bip01_L_Foot", true);
    rightFoot_ = jackNode_:GetChild("Bip01_R_Foot", true);

    -- NOTE: Crashes here for some reason
    leftEffector_  = leftFoot_:CreateComponent("IKEffector")

    --rightEffector_ = rightFoot_:CreateComponent("IKEffector")
    -- Control 2 segments up to the hips
    --leftEffector_.chainLength = 2;
    --rightEffector_.chainLength = 2;

    -- For the effectors to work, an IKSolver needs to be attached to one of
    -- the parent nodes. Typically, you want to place the solver as close as
    -- possible to the effectors for optimal performance. Since in this case
    -- we're solving the legs only, we can place the solver at the spine.
    --local spine = jackNode_:GetChild("Bip01_Spine", true);
    --solver_ = spine:CreateComponent("IKSolver");

    -- Disable auto-solving, which means we can call Solve() manually.
    --solver_.autoSolve = false;

    -- When this is enabled, the solver will use the current positions of the
    -- nodes in the skeleton as its basis every frame. If you disable this, then
    -- the solver will store the initial positions of the nodes once and always
    -- use those positions for calculating solutions.
    -- With animated characters you generally want to continuously update the
    -- initial positions.
    --solver_.updatePose = true;

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

function UpdateCameraAndFloor(timeStep)
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
    UpdateCameraAndFloor(timeStep)
end
