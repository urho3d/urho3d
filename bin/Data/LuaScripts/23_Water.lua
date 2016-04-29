-- Water example.
-- This sample demonstrates:
--     - Creating a large plane to represent a water body for rendering
--     - Setting up a second camera to render reflections on the water surface

require "LuaScripts/Utilities/Sample"

local reflectionCameraNode = nil
local waterNode = nil
local waterPlane = Plane()
local waterClipPlane = Plane()

function Start()
    -- Execute the common startup for samples
    SampleStart()

    -- Create the scene content
    CreateScene()

    -- Create the UI content
    CreateInstructions()

    -- Setup the viewport for displaying the scene
    SetupViewport()

    -- Set the mouse mode to use in the sample
    SampleInitMouseMode(MM_RELATIVE)

    -- Hook up to the frame update event
    SubscribeToEvents()
end

function CreateScene()
    scene_ = Scene()

    -- Create octree, use default volume (-1000, -1000, -1000) to (1000, 1000, 1000)
    scene_:CreateComponent("Octree")

    -- Create a Zone component for ambient lighting & fog control
    local zoneNode = scene_:CreateChild("Zone")
    local zone = zoneNode:CreateComponent("Zone")
    zone.boundingBox = BoundingBox(-1000.0, 1000.0)
    zone.ambientColor = Color(0.15, 0.15, 0.15)
    zone.fogColor = Color(1.0, 1.0, 1.0)
    zone.fogStart = 500.0
    zone.fogEnd = 750.0

    -- Create a directional light to the world. Enable cascaded shadows on it
    local lightNode = scene_:CreateChild("DirectionalLight")
    lightNode.direction = Vector3(0.6, -1.0, 0.8)
    local light = lightNode:CreateComponent("Light")
    light.lightType = LIGHT_DIRECTIONAL
    light.castShadows = true
    light.shadowBias = BiasParameters(0.00025, 0.5)
    light.shadowCascade = CascadeParameters(10.0, 50.0, 200.0, 0.0, 0.8)
    light.specularIntensity = 0.5;
    -- Apply slightly overbright lighting to match the skybox
    light.color = Color(1.2, 1.2, 1.2);

    -- Create skybox. The Skybox component is used like StaticModel, but it will be always located at the camera, giving the
    -- illusion of the box planes being far away. Use just the ordinary Box model and a suitable material, whose shader will
    -- generate the necessary 3D texture coordinates for cube mapping
    local skyNode = scene_:CreateChild("Sky")
    skyNode:SetScale(500.0) -- The scale actually does not matter
    local skybox = skyNode:CreateComponent("Skybox")
    skybox.model = cache:GetResource("Model", "Models/Box.mdl")
    skybox.material = cache:GetResource("Material", "Materials/Skybox.xml")

    -- Create heightmap terrain
    local terrainNode = scene_:CreateChild("Terrain")
    terrainNode.position = Vector3(0.0, 0.0, 0.0)
    local terrain = terrainNode:CreateComponent("Terrain")
    terrain.patchSize = 64
    terrain.spacing = Vector3(2.0, 0.5, 2.0) -- Spacing between vertices and vertical resolution of the height map
    terrain.smoothing = true
    terrain.heightMap = cache:GetResource("Image", "Textures/HeightMap.png")
    terrain.material = cache:GetResource("Material", "Materials/Terrain.xml")
    -- The terrain consists of large triangles, which fits well for occlusion rendering, as a hill can occlude all
    -- terrain patches and other objects behind it
    terrain.occluder = true

    -- Create 1000 boxes in the terrain. Always face outward along the terrain normal
    local NUM_OBJECTS = 1000
    for i = 1, NUM_OBJECTS do
        local objectNode = scene_:CreateChild("Box")
        local position = Vector3(Random(2000.0) - 1000.0, 0.0, Random(2000.0) - 1000.0)
        position.y = terrain:GetHeight(position) + 2.25
        objectNode.position = position
        -- Create a rotation quaternion from up vector to terrain normal
        objectNode.rotation = Quaternion(Vector3(0.0, 1.0, 0.0), terrain:GetNormal(position))
        objectNode:SetScale(5.0)
        local object = objectNode:CreateComponent("StaticModel")
        object.model = cache:GetResource("Model", "Models/Box.mdl")
        object.material = cache:GetResource("Material", "Materials/Stone.xml")
        object.castShadows = true
    end

    -- Create a water plane object that is as large as the terrain
    waterNode = scene_:CreateChild("Water")
    waterNode.scale = Vector3(2048.0, 1.0, 2048.0)
    waterNode.position = Vector3(0.0, 5.0, 0.0)
    local water = waterNode:CreateComponent("StaticModel")
    water.model = cache:GetResource("Model", "Models/Plane.mdl")
    water.material = cache:GetResource("Material", "Materials/Water.xml")
    -- Set a different viewmask on the water plane to be able to hide it from the reflection camera
    water.viewMask = 0x80000000

    -- Create the camera. Set far clip to match the fog. Note: now we actually create the camera node outside
    -- the scene, because we want it to be unaffected by scene load / save
    cameraNode = Node()
    local camera = cameraNode:CreateComponent("Camera")
    camera.farClip = 750.0

    -- Set an initial position for the camera scene node above the floor
    cameraNode.position = Vector3(0.0, 7.0, -20.0)
