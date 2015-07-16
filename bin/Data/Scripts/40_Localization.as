#include "Scripts/Utilities/Sample.as"

Text@ helloText;

void Start()
{
    // Execute the common startup for samples
    SampleStart();
    
    input.mouseVisible = true;
    
    localization.LoadJSONFile("StringsEnRu.json");
    localization.LoadJSONFile("StringsDe.json");
    SubscribeToEvent("ChangeLanguage", "HandleChangeLanguage");

    // Create "Hello World" Text
    CreateText();

    // Finally, hook-up this HelloWorld instance to handle update events
    SubscribeToEvents();
}

void CreateText()
{
    // Construct new Text object
    helloText = Text();

    // Set String to display
    //helloText.text = localization.Get("lang");
    helloText.text = "lang";
    helloText.autoLocalizable = true;

    // Set font and text color
    helloText.SetFont(cache.GetResource("Font", "Fonts/Anonymous Pro.ttf"), 30);
    helloText.color = Color(0.0f, 1.0f, 0.0f);

    // Align Text center-screen
    helloText.horizontalAlignment = HA_CENTER;
    helloText.verticalAlignment = VA_CENTER;

    // Add Text instance to the UI root element
    ui.root.AddChild(helloText);
}

void SubscribeToEvents()
{
    // Subscribe HandleUpdate() function for processing update events
    SubscribeToEvent("Update", "HandleUpdate");
}

void HandleUpdate(StringHash eventType, VariantMap& eventData)
{
   if (input.keyPress[KEY_SPACE])
   {
       uint lang = localization.languageIndex;
       lang++;
       if (lang >= localization.numLanguages)
           lang = 0;
       localization.SetLanguage(lang);
   }
}


void HandleChangeLanguage(StringHash eventType, VariantMap& eventData)
{
    //helloText.text = localization.Get("lang");
}

// Create XML patch instructions for screen joystick layout specific to this sample app
String patchInstructions =
        "<patch>" +
        "    <add sel=\"/element/element[./attribute[@name='Name' and @value='Hat0']]\">" +
        "        <attribute name=\"Is Visible\" value=\"false\" />" +
        "    </add>" +
        "</patch>";
