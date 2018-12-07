//
// Copyright (c) 2008-2018 the Urho3D project.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#include <Urho3D/Audio/Audio.h>
#include <Urho3D/Audio/Sound.h>
#include <Urho3D/Core/CoreEvents.h>
#include <Urho3D/Engine/Engine.h>
#include <Urho3D/Graphics/Graphics.h>
#include <Urho3D/Graphics/Zone.h>
#include <Urho3D/Input/Input.h>
#include <Urho3D/IO/IOEvents.h>
#include <Urho3D/IO/Log.h>
#include <Urho3D/IO/MemoryBuffer.h>
#include <Urho3D/IO/VectorBuffer.h>
#include <Urho3D/Network/Network.h>
#include <Urho3D/Network/NetworkEvents.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Scene/Scene.h>
#include <Urho3D/UI/Button.h>
#include <Urho3D/UI/Font.h>
#include <Urho3D/UI/LineEdit.h>
#include <Urho3D/UI/Text.h>
#include <Urho3D/UI/UI.h>
#include <Urho3D/UI/UIEvents.h>

#include "P2PMultiplayer.h"

#include <Urho3D/DebugNew.h>

// Undefine Windows macro, as our Connection class has a function called SendMessage
#ifdef SendMessage
#undef SendMessage
#endif

URHO3D_DEFINE_APPLICATION_MAIN(P2PMultplayer)

P2PMultplayer::P2PMultplayer(Context* context) :
    Sample(context)
{
}

void P2PMultplayer::Start()
{
    // Execute base class startup
    Sample::Start();

    // Enable OS cursor
    GetSubsystem<Input>()->SetMouseVisible(true);

    // Create the user interface
    CreateUI();

    // Subscribe to UI and network events
    SubscribeToEvents();

    // Set the mouse mode to use in the sample
    Sample::InitMouseMode(MM_FREE);

    GetSubsystem<Network>()->SetMode(PEER_TO_PEER);
}

void P2PMultplayer::CreateUI()
{
    SetLogoVisible(true); // We need the full rendering window

    auto* graphics = GetSubsystem<Graphics>();
    UIElement* root = GetSubsystem<UI>()->GetRoot();
    auto* cache = GetSubsystem<ResourceCache>();
    auto* uiStyle = cache->GetResource<XMLFile>("UI/DefaultStyle.xml");
    // Set style to the UI root so that elements will inherit it
    root->SetDefaultStyle(uiStyle);

    auto* font = cache->GetResource<Font>("Fonts/Anonymous Pro.ttf");
    logHistoryText_ = root->CreateChild<Text>();
    logHistoryText_->SetFont(font, 12);
    logHistoryText_->SetPosition(20, 200);
    logHistory_.Resize(20);

    // Create NAT server config fields
    int marginTop = 40;
    CreateLabel("1. Run NAT server somewhere, enter NAT server info and press 'Save NAT settings'", IntVector2(20, marginTop-20));
    natServerAddress_ = CreateLineEdit("nat.frameskippers.com", 200, IntVector2(20, marginTop));
    natServerPort_ = CreateLineEdit("30123", 100, IntVector2(240, marginTop));
    saveNatSettingsButton_ = CreateButton("Save NAT settings", 160, IntVector2(360, marginTop));

    // Create server start button
    marginTop = 120;
    CreateLabel("2. Create server and give others your server GUID", IntVector2(20, marginTop-20));
    guid_ = CreateLineEdit("Your server GUID", 200, IntVector2(20, marginTop));
    startServerButton_ = CreateButton("Start server", 160, IntVector2(240, marginTop));

    // Create client connection related fields
    marginTop = 200;
    CreateLabel("3. Input remote server GUID", IntVector2(20, marginTop-20));
    serverGuid_ = CreateLineEdit("Remote server GUID", 200, IntVector2(20, marginTop));
    connectButton_ = CreateButton("Connect", 160, IntVector2(240, marginTop));

    marginTop = 240;
    peerCount_ = CreateLabel("Peers: 0", IntVector2(20, marginTop));
    marginTop = 260;
    myInfo_ = CreateLabel("My GUID: ", IntVector2(20, marginTop));
    marginTop = 280;
    hostInfo_ = CreateLabel("Host: ", IntVector2(20, marginTop));

    marginTop = 340;
    CreateLabel("Give the host role to other peers", IntVector2(20, marginTop));
    marginTop = 360;
    resetHost_ = CreateButton("Reset host", 240, IntVector2(20, marginTop));

    // No viewports or scene is defined. However, the default zone's fog color controls the fill color
    GetSubsystem<Renderer>()->GetDefaultZone()->SetFogColor(Color(0.0f, 0.0f, 0.1f));
}

