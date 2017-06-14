-- Urho2D physics Constraints sample.
-- This sample is designed to help understanding and chosing the right constraint.
-- This sample demonstrates:
--      - Creating physics constraints
--      - Creating Edge and Polygon Shapes from vertices
--      - Displaying physics debug geometry and constraints' joints
--      - Using SetOrderInLayer to alter the way sprites are drawn in relation to each other
--      - Using Text3D to display some text affected by zoom
--      - Setting the background color for the scene

require "LuaScripts/Utilities/Sample"

local camera = nil
local physicsWorld = nil
local pickedNode = nil
local dummyBody = nil

function Start()
    SampleStart()
    CreateScene()
    input.mouseVisible = true -- Show mouse cursor
    CreateInstructions()
    -- Set the mouse mode to use in the sample
    SampleInitMouseMode(MM_FREE)
    SubscribeToEvents()
end

function CreateScene()
    scene_ = Scene()
    scene_:CreateComponent("Octree")
    scene_:CreateComponent("DebugRenderer")
    physicsWorld = scene_:CreateComponent("PhysicsWorld2D")
    physicsWorld.drawJoint = true -- Display the joints (Note that DrawDebugGeometry() must be set to true to acually draw the joints)
    drawDebug = true -- Set DrawDebugGeometry() to true

    -- Create camera
    cameraNode = scene_:CreateChild("Camera")
    cameraNode.position = Vector3(0, 0, 0) -- Note that Z setting is discarded; use camera.zoom instead (see MoveCamera() below for example)
    camera = cameraNode:CreateComponent("Camera")
    camera.orthographic = true
    camera.orthoSize = graphics.height * PIXEL_SIZE
    camera.zoom = 1.2 * Min(graphics.width / 1280, graphics.height / 800) -- Set zoom according to user's resolution to ensure full visibility (initial zoom (1.2) is set for full visibility at 1280x800 resolution)
    renderer:SetViewport(0, Viewport:new(scene_, camera))
    renderer.defaultZone.fogColor = Color(0.1, 0.1, 0.1) -- Set background color for the scene

    -- Create a 4x3 grid
    for i=0, 4 do
        local edgeNode = scene_:CreateChild("VerticalEdge")
        local edgeBody = edgeNode:CreateComponent("RigidBody2D")
        if dummyBody == nil then dummyBody = edgeBody end -- Mark first edge as dummy body (used by mouse pick)
        local edgeShape = edgeNode:CreateComponent("CollisionEdge2D")
        edgeShape:SetVertices(Vector2(i*2.5 -5, -3), Vector2(i*2.5 -5, 3))
        edgeShape.friction = 0.5 -- Set friction
    end

    for j=0, 3 do
        local edgeNode = scene_:CreateChild("HorizontalEdge")
        local edgeBody = edgeNode:CreateComponent("RigidBody2D")
        local edgeShape = edgeNode:CreateComponent("CollisionEdge2D")
        edgeShape:SetVertices(Vector2(-5, j*2 -3), Vector2(5, j*2 -3))
        edgeShape.friction = 0.5 -- Set friction
    end

    -- Create a box (will be cloned later)
    local box  = scene_:CreateChild("Box")
    box.position = Vector3(0.8, -2, 0)
    local staticSprite = box:CreateComponent("StaticSprite2D")
    staticSprite.sprite = cache:GetResource("Sprite2D", "Urho2D/Box.png")
    local body = box:CreateComponent("RigidBody2D")
    body.bodyType = BT_DYNAMIC
    body.linearDamping = 0
    body.angularDamping  = 0
    local shape = box:CreateComponent("CollisionBox2D") -- Create box shape
    shape.size = Vector2(0.32, 0.32) -- Set size
    shape.density = 1 -- Set shape density (kilograms per meter squared)
    shape.friction = 0.5 -- Set friction
    shape.restitution = 0.1 -- Set restitution (slight bounce)

    -- Create a ball (will be cloned later)
    local ball  = scene_:CreateChild("Ball")
    ball.position = Vector3(1.8, -2, 0)
    local staticSprite = ball:CreateComponent("StaticSprite2D")
    staticSprite.sprite = cache:GetResource("Sprite2D", "Urho2D/Ball.png")
    local body = ball:CreateComponent("RigidBody2D")
    body.bodyType = BT_DYNAMIC
    body.linearDamping = 0
    body.angularDamping  = 0
    local shape = ball:CreateComponent("CollisionCircle2D") -- Create circle shape
    shape.radius = 0.16 -- Set radius
    shape.density = 1 -- Set shape density (kilograms per meter squared)
    shape.friction = 0.5 -- Set friction
    shape.restitution = 0.6 -- Set restitution: make it bounce

    -- Create a polygon
    local node = scene_:CreateChild("Polygon")
    node.position = Vector3(1.6, -2, 0)
    node:SetScale(0.7)
    local staticSprite = node:CreateComponent("StaticSprite2D")
    staticSprite.sprite = cache:GetResource("Sprite2D", "Urho2D/Aster.png")
    local body = node:CreateComponent("RigidBody2D")
    body.bodyType = BT_DYNAMIC
    local shape = node:CreateComponent("CollisionPolygon2D")
    shape:SetVertices{Vector2(-0.8, -0.3), Vector2(0.5, -0.8), Vector2(0.8, -0.3), Vector2(0.8, 0.5), Vector2(0.5, 0.9), Vector2(-0.5, 0.7)}
    shape.density = 1 -- Set shape density (kilograms per meter squared)
    shape.friction = 0.3 -- Set friction
    shape.restitution = 0 -- Set restitution (no bounce)

    -- Create a ConstraintDistance2D
    CreateFlag("ConstraintDistance2D", -4.97, 3) -- Display Text3D flag
    local boxNode = box:Clone()
    local ballNode = ball:Clone()
    local ballBody = ballNode:GetComponent("RigidBody2D")
    boxNode.position = Vector3(-4.5, 2, 0)
    ballNode.position = Vector3(-3, 2, 0)

    local constraintDistance = boxNode:CreateComponent("ConstraintDistance2D") -- Apply ConstraintDistance2D to box
    constraintDistance.otherBody = ballBody -- Constrain ball to box
    constraintDistance.ownerBodyAnchor = boxNode.position2D
    constraintDistance.otherBodyAnchor = ballNode.position2D
    -- Make the constraint soft (comment to make it rigid, which is its basic behavior)
    constraintDistance.frequencyHz = 4
    constraintDistance.dampingRatio = 0.5

    -- Create a ConstraintFriction2D ********** Not functional. From Box2d samples it seems that 2 anchors are required, Urho2D only provides 1, needs investigation ***********
    CreateFlag("ConstraintFriction2D", 0.03, 1) -- Display Text3D flag
    local boxNode = box:Clone()
    local ballNode = ball:Clone()
    boxNode.position = Vector3(0.5, 0, 0)
    ballNode.position = Vector3(1.5, 0, 0)

    local constraintFriction = boxNode:CreateComponent("ConstraintFriction2D") -- Apply ConstraintDistance2D to box
    constraintFriction.otherBody = ballNode:GetComponent("RigidBody2D") -- Constraint ball to box
    constraintFriction.ownerBodyAnchor = boxNode.position2D
    --constraintFriction.otherBodyAnchor = ballNode.position2D
    --constraintFriction.maxForce = 10 -- ballBody.mass * gravity
    --constraintDistance.maxTorque = 10 -- ballBody.mass * radius * gravity

    -- Create a ConstraintGear2D
    CreateFlag("ConstraintGear2D", -4.97, -1) -- Display Text3D flag
    local baseNode = box:Clone()
    baseNode:GetComponent("RigidBody2D").bodyType = BT_STATIC
    baseNode.position = Vector3(-3.7, -2.5, 0)
    local ball1Node = ball:Clone()
    ball1Node.position = Vector3(-4.5, -2, 0)
    local ball1Body = ball1Node:GetComponent("RigidBody2D")
    local ball2Node = ball:Clone()
    ball2Node.position = Vector3(-3, -2, 0)
    local ball2Body = ball2Node:GetComponent("RigidBody2D")

    local gear1 = baseNode:CreateComponent("ConstraintRevolute2D") -- Apply constraint to baseBox
    gear1.otherBody = ball1Body -- Constrain ball1 to baseBox
    gear1.anchor = ball1Node.position2D
    local gear2 = baseNode:CreateComponent("ConstraintRevolute2D") -- Apply constraint to baseBox
    gear2.otherBody = ball2Body -- Constrain ball2 to baseBox
    gear2.anchor = ball2Node.position2D

    local constraintGear = ball1Node:CreateComponent("ConstraintGear2D") -- Apply constraint to ball1
    constraintGear.otherBody = ball2Body -- Constrain ball2 to ball1
    constraintGear.ownerConstraint = gear1
    constraintGear.otherConstraint = gear2
    constraintGear.ratio=1

    ball1Body:ApplyAngularImpulse(0.015, true) -- Animate

    -- Create a vehicle from a compound of 2 ConstraintWheel2Ds
    CreateFlag("ConstraintWheel2Ds compound", -2.45, -1) -- Display Text3D flag
    local car = box:Clone()
    car.scale = Vector3(4, 1, 0)
    car.position = Vector3(-1.2, -2.3, 0)
    car:GetComponent("StaticSprite2D").orderInLayer = 0 -- Draw car on top of the wheels (set to -1 to draw below)
    local ball1Node = ball:Clone()
    ball1Node.position = Vector3(-1.6, -2.5, 0)
    local ball2Node = ball:Clone()
    ball2Node.position = Vector3(-0.8, -2.5, 0)

    local wheel1 = car:CreateComponent("ConstraintWheel2D")
    wheel1.otherBody = ball1Node:GetComponent("RigidBody2D")
    wheel1.anchor = ball1Node.position2D
    wheel1.axis = Vector2(0, 1)
    wheel1.maxMotorTorque = 20
    wheel1.frequencyHz = 4
    wheel1.dampingRatio = 0.4

    local wheel2 = car:CreateComponent("ConstraintWheel2D")
    wheel2.otherBody = ball2Node:GetComponent("RigidBody2D")
    wheel2.anchor = ball2Node.position2D
    wheel2.axis = Vector2(0, 1)
    wheel2.maxMotorTorque = 10
    wheel2.frequencyHz = 4
    wheel2.dampingRatio = 0.4

    -- Create a ConstraintMotor2D
    CreateFlag("ConstraintMotor2D", 2.53, -1) -- Display Text3D flag
    local boxNode = box:Clone()
    boxNode:GetComponent("RigidBody2D").bodyType = BT_STATIC
    local ballNode = ball:Clone()
    boxNode.position = Vector3(3.8, -2.1, 0)
    ballNode.position = Vector3(3.8, -1.5, 0)

    constraintMotor = boxNode:CreateComponent("ConstraintMotor2D")
    constraintMotor.otherBody = ballNode:GetComponent("RigidBody2D") -- Constrain ball to box
    constraintMotor.linearOffset = Vector2(0, 0.8) -- Set ballNode position relative to boxNode position = (0,0)
    constraintMotor.angularOffset = 0.1
    constraintMotor.maxForce = 5
    constraintMotor.maxTorque = 10
    constraintMotor.correctionFactor = 1
    constraintMotor.collideConnected = true -- doesn't work

    -- Create a ConstraintMouse2D is demonstrated in HandleMouseButtonDown() function. It is used to "grasp" the sprites with the mouse.
    CreateFlag("ConstraintMouse2D", 0.03, -1) -- Display Text3D flag

    -- Create a ConstraintPrismatic2D
    CreateFlag("ConstraintPrismatic2D", 2.53, 3) -- Display Text3D flag
    local boxNode = box:Clone()
    boxNode:GetComponent("RigidBody2D").bodyType = BT_STATIC
    local ballNode = ball:Clone()
    boxNode.position = Vector3(3.3, 2.5, 0)
    ballNode.position = Vector3(4.3, 2, 0)

    local constraintPrismatic = boxNode:CreateComponent("ConstraintPrismatic2D")
    constraintPrismatic.otherBody = ballNode:GetComponent("RigidBody2D") -- Constrain ball to box
    constraintPrismatic.axis = Vector2(1, 1) -- Slide from [0,0] to [1,1]
    constraintPrismatic.anchor = Vector2(4, 2)
    constraintPrismatic.lowerTranslation = -1
    constraintPrismatic.upperTranslation = 0.5
    constraintPrismatic.enableLimit = true
    constraintPrismatic.maxMotorForce = 1
    constraintPrismatic.motorSpeed = 0

    -- Create a ConstraintPulley2D
    CreateFlag("ConstraintPulley2D", 0.03, 3) -- Display Text3D flag
    local boxNode = box:Clone()
    local ballNode = ball:Clone()
    boxNode.position = Vector3(0.5, 2, 0)
    ballNode.position = Vector3(2, 2, 0)

    local constraintPulley = boxNode:CreateComponent("ConstraintPulley2D") -- Apply constraint to box
    constraintPulley.otherBody = ballNode:GetComponent("RigidBody2D") -- Constrain ball to box
    constraintPulley.ownerBodyAnchor = boxNode.position2D
    constraintPulley.otherBodyAnchor = ballNode.position2D
    constraintPulley.ownerBodyGroundAnchor = boxNode.position2D + Vector2(0, 1)
    constraintPulley.otherBodyGroundAnchor = ballNode.position2D + Vector2(0, 1)
    constraintPulley.ratio = 1 -- Weight ratio between ownerBody and otherBody

    -- Create a ConstraintRevolute2D
    CreateFlag("ConstraintRevolute2D", -2.45, 3) -- Display Text3D flag
    local boxNode = box:Clone()
    boxNode:GetComponent("RigidBody2D").bodyType = BT_STATIC
    local ballNode = ball:Clone()
    boxNode.position = Vector3(-2, 1.5, 0)
    ballNode.position = Vector3(-1, 2, 0)

    local constraintRevolute = boxNode:CreateComponent("ConstraintRevolute2D") -- Apply constraint to box
    constraintRevolute.otherBody = ballNode:GetComponent("RigidBody2D") -- Constrain ball to box
    constraintRevolute.anchor = Vector2(-1, 1.5)
    constraintRevolute.lowerAngle = -1 -- In radians
    constraintRevolute.upperAngle = 0.5 -- In radians
    constraintRevolute.enableLimit = true
    constraintRevolute.maxMotorTorque = 10
    constraintRevolute.motorSpeed = 0
    constraintRevolute.enableMotor = true

    -- Create a ConstraintRope2D
    CreateFlag("ConstraintRope2D", -4.97, 1) -- Display Text3D flag
    local boxNode = box:Clone()
    boxNode:GetComponent("RigidBody2D").bodyType = BT_STATIC
    local ballNode = ball:Clone()
    boxNode.position = Vector3(-3.7, 0.7, 0)
    ballNode.position = Vector3(-4.5, 0, 0)

    local constraintRope = boxNode:CreateComponent("ConstraintRope2D")
    constraintRope.otherBody = ballNode:GetComponent("RigidBody2D") -- Constrain ball to box
    constraintRope.ownerBodyAnchor = Vector2(0, -0.5) -- Offset from box (OwnerBody) : the rope is rigid from OwnerBody center to this ownerBodyAnchor
    constraintRope.maxLength = 0.9 -- Rope length
    constraintRope.collideConnected = true

    -- Create a ConstraintWeld2D
    CreateFlag("ConstraintWeld2D", -2.45, 1) -- Display Text3D flag
    local boxNode = box:Clone()
    local ballNode = ball:Clone()
    boxNode.position = Vector3(-0.5, 0, 0)
    ballNode.position = Vector3(-2, 0, 0)

    local constraintWeld = boxNode:CreateComponent("ConstraintWeld2D")
    constraintWeld.otherBody = ballNode:GetComponent("RigidBody2D") -- Constrain ball to box
    constraintWeld.anchor = boxNode.position2D
    constraintWeld.frequencyHz = 4
    constraintWeld.dampingRatio = 0.5

    -- ConstraintWheel2D
    CreateFlag("ConstraintWheel2D",  2.53, 1) -- Display Text3D flag
    local boxNode = box:Clone()
    local ballNode = ball:Clone()
    boxNode.position = Vector3(3.8, 0, 0)
    ballNode.position = Vector3(3.8, 0.9, 0)

    local constraintWheel = boxNode:CreateComponent("ConstraintWheel2D")
    constraintWheel.otherBody = ballNode:GetComponent("RigidBody2D") -- Constrain ball to box
    constraintWheel.anchor = ballNode.position2D
    constraintWheel.axis = Vector2(0, 1)
    constraintWheel.enableMotor = true
    constraintWheel.maxMotorTorque = 1
    constraintWheel.motorSpeed = 0
    constraintWheel.frequencyHz = 4
    constraintWheel.dampingRatio = 0.5
    constraintWheel.collideConnected = true -- doesn't work
