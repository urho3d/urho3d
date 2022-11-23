// Light animation example.
// This sample is base on StaticScene, and it demonstrates:
//     - Usage of attribute animation for light color & UI animation

#include "Scripts/Utilities/Sample.as"

void Start()
{
    // Execute the common startup for samples
    SampleStart();

    // Create the UI content
    CreateInstructions();

    // Create the scene content
    CreateScene();

    // Setup the viewport for displaying the scene
    SetupViewport();

    // Set the mouse mode to use in the sample
    SampleInitMouseMode(MM_RELATIVE);

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

    // Create a child scene node (at world origin) and a StaticModel component into it. Set the StaticModel to show a simple
    // plane mesh with a "stone" material. Note that naming the scene nodes is optional. Scale the scene node larger
    // (100 x 100 world units)
    Node@ planeNode = scene_.CreateChild("Plane");
    planeNode.scale = Vector3(100.0f, 1.0f, 100.0f);
    StaticModel@ planeObject = planeNode.CreateComponent("StaticModel");
    planeObject.model = cache.GetResource("Model", "Models/Plane.mdl");
    planeObject.material = cache.GetResource("Material", "Materials/StoneTiled.xml");

    // Create a point light to the world so that we can see something.
    Node@ lightNode = scene_.CreateChild("DirectionalLight");
    Light@ light = lightNode.CreateComponent("Light");
    light.lightType = LIGHT_POINT;
    light.range = 10.0f;

    // Create light color animation
    ValueAnimation@ colorAnimation = ValueAnimation();
    colorAnimation.SetKeyFrame(0.0f, Variant(Color::WHITE));
    colorAnimation.SetKeyFrame(1.0f, Variant(Color::RED));
    colorAnimation.SetKeyFrame(2.0f, Variant(Color::YELLOW));
    colorAnimation.SetKeyFrame(3.0f, Variant(Color::GREEN));
    colorAnimation.SetKeyFrame(4.0f, Variant(Color::WHITE));
    light.SetAttributeAnimation("Color", colorAnimation);

    // Create text animation
    ValueAnimation@ textAnimation = ValueAnimation();
    textAnimation.SetKeyFrame(0.0f, Variant("WHITE"));
    textAnimation.SetKeyFrame(1.0f, Variant("RED"));
    textAnimation.SetKeyFrame(2.0f, Variant("YELLOW"));
    textAnimation.SetKeyFrame(3.0f, Variant("GREEN"));
    textAnimation.SetKeyFrame(4.0f, Variant("WHITE"));
    ui.root.GetChild("animatingText").SetAttributeAnimation("Text", textAnimation);
    
    // Create UI element animation
    // (note: a spritesheet and "Image Rect" attribute should be used in real use cases for better performance)
    ValueAnimation@ spriteAnimation = ValueAnimation();
    spriteAnimation.SetKeyFrame(0.0f, Variant(ResourceRef("Texture2D", "Urho2D/GoldIcon/1.png")));
    spriteAnimation.SetKeyFrame(0.1f, Variant(ResourceRef("Texture2D", "Urho2D/GoldIcon/2.png")));
    spriteAnimation.SetKeyFrame(0.2f, Variant(ResourceRef("Texture2D", "Urho2D/GoldIcon/3.png")));
    spriteAnimation.SetKeyFrame(0.3f, Variant(ResourceRef("Texture2D", "Urho2D/GoldIcon/4.png")));
    spriteAnimation.SetKeyFrame(0.4f, Variant(ResourceRef("Texture2D", "Urho2D/GoldIcon/5.png")));
    spriteAnimation.SetKeyFrame(0.5f, Variant(ResourceRef("Texture2D", "Urho2D/GoldIcon/1.png")));
    ui.root.GetChild("animatingSprite").SetAttributeAnimation("Texture", spriteAnimation);

    // Create light position animation
    ValueAnimation@ positionAnimation = ValueAnimation();
    // Use spline interpolation method
    positionAnimation.interpolationMethod = IM_SPLINE;
    // Set spline tension
    positionAnimation.splineTension = 0.7f;
    positionAnimation.SetKeyFrame(0.0f, Variant(Vector3(-30.0f, 5.0f, -30.0f)));
    positionAnimation.SetKeyFrame(1.0f, Variant(Vector3( 30.0f, 5.0f, -30.0f)));
    positionAnimation.SetKeyFrame(2.0f, Variant(Vector3( 30.0f, 5.0f,  30.0f)));
    positionAnimation.SetKeyFrame(3.0f, Variant(Vector3(-30.0f, 5.0f,  30.0f)));
    positionAnimation.SetKeyFrame(4.0f, Variant(Vector3(-30.0f, 5.0f, -30.0f)));
    lightNode.SetAttributeAnimation("Position", positionAnimation);

    // Create more StaticModel objects to the scene, randomly positioned, rotated and scaled. For rotation, we construct a
    // quaternion from Euler angles where the Y angle (rotation about the Y axis) is randomized. The mushroom model contains
    // LOD levels, so the StaticModel component will automatically select the LOD level according to the view distance (you'll
    // see the model get simpler as it moves further away). Finally, rendering a large number of the same object with the
    // same material allows instancing to be used, if the GPU supports it. This reduces the amount of CPU work in rendering the
    // scene.
    const uint NUM_OBJECTS = 200;
    for (uint i = 0; i < NUM_OBJECTS; ++i)
    {
        Node@ mushroomNode = scene_.CreateChild("Mushroom");
        mushroomNode.position = Vector3(Random(90.0f) - 45.0f, 0.0f, Random(90.0f) - 45.0f);
        mushroomNode.rotation = Quaternion(0.0f, Random(360.0f), 0.0f);
        mushroomNode.SetScale(0.5f + Random(2.0f));
        StaticModel@ mushroomObject = mushroomNode.CreateComponent("StaticModel");
        mushroomObject.model = cache.GetResource("Model", "Models/Mushroom.mdl");
        mushroomObject.material = cache.GetResource("Material", "Materials/Mushroom.xml");
    }

    // Create a scene node for the camera, which we will move around
    // The camera will use default settings (1000 far clip distance, 45 degrees FOV, set aspect ratio automatically)
    cameraNode = scene_.CreateChild("Camera");
    cameraNode.CreateComponent("Camera");

    // Set an initial position for the camera scene node above the plane
    cameraNode.position = Vector3(0.0f, 5.0f, 0.0f);
}

