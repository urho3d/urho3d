require "LuaScripts/Utilities/Network"

local testScene
local camera
local cameraNode

local yaw = 0
local pitch = 0
local drawDebug = 0

function Start()
    if not engine:IsHeadless() then
        InitConsole()
        InitUI()
    else
        OpenConsoleWindow()
    end
    
    ParseNetworkArguments()

    InitScene()
    
    SubscribeToEvent("Update", "HandleUpdate")
    SubscribeToEvent("KeyDown", "HandleKeyDown")
    SubscribeToEvent("MouseMove", "HandleMouseMove")
    SubscribeToEvent("MouseButtonDown", "HandleMouseButtonDown")
    SubscribeToEvent("MouseButtonUp", "HandleMouseButtonUp")
    SubscribeToEvent("PostRenderUpdate", "HandlePostRenderUpdate")
    SubscribeToEvent("SpawnBox", "HandleSpawnBox")
    SubscribeToEvent("PhysicsCollision", "HandlePhysicsCollision")
    
    network:RegisterRemoteEvent("SpawnBox")
    
    if runServer then
        network:StartServer(serverPort)
        SubscribeToEvent("ClientConnected", "HandleClientConnected")

        -- Disable physics interpolation to ensure clients get sent physically correct transforms
        testScene:GetComponent("PhysicsWorld"):SetInterpolation(false)
    end
    
    if runClient then
        network:Connect(serverAddress, serverPort, testScene)
    end
end

function Stop()
    testScene = nil
    camera = nil
    cameraNode = nil
end

function InitConsole()
    local uiStyle = cache:GetResource("XMLFile", "UI/DefaultStyle.xml")

    engine:CreateDebugHud()
    debugHud.defaultStyle = uiStyle
    debugHud.mode = DEBUGHUD_SHOW_ALL

    engine:CreateConsole()
    console.defaultStyle = uiStyle
end

function InitUI()
    local uiStyle = cache:GetResource("XMLFile", "UI/DefaultStyle.xml")
    
    local newCursor = Cursor:new()
    newCursor.styleAuto = uiStyle
    newCursor.position = IntVector2(graphics:GetWidth()/ 2, graphics:GetHeight() / 2)
    ui.cursor = newCursor
    
    if GetPlatform() == "Android" or GetPlatform() == "iOS" then
        ui.cursor.visible = false
    end
end