void P2PMultplayer::SubscribeToEvents()
{
    SubscribeToEvent(E_UPDATE, URHO3D_HANDLER(P2PMultplayer, HandleUpdate));
    SubscribeToEvent(E_SERVERCONNECTED, URHO3D_HANDLER(P2PMultplayer, HandleServerConnected));
    SubscribeToEvent(E_SERVERDISCONNECTED, URHO3D_HANDLER(P2PMultplayer, HandleServerDisconnected));
    SubscribeToEvent(E_CONNECTFAILED, URHO3D_HANDLER(P2PMultplayer, HandleConnectFailed));

    // NAT server connection related events
    SubscribeToEvent(E_NATMASTERCONNECTIONFAILED, URHO3D_HANDLER(P2PMultplayer, HandleNatConnectionFailed));
    SubscribeToEvent(E_NATMASTERCONNECTIONSUCCEEDED, URHO3D_HANDLER(P2PMultplayer, HandleNatConnectionSucceeded));

    // NAT punchtrough request events
    SubscribeToEvent(E_NETWORKNATPUNCHTROUGHSUCCEEDED, URHO3D_HANDLER(P2PMultplayer, HandleNatPunchtroughSucceeded));
    SubscribeToEvent(E_NETWORKNATPUNCHTROUGHFAILED, URHO3D_HANDLER(P2PMultplayer, HandleNatPunchtroughFailed));

    SubscribeToEvent(E_CLIENTCONNECTED, URHO3D_HANDLER(P2PMultplayer, HandleClientConnected));
    SubscribeToEvent(E_CLIENTDISCONNECTED, URHO3D_HANDLER(P2PMultplayer, HandleClientDisconnected));

    SubscribeToEvent(saveNatSettingsButton_, "Released", URHO3D_HANDLER(P2PMultplayer, HandleSaveNatSettings));
    SubscribeToEvent(startServerButton_, "Released", URHO3D_HANDLER(P2PMultplayer, HandleStartServer));
    SubscribeToEvent(connectButton_, "Released", URHO3D_HANDLER(P2PMultplayer, HandleConnect));
    SubscribeToEvent(resetHost_, "Released", URHO3D_HANDLER(P2PMultplayer, HandleResetHost));
}

Button* P2PMultplayer::CreateButton(const String& text, int width, IntVector2 position)
{
    auto* cache = GetSubsystem<ResourceCache>();
    auto* font = cache->GetResource<Font>("Fonts/Anonymous Pro.ttf");

    auto* button = GetSubsystem<UI>()->GetRoot()->CreateChild<Button>();
    button->SetStyleAuto();
    button->SetFixedWidth(width);
    button->SetFixedHeight(30);
    button->SetPosition(position);

    auto* buttonText = button->CreateChild<Text>();
    buttonText->SetFont(font, 12);
    buttonText->SetAlignment(HA_CENTER, VA_CENTER);
    buttonText->SetText(text);

    return button;
}

LineEdit* P2PMultplayer::CreateLineEdit(const String& placeholder, int width, IntVector2 pos)
{
    auto* textEdit = GetSubsystem<UI>()->GetRoot()->CreateChild<LineEdit>("");
    textEdit->SetStyleAuto();
    textEdit->SetFixedWidth(width);
    textEdit->SetFixedHeight(30);
    textEdit->SetText(placeholder);
    textEdit->SetPosition(pos);
    return textEdit;
}

