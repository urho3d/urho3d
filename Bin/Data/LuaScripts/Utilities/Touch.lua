-- Mobile framework for Android/iOS
-- Gamepad from Ninja Snow War
-- Gyroscope (activated by default)
-- Touches patterns:
--     - 1 finger touch  = pick object through raycast
--     - 1 or 2 fingers drag  = rotate camera
--     - 3 fingers touch = switch between first/third person view
--     - 4 fingers touch = switch shadows on/off
--     - 2 fingers sliding in opposite direction (up/down) = zoom in/out

-- 3 fingers touch & 4 fingers touch could be used to switch gyroscope on/off, activate/deactivate secondary viewport, activate a panel GUI, switch debug HUD/geometry, toggle console, switch the gyroscope...

-- Setup:
-- - On init, call this script using 'require "LuaScripts/Utilities/Touch" end' then 'InitTouchInput()' on mobile platforms
--   -> to detect platform, use 'if GetPlatform() == "Android" or GetPlatform() == "iOS"')
-- - Subscribe to touch events (Begin, Move, End) using 'SubscribeToTouchEvents()'
-- - Call the update function 'updateTouches()' from HandleUpdate or equivalent update handler function

TOUCH_SENSITIVITY = 5.0
GYROSCOPE_THRESHOLD = 0.1
CAMERA_MIN_DIST = 1.0
CAMERA_INITIAL_DIST = 5.0
CAMERA_MAX_DIST = 20.0

local moveTouchID = -1
local rotateTouchID = -1
local fireTouchID = -1
local moveButton
local fireButton
local touchButtonSize = 96
local touchButtonBorder = 12
local zoom = false
local newFirstPerson = nil
local shadowMode = true

firstPerson = false
touchEnabled = false
cameraDistance = CAMERA_INITIAL_DIST
cameraNode = nil

-- Create Gamepad Buttons

function InitTouchInput()
    moveButton = ui.root:CreateChild("BorderImage")
    moveButton.texture = cache:GetResource("Texture2D", "Textures/TouchInput.png")
    moveButton.imageRect = IntRect(0, 0, 96, 96) -- Crop right side of the texture
    moveButton:SetAlignment(HA_LEFT, VA_BOTTOM)
    moveButton:SetPosition(touchButtonBorder, -touchButtonBorder)
    moveButton:SetSize(touchButtonSize, touchButtonSize)
    moveButton.opacity = 0.25

    fireButton = ui.root:CreateChild("BorderImage")
    fireButton.texture = cache:GetResource("Texture2D", "Textures/TouchInput.png")
    fireButton.imageRect = IntRect(96, 0, 192, 96) -- Crop left side of the texture
    fireButton:SetAlignment(HA_RIGHT, VA_BOTTOM)
    fireButton:SetPosition(-touchButtonBorder, -touchButtonBorder)
    fireButton:SetSize(touchButtonSize, touchButtonSize)
    fireButton.opacity = 0.25

    touchEnabled = true
end

function SubscribeToTouchEvents()
    SubscribeToEvent("TouchBegin", "HandleTouchBegin")
    SubscribeToEvent("TouchEnd", "HandleTouchEnd")
end

