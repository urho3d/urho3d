-- Scene network replication example.
-- This sample demonstrates:
--     - Creating a scene in which network clients can join
--     - Giving each client an object to control and sending the controls from the clients to the server,
--       where the authoritative simulation happens
--     - Controlling a physics object's movement by applying forces

require "LuaScripts/Utilities/Sample"

-- UDP port we will use
local SERVER_PORT = 2345

-- Control bits we define
local CTRL_FORWARD = 1
local CTRL_BACK = 2
local CTRL_LEFT = 4
local CTRL_RIGHT = 8

local instructionsText = nil
local buttonContainer = nil
local textEdit = nil
local connectButton = nil
local disconnectButton = nil
local startServerButton = nil
local clients = {}
local clientObjectID = 0

function Start()
    -- Execute the common startup for samples
    SampleStart()

    -- Create the scene content
    CreateScene()

    -- Create the UI content
    CreateUI()

    -- Setup the viewport for displaying the scene
    SetupViewport()

    -- Set the mouse mode to use in the sample
    SampleInitMouseMode(MM_RELATIVE)

    -- Hook up to necessary events
    SubscribeToEvents()
end

function CreateScene()
    scene_ = Scene()

    -- Create octree and physics world with default settings. Create them as local so that they are not needlessly replicated
    -- when a client connects
    scene_:CreateComponent("Octree", LOCAL)
    scene_:CreateComponent("PhysicsWorld", LOCAL)

    -- All static scene content and the camera are also created as local, so that they are unaffected by scene replication and are
    -- not removed from the client upon connection. Create a Zone component first for ambient lighting & fog control.
    local zoneNode = scene_:CreateChild("Zone", LOCAL)
    local zone = zoneNode:CreateComponent("Zone")
    zone.boundingBox = BoundingBox(-1000.0, 1000.0)
    zone.ambientColor = Color(0.1, 0.1, 0.1)
    zone.fogStart = 100.0
    zone.fogEnd = 300.0

    -- Create a directional light without shadows
    local lightNode = scene_:CreateChild("DirectionalLight", LOCAL)
    lightNode.direction = Vector3(0.5, -1.0, 0.5)
    local light = lightNode:CreateComponent("Light")
    light.lightType = LIGHT_DIRECTIONAL
    light.color = Color(0.2, 0.2, 0.2)
    light.specularIntensity = 1.0

    -- Create a "floor" consisting of several tiles. Make the tiles physical but leave small cracks between them
    for y = -20, 20 do
        for x = -20, 20 do
            local floorNode = scene_:CreateChild("FloorTile", LOCAL)
            floorNode.position = Vector3(x * 20.2, -0.5, y * 20.2)
            floorNode.scale = Vector3(20.0, 1.0, 20.0)
            local floorObject = floorNode:CreateComponent("StaticModel")
            floorObject.model = cache:GetResource("Model", "Models/Box.mdl")
            floorObject.material = cache:GetResource("Material", "Materials/Stone.xml")

            local body = floorNode:CreateComponent("RigidBody")
            body.friction = 1.0
            local shape = floorNode:CreateComponent("CollisionShape")
            shape:SetBox(Vector3(1.0, 1.0, 1.0))
        end
    end

    -- Create the camera. Limit far clip distance to match the fog
    -- The camera needs to be created into a local node so that each client can retain its own camera, that is unaffected by
    -- network messages. Furthermore, because the client removes all replicated scene nodes when connecting to a server scene,
    -- the screen would become blank if the camera node was replicated (as only the locally created camera is assigned to a
    -- viewport in SetupViewports() below)
    cameraNode = scene_:CreateChild("Camera", LOCAL)
    local camera = cameraNode:CreateComponent("Camera")
    camera.farClip = 300.0

    -- Set an initial position for the camera scene node above the plane
    cameraNode.position = Vector3(0.0, 5.0, 0.0)
end

