-- Ragdoll example.
-- This sample demonstrates:
--     - Detecting physics collisions
--     - Moving an AnimatedModel's bones with physics and connecting them with constraints
--     - Using rolling friction to stop rolling objects from moving infinitely

require "LuaScripts/Utilities/Sample"

function Start()
    -- Execute the common startup for samples
    SampleStart()

    -- Create the scene content
    CreateScene()

    -- Create the UI content
    CreateInstructions()

    -- Setup the viewport for displaying the scene
    SetupViewport()

    -- Hook up to the frame update and render post-update events
    SubscribeToEvents()
end

function CreateScene()
    scene_ = Scene()

    -- Create octree, use default volume (-1000, -1000, -1000) to (1000, 1000, 1000)
    -- Create a physics simulation world with default parameters, which will update at 60fps. Like the Octree must
    -- exist before creating drawable components, the PhysicsWorld must exist before creating physics components.
    -- Finally, create a DebugRenderer component so that we can draw physics debug geometry
    scene_:CreateComponent("Octree")
    scene_:CreateComponent("PhysicsWorld")
    scene_:CreateComponent("DebugRenderer")

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

    -- Create a floor object, 500 x 500 world units. Adjust position so that the ground is at zero Y
    local floorNode = scene_:CreateChild("Floor")
    floorNode.position = Vector3(0.0, -0.5, 0.0)
    floorNode.scale = Vector3(500.0, 1.0, 500.0)
    local floorObject = floorNode:CreateComponent("StaticModel")
    floorObject.model = cache:GetResource("Model", "Models/Box.mdl")
    floorObject.material = cache:GetResource("Material", "Materials/StoneTiled.xml")

    -- Make the floor physical by adding RigidBody and CollisionShape components
    local body = floorNode:CreateComponent("RigidBody")
    -- We will be spawning spherical objects in this sample. The ground also needs non-zero rolling friction so that
    -- the spheres will eventually come to rest
    body.rollingFriction = 0.15
    local shape = floorNode:CreateComponent("CollisionShape")
    -- Set a box shape of size 1 x 1 x 1 for collision. The shape will be scaled with the scene node scale, so the
    -- rendering and physics representation sizes should match (the box model is also 1 x 1 x 1.)
    shape:SetBox(Vector3(1.0, 1.0, 1.0))

    -- Create animated models
    for z = -1, 1 do
        for x = -4, 4 do
            local modelNode = scene_:CreateChild("Jack")
            modelNode.position = Vector3(x * 5.0, 0.0, z * 5.0)
            modelNode.rotation = Quaternion(0.0, 180.0, 0.0)
            local modelObject = modelNode:CreateComponent("AnimatedModel")
            modelObject.model = cache:GetResource("Model", "Models/Jack.mdl")
            modelObject.material = cache:GetResource("Material", "Materials/Jack.xml")
            modelObject.castShadows = true
            -- Set the model to also update when invisible to avoid staying invisible when the model should come into
            -- view, but does not as the bounding box is not updated
            modelObject.updateInvisible = true

            -- Create a rigid body and a collision shape. These will act as a trigger for transforming the
            -- model into a ragdoll when hit by a moving object
            local body = modelNode:CreateComponent("RigidBody")
            -- The trigger mode makes the rigid body only detect collisions, but impart no forces on the
            -- colliding objects
            body.trigger = true
            local shape = modelNode:CreateComponent("CollisionShape")
            -- Create the capsule shape with an offset so that it is correctly aligned with the model, which
            -- has its origin at the feet
            shape:SetCapsule(0.7, 2.0, Vector3(0.0, 1.0, 0.0))

            -- Create a custom script object that reacts to collisions and creates the ragdoll
            modelNode:CreateScriptObject("CreateRagdoll")
        end
    end

    -- Create the camera. Limit far clip distance to match the fog. Note: now we actually create the camera node outside
    -- the scene, because we want it to be unaffected by scene load / save
    cameraNode = Node()
    local camera = cameraNode:CreateComponent("Camera")
    camera.farClip = 300.0

    -- Set an initial position for the camera scene node above the floor
    cameraNode.position = Vector3(0.0, 5.0, -20.0)
end

function CreateInstructions()
    -- Construct new Text object, set string to display and font to use
    local instructionText = ui.root:CreateChild("Text")
    instructionText:SetText(
        "Use WASD keys and mouse to move\n"..
        "LMB to spawn physics objects\n"..
        "F5 to save scene, F7 to load\n"..
        "Space to toggle physics debug geometry")
    instructionText:SetFont(cache:GetResource("Font", "Fonts/Anonymous Pro.ttf"), 15)
    -- The text has multiple rows. Center them in relation to each other
    instructionText.textAlignment = HA_CENTER

    -- Position the text relative to the screen center
    instructionText.horizontalAlignment = HA_CENTER
    instructionText.verticalAlignment = VA_CENTER
    instructionText:SetPosition(0, ui.root.height / 4)
