/// A 3D UI demonstration based on the HelloGUI sample. Renders UI alternatively
/// either to a 3D scene object using UIComponent, or directly to the backbuffer.

#include "Scripts/Utilities/Sample.as"

Window@ window;
IntVector2 dragBeginPosition = IntVector2::ZERO;
UIElement@ textureRoot;
WeakHandle current;
bool renderOnCube = false;
bool drawDebug_ = false;
bool animateCube = true;

void Start()
{
    // Execute the common startup for samples
    SampleStart();

    // Enable OS cursor
    input.mouseVisible = true;

    // Load XML file containing default UI style sheet
    XMLFile@ style = cache.GetResource("XMLFile", "UI/DefaultStyle.xml");

    // Set the loaded style as default style
    ui.root.defaultStyle = style;

    // Initialize Scene
    InitScene();

    // Initialize Window
    InitWindow();

    // Create and add some controls to the Window
    InitControls();

    // Create a draggable Fish
    CreateDraggableFish();

    // Create 3D UI rendered on a cube.
    Init3DUI();

    // Set the mouse mode to use in the sample
    SampleInitMouseMode(MM_FREE);
}

void InitControls()
{
    // Create a CheckBox
    CheckBox@ checkBox = CheckBox();
    checkBox.name = "CheckBox";

    // Create a Button
    Button@ button = Button();
    button.name = "Button";
    button.minHeight = 24;

    // Create a LineEdit
    LineEdit@ lineEdit = LineEdit();
    lineEdit.name = "LineEdit";
    lineEdit.minHeight = 24;

    // Add controls to Window
    window.AddChild(checkBox);
    window.AddChild(button);
    window.AddChild(lineEdit);

    // Apply previously set default style
    checkBox.SetStyleAuto();
    button.SetStyleAuto();
    lineEdit.SetStyleAuto();
    
    Text@ instructions = Text();
    instructions.SetStyleAuto();
    instructions.text = "[TAB]   - toggle between rendering on screen or cube.\n"
                        "[Space] - toggle cube rotation.";
    ui.root.AddChild(instructions);
}

void InitScene()
{
    scene_ = Scene();

    scene_.CreateComponent("Octree");
    Zone@ zone = scene_.CreateComponent("Zone");
    zone.boundingBox = BoundingBox(-1000.0f, 1000.0f);
    zone.fogColor = GRAY;
    zone.fogStart = 100.0f;
    zone.fogEnd = 300.0f;

    // Create a child scene node (at world origin) and a StaticModel component into it.
    Node@ boxNode = scene_.CreateChild("Box");
    boxNode.scale = Vector3(5.0f, 5.0f, 5.0f);
    boxNode.rotation = Quaternion(90, Vector3::LEFT);

    // Create a box model and hide it initially.
    StaticModel@ boxModel = boxNode.CreateComponent("StaticModel");
    boxModel.model = cache.GetResource("Model", "Models/Box.mdl");
    boxNode.enabled = false;

    // Create a camera.
    cameraNode = scene_.CreateChild("Camera");
    cameraNode.CreateComponent("Camera");

    // Set an initial position for the camera scene node.
    cameraNode.position = Vector3(0.0f, 0.0f, -10.0f);

    // Set up a viewport so 3D scene can be visible.
    Viewport@ viewport = Viewport(scene_, cameraNode.GetComponent("Camera"));
    renderer.viewports[0] = viewport;

    // Subscribe to update event and animate cube and handle input.
    SubscribeToEvent("Update", "HandleUpdate");
}

void InitWindow()
{
    // Create the Window and add it to the UI's root node
    window = Window();
    ui.root.AddChild(window);

    // Set Window size and layout settings
    window.minWidth = 384;
    window.SetLayout(LM_VERTICAL, 6, IntRect(6, 6, 6, 6));
    window.SetAlignment(HA_CENTER, VA_CENTER);
    window.name = "Window";

    // Create Window 'titlebar' container
    UIElement@ titleBar = UIElement();
    titleBar.SetMinSize(0, 24);
    titleBar.verticalAlignment = VA_TOP;
    titleBar.layoutMode = LM_HORIZONTAL;

    // Create the Window title Text
    Text@ windowTitle = Text();
    windowTitle.name = "WindowTitle";
    windowTitle.text = "Hello GUI!";

    // Create the Window's close button
    Button@ buttonClose = Button();
    buttonClose.name = "CloseButton";

    // Add the controls to the title bar
    titleBar.AddChild(windowTitle);
    titleBar.AddChild(buttonClose);

    // Add the title bar to the Window
    window.AddChild(titleBar);

    // Create a list.
    ListView@ list = window.CreateChild("ListView");
    list.selectOnClickEnd = true;
    list.highlightMode = HM_ALWAYS;
    list.minHeight = 200;

    for (int i = 0; i < 32; i++)
    {
        Text@ text = Text();
        text.SetStyleAuto();
        text.text = "List item " + i;
        text.name = "Item " + i;
        list.AddItem(text);
    }

    // Apply styles
    window.SetStyleAuto();
    list.SetStyleAuto();
    windowTitle.SetStyleAuto();
    buttonClose.style = "CloseButton";

    // Subscribe to buttonClose release (following a 'press') events
    SubscribeToEvent(buttonClose, "Released", "HandleClosePressed");

    // Subscribe also to all UI mouse clicks just to see where we have clicked
    SubscribeToEvent("UIMouseClick", "HandleControlClicked");
}

