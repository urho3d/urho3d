-- Vehicle example.
-- This sample demonstrates:
--     - Creating a heightmap terrain with collision
--     - Constructing a physical vehicle with rigid bodies for the hull and the wheels, joined with constraints
--     - Saving and loading the variables of a script object, including node & component references

require "LuaScripts/Utilities/Sample"

local CTRL_FORWARD = 1
local CTRL_BACK = 2
local CTRL_LEFT = 4
local CTRL_RIGHT = 8

local CAMERA_DISTANCE = 10.0
local YAW_SENSITIVITY = 0.1
local ENGINE_POWER = 10.0
local DOWN_FORCE = 10.0
local MAX_WHEEL_ANGLE = 22.5

local vehicleNode = nil

function Start()
    -- Execute the common startup for samples
    SampleStart()

    -- Create static scene content
    CreateScene()

    -- Create the controllable vehicle
    CreateVehicle()

    -- Create the UI content
    CreateInstructions()

    -- Set the mouse mode to use in the sample
    SampleInitMouseMode(MM_RELATIVE)

    -- Subscribe to necessary events
    SubscribeToEvents()
end

function CreateScene()
    scene_ = Scene()

    -- Create scene subsystem components
    scene_:CreateComponent("Octree")
    scene_:CreateComponent("PhysicsWorld")

    -- Create camera and define viewport. Camera does not necessarily have to belong to the scene
    cameraNode = Node()
    local camera = cameraNode:CreateComponent("Camera")
    camera.farClip = 500.0

    renderer:SetViewport(0, Viewport:new(scene_, camera))

    -- Create static scene content. First create a zone for ambient lighting and fog control
    local zoneNode = scene_:CreateChild("Zone")
    local zone = zoneNode:CreateComponent("Zone")
    zone.ambientColor = Color(0.15, 0.15, 0.15)
    zone.fogColor = Color(0.5, 0.5, 0.7)
    zone.fogStart = 300.0
    zone.fogEnd = 500.0
    zone.boundingBox = BoundingBox(-2000.0, 2000.0)

    -- Create a directional light to the world. Enable cascaded shadows on it
    local lightNode = scene_:CreateChild("DirectionalLight")
    lightNode.direction = Vector3(0.3, -0.5, 0.425)
    local light = lightNode:CreateComponent("Light")
    light.lightType = LIGHT_DIRECTIONAL
    light.castShadows = true
    light.shadowBias = BiasParameters(0.00025, 0.5)
    light.shadowCascade = CascadeParameters(10.0, 50.0, 200.0, 0.0, 0.8)
    light.specularIntensity = 0.5

    -- Create heightmap terrain with collision
    local terrainNode = scene_:CreateChild("Terrain")
    terrainNode.position = Vector3(0.0, 0.0, 0.0)
    local terrain = terrainNode:CreateComponent("Terrain")
    terrain.patchSize = 64
    terrain.spacing = Vector3(2.0, 0.1, 2.0) -- Spacing between vertices and vertical resolution of the height map
    terrain.smoothing = true
    terrain.heightMap = cache:GetResource("Image", "Textures/HeightMap.png")
    terrain.material = cache:GetResource("Material", "Materials/Terrain.xml")
    -- The terrain consists of large triangles, which fits well for occlusion rendering, as a hill can occlude all
    -- terrain patches and other objects behind it
    terrain.occluder = true

    local body = terrainNode:CreateComponent("RigidBody")
    body.collisionLayer = 2 -- Use layer bitmask 2 for static geometry
    local shape = terrainNode:CreateComponent("CollisionShape")
    shape:SetTerrain()

    -- Create 1000 mushrooms in the terrain. Always face outward along the terrain normal
    local NUM_MUSHROOMS = 1000
    for i = 1, NUM_MUSHROOMS do
        local objectNode = scene_:CreateChild("Mushroom")
        local position = Vector3(Random(2000.0) - 1000.0, 0.0, Random(2000.0) - 1000.0)
        position.y = terrain:GetHeight(position) - 0.1
        objectNode.position = position
        -- Create a rotation quaternion from up vector to terrain normal
        objectNode.rotation = Quaternion(Vector3(0.0, 1.0, 0.0), terrain:GetNormal(position))
        objectNode:SetScale(3.0)
        local object = objectNode:CreateComponent("StaticModel")
        object.model = cache:GetResource("Model", "Models/Mushroom.mdl")
        object.material = cache:GetResource("Material", "Materials/Mushroom.xml")
        object.castShadows = true

        local body = objectNode:CreateComponent("RigidBody")
        body.collisionLayer = 2
        local shape = objectNode:CreateComponent("CollisionShape")
        shape:SetTriangleMesh(object.model, 0)
    end
