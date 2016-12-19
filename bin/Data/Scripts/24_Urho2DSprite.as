// Urho2D sprite example.
// This sample demonstrates:
//     - Creating a 2D scene with sprite
//     - Displaying the scene using the Renderer subsystem
//     - Handling keyboard to move and zoom 2D camera

#include "Scripts/Utilities/Sample.as"

Array<Node@> spriteNodes;

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

    Sprite2D@ sprite = cache.GetResource("Sprite2D", "Urho2D/Aster.png");
    if (sprite is null)
        return;

    uint halfWidth = uint(graphics.width * PIXEL_SIZE * 0.5f);
    uint halfHeight = uint(graphics.height * PIXEL_SIZE * 0.5f);
    // Create more StaticModel objects to the scene, randomly positioned, rotated and scaled. For rotation, we construct a
    // quaternion from Euler angles where the Y angle (rotation about the Y axis) is randomized. The mushroom model contains
    // LOD levels, so the StaticModel component will automatically select the LOD level according to the view distance (you'll
    // see the model get simpler as it moves further away). Finally, rendering a large number of the same object with the
    // same material allows instancing to be used, if the GPU supports it. This reduces the amount of CPU work in rendering the
    // scene.
    const uint NUM_SPRITES = 200;
    for (uint i = 0; i < NUM_SPRITES; ++i)
    {
        Node@ spriteNode = scene_.CreateChild("StaticSprite2D");
        spriteNode.position = Vector3(Random(-halfWidth, halfWidth), Random(-halfHeight, halfHeight), 0.0f);

        StaticSprite2D@ staticSprite = spriteNode.CreateComponent("StaticSprite2D");
        // Set color
        staticSprite.color = Color(Random(1.0f), Random(1.0f), Random(1.0f), 1.0f);
        // Set blend mode
        staticSprite.blendMode = BLEND_ALPHA;
        // Set sprite
        staticSprite.sprite = sprite;

        spriteNode.vars["MoveSpeed"] = Vector3(Random(-2.0f, 2.0f), Random(-2.0f, 2.0f), 0.0f);
        spriteNode.vars["RotateSpeed"] = Random(-90.0f, 90.0f);

        spriteNodes.Push(spriteNode);
    }

    AnimationSet2D@ animationSet = cache.GetResource("AnimationSet2D", "Urho2D/GoldIcon.scml");
    if (animationSet is null)
        return;
    Node@ spriteNode = scene_.CreateChild("AnimatedSprite2D");
    spriteNode.position = Vector3(0.0f, 0.0f, -1.0f);

    AnimatedSprite2D@ animatedSprite = spriteNode.CreateComponent("AnimatedSprite2D");
    // Set animation
    animatedSprite.animationSet = animationSet;
    animatedSprite.animation = "idle";
}

