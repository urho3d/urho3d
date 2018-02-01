-- Ribbon trail demo.
-- This sample demonstrates how to adjust the position of animated feet so they match the ground's angle using IK.

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
    leftFoot_  = jackNode_:GetChild("Bip01_L_Foot", true)
    rightFoot_ = jackNode_:GetChild("Bip01_R_Foot", true)
    leftEffector_  = leftFoot_:CreateComponent("IKEffector")
    rightEffector_ = rightFoot_:CreateComponent("IKEffector")
    -- Control 2 segments up to the hips
    leftEffector_.chainLength = 2
    rightEffector_.chainLength = 2

    -- For the effectors to work, an IKSolver needs to be attached to one of
    -- the parent nodes. Typically, you want to place the solver as close as
    -- possible to the effectors for optimal performance. Since in this case
    -- we're solving the legs only, we can place the solver at the spine.
    local spine = jackNode_:GetChild("Bip01_Spine", true)
    solver_ = spine:CreateComponent("IKSolver")

    -- Two-bone solver is more efficient and more stable than FABRIK (but only
    -- works for two bones, obviously).
    solver_.algorithm = IKSolver.TWO_BONE

    -- Disable auto-solving, which means we can call Solve() manually.
    solver_.AUTO_SOLVE = false

    -- Only enable this so the debug draw shows us the pose before solving.
    -- This should NOT be enabled for any other reason (it does nothing and is
    -- a waste of performance).
    solver_.UPDATE_ORIGINAL_POSE = true

    -- Create the camera.
    cameraRotateNode_ = scene_:CreateChild("CameraRotate")
    cameraNode = cameraRotateNode_:CreateChild("Camera")
    cameraNode:CreateComponent("Camera")

    -- Set an initial position for the camera scene node above the plane
    cameraNode.position = Vector3(0.0, 0.0, -4.0)
    cameraRotateNode_.position = Vector3(0.0, 0.4, 0.0)
    pitch = 20.0
    yaw = 50.0
end

function CreateInstructions()
    -- Construct new Text object, set string to display and font to use
    local instructionText = ui.root:CreateChild("Text")
    instructionText:SetText("Left-Click and drag to look around\nRight-Click and drag to change incline\nPress space to reset floor\nPress D to draw debug geometry")
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

    -- Mouse sensitivity as degrees per pixel
    local MOUSE_SENSITIVITY = 0.1

    -- Use this frame's mouse motion to adjust camera node yaw and pitch. Clamp the pitch between -90 and 90 degrees
    if input:GetMouseButtonDown(MOUSEB_LEFT) then
        local mouseMove = input.mouseMove
        yaw = yaw +MOUSE_SENSITIVITY * mouseMove.x
        pitch = pitch + MOUSE_SENSITIVITY * mouseMove.y
        pitch = Clamp(pitch, -90.0, 90.0)
    end

    if input:GetMouseButtonDown(MOUSEB_RIGHT) then
        local mouseMoveInt = input.mouseMove
        local mouseMove = Vector2()
        mouseMove.x = -Cos(yaw) * mouseMoveInt.y - Sin(yaw) * mouseMoveInt.x
        mouseMove.y = Sin(yaw) * mouseMoveInt.y - Cos(yaw) * mouseMoveInt.x

        floorPitch_ = floorPitch_ + MOUSE_SENSITIVITY * mouseMove.x
        floorPitch_ = Clamp(floorPitch_, -90.0, 90.0)
        floorRoll_ = floorRoll_ + MOUSE_SENSITIVITY * mouseMove.y
    end

    if input:GetKeyPress(KEY_SPACE) then
        floorPitch_ = 0.0
        floorRoll_ = 0.0
    end

    if input:GetKeyPress(KEY_D) then
        drawDebug_ = not drawDebug_
    end

    -- Construct new orientation for the camera scene node from yaw and pitch. Roll is fixed to zero
    cameraRotateNode_.rotation = Quaternion(pitch, yaw, 0.0)
    floorNode_.rotation = Quaternion(floorPitch_, 0.0, floorRoll_)
end

function SubscribeToEvents()
    -- Subscribe HandleUpdate() function for processing update events
    SubscribeToEvent("Update", "HandleUpdate")
    SubscribeToEvent("PostRenderUpdate", "HandlePostRenderUpdate")
    SubscribeToEvent("SceneDrawableUpdateFinished", "HandleSceneDrawableUpdateFinished")
end

function HandleUpdate(eventType, eventData)
    -- Take the frame time step, which is stored as a float
    local timeStep = eventData["TimeStep"]:GetFloat()

    -- Move the camera, scale movement with time step
    UpdateCameraAndFloor(timeStep)
end

function HandlePostRenderUpdate(eventType, eventData)
    if drawDebug_ then
        solver_:DrawDebugGeometry(false)
    end
end

function HandleSceneDrawableUpdateFinished(eventType, eventData)
    local physicsWorld = scene_:GetComponent("PhysicsWorld")
    local leftFootPosition = leftFoot_.worldPosition
    local rightFootPosition = rightFoot_.worldPosition

    -- Cast ray down to get the normal of the underlying surface
    local result = physicsWorld:RaycastSingle(Ray(leftFootPosition + Vector3(0, 1, 0), Vector3(0, -1, 0)), 2)
    if result.body then
        -- Cast again, but this time along the normal. Set the target position
        -- to the ray intersection
        local oppositeNormal = result.normal * -1
        result = physicsWorld:RaycastSingle(Ray(leftFootPosition + result.normal, oppositeNormal), 2)
        -- The foot node has an offset relative to the root node
        footOffset = leftFoot_.worldPosition.y - jackNode_.worldPosition.y
        leftEffector_.targetPosition = result.position + result.normal * footOffset
        -- Rotate foot according to normal
        leftFoot_:Rotate(Quaternion(Vector3(0, 1, 0), result.normal), TS_WORLD)
    end

    -- Same deal with the right foot
    result = physicsWorld:RaycastSingle(Ray(rightFootPosition + Vector3(0, 1, 0), Vector3(0, -1, 0)), 2)
    if result.body then
        local oppositeNormal = result.normal * -1
        result = physicsWorld:RaycastSingle(Ray(rightFootPosition + result.normal, oppositeNormal), 2)
        footOffset = rightFoot_.worldPosition.y - jackNode_.worldPosition.y
        rightEffector_.targetPosition = result.position + result.normal * footOffset
        rightFoot_:Rotate(Quaternion(Vector3(0, 1, 0), result.normal), TS_WORLD)
    end

    solver_:Solve()
end
