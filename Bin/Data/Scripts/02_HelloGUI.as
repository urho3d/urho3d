// A simple 'HelloWorld' GUI created purely from code.
// This sample demonstrates:
//     - Creation of controls and building a UI hierarchy
//     - Loading UI style from XML and applying it to controls
//     - Handling of global and per-control events

#include "Scripts/Utilities/Sample.as"

Window@ window;

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

    // Initialize Window
    InitWindow();

    // Create and add some controls to the Window
    InitControls();

    SubscribeToEvents();
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
}

void InitWindow()
{
    // Create the Window and add it to the UI's root node
    window = Window();
    ui.root.AddChild(window);

    // Set Window size and layout settings
    window.SetMinSize(384, 192);
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

    // Apply styles
    window.SetStyleAuto();
    windowTitle.SetStyleAuto();
    buttonClose.style = "CloseButton";

    // Lastly, subscribe to buttonClose release (following a 'press') events
    SubscribeToEvent(buttonClose, "Released", "HandleClosePressed");
}

void SubscribeToEvents()
{
    // Subscribe handler; invoked whenever a mouse click event is dispatched
    SubscribeToEvent("UIMouseClick", "HandleControlClicked");
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
    // Note difference to C++: in C++ we would call GetPtr() and cast the void pointer to UIElement, here we must specify
    // what kind of object we are getting. Null will be returned on type mismatch
    UIElement@ clicked = eventData["Element"].GetUIElement();

    String name = "...?";
    if (clicked !is null)
    {
        // Get the name of the control that was clicked
        name = clicked.name;
    }

    // Update the Window's title text
    windowTitle.text = "Hello " + name + "!";
}
