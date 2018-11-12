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
#include <Urho3D/Engine/Engine.h>
#include <Urho3D/Graphics/Graphics.h>
#include <Urho3D/Graphics/Model.h>
#include <Urho3D/Graphics/Zone.h>
#include <Urho3D/Graphics/Octree.h>
#include <Urho3D/Graphics/StaticModel.h>
#include <Urho3D/Input/Input.h>
#include <Urho3D/IO/IOEvents.h>
#include <Urho3D/IO/Log.h>
#include <Urho3D/IO/MemoryBuffer.h>
#include <Urho3D/IO/VectorBuffer.h>
#include <Urho3D/Network/Network.h>
#include <Urho3D/Network/NetworkEvents.h>
#include <Urho3D/Network/HttpRequest.h>
#include <Urho3D/Network/Protocol.h>
#include <Urho3D/Physics/CollisionShape.h>
#include <Urho3D/Physics/PhysicsEvents.h>
#include <Urho3D/Physics/PhysicsWorld.h>
#include <Urho3D/Physics/RigidBody.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Scene/Scene.h>
#include <Urho3D/UI/Button.h>
#include <Urho3D/UI/Font.h>
#include <Urho3D/UI/LineEdit.h>
#include <Urho3D/UI/Text.h>
#include <Urho3D/UI/Text3D.h>
#include <Urho3D/UI/UI.h>
#include <Urho3D/UI/UIEvents.h>
#include <Urho3D/Core/CoreEvents.h>

#include "P2PMultiplayer.h"

#include <Urho3D/DebugNew.h>

// Undefine Windows macro, as our Connection class has a function called SendMessage
#ifdef SendMessage
#undef SendMessage
#endif

URHO3D_DEFINE_APPLICATION_MAIN(P2PMultiplayer)

P2PMultiplayer::P2PMultiplayer(Context* context) :
    Sample(context),
    gameState_(GameState::IN_MENU)
{
    Peer::RegisterObject(context);
}

void P2PMultiplayer::Start()
{
    // Execute base class startup
    Sample::Start();

    // Enable OS cursor
    GetSubsystem<Input>()->SetMouseVisible(true);

    // Create the user interface
    CreateUI();

    CreateScene();

    SetupViewport();

    // Subscribe to UI and network events
    SubscribeToEvents();

    // Set the mouse mode to use in the sample
    Sample::InitMouseMode(MM_FREE);

    Init();
}

void P2PMultiplayer::CreateUI()
{
    SetLogoVisible(false); // We need the full rendering window

    auto* graphics = GetSubsystem<Graphics>();
    UIElement* root = GetSubsystem<UI>()->GetRoot();
    auto* cache = GetSubsystem<ResourceCache>();
    auto* uiStyle = cache->GetResource<XMLFile>("UI/DefaultStyle.xml");
    // Set style to the UI root so that elements will inherit it
    root->SetDefaultStyle(uiStyle);
//
    int marginTop = 20;
//    CreateLabel("1. Start server", IntVector2(20, marginTop-20));
    startSession_ = CreateButton("Start session", 160, IntVector2(20, marginTop));
    nickname_ = CreateLineEdit("Nickname", 160, IntVector2(200, marginTop));
    marginTop += 40;
    guid_ = CreateLineEdit("", 200, IntVector2(20, marginTop));
    marginTop += 40;
    joinSession_ = CreateButton("Join session", 160, IntVector2(20, marginTop));

	marginTop += 80;
    clientCount_ = CreateLabel("Connections: 0", IntVector2(20, marginTop));
    marginTop += 40;
    myGuid_ = CreateLabel("My GUID: ", IntVector2(20, marginTop));
    marginTop += 40;
    hostGuid_ = CreateLabel("HOST GUID:", IntVector2(20, marginTop));

    statusMessage_ = CreateLabel("Status: Started", IntVector2(20, -20));
    statusMessage_->SetAlignment(HA_LEFT, VA_BOTTOM);

    String information = "R - Reset host, if you are the host, \nthis role will be passed to other peers";
    information += "\nE - Disconnect";
    information += "\nT - Toggle ready state";
    information += "\nWASD - move around";
    information += "\nH - Toggle mouse visible/hidden";
    information += "\nN - Start game with other peers\n(requires that all peers are ready)";

    info_ = CreateLabel(information, IntVector2(0, 50));
    info_->SetHorizontalAlignment(HA_RIGHT);

//     No viewports or scene is defined. However, the default zone's fog color controls the fill color
    GetSubsystem<Renderer>()->GetDefaultZone()->SetFogColor(Color(0.0f, 0.0f, 0.1f));
}