function CreateUI()
    local uiStyle = cache:GetResource("XMLFile", "UI/DefaultStyle.xml")
    -- Set style to the UI root so that elements will inherit it
    ui.root.defaultStyle = uiStyle

    -- Create a Cursor UI element because we want to be able to hide and show it at will. When hidden, the mouse cursor will
    -- control the camera, and when visible, it will point the raycast target
    local cursor = ui.root:CreateChild("Cursor")
    cursor:SetStyleAuto(uiStyle)
    ui.cursor = cursor
    -- Set starting position of the cursor at the rendering window center
    cursor:SetPosition(graphics.width / 2, graphics.height / 2)

    -- Construct the instructions text element
    instructionsText = ui.root:CreateChild("Text")
    instructionsText:SetText("Use WASD keys to move and RMB to rotate view")
    instructionsText:SetFont(cache:GetResource("Font", "Fonts/Anonymous Pro.ttf"), 15)
    -- Position the text relative to the screen center
    instructionsText.horizontalAlignment = HA_CENTER
    instructionsText.verticalAlignment = VA_CENTER
    instructionsText:SetPosition(0, graphics.height / 4)
    -- Hide until connected
    instructionsText.visible = false

    buttonContainer = ui.root:CreateChild("UIElement")
    buttonContainer:SetFixedSize(500, 20)
    buttonContainer:SetPosition(20, 20)
    buttonContainer.layoutMode = LM_HORIZONTAL

    textEdit = buttonContainer:CreateChild("LineEdit")
    textEdit:SetStyleAuto()

    connectButton = CreateButton("Connect", 90)
    disconnectButton = CreateButton("Disconnect", 100)
    startServerButton = CreateButton("Start Server", 110)

    UpdateButtons()
end

function SetupViewport()
    -- Set up a viewport to the Renderer subsystem so that the 3D scene can be seen
    local viewport = Viewport:new(scene_, cameraNode:GetComponent("Camera"))
    renderer:SetViewport(0, viewport)
end

function SubscribeToEvents()
    -- Subscribe to fixed timestep physics updates for setting or applying controls
    SubscribeToEvent("PhysicsPreStep", "HandlePhysicsPreStep")

    -- Subscribe HandlePostUpdate() method for processing update events. Subscribe to PostUpdate instead
    -- of the usual Update so that physics simulation has already proceeded for the frame, and can
    -- accurately follow the object with the camera
    SubscribeToEvent("PostUpdate", "HandlePostUpdate")

    -- Subscribe to button actions
    SubscribeToEvent(connectButton, "Released", "HandleConnect")
    SubscribeToEvent(disconnectButton, "Released", "HandleDisconnect")
    SubscribeToEvent(startServerButton, "Released", "HandleStartServer")

    -- Subscribe to network events
    SubscribeToEvent("ServerConnected", "HandleConnectionStatus")
    SubscribeToEvent("ServerDisconnected", "HandleConnectionStatus")
    SubscribeToEvent("ConnectFailed", "HandleConnectionStatus")
    SubscribeToEvent("ClientConnected", "HandleClientConnected")
    SubscribeToEvent("ClientDisconnected", "HandleClientDisconnected")
    -- This is a custom event, sent from the server to the client. It tells the node ID of the object the client should control
    SubscribeToEvent("ClientObjectID", "HandleClientObjectID")
    -- Events sent between client & server (remote events) must be explicitly registered or else they are not allowed to be received
    network:RegisterRemoteEvent("ClientObjectID");
end

function CreateButton(text, width)
    local font = cache:GetResource("Font", "Fonts/Anonymous Pro.ttf")

    local button = buttonContainer:CreateChild("Button")
    button:SetStyleAuto()
    button:SetFixedWidth(width)

    local buttonText = button:CreateChild("Text")
    buttonText:SetFont(font, 12)
    buttonText:SetAlignment(HA_CENTER, VA_CENTER)
    buttonText:SetText(text)

    return button
end

function UpdateButtons()
    local serverConnection = network:GetServerConnection()
    local serverRunning = network.serverRunning

    -- Show and hide buttons so that eg. Connect and Disconnect are never shown at the same time
    connectButton.visible = serverConnection == nil and not serverRunning
    disconnectButton.visible = serverConnection ~= nil or serverRunning
    startServerButton.visible = serverConnection == nil and not serverRunning
    textEdit.visible = serverConnection == nil and not serverRunning
