-- Moving character example.
-- This sample demonstrates:
--     - Controlling a humanoid character through physics
--     - Driving animations using the AnimationController component
--     - Manual control of a bone scene node
--     - Implementing 1st and 3rd person cameras, using raycasts to avoid the 3rd person camera clipping into scenery
--     - Saving and loading the variables of a script object
--     - Using touch inputs/gyroscope for iOS/Android (implemented through an external file)

require "LuaScripts/Utilities/Sample"
require "LuaScripts/Utilities/Touch"

-- Variables used by external file are made global in order to be accessed

CTRL_FORWARD = 1
CTRL_BACK = 2
CTRL_LEFT = 4
CTRL_RIGHT = 8
local CTRL_JUMP = 16

local MOVE_FORCE = 0.8
local INAIR_MOVE_FORCE = 0.02
local BRAKE_FORCE = 0.2
local JUMP_FORCE = 7.0
local YAW_SENSITIVITY = 0.1
local INAIR_THRESHOLD_TIME = 0.1
firstPerson = false -- First person camera flag

local characterNode = nil

function Start()
    -- Execute the common startup for samples
    SampleStart()

    -- Create static scene content
    CreateScene()

    -- Create the controllable character
    CreateCharacter()

    -- Create the UI content
    CreateInstructions()

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
    camera.farClip = 300.0
    renderer:SetViewport(0, Viewport:new(scene_, camera))

    -- Create a Zone component for ambient lighting & fog control
    local zoneNode = scene_:CreateChild("Zone")
    local zone = zoneNode:CreateComponent("Zone")
    zone.boundingBox = BoundingBox(-1000.0, 1000.0)
    zone.ambientColor = Color(0.15, 0.15, 0.15)
    zone.fogColor = Color(0.5, 0.5, 0.7)
    zone.fogStart = 100.0
    zone.fogEnd = 300.0

    -- Create a directional light to the world. Enable cascaded shadows on it
    local lightNode = scene_:CreateChild("DirectionalLight")
    lightNode.direction = Vector3(0.6, -1.0, 0.8)
    local light = lightNode:CreateComponent("Light")
    light.lightType = LIGHT_DIRECTIONAL
    light.castShadows = true
    light.shadowBias = BiasParameters(0.00025, 0.5)
    -- Set cascade splits at 10, 50 and 200 world units, fade shadows out at 80% of maximum shadow distance
    light.shadowCascade = CascadeParameters(10.0, 50.0, 200.0, 0.0, 0.8)

    -- Create the floor object
    local floorNode = scene_:CreateChild("Floor")
    floorNode.position = Vector3(0.0, -0.5, 0.0)
    floorNode.scale = Vector3(200.0, 1.0, 200.0)
    local object = floorNode:CreateComponent("StaticModel")
    object.model = cache:GetResource("Model", "Models/Box.mdl")
    object.material = cache:GetResource("Material", "Materials/Stone.xml")

    local body = floorNode:CreateComponent("RigidBody")
    -- Use collision layer bit 2 to mark world scenery. This is what we will raycast against to prevent camera from going
    -- inside geometry
    body.collisionLayer = 2
    local shape = floorNode:CreateComponent("CollisionShape")
    shape:SetBox(Vector3(1.0, 1.0, 1.0))

    -- Create mushrooms of varying sizes
    local NUM_MUSHROOMS = 60
    for i = 1, NUM_MUSHROOMS do
        local objectNode = scene_:CreateChild("Mushroom")
        objectNode.position = Vector3(Random(180.0) - 90.0, 0.0, Random(180.0) - 90.0)
        objectNode.rotation = Quaternion(0.0, Random(360.0), 0.0)
        objectNode:SetScale(2.0 + Random(5.0))
        local object = objectNode:CreateComponent("StaticModel")
        object.model = cache:GetResource("Model", "Models/Mushroom.mdl")
        object.material = cache:GetResource("Material", "Materials/Mushroom.xml")
        object.castShadows = true

        local body = objectNode:CreateComponent("RigidBody")
        body.collisionLayer = 2
        local shape = objectNode:CreateComponent("CollisionShape")
        shape:SetTriangleMesh(object.model, 0)
    end

    -- Create movable boxes. Let them fall from the sky at first
    local NUM_BOXES = 100
    for i = 1, NUM_BOXES do
        local scale = Random(2.0) + 0.5

        local objectNode = scene_:CreateChild("Box")
        objectNode.position = Vector3(Random(180.0) - 90.0, Random(10.0) + 10.0, Random(180.0) - 90.0)
        objectNode.rotation = Quaternion(Random(360.0), Random(360.0), Random(360.0))
        objectNode:SetScale(scale)
        local object = objectNode:CreateComponent("StaticModel")
        object.model = cache:GetResource("Model", "Models/Box.mdl")
        object.material = cache:GetResource("Material", "Materials/Stone.xml")
        object.castShadows = true

        local body = objectNode:CreateComponent("RigidBody")
        body.collisionLayer = 2
        -- Bigger boxes will be heavier and harder to move
        body.mass = scale * 2.0
        local shape = objectNode:CreateComponent("CollisionShape")
        shape:SetBox(Vector3(1.0, 1.0, 1.0))
    end
