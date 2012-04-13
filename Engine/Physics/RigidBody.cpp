//
// Urho3D Engine
// Copyright (c) 2008-2012 Lasse Öörni
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
#include "PhysicsUtils.h"
#include "PhysicsWorld.h"
#include "Profiler.h"
#include "ResourceCache.h"
#include "ResourceEvents.h"
#include "RigidBody.h"
#include "Scene.h"
#include "XMLElement.h"

#include <BulletDynamics/Dynamics/btDiscreteDynamicsWorld.h>
#include <BulletDynamics/Dynamics/btRigidBody.h>
#include <BulletCollision/CollisionShapes/btCompoundShape.h>

static const float DEFAULT_MASS = 0.0f;
static const float DEFAULT_FRICTION = 0.5f;
static const float DEFAULT_RESTITUTION = 0.0f;
static const float DEFAULT_LINEAR_REST_THRESHOLD = 0.8f;
static const float DEFAULT_ANGULAR_REST_THRESHOLD = 1.0f;
static const unsigned DEFAULT_COLLISION_LAYER = 0x1;
static const unsigned DEFAULT_COLLISION_MASK = M_MAX_UNSIGNED;

static const String collisionEventModeNames[] = 
{
    "Never",
    "When Active",
    "Always",
    ""
};

OBJECTTYPESTATIC(RigidBody);

RigidBody::RigidBody(Context* context) :
    Component(context),
    body_(0),
    compoundShape_(0),
    mass_(DEFAULT_MASS),
    collisionLayer_(DEFAULT_COLLISION_LAYER),
    collisionMask_(DEFAULT_COLLISION_MASK),
    collisionEventMode_(COLLISION_ACTIVE),
    inSetTransform_(false)
{
    compoundShape_ = new btCompoundShape();
}

RigidBody::~RigidBody()
{
    ReleaseBody();
    
    if (physicsWorld_)
        physicsWorld_->RemoveRigidBody(this);
    
    delete compoundShape_;
    compoundShape_ = 0;
}