end

function CreateControllableObject()
    -- Create the scene node & visual representation. This will be a replicated object
    local ballNode = scene_:CreateChild("Ball")
    ballNode.position = Vector3(Random(40.0) - 20.0, 5.0, Random(40.0) - 20.0)
    ballNode:SetScale(0.5)
    local ballObject = ballNode:CreateComponent("StaticModel")
    ballObject.model = cache:GetResource("Model", "Models/Sphere.mdl")
    ballObject.material = cache:GetResource("Material", "Materials/StoneSmall.xml")

    -- Create the physics components
    local body = ballNode:CreateComponent("RigidBody")
    body.mass = 1.0
    body.friction = 1.0
    -- In addition to friction, use motion damping so that the ball can not accelerate limitlessly
    body.linearDamping = 0.5
    body.angularDamping = 0.5
    local shape = ballNode:CreateComponent("CollisionShape")
    shape:SetSphere(1.0)

    -- Create a random colored point light at the ball so that can see better where is going
    local light = ballNode:CreateComponent("Light")
    light.range = 3.0
    light.color = Color(0.5 + RandomInt(2) * 0.5, 0.5 + RandomInt(2) * 0.5, 0.5 + RandomInt(2) * 0.5)

    return ballNode
end

function MoveCamera()
    input.mouseVisible = input.mouseMode ~= MM_RELATIVE
    mouseDown = input:GetMouseButtonDown(MOUSEB_RIGHT)

    -- Override the MM_RELATIVE mouse grabbed settings, to allow interaction with UI
    input.mouseGrabbed = mouseDown

    -- Right mouse button controls mouse cursor visibility: hide when pressed
    ui.cursor.visible = not mouseDown

    -- Mouse sensitivity as degrees per pixel
    local MOUSE_SENSITIVITY = 0.1

    -- Use this frame's mouse motion to adjust camera node yaw and pitch. Clamp the pitch and only move the camera
    -- when the cursor is hidden
    if not ui.cursor.visible then
        local mouseMove = input.mouseMove
        yaw = yaw + MOUSE_SENSITIVITY * mouseMove.x
        pitch = pitch + MOUSE_SENSITIVITY * mouseMove.y
        pitch = Clamp(pitch, 1.0, 90.0)
    end

    -- Construct new orientation for the camera scene node from yaw and pitch. Roll is fixed to zero
    cameraNode.rotation = Quaternion(pitch, yaw, 0.0)

    -- Only move the camera / show instructions if we have a controllable object
    local showInstructions = false
    if clientObjectID ~= 0 then
        local ballNode = scene_:GetNode(clientObjectID)
        if ballNode ~= nil then
            local CAMERA_DISTANCE = 5.0

            -- Move camera some distance away from the ball
            cameraNode.position = ballNode.position + cameraNode.rotation * Vector3(0.0, 0.0, -1.0) * CAMERA_DISTANCE
            showInstructions = true
        end
    end

    instructionsText.visible = showInstructions
end

function HandlePostUpdate(eventType, eventData)

    -- We only rotate the camera according to mouse movement since last frame, so do not need the time step
    MoveCamera()
end

