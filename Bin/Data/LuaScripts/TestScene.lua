ExecuteFile("LuaScripts/Utilities/Network.lua")

local testScene
local camera
local cameraNode

local yaw = 0
local pitch = 0
local drawDebug = 0

local context = GetContext()

local audio = GetAudio()
local cache = GetCache()
local engine = GetEngine()
local fileSystem = GetFileSystem()
local graphics = GetGraphics()
local input = GetInput()
local network = GetNetwork()
local renderer = GetRenderer()
local ui = GetUI()

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
        testScene:GetPhysicsWorld():SetInterpolation(false)
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
    local uiStyle = cache:GetXMLFile("UI/DefaultStyle.xml")

    local debugHud = engine:CreateDebugHud()
    debugHud:SetDefaultStyle(uiStyle)
    debugHud:SetMode(DEBUGHUD_SHOW_ALL)

    local console = engine:CreateConsole()
    console:SetDefaultStyle(uiStyle)
end

function InitUI()
    local uiStyle = cache:GetXMLFile("UI/DefaultStyle.xml")
    
    local newCursor = Cursor:new(context)
    newCursor:SetStyleAuto(uiStyle)
    newCursor:SetPosition(graphics:GetWidth()/ 2, graphics:GetHeight() / 2)
    ui:SetCursor(newCursor)
    
    if GetPlatform():Eq("Android") or GetPlatform():Eq("iOS") then
        ui:GetCursor():SetVisible(false)
    end
end

function InitScene()
    testScene = Scene(context)
    
    -- Create the camera outside the scene so it is unaffected by scene load/save
    cameraNode = Node(context)
    camera = cameraNode:CreateCamera()
    cameraNode:SetPosition(Vector3(0, 2, 0))

    if not engine:IsHeadless() then
        renderer:SetViewport(0, Viewport:new(context, testScene, camera))
        
        -- Add bloom & FXAA effects to the renderpath. Clone the default renderpath so that we don't affect it
        -- local newRenderPathPtr = renderer:GetViewport(0):GetRenderPath():Clone()
        -- local newRenderPath = newRenderPathPtr:Get()
        local newRenderPath = renderer:GetViewport(0):GetRenderPath():Clone()
        newRenderPath:Append(cache:GetXMLFile("PostProcess/Bloom.xml"))
        newRenderPath.Append(cache:GetXMLFile("PostProcess/EdgeFilter.xml"))
        newRenderPath:SetEnabled("Bloom", false)
        newRenderPath:SetEnabled("EdgeFilter", false)
        renderer:GetViewport(0):SetRenderPath(newRenderPath)
        audio:SetListener(cameraNode:CreateSoundListener())
    end
    
    if runClient then
        return
    end

    local world = testScene:CreatePhysicsWorld()
    testScene:CreateOctree()
    testScene:CreateDebugRenderer()

    local zoneNode = testScene:CreateChild("Zone")
    local zone = zoneNode:CreateZone()
    zone:SetAmbientColor(Color(0.15, 0.15, 0.15))
    zone:SetFogColor(Color(0.5, 0.5, 0.7))
    zone:SetFogStart(100.0)
    zone:SetFogEnd(300.0)
    zone:SetBoundingBox(BoundingBox(-1000, 1000))
    
    if true then
        local lightNode = testScene:CreateChild("GlobalLight")
        lightNode:SetDirection(Vector3(0.3, -0.5, 0.425))

        local light = lightNode:CreateLight()
        light:SetLightType(LIGHT_DIRECTIONAL)
        light:SetCastShadows(true)
        light:SetShadowBias(BiasParameters(0.0001, 0.5))
        light:SetShadowCascade(CascadeParameters(10.0, 50.0, 200.0, 0.0, 0.8))
        light:SetSpecularIntensity(0.5)
    end

    if true then
        local objectNode = testScene:CreateChild("Floor")
        objectNode:SetPosition(Vector3(0, -0.5, 0))
        objectNode:SetScale(Vector3(200, 1, 200))
        
        local object = objectNode:CreateStaticModel()
        object:SetModel(cache:GetModel("Models/Box.mdl"))
        object:SetMaterial(cache:GetMaterial("Materials/StoneTiled.xml"))
        object:SetOccluder(true)

        local body = objectNode:CreateRigidBody()
        local shape = objectNode:CreateCollisionShape()
        shape:SetBox(Vector3(1, 1, 1))
    end

    for i = 1, 50 do
        local objectNode = testScene:CreateChild("Box")
        objectNode:SetPosition(Vector3(Random() * 180 - 90, 1, Random() * 180 - 90))
        objectNode:SetScale(2)

        local object = objectNode:CreateStaticModel()
        object:SetModel(cache:GetModel("Models/Box.mdl"))
        object:SetMaterial(cache:GetMaterial("Materials/Stone.xml"))
        object:SetCastShadows(true)

        local body = objectNode:CreateRigidBody()
        local shape = objectNode:CreateCollisionShape()
        shape:SetBox(Vector3(1, 1, 1))
    end

    for i = 1, 10 do
        local objectNode = testScene:CreateChild("Box")
        objectNode:SetPosition(Vector3(Random() * 180 - 90, 10, Random() * 180 - 90))
        objectNode:SetScale(20)

        local object = objectNode:CreateStaticModel()
        object:SetModel(cache:GetModel("Models/Box.mdl"))
        object:SetMaterial(cache:GetMaterial("Materials/Stone.xml"))
        object:SetCastShadows(true)
        object:SetOccluder(true)

        local body = objectNode:CreateRigidBody()
        local shape = objectNode:CreateCollisionShape()
        shape:SetBox(Vector3(1, 1, 1))
    end
    
    
    
    for i = 1, 50 do
        local objectNode = testScene:CreateChild("Mushroom")
        objectNode:SetPosition(Vector3(Random() * 180 - 90, 0, Random() * 180 - 90))
        objectNode:SetRotation(Quaternion(0, Random(360.0), 0))
        objectNode:SetScale(5)

        local object = objectNode:CreateStaticModel()
        object:SetModel(cache:GetModel("Models/Mushroom.mdl"))
        object:SetMaterial(cache:GetMaterial("Materials/Mushroom.xml"))
        object:SetCastShadows(true)

        local body = objectNode:CreateRigidBody()
        local shape = objectNode:CreateCollisionShape()
        shape:SetTriangleMesh(object:GetModel())
    end

    
    for i = 1, 50 do
        local objectNode = testScene:CreateChild("Jack")
        objectNode:SetPosition(Vector3(Random() * 180 - 90, 0, Random() * 180 - 90))
        objectNode:SetRotation(Quaternion(0, Random() * 360, 0))

        local object = objectNode:CreateAnimatedModel()
        object:SetModel(cache:GetModel("Models/Jack.mdl"))
        object:SetMaterial(cache:GetMaterial("Materials/Jack.xml"))
        object:SetCastShadows(true)

        
        -- Create a capsule shape for detecting collisions
        local body = objectNode:CreateRigidBody()
        body:SetPhantom(true)
        
        local shape = objectNode:CreateCollisionShape()
        shape:SetCapsule(0.7, 1.8, Vector3(0.0, 0.9, 0.0))
        local ctrl = objectNode:CreateAnimationController()
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
            cameraNode:TranslateRelative(Vector3(0, 0, 10) * speed)
        end
        if input:GetKeyDown(KEY_S) then
            cameraNode:TranslateRelative(Vector3(0, 0, -10) * speed)
        end
        if input:GetKeyDown(KEY_A) then
            cameraNode:TranslateRelative(Vector3(-10, 0, 0) * speed)
        end
        if input:GetKeyDown(KEY_D) then
            cameraNode:TranslateRelative(Vector3(10, 0, 0) * speed)
        end
    end    
