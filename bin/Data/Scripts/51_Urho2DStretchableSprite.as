// Urho2D stretchable sprite example.
// This sample demonstrates:
//     - Creating a 2D scene with both static and stretchable sprites
//     - Difference in scaling static and stretchable sprites
//     - Similarity in otherwise transforming static and stretchable sprites
//     - Displaying the scene using the Renderer subsystem
//     - Handling keyboard to transform nodes

#include "Scripts/Utilities/Sample.as"

Node@ refSpriteNode = null;
Node@ stretchSpriteNode = null;
int selectTransform = 0;

void Start()
{
    // Execute the common startup for samples
    SampleStart();

    // Create the scene content
    CreateScene();

    // Create the UI content
    CreateInstructions();

    // Setup the viewport for displaying the scene
    SetupViewport();

    // Set the mouse mode to use in the sample
    SampleInitMouseMode(MM_FREE);

    // Hook up to the frame update events
    SubscribeToEvents();
}

void CreateScene()
{
    scene_ = Scene();

    // Create the Octree component to the scene. This is required before adding any drawable components, or else nothing will
    // show up. The default octree volume will be from (-1000, -1000, -1000) to (1000, 1000, 1000) in world coordinates; it
    // is also legal to place objects outside the volume but their visibility can then not be checked in a hierarchically
    // optimizing manner
    scene_.CreateComponent("Octree");

    // Create a scene node for the camera, which we will move around
    // The camera will use default settings (1000 far clip distance, 45 degrees FOV, set aspect ratio automatically)
    cameraNode = scene_.CreateChild("Camera");
    // Set an initial position for the camera scene node above the plane
    cameraNode.position = Vector3(0.0f, 0.0f, -10.0f);

    Camera@ camera = cameraNode.CreateComponent("Camera");
    camera.orthographic = true;
    camera.orthoSize = graphics.height * PIXEL_SIZE;

    @refSpriteNode = scene_.CreateChild("regular sprite");
    @stretchSpriteNode = scene_.CreateChild("stretchable sprite");

    Sprite2D@ sprite = cache.GetResource("Sprite2D", "Urho2D/Stretchable.png");
    if (sprite !is null)
    {
        StaticSprite2D@ staticSprite = refSpriteNode.CreateComponent("StaticSprite2D");
        staticSprite.sprite = sprite;

        StretchableSprite2D@ stretchSprite = stretchSpriteNode.CreateComponent("StretchableSprite2D");
        stretchSprite.sprite = sprite;
        stretchSprite.border = IntRect(25, 25, 25, 25);

        refSpriteNode.Translate2D(Vector2(-2.0f, 0.0f));
        stretchSpriteNode.Translate2D(Vector2(2.0f, 0.0f));
    }
}

void CreateInstructions()
{
    // Construct new Text object, set string to display and font to use
    Text@ instructionText = ui.root.CreateChild("Text");
    instructionText.text = "Use WASD keys to transform, Tab key to cycle through\n"
                           "Scale, Rotate, and Translate transform modes. In Rotate\n"
                           "mode, combine A/D keys with Ctrl key to rotate about\n"
                           "the Z axis";
    instructionText.SetFont(cache.GetResource("Font", "Fonts/Anonymous Pro.ttf"), 12);

    // Position the text relative to the screen center
    instructionText.horizontalAlignment = HA_CENTER;
    instructionText.verticalAlignment = VA_CENTER;
    instructionText.SetPosition(0, ui.root.height / 4);
}

void SetupViewport()
{
    // Set up a viewport to the Renderer subsystem so that the 3D scene can be seen. We need to define the scene and the camera
    // at minimum. Additionally we could configure the viewport screen size and the rendering path (eg. forward / deferred) to
    // use, but now we just use full screen and default render path configured in the engine command line options
    Viewport@ viewport = Viewport(scene_, cameraNode.GetComponent("Camera"));
    renderer.viewports[0] = viewport;
}

void SubscribeToEvents()
{
    // Subscribe to Key Up event, to handle individual key presses
    SubscribeToEvent("KeyUp", "OnKeyUp");

    // Subscribe HandleUpdate() function for processing update events
    SubscribeToEvent("Update", "HandleUpdate");

    // Unsubscribe the SceneUpdate event from base class to prevent camera pitch and yaw in 2D sample
    UnsubscribeFromEvent("SceneUpdate");
}