void P2PMultiplayer::SubscribeToEvents()
{
    SubscribeToEvent(E_UPDATE, URHO3D_HANDLER(P2PMultiplayer, HandleUpdate));

    SubscribeToEvent(startSession_, "Released", URHO3D_HANDLER(P2PMultiplayer, HandleStartP2PSession));
    SubscribeToEvent(joinSession_, "Released", URHO3D_HANDLER(P2PMultiplayer, HandleJoinP2PSession));

    SubscribeToEvent(E_CLIENTCONNECTED, URHO3D_HANDLER(P2PMultiplayer, HandleClientConnected));
    SubscribeToEvent(E_CLIENTDISCONNECTED, URHO3D_HANDLER(P2PMultiplayer, HandleClientDisconnected));
    SubscribeToEvent(E_P2PALLREADYCHANGED, URHO3D_HANDLER(P2PMultiplayer, HandleAllReadyChanged));
    SubscribeToEvent(E_P2PNEWHOST, URHO3D_HANDLER(P2PMultiplayer, HandleNewHost));
    SubscribeToEvent(E_NETWORKBANNED, URHO3D_HANDLER(P2PMultiplayer, HandleBanned));
    SubscribeToEvent(E_CLIENTIDENTITY, URHO3D_HANDLER(P2PMultiplayer, HandleClientIdentity));

    GetSubsystem<Network>()->RegisterRemoteEvent("GameStart");
    SubscribeToEvent("GameStart", URHO3D_HANDLER(P2PMultiplayer, HandleGameState));
}

void P2PMultiplayer::HandleStartP2PSession(StringHash eventType, VariantMap& eventData)
{
    peers_.Clear();
    URHO3D_LOGINFO("HandleStartP2PSession");
    VariantMap identity;
    identity["Name"] = nickname_->GetText();
    GetSubsystem<Network>()->StartSession(scene_, identity);
    statusMessage_->SetText("Status: Starting P2P session");
    httpRequest_ = GetSubsystem<Network>()->MakeHttpRequest("http://frameskippers.com:82/?guid=" + GetSubsystem<Network>()->GetGUID());

    SubscribeToEvent(E_P2PSESSIONSTARTED, URHO3D_HANDLER(P2PMultiplayer, HandleSessionStarted));
    SubscribeToEvent(E_P2PSESSIONJOINED, URHO3D_HANDLER(P2PMultiplayer, HandleSessionJoined));
}

void P2PMultiplayer::HandleJoinP2PSession(StringHash eventType, VariantMap& eventData)
{
    peers_.Clear();
    URHO3D_LOGINFO("HandleJoinP2PSession " + guid_->GetText());
    VariantMap identity;
    SetRandomSeed(Time::GetSystemTime());
    identity["Name"] = nickname_->GetText();
    GetSubsystem<Network>()->JoinSession(guid_->GetText(), scene_, identity);
//    GetSubsystem<Network>()->SetSimulatedLatency(Random(10.0f));
//    GetSubsystem<Network>()->SetSimulatedLatency(10 + Random(100));

    statusMessage_->SetText("Status: Joining " + guid_->GetText() + " P2P session");
}

