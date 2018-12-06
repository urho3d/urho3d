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
#include <Urho3D/UI/MessageBox.h>
#include <Urho3D/UI/UIEvents.h>
#include <Urho3D/Core/CoreEvents.h>

#include "P2PMultiplayerExtended.h"

#include <Urho3D/DebugNew.h>

// Undefine Windows macro, as our Connection class has a function called SendMessage
#ifdef SendMessage
#undef SendMessage
#endif

#ifdef MessageBox
#undef MessageBox
#endif

URHO3D_DEFINE_APPLICATION_MAIN(P2PMultiplayer)

static String API_SEARCH_SESSION = "http://master.frameskippers.com/open";
static String API_NEW_SESSION = "http://master.frameskippers.com/new";
static String API_REMOVE_SESSION = "http://master.frameskippers.com/delete";

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

    CreatePlayerListWindow();
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

    int marginTop = 20;
    searchGame_ = CreateButton("Search for session", 200, IntVector2(20, marginTop));
    nickname_ = CreateLineEdit("User", 160, IntVector2(240, marginTop));
    SetRandomSeed(Time::GetSystemTime());
    nickname_->SetText(nickname_->GetText() + "_" + String(Random(1, 1000)));

	marginTop += 80;
    clientCount_ = CreateLabel("Connections: 0", IntVector2(20, marginTop));

    statusMessage_ = CreateLabel("", IntVector2(20, -20));
    SetStatusMessage("Started");
    statusMessage_->SetAlignment(HA_LEFT, VA_BOTTOM);

    String information = "R - Reset host";
    information += "\nE - Disconnect";
    information += "\nTAB - Show player list";
    information += "\nWASD - move around";
    information += "\nH - Toggle mouse visible/hidden";
    information += "\nSpace - Jump";

    info_ = CreateLabel(information, IntVector2(0, 50));
    info_->SetHorizontalAlignment(HA_RIGHT);

//     No viewports or scene is defined. However, the default zone's fog color controls the fill color
    GetSubsystem<Renderer>()->GetDefaultZone()->SetFogColor(Color(0.0f, 0.0f, 0.1f));
}

void P2PMultiplayer::SubscribeToEvents()
{
    SubscribeToEvent(E_UPDATE, URHO3D_HANDLER(P2PMultiplayer, HandleUpdate));
    SubscribeToEvent(searchGame_, "Released", URHO3D_HANDLER(P2PMultiplayer, HandleSearchSession));

    SubscribeToEvent(E_CLIENTCONNECTED, URHO3D_HANDLER(P2PMultiplayer, HandleClientConnected));
    SubscribeToEvent(E_CLIENTDISCONNECTED, URHO3D_HANDLER(P2PMultiplayer, HandleClientDisconnected));
    SubscribeToEvent(E_P2PALLREADYCHANGED, URHO3D_HANDLER(P2PMultiplayer, HandleAllReadyChanged));
    SubscribeToEvent(E_P2PNEWHOST, URHO3D_HANDLER(P2PMultiplayer, HandleNewHost));
    SubscribeToEvent(E_NETWORKBANNED, URHO3D_HANDLER(P2PMultiplayer, HandleBanned));
    SubscribeToEvent(E_CLIENTIDENTITY, URHO3D_HANDLER(P2PMultiplayer, HandleClientIdentity));
    SubscribeToEvent(E_SERVERFULL, URHO3D_HANDLER(P2PMultiplayer, HandleServerFull));

    GetSubsystem<Network>()->RegisterRemoteEvent("GameStart");
    SubscribeToEvent("GameStart", URHO3D_HANDLER(P2PMultiplayer, HandleGameState));
}

void P2PMultiplayer::HandleSearchSession(StringHash eventType, VariantMap& eventData)
{
    if (GetSubsystem<Network>()->IsServerRunning() || GetSubsystem<Network>()->IsConnectedHost()) {
        URHO3D_LOGERROR("Already connected to session!");
        return;
    }
    httpRequest_ = GetSubsystem<Network>()->MakeHttpRequest(API_SEARCH_SESSION);
}