void HandleUpdate(StringHash eventType, VariantMap& eventData)
{
    // Take the frame time step, which is stored as a float
    float timeStep = eventData["TimeStep"].GetFloat();

    switch (selectTransform)
    {
    case 0:
        ScaleSprites(timeStep);
        break;
    case 1:
        RotateSprites(timeStep);
        break;
    case 2:
        TranslateSprites(timeStep);
        break;
    default:
        log.Error("Bad transform selection: " + selectTransform);
    }
}

void OnKeyUp(StringHash eventType, VariantMap& eventData)
{
    int key = eventData["Key"].GetInt();

    if(key == KEY_TAB)
    {
        ++selectTransform;
        selectTransform %= 3;
    }
    else if(key == KEY_ESCAPE)
        engine.Exit();
}

void TranslateSprites(float timeStep)
{
    const float speed = 1.0f;
    const bool left = input.keyDown[KEY_A],
               right = input.keyDown[KEY_D],
               up = input.keyDown[KEY_W],
               down = input.keyDown[KEY_S];

    if (left || right || up || down)
    {
        const float quantum = timeStep * speed;
        const Vector2 translate = Vector2(
            (left ? -quantum : 0.0f) + (right ? quantum : 0.0f),
            (down ? -quantum : 0.0f) + (up ? quantum : 0.0f));

        refSpriteNode.Translate2D(translate);
        stretchSpriteNode.Translate2D(translate);
    }
}

void RotateSprites(float timeStep)
{
    const float speed = 45.0f;

    const bool left = input.keyDown[KEY_A],
               right = input.keyDown[KEY_D],
               up = input.keyDown[KEY_W],
               down = input.keyDown[KEY_S],
               ctrl = input.keyDown[KEY_CTRL];

    if (left || right || up || down)
    {
        const float quantum = timeStep * speed;

        const float xrot = (up ? -quantum : 0.0f) + (down ? quantum: 0.0f);
        const float rot2 = (left ? -quantum: 0.0f) + (right ? quantum : 0.0f);
        const Quaternion totalRot = Quaternion(xrot,
                                               ctrl ? 0.0f : rot2,
                                               ctrl ? rot2 : 0.0f);

        refSpriteNode.Rotate(totalRot);
        stretchSpriteNode.Rotate(totalRot);
    }
}

void ScaleSprites(float timeStep)
{
    const float speed = 0.5f;

    const bool left = input.keyDown[KEY_A],
               right = input.keyDown[KEY_D],
               up = input.keyDown[KEY_W],
               down = input.keyDown[KEY_S];
    if (left || right || up || down)
    {
        const float quantum = timeStep * speed;
        const Vector2 scale = Vector2(
            1.0f + (right ? quantum : left ? -quantum : 0.0f),
            1.0f + (up ? quantum : down ? -quantum : 0.0f));

        refSpriteNode.Scale2D(scale);
        stretchSpriteNode.Scale2D(scale);
    }
}

// Create XML patch instructions for screen joystick layout specific to this sample app
String patchInstructions =
        "<patch>"
        "    <remove sel=\"/element/element[./attribute[@name='Name' and @value='Button0']]/attribute[@name='Is Visible']\" />"
        "    <replace sel=\"/element/element[./attribute[@name='Name' and @value='Button0']]/element[./attribute[@name='Name' and @value='Label']]/attribute[@name='Text']/@value\">TAB</replace>"
        "    <add sel=\"/element/element[./attribute[@name='Name' and @value='Button0']]\">"
        "        <element type=\"Text\">"
        "            <attribute name=\"Name\" value=\"KeyBinding\" />"
        "            <attribute name=\"Text\" value=\"TAB\" />"
        "        </element>"
        "    </add>"
        "    <remove sel=\"/element/element[./attribute[@name='Name' and @value='Button1']]/attribute[@name='Is Visible']\" />"
        "    <replace sel=\"/element/element[./attribute[@name='Name' and @value='Button1']]/element[./attribute[@name='Name' and @value='Label']]/attribute[@name='Text']/@value\">CTRL</replace>"
        "    <add sel=\"/element/element[./attribute[@name='Name' and @value='Button1']]\">"
        "        <element type=\"Text\">"
        "            <attribute name=\"Name\" value=\"KeyBinding\" />"
        "            <attribute name=\"Text\" value=\"LCTRL\" />"
        "        </element>"
        "    </add>"
        "</patch>";
