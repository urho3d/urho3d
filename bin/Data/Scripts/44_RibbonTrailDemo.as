// Ribbon trail demo.
// This sample demonstrates how to use both trail types of RibbonTrail component.

#include "Scripts/Utilities/Sample.as"

Node@ boxNode1;
Node@ boxNode2;
RibbonTrail@ swordTrail;
AnimationController@ ninjaAnimCtrl;
float timeStepSum = 0.0f;
float swordTrailStartTime = 0.2f;
float swordTrailEndTime = 0.46f;

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
    SampleInitMouseMode(MM_RELATIVE);

    // Hook up to the frame update events
    SubscribeToEvents();
}

void CreateScene()
{
    scene_ = Scene();

    // Create octree, use default volume (-1000, -1000, -1000) to (1000, 1000, 1000)
    scene_.CreateComponent("Octree");

    // Create scene node & StaticModel component for showing a static plane
    Node@ planeNode = scene_.CreateChild("Plane");
    planeNode.scale = Vector3(100.0f, 1.0f, 100.0f);
    StaticModel@ planeObject = planeNode.CreateComponent("StaticModel");
    planeObject.model = cache.GetResource("Model", "Models/Plane.mdl");
    planeObject.material = cache.GetResource("Material", "Materials/StoneTiled.xml");

    // Create a directional light to the world.
    Node@ lightNode = scene_.CreateChild("DirectionalLight");
    lightNode.direction = Vector3(0.6f, -1.0f, 0.8f); // The direction vector does not need to be normalized
    Light@ light = lightNode.CreateComponent("Light");
    light.lightType = LIGHT_DIRECTIONAL;
    light.castShadows = true;
    light.shadowBias = BiasParameters(0.00005f, 0.5f);
    // Set cascade splits at 10, 50 and 200 world units, fade shadows out at 80% of maximum shadow distance
    light.shadowCascade = CascadeParameters(10.0f, 50.0f, 200.0f, 0.0f, 0.8f);
    
    // Create first box for face camera trail demo with 1 column.
    boxNode1 = scene_.CreateChild("Box1");
    StaticModel@ box1 = boxNode1.CreateComponent("StaticModel");
    box1.model = cache.GetResource("Model", "Models/Box.mdl");
    box1.castShadows = true;
    RibbonTrail@ boxTrail1 = boxNode1.CreateComponent("RibbonTrail");
    boxTrail1.material = cache.GetResource("Material", "Materials/RibbonTrail.xml");
    boxTrail1.startColor = Color(1.0f, 0.5f, 0.0f, 1.0f);
    boxTrail1.endColor = Color(1.0f, 1.0f, 0.0f, 0.0f);
    boxTrail1.width = 0.5f;
    boxTrail1.updateInvisible = true;
    
    // Create second box for face camera trail demo with 4 column.
    // This will produce less distortion than first trail.
    boxNode2 = scene_.CreateChild("Box2");
    StaticModel@ box2 = boxNode2.CreateComponent("StaticModel");
    box2.model = cache.GetResource("Model", "Models/Box.mdl");
    box2.castShadows = true;
    RibbonTrail@ boxTrail2 = boxNode2.CreateComponent("RibbonTrail");
    boxTrail2.material = cache.GetResource("Material", "Materials/RibbonTrail.xml");
    boxTrail2.startColor = Color(1.0f, 0.5f, 0.0f, 1.0f);
    boxTrail2.endColor = Color(1.0f, 1.0f, 0.0f, 0.0f);
    boxTrail2.width = 0.5f;
    boxTrail2.tailColumn = 4;
    boxTrail2.updateInvisible = true;
    
    // Load ninja animated model for bone trail demo.
    Node@ ninjaNode = scene_.CreateChild("Ninja");
    ninjaNode.position = Vector3(5.0f, 0.0f, 0.0f);
    ninjaNode.rotation = Quaternion(0.0f, 180.0f, 0.0f);
    AnimatedModel@ ninja = ninjaNode.CreateComponent("AnimatedModel");
    ninja.model = cache.GetResource("Model", "Models/NinjaSnowWar/Ninja.mdl");
    ninja.material = cache.GetResource("Material", "Materials/NinjaSnowWar/Ninja.xml");
    ninja.castShadows = true;

    // Create animation controller and play attack animation.
    ninjaAnimCtrl = ninjaNode.CreateComponent("AnimationController");
    ninjaAnimCtrl.PlayExclusive("Models/NinjaSnowWar/Ninja_Attack3.ani", 0, true, 0.0f);

    // Add ribbon trail to tip of sword.
    Node@ swordTip = ninjaNode.GetChild("Joint29", true);
    swordTrail = swordTip.CreateComponent("RibbonTrail");

    // Set sword trail type to bone and set other parameters.
    swordTrail.trailType = TT_BONE;
    swordTrail.material = cache.GetResource("Material", "Materials/SlashTrail.xml");
    swordTrail.lifetime = 0.22f;
    swordTrail.startColor = Color(1.0f, 1.0f, 1.0f, 0.75f);
    swordTrail.endColor = Color(0.2, 0.5f, 1.0f, 0.0f);
    swordTrail.tailColumn = 4;
    swordTrail.updateInvisible = true;
    
    // Add floating text for info.
    Node@ boxTextNode1 = scene_.CreateChild("BoxText1");
    boxTextNode1.position = Vector3(-1.0f, 2.0f, 0.0f);
    Text3D@ boxText1 = boxTextNode1.CreateComponent("Text3D");
    boxText1.text = "Face Camera Trail (4 Column)";
    boxText1.SetFont(cache.GetResource("Font", "Fonts/BlueHighway.sdf"), 24);

    Node@ boxTextNode2 = scene_.CreateChild("BoxText2");
    boxTextNode2.position = Vector3(-6.0f, 2.0f, 0.0f);
    Text3D@ boxText2 = boxTextNode2.CreateComponent("Text3D");
    boxText2.text = "Face Camera Trail (1 Column)";
    boxText2.SetFont(cache.GetResource("Font", "Fonts/BlueHighway.sdf"), 24);

    Node@ ninjaTextNode2 = scene_.CreateChild("NinjaText");
    ninjaTextNode2.position = Vector3(4.0f, 2.5f, 0.0f);
    Text3D@ ninjaText = ninjaTextNode2.CreateComponent("Text3D");
    ninjaText.text = "Bone Trail (4 Column)";
    ninjaText.SetFont(cache.GetResource("Font", "Fonts/BlueHighway.sdf"), 24);

    // Create the camera.
    cameraNode = scene_.CreateChild("Camera");
    cameraNode.CreateComponent("Camera");

    // Set an initial position for the camera scene node above the plane
    cameraNode.position = Vector3(0.0f, 2.0f, -14.0f);
}

