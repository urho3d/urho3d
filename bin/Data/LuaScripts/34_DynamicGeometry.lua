-- Dynamic geometry example.
-- This sample demonstrates:
--     - Cloning a Model resource
--     - Modifying the vertex buffer data of the cloned models at runtime to efficiently animate them
--     - Creating a Model resource and its buffer data from scratch

require "LuaScripts/Utilities/Sample"

local boxNodes = {}
local animate = false
local useGroups = false

local animate = true;
local animTime = 0.0
local originalVertexData = VectorBuffer()
local animatingBuffers = {}
local originalVertices = {}
local vertexDuplicates = {}

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
    scene_ = Scene()

    -- Create the Octree component to the scene so that drawable objects can be rendered. Use default volume
    -- (-1000, -1000, -1000) to (1000, 1000, 1000)
    scene_:CreateComponent("Octree")

    -- Create a Zone for ambient light & fog control
    local zoneNode = scene_:CreateChild("Zone")
    local zone = zoneNode:CreateComponent("Zone")
    zone.boundingBox = BoundingBox(-1000.0, 1000.0)
    zone.fogColor = Color(0.2, 0.2, 0.2)
    zone.fogStart = 200.0
    zone.fogEnd = 300.0

    -- Create a directional light
    local lightNode = scene_:CreateChild("DirectionalLight")
    lightNode.direction = Vector3(-0.6, -1.0, -0.8) -- The direction vector does not need to be normalized
    local light = lightNode:CreateComponent("Light")
    light.lightType = LIGHT_DIRECTIONAL
    light.color = Color(0.4, 1.0, 0.4)
    light.specularIntensity = 1.5

    -- Get the original model and its unmodified vertices, which are used as source data for the animation
    local originalModel = cache:GetResource("Model", "Models/Box.mdl")
    if originalModel == nil then
        print("Model not found, cannot initialize example scene")
        return
    end

    -- Get the vertex buffer from the first geometry's first LOD level
    local buffer = originalModel:GetGeometry(0, 0):GetVertexBuffer(0)
    originalVertexData = buffer:GetData()
    local numVertices = buffer.vertexCount
    local vertexSize = buffer.vertexSize
    -- Copy the original vertex positions
    for i = 0, numVertices - 1 do
        originalVertexData:Seek(i * vertexSize)
        originalVertices[i+1] = originalVertexData:ReadVector3()
    end

    -- Detect duplicate vertices to allow seamless animation
    for i = 1, table.getn(originalVertices) do
        vertexDuplicates[i] = i -- Assume not a duplicate
        for j = 1, i - 1 do
            if originalVertices[i]:Equals(originalVertices[j]) then
                vertexDuplicates[i] = j
                break
            end
        end
    end

    -- Create StaticModels in the scene. Clone the model for each so that we can modify the vertex data individually
    for y = -1, 1 do
        for x = -1, 1 do
            local node = scene_:CreateChild("Object")
            node.position = Vector3(x * 2.0, 0.0, y * 2.0)
            local object = node:CreateComponent("StaticModel")
            local cloneModel = originalModel:Clone()
            object.model = cloneModel
            -- Store the cloned vertex buffer that we will modify when animating
            table.insert(animatingBuffers, cloneModel:GetGeometry(0, 0):GetVertexBuffer(0))
        end
    end

    -- Finally create one model (pyramid shape) and a StaticModel to display it from scratch
    -- Note: there are duplicated vertices to enable face normals. We will calculate normals programmatically
    local numVertices = 18

    local vertexData = {
        -- Position          Normal
        0.0, 0.5, 0.0,       0.0, 0.0, 0.0,
        0.5, -0.5, 0.5,      0.0, 0.0, 0.0,
        0.5, -0.5, -0.5,     0.0, 0.0, 0.0,

        0.0, 0.5, 0.0,       0.0, 0.0, 0.0,
        -0.5, -0.5, 0.5,     0.0, 0.0, 0.0,
        0.5, -0.5, 0.5,      0.0, 0.0, 0.0,

        0.0, 0.5, 0.0,       0.0, 0.0, 0.0,
        -0.5, -0.5, -0.5,    0.0, 0.0, 0.0,
        -0.5, -0.5, 0.5,     0.0, 0.0, 0.0,

        0.0, 0.5, 0.0,       0.0, 0.0, 0.0,
        0.5, -0.5, -0.5,     0.0, 0.0, 0.0,
        -0.5, -0.5, -0.5,    0.0, 0.0, 0.0,

        0.5, -0.5, -0.5,     0.0, 0.0, 0.0,
        0.5, -0.5, 0.5,      0.0, 0.0, 0.0,
        -0.5, -0.5, 0.5,     0.0, 0.0, 0.0,

        0.5, -0.5, -0.5,     0.0, 0.0, 0.0,
        -0.5, -0.5, 0.5,     0.0, 0.0, 0.0,
        -0.5, -0.5, -0.5,    0.0, 0.0, 0.0
    }

    local indexData = {
        0, 1, 2,
        3, 4, 5,
        6, 7, 8,
        9, 10, 11,
        12, 13, 14,
        15, 16, 17
    }

    -- Calculate face normals now
    for i = 0, numVertices - 1, 3 do
        local v1 = Vector3(vertexData[6 * i + 1], vertexData[6 * i + 2], vertexData[6 * i + 3])
        local v2 = Vector3(vertexData[6 * i + 7], vertexData[6 * i + 8], vertexData[6 * i + 9])
        local v3 = Vector3(vertexData[6 * i + 13], vertexData[6 * i + 14], vertexData[6 * i + 15])

        local edge1 = v1 - v2
        local edge2 = v1 - v3
        local normal = edge1:CrossProduct(edge2):Normalized()
        vertexData[6 * i + 4] = normal.x
        vertexData[6 * i + 5] = normal.y
        vertexData[6 * i + 6] = normal.z
        vertexData[6 * i + 10] = normal.x
        vertexData[6 * i + 11] = normal.y
        vertexData[6 * i + 12] = normal.z
        vertexData[6 * i + 16] = normal.x
        vertexData[6 * i + 17] = normal.y
        vertexData[6 * i + 18] = normal.z
    end

    -- Create model, buffers and geometry without garbage collection, as they will be managed
    -- by the StaticModel component once assigned to it
    local fromScratchModel = Model:new()
    local vb = VertexBuffer:new()
    local ib = IndexBuffer:new()
    local geom = Geometry:new()

    -- Shadowed buffer needed for raycasts to work, and so that data can be automatically restored on device loss
    vb.shadowed = true
    -- We could use the "legacy" element bitmask to define elements for more compact code, but let's demonstrate
    -- defining the vertex elements explicitly to allow any element types and order
    local elements = {
        VertexElement(TYPE_VECTOR3, SEM_POSITION),
        VertexElement(TYPE_VECTOR3, SEM_NORMAL)
    }
    vb:SetSize(numVertices, elements)
    local temp = VectorBuffer()
    for i = 1, numVertices * 6 do
        temp:WriteFloat(vertexData[i])
    end
    vb:SetData(temp)

    ib.shadowed = true
    ib:SetSize(numVertices, false)
    temp:Clear()
    for i = 1, numVertices do
        temp:WriteUShort(indexData[i])
    end
    ib:SetData(temp)

    geom:SetVertexBuffer(0, vb)
    geom:SetIndexBuffer(ib)
    geom:SetDrawRange(TRIANGLE_LIST, 0, numVertices)

    fromScratchModel.numGeometries = 1
    fromScratchModel:SetGeometry(0, 0, geom)
    fromScratchModel.boundingBox = BoundingBox(Vector3(-0.5, -0.5, -0.5), Vector3(0.5, 0.5, 0.5))

    local node = scene_:CreateChild("FromScratchObject")
    node.position = Vector3(0.0, 3.0, 0.0)
    local object = node:CreateComponent("StaticModel")
    object.model = fromScratchModel

    -- Create the camera. Create it outside the scene so that we can clear the whole scene without affecting it
    cameraNode = Node()
    cameraNode.position = Vector3(0.0, 2.0, -20.0)
    local camera = cameraNode:CreateComponent("Camera")
    camera.farClip = 300.0
