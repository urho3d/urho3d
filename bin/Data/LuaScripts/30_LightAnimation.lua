-- Light animation example.
-- This sample is base on StaticScene, and it demonstrates:
--     - Usage of attribute animation for light color animation

require "LuaScripts/Utilities/Sample"

function Start()
    -- Execute the common startup for samples
    SampleStart()

    -- Create the UI content
    CreateInstructions()

    -- Create the scene content
    CreateScene()

    -- Setup the viewport for displaying the scene
    SetupViewport()

    -- Hook up to the frame update events
    SubscribeToEvents()
end

function CreateScene()
    scene_ = Scene()

    -- Create the Octree component to the scene. This is required before adding any drawable components, or else nothing will
    -- show up. The default octree volume will be from (-1000, -1000, -1000) to (1000, 1000, 1000) in world coordinates it
    -- is also legal to place objects outside the volume but their visibility can then not be checked in a hierarchically
    -- optimizing manner
    scene_:CreateComponent("Octree")

    -- Create a child scene node (at world origin) and a StaticModel component into it. Set the StaticModel to show a simple
    -- plane mesh with a "stone" material. Note that naming the scene nodes is optional. Scale the scene node larger
    -- (100 x 100 world units)
    local planeNode = scene_:CreateChild("Plane")
    planeNode.scale = Vector3(100.0, 1.0, 100.0)
    local planeObject = planeNode:CreateComponent("StaticModel")
    planeObject.model = cache:GetResource("Model", "Models/Plane.mdl")
    planeObject.material = cache:GetResource("Material", "Materials/StoneTiled.xml")

    -- Create a point light to the world so that we can see something.
    local lightNode = scene_:CreateChild("DirectionalLight")
    local light = lightNode:CreateComponent("Light")
    light.lightType = LIGHT_POINT
    light.range = 10.0

    -- Create light color animation
    local colorAnimation = ValueAnimation:new()
    colorAnimation:SetKeyFrame(0.0, Variant(Color.WHITE))
    colorAnimation:SetKeyFrame(1.0, Variant(Color.RED))
    colorAnimation:SetKeyFrame(2.0, Variant(Color.YELLOW))
    colorAnimation:SetKeyFrame(3.0, Variant(Color.GREEN))
    colorAnimation:SetKeyFrame(4.0, Variant(Color.WHITE))
    light:SetAttributeAnimation("Color", colorAnimation)

    -- Create text animation
    local textAnimation = ValueAnimation:new()
    textAnimation:SetKeyFrame(0.0, Variant("WHITE"))
    textAnimation:SetKeyFrame(1.0, Variant("RED"))
    textAnimation:SetKeyFrame(2.0, Variant("YELLOW"))
    textAnimation:SetKeyFrame(3.0, Variant("GREEN"))
    textAnimation:SetKeyFrame(4.0, Variant("WHITE"))
    ui.root:GetChild("animatingText"):SetAttributeAnimation("Text", textAnimation)

    -- Create light position animation
    local positionAnimation = ValueAnimation:new()
    -- Use spline interpolation method
    positionAnimation.interpolationMethod = IM_SPLINE
    -- Set spline tension
    positionAnimation.splineTension = 0.7
    positionAnimation:SetKeyFrame(0.0, Variant(Vector3(-30.0, 5.0, -30.0)))
    positionAnimation:SetKeyFrame(1.0, Variant(Vector3( 30.0, 5.0, -30.0)))
    positionAnimation:SetKeyFrame(2.0, Variant(Vector3( 30.0, 5.0,  30.0)))
    positionAnimation:SetKeyFrame(3.0, Variant(Vector3(-30.0, 5.0,  30.0)))
    positionAnimation:SetKeyFrame(4.0, Variant(Vector3(-30.0, 5.0, -30.0)))
    lightNode:SetAttributeAnimation("Position", positionAnimation)

    -- Create more StaticModel objects to the scene, randomly positioned, rotated and scaled. For rotation, we construct a
    -- quaternion from Euler angles where the Y angle (rotation about the Y axis) is randomized. The mushroom model contains
    -- LOD levels, so the StaticModel component will automatically select the LOD level according to the view distance (you'll
    -- see the model get simpler as it moves further away). Finally, rendering a large number of the same object with the
    -- same material allows instancing to be used, if the GPU supports it. This reduces the amount of CPU work in rendering the
    -- scene.
    local NUM_OBJECTS = 200
    for i = 1, NUM_OBJECTS do
        local mushroomNode = scene_:CreateChild("Mushroom")
        mushroomNode.position = Vector3(Random(90.0) - 45.0, 0.0, Random(90.0) - 45.0)
        mushroomNode.rotation = Quaternion(0.0, Random(360.0), 0.0)
        mushroomNode:SetScale(0.5 + Random(2.0))
        local mushroomObject = mushroomNode:CreateComponent("StaticModel")
        mushroomObject.model = cache:GetResource("Model", "Models/Mushroom.mdl")
        mushroomObject.material = cache:GetResource("Material", "Materials/Mushroom.xml")
    end

    -- Create a scene node for the camera, which we will move around
    -- The camera will use default settings (1000 far clip distance, 45 degrees FOV, set aspect ratio automatically)
    cameraNode = scene_:CreateChild("Camera")
    cameraNode:CreateComponent("Camera")

    -- Set an initial position for the camera scene node above the plane
    cameraNode.position = Vector3(0.0, 5.0, 0.0)
end

function CreateInstructions()
    -- Construct new Text object, set string to display and font to use
    local instructionText = ui.root:CreateChild("Text")
    instructionText:SetText("Use WASD keys and mouse to move")
    local font = cache:GetResource("Font", "Fonts/Anonymous Pro.ttf")
    instructionText:SetFont(font, 15)

    -- Position the text relative to the screen center
    instructionText.horizontalAlignment = HA_CENTER
    instructionText.verticalAlignment = VA_CENTER
    instructionText:SetPosition(0, ui.root.height / 4)

    -- Animating text
    local text = ui.root:CreateChild("Text", "animatingText")
    text:SetFont(font, 15)
    text.horizontalAlignment = HA_CENTER
    text.verticalAlignment = VA_CENTER
    text:SetPosition(0, ui.root.height / 4 + 20)
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
    yaw = yaw +MOUSE_SENSITIVITY * mouseMove.x
    pitch = pitch + MOUSE_SENSITIVITY * mouseMove.y
    pitch = Clamp(pitch, -90.0, 90.0)

    -- Construct new orientation for the camera scene node from yaw and pitch. Roll is fixed to zero
    cameraNode.rotation = Quaternion(pitch, yaw, 0.0)

    -- Read WASD keys and move the camera scene node to the corresponding direction if they are pressed
    -- Use the Translate() function (default local space) to move relative to the node's orientation.
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