end

function SetupViewport()
    -- Set up a viewport to the Renderer subsystem so that the 3D scene can be seen
    local viewport = Viewport:new(scene_, cameraNode:GetComponent("Camera"))
    renderer:SetViewport(0, viewport)
end

function SubscribeToEvents()
    -- Subscribe HandleUpdate() function for processing update events
    SubscribeToEvent("Update", "HandleUpdate")

    -- Subscribe HandlePostRenderUpdate() function for processing the post-render update event, during which we request
    -- debug geometry
    SubscribeToEvent("PostRenderUpdate", "HandlePostRenderUpdate")
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
    yaw = yaw + MOUSE_SENSITIVITY * mouseMove.x
    pitch = pitch  +MOUSE_SENSITIVITY * mouseMove.y
    pitch = Clamp(pitch, -90.0, 90.0)

    -- Construct new orientation for the camera scene node from yaw and pitch. Roll is fixed to zero
    cameraNode.rotation = Quaternion(pitch, yaw, 0.0)

    -- Read WASD keys and move the camera scene node to the corresponding direction if they are pressed
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

    -- "Shoot" a physics object with left mousebutton
    if input:GetMouseButtonPress(MOUSEB_LEFT) then
        SpawnObject()
    end

    -- Check for loading/saving the scene. Save the scene to the file Data/Scenes/Physics.xml relative to the executable
    -- directory
    if input:GetKeyPress(KEY_F5) then
        scene_:SaveXML(fileSystem:GetProgramDir().."Data/Scenes/Ragdolls.xml")
    end
    if input:GetKeyPress(KEY_F7) then
        scene_:LoadXML(fileSystem:GetProgramDir().."Data/Scenes/Ragdolls.xml")
    end

    -- Toggle debug geometry with space
    if input:GetKeyPress(KEY_SPACE) then
        drawDebug = not drawDebug
    end
end

function SpawnObject()
    local boxNode = scene_:CreateChild("Sphere")
    boxNode.position = cameraNode.position
    boxNode.rotation = cameraNode.rotation
    boxNode:SetScale(0.25)
    local boxObject = boxNode:CreateComponent("StaticModel")
    boxObject.model = cache:GetResource("Model", "Models/Sphere.mdl")
    boxObject.material = cache:GetResource("Material", "Materials/StoneSmall.xml")
    boxObject.castShadows = true

    local body = boxNode:CreateComponent("RigidBody")
    body.mass = 1.0
    body.rollingFriction = 0.15
    local shape = boxNode:CreateComponent("CollisionShape")
    shape:SetSphere(1.0)

    local OBJECT_VELOCITY = 10.0

    -- Set initial velocity for the RigidBody based on camera forward vector. Add also a slight up component
    -- to overcome gravity better
    body.linearVelocity = cameraNode.rotation * Vector3(0.0, 0.25, 1.0) * OBJECT_VELOCITY
end

function HandleUpdate(eventType, eventData)
    -- Take the frame time step, which is stored as a float
    local timeStep = eventData:GetFloat("TimeStep")

    -- Move the camera, scale movement with time step
    MoveCamera(timeStep)
end

function HandlePostRenderUpdate(eventType, eventData)
    -- If draw debug mode is enabled, draw physics debug geometry. Use depth test to make the result easier to interpret
    if drawDebug then
        scene_:GetComponent("PhysicsWorld"):DrawDebugGeometry(true)
    end
end

-- CreateRagdoll script object class
CreateRagdoll = ScriptObject()

function CreateRagdoll:Start()
    -- Subscribe physics collisions that concern this scene node
    self:SubscribeToEvent(self.node, "NodeCollision", "CreateRagdoll:HandleNodeCollision")
end