void CreateInstructions()
{
    // Construct new Text object, set string to display and font to use
    Text@ instructionText = ui.root.CreateChild("Text");
    instructionText.text = "Use WASD keys and mouse to move";
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
        cameraNode.Translate(Vector3(0.0f, 0.0f, 1.0f) * MOVE_SPEED * timeStep);
    if (input.keyDown[KEY_S])
        cameraNode.Translate(Vector3(0.0f, 0.0f, -1.0f) * MOVE_SPEED * timeStep);
    if (input.keyDown[KEY_A])
        cameraNode.Translate(Vector3(-1.0f, 0.0f, 0.0f) * MOVE_SPEED * timeStep);
    if (input.keyDown[KEY_D])
        cameraNode.Translate(Vector3(1.0f, 0.0f, 0.0f) * MOVE_SPEED * timeStep);
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
    
    // Sum of timesteps.
    timeStepSum += timeStep;
    
    // Move first box with pattern.
    boxNode1.SetTransform(Vector3(-4.0 + 3.0 * Cos(100.0 * timeStepSum), 0.5, -2.0 * Cos(400.0 * timeStepSum)), Quaternion());
    
    // Move second box with pattern.
    boxNode2.SetTransform(Vector3(0.0 + 3.0 * Cos(100.0 * timeStepSum), 0.5, -2.0 * Cos(400.0 * timeStepSum)), Quaternion());
    
    // Get elapsed attack animation time.
    float swordAnimTime = ninjaAnimCtrl.GetAnimationState("Models/NinjaSnowWar/Ninja_Attack3.ani").time;

    // Stop emitting trail when sword is finished slashing.
    if (!swordTrail.emitting && swordAnimTime > swordTrailStartTime && swordAnimTime < swordTrailEndTime)
        swordTrail.emitting = true;
    else if (swordTrail.emitting && swordAnimTime >= swordTrailEndTime)
        swordTrail.emitting = false;
}

// Create XML patch instructions for screen joystick layout specific to this sample app
String patchInstructions = "";