end

function CreateFlag(text, x, y) -- Used to create Tex3D flags
    local flagNode = scene_:CreateChild("Flag")
    flagNode.position = Vector3(x, y, 0)
    local flag3D = flagNode:CreateComponent("Text3D") -- We use Text3D in order to make the text affected by zoom (so that it sticks to 2D)
    flag3D.text = text
    flag3D:SetFont(cache:GetResource("Font", "Fonts/Anonymous Pro.ttf"), 15)
end

function CreateInstructions()
    -- Construct new Text object, set string to display and font to use
    local instructionText = ui.root:CreateChild("Text")
    instructionText:SetText("Use WASD keys and mouse to move, Use PageUp PageDown to zoom.\n Space to toggle debug geometry and joints - F5 to save the scene.")
    instructionText:SetFont(cache:GetResource("Font", "Fonts/Anonymous Pro.ttf"), 15)
    instructionText.textAlignment = HA_CENTER -- Center rows in relation to each other

    -- Position the text relative to the screen center
    instructionText.horizontalAlignment = HA_CENTER
    instructionText.verticalAlignment = VA_CENTER

    instructionText:SetPosition(0, ui.root.height / 4)
end

function MoveCamera(timeStep)
    if ui.focusElement ~= nil then return end -- Do not move if the UI has a focused element (the console)

    local MOVE_SPEED = 4 -- Movement speed as world units per second

    -- Read WASD keys and move the camera scene node to the corresponding direction if they are pressed
    if input:GetKeyDown(KEY_W) then cameraNode:Translate(Vector3(0, 1, 0) * MOVE_SPEED * timeStep) end
    if input:GetKeyDown(KEY_S) then cameraNode:Translate(Vector3(0, -1, 0) * MOVE_SPEED * timeStep) end
    if input:GetKeyDown(KEY_A) then cameraNode:Translate(Vector3(-1, 0, 0) * MOVE_SPEED * timeStep) end
    if input:GetKeyDown(KEY_D) then cameraNode:Translate(Vector3(1, 0, 0) * MOVE_SPEED * timeStep) end

    if input:GetKeyDown(KEY_PAGEUP) then camera.zoom = camera.zoom * 1.01 end -- Zoom In
    if input:GetKeyDown(KEY_PAGEDOWN) then camera.zoom = camera.zoom * 0.99 end -- Zoom Out
