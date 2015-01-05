-- Navigation example.
-- This sample demonstrates:
--     - Generating a navigation mesh into the scene
--     - Performing path queries to the navigation mesh
--     - Rebuilding the navigation mesh partially when adding or removing objects
--     - Visualizing custom debug geometry
--     - Raycasting drawable components
--     - Making a node follow the Detour path

require "LuaScripts/Utilities/Sample"

local endPos = nil
local currentPath = {}

function Start()
    -- Execute the common startup for samples
    SampleStart()

    -- Create the scene content
    CreateScene()

    -- Create the UI content
    CreateUI()

    -- Setup the viewport for displaying the scene
    SetupViewport()

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

    -- Create some mushrooms
    local NUM_MUSHROOMS = 100
    for i = 1, NUM_MUSHROOMS do
        CreateMushroom(Vector3(Random(90.0) - 45.0, 0.0, Random(90.0) - 45.0))
    end

    -- Create randomly sized boxes. If boxes are big enough, make them occluders. Occluders will be software rasterized before
    -- rendering to a low-resolution depth-only buffer to test the objects in the view frustum for visibility
    local NUM_BOXES = 20
    for i = 1, NUM_BOXES do
        local boxNode = scene_:CreateChild("Box")
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

    -- Create Jack node that will follow the path
    jackNode = scene_:CreateChild("Jack")
    jackNode.position = Vector3(-5, 0, 20)
    local modelObject = jackNode:CreateComponent("AnimatedModel")
    modelObject.model = cache:GetResource("Model", "Models/Jack.mdl")
    modelObject.material = cache:GetResource("Material", "Materials/Jack.xml")
    modelObject.castShadows = true

    -- Create a NavigationMesh component to the scene root
    local navMesh = scene_:CreateComponent("NavigationMesh")
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

    -- Create the camera. Limit far clip distance to match the fog
    cameraNode = scene_:CreateChild("Camera")
    local camera = cameraNode:CreateComponent("Camera")
    camera.farClip = 300.0

    -- Set an initial position for the camera scene node above the plane
    cameraNode.position = Vector3(0.0, 5.0, 0.0)
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
    local instructionText = ui.root:CreateChild("Text")
    instructionText.text = "Use WASD keys to move, RMB to rotate view\n"..
        "LMB to set destination, SHIFT+LMB to teleport\n"..
        "MMB to add or remove obstacles\n"..
        "Space to toggle debug geometry"
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
    -- Right mouse button controls mouse cursor visibility: hide when pressed
    ui.cursor.visible = not input:GetMouseButtonDown(MOUSEB_RIGHT)

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
    -- Set destination or teleport with left mouse button
    if input:GetMouseButtonPress(MOUSEB_LEFT) then
        SetPathPoint()
    end
    -- Add or remove objects with middle mouse button, then rebuild navigation mesh partially
    if input:GetMouseButtonPress(MOUSEB_MIDDLE) then
        AddOrRemoveObject()
    end
    -- Toggle debug geometry with space
    if input:GetKeyPress(KEY_SPACE) then
        drawDebug = not drawDebug
    end
end

function SetPathPoint()
    local result, hitPos, hitDrawable = Raycast(250.0)
    local navMesh = scene_:GetComponent("NavigationMesh")
    if result then
        local pathPos = navMesh:FindNearestPoint(hitPos, Vector3.ONE)

        if input:GetQualifierDown(QUAL_SHIFT) then
            -- Teleport
            currentPath = {}
            jackNode:LookAt(Vector3(pathPos.x, jackNode.position.y, pathPos.z), Vector3(0.0, 1.0, 0.0))
            jackNode.position = pathPos
        else
            -- Calculate path from Jack's current position to the end point
            endPos = pathPos
            currentPath = navMesh:FindPath(jackNode.position, endPos)
        end
    end
end

