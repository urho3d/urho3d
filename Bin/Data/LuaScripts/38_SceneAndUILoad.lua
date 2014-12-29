-- Scene & UI load example.
-- This sample demonstrates:
--      - Loading a scene from a file and showing it
--      - Loading a UI layout from a file and showing it
--      - Subscribing to the UI layout's events

require "LuaScripts/Utilities/Sample"

function Start()
    -- Execute the common startup for samples
    SampleStart()

    -- Create the scene content
    CreateScene()

    -- Create the UI content
    CreateUI()

    -- Setup the viewport for displaying the scene
    SetupViewport()

    -- Subscribe to global events for camera movement
    SubscribeToEvents()
end

function CreateScene()
    scene_ = Scene()

    -- Load scene content prepared in the editor (XML format). GetFile() returns an open file from the resource system
    -- which scene.LoadXML() will read
    local file = cache:GetFile("Scenes/SceneLoadExample.xml")
    scene_:LoadXML(file)
    -- In Lua the file returned by GetFile() needs to be deleted manually
    file:delete()

    -- Create the camera (not included in the scene file)
    cameraNode = scene_:CreateChild("Camera")
    cameraNode:CreateComponent("Camera")

    -- Set an initial position for the camera scene node above the plane
    cameraNode.position = Vector3(0.0, 2.0, -10.0)
end

function CreateUI()
    -- Set up global UI style into the root UI element
    local style = cache:GetResource("XMLFile", "UI/DefaultStyle.xml")
    ui.root.defaultStyle = style

    -- Create a Cursor UI element because we want to be able to hide and show it at will. When hidden, the mouse cursor will
    -- control the camera, and when visible, it will interact with the UI
    local cursor = ui.root:CreateChild("Cursor")
    cursor:SetStyleAuto()
    ui.cursor = cursor
    -- Set starting position of the cursor at the rendering window center
    cursor:SetPosition(graphics.width / 2, graphics.height / 2)

    -- Load UI content prepared in the editor and add to the UI hierarchy
    local layoutRoot = ui:LoadLayout(cache:GetResource("XMLFile", "UI/UILoadExample.xml"))
    ui.root:AddChild(layoutRoot)

    -- Subscribe to button actions (toggle scene lights when pressed then released)
    local button = layoutRoot:GetChild("ToggleLight1", true)
    if button ~= nil then
        SubscribeToEvent(button, "Released", "ToggleLight1")
    end
    button = layoutRoot:GetChild("ToggleLight2", true)
    if button ~= nil then
        SubscribeToEvent(button, "Released", "ToggleLight2")
    end
end

function ToggleLight1()
    local lightNode = scene_:GetChild("Light1", true)
    if lightNode  ~= nil then
        lightNode.enabled = not lightNode.enabled
    end
end

function ToggleLight2()
    local lightNode = scene_:GetChild("Light2", true)
    if lightNode  ~= nil then
        lightNode.enabled = not lightNode.enabled
    end
end


function SetupViewport()
    -- Set up a viewport to the Renderer subsystem so that the 3D scene can be seen
    local viewport = Viewport:new(scene_, cameraNode:GetComponent("Camera"))
    renderer:SetViewport(0, viewport)
end

function SubscribeToEvents()
    -- Subscribe HandleUpdate() function for camera motion
    SubscribeToEvent("Update", "HandleUpdate")
end

function HandleUpdate(eventType, eventData)
    -- Take the frame time step, which is stored as a float
    local timeStep = eventData:GetFloat("TimeStep")

    -- Move the camera, scale movement with time step
    MoveCamera(timeStep)
end

function MoveCamera(timeStep)
    -- Right mouse button controls mouse cursor visibility: hide when pressed
    ui.cursor.visible = not input:GetMouseButtonDown(MOUSEB_RIGHT)

    -- Do not move if the UI has a focused element
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
end