void RigidBody::RegisterObject(Context* context)
{
    context->RegisterFactory<RigidBody>();
    
    ACCESSOR_ATTRIBUTE(RigidBody, VAR_VECTOR3, "Physics Position", GetPosition, SetPosition, Vector3, Vector3::ZERO, AM_FILE | AM_NOEDIT);
    ACCESSOR_ATTRIBUTE(RigidBody, VAR_QUATERNION, "Physics Rotation", GetRotation, SetRotation, Quaternion, Quaternion::IDENTITY, AM_FILE | AM_NOEDIT);
    ACCESSOR_ATTRIBUTE(RigidBody, VAR_FLOAT, "Mass", GetMass, SetMass, float, DEFAULT_MASS, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(RigidBody, VAR_FLOAT, "Friction", GetFriction, SetFriction, float, DEFAULT_FRICTION, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(RigidBody, VAR_FLOAT, "Restitution", GetRestitution, SetRestitution, float, DEFAULT_RESTITUTION, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(RigidBody, VAR_VECTOR3, "Linear Velocity", GetLinearVelocity, SetLinearVelocity, Vector3, Vector3::ZERO, AM_DEFAULT | AM_LATESTDATA);
    ACCESSOR_ATTRIBUTE(RigidBody, VAR_VECTOR3, "Angular Velocity", GetAngularVelocity, SetAngularVelocity, Vector3, Vector3::ZERO, AM_FILE);
    ACCESSOR_ATTRIBUTE(RigidBody, VAR_VECTOR3, "Linear Factor", GetLinearFactor, SetLinearFactor, Vector3, Vector3::ONE, AM_DEFAULT | AM_LATESTDATA);
    ACCESSOR_ATTRIBUTE(RigidBody, VAR_VECTOR3, "Angular Factor", GetAngularFactor, SetAngularFactor, Vector3, Vector3::ONE, AM_FILE);
    ACCESSOR_ATTRIBUTE(RigidBody, VAR_FLOAT, "Linear Damping", GetLinearDamping, SetLinearDamping, float, 0.0f, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(RigidBody, VAR_FLOAT, "Angular Damping", GetAngularDamping, SetAngularDamping, float, 0.01f, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(RigidBody, VAR_FLOAT, "Linear Rest Threshold", GetLinearRestThreshold, SetLinearRestThreshold, float, 0.01f, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(RigidBody, VAR_FLOAT, "Angular Rest Threshold", GetAngularRestThreshold, SetAngularRestThreshold, float, 0.01f, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(RigidBody, VAR_INT, "Collision Layer", GetCollisionLayer, SetCollisionLayer, unsigned, DEFAULT_COLLISION_LAYER, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(RigidBody, VAR_INT, "Collision Mask", GetCollisionMask, SetCollisionMask, unsigned, DEFAULT_COLLISION_MASK, AM_DEFAULT);
    REF_ACCESSOR_ATTRIBUTE(RigidBody, VAR_BUFFER, "Network Angular Velocity", GetNetAngularVelocityAttr, SetNetAngularVelocityAttr, PODVector<unsigned char>, PODVector<unsigned char>(), AM_NET | AM_LATESTDATA | AM_NOEDIT);
    ENUM_ATTRIBUTE(RigidBody, "Collision Event Mode", collisionEventMode_, collisionEventModeNames, COLLISION_ACTIVE, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(RigidBody, VAR_BOOL, "Use Gravity", GetUseGravity, SetUseGravity, bool, true, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(RigidBody, VAR_BOOL, "Is Kinematic", IsKinematic, SetKinematic, bool, false, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(RigidBody, VAR_BOOL, "Is Phantom", IsPhantom, SetPhantom, bool, false, AM_DEFAULT);
}

void RigidBody::getWorldTransform(btTransform &worldTrans) const
{
    if (node_)
    {
        worldTrans.setOrigin(ToBtVector3(node_->GetWorldPosition()));
        worldTrans.setRotation(ToBtQuaternion(node_->GetWorldRotation()));
    }
}

void RigidBody::setWorldTransform(const btTransform &worldTrans)
{
    /// \todo If rigid body is parented, should set the transforms in hierarchy order (parent first)
    if (node_)
    {
        inSetTransform_ = true;
        node_->SetWorldPosition(ToVector3(worldTrans.getOrigin()));
        node_->SetWorldRotation(ToQuaternion(worldTrans.getRotation()));
        inSetTransform_ = false;
    }
}

void RigidBody::SetMass(float mass)
{
    mass = Max(mass, 0.0f);
    
    if (mass != mass_)
    {
        mass_ = mass;
        AddBodyToWorld();
        
        if (mass > 0.0f)
            Activate();
        else
        {
            SetLinearVelocity(Vector3::ZERO);
            SetAngularVelocity(Vector3::ZERO);
        }
    }
}

void RigidBody::SetPosition(Vector3 position)
{
    if (body_)
    {
        btTransform& worldTrans = body_->getWorldTransform();
        worldTrans.setOrigin(ToBtVector3(position));
        
        // When forcing the physics position, set also interpolated position so that there is no jitter
        btTransform interpTrans = body_->getInterpolationWorldTransform();
        interpTrans.setOrigin(worldTrans.getOrigin());
        body_->setInterpolationWorldTransform(interpTrans);
    }
}

void RigidBody::SetRotation(Quaternion rotation)
{
    if (body_)
    {
        btTransform& worldTrans = body_->getWorldTransform();
        worldTrans.setRotation(ToBtQuaternion(rotation));
        
        // When forcing the physics position, set also interpolated position so that there is no jitter
        btTransform interpTrans = body_->getInterpolationWorldTransform();
        interpTrans.setRotation(worldTrans.getRotation());
        body_->setInterpolationWorldTransform(interpTrans);
    }
}

void RigidBody::SetTransform(const Vector3& position, const Quaternion& rotation)
{
    if (body_)
    {
        btTransform& worldTrans = body_->getWorldTransform();
        worldTrans.setOrigin(ToBtVector3(position));
        worldTrans.setRotation(ToBtQuaternion(rotation));
        
        // When forcing the physics position, set also interpolated position so that there is no jitter
        btTransform interpTrans = body_->getInterpolationWorldTransform();
        interpTrans.setOrigin(worldTrans.getOrigin());
        interpTrans.setRotation(worldTrans.getRotation());
        body_->setInterpolationWorldTransform(interpTrans);
    }
}

void RigidBody::SetLinearVelocity(Vector3 velocity)
{
    if (body_)
    {
        body_->setLinearVelocity(ToBtVector3(velocity));
        if (velocity != Vector3::ZERO)
            Activate();
    }
}

void RigidBody::SetLinearFactor(Vector3 factor)
{
    if (body_)
        body_->setLinearFactor(ToBtVector3(factor));
}

void RigidBody::SetLinearRestThreshold(float threshold)
{
    if (body_)
        body_->setSleepingThresholds(threshold, body_->getAngularSleepingThreshold());
}

void RigidBody::SetLinearDamping(float damping)
{
    if (body_)
        body_->setDamping(damping, body_->getAngularDamping());
}

void RigidBody::SetAngularVelocity(Vector3 velocity)
{
    if (body_)
    {
        body_->setAngularVelocity(ToBtVector3(velocity));
        if (velocity != Vector3::ZERO)
            Activate();
    }
}

void RigidBody::SetAngularFactor(Vector3 factor)
{
    if (body_)
        body_->setAngularFactor(ToBtVector3(factor));
}

void RigidBody::SetAngularRestThreshold(float threshold)
{
    if (body_)
        body_->setSleepingThresholds(body_->getLinearSleepingThreshold(), threshold);
}

void RigidBody::SetAngularDamping(float damping)
{
    if (body_)
        body_->setDamping(body_->getLinearDamping(), damping);
}

void RigidBody::SetFriction(float friction)
{
    if (body_)
        body_->setFriction(friction);
}

void RigidBody::SetRestitution(float restitution)
{
    if (body_)
        body_->setRestitution(restitution);
}

void RigidBody::SetUseGravity(bool enable)
{
    if (physicsWorld_ && body_)
    {
        btDiscreteDynamicsWorld* world = physicsWorld_->GetWorld();
        
        int flags = body_->getFlags();
        if (enable)
            flags &= ~BT_DISABLE_WORLD_GRAVITY;
        else
            flags |= BT_DISABLE_WORLD_GRAVITY;
        body_->setFlags(flags);
        
        if (enable)
            body_->setGravity(world->getGravity());
        else
            body_->setGravity(btVector3(0.0f, 0.0f, 0.0f));
    }
}

void RigidBody::SetKinematic(bool enable)
{
    if (body_)
    {
        int flags = body_->getCollisionFlags();
        if (enable)
            flags |= btCollisionObject::CF_KINEMATIC_OBJECT;
        else
            flags &= ~btCollisionObject::CF_KINEMATIC_OBJECT;
        body_->setCollisionFlags(flags),
        
        AddBodyToWorld();
    }
}

void RigidBody::SetPhantom(bool enable)
{
    if (body_)
    {
        int flags = body_->getCollisionFlags();
        if (enable)
            flags |= btCollisionObject::CF_NO_CONTACT_RESPONSE;
        else
            flags &= ~btCollisionObject::CF_NO_CONTACT_RESPONSE;
        body_->setCollisionFlags(flags);
        
        AddBodyToWorld();
    }
}

void RigidBody::SetCollisionLayer(unsigned layer)
{
    if (layer != collisionLayer_)
    {
        collisionLayer_ = layer;
        AddBodyToWorld();
    }
}

void RigidBody::SetCollisionMask(unsigned mask)
{
    if (mask != collisionMask_)
    {
        collisionMask_ = mask;
        AddBodyToWorld();
    }
}

void RigidBody::SetCollisionLayerAndMask(unsigned layer, unsigned mask)
{
    if (layer != collisionLayer_ || mask != collisionMask_)
    {
        collisionLayer_ = layer;
        collisionMask_ = mask;
        AddBodyToWorld();
    }
}

void RigidBody::SetCollisionEventMode(CollisionEventMode mode)
{
    collisionEventMode_ = mode;
}

void RigidBody::ApplyForce(const Vector3& force)
{
    if (body_ && force != Vector3::ZERO)
        body_->applyCentralForce(ToBtVector3(force));
}

void RigidBody::ApplyForce(const Vector3& force, const Vector3& position)
{
    if (body_ && force != Vector3::ZERO)
        body_->applyForce(ToBtVector3(force), ToBtVector3(position));
}

void RigidBody::ApplyTorque(const Vector3& torque)
{
    if (body_ && torque != Vector3::ZERO)
        body_->applyTorque(ToBtVector3(torque));
}

void RigidBody::ApplyImpulse(const Vector3& impulse)
{
    if (body_ && impulse != Vector3::ZERO)
        body_->applyCentralImpulse(ToBtVector3(impulse));
}

void RigidBody::ApplyImpulse(const Vector3& impulse, const Vector3& position)
{
    if (body_ && impulse != Vector3::ZERO)
        body_->applyImpulse(ToBtVector3(impulse), ToBtVector3(position));
}

void RigidBody::ApplyTorqueImpulse(const Vector3& torque)
{
    if (body_ && torque != Vector3::ZERO)
        body_->applyTorqueImpulse(ToBtVector3(torque));
}

void RigidBody::ResetForces()
{
    if (body_)
        body_->clearForces();
}

void RigidBody::Activate()
{
    if (body_)
        body_->activate();
}

Vector3 RigidBody::GetPosition() const
{
    if (body_)
        return ToVector3(body_->getWorldTransform().getOrigin());
    else
        return Vector3::ZERO;
}

Quaternion RigidBody::GetRotation() const
{
    if (body_)
        return ToQuaternion(body_->getWorldTransform().getRotation());
    else
        return Quaternion::IDENTITY;
}

Vector3 RigidBody::GetLinearVelocity() const
{
    if (body_)
        return ToVector3(body_->getLinearVelocity());
    else
        return Vector3::ZERO;
}

Vector3 RigidBody::GetLinearFactor() const
{
    if (body_)
        return ToVector3(body_->getLinearFactor());
    else
        return Vector3::ZERO;
}

float RigidBody::GetLinearRestThreshold() const
{
    if (body_)
        return body_->getLinearSleepingThreshold();
    else
        return 0.0f;
}

float RigidBody::GetLinearDamping() const
{
    if (body_)
        return body_->getLinearDamping();
    else
        return 0.0f;
}

Vector3 RigidBody::GetAngularVelocity() const
{
    if (body_)
        return ToVector3(body_->getAngularVelocity());
    else
        return Vector3::ZERO;
}

Vector3 RigidBody::GetAngularFactor() const
{
    if (body_)
        return ToVector3(body_->getAngularFactor());
    else
        return Vector3::ZERO;
}

float RigidBody::GetAngularRestThreshold() const
{
    if (body_)
        return body_->getAngularSleepingThreshold();
    else
        return 0.0f;
}

float RigidBody::GetAngularDamping() const
{
    if (body_)
        return body_->getAngularDamping();
    else
        return 0.0f;
}

float RigidBody::GetFriction() const
{
    if (body_)
        return body_->getFriction();
    else
        return 0.0f;
}

float RigidBody::GetRestitution() const
{
    if (body_)
        return body_->getRestitution();
    else
        return 0.0f;
}

bool RigidBody::GetUseGravity() const
{
    if (body_)
        return (body_->getFlags() & BT_DISABLE_WORLD_GRAVITY) == 0;
    else
        return true;
}

bool RigidBody::IsKinematic() const
{
    if (body_)
        return (body_->getCollisionFlags() & btCollisionObject::CF_KINEMATIC_OBJECT) != 0;
    else
        return false;
}

bool RigidBody::IsPhantom() const
{
    if (body_)
        return (body_->getCollisionFlags() & btCollisionObject::CF_NO_CONTACT_RESPONSE) != 0;
    else
        return false;
}

bool RigidBody::IsActive() const
{
    if (body_)
        return body_->isActive();
    else
        return false;
}

void RigidBody::UpdateMass()
{
    if (body_)
    {
        btVector3 localInertia(0.0f, 0.0f, 0.0f);
        if (mass_ > 0.0f)
            compoundShape_->calculateLocalInertia(mass_, localInertia);
        body_->setMassProps(mass_, localInertia);
    }
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

void RigidBody::DrawDebugGeometry(DebugRenderer* debug, bool depthTest)
{
    if (debug && physicsWorld_ && body_)
    {
        physicsWorld_->SetDebugRenderer(debug);
        physicsWorld_->SetDebugDepthTest(depthTest);
        
        btDiscreteDynamicsWorld* world = physicsWorld_->GetWorld();
        world->debugDrawObject(body_->getWorldTransform(), compoundShape_, IsActive() ? btVector3(1.0f, 1.0f, 1.0f) : 
            btVector3(0.0f, 1.0f, 0.0f));
        
        physicsWorld_->SetDebugRenderer(0);
    }
}

void RigidBody::OnMarkedDirty(Node* node)
{
    /// \todo If the node contains a SmoothedTransform component, do not react to dirtying, but rather update the position elsewhere
    if (!inSetTransform_)
    {
        // Physics operations are not safe from worker threads
        Scene* scene = node->GetScene();
        if (scene && scene->IsThreadedUpdate())
        {
            scene->DelayedMarkedDirty(this);
            return;
        }
        
        Vector3 newWorldPos = node_->GetWorldPosition();
        Quaternion newWorldRot = node_->GetWorldRotation();
        
        if (newWorldPos != GetPosition())
            SetPosition(newWorldPos);
        if (newWorldRot != GetRotation())
            SetRotation(newWorldRot);
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
            else
                LOGERROR("Null physics world, can not create rigid body");
            
            AddBodyToWorld();
        }
        node->AddListener(this);
    }
}

void RigidBody::AddBodyToWorld()
{
    if (!physicsWorld_)
        return;
    
    btDiscreteDynamicsWorld* world = physicsWorld_->GetWorld();
    if (body_)
    {
        world->removeRigidBody(body_);
        UpdateMass();
    }
    else
    {
        btVector3 localInertia(0.0f, 0.0f, 0.0f);
        body_ = new btRigidBody(mass_, this, compoundShape_, localInertia);
        body_->setUserPointer(this);
        
        // Check if CollisionShapes already exist in the node and add them to the compound shape
        // Note: NotifyRigidBody() will cause mass to be updated
        PODVector<CollisionShape*> shapes;
        node_->GetDerivedComponents<CollisionShape>(shapes);
        for (PODVector<CollisionShape*>::Iterator i = shapes.Begin(); i != shapes.End(); ++i)
            (*i)->NotifyRigidBody();
    }
    
    int flags = body_->getCollisionFlags();
    if (mass_ > 0.0f)
        flags &= ~btCollisionObject::CF_STATIC_OBJECT;
    else
        flags |= btCollisionObject::CF_STATIC_OBJECT;
    body_->setCollisionFlags(flags);
    
    world->addRigidBody(body_, collisionLayer_, collisionMask_);
}

void RigidBody::ReleaseBody()
{
    if (body_)
    {
        if (physicsWorld_)
        {
            btDiscreteDynamicsWorld* world = physicsWorld_->GetWorld();
            world->removeRigidBody(body_);
        }
        
        delete body_;
        body_ = 0;
    }
}
