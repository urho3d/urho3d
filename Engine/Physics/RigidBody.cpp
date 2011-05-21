//
// Urho3D Engine
// Copyright (c) 2008-2011 Lasse Öörni
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

#include "Precompiled.h"
#include "CollisionShape.h"
#include "Context.h"
#include "Log.h"
#include "PhysicsWorld.h"
#include "ResourceCache.h"
#include "ResourceEvents.h"
#include "RigidBody.h"
#include "Scene.h"
#include "XMLElement.h"

#include <ode/ode.h>

#include "DebugNew.h"

static const float DEFAULT_MASS = 1.0f;

static const String modeNames[] =
{
    "static",
    "dynamic",
    "kinematic"
};

OBJECTTYPESTATIC(RigidBody);

RigidBody::RigidBody(Context* context) :
    Component(context),
    mass_(DEFAULT_MASS),
    body_(0),
    inPostStep_(false)
{
}

RigidBody::~RigidBody()
{
    ReleaseBody();
    
    if (physicsWorld_)
        physicsWorld_->RemoveRigidBody(this);
}

void RigidBody::RegisterObject(Context* context)
{
    context->RegisterFactory<RigidBody>();
    
    ATTRIBUTE(RigidBody, VAR_FLOAT, "Mass", mass_, DEFAULT_MASS);
    ACCESSOR_ATTRIBUTE_MODE(RigidBody, VAR_VECTOR3, "Physics Position", GetPosition, SetPosition, Vector3, Vector3::ZERO, AM_SERIALIZATION);
    ACCESSOR_ATTRIBUTE_MODE(RigidBody, VAR_QUATERNION, "Physics Rotation", GetRotation, SetRotation, Quaternion, Quaternion::IDENTITY, AM_SERIALIZATION);
    ACCESSOR_ATTRIBUTE(RigidBody, VAR_VECTOR3, "Linear Velocity", GetLinearVelocity, SetLinearVelocity, Vector3, Vector3::ZERO);
    ACCESSOR_ATTRIBUTE(RigidBody, VAR_FLOAT, "Linear Rest Threshold", GetLinearRestThreshold, SetLinearRestThreshold, float, 0.01f);
    ACCESSOR_ATTRIBUTE(RigidBody, VAR_FLOAT, "Linear Damping Threshold", GetLinearDampingThreshold, SetLinearDampingThreshold, float, 0.01f);
    ACCESSOR_ATTRIBUTE(RigidBody, VAR_FLOAT, "Linear Damping Scale", GetLinearDampingScale, SetLinearDampingScale, float, 0.0f);
    ACCESSOR_ATTRIBUTE(RigidBody, VAR_VECTOR3, "Angular Velocity", GetAngularVelocity, SetAngularVelocity, Vector3, Vector3::ZERO);
    ACCESSOR_ATTRIBUTE(RigidBody, VAR_FLOAT, "Angular Rest Threshold", GetAngularRestThreshold, SetAngularRestThreshold, float, 0.01f);
    ACCESSOR_ATTRIBUTE(RigidBody, VAR_FLOAT, "Angular Damping Threshold", GetAngularDampingThreshold, SetAngularDampingThreshold, float, 0.01f);
    ACCESSOR_ATTRIBUTE(RigidBody, VAR_FLOAT, "Angular Damping Scale", GetAngularDampingScale, SetAngularDampingScale, float, 0.0f);
    ACCESSOR_ATTRIBUTE(RigidBody, VAR_FLOAT, "Angular Max Velocity", GetAngularMaxVelocity, SetAngularMaxVelocity, float, M_INFINITY);
    ACCESSOR_ATTRIBUTE(RigidBody, VAR_BOOL, "Is Active", IsActive, SetActive, bool, true);
}

void RigidBody::SetMass(float mass)
{
    mass_ = Max(mass, 0.0f);
    UpdateMass();
}

