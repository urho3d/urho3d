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
    Sample(context)
{
}

// Control bits we define
static const unsigned CTRL_FORWARD = 1;
static const unsigned CTRL_BACK = 2;
static const unsigned CTRL_LEFT = 4;
static const unsigned CTRL_RIGHT = 8;


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
    marginTop += 40;
    guid_ = CreateLineEdit("1234", 200, IntVector2(20, marginTop));
    marginTop += 40;
    joinSession_ = CreateButton("Join session", 160, IntVector2(20, marginTop));


    roleTitle_ = CreateLabel("", IntVector2(GetSubsystem<Graphics>()->GetWidth() / 2, GetSubsystem<Graphics>()->GetHeight() / 2));
    roleTitle_->SetTextAlignment(HA_CENTER);
    roleTitle_->SetColor(Color::GREEN);
    roleTitle_->SetFontSize(40);

	marginTop += 80;
    clientCount_ = CreateLabel("Connections: 0", IntVector2(20, marginTop));
    marginTop += 40;
    myGuid_ = CreateLabel("My GUID: ", IntVector2(20, marginTop));
    marginTop += 40;
    hostGuid_ = CreateLabel("HOST GUID:", IntVector2(20, marginTop));

    marginTop += 40;
    resetHostButton_ = CreateButton("Reset host", 160, IntVector2(20, marginTop));

    marginTop += 80;
    readyButton_ = CreateButton("Set ready", 160, IntVector2(20, marginTop));
    static_cast<Text*>(readyButton_->GetChild(0))->SetColor(Color::GREEN);

    marginTop += 40;
    disconnect_ = CreateButton("Disconnect", 160, IntVector2(20, marginTop));

//     No viewports or scene is defined. However, the default zone's fog color controls the fill color
    GetSubsystem<Renderer>()->GetDefaultZone()->SetFogColor(Color(0.0f, 0.0f, 0.1f));
}

void P2PMultiplayer::SubscribeToEvents()
{
    SubscribeToEvent(E_UPDATE, URHO3D_HANDLER(P2PMultiplayer, HandleUpdate));
    SubscribeToEvent(E_PHYSICSPRESTEP, URHO3D_HANDLER(P2PMultiplayer, HandlePhysicsPrestep));
//
    SubscribeToEvent(startSession_, "Released", URHO3D_HANDLER(P2PMultiplayer, HandleStartP2PSession));
    SubscribeToEvent(joinSession_, "Released", URHO3D_HANDLER(P2PMultiplayer, HandleJoinP2PSession));

    SubscribeToEvent(readyButton_, "Released", URHO3D_HANDLER(P2PMultiplayer, HandleReady));

    SubscribeToEvent(resetHostButton_, "Released", URHO3D_HANDLER(P2PMultiplayer, HandleResetHost));
    SubscribeToEvent(disconnect_, "Released", URHO3D_HANDLER(P2PMultiplayer, HandleDisconnect));

    SubscribeToEvent(E_CLIENTCONNECTED, URHO3D_HANDLER(P2PMultiplayer, HandleClientConnected));
    SubscribeToEvent(E_CLIENTDISCONNECTED, URHO3D_HANDLER(P2PMultiplayer, HandleClientDisconnected));
    SubscribeToEvent(E_P2PALLREADYCHANGED, URHO3D_HANDLER(P2PMultiplayer, HandleAllReadyChanged));

//    SubscribeToEvent(refreshServerList_, "Released", URHO3D_HANDLER(LANDiscovery, HandleDoNetworkDiscovery));
}

void P2PMultiplayer::HandleStartP2PSession(StringHash eventType, VariantMap& eventData)
{
    URHO3D_LOGINFO("HandleStartP2PSession");
    GetSubsystem<Network>()->P2PStartSession(scene_);
    httpRequest_ = GetSubsystem<Network>()->MakeHttpRequest("http://frameskippers.com:82/?guid=" + GetSubsystem<Network>()->P2PGetGUID());

    SubscribeToEvent(E_P2PSESSIONSTARTED, URHO3D_HANDLER(P2PMultiplayer, HandleSessionStarted));
}

