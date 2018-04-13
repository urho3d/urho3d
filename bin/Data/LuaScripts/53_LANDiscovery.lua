-- Chat example
-- This sample demonstrates:
--     - Starting up a network server or connecting to it
--     - Implementing simple chat functionality with network messages

require "LuaScripts/Utilities/Sample"

local startServer = nil;
local stopServer = nil;
local refreshServerList = nil;
local serverList = nil;

-- Local server port
local SERVER_PORT = 54654

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
end

function CreateUI()

    SetLogoVisible(true) -- We need the full rendering window

    local uiStyle = cache:GetResource("XMLFile", "UI/DefaultStyle.xml")
    -- Set style to the UI root so that elements will inherit it
    ui.root.defaultStyle = uiStyle


    local marginTop = 20
    CreateLabel("1. Start server", IntVector2(20, marginTop-20));
    startServer = CreateButton("Start server", 160, IntVector2(20, marginTop));
    stopServer = CreateButton("Stop server", 160, IntVector2(20, marginTop));
    stopServer.visible = false;


    marginTop = marginTop + 80;
    CreateLabel("2. Discover LAN servers", IntVector2(20, marginTop-20));
    refreshServerList = CreateButton("Search...", 160, IntVector2(20, marginTop));


    marginTop = marginTop + 80;
    CreateLabel("Local servers:", IntVector2(20, marginTop - 20));
    serverList = CreateLabel("", IntVector2(20, marginTop));

end

function SubscribeToEvents()
    SubscribeToEvent("NetworkHostDiscovered", "HandleNetworkHostDiscovered");

    SubscribeToEvent(startServer, "Released", "HandleStartServer");
    SubscribeToEvent(stopServer, "Released", "HandleStopServer");
    SubscribeToEvent(refreshServerList, "Released", "HandleDoNetworkDiscovery");
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
    return label
end

function HandleNetworkHostDiscovered(eventType, eventData)
    local text = serverList.text
    local data = eventData["Beacon"]:GetVariantMap()
    text = text .. "\n" .. data["Name"]:GetString() .. "(" .. data["Players"]:GetInt() .. ")" .. eventData["Address"]:GetString() .. ":" .. eventData["Port"]:GetInt()
    serverList:SetText(text)
end

function HandleStartServer(eventType, eventData)
    if network:StartServer(SERVER_PORT) == true
    then
        local data = VariantMap();
        data["Name"] = "Test server";
        data["Players"] = 100;
        -- Set data which will be sent to all who requests LAN network discovery
        network:SetDiscoveryBeacon(data);
        startServer.visible = false;
        stopServer.visible = true;
    end
end

function HandleStopServer(eventType, eventData)
    network:StopServer();
    startServer.visible = true;
    stopServer.visible = false;
end

function HandleDoNetworkDiscovery(eventType, eventData)
    network:DiscoverHosts(SERVER_PORT)
    serverList:SetText("")
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