void P2PMultiplayer::StartSession()
{
    peers_.Clear();
    VariantMap identity;
    identity["Name"] = nickname_->GetText();
    GetSubsystem<Network>()->StartSession(scene_, identity);
    SetStatusMessage("Starting P2P session");
    httpRequest_ = GetSubsystem<Network>()->MakeHttpRequest(API_NEW_SESSION + "?guid=" + GetSubsystem<Network>()->GetGUID() + "&state=" + String((int)gameState_) + "&peers=1");

    SubscribeToEvent(E_P2PSESSIONSTARTED, URHO3D_HANDLER(P2PMultiplayer, HandleSessionStarted));
    SubscribeToEvent(E_P2PSESSIONJOINED, URHO3D_HANDLER(P2PMultiplayer, HandleSessionJoined));
}

void P2PMultiplayer::JoinSession(const String& guid)
{
    peers_.Clear();
    VariantMap identity;
    SetRandomSeed(Time::GetSystemTime());
    identity["Name"] = nickname_->GetText();
    GetSubsystem<Network>()->JoinSession(guid, scene_, identity);

    SetStatusMessage("Joining " + guid + " P2P session");
}

void P2PMultiplayer::HandleSessionStarted(StringHash eventType, VariantMap& eventData)
{
    UnsubscribeFromEvent(E_P2PSESSIONSTARTED);
    SetStatusMessage("P2P Session started");
    gameState_ = GameState::IN_LOBBY;
}

void P2PMultiplayer::HandleSessionJoined(StringHash eventType, VariantMap& eventData)
{
    SetStatusMessage("Joined P2P Session");
    gameState_ = GameState::IN_LOBBY;
}

