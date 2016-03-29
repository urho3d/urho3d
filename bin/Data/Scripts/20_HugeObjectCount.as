// Huge object count example.
// This sample demonstrates:
//     - Creating a scene with 250 x 250 simple objects
//     - Competing with http://yosoygames.com.ar/wp/2013/07/ogre-2-0-is-up-to-3x-faster/ :)
//     - Allowing examination of performance hotspots in the rendering code
//     - Optionally speeding up rendering by grouping objects with the StaticModelGroup component

#include "Scripts/Utilities/Sample.as"

Array<Node@> boxNodes;
bool animate = false;
bool useGroups = false;

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
    if (scene_ is null)
        scene_ = Scene();
    else
    {
        scene_.Clear();
        boxNodes.Clear();
    }

    // Create the Octree component to the scene so that drawable objects can be rendered. Use default volume
    // (-1000, -1000, -1000) to (1000, 1000, 1000)
    scene_.CreateComponent("Octree");

    // Create a Zone for ambient light & fog control
    Node@ zoneNode = scene_.CreateChild("Zone");
    Zone@ zone = zoneNode.CreateComponent("Zone");
    zone.boundingBox = BoundingBox(-1000.0f, 1000.0f);
    zone.fogColor = Color(0.2f, 0.2f, 0.2f);
    zone.fogStart = 200.0f;
    zone.fogEnd = 300.0f;

    // Create a directional light
    Node@ lightNode = scene_.CreateChild("DirectionalLight");
    lightNode.direction = Vector3(-0.6f, -1.0f, -0.8f); // The direction vector does not need to be normalized
    Light@ light = lightNode.CreateComponent("Light");
    light.lightType = LIGHT_DIRECTIONAL;

    if (!useGroups)
    {
        light.color = Color(0.7f, 0.35f, 0.0f);

        // Create individual box StaticModels in the scene
        for (int y = -125; y < 125; ++y)
        {
            for (int x = -125; x < 125; ++x)
            {
                Node@ boxNode = scene_.CreateChild("Box");
                boxNode.position = Vector3(x * 0.3f, 0.0f, y * 0.3f);
                boxNode.SetScale(0.25f);
                StaticModel@ boxObject = boxNode.CreateComponent("StaticModel");
                boxObject.model = cache.GetResource("Model", "Models/Box.mdl");
                boxNodes.Push(boxNode);
            }
        }
    }
    else
    {
        light.color = Color(0.6f, 0.6f, 0.6f);
        light.specularIntensity = 1.5f;

        // Create StaticModelGroups in the scene
        StaticModelGroup@ lastGroup;

        for (int y = -125; y < 125; ++y)
        {
            for (int x = -125; x < 125; ++x)
            {
                // Create new group if no group yet, or the group has already "enough" objects. The tradeoff is between culling
                // accuracy and the amount of CPU processing needed for all the objects. Note that the group's own transform
                // does not matter, and it does not render anything if instance nodes are not added to it
                if (lastGroup is null || lastGroup.numInstanceNodes >= 25 * 25)
                {
                    Node@ boxGroupNode = scene_.CreateChild("BoxGroup");
                    lastGroup = boxGroupNode.CreateComponent("StaticModelGroup");
                    lastGroup.model = cache.GetResource("Model", "Models/Box.mdl");
                }

                Node@ boxNode = scene_.CreateChild("Box");
                boxNode.position = Vector3(x * 0.3f, 0.0f, y * 0.3f);
                boxNode.SetScale(0.25f);
                boxNodes.Push(boxNode);
                lastGroup.AddInstanceNode(boxNode);
            }
        }
    }

    // Create the camera. Create it outside the scene so that we can clear the whole scene without affecting it
    if (cameraNode is null)
    {
        cameraNode = Node("Camera");
        cameraNode.position = Vector3(0.0f, 10.0f, -100.0f);
        Camera@ camera = cameraNode.CreateComponent("Camera");
        camera.farClip = 300.0f;
    }
}