end

function CreateVehicle()
    vehicleNode = scene_:CreateChild("Vehicle")
    vehicleNode.position = Vector3(0.0, 5.0, 0.0)

    -- Create the vehicle logic script object
    local vehicle = vehicleNode:CreateScriptObject("Vehicle")
    -- Create the rendering and physics components
    vehicle:Init()
end

function CreateInstructions()
    -- Construct new Text object, set string to display and font to use
    local instructionText = ui.root:CreateChild("Text")
    instructionText.text = "Use WASD keys to drive, mouse/touch to rotate camera\n"..
        "F5 to save scene, F7 to load"
    instructionText:SetFont(cache:GetResource("Font", "Fonts/Anonymous Pro.ttf"), 15)
    -- The text has multiple rows. Center them in relation to each other
    instructionText.textAlignment = HA_CENTER

    -- Position the text relative to the screen center
    instructionText.horizontalAlignment = HA_CENTER
    instructionText.verticalAlignment = VA_CENTER
    instructionText:SetPosition(0, ui.root.height / 4)
end

function SubscribeToEvents()
    -- Subscribe to Update event for setting the vehicle controls before physics simulation
    SubscribeToEvent("Update", "HandleUpdate")

    -- Subscribe to PostUpdate event for updating the camera position after physics simulation
    SubscribeToEvent("PostUpdate", "HandlePostUpdate")

    -- Unsubscribe the SceneUpdate event from base class as the camera node is being controlled in HandlePostUpdate() in this sample
    UnsubscribeFromEvent("SceneUpdate")
end

function HandleUpdate(eventType, eventData)
    if vehicleNode == nil then
        return
    end

    local vehicle = vehicleNode:GetScriptObject()
    if vehicle == nil then
        return
    end

    -- Get movement controls and assign them to the vehicle component. If UI has a focused element, clear controls
    if ui.focusElement == nil then
        vehicle.controls:Set(CTRL_FORWARD, input:GetKeyDown(KEY_W))
        vehicle.controls:Set(CTRL_BACK, input:GetKeyDown(KEY_S))
        vehicle.controls:Set(CTRL_LEFT, input:GetKeyDown(KEY_A))
        vehicle.controls:Set(CTRL_RIGHT, input:GetKeyDown(KEY_D))

        -- Add yaw & pitch from the mouse motion or touch input. Used only for the camera, does not affect motion
        if touchEnabled then
            for i=0, input.numTouches - 1 do
                local state = input:GetTouch(i)
                if not state.touchedElement then -- Touch on empty space
                    local camera = cameraNode:GetComponent("Camera")
                    if not camera then return end

                    vehicle.controls.yaw = vehicle.controls.yaw + TOUCH_SENSITIVITY * camera.fov / graphics.height * state.delta.x
                    vehicle.controls.pitch = vehicle.controls.pitch + TOUCH_SENSITIVITY * camera.fov / graphics.height * state.delta.y
                end
            end
        else
            vehicle.controls.yaw = vehicle.controls.yaw + input.mouseMoveX * YAW_SENSITIVITY
            vehicle.controls.pitch = vehicle.controls.pitch + input.mouseMoveY * YAW_SENSITIVITY
        end
        -- Limit pitch
        vehicle.controls.pitch = Clamp(vehicle.controls.pitch, 0.0, 80.0)

        -- Check for loading / saving the scene
        if input:GetKeyPress(KEY_F5) then
            scene_:SaveXML(fileSystem:GetProgramDir() .. "Data/Scenes/VehicleDemo.xml")
        end
        if input:GetKeyPress(KEY_F7) then
            scene_:LoadXML(fileSystem:GetProgramDir() .. "Data/Scenes/VehicleDemo.xml")
            -- After loading we have to reacquire the vehicle scene node, as it has been recreated
            -- Simply find by name as there's only one of them
            vehicleNode = scene_:GetChild("Vehicle", true)
            vehicleNode:GetScriptObject():PostInit()
        end
    else
        vehicle.controls:Set(CTRL_FORWARD + CTRL_BACK + CTRL_LEFT + CTRL_RIGHT, false)
    end
end

