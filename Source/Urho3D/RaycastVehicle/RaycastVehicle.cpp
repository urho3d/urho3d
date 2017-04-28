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
#include "../RaycastVehicle/RaycastVehicle.h"

namespace Urho3D
{

RaycastVehicle::RaycastVehicle(Context* context)
    : LogicComponent ( context )
{
    // fixed update() for inputs and post update() to sync wheels for rendering
    SetUpdateEventMask ( USE_FIXEDUPDATE | USE_POSTUPDATE );
    m_vehicleRayCaster = NULL;
    m_vehicle = NULL;
    m_vpNodeWheel.Clear();
    activate = false;
}
RaycastVehicle::~RaycastVehicle()
{
    if (m_vehicleRayCaster)
    {
        delete m_vehicleRayCaster;
        m_vehicleRayCaster = NULL;
    }
    if (m_vehicle)
    {
        delete m_vehicle;
        m_vehicle = NULL;
    }
    m_vpNodeWheel.Clear();
}
//=============================================================================
//=============================================================================
void RaycastVehicle::RegisterObject ( Context* context )
{
    context->RegisterFactory<RaycastVehicle>();
}
void RaycastVehicle::ApplyAttributes()
{
}
void RaycastVehicle::Init()
{
    hullBody_ = node_->GetOrCreateComponent<RigidBody>();
    int rightIndex = 0;
    int upIndex = 1;
    int forwardIndex = 2;
    Scene* scene = GetScene();
    PhysicsWorld *pPhysWorld = scene->GetComponent<PhysicsWorld>();
    btDynamicsWorld *pbtDynWorld = ( btDynamicsWorld* ) pPhysWorld->GetWorld();

    m_vehicleRayCaster = new btDefaultVehicleRaycaster ( pbtDynWorld );
    btRigidBody *bthullBody = hullBody_->GetBody();
    m_vehicle = new btRaycastVehicle ( m_tuning, bthullBody,
                                       m_vehicleRayCaster );
    pbtDynWorld->addVehicle ( m_vehicle );

    m_vehicle->setCoordinateSystem ( rightIndex, upIndex, forwardIndex );
}
void RaycastVehicle::FixedUpdate(float timeStep)
{
    for (int i = 0; i < m_vehicle->getNumWheels(); i++) {
        btWheelInfo whInfo = m_vehicle->getWheelInfo(i);
        if (whInfo.m_engineForce != 0.0f || whInfo.m_steering != 0.0f) {
            hullBody_->Activate();
            break;
        }
    }
}
void RaycastVehicle::PostUpdate (float timeStep)
{
    for (int i = 0; i < m_vehicle->getNumWheels(); i++) {
        m_vehicle->updateWheelTransform ( i, true );
        btTransform transform = m_vehicle->getWheelTransformWS ( i );
        Vector3 v3Origin = ToVector3 ( transform.getOrigin() );
        Quaternion qRot = ToQuaternion ( transform.getRotation() );

        Node *pWheel = m_vpNodeWheel[ i ];
        pWheel->SetPosition ( v3Origin );
        pWheel->SetRotation ( qRot * orig_rotation[i]);
    }
}
void RaycastVehicle::AddWheel(Node *wheelNode, Vector3 connectionPoint,
                              Vector3 wheelDirection, Vector3 wheelAxle,
                              float restLength, float wheelRadius,
                              bool frontWheel)
{
    int id = GetNumWheels();
    btVector3 connectionPointCS0(connectionPoint.x_, connectionPoint.y_, connectionPoint.z_);
    btVector3 wheelDirectionCS0(wheelDirection.x_, wheelDirection.y_, wheelDirection.z_);
    btVector3 wheelAxleCS(wheelAxle.x_, wheelAxle.y_, wheelAxle.z_);
    btWheelInfo& wheel = m_vehicle->addWheel(connectionPointCS0,
                                             wheelDirectionCS0,
                                             wheelAxleCS,
                                             restLength,
                                             wheelRadius,
                                             m_tuning,
                                             frontWheel);
    
    m_vpNodeWheel.Push(wheelNode);
    orig_rotation.Push(wheelNode->GetRotation());
}
void RaycastVehicle::ResetSuspension()
{
    m_vehicle->resetSuspension();
}
void RaycastVehicle::UpdateWheelTransform(int wheel, bool interpolated)
{
    m_vehicle->updateWheelTransform(wheel, interpolated);
}

Vector3 RaycastVehicle::GetWheelPosition(int wheel)
{
    btTransform transform = m_vehicle->getWheelTransformWS(wheel);
    Vector3 origin = ToVector3(transform.getOrigin());
    return origin;
}
Quaternion RaycastVehicle::GetWheelRotation(int wheel)
{
    btTransform transform = m_vehicle->getWheelTransformWS(wheel);
    Quaternion rotation = ToQuaternion(transform.getRotation());
    return rotation;
}
Vector3 RaycastVehicle::GetWheelConnectionPoint(int wheel)
{
    btWheelInfo whInfo = m_vehicle->getWheelInfo(wheel);
    return ToVector3(whInfo.m_chassisConnectionPointCS);
}
void RaycastVehicle::SetSteeringValue(int wheel, float steeringValue)
{
    m_vehicle->setSteeringValue(steeringValue, wheel);
}
void RaycastVehicle::SetWheelSuspensionStiffness(int wheel, float stiffness)
{
    btWheelInfo whInfo = m_vehicle->getWheelInfo(wheel);
    whInfo.m_suspensionStiffness = stiffness;
}
float RaycastVehicle::GetWheelSuspensionStiffness(int wheel)
{
    btWheelInfo whInfo = m_vehicle->getWheelInfo(wheel);
    return whInfo.m_suspensionStiffness;
}
void RaycastVehicle::SetWheelDampingRelaxation(int wheel, float damping)
{
    btWheelInfo whInfo = m_vehicle->getWheelInfo(wheel);
    whInfo.m_wheelsDampingRelaxation = damping;
}
float RaycastVehicle::GetWheelDampingRelaxation(int wheel)
{
    btWheelInfo whInfo = m_vehicle->getWheelInfo(wheel);
    return whInfo.m_wheelsDampingRelaxation;
}
void RaycastVehicle::SetWheelDampingCompression(int wheel, float compression)
{
    btWheelInfo whInfo = m_vehicle->getWheelInfo(wheel);
    whInfo.m_wheelsDampingCompression = compression;
}
float RaycastVehicle::GetWheelDampingCompression(int wheel)
{
    btWheelInfo whInfo = m_vehicle->getWheelInfo(wheel);
    return whInfo.m_wheelsDampingCompression;
}
void RaycastVehicle::SetWheelFrictionSlip(int wheel, float slip)
{
    btWheelInfo whInfo = m_vehicle->getWheelInfo(wheel);
    whInfo.m_frictionSlip = slip;
}
float RaycastVehicle::GetWheelFrictionSlip(int wheel)
{
    btWheelInfo whInfo = m_vehicle->getWheelInfo(wheel);
    return whInfo.m_frictionSlip;
}
void RaycastVehicle::SetWheelRollInfluence(int wheel, float rollInfluence)
{
    btWheelInfo whInfo = m_vehicle->getWheelInfo(wheel);
    whInfo.m_rollInfluence = rollInfluence;
}
float RaycastVehicle::GetWheelRollInfluence(int wheel)
{
    btWheelInfo whInfo = m_vehicle->getWheelInfo(wheel);
    return whInfo.m_rollInfluence;
}
void RaycastVehicle::SetEngineForce(int wheel, float force)
{
    m_vehicle->applyEngineForce(force, wheel);
}

// ----------------------------------------------------------------------------
void RegisterRaycastVehicleLibrary(Context* context)
{
    RaycastVehicle::RegisterObject(context);
}

} // namespace Urho3D
