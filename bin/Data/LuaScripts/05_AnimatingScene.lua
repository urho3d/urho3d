-- Animating 3D scene example.
-- This sample demonstrates:
--     - Creating a 3D scene and using a script component to animate the objects
--     - Controlling scene ambience with the Zone component
--     - Attaching a light to an object (the camera)

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

    -- Hook up to the frame update events
    SubscribeToEvents()
end

function CreateScene()
    scene_ = Scene()

    -- Create the Octree component to the scene so that drawable objects can be rendered. Use default volume
    -- (-1000, -1000, -1000) to (1000, 1000, 1000)
    scene_:CreateComponent("Octree")

    -- Create a Zone component into a child scene node. The Zone controls ambient lighting and fog settings. Like the Octree,
    -- it also defines its volume with a bounding box, but can be rotated (so it does not need to be aligned to the world X, Y
    -- and Z axes.) Drawable objects "pick up" the zone they belong to and use it when rendering several zones can exist
    local zoneNode = scene_:CreateChild("Zone")
    local zone = zoneNode:CreateComponent("Zone")
    -- Set same volume as the Octree, set a close bluish fog and some ambient light
    zone.boundingBox = BoundingBox(-1000.0, 1000.0)
    zone.ambientColor = Color(0.05, 0.1, 0.15)
    zone.fogColor = Color(0.1, 0.2, 0.3)
    zone.fogStart = 10.0
    zone.fogEnd = 100.0

    -- Create randomly positioned and oriented box StaticModels in the scene
    local NUM_OBJECTS = 2000
    for i = 1, NUM_OBJECTS do
        local boxNode = scene_:CreateChild("Box")
        boxNode.position = Vector3(Random(200.0) - 100.0, Random(200.0) - 100.0, Random(200.0) - 100.0)
        -- Orient using random pitch, yaw and roll Euler angles
        boxNode.rotation = Quaternion(Random(360.0), Random(360.0), Random(360.0))
        local boxObject = boxNode:CreateComponent("StaticModel")
        boxObject.model = cache:GetResource("Model", "Models/Box.mdl")
        boxObject.material = cache:GetResource("Material", "Materials/Stone.xml")

        -- Add the Rotator script object which will rotate the scene node each frame, when the scene sends its update event.
        -- This requires the C++ component LuaScriptInstance in the scene node, which acts as a container. We need to tell the
        -- class name to instantiate the object


        local object = boxNode:CreateScriptObject("Rotator")
        object.rotationSpeed = {10.0, 20.0, 30.0}
    end

    -- Create the camera. Let the starting position be at the world origin. As the fog limits maximum visible distance, we can
    -- bring the far clip plane closer for more effective culling of distant objects
    cameraNode = scene_:CreateChild("Camera")
    local camera = cameraNode:CreateComponent("Camera")
    camera.farClip = 100.0

    -- Create a point light to the camera scene node
    light = cameraNode:CreateComponent("Light")
    light.lightType = LIGHT_POINT
    light.range = 30.0
end

function CreateInstructions()
    -- Construct new Text object, set string to display and font to use
    local instructionText = ui.root:CreateChild("Text")
    instructionText:SetText("Use WASD keys and mouse to move")
    instructionText:SetFont(cache:GetResource("Font", "Fonts/Anonymous Pro.ttf"), 15)

    -- Position the text relative to the screen center
    instructionText.horizontalAlignment = HA_CENTER
    instructionText.verticalAlignment = VA_CENTER
    instructionText:SetPosition(0, ui.root.height / 4)
end

function SetupViewport()
    -- Set up a viewport to the Renderer subsystem so that the 3D scene can be seen. We need to define the scene and the camera
    -- at minimum. Additionally we could configure the viewport screen size and the rendering path (eg. forward / deferred) to
    -- use, but now we just use full screen and default render path configured in the engine command line options
    local viewport = Viewport:new(scene_, cameraNode:GetComponent("Camera"))
    renderer:SetViewport(0, viewport)
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
    pitch = pitch +  MOUSE_SENSITIVITY * mouseMove.y
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
end

function SubscribeToEvents()
    -- Subscribe HandleUpdate() function for processing update events
    SubscribeToEvent("Update", "HandleUpdate")
end

function HandleUpdate(eventType, eventData)
    -- Take the frame time step, which is stored as a float
    local timeStep = eventData:GetFloat("TimeStep")

    -- Move the camera, scale movement with time step
    MoveCamera(timeStep)
end

-- Rotator script object class. Script objects to be added to a scene node must implement the empty ScriptObject interface
Rotator = ScriptObject()

function Rotator:Start()
    self.rotationSpeed = {0.0, 0.0, 0.0}
end

function Rotator:Update(timeStep)
    local x = self.rotationSpeed[1] * timeStep
    local y = self.rotationSpeed[2] * timeStep
    local z = self.rotationSpeed[3] * timeStep
    self.node:Rotate(Quaternion(x, y, z))
end