void CreateInstructions()
{
    // Construct new Text object, set string to display and font to use
    Text@ instructionText = ui.root.CreateChild("Text");
    instructionText.text = "Use WASD keys and mouse to move";
    Font@ font = cache.GetResource("Font", "Fonts/Anonymous Pro.ttf");
    instructionText.SetFont(font, 15);

    // Position the text relative to the screen center
    instructionText.horizontalAlignment = HA_CENTER;
    instructionText.verticalAlignment = VA_CENTER;
    instructionText.SetPosition(0, ui.root.height / 4);

    // Animating text
    Text@ text = ui.root.CreateChild("Text", "animatingText");
    text.SetFont(font, 15);
    text.horizontalAlignment = HA_CENTER;
    text.verticalAlignment = VA_CENTER;
    text.SetPosition(0, ui.root.height / 4 + 20);

    // Animating sprite in the top left corner
    Sprite@ sprite = ui.root.CreateChild("Sprite", "animatingSprite");
    sprite.SetPosition(8, 8);
    sprite.SetSize(64, 64);
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
    const float MOVE_SPEED = 20.0f;
    // Mouse sensitivity as degrees per pixel
    const float MOUSE_SENSITIVITY = 0.1f;

    // Use this frame's mouse motion to adjust camera node yaw and pitch. Clamp the pitch between -90 and 90 degrees
    IntVector2 mouseMove = input.mouseMove;
    yaw += MOUSE_SENSITIVITY * mouseMove.x;
    pitch += MOUSE_SENSITIVITY * mouseMove.y;
    pitch = Clamp(pitch, -90.0f, 90.0f);

    // Construct new orientation for the camera scene node from yaw and pitch. Roll is fixed to zero
    cameraNode.rotation = Quaternion(pitch, yaw, 0.0f);

    // Read WASD keys and move the camera scene node to the corresponding direction if they are pressed
    // Use the Translate() function (default local space) to move relative to the node's orientation.
    if (input.keyDown[KEY_W])
        cameraNode.Translate(Vector3::FORWARD * MOVE_SPEED * timeStep);
    if (input.keyDown[KEY_S])
        cameraNode.Translate(Vector3::BACK * MOVE_SPEED * timeStep);
    if (input.keyDown[KEY_A])
        cameraNode.Translate(Vector3::LEFT * MOVE_SPEED * timeStep);
    if (input.keyDown[KEY_D])
        cameraNode.Translate(Vector3::RIGHT * MOVE_SPEED * timeStep);
}

void SubscribeToEvents()
{
    // Subscribe HandleUpdate() function for processing update events
    SubscribeToEvent("Update", "HandleUpdate");
}

void HandleUpdate(StringHash eventType, VariantMap& eventData)
{
    // Take the frame time step, which is stored as a float
    float timeStep = eventData["TimeStep"].GetFloat();

    // Move the camera, scale movement with time step
    MoveCamera(timeStep);
}

// Create XML patch instructions for screen joystick layout specific to this sample app
String patchInstructions = "";
