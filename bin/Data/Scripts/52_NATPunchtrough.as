// This first example, maintaining tradition, prints a "Hello World" message.
// Furthermore it shows:
//     - Using the Sample utility functions as a base for the application
//     - Adding a Text element to the graphical user interface
//     - Subscribing to and handling of update events

#include "Scripts/Utilities/Sample.as"

LineEdit@ natServerAddress;
LineEdit@ natServerPort;
Button@ saveNatSettingsButton;

Button@ startServerButton;

LineEdit@ serverGuid;
Button@ connectButton;

Text@ logHistoryText;
Array<String> logHistory;

LineEdit@ guid;

const int SERVER_PORT = 54654;

void Start()
{
    // Execute the common startup for samples
    SampleStart();

    // Create "Hello World" Text
    CreateText();

    // Set the mouse mode to use in the sample
    SampleInitMouseMode(MM_FREE);

    // Finally, hook-up this HelloWorld instance to handle update events
    SubscribeToEvents();
}

void CreateText()
{
    XMLFile@ uiStyle = cache.GetResource("XMLFile", "UI/DefaultStyle.xml");
    // Set style to the UI root so that elements will inherit it
    ui.root.defaultStyle = uiStyle;

    // Create log element to view latest logs from the system
    Font@ font = cache.GetResource("Font", "Fonts/Anonymous Pro.ttf");
    logHistoryText = ui.root.CreateChild("Text");
    logHistoryText.SetFont(font, 12);
    logHistoryText.SetPosition(20, 200);

    logHistory.Resize(20);

    // Create NAT server config fields
    int marginTop = 40;
    CreateLabel("1. Run NAT server somewhere, enter NAT server info and press 'Save NAT settings'", IntVector2(20, marginTop-20));
    natServerAddress = CreateLineEdit("127.0.0.1", 200, IntVector2(20, marginTop));
    natServerPort = CreateLineEdit("61111", 100, IntVector2(240, marginTop));
    saveNatSettingsButton = CreateButton("Save NAT settings", 160, IntVector2(360, marginTop));

    // Create server start button
    marginTop = 120;
    CreateLabel("2. Create server and give others your server GUID", IntVector2(20, marginTop-20));
    guid = CreateLineEdit("Your server GUID", 200, IntVector2(20, marginTop));
    startServerButton = CreateButton("Start server", 160, IntVector2(240, marginTop));

    // Create client connection related fields
    marginTop = 200;
    CreateLabel("3. Input local or remote server GUID", IntVector2(20, marginTop-20));
    serverGuid = CreateLineEdit("Remote server GUID", 200, IntVector2(20, marginTop));
    connectButton = CreateButton("Connect", 160, IntVector2(240, marginTop));
}

void SubscribeToEvents()
{
    // Subscribe HandleUpdate() function for processing update events
    SubscribeToEvent("ServerConnected", "HandleServerConnected");
    SubscribeToEvent("ServerDisconnected", "HandleServerDisconnected");
    SubscribeToEvent("ConnectFailed", "HandleConnectFailed");

    // NAT server connection related events
    SubscribeToEvent("NetworkNatMasterConnectionFailed", "HandleNatConnectionFailed");
    SubscribeToEvent("NetworkNatMasterConnectionSucceeded", "HandleNatConnectionSucceeded");

    // NAT punchtrough request events
    SubscribeToEvent("NetworkNatPunchtroughSucceeded", "HandleNatPunchtroughSucceeded");
    SubscribeToEvent("NetworkNatPunchtroughFailed", "HandleNatPunchtroughFailed");

    SubscribeToEvent("ClientConnected", "HandleClientConnected");
    SubscribeToEvent("ClientDisconnected", "HandleClientDisconnected");

    SubscribeToEvent(saveNatSettingsButton, "Released", "HandleSaveNatSettings");
    SubscribeToEvent(startServerButton, "Released", "HandleStartServer");
    SubscribeToEvent(connectButton, "Released", "HandleConnect");
}

void CreateLabel(const String&in text, IntVector2 pos)
{
    // Create log element to view latest logs from the system
    Font@ font = cache.GetResource("Font", "Fonts/Anonymous Pro.ttf");
    Text@ label = ui.root.CreateChild("Text");
    label.SetFont(font, 12);
    label.color = Color(0.0f, 1.0f, 0.0f);
    label.SetPosition(pos.x, pos.y);
    label.text = text;
}