function InitScene()
    testScene = Scene()
    
    -- Create the camera outside the scene so it is unaffected by scene load/save
    cameraNode = Node()
    camera = cameraNode:CreateComponent("Camera")
    cameraNode.position = Vector3(0, 2, 0)

    if not engine:IsHeadless() then
        renderer:SetViewport(0, Viewport:new(testScene, camera))
        
        -- Add bloom & FXAA effects to the renderpath. Clone the default renderpath so that we don't affect it
        -- local newRenderPathPtr = renderer:GetViewport(0):GetRenderPath():Clone()
        -- local newRenderPath = newRenderPathPtr:Get()
        local newRenderPath = renderer:GetViewport(0):GetRenderPath():Clone()
        newRenderPath:Append(cache:GetResource("XMLFile", "PostProcess/Bloom.xml"))
        newRenderPath:Append(cache:GetResource("XMLFile", "PostProcess/EdgeFilter.xml"))
        newRenderPath:SetEnabled("Bloom", false)
        newRenderPath:SetEnabled("EdgeFilter", false)
        renderer:GetViewport(0):SetRenderPath(newRenderPath)
        audio:SetListener(cameraNode:CreateComponent("SoundListener"))
    end
    
    if runClient then
        return
    end

    local world = testScene:CreateComponent("PhysicsWorld")
    testScene:CreateComponent("Octree")
    testScene:CreateComponent("DebugRenderer")

    local zoneNode = testScene:CreateChild("Zone")
    local zone = zoneNode:CreateComponent("Zone")
    zone.ambientColor = Color(0.15, 0.15, 0.15)
    zone.fogColor = Color(0.5, 0.5, 0.7)
    zone.fogStart = 100.0
    zone.fogEnd = 300.0
    zone.boundingBox = BoundingBox(-1000, 1000)
    
    if true then
        local lightNode = testScene:CreateChild("GlobalLight")
        lightNode.direction = Vector3(0.3, -0.5, 0.425)
        
        local light = lightNode:CreateComponent("Light")
        light.lightType = LIGHT_DIRECTIONAL
        light.castShadows = true
        light.shadowBias = BiasParameters(0.00025, 0.5)
        light.shadowCascade = CascadeParameters(10.0, 50.0, 200.0, 0.0, 0.8)
        light.specularIntensity = 0.5
    end

    if true then
        local objectNode = testScene:CreateChild("Floor")
        objectNode.position = Vector3(0, -0.5, 0)
        objectNode.scale = Vector3(200, 1, 200)
        
        local object = objectNode:CreateComponent("StaticModel")
        object.model = cache:GetResource("Model", "Models/Box.mdl")
        object.material = cache:GetResource("Material", "Materials/StoneTiled.xml")
        object.occluder = true

        local body = objectNode:CreateComponent("RigidBody")
        local shape = objectNode:CreateComponent("CollisionShape")
        shape:SetBox(Vector3(1, 1, 1))
    end

    for i = 1, 50 do
        local objectNode = testScene:CreateChild("Box")
        objectNode.position = Vector3(Random() * 180 - 90, 1, Random() * 180 - 90)
        objectNode:SetScale(2)

        local object = objectNode:CreateComponent("StaticModel")
        object.model = cache:GetResource("Model", "Models/Box.mdl")
        object.material = cache:GetResource("Material", "Materials/Stone.xml")
        object.castShadows = true

        local body = objectNode:CreateComponent("RigidBody")
        local shape = objectNode:CreateComponent("CollisionShape")
        shape:SetBox(Vector3(1, 1, 1))
    end

    for i = 1, 10 do
        local objectNode = testScene:CreateChild("Box")
        objectNode.position = Vector3(Random() * 180 - 90, 10, Random() * 180 - 90)
        objectNode:SetScale(20)

        local object = objectNode:CreateComponent("StaticModel")
        object.model = cache:GetResource("Model", "Models/Box.mdl")
        object.material = cache:GetResource("Material", "Materials/Stone.xml")
        object.castShadows = true
        object.occluder = true

        local body = objectNode:CreateComponent("RigidBody")
        local shape = objectNode:CreateComponent("CollisionShape")
        shape:SetBox(Vector3(1, 1, 1))
    end
    
    
    
    for i = 1, 50 do
        local objectNode = testScene:CreateChild("Mushroom")
        objectNode.position = Vector3(Random() * 180 - 90, 0, Random() * 180 - 90)
        objectNode.rotation = Quaternion(0, Random(360.0), 0)
        objectNode:SetScale(5)

        local object = objectNode:CreateComponent("StaticModel")
        object.model = cache:GetResource("Model", "Models/Mushroom.mdl")
        object.material = cache:GetResource("Material", "Materials/Mushroom.xml")
        object.castShadows = true

        local body = objectNode:CreateComponent("RigidBody")
        local shape = objectNode:CreateComponent("CollisionShape")
        shape:SetTriangleMesh(object:GetModel())
    end

    
    for i = 1, 50 do
        local objectNode = testScene:CreateChild("Jack")
        objectNode:SetPosition(Vector3(Random() * 180 - 90, 0, Random() * 180 - 90))
        objectNode:SetRotation(Quaternion(0, Random() * 360, 0))

        local object = objectNode:CreateComponent("AnimatedModel")
        object.model = cache:GetResource("Model", "Models/Jack.mdl")
        object.material = cache:GetResource("Material", "Materials/Jack.xml")
        object.castShadows = true
        
        -- Create a capsule shape for detecting collisions
        local body = objectNode:CreateComponent("RigidBody")
        body.trigger = true
        
        local shape = objectNode:CreateComponent("CollisionShape")
        shape:SetCapsule(0.7, 1.8, Vector3(0.0, 0.9, 0.0))
        local ctrl = objectNode:CreateComponent("AnimationController")
        ctrl:Play("Models/Jack_Walk.ani", 0, true, 0.0)
    end
end

