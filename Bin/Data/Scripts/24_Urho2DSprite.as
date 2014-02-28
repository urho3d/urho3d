// Urho2D spriteexample.
// This sample demonstrates:
//     - Creating a 2D scene with static sprite
//     - Displaying the scene using the Renderer subsystem
//     - Handling keyboard to move and zoom camera

#include "Scripts/Utilities/Sample.as"

Scene@ scene_;
Node@ cameraNode;
Array<Node@> spriteNodes;

const uint NUM_SPRITES = 200;
const ShortStringHash VAR_MOVESPEED("MoveSpeed");
const ShortStringHash VAR_ROTATESPEED("RotateSpeed");

void Start()
{
    // Execute the common startup for samples
    SampleStart();

    // Create the scene content
    CreateScene();

    // Create the UI content
    CreateInstructions();

    // Setup the viewports for displaying the scene and rendering the water reflection
    SetupViewports();

    // Hook up to the frame update and render post-update events
    SubscribeToEvents();
}

void CreateScene()
{
    scene_ = Scene();

    // Create octree, use default volume (-1000, -1000, -1000) to (1000, 1000, 1000)
    scene_.CreateComponent("Octree");

    // Create a scene node for the camera, which we will move around
    // The camera will use default settings (1000 far clip distance, 45 degrees FOV, set aspect ratio automatically)
    cameraNode = scene_.CreateChild("Camera");
    // Set an initial position for the camera scene node above the plane
    cameraNode.position = Vector3(0.0, 0.0, -10.0);
    
    Camera@ camera = cameraNode.CreateComponent("Camera");
    camera.orthographic = true;

    float width = float(graphics.width);
    float height = float(graphics.height);
    camera.SetOrthoSize(Vector2(width, height));

    Sprite2D@ sprite = cache.GetResource("Sprite2D", "Textures/Aster.png");
    if (sprite is null)
        return;

    float halfWidth = width * 0.5;
    float halfHeight = height * 0.5;

    for ( uint i = 0; i < NUM_SPRITES; ++i )
    {
        Node@ spriteNode = scene_.CreateChild("Urho2DSprite");
        spriteNode.position = Vector3(Random(-halfWidth, halfWidth), Random(-halfHeight, halfHeight), 0.0);
        spriteNode.SetScale(0.2 + Random(0.2));

        StaticSprite2D@ staticSprite = spriteNode.CreateComponent("StaticSprite2D");
        staticSprite.color = Color(Random(1.0), Random(1.0), Random(1.0), 1.0);
        staticSprite.blendMode = BLEND_ALPHA;
        staticSprite.sprite = sprite;

        spriteNode.vars[VAR_MOVESPEED] = Vector3(Random(-200.0, 200.0), Random(-200, 200.0), 0.0);
        spriteNode.vars[VAR_ROTATESPEED] = Random(-90.0, 90.0);
        spriteNodes.Push(spriteNode);
    }
}

void CreateInstructions()
{
    // Construct new Text object, set string to display and font to use
    Text@ instructionText = ui.root.CreateChild("Text");
    instructionText.text = "Use WASD keys and mouse to move, Use PageUp PageDown to zoom";
    instructionText.SetFont(cache.GetResource("Font", "Fonts/Anonymous Pro.ttf"), 15);
    instructionText.textAlignment = HA_CENTER;

    // Position the text relative to the screen center
    instructionText.horizontalAlignment = HA_CENTER;
    instructionText.verticalAlignment = VA_CENTER;
    instructionText.SetPosition(0, ui.root.height / 4);
}

void SetupViewports()
{
    // Set up a viewport to the Renderer subsystem so that the 3D scene can be seen
    Viewport@ viewport = Viewport(scene_, cameraNode.GetComponent("Camera"));
    renderer.viewports[0] = viewport;
}

void SubscribeToEvents()
{
    // Subscribe HandleUpdate() function for processing update events
    SubscribeToEvent("Update", "HandleUpdate");
}

void MoveCamera(float timeStep)
{
    // Do not move if the UI has a focused element (the console)
    if (ui.focusElement !is null)
        return;

    // Movement speed as world units per second
    const float MOVE_SPEED = 400.0;

    // Read WASD keys and move the camera scene node to the corresponding direction if they are pressed
    if (input.keyDown['W'])
        cameraNode.TranslateRelative(Vector3(0.0, 1.0, 0.0) * MOVE_SPEED * timeStep);
    if (input.keyDown['S'])
        cameraNode.TranslateRelative(Vector3(0.0, -1.0, 0.0) * MOVE_SPEED * timeStep);
    if (input.keyDown['A'])
        cameraNode.TranslateRelative(Vector3(-1.0, 0.0, 0.0) * MOVE_SPEED * timeStep);
    if (input.keyDown['D'])
        cameraNode.TranslateRelative(Vector3(1.0, 0.0, 0.0) * MOVE_SPEED * timeStep);

    if (input.keyDown[KEY_PAGEUP])
    {
        Camera@ camera = cameraNode.GetComponent("Camera");
        camera.zoom = camera.zoom * 1.01;
    }

    if (input.keyDown[KEY_PAGEDOWN])
    {
        Camera@ camera = cameraNode.GetComponent("Camera");
        camera.zoom = camera.zoom * 0.99;
    }
}

void HandleUpdate(StringHash eventType, VariantMap& eventData)
{
    // Take the frame time step, which is stored as a float
    float timeStep = eventData["TimeStep"].GetFloat();

    // Move the camera, scale movement with time step
    MoveCamera(timeStep);
}