void P2PMultiplayer::HandleSessionStarted(StringHash eventType, VariantMap& eventData)
{
    UnsubscribeFromEvent(E_P2PSESSIONSTARTED);
//    CreatePlayerNode(GetSubsystem<Network>()->GetServerConnection());

    statusMessage_->SetText("Status: P2P Session started");

    gameState_ = GameState::IN_LOBBY;
}

void P2PMultiplayer::HandleSessionJoined(StringHash eventType, VariantMap& eventData)
{
    statusMessage_->SetText("Status: joined P2P Session");

    gameState_ = GameState::IN_LOBBY;
}

void P2PMultiplayer::HandleUpdate(StringHash eventType, VariantMap& eventData)
{
    using namespace Update;
    auto input = GetSubsystem<Input>();
    float timestep = eventData[P_TIMESTEP].GetFloat();
    static float gametime;
    gametime += timestep * 10;

    if (input->GetKeyPress(KEY_R)) {
        GetSubsystem<Network>()->ResetHost();
    }
    if (input->GetKeyPress(KEY_E)) {
        GetSubsystem<Network>()->Disconnect(1000);
        peers_.Clear();

        GetSubsystem<Input>()->SetMouseVisible(true);
        GetSubsystem<Input>()->SetMouseGrabbed(false);
        GetSubsystem<Input>()->SetMouseMode(MouseMode::MM_FREE);

        statusMessage_->SetText("Status: Disconnected");
    }

    if (input->GetKeyPress(KEY_H)) {
        if (input->IsMouseVisible()) {
            input->SetMouseVisible(false);
            input->SetMouseGrabbed(true);
            input->SetMouseMode(MouseMode::MM_WRAP);
        } else {
            input->SetMouseVisible(true);
            input->SetMouseGrabbed(false);
            input->SetMouseMode(MouseMode::MM_FREE);
        }
    }

    if (input->GetKeyPress(KEY_T)) {
        GetSubsystem<Network>()->SetReady(!GetSubsystem<Network>()->GetReady());
    }
    if (GetSubsystem<Network>()->IsHostSystem() && input->GetKeyPress(KEY_N)) {
        if (_allReady) {
            startGame_ = true;
            startCountdown_.Reset();
        } else {
            statusMessage_->SetText("Status: Can't start game, not all players are ready!");
        }
    }

    if (startGame_) {
        int timeRemaining = 5 - (int)(startCountdown_.GetMSec(false) / 1000);
        statusMessage_->SetText("Status: Countdown till start " + String(timeRemaining));
    }
    if (startGame_ && startCountdown_.GetMSec(false) > 5000) {
        startGame_ = false;
        InitPlayers();
    }

    // Mouse sensitivity as degrees per pixel
    const float MOUSE_SENSITIVITY = 0.1f;

    // Use this frame's mouse motion to adjust camera node yaw and pitch. Clamp the pitch and only move the camera
    // when the cursor is hidden
    IntVector2 mouseMove = input->GetMouseMove();
    yaw_ += MOUSE_SENSITIVITY * mouseMove.x_;
    pitch_ += MOUSE_SENSITIVITY * mouseMove.y_;
    pitch_ = Clamp(pitch_, 1.0f, 90.0f);

    // Construct new orientation for the camera scene node from yaw and pitch. Roll is fixed to zero
    cameraNode_->SetRotation(Quaternion(pitch_, yaw_, 0.0f));

    if (GetSubsystem<Network>()->GetServerConnection()) {
        Controls controls;
        // Copy mouse yaw
        controls.yaw_ = yaw_;

        controls.Set(CTRL_FORWARD, input->GetKeyDown(KEY_W));
        controls.Set(CTRL_BACK, input->GetKeyDown(KEY_S));
        controls.Set(CTRL_LEFT, input->GetKeyDown(KEY_A));
        controls.Set(CTRL_RIGHT, input->GetKeyDown(KEY_D));
        GetSubsystem<Network>()->GetServerConnection()->SetControls(controls);
    }

    if (timer_.GetMSec(false) > 5000) {
        timer_.Reset();

        //TODO fix this
        if (GetSubsystem<Network>()->GetServerConnection()) {
            auto clients = GetSubsystem<Network>()->GetClientConnections();
            for (auto it = clients.Begin(); it != clients.End(); ++it) {
                VectorBuffer msg;
                msg.WriteVariantMap(GetSubsystem<Network>()->GetServerConnection()->GetIdentity());
                (*it)->SendMessage(MSG_IDENTITY, true, true, msg);
            }
        }

        UpdatePlayerList();
        if (GetSubsystem<Network>()->GetClientConnections().Size() != peers_.Size() - 1) {
            UpdateClientObjects();
        }

        clientCount_->SetText("Connections: " + String(GetSubsystem<Network>()->GetParticipantCount()));
        myGuid_->SetText("My GUID: " + GetSubsystem<Network>()->GetGUID());
        hostGuid_->SetText("Host GUID: " + GetSubsystem<Network>()->GetHostAddress());

        if (GetSubsystem<Network>()->GetGUID() == GetSubsystem<Network>()->GetHostAddress()) {
            hostGuid_->SetColor(Color::RED);
            myGuid_->SetColor(Color::RED);
        } else {
            myGuid_->SetColor(Color::GREEN);
            hostGuid_->SetColor(Color::GREEN);
        }

        if (httpRequest_.Null()) {
            httpRequest_ = GetSubsystem<Network>()->MakeHttpRequest("http://frameskippers.com:82/guid.txt");
            message_.Clear();
        }
        else
        {
            // Initializing HTTP request
            if (httpRequest_->GetState() == HTTP_INITIALIZING)
                return;
                // An error has occurred
            else if (httpRequest_->GetState() == HTTP_ERROR)
            {
            }
                // Get message data
            else
            {
                if (httpRequest_->GetAvailableSize() > 0) {
                    message_ += httpRequest_->ReadLine();
                }
                else
                {
                    guid_->SetText(message_);
                    httpRequest_.Reset();
                }
            }
        }
    }

    if (gameState_ == IN_GAME) {
        auto serverConnection = GetSubsystem<Network>()->GetServerConnection();
        if (serverConnection) {
            if (peers_[serverConnection] && peers_[serverConnection]->GetNode()) {
                const float CAMERA_DISTANCE = 4.0f;

                // Move camera some distance away from the ball
                cameraNode_->SetPosition(peers_[serverConnection]->GetNode()->GetPosition() + cameraNode_->GetRotation() * Vector3::BACK * CAMERA_DISTANCE);
            } else {
                UpdateClientObjects();
            }
        }
    }
}