function HandleUpdate(eventType, eventData)
    local timeStep = eventData:GetFloat("TimeStep")
    
    if ui:GetFocusElement() == nil then
        local speedMultiplier = 1.0
        if input:GetKeyDown(KEY_LSHIFT) then
            speedMultiplier = 5.0
        end        
        if input:GetKeyDown(KEY_LCTRL) then
            speedMultiplier = 0.1
        end
        
        local speed = timeStep * speedMultiplier
        
        if input:GetKeyDown(KEY_W) then
            cameraNode:Translate(Vector3(0, 0, 10) * speed)
        end
        if input:GetKeyDown(KEY_S) then
            cameraNode:Translate(Vector3(0, 0, -10) * speed)
        end
        if input:GetKeyDown(KEY_A) then
            cameraNode:Translate(Vector3(-10, 0, 0) * speed)
        end
        if input:GetKeyDown(KEY_D) then
            cameraNode:Translate(Vector3(10, 0, 0) * speed)
        end
    end    
end

function HandleKeyDown(eventType, eventData)
    local key = eventData:GetInt("Key")

    if key == KEY_ESC then
        if ui:GetFocusElement() == nil then
            engine:Exit()
        else
            console:SetVisible(false)
        end
    end

    if key == KEY_F1 then
        console:Toggle()
    end
    
    if ui:GetFocusElement() == nil then
        if key == KEY_1 then
            local quality = renderer:GetTextureQuality()
            quality = quality + 1
            if quality > 2 then
                quality = 0
            end
            renderer:SetTextureQuality(quality)
        end
        
        if key == KEY_2 then
            local quality = renderer:GetMaterialQuality()
            quality = quality + 1
            if quality > 2 then
                quality = 0
            end
            renderer:SetMaterialQuality(quality)
        end
        
        if key == KEY_3 then
            renderer:SetSpecularLighting(not renderer:GetSpecularLighting())
        end

        if key == KEY_4 then
            renderer:SetDrawShadows(not renderer:GetDrawShadows())
        end

        if key == KEY_5 then
            local size = renderer:GetShadowMapSize()
            size = size * 2
            if size > 2048 then
                size = 512
            end
            renderer:SetShadowMapSize(size)
        end

        if key == KEY_6 then
            renderer:SetShadowQuality(renderer:GetShadowQuality() + 1)
        end

        if key == KEY_7 then
            local occlusion = renderer:GetMaxOccluderTriangles() > 0
            occlusion = not occlusion
            if occlusion then
                renderer:SetMaxOccluderTriangles(5000)
            else
                renderer:SetMaxOccluderTriangles(0)
            end
        end
        
        if key == KEY_8 then
            renderer:SetDynamicInstancing(not renderer:GetDynamicInstancing())
        end

        if key == KEY_SPACE then
            drawDebug = drawDebug + 1
            if drawDebug > 2 then
                drawDebug = 0
            end
        end

        if key == KEY_B then
            renderer:GetViewport(0):GetRenderPath():ToggleEnabled("Bloom")
        end

        if key == KEY_F then
            renderer:GetViewport(0):GetRenderPath():ToggleEnabled("EdgeFilter")
        end

        if key == KEY_O then
            camera:SetOrthographic(not camera:IsOrthographic())
        end

        if key == KEY_T then
            debugHud:Toggle(DEBUGHUD_SHOW_PROFILER)
        end
        
        
        if key == KEY_F5  then
            testScene:SaveXML(fileSystem:GetProgramDir() + "Data/Scenes/LuaTestScene.xml")
        end
        
        if key == KEY_F7 then
            testScene:LoadXML(fileSystem:GetProgramDir() + "Data/Scenes/LuaTestScene.xml")
        end
    end    
end

function HandleMouseMove(eventType, eventData)
    local buttons = eventData:GetInt("Buttons")
    if buttons == MOUSEB_RIGHT then
        local mousedx = eventData:GetInt("DX")
        local mousedy = eventData:GetInt("DY")
        yaw = yaw + (mousedx / 10.0)
        pitch = pitch + (mousedy / 10.0)
        if pitch < -90.0 then
            pitch = -90.0
        end
        if pitch > 90.0 then
            pitch = 90.0
        end
        cameraNode:SetRotation(Quaternion(pitch, yaw, 0))
    end