function HandlePostUpdate(eventType, eventData)
    if vehicleNode == nil then
        return
    end

    local vehicle = vehicleNode:GetScriptObject()
    if vehicle == nil then
        return
    end

    -- Physics update has completed. Position camera behind vehicle
    local dir = Quaternion(vehicleNode.rotation:YawAngle(), Vector3(0.0, 1.0, 0.0))
    dir = dir * Quaternion(vehicle.controls.yaw, Vector3(0.0, 1.0, 0.0))
    dir = dir * Quaternion(vehicle.controls.pitch, Vector3(1.0, 0.0, 0.0))

    local cameraTargetPos = vehicleNode.position - dir * Vector3(0.0, 0.0, CAMERA_DISTANCE)
    local cameraStartPos = vehicleNode.position
    -- Raycast camera against static objects (physics collision mask 2)
    -- and move it closer to the vehicle if something in between
    local cameraRay = Ray(cameraStartPos, (cameraTargetPos - cameraStartPos):Normalized())
    local cameraRayLength = (cameraTargetPos - cameraStartPos):Length();
    local physicsWorld = scene_:GetComponent("PhysicsWorld")
    local result = physicsWorld:RaycastSingle(cameraRay, cameraRayLength, 2)
    if result.body ~= nil then
        cameraTargetPos = cameraStartPos + cameraRay.direction * (result.distance - 0.5)
    end
    cameraNode.position = cameraTargetPos
    cameraNode.rotation = dir
end

-- Vehicle script object class
--
-- When saving, the node and component handles are automatically converted into nodeID or componentID attributes
-- and are acquired from the scene when loading. The steering member variable will likewise be saved automatically.
-- The Controls object can not be automatically saved, so handle it manually in the Load() and Save() methods

Vehicle = ScriptObject()

function Vehicle:Start()
    -- Current left/right steering amount (-1 to 1.)
    self.steering = 0.0
    -- Vehicle controls.
    self.controls = Controls()
end

function Vehicle:Load(deserializer)
    self.controls.yaw = deserializer:ReadFloat()
    self.controls.pitch = deserializer:ReadFloat()
end

function Vehicle:Save(serializer)
    serializer:WriteFloat(self.controls.yaw)
    serializer:WriteFloat(self.controls.pitch)
end

function Vehicle:Init()
    -- This function is called only from the main program when initially creating the vehicle, not on scene load
    local node = self.node
    local hullObject = node:CreateComponent("StaticModel")
    self.hullBody = node:CreateComponent("RigidBody")
    local hullShape = node:CreateComponent("CollisionShape")

    node.scale = Vector3(1.5, 1.0, 3.0)
    hullObject.model = cache:GetResource("Model", "Models/Box.mdl")
    hullObject.material = cache:GetResource("Material", "Materials/Stone.xml")
    hullObject.castShadows = true
    hullShape:SetBox(Vector3(1.0, 1.0, 1.0))

    self.hullBody.mass = 4.0
    self.hullBody.linearDamping = 0.2 -- Some air resistance
    self.hullBody.angularDamping = 0.5
    self.hullBody.collisionLayer = 1
    self.frontLeft = self:InitWheel("FrontLeft", Vector3(-0.6, -0.4, 0.3))
    self.frontRight = self:InitWheel("FrontRight", Vector3(0.6, -0.4, 0.3))
    self.rearLeft = self:InitWheel("RearLeft", Vector3(-0.6, -0.4, -0.3))
    self.rearRight = self:InitWheel("RearRight", Vector3(0.6, -0.4, -0.3))

    self:PostInit()
end

function Vehicle:PostInit()
    self.frontLeft = scene_:GetChild("FrontLeft")
    self.frontRight = scene_:GetChild("FrontRight")
    self.rearLeft = scene_:GetChild("RearLeft")
    self.rearRight = scene_:GetChild("RearRight")

    self.frontLeftAxis = self.frontLeft:GetComponent("Constraint")
    self.frontRightAxis = self.frontRight:GetComponent("Constraint")

    self.hullBody = self.node:GetComponent("RigidBody")

    self.frontLeftBody = self.frontLeft:GetComponent("RigidBody")
    self.frontRightBody = self.frontRight:GetComponent("RigidBody")
    self.rearLeftBody = self.rearLeft:GetComponent("RigidBody")
    self.rearRightBody = self.rearRight:GetComponent("RigidBody")
end

