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

#include "../Core/Context.h"
#include "../Physics/PhysicsUtils.h"
#include "../Physics/RigidBody.h"
#include "../Physics/PhysicsWorld.h"
#include "../Scene/Scene.h"
#include "../IO/Log.h"
#include "../Physics/RaycastVehicle.h"

#include <Bullet/BulletDynamics/Vehicle/btRaycastVehicle.h>
#include <Bullet/BulletDynamics/Dynamics/btDiscreteDynamicsWorld.h>

namespace Urho3D
{

const IntVector3 RaycastVehicle::RIGHT_UP_FORWARD(0, 1, 2);
const IntVector3 RaycastVehicle::RIGHT_FORWARD_UP(0, 2, 1);
const IntVector3 RaycastVehicle::UP_FORWARD_RIGHT(1, 2, 0);
const IntVector3 RaycastVehicle::UP_RIGHT_FORWARD(1, 0, 2);
const IntVector3 RaycastVehicle::FORWARD_RIGHT_UP(2, 0, 1);
const IntVector3 RaycastVehicle::FORWARD_UP_RIGHT(2, 1, 0);

struct RaycastVehicleData
{
    RaycastVehicleData()
    {
        vehicleRayCaster_ = nullptr;
        vehicle_ = nullptr;
        added_ = false;
    }

    ~RaycastVehicleData()
    {
        delete vehicleRayCaster_;

        vehicleRayCaster_ = nullptr;
        if (vehicle_)
        {
            if (physWorld_ && added_)
            {
                btDynamicsWorld* pbtDynWorld = physWorld_->GetWorld();
                if (pbtDynWorld)
                    pbtDynWorld->removeAction(vehicle_);
                added_ = false;
            }
            delete vehicle_;
        }
        vehicle_ = nullptr;
    }

    btRaycastVehicle* Get()
    {
        return vehicle_;
    }

    void Init(Scene* scene, RigidBody* body, bool enabled, const IntVector3& coordinateSystem)
    {
        auto* pPhysWorld = scene->GetComponent<PhysicsWorld>();
        btDynamicsWorld* pbtDynWorld = pPhysWorld->GetWorld();
        if (!pbtDynWorld)
            return;

        // Delete old vehicle & action first
        delete vehicleRayCaster_;
        if (vehicle_)
        {
            if (added_)
                pbtDynWorld->removeAction(vehicle_);
            delete vehicle_;
        }

        vehicleRayCaster_ = new btDefaultVehicleRaycaster(pbtDynWorld);
        btRigidBody* bthullBody = body->GetBody();
        vehicle_ = new btRaycastVehicle(tuning_, bthullBody, vehicleRayCaster_);
        if (enabled)
        {
            pbtDynWorld->addAction(vehicle_);
            added_ = true;
        }

        SetCoordinateSystem(coordinateSystem);
        physWorld_ = pPhysWorld;
    }

    void SetCoordinateSystem(const IntVector3& coordinateSystem)
    {
        if (vehicle_)
            vehicle_->setCoordinateSystem(coordinateSystem.x_, coordinateSystem.y_, coordinateSystem.z_);
    }

    void SetEnabled(bool enabled)
    {
        if (!physWorld_ || !vehicle_)
            return;
        btDynamicsWorld* pbtDynWorld = physWorld_->GetWorld();
        if (!pbtDynWorld)
            return;

        if (enabled && !added_)
        {
            pbtDynWorld->addAction(vehicle_);
            added_ = true;
        }
        else if (!enabled && added_)
        {
            pbtDynWorld->removeAction(vehicle_);
            added_ = false;
        }
    }