void CreateDraggableFish()
{
    // Create a draggable Fish button
    Button@ draggableFish = ui.root.CreateChild("Button", "Fish");
    draggableFish.texture = cache.GetResource("Texture2D", "Textures/UrhoDecal.dds"); // Set texture
    draggableFish.blendMode = BLEND_ADD;
    draggableFish.SetSize(128, 128);
    draggableFish.SetPosition((graphics.width - draggableFish.width) / 2, 200);

    // Add a tooltip to Fish button
    ToolTip@ toolTip = draggableFish.CreateChild("ToolTip");
    toolTip.position = IntVector2(draggableFish.width + 5, draggableFish.width/2); // slightly offset from fish
    BorderImage@ textHolder = toolTip.CreateChild("BorderImage");
    textHolder.SetStyle("ToolTipBorderImage");
    Text@ toolTipText = textHolder.CreateChild("Text");
    toolTipText.SetStyle("ToolTipText");
    toolTipText.text = "Please drag me!";

    // Subscribe draggableFish to Drag Events (in order to make it draggable)
    // See "Event list" in documentation's Main Page for reference on available Events and their eventData
    SubscribeToEvent(draggableFish, "DragBegin", "HandleDragBegin");
    SubscribeToEvent(draggableFish, "DragMove", "HandleDragMove");
    SubscribeToEvent(draggableFish, "DragEnd", "HandleDragEnd");
}

void HandleDragBegin(StringHash eventType, VariantMap& eventData)
{
    // Get UIElement relative position where input (touch or click) occurred (top-left = IntVector2(0,0))
    dragBeginPosition = IntVector2(eventData["ElementX"].GetInt(), eventData["ElementY"].GetInt());
}

void HandleDragMove(StringHash eventType, VariantMap& eventData)
{
    IntVector2 dragCurrentPosition = IntVector2(eventData["X"].GetInt(), eventData["Y"].GetInt());
    // Get the element (fish) that is being dragged. GetPtr() returns a RefCounted handle which can be cast implicitly
    UIElement@ draggedElement = eventData["Element"].GetPtr();
    draggedElement.position = dragCurrentPosition - dragBeginPosition;
}

void HandleDragEnd(StringHash eventType, VariantMap& eventData) // For reference (not used here)
{
}

void HandleClosePressed(StringHash eventType, VariantMap& eventData)
{
    engine.Exit();
}

void HandleControlClicked(StringHash eventType, VariantMap& eventData)
{
    // Get the Text control acting as the Window's title
    Text@ windowTitle = window.GetChild("WindowTitle", true);

    // Get control that was clicked
    UIElement@ clicked = eventData["Element"].GetPtr();

    String name = "...?";
    if (clicked !is null)
    {
        // Get the name of the control that was clicked
        name = clicked.name;
    }

    // Update the Window's title text
    windowTitle.text = "Hello " + name + "!";
}

void Init3DUI()
{
    // Node that will get UI rendered on it.
    Node@ boxNode = scene_.GetChild("Box");
    // Create a component that sets up UI rendering. It sets material to StaticModel of the node.
    UIComponent@ component = boxNode.CreateComponent("UIComponent");
    // Optionally modify material. Technique is changed so object is visible without any lights.
    component.material.SetTechnique(0, cache.GetResource("Technique", "Techniques/DiffUnlit.xml"));
    // Save root element of texture UI for later use.
    textureRoot = component.root;
    // Set size of root element. This is size of texture as well.
    textureRoot.SetSize(512, 512);
}

void HandleUpdate(StringHash eventType, VariantMap& eventData)
{
    float timeStep = eventData["TimeStep"].GetFloat();
    Node@ node = scene_.GetChild("Box");

    if (current.Get() !is null && drawDebug_)
        ui.DebugDraw(cast<UIElement>(current.Get()));

    if (input.mouseButtonPress[MOUSEB_LEFT])
        current = ui.GetElementAt(input.mousePosition);

    if (input.keyPress[KEY_TAB])
    {
        renderOnCube = !renderOnCube;
        // Toggle between rendering on screen or to texture.
        if (renderOnCube)
        {
            node.enabled = true;
            textureRoot.AddChild(window);
        }
        else
        {
            node.enabled = false;
            ui.root.AddChild(window);
        }
    }

    if (input.keyPress[KEY_SPACE])
        animateCube = !animateCube;

    if (input.keyPress[KEY_F2])
        drawDebug_ = !drawDebug_;

    if (animateCube)
    {
        node.Yaw(6.0f * timeStep * 1.5f);
        node.Roll(-6.0f * timeStep * 1.5f);
        node.Pitch(-6.0f * timeStep * 1.5f);
    }
}

// Create XML patch instructions for screen joystick layout specific to this sample app
String patchInstructions =
        "<patch>" +
        "    <add sel=\"/element/element[./attribute[@name='Name' and @value='Hat0']]\">" +
        "        <attribute name=\"Is Visible\" value=\"false\" />" +
        "    </add>" +
        "</patch>";
