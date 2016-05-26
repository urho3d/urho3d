// Http request example.
// This example demonstrates:
//     - How to use Http request API

#include "Scripts/Utilities/Sample.as"

String message;
Text@ text;
HttpRequest@ httpRequest;

void Start()
{
    // Execute the common startup for samples
    SampleStart();

    // Create the user interface
    CreateUI();

    // Set the mouse mode to use in the sample
    SampleInitMouseMode(MM_FREE);

    // Subscribe to basic events such as update
    SubscribeToEvents();
}

void CreateUI()
{
    // Construct new Text object
    text = Text();

    // Set font and text color
    text.SetFont(cache.GetResource("Font", "Fonts/Anonymous Pro.ttf"), 15);
    text.color = Color(1.0f, 1.0f, 0.0f);

    // Align Text center-screen
    text.horizontalAlignment = HA_CENTER;
    text.verticalAlignment = VA_CENTER;

    // Add Text instance to the UI root element
    ui.root.AddChild(text);
}

void SubscribeToEvents()
{
    // Subscribe HandleUpdate() function for processing HTTP request
    SubscribeToEvent("Update", "HandleUpdate");
}

void HandleUpdate(StringHash eventType, VariantMap& eventData)
{
    // Create HTTP request
    if (httpRequest is null)
        httpRequest = network.MakeHttpRequest("http://httpbin.org/ip");
    else
    {
        // Initializing HTTP request
        if (httpRequest.state == HTTP_INITIALIZING)
            return;
        // An error has occured
        else if (httpRequest.state == HTTP_ERROR)
        {
            text.text = "An error has occured.";
            UnsubscribeFromEvent("Update");
        }
        // Get message data
        else
        {
            if (httpRequest.availableSize > 0)
                message += httpRequest.ReadLine();
            else
            {
                text.text = "Processing...";

                JSONFile@ json = JSONFile();
                json.FromString(message);

                JSONValue val = json.GetRoot().Get("origin");

                if (val.isNull)
                    text.text = "Invalid string.";
                else
                    text.text =  "Your IP is: " + val.GetString();

                UnsubscribeFromEvent("Update");
            }
        }
    }
}

// Create XML patch instructions for screen joystick layout specific to this sample app
String patchInstructions =
        "<patch>" +
        "    <add sel=\"/element/element[./attribute[@name='Name' and @value='Hat0']]\">" +
        "        <attribute name=\"Is Visible\" value=\"false\" />" +
        "    </add>" +
        "</patch>";

