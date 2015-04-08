-- Physics stress test example.
-- This sample demonstrates:
--     - Physics and rendering performance with a high (1000) moving object count
--     - Using triangle meshes for collision
--     - Optimizing physics simulation by leaving out collision event signaling
--     - Usage of Lua Coroutine to yield/resume based on time step

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
    -- Create a physics simulation world with default parameters, which will update at 60ps. Like the Octree must
    -- exist before creating drawable components, the PhysicsWorld must exist before creating physics components.
    -- Finally, create a DebugRenderer component so that we can draw physics debug geometry
    scene_:CreateComponent("Octree")
    scene_:CreateComponent("PhysicsWorld")
    scene_:CreateComponent("DebugRenderer")

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

    if true then
        -- Create a floor object, 500 x 500 world units. Adjust position so that the ground is at zero Y
        local floorNode = scene_:CreateChild("Floor")
        floorNode.position = Vector3(0.0, -0.5, 0.0)
        floorNode.scale = Vector3(500.0, 1.0, 500.0)
        local floorObject = floorNode:CreateComponent("StaticModel")
        floorObject.model = cache:GetResource("Model", "Models/Box.mdl")
        floorObject.material = cache:GetResource("Material", "Materials/StoneTiled.xml")

        -- Make the floor physical by adding RigidBody and CollisionShape components
        local body = floorNode:CreateComponent("RigidBody")
        local shape = floorNode:CreateComponent("CollisionShape")
        -- Set a box shape of size 1 x 1 x 1 for collision. The shape will be scaled with the scene node scale, so the
        -- rendering and physics representation sizes should match (the box model is also 1 x 1 x 1.)
        shape:SetBox(Vector3(1.0, 1.0, 1.0))
    end

    -- Create static mushrooms with triangle mesh collision
    local NUM_MUSHROOMS = 50
    for i = 1, NUM_MUSHROOMS do
        local mushroomNode = scene_:CreateChild("Mushroom")
        mushroomNode.position = Vector3(Random(400.0) - 200.0, 0.0, Random(400.0) - 200.0)
        mushroomNode.rotation = Quaternion(0.0, Random(360.0), 0.0)
        mushroomNode:SetScale(5.0 + Random(5.0))
        local mushroomObject = mushroomNode:CreateComponent("StaticModel")
        mushroomObject.model = cache:GetResource("Model", "Models/Mushroom.mdl")
        mushroomObject.material = cache:GetResource("Material", "Materials/Mushroom.xml")
        mushroomObject.castShadows = true

        local body = mushroomNode:CreateComponent("RigidBody")
        local shape = mushroomNode:CreateComponent("CollisionShape")
        -- By default the highest LOD level will be used, the LOD level can be passed as an optional parameter
        shape:SetTriangleMesh(mushroomObject.model)
    end

    -- Start coroutine to create a large amount of falling physics objects
    coroutine.start(function()
            local NUM_OBJECTS = 1000
            for i = 1, NUM_OBJECTS do
                local boxNode = scene_:CreateChild("Box")
                boxNode.position = Vector3(0.0, 100.0, 0.0)
                local boxObject = boxNode:CreateComponent("StaticModel")
                boxObject.model = cache:GetResource("Model", "Models/Box.mdl")
                boxObject.material = cache:GetResource("Material", "Materials/StoneSmall.xml")
                boxObject.castShadows = true

                -- Give the RigidBody mass to make it movable and also adjust friction
                local body = boxNode:CreateComponent("RigidBody")
                body.mass = 1.0
                body.friction = 1.0

                -- Set linear velocity
                body.linearVelocity = Vector3(0.0, -50.0, 0.0)

                -- Disable collision event signaling to reduce CPU load of the physics simulation
                body.collisionEventMode = COLLISION_NEVER
                local shape = boxNode:CreateComponent("CollisionShape")
                shape:SetBox(Vector3(1.0, 1.0, 1.0))
                -- sleep coroutine
                coroutine.sleep(0.1)
            end
        end)

    -- Create the camera. Limit far clip distance to match the fog. Note: now we actually create the camera node outside
    -- the scene, because we want it to be unaffected by scene load/save
    cameraNode = Node()
    local camera = cameraNode:CreateComponent("Camera")
    camera.farClip = 300.0

    -- Set an initial position for the camera scene node above the floor
    cameraNode.position = Vector3(0.0, 3.0, -20.0)