void P2PMultiplayer::Init() {
    GetSubsystem<Network>()->SetMode(NetworkMode::PEER_TO_PEER);
    GetSubsystem<Network>()->SetNATServerInfo("frameskippers.com", 61111);
    GetSubsystem<Network>()->SetUpdateFps(30);

    httpRequest_ = GetSubsystem<Network>()->MakeHttpRequest("http://frameskippers.com:82/guid.txt");
}

//
Button* P2PMultiplayer::CreateButton(const String& text, int width, IntVector2 position)
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

LineEdit* P2PMultiplayer::CreateLineEdit(const String& placeholder, int width, IntVector2 pos)
{
    auto* textEdit = GetSubsystem<UI>()->GetRoot()->CreateChild<LineEdit>("");
    textEdit->SetStyleAuto();
    textEdit->SetFixedWidth(width);
    textEdit->SetFixedHeight(30);
    textEdit->SetText(placeholder);
    textEdit->SetPosition(pos);
    return textEdit;
}

//
Text* P2PMultiplayer::CreateLabel(const String& text, IntVector2 pos)
{
    auto* cache = GetSubsystem<ResourceCache>();
    // Create log element to view latest logs from the system
    auto* font = cache->GetResource<Font>("Fonts/Anonymous Pro.ttf");
    auto* label = GetSubsystem<UI>()->GetRoot()->CreateChild<Text>();
    label->SetFont(font, 12);
    label->SetColor(Color(0.0f, 1.0f, 0.0f));
    label->SetPosition(pos);
    label->SetText(text);
    label->SetTextEffect(TextEffect::TE_STROKE);
	return label;
}

