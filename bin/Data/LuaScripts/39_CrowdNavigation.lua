-- CrowdNavigation example.
-- This sample demonstrates:
--     - Generating a dynamic navigation mesh into the scene
--     - Performing path queries to the navigation mesh
--     - Adding and removing obstacles/agents at runtime
--     - Raycasting drawable components
--     - Crowd movement management
--     - Accessing crowd agents with the crowd manager
--     - Using off-mesh connections to make boxes climbable
--     - Using agents to simulate moving obstacles

require "LuaScripts/Utilities/Sample"

local INSTRUCTION = "instructionText"

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

    -- Hook up to the frame update and render post-update events
    SubscribeToEvents()
end

function CreateScene()
    scene_ = Scene()
    -- Create octree, use default volume (-1000, -1000, -1000) to (1000, 1000, 1000)
    -- Also create a DebugRenderer component so that we can draw debug geometry
    scene_:CreateComponent("Octree")
    scene_:CreateComponent("DebugRenderer")

    -- Create scene node & StaticModel component for showing a static plane
    local planeNode = scene_:CreateChild("Plane")
    planeNode.scale = Vector3(100.0, 1.0, 100.0)
    local planeObject = planeNode:CreateComponent("StaticModel")
    planeObject.model = cache:GetResource("Model", "Models/Plane.mdl")
    planeObject.material = cache:GetResource("Material", "Materials/StoneTiled.xml")

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

    -- Create randomly sized boxes. If boxes are big enough, make them occluders. Occluders will be software rasterized before
    -- rendering to a low-resolution depth-only buffer to test the objects in the view frustum for visibility
    local boxGroup = scene_:CreateChild("Boxes")
    for i = 1, 20 do
        local boxNode = boxGroup:CreateChild("Box")
        local size = 1.0 + Random(10.0)
        boxNode.position = Vector3(Random(80.0) - 40.0, size * 0.5, Random(80.0) - 40.0)
        boxNode:SetScale(size)
        local boxObject = boxNode:CreateComponent("StaticModel")
        boxObject.model = cache:GetResource("Model", "Models/Box.mdl")
        boxObject.material = cache:GetResource("Material", "Materials/Stone.xml")
        boxObject.castShadows = true
        if size >= 3.0 then
            boxObject.occluder = true
        end
    end

    -- Create a DynamicNavigationMesh component to the scene root
    local navMesh = scene_:CreateComponent("DynamicNavigationMesh")
    -- Enable drawing debug geometry for obstacles and off-mesh connections
    navMesh.drawObstacles = true
    navMesh.drawOffMeshConnections = true
    -- Set the agent height large enough to exclude the layers under boxes
    navMesh.agentHeight = 10
    -- Set nav mesh cell height to minimum (allows agents to be grounded)
    navMesh.cellHeight = 0.05
    -- Create a Navigable component to the scene root. This tags all of the geometry in the scene as being part of the
    -- navigation mesh. By default this is recursive, but the recursion could be turned off from Navigable
    scene_:CreateComponent("Navigable")
    -- Add padding to the navigation mesh in Y-direction so that we can add objects on top of the tallest boxes
    -- in the scene and still update the mesh correctly
    navMesh.padding = Vector3(0.0, 10.0, 0.0)
    -- Now build the navigation geometry. This will take some time. Note that the navigation mesh will prefer to use
    -- physics geometry from the scene nodes, as it often is simpler, but if it can not find any (like in this example)
    -- it will use renderable geometry instead
    navMesh:Build()

    -- Create an off-mesh connection for each box to make it climbable (tiny boxes are skipped).
    -- Note that OffMeshConnections must be added before building the navMesh, but as we are adding Obstacles next, tiles will be automatically rebuilt.
    -- Creating connections post-build here allows us to use FindNearestPoint() to procedurally set accurate positions for the connection
    CreateBoxOffMeshConnections(navMesh, boxGroup)

    -- Create some mushrooms as obstacles. Note that obstacles are non-walkable areas
    for i = 1, 100 do
        CreateMushroom(Vector3(Random(90.0) - 45.0, 0.0, Random(90.0) - 45.0))
    end

    -- Create a CrowdManager component to the scene root (mandatory for crowd agents)
    local crowdManager = scene_:CreateComponent("CrowdManager")
    local params = crowdManager:GetObstacleAvoidanceParams(0)
    -- Set the params to "High (66)" setting
    params.velBias = 0.5
    params.adaptiveDivs = 7
    params.adaptiveRings = 3
    params.adaptiveDepth = 3
    crowdManager:SetObstacleAvoidanceParams(0, params)

    -- Create some movable barrels. We create them as crowd agents, as for moving entities it is less expensive and more convenient than using obstacles
    CreateMovingBarrels(navMesh)

    -- Create Jack node as crowd agent
    SpawnJack(Vector3(-5, 0, 20), scene_:CreateChild("Jacks"))

    -- Create the camera. Limit far clip distance to match the fog. Note: now we actually create the camera node outside
    -- the scene, because we want it to be unaffected by scene load / save
    cameraNode = Node()
    local camera = cameraNode:CreateComponent("Camera")
    camera.farClip = 300.0

    -- Set an initial position for the camera scene node above the plane and looking down
    cameraNode.position = Vector3(0.0, 50.0, 0.0)
    pitch = 80.0
    cameraNode.rotation = Quaternion(pitch, yaw, 0.0)
