-- Billboard example.
-- This sample demonstrates:
--     - Populating a 3D scene with billboard sets and several shadow casting spotlights
--     - Parenting scene nodes to allow more intuitive creation of groups of objects
--     - Examining rendering performance with a somewhat large object and light count

require "LuaScripts/Utilities/Sample"

local lightNodes = {}
local billboardNodes = {}

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
    -- Also create a DebugRenderer component so that we can draw debug geometry
    scene_:CreateComponent("Octree")
    scene_:CreateComponent("DebugRenderer")

    -- Create a Zone component for ambient lighting & fog control
    local zoneNode = scene_:CreateChild("Zone")
    local zone = zoneNode:CreateComponent("Zone")
    zone.boundingBox = BoundingBox(-1000.0, 1000.0)
    zone.ambientColor = Color(0.1, 0.1, 0.1)
    zone.fogStart = 100.0
    zone.fogEnd = 300.0

    -- Create a directional light without shadows
    local lightNode = scene_:CreateChild("DirectionalLight")
    lightNode.direction = Vector3(0.5, -1.0, 0.5)
    local light = lightNode:CreateComponent("Light")
    light.lightType = LIGHT_DIRECTIONAL
    light.color = Color(0.2, 0.2, 0.2)
    light.specularIntensity = 1.0

    -- Create a "floor" consisting of several tiles
    for y = -5, 5 do
        for x = -5, 5 do
            local floorNode = scene_:CreateChild("FloorTile")
            floorNode.position = Vector3(x * 20.5, -0.5, y * 20.5)
            floorNode.scale = Vector3(20.0, 1.0, 20.0)
            local floorObject = floorNode:CreateComponent("StaticModel")
            floorObject.model = cache:GetResource("Model", "Models/Box.mdl")
            floorObject.material = cache:GetResource("Material", "Materials/Stone.xml")
        end
    end

    -- Create groups of mushrooms, which act as shadow casters
    local NUM_MUSHROOMGROUPS = 25
    local NUM_MUSHROOMS = 25

    for i = 1, NUM_MUSHROOMGROUPS do
        -- First create a scene node for the group. The individual mushrooms nodes will be created as children
        local groupNode = scene_:CreateChild("MushroomGroup")
        groupNode.position = Vector3(Random(190.0) - 95.0, 0.0, Random(190.0) - 95.0)

        for j = 1, NUM_MUSHROOMS do
            local mushroomNode = groupNode:CreateChild("Mushroom")
            mushroomNode.position = Vector3(Random(25.0) - 12.5, 0.0, Random(25.0) - 12.5)
            mushroomNode.rotation = Quaternion(0.0, Random() * 360.0, 0.0)
            mushroomNode:SetScale(1.0 + Random() * 4.0)
            local mushroomObject = mushroomNode:CreateComponent("StaticModel")
            mushroomObject.model = cache:GetResource("Model", "Models/Mushroom.mdl")
            mushroomObject.material = cache:GetResource("Material", "Materials/Mushroom.xml")
            mushroomObject.castShadows = true
        end
    end

    -- Create billboard sets (floating smoke)
    local NUM_BILLBOARDNODES = 25
    local NUM_BILLBOARDS = 10

    for i = 1, NUM_BILLBOARDNODES do
        local smokeNode = scene_:CreateChild("Smoke")
        smokeNode.position = Vector3(Random(200.0) - 100.0, Random(20.0) + 10.0, Random(200.0) - 100.0)

        local billboardObject = smokeNode:CreateComponent("BillboardSet")
        billboardObject.numBillboards = NUM_BILLBOARDS
        billboardObject.material = cache:GetResource("Material", "Materials/LitSmoke.xml")
        billboardObject.sorted = true

        for j = 1, NUM_BILLBOARDS do
            local bb = billboardObject:GetBillboard(j - 1)
            bb.position = Vector3(Random(12.0) - 6.0, Random(8.0) - 4.0, Random(12.0) - 6.0)
            bb.size = Vector2(Random(2.0) + 3.0, Random(2.0) + 3.0)
            bb.rotation = Random() * 360.0
            bb.enabled = true
        end

        -- After modifying the billboards, they need to be "commited" so that the BillboardSet updates its internals
        billboardObject:Commit()

        table.insert(billboardNodes, smokeNode)
    end

    -- Create shadow casting spotlights
    local NUM_LIGHTS = 9

    for i = 0, NUM_LIGHTS - 1 do
        local lightNode = scene_:CreateChild("SpotLight")
        local light = lightNode:CreateComponent("Light")

        local angle = 0.0

        local position = Vector3((i % 3) * 60.0 - 60.0, 45.0, math.floor(i / 3) * 60.0 - 60.0)
        local color = Color(((i + 1) % 2) * 0.5 + 0.5, (math.floor((i + 1) / 2) % 2) * 0.5 + 0.5, (math.floor((i + 1) / 4) % 2) * 0.5 + 0.5)

        lightNode.position = position
        lightNode.direction = Vector3(math.sin(M_DEGTORAD * angle), -1.5, math.cos(M_DEGTORAD * angle))

        light.lightType = LIGHT_SPOT
        light.range = 90.0
        light.rampTexture = cache:GetResource("Texture2D", "Textures/RampExtreme.png")
        light.fov = 45.0
        light.color = color
        light.specularIntensity = 1.0
        light.castShadows = true
        light.shadowBias = BiasParameters(0.00002, 0.0)

        -- Configure shadow fading for the lights. When they are far away enough, the lights eventually become unshadowed for
        -- better GPU performance. Note that we could also set the maximum distance for each object to cast shadows
        light.shadowFadeDistance = 100.0 -- Fade start distance
        light.shadowDistance = 125.0 -- Fade end distance, shadows are disabled
        -- Set half resolution for the shadow maps for increased performance
        light.shadowResolution = 0.5
        -- The spot lights will not have anything near them, so move the near plane of the shadow camera farther
        -- for better shadow depth resolution
        light.shadowNearFarRatio = 0.01

        table.insert(lightNodes, lightNode)
    end

    -- Create the camera. Limit far clip distance to match the fog
    cameraNode = scene_:CreateChild("Camera")
    local camera = cameraNode:CreateComponent("Camera")
    camera.farClip = 300.0

    -- Set an initial position for the camera scene node above the plane
    cameraNode.position = Vector3(0.0, 5.0, 0.0)