end

function SubscribeToEvents()
    SubscribeToEvent("Update", "HandleUpdate")
    SubscribeToEvent("PostRenderUpdate", "HandlePostRenderUpdate")
    SubscribeToEvent("MouseButtonDown", "HandleMouseButtonDown")
    if touchEnabled then SubscribeToEvent("TouchBegin", "HandleTouchBegin3") end
    -- Unsubscribe the SceneUpdate event from base class to prevent camera pitch and yaw in 2D sample
    UnsubscribeFromEvent("SceneUpdate")
end

function HandleUpdate(eventType, eventData)
    local timestep = eventData["TimeStep"]:GetFloat()
    MoveCamera(timestep) -- Move the camera according to frame's time step
    if input:GetKeyPress(KEY_SPACE) then drawDebug = not drawDebug end -- Toggle debug geometry with space
    if input:GetKeyPress(KEY_F5) then scene_:SaveXML(fileSystem:GetProgramDir().."Data/Scenes/Constraints.xml") end -- Save scene
end

function HandlePostRenderUpdate(eventType, eventData)
    if drawDebug then physicsWorld:DrawDebugGeometry() end
end

function HandleMouseButtonDown(eventType, eventData)
    local rigidBody = physicsWorld:GetRigidBody(input.mousePosition.x, input.mousePosition.y) -- Raycast for RigidBody2Ds to pick
    if rigidBody ~= nil then
        pickedNode = rigidBody.node
        local staticSprite = pickedNode:GetComponent("StaticSprite2D")
        staticSprite.color = Color(1, 0, 0, 1) -- Temporary modify color of the picked sprite

        -- ConstraintMouse2D - Temporary apply this constraint to the pickedNode to allow grasping and moving with the mouse
        local constraintMouse = pickedNode:CreateComponent("ConstraintMouse2D")
        constraintMouse.target = GetMousePositionXY()
        constraintMouse.maxForce = 1000 * rigidBody.mass
        constraintMouse.collideConnected = true
        constraintMouse.otherBody = dummyBody  -- Use dummy body instead of rigidBody. It's better to create a dummy body automatically in ConstraintMouse2D
    end
    SubscribeToEvent("MouseMove", "HandleMouseMove")
    SubscribeToEvent("MouseButtonUp", "HandleMouseButtonUp")