end

function CreateInstructions()
    -- Construct new Text object, set string to display and font to use
    local instructionText = ui.root:CreateChild("Text")
    instructionText:SetText("Use WASD keys and mouse to move")
    instructionText:SetFont(cache:GetResource("Font", "Fonts/Anonymous Pro.ttf"), 15)
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

    -- Create a mathematical plane to represent the water in calculations
    waterPlane = Plane(waterNode.worldRotation * Vector3(0.0, 1.0, 0.0), waterNode.worldPosition)
    -- Create a downward biased plane for reflection view clipping. Biasing is necessary to avoid too aggressive clipping
    waterClipPlane = Plane(waterNode.worldRotation * Vector3(0.0, 1.0, 0.0), waterNode.worldPosition -
        Vector3(0.0, 0.1, 0.0))

    -- Create camera for water reflection
    -- It will have the same farclip and position as the main viewport camera, but uses a reflection plane to modify
    -- its position when rendering
    reflectionCameraNode = cameraNode:CreateChild()
    local reflectionCamera = reflectionCameraNode:CreateComponent("Camera")
    reflectionCamera.farClip = 750.0
    reflectionCamera.viewMask = 0x7fffffff -- Hide objects with only bit 31 in the viewmask (the water plane)
    reflectionCamera.autoAspectRatio = false
    reflectionCamera.useReflection = true
    reflectionCamera.reflectionPlane = waterPlane
    reflectionCamera.useClipping = true -- Enable clipping of geometry behind water plane
    reflectionCamera.clipPlane = waterClipPlane
    -- The water reflection texture is rectangular. Set reflection camera aspect ratio to match
    reflectionCamera.aspectRatio = graphics.width / graphics.height
    -- View override flags could be used to optimize reflection rendering. For example disable shadows
    --reflectionCamera.viewOverrideFlags = VO_DISABLE_SHADOWS

    -- Create a texture and setup viewport for water reflection. Assign the reflection texture to the diffuse
    -- texture unit of the water material
    local texSize = 1024
    local renderTexture = Texture2D:new()
    renderTexture:SetSize(texSize, texSize, Graphics:GetRGBFormat(), TEXTURE_RENDERTARGET)
    renderTexture.filterMode = FILTER_BILINEAR
    local surface = renderTexture.renderSurface
    local rttViewport = Viewport:new(scene_, reflectionCamera)
    surface:SetViewport(0, rttViewport)
    local waterMat = cache:GetResource("Material", "Materials/Water.xml")
    waterMat:SetTexture(TU_DIFFUSE, renderTexture)
end

function SubscribeToEvents()
    -- Subscribe HandleUpdate() function for processing update events
    SubscribeToEvent("Update", "HandleUpdate")
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

    -- In case resolution has changed, adjust the reflection camera aspect ratio
    local reflectionCamera = reflectionCameraNode:GetComponent("Camera")
    reflectionCamera.aspectRatio = graphics.width / graphics.height
end

function HandleUpdate(eventType, eventData)
    -- Take the frame time step, which is stored as a float
    local timeStep = eventData["TimeStep"]:GetFloat()

    -- Move the camera, scale movement with time step
    MoveCamera(timeStep)
end
