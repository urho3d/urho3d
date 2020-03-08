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

#include "Vehicle.h"
#include <Urho3D/Core/Context.h>
#include <Urho3D/Graphics/DebugRenderer.h>
#include <Urho3D/Graphics/DecalSet.h>
#include <Urho3D/Graphics/Material.h>
#include <Urho3D/Graphics/Model.h>
#include <Urho3D/Graphics/ParticleEffect.h>
#include <Urho3D/Graphics/ParticleEmitter.h>
#include <Urho3D/Graphics/StaticModel.h>
#include <Urho3D/IO/Log.h>
#include <Urho3D/Physics/CollisionShape.h>
#include <Urho3D/Physics/Constraint.h>
#include <Urho3D/Physics/PhysicsEvents.h>
#include <Urho3D/Physics/PhysicsWorld.h>
#include <Urho3D/Physics/RaycastVehicle.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Scene/Scene.h>

using namespace Urho3D;

const float CHASSIS_WIDTH = 2.6f;

void Vehicle::RegisterObject(Context* context)
{
    context->RegisterFactory<Vehicle>();
    URHO3D_ATTRIBUTE("Steering", float, steering_, 0.0f, AM_DEFAULT);
    URHO3D_ATTRIBUTE("Controls Yaw", float, controls_.yaw_, 0.0f, AM_DEFAULT);
    URHO3D_ATTRIBUTE("Controls Pitch", float, controls_.pitch_, 0.0f, AM_DEFAULT);
}

Vehicle::Vehicle(Urho3D::Context* context)
    : LogicComponent(context),
      steering_(0.0f)
{
    SetUpdateEventMask(USE_FIXEDUPDATE | USE_POSTUPDATE);
    engineForce_ = 0.0f;
    brakingForce_ = 50.0f;
    vehicleSteering_ = 0.0f;
    maxEngineForce_ = 2500.0f;
    wheelRadius_ = 0.5f;
    suspensionRestLength_ = 0.6f;
    wheelWidth_ = 0.4f;
    suspensionStiffness_ = 14.0f;
    suspensionDamping_ = 2.0f;
    suspensionCompression_ = 4.0f;
    wheelFriction_ = 1000.0f;
    rollInfluence_ = 0.12f;
    emittersCreated = false;
}

Vehicle::~Vehicle() = default;

void Vehicle::Init()
{
    auto* vehicle = node_->CreateComponent<RaycastVehicle>();
    vehicle->Init();
    auto* hullBody = node_->GetComponent<RigidBody>();
    hullBody->SetMass(800.0f);
    hullBody->SetLinearDamping(0.2f); // Some air resistance
    hullBody->SetAngularDamping(0.5f);
    hullBody->SetCollisionLayer(1);
    // This function is called only from the main program when initially creating the vehicle, not on scene load
    auto* cache = GetSubsystem<ResourceCache>();
    auto* hullObject = node_->CreateComponent<StaticModel>();
    // Setting-up collision shape
    auto* hullColShape = node_->CreateComponent<CollisionShape>();
    Vector3 v3BoxExtents = Vector3::ONE;
    hullColShape->SetBox(v3BoxExtents);
    node_->SetScale(Vector3(2.3f, 1.0f, 4.0f));
    hullObject->SetModel(cache->GetResource<Model>("Models/Box.mdl"));
    hullObject->SetMaterial(cache->GetResource<Material>("Materials/Stone.xml"));
    hullObject->SetCastShadows(true);
    float connectionHeight = -0.4f;
    bool isFrontWheel = true;
    Vector3 wheelDirection(0, -1, 0);
    Vector3 wheelAxle(-1, 0, 0);
    // We use not scaled coordinates here as everything will be scaled.
    // Wheels are on bottom at edges of the chassis
    // Note we don't set wheel nodes as children of hull (while we could) to avoid scaling to affect them.
    float wheelX = CHASSIS_WIDTH / 2.0f - wheelWidth_;
    // Front left
    connectionPoints_[0] = Vector3(-wheelX, connectionHeight, 2.5f - GetWheelRadius() * 2.0f);
    // Front right
    connectionPoints_[1] = Vector3(wheelX, connectionHeight, 2.5f - GetWheelRadius() * 2.0f);
    // Back left
    connectionPoints_[2] = Vector3(-wheelX, connectionHeight, -2.5f + GetWheelRadius() * 2.0f);
    // Back right
    connectionPoints_[3] = Vector3(wheelX, connectionHeight, -2.5f + GetWheelRadius() * 2.0f);
    const Color LtBrown(0.972f, 0.780f, 0.412f);
    for (int id = 0; id < sizeof(connectionPoints_) / sizeof(connectionPoints_[0]); id++)
    {
        Node* wheelNode = GetScene()->CreateChild();
        Vector3 connectionPoint = connectionPoints_[id];
        // Front wheels are at front (z > 0)
        // back wheels are at z < 0
        // Setting rotation according to wheel position
        bool isFrontWheel = connectionPoints_[id].z_ > 0.0f;
        wheelNode->SetRotation(connectionPoint.x_ >= 0.0 ? Quaternion(0.0f, 0.0f, -90.0f) : Quaternion(0.0f, 0.0f, 90.0f));
        wheelNode->SetWorldPosition(node_->GetWorldPosition() + node_->GetWorldRotation() * connectionPoints_[id]);
        vehicle->AddWheel(wheelNode, wheelDirection, wheelAxle, suspensionRestLength_, wheelRadius_, isFrontWheel);
        vehicle->SetWheelSuspensionStiffness(id, suspensionStiffness_);
        vehicle->SetWheelDampingRelaxation(id, suspensionDamping_);
        vehicle->SetWheelDampingCompression(id, suspensionCompression_);
        vehicle->SetWheelFrictionSlip(id, wheelFriction_);
        vehicle->SetWheelRollInfluence(id, rollInfluence_);
        wheelNode->SetScale(Vector3(1.0f, 0.65f, 1.0f));
        auto* pWheel = wheelNode->CreateComponent<StaticModel>();
        pWheel->SetModel(cache->GetResource<Model>("Models/Cylinder.mdl"));
        pWheel->SetMaterial(cache->GetResource<Material>("Materials/Stone.xml"));
        pWheel->SetCastShadows(true);
        CreateEmitter(connectionPoints_[id]);
    }
    emittersCreated = true;
    vehicle->ResetWheels();
}

