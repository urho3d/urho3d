-- Render to texture example
-- This sample demonstrates:
--     - Creating two 3D scenes and rendering the other into a texture
--     - Creating rendertarget textures and materials programmatically

require "LuaScripts/Utilities/Sample"

local rttScene_ = nil
local rttCameraNode = nil

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

    -- Hook up to the frame update events
    SubscribeToEvents()
end

function CreateScene()
    -- Create the scene which will be rendered to a texture
    rttScene_ = Scene()

    -- Create octree, use default volume (-1000, -1000, -1000) to (1000, 1000, 1000)
    rttScene_:CreateComponent("Octree")

    -- Create a Zone for ambient light & fog control
    local zoneNode = rttScene_:CreateChild("Zone")
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
        local boxNode = rttScene_:CreateChild("Box")
        boxNode.position = Vector3(Random(200.0) - 100.0, Random(200.0) - 100.0, Random(200.0) - 100.0)
        -- Orient using random pitch, yaw and roll Euler angles
        boxNode.rotation = Quaternion(Random(360.0), Random(360.0), Random(360.0))
        local boxObject = boxNode:CreateComponent("StaticModel")
        boxObject.model = cache:GetResource("Model", "Models/Box.mdl")
        boxObject.material = cache:GetResource("Material", "Materials/Stone.xml")

        -- Add our custom Rotator component which will rotate the scene node each frame, when the scene sends its update event.
        -- Simply set same rotation speed for all objects
        local rotator = boxNode:CreateScriptObject("Rotator")
        rotator.rotationSpeed = { 10.0, 20.0, 30.0 }
    end

    -- Create a camera for the render-to-texture scene. Simply leave it at the world origin and let it observe the scene
    rttCameraNode = rttScene_:CreateChild("Camera")
    local camera = rttCameraNode:CreateComponent("Camera")
    camera.farClip = 100.0

    -- Create a point light to the camera scene node
    local light = rttCameraNode:CreateComponent("Light")
    light.lightType = LIGHT_POINT
    light.range = 30.0

    -- Create the scene in which we move around
    scene_ = Scene()

    -- Create octree, use also default volume (-1000, -1000, -1000) to (1000, 1000, 1000)
    scene_:CreateComponent("Octree")

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
            floorNode.scale = Vector3(20.0, 1.0, 20.)
            local floorObject = floorNode:CreateComponent("StaticModel")
            floorObject.model = cache:GetResource("Model", "Models/Box.mdl")
            floorObject.material = cache:GetResource("Material", "Materials/Stone.xml")
        end
    end

    -- Create a "screen" like object for viewing the second scene. Construct it from two StaticModels, a box for the frame
    -- and a plane for the actual view
    local boxNode = scene_:CreateChild("ScreenBox")
    boxNode.position = Vector3(0.0, 10.0, 0.0)
    boxNode.scale = Vector3(21.0, 16.0, 0.5)
    local boxObject = boxNode:CreateComponent("StaticModel")
    boxObject.model = cache:GetResource("Model", "Models/Box.mdl")
    boxObject.material = cache:GetResource("Material", "Materials/Stone.xml")

    local screenNode = scene_:CreateChild("Screen")
    screenNode.position = Vector3(0.0, 10.0, -0.27)
    screenNode.rotation = Quaternion(-90.0, 0.0, 0.0)
    screenNode.scale = Vector3(20.0, 0.0, 15.0)
    local screenObject = screenNode:CreateComponent("StaticModel")
    screenObject.model = cache:GetResource("Model", "Models/Plane.mdl")

    -- Create a renderable texture (1024x768, RGB format), enable bilinear filtering on it
    local renderTexture = Texture2D:new()
    renderTexture:SetSize(1024, 768, Graphics:GetRGBFormat(), TEXTURE_RENDERTARGET)
    renderTexture.filterMode = FILTER_BILINEAR

    -- Create a new material from scratch, use the diffuse unlit technique, assign the render texture
    -- as its diffuse texture, then assign the material to the screen plane object
    local renderMaterial = Material:new()
    renderMaterial:SetTechnique(0, cache:GetResource("Technique", "Techniques/DiffUnlit.xml"))
    renderMaterial:SetTexture(TU_DIFFUSE, renderTexture)
    screenObject.material = renderMaterial

    -- Get the texture's RenderSurface object (exists when the texture has been created in rendertarget mode)
    -- and define the viewport for rendering the second scene, similarly as how backbuffer viewports are defined
    -- to the Renderer subsystem. By default the texture viewport will be updated when the texture is visible
    -- in the main view
    local surface = renderTexture.renderSurface
    local rttViewport = Viewport:new(rttScene_, rttCameraNode:GetComponent("Camera"))
    surface:SetViewport(0, rttViewport)

    -- Create the camera which we will move around. Limit far clip distance to match the fog
    cameraNode = scene_:CreateChild("Camera")
    local camera = cameraNode:CreateComponent("Camera")
    camera.farClip = 300.0

    -- Set an initial position for the camera scene node above the plane
    cameraNode.position = Vector3(0.0, 7.0, -30.0)
end

function CreateInstructions()
    -- Construct new Text object, set string to display and font to use
    local instructionText = ui.root:CreateChild("Text")
    instructionText.text = "Use WASD keys and mouse to move"
    instructionText:SetFont(cache:GetResource("Font", "Fonts/Anonymous Pro.ttf"), 15)

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
    local delta = MOVE_SPEED * timeStep
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
    local timeStep = eventData["TimeStep"]:GetFloat()

    -- Move the camera, scale movement with time step
    MoveCamera(timeStep)
end

-- Rotator script object class. Script objects to be added to a scene node must implement the empty ScriptObject interface
Rotator = ScriptObject()

function Rotator:Start()
    self.rotationSpeed = {0.0, 0.0, 0.0}
end

-- Update is called during the variable timestep scene update
function Rotator:Update(timeStep)
    local x = self.rotationSpeed[1] * timeStep
    local y = self.rotationSpeed[2] * timeStep
    local z = self.rotationSpeed[3] * timeStep
    self.node:Rotate(Quaternion(x, y, z))
end
