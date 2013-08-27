//
// Copyright (c) 2008-2013 the Urho3D project.
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

#include "Button.h"
#include "Camera.h"
#include "CollisionShape.h"
#include "Connection.h"
#include "Controls.h"
#include "CoreEvents.h"
#include "Cursor.h"
#include "Engine.h"
#include "Font.h"
#include "Graphics.h"
#include "Input.h"
#include "Light.h"
#include "LineEdit.h"
#include "Log.h"
#include "Material.h"
#include "Model.h"
#include "Network.h"
#include "NetworkEvents.h"
#include "Octree.h"
#include "PhysicsEvents.h"
#include "PhysicsWorld.h"
#include "Renderer.h"
#include "RigidBody.h"
#include "ResourceCache.h"
#include "StaticModel.h"
#include "Text.h"
#include "UI.h"
#include "UIEvents.h"
#include "XMLFile.h"
#include "Zone.h"

#include "SceneReplication.h"

#include "DebugNew.h"

// UDP port we will use
static const unsigned short SERVER_PORT = 2345;
// Identifier for our custom remote event we use to tell the client which object they control
static const StringHash E_CLIENTOBJECTID("ClientObjectID");
// Identifier for the node ID parameter in the event data
static const ShortStringHash P_ID("ID");

// Control bits we define
static const unsigned CTRL_FORWARD = 1;
static const unsigned CTRL_BACK = 2;
static const unsigned CTRL_LEFT = 4;
static const unsigned CTRL_RIGHT = 8;

// Expands to this example's entry-point
DEFINE_APPLICATION_MAIN(SceneReplication)

SceneReplication::SceneReplication(Context* context) :
    Sample(context),
    yaw_(0.0f),
    pitch_(1.0f)
{
}

void SceneReplication::Start()
{
    // Execute base class startup
    Sample::Start();

    // Create the scene content
    CreateScene();
    
    // Create the UI content
    CreateUI();
    
    // Setup the viewport for displaying the scene
    SetupViewport();

    // Hook up to necessary events
    SubscribeToEvents();
}

void SceneReplication::CreateScene()
{
    scene_ = new Scene(context_);
    
    // Create the camera. Limit far clip distance to match the fog. Camera is created outside the scene so that network
    // replication will not affect it (the scene will be cleared when connecting as a client)
    cameraNode_ = new Node(context_);
    Camera* camera = cameraNode_->CreateComponent<Camera>();
    camera->SetFarClip(300.0f);
    
    // Set an initial position for the camera scene node above the plane
    cameraNode_->SetPosition(Vector3(0.0f, 5.0f, 0.0f));
}

void SceneReplication::CreateUI()
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    UI* ui = GetSubsystem<UI>();
    UIElement* root = ui->GetRoot();
    XMLFile* uiStyle = cache->GetResource<XMLFile>("UI/DefaultStyle.xml");
    // Set style to the UI root so that elements will inherit it
    root->SetDefaultStyle(uiStyle);

    // Create a Cursor UI element because we want to be able to hide and show it at will. When hidden, the mouse cursor will
    // control the camera, and when visible, it can interact with the login UI
    SharedPtr<Cursor> cursor(new Cursor(context_));
    cursor->SetStyleAuto(uiStyle);
    ui->SetCursor(cursor);
    // Set starting position of the cursor at the rendering window center
    Graphics* graphics = GetSubsystem<Graphics>();
    cursor->SetPosition(graphics->GetWidth() / 2, graphics->GetHeight() / 2);
    
    // Construct the instructions text element
    instructionsText_ = ui->GetRoot()->CreateChild<Text>();
    instructionsText_->SetText(
        "Use WASD keys to move and RMB to rotate view"
    );
    instructionsText_->SetFont(cache->GetResource<Font>("Fonts/Anonymous Pro.ttf"), 15);
    // Position the text relative to the screen center
    instructionsText_->SetHorizontalAlignment(HA_CENTER);
    instructionsText_->SetVerticalAlignment(VA_CENTER);
    instructionsText_->SetPosition(0, ui->GetRoot()->GetHeight() / 4);
    // Hide until connected
    instructionsText_->SetVisible(false);
    
    buttonContainer_ = root->CreateChild<UIElement>();
    buttonContainer_->SetFixedSize(500, 20);
    buttonContainer_->SetPosition(20, 20);
    buttonContainer_->SetLayoutMode(LM_HORIZONTAL);
    
    textEdit_ = buttonContainer_->CreateChild<LineEdit>();
    textEdit_->SetStyleAuto();
    
    connectButton_ = CreateButton("Connect", 90);
    disconnectButton_ = CreateButton("Disconnect", 100);
    startServerButton_ = CreateButton("Start Server", 110);
    
    UpdateButtons();
}

