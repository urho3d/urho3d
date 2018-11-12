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

#include <Urho3D/Input/Controls.h>
#include <Urho3D/Scene/LogicComponent.h>
#include <Urho3D/Network/Connection.h>
#include <Urho3D/Core/Context.h>
#include <Urho3D/IO/MemoryBuffer.h>
#include <Urho3D/Physics/CollisionShape.h>
#include <Urho3D/Physics/PhysicsEvents.h>
#include <Urho3D/Physics/PhysicsWorld.h>
#include <Urho3D/Physics/RigidBody.h>
#include <Urho3D/Scene/Scene.h>
#include <Urho3D/Scene/SceneEvents.h>
#include <Urho3D/Graphics/Light.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Scene/Scene.h>
#include <Urho3D/Graphics/Zone.h>
#include <Urho3D/Graphics/Model.h>
#include <Urho3D/Graphics/StaticModel.h>
#include <Urho3D/UI/Text3D.h>
#include <Urho3D/Graphics/Material.h>
#include <Urho3D/UI/Font.h>
#include <Urho3D/IO/Log.h>
#include <Urho3D/Network/Network.h>

#include "Peer.h"

Peer::Peer(Context* context) :
        Object(context)
{
    SubscribeToEvent(E_PHYSICSPRESTEP, URHO3D_HANDLER(Peer, HandlePhysicsPrestep));
}

Peer::~Peer()
{
    DestroyNode();
}

void Peer::RegisterObject(Context* context)
{
    context->RegisterFactory<Peer>();
}

void Peer::HandlePhysicsPrestep(StringHash eventType, VariantMap& eventData)
{
    // Only allow the host to update the player movements
    if (!GetSubsystem<Network>()->IsHostSystem()) {
        return;
    }

    bool isHost = false;
    String nickname = "Unnnamed";
    Controls oldControls = controls_;
    if (connection_) {
        controls_ = connection_->GetControls();
        if (connection_->GetGUID() == GetSubsystem<Network>()->GetHostAddress()) {
            isHost = true;
        }
        nickname = connection_->GetIdentity()["Name"].GetString();
    }

    const float MOVE_TORQUE = 3.0f;

    if (!node_ || !connection_) {
        return;
    }

    const bool ready = connection_->GetReady();

    auto body = node_->GetComponent<RigidBody>();

    if (ready) {
        Quaternion rotation(0.0f, controls_.yaw_, 0.0f);
        // Movement torque is applied before each simulation step, which happen at 60 FPS. This makes the simulation
        // independent from rendering framerate. We could also apply forces (which would enable in-air control),
        // but want to emphasize that it's a ball which should only control its motion by rolling along the ground
        if (controls_.buttons_ & CTRL_FORWARD) {
            body->ApplyTorque(rotation * Vector3::RIGHT * MOVE_TORQUE);
        }
        if (controls_.buttons_ & CTRL_BACK) {
            body->ApplyTorque(rotation * Vector3::LEFT * MOVE_TORQUE);
        }
        if (controls_.buttons_ & CTRL_LEFT) {
            body->ApplyTorque(rotation * Vector3::FORWARD * MOVE_TORQUE);
        }
        if (controls_.buttons_ & CTRL_RIGHT) {
            body->ApplyTorque(rotation * Vector3::BACK * MOVE_TORQUE);
        }

        if (controls_.IsPressed(CTRL_JUMP, oldControls)) {
            if (body->GetLinearVelocity().y_ < 1) {
                body->ApplyForce(Vector3(0, 200, 0));
            }
        }
    }

    String readyString = "Ready";
    if (!ready) {
        readyString = "Not ready";
    }
    auto text = node_->GetComponent<Text3D>();
    if (text && updateTimer_.GetMSec(false) > 3000) {
        if (isHost) {
            // Since host label almost never changes, we have to add some sort of random value to it so it could be synced between peers
            text->SetText("         [" + readyString + "] " + nickname + " [" + String(Random(1, 3)) + "] [HOST]");
            // Same for the color
            text->SetColor(Color(1.0f, 1.0f, Random(0.0f, 0.01f)));
        } else {
            text->SetText("         [" + readyString + "] " + nickname + " [" + String(connection_->GetLastPing()) + "]");
            text->SetColor(Color(0.0f, 1.0f, Random(0.0f, 0.01f)));
        }

        updateTimer_.Reset();

//        connection_->Ban("I don't like you!");
    }
}

void Peer::SetScene(Scene* scene)
{
    scene_ = scene;
}

void Peer::Create(Connection* connection)
{
    connection_ = connection;

    auto* cache = GetSubsystem<ResourceCache>();

    // Create the scene node & visual representation. This will be a replicated object
    node_ = scene_->CreateChild();
    node_->AddTag("Player");
    node_->SetVar("GUID", connection->GetGUID());
    node_->SetPosition(Vector3(0, 10, 0));
    node_->SetScale(0.5f);
    auto* ballObject = node_->CreateComponent<StaticModel>();
    ballObject->SetModel(cache->GetResource<Model>("Models/Sphere.mdl"));
    ballObject->SetMaterial(cache->GetResource<Material>("Materials/StoneSmall.xml"));

    auto* titleText = node_->CreateComponent<Text3D>(REPLICATED);
    titleText->SetText(connection->GetGUID());
    titleText->SetFaceCameraMode(FaceCameraMode::FC_LOOKAT_XYZ);
    titleText->SetFont(cache->GetResource<Font>("Fonts/BlueHighway.sdf"), 30);

    // Create the physics components
    auto* body = node_->CreateComponent<RigidBody>();
    body->SetMass(1.0f);
    body->SetFriction(1.0f);
    // In addition to friction, use motion damping so that the ball can not accelerate limitlessly
    body->SetLinearDamping(0.5f);
    body->SetAngularDamping(0.5f);
    //body->SetLinearVelocity(Vector3(0.1, 1, 0.1));
    auto* shape = node_->CreateComponent<CollisionShape>();
    shape->SetSphere(1.0f);

    // Create a random colored point light at the ball so that can see better where is going
    auto* light = node_->CreateComponent<Light>();
    light->SetRange(3.0f);
    light->SetColor(Color(0.5f + ((unsigned)Rand() & 1u) * 0.5f, 0.5f + ((unsigned)Rand() & 1u) * 0.5f, 0.5f + ((unsigned)Rand() & 1u) * 0.5f));

    //node_->SetScale(1.0f);
}

void Peer::SetNode(Node* node)
{
    node_ = node;
}

void Peer::SetConnection(Connection* connection)
{
    connection_ = connection;
}

void Peer::DestroyNode()
{
    if (node_) {
        node_->Remove();
    }
}