function CreateRagdoll:HandleNodeCollision(eventType, eventData)
    -- Get the other colliding body, make sure it is moving (has nonzero mass)
    local otherBody = eventData:GetPtr("RigidBody", "OtherBody")

    if otherBody.mass > 0.0 then
        -- We do not need the physics components in the AnimatedModel's root scene node anymore
        self.node:RemoveComponent("RigidBody")
        self.node:RemoveComponent("CollisionShape")

        -- Create RigidBody & CollisionShape components to bones
        self:CreateRagdollBone("Bip01_Pelvis", SHAPE_BOX, Vector3(0.3, 0.2, 0.25), Vector3(0.0, 0.0, 0.0),
            Quaternion(0.0, 0.0, 0.0))
        self:CreateRagdollBone("Bip01_Spine1", SHAPE_BOX, Vector3(0.35, 0.2, 0.3), Vector3(0.15, 0.0, 0.0),
            Quaternion(0.0, 0.0, 0.0))
        self:CreateRagdollBone("Bip01_L_Thigh", SHAPE_CAPSULE, Vector3(0.175, 0.45, 0.175), Vector3(0.25, 0.0, 0.0),
            Quaternion(0.0, 0.0, 90.0))
        self:CreateRagdollBone("Bip01_R_Thigh", SHAPE_CAPSULE, Vector3(0.175, 0.45, 0.175), Vector3(0.25, 0.0, 0.0),
            Quaternion(0.0, 0.0, 90.0))
        self:CreateRagdollBone("Bip01_L_Calf", SHAPE_CAPSULE, Vector3(0.15, 0.55, 0.15), Vector3(0.25, 0.0, 0.0),
            Quaternion(0.0, 0.0, 90.0))
        self:CreateRagdollBone("Bip01_R_Calf", SHAPE_CAPSULE, Vector3(0.15, 0.55, 0.15), Vector3(0.25, 0.0, 0.0),
            Quaternion(0.0, 0.0, 90.0))
        self:CreateRagdollBone("Bip01_Head", SHAPE_BOX, Vector3(0.2, 0.2, 0.2), Vector3(0.1, 0.0, 0.0),
            Quaternion(0.0, 0.0, 0.0))
        self:CreateRagdollBone("Bip01_L_UpperArm", SHAPE_CAPSULE, Vector3(0.15, 0.35, 0.15), Vector3(0.1, 0.0, 0.0),
            Quaternion(0.0, 0.0, 90.0))
        self:CreateRagdollBone("Bip01_R_UpperArm", SHAPE_CAPSULE, Vector3(0.15, 0.35, 0.15), Vector3(0.1, 0.0, 0.0),
            Quaternion(0.0, 0.0, 90.0))
        self:CreateRagdollBone("Bip01_L_Forearm", SHAPE_CAPSULE, Vector3(0.125, 0.4, 0.125), Vector3(0.2, 0.0, 0.0),
            Quaternion(0.0, 0.0, 90.0))
        self:CreateRagdollBone("Bip01_R_Forearm", SHAPE_CAPSULE, Vector3(0.125, 0.4, 0.125), Vector3(0.2, 0.0, 0.0),
            Quaternion(0.0, 0.0, 90.0))

        -- Create Constraints between bones
        self:CreateRagdollConstraint("Bip01_L_Thigh", "Bip01_Pelvis", CONSTRAINT_CONETWIST, Vector3(0.0, 0.0, -1.0),
            Vector3(0.0, 0.0, 1.0), Vector2(45.0, 45.0), Vector2(0.0, 0.0), true)
        self:CreateRagdollConstraint("Bip01_R_Thigh", "Bip01_Pelvis", CONSTRAINT_CONETWIST, Vector3(0.0, 0.0, -1.0),
            Vector3(0.0, 0.0, 1.0), Vector2(45.0, 45.0), Vector2(0.0, 0.0), true)
        self:CreateRagdollConstraint("Bip01_L_Calf", "Bip01_L_Thigh", CONSTRAINT_HINGE, Vector3(0.0, 0.0, -1.0),
            Vector3(0.0, 0.0, -1.0), Vector2(90.0, 0.0), Vector2(0.0, 0.0), true)
        self:CreateRagdollConstraint("Bip01_R_Calf", "Bip01_R_Thigh", CONSTRAINT_HINGE, Vector3(0.0, 0.0, -1.0),
            Vector3(0.0, 0.0, -1.0), Vector2(90.0, 0.0), Vector2(0.0, 0.0), true)
        self:CreateRagdollConstraint("Bip01_Spine1", "Bip01_Pelvis", CONSTRAINT_HINGE, Vector3(0.0, 0.0, 1.0),
            Vector3(0.0, 0.0, 1.0), Vector2(45.0, 0.0), Vector2(-10.0, 0.0), true)
        self:CreateRagdollConstraint("Bip01_Head", "Bip01_Spine1", CONSTRAINT_CONETWIST, Vector3(-1.0, 0.0, 0.0),
            Vector3(-1.0, 0.0, 0.0), Vector2(0.0, 30.0), Vector2(0.0, 0.0), true)
        self:CreateRagdollConstraint("Bip01_L_UpperArm", "Bip01_Spine1", CONSTRAINT_CONETWIST, Vector3(0.0, -1.0, 0.0),
            Vector3(0.0, 1.0, 0.0), Vector2(45.0, 45.0), Vector2(0.0, 0.0), false)
        self:CreateRagdollConstraint("Bip01_R_UpperArm", "Bip01_Spine1", CONSTRAINT_CONETWIST, Vector3(0.0, -1.0, 0.0),
            Vector3(0.0, 1.0, 0.0), Vector2(45.0, 45.0), Vector2(0.0, 0.0), false)
        self:CreateRagdollConstraint("Bip01_L_Forearm", "Bip01_L_UpperArm", CONSTRAINT_HINGE, Vector3(0.0, 0.0, -1.0),
            Vector3(0.0, 0.0, -1.0), Vector2(90.0, 0.0), Vector2(0.0, 0.0), true)
        self:CreateRagdollConstraint("Bip01_R_Forearm", "Bip01_R_UpperArm", CONSTRAINT_HINGE, Vector3(0.0, 0.0, -1.0),
            Vector3(0.0, 0.0, -1.0), Vector2(90.0, 0.0), Vector2(0.0, 0.0), true)

        -- Disable keyframe animation from all bones so that they will not interfere with the ragdoll
        local model = self.node:GetComponent("AnimatedModel")
        local skeleton = model.skeleton
        for i = 0, skeleton.numBones - 1 do
            skeleton:GetBone(i).animated = false
        end

        -- Finally remove self (the ScriptInstance which holds this script object) from the scene node. Note that this must
        -- be the last operation performed in the function
        self.instance:Remove()
    end