end

function CreateUI()
    -- Create a Cursor UI element because we want to be able to hide and show it at will. When hidden, the mouse cursor will
    -- control the camera, and when visible, it will point the raycast target
    local style = cache:GetResource("XMLFile", "UI/DefaultStyle.xml")
    local cursor = Cursor:new()
    cursor:SetStyleAuto(style)
    ui.cursor = cursor
    -- Set starting position of the cursor at the rendering window center
    cursor:SetPosition(graphics.width / 2, graphics.height / 2)

    -- Construct new Text object, set string to display and font to use
    local instructionText = ui.root:CreateChild("Text", INSTRUCTION)
    instructionText.text = "Use WASD keys to move, RMB to rotate view\n"..
        "LMB to set destination, SHIFT+LMB to spawn a Jack\n"..
        "MMB or O key to add obstacles or remove obstacles/agents\n"..
        "F5 to save scene, F7 to load\n"..
        "Space to toggle debug geometry\n"..
        "F12 to toggle this instruction text"
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

    -- Subscribe HandlePostRenderUpdate() function for processing the post-render update event, during which we request debug geometry
    SubscribeToEvent("PostRenderUpdate", "HandlePostRenderUpdate")

    -- Subscribe HandleCrowdAgentFailure() function for resolving invalidation issues with agents, during which we
    -- use a larger extents for finding a point on the navmesh to fix the agent's position
    SubscribeToEvent("CrowdAgentFailure", "HandleCrowdAgentFailure")

    -- Subscribe HandleCrowdAgentReposition() function for controlling the animation
    SubscribeToEvent("CrowdAgentReposition", "HandleCrowdAgentReposition")

    -- Subscribe HandleCrowdAgentFormation() function for positioning agent into a formation
    SubscribeToEvent("CrowdAgentFormation", "HandleCrowdAgentFormation")
end

function SpawnJack(pos, jackGroup)
    local jackNode = jackGroup:CreateChild("Jack")
    jackNode.position = pos
    local modelObject = jackNode:CreateComponent("AnimatedModel")
    modelObject.model = cache:GetResource("Model", "Models/Jack.mdl")
    modelObject.material = cache:GetResource("Material", "Materials/Jack.xml")
    modelObject.castShadows = true
    jackNode:CreateComponent("AnimationController")

    -- Create a CrowdAgent component and set its height and realistic max speed/acceleration. Use default radius
    local agent = jackNode:CreateComponent("CrowdAgent")
    agent.height = 2.0
    agent.maxSpeed = 3.0
    agent.maxAccel = 5.0
end

