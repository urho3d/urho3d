//
// Copyright (c) 2008-2020 the Urho3D project.
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

#include "LANDiscovery.h"

#include <Urho3D/DebugNew.h>

// Undefine Windows macro, as our Connection class has a function called SendMessage
#ifdef SendMessage
#undef SendMessage
#endif

URHO3D_DEFINE_APPLICATION_MAIN(LANDiscovery)

LANDiscovery::LANDiscovery(Context* context) :
    Sample(context)
{
}

void LANDiscovery::Start()
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
}

void LANDiscovery::CreateUI()
{
    SetLogoVisible(true); // We need the full rendering window

    auto* graphics = GetSubsystem<Graphics>();
    UIElement* root = GetSubsystem<UI>()->GetRoot();
    auto* cache = GetSubsystem<ResourceCache>();
    auto* uiStyle = cache->GetResource<XMLFile>("UI/DefaultStyle.xml");
    // Set style to the UI root so that elements will inherit it
    root->SetDefaultStyle(uiStyle);

    int marginTop = 20;
    CreateLabel("1. Start server", IntVector2(20, marginTop-20));
    startServer_ = CreateButton("Start server", 160, IntVector2(20, marginTop));
    stopServer_ = CreateButton("Stop server", 160, IntVector2(20, marginTop));
    stopServer_->SetVisible(false);

    // Create client connection related fields
    marginTop += 80;
    CreateLabel("2. Discover LAN servers", IntVector2(20, marginTop-20));
    refreshServerList_ = CreateButton("Search...", 160, IntVector2(20, marginTop));

    marginTop += 80;
    CreateLabel("Local servers:", IntVector2(20, marginTop - 20));
    serverList_ = CreateLabel("", IntVector2(20, marginTop));

    // No viewports or scene is defined. However, the default zone's fog color controls the fill color
    GetSubsystem<Renderer>()->GetDefaultZone()->SetFogColor(Color(0.0f, 0.0f, 0.1f));
}

void LANDiscovery::SubscribeToEvents()
{
    SubscribeToEvent(E_NETWORKHOSTDISCOVERED, URHO3D_HANDLER(LANDiscovery, HandleNetworkHostDiscovered));

    SubscribeToEvent(startServer_, "Released", URHO3D_HANDLER(LANDiscovery, HandleStartServer));
    SubscribeToEvent(stopServer_, "Released", URHO3D_HANDLER(LANDiscovery, HandleStopServer));
    SubscribeToEvent(refreshServerList_, "Released", URHO3D_HANDLER(LANDiscovery, HandleDoNetworkDiscovery));
}

Button* LANDiscovery::CreateButton(const String& text, int width, IntVector2 position)
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

Text* LANDiscovery::CreateLabel(const String& text, IntVector2 pos)
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

void LANDiscovery::HandleNetworkHostDiscovered(StringHash eventType, VariantMap& eventData)
{
    using namespace NetworkHostDiscovered;
    URHO3D_LOGINFO("Server discovered!");
    String text = serverList_->GetText();
    VariantMap data = eventData[P_BEACON].GetVariantMap();
    text += "\n" + data["Name"].GetString() + "(" + String(data["Players"].GetInt()) + ")" + eventData[P_ADDRESS].GetString() + ":" + String(eventData[P_PORT].GetInt());
    serverList_->SetText(text);
}

void LANDiscovery::HandleStartServer(StringHash eventType, VariantMap& eventData)
{
    if (GetSubsystem<Network>()->StartServer(SERVER_PORT)) {
        VariantMap data;
        data["Name"] = "Test server";
        data["Players"] = 100;
        /// Set data which will be sent to all who requests LAN network discovery
        GetSubsystem<Network>()->SetDiscoveryBeacon(data);
        startServer_->SetVisible(false);
        stopServer_->SetVisible(true);
    }
}

void LANDiscovery::HandleStopServer(StringHash eventType, VariantMap& eventData)
{
    GetSubsystem<Network>()->StopServer();
    startServer_->SetVisible(true);
    stopServer_->SetVisible(false);
}

void LANDiscovery::HandleDoNetworkDiscovery(StringHash eventType, VariantMap& eventData)
{
    /// Pass in the port that should be checked
    GetSubsystem<Network>()->DiscoverHosts(SERVER_PORT);
    serverList_->SetText("");
}