function Vehicle:InitWheel(name, offset)
    -- Note: do not parent the wheel to the hull scene node. Instead create it on the root level and let the physics
    -- constraint keep it together
    local wheelNode = scene_:CreateChild(name)
    local node = self.node
    wheelNode.position = node:LocalToWorld(offset)
    if offset.x >= 0.0 then
        wheelNode.rotation = node.worldRotation * Quaternion(0.0, 0.0, -90.0)
    else
        wheelNode.rotation = node.worldRotation * Quaternion(0.0, 0.0, 90.0)
    end
    wheelNode.scale = Vector3(0.8, 0.5, 0.8)

    local wheelObject = wheelNode:CreateComponent("StaticModel")
    local wheelBody = wheelNode:CreateComponent("RigidBody")
    local wheelShape = wheelNode:CreateComponent("CollisionShape")
    local wheelConstraint = wheelNode:CreateComponent("Constraint")

    wheelObject.model = cache:GetResource("Model", "Models/Cylinder.mdl")
    wheelObject.material = cache:GetResource("Material", "Materials/Stone.xml")
    wheelObject.castShadows = true
    wheelShape:SetSphere(1.0)
    wheelBody.friction = 1
    wheelBody.mass = 1
    wheelBody.linearDamping = 0.2 -- Some air resistance
    wheelBody.angularDamping = 0.75 -- Could also use rolling friction
    wheelBody.collisionLayer = 1
    wheelConstraint.constraintType = CONSTRAINT_HINGE
    wheelConstraint.otherBody = node:GetComponent("RigidBody")
    wheelConstraint.worldPosition = wheelNode.worldPosition -- Set constraint's both ends at wheel's location
    wheelConstraint.axis = Vector3(0.0, 1.0, 0.0) -- Wheel rotates around its local Y-axis

    if offset.x >= 0.0 then -- Wheel's hull axis points either left or right
        wheelConstraint.otherAxis = Vector3(1.0, 0.0, 0.0)
    else
        wheelConstraint.otherAxis = Vector3(-1.0, 0.0, 0.0)
    end

    wheelConstraint.lowLimit = Vector2(-180.0, 0.0) -- Let the wheel rotate freely around the axis
    wheelConstraint.highLimit = Vector2(180.0, 0.0)
    wheelConstraint.disableCollision = true -- Let the wheel intersect the vehicle hull

    return wheelNode
end

function Vehicle:FixedUpdate(timeStep)
    local newSteering = 0.0
    local accelerator = 0.0

    if self.controls:IsDown(CTRL_LEFT) then
        newSteering = -1.0
    end
    if self.controls:IsDown(CTRL_RIGHT) then
        newSteering = 1.0
    end
    if self.controls:IsDown(CTRL_FORWARD) then
        accelerator = 1.0
    end
    if self.controls:IsDown(CTRL_BACK) then
        accelerator = -0.5
    end

    -- When steering, wake up the wheel rigidbodies so that their orientation is updated
    if newSteering ~= 0.0 then
        self.frontLeftBody:Activate()
        self.frontRightBody:Activate()
        self.steering = self.steering * 0.95 + newSteering * 0.05
    else
        self.steering = self.steering * 0.8 + newSteering * 0.2
    end

    local steeringRot = Quaternion(0.0, self.steering * MAX_WHEEL_ANGLE, 0.0)
    self.frontLeftAxis.otherAxis = steeringRot * Vector3(-1.0, 0.0, 0.0)
    self.frontRightAxis.otherAxis = steeringRot * Vector3(1.0, 0.0, 0.0)

    if accelerator ~= 0.0 then
        -- Torques are applied in world space, so need to take the vehicle & wheel rotation into account
        local torqueVec = Vector3(ENGINE_POWER * accelerator, 0.0, 0.0)
        local node = self.node
        self.frontLeftBody:ApplyTorque(node.rotation * steeringRot * torqueVec)
        self.frontRightBody:ApplyTorque(node.rotation * steeringRot * torqueVec)
        self.rearLeftBody:ApplyTorque(node.rotation * torqueVec)
        self.rearRightBody:ApplyTorque(node.rotation * torqueVec)
    end

    -- Apply downforce proportional to velocity
    local localVelocity = self.hullBody.rotation:Inverse() * self.hullBody.linearVelocity
    self.hullBody:ApplyForce(self.hullBody.rotation * Vector3(0.0, -1.0, 0.0) * Abs(localVelocity.z) * DOWN_FORCE)
end
