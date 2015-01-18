// Common sample initialization as a framework for all samples.
//    - Create Urho3D logo at screen;
//    - Set custom window title and icon;
//    - Create Console and Debug HUD, and use F1 and F2 key to toggle them;
//    - Toggle rendering options from the keys 1-8;
//    - Take screenshots with key 9;
//    - Handle Esc key down to hide Console or exit application;
//    - Init touch input on mobile platform using screen joysticks (patched for each individual sample)

Sprite@ logoSprite;
Scene@ scene_;
uint screenJoystickIndex = M_MAX_UNSIGNED; // Screen joystick index for navigational controls (mobile platforms only)
uint screenJoystickSettingsIndex = M_MAX_UNSIGNED; // Screen joystick index for settings (mobile platforms only)
bool touchEnabled = false; // Flag to indicate whether touch input has been enabled
bool paused = false; // Pause flag
bool drawDebug = false; // Draw debug geometry flag
Node@ cameraNode; // Camera scene node
float yaw = 0.0f; // Camera yaw angle
float pitch = 0.0f; // Camera pitch angle
const float TOUCH_SENSITIVITY = 2;

void SampleStart()
{
    if (GetPlatform() == "Android" || GetPlatform() == "iOS" || input.touchEmulation)
        // On mobile platform, enable touch by adding a screen joystick
        InitTouchInput();
    else if (input.numJoysticks == 0)
        // On desktop platform, do not detect touch when we already got a joystick
        SubscribeToEvent("TouchBegin", "HandleTouchBegin");

    // Create logo
    CreateLogo();

    // Set custom window Title & Icon
    SetWindowTitleAndIcon();

    // Create console and debug HUD
    CreateConsoleAndDebugHud();

    // Subscribe key down event
    SubscribeToEvent("KeyDown", "HandleKeyDown");

    // Subscribe scene update event
    SubscribeToEvent("SceneUpdate", "HandleSceneUpdate");
}

void InitTouchInput()
{
    touchEnabled = true;

    XMLFile@ layout = cache.GetResource("XMLFile", "UI/ScreenJoystick_Samples.xml");
    if (!patchInstructions.empty)
    {
        // Patch the screen joystick layout further on demand
        XMLFile@ patchFile = XMLFile();
        if (patchFile.FromString(patchInstructions))
            layout.Patch(patchFile);
    }
    screenJoystickIndex = input.AddScreenJoystick(layout, cache.GetResource("XMLFile", "UI/DefaultStyle.xml"));
    input.screenJoystickVisible[0] = true;
}

void SetLogoVisible(bool enable)
{
    if (logoSprite !is null)
        logoSprite.visible = enable;
}

void CreateLogo()
{
    // Get logo texture
    Texture2D@ logoTexture = cache.GetResource("Texture2D", "Textures/LogoLarge.png");
    if (logoTexture is null)
        return;

    // Create logo sprite and add to the UI layout
    logoSprite = ui.root.CreateChild("Sprite");

    // Set logo sprite texture
    logoSprite.texture = logoTexture;

    int textureWidth = logoTexture.width;
    int textureHeight = logoTexture.height;

    // Set logo sprite scale
    logoSprite.SetScale(256.0f / textureWidth);

    // Set logo sprite size
    logoSprite.SetSize(textureWidth, textureHeight);

    // Set logo sprite hot spot
    logoSprite.SetHotSpot(0, textureHeight);

    // Set logo sprite alignment
    logoSprite.SetAlignment(HA_LEFT, VA_BOTTOM);

    // Make logo not fully opaque to show the scene underneath
    logoSprite.opacity = 0.75f;

    // Set a low priority for the logo so that other UI elements can be drawn on top
    logoSprite.priority = -100;
}

void SetWindowTitleAndIcon()
{
    Image@ icon = cache.GetResource("Image", "Textures/UrhoIcon.png");
    graphics.windowIcon = icon;
    graphics.windowTitle = "Urho3D Sample";
}

void CreateConsoleAndDebugHud()
{
    // Get default style
    XMLFile@ xmlFile = cache.GetResource("XMLFile", "UI/DefaultStyle.xml");
    if (xmlFile is null)
        return;

    // Create console
    Console@ console = engine.CreateConsole();
    console.defaultStyle = xmlFile;
    console.background.opacity = 0.8f;

    // Create debug HUD
    DebugHud@ debugHud = engine.CreateDebugHud();
    debugHud.defaultStyle = xmlFile;
}