void RigidBody::SetPosition(Vector3 position)
{
    if (body_)
    {
        dBodySetPosition(body_, position.x_, position.y_, position.z_);
        previousPosition_ = position;
    }
}

void RigidBody::SetRotation(Quaternion rotation)
{
    if (body_)
    {
        dBodySetQuaternion(body_, rotation.GetData());
        previousRotation_ = rotation;
    }
}

void RigidBody::SetTransform(const Vector3& position, const Quaternion& rotation)
{
    if (body_)
    {
        dBodySetPosition(body_, position.x_, position.y_, position.z_);
        dBodySetQuaternion(body_, rotation.GetData());
        previousPosition_ = position;
        previousRotation_ = rotation;
    }
}

void RigidBody::SetLinearVelocity(Vector3 velocity)
{
    if (body_)
        dBodySetLinearVel(body_, velocity.x_, velocity.y_, velocity.z_);
}

void RigidBody::SetLinearRestThreshold(float threshold)
{
    if (body_)
        dBodySetAutoDisableLinearThreshold(body_, threshold);
}

void RigidBody::SetLinearDampingThreshold(float threshold)
{
    if (body_)
        dBodySetLinearDampingThreshold(body_, threshold);
}

void RigidBody::SetLinearDampingScale(float scale)
{
    if (body_)
        dBodySetLinearDamping(body_, scale);
}

void RigidBody::SetAngularVelocity(Vector3 velocity)
{
    if (body_)
        dBodySetAngularVel(body_, velocity.x_, velocity.y_, velocity.z_);
}

void RigidBody::SetAngularRestThreshold(float threshold)
{
    if (body_)
        dBodySetAutoDisableAngularThreshold(body_, threshold);
}

void RigidBody::SetAngularDampingThreshold(float threshold)
{
    if (body_)
        dBodySetAngularDampingThreshold(body_, threshold);
}

void RigidBody::SetAngularDampingScale(float scale)
{
    if (body_)
        dBodySetAngularDamping(body_, scale);
}

void RigidBody::SetAngularMaxVelocity(float velocity)
{
    if (body_)
        dBodySetMaxAngularSpeed(body_, velocity);
}

void RigidBody::SetActive(bool active)
{
    if (body_)
    {
        if ((active) && (!dBodyIsEnabled(body_)))
            dBodyEnable(body_);
        else if ((!active) && (dBodyIsEnabled(body_)))
            dBodyDisable(body_);
    }
}

void RigidBody::ApplyForce(const Vector3& force)
{
    if (force == Vector3::ZERO)
        return;
    
    if (body_)
    {
        SetActive(true);
        dBodyAddForce(body_, force.x_, force.y_, force.z_);
    }
}

void RigidBody::ApplyForceAtPosition(const Vector3& force, const Vector3& position)
{
    if (force == Vector3::ZERO)
        return;
    
    if (body_)
    {
        SetActive(true);
        dBodyAddForceAtRelPos(body_, force.x_, force.y_, force.z_, position.x_, position.y_, position.z_);
    }
}

void RigidBody::ApplyTorque(const Vector3& torque)
{
    if (torque == Vector3::ZERO)
        return;
    
    if (body_)
    {
        SetActive(true);
        dBodyAddTorque(body_, torque.x_, torque.y_, torque.z_);
    }
}

void RigidBody::ResetForces()
{
    if (body_)
    {
        dBodySetForce(body_, 0.0f, 0.0f, 0.0f);
        dBodySetTorque(body_, 0.0f, 0.0f, 0.0f);
    }
}

Vector3 RigidBody::GetPosition() const
{
    if (body_)
    {
        const dReal* pos = dBodyGetPosition(body_);
        return Vector3(pos[0], pos[1], pos[2]);
    }
    else return node_->GetWorldPosition();
}

Quaternion RigidBody::GetRotation() const
{
    if (body_)
    {
        const dReal* quat = dBodyGetQuaternion(body_);
        return Quaternion(quat[0], quat[1], quat[2], quat[3]);
    }
    else return node_->GetWorldRotation();
}