end

function CreateCharacter()
    characterNode = scene_:CreateChild("Jack")
    characterNode.position = Vector3(0.0, 1.0, 0.0)

    -- Create the rendering component + animation controller
    local object = characterNode:CreateComponent("AnimatedModel")
    object.model = cache:GetResource("Model", "Models/Jack.mdl")
    object.material = cache:GetResource("Material", "Materials/Jack.xml")
    object.castShadows = true
    characterNode:CreateComponent("AnimationController")

    -- Set the head bone for manual control
    object.skeleton:GetBone("Bip01_Head").animated = false

    -- Create rigidbody, and set non-zero mass so that the body becomes dynamic
    local body = characterNode:CreateComponent("RigidBody")
    body.collisionLayer = 1
    body.mass = 1.0

    -- Set zero angular factor so that physics doesn't turn the character on its own.
    -- Instead we will control the character yaw manually
    body.angularFactor = Vector3(0.0, 0.0, 0.0)

    -- Set the rigidbody to signal collision also when in rest, so that we get ground collisions properly
    body.collisionEventMode = COLLISION_ALWAYS

    -- Set a capsule shape for collision
    local shape = characterNode:CreateComponent("CollisionShape")
    shape:SetCapsule(0.7, 1.8, Vector3(0.0, 0.9, 0.0))

    -- Create the character logic object, which takes care of steering the rigidbody
    characterNode:CreateScriptObject("Character")
end

function CreateInstructions()
    -- Construct new Text object, set string to display and font to use
    local instructionText = ui.root:CreateChild("Text")
    instructionText:SetText(
        "Use WASD keys and mouse to move\n"..
        "Space to jump, F to toggle 1st/3rd person\n"..
        "F5 to save scene, F7 to load")
    instructionText:SetFont(cache:GetResource("Font", "Fonts/Anonymous Pro.ttf"), 15)
    -- The text has multiple rows. Center them in relation to each other
    instructionText.textAlignment = HA_CENTER

    -- Position the text relative to the screen center
    instructionText.horizontalAlignment = HA_CENTER
    instructionText.verticalAlignment = VA_CENTER
    instructionText:SetPosition(0, ui.root.height / 4)
end

function SubscribeToEvents()
    -- Subscribe to Update event for setting the character controls before physics simulation
    SubscribeToEvent("Update", "HandleUpdate")

    -- Subscribe to PostUpdate event for updating the camera position after physics simulation
    SubscribeToEvent("PostUpdate", "HandlePostUpdate")

    -- Unsubscribe the SceneUpdate event from base class as the camera node is being controlled in HandlePostUpdate() in this sample
    UnsubscribeFromEvent("SceneUpdate")
end