void SceneReplication::SetupViewport()
{
    Renderer* renderer = GetSubsystem<Renderer>();
    
    // Set up a viewport to the Renderer subsystem so that the 3D scene can be seen
    SharedPtr<Viewport> viewport(new Viewport(context_, scene_, cameraNode_->GetComponent<Camera>()));
    renderer->SetViewport(0, viewport);
}

void SceneReplication::SubscribeToEvents()
{
    // Subscribe to fixed timestep physics updates for setting or applying controls
    SubscribeToEvent(E_PHYSICSPRESTEP, HANDLER(SceneReplication, HandlePhysicsPreStep));
    
    // Subscribe HandlePostUpdate() method for processing update events. Subscribe to PostUpdate instead
    // of the usual Update so that physics simulation has already proceeded for the frame, and can
    // accurately follow the object with the camera
    SubscribeToEvent(E_POSTUPDATE, HANDLER(SceneReplication, HandlePostUpdate));
    
    // Subscribe to button actions
    SubscribeToEvent(connectButton_, E_RELEASED, HANDLER(SceneReplication, HandleConnect));
    SubscribeToEvent(disconnectButton_, E_RELEASED, HANDLER(SceneReplication, HandleDisconnect));
    SubscribeToEvent(startServerButton_, E_RELEASED, HANDLER(SceneReplication, HandleStartServer));

    // Subscribe to network events
    SubscribeToEvent(E_SERVERCONNECTED, HANDLER(SceneReplication, HandleConnectionStatus));
    SubscribeToEvent(E_SERVERDISCONNECTED, HANDLER(SceneReplication, HandleConnectionStatus));
    SubscribeToEvent(E_CONNECTFAILED, HANDLER(SceneReplication, HandleConnectionStatus));
    SubscribeToEvent(E_CLIENTCONNECTED, HANDLER(SceneReplication, HandleClientConnected));
    SubscribeToEvent(E_CLIENTDISCONNECTED, HANDLER(SceneReplication, HandleClientDisconnected));
    // This is a custom event, sent from the server to the client. It tells the node ID of the object the client should control
    SubscribeToEvent(E_CLIENTOBJECTID, HANDLER(SceneReplication, HandleClientObjectID));
}

Button* SceneReplication::CreateButton(const String& text, int width)
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    Font* font = cache->GetResource<Font>("Fonts/Anonymous Pro.ttf");
    
    Button* button = buttonContainer_->CreateChild<Button>();
    button->SetStyleAuto();
    button->SetFixedWidth(width);
    
    Text* buttonText = button->CreateChild<Text>();
    buttonText->SetFont(font, 12);
    buttonText->SetAlignment(HA_CENTER, VA_CENTER);
    buttonText->SetText(text);
    
    return button;
}

