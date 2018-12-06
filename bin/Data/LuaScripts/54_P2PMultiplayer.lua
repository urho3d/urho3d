-- Chat example
-- This sample demonstrates:
--     - Starting up a network server or connecting to it
--     - Implementing simple chat functionality with network messages

require "LuaScripts/Utilities/Sample"

local natServerAddress = nil
local natServerPort = nil
local saveNatSettingsButton = nil

local startServerButton = nil

local serverGuid = nil
local connectButton = nil

local logHistory = {}
local logHistoryText = nil

local peerCount = nil
local myInfo = nil
local hostInfo = nil

local guid = nil

local timer = 0;

function Start()
    -- Execute the common startup for samples
    SampleStart()

    -- Enable OS cursor
    input.mouseVisible = true

    -- Create the user interface
    CreateUI()

    -- Set the mouse mode to use in the sample
    SampleInitMouseMode(MM_FREE)

    -- Subscribe to UI and network events
    SubscribeToEvents()

    network:SetMode(PEER_TO_PEER);
end

function CreateUI()

    SetLogoVisible(true) -- We need the full rendering window

    local uiStyle = cache:GetResource("XMLFile", "UI/DefaultStyle.xml")
    -- Set style to the UI root so that elements will inherit it
    ui.root.defaultStyle = uiStyle

    local font = cache:GetResource("Font", "Fonts/Anonymous Pro.ttf")
    logHistoryText = ui.root:CreateChild("Text")
    logHistoryText:SetFont(font, 12)
    logHistoryText:SetPosition(20, 200);

    local marginTop = 40
    CreateLabel("1. Run NAT server somewhere, enter NAT server info and press 'Save NAT settings'", IntVector2(20, marginTop-20));
    natServerAddress = CreateLineEdit("nat.frameskippers.com", 200, IntVector2(20, marginTop));
    natServerPort = CreateLineEdit("30123", 100, IntVector2(240, marginTop));
    saveNatSettingsButton = CreateButton("Save NAT settings", 160, IntVector2(360, marginTop));


    marginTop = 120;
    CreateLabel("2. Create server and give others your server GUID", IntVector2(20, marginTop-20));
    guid = CreateLineEdit("Your server GUID", 200, IntVector2(20, marginTop));
    startServerButton = CreateButton("Start session", 160, IntVector2(240, marginTop));


    marginTop = 200;
    CreateLabel("3. Input remote session GUID", IntVector2(20, marginTop-20));
    serverGuid = CreateLineEdit("Remote server GUID", 200, IntVector2(20, marginTop));
    connectButton = CreateButton("Join session", 160, IntVector2(240, marginTop));

    marginTop = 240;
    peerCount = CreateLabel("Peers: 0", IntVector2(20, marginTop));
    marginTop = 260;
    myInfo = CreateLabel("My GUID: ", IntVector2(20, marginTop));
    marginTop = 280;
    hostInfo = CreateLabel("Host: ", IntVector2(20, marginTop));

    local size = 20
    for i = 1, size do
        table.insert(logHistory, "")
    end

    -- No viewports or scene is defined. However, the default zone's fog color controls the fill color
    renderer.defaultZone.fogColor = Color(0.0, 0.0, 0.1)
end

function SubscribeToEvents()
    SubscribeToEvent("Update", "HandleUpdate");
    SubscribeToEvent("ServerConnected", "HandleServerConnected");
    SubscribeToEvent("ServerDisconnected", "HandleServerDisconnected");
    SubscribeToEvent("ConnectFailed", "HandleConnectFailed");

    -- NAT server connection related events
    SubscribeToEvent("NetworkNatMasterConnectionFailed", "HandleNatConnectionFailed");
    SubscribeToEvent("NetworkNatMasterConnectionSucceeded", "HandleNatConnectionSucceeded");

    -- NAT punchtrough request events
    SubscribeToEvent("NetworkNatPunchtroughSucceeded", "HandleNatPunchtroughSucceeded");
    SubscribeToEvent("NetworkNatPunchtroughFailed", "HandleNatPunchtroughFailed");

    SubscribeToEvent("ClientConnected", "HandleClientConnected");
    SubscribeToEvent("ClientDisconnected", "HandleClientDisconnected");

    -- Subscribe to UI element events
    SubscribeToEvent(saveNatSettingsButton, "Released", "HandleSaveNatSettings");
    SubscribeToEvent(startServerButton, "Released", "HandleStartServer");
    SubscribeToEvent(connectButton, "Released", "HandleConnect");
end

function CreateButton(text, width, position)
    local font = cache:GetResource("Font", "Fonts/Anonymous Pro.ttf")

    local button = ui.root:CreateChild("Button")
    button:SetStyleAuto()
    button:SetFixedWidth(width)
    button:SetFixedHeight(30)
    button:SetPosition(position.x, position.y)

    local buttonText = button:CreateChild("Text")
    buttonText:SetFont(font, 12)
    buttonText:SetAlignment(HA_CENTER, VA_CENTER)
    buttonText.text = text

    return button
