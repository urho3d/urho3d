-- Multiple viewports example.
-- This sample demonstrates:
--     - Setting up two viewports with two separate cameras
--     - Adding post processing effects to a viewport's render path and toggling them

require "LuaScripts/Utilities/Sample"

local rearCameraNode = nil

function Start()
    -- Execute the common startup for samples
    SampleStart()

    -- Create the scene content
    CreateScene()

    -- Create the UI content
    CreateInstructions()

    -- Setup the viewports for displaying the scene
    SetupViewports()

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

    -- Create some mushrooms
    local NUM_MUSHROOMS = 240
    for i = 1, NUM_MUSHROOMS do
        local mushroomNode = scene_:CreateChild("Mushroom")
        mushroomNode.position = Vector3(Random(90.0) - 45.0, 0.0, Random(90.0) - 45.0)
        mushroomNode.rotation = Quaternion(0.0, Random(360.0), 0.0)
        mushroomNode:SetScale(0.5 + Random(2.0))
        local mushroomObject = mushroomNode:CreateComponent("StaticModel")
        mushroomObject.model = cache:GetResource("Model", "Models/Mushroom.mdl")
        mushroomObject.material = cache:GetResource("Material", "Materials/Mushroom.xml")
        mushroomObject.castShadows = true
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

    -- Create the camera. Limit far clip distance to match the fog
    cameraNode = scene_:CreateChild("Camera")
    local camera = cameraNode:CreateComponent("Camera")
    camera.farClip = 300.0

    -- Parent the rear camera node to the front camera node and turn it 180 degrees to face backward
    -- Here, we use the angle-axis constructor for Quaternion instead of the usual Euler angles
    rearCameraNode = cameraNode:CreateChild("RearCamera")
    rearCameraNode:Rotate(Quaternion(180.0, Vector3(0.0, 1.0, 0.0)))
    local rearCamera = rearCameraNode:CreateComponent("Camera")
    rearCamera.farClip = 300.0
    -- Because the rear viewport is rather small, disable occlusion culling from it. Use the camera's
    -- "view override flags" for this. We could also disable eg. shadows or force low material quality
    -- if we wanted
    rearCamera.viewOverrideFlags = VO_DISABLE_OCCLUSION

    -- Set an initial position for the front camera scene node above the plane
    cameraNode.position = Vector3(0.0, 5.0, 0.0)
end

function CreateInstructions()
    -- Construct new Text object, set string to display and font to use
    local instructionText = ui.root:CreateChild("Text")
    instructionText.text =
        "Use WASD keys and mouse to move\n"..
        "B to toggle bloom, F to toggle FXAA\n"..
        "Space to toggle debug geometry\n"
    instructionText:SetFont(cache:GetResource("Font", "Fonts/Anonymous Pro.ttf"), 15)
    -- The text has multiple rows. Center them in relation to each other
    instructionText.textAlignment = HA_CENTER

    -- Position the text relative to the screen center
    instructionText.horizontalAlignment = HA_CENTER
    instructionText.verticalAlignment = VA_CENTER
    instructionText:SetPosition(0, ui.root.height / 4)
end

function SetupViewports()
    renderer.numViewports = 2

    -- Set up the front camera viewport
    local viewport = Viewport:new(scene_, cameraNode:GetComponent("Camera"))
    renderer:SetViewport(0, viewport)

    -- Clone the default render path so that we do not interfere with the other viewport, then add
    -- bloom and FXAA post process effects to the front viewport. Render path commands can be tagged
    -- for example with the effect name to allow easy toggling on and off. We start with the effects
    -- disabled.
    local effectRenderPath = viewport:GetRenderPath():Clone()
    effectRenderPath:Append(cache:GetResource("XMLFile", "PostProcess/Bloom.xml"))
    effectRenderPath:Append(cache:GetResource("XMLFile", "PostProcess/FXAA2.xml"))
    -- Make the bloom mixing parameter more pronounced
    effectRenderPath:SetShaderParameter("BloomMix", Variant(Vector2(0.9, 0.6)))
    effectRenderPath:SetEnabled("Bloom", false)
    effectRenderPath:SetEnabled("FXAA2", false)
    viewport:SetRenderPath(effectRenderPath)

    -- Set up the rear camera viewport on top of the front view ("rear view mirror")
    -- The viewport index must be greater in that case, otherwise the view would be left behind
    local rearViewport = Viewport:new(scene_, rearCameraNode:GetComponent("Camera"),
        IntRect(graphics.width * 2 / 3, 32, graphics.width - 32, graphics.height / 3))
    renderer:SetViewport(1, rearViewport)
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

    -- Toggle post processing effects on the front viewport. Note that the rear viewport is unaffected
    local effectRenderPath = renderer:GetViewport(0).renderPath
    if input:GetKeyPress(KEY_B) then
        effectRenderPath:ToggleEnabled("Bloom")
    end
    if input:GetKeyPress(KEY_F) then
        effectRenderPath:ToggleEnabled("FXAA2")
    end

    -- Toggle debug geometry with space
    if input:GetKeyPress(KEY_SPACE) then
        drawDebug = not drawDebug
    end
end

function HandleUpdate(eventType, eventData)
    -- Take the frame time step, which is stored as a float
    local timeStep = eventData["TimeStep"]:GetFloat()

    -- Move the camera, scale movement with time step
    MoveCamera(timeStep)
end

function HandlePostRenderUpdate(eventType, eventData)
    -- If draw debug mode is enabled, draw viewport debug geometry. Disable depth test so that we can see the effect of occlusion
    if drawDebug then
        renderer:DrawDebugGeometry(false)
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
        "                <attribute name=\"Text\" value=\"FXAA\" />" ..
        "            </element>" ..
        "            <element type=\"Text\">" ..
        "                <attribute name=\"Name\" value=\"KeyBinding\" />" ..
        "                <attribute name=\"Text\" value=\"F\" />" ..
        "            </element>" ..
        "        </element>" ..
        "    </add>" ..
        "    <remove sel=\"/element/element[./attribute[@name='Name' and @value='Button0']]/attribute[@name='Is Visible']\" />" ..
        "    <replace sel=\"/element/element[./attribute[@name='Name' and @value='Button0']]/element[./attribute[@name='Name' and @value='Label']]/attribute[@name='Text']/@value\">Bloom</replace>" ..
        "    <add sel=\"/element/element[./attribute[@name='Name' and @value='Button0']]\">" ..
        "        <element type=\"Text\">" ..
        "            <attribute name=\"Name\" value=\"KeyBinding\" />" ..
        "            <attribute name=\"Text\" value=\"B\" />" ..
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