void Vehicle::CreateEmitter(Vector3 place)
{
    auto* cache = GetSubsystem<ResourceCache>();
    Node* emitter = GetScene()->CreateChild();
    emitter->SetWorldPosition(node_->GetWorldPosition() + node_->GetWorldRotation() * place + Vector3(0, -wheelRadius_, 0));
    auto* particleEmitter = emitter->CreateComponent<ParticleEmitter>();
    particleEmitter->SetEffect(cache->GetResource<ParticleEffect>("Particle/Dust.xml"));
    particleEmitter->SetEmitting(false);
    particleEmitterNodeList_.Push(emitter);
    emitter->SetTemporary(true);
}

/// Applying attributes
void Vehicle::ApplyAttributes()
{
    auto* vehicle = node_->GetOrCreateComponent<RaycastVehicle>();
    if (emittersCreated)
        return;
    for (const auto& connectionPoint : connectionPoints_)
    {
        CreateEmitter(connectionPoint);
    }
    emittersCreated = true;
}

void Vehicle::FixedUpdate(float timeStep)
{
    float newSteering = 0.0f;
    float accelerator = 0.0f;
    bool brake = false;
    auto* vehicle = node_->GetComponent<RaycastVehicle>();
    // Read controls
    if (controls_.buttons_ & CTRL_LEFT)
    {
        newSteering = -1.0f;
    }
    if (controls_.buttons_ & CTRL_RIGHT)
    {
        newSteering = 1.0f;
    }
    if (controls_.buttons_ & CTRL_FORWARD)
    {
        accelerator = 1.0f;
    }
    if (controls_.buttons_ & CTRL_BACK)
    {
        accelerator = -0.5f;
    }
    if (controls_.buttons_ & CTRL_BRAKE)
    {
        brake = true;
    }
    // When steering, wake up the wheel rigidbodies so that their orientation is updated
    if (newSteering != 0.0f)
    {
        SetSteering(GetSteering() * 0.95f + newSteering * 0.05f);
    }
    else
    {
        SetSteering(GetSteering() * 0.8f + newSteering * 0.2f);
    }
    // Set front wheel angles
    vehicleSteering_ = steering_;
    int wheelIndex = 0;
    vehicle->SetSteeringValue(wheelIndex, vehicleSteering_);
    wheelIndex = 1;
    vehicle->SetSteeringValue(wheelIndex, vehicleSteering_);
    // apply forces
    engineForce_ = maxEngineForce_ * accelerator;
    // 2x wheel drive
    vehicle->SetEngineForce(2, engineForce_);
    vehicle->SetEngineForce(3, engineForce_);
    for (int i = 0; i < vehicle->GetNumWheels(); i++)
    {
        if (brake)
        {
            vehicle->SetBrake(i, brakingForce_);
        }
        else
        {
            vehicle->SetBrake(i, 0.0f);
        }
    }
}

void Vehicle::PostUpdate(float timeStep)
{
    auto* vehicle = node_->GetComponent<RaycastVehicle>();
    auto* vehicleBody = node_->GetComponent<RigidBody>();
    Vector3 velocity = vehicleBody->GetLinearVelocity();
    Vector3 accel = (velocity - prevVelocity_) / timeStep;
    float planeAccel = Vector3(accel.x_, 0.0f, accel.z_).Length();
    for (int i = 0; i < vehicle->GetNumWheels(); i++)
    {
        Node* emitter = particleEmitterNodeList_[i];
        auto* particleEmitter = emitter->GetComponent<ParticleEmitter>();
        if (vehicle->WheelIsGrounded(i) && (vehicle->GetWheelSkidInfoCumulative(i) < 0.9f || vehicle->GetBrake(i) > 2.0f ||
            planeAccel > 15.0f))
        {
            particleEmitterNodeList_[i]->SetWorldPosition(vehicle->GetContactPosition(i));
            if (!particleEmitter->IsEmitting())
            {
                particleEmitter->SetEmitting(true);
            }
            URHO3D_LOGDEBUG("GetWheelSkidInfoCumulative() = " +
                            String(vehicle->GetWheelSkidInfoCumulative(i)) + " " +
                            String(vehicle->GetMaxSideSlipSpeed()));
            /* TODO: Add skid marks here */
        }
        else if (particleEmitter->IsEmitting())
        {
            particleEmitter->SetEmitting(false);
        }
    }
    prevVelocity_ = velocity;
}