end

function HandleMouseButtonUp(eventType, eventData)
    if pickedNode ~= nil then
        local staticSprite = pickedNode:GetComponent("StaticSprite2D")
        staticSprite.color = Color(1, 1, 1, 1) -- Restore picked sprite color

        pickedNode:RemoveComponent("ConstraintMouse2D") -- Remove temporary constraint
        pickedNode = nil
    end
    UnsubscribeFromEvent("MouseMove")
    UnsubscribeFromEvent("MouseButtonUp")
end

function GetMousePositionXY()
    local screenPoint = Vector3(input.mousePosition.x / graphics.width, input.mousePosition.y / graphics.height, 0)
    local worldPoint = camera:ScreenToWorldPoint(screenPoint)
    return Vector2(worldPoint.x, worldPoint.y)
end

function HandleMouseMove(eventType, eventData)
    if pickedNode ~= nil then
        local constraintMouse = pickedNode:GetComponent("ConstraintMouse2D")
        constraintMouse.target = GetMousePositionXY()
    end
end

function HandleTouchBegin3(eventType, eventData)
    local rigidBody = physicsWorld:GetRigidBody(eventData["X"]:GetInt(), eventData["Y"]:GetInt()) -- Raycast for RigidBody2Ds to pick
    if rigidBody ~= nil then
        pickedNode = rigidBody.node
        local staticSprite = pickedNode:GetComponent("StaticSprite2D")
        staticSprite.color = Color(1, 0, 0, 1) -- Temporary modify color of the picked sprite
        local rigidBody = pickedNode:GetComponent("RigidBody2D")

        -- ConstraintMouse2D - Temporary apply this constraint to the pickedNode to allow grasping and moving with touch
        local constraintMouse = pickedNode:CreateComponent("ConstraintMouse2D")
        constraintMouse.target = camera:ScreenToWorldPoint(Vector3(eventData["X"]:GetInt() / graphics.width, eventData["Y"]:GetInt() / graphics.height, 0))
        constraintMouse.maxForce = 1000 * rigidBody.mass
        constraintMouse.collideConnected = true
        constraintMouse.otherBody = dummyBody  -- Use dummy body instead of rigidBody. It's better to create a dummy body automatically in ConstraintMouse2D
        constraintMouse.dampingRatio = 0
    end
    SubscribeToEvent("TouchMove", "HandleTouchMove3")
    SubscribeToEvent("TouchEnd", "HandleTouchEnd3")