function CreateMushroom(pos)
    local mushroomNode = scene_:CreateChild("Mushroom")
    mushroomNode.position = pos
    mushroomNode.rotation = Quaternion(0.0, Random(360.0), 0.0)
    mushroomNode:SetScale(2.0 + Random(0.5))
    local mushroomObject = mushroomNode:CreateComponent("StaticModel")
    mushroomObject.model = cache:GetResource("Model", "Models/Mushroom.mdl")
    mushroomObject.material = cache:GetResource("Material", "Materials/Mushroom.xml")
    mushroomObject.castShadows = true

    -- Create the navigation Obstacle component and set its height & radius proportional to scale
    local obstacle = mushroomNode:CreateComponent("Obstacle")
    obstacle.radius = mushroomNode.scale.x
    obstacle.height = mushroomNode.scale.y
end

function CreateBoxOffMeshConnections(navMesh, boxGroup)
    boxes = boxGroup:GetChildren()
    for i, box in ipairs(boxes) do
        local boxPos = box.position
        local boxHalfSize = box.scale.x / 2

        -- Create 2 empty nodes for the start & end points of the connection. Note that order matters only when using one-way/unidirectional connection.
        local connectionStart = box:CreateChild("ConnectionStart")
        connectionStart.worldPosition = navMesh:FindNearestPoint(boxPos + Vector3(boxHalfSize, -boxHalfSize, 0)) -- Base of box
        local connectionEnd = connectionStart:CreateChild("ConnectionEnd")
        connectionEnd.worldPosition = navMesh:FindNearestPoint(boxPos + Vector3(boxHalfSize, boxHalfSize, 0)) -- Top of box

        -- Create the OffMeshConnection component to one node and link the other node
        local connection = connectionStart:CreateComponent("OffMeshConnection")
        connection.endPoint = connectionEnd
    end
end

function CreateMovingBarrels(navMesh)
    local barrel = scene_:CreateChild("Barrel")
    local model = barrel:CreateComponent("StaticModel")
    model.model = cache:GetResource("Model", "Models/Cylinder.mdl")
    model.material = cache:GetResource("Material", "Materials/StoneTiled.xml")
    model.material:SetTexture(TU_DIFFUSE, cache:GetResource("Texture2D", "Textures/TerrainDetail2.dds"))
    model.castShadows = true
    for i = 1, 20 do
        local clone = barrel:Clone()
        local size = 0.5 + Random(1)
        clone.scale = Vector3(size / 1.5, size * 2, size / 1.5)
        clone.position = navMesh:FindNearestPoint(Vector3(Random(80.0) - 40.0, size * 0.5 , Random(80.0) - 40.0))
        local agent = clone:CreateComponent("CrowdAgent")
        agent.radius = clone.scale.x * 0.5
        agent.height = size
        agent.navigationQuality = NAVIGATIONQUALITY_LOW
    end
    barrel:Remove()
end

function SetPathPoint(spawning)
    local hitPos, hitDrawable = Raycast(250.0)

    if hitDrawable then
        local navMesh = scene_:GetComponent("DynamicNavigationMesh")
        local pathPos = navMesh:FindNearestPoint(hitPos, Vector3.ONE)
        local jackGroup = scene_:GetChild("Jacks")
        if spawning then
            -- Spawn a jack at the target position
            SpawnJack(pathPos, jackGroup)
        else
            -- Set crowd agents target position
            scene_:GetComponent("CrowdManager"):SetCrowdTarget(pathPos, jackGroup)
        end
    end
end

function AddOrRemoveObject()
    -- Raycast and check if we hit a mushroom node. If yes, remove it, if no, create a new one
    local hitPos, hitDrawable = Raycast(250.0)
    if hitDrawable then

        local hitNode = hitDrawable.node
        if hitNode.name == "Mushroom" then
            hitNode:Remove()
        elseif hitNode.name == "Jack" then
            hitNode:Remove()
        else
            CreateMushroom(hitPos)
        end
    end
end