end

function CreateLabel(text, position)
    local font = cache:GetResource("Font", "Fonts/Anonymous Pro.ttf")
    local label = ui.root:CreateChild("Text")
    label:SetFont(font, 12)
    label.color = Color(0.0, 1.0, 0.0)
    label:SetPosition(position.x, position.y)
    label.text = text
    return label;
end

function CreateLineEdit(placeholder, width, position)
    local textEdit = ui.root:CreateChild("LineEdit")
    textEdit:SetStyleAuto()
    textEdit:SetFixedWidth(width)
    textEdit:SetFixedHeight(30)
    textEdit.text = placeholder
    textEdit:SetPosition(position.x, position.y)
    return textEdit
end

function ShowLogMessage(row)
    table.remove(logHistory, 1)
    table.insert(logHistory, row)

    -- Concatenate all the rows in history
    local allRows = ""
    for i, r in ipairs(logHistory) do
        allRows = allRows .. r .. "\n"
    end
    logHistoryText.text = allRows
end


function HandleLogMessage(eventType, eventData)
    ShowChatText(eventData["Message"]:GetString())
end

function HandleSaveNatSettings(eventType, eventData)

    local address = natServerAddress.text
    local port = natServerPort.text
    -- Save NAT server configuration
    network:SetNATServerInfo(address, port);
    ShowLogMessage("Saving NAT settings: " .. address .. ":" .. port);
end

function HandleServerConnected(eventType, eventData)

end

function HandleConnect(eventType, eventData)
    local address = textEdit.text
    if address == "" then
        address = "localhost" -- Use localhost to connect if nothing else specified
    end

    -- Empty the text edit after reading the address to connect to
    textEdit.text = ""

    -- Connect to server, do not specify a client scene as we are not using scene replication, just messages.
    -- At connect time we could also send identity parameters (such as username) in a VariantMap, but in this
    -- case we skip it for simplicity
    network:Connect(address, CHAT_SERVER_PORT, nil)

end

function HandleServerConnected(eventType, eventData)
    ShowLogMessage("Client: Server connected!");
end

function HandleServerDisconnected(eventType, eventData)
    ShowLogMessage("Client: Server disconnected!");
end

function HandleConnectFailed(eventType, eventData)
    ShowLogMessage("Client: Connection failed!");
end

function HandleStartServer(eventType, eventData)
    network:StartSession(scene_);
    ShowLogMessage("Server: P2P Session started: ");

    -- Output our assigned GUID which others will use to connect to our server
    guid.text = network:GetGUID();
end

function HandleConnect(eventType, eventData)
    local userData = VariantMap()
    userData["Name"] = "Urho3D";

    -- Attempt connecting to server using custom GUID, Scene = null as a second parameter and user identity is passed as third parameter
    network:JoinSession(serverGuid.text, scene_, userData);
    ShowLogMessage("Client: Joining P2P session: " + serverGuid.text);
end

function HandleNatConnectionFailed(eventType, eventData)
    ShowLogMessage("Connection to NAT master server failed!");
end

function HandleNatConnectionSucceeded(eventType, eventData)
    ShowLogMessage("Connection to NAT master server succeeded!");
end

function HandleNatPunchtroughSucceeded(eventType, eventData)
    ShowLogMessage("NAT punchtrough succeeded!");
end

function HandleNatPunchtroughFailed(eventType, eventData)
    ShowLogMessage("NAT punchtrough failed!");
end

function HandleClientConnected(eventType, eventData)
    ShowLogMessage("Server: Client connected!");
end

function HandleClientDisconnected(eventType, eventData)
    ShowLogMessage("Server: Client disconnected!");
end

function UpdateInfo()
    peerCount.text = "Peers: " .. network:GetParticipantCount();
    hostInfo.text = "Host: " .. network:GetHostAddress();
    myInfo.text = "My GUID: " .. network:GetGUID();
end

function HandleUpdate(eventType, eventData)
    local timeStep = eventData["TimeStep"]:GetFloat();
    timer = timer + timeStep;
    if timer > 0.5 then
        timer = 0;
        UpdateInfo();
    end
end

-- Create XML patch instructions for screen joystick layout specific to this sample app
function GetScreenJoystickPatchString()
    return
        "<patch>" ..
        "    <add sel=\"/element/element[./attribute[@name='Name' and @value='Button2']]\">" ..
        "        <attribute name=\"Is Visible\" value=\"false\" />" ..
        "    </add>" ..
        "    <add sel=\"/element/element[./attribute[@name='Name' and @value='Hat0']]\">" ..
        "        <attribute name=\"Is Visible\" value=\"false\" />" ..
        "    </add>" ..
        "</patch>"
end