void P2PMultiplayer::SetStatusMessage(const String& message)
{
    String allMessages;
    for (auto it = messages_.Begin(); it != messages_.End(); ++it) {
        allMessages += (*it) + "\n";
    }
    statusMessage_->SetText("Status: " + allMessages);
    messages_.Push(message);
    if (messages_.Size() > 15) {
        messages_.PopFront();
    }
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
    if (input->GetKeyPress(KEY_TAB)) {
        playerList_->SetVisible(!playerList_->IsVisible());
    }
    if (input->GetKeyPress(KEY_E)) {
        GetSubsystem<Network>()->Disconnect(1000);
        httpRequest_ = GetSubsystem<Network>()->MakeHttpRequest(API_REMOVE_SESSION + "?guid=" + GetSubsystem<Network>()->GetGUID());
        peers_.Clear();

        GetSubsystem<Input>()->SetMouseVisible(true);
        GetSubsystem<Input>()->SetMouseGrabbed(false);
        GetSubsystem<Input>()->SetMouseMode(MouseMode::MM_FREE);

        SetStatusMessage("Disconnected");

        UpdatePlayerList();

        gameState_ = IN_MENU;
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

    if (gameState_ == IN_GAME) {
        // Construct new orientation for the camera scene node from yaw and pitch. Roll is fixed to zero
        cameraNode_->SetRotation(Quaternion(pitch_, yaw_, 0.0f));
    }

    if (GetSubsystem<Network>()->GetServerConnection()) {
        Controls controls;
        // Copy mouse yaw
        controls.yaw_ = yaw_;

        controls.Set(CTRL_FORWARD, input->GetKeyDown(KEY_W));
        controls.Set(CTRL_BACK, input->GetKeyDown(KEY_S));
        controls.Set(CTRL_LEFT, input->GetKeyDown(KEY_A));
        controls.Set(CTRL_RIGHT, input->GetKeyDown(KEY_D));
        controls.Set(CTRL_JUMP, input->GetKeyDown(KEY_SPACE));
        GetSubsystem<Network>()->GetServerConnection()->SetControls(controls);
    }

    if (timer_.GetMSec(false) > 1000) {
        timer_.Reset();

        if (startGame_) {
            int timeRemaining = 5 - (int)(startCountdown_.GetMSec(false) / 1000);
            SetStatusMessage("Countdown till start " + String(timeRemaining));
        }

        if (GetSubsystem<Network>()->GetClientConnections().Size() != peers_.Size() - 1) {
            UpdateClientObjects();
        }

        clientCount_->SetText("Connections: " + String(GetSubsystem<Network>()->GetParticipantCount()));

        if (GetSubsystem<Network>()->IsHostSystem() && GetSubsystem<Network>()->IsServerRunning()) {
            httpRequest_ = GetSubsystem<Network>()->MakeHttpRequest(
                    API_NEW_SESSION + "?guid=" + GetSubsystem<Network>()->GetGUID() + "&state=" +
                    String((int) gameState_) + "&peers=" + String(GetSubsystem<Network>()->GetClientConnections().Size() + 1));
        }
    }

    if (!httpRequest_.Null()) {
        // Initializing HTTP request
        if (httpRequest_->GetState() == HTTP_INITIALIZING) {

        }
        else if (httpRequest_->GetState() == HTTP_ERROR) {
            URHO3D_LOGERROR("Master server returned error!");
            SetStatusMessage("Master server returned error!");
        }
        else
        {
            if (httpRequest_->GetAvailableSize() > 0) {
                message_ = httpRequest_->ReadString();
            }
            else
            {
                String url = httpRequest_->GetURL();
                httpRequest_.Reset();
                if (url == API_SEARCH_SESSION) {
                    URHO3D_LOGINFO("Search finished! " + message_);
                    SharedPtr<JSONFile> json(new JSONFile(context_));
                    json->FromString(message_);

                    message_.Clear();

                    JSONValue val = json->GetRoot().Get("guid");

                    if (val.IsNull()) {
                        URHO3D_LOGWARNING("No active sessions, starting new one");
                        new Urho3D::MessageBox(context_, "Creating new P2P session", "No active sessions");
                        StartSession();
                    }
                    else {
                        URHO3D_LOGWARNING("Found incomplete session, joining it");
                        new Urho3D::MessageBox(context_, "Joining other p2p session: " + val.GetString(), "Incomplete session found");
                        JoinSession(val.GetString());
                    }
                } else if (url.Contains(API_NEW_SESSION)) {
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
    GetSubsystem<Network>()->SetNATServerInfo("nat.frameskippers.com", 30123);
    GetSubsystem<Network>()->SetUpdateFps(30);

    //httpRequest_ = GetSubsystem<Network>()->MakeHttpRequest("http://frameskippers.com:82/guid.txt");
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

    SetStatusMessage("Client connected");

    UpdatePlayerList();
}

void P2PMultiplayer::HandleClientDisconnected(StringHash eventType, VariantMap& eventData)
{
    using namespace ClientConnected;

//    // When a client disconnects, remove the controlled object
    auto* connection = static_cast<Connection*>(eventData[P_CONNECTION].GetPtr());
    DestroyPlayerNode(connection);

    UpdateClientObjects();

    SetStatusMessage("Client discconnected");

    UpdatePlayerList();
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
        startGame_ = true;
        startCountdown_.Reset();
    } else {
        if (startGame_) {
            startGame_ = false;
            SetStatusMessage("Countdown stopped! Not all players are ready!");
        }
    }

    UpdatePlayerList();
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

    String guid = eventData[P_GUID].GetString();
    SetStatusMessage("New host elected: " + eventData[P_GUID].GetString());

    if (guid != GetSubsystem<Network>()->GetGUID()) {
        httpRequest_ = GetSubsystem<Network>()->MakeHttpRequest(API_REMOVE_SESSION + "?guid=" + GetSubsystem<Network>()->GetGUID());
    }

    UpdatePlayerList();
}

void P2PMultiplayer::HandleBanned(StringHash eventType, VariantMap& eventData)
{
    GetSubsystem<Network>()->Disconnect(1000);
    httpRequest_ = GetSubsystem<Network>()->MakeHttpRequest(API_REMOVE_SESSION + "?guid=" + GetSubsystem<Network>()->GetGUID());
    peers_.Clear();

    GetSubsystem<Input>()->SetMouseVisible(true);
    GetSubsystem<Input>()->SetMouseGrabbed(false);

    gameState_ = IN_MENU;

//    GetSubsystem<Input>()->SetMouseMode(MouseMode::MM_FREE);

    using namespace NetworkBanned;
    URHO3D_LOGWARNING("We have been banned, reason: " + eventData[P_REASON].GetString());

    SetStatusMessage("You are banned");
}

void P2PMultiplayer::HandleClientIdentity(StringHash eventType, VariantMap& eventData)
{
    using namespace ClientIdentity;
    auto connection = static_cast<Connection*>(eventData[P_CONNECTION].GetPtr());
//    URHO3D_LOGINFO("Client identity: Client " + connection->GetGUID() + " => " + connection->GetIdentity()["Name"].GetString());
    UpdatePlayerList();
}

void P2PMultiplayer::InitPlayers()
{
    if (!GetSubsystem<Network>()->IsHostSystem()) {
        return;
    }
    if (!_allReady) {
        SetStatusMessage("Can't start, not all players are ready!");
        return;
    }
    auto clients = GetSubsystem<Network>()->GetClientConnections();
    for (auto it = clients.Begin(); it != clients.End(); ++it) {
        CreatePlayerNode((*it));
    }

    if (GetSubsystem<Network>()->GetServerConnection()) {
        CreatePlayerNode(GetSubsystem<Network>()->GetServerConnection());
    }

    SetStatusMessage("Initializing all players");

    gameState_ = IN_GAME;
    VariantMap data = GetEventDataMap();
    data["GameState"] = gameState_;
    GetSubsystem<Network>()->BroadcastRemoteEvent("GameStart", false, data);
    playerList_->SetVisible(false);
}

void P2PMultiplayer::HandleGameState(StringHash eventType, VariantMap& eventData)
{
    if (eventType == "GameStart") {
        gameState_ = (GameState) eventData["GameState"].GetUInt();
        SetStatusMessage("Game started!");
        playerList_->SetVisible(false);
    }
}

void P2PMultiplayer::UpdatePlayerList()
{
    auto* cache = GetSubsystem<ResourceCache>();
    auto* font = cache->GetResource<Font>("Fonts/Anonymous Pro.ttf");
    auto* label = GetSubsystem<UI>()->GetRoot()->CreateChild<Text>();

    playerList_->RemoveAllChildren();

    auto playerName = playerList_->CreateChild<Text>();
    playerName->SetPosition(IntVector2(10, 10));
    playerName->SetAlignment(HA_LEFT, VA_TOP);
    playerName->SetText("Nickname");
    playerName->SetFont(font, 12);
    playerName->SetFontSize(16);
    playerName->SetTextEffect(TextEffect::TE_SHADOW);
    playerName->SetColor(Color::GRAY);

    auto playerGuid = playerList_->CreateChild<Text>();
    playerGuid->SetPosition(IntVector2(0, 10));
    playerGuid->SetAlignment(HA_CENTER, VA_TOP);
    playerGuid->SetText("Ping");
    playerGuid->SetFont(font, 12);
    playerGuid->SetFontSize(16);
    playerGuid->SetTextEffect(TextEffect::TE_SHADOW);
    playerGuid->SetColor(Color::GRAY);

    auto playerStatus = playerList_->CreateChild<Text>();
    playerStatus->SetPosition(IntVector2(-10, 10));
    playerStatus->SetAlignment(HA_RIGHT, VA_TOP);
    playerStatus->SetText("Ready status");
    playerStatus->SetFont(font, 12);
    playerStatus->SetFontSize(16);
    playerStatus->SetTextEffect(TextEffect::TE_SHADOW);
    playerStatus->SetColor(Color::GRAY);

    int marginTop = 40;

    auto connections = GetSubsystem<Network>()->GetClientConnections();
    connections.Push(SharedPtr<Connection>(GetSubsystem<Network>()->GetServerConnection()));
    for (auto it = connections.Begin(); it != connections.End(); ++it) {
        if ((*it)) {
            auto playerName = playerList_->CreateChild<Text>();
            playerName->SetPosition(IntVector2(20, marginTop));
            playerName->SetAlignment(HA_LEFT, VA_TOP);
            playerName->SetText((*it)->GetIdentity()["Name"].GetString());
            playerName->SetFont(font, 12);
            playerName->SetTextEffect(TextEffect::TE_SHADOW);

            if ((*it)->GetGUID() == GetSubsystem<Network>()->GetHostAddress()) {
                playerName->SetText(playerName->GetText() + " [HOST]");
            }

            auto playerGuid = playerList_->CreateChild<Text>();
            playerGuid->SetPosition(IntVector2(0, marginTop));
            playerGuid->SetAlignment(HA_CENTER, VA_TOP);
            playerGuid->SetText(String((*it)->GetLastPing()));
            playerGuid->SetFont(font, 12);
            playerGuid->SetTextEffect(TextEffect::TE_SHADOW);

            if ((*it) == GetSubsystem<Network>()->GetServerConnection()) {
                playerName->SetColor(Color::GREEN);

                auto readyState = playerList_->CreateChild<Button>();
                readyState->SetPosition(IntVector2(-20, marginTop - 5));
                readyState->SetAlignment(HA_RIGHT, VA_TOP);
                readyState->SetStyleAuto();
                readyState->SetWidth(100);
                readyState->SetHeight(30);

                SubscribeToEvent(readyState, "Released", [&](StringHash eventType, VariantMap& eventData) {
                    GetSubsystem<Network>()->SetReady(!GetSubsystem<Network>()->GetReady());
                });

                auto playerStatus = readyState->CreateChild<Text>();
                playerStatus->SetAlignment(HA_CENTER, VA_CENTER);
                playerStatus->SetText((*it)->GetReady() ? "Ready" : "Not ready");
                playerStatus->SetColor((*it)->GetReady() ? Color::GREEN : Color::RED);
                playerStatus->SetFont(font, 12);
                playerStatus->SetTextEffect(TextEffect::TE_SHADOW);

            }
            else {
                auto playerStatus = playerList_->CreateChild<Text>();
                playerStatus->SetPosition(IntVector2(-20, marginTop));
                playerStatus->SetAlignment(HA_RIGHT, VA_TOP);
                playerStatus->SetText((*it)->GetReady() ? "Ready" : "Not ready");
                playerStatus->SetColor((*it)->GetReady() ? Color::GREEN : Color::RED);
                playerStatus->SetFont(font, 12);
                playerStatus->SetTextEffect(TextEffect::TE_SHADOW);
            }
            marginTop += 25;
        }
    }
}

void P2PMultiplayer::CreatePlayerListWindow()
{
    playerList_ = GetSubsystem<UI>()->GetRoot()->CreateChild<Window>();
    playerList_->SetStyleAuto();
    playerList_->SetAlignment(HA_CENTER, VA_CENTER);
    playerList_->SetSize(IntVector2(GetSubsystem<Graphics>()->GetWidth() - 200, GetSubsystem<Graphics>()->GetHeight() - 400));
    playerList_->BringToFront();
}

void P2PMultiplayer::HandleServerFull(StringHash eventType, VariantMap& eventData)
{
    UpdatePlayerList();
}