function Raycast(maxDistance)
    local pos = ui.cursorPosition
    -- Check the cursor is visible and there is no UI element in front of the cursor
    if (not ui.cursor.visible) or (ui:GetElementAt(pos, true) ~= nil) then
        return nil, nil
    end

    local camera = cameraNode:GetComponent("Camera")
    local cameraRay = camera:GetScreenRay(pos.x / graphics.width, pos.y / graphics.height)
    -- Pick only geometry objects, not eg. zones or lights, only get the first (closest) hit
    local octree = scene_:GetComponent("Octree")
    local result = octree:RaycastSingle(cameraRay, RAY_TRIANGLE, maxDistance, DRAWABLE_GEOMETRY)
    if result.drawable ~= nil then
        return result.position, result.drawable
    end

    return nil, nil
end

function MoveCamera(timeStep)
    input.mouseVisible = input.mouseMode ~= MM_RELATIVE
    mouseDown = input:GetMouseButtonDown(MOUSEB_RIGHT)

    -- Override the MM_RELATIVE mouse grabbed settings, to allow interaction with UI
    input.mouseGrabbed = mouseDown

    -- Right mouse button controls mouse cursor visibility: hide when pressed
    ui.cursor.visible = not mouseDown

    -- Do not move if the UI has a focused element (the console)
    if ui.focusElement ~= nil then
        return
    end

    -- Movement speed as world units per second
    local MOVE_SPEED = 20.0
    -- Mouse sensitivity as degrees per pixel
    local MOUSE_SENSITIVITY = 0.1

    -- Use this frame's mouse motion to adjust camera node yaw and pitch. Clamp the pitch between -90 and 90 degrees
    -- Only move the camera when the cursor is hidden
    if not ui.cursor.visible then
        local mouseMove = input.mouseMove
        yaw = yaw + MOUSE_SENSITIVITY * mouseMove.x
        pitch = pitch + MOUSE_SENSITIVITY * mouseMove.y
        pitch = Clamp(pitch, -90.0, 90.0)

        -- Construct new orientation for the camera scene node from yaw and pitch. Roll is fixed to zero
        cameraNode.rotation = Quaternion(pitch, yaw, 0.0)
    end

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

    -- Set destination or spawn a jack with left mouse button
    if input:GetMouseButtonPress(MOUSEB_LEFT) then
        SetPathPoint(input:GetQualifierDown(QUAL_SHIFT))
    -- Add new obstacle or remove existing obstacle/agent with middle mouse button
    elseif input:GetMouseButtonPress(MOUSEB_MIDDLE) or input:GetKeyPress(KEY_O) then
        AddOrRemoveObject()
    end

    -- Check for loading/saving the scene from/to the file Data/Scenes/CrowdNavigation.xml relative to the executable directory
    if input:GetKeyPress(KEY_F5) then
        scene_:SaveXML(fileSystem:GetProgramDir().."Data/Scenes/CrowdNavigation.xml")
    elseif input:GetKeyPress(KEY_F7) then
        scene_:LoadXML(fileSystem:GetProgramDir().."Data/Scenes/CrowdNavigation.xml")

    -- Toggle debug geometry with space
    elseif input:GetKeyPress(KEY_SPACE) then
        drawDebug = not drawDebug

    -- Toggle instruction text with F12
    elseif input:GetKeyPress(KEY_F12) then
        instruction = ui.root:GetChild(INSTRUCTION)
        instruction.visible = not instruction.visible
    end
end

function HandleUpdate(eventType, eventData)
    -- Take the frame time step, which is stored as a float
    local timeStep = eventData["TimeStep"]:GetFloat()

    -- Move the camera, scale movement with time step
    MoveCamera(timeStep)
end

function HandlePostRenderUpdate(eventType, eventData)
    if drawDebug then
        -- Visualize navigation mesh, obstacles and off-mesh connections
        scene_:GetComponent("DynamicNavigationMesh"):DrawDebugGeometry(true)
        -- Visualize agents' path and position to reach
        scene_:GetComponent("CrowdManager"):DrawDebugGeometry(true)
    end
end