void SceneReplication::UpdateButtons()
{
    Network* network = GetSubsystem<Network>();
    Connection* serverConnection = network->GetServerConnection();
    bool serverRunning = network->IsServerRunning();
    
    // Show and hide buttons so that eg. Connect and Disconnect are never shown at the same time
    connectButton_->SetVisible(!serverConnection && !serverRunning);
    disconnectButton_->SetVisible(serverConnection || serverRunning);
    startServerButton_->SetVisible(!serverConnection && !serverRunning);
    textEdit_->SetVisible(!serverConnection && !serverRunning);
}

Node* SceneReplication::CreateControllableObject()
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    
    // Create the scene node & visual representation
    Node* ballNode = scene_->CreateChild("Ball");
    ballNode->SetPosition(Vector3(Random(40.0f) - 20.0f, 5.0f, Random(40.0f) - 20.0f));
    ballNode->SetScale(0.5f);
    StaticModel* ballObject = ballNode->CreateComponent<StaticModel>();
    ballObject->SetModel(cache->GetResource<Model>("Models/Sphere.mdl"));
    ballObject->SetMaterial(cache->GetResource<Material>("Materials/StoneSmall.xml"));
    
    // Create the physics components
    RigidBody* body = ballNode->CreateComponent<RigidBody>();
    body->SetMass(1.0f);
    body->SetFriction(1.0f);
    // In addition to friction, use motion damping so that the ball can not accelerate limitlessly
    body->SetLinearDamping(0.5f);
    body->SetAngularDamping(0.5f);
    CollisionShape* shape = ballNode->CreateComponent<CollisionShape>();
    shape->SetSphere(1.0f);
    
    // Create a random colored point light at the ball so that can see better where is going
    Light* light = ballNode->CreateComponent<Light>();
    light->SetRange(3.0f);
    light->SetColor(Color(0.5f + (Rand() & 1) * 0.5f, 0.5f + (Rand() & 1) * 0.5f, 0.5f + (Rand() & 1) * 0.5f));
    
    return ballNode;
}

void SceneReplication::MoveCamera()
{
    // Right mouse button controls mouse cursor visibility: hide when pressed
    UI* ui = GetSubsystem<UI>();
    Input* input = GetSubsystem<Input>();
    ui->GetCursor()->SetVisible(!input->GetMouseButtonDown(MOUSEB_RIGHT));
    
    // Mouse sensitivity as degrees per pixel
    const float MOUSE_SENSITIVITY = 0.1f;
    
    // Use this frame's mouse motion to adjust camera node yaw and pitch. Clamp the pitch and only move the camera
    // when the cursor is hidden
    if (!ui->GetCursor()->IsVisible())
    {
        IntVector2 mouseMove = input->GetMouseMove();
        yaw_ += MOUSE_SENSITIVITY * mouseMove.x_;
        pitch_ += MOUSE_SENSITIVITY * mouseMove.y_;
        pitch_ = Clamp(pitch_, 1.0f, 90.0f);
    }
    
    // Construct new orientation for the camera scene node from yaw and pitch. Roll is fixed to zero
    cameraNode_->SetRotation(Quaternion(pitch_, yaw_, 0.0f));
    
    // Only move the camera / show instructions if we have a controllable object
    bool showInstructions = false;
    if (clientObjectID_)
    {
        Node* ballNode = scene_->GetNode(clientObjectID_);
        if (ballNode)
        {
            const float CAMERA_DISTANCE = 5.0f;
            
            // Move camera some distance away from the ball
            cameraNode_->SetPosition(ballNode->GetPosition() + cameraNode_->GetRotation() * Vector3::BACK * CAMERA_DISTANCE);
            showInstructions = true;
        }
    }
    
    instructionsText_->SetVisible(showInstructions);
}

void SceneReplication::HandlePostUpdate(StringHash eventType, VariantMap& eventData)
{
    // We only rotate the camera according to mouse movement since last frame, so do not need the time step
    MoveCamera();
}