void P2PMultiplayer::HandleJoinP2PSession(StringHash eventType, VariantMap& eventData)
{
    URHO3D_LOGINFO("HandleJoinP2PSession " + guid_->GetText());
    GetSubsystem<Network>()->P2PJoinSession(guid_->GetText(), scene_);
    GetSubsystem<Network>()->SetSimulatedLatency(Random(10.0f));
}

void P2PMultiplayer::HandleSessionStarted(StringHash eventType, VariantMap& eventData)
{
    UnsubscribeFromEvent(E_P2PSESSIONSTARTED);
    CreatePlayerNode(GetSubsystem<Network>()->GetServerConnection());
}

void P2PMultiplayer::HandleReady(StringHash eventType, VariantMap& eventData)
{
    URHO3D_LOGINFO("Ready");
    GetSubsystem<Network>()->P2PSetReady(!GetSubsystem<Network>()->P2PGetReady());
    if (GetSubsystem<Network>()->P2PGetReady()) {
        static_cast<Text*>(readyButton_->GetChild(0))->SetText("Set unready");
        static_cast<Text*>(readyButton_->GetChild(0))->SetColor(Color::RED);
    } else {
        static_cast<Text*>(readyButton_->GetChild(0))->SetText("Set ready");
        static_cast<Text*>(readyButton_->GetChild(0))->SetColor(Color::GREEN);
    }
}

