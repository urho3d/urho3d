//
// Copyright (c) 2008-2016 the Urho3D project.
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

#include "../Precompiled.h"

#include "../Core/Context.h"
#include "../Core/Profiler.h"
#include "../IO/Log.h"
#include "../IO/MemoryBuffer.h"
#include "../Physics/CollisionShape.h"
#include "../Physics/Constraint.h"
#include "../Physics/PhysicsUtils.h"
#include "../Physics/PhysicsWorld.h"
#include "../Physics/RigidBody.h"
#include "../Resource/ResourceCache.h"
#include "../Resource/ResourceEvents.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneEvents.h"
#include "../Scene/SmoothedTransform.h"

#include <Bullet/BulletDynamics/Dynamics/btDiscreteDynamicsWorld.h>
#include <Bullet/BulletDynamics/Dynamics/btRigidBody.h>
#include <Bullet/BulletCollision/CollisionShapes/btCompoundShape.h>

namespace Urho3D
{

static const float DEFAULT_MASS = 0.0f;
static const float DEFAULT_FRICTION = 0.5f;
static const float DEFAULT_RESTITUTION = 0.0f;
static const float DEFAULT_ROLLING_FRICTION = 0.0f;
static const unsigned DEFAULT_COLLISION_LAYER = 0x1;
static const unsigned DEFAULT_COLLISION_MASK = M_MAX_UNSIGNED;

static const char* collisionEventModeNames[] =
{
    "Never",
    "When Active",
    "Always",
    0
};

extern const char* PHYSICS_CATEGORY;

RigidBody::RigidBody(Context* context) :
    Component(context),
    body_(0),
    compoundShape_(0),
    shiftedCompoundShape_(0),
    gravityOverride_(Vector3::ZERO),
    centerOfMass_(Vector3::ZERO),
    mass_(DEFAULT_MASS),
    collisionLayer_(DEFAULT_COLLISION_LAYER),
    collisionMask_(DEFAULT_COLLISION_MASK),
    collisionEventMode_(COLLISION_ACTIVE),
    lastPosition_(Vector3::ZERO),
    lastRotation_(Quaternion::IDENTITY),
    kinematic_(false),
    trigger_(false),
    useGravity_(true),
    readdBody_(false),
    inWorld_(false),
    enableMassUpdate_(true),
    hasSimulated_(false)
{
    compoundShape_ = new btCompoundShape();
    shiftedCompoundShape_ = new btCompoundShape();
}

RigidBody::~RigidBody()
{
    ReleaseBody();

    if (physicsWorld_)
        physicsWorld_->RemoveRigidBody(this);

    delete compoundShape_;
    compoundShape_ = 0;
    delete shiftedCompoundShape_;
    shiftedCompoundShape_ = 0;
}

void RigidBody::RegisterObject(Context* context)
{
    context->RegisterFactory<RigidBody>(PHYSICS_CATEGORY);

    URHO3D_ACCESSOR_ATTRIBUTE("Is Enabled", IsEnabled, SetEnabled, bool, true, AM_DEFAULT);
    URHO3D_MIXED_ACCESSOR_ATTRIBUTE("Physics Rotation", GetRotation, SetRotation, Quaternion, Quaternion::IDENTITY, AM_FILE | AM_NOEDIT);
    URHO3D_MIXED_ACCESSOR_ATTRIBUTE("Physics Position", GetPosition, SetPosition, Vector3, Vector3::ZERO, AM_FILE | AM_NOEDIT);
    URHO3D_ATTRIBUTE("Mass", float, mass_, DEFAULT_MASS, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Friction", GetFriction, SetFriction, float, DEFAULT_FRICTION, AM_DEFAULT);
    URHO3D_MIXED_ACCESSOR_ATTRIBUTE("Anisotropic Friction", GetAnisotropicFriction, SetAnisotropicFriction, Vector3, Vector3::ONE,
        AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Rolling Friction", GetRollingFriction, SetRollingFriction, float, DEFAULT_ROLLING_FRICTION, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Restitution", GetRestitution, SetRestitution, float, DEFAULT_RESTITUTION, AM_DEFAULT);
    URHO3D_MIXED_ACCESSOR_ATTRIBUTE("Linear Velocity", GetLinearVelocity, SetLinearVelocity, Vector3, Vector3::ZERO,
        AM_DEFAULT | AM_LATESTDATA);
    URHO3D_MIXED_ACCESSOR_ATTRIBUTE("Angular Velocity", GetAngularVelocity, SetAngularVelocity, Vector3, Vector3::ZERO, AM_FILE);
    URHO3D_MIXED_ACCESSOR_ATTRIBUTE("Linear Factor", GetLinearFactor, SetLinearFactor, Vector3, Vector3::ONE, AM_DEFAULT);
    URHO3D_MIXED_ACCESSOR_ATTRIBUTE("Angular Factor", GetAngularFactor, SetAngularFactor, Vector3, Vector3::ONE, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Linear Damping", GetLinearDamping, SetLinearDamping, float, 0.0f, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Angular Damping", GetAngularDamping, SetAngularDamping, float, 0.0f, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Linear Rest Threshold", GetLinearRestThreshold, SetLinearRestThreshold, float, 0.8f, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Angular Rest Threshold", GetAngularRestThreshold, SetAngularRestThreshold, float, 1.0f, AM_DEFAULT);
    URHO3D_ATTRIBUTE("Collision Layer", int, collisionLayer_, DEFAULT_COLLISION_LAYER, AM_DEFAULT);
    URHO3D_ATTRIBUTE("Collision Mask", int, collisionMask_, DEFAULT_COLLISION_MASK, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Contact Threshold", GetContactProcessingThreshold, SetContactProcessingThreshold, float, BT_LARGE_FLOAT,
        AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("CCD Radius", GetCcdRadius, SetCcdRadius, float, 0.0f, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("CCD Motion Threshold", GetCcdMotionThreshold, SetCcdMotionThreshold, float, 0.0f, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Network Angular Velocity", GetNetAngularVelocityAttr, SetNetAngularVelocityAttr, PODVector<unsigned char>,
        Variant::emptyBuffer, AM_NET | AM_LATESTDATA | AM_NOEDIT);
    URHO3D_ENUM_ATTRIBUTE("Collision Event Mode", collisionEventMode_, collisionEventModeNames, COLLISION_ACTIVE, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Use Gravity", GetUseGravity, SetUseGravity, bool, true, AM_DEFAULT);
    URHO3D_ATTRIBUTE("Is Kinematic", bool, kinematic_, false, AM_DEFAULT);
    URHO3D_ATTRIBUTE("Is Trigger", bool, trigger_, false, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Gravity Override", GetGravityOverride, SetGravityOverride, Vector3, Vector3::ZERO, AM_DEFAULT);
}

void RigidBody::OnSetAttribute(const AttributeInfo& attr, const Variant& src)
{
    Serializable::OnSetAttribute(attr, src);

    // Change of any non-accessor attribute requires the rigid body to be re-added to the physics world
    if (!attr.accessor_)
        readdBody_ = true;
}

void RigidBody::ApplyAttributes()
{
    if (readdBody_)
        AddBodyToWorld();
}

void RigidBody::OnSetEnabled()
{
    bool enabled = IsEnabledEffective();

    if (enabled && !inWorld_)
        AddBodyToWorld();
    else if (!enabled && inWorld_)
        RemoveBodyFromWorld();
}

void RigidBody::getWorldTransform(btTransform& worldTrans) const
{
    // We may be in a pathological state where a RigidBody exists without a scene node when this callback is fired,
    // so check to be sure
    if (node_)
    {
        lastPosition_ = node_->GetWorldPosition();
        lastRotation_ = node_->GetWorldRotation();
        worldTrans.setOrigin(ToBtVector3(lastPosition_ + lastRotation_ * centerOfMass_));
        worldTrans.setRotation(ToBtQuaternion(lastRotation_));
    }

    hasSimulated_ = true;
}

void RigidBody::setWorldTransform(const btTransform& worldTrans)
{
    Quaternion newWorldRotation = ToQuaternion(worldTrans.getRotation());
    Vector3 newWorldPosition = ToVector3(worldTrans.getOrigin()) - newWorldRotation * centerOfMass_;
    RigidBody* parentRigidBody = 0;

    // It is possible that the RigidBody component has been kept alive via a shared pointer,
    // while its scene node has already been destroyed
    if (node_)
    {
        // If the rigid body is parented to another rigid body, can not set the transform immediately.
        // In that case store it to PhysicsWorld for delayed assignment
        Node* parent = node_->GetParent();
        if (parent != GetScene() && parent)
            parentRigidBody = parent->GetComponent<RigidBody>();

        if (!parentRigidBody)
            ApplyWorldTransform(newWorldPosition, newWorldRotation);
        else
        {
            DelayedWorldTransform delayed;
            delayed.rigidBody_ = this;
            delayed.parentRigidBody_ = parentRigidBody;
            delayed.worldPosition_ = newWorldPosition;
            delayed.worldRotation_ = newWorldRotation;
            physicsWorld_->AddDelayedWorldTransform(delayed);
        }

        MarkNetworkUpdate();
    }

    hasSimulated_ = true;
}

void RigidBody::DrawDebugGeometry(DebugRenderer* debug, bool depthTest)
{
    if (debug && physicsWorld_ && body_ && IsEnabledEffective())
    {
        physicsWorld_->SetDebugRenderer(debug);
        physicsWorld_->SetDebugDepthTest(depthTest);

        btDiscreteDynamicsWorld* world = physicsWorld_->GetWorld();
        world->debugDrawObject(body_->getWorldTransform(), shiftedCompoundShape_, IsActive() ? btVector3(1.0f, 1.0f, 1.0f) :
            btVector3(0.0f, 1.0f, 0.0f));

        physicsWorld_->SetDebugRenderer(0);
    }
}

void RigidBody::SetMass(float mass)
{
    mass = Max(mass, 0.0f);

    if (mass != mass_)
    {
        mass_ = mass;
        AddBodyToWorld();
        MarkNetworkUpdate();
    }
}

void RigidBody::SetPosition(const Vector3& position)
{
    if (body_)
    {
        btTransform& worldTrans = body_->getWorldTransform();
        worldTrans.setOrigin(ToBtVector3(position + ToQuaternion(worldTrans.getRotation()) * centerOfMass_));

        // When forcing the physics position, set also interpolated position so that there is no jitter
        // When not inside the simulation loop, this may lead to erratic movement of parented rigidbodies
        // so skip in that case. Exception made before first simulation tick so that interpolation position
        // of e.g. instantiated prefabs will be correct from the start
        if (!hasSimulated_ || physicsWorld_->IsSimulating())
        {
            btTransform interpTrans = body_->getInterpolationWorldTransform();
            interpTrans.setOrigin(worldTrans.getOrigin());
            body_->setInterpolationWorldTransform(interpTrans);
        }

        Activate();
        MarkNetworkUpdate();
    }
}

void RigidBody::SetRotation(const Quaternion& rotation)
{
    if (body_)
    {
        Vector3 oldPosition = GetPosition();
        btTransform& worldTrans = body_->getWorldTransform();
        worldTrans.setRotation(ToBtQuaternion(rotation));
        if (!centerOfMass_.Equals(Vector3::ZERO))
            worldTrans.setOrigin(ToBtVector3(oldPosition + rotation * centerOfMass_));

        if (!hasSimulated_ || physicsWorld_->IsSimulating())
        {
            btTransform interpTrans = body_->getInterpolationWorldTransform();
            interpTrans.setRotation(worldTrans.getRotation());
            if (!centerOfMass_.Equals(Vector3::ZERO))
                interpTrans.setOrigin(worldTrans.getOrigin());
            body_->setInterpolationWorldTransform(interpTrans);
        }
        
        body_->updateInertiaTensor();

        Activate();
        MarkNetworkUpdate();
    }
}

void RigidBody::SetTransform(const Vector3& position, const Quaternion& rotation)
{
    if (body_)
    {
        btTransform& worldTrans = body_->getWorldTransform();
        worldTrans.setRotation(ToBtQuaternion(rotation));
        worldTrans.setOrigin(ToBtVector3(position + rotation * centerOfMass_));

        if (!hasSimulated_ || physicsWorld_->IsSimulating())
        {
            btTransform interpTrans = body_->getInterpolationWorldTransform();
            interpTrans.setOrigin(worldTrans.getOrigin());
            interpTrans.setRotation(worldTrans.getRotation());
            body_->setInterpolationWorldTransform(interpTrans);
        }

        body_->updateInertiaTensor();

        Activate();
        MarkNetworkUpdate();
    }
}

void RigidBody::SetLinearVelocity(const Vector3& velocity)
{
    if (body_)
    {
        body_->setLinearVelocity(ToBtVector3(velocity));
        if (velocity != Vector3::ZERO)
            Activate();
        MarkNetworkUpdate();
    }
}

void RigidBody::SetLinearFactor(const Vector3& factor)
{
    if (body_)
    {
        body_->setLinearFactor(ToBtVector3(factor));
        MarkNetworkUpdate();
    }
}

void RigidBody::SetLinearRestThreshold(float threshold)
{
    if (body_)
    {
        body_->setSleepingThresholds(threshold, body_->getAngularSleepingThreshold());
        MarkNetworkUpdate();
    }
}

void RigidBody::SetLinearDamping(float damping)
{
    if (body_)
    {
        body_->setDamping(damping, body_->getAngularDamping());
        MarkNetworkUpdate();
    }
}

void RigidBody::SetAngularVelocity(const Vector3& velocity)
{
    if (body_)
    {
        body_->setAngularVelocity(ToBtVector3(velocity));
        if (velocity != Vector3::ZERO)
            Activate();
        MarkNetworkUpdate();
    }
}

void RigidBody::SetAngularFactor(const Vector3& factor)
{
    if (body_)
    {
        body_->setAngularFactor(ToBtVector3(factor));
        MarkNetworkUpdate();
    }
}

void RigidBody::SetAngularRestThreshold(float threshold)
{
    if (body_)
    {
        body_->setSleepingThresholds(body_->getLinearSleepingThreshold(), threshold);
        MarkNetworkUpdate();
    }
}

void RigidBody::SetAngularDamping(float damping)
{
    if (body_)
    {
        body_->setDamping(body_->getLinearDamping(), damping);
        MarkNetworkUpdate();
    }
}

void RigidBody::SetFriction(float friction)
{
    if (body_)
    {
        body_->setFriction(friction);
        MarkNetworkUpdate();
    }
}

void RigidBody::SetAnisotropicFriction(const Vector3& friction)
{
    if (body_)
    {
        body_->setAnisotropicFriction(ToBtVector3(friction));
        MarkNetworkUpdate();
    }
}

void RigidBody::SetRollingFriction(float friction)
{
    if (body_)
    {
        body_->setRollingFriction(friction);
        MarkNetworkUpdate();
    }
}

void RigidBody::SetRestitution(float restitution)
{
    if (body_)
    {
        body_->setRestitution(restitution);
        MarkNetworkUpdate();
    }
}

void RigidBody::SetContactProcessingThreshold(float threshold)
{
    if (body_)
    {
        body_->setContactProcessingThreshold(threshold);
        MarkNetworkUpdate();
    }
}

void RigidBody::SetCcdRadius(float radius)
{
    radius = Max(radius, 0.0f);
    if (body_)
    {
        body_->setCcdSweptSphereRadius(radius);
        MarkNetworkUpdate();
    }
}

void RigidBody::SetCcdMotionThreshold(float threshold)
{
    threshold = Max(threshold, 0.0f);
    if (body_)
    {
        body_->setCcdMotionThreshold(threshold);
        MarkNetworkUpdate();
    }
}

void RigidBody::SetUseGravity(bool enable)
{
    if (enable != useGravity_)
    {
        useGravity_ = enable;
        UpdateGravity();
        MarkNetworkUpdate();
    }
}

void RigidBody::SetGravityOverride(const Vector3& gravity)
{
    if (gravity != gravityOverride_)
    {
        gravityOverride_ = gravity;
        UpdateGravity();
        MarkNetworkUpdate();
    }
}

void RigidBody::SetKinematic(bool enable)
{
    if (enable != kinematic_)
    {
        kinematic_ = enable;
        AddBodyToWorld();
        MarkNetworkUpdate();
    }
}

void RigidBody::SetTrigger(bool enable)
{
    if (enable != trigger_)
    {
        trigger_ = enable;
        AddBodyToWorld();
        MarkNetworkUpdate();
    }
}

void RigidBody::SetCollisionLayer(unsigned layer)
{
    if (layer != collisionLayer_)
    {
        collisionLayer_ = layer;
        AddBodyToWorld();
        MarkNetworkUpdate();
    }
}

void RigidBody::SetCollisionMask(unsigned mask)
{
    if (mask != collisionMask_)
    {
        collisionMask_ = mask;
        AddBodyToWorld();
        MarkNetworkUpdate();
    }
}

void RigidBody::SetCollisionLayerAndMask(unsigned layer, unsigned mask)
{
    if (layer != collisionLayer_ || mask != collisionMask_)
    {
        collisionLayer_ = layer;
        collisionMask_ = mask;
        AddBodyToWorld();
        MarkNetworkUpdate();
    }
}

void RigidBody::SetCollisionEventMode(CollisionEventMode mode)
{
    collisionEventMode_ = mode;
    MarkNetworkUpdate();
}

void RigidBody::ApplyForce(const Vector3& force)
{
    if (body_ && force != Vector3::ZERO)
    {
        Activate();
        body_->applyCentralForce(ToBtVector3(force));
    }
}

void RigidBody::ApplyForce(const Vector3& force, const Vector3& position)
{
    if (body_ && force != Vector3::ZERO)
    {
        Activate();
        body_->applyForce(ToBtVector3(force), ToBtVector3(position - centerOfMass_));
    }
}

void RigidBody::ApplyTorque(const Vector3& torque)
{
    if (body_ && torque != Vector3::ZERO)
    {
        Activate();
        body_->applyTorque(ToBtVector3(torque));
    }
}

void RigidBody::ApplyImpulse(const Vector3& impulse)
{
    if (body_ && impulse != Vector3::ZERO)
    {
        Activate();
        body_->applyCentralImpulse(ToBtVector3(impulse));
    }
}

void RigidBody::ApplyImpulse(const Vector3& impulse, const Vector3& position)
{
    if (body_ && impulse != Vector3::ZERO)
    {
        Activate();
        body_->applyImpulse(ToBtVector3(impulse), ToBtVector3(position - centerOfMass_));
    }
}

void RigidBody::ApplyTorqueImpulse(const Vector3& torque)
{
    if (body_ && torque != Vector3::ZERO)
    {
        Activate();
        body_->applyTorqueImpulse(ToBtVector3(torque));
    }
}

void RigidBody::ResetForces()
{
    if (body_)
        body_->clearForces();
}

void RigidBody::Activate()
{
    if (body_ && mass_ > 0.0f)
        body_->activate(true);
}

void RigidBody::ReAddBodyToWorld()
{
    if (body_ && inWorld_)
        AddBodyToWorld();
}

void RigidBody::DisableMassUpdate()
{
    enableMassUpdate_ = false;
}

void RigidBody::EnableMassUpdate()
{
    if (!enableMassUpdate_)
    {
        enableMassUpdate_ = true;
        UpdateMass();
    }
}

Vector3 RigidBody::GetPosition() const
{
    if (body_)
    {
        const btTransform& transform = body_->getWorldTransform();
        return ToVector3(transform.getOrigin()) - ToQuaternion(transform.getRotation()) * centerOfMass_;
    }
    else
        return Vector3::ZERO;
}

Quaternion RigidBody::GetRotation() const
{
    return body_ ? ToQuaternion(body_->getWorldTransform().getRotation()) : Quaternion::IDENTITY;
}

Vector3 RigidBody::GetLinearVelocity() const
{
    return body_ ? ToVector3(body_->getLinearVelocity()) : Vector3::ZERO;
}

Vector3 RigidBody::GetLinearFactor() const
{
    return body_ ? ToVector3(body_->getLinearFactor()) : Vector3::ZERO;
}

Vector3 RigidBody::GetVelocityAtPoint(const Vector3& position) const
{
    return body_ ? ToVector3(body_->getVelocityInLocalPoint(ToBtVector3(position - centerOfMass_))) : Vector3::ZERO;
}

float RigidBody::GetLinearRestThreshold() const
{
    return body_ ? body_->getLinearSleepingThreshold() : 0.0f;
}

float RigidBody::GetLinearDamping() const
{
    return body_ ? body_->getLinearDamping() : 0.0f;
}

Vector3 RigidBody::GetAngularVelocity() const
{
    return body_ ? ToVector3(body_->getAngularVelocity()) : Vector3::ZERO;
}

Vector3 RigidBody::GetAngularFactor() const
{
    return body_ ? ToVector3(body_->getAngularFactor()) : Vector3::ZERO;
}

float RigidBody::GetAngularRestThreshold() const
{
    return body_ ? body_->getAngularSleepingThreshold() : 0.0f;
}

float RigidBody::GetAngularDamping() const
{
    return body_ ? body_->getAngularDamping() : 0.0f;
}

float RigidBody::GetFriction() const
{
    return body_ ? body_->getFriction() : 0.0f;
}

Vector3 RigidBody::GetAnisotropicFriction() const
{
    return body_ ? ToVector3(body_->getAnisotropicFriction()) : Vector3::ZERO;
}

float RigidBody::GetRollingFriction() const
{
    return body_ ? body_->getRollingFriction() : 0.0f;
}

float RigidBody::GetRestitution() const
{
    return body_ ? body_->getRestitution() : 0.0f;
}

float RigidBody::GetContactProcessingThreshold() const
{
    return body_ ? body_->getContactProcessingThreshold() : 0.0f;
}

float RigidBody::GetCcdRadius() const
{
    return body_ ? body_->getCcdSweptSphereRadius() : 0.0f;
}

float RigidBody::GetCcdMotionThreshold() const
{
    return body_ ? body_->getCcdMotionThreshold() : 0.0f;
}

bool RigidBody::IsActive() const
{
    return body_ ? body_->isActive() : false;
}

void RigidBody::GetCollidingBodies(PODVector<RigidBody*>& result) const
{
    if (physicsWorld_)
        physicsWorld_->GetCollidingBodies(result, this);
    else
        result.Clear();
}

void RigidBody::ApplyWorldTransform(const Vector3& newWorldPosition, const Quaternion& newWorldRotation)
{
    // In case of holding an extra reference to the RigidBody, this could be called in a situation
    // where node is already null
    if (!node_ || !physicsWorld_)
        return;

    physicsWorld_->SetApplyingTransforms(true);

    // Apply transform to the SmoothedTransform component instead of node transform if available
    if (smoothedTransform_)
    {
        smoothedTransform_->SetTargetWorldPosition(newWorldPosition);
        smoothedTransform_->SetTargetWorldRotation(newWorldRotation);
        lastPosition_ = newWorldPosition;
        lastRotation_ = newWorldRotation;
    }
    else
    {
        node_->SetWorldPosition(newWorldPosition);
        node_->SetWorldRotation(newWorldRotation);
        lastPosition_ = node_->GetWorldPosition();
        lastRotation_ = node_->GetWorldRotation();
    }

    physicsWorld_->SetApplyingTransforms(false);
}

void RigidBody::UpdateMass()
{
    if (!body_ || !enableMassUpdate_)
        return;

    btTransform principal;
    principal.setRotation(btQuaternion::getIdentity());
    principal.setOrigin(btVector3(0.0f, 0.0f, 0.0f));

    // Calculate center of mass shift from all the collision shapes
    unsigned numShapes = (unsigned)compoundShape_->getNumChildShapes();
    if (numShapes)
    {
        PODVector<float> masses(numShapes);
        for (unsigned i = 0; i < numShapes; ++i)
        {
            // The actual mass does not matter, divide evenly between child shapes
            masses[i] = 1.0f;
        }

        btVector3 inertia(0.0f, 0.0f, 0.0f);
        compoundShape_->calculatePrincipalAxisTransform(&masses[0], principal, inertia);
    }

    // Add child shapes to shifted compound shape with adjusted offset
    while (shiftedCompoundShape_->getNumChildShapes())
        shiftedCompoundShape_->removeChildShapeByIndex(shiftedCompoundShape_->getNumChildShapes() - 1);
    for (unsigned i = 0; i < numShapes; ++i)
    {
        btTransform adjusted = compoundShape_->getChildTransform(i);
        adjusted.setOrigin(adjusted.getOrigin() - principal.getOrigin());
        shiftedCompoundShape_->addChildShape(adjusted, compoundShape_->getChildShape(i));
    }

    // If shifted compound shape has only one child with no offset/rotation, use the child shape
    // directly as the rigid body collision shape for better collision detection performance
    bool useCompound = !numShapes || numShapes > 1;
    if (!useCompound)
    {
        const btTransform& childTransform = shiftedCompoundShape_->getChildTransform(0);
        if (!ToVector3(childTransform.getOrigin()).Equals(Vector3::ZERO) ||
            !ToQuaternion(childTransform.getRotation()).Equals(Quaternion::IDENTITY))
            useCompound = true;
    }
    body_->setCollisionShape(useCompound ? shiftedCompoundShape_ : shiftedCompoundShape_->getChildShape(0));

    // If we have one shape and this is a triangle mesh, we use a custom material callback in order to adjust internal edges
    if (!useCompound && body_->getCollisionShape()->getShapeType() == SCALED_TRIANGLE_MESH_SHAPE_PROXYTYPE &&
        physicsWorld_->GetInternalEdge())
        body_->setCollisionFlags(body_->getCollisionFlags() | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);
    else
        body_->setCollisionFlags(body_->getCollisionFlags() & ~btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);

    // Reapply rigid body position with new center of mass shift
    Vector3 oldPosition = GetPosition();
    centerOfMass_ = ToVector3(principal.getOrigin());
    SetPosition(oldPosition);

    // Calculate final inertia
    btVector3 localInertia(0.0f, 0.0f, 0.0f);
    if (mass_ > 0.0f)
        shiftedCompoundShape_->calculateLocalInertia(mass_, localInertia);
    body_->setMassProps(mass_, localInertia);
    body_->updateInertiaTensor();

    // Reapply constraint positions for new center of mass shift
    if (node_)
    {
        for (PODVector<Constraint*>::Iterator i = constraints_.Begin(); i != constraints_.End(); ++i)
            (*i)->ApplyFrames();
    }
}

void RigidBody::UpdateGravity()
{
    if (physicsWorld_ && body_)
    {
        btDiscreteDynamicsWorld* world = physicsWorld_->GetWorld();

        int flags = body_->getFlags();
        if (useGravity_ && gravityOverride_ == Vector3::ZERO)
            flags &= ~BT_DISABLE_WORLD_GRAVITY;
        else
            flags |= BT_DISABLE_WORLD_GRAVITY;
        body_->setFlags(flags);

        if (useGravity_)
        {
            // If override vector is zero, use world's gravity
            if (gravityOverride_ == Vector3::ZERO)
                body_->setGravity(world->getGravity());
            else
                body_->setGravity(ToBtVector3(gravityOverride_));
        }
        else
            body_->setGravity(btVector3(0.0f, 0.0f, 0.0f));
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

void RigidBody::AddConstraint(Constraint* constraint)
{
    constraints_.Push(constraint);
}

void RigidBody::RemoveConstraint(Constraint* constraint)
{
    constraints_.Remove(constraint);
    // A constraint being removed should possibly cause the object to eg. start falling, so activate
    Activate();
}

void RigidBody::ReleaseBody()
{
    if (body_)
    {
        // Release all constraints which refer to this body
        // Make a copy for iteration
        PODVector<Constraint*> constraints = constraints_;
        for (PODVector<Constraint*>::Iterator i = constraints.Begin(); i != constraints.End(); ++i)
            (*i)->ReleaseConstraint();

        RemoveBodyFromWorld();

        delete body_;
        body_ = 0;
    }
}

void RigidBody::OnMarkedDirty(Node* node)
{
    // If node transform changes, apply it back to the physics transform. However, do not do this when a SmoothedTransform
    // is in use, because in that case the node transform will be constantly updated into smoothed, possibly non-physical
    // states; rather follow the SmoothedTransform target transform directly
    // Also, for kinematic objects Bullet asks the position from us, so we do not need to apply ourselves
    // (exception: initial setting of transform)
    if ((!kinematic_ || !hasSimulated_) && (!physicsWorld_ || !physicsWorld_->IsApplyingTransforms()) && !smoothedTransform_)
    {
        // Physics operations are not safe from worker threads
        Scene* scene = GetScene();
        if (scene && scene->IsThreadedUpdate())
        {
            scene->DelayedMarkedDirty(this);
            return;
        }

        // Check if transform has changed from the last one set in ApplyWorldTransform()
        Vector3 newPosition = node_->GetWorldPosition();
        Quaternion newRotation = node_->GetWorldRotation();

        if (!newRotation.Equals(lastRotation_))
        {
            lastRotation_ = newRotation;
            SetRotation(newRotation);
        }
        if (!newPosition.Equals(lastPosition_))
        {
            lastPosition_ = newPosition;
            SetPosition(newPosition);
        }
    }
}

void RigidBody::OnNodeSet(Node* node)
{
    if (node)
        node->AddListener(this);
}

void RigidBody::OnSceneSet(Scene* scene)
{
    if (scene)
    {
        if (scene == node_)
            URHO3D_LOGWARNING(GetTypeName() + " should not be created to the root scene node");

        physicsWorld_ = scene->GetOrCreateComponent<PhysicsWorld>();
        physicsWorld_->AddRigidBody(this);

        AddBodyToWorld();
    }
    else
    {
        ReleaseBody();

        if (physicsWorld_)
            physicsWorld_->RemoveRigidBody(this);
    }
}

void RigidBody::AddBodyToWorld()
{
    if (!physicsWorld_)
        return;

    URHO3D_PROFILE(AddBodyToWorld);

    if (mass_ < 0.0f)
        mass_ = 0.0f;

    if (body_)
        RemoveBodyFromWorld();
    else
    {
        // Correct inertia will be calculated below
        btVector3 localInertia(0.0f, 0.0f, 0.0f);
        body_ = new btRigidBody(mass_, this, shiftedCompoundShape_, localInertia);
        body_->setUserPointer(this);

        // Check for existence of the SmoothedTransform component, which should be created by now in network client mode.
        // If it exists, subscribe to its change events
        smoothedTransform_ = GetComponent<SmoothedTransform>();
        if (smoothedTransform_)
        {
            SubscribeToEvent(smoothedTransform_, E_TARGETPOSITION, URHO3D_HANDLER(RigidBody, HandleTargetPosition));
            SubscribeToEvent(smoothedTransform_, E_TARGETROTATION, URHO3D_HANDLER(RigidBody, HandleTargetRotation));
        }

        // Check if CollisionShapes already exist in the node and add them to the compound shape.
        // Do not update mass yet, but do it once all shapes have been added
        PODVector<CollisionShape*> shapes;
        node_->GetComponents<CollisionShape>(shapes);
        for (PODVector<CollisionShape*>::Iterator i = shapes.Begin(); i != shapes.End(); ++i)
            (*i)->NotifyRigidBody(false);

        // Check if this node contains Constraint components that were waiting for the rigid body to be created, and signal them
        // to create themselves now
        PODVector<Constraint*> constraints;
        node_->GetComponents<Constraint>(constraints);
        for (PODVector<Constraint*>::Iterator i = constraints.Begin(); i != constraints.End(); ++i)
            (*i)->CreateConstraint();
    }

    UpdateMass();
    UpdateGravity();

    int flags = body_->getCollisionFlags();
    if (trigger_)
        flags |= btCollisionObject::CF_NO_CONTACT_RESPONSE;
    else
        flags &= ~btCollisionObject::CF_NO_CONTACT_RESPONSE;
    if (kinematic_)
        flags |= btCollisionObject::CF_KINEMATIC_OBJECT;
    else
        flags &= ~btCollisionObject::CF_KINEMATIC_OBJECT;
    body_->setCollisionFlags(flags);
    body_->forceActivationState(kinematic_ ? DISABLE_DEACTIVATION : ISLAND_SLEEPING);

    if (!IsEnabledEffective())
        return;

    btDiscreteDynamicsWorld* world = physicsWorld_->GetWorld();
    world->addRigidBody(body_, (short)collisionLayer_, (short)collisionMask_);
    inWorld_ = true;
    readdBody_ = false;
    hasSimulated_ = false;

    if (mass_ > 0.0f)
        Activate();
    else
    {
        SetLinearVelocity(Vector3::ZERO);
        SetAngularVelocity(Vector3::ZERO);
    }
}

void RigidBody::RemoveBodyFromWorld()
{
    if (physicsWorld_ && body_ && inWorld_)
    {
        btDiscreteDynamicsWorld* world = physicsWorld_->GetWorld();
        world->removeRigidBody(body_);
        inWorld_ = false;
    }
}

void RigidBody::HandleTargetPosition(StringHash eventType, VariantMap& eventData)
{
    // Copy the smoothing target position to the rigid body
    if (!physicsWorld_ || !physicsWorld_->IsApplyingTransforms())
        SetPosition(static_cast<SmoothedTransform*>(GetEventSender())->GetTargetWorldPosition());
}

void RigidBody::HandleTargetRotation(StringHash eventType, VariantMap& eventData)
{
    // Copy the smoothing target rotation to the rigid body
    if (!physicsWorld_ || !physicsWorld_->IsApplyingTransforms())
        SetRotation(static_cast<SmoothedTransform*>(GetEventSender())->GetTargetWorldRotation());
}

}