end

function CreateInstructions()
    -- Construct new Text object, set string to display and font to use
    local instructionText = ui.root:CreateChild("Text")
    instructionText:SetText("Use WASD keys and mouse/touch to move\n"..
        "Space to toggle animation")
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
end

function AnimateObjects(timeStep)
    animTime = animTime + timeStep * 100.0;

    -- Repeat for each of the cloned vertex buffers
    for i = 1, table.getn(animatingBuffers) do
        local startPhase = animTime + i * 30.0
        local buffer = animatingBuffers[i]

        -- Need to prepare a VectorBuffer with all data (positions, normals, uvs...)
        local newData = VectorBuffer()
        local numVertices = buffer.vertexCount
        local vertexSize = buffer.vertexSize
        for j = 1, numVertices do
            -- If there are duplicate vertices, animate them in phase of the original
            local phase = startPhase + vertexDuplicates[j] * 10.0
            local src = originalVertices[j]
            local dest = Vector3(src.x * (1.0 + 0.1 * Sin(phase)),
                src.y * (1.0 + 0.1 * Sin(phase + 60.0)),
                src.z * (1.0 + 0.1 * Sin(phase + 120.0)))

            -- Write position
            newData:WriteVector3(dest)
            -- Copy other vertex elements
            originalVertexData:Seek((j - 1) * vertexSize + 12) -- Seek past the vertex position
            for k = 12, vertexSize - 4, 4 do
                newData:WriteFloat(originalVertexData:ReadFloat())
            end
        end

        buffer:SetData(newData)
    end
end

function HandleUpdate(eventType, eventData)
    -- Take the frame time step, which is stored as a float
    local timeStep = eventData["TimeStep"]:GetFloat()

    -- Toggle animation with space
    if input:GetKeyPress(KEY_SPACE) then
        animate = not animate
    end

    -- Move the camera, scale movement with time step
    MoveCamera(timeStep)

    -- Animate scene if enabled
    if animate then
        AnimateObjects(timeStep)
    end
end

-- Create XML patch instructions for screen joystick layout specific to this sample app
function GetScreenJoystickPatchString()
    return
        "<patch>" ..
        "    <remove sel=\"/element/element[./attribute[@name='Name' and @value='Button0']]/attribute[@name='Is Visible']\" />" ..
        "    <replace sel=\"/element/element[./attribute[@name='Name' and @value='Button0']]/element[./attribute[@name='Name' and @value='Label']]/attribute[@name='Text']/@value\">Animation</replace>" ..
        "    <add sel=\"/element/element[./attribute[@name='Name' and @value='Button0']]\">" ..
        "        <element type=\"Text\">" ..
        "            <attribute name=\"Name\" value=\"KeyBinding\" />" ..
        "            <attribute name=\"Text\" value=\"SPACE\" />" ..
        "        </element>" ..
        "    </add>" ..
        "</patch>"
end