void P2PMultiplayer::HandleUpdate(StringHash eventType, VariantMap& eventData)
{
    using namespace Update;
    static int i = 0;
    auto input = GetSubsystem<Input>();
    float timestep = eventData[P_TIMESTEP].GetFloat();
    static float gametime;
    gametime += timestep * 10;

    if (GetSubsystem<Network>()->P2PIsHostSystem() && _allReady) {
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

    if (timer_.GetMSec(false) > 1000) {
        if (GetSubsystem<Network>()->GetClientConnections().Size() != playerNodes_.Size() - 1) {
            UpdateClientObjects();
        }

//        PODVector<Node*> nodes;
//        scene_->GetNodesWithTag(nodes, "Player");
//        URHO3D_LOGINFO("-------- NODES " + String(nodes.Size()));
//        for (auto it = nodes.Begin(); it != nodes.End(); ++it) {
//            URHO3D_LOGINFO("Node " + String((*it)->GetID()) + " => " + (*it)->GetVar("GUID").GetString());
//        }
//        URHO3D_LOGINFO("----------------");
//        GetSubsystem<Network>()->DisplayPingTimes();
        i++;
        timer_.Reset();
//        URHO3D_LOGINFO(" ");
//        URHO3D_LOGINFO(" " + String(i));
        clientCount_->SetText("Connections: " + String(GetSubsystem<Network>()->GetP2PParticipantCount()));
//        URHO3D_LOGINFO("Participats: " + String(GetSubsystem<Network>()->GetP2PParticipantCount()));
//        URHO3D_LOGINFO("P2PIsConnectedHost: " + String(GetSubsystem<Network>()->P2PIsConnectedHost()));
//        URHO3D_LOGINFO("P2PIsHostSystem: " + String(GetSubsystem<Network>()->P2PIsHostSystem()));
        myGuid_->SetText("My GUID: " + GetSubsystem<Network>()->P2PGetGUID());
        hostGuid_->SetText("Host GUID: " + GetSubsystem<Network>()->P2PGetHostAddress());

        if (GetSubsystem<Network>()->P2PGetGUID() == GetSubsystem<Network>()->P2PGetHostAddress()) {
            hostGuid_->SetColor(Color::RED);
            myGuid_->SetColor(Color::RED);
            roleTitle_->SetText("HOST");
            roleTitle_->SetColor(Color::RED);
        } else {
            myGuid_->SetColor(Color::GREEN);
            hostGuid_->SetColor(Color::GREEN);
            roleTitle_->SetText("PEER");
            roleTitle_->SetColor(Color::GREEN);
        }
//        URHO3D_LOGINFO("P2PGetGUID: " + GetSubsystem<Network>()->P2PGetGUID());
//        URHO3D_LOGINFO("P2PGetHostAddress: " + GetSubsystem<Network>()->P2PGetHostAddress());
//        URHO3D_LOGINFO("--------");
//        GetSubsystem<Network>()->P2PShowReadyStatus();
//        URHO3D_LOGINFO("");

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

        if (GetSubsystem<Network>()->P2PGetReady()) {
            static_cast<Text*>(readyButton_->GetChild(0))->SetText("Set unready");
            static_cast<Text*>(readyButton_->GetChild(0))->SetColor(Color::RED);
        } else {
            static_cast<Text*>(readyButton_->GetChild(0))->SetText("Set ready");
            static_cast<Text*>(readyButton_->GetChild(0))->SetColor(Color::GREEN);
        }
    }

    auto serverConnection = GetSubsystem<Network>()->GetServerConnection();
    if (serverConnection) {
        if (playerNodes_[serverConnection]) {
//            GetSubsystem<Input>()->SetMouseVisible(false);
//            cameraNode_->LookAt(playerNodes_[serverConnection]->GetWorldPosition());
            const float CAMERA_DISTANCE = 5.0f;

            // Move camera some distance away from the ball
            cameraNode_->SetPosition(playerNodes_[serverConnection]->GetPosition() + cameraNode_->GetRotation() * Vector3::BACK * CAMERA_DISTANCE);
        } else {
            UpdateClientObjects();
//            GetSubsystem<Input>()->SetMouseVisible(true);
        }
    }
}

void P2PMultiplayer::HandlePhysicsPrestep(StringHash eventType, VariantMap& eventData)
{
    if (!GetSubsystem<Network>()->P2PIsHostSystem()) {
        return;
    }

    // Apply client controls to the nodes only if we're the host
    using namespace PhysicsPreStep;
    float timestep = eventData[P_TIMESTEP].GetFloat();
    auto clients = GetSubsystem<Network>()->GetClientConnections();
    for (auto it = clients.Begin(); it != clients.End(); ++it) {
        // Get the last controls sent by the client
        const Controls& controls = (*it)->GetControls();
        // Torque is relative to the forward vector
        Quaternion rotation(0.0f, controls.yaw_, 0.0f);

        const float MOVE_TORQUE = 3.0f;

        if (!playerNodes_[(*it)]) {
            continue;
        }
        RigidBody* body = playerNodes_[(*it)]->GetComponent<RigidBody>();
        // Movement torque is applied before each simulation step, which happen at 60 FPS. This makes the simulation
        // independent from rendering framerate. We could also apply forces (which would enable in-air control),
        // but want to emphasize that it's a ball which should only control its motion by rolling along the ground
        if (controls.buttons_ & CTRL_FORWARD) {
            body->ApplyTorque(rotation * Vector3::RIGHT * MOVE_TORQUE);
        }
        if (controls.buttons_ & CTRL_BACK) {
            body->ApplyTorque(rotation * Vector3::LEFT * MOVE_TORQUE);
        }
        if (controls.buttons_ & CTRL_LEFT) {
            body->ApplyTorque(rotation * Vector3::FORWARD * MOVE_TORQUE);
        }
        if (controls.buttons_ & CTRL_RIGHT) {
            body->ApplyTorque(rotation * Vector3::BACK * MOVE_TORQUE);
        }
    }

    auto serverConnection = GetSubsystem<Network>()->GetServerConnection();
    if (serverConnection) {
        const Controls& controls = serverConnection->GetControls();
        // Torque is relative to the forward vector
        Quaternion rotation(0.0f, controls.yaw_, 0.0f);

        const float MOVE_TORQUE = 3.0f;
        if (!playerNodes_[serverConnection]) {
            return;
        }

        RigidBody* body = playerNodes_[serverConnection]->GetComponent<RigidBody>();
        // Movement torque is applied before each simulation step, which happen at 60 FPS. This makes the simulation
        // independent from rendering framerate. We could also apply forces (which would enable in-air control),
        // but want to emphasize that it's a ball which should only control its motion by rolling along the ground
        if (controls.buttons_ & CTRL_FORWARD) {
            body->ApplyTorque(rotation * Vector3::RIGHT * MOVE_TORQUE);
        }
        if (controls.buttons_ & CTRL_BACK) {
            body->ApplyTorque(rotation * Vector3::LEFT * MOVE_TORQUE);
        }
        if (controls.buttons_ & CTRL_LEFT) {
            body->ApplyTorque(rotation * Vector3::FORWARD * MOVE_TORQUE);
        }
        if (controls.buttons_ & CTRL_RIGHT) {
            body->ApplyTorque(rotation * Vector3::BACK * MOVE_TORQUE);
        }
    }
}

void P2PMultiplayer::Init()
{
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

    // Create the scene node & visual representation. This will be a replicated object
    Node* ballNode = scene_->CreateChild("Ball");
    ballNode->SetPosition(Vector3(0, 10, 0));
    ballNode->SetScale(0.5f);
    auto* ballObject = ballNode->CreateComponent<StaticModel>();
    ballObject->SetModel(cache->GetResource<Model>("Models/Sphere.mdl"));
    ballObject->SetMaterial(cache->GetResource<Material>("Materials/StoneSmall.xml"));

    // Create the physics components
    auto* body = ballNode->CreateComponent<RigidBody>();
    body->SetMass(1.0f);
    body->SetFriction(1.0f);
    body->SetRestitution(0.0);
    // In addition to friction, use motion damping so that the ball can not accelerate limitlessly
    body->SetLinearDamping(0.5f);
//    body->SetAngularDamping(0.5f);
    //body->SetLinearVelocity(Vector3(0.1, 1, 0.1));
    auto* shape = ballNode->CreateComponent<CollisionShape>();
    shape->SetSphere(1.0f);

    // Create a random colored point light at the ball so that can see better where is going
    auto* light2 = ballNode->CreateComponent<Light>();
    light2->SetRange(3.0f);
    light2->SetColor(
        Color(0.5f + ((unsigned)Rand() & 1u) * 0.5f, 0.5f + ((unsigned)Rand() & 1u) * 0.5f, 0.5f + ((unsigned)Rand() & 1u) * 0.5f));
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
    URHO3D_LOGERROR("CLIENT CONNECTED!");
//    return;
    using namespace ClientConnected;

    // When a client connects, assign to scene to begin scene replication
    auto* newConnection = static_cast<Connection*>(eventData[P_CONNECTION].GetPtr());
    newConnection->SetScene(scene_);

    CreatePlayerNode(newConnection);

    UpdateClientObjects();
}

void P2PMultiplayer::HandleClientDisconnected(StringHash eventType, VariantMap& eventData)
{
    URHO3D_LOGERROR("CLIENT DISCONNECTED!");
    using namespace ClientConnected;
//
//    // When a client disconnects, remove the controlled object
    auto* connection = static_cast<Connection*>(eventData[P_CONNECTION].GetPtr());
    DestroyPlayerNode(connection);

    UpdateClientObjects();
}

void P2PMultiplayer::UpdateClientObjects()
{
    PODVector<Node*> playerNodes;
    scene_->GetNodesWithTag(playerNodes, "Player");
    auto clients = GetSubsystem<Network>()->GetClientConnections();
    for (auto it = clients.Begin(); it != clients.End(); ++it) {
        for (auto it2 = playerNodes.Begin(); it2 != playerNodes.End(); ++it2) {
            if ((*it2)->GetVar("GUID").GetString() == (*it)->GetGUID()) {
//                URHO3D_LOGERROR("Found client controlled node");
                playerNodes_[(*it)] = (*it2);
            }
        }
    }
    for (auto it2 = playerNodes.Begin(); it2 != playerNodes.End(); ++it2) {
//        URHO3D_LOGERROR("GUID: " + (*it2)->GetVar("GUID").GetString() + " == " + GetSubsystem<Network>()->P2PGetGUID());
        if ((*it2)->GetVar("GUID").GetString() == GetSubsystem<Network>()->P2PGetGUID()) {
//            URHO3D_LOGERROR("We found our node with specific GUID!");
            playerNodes_[GetSubsystem<Network>()->GetServerConnection()] = (*it2);
        }
    }
//    URHO3D_LOGINFOF("Player nodes: %i", playerNodes_.Size());

}

void P2PMultiplayer::HandleResetHost(StringHash eventType, VariantMap& eventData)
{
    GetSubsystem<Network>()->P2PResetHost();
}

void P2PMultiplayer::HandleAllReadyChanged(StringHash eventType, VariantMap& eventData)
{
    using namespace P2PAllReadyChanged;
    _allReady = eventData[P_READY].GetBool();
}

void P2PMultiplayer::HandleDisconnect(StringHash eventType, VariantMap& eventData)
{
    GetSubsystem<Network>()->Disconnect(1000);
    for (auto it = playerNodes_.Begin(); it != playerNodes_.End(); ++it) {
        if ((*it).second_) {
            (*it).second_->Remove();
        }
    }
    playerNodes_.Clear();
}

void P2PMultiplayer::CreatePlayerNode(Connection* connection)
{
    if (playerNodes_[connection]) {
        return;
    }

    if (GetSubsystem<Network>()->GetClientConnections().Size() != 0 && !GetSubsystem<Network>()->P2PIsHostSystem()) {
        return;
    }
    // Then create a controllable object for that client
//    Node* newObject = CreateControllableObject();
//    serverObjects_[newConnection] = newObject;

    // Finally send the object's node ID using a remote event
//    VariantMap remoteEventData;
//    remoteEventData[P_ID] = newObject->GetID();
//    newConnection->SendRemoteEvent(E_CLIENTOBJECTID, true, remoteEventData);
    auto* cache = GetSubsystem<ResourceCache>();

    // Create the scene node & visual representation. This will be a replicated object
    Node* ballNode = scene_->CreateChild();
    ballNode->AddTag("Player");
    ballNode->SetVar("GUID", connection->GetGUID());
    ballNode->SetPosition(Vector3(0, 10, 0));
    ballNode->SetScale(0.5f);
    auto* ballObject = ballNode->CreateComponent<StaticModel>();
    ballObject->SetModel(cache->GetResource<Model>("Models/Sphere.mdl"));
    ballObject->SetMaterial(cache->GetResource<Material>("Materials/StoneSmall.xml"));

    auto* titleText = ballNode->CreateComponent<Text3D>(REPLICATED);
    titleText->SetText(connection->GetGUID());
    titleText->SetFaceCameraMode(FaceCameraMode::FC_LOOKAT_XYZ);
    titleText->SetFont(cache->GetResource<Font>("Fonts/BlueHighway.sdf"), 24);

    // Create the physics components
    auto* body = ballNode->CreateComponent<RigidBody>();
    body->SetMass(1.0f);
    body->SetFriction(1.0f);
    // In addition to friction, use motion damping so that the ball can not accelerate limitlessly
    body->SetLinearDamping(0.5f);
    body->SetAngularDamping(0.5f);
    //body->SetLinearVelocity(Vector3(0.1, 1, 0.1));
    auto* shape = ballNode->CreateComponent<CollisionShape>();
    shape->SetSphere(1.0f);

    // Create a random colored point light at the ball so that can see better where is going
    auto* light = ballNode->CreateComponent<Light>();
    light->SetRange(3.0f);
    light->SetColor(Color(0.5f + ((unsigned)Rand() & 1u) * 0.5f, 0.5f + ((unsigned)Rand() & 1u) * 0.5f, 0.5f + ((unsigned)Rand() & 1u) * 0.5f));
    playerNodes_[connection] = ballNode;
}

void P2PMultiplayer::DestroyPlayerNode(Connection* connection)
{
    if (playerNodes_[connection]) {
        playerNodes_[connection]->Remove();
        playerNodes_.Erase(connection);
    }
}