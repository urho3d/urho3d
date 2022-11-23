#include "Scripts/Utilities/Sample.as"

// Current score
BigInt score_;

// Number of points received per click
BigInt power_ = 1;

// Delay after click
float clickDelay_ = 0.f;

void Start()
{
    SampleStart();
    CreateUI();
    SampleInitMouseMode(MM_FREE);
    SubscribeToEvents();
}

// Construct UI elements
void CreateUI()
{
    XMLFile@ style = cache.GetResource("XMLFile", "UI/DefaultStyle.xml");
    ui.root.defaultStyle = style;

    // Text in the center of the screen will initially contain hint, and then score
    Text@ scoreText = ui.root.CreateChild("Text", "Score");
    scoreText.SetText("Hold LMB to play.\nClick RMB to upgrade power.");
    scoreText.SetFont(cache.GetResource("Font", "Fonts/Anonymous Pro.ttf"), 30);
    scoreText.SetColor(Color::GREEN);
    scoreText.SetHorizontalAlignment(HA_CENTER);
    scoreText.SetVerticalAlignment(VA_CENTER);

    Text@ powerText = ui.root.CreateChild("Text", "Power");
    powerText.SetText("Power: " + power_.ToString());
    powerText.SetFont(cache.GetResource("Font", "Fonts/Anonymous Pro.ttf"), 30);
    powerText.SetColor(Color::WHITE);
    powerText.SetPosition(IntVector2(10, 10));
}

void SubscribeToEvents()
{
    SubscribeToEvent("Update", "HandleUpdate");
    SubscribeToEvent("MouseButtonDown", "HandleMouseButtonDown");
}

String ShortNumberRepresentation(const BigInt&in value)
{
    String str = value.ToString();

    uint len = str.Length();

    if (len > 45)
        return str.Substring(0, len - 45) + " quattuordecillion";

    if (len > 42)
        return str.Substring(0, len - 42) + " tredecillion";

    if (len > 39)
        return str.Substring(0, len - 39) + " duodecillion";

    if (len > 36)
        return str.Substring(0, len - 36) + " undecillion";

    if (len > 33)
        return str.Substring(0, len - 33) + " decillion";

    if (len > 30)
        return str.Substring(0, len - 30) + " nonillion";

    if (len > 27)
        return str.Substring(0, len - 27) + " octillion";

    if (len > 24)
        return str.Substring(0, len - 24) + " septillion";

    if (len > 21)
        return str.Substring(0, len - 21) + " sextillion";

    if (len > 18)
        return str.Substring(0, len - 18) + " quintillion";

    if (len > 15)
        return str.Substring(0, len - 15) + " quadrillion";

    if (len > 12)
        return str.Substring(0, len - 12) + " trillion";

    if (len > 9)
        return str.Substring(0, len - 9) + " billion";

    if (len > 6)
        return str.Substring(0, len - 6) + " million";

    if (len > 3)
        return str.Substring(0, len - 3) + " thousand";

    return str;
}

void HandleUpdate(StringHash eventType, VariantMap& eventData)
{
    float timeStep = eventData["TimeStep"].GetFloat();

    if (clickDelay_ > 0.f)
        clickDelay_ -= timeStep;

    if (input.GetMouseButtonDown(MOUSEB_LEFT) && clickDelay_ <= 0.f)
    {
        score_ += power_;

        Text@ scoreText = cast<Text>(ui.root.GetChild("Score", false));
        scoreText.SetText(ShortNumberRepresentation(score_));

        clickDelay_ = 0.2f;
    }
}

// Handle the mouse click event
void HandleMouseButtonDown(StringHash eventType, VariantMap& eventData)
{
    MouseButton button = eventData["Button"].GetUInt();
    
    if (button == MOUSEB_RIGHT)
    {
        power_ *= 2;

        Text@ powerText = cast<Text>(ui.root.GetChild("Power", false));
        powerText.SetText("Power: " + ShortNumberRepresentation(power_));
    }
}

// Create XML patch instructions for screen joystick layout specific to this sample app
String patchInstructions =
        "<patch>" +
        "    <add sel=\"/element/element[./attribute[@name='Name' and @value='Hat0']]\">" +
        "        <attribute name=\"Is Visible\" value=\"false\" />" +
        "    </add>" +
        "</patch>";