function HandleUpdate(eventType, eventData)
    if characterNode == nil then
        return
    end

    local character = characterNode:GetScriptObject()
    if character == nil then
        return
    end

    -- Clear previous controls
    character.controls:Set(CTRL_FORWARD + CTRL_BACK + CTRL_LEFT + CTRL_RIGHT + CTRL_JUMP, false)

    -- Update controls using touch utility
    if touchEnabled then UpdateTouches(character.controls) end

    -- Update controls using keys
    if ui.focusElement == nil then
        if not touchEnabled or not useGyroscope then
            if input:GetKeyDown(KEY_W) then character.controls:Set(CTRL_FORWARD, true) end
            if input:GetKeyDown(KEY_S) then character.controls:Set(CTRL_BACK, true) end
            if input:GetKeyDown(KEY_A) then character.controls:Set(CTRL_LEFT, true) end
            if input:GetKeyDown(KEY_D) then character.controls:Set(CTRL_RIGHT, true) end
        end
        if input:GetKeyDown(KEY_SPACE) then character.controls:Set(CTRL_JUMP, true) end

        -- Add character yaw & pitch from the mouse motion or touch input
        if touchEnabled then
            for i=0, input.numTouches - 1 do
                local state = input:GetTouch(i)
                if not state.touchedElement then -- Touch on empty space
                    local camera = cameraNode:GetComponent("Camera")
                    if not camera then return end

                    character.controls.yaw = character.controls.yaw + TOUCH_SENSITIVITY * camera.fov / graphics.height * state.delta.x
                    character.controls.pitch = character.controls.pitch + TOUCH_SENSITIVITY * camera.fov / graphics.height * state.delta.y
                end
            end
        else
            character.controls.yaw = character.controls.yaw + input.mouseMoveX * YAW_SENSITIVITY
            character.controls.pitch = character.controls.pitch + input.mouseMoveY * YAW_SENSITIVITY
        end
        -- Limit pitch
        character.controls.pitch = Clamp(character.controls.pitch, -80.0, 80.0)
        -- Set rotation already here so that it's updated every rendering frame instead of every physics frame
        characterNode.rotation = Quaternion(character.controls.yaw, Vector3(0.0, 1.0, 0.0))

        -- Switch between 1st and 3rd person
        if input:GetKeyPress(KEY_F) then
            firstPerson = not firstPerson
        end

        -- Turn on/off gyroscope on mobile platform
        if input:GetKeyPress(KEY_G) then
            useGyroscope = not useGyroscope
        end

        -- Check for loading / saving the scene
        if input:GetKeyPress(KEY_F5) then
            scene_:SaveXML(fileSystem:GetProgramDir().."Data/Scenes/CharacterDemo.xml")
        end
        if input:GetKeyPress(KEY_F7) then
            scene_:LoadXML(fileSystem:GetProgramDir().."Data/Scenes/CharacterDemo.xml")
            -- After loading we have to reacquire the character scene node, as it has been recreated
            -- Simply find by name as there's only one of them
            characterNode = scene_:GetChild("Jack", true)
            if characterNode == nil then
                return
            end
        end
    end
end

function HandlePostUpdate(eventType, eventData)
    if characterNode == nil then
        return
    end

    local character = characterNode:GetScriptObject()
    if character == nil then
        return
    end

    -- Get camera lookat dir from character yaw + pitch
    local rot = characterNode.rotation
    local dir = rot * Quaternion(character.controls.pitch, Vector3(1.0, 0.0, 0.0))

    -- Turn head to camera pitch, but limit to avoid unnatural animation
    local headNode = characterNode:GetChild("Bip01_Head", true)
    local limitPitch = Clamp(character.controls.pitch, -45.0, 45.0)
    local headDir = rot * Quaternion(limitPitch, Vector3(1.0, 0.0, 0.0))
    -- This could be expanded to look at an arbitrary target, now just look at a point in front
    local headWorldTarget = headNode.worldPosition + headDir * Vector3(0.0, 0.0, 1.0)
    headNode:LookAt(headWorldTarget, Vector3(0.0, 1.0, 0.0))
    -- Correct head orientation because LookAt assumes Z = forward, but the bone has been authored differently (Y = forward)
    headNode:Rotate(Quaternion(0.0, 90.0, 90.0))

    if firstPerson then
        -- First person camera: position to the head bone + offset slightly forward & up
        cameraNode.position = headNode.worldPosition + rot * Vector3(0.0, 0.15, 0.2)
        cameraNode.rotation = dir
    else
        -- Third person camera: position behind the character
        local aimPoint = characterNode.position + rot * Vector3(0.0, 1.7, 0.0) -- You can modify x Vector3 value to translate the fixed character position (indicative range[-2;2])

        -- Collide camera ray with static physics objects (layer bitmask 2) to ensure we see the character properly
        local rayDir = dir * Vector3(0.0, 0.0, -1.0) -- For indoor scenes you can use dir * Vector3(0.0, 0.0, -0.5) to prevent camera from crossing the walls
        local rayDistance = cameraDistance
        local result = scene_:GetComponent("PhysicsWorld"):RaycastSingle(Ray(aimPoint, rayDir), rayDistance, 2)
        if result.body ~= nil then
            rayDistance = Min(rayDistance, result.distance)
        end
        rayDistance = Clamp(rayDistance, CAMERA_MIN_DIST, cameraDistance)

        cameraNode.position = aimPoint + rayDir * rayDistance
        cameraNode.rotation = dir
    end
