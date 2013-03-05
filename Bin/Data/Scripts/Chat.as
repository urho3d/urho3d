#include "Scripts/Utilities/Network.as"

Text@ chatHistoryText;
UIElement@ buttonLayout;
LineEdit@ textEdit;
Button@ sendButton;
Button@ connectButton;
Button@ disconnectButton;
Button@ startServerButton;

XMLFile@ uiStyle;
Font@ font;
Array<String> chatHistory;
bool inLogMessage = false;

const int MSG_CHAT = 32;

void Start()
{
    SubscribeToEvent("NetworkMessage", "HandleNetworkMessage");

    if (engine.headless)
        OpenConsoleWindow();
    else
    {
        InitUI();

        SubscribeToEvent("LogMessage", "HandleLogMessage");
        SubscribeToEvent("KeyDown", "HandleKeyDown");
        SubscribeToEvent(textEdit, "TextFinished", "HandleTextFinished");
        SubscribeToEvent(sendButton, "Pressed", "HandleSend");
        SubscribeToEvent(connectButton, "Pressed", "HandleConnect");
        SubscribeToEvent(disconnectButton, "Pressed", "HandleDisconnect");
        SubscribeToEvent(startServerButton, "Pressed", "HandleStartServer");
    }
    
    ParseNetworkArguments();
    if (runServer)
        network.StartServer(serverPort);
    if (runClient)
        network.Connect(serverAddress, serverPort, null);
}

void InitUI()
{
    uiStyle = cache.GetResource("XMLFile", "UI/DefaultStyle.xml");
    font = cache.GetResource("Font", "Fonts/Anonymous Pro.ttf");

    engine.CreateDebugHud();
    debugHud.style = uiStyle;
    debugHud.mode = DEBUGHUD_SHOW_PROFILER;
    debugHud.profilerText.opacity = 0.5;

    Cursor@ newCursor = Cursor("Cursor");
    newCursor.style = uiStyle;
    newCursor.position = IntVector2(graphics.width / 2, graphics.height / 2);
    ui.cursor = newCursor;

    chatHistoryText = Text();
    chatHistoryText.SetFont(font, 12);
    ui.root.AddChild(chatHistoryText);

    buttonLayout = UIElement();
    buttonLayout.SetFixedSize(graphics.width, 20);
    buttonLayout.position = IntVector2(0, graphics.height - 20);
    buttonLayout.layoutMode = LM_HORIZONTAL;
    ui.root.AddChild(buttonLayout);

    textEdit = LineEdit();
    textEdit.style = uiStyle;
    buttonLayout.AddChild(textEdit);

    sendButton = AddUIButton("Send", 70);
    connectButton = AddUIButton("Connect", 90);
    disconnectButton = AddUIButton("Disconnect", 100);
    startServerButton = AddUIButton("Start Server", 110);

    chatHistory.Resize((graphics.height - 20) / chatHistoryText.rowHeight);
    
    // No viewports or scene is defined. However, the default zone's fog color controls the fill color
    renderer.defaultZone.fogColor = Color(0, 0, 0.1);
}

Button@ AddUIButton(const String& text, int width)
{
    Button@ button = Button();
    button.style = uiStyle;
    button.SetFixedWidth(width);

    Text@ buttonText = Text();
    buttonText.SetFont(font, 12);
    buttonText.horizontalAlignment = HA_CENTER;
    buttonText.verticalAlignment = VA_CENTER;
    buttonText.text = text;
    
    button.AddChild(buttonText);
    buttonLayout.AddChild(button);

    return button;
}

void AddChatRow(const String& row)
{
    // If running in headless mode, only print the row to the log
    if (chatHistory.empty)
    {
        Print(row);
        return;
    }

    chatHistory.Erase(0);
    chatHistory.Push(row);
    
    String allRows;
    for (uint i = 0; i < chatHistory.length; ++i)
        allRows += chatHistory[i] + "\n";
    chatHistoryText.text = allRows;
}

void HandleTextFinished()
{
    Connection@ serverConnection = network.serverConnection;
    if (serverConnection is null || !serverConnection.connected)
        HandleConnect();
    else
        HandleSend();
}

void HandleSend()
{
    String chatText = textEdit.text.Trimmed();
    Connection@ serverConnection = network.serverConnection;
    
    if (!chatText.empty && serverConnection !is null)
    {
        VectorBuffer msg;
        msg.WriteString(chatText);
        serverConnection.SendMessage(MSG_CHAT, true, true, msg);
        textEdit.text = "";
    }
}

void HandleConnect()
{
    String address = textEdit.text.Trimmed();
    if (!address.empty)
    {
        network.Connect(address, serverPort, null);
        textEdit.text = "";
    }
}

void HandleDisconnect()
{
    network.Disconnect();
}

void HandleStartServer()
{
    if (!network.serverRunning)
        network.StartServer(serverPort);
}

void HandleNetworkMessage(StringHash eventType, VariantMap& eventData)
{
    Connection@ source = eventData["Connection"].GetConnection();

    if (eventData["MessageID"].GetInt() == MSG_CHAT)
    {
        VectorBuffer msg = eventData["Data"].GetBuffer();
        String chatText = msg.ReadString();

        // If we are client, only show the text. If we are server, broadcast to all clients with the sender address prepended
        bool broadcast = source !is network.serverConnection;
        if (!broadcast)
            AddChatRow(chatText);
        else
        {
            chatText = source.address + ":" + source.port + " " + chatText;
            AddChatRow(chatText);

            VectorBuffer newMsg;
            newMsg.WriteString(chatText);

            Array<Connection@> clients = network.clientConnections;
            for (uint i = 0; i < clients.length; ++i)
                clients[i].SendMessage(MSG_CHAT, true, true, newMsg);
        }
    }
}

void HandleLogMessage(StringHash eventType, VariantMap& eventData)
{
    if (!inLogMessage)
    {
        inLogMessage = true;
        AddChatRow(eventData["Message"].GetString());
        inLogMessage = false;
    }
}

void HandleKeyDown(StringHash eventType, VariantMap& eventData)
{
    if (eventData["Key"].GetInt() == KEY_ESC && ui.focusElement is null)
        engine.Exit();
}
