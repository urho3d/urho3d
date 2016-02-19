-- Mobile framework for Android/iOS
-- Gamepad from Ninja Snow War
-- Touches patterns:
--     - 1 finger touch  = pick object through raycast
--     - 1 or 2 fingers drag  = rotate camera
--     - 2 fingers sliding in opposite direction (up/down) = zoom in/out

-- Setup: Call the update function 'UpdateTouches()' from HandleUpdate or equivalent update handler function

local GYROSCOPE_THRESHOLD = 0.1
CAMERA_MIN_DIST = 1.0
CAMERA_MAX_DIST = 20.0

local zoom = false
useGyroscope = false
cameraDistance = 5.0

function UpdateTouches(controls) -- Called from HandleUpdate

    zoom = false -- reset bool

    -- Zoom in/out
    if input.numTouches == 2 then
        local touch1 = input:GetTouch(0)
        local touch2 = input:GetTouch(1)

        -- Check for zoom pattern (touches moving in opposite directions and on empty space)
        if not touch1.touchedElement and not touch2.touchedElement and ((touch1.delta.y > 0 and touch2.delta.y < 0) or (touch1.delta.y < 0 and touch2.delta.y > 0)) then zoom = true else zoom = false end

        -- Check for zoom direction (in/out)
        if zoom then
            if Abs(touch1.position.y - touch2.position.y) > Abs(touch1.lastPosition.y - touch2.lastPosition.y) then sens = -1 else sens = 1 end
            cameraDistance = cameraDistance + Abs(touch1.delta.y - touch2.delta.y) * sens * TOUCH_SENSITIVITY / 50
            cameraDistance = Clamp(cameraDistance, CAMERA_MIN_DIST, CAMERA_MAX_DIST) -- Restrict zoom range to [1;20]
        end
    end

    -- Gyroscope (emulated by SDL through a virtual joystick)
    if useGyroscope and input.numJoysticks > 0 then -- numJoysticks = 1 on iOS & Android
        local joystick = input:GetJoystickByIndex(0) -- JoystickState
        if joystick.numAxes >= 2 then
            if joystick:GetAxisPosition(0) < -GYROSCOPE_THRESHOLD then controls:Set(CTRL_LEFT, true) end
            if joystick:GetAxisPosition(0) > GYROSCOPE_THRESHOLD then controls:Set(CTRL_RIGHT, true) end
            if joystick:GetAxisPosition(1) < -GYROSCOPE_THRESHOLD then controls:Set(CTRL_FORWARD, true) end
            if joystick:GetAxisPosition(1) > GYROSCOPE_THRESHOLD then controls:Set(CTRL_BACK, true) end
        end
    end
end