void SceneReplication::HandlePhysicsPreStep(StringHash eventType, VariantMap& eventData)
{
    // This function is different on the client and server. The client collects controls (WASD controls + yaw angle)
    // and sets them to its server connection object, so that they will be sent to the server automatically at a
    // fixed rate, by default 30 FPS. The server will actually apply the controls (authoritative simulation.)
    Network* network = GetSubsystem<Network>();
    Connection* serverConnection = network->GetServerConnection();
    
    // Client: collect controls
    if (serverConnection)
    {
        UI* ui = GetSubsystem<UI>();
        Input* input = GetSubsystem<Input>();
        Controls controls;
        
        // Assume buttons are not pressed, copy yaw
        controls.buttons_ = 0;
        controls.yaw_ = yaw_;
        
        // Only apply WASD controls if there is no focused UI element
        if (!ui->GetFocusElement())
        {
            if (input->GetKeyDown('W'))
                controls.buttons_ |= CTRL_FORWARD;
            if (input->GetKeyDown('S'))
                controls.buttons_ |= CTRL_BACK;
            if (input->GetKeyDown('A'))
                controls.buttons_ |= CTRL_LEFT;
            if (input->GetKeyDown('D'))
                controls.buttons_ |= CTRL_RIGHT;
        }
        
        serverConnection->SetControls(controls);
        // In case the server wants to do position-based interest management using the NetworkPriority components, we should also
        // tell it our observer (camera) position. In this sample it is not in use, but eg. the NinjaSnowWar game uses it
        serverConnection->SetPosition(cameraNode_->GetPosition());
    }
    // Server: apply controls to client objects
    else if (network->IsServerRunning())
    {
        const Vector<SharedPtr<Connection> >& connections = network->GetClientConnections();
        
        for (unsigned i = 0; i < connections.Size(); ++i)
        {
            Connection* connection = connections[i];
            // Get the object this connection is controlling
            Node* ballNode = serverObjects_[connection];
            if (!ballNode)
                continue;
            
            RigidBody* body = ballNode->GetComponent<RigidBody>();
            
            // Get the last controls sent by the client
            const Controls& controls = connection->GetControls();
            // Torque is relative to the forward vector
            Quaternion rotation(0.0f, controls.yaw_, 0.0f);
            
            const float MOVE_TORQUE = 3.0f;
            
            // Movement torque is applied before each simulation step, which happen at 60 FPS. This makes the simulation
            // independent from rendering framerate. We could also apply forces (which would enable in-air control),
            // but want to emphasize that it's a ball which should only control its motion by rolling along the ground
            if (controls.buttons_ & CTRL_FORWARD)
                body->ApplyTorque(rotation * Vector3::RIGHT * MOVE_TORQUE);
            if (controls.buttons_ & CTRL_BACK)
                body->ApplyTorque(rotation * Vector3::LEFT * MOVE_TORQUE);
            if (controls.buttons_ & CTRL_LEFT)
                body->ApplyTorque(rotation * Vector3::FORWARD * MOVE_TORQUE);
            if (controls.buttons_ & CTRL_RIGHT)
                body->ApplyTorque(rotation * Vector3::BACK * MOVE_TORQUE);
        }
    }
}

void SceneReplication::HandleConnect(StringHash eventType, VariantMap& eventData)
{
    Network* network = GetSubsystem<Network>();
    String address = textEdit_->GetText().Trimmed();
    if (address.Empty())
        address = "localhost"; // Use localhost to connect if nothing else specified
    
    // Connect to server, specify scene to use as a client for replication
    clientObjectID_ = 0; // Reset own object ID from possible previous connection
    network->Connect(address, SERVER_PORT, scene_);
    
    UpdateButtons();
}

void SceneReplication::HandleDisconnect(StringHash eventType, VariantMap& eventData)
{
    Network* network = GetSubsystem<Network>();
    Connection* serverConnection = network->GetServerConnection();
    // If we were connected to server, disconnect
    if (serverConnection)
    {
        serverConnection->Disconnect();
        scene_->Clear();
        clientObjectID_ = 0;
    }
    // Or if we were running a server, stop it
    else if (network->IsServerRunning())
    {
        network->StopServer();
        scene_->Clear();
    }
    
    
    UpdateButtons();
}

