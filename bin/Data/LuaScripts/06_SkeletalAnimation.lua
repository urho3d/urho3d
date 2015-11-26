-- Skeletal animation example.
-- This sample demonstrates:
--     - Populating a 3D scene with skeletally animated AnimatedModel components
--     - Moving the animated models and advancing their animation using a script object
--     - Enabling a cascaded shadow map on a directional light, which allows high-quality shadows
--       over a large area (typically used in outdoor scenes for shadows cast by sunlight)
--     - Displaying renderer debug geometry

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

    -- Create animated models
    local uint NUM_MODELS = 100
    local MODEL_MOVE_SPEED = 2.0
    local MODEL_ROTATE_SPEED = 100.0
    local bounds = BoundingBox(Vector3(-47.0, 0.0, -47.0), Vector3(47.0, 0.0, 47.0))

    for i = 1, NUM_MODELS do
        local modelNode = scene_:CreateChild("Jack")
        modelNode.position = Vector3(Random(90.0) - 45.0, 0.0, Random(90.0) - 45.0)
        modelNode.rotation = Quaternion(0.0, Random(360.0), 0.0)
        local modelObject = modelNode:CreateComponent("AnimatedModel")
        modelObject.model = cache:GetResource("Model", "Models/Jack.mdl")
        modelObject.material = cache:GetResource("Material", "Materials/Jack.xml")
        modelObject.castShadows = true

        -- Create an AnimationState for a walk animation. Its time position will need to be manually updated to advance the
        -- animation, The alternative would be to use an AnimationController component which updates the animation automatically,
        -- but we need to update the model's position manually in any case
        local walkAnimation = cache:GetResource("Animation", "Models/Jack_Walk.ani")
        local state = modelObject:AddAnimationState(walkAnimation)
        -- Enable full blending weight and looping
        state.weight = 1.0
        state.looped = true
        state.time = Random(walkAnimation.length)

        -- Create our Mover script object that will move & animate the model during each frame's update.

        local object = modelNode:CreateScriptObject("Mover")
        object:SetParameters(MODEL_MOVE_SPEED, MODEL_ROTATE_SPEED, bounds)
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
    instructionText:SetText("Use WASD keys and mouse to move\n"..
        "Space to toggle debug geometry")
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

    -- Subscribe HandlePostRenderUpdate() function for processing the post-render update event, sent after Renderer subsystem is
    -- done with defining the draw calls for the viewports (but before actually executing them.) We will request debug geometry
    -- rendering during that event
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

function HandleUpdate(eventType, eventData)
    -- Take the frame time step, which is stored as a float
    local timeStep = eventData["TimeStep"]:GetFloat()

    -- Move the camera, scale movement with time step
    MoveCamera(timeStep)
end

function HandlePostRenderUpdate(eventType, eventData)
    -- If draw debug mode is enabled, draw viewport debug geometry, which will show eg. drawable bounding boxes and skeleton
    -- bones. Note that debug geometry has to be separately requested each frame. Disable depth test so that we can see the
    -- bones properly
    if drawDebug then
        renderer:DrawDebugGeometry(false)
    end
end

-- Mover script object class
Mover = ScriptObject()

function Mover:Start()
    self.moveSpeed = 0.0
    self.rotationSpeed = 0.0
    self.bounds = BoundingBox()
end

function Mover:SetParameters(moveSpeed, rotationSpeed, bounds)
    self.moveSpeed = moveSpeed
    self.rotationSpeed = rotationSpeed
    self.bounds = bounds
end

function Mover:Update(timeStep)
    local node = self.node
    node:Translate(Vector3(0.0, 0.0, 1.0) * self.moveSpeed * timeStep)

    -- If in risk of going outside the plane, rotate the model right
    local pos = node.position
    local bounds = self.bounds
    if pos.x < bounds.min.x or pos.x > bounds.max.x or pos.z < bounds.min.z or pos.z > bounds.max.z then
        node:Yaw(self.rotationSpeed * timeStep)
    end

    -- Get the model's first (only) animation state and advance its time
    local model = node:GetComponent("AnimatedModel")
    local state = model:GetAnimationState(0)
    if state ~= nil then
        state:AddTime(timeStep)
    end
end

-- Create XML patch instructions for screen joystick layout specific to this sample app
function GetScreenJoystickPatchString()
    return
        "<patch>"..
        "    <remove sel=\"/element/element[./attribute[@name='Name' and @value='Button1']]/attribute[@name='Is Visible']\" />"..
        "    <replace sel=\"/element/element[./attribute[@name='Name' and @value='Button1']]/element[./attribute[@name='Name' and @value='Label']]/attribute[@name='Text']/@value\">Debug</replace>"..
        "    <add sel=\"/element/element[./attribute[@name='Name' and @value='Button1']]\">"..
        "        <element type=\"Text\">"..
        "            <attribute name=\"Name\" value=\"KeyBinding\" />"..
        "            <attribute name=\"Text\" value=\"SPACE\" />"..
        "        </element>"..
        "    </add>"..
        "</patch>"
end
