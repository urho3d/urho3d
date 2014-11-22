// Urho3D UI Drag Example:
// This sample demonstrates:
//     - Creating GUI elements from AngelScript
//     - Loading GUI Style from xml
//     - Subscribing to GUI drag events and handling them.

#include "Scripts/Utilities/Sample.as"
StringHash VAR_BUTTONS("BUTTONS");
StringHash VAR_START("START");
StringHash VAR_DELTA("DELTA");

void Start()
{
    // Execute base class startup
    SampleStart();

    // Set mouse visible
    String platform = GetPlatform();
    if (platform != "Android" and platform != "iOS")
        input.mouseVisible = true;
    
    // Create the UI content
    CreateGUI();
    CreateInstructions();

    // Hook up to the frame update events
    SubscribeToEvents();
}

void CreateGUI()
{
    UIElement@ root = ui.root;
    // Load the style sheet from xml
    root.defaultStyle = cache.GetResource("XMLFile", "UI/DefaultStyle.xml");

    for (int i=0; i < 10; i++)
    {
        Button@ b = Button();
        root.AddChild(b);
        // Reference a style from the style sheet loaded earlier:
        b.style = "Button";
        b.size = IntVector2(300, 100);
        b.position = IntVector2(50*i, 50*i);

        SubscribeToEvent(b, "DragMove", "HandleDragMove");
        SubscribeToEvent(b, "DragBegin", "HandleDragBegin");
        SubscribeToEvent(b, "DragCancel", "HandleDragCancel");

        {
            Text@ t = Text();
            b.AddChild(t);
            t.style = "Text";
            t.horizontalAlignment = HA_CENTER;
            t.verticalAlignment = VA_CENTER;
            t.name = "Text";
        }

        {
            Text@ t = Text();
            b.AddChild(t);
            t.style = "Text";
            t.name = "Event Touch";
            t.horizontalAlignment = HA_CENTER;
            t.verticalAlignment = VA_BOTTOM;
        }

        {
            Text@ t = Text();
            b.AddChild(t);
            t.style ="Text";
            t.name = "Num Touch";
            t.horizontalAlignment = HA_CENTER;
            t.verticalAlignment = VA_TOP;
        }
    }

    for (int i = 0; i < 10; i++)
    {
        Text@ t = Text();
        root.AddChild(t);
        t.style = "Text";
        t.name = "Touch "+ String(i);
        t.visible = false;
    }
}

void CreateInstructions()
{
    // Construct new Text object, set string to display and font to use
    Text@ instructionText = ui.root.CreateChild("Text");
    instructionText.text = "Drag on the buttons to move them around.\nMulti- button drag also supported.";
    instructionText.SetFont(cache.GetResource("Font", "Fonts/Anonymous Pro.ttf"), 15);

    // Position the text relative to the screen center
    instructionText.horizontalAlignment = HA_CENTER;
    instructionText.verticalAlignment = VA_CENTER;
    instructionText.SetPosition(0, ui.root.height / 4);
}

void SubscribeToEvents()
{
    // Subscribe HandleUpdate() function for processing update events
    SubscribeToEvent("Update", "HandleUpdate");
}

void HandleDragBegin(StringHash eventType, VariantMap& eventData)
{
    Button@ element = eventData["Element"].GetPtr();

    int lx = eventData["X"].GetInt();
    int ly = eventData["Y"].GetInt();

    IntVector2 p = element.position;
    element.vars[VAR_START] = p;
    element.vars[VAR_DELTA] = IntVector2(p.x - lx, p.y - ly);

    int buttons = eventData["Buttons"].GetInt();
    element.vars[VAR_BUTTONS] = buttons;

    Text@ t = element.GetChild(String("Text"));
    t.text = "Drag Begin Buttons: " + String(buttons);

    t = element.GetChild(String("Num Touch"));
    t.text = "Number of buttons: " + String(eventData["NumButtons"].GetInt());
}

void HandleDragMove(StringHash eventType, VariantMap& eventData)
{
    Button@ element = eventData["Element"].GetPtr();
    int buttons = eventData["Buttons"].GetInt();
    IntVector2 d = element.vars[VAR_DELTA].GetIntVector2();
    int X = eventData["X"].GetInt() + d.x;
    int Y = eventData["Y"].GetInt() + d.y;
    int BUTTONS = element.vars[VAR_BUTTONS].GetInt();

    Text@ t = element.GetChild(String("Event Touch"));
    t.text = "Drag Move Buttons: " + String(buttons);

    if (buttons == BUTTONS)
        element.position = IntVector2(X, Y);
}

void HandleDragCancel(StringHash eventType, VariantMap& eventData)
{
    Button@ element = eventData["Element"].GetPtr();
    IntVector2 P = element.vars[VAR_START].GetIntVector2();
    element.position = P;
}

void HandleUpdate(StringHash eventType, VariantMap& eventData)
{
    UIElement@ root = ui.root;

    uint n = input.numTouches;
    for (uint i = 0; i < n; i++)
    {
        Text@ t = root.GetChild("Touch " + String(i));
        TouchState@ ts = input.touches[i];
        t.text = "Touch "+ String(ts.touchID);
        
        IntVector2 pos = ts.position;
        pos.y -= 30;

        t.position = pos;
        t.visible = true;
    }

    for (uint i = n; i < 10; i++)
    {
        Text@ t = root.GetChild("Touch " + String(i));
        t.visible = false;
    }
}

// Create XML patch instructions for screen joystick layout specific to this sample app
String patchInstructions =
        "<patch>" +
        "    <add sel=\"/element/element[./attribute[@name='Name' and @value='Hat0']]\">" +
        "        <attribute name=\"Is Visible\" value=\"false\" />" +
        "    </add>" +
        "</patch>";