end


function HandleMouseButtonDown(eventType, eventData)
    local button = eventData:GetInt("Button")
    if button == MOUSEB_RIGHT then
        local cursor = ui:GetCursor()
        cursor:SetVisible(false)        
    end    
    
    -- Test either creating a new physics object or painting a decal (SHIFT down)
    if button == MOUSEB_LEFT and ui:GetElementAt(ui:GetCursorPosition(), true) == nil and ui:GetFocusElement() == nil then
        if not input:GetQualifierDown(QUAL_SHIFT) then
            local eventData = VariantMap()
            eventData:SetVector3("Pos", cameraNode:GetPosition())
            eventData:SetQuaternion("Rot", cameraNode:GetRotation())

            -- If we are the client, send the spawn command as a remote event, else send locally
            if runClient then
                if network:GetServerConnection() ~= nil then
                    network:GetServerConnection():SendRemoteEvent("SpawnBox", true, eventData)
                end
            else
                SendEvent("SpawnBox", eventData)
            end
        else
            local pos = ui:GetCursorPosition()
            if ui:GetElementAt(pos, true) == nil and testScene:GetComponent("Octree") ~= nil then
                local cameraRay = camera:GetScreenRay(pos.x / graphics:GetWidth(), pos.y / graphics:GetHeight())
                local result = testScene:GetComponent("Octree"):RaycastSingle(cameraRay, RAY_TRIANGLE, 250.0, DRAWABLE_GEOMETRY)
                if result.drawable ~= nil then
                    local decal = result.drawable:GetNode():GetComponent("DecalSet")
                    if decal == nil then
                        decal = result.drawable:GetNode():CreateComponent("DecalSet")
                        decal.material = cache:GetResource("Material", "Materials/UrhoDecal.xml")
                        -- Increase max. vertices/indices if the target is skinned
                        if result.drawable:GetTypeName() == "AnimatedModel" then
                            decal.maxVertices = 2048
                            decal.maxIndices = 4096
                        end
                    end
                    decal:AddDecal(result.drawable, result.position, cameraNode:GetWorldRotation(), 0.5, 1.0, 1.0, Vector2(0, 0), Vector2(1, 1))
                end
            end
        end
    end
end

function HandleSpawnBox(eventType, eventData)
    local position = eventData:GetVector3("Pos")
    local rotation = eventData:GetQuaternion("Rot")
    
    local newNode = testScene:CreateChild("")
    newNode.position = position
    newNode.rotation =rotation
    newNode:SetScale(0.2)
    
    local body = newNode:CreateComponent("RigidBody")
    body.mass = 1.0
    body.friction = 1.0
    body.linearVelocity = rotation * Vector3(0.0, 1.0, 10.0)

    local shape = newNode:CreateComponent("CollisionShape")
    shape:SetBox(Vector3(1, 1, 1))

    local object = newNode:CreateComponent("StaticModel")
    object.model = cache:GetResource("Model", "Models/Box.mdl")
    object.material = cache:GetResource("Material", "Materials/StoneSmall.xml")
    object.castShadows = true
    object.shadowDistance = 150.0
    object.drawDistance = 200.0
end

function HandleMouseButtonUp(eventType, eventData)
    if eventData:GetInt("Button") == MOUSEB_RIGHT then
        ui:GetCursor():SetVisible(true)
    end
end

function HandlePostRenderUpdate()
    if engine.headless then
        return
    end
    
    -- Draw rendering debug geometry without depth test to see the effect of occlusion
    if drawDebug == 1 then
        renderer:DrawDebugGeometry(true)
    end
    if drawDebug == 2 then
        testScene:GetComponent("PhysicsWorld"):DrawDebugGeometry(true)
    end
    
    local pos = ui.cursorPosition
    if ui:GetElementAt(pos, true) == nil and testScene:GetComponent("Octree") ~= nil then
        local cameraRay = camera:GetScreenRay(pos.x / graphics:GetWidth(), pos.y / graphics:GetHeight())
        local result = testScene:GetComponent("Octree"):RaycastSingle(cameraRay, RAY_TRIANGLE, 250.0, DRAWABLE_GEOMETRY)
        if result.drawable ~= nil then
            local rayHitPos = cameraRay.origin + cameraRay.direction * result.distance
            testScene:GetComponent("DebugRenderer"):AddBoundingBox(BoundingBox(rayHitPos + Vector3(-0.01, -0.01, -0.01), rayHitPos +
                Vector3(0.01, 0.01, 0.01)), Color(1.0, 1.0, 1.0), true)
        end
    end
