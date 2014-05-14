-- Chat example
-- This sample demonstrates:
--     - Starting up a network server or connecting to it
--     - Implementing simple chat functionality with network messages

require "LuaScripts/Utilities/Sample"

-- Identifier for the chat network messages
local MSG_CHAT = 32
-- UDP port we will use
local CHAT_SERVER_PORT = 2345

local chatHistory = {}
local chatHistoryText = nil
local buttonContainer = nil
local textEdit = nil
local sendButton = nil
local connectButton = nil
local disconnectButton = nil
local startServerButton = nil

function Start()
    -- Execute the common startup for samples
    SampleStart()

    -- Enable OS cursor
    input.mouseVisible = true

    -- Create the user interface
    CreateUI()

    -- Subscribe to UI and network events
    SubscribeToEvents()
end

function CreateUI()
    SetLogoVisible(false) -- We need the full rendering window

    local uiStyle = cache:GetResource("XMLFile", "UI/DefaultStyle.xml")
    -- Set style to the UI root so that elements will inherit it
    ui.root.defaultStyle = uiStyle

    local font = cache:GetResource("Font", "Fonts/Anonymous Pro.ttf")
    chatHistoryText = ui.root:CreateChild("Text")
    chatHistoryText:SetFont(font, 12)

    buttonContainer = ui.root:CreateChild("UIElement")
    buttonContainer:SetFixedSize(graphics.width, 20)
    buttonContainer:SetPosition(0, graphics.height - 20)
    buttonContainer.layoutMode = LM_HORIZONTAL

    textEdit = buttonContainer:CreateChild("LineEdit")
    textEdit:SetStyleAuto()

    sendButton = CreateButton("Send", 70)
    connectButton = CreateButton("Connect", 90)
    disconnectButton = CreateButton("Disconnect", 100)
    startServerButton = CreateButton("Start Server", 110)

    UpdateButtons()

    local size = (graphics.height - 20) / chatHistoryText.rowHeight
    for i = 1, size do
        table.insert(chatHistory, "")
    end

    -- No viewports or scene is defined. However, the default zone's fog color controls the fill color
    renderer.defaultZone.fogColor = Color(0.0, 0.0, 0.1)
end

function SubscribeToEvents()
    -- Subscribe to UI element events
    SubscribeToEvent(textEdit, "TextFinished", "HandleSend")
    SubscribeToEvent(sendButton, "Released", "HandleSend")
    SubscribeToEvent(connectButton, "Released", "HandleConnect")
    SubscribeToEvent(disconnectButton, "Released", "HandleDisconnect")
    SubscribeToEvent(startServerButton, "Released", "HandleStartServer")

    -- Subscribe to log messages so that we can pipe them to the chat window
    SubscribeToEvent("LogMessage", "HandleLogMessage")

    -- Subscribe to network events
    SubscribeToEvent("NetworkMessage", "HandleNetworkMessage")
    SubscribeToEvent("ServerConnected", "HandleConnectionStatus")
    SubscribeToEvent("ServerDisconnected", "HandleConnectionStatus")
    SubscribeToEvent("ConnectFailed", "HandleConnectionStatus")
end

function CreateButton(text, width)
    local font = cache:GetResource("Font", "Fonts/Anonymous Pro.ttf")

    local button = buttonContainer:CreateChild("Button")
    button:SetStyleAuto()
    button:SetFixedWidth(width)

    local buttonText = button:CreateChild("Text")
    buttonText:SetFont(font, 12)
    buttonText:SetAlignment(HA_CENTER, VA_CENTER)
    buttonText.text = text

    return button
end

function ShowChatText(row)
    table.remove(chatHistory, 1)
    table.insert(chatHistory, row)

    -- Concatenate all the rows in history
    local allRows = ""
    for i, r in ipairs(chatHistory) do
        allRows = allRows .. r .. "\n"
    end
    chatHistoryText.text = allRows
end

function UpdateButtons()
    local serverConnection = network.serverConnection
    local serverRunning = network.serverRunning

    -- Show and hide buttons so that eg. Connect and Disconnect are never shown at the same time
    sendButton.visible = serverConnection ~= nil
    connectButton.visible = (serverConnection == nil) and (not serverRunning)
    disconnectButton.visible = (serverConnection ~= nil) or serverRunning
    startServerButton.visible = (serverConnection == nil) and (not serverRunning)
end

function HandleLogMessage(eventType, eventData)
    ShowChatText(eventData:GetString("Message"))
end

function HandleSend(eventType, eventData)
    local text = textEdit.text
    if text == "" then
        return -- Do not send an empty message
    end

    local serverConnection = network.serverConnection
    if serverConnection ~= nil then
        -- A VectorBuffer object is convenient for constructing a message to send
        local msg = VectorBuffer()
        msg:WriteString(text)
        -- Send the chat message as in-order and reliable
        serverConnection:SendMessage(MSG_CHAT, true, true, msg)
        -- Empty the text edit after sending
        textEdit.text = ""
    end
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

    UpdateButtons()
end

function HandleDisconnect(eventType, eventData)
    local serverConnection = network.serverConnection
    -- If we were connected to server, disconnect
    if serverConnection ~= nil then
        serverConnection:Disconnect()
    -- Or if we were running a server, stop it
    else
        if network.serverRunning then
            network:StopServer()
        end
    end

    UpdateButtons()
end

function HandleStartServer(eventType, eventData)
    network:StartServer(CHAT_SERVER_PORT)

    UpdateButtons()
end

function HandleNetworkMessage(eventType, eventData)
    local msgID = eventData:GetInt("MessageID")
    if msgID == MSG_CHAT then
        local msg = eventData:GetBuffer("Data")
        local text = msg:ReadString()
        -- If we are the server, prepend the sender's IP address and port and echo to everyone
        -- If we are a client, just display the message
        if network.serverRunning then
            local sender = eventData:GetPtr("Connection", "Connection")
            text = sender:ToString() .. " " .. text
            local sendMsg = VectorBuffer()
            sendMsg:WriteString(text)
            -- Broadcast as in-order and reliable
            network:BroadcastMessage(MSG_CHAT, true, true, sendMsg)
        end
        ShowChatText(text)
    end
end

function HandleConnectionStatus(eventType, eventData)
    UpdateButtons()
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