end

function HandleKeyDown(eventType, eventData)
    local key = eventData:GetInt("Key")

    if key == KEY_ESC then
        if ui:GetFocusElement() == nil then
            engine:Exit()
        else
            local console = GetConsole()
            console:SetVisible(false)
        end
    end

    if key == KEY_F1 then
        local console = GetConsole()
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
            local debugHud = GetDebugHud()
            debugHud:Toggle(DEBUGHUD_SHOW_PROFILER)
        end
        
        
        if key == KEY_F5  then
            local xmlFile = File(context, fileSystem:GetProgramDir() + "Data/Scenes/LuaTestScene.xml", FILE_WRITE)
            testScene:SaveXML(xmlFile)
        end
        
        if key == KEY_F7 then
            local xmlFile = File(context, fileSystem:GetProgramDir() + "Data/Scenes/LuaTestScene.xml", FILE_READ)
            if xmlFile:IsOpen() then
                testScene:LoadXML(xmlFile)
            end
        end
        --]]
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
            if ui:GetElementAt(pos, true) == nil and testScene:GetOctree() ~= nil then
                local cameraRay = camera:GetScreenRay(pos.x / graphics:GetWidth(), pos.y / graphics:GetHeight())
                local result = testScene:GetOctree():RaycastSingle(cameraRay, RAY_TRIANGLE, 250.0, DRAWABLE_GEOMETRY)
                if result.drawable ~= nil then
                    local rayHitPos = cameraRay.origin + cameraRay.direction * result.distance
                    local decal = result.drawable:GetNode():GetDecalSet()
                    if decal == nil then
                        decal = result.drawable:GetNode():CreateDecalSet()
                        decal:SetMaterial(cache:GetMaterial("Materials/UrhoDecal.xml"))
                        -- Increase max. vertices/indices if the target is skinned
                        --[[
                        if result.drawable:GetTypeName() == "AnimatedModel")
                        {
                            decal.maxVertices = 2048
                            decal.maxIndices = 4096
                        }
                        --]]
                    end
                    decal:AddDecal(result.drawable, rayHitPos, cameraNode:GetWorldRotation(), 0.5, 1.0, 1.0, Vector2(0, 0), Vector2(1, 1))
                end
            end
        end
    end