Text* P2PMultplayer::CreateLabel(const String& text, IntVector2 pos)
{
    auto* cache = GetSubsystem<ResourceCache>();
    // Create log element to view latest logs from the system
    auto* font = cache->GetResource<Font>("Fonts/Anonymous Pro.ttf");
    auto* label = GetSubsystem<UI>()->GetRoot()->CreateChild<Text>();
    label->SetFont(font, 12);
    label->SetColor(Color(0.0f, 1.0f, 0.0f));
    label->SetPosition(pos);
    label->SetText(text);

    return label;
}

void P2PMultplayer::ShowLogMessage(const String& row)
{
    logHistory_.Erase(0);
    logHistory_.Push(row);

    // Concatenate all the rows in history
    String allRows;
    for (unsigned i = 0; i < logHistory_.Size(); ++i)
        allRows += logHistory_[i] + "\n";

    logHistoryText_->SetText(allRows);
}

void P2PMultplayer::HandleSaveNatSettings(StringHash eventType, VariantMap& eventData)
{
    // Save NAT server configuration
    GetSubsystem<Network>()->SetNATServerInfo(natServerAddress_->GetText(), ToInt(natServerPort_->GetText()));
    ShowLogMessage("Saving NAT settings: " + natServerAddress_->GetText() + ":" + natServerPort_->GetText());
}

void P2PMultplayer::HandleServerConnected(StringHash eventType, VariantMap& eventData)
{
    ShowLogMessage("Client: Server connected!");
}

void P2PMultplayer::HandleServerDisconnected(StringHash eventType, VariantMap& eventData)
{
    ShowLogMessage("Client: Server disconnected!");
}

void P2PMultplayer::HandleConnectFailed(StringHash eventType, VariantMap& eventData)
{
    ShowLogMessage("Client: Connection failed!");
}

void P2PMultplayer::HandleStartServer(StringHash eventType, VariantMap& eventData)
{
    ShowLogMessage("Server: Server started P2P session");

    GetSubsystem<Network>()->StartSession(scene_);
    // Output our assigned GUID which others will use to connect to our server
    guid_->SetText(GetSubsystem<Network>()->GetGUID());
}

void P2PMultplayer::HandleConnect(StringHash eventType, VariantMap& eventData)
{
    VariantMap userData = GetEventDataMap();
    userData["Name"] = "Urho3D";

    // Attempt connecting to server using custom GUID, Scene = null as a second parameter and user identity is passed as third parameter
    GetSubsystem<Network>()->JoinSession(serverGuid_->GetText(), scene_, userData);
    ShowLogMessage("Client: Attempting Join P2@ session " + serverGuid_->GetText());
}

void P2PMultplayer::HandleNatConnectionFailed(StringHash eventType, VariantMap& eventData)
{
    ShowLogMessage("Connection to NAT master server failed!");
}

void P2PMultplayer::HandleNatConnectionSucceeded(StringHash eventType, VariantMap& eventData)
{
    ShowLogMessage("Connection to NAT master server succeeded!");
}

void P2PMultplayer::HandleNatPunchtroughSucceeded(StringHash eventType, VariantMap& eventData)
{
    ShowLogMessage("NAT punchtrough succeeded!");
}

void P2PMultplayer::HandleNatPunchtroughFailed(StringHash eventType, VariantMap& eventData)
{
    ShowLogMessage("NAT punchtrough failed!");
}

void P2PMultplayer::HandleClientConnected(StringHash eventType, VariantMap& eventData)
{
    ShowLogMessage("Server: Client connected!");
}

void P2PMultplayer::HandleClientDisconnected(StringHash eventType, VariantMap& eventData)
{
    ShowLogMessage("Server: Client disconnected!");
}

void P2PMultplayer::UpdateInfo()
{
    peerCount_->SetText("Peers: " + String(GetSubsystem<Network>()->GetParticipantCount()));
    hostInfo_->SetText("Host: " + GetSubsystem<Network>()->GetHostAddress());
    myInfo_->SetText("My GUID: " + GetSubsystem<Network>()->GetGUID());
}

void P2PMultplayer::HandleUpdate(StringHash eventType, VariantMap& eventData)
{
    if (updateTimer_.GetMSec(false) > 500) {
        updateTimer_.Reset();
        UpdateInfo();
    }
}

void P2PMultplayer::HandleResetHost(StringHash eventType, VariantMap& eventData)
{
    GetSubsystem<Network>()->ResetHost();
}