function AddOrRemoveObject()
    -- Raycast and check if we hit a mushroom node. If yes, remove it, if no, create a new one
    local result, hitPos, hitDrawable = Raycast(250.0)
    if result then
        -- The part of the navigation mesh we must update, which is the world bounding box of the associated
        -- drawable component
        local updateBox = nil

        local hitNode = hitDrawable:GetNode()
        if hitNode.name == "Mushroom" then
            updateBox = hitDrawable.worldBoundingBox
            hitNode:Remove()
        else
            local newNode = CreateMushroom(hitPos)
            local newObject = newNode:GetComponent("StaticModel")
            updateBox = newObject.worldBoundingBox
        end

        -- Rebuild part of the navigation mesh, then recalculate path if applicable
        local navMesh = scene_:GetComponent("NavigationMesh")
        navMesh:Build(updateBox)
        if table.maxn(currentPath) > 0 then
            currentPath = navMesh:FindPath(jackNode.position, endPos)
        end
    end
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
    return mushroomNode
end

function Raycast(maxDistance)
    local hitPos = nil
    local hitDrawable = nil

    local pos = ui.cursorPosition
    -- Check the cursor is visible and there is no UI element in front of the cursor
    if (not ui.cursor.visible) or (ui:GetElementAt(pos, true) ~= nil) then
        return false, nil, nil
    end

    local camera = cameraNode:GetComponent("Camera")
    local cameraRay = camera:GetScreenRay(pos.x / graphics.width, pos.y / graphics.height)
    -- Pick only geometry objects, not eg. zones or lights, only get the first (closest) hit
    local octree = scene_:GetComponent("Octree")
    local result = octree:RaycastSingle(cameraRay, RAY_TRIANGLE, maxDistance, DRAWABLE_GEOMETRY)
    if result.drawable ~= nil then
        -- Calculate hit position in world space
        hitPos = cameraRay.origin + cameraRay.direction * result.distance
        hitDrawable = result.drawable
        return true, hitPos, hitDrawable
    end

    return false, nil, nil
end

function HandleUpdate(eventType, eventData)
    -- Take the frame time step, which is stored as a float
    local timeStep = eventData:GetFloat("TimeStep")

    -- Move the camera, scale movement with time step
    MoveCamera(timeStep)

    -- Make Jack follow the Detour path
    FollowPath(timeStep)
end

function FollowPath(timeStep)
    if table.maxn(currentPath) > 0 then
        local nextWaypoint = currentPath[1] -- NB: currentPath[1] is the next waypoint in order

        -- Rotate Jack toward next waypoint to reach and move. Check for not overshooting the target
        local move = 5 * timeStep
        local distance = (jackNode.position - nextWaypoint):Length()
        if move > distance then
            move = distance
        end

        jackNode:LookAt(nextWaypoint, Vector3(0.0, 1.0, 0.0))
        jackNode:Translate(Vector3(0.0, 0.0, 1.0) * move)

        -- Remove waypoint if reached it
        if distance < 0.1 then
            table.remove(currentPath, 1)
        end
    end
end

function HandlePostRenderUpdate(eventType, eventData)
    -- If draw debug mode is enabled, draw navigation mesh debug geometry
    if drawDebug then
        local navMesh = scene_:GetComponent("NavigationMesh")
        navMesh:DrawDebugGeometry(true)
    end

    -- Visualize the start and end points and the last calculated path
    local size = table.maxn(currentPath)
    if size > 0 then
        local debug = scene_:GetComponent("DebugRenderer")
        debug:AddBoundingBox(BoundingBox(endPos - Vector3(0.1, 0.1, 0.1), endPos + Vector3(0.1, 0.1, 0.1)), Color(1.0, 1.0, 1.0))

        -- Draw the path with a small upward bias so that it does not clip into the surfaces
        local bias = Vector3(0.0, 0.05, 0.0)
        debug:AddLine(jackNode.position + bias, currentPath[1] + bias, Color(1.0, 1.0, 1.0))

        if size > 1 then
            for i = 1, size - 1 do
                debug:AddLine(currentPath[i] + bias, currentPath[i + 1] + bias, Color(1.0, 1.0, 1.0))
            end
        end
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
        "                <attribute name=\"Text\" value=\"Teleport\" />" ..
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