void CreateInstructions()
{
    // Construct new Text object, set string to display and font to use
    Text@ instructionText = ui.root.CreateChild("Text");
    instructionText.text = "Use WASD keys and mouse to move, Use PageUp PageDown to zoom.";
    instructionText.SetFont(cache.GetResource("Font", "Fonts/Anonymous Pro.ttf"), 15);

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

void MoveCamera(float timeStep)
{
    // Do not move if the UI has a focused element (the console)
    if (ui.focusElement !is null)
        return;

    // Movement speed as world units per second
    const float MOVE_SPEED = 4.0f;

    // Read WASD keys and move the camera scene node to the corresponding direction if they are pressed
    if (input.keyDown[KEY_W])
        cameraNode.Translate(Vector3(0.0f, 1.0f, 0.0f) * MOVE_SPEED * timeStep);
    if (input.keyDown[KEY_S])
        cameraNode.Translate(Vector3(0.0f, -1.0f, 0.0f) * MOVE_SPEED * timeStep);
    if (input.keyDown[KEY_A])
        cameraNode.Translate(Vector3(-1.0f, 0.0f, 0.0f) * MOVE_SPEED * timeStep);
    if (input.keyDown[KEY_D])
        cameraNode.Translate(Vector3(1.0f, 0.0f, 0.0f) * MOVE_SPEED * timeStep);

    if (input.keyDown[KEY_PAGEUP])
    {
        Camera@ camera = cameraNode.GetComponent("Camera");
        camera.zoom = camera.zoom * 1.01f;
    }

    if (input.keyDown[KEY_PAGEDOWN])
    {
        Camera@ camera = cameraNode.GetComponent("Camera");
        camera.zoom = camera.zoom * 0.99f;
    }
}

void SubscribeToEvents()
{
    // Subscribe HandleUpdate() function for processing update events
    SubscribeToEvent("Update", "HandleUpdate");

    // Unsubscribe the SceneUpdate event from base class to prevent camera pitch and yaw in 2D sample
    UnsubscribeFromEvent("SceneUpdate");
}

void HandleUpdate(StringHash eventType, VariantMap& eventData)
{
    // Take the frame time step, which is stored as a float
    float timeStep = eventData["TimeStep"].GetFloat();

    // Move the camera, scale movement with time step
    MoveCamera(timeStep);

    float halfWidth = graphics.width * 0.5f * PIXEL_SIZE;
    float halfHeight = graphics.height * 0.5f * PIXEL_SIZE;

    // Go through all sprites
    for (uint i = 0; i < spriteNodes.length; ++i)
    {
        Node@ spriteNode = spriteNodes[i];

        Vector3 moveSpeed = spriteNode.vars["MoveSpeed"].GetVector3();
        Vector3 newPosition = spriteNode.position + moveSpeed * timeStep;

        if (newPosition.x < -halfWidth || newPosition.x > halfWidth)
        {
            newPosition.x = spriteNode.position.x;
            moveSpeed.x = -moveSpeed.x;
            spriteNode.vars["MoveSpeed"] = moveSpeed;
        }

        if (newPosition.y < -halfHeight || newPosition.y > halfHeight)
        {
            newPosition.y = spriteNode.position.y;
            moveSpeed.y = -moveSpeed.y;
            spriteNode.vars["MoveSpeed"] = moveSpeed;
        }

        spriteNode.position = newPosition;
        spriteNode.Roll(spriteNode.vars["RotateSpeed"].GetFloat() * timeStep);
    }
}

// Create XML patch instructions for screen joystick layout specific to this sample app
String patchInstructions =
        "<patch>" +
        "    <remove sel=\"/element/element[./attribute[@name='Name' and @value='Button0']]/attribute[@name='Is Visible']\" />" +
        "    <replace sel=\"/element/element[./attribute[@name='Name' and @value='Button0']]/element[./attribute[@name='Name' and @value='Label']]/attribute[@name='Text']/@value\">Zoom In</replace>" +
        "    <add sel=\"/element/element[./attribute[@name='Name' and @value='Button0']]\">" +
        "        <element type=\"Text\">" +
        "            <attribute name=\"Name\" value=\"KeyBinding\" />" +
        "            <attribute name=\"Text\" value=\"PAGEUP\" />" +
        "        </element>" +
        "    </add>" +
        "    <remove sel=\"/element/element[./attribute[@name='Name' and @value='Button1']]/attribute[@name='Is Visible']\" />" +
        "    <replace sel=\"/element/element[./attribute[@name='Name' and @value='Button1']]/element[./attribute[@name='Name' and @value='Label']]/attribute[@name='Text']/@value\">Zoom Out</replace>" +
        "    <add sel=\"/element/element[./attribute[@name='Name' and @value='Button1']]\">" +
        "        <element type=\"Text\">" +
        "            <attribute name=\"Name\" value=\"KeyBinding\" />" +
        "            <attribute name=\"Text\" value=\"PAGEDOWN\" />" +
        "        </element>" +
        "    </add>" +
        "</patch>";