function updateTouches(controls) -- Called from HandleUpdate
    local controls = characterNode:GetScriptObject().controls
    local camera = cameraNode:GetComponent("Camera")
    zoom = false -- reset bool

    -- Touch Inputs
    if touchEnabled then

        -- Zoom in/out
        if input.numTouches == 2 then
            local touch1 = input:GetTouch(0)
            local touch2 = input:GetTouch(1)

            -- Check for zoom pattern (touches moving in opposite directions)
            if (touch1.delta.y > 0 and touch2.delta.y < 0) or (touch1.delta.y < 0 and touch2.delta.y > 0) then zoom = true else zoom = false end

            -- Check for zoom direction (in/out)
            if zoom then
                if Abs(touch1.position.y - touch2.position.y) > Abs(touch1.lastPosition.y - touch2.lastPosition.y) then sens = -1 else sens = 1 end
                cameraDistance = cameraDistance + Abs(touch1.delta.y - touch2.delta.y) * sens * TOUCH_SENSITIVITY / 50
                cameraDistance = Clamp(cameraDistance, CAMERA_MIN_DIST, CAMERA_MAX_DIST) -- Restrict zoom range to [1;20]
            end
        end

        -- Switch 1st/3rd person mode
        if input.numTouches == 3 then newFirstPerson = not firstPerson end

        -- Switch draw debug
        if input.numTouches == 4 then shadowMode = not renderer.drawShadows end

        -- Rotate and Move
        if not zoom then
            for i = 0, input.numTouches-1 do -- numtouches=[0;4]

                local touch = input:GetTouch(i) -- TouchState

                if touch.touchID == rotateTouchID then
                    controls.yaw = controls.yaw + TOUCH_SENSITIVITY * camera.fov / graphics.height * touch.delta.x
                    controls.pitch = controls.pitch + TOUCH_SENSITIVITY * camera.fov / graphics.height * touch.delta.y
                    controls.pitch = Clamp(controls.pitch, -80, 80) -- Limit pitch
                end

                if touch.touchID == moveTouchID then
                    local relX = touch.position.x - moveButton.screenPosition.x - touchButtonSize / 2
                    local relY = touch.position.y - moveButton.screenPosition.y - touchButtonSize / 2
                        if relY < 0 and Abs(relX * 3 / 2) < Abs(relY) then controls:Set(CTRL_FORWARD, true) end
                        if relY > 0 and Abs(relX * 3 / 2) < Abs(relY) then controls:Set(CTRL_BACK, true) end
                        if relX < 0 and Abs(relY * 3 / 2) < Abs(relX) then controls:Set(CTRL_LEFT, true) end
                        if relX > 0 and Abs(relY * 3 / 2) < Abs(relX) then controls:Set(CTRL_RIGHT, true) end
                    end
                end
        end

        if fireTouchID >= 0 then controls:Set(CTRL_JUMP, true) end
    end

    -- Gyroscope (emulated by SDL through a virtual joystick)
    if input.numJoysticks > 0 then -- numJoysticks = 1 on iOS & Android
        local joystick = input:GetJoystick(0) -- JoystickState
        if joystick.numAxes >= 2 then
            if joystick:GetAxisPosition(0) < -GYROSCOPE_THRESHOLD then controls:Set(CTRL_LEFT, true) end
            if joystick:GetAxisPosition(0) > GYROSCOPE_THRESHOLD then controls:Set(CTRL_RIGHT, true) end
            if joystick:GetAxisPosition(1) < -GYROSCOPE_THRESHOLD then controls:Set(CTRL_FORWARD, true) end
            if joystick:GetAxisPosition(1) > GYROSCOPE_THRESHOLD then controls:Set(CTRL_BACK, true) end
        end
    end
end

function HandleTouchBegin(eventType, eventData)

    local touchID = eventData:GetInt("TouchID") -- Get #touches or dragging value

    local pos = IntVector2(eventData:GetInt("X"), eventData:GetInt("Y")) -- Get touch coordinates
    local element = ui:GetElementAt(pos, false) -- Get gamepad UIElement touched (if any)

    -- Check for gamepad button touched. If none, rotate
    if element == moveButton then moveTouchID = touchID
    elseif element == fireButton then fireTouchID = touchID
    else rotateTouchID = touchID end

    -- Raycast of RigidBodies (for example to acquire a target)
    local camera = cameraNode:GetComponent("Camera")
    local cameraRay = camera:GetScreenRay(eventData:GetInt("X") / graphics.width, eventData:GetInt("Y") / graphics.height)
    local result = scene_:GetComponent("PhysicsWorld"):RaycastSingle(cameraRay, camera.farClip, 2) -- NB: here we restrict targets to layer 2
    if result.body ~= nil then print("Physics raycast hit " .. result.body:GetNode().name) end

    -- Raycast of drawable components (for targets with or without physics)
    local result2 = scene_:GetComponent("Octree"):RaycastSingle(cameraRay, RAY_TRIANGLE, camera.farClip, DRAWABLE_GEOMETRY)
    if result2.drawable ~= nil then print("Drawable raycast hit " .. result2.drawable:GetNode().name) end
end


function HandleTouchEnd(eventType, eventData)
    local touchID = eventData:GetInt("TouchID")

    if touchID == moveTouchID then moveTouchID = -1 end
    if touchID == rotateTouchID then rotateTouchID = -1 end
    if touchID == fireTouchID then fireTouchID = -1 end

    -- On-release Update
    firstPerson = newFirstPerson
    renderer.drawShadows = shadowMode
end