    WeakPtr<PhysicsWorld> physWorld_;
    btVehicleRaycaster* vehicleRayCaster_;
    btRaycastVehicle* vehicle_;
    btRaycastVehicle::btVehicleTuning tuning_;
    bool added_;
};

RaycastVehicle::RaycastVehicle(Context* context) :
    LogicComponent(context)
{
    // fixed update() for inputs and post update() to sync wheels for rendering
    SetUpdateEventMask(USE_FIXEDUPDATE | USE_FIXEDPOSTUPDATE | USE_POSTUPDATE);
    vehicleData_ = new RaycastVehicleData();
    coordinateSystem_ = RIGHT_UP_FORWARD;
    wheelNodes_.Clear();
    activate_ = false;
    inAirRPM_ = 0.0f;
    maxSideSlipSpeed_ = 4.0f;
}

RaycastVehicle::~RaycastVehicle()
{
    delete vehicleData_;
    wheelNodes_.Clear();
}

static const StringVector wheelElementNames =
{
    "Number of wheels",
    "   Wheel node id",
    "   Wheel direction",
    "   Wheel axle",
    "   Wheel rest length",
    "   Wheel radius",
    "   Wheel is front wheel",
    "   Steering",
    "   Connection point vector",
    "   Original rotation",
    "   Cumulative skid info",
    "   Side skip speed",
    "   Grounded",
    "   Contact position",
    "   Contact normal",
    "   Suspension stiffness",
    "   Damping relaxation",
    "   Damping compression",
    "   Friction slip",
    "   Roll influence",
    "   Engine force",
    "   Brake"
};

void RaycastVehicle::RegisterObject(Context* context)
{
    context->RegisterFactory<RaycastVehicle>();
    URHO3D_MIXED_ACCESSOR_ATTRIBUTE("Wheel data", GetWheelDataAttr, SetWheelDataAttr, VariantVector, Variant::emptyVariantVector, AM_DEFAULT)
        .SetMetadata(AttributeMetadata::P_VECTOR_STRUCT_ELEMENTS, wheelElementNames);
    URHO3D_ATTRIBUTE("Maximum side slip threshold", float, maxSideSlipSpeed_, 4.0f, AM_DEFAULT);
    URHO3D_ATTRIBUTE("RPM for wheel motors in air (0=calculate)", float, inAirRPM_, 0.0f, AM_DEFAULT);
    URHO3D_ATTRIBUTE("Coordinate system", IntVector3, coordinateSystem_, RIGHT_UP_FORWARD, AM_DEFAULT);
}

void RaycastVehicle::OnSetEnabled()
{
    if (vehicleData_)
        vehicleData_->SetEnabled(IsEnabledEffective());
}

void RaycastVehicle::ApplyAttributes()
{
    int index = 0;
    hullBody_ = node_->GetOrCreateComponent<RigidBody>();
    Scene* scene = GetScene();
    vehicleData_->Init(scene, hullBody_, IsEnabledEffective(), coordinateSystem_);
    VariantVector& value = loadedWheelData_;
    int numObjects = value[index++].GetInt();
    int wheelIndex = 0;
    origRotation_.Clear();
    skidInfoCumulative_.Clear();
    wheelSideSlipSpeed_.Clear();

    for (int i = 0; i < numObjects; i++)
    {
        int node_id = value[index++].GetInt();
        Vector3 direction = value[index++].GetVector3();
        Vector3 axle = value[index++].GetVector3();
        float restLength = value[index++].GetFloat();
        float radius = value[index++].GetFloat();
        bool isFrontWheel = value[index++].GetBool();
        float steering = value[index++].GetFloat();
        Vector3 connectionPoint = value[index++].GetVector3();
        Quaternion origRotation = value[index++].GetQuaternion();
        float skidInfoC = value[index++].GetFloat();
        float sideSlipSpeed = value[index++].GetFloat();

        bool isContact = value[index++].GetBool();
        Vector3 contactPosition = value[index++].GetVector3();
        Vector3 contactNormal = value[index++].GetVector3();
        float suspensionStiffness = value[index++].GetFloat();
        float dampingRelaxation = value[index++].GetFloat();
        float dampingCompression = value[index++].GetFloat();
        float frictionSlip = value[index++].GetFloat();
        float rollInfluence = value[index++].GetFloat();
        float engineForce = value[index++].GetFloat();
        float brake = value[index++].GetFloat();
        float skidInfo = value[index++].GetFloat();
        Node* wheelNode = GetScene()->GetNode(node_id);
        if (!wheelNode)
        {
            URHO3D_LOGERROR("RaycastVehicle: Incorrect node id = " + String(node_id) + " index: " + String(index));
            continue;
        }
        btRaycastVehicle* vehicle = vehicleData_->Get();
        int id = GetNumWheels();
        btVector3 connectionPointCS0(connectionPoint.x_, connectionPoint.y_, connectionPoint.z_);
        btVector3 wheelDirectionCS0(direction.x_, direction.y_, direction.z_);
        btVector3 wheelAxleCS(axle.x_, axle.y_, axle.z_);
        btWheelInfo& wheel = vehicle->addWheel(connectionPointCS0,
                                wheelDirectionCS0,
                                wheelAxleCS,
                                restLength,
                                radius,
                                vehicleData_->tuning_,
                                isFrontWheel);
        wheelNodes_.Push(wheelNode);
        origRotation_.Push(origRotation);
        skidInfoCumulative_.Push(skidInfoC);
        wheelSideSlipSpeed_.Push(sideSlipSpeed);
        SetSteeringValue(wheelIndex, steering);
        wheel.m_raycastInfo.m_isInContact = isContact;
        wheel.m_raycastInfo.m_contactNormalWS = btVector3(contactNormal.x_, contactNormal.y_, contactNormal.z_);
        wheel.m_raycastInfo.m_contactPointWS = btVector3(contactPosition.x_, contactPosition.y_, contactPosition.z_);
        wheel.m_suspensionStiffness = suspensionStiffness;
        wheel.m_wheelsDampingRelaxation = dampingRelaxation;
        wheel.m_wheelsDampingCompression = dampingCompression;
        wheel.m_frictionSlip = frictionSlip;
        wheel.m_rollInfluence = rollInfluence;
        wheel.m_engineForce = engineForce;
        wheel.m_brake = brake;
        wheel.m_skidInfo = skidInfo;
        wheelIndex++;
    }
    URHO3D_LOGDEBUG("maxSideSlipSpeed_ value: " + String(maxSideSlipSpeed_));
    URHO3D_LOGDEBUG("loaded items: " + String(index));
    URHO3D_LOGDEBUG("loaded wheels: " + String(GetNumWheels()));
}

void RaycastVehicle::Init()
{
    hullBody_ = node_->GetOrCreateComponent<RigidBody>();
    Scene* scene = GetScene();
    vehicleData_->Init(scene, hullBody_, IsEnabledEffective(), coordinateSystem_);
}

void RaycastVehicle::FixedUpdate(float timeStep)
{
    btRaycastVehicle* vehicle = vehicleData_->Get();
    for (int i = 0; i < GetNumWheels(); i++)
    {
        btWheelInfo whInfo = vehicle->getWheelInfo(i);
        if (whInfo.m_engineForce != 0.0f || whInfo.m_steering != 0.0f)
        {
            hullBody_->Activate();
            break;
        }
    }
}

void RaycastVehicle::PostUpdate(float timeStep)
{
    btRaycastVehicle* vehicle = vehicleData_->Get();
    for (int i = 0; i < GetNumWheels(); i++)
    {
        vehicle->updateWheelTransform(i, true);
        btTransform transform = vehicle->getWheelTransformWS(i);
        Vector3 origin = ToVector3(transform.getOrigin());
        Quaternion qRot = ToQuaternion(transform.getRotation());
        Node* pWheel = wheelNodes_[i];
        pWheel->SetWorldPosition(origin);
        pWheel->SetWorldRotation(qRot * origRotation_[i]);
    }
}

void RaycastVehicle::FixedPostUpdate(float timeStep)
{
    btRaycastVehicle* vehicle = vehicleData_->Get();
    Vector3 velocity = hullBody_->GetLinearVelocity();
    for (int i = 0; i < GetNumWheels(); i++)
    {
        btWheelInfo& whInfo = vehicle->getWheelInfo(i);
        if (!WheelIsGrounded(i) && GetEngineForce(i) != 0.0f)
        {
            float delta;
            if (inAirRPM_ != 0.0f)
            {
                delta = inAirRPM_ * timeStep / 60.0f;
            }
            else
            {
                delta = 8.0f * GetEngineForce(i) * timeStep / (hullBody_->GetMass() * GetWheelRadius(i));
            }
            if (Abs(whInfo.m_deltaRotation) < Abs(delta))
            {
                whInfo.m_rotation += delta - whInfo.m_deltaRotation;
                whInfo.m_deltaRotation = delta;
            }
            if (skidInfoCumulative_[i] > 0.05f)
            {
                skidInfoCumulative_[i] -= 0.002;
            }
        }
        else
        {
            skidInfoCumulative_[i] = GetWheelSkidInfo(i);
        }
        wheelSideSlipSpeed_[i] = Abs(ToVector3(whInfo.m_raycastInfo.m_wheelAxleWS).DotProduct(velocity));
        if (wheelSideSlipSpeed_[i] > maxSideSlipSpeed_)
        {
            skidInfoCumulative_[i] = Clamp(skidInfoCumulative_[i], 0.0f, 0.89f);
        }
    }
}

void RaycastVehicle::SetMaxSideSlipSpeed(float speed)
{
    maxSideSlipSpeed_ = speed;
}

float RaycastVehicle::GetMaxSideSlipSpeed() const
{
    return maxSideSlipSpeed_;
}

void RaycastVehicle::SetWheelSkidInfoCumulative(int wheel, float skid)
{
    skidInfoCumulative_[wheel] = skid;
}

float RaycastVehicle::GetWheelSkidInfoCumulative(int wheel) const
{
    return skidInfoCumulative_[wheel];
}

void RaycastVehicle::AddWheel(Node* wheelNode,
                                Vector3 wheelDirection, Vector3 wheelAxle,
                                float restLength, float wheelRadius,
                                bool frontWheel)
{
    btRaycastVehicle* vehicle = vehicleData_->Get();
    int id = GetNumWheels();
    Vector3 connectionPoint = wheelNode->GetWorldPosition() - node_->GetWorldPosition();
    btVector3 connectionPointCS0(connectionPoint.x_, connectionPoint.y_, connectionPoint.z_);
    btVector3 wheelDirectionCS0(wheelDirection.x_, wheelDirection.y_, wheelDirection.z_);
    btVector3 wheelAxleCS(wheelAxle.x_, wheelAxle.y_, wheelAxle.z_);
    btWheelInfo& wheel = vehicle->addWheel(connectionPointCS0,
                            wheelDirectionCS0,
                            wheelAxleCS,
                            restLength,
                            wheelRadius,
                            vehicleData_->tuning_,
                            frontWheel);

    wheelNodes_.Push(wheelNode);
    origRotation_.Push(wheelNode->GetWorldRotation());
    skidInfoCumulative_.Push(1.0f);
    wheelSideSlipSpeed_.Push(0.0f);
    wheel.m_raycastInfo.m_isInContact = false;
}

void RaycastVehicle::ResetSuspension()
{
    btRaycastVehicle* vehicle = vehicleData_->Get();
    vehicle->resetSuspension();
}

void RaycastVehicle::UpdateWheelTransform(int wheel, bool interpolated)
{
    btRaycastVehicle* vehicle = vehicleData_->Get();
    vehicle->updateWheelTransform(wheel, interpolated);
}

Vector3 RaycastVehicle::GetWheelPosition(int wheel)
{
    btRaycastVehicle* vehicle = vehicleData_->Get();
    btTransform transform = vehicle->getWheelTransformWS(wheel);
    Vector3 origin = ToVector3(transform.getOrigin());
    return origin;
}

Quaternion RaycastVehicle::GetWheelRotation(int wheel)
{
    btRaycastVehicle* vehicle = vehicleData_->Get();
    const btTransform& transform = vehicle->getWheelTransformWS(wheel);
    Quaternion rotation = ToQuaternion(transform.getRotation());
    return rotation;
}

Vector3 RaycastVehicle::GetWheelConnectionPoint(int wheel) const
{
    btRaycastVehicle* vehicle = vehicleData_->Get();
    btWheelInfo whInfo = vehicle->getWheelInfo(wheel);
    return ToVector3(whInfo.m_chassisConnectionPointCS);
}

void RaycastVehicle::SetSteeringValue(int wheel, float steeringValue)
{
    btRaycastVehicle* vehicle = vehicleData_->Get();
    vehicle->setSteeringValue(steeringValue, wheel);
}

float RaycastVehicle::GetSteeringValue(int wheel) const
{
    btRaycastVehicle* vehicle = vehicleData_->Get();
    btWheelInfo whInfo = vehicle->getWheelInfo(wheel);
    return whInfo.m_steering;
}

void RaycastVehicle::SetWheelSuspensionStiffness(int wheel, float stiffness)
{
    btRaycastVehicle* vehicle = vehicleData_->Get();
    btWheelInfo& whInfo = vehicle->getWheelInfo(wheel);
    whInfo.m_suspensionStiffness = stiffness;
}

float RaycastVehicle::GetWheelSuspensionStiffness(int wheel) const
{
    btRaycastVehicle* vehicle = vehicleData_->Get();
    btWheelInfo whInfo = vehicle->getWheelInfo(wheel);
    return whInfo.m_suspensionStiffness;
}

void RaycastVehicle::SetWheelDampingRelaxation(int wheel, float damping)
{
    btRaycastVehicle* vehicle = vehicleData_->Get();
    btWheelInfo& whInfo = vehicle->getWheelInfo(wheel);
    whInfo.m_wheelsDampingRelaxation = damping;
}

float RaycastVehicle::GetWheelDampingRelaxation(int wheel) const
{
    btRaycastVehicle* vehicle = vehicleData_->Get();
    btWheelInfo whInfo = vehicle->getWheelInfo(wheel);
    return whInfo.m_wheelsDampingRelaxation;
}

void RaycastVehicle::SetWheelDampingCompression(int wheel, float compression)
{
    btRaycastVehicle* vehicle = vehicleData_->Get();
    btWheelInfo& whInfo = vehicle->getWheelInfo(wheel);
    whInfo.m_wheelsDampingCompression = compression;
}

float RaycastVehicle::GetWheelDampingCompression(int wheel) const
{
    btRaycastVehicle* vehicle = vehicleData_->Get();
    btWheelInfo whInfo = vehicle->getWheelInfo(wheel);
    return whInfo.m_wheelsDampingCompression;
}

void RaycastVehicle::SetWheelFrictionSlip(int wheel, float slip)
{
    btRaycastVehicle* vehicle = vehicleData_->Get();
    btWheelInfo& whInfo = vehicle->getWheelInfo(wheel);
    whInfo.m_frictionSlip = slip;
}

float RaycastVehicle::GetWheelFrictionSlip(int wheel) const
{
    btRaycastVehicle* vehicle = vehicleData_->Get();
    btWheelInfo whInfo = vehicle->getWheelInfo(wheel);
    return whInfo.m_frictionSlip;
}

void RaycastVehicle::SetWheelRollInfluence(int wheel, float rollInfluence)
{
    btRaycastVehicle* vehicle = vehicleData_->Get();
    btWheelInfo& whInfo = vehicle->getWheelInfo(wheel);
    whInfo.m_rollInfluence = rollInfluence;
}

Vector3 RaycastVehicle::GetContactPosition(int wheel) const
{
    btRaycastVehicle* vehicle = vehicleData_->Get();
    btWheelInfo& whInfo = vehicle->getWheelInfo(wheel);
    return ToVector3(whInfo.m_raycastInfo.m_contactPointWS);
}

Vector3 RaycastVehicle::GetContactNormal(int wheel) const
{
    btRaycastVehicle* vehicle = vehicleData_->Get();
    btWheelInfo& whInfo = vehicle->getWheelInfo(wheel);
    return ToVector3(whInfo.m_raycastInfo.m_contactNormalWS);
}

float RaycastVehicle::GetWheelSideSlipSpeed(int wheel) const
{
    return wheelSideSlipSpeed_[wheel];
}

float RaycastVehicle::GetWheelRollInfluence(int wheel) const
{
    btRaycastVehicle* vehicle = vehicleData_->Get();
    btWheelInfo whInfo = vehicle->getWheelInfo(wheel);
    return whInfo.m_rollInfluence;
}

void RaycastVehicle::SetWheelRadius(int wheel, float wheelRadius)
{
    btRaycastVehicle* vehicle = vehicleData_->Get();
    btWheelInfo& whInfo = vehicle->getWheelInfo(wheel);
    whInfo.m_wheelsRadius = wheelRadius;
}

float RaycastVehicle::GetWheelRadius(int wheel) const
{
    btRaycastVehicle* vehicle = vehicleData_->Get();
    btWheelInfo& whInfo = vehicle->getWheelInfo(wheel);
    return whInfo.m_wheelsRadius;
}

void RaycastVehicle::SetEngineForce(int wheel, float force)
{
    btRaycastVehicle* vehicle = vehicleData_->Get();
    vehicle->applyEngineForce(force, wheel);
}

float RaycastVehicle::GetEngineForce(int wheel) const
{
    btRaycastVehicle* vehicle = vehicleData_->Get();
    btWheelInfo whInfo = vehicle->getWheelInfo(wheel);
    return whInfo.m_engineForce;
}

void RaycastVehicle::SetBrake(int wheel, float force)
{
    btRaycastVehicle* vehicle = vehicleData_->Get();
    vehicle->setBrake(force, wheel);
}

float RaycastVehicle::GetBrake(int wheel) const
{
    btRaycastVehicle* vehicle = vehicleData_->Get();
    btWheelInfo whInfo = vehicle->getWheelInfo(wheel);
    return whInfo.m_brake;
}

int RaycastVehicle::GetNumWheels() const
{
    btRaycastVehicle* vehicle = vehicleData_->Get();
    return vehicle->getNumWheels();
}

Node* RaycastVehicle::GetWheelNode(int wheel) const
{
    return wheelNodes_[wheel];
}

void RaycastVehicle::SetMaxSuspensionTravel(int wheel, float maxSuspensionTravel)
{
    btRaycastVehicle* vehicle = vehicleData_->Get();
    btWheelInfo& whInfo = vehicle->getWheelInfo(wheel);
    whInfo.m_maxSuspensionTravelCm = maxSuspensionTravel;
}

float RaycastVehicle::GetMaxSuspensionTravel(int wheel)
{
    btRaycastVehicle* vehicle = vehicleData_->Get();
    btWheelInfo whInfo = vehicle->getWheelInfo(wheel);
    return whInfo.m_maxSuspensionTravelCm;
}

void RaycastVehicle::SetWheelDirection(int wheel, Vector3 direction)
{
    btVector3 dir(direction.x_, direction.y_, direction.z_);
    btRaycastVehicle* vehicle = vehicleData_->Get();
    btWheelInfo& whInfo = vehicle->getWheelInfo(wheel);
    whInfo.m_wheelDirectionCS = dir;
}

Vector3 RaycastVehicle::GetWheelDirection(int wheel) const
{
    btRaycastVehicle* vehicle = vehicleData_->Get();
    btWheelInfo& whInfo = vehicle->getWheelInfo(wheel);
    return ToVector3(whInfo.m_wheelDirectionCS);
}

void RaycastVehicle::SetWheelAxle(int wheel, Vector3 axle)
{
    btVector3 ax(axle.x_, axle.y_, axle.z_);
    btRaycastVehicle* vehicle = vehicleData_->Get();
    btWheelInfo& whInfo = vehicle->getWheelInfo(wheel);
    whInfo.m_wheelAxleCS = ax;
}

Vector3 RaycastVehicle::GetWheelAxle(int wheel) const
{
    btRaycastVehicle* vehicle = vehicleData_->Get();
    btWheelInfo& whInfo = vehicle->getWheelInfo(wheel);
    return ToVector3(whInfo.m_wheelAxleCS);
}

void RaycastVehicle::SetWheelRestLength(int wheel, float length)
{
    btRaycastVehicle* vehicle = vehicleData_->Get();
    btWheelInfo& whInfo = vehicle->getWheelInfo(wheel);
    whInfo.m_suspensionRestLength1 = length;
}

float RaycastVehicle::GetWheelRestLength(int wheel) const
{
    btRaycastVehicle* vehicle = vehicleData_->Get();
    btWheelInfo& whInfo = vehicle->getWheelInfo(wheel);
    return whInfo.m_suspensionRestLength1;
}

void RaycastVehicle::SetWheelSkidInfo(int wheel, float factor)
{
    btRaycastVehicle* vehicle = vehicleData_->Get();
    btWheelInfo& whInfo = vehicle->getWheelInfo(wheel);
    whInfo.m_skidInfo = factor;
}

float RaycastVehicle::GetWheelSkidInfo(int wheel) const
{
    btRaycastVehicle* vehicle = vehicleData_->Get();
    btWheelInfo& whInfo = vehicle->getWheelInfo(wheel);
    return whInfo.m_skidInfo;
}

bool RaycastVehicle::IsFrontWheel(int wheel) const
{
    btRaycastVehicle* vehicle = vehicleData_->Get();
    btWheelInfo& whInfo = vehicle->getWheelInfo(wheel);
    return whInfo.m_bIsFrontWheel;
}

bool RaycastVehicle::WheelIsGrounded(int wheel) const
{
    btRaycastVehicle* vehicle = vehicleData_->Get();
    btWheelInfo whInfo = vehicle->getWheelInfo(wheel);
    return whInfo.m_raycastInfo.m_isInContact;
}

void RaycastVehicle::SetInAirRPM(float rpm)
{
    inAirRPM_ = rpm;
}

float RaycastVehicle::GetInAirRPM() const
{
    return inAirRPM_;
}

void RaycastVehicle::SetCoordinateSystem(const IntVector3& coordinateSystem)
{
    coordinateSystem_ = coordinateSystem;
    vehicleData_->SetCoordinateSystem(coordinateSystem_);
}

void RaycastVehicle::ResetWheels()
{
    ResetSuspension();
    for (int i = 0; i < GetNumWheels(); i++)
    {
        UpdateWheelTransform(i, true);
        Vector3 origin = GetWheelPosition(i);
        Node* wheelNode = GetWheelNode(i);
        wheelNode->SetWorldPosition(origin);
    }
}

VariantVector RaycastVehicle::GetWheelDataAttr() const
{
    VariantVector ret;
    ret.Reserve(GetNumWheels() * 22 + 1);
    ret.Push(GetNumWheels());
    for (int i = 0; i < GetNumWheels(); i++)
    {
        Node* wNode = GetWheelNode(i);
        int node_id = wNode->GetID();
        URHO3D_LOGDEBUG("RaycastVehicle: Saving node id = " + String(node_id));
        ret.Push(node_id);
        ret.Push(GetWheelDirection(i));
        ret.Push(GetWheelAxle(i));
        ret.Push(GetWheelRestLength(i));
        ret.Push(GetWheelRadius(i));
        ret.Push(IsFrontWheel(i));
        ret.Push(GetSteeringValue(i));
        ret.Push(GetWheelConnectionPoint(i));
        ret.Push(origRotation_[i]);
        ret.Push(GetWheelSkidInfoCumulative(i));
        ret.Push(GetWheelSideSlipSpeed(i));
        ret.Push(WheelIsGrounded(i));
        ret.Push(GetContactPosition(i));
        ret.Push(GetContactNormal(i));       // 14
        ret.Push(GetWheelSuspensionStiffness(i));
        ret.Push(GetWheelDampingRelaxation(i));
        ret.Push(GetWheelDampingCompression(i));
        ret.Push(GetWheelFrictionSlip(i));
        ret.Push(GetWheelRollInfluence(i));
        ret.Push(GetEngineForce(i));
        ret.Push(GetBrake(i));
        ret.Push(GetWheelSkidInfo(i));
    }
    URHO3D_LOGDEBUG("RaycastVehicle: saved items: " + String(ret.Size()));
    URHO3D_LOGDEBUG("maxSideSlipSpeed_ value save: " + String(maxSideSlipSpeed_));
    return ret;
}

void RaycastVehicle::SetWheelDataAttr(const VariantVector& value)
{
    if (!vehicleData_)
    {
        URHO3D_LOGERROR("RaycastVehicle: vehicleData doesn't exist");
        return;
    }
    if (value.Size() < 2)
    {
        URHO3D_LOGERROR("RaycastVehicle: Incorrect vehicleData");
        return;
    }

    loadedWheelData_ = value;
}

} // namespace Urho3D