void P2PMultiplayer::CreateScene()
{
//    return;
    scene_ = new Scene(context_);

    auto* cache = GetSubsystem<ResourceCache>();

    // Create octree and physics world with default settings. Create them as local so that they are not needlessly replicated
    // when a client connects
    scene_->CreateComponent<Octree>(LOCAL);
    scene_->CreateComponent<PhysicsWorld>(LOCAL);

    // All static scene content and the camera are also created as local, so that they are unaffected by scene replication and are
    // not removed from the client upon connection. Create a Zone component first for ambient lighting & fog control.
    Node* zoneNode = scene_->CreateChild("Zone", LOCAL);
    auto* zone = zoneNode->CreateComponent<Zone>();
    zone->SetBoundingBox(BoundingBox(-1000.0f, 1000.0f));
    zone->SetAmbientColor(Color(0.1f, 0.1f, 0.1f));
    zone->SetFogStart(100.0f);
    zone->SetFogEnd(300.0f);

    // Create a directional light without shadows
    Node* lightNode = scene_->CreateChild("DirectionalLight", LOCAL);
    lightNode->SetDirection(Vector3(0.5f, -1.0f, 0.5f));
    auto* light = lightNode->CreateComponent<Light>();
    light->SetLightType(LIGHT_DIRECTIONAL);
    light->SetColor(Color(0.2f, 0.2f, 0.2f));
    light->SetSpecularIntensity(1.0f);

    // Create a "floor" consisting of several tiles. Make the tiles physical but leave small cracks between them
    for (int y = -20; y <= 20; ++y)
    {
        for (int x = -20; x <= 20; ++x)
        {
            Node* floorNode = scene_->CreateChild("FloorTile", LOCAL);
            floorNode->SetPosition(Vector3(x * 20.2f, -0.5f, y * 20.2f));
            floorNode->SetScale(Vector3(20.0f, 1.0f, 20.0f));
            auto* floorObject = floorNode->CreateComponent<StaticModel>();
            floorObject->SetModel(cache->GetResource<Model>("Models/Box.mdl"));
            floorObject->SetMaterial(cache->GetResource<Material>("Materials/Stone.xml"));

            auto* body = floorNode->CreateComponent<RigidBody>();
            body->SetFriction(1.0f);
            body->SetRestitution(0.5);
            auto* shape = floorNode->CreateComponent<CollisionShape>();
            shape->SetBox(Vector3::ONE);
        }
    }

    // Create the camera. Limit far clip distance to match the fog
    // The camera needs to be created into a local node so that each client can retain its own camera, that is unaffected by
    // network messages. Furthermore, because the client removes all replicated scene nodes when connecting to a server scene,
    // the screen would become blank if the camera node was replicated (as only the locally created camera is assigned to a
    // viewport in SetupViewports() below)
    cameraNode_ = scene_->CreateChild("Camera", LOCAL);
    auto* camera = cameraNode_->CreateComponent<Camera>();
    camera->SetFarClip(300.0f);

    // Set an initial position for the camera scene node above the plane
    cameraNode_->SetPosition(Vector3(-10.0f, 10.0f, 10.0f));
    cameraNode_->LookAt(Vector3(0, 0, 0));
}

void P2PMultiplayer::SetupViewport()
{
//    return;
    auto* renderer = GetSubsystem<Renderer>();

    // Set up a viewport to the Renderer subsystem so that the 3D scene can be seen
    SharedPtr<Viewport> viewport(new Viewport(context_, scene_, cameraNode_->GetComponent<Camera>()));
    renderer->SetViewport(0, viewport);
}