void ShowLogMessage(const String& row)
{
    logHistory.Erase(0);
    logHistory.Push(row);

    // Concatenate all the rows in history
    String allRows;
    for (uint i = 0; i < logHistory.length; ++i)
        allRows += logHistory[i] + "\n";

    logHistoryText.text = allRows;
}

LineEdit@ CreateLineEdit(const String&in placeholder, int width, IntVector2 pos)
{
    LineEdit@ textEdit = ui.root.CreateChild("LineEdit");
    textEdit.SetStyleAuto();
    textEdit.SetFixedWidth(width);
    textEdit.SetFixedHeight(30);
    textEdit.text = placeholder;
    textEdit.SetPosition(pos.x, pos.y);
    return textEdit;
}

Button@ CreateButton(const String&in text, int width, IntVector2 pos)
{
    Font@ font = cache.GetResource("Font", "Fonts/Anonymous Pro.ttf");

    Button@ button = ui.root.CreateChild("Button");
    button.SetStyleAuto();
    button.SetFixedWidth(width);
    button.SetFixedHeight(30);
    button.SetPosition(pos.x, pos.y);

    Text@ buttonText = button.CreateChild("Text");
    buttonText.SetFont(font, 12);
    buttonText.SetAlignment(HA_CENTER, VA_CENTER);
    buttonText.text = text;

    return button;
}

void HandleSaveNatSettings(StringHash eventType, VariantMap& eventData)
{
    // Save NAT server configuration
    network.SetNATServerInfo(natServerAddress.text, natServerPort.text.ToI32());
    ShowLogMessage("Saving NAT settings: " + natServerAddress.text + ":" + natServerPort.text);
}

void HandleServerConnected(StringHash eventType, VariantMap& eventData)
{
    ShowLogMessage("Client: Server connected!");
}

void HandleServerDisconnected(StringHash eventType, VariantMap& eventData)
{
    ShowLogMessage("Client: Server disconnected!");
}

void HandleConnectFailed(StringHash eventType, VariantMap& eventData)
{
    ShowLogMessage("Client: Connection failed!");
}

void HandleStartServer(StringHash eventType, VariantMap& eventData)
{
    network.StartServer(SERVER_PORT);
    ShowLogMessage("Server: Server started on port: " + String(SERVER_PORT));

    // Connect to the NAT server
    network.StartNATClient();
    ShowLogMessage("Server: Starting NAT client for server...");

    // Output our assigned GUID which others will use to connect to our server
    guid.text = network.guid;
}

void HandleConnect(StringHash eventType, VariantMap& eventData)
{
    VariantMap userData;
    userData["Name"] = "Urho3D";

    // Attempt connecting to server using custom GUID, Scene = null as a second parameter and user identity is passed as third parameter
    network.AttemptNATPunchtrough(serverGuid.text, null, userData);
    ShowLogMessage("Client: Attempting NAT punchtrough to guid: " + serverGuid.text);
}

void HandleNatConnectionFailed(StringHash eventType, VariantMap& eventData)
{
    ShowLogMessage("Connection to NAT master server failed!");
}

void HandleNatConnectionSucceeded(StringHash eventType, VariantMap& eventData)
{
    ShowLogMessage("Connection to NAT master server succeeded!");   
}

void HandleNatPunchtroughSucceeded(StringHash eventType, VariantMap& eventData)
{
    ShowLogMessage("NAT punchtrough succeeded!");
}

void HandleNatPunchtroughFailed(StringHash eventType, VariantMap& eventData)
{
    ShowLogMessage("NAT punchtrough failed!");
}

void HandleClientConnected(StringHash eventType, VariantMap& eventData)
{
    ShowLogMessage("Server: Client connected!");
}

void HandleClientDisconnected(StringHash eventType, VariantMap& eventData)
{
    ShowLogMessage("Server: Client disconnected!");   
}

// Create XML patch instructions for screen joystick layout specific to this sample app
String patchInstructions =
        "<patch>" +
        "    <add sel=\"/element/element[./attribute[@name='Name' and @value='Hat0']]\">" +
        "        <attribute name=\"Is Visible\" value=\"false\" />" +
        "    </add>" +
        "</patch>";
