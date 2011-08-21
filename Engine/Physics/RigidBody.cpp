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
#include "MemoryBuffer.h"
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
    
    ATTRIBUTE(RigidBody, VAR_FLOAT, "Mass", mass_, DEFAULT_MASS, AM_DEFAULT);
    REF_ACCESSOR_ATTRIBUTE(RigidBody, VAR_VECTOR3, "Physics Position", GetPosition, SetPosition, Vector3, Vector3::ZERO, AM_FILE | AM_NOEDIT);
    REF_ACCESSOR_ATTRIBUTE(RigidBody, VAR_QUATERNION, "Physics Rotation", GetRotation, SetRotation, Quaternion, Quaternion::IDENTITY, AM_FILE | AM_NOEDIT);
    REF_ACCESSOR_ATTRIBUTE(RigidBody, VAR_VECTOR3, "Lin Velocity", GetLinearVelocity, SetLinearVelocity, Vector3, Vector3::ZERO, AM_DEFAULT | AM_LATESTDATA);
    ACCESSOR_ATTRIBUTE(RigidBody, VAR_FLOAT, "Lin Rest Threshold", GetLinearRestThreshold, SetLinearRestThreshold, float, 0.01f, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(RigidBody, VAR_FLOAT, "Lin Damp Threshold", GetLinearDampingThreshold, SetLinearDampingThreshold, float, 0.01f, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(RigidBody, VAR_FLOAT, "Lin Damp Scale", GetLinearDampingScale, SetLinearDampingScale, float, 0.0f, AM_DEFAULT);
    REF_ACCESSOR_ATTRIBUTE(RigidBody, VAR_VECTOR3, "Ang Velocity", GetAngularVelocity, SetAngularVelocity, Vector3, Vector3::ZERO, AM_FILE);
    ACCESSOR_ATTRIBUTE(RigidBody, VAR_FLOAT, "Ang Rest Threshold", GetAngularRestThreshold, SetAngularRestThreshold, float, 0.01f, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(RigidBody, VAR_FLOAT, "Ang Damp Threshold", GetAngularDampingThreshold, SetAngularDampingThreshold, float, 0.01f, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(RigidBody, VAR_FLOAT, "Ang Damp Scale", GetAngularDampingScale, SetAngularDampingScale, float, 0.0f, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(RigidBody, VAR_FLOAT, "Ang Max Velocity", GetAngularMaxVelocity, SetAngularMaxVelocity, float, M_INFINITY, AM_DEFAULT);
    REF_ACCESSOR_ATTRIBUTE(RigidBody, VAR_BUFFER, "Network Ang Velocity", GetNetAngularVelocityAttr, SetNetAngularVelocityAttr, PODVector<unsigned char>, PODVector<unsigned char>(), AM_NET | AM_LATESTDATA | AM_NOEDIT);
    ACCESSOR_ATTRIBUTE(RigidBody, VAR_BOOL, "Is Active", IsActive, SetActive, bool, true, AM_FILE);
}

void RigidBody::SetMass(float mass)
{
    mass_ = Max(mass, 0.0f);
    UpdateMass();
}

void RigidBody::SetPosition(const Vector3& position)
{
    if (body_)
    {
        dBodySetPosition(body_, position.x_, position.y_, position.z_);
        previousPosition_ = position;
    }
}

void RigidBody::SetRotation(const Quaternion& rotation)
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

void RigidBody::SetLinearVelocity(const Vector3& velocity)
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

void RigidBody::SetAngularVelocity(const Vector3& velocity)
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
        if (active && !dBodyIsEnabled(body_))
            dBodyEnable(body_);
        else if (!active && dBodyIsEnabled(body_))
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

const Vector3& RigidBody::GetPosition() const
{
    if (body_)
        return *reinterpret_cast<const Vector3*>(dBodyGetPosition(body_));
    else
        return Vector3::ZERO;
}

const Quaternion& RigidBody::GetRotation() const
{
    if (body_)
        return *reinterpret_cast<const Quaternion*>(dBodyGetQuaternion(body_));
    else
        return Quaternion::IDENTITY;
}

const Vector3& RigidBody::GetLinearVelocity() const
{
    if (body_)
        return *reinterpret_cast<const Vector3*>(dBodyGetLinearVel(body_));
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

const Vector3& RigidBody::GetAngularVelocity() const
{
    if (body_)
        return *reinterpret_cast<const Vector3*>(dBodyGetAngularVel(body_));
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

void RigidBody::SetNetAngularVelocityAttr(const PODVector<unsigned char>& value)
{
    float maxVelocity = physicsWorld_ ? physicsWorld_->GetMaxNetworkAngularVelocity() : DEFAULT_MAX_NETWORK_ANGULAR_VELOCITY;
    MemoryBuffer buf(value);
    SetAngularVelocity(buf.ReadPackedVector3(maxVelocity));
}

const PODVector<unsigned char>& RigidBody::GetNetAngularVelocityAttr() const
{
    float maxVelocity = physicsWorld_ ? physicsWorld_->GetMaxNetworkAngularVelocity() : DEFAULT_MAX_NETWORK_ANGULAR_VELOCITY;
    attrBuffer_.Clear();
    attrBuffer_.WritePackedVector3(GetAngularVelocity(), maxVelocity);
    return attrBuffer_.GetBuffer();
}

void RigidBody::OnMarkedDirty(Node* node)
{
    // If the node is smoothed, do not use the dirty callback, but rather update manually during prestep
    if (node_->IsSmoothed())
        return;
    
    // Clear the dirty flag by querying world position; this way we are sure to get the dirty notification immediately
    // also the next time the node transform changes
    Vector3 newPosition = node_->GetWorldPosition();
    
    // Disregard node dirtying during the physics poststep, when we set node transform ourselves
    if (inPostStep_ || !body_)
        return;
    
    const Vector3& currentPosition = *reinterpret_cast<const Vector3*>(dBodyGetPosition(body_));
    const Quaternion& currentRotation = *reinterpret_cast<const Quaternion*>(dBodyGetQuaternion(body_));
    Quaternion newRotation = node_->GetWorldRotation();
    
    if (newPosition != currentPosition || newRotation != currentRotation)
    {
        SetActive(true);
        dBodySetPosition(body_, newPosition.x_, newPosition.y_, newPosition.z_);
        dBodySetQuaternion(body_, newRotation.GetData());
        previousPosition_ = newPosition;
        previousRotation_ = newRotation;
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
    if (!body_)
        return;
    
    const Vector3& currentPosition = *reinterpret_cast<const Vector3*>(dBodyGetPosition(body_));
    const Quaternion& currentRotation = *reinterpret_cast<const Quaternion*>(dBodyGetQuaternion(body_));
    
    if (!node_->IsSmoothed())
    {
        // If no smoothing, store the current body position for interpolation
        previousPosition_ = currentPosition;
        previousRotation_ = currentRotation;
    }
    else
    {
        // If smoothing is active, get the node's target transform and check manually if it has changed
        Matrix3x4 transform = node_->GetWorldTargetTransform();
        Vector3 newPosition = transform.Translation();
        Quaternion newRotation = transform.Rotation();
        
        if (newPosition != currentPosition || newRotation != currentRotation)
        {
            SetActive(true);
            dBodySetPosition(body_, newPosition.x_, newPosition.y_, newPosition.z_);
            dBodySetQuaternion(body_, newRotation.GetData());
        }
    }
}

void RigidBody::PostStep(float t, HashSet<RigidBody*>& processedBodies)
{
    if (!body_ || !IsActive())
        return;
    
    processedBodies.Insert(this);
    inPostStep_ = true;
    
    // If the parent node has a rigid body, process it first. For now, treat node parented to the Scene as unparented
    Node* parent = node_->GetParent();
    bool hasParent = parent && parent != node_->GetScene();
    if (hasParent)
    {
        RigidBody* parentBody = parent->GetComponent<RigidBody>();
        if (parentBody)
        {
            if (!processedBodies.Contains(parentBody))
                parentBody->PostStep(t, processedBodies);
        }
    }
    
    // Apply the physics transform to rendering transform now
    const Vector3& currentPosition = *reinterpret_cast<const Vector3*>(dBodyGetPosition(body_));
    const Quaternion& currentRotation = *reinterpret_cast<const Quaternion*>(dBodyGetQuaternion(body_));
    if (!hasParent)
    {
        // If node already has motion smoothing enabled, do not do substep interpolation
        if (!node_->IsSmoothed())
            node_->SetTransform(previousPosition_.Lerp(currentPosition, t), previousRotation_.Slerp(currentRotation, t));
        else
            node_->SetTransform(currentPosition, currentRotation);
    }
    else
    {
        // Transform rigid body's world coordinates back to parent's space
        if (!node_->IsSmoothed())
        {
            Matrix3x4 newTransform(parent->GetWorldTransform().Inverse() * Matrix3x4(previousPosition_.Lerp(currentPosition, t),
                previousRotation_.Slerp(currentRotation, t), Vector3::UNITY));
            node_->SetTransform(newTransform.Translation(), newTransform.Rotation());
        }
        else
        {
            Matrix3x4 newTransform(parent->GetWorldTargetTransform().Inverse() * Matrix3x4(currentPosition, currentRotation,
                Vector3::UNITY));
            node_->SetTransform(newTransform.Translation(), newTransform.Rotation());
        }
    }
    
    inPostStep_ = false;
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
        
        // Set initial transform. Use target position in case the node is smoothed
        const Vector3& position = node_->GetTargetPosition();
        Quaternion rotation = node_->GetTargetRotation();
        dBodySetPosition(body_, position.x_, position.y_, position.z_);
        dBodySetQuaternion(body_, rotation.GetData());
        previousPosition_ = position;
        previousRotation_ = rotation;
        
        // Associate geometries with the body
        PODVector<CollisionShape*> shapes;
        GetComponents<CollisionShape>(shapes);
        for (unsigned i = 0; i < shapes.Size(); ++i)
            shapes[i]->UpdateTransform();
    }
    
    UpdateMass();
}

void RigidBody::ReleaseBody()
{
    if (!body_ || !physicsWorld_)
        return;
    
    PODVector<CollisionShape*> shapes;
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
    
    // Get all attached collision shapes to calculate the mass
    PODVector<CollisionShape*> shapes;
    GetComponents<CollisionShape>(shapes);
    float density = 1.0f;
    
    for (unsigned i = 0; i < shapes.Size(); ++i)
    {
        CollisionShape* shape = shapes[i];
        
        dMass subMass;
        Vector3 size = shape->GetSize() * node_->GetScale();
        Vector3 offset = shape->GetPosition() * node_->GetScale();
        
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
