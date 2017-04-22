//
// Copyright (c) 2008-2017 the Urho3D project.
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
#include <Bullet/BulletDynamics/Vehicle/btRaycastVehicle.h>
#include <Bullet/BulletDynamics/Dynamics/btDynamicsWorld.h>
#include "../Physics/PhysicsUtils.h"
#include "../Physics/RigidBody.h"
#include "../Physics/PhysicsWorld.h"
#include "../Scene/Scene.h"
#include "../IO/Log.h"
#include "../Physics/RaycastVehicle.h"

namespace Urho3D
{

    class RaycastVehicleData
    {
            // raycast vehicle
            btVehicleRaycaster                  *m_vehicleRayCaster;
            btRaycastVehicle                    *m_vehicle;
        public:
            btRaycastVehicle::btVehicleTuning   m_tuning;
            RaycastVehicleData()
            {
                m_vehicleRayCaster = NULL;
                m_vehicle = NULL;
            }
            ~RaycastVehicleData()
            {
                if (m_vehicleRayCaster)
                {
                    delete m_vehicleRayCaster;
                }
                m_vehicleRayCaster = NULL;
                if (m_vehicle)
                {
                    delete m_vehicle;
                }
                m_vehicle = NULL;
            }
            btRaycastVehicle *Get()
            {
                return m_vehicle;
            }
            void Init(Scene *scene, RigidBody *body)
            {
                int rightIndex = 0;
                int upIndex = 1;
                int forwardIndex = 2;
                PhysicsWorld *pPhysWorld = scene->GetComponent<PhysicsWorld>();
                btDynamicsWorld *pbtDynWorld = (btDynamicsWorld*) pPhysWorld->GetWorld();

                m_vehicleRayCaster = new btDefaultVehicleRaycaster(pbtDynWorld);
                btRigidBody *bthullBody = body->GetBody();
                m_vehicle = new btRaycastVehicle(m_tuning, bthullBody,
                                                 m_vehicleRayCaster);
                pbtDynWorld->addVehicle(m_vehicle);

                m_vehicle->setCoordinateSystem(rightIndex, upIndex, forwardIndex);
            }
    };