void P2PMultiplayer::HandleClientConnected(StringHash eventType, VariantMap& eventData)
{
    using namespace ClientConnected;

    // When a client connects, assign to scene to begin scene replication
    auto* newConnection = static_cast<Connection*>(eventData[P_CONNECTION].GetPtr());
    newConnection->SetScene(scene_);

    //CreatePlayerNode(newConnection);

    //UpdateClientObjects();

    statusMessage_->SetText("Status: Client connected");
}

void P2PMultiplayer::HandleClientDisconnected(StringHash eventType, VariantMap& eventData)
{
    using namespace ClientConnected;

//    // When a client disconnects, remove the controlled object
    auto* connection = static_cast<Connection*>(eventData[P_CONNECTION].GetPtr());
    DestroyPlayerNode(connection);

    UpdateClientObjects();

    statusMessage_->SetText("Status: Client discconnected");
}

void P2PMultiplayer::UpdateClientObjects()
{
    PODVector<Node*> playerNodes;
    scene_->GetNodesWithTag(playerNodes, "Player");
    auto clients = GetSubsystem<Network>()->GetClientConnections();
    for (auto it = clients.Begin(); it != clients.End(); ++it) {
        for (auto it2 = playerNodes.Begin(); it2 != playerNodes.End(); ++it2) {
            if ((*it2)->GetVar("GUID").GetString() == (*it)->GetGUID()) {
                if (!peers_[(*it)]) {
                    peers_[(*it)] = new Peer(context_);
                    peers_[(*it)]->SetConnection((*it));
                    peers_[(*it)]->SetScene(scene_);
                }
                peers_[(*it)]->SetNode((*it2));
            }
        }
    }
    for (auto it2 = playerNodes.Begin(); it2 != playerNodes.End(); ++it2) {
        if ((*it2)->GetVar("GUID").GetString() == GetSubsystem<Network>()->GetGUID()) {
            if (!peers_[GetSubsystem<Network>()->GetServerConnection()]) {
                peers_[GetSubsystem<Network>()->GetServerConnection()] = new Peer(context_);
                peers_[GetSubsystem<Network>()->GetServerConnection()]->SetConnection(GetSubsystem<Network>()->GetServerConnection());
                peers_[GetSubsystem<Network>()->GetServerConnection()]->SetScene(scene_);
            }
            peers_[GetSubsystem<Network>()->GetServerConnection()]->SetNode(*it2);
        }
    }
}

void P2PMultiplayer::HandleAllReadyChanged(StringHash eventType, VariantMap& eventData)
{
    using namespace P2PAllReadyChanged;
    _allReady = eventData[P_READY].GetBool();

    if (_allReady) {
        statusMessage_->SetText("Status: All players are ready");
    } else {
        if (startGame_) {
            startGame_ = false;
            statusMessage_->SetText("Status: Countdown stopped! Not all players are ready!");
        }
    }
}

void P2PMultiplayer::CreatePlayerNode(Connection* connection)
{
    if (peers_[connection]) {
        return;
    }

    peers_[connection] = new Peer(context_);
    peers_[connection]->SetScene(scene_);
    peers_[connection]->Create(connection);
}

void P2PMultiplayer::DestroyPlayerNode(Connection* connection)
{
    if (peers_[connection]) {
        peers_[connection]->DestroyNode();
        peers_.Erase(connection);
    }
}

void P2PMultiplayer::HandleNewHost(StringHash eventType, VariantMap& eventData)
{
    using namespace P2PNewHost;
    URHO3D_LOGINFOF("Host changed %s, %i => %s", eventData[P_ADDRESS].GetString().CString(), eventData[P_PORT].GetInt(), eventData[P_GUID].GetString().CString());
    SetRandomSeed(Time::GetSystemTime());

    statusMessage_->SetText("Status: New host elected: " + eventData[P_GUID].GetString());
//    if (!GetSubsystem<Network>()->IsHostSystem()) {
//        // Non-hosts should clear the previous state
//        peers_.Clear();
//    }
}