end

function HandleClientConnected(eventType, eventData)
    local connection = eventData:GetPtr("Connection", "Connection")
    connection.scene = testScene -- Begin scene replication to the client
    connection.logStatistics = true
end


function HandlePhysicsCollision(eventType, eventData)
    -- Check if either of the nodes has an AnimatedModel component
    local nodeA = eventData:GetPtr("Node", "NodeA")
    local nodeB = eventData:GetPtr("Node", "NodeB")
    if nodeA:HasComponent("AnimatedModel") then
        HandleHit(nodeA)
    elseif nodeB:HasComponent("AnimatedModel") then
        HandleHit(nodeB)
    end
end

function HandleHit(node)
    -- Remove the trigger physics shape, and create the ragdoll
    node:RemoveComponent("RigidBody")
    node:RemoveComponent("CollisionShape")
    CreateRagdoll(node:GetComponent("AnimatedModel"))
end

function CreateRagdoll(model)
    local root = model:GetNode()
    CreateRagdollBone(root, "Bip01_Pelvis", SHAPE_BOX, Vector3(0.3, 0.2, 0.25), Vector3(0, 0, 0), Quaternion(0, 0, 0))
    CreateRagdollBone(root, "Bip01_Spine1", SHAPE_BOX, Vector3(0.35, 0.2, 0.3), Vector3(0.15, 0, 0), Quaternion(0, 0, 0))
    CreateRagdollBone(root, "Bip01_L_Thigh", SHAPE_CAPSULE, Vector3(0.175, 0.45, 0.175), Vector3(0.25, 0, 0), Quaternion(0, 0, 90))
    CreateRagdollBone(root, "Bip01_R_Thigh", SHAPE_CAPSULE, Vector3(0.175, 0.45, 0.175), Vector3(0.25, 0, 0), Quaternion(0, 0, 90))
    CreateRagdollBone(root, "Bip01_L_Calf", SHAPE_CAPSULE, Vector3(0.15, 0.55, 0.15), Vector3(0.25, 0, 0), Quaternion(0, 0, 90))
    CreateRagdollBone(root, "Bip01_R_Calf", SHAPE_CAPSULE, Vector3(0.15, 0.55, 0.15), Vector3(0.25, 0, 0), Quaternion(0, 0, 90))
    CreateRagdollBone(root, "Bip01_Head", SHAPE_BOX, Vector3(0.2, 0.2, 0.2), Vector3(0.1, 0, 0), Quaternion(0, 0, 0))
    CreateRagdollBone(root, "Bip01_L_UpperArm", SHAPE_CAPSULE, Vector3(0.15, 0.35, 0.15), Vector3(0.1, 0, 0), Quaternion(0, 0, 90))
    CreateRagdollBone(root, "Bip01_R_UpperArm", SHAPE_CAPSULE, Vector3(0.15, 0.35, 0.15), Vector3(0.1, 0, 0), Quaternion(0, 0, 90))
    CreateRagdollBone(root, "Bip01_L_Forearm", SHAPE_CAPSULE, Vector3(0.125, 0.4, 0.125), Vector3(0.2, 0, 0), Quaternion(0, 0, 90))
    CreateRagdollBone(root, "Bip01_R_Forearm", SHAPE_CAPSULE, Vector3(0.125, 0.4, 0.125), Vector3(0.2, 0, 0), Quaternion(0, 0, 90))
    
    CreateRagdollConstraint(root, "Bip01_L_Thigh", "Bip01_Pelvis", CONSTRAINT_CONETWIST, Vector3(0, 0, -1), Vector3(0, 0, 1), Vector2(45, 45), Vector2(0, 0), true)
    CreateRagdollConstraint(root, "Bip01_R_Thigh", "Bip01_Pelvis", CONSTRAINT_CONETWIST, Vector3(0, 0, -1), Vector3(0, 0, 1), Vector2(45, 45), Vector2(0, 0), true)
    CreateRagdollConstraint(root, "Bip01_L_Calf", "Bip01_L_Thigh", CONSTRAINT_HINGE, Vector3(0, 0, -1), Vector3(0, 0, -1), Vector2(90, 0), Vector2(0, 0), true)
    CreateRagdollConstraint(root, "Bip01_R_Calf", "Bip01_R_Thigh", CONSTRAINT_HINGE, Vector3(0, 0, -1), Vector3(0, 0, -1), Vector2(90, 0), Vector2(0, 0), true)
    CreateRagdollConstraint(root, "Bip01_Spine1", "Bip01_Pelvis", CONSTRAINT_HINGE, Vector3(0, 0, 1), Vector3(0, 0, 1), Vector2(45, 0), Vector2(-10, 0), true)
    CreateRagdollConstraint(root, "Bip01_Head", "Bip01_Spine1", CONSTRAINT_CONETWIST, Vector3(1, 0, 0), Vector3(1, 0, 0), Vector2(0, 30), Vector2(0, 0), true)
    CreateRagdollConstraint(root, "Bip01_L_UpperArm", "Bip01_Spine1", CONSTRAINT_CONETWIST, Vector3(0, -1, 0), Vector3(0, 1, 0), Vector2(45, 45), Vector2(0, 0), false)
    CreateRagdollConstraint(root, "Bip01_R_UpperArm", "Bip01_Spine1", CONSTRAINT_CONETWIST, Vector3(0, -1, 0), Vector3(0, 1, 0), Vector2(45, 45), Vector2(0, 0), false)
    CreateRagdollConstraint(root, "Bip01_L_Forearm", "Bip01_L_UpperArm", CONSTRAINT_HINGE, Vector3(0, 0, -1), Vector3(0, 0, -1), Vector2(90, 0), Vector2(0, 0), true)
    CreateRagdollConstraint(root, "Bip01_R_Forearm", "Bip01_R_UpperArm", CONSTRAINT_HINGE, Vector3(0, 0, -1), Vector3(0, 0, -1), Vector2(90, 0), Vector2(0, 0), true)

    -- Disable animation from all bones (both physical and non-physical) to not interfere
    local skel = model:GetSkeleton()
    for i = 1, skel:GetNumBones() do
        skel:GetBone(i-1).animated = false
    end