end

function CreateInstructions()
    -- Construct new Text object, set string to display and font to use
    local instructionText = ui.root:CreateChild("Text")
    instructionText.text =
        "Use WASD keys and mouse to move\n"..
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
    pitch = pitch + MOUSE_SENSITIVITY * mouseMove.y
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

    -- Toggle debug geometry with space
    if input:GetKeyPress(KEY_SPACE) then
        drawDebug = not drawDebug
    end
end

function AnimateScene(timeStep)
    local LIGHT_ROTATION_SPEED = 20.0
    local BILLBOARD_ROTATION_SPEED = 50.0

    -- Rotate the lights around the world Y-axis
    for i, v in ipairs(lightNodes) do
        v:Rotate(Quaternion(0.0, LIGHT_ROTATION_SPEED * timeStep, 0.0), TS_WORLD)
    end

    -- Rotate the individual billboards within the billboard sets, then recommit to make the changes visible
    for i, v in ipairs(billboardNodes) do
        local billboardObject = v:GetComponent("BillboardSet")

        for j = 1, billboardObject.numBillboards do
            local bb = billboardObject:GetBillboard(j - 1)
            bb.rotation = bb.rotation + BILLBOARD_ROTATION_SPEED * timeStep
        end

        billboardObject:Commit()
    end
end

function HandleUpdate(eventType, eventData)
    -- Take the frame time step, which is stored as a float
    local timeStep = eventData:GetFloat("TimeStep")

    -- Move the camera and animate the scene, scale movement with time step
    MoveCamera(timeStep)
    AnimateScene(timeStep)
end

function HandlePostRenderUpdate(eventType, eventData)
    -- If draw debug mode is enabled, draw viewport debug geometry. This time use depth test, as otherwise the result becomes
    -- hard to interpret due to large object count
    if drawDebug then
        renderer:DrawDebugGeometry(true)
    end
end

-- Create XML patch instructions for screen joystick layout specific to this sample app
function GetScreenJoystickPatchString()
    return
        "<patch>" ..
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