function HandleCrowdAgentFailure(eventType, eventData)
    local node = eventData["Node"]:GetPtr("Node")
    local agentState = eventData["CrowdAgentState"]:GetInt()

    -- If the agent's state is invalid, likely from spawning on the side of a box, find a point in a larger area
    if agentState == CA_STATE_INVALID then
        -- Get a point on the navmesh using more generous extents
        local newPos = scene_:GetComponent("DynamicNavigationMesh"):FindNearestPoint(node.position, Vector3(5, 5, 5))
        -- Set the new node position, CrowdAgent component will automatically reset the state of the agent
        node.position = newPos
    end
end

function HandleCrowdAgentReposition(eventType, eventData)
    local WALKING_ANI = "Models/Jack_Walk.ani"

    local node = eventData["Node"]:GetPtr("Node")
    local agent = eventData["CrowdAgent"]:GetPtr("CrowdAgent")
    local velocity = eventData["Velocity"]:GetVector3()
    local timeStep = eventData["TimeStep"]:GetFloat()

    -- Only Jack agent has animation controller
    local animCtrl = node:GetComponent("AnimationController")
    if animCtrl ~= nil then
        local speed = velocity:Length()
        if animCtrl:IsPlaying(WALKING_ANI) then
            local speedRatio = speed / agent.maxSpeed
            -- Face the direction of its velocity but moderate the turning speed based on the speed ratio and timeStep
            node.rotation = node.rotation:Slerp(Quaternion(Vector3.FORWARD, velocity), 10.0 * timeStep * speedRatio)
            -- Throttle the animation speed based on agent speed ratio (ratio = 1 is full throttle)
            animCtrl:SetSpeed(WALKING_ANI, speedRatio * 1.5)
        else
            animCtrl:Play(WALKING_ANI, 0, true, 0.1)
        end

        -- If speed is too low then stop the animation
        if speed < agent.radius then
            animCtrl:Stop(WALKING_ANI, 0.5)
        end
    end
end

function HandleCrowdAgentFormation(eventType, eventData)
    local index = eventData["Index"]:GetUInt()
    local size = eventData["Size"]:GetUInt()
    local position = eventData["Position"]:GetVector3()

    -- The first agent will always move to the exact position, all other agents will select a random point nearby
    if index > 0 then
        local crowdManager = GetEventSender()
        local agent = eventData["CrowdAgent"]:GetPtr("CrowdAgent")
        eventData["Position"] = crowdManager:GetRandomPointInCircle(position, agent.radius, agent.queryFilterType)
    end
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
        "                <attribute name=\"Text\" value=\"Spawn\" />" ..
        "            </element>" ..
        "            <element type=\"Text\">" ..
        "                <attribute name=\"Name\" value=\"KeyBinding\" />" ..
        "                <attribute name=\"Text\" value=\"LSHIFT\" />" ..
        "            </element>" ..
        "            <element type=\"Text\">" ..
        "                <attribute name=\"Name\" value=\"MouseButtonBinding\" />" ..
        "                <attribute name=\"Text\" value=\"LEFT\" />" ..
        "            </element>" ..
        "        </element>" ..
        "        <element type=\"Button\">" ..
        "            <attribute name=\"Name\" value=\"Button4\" />" ..
        "            <attribute name=\"Position\" value=\"-120 -12\" />" ..
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
        "                <attribute name=\"Text\" value=\"Obstacles\" />" ..
        "            </element>" ..
        "            <element type=\"Text\">" ..
        "                <attribute name=\"Name\" value=\"MouseButtonBinding\" />" ..
        "                <attribute name=\"Text\" value=\"MIDDLE\" />" ..
        "            </element>" ..
        "        </element>" ..
        "    </add>" ..
        "    <remove sel=\"/element/element[./attribute[@name='Name' and @value='Button0']]/attribute[@name='Is Visible']\" />" ..
        "    <replace sel=\"/element/element[./attribute[@name='Name' and @value='Button0']]/element[./attribute[@name='Name' and @value='Label']]/attribute[@name='Text']/@value\">Set</replace>" ..
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