function HandlePhysicsPreStep(eventType, eventData)

    -- This function is different on the client and server. The client collects controls (WASD controls + yaw angle)
    -- and sets them to its server connection object, so that they will be sent to the server automatically at a
    -- fixed rate, by default 30 FPS. The server will actually apply the controls (authoritative simulation.)
    local serverConnection = network:GetServerConnection()

    -- Client: collect controls
    if serverConnection ~= nil then
        local controls = Controls()

        -- Copy mouse yaw
        controls.yaw = yaw

        -- Only apply WASD controls if there is no focused UI element
        if ui.focusElement == nil then
            controls:Set(CTRL_FORWARD, input:GetKeyDown(KEY_W))
            controls:Set(CTRL_BACK, input:GetKeyDown(KEY_S))
            controls:Set(CTRL_LEFT, input:GetKeyDown(KEY_A))
            controls:Set(CTRL_RIGHT, input:GetKeyDown(KEY_D))
        end

        serverConnection.controls = controls
        -- In case the server wants to do position-based interest management using the NetworkPriority components, we should also
        -- tell it our observer (camera) position. In this sample it is not in use, but eg. the NinjaSnowWar game uses it
        serverConnection.position = cameraNode.position
    -- Server: apply controls to client objects
    elseif network.serverRunning then
        for i, v in ipairs(clients) do
            local connection = v.connection
            -- Get the object this connection is controlling
            local ballNode = v.object

            local body = ballNode:GetComponent("RigidBody")

            -- Torque is relative to the forward vector
            local rotation = Quaternion(0.0, connection.controls.yaw, 0.0)

            local MOVE_TORQUE = 3.0

            -- Movement torque is applied before each simulation step, which happen at 60 FPS. This makes the simulation
            -- independent from rendering framerate. We could also apply forces (which would enable in-air control),
            -- but want to emphasize that it's a ball which should only control its motion by rolling along the ground
            if connection.controls:IsDown(CTRL_FORWARD) then
                body:ApplyTorque(rotation * Vector3(1.0, 0.0, 0.0) * MOVE_TORQUE)
            end
            if connection.controls:IsDown(CTRL_BACK) then
                body:ApplyTorque(rotation * Vector3(-1.0, 0.0, 0.0) * MOVE_TORQUE)
            end
            if connection.controls:IsDown(CTRL_LEFT) then
                body:ApplyTorque(rotation * Vector3(0.0, 0.0, 1.0) * MOVE_TORQUE)
            end
            if connection.controls:IsDown(CTRL_RIGHT) then
                body:ApplyTorque(rotation * Vector3(0.0, 0.0, -1.0) * MOVE_TORQUE)
            end
        end
    end
end

function HandleConnect(eventType, eventData)
    local address = textEdit.text
    if address == "" then
        address = "localhost" -- Use localhost to connect if nothing else specified
    end

    -- Connect to server, specify scene to use as a client for replication
    clientObjectID = 0 -- Reset own object ID from possible previous connection
    network:Connect(address, SERVER_PORT, scene_)

    UpdateButtons()
end

function HandleDisconnect(eventType, eventData)
    local serverConnection = network.serverConnection
    -- If we were connected to server, disconnect. Or if we were running a server, stop it. In both cases clear the
    -- scene of all replicated content, but let the local nodes & components (the static world + camera) stay
    if serverConnection ~= nil then
        serverConnection:Disconnect()
        scene_:Clear(true, false)
        clientObjectID = 0
    -- Or if we were running a server, stop it
    elseif network.serverRunning then
        network:StopServer()
        scene_:Clear(true, false)
    end

    UpdateButtons()
end

function HandleStartServer(eventType, eventData)
    network:StartServer(SERVER_PORT)

    UpdateButtons()
end

function HandleConnectionStatus(eventType, eventData)
    UpdateButtons()
end

function HandleClientConnected(eventType, eventData)
    -- When a client connects, assign to scene to begin scene replication
    local newConnection = eventData["Connection"]:GetPtr("Connection")
    newConnection.scene = scene_

    -- Then create a controllable object for that client
    local newObject = CreateControllableObject()
    local newClient = {}
    newClient.connection = newConnection
    newClient.object = newObject
    table.insert(clients, newClient)

    -- Finally send the object's node ID using a remote event
    local remoteEventData = VariantMap()
    remoteEventData:SetInt("ID", newObject.ID)
    newConnection:SendRemoteEvent("ClientObjectID", true, remoteEventData)
end

function HandleClientDisconnected(eventType, eventData)
    -- When a client disconnects, remove the controlled object
    local connection = eventData["Connection"]:GetPtr("Connection")
    for i, v in ipairs(clients) do
        if v.connection == connection then
            v.object:Remove()
            table.remove(clients, i)
            break
        end
    end
end

function HandleClientObjectID(eventType, eventData)
    clientObjectID = eventData["ID"]:GetUInt()
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