void CreateInstructions()
{
    // Construct new Text object, set string to display and font to use
    Text@ instructionText = ui.root.CreateChild("Text");
    instructionText.text =
        "Use WASD keys and mouse to move\n"
        "Space to toggle animation\n"
        "G to toggle object group optimization";
    instructionText.SetFont(cache.GetResource("Font", "Fonts/Anonymous Pro.ttf"), 15);
    // The text has multiple rows. Center them in relation to each other
    instructionText.textAlignment = HA_CENTER;

    // Position the text relative to the screen center
    instructionText.horizontalAlignment = HA_CENTER;
    instructionText.verticalAlignment = VA_CENTER;
    instructionText.SetPosition(0, ui.root.height / 4);
}

void SetupViewport()
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
    if (input.keyDown['W'])
        cameraNode.Translate(Vector3(0.0f, 0.0f, 1.0f) * MOVE_SPEED * timeStep);
    if (input.keyDown['S'])
        cameraNode.Translate(Vector3(0.0f, 0.0f, -1.0f) * MOVE_SPEED * timeStep);
    if (input.keyDown['A'])
        cameraNode.Translate(Vector3(-1.0f, 0.0f, 0.0f) * MOVE_SPEED * timeStep);
    if (input.keyDown['D'])
        cameraNode.Translate(Vector3(1.0f, 0.0f, 0.0f) * MOVE_SPEED * timeStep);
}

void AnimateObjects(float timeStep)
{
    const float ROTATE_SPEED = 15.0f;
    // Rotate about the Z axis (roll)
    Quaternion rotateQuat(ROTATE_SPEED * timeStep, Vector3(0.0f, 0.0f, 1.0f));

    for (uint i = 0; i < boxNodes.length; ++i)
        boxNodes[i].Rotate(rotateQuat);
}

void HandleUpdate(StringHash eventType, VariantMap& eventData)
{
    // Take the frame time step, which is stored as a float
    float timeStep = eventData["TimeStep"].GetFloat();

    // Toggle animation with space
    if (input.keyPress[KEY_SPACE])
        animate = !animate;

    // Toggle grouped / ungrouped mode
    if (input.keyPress['G'])
    {
        useGroups = !useGroups;
        CreateScene();
    }

    // Move the camera, scale movement with time step
    MoveCamera(timeStep);

    // Animate scene if enabled
    if (animate)
        AnimateObjects(timeStep);
}

// Create XML patch instructions for screen joystick layout specific to this sample app
String patchInstructions =
        "<patch>" +
        "    <remove sel=\"/element/element[./attribute[@name='Name' and @value='Button0']]/attribute[@name='Is Visible']\" />" +
        "    <replace sel=\"/element/element[./attribute[@name='Name' and @value='Button0']]/element[./attribute[@name='Name' and @value='Label']]/attribute[@name='Text']/@value\">Group</replace>" +
        "    <add sel=\"/element/element[./attribute[@name='Name' and @value='Button0']]\">" +
        "        <element type=\"Text\">" +
        "            <attribute name=\"Name\" value=\"KeyBinding\" />" +
        "            <attribute name=\"Text\" value=\"G\" />" +
        "        </element>" +
        "    </add>" +
        "    <remove sel=\"/element/element[./attribute[@name='Name' and @value='Button1']]/attribute[@name='Is Visible']\" />" +
        "    <replace sel=\"/element/element[./attribute[@name='Name' and @value='Button1']]/element[./attribute[@name='Name' and @value='Label']]/attribute[@name='Text']/@value\">Animation</replace>" +
        "    <add sel=\"/element/element[./attribute[@name='Name' and @value='Button1']]\">" +
        "        <element type=\"Text\">" +
        "            <attribute name=\"Name\" value=\"KeyBinding\" />" +
        "            <attribute name=\"Text\" value=\"SPACE\" />" +
        "        </element>" +
        "    </add>" +
        "</patch>";