Vector3 RigidBody::GetLinearVelocity() const
{
    if (body_)
    {
        const dReal* vel = dBodyGetLinearVel(body_);
        return Vector3(vel[0], vel[1], vel[2]);
    }
    else
        return Vector3::ZERO;
}

float RigidBody::GetLinearRestThreshold() const
{
    if (body_)
        return dBodyGetAutoDisableLinearThreshold(body_);
    else
        return 0.0f;
}

float RigidBody::GetLinearDampingThreshold() const
{
    if (body_)
        return dBodyGetLinearDampingThreshold(body_);
    else
        return 0.0f;
}

float RigidBody::GetLinearDampingScale() const
{
    if (body_)
        return dBodyGetLinearDamping(body_);
    else
        return 0.0f;
}

Vector3 RigidBody::GetAngularVelocity() const
{
    if (body_)
    {
        const dReal* vel = dBodyGetAngularVel(body_);
        return Vector3(vel[0], vel[1], vel[2]);
    }
    else
        return Vector3::ZERO;
}

float RigidBody::GetAngularRestThreshold() const
{
    if (body_)
        return dBodyGetAutoDisableAngularThreshold(body_);
    else
        return 0.0f;
}

float RigidBody::GetAngularDampingThreshold() const
{
    if (body_)
        return dBodyGetAngularDampingThreshold(body_);
    else
        return 0.0f;
}

float RigidBody::GetAngularDampingScale() const
{
    if (body_)
        return dBodyGetAngularDamping(body_);
    else
        return 0.0f;
}

float RigidBody::GetAngularMaxVelocity() const
{
    if (body_)
        return dBodyGetMaxAngularSpeed(body_);
    else
        return 0.0f;
}

bool RigidBody::IsActive() const
{
    if (body_)
        return dBodyIsEnabled(body_) != 0;
    else
        return false;
}

void RigidBody::OnMarkedDirty(Node* node)
{
    // Clear the dirty flag by querying world position; this way we are sure to get the dirty notification immediately
    // also the next time the node transform changes
    const Vector3& position = node_->GetWorldPosition();
    Quaternion rotation = node_->GetWorldRotation();
    
    // Disregard node dirtying during the physics poststep, when rendering transform is synced from physics transform
    if (inPostStep_)
        return;
    
    if (body_)
    {
        if ((GetPosition() != position) || (GetRotation() != rotation))
        {
            SetActive(true);
            dBodySetPosition(body_, position.x_, position.y_, position.z_);
            dBodySetQuaternion(body_, rotation.GetData());
        }
        previousPosition_ = position;
        previousRotation_ = rotation;
    }
}

void RigidBody::OnNodeSet(Node* node)
{
    if (node)
    {
        Scene* scene = node->GetScene();
        if (scene)
        {
            physicsWorld_ = scene->GetComponent<PhysicsWorld>();
            if (physicsWorld_)
                physicsWorld_->AddRigidBody(this);
            
            CreateBody();
        }
        node->AddListener(this);
    }
}

void RigidBody::PreStep()
{
    // Store the previous position for interpolation
    if (body_)
    {
        const dReal* pos = dBodyGetPosition(body_);
        const dReal* quat = dBodyGetQuaternion(body_);
        previousPosition_ = Vector3(pos[0], pos[1], pos[2]);
        previousRotation_ = Quaternion(quat[0], quat[1], quat[2], quat[3]);
    }
}

void RigidBody::PostStep(float t)
{
    if ((body_) && (IsActive()))
    {
        inPostStep_ = true;
        
        const dReal* pos = dBodyGetPosition(body_);
        const dReal* quat = dBodyGetQuaternion(body_);
        Vector3 currentPosition(pos[0], pos[1], pos[2]);
        Quaternion currentRotation(quat[0], quat[1], quat[2], quat[3]);
        
        /// \todo If the node is parented, transform will not be set correctly
        node_->SetPosition(previousPosition_.Lerp(currentPosition, t));
        node_->SetRotation(previousRotation_.Slerp(currentRotation, t));
        
        inPostStep_ = false;
    }
}