end

function CreateRagdoll:CreateRagdollBone(boneName, type, size, position, rotation)
    -- Find the correct child scene node recursively
    local boneNode = self.node:GetChild(boneName, true)
    if boneNode == nil then
        print("Could not find bone " .. boneName .. " for creating ragdoll physics components\n")
        return
    end

    local body = boneNode:CreateComponent("RigidBody")
    -- Set mass to make movable
    body.mass = 1.0
    -- Set damping parameters to smooth out the motion
    body.linearDamping = 0.05
    body.angularDamping = 0.85
    -- Set rest thresholds to ensure the ragdoll rigid bodies come to rest to not consume CPU endlessly
    body.linearRestThreshold = 1.5
    body.angularRestThreshold = 2.5

    local shape = boneNode:CreateComponent("CollisionShape")
    -- We use either a box or a capsule shape for all of the bones
    if type == SHAPE_BOX then
        shape:SetBox(size, position, rotation)
    else
        shape:SetCapsule(size.x, size.y, position, rotation)
    end
end

function CreateRagdoll:CreateRagdollConstraint(boneName, parentName, type, axis, parentAxis, highLimit, lowLimit, disableCollision)
    local boneNode = self.node:GetChild(boneName, true)
    local parentNode = self.node:GetChild(parentName, true)
    if boneNode == nil then
        print("Could not find bone " .. boneName .. " for creating ragdoll constraint\n")
        return
    end
    if parentNode == nil then
        print("Could not find bone " .. parentName .. " for creating ragdoll constraint\n")
        return
    end

    local constraint = boneNode:CreateComponent("Constraint")
    constraint.constraintType = type
    -- Most of the constraints in the ragdoll will work better when the connected bodies don't collide against each other
    constraint.disableCollision = disableCollision
    -- The connected body must be specified before setting the world position
    constraint.otherBody = parentNode:GetComponent("RigidBody")
    -- Position the constraint at the child bone we are connecting
    constraint.worldPosition = boneNode.worldPosition
    -- Configure axes and limits
    constraint.axis = axis
    constraint.otherAxis = parentAxis
    constraint.highLimit = highLimit
    constraint.lowLimit = lowLimit
end

-- Create XML patch instructions for screen joystick layout specific to this sample app
function GetScreenJoystickPatchString()
    return
        "<patch>" ..
        "    <remove sel=\"/element/element[./attribute[@name='Name' and @value='Button0']]/attribute[@name='Is Visible']\" />" ..
        "    <replace sel=\"/element/element[./attribute[@name='Name' and @value='Button0']]/element[./attribute[@name='Name' and @value='Label']]/attribute[@name='Text']/@value\">Spawn</replace>" ..
        "    <add sel=\"/element/element[./attribute[@name='Name' and @value='Button0']]\">" ..
        "        <element type=\"Text\">" ..
        "            <attribute name=\"Name\" value=\"MouseButtonBinding\" />" ..
        "            <attribute name=\"Text\" value=\"LEFT\" />" ..
        "        </element>" ..
        "    </add>" ..
        "    <remove sel=\"/element/element[./attribute[@name='Name' and @value='Button1']]/attribute[@name='Is Visible']\" />" ..
        "    <replace sel=\"/element/element[./attribute[@name='Name' and @value='Button1']]/element[./attribute[@name='Name' and @value='Label']]/attribute[@name='Text']/@value\">Debug</replace>" ..
        "    <add sel=\"/element/element[./attribute[@name='Name' and @value='Button1']]\">" ..
        "        <element type=\"Text\">" ..
        "            <attribute name=\"Name\" value=\"KeyBinding\" />" ..
        "            <attribute name=\"Text\" value=\"SPACE\" />" ..
        "        </element>" ..
        "    </add>" ..
        "</patch>"
end