void P2PMultiplayer::HandleBanned(StringHash eventType, VariantMap& eventData)
{
    GetSubsystem<Network>()->Disconnect(1000);
    peers_.Clear();

    GetSubsystem<Input>()->SetMouseVisible(true);
    GetSubsystem<Input>()->SetMouseGrabbed(false);
//    GetSubsystem<Input>()->SetMouseMode(MouseMode::MM_FREE);

    using namespace NetworkBanned;
    URHO3D_LOGWARNING("We have been banned, reason: " + eventData[P_REASON].GetString());

    statusMessage_->SetText("Status: You are banned");
}

void P2PMultiplayer::HandleClientIdentity(StringHash eventType, VariantMap& eventData)
{
    using namespace ClientIdentity;
    Connection* connection = static_cast<Connection*>(eventData[P_CONNECTION].GetPtr());
    URHO3D_LOGINFO("Client identity: Client " + connection->GetGUID() + " => " + connection->GetIdentity()["Name"].GetString());
    //statusMessage_->SetText("Status: Client " + connection->GetGUID() + " => " + connection->GetIdentity()["Name"].GetString());
}

void P2PMultiplayer::InitPlayers()
{
    if (!_allReady) {
        statusMessage_->SetText("Status: Can't start, not all players are ready!");
        return;
    }
    auto clients = GetSubsystem<Network>()->GetClientConnections();
    for (auto it = clients.Begin(); it != clients.End(); ++it) {
        CreatePlayerNode((*it));
    }

    CreatePlayerNode(GetSubsystem<Network>()->GetServerConnection());

    statusMessage_->SetText("Status: Initializing all players");

    gameState_ = IN_GAME;
    VariantMap data = GetEventDataMap();
    data["GameState"] = gameState_;
    GetSubsystem<Network>()->BroadcastRemoteEvent("GameStart", false, data);
}

void P2PMultiplayer::HandleGameState(StringHash eventType, VariantMap& eventData)
{
    if (eventType == "GameStart") {
        gameState_ = (GameState) eventData["GameState"].GetUInt();
        statusMessage_->SetText("Status: Game started!");
    }
}

void P2PMultiplayer::UpdatePlayerList()
{
    if (!GetSubsystem<Network>()->GetServerConnection()) {
        return;
    }
    for (auto it = playerList_.Begin(); it != playerList_.End(); ++it) {
        if ((*it)) {
            (*it)->Remove();
        }
    }
    playerList_.Clear();

    int margin = -10;
    SharedPtr<Text> me(CreateLabel("", IntVector2(-10, margin)));
    me->SetAlignment(HA_RIGHT, VA_BOTTOM);
    String ready = "READY";
    if (!GetSubsystem<Network>()->GetServerConnection()->GetReady()) {
        ready = "NOT READY";
        me->SetColor(Color::YELLOW);
    } else {
        me->SetColor(Color::GREEN);
    }
    me->SetText(GetSubsystem<Network>()->GetServerConnection()->GetIdentity()["Name"].GetString() + " [" + ready + "]");

    playerList_.Push(me);

    auto clients = GetSubsystem<Network>()->GetClientConnections();
    for (auto it = clients.Begin(); it != clients.End(); ++it) {
        margin -= 20;
        ready = "READY";
        SharedPtr<Text> peer(CreateLabel("", IntVector2(-10, margin)));
        if (!(*it)->GetReady()) {
            ready = "NOT READY";
            peer->SetColor(Color::YELLOW);
        } else {
            peer->SetColor(Color::GREEN);
        }
        peer->SetAlignment(HA_RIGHT, VA_BOTTOM);
        peer->SetText((*it)->GetIdentity()["Name"].GetString() + " [" + ready + "]");
        playerList_.Push(peer);
    }
}