end

-- Character script object class
Character = ScriptObject()

function Character:Start()
    -- Character controls.
    self.controls = Controls()
    -- Grounded flag for movement.
    self.onGround = false
    -- Jump flag.
    self.okToJump = true
    -- In air timer. Due to possible physics inaccuracy, character can be off ground for max. 1/10 second and still be allowed to move.
    self.inAirTimer = 0.0

    self:SubscribeToEvent(self.node, "NodeCollision", "Character:HandleNodeCollision")
end

function Character:Load(deserializer)
    self.controls.yaw = deserializer:ReadFloat()
    self.controls.pitch = deserializer:ReadFloat()
end

function Character:Save(serializer)
    serializer:WriteFloat(self.controls.yaw)
    serializer:WriteFloat(self.controls.pitch)
end

function Character:HandleNodeCollision(eventType, eventData)
    local contacts = eventData["Contacts"]:GetBuffer()

    while not contacts.eof do
        local contactPosition = contacts:ReadVector3()
        local contactNormal = contacts:ReadVector3()
        local contactDistance = contacts:ReadFloat()
        local contactImpulse = contacts:ReadFloat()

        -- If contact is below node center and mostly vertical, assume it's a ground contact
        if contactPosition.y < self.node.position.y + 1.0 then
            local level = Abs(contactNormal.y)
            if level > 0.75 then
                self.onGround = true
            end
        end
    end
end

function Character:FixedUpdate(timeStep)
    -- Could cache the components for faster access instead of finding them each frame
    local body = self.node:GetComponent("RigidBody")
    local animCtrl = self.node:GetComponent("AnimationController")

    -- Update the in air timer. Reset if grounded
    if not self.onGround then
        self.inAirTimer = self.inAirTimer + timeStep
    else
        self.inAirTimer = 0.0
    end
    -- When character has been in air less than 1/10 second, it's still interpreted as being on ground
    local softGrounded = self.inAirTimer < INAIR_THRESHOLD_TIME

    -- Update movement & animation
    local rot = self.node.rotation
    local moveDir = Vector3(0.0, 0.0, 0.0)
    local velocity = body.linearVelocity
    -- Velocity on the XZ plane
    local planeVelocity = Vector3(velocity.x, 0.0, velocity.z)

    if self.controls:IsDown(CTRL_FORWARD) then
        moveDir = moveDir + Vector3(0.0, 0.0, 1.0)
    end
    if self.controls:IsDown(CTRL_BACK) then
        moveDir = moveDir + Vector3(0.0, 0.0, -1.0)
    end
    if self.controls:IsDown(CTRL_LEFT) then
        moveDir = moveDir + Vector3(-1.0, 0.0, 0.0)
    end
    if self.controls:IsDown(CTRL_RIGHT) then
        moveDir = moveDir + Vector3(1.0, 0.0, 0.0)
    end

    -- Normalize move vector so that diagonal strafing is not faster
    if moveDir:LengthSquared() > 0.0 then
        moveDir:Normalize()
    end

    -- If in air, allow control, but slower than when on ground
    if softGrounded then
        body:ApplyImpulse(rot * moveDir * MOVE_FORCE)
    else
        body:ApplyImpulse(rot * moveDir * INAIR_MOVE_FORCE)
    end

    if softGrounded then
        -- When on ground, apply a braking force to limit maximum ground velocity
        local brakeForce = planeVelocity * -BRAKE_FORCE
        body:ApplyImpulse(brakeForce)

        -- Jump. Must release jump control inbetween jumps
        if self.controls:IsDown(CTRL_JUMP) then
            if self.okToJump then
                body:ApplyImpulse(Vector3(0.0, 1.0, 0.0) * JUMP_FORCE)
                self.okToJump = false
            end
        else
            self.okToJump = true
        end
    end

    -- Play walk animation if moving on ground, otherwise fade it out
    if softGrounded and not moveDir:Equals(Vector3(0.0, 0.0, 0.0)) then
        animCtrl:PlayExclusive("Models/Jack_Walk.ani", 0, true, 0.2)
    else
        animCtrl:Stop("Models/Jack_Walk.ani", 0.2)
    end
    -- Set walk animation speed proportional to velocity
    animCtrl:SetSpeed("Models/Jack_Walk.ani", planeVelocity:Length() * 0.3)

    -- Reset grounded flag for next frame
    self.onGround = false
