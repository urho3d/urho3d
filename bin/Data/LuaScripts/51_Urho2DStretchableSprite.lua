-- Urho2D stretchable sprite example.
-- This sample demonstrates:
--     - Creating a 2D scene with both static and stretchable sprites
--     - Difference in scaling static and stretchable sprites
--     - Similarity in otherwise transforming static and stretchable sprites
--     - Displaying the scene using the Renderer subsystem
--     - Handling keyboard to transform nodes

require "LuaScripts/Utilities/Sample"

local selectTransform = 0 -- Transform mode tracking index.
local refSpriteNode = nil -- Reference (static) sprite node.
local stretchSpriteNode = nil -- Stretchable sprite node.

function Start()
    -- Execute base class startup
    SampleStart()

    -- Create the scene content
    CreateScene()

    -- Create the UI content
    CreateInstructions()

    -- Setup the viewport for displaying the scene
    SetupViewport()

    -- Set the mouse mode to use in the sample
    SampleInitMouseMode(MM_FREE)

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

    -- Create a scene node for the camera, which we will move around
    -- The camera will use default settings (1000 far clip distance, 45 degrees FOV, set aspect ratio automatically)
    cameraNode = scene_:CreateChild("Camera")
    -- Set an initial position for the camera scene node above the plane
    cameraNode.position = Vector3(0.0, 0.0, -10.0)
    local camera = cameraNode:CreateComponent("Camera")
    camera.orthographic = true
    camera.orthoSize = graphics.height * PIXEL_SIZE

    -- Setup sprites and nodes on the scene
    refSpriteNode = scene_:CreateChild("regular sprite")
    stretchSpriteNode = scene_:CreateChild("stretch sprite")
    local sprite = cache:GetResource("Sprite2D", "Urho2D/Stretchable.png")
    if sprite then
        local staticSprite = refSpriteNode:CreateComponent("StaticSprite2D")
        staticSprite.sprite = sprite

        local stretchSprite = stretchSpriteNode:CreateComponent("StretchableSprite2D")
        stretchSprite.sprite = sprite
        stretchSprite.border = IntRect(25, 25, 25, 25)

        refSpriteNode:Translate2D(Vector2(-2, 0))
        stretchSpriteNode:Translate2D(Vector2(2, 0))
    end
end

function CreateInstructions()
    -- Construct new Text object, set string to display and font to use
    local instructionText = ui.root:CreateChild("Text")
    instructionText:SetText("Use WASD keys and mouse to move, Use PageUp PageDown to zoom.")
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

function SubscribeToEvents()
    -- Subscribe HandleUpdate() function for processing update events
    SubscribeToEvent("Update", "HandleUpdate")
    -- Subscribe HandleUpdate() function for processing update events
    SubscribeToEvent("KeyUp", "HandleKeyUp")

    -- Unsubscribe the SceneUpdate event from base class to prevent camera pitch and yaw in 2D sample
    UnsubscribeFromEvent("SceneUpdate")
end

function HandleUpdate(eventType, eventData)
    local timeStep = eventData["TimeStep"]:GetFloat()

    if selectTransform == 0 then
        ScaleSprites(timeStep)
    elseif selectTransform == 1 then
        RotateSprites(timeStep)
    elseif selectTransform == 2 then
        TranslateSprites(timeStep)
    else
        log:Write(LOG_ERROR, "bad transform selection " .. selectTransform)
  end
end

function HandleKeyUp(eventType, eventData)
    local key = eventData["Key"]:GetInt()

    if key == KEY_TAB then
        selectTransform = (selectTransform + 1) % 3
    elseif key == KEY_ESCAPE then
        engine:Exit()
    end
end

function TranslateSprites(timeStep)
    local speed = 1
    local left = input:GetKeyDown(KEY_A)
    local right = input:GetKeyDown(KEY_D)
    local up = input:GetKeyDown(KEY_W)
    local down = input:GetKeyDown(KEY_S)

    if left or right or up or down then
        local quantum = timeStep * speed
        local translate = Vector2((left and -quantum or 0) + (right and quantum or 0),
                                  (down and -quantum or 0) + (up and quantum or 0))

        refSpriteNode:Translate2D(translate)
        stretchSpriteNode:Translate2D(translate)
    end
end

function RotateSprites(timeStep)
    local speed = 45
    local left = input:GetKeyDown(KEY_A)
    local right = input:GetKeyDown(KEY_D)
    local up = input:GetKeyDown(KEY_W)
    local down = input:GetKeyDown(KEY_S)
    local ctrl = input:GetKeyDown(KEY_CTRL)

    if left or right or up or down then
        local quantum = timeStep * speed
        local xrot = (up and -quantum or 0) + (down and quantum or 0)
        local rot2 = (left and -quantum or 0) + (right and quantum or 0)
        local totalRot = Quaternion(xrot, ctrl and 0 or rot2, ctrl and rot2 or 0)

        refSpriteNode:Rotate(totalRot)
        stretchSpriteNode:Rotate(totalRot)
    end
end

function ScaleSprites(timeStep)
    local speed = 0.5
    local left = input:GetKeyDown(KEY_A)
    local right = input:GetKeyDown(KEY_D)
    local up = input:GetKeyDown(KEY_W)
    local down = input:GetKeyDown(KEY_S)

    if left or right or up or down then
        local quantum = timeStep * speed
        local scale = Vector2(1 + (right and quantum or left and -quantum or 0),
                              1 + (up and quantum or down and -quantum or 0))

        refSpriteNode:Scale2D(scale)
        stretchSpriteNode:Scale2D(scale)
    end
end


-- Create XML patch instructions for screen joystick layout specific to this sample app
function GetScreenJoystickPatchString()
    return
        "<patch>" ..
        "    <remove sel=\"/element/element[./attribute[@name='Name' and @value='Button0']]/attribute[@name='Is Visible']\" />" ..
        "    <replace sel=\"/element/element[./attribute[@name='Name' and @value='Button0']]/element[./attribute[@name='Name' and @value='Label']]/attribute[@name='Text']/@value\">TAB</replace>" ..
        "    <add sel=\"/element/element[./attribute[@name='Name' and @value='Button0']]\">" ..
        "        <element type=\"Text\">" ..
        "            <attribute name=\"Name\" value=\"KeyBinding\" />" ..
        "            <attribute name=\"Text\" value=\"TAB\" />" ..
        "        </element>" ..
        "    </add>" ..
        "    <remove sel=\"/element/element[./attribute[@name='Name' and @value='Button1']]/attribute[@name='Is Visible']\" />" ..
        "    <replace sel=\"/element/element[./attribute[@name='Name' and @value='Button1']]/element[./attribute[@name='Name' and @value='Label']]/attribute[@name='Text']/@value\">CTRL</replace>" ..
        "    <add sel=\"/element/element[./attribute[@name='Name' and @value='Button1']]\">" ..
        "        <element type=\"Text\">" ..
        "            <attribute name=\"Name\" value=\"KeyBinding\" />" ..
        "            <attribute name=\"Text\" value=\"LCTRL\" />" ..
        "        </element>" ..
        "    </add>" ..
        "</patch>"
end