end

function CreateRagdollBone(root, boneName, type, size, position, rotation)
    local boneNode = root:GetChild(boneName, true)
    if boneNode == nil or boneNode:HasComponent("RigidBody") then
        return
    end

    -- In networked operation both client and server detect collisions separately, and create ragdolls on their own
    -- (bones are not synced over network.) To prevent replicated component ID range clashes when the client creates
    -- any components, it is important that the LOCAL creation mode is specified.
    local body = boneNode:CreateComponent("RigidBody", LOCAL)
    body.mass = 1.0
    body.linearDamping = 0.05
    body.angularDamping = 0.85
    body.linearRestThreshold = 1.5
    body.angularRestThreshold = 2.5

    local shape = boneNode:CreateComponent("CollisionShape", LOCAL)
    shape.shapeType = type
    shape.size = size
    shape.position = position
    shape.rotation = rotation
end

function CreateRagdollConstraint(root, boneName, parentName, type, axis, parentAxis, highLimit, lowLimit, disableCollision)
    local boneNode = root:GetChild(boneName, true)
    local parentNode = root:GetChild(parentName, true)
    if boneNode == nil or parentNode == nil or boneNode:HasComponent("Constraint") then
        return
    end

    local constraint = boneNode:CreateComponent("Constraint", LOCAL)
    constraint.constraintType = type
    constraint.disableCollision = disableCollision
    -- The connected body must be specified before setting the world position
    constraint.otherBody = parentNode:GetComponent("RigidBody")
    constraint.worldPosition = boneNode.worldPosition
    constraint:SetAxis(axis)
    constraint:SetOtherAxis(parentAxis)
    constraint.highLimit = highLimit
    constraint.lowLimit = lowLimit
end