end

-- Create XML patch instructions for screen joystick layout specific to this sample app
function GetScreenJoystickPatchString()
    return
        "<patch>" ..
        "    <add sel=\"/element\">" ..
        "        <element type=\"Button\">" ..
        "            <attribute name=\"Name\" value=\"Button3\" />" ..
        "            <attribute name=\"Position\" value=\"-120 -120\" />" ..
        "            <attribute name=\"Size\" value=\"96 96\" />" ..
        "            <attribute name=\"Horiz Alignment\" value=\"Right\" />" ..
        "            <attribute name=\"Vert Alignment\" value=\"Bottom\" />" ..
        "            <attribute name=\"Texture\" value=\"Texture2D;Textures/TouchInput.png\" />" ..
        "            <attribute name=\"Image Rect\" value=\"96 0 192 96\" />" ..
        "            <attribute name=\"Hover Image Offset\" value=\"0 0\" />" ..
        "            <attribute name=\"Pressed Image Offset\" value=\"0 0\" />" ..
        "            <element type=\"Text\">" ..
        "                <attribute name=\"Name\" value=\"Label\" />" ..
        "                <attribute name=\"Horiz Alignment\" value=\"Center\" />" ..
        "                <attribute name=\"Vert Alignment\" value=\"Center\" />" ..
        "                <attribute name=\"Color\" value=\"0 0 0 1\" />" ..
        "                <attribute name=\"Text\" value=\"Gyroscope\" />" ..
        "            </element>" ..
        "            <element type=\"Text\">" ..
        "                <attribute name=\"Name\" value=\"KeyBinding\" />" ..
        "                <attribute name=\"Text\" value=\"G\" />" ..
        "            </element>" ..
        "        </element>" ..
        "    </add>" ..
        "    <remove sel=\"/element/element[./attribute[@name='Name' and @value='Button0']]/attribute[@name='Is Visible']\" />" ..
        "    <replace sel=\"/element/element[./attribute[@name='Name' and @value='Button0']]/element[./attribute[@name='Name' and @value='Label']]/attribute[@name='Text']/@value\">1st/3rd</replace>" ..
        "    <add sel=\"/element/element[./attribute[@name='Name' and @value='Button0']]\">" ..
        "        <element type=\"Text\">" ..
        "            <attribute name=\"Name\" value=\"KeyBinding\" />" ..
        "            <attribute name=\"Text\" value=\"F\" />" ..
        "        </element>" ..
        "    </add>" ..
        "    <remove sel=\"/element/element[./attribute[@name='Name' and @value='Button1']]/attribute[@name='Is Visible']\" />" ..
        "    <replace sel=\"/element/element[./attribute[@name='Name' and @value='Button1']]/element[./attribute[@name='Name' and @value='Label']]/attribute[@name='Text']/@value\">Jump</replace>" ..
        "    <add sel=\"/element/element[./attribute[@name='Name' and @value='Button1']]\">" ..
        "        <element type=\"Text\">" ..
        "            <attribute name=\"Name\" value=\"KeyBinding\" />" ..
        "            <attribute name=\"Text\" value=\"SPACE\" />" ..
        "        </element>" ..
        "    </add>" ..
        "</patch>"
end
