// Chat example
// This sample demonstrates:
//     - Starting up a network server or connecting to it
//     - Implementing simple chat functionality with network messages

#include "Scripts/Utilities/Sample.as"

// Identifier for the chat network messages
const int MSG_CHAT = 32;
// UDP port we will use
const uint CHAT_SERVER_PORT = 2345;

Array<String> chatHistory;
Text@ chatHistoryText;
UIElement@ buttonContainer;
LineEdit@ textEdit;
Button@ sendButton;
Button@ connectButton;
Button@ disconnectButton;
Button@ startServerButton;

void Start()
{
    // Execute the common startup for samples
    SampleStart();

    // Enable OS cursor
    input.mouseVisible = true;

    // Create the user interface
    CreateUI();

    // Subscribe to UI and network events
    SubscribeToEvents();
}

void CreateUI()
{
    SetLogoVisible(false); // We need the full rendering window

    XMLFile@ uiStyle = cache.GetResource("XMLFile", "UI/DefaultStyle.xml");
    // Set style to the UI root so that elements will inherit it
    ui.root.defaultStyle = uiStyle;

    Font@ font = cache.GetResource("Font", "Fonts/Anonymous Pro.ttf");
    chatHistoryText = ui.root.CreateChild("Text");
    chatHistoryText.SetFont(font, 12);

    buttonContainer = ui.root.CreateChild("UIElement");
    buttonContainer.SetFixedSize(graphics.width, 20);
    buttonContainer.SetPosition(0, graphics.height - 20);
    buttonContainer.layoutMode = LM_HORIZONTAL;

    textEdit = buttonContainer.CreateChild("LineEdit");
    textEdit.SetStyleAuto();

    sendButton = CreateButton("Send", 70);
    connectButton = CreateButton("Connect", 90);
    disconnectButton = CreateButton("Disconnect", 100);
    startServerButton = CreateButton("Start Server", 110);

    UpdateButtons();

    chatHistory.Resize((graphics.height - 20) / chatHistoryText.rowHeight);

    // No viewports or scene is defined. However, the default zone's fog color controls the fill color
    renderer.defaultZone.fogColor = Color(0.0f, 0.0f, 0.1f);
}

void SubscribeToEvents()
{
    // Subscribe to UI element events
    SubscribeToEvent(textEdit, "TextFinished", "HandleSend");
    SubscribeToEvent(sendButton, "Released", "HandleSend");
    SubscribeToEvent(connectButton, "Released", "HandleConnect");
    SubscribeToEvent(disconnectButton, "Released", "HandleDisconnect");
    SubscribeToEvent(startServerButton, "Released", "HandleStartServer");

    // Subscribe to log messages so that we can pipe them to the chat window
    SubscribeToEvent("LogMessage", "HandleLogMessage");

    // Subscribe to network events
    SubscribeToEvent("NetworkMessage", "HandleNetworkMessage");
    SubscribeToEvent("ServerConnected", "HandleConnectionStatus");
    SubscribeToEvent("ServerDisconnected", "HandleConnectionStatus");
    SubscribeToEvent("ConnectFailed", "HandleConnectionStatus");
}

Button@ CreateButton(const String&in text, int width)
{
    Font@ font = cache.GetResource("Font", "Fonts/Anonymous Pro.ttf");

    Button@ button = buttonContainer.CreateChild("Button");
    button.SetStyleAuto();
    button.SetFixedWidth(width);

    Text@ buttonText = button.CreateChild("Text");
    buttonText.SetFont(font, 12);
    buttonText.SetAlignment(HA_CENTER, VA_CENTER);
    buttonText.text = text;

    return button;
}

void ShowChatText(const String& row)
{
    chatHistory.Erase(0);
    chatHistory.Push(row);

    // Concatenate all the rows in history
    String allRows;
    for (uint i = 0; i < chatHistory.length; ++i)
        allRows += chatHistory[i] + "\n";

    chatHistoryText.text = allRows;
}

void UpdateButtons()
{
    Connection@ serverConnection = network.serverConnection;
    bool serverRunning = network.serverRunning;

    // Show and hide buttons so that eg. Connect and Disconnect are never shown at the same time
    sendButton.visible = serverConnection !is null;
    connectButton.visible = serverConnection is null && !serverRunning;
    disconnectButton.visible = serverConnection !is null || serverRunning;
    startServerButton.visible = serverConnection is null && !serverRunning;
}

void HandleLogMessage(StringHash eventType, VariantMap& eventData)
{
    ShowChatText(eventData["Message"].GetString());
}

void HandleSend(StringHash eventType, VariantMap& eventData)
{
    String text = textEdit.text;
    if (text.empty)
        return; // Do not send an empty message

    Connection@ serverConnection = network.serverConnection;

    if (serverConnection !is null)
    {
        // A VectorBuffer object is convenient for constructing a message to send
        VectorBuffer msg;
        msg.WriteString(text);
        // Send the chat message as in-order and reliable
        serverConnection.SendMessage(MSG_CHAT, true, true, msg);
        // Empty the text edit after sending
        textEdit.text = "";
    }
}

void HandleConnect(StringHash eventType, VariantMap& eventData)
{
    String address = textEdit.text.Trimmed();
    if (address.empty)
        address = "localhost"; // Use localhost to connect if nothing else specified
    // Empty the text edit after reading the address to connect to
    textEdit.text = "";

    // Connect to server, do not specify a client scene as we are not using scene replication, just messages.
    // At connect time we could also send identity parameters (such as username) in a VariantMap, but in this
    // case we skip it for simplicity
    network.Connect(address, CHAT_SERVER_PORT, null);

    UpdateButtons();
}

void HandleDisconnect(StringHash eventType, VariantMap& eventData)
{
    Connection@ serverConnection = network.serverConnection;
    // If we were connected to server, disconnect
    if (serverConnection !is null)
        serverConnection.Disconnect();
    // Or if we were running a server, stop it
    else if (network.serverRunning)
        network.StopServer();

    UpdateButtons();
}

void HandleStartServer(StringHash eventType, VariantMap& eventData)
{
    network.StartServer(CHAT_SERVER_PORT);

    UpdateButtons();
}

void HandleNetworkMessage(StringHash eventType, VariantMap& eventData)
{
    int msgID = eventData["MessageID"].GetInt();
    if (msgID == MSG_CHAT)
    {
        VectorBuffer msg = eventData["Data"].GetBuffer();
        String text = msg.ReadString();

        // If we are the server, prepend the sender's IP address and port and echo to everyone
        // If we are a client, just display the message
        if (network.serverRunning)
        {
            Connection@ sender = eventData["Connection"].GetPtr();

            text = sender.ToString() + " " + text;

            VectorBuffer sendMsg;
            sendMsg.WriteString(text);
            // Broadcast as in-order and reliable
            network.BroadcastMessage(MSG_CHAT, true, true, sendMsg);
        }

        ShowChatText(text);
    }
}

void HandleConnectionStatus(StringHash eventType, VariantMap& eventData)
{
    UpdateButtons();
}

// Create XML patch instructions for screen joystick layout specific to this sample app
String patchInstructions =
        "<patch>" +
        "    <add sel=\"/element/element[./attribute[@name='Name' and @value='Button2']]\">" +
        "        <attribute name=\"Is Visible\" value=\"false\" />" +
        "    </add>" +
        "    <add sel=\"/element/element[./attribute[@name='Name' and @value='Hat0']]\">" +
        "        <attribute name=\"Is Visible\" value=\"false\" />" +
        "    </add>" +
        "</patch>";
