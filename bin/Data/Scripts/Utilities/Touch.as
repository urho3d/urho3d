// Mobile framework for Android/iOS
// Gamepad from NinjaSnowWar
// Touches patterns:
//     - 1 finger touch  = pick object through raycast
//     - 1 or 2 fingers drag  = rotate camera
//     - 2 fingers sliding in opposite direction (up/down) = zoom in/out

// Setup: Call the update function 'UpdateTouches()' from HandleUpdate or equivalent update handler function

const float GYROSCOPE_THRESHOLD = 0.1;
const float CAMERA_MIN_DIST = 1.0f;
const float CAMERA_MAX_DIST = 20.0f;

bool zoom = false;
bool useGyroscope = false;
float cameraDistance = 5.0;

void UpdateTouches(Controls& controls) // Called from HandleUpdate
{
    zoom = false; // reset bool

    // Zoom in/out
    if (input.numTouches == 2)
    {
        TouchState@ touch1 = input.touches[0];
        TouchState@ touch2 = input.touches[1];

        // Check for zoom pattern (touches moving in opposite directions)
        if (touch1.touchedElement is null && touch2.touchedElement is null && ((touch1.delta.y > 0 && touch2.delta.y < 0) || (touch1.delta.y < 0 && touch2.delta.y > 0)))
            zoom = true;
        else
            zoom = false;

        if (zoom)
        {
            int sens = 0;
            // Check for zoom direction (in/out)
            if (Abs(touch1.position.y - touch2.position.y) > Abs(touch1.lastPosition.y - touch2.lastPosition.y))
                sens = -1;
            else
                sens = 1;
            cameraDistance += Abs(touch1.delta.y - touch2.delta.y) * sens * TOUCH_SENSITIVITY / 50;
            cameraDistance = Clamp(cameraDistance, CAMERA_MIN_DIST, CAMERA_MAX_DIST); // Restrict zoom range to [1;20]
        }
    }

    // Gyroscope (emulated by SDL through a virtual joystick)
    if (input.numJoysticks > 0) // numJoysticks = 1 on iOS & Android
    {
        JoystickState@ joystick = input.joysticksByIndex[0];
        if (joystick.numAxes >= 2)
        {
            if (joystick.axisPosition[0] < -GYROSCOPE_THRESHOLD)
                controls.Set(CTRL_LEFT, true);
            if (joystick.axisPosition[0] > GYROSCOPE_THRESHOLD)
                controls.Set(CTRL_RIGHT, true);
            if (joystick.axisPosition[1] < -GYROSCOPE_THRESHOLD)
                controls.Set(CTRL_FORWARD, true);
            if (joystick.axisPosition[1] > GYROSCOPE_THRESHOLD)
                controls.Set(CTRL_BACK, true);
        }
    }
}