void RigidBody::CreateBody()
{
    if (!physicsWorld_)
    {
        LOGERROR("Null physics world, can not create body");
        return;
    }
    
    if (!body_)
    {
        body_ = dBodyCreate(physicsWorld_->GetWorld());
        
        // Set the user data pointer
        dBodySetData(body_, this);
        
        // Set rendering transform as the initial transform
        const Vector3& position = node_->GetWorldPosition();
        Quaternion rotation = node_->GetWorldRotation();
        dBodySetPosition(body_, position.x_, position.y_, position.z_);
        dBodySetQuaternion(body_, rotation.GetData());
        previousPosition_ = position;
        previousRotation_ = rotation;
        
        // Associate geometries with the body
        Vector<CollisionShape*> shapes;
        GetComponents<CollisionShape>(shapes);
        for (unsigned i = 0; i < shapes.Size(); ++i)
            shapes[i]->UpdateTransform();
    }
    
    UpdateMass();
}

void RigidBody::ReleaseBody()
{
    if (!body_)
        return;
    
    Vector<CollisionShape*> shapes;
    GetComponents<CollisionShape>(shapes);
    
    // First remove rigid body associations
    for (unsigned i = 0; i < shapes.Size(); ++i)
    {
        dGeomID geom = shapes[i]->GetGeometry();
        if (geom)
            dGeomSetBody(geom, 0);
    }
    
    dBodyDestroy(body_);
    body_ = 0;
    
    // Then update geometry transforms
    for (unsigned i = 0; i < shapes.Size(); ++i)
        shapes[i]->UpdateTransform();
}

void RigidBody::UpdateMass()
{
    if (!body_)
        return;
    
    dMass mass;
    dMassSetZero(&mass);
    
    float density = 1.0f;
    
    // Get all attached collision shapes to calculate the mass
    Vector<CollisionShape*> shapes;
    GetComponents<CollisionShape>(shapes);
    
    for (unsigned i = 0; i < shapes.Size(); ++i)
    {
        CollisionShape* shape = shapes[i];
        
        dMass subMass;
        Vector3 size = shape->GetSize() * GetWorldScale();
        Vector3 offset = shape->GetPosition() * GetWorldScale();
        
        switch (shape->GetShapeType())
        {
        case SHAPE_BOX:
            dMassSetBox(&subMass, density, size.x_, size.y_, size.z_);
            break;
            
        case SHAPE_SPHERE:
            dMassSetSphere(&subMass, density, size.x_);
            break;
            
        case SHAPE_CYLINDER:
            dMassSetCylinder(&subMass, density, 2, size.x_, size.z_);
            break;
            
        case SHAPE_CAPSULE:
            dMassSetCapsule(&subMass, density, 2, size.x_, size.z_);
            break;
            
        case SHAPE_TRIANGLEMESH:
            dMassSetBox(&subMass, density, size.x_, size.y_, size.z_);
            break;
        }
        
        dMatrix3 rotMatrix;
        dRfromQ(rotMatrix, shape->GetRotation().GetData());
        dMassTranslate(&subMass, offset.x_, offset.y_, offset.z_);
        dMassRotate(&subMass, rotMatrix);
        dMassAdd(&mass, &subMass);
    }
    
    // If zero mass or no geometries, set kinematic mode
    if (mass.mass <= 0.0f)
        dBodySetKinematic(body_);
    else
    {
        // Translate final mass to center; anything else is unsupported in ODE
        dMassTranslate(&mass, -mass.c[0], -mass.c[1], -mass.c[2]);
        dMassAdjust(&mass, mass_);
        dBodySetMass(body_, &mass);
    }
}