void SceneReplication::HandleStartServer(StringHash eventType, VariantMap& eventData)
{
    Network* network = GetSubsystem<Network>();
    network->StartServer(SERVER_PORT);
    
    // Create scene content on the server only
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    
    // Create octree and physics world with default settings
    scene_->CreateComponent<Octree>();
    scene_->CreateComponent<PhysicsWorld>();
    
    // Create a Zone component for ambient lighting & fog control
    Node* zoneNode = scene_->CreateChild("Zone");
    Zone* zone = zoneNode->CreateComponent<Zone>();
    zone->SetBoundingBox(BoundingBox(-1000.0f, 1000.0f));
    zone->SetAmbientColor(Color(0.1f, 0.1f, 0.1f));
    zone->SetFogStart(100.0f);
    zone->SetFogEnd(300.0f);
    
    // Create a directional light without shadows
    Node* lightNode = scene_->CreateChild("DirectionalLight");
    lightNode->SetDirection(Vector3(0.5f, -1.0f, 0.5f));
    Light* light = lightNode->CreateComponent<Light>();
    light->SetLightType(LIGHT_DIRECTIONAL);
    light->SetColor(Color(0.2f, 0.2f, 0.2f));
    light->SetSpecularIntensity(1.0f);
    
    // Create a "floor" consisting of several tiles. Make the tiles physical but leave small cracks between them
    for (int y = -20; y <= 20; ++y)
    {
        for (int x = -20; x <= 20; ++x)
        {
            Node* floorNode = scene_->CreateChild("FloorTile");
            floorNode->SetPosition(Vector3(x * 20.2f, -0.5f, y * 20.2f));
            floorNode->SetScale(Vector3(20.0f, 1.0f, 20.0f));
            StaticModel* floorObject = floorNode->CreateComponent<StaticModel>();
            floorObject->SetModel(cache->GetResource<Model>("Models/Box.mdl"));
            floorObject->SetMaterial(cache->GetResource<Material>("Materials/Stone.xml"));
            
            RigidBody* body = floorNode->CreateComponent<RigidBody>();
            body->SetFriction(1.0f);
            CollisionShape* shape = floorNode->CreateComponent<CollisionShape>();
            shape->SetBox(Vector3::ONE);
        }
    }
    
    UpdateButtons();
}

void SceneReplication::HandleConnectionStatus(StringHash eventType, VariantMap& eventData)
{
    UpdateButtons();
}

void SceneReplication::HandleClientConnected(StringHash eventType, VariantMap& eventData)
{
    using namespace ClientConnected;
    
    // When a client connects, assign to scene to begin scene replication
    Connection* newConnection = (Connection*)eventData[P_CONNECTION].GetPtr();
    newConnection->SetScene(scene_);
    
    // Then create a controllable object for that client
    Node* newObject = CreateControllableObject();
    serverObjects_[newConnection] = newObject;
    
    // Finally send the object's node ID using a remote event
    VariantMap remoteEventData;
    remoteEventData[P_ID] = newObject->GetID();
    newConnection->SendRemoteEvent(E_CLIENTOBJECTID, true, remoteEventData);
}

void SceneReplication::HandleClientDisconnected(StringHash eventType, VariantMap& eventData)
{
    using namespace ClientConnected;
    
    // When a client disconnects, remove the controlled object
    Connection* connection = (Connection*)eventData[P_CONNECTION].GetPtr();
    Node* object = serverObjects_[connection];
    if (object)
        object->Remove();
    
    serverObjects_.Erase(connection);
}

void SceneReplication::HandleClientObjectID(StringHash eventType, VariantMap& eventData)
{
    clientObjectID_ = eventData[P_ID].GetUInt();
}