end

function CreateInstructions()
    -- Construct new Text object, set string to display and font to use
    local instructionText = ui.root:CreateChild("Text")
    instructionText:SetText("Use WASD keys and mouse to move\n"..
        "LMB to spawn physics objects\n"..
        "F5 to save scene, F7 to load\n"..
        "Space to toggle physics debug geometry")
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
    pitch = pitch  +MOUSE_SENSITIVITY * mouseMove.y
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

    -- "Shoot" a physics object with left mousebutton
    if input:GetMouseButtonPress(MOUSEB_LEFT) then
        SpawnObject()
    end

    -- Check for loading/saving the scene. Save the scene to the file Data/Scenes/Physics.xml relative to the executable
    -- directory
    if input:GetKeyPress(KEY_F5) then
        scene_:SaveXML(fileSystem:GetProgramDir().."Data/Scenes/PhysicsStressTest.xml")
    end
    if input:GetKeyPress(KEY_F7) then
        scene_:LoadXML(fileSystem:GetProgramDir().."Data/Scenes/PhysicsStressTest.xml")
    end

    -- Toggle debug geometry with space
    if input:GetKeyPress(KEY_SPACE) then
        drawDebug = not drawDebug
    end
end

function SpawnObject()
    -- Create a smaller box at camera position
    local boxNode = scene_:CreateChild("SmallBox")
    boxNode.position = cameraNode.position
    boxNode.rotation = cameraNode.rotation
    boxNode:SetScale(0.25)
    local boxObject = boxNode:CreateComponent("StaticModel")
    boxObject.model = cache:GetResource("Model", "Models/Box.mdl")
    boxObject.material = cache:GetResource("Material", "Materials/StoneSmall.xml")
    boxObject.castShadows = true

    -- Create physics components, use a smaller mass also
    local body = boxNode:CreateComponent("RigidBody")
    body.mass = 0.25
    body.friction = 0.75
    local shape = boxNode:CreateComponent("CollisionShape")
    shape:SetBox(Vector3(1.0, 1.0, 1.0))

    local OBJECT_VELOCITY = 10.0

    -- Set initial velocity for the RigidBody based on camera forward vector. Add also a slight up component
    -- to overcome gravity better
    body.linearVelocity = cameraNode.rotation * Vector3(0.0, 0.25, 1.0) * OBJECT_VELOCITY
end

function HandleUpdate(eventType, eventData)
    -- Take the frame time step, which is stored as a float
    local timeStep = eventData:GetFloat("TimeStep")

    -- Move the camera, scale movement with time step
    MoveCamera(timeStep)
end

function HandlePostRenderUpdate(eventType, eventData)
    -- If draw debug mode is enabled, draw physics debug geometry. Use depth test to make the result easier to interpret
    if drawDebug then
        scene_:GetComponent("PhysicsWorld"):DrawDebugGeometry(true)
    end
end

-- Create XML patch instructions for screen joystick layout specific to this sample app
function GetScreenJoystickPatchString()
    return
        "<patch>" ..
        "    <remove sel=\"/element/element[./attribute[@name='Name' and @value='Button0']]/attribute[@name='Is Visible']\" />" ..
        "    <replace sel=\"/element/element[./attribute[@name='Name' and @value='Button0']]/element[./attribute[@name='Name' and @value='Label']]/attribute[@name='Text']/@value\">Spawn</replace>" ..
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