end

function HandleSpawnBox(eventType, eventData)
    local position = eventData:GetVector3("Pos")
    local rotation = eventData:GetQuaternion("Rot")
    
    local newNode = testScene:CreateChild("")
    newNode:SetPosition(position)
    newNode:SetRotation(rotation)
    newNode:SetScale(0.2)
    
    local body = newNode:CreateRigidBody()
    body:SetMass(1.0)
    body:SetFriction(1.0)
    body:SetLinearVelocity(rotation * Vector3(0.0, 1.0, 10.0))

    local shape = newNode:CreateCollisionShape()
    shape:SetBox(Vector3(1, 1, 1))

    local object = newNode:CreateStaticModel()
    object:SetModel(cache:GetModel("Models/Box.mdl"))
    object:SetMaterial(cache:GetMaterial("Materials/StoneSmall.xml"))
    object:SetCastShadows(true)
    object:SetShadowDistance(150.0)
    object:SetDrawDistance(200.0)
end

function HandleMouseButtonUp(eventType, eventData)
    if eventData:GetInt("Button") == MOUSEB_RIGHT then
        ui:GetCursor():SetVisible(true)
    end
end

function HandlePostRenderUpdate()
    if engine:IsHeadless() then
        return
    end
    
    -- Draw rendering debug geometry without depth test to see the effect of occlusion
    if drawDebug == 1 then
        renderer:DrawDebugGeometry(false)
    end
    if drawDebug == 2 then
        testScene:GetPhysicsWorld():DrawDebugGeometry(true)
    end
    
    local pos = ui:GetCursorPosition()
    if ui:GetElementAt(pos, true) == nil and testScene:GetOctree() ~= nil then
        local cameraRay = camera:GetScreenRay(pos.x / graphics:GetWidth(), pos.y / graphics:GetHeight())
        local result = testScene:GetOctree():RaycastSingle(cameraRay, RAY_TRIANGLE, 250.0, DRAWABLE_GEOMETRY)
        if result.drawable ~= nil then
            local rayHitPos = cameraRay.origin + cameraRay.direction * result.distance
            testScene:GetDebugRenderer():AddBoundingBox(BoundingBox(rayHitPos + Vector3(-0.01, -0.01, -0.01), rayHitPos +
                Vector3(0.01, 0.01, 0.01)), Color(1.0, 1.0, 1.0), true)
        end
    end
end

function HandleClientConnected(eventType, eventData)
    local connection = eventData:GetConnection("Connection")
    connection:SetScene(testScene) -- Begin scene replication to the client
    connection:SetLogStatistics(true)
end


function HandlePhysicsCollision(eventType, eventData)
    -- Check if either of the nodes has an AnimatedModel component
    local nodeA = eventData:GetNode("NodeA")
    local nodeB = eventData:GetNode("NodeB")
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
    CreateRagdoll(node:GetAnimatedModel())
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
    local body = boneNode:CreateRigidBody(LOCAL)
    body:SetMass(1.0)
    body:SetLinearDamping(0.05)
    body:SetAngularDamping(0.85)
    body:SetLinearRestThreshold(1.5)
    body:SetAngularRestThreshold(2.5)

    local shape = boneNode:CreateCollisionShape(LOCAL)
    shape:SetShapeType(type)
    shape:SetSize(size)
    shape:SetPosition(position)
    shape:SetRotation(rotation)
end

function CreateRagdollConstraint(root, boneName, parentName, type, axis, parentAxis, highLimit, lowLimit, disableCollision)
    local boneNode = root:GetChild(boneName, true)
    local parentNode = root:GetChild(parentName, true)
    if boneNode == nil or parentNode == nil or boneNode:HasComponent("Constraint") then
        return
    end

    local constraint = boneNode:CreateConstraint(LOCAL)
    constraint:SetConstraintType(type)
    constraint:SetDisableCollision(disableCollision)
    -- The connected body must be specified before setting the world position
    constraint:SetOtherBody(parentNode:GetRigidBody())
    constraint:SetWorldPosition(boneNode:GetWorldPosition())
    constraint:SetAxis(axis)
    constraint:SetOtherAxis(parentAxis)
    constraint:SetHighLimit(highLimit)
    constraint:SetLowLimit(lowLimit)
end