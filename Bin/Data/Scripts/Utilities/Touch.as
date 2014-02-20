// Mobile framework for Android/iOS
// Gamepad from NinjaSnowWar
// Gyroscope (activated by default)
// Touches patterns:
//     - 1 finger touch  = pick object through raycast
//     - 1 or 2 fingers drag  = rotate camera
//     - 3 fingers touch = switch between first/third person view
//     - 4 fingers touch = switch shadows on/off
//     - 2 fingers sliding in opposite direction (up/down) = zoom in/out

// 3 fingers touch & 4 fingers touch could be used to switch gyroscope on/off, activate/deactivate secondary viewport, activate a panel GUI, switch debug HUD/geometry, toggle console, switch the gyroscope...

// Setup:
// - On init, call this script using '#include "Scripts/Utilities/Touch.as"' then 'InitTouchInput()' on mobile platforms
//   -> to detect platform, use 'if (GetPlatform() == "Android" || GetPlatform() == "iOS")'
// - Subscribe to touch events (Begin, Move, End) using 'SubscribeToTouchEvents()'
// - Call the update function 'UpdateTouches()' from HandleUpdate or equivalent update handler function

const float TOUCH_SENSITIVITY = 5.0;
const float GYROSCOPE_THRESHOLD = 0.1;
const float CAMERA_MIN_DIST = 1.0f;
const float CAMERA_INITIAL_DIST = 5.0f;
const float CAMERA_MAX_DIST = 20.0f;

bool firstPerson = false;
bool touchEnabled = false;
bool zoom = false;
bool newFirstPerson = false;
bool shadowMode = true;

Node@ cameraNode;
float cameraDistance = CAMERA_INITIAL_DIST;

BorderImage@ moveButton;
BorderImage@ fireButton;
int touchButtonSize = 96;
int touchButtonBorder = 12;
int moveTouchID = -1;
int rotateTouchID = -1;
int fireTouchID = -1;

void InitTouchInput() // Create Gamepad Buttons
{
    moveButton = ui.root.CreateChild("BorderImage");
    moveButton.texture = cache.GetResource("Texture2D", "Textures/TouchInput.png");
    moveButton.imageRect = IntRect(0, 0, 96, 96);
    moveButton.SetAlignment(HA_LEFT, VA_BOTTOM);
    moveButton.SetPosition(touchButtonBorder, -touchButtonBorder);
    moveButton.SetSize(touchButtonSize, touchButtonSize);
    moveButton.opacity = 0.25;

    fireButton = ui.root.CreateChild("BorderImage");
    fireButton.texture = cache.GetResource("Texture2D", "Textures/TouchInput.png");
    fireButton.imageRect = IntRect(96, 0, 192, 96);
    fireButton.SetAlignment(HA_RIGHT, VA_BOTTOM);
    fireButton.SetPosition(-touchButtonBorder, -touchButtonBorder);
    fireButton.SetSize(touchButtonSize, touchButtonSize);
    fireButton.opacity = 0.25;
    
    touchEnabled = true;
}

void SubscribeToTouchEvents()
{
    SubscribeToEvent("TouchBegin", "HandleTouchBegin");
    SubscribeToEvent("TouchEnd", "HandleTouchEnd");
}

void UpdateTouches(Controls& controls) // Called from HandleUpdate
{
    Camera@ camera = cameraNode.GetComponent("Camera");
    zoom = false; // reset bool

    // Touch Inputs
    if (touchEnabled)
    {
        // Zoom in/out
        if (input.numTouches == 2)
        {
            TouchState@ touch1 = input.touches[0];
            TouchState@ touch2 = input.touches[1];

            // Check for zoom pattern (touches moving in opposite directions)
            if ((touch1.delta.y > 0 && touch2.delta.y < 0) || (touch1.delta.y < 0 && touch2.delta.y > 0))
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

        // Switch 1st/3rd person mode
        if (input.numTouches == 3)
            newFirstPerson = !firstPerson;

        // Switch draw debug
        if (input.numTouches == 4)
            shadowMode = !renderer.drawShadows;

        // Rotate and Move
        if (!zoom)
        {
            for (uint i = 0; i < input.numTouches; ++i)
            {
                TouchState@ touch = input.touches[i];

                if (touch.touchID == rotateTouchID)
                {
                    controls.yaw += TOUCH_SENSITIVITY * camera.fov / graphics.height * touch.delta.x;
                    controls.pitch += TOUCH_SENSITIVITY * camera.fov / graphics.height * touch.delta.y;
                    controls.pitch = Clamp(controls.pitch, -80.0f, 80.0f); // Limit pitch
                }

                if (touch.touchID == moveTouchID)
                {
                    int relX = touch.position.x - moveButton.screenPosition.x - touchButtonSize / 2;
                    int relY = touch.position.y - moveButton.screenPosition.y - touchButtonSize / 2;
                    if (relY < 0 && Abs(relX * 3 / 2) < Abs(relY))
                        controls.Set(CTRL_FORWARD, true);
                    if (relY > 0 && Abs(relX * 3 / 2) < Abs(relY))
                        controls.Set(CTRL_BACK, true);
                    if (relX < 0 && Abs(relY * 3 / 2) < Abs(relX))
                        controls.Set(CTRL_LEFT, true);
                    if (relX > 0 && Abs(relY * 3 / 2) < Abs(relX))
                        controls.Set(CTRL_RIGHT, true);
                }
            }
        }

        if (fireTouchID >= 0)
            controls.Set(CTRL_JUMP, true);
    }

    // Gyroscope (emulated by SDL through a virtual joystick)
    if (input.numJoysticks > 0) // numJoysticks = 1 on iOS & Android
    {
        JoystickState@ joystick = input.joysticks[0];
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

void HandleTouchBegin(StringHash eventType, VariantMap& eventData)
{
    int touchID = eventData["TouchID"].GetInt(); // Get #touches or dragging value
    IntVector2 pos(eventData["X"].GetInt(), eventData["Y"].GetInt()); // Get touch coordinates
    UIElement@ element = ui.GetElementAt(pos, false); // Get gamepad UIElement touched (if any)

    // Check for gamepad button touched. If none, rotate
    if (element is moveButton)
        moveTouchID = touchID;
    else if (element is fireButton)
        fireTouchID = touchID;
    else
        rotateTouchID = touchID;

    // Init Raycast (for example to acquire a target)
    Camera@ camera = cameraNode.GetComponent("Camera");
    Ray cameraRay = camera.GetScreenRay(float(eventData["X"].GetInt()) / graphics.width, float(eventData["Y"].GetInt()) / graphics.height);

    // Raycast of RigidBodies
    PhysicsRaycastResult result = scene_.physicsWorld.RaycastSingle(cameraRay, camera.farClip, 2); // NB: here we restrict targets to layer 2
    if (result.body !is null)
        log.Info("Physics raycast hit " + result.body.node.name);

    // Raycast of drawable components (for targets without physics)
    RayQueryResult result2 = scene_.octree.RaycastSingle(cameraRay, RAY_TRIANGLE, camera.farClip, DRAWABLE_GEOMETRY);
    if (result2.drawable !is null)
        log.Info("Drawable raycast hit " + result2.drawable.node.name);
}

void HandleTouchEnd(StringHash eventType, VariantMap& eventData)
{
    int touchID = eventData["TouchID"].GetInt();

    if (touchID == moveTouchID)
        moveTouchID = -1;
    if (touchID == rotateTouchID)
        rotateTouchID = -1;
    if (touchID == fireTouchID)
        fireTouchID = -1;

    // On-release Update
    firstPerson = newFirstPerson;
    renderer.drawShadows = shadowMode;
}