end

function HandleTouchMove3(eventType, eventData)
    if pickedNode ~= nil then
        local constraintMouse = pickedNode:GetComponent("ConstraintMouse2D")
        constraintMouse.target = camera:ScreenToWorldPoint(Vector3(eventData["X"]:GetInt() / graphics.width, eventData["Y"]:GetInt() / graphics.height, 0))
    end
end

function HandleTouchEnd3(eventType, eventData)
    if pickedNode ~= nil then
        local staticSprite = pickedNode:GetComponent("StaticSprite2D")
        staticSprite.color = Color(1, 1, 1, 1) -- Restore picked sprite color

        pickedNode:RemoveComponent("ConstraintMouse2D") -- Remove temporary constraint
        pickedNode = nil
    end
    UnsubscribeFromEvent("TouchMove")
    UnsubscribeFromEvent("TouchEnd")
end

-- Create XML patch instructions for screen joystick layout specific to this sample app
function GetScreenJoystickPatchString()
    return
        "<patch>" ..
        "    <remove sel=\"/element/element[./attribute[@name='Name' and @value='Button0']]/attribute[@name='Is Visible']\" />" ..
        "    <replace sel=\"/element/element[./attribute[@name='Name' and @value='Button0']]/element[./attribute[@name='Name' and @value='Label']]/attribute[@name='Text']/@value\">Zoom In</replace>" ..
        "    <add sel=\"/element/element[./attribute[@name='Name' and @value='Button0']]\">" ..
        "        <element type=\"Text\">" ..
        "            <attribute name=\"Name\" value=\"KeyBinding\" />" ..
        "            <attribute name=\"Text\" value=\"PAGEUP\" />" ..
        "        </element>" ..
        "    </add>" ..
        "    <remove sel=\"/element/element[./attribute[@name='Name' and @value='Button1']]/attribute[@name='Is Visible']\" />" ..
        "    <replace sel=\"/element/element[./attribute[@name='Name' and @value='Button1']]/element[./attribute[@name='Name' and @value='Label']]/attribute[@name='Text']/@value\">Zoom Out</replace>" ..
        "    <add sel=\"/element/element[./attribute[@name='Name' and @value='Button1']]\">" ..
        "        <element type=\"Text\">" ..
        "            <attribute name=\"Name\" value=\"KeyBinding\" />" ..
        "            <attribute name=\"Text\" value=\"PAGEDOWN\" />" ..
        "        </element>" ..
        "    </add>" ..
        "</patch>"
end
