-- PBR materials example.
-- This sample demonstrates:
--      - Loading a scene that showcases physically based materials & shaders
--
-- To use with deferred rendering, a PBR deferred renderpath should be chosen:
-- CoreData/RenderPaths/PBRDeferred.xml or CoreData/RenderPaths/PBRDeferredHWDepth.xml

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
    local file = cache:GetFile("Scenes/PBRExample.xml")
    scene_:LoadXML(file)
    -- In Lua the file returned by GetFile() needs to be deleted manually
    file:delete()

    -- Create the camera (not included in the scene file)
    cameraNode = scene_:CreateChild("Camera")
    cameraNode:CreateComponent("Camera")

    -- Set an initial position for the camera scene node above the plane
    cameraNode.position = Vector3(0.0, 4.0, 0.0)
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
end

function SetupViewport()
    renderer.hdrRendering = true;

    -- Set up a viewport to the Renderer subsystem so that the 3D scene can be seen
    local viewport = Viewport:new(scene_, cameraNode:GetComponent("Camera"))
    renderer:SetViewport(0, viewport)

    -- Add post-processing effects appropriate with the example scene
    local effectRenderPath = viewport:GetRenderPath():Clone()
    effectRenderPath:Append(cache:GetResource("XMLFile", "PostProcess/BloomHDR.xml"))
    effectRenderPath:Append(cache:GetResource("XMLFile", "PostProcess/FXAA2.xml"))
    effectRenderPath:Append(cache:GetResource("XMLFile", "PostProcess/GammaCorrection.xml"))

    viewport.renderPath = effectRenderPath;
end

function SubscribeToEvents()
    -- Subscribe HandleUpdate() function for camera motion
    SubscribeToEvent("Update", "HandleUpdate")
end

function HandleUpdate(eventType, eventData)
    -- Take the frame time step, which is stored as a float
    local timeStep = eventData["TimeStep"]:GetFloat()

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
    local MOVE_SPEED = 10.0
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