void HandleKeyDown(StringHash eventType, VariantMap& eventData)
{
    int key = eventData["Key"].GetInt();

    // Close console (if open) or exit when ESC is pressed
    if (key == KEY_ESC)
    {
        if (!console.visible)
            engine.Exit();
        else
            console.visible = false;
    }

    // Toggle console with F1
    else if (key == KEY_F1)
        console.Toggle();

    // Toggle debug HUD with F2
    else if (key == KEY_F2)
        debugHud.ToggleAll();

    // Common rendering quality controls, only when UI has no focused element
    if (ui.focusElement is null)
    {
        // Preferences / Pause
        if (key == KEY_SELECT && touchEnabled)
        {
            paused = !paused;

            if (screenJoystickSettingsIndex == M_MAX_UNSIGNED)
            {
                // Lazy initialization
                screenJoystickSettingsIndex = input.AddScreenJoystick(cache.GetResource("XMLFile", "UI/ScreenJoystickSettings_Samples.xml"), cache.GetResource("XMLFile", "UI/DefaultStyle.xml"));
            }
            else
                input.screenJoystickVisible[screenJoystickSettingsIndex] = paused;
        }

        // Texture quality
        else if (key == '1')
        {
            int quality = renderer.textureQuality;
            ++quality;
            if (quality > QUALITY_HIGH)
                quality = QUALITY_LOW;
            renderer.textureQuality = quality;
        }

        // Material quality
        else if (key == '2')
        {
            int quality = renderer.materialQuality;
            ++quality;
            if (quality > QUALITY_HIGH)
                quality = QUALITY_LOW;
            renderer.materialQuality = quality;
        }

        // Specular lighting
        else if (key == '3')
            renderer.specularLighting = !renderer.specularLighting;

        // Shadow rendering
        else if (key == '4')
            renderer.drawShadows = !renderer.drawShadows;

        // Shadow map resolution
        else if (key == '5')
        {
            int shadowMapSize = renderer.shadowMapSize;
            shadowMapSize *= 2;
            if (shadowMapSize > 2048)
                shadowMapSize = 512;
            renderer.shadowMapSize = shadowMapSize;
        }

        // Shadow depth and filtering quality
        else if (key == '6')
        {
            int quality = renderer.shadowQuality;
            ++quality;
            if (quality > SHADOWQUALITY_HIGH_24BIT)
                quality = SHADOWQUALITY_LOW_16BIT;
            renderer.shadowQuality = quality;
        }

        // Occlusion culling
        else if (key == '7')
        {
            bool occlusion = renderer.maxOccluderTriangles > 0;
            occlusion = !occlusion;
            renderer.maxOccluderTriangles = occlusion ? 5000 : 0;
        }

        // Instancing
        else if (key == '8')
            renderer.dynamicInstancing = !renderer.dynamicInstancing;

        // Take screenshot
        else if (key == '9')
        {
            Image@ screenshot = Image();
            graphics.TakeScreenShot(screenshot);
            // Here we save in the Data folder with date and time appended
            screenshot.SavePNG(fileSystem.programDir + "Data/Screenshot_" +
                time.timeStamp.Replaced(':', '_').Replaced('.', '_').Replaced(' ', '_') + ".png");
        }
    }
}

void HandleSceneUpdate(StringHash eventType, VariantMap& eventData)
{
    // Move the camera by touch, if the camera node is initialized by descendant sample class
    if (touchEnabled && cameraNode !is null)
    {
        for (uint i = 0; i < input.numTouches; ++i)
        {
            TouchState@ state = input.touches[i];
            if (state.touchedElement is null) // Touch on empty space
            {
                if (state.delta.x !=0 || state.delta.y !=0)
                {
                    Camera@ camera = cameraNode.GetComponent("Camera");
                    if (camera is null)
                        return;

                    yaw += TOUCH_SENSITIVITY * camera.fov / graphics.height * state.delta.x;
                    pitch += TOUCH_SENSITIVITY * camera.fov / graphics.height * state.delta.y;

                    // Construct new orientation for the camera scene node from yaw and pitch; roll is fixed to zero
                    cameraNode.rotation = Quaternion(pitch, yaw, 0.0f);
                }
                else
                {
                    // Move the cursor to the touch position
                    Cursor@ cursor = ui.cursor;
                    if (cursor !is null && cursor.visible)
                        cursor.position = state.position;
                }
            }
        }
    }
}

void HandleTouchBegin(StringHash eventType, VariantMap& eventData)
{
    // On some platforms like Windows the presence of touch input can only be detected dynamically
    InitTouchInput();
    UnsubscribeFromEvent("TouchBegin");
}