    RaycastVehicle::RaycastVehicle(Context* context)
        : LogicComponent(context)
    {
        // fixed update() for inputs and post update() to sync wheels for rendering
        SetUpdateEventMask(USE_FIXEDUPDATE | USE_FIXEDPOSTUPDATE | USE_POSTUPDATE);
        vehicleData_ = new RaycastVehicleData;
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
    const char* wheelElementNames[] =
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
        "   Brake",
        0
    };
    void RaycastVehicle::RegisterObject(Context* context)
    {
        context->RegisterFactory<RaycastVehicle>();
        URHO3D_MIXED_ACCESSOR_VARIANT_VECTOR_STRUCTURE_ATTRIBUTE("Wheel data", GetWheelDataForSave, SetLoadedWheelData,
                VariantVector, Variant::emptyVariantVector,
                wheelElementNames, AM_DEFAULT);
        URHO3D_ATTRIBUTE("Maximum side slip threshold", float, maxSideSlipSpeed_, 4.0f, AM_DEFAULT);
        URHO3D_ATTRIBUTE("RPM for wheel motors in air (0=calculate)", float, inAirRPM_, 0.0f, AM_DEFAULT);
    }
    VariantVector RaycastVehicle::GetWheelDataForSave() const
    {
        VariantVector ret;
        ret.Reserve(GetNumWheels() * 22 + 1);
        ret.Push(GetNumWheels());
        for (int i = 0; i < GetNumWheels(); i++)
        {
            Node *wNode = GetWheelNode(i);
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
    void RaycastVehicle::SetLoadedWheelData(const VariantVector& value)
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
    void RaycastVehicle::ApplyAttributes()
    {
        int index = 0;
        hullBody_ = node_->GetOrCreateComponent<RigidBody>();
        Scene* scene = GetScene();
        vehicleData_->Init(scene, hullBody_);
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
            Node *wheelNode = GetScene()->GetNode(node_id);
            if (!wheelNode)
            {
                URHO3D_LOGERROR("RaycastVehicle: Incorrect node id = " + String(node_id) + " index: " + String(index));
                continue;
            }
            btRaycastVehicle *m_vehicle = vehicleData_->Get();
            int id = GetNumWheels();
            btVector3 connectionPointCS0(connectionPoint.x_, connectionPoint.y_, connectionPoint.z_);
            btVector3 wheelDirectionCS0(direction.x_, direction.y_, direction.z_);
            btVector3 wheelAxleCS(axle.x_, axle.y_, axle.z_);
            btWheelInfo& wheel = m_vehicle->addWheel(connectionPointCS0,
                                 wheelDirectionCS0,
                                 wheelAxleCS,
                                 restLength,
                                 radius,
                                 vehicleData_->m_tuning,
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
        vehicleData_->Init(scene, hullBody_);
    }
    void RaycastVehicle::FixedUpdate(float timeStep)
    {
        btRaycastVehicle *m_vehicle = vehicleData_->Get();
        for (int i = 0; i < GetNumWheels(); i++)
        {
            btWheelInfo whInfo = m_vehicle->getWheelInfo(i);
            if (whInfo.m_engineForce != 0.0f || whInfo.m_steering != 0.0f)
            {
                hullBody_->Activate();
                break;
            }
        }
    }
    void RaycastVehicle::PostUpdate(float timeStep)
    {
        btRaycastVehicle *m_vehicle = vehicleData_->Get();
        for (int i = 0; i < GetNumWheels(); i++)
        {
            m_vehicle->updateWheelTransform(i, true);
            btTransform transform = m_vehicle->getWheelTransformWS(i);
            Vector3 origin = ToVector3(transform.getOrigin());
            Quaternion qRot = ToQuaternion(transform.getRotation());
            Node *pWheel = wheelNodes_[i];
            pWheel->SetWorldPosition(origin);
            pWheel->SetWorldRotation(qRot * origRotation_[i]);
        }
    }
    void RaycastVehicle::FixedPostUpdate(float timeStep)
    {
        btRaycastVehicle *m_vehicle = vehicleData_->Get();
        Vector3 velocity = hullBody_->GetLinearVelocity();
        for (int i = 0; i < GetNumWheels(); i++)
        {
            btWheelInfo& whInfo = m_vehicle->getWheelInfo(i);
            if (!WheelIsGrounded(i) && GetEngineForce(i) != 0.0f)
            {
                float delta;
                if (inAirRPM_ != 0.0f)
                {
                    delta = inAirRPM_ * timeStep / 60.0f;
                }
                else
                {
                    delta = 8.0 * GetEngineForce(i) * timeStep / (hullBody_->GetMass() * GetWheelRadius(i));
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
    void RaycastVehicle::AddWheel(Node *wheelNode,
                                  Vector3 wheelDirection, Vector3 wheelAxle,
                                  float restLength, float wheelRadius,
                                  bool frontWheel)
    {
        btRaycastVehicle *m_vehicle = vehicleData_->Get();
        int id = GetNumWheels();
        Vector3 connectionPoint = wheelNode->GetWorldPosition() - node_->GetWorldPosition();
        btVector3 connectionPointCS0(connectionPoint.x_, connectionPoint.y_, connectionPoint.z_);
        btVector3 wheelDirectionCS0(wheelDirection.x_, wheelDirection.y_, wheelDirection.z_);
        btVector3 wheelAxleCS(wheelAxle.x_, wheelAxle.y_, wheelAxle.z_);
        btWheelInfo& wheel = m_vehicle->addWheel(connectionPointCS0,
                             wheelDirectionCS0,
                             wheelAxleCS,
                             restLength,
                             wheelRadius,
                             vehicleData_->m_tuning,
                             frontWheel);

        wheelNodes_.Push(wheelNode);
        origRotation_.Push(wheelNode->GetWorldRotation());
        skidInfoCumulative_.Push(1.0f);
        wheelSideSlipSpeed_.Push(0.0f);
        wheel.m_raycastInfo.m_isInContact = false;
    }
    void RaycastVehicle::ResetSuspension()
    {
        btRaycastVehicle *m_vehicle = vehicleData_->Get();
        m_vehicle->resetSuspension();
    }
    void RaycastVehicle::UpdateWheelTransform(int wheel, bool interpolated)
    {
        btRaycastVehicle *m_vehicle = vehicleData_->Get();
        m_vehicle->updateWheelTransform(wheel, interpolated);
    }

    Vector3 RaycastVehicle::GetWheelPosition(int wheel)
    {
        btRaycastVehicle *m_vehicle = vehicleData_->Get();
        btTransform transform = m_vehicle->getWheelTransformWS(wheel);
        Vector3 origin = ToVector3(transform.getOrigin());
        return origin;
    }
    Quaternion RaycastVehicle::GetWheelRotation(int wheel)
    {
        btRaycastVehicle *m_vehicle = vehicleData_->Get();
        btTransform transform = m_vehicle->getWheelTransformWS(wheel);
        Quaternion rotation = ToQuaternion(transform.getRotation());
        return rotation;
    }
    Vector3 RaycastVehicle::GetWheelConnectionPoint(int wheel) const
    {
        btRaycastVehicle *m_vehicle = vehicleData_->Get();
        btWheelInfo whInfo = m_vehicle->getWheelInfo(wheel);
        return ToVector3(whInfo.m_chassisConnectionPointCS);
    }
    void RaycastVehicle::SetSteeringValue(int wheel, float steeringValue)
    {
        btRaycastVehicle *m_vehicle = vehicleData_->Get();
        m_vehicle->setSteeringValue(steeringValue, wheel);
    }
    float RaycastVehicle::GetSteeringValue(int wheel) const
    {
        btRaycastVehicle *m_vehicle = vehicleData_->Get();
        btWheelInfo whInfo = m_vehicle->getWheelInfo(wheel);
        return whInfo.m_steering;
    }
    void RaycastVehicle::SetWheelSuspensionStiffness(int wheel, float stiffness)
    {
        btRaycastVehicle *m_vehicle = vehicleData_->Get();
        btWheelInfo& whInfo = m_vehicle->getWheelInfo(wheel);
        whInfo.m_suspensionStiffness = stiffness;
    }
    float RaycastVehicle::GetWheelSuspensionStiffness(int wheel) const
    {
        btRaycastVehicle *m_vehicle = vehicleData_->Get();
        btWheelInfo whInfo = m_vehicle->getWheelInfo(wheel);
        return whInfo.m_suspensionStiffness;
    }
    void RaycastVehicle::SetWheelDampingRelaxation(int wheel, float damping)
    {
        btRaycastVehicle *m_vehicle = vehicleData_->Get();
        btWheelInfo& whInfo = m_vehicle->getWheelInfo(wheel);
        whInfo.m_wheelsDampingRelaxation = damping;
    }
    float RaycastVehicle::GetWheelDampingRelaxation(int wheel) const
    {
        btRaycastVehicle *m_vehicle = vehicleData_->Get();
        btWheelInfo whInfo = m_vehicle->getWheelInfo(wheel);
        return whInfo.m_wheelsDampingRelaxation;
    }
    void RaycastVehicle::SetWheelDampingCompression(int wheel, float compression)
    {
        btRaycastVehicle *m_vehicle = vehicleData_->Get();
        btWheelInfo& whInfo = m_vehicle->getWheelInfo(wheel);
        whInfo.m_wheelsDampingCompression = compression;
    }
    float RaycastVehicle::GetWheelDampingCompression(int wheel) const
    {
        btRaycastVehicle *m_vehicle = vehicleData_->Get();
        btWheelInfo whInfo = m_vehicle->getWheelInfo(wheel);
        return whInfo.m_wheelsDampingCompression;
    }
    void RaycastVehicle::SetWheelFrictionSlip(int wheel, float slip)
    {
        btRaycastVehicle *m_vehicle = vehicleData_->Get();
        btWheelInfo& whInfo = m_vehicle->getWheelInfo(wheel);
        whInfo.m_frictionSlip = slip;
    }
    float RaycastVehicle::GetWheelFrictionSlip(int wheel) const
    {
        btRaycastVehicle *m_vehicle = vehicleData_->Get();
        btWheelInfo whInfo = m_vehicle->getWheelInfo(wheel);
        return whInfo.m_frictionSlip;
    }
    void RaycastVehicle::SetWheelRollInfluence(int wheel, float rollInfluence)
    {
        btRaycastVehicle *m_vehicle = vehicleData_->Get();
        btWheelInfo& whInfo = m_vehicle->getWheelInfo(wheel);
        whInfo.m_rollInfluence = rollInfluence;
    }
    Vector3 RaycastVehicle::GetContactPosition(int wheel) const
    {
        btRaycastVehicle *m_vehicle = vehicleData_->Get();
        btWheelInfo& whInfo = m_vehicle->getWheelInfo(wheel);
        return ToVector3(whInfo.m_raycastInfo.m_contactPointWS);
    }
    Vector3 RaycastVehicle::GetContactNormal(int wheel) const
    {
        btRaycastVehicle *m_vehicle = vehicleData_->Get();
        btWheelInfo& whInfo = m_vehicle->getWheelInfo(wheel);
        return ToVector3(whInfo.m_raycastInfo.m_contactNormalWS);
    }
    float RaycastVehicle::GetWheelSideSlipSpeed(int wheel) const
    {
        return wheelSideSlipSpeed_[wheel];
    }
    float RaycastVehicle::GetWheelRollInfluence(int wheel) const
    {
        btRaycastVehicle *m_vehicle = vehicleData_->Get();
        btWheelInfo whInfo = m_vehicle->getWheelInfo(wheel);
        return whInfo.m_rollInfluence;
    }
    void RaycastVehicle::SetWheelRadius(int wheel, float wheelRadius)
    {
        btRaycastVehicle *m_vehicle = vehicleData_->Get();
        btWheelInfo& whInfo = m_vehicle->getWheelInfo(wheel);
        whInfo.m_wheelsRadius = wheelRadius;
    }
    float RaycastVehicle::GetWheelRadius(int wheel) const
    {
        btRaycastVehicle *m_vehicle = vehicleData_->Get();
        btWheelInfo& whInfo = m_vehicle->getWheelInfo(wheel);
        return whInfo.m_wheelsRadius;
    }
    void RaycastVehicle::SetEngineForce(int wheel, float force)
    {
        btRaycastVehicle *m_vehicle = vehicleData_->Get();
        m_vehicle->applyEngineForce(force, wheel);
    }
    float RaycastVehicle::GetEngineForce(int wheel) const
    {
        btRaycastVehicle *m_vehicle = vehicleData_->Get();
        btWheelInfo whInfo = m_vehicle->getWheelInfo(wheel);
        return whInfo.m_engineForce;
    }
    void RaycastVehicle::SetBrake(int wheel, float force)
    {
        btRaycastVehicle *m_vehicle = vehicleData_->Get();
        m_vehicle->setBrake(force, wheel);
    }
    float RaycastVehicle::GetBrake(int wheel) const
    {
        btRaycastVehicle *m_vehicle = vehicleData_->Get();
        btWheelInfo whInfo = m_vehicle->getWheelInfo(wheel);
        return whInfo.m_brake;
    }
    int RaycastVehicle::GetNumWheels() const
    {
        btRaycastVehicle *m_vehicle = vehicleData_->Get();
        return m_vehicle->getNumWheels();
    }
    Node *RaycastVehicle::GetWheelNode(int wheel) const
    {
        return wheelNodes_[wheel];
    }
    void RaycastVehicle::SetMaxSuspensionTravel(int wheel, float maxSuspensionTravel)
    {
        btRaycastVehicle *m_vehicle = vehicleData_->Get();
        btWheelInfo& whInfo = m_vehicle->getWheelInfo(wheel);
        whInfo.m_maxSuspensionTravelCm = maxSuspensionTravel;
    }
    float RaycastVehicle::GetMaxSuspensionTravel(int wheel)
    {
        btRaycastVehicle *m_vehicle = vehicleData_->Get();
        btWheelInfo whInfo = m_vehicle->getWheelInfo(wheel);
        return whInfo.m_maxSuspensionTravelCm;
    }
    void RaycastVehicle::SetWheelDirection(int wheel, Vector3 direction)
    {
        btVector3 dir(direction.x_, direction.y_, direction.z_);
        btRaycastVehicle *m_vehicle = vehicleData_->Get();
        btWheelInfo& whInfo = m_vehicle->getWheelInfo(wheel);
        whInfo.m_wheelDirectionCS = dir;
    }
    Vector3 RaycastVehicle::GetWheelDirection(int wheel) const
    {
        btRaycastVehicle *m_vehicle = vehicleData_->Get();
        btWheelInfo& whInfo = m_vehicle->getWheelInfo(wheel);
        return ToVector3(whInfo.m_wheelDirectionCS);
    }
    void RaycastVehicle::SetWheelAxle(int wheel, Vector3 axle)
    {
        btVector3 ax(axle.x_, axle.y_, axle.z_);
        btRaycastVehicle *m_vehicle = vehicleData_->Get();
        btWheelInfo& whInfo = m_vehicle->getWheelInfo(wheel);
        whInfo.m_wheelAxleCS = ax;
    }
    Vector3 RaycastVehicle::GetWheelAxle(int wheel) const
    {
        btRaycastVehicle *m_vehicle = vehicleData_->Get();
        btWheelInfo& whInfo = m_vehicle->getWheelInfo(wheel);
        return ToVector3(whInfo.m_wheelAxleCS);
    }
    void RaycastVehicle::SetWheelRestLength(int wheel, float length)
    {
        btRaycastVehicle *m_vehicle = vehicleData_->Get();
        btWheelInfo& whInfo = m_vehicle->getWheelInfo(wheel);
        whInfo.m_suspensionRestLength1 = length;
    }
    float RaycastVehicle::GetWheelRestLength(int wheel) const
    {
        btRaycastVehicle *m_vehicle = vehicleData_->Get();
        btWheelInfo& whInfo = m_vehicle->getWheelInfo(wheel);
        return whInfo.m_suspensionRestLength1;
    }
    void RaycastVehicle::SetWheelSkidInfo(int wheel, float factor)
    {
        btRaycastVehicle *m_vehicle = vehicleData_->Get();
        btWheelInfo& whInfo = m_vehicle->getWheelInfo(wheel);
        whInfo.m_skidInfo = factor;
    }
    float RaycastVehicle::GetWheelSkidInfo(int wheel) const
    {
        btRaycastVehicle *m_vehicle = vehicleData_->Get();
        btWheelInfo& whInfo = m_vehicle->getWheelInfo(wheel);
        return whInfo.m_skidInfo;
    }
    bool RaycastVehicle::IsFrontWheel(int wheel) const
    {
        btRaycastVehicle *m_vehicle = vehicleData_->Get();
        btWheelInfo& whInfo = m_vehicle->getWheelInfo(wheel);
        return whInfo.m_bIsFrontWheel;
    }
    bool RaycastVehicle::WheelIsGrounded(int wheel) const
    {
        btRaycastVehicle *m_vehicle = vehicleData_->Get();
        btWheelInfo whInfo = m_vehicle->getWheelInfo(wheel);
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
    void RaycastVehicle::ResetWheels()
    {
        ResetSuspension();
        for (int i = 0; i < GetNumWheels(); i++)
        {
            UpdateWheelTransform(i, true);
            Vector3 origin = GetWheelPosition(i);
            Node *wheelNode = GetWheelNode(i);
            wheelNode->SetWorldPosition(origin);
        }
    }

    void RegisterRaycastVehicleLibrary(Context* context)
    {
        RaycastVehicle::RegisterObject(context);
    }

} // namespace Urho3D
