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

#pragma once

#include "../IO/VectorBuffer.h"
#include "../Scene/Component.h"

#include <Bullet/LinearMath/btMotionState.h>

class btCompoundShape;
class btRigidBody;

namespace Urho3D
{

class CollisionShape;
class Constraint;
class PhysicsWorld;
class SmoothedTransform;

/// Rigid body collision event signaling mode.
enum CollisionEventMode
{
    COLLISION_NEVER = 0,
    COLLISION_ACTIVE,
    COLLISION_ALWAYS
};

/// Physics rigid body component.
class URHO3D_API RigidBody : public Component, public btMotionState
{
    URHO3D_OBJECT(RigidBody, Component);

public:
    /// Construct.
    RigidBody(Context* context);
    /// Destruct. Free the rigid body and geometries.
    virtual ~RigidBody();
    /// Register object factory.
    static void RegisterObject(Context* context);

    /// Handle attribute write access.
    virtual void OnSetAttribute(const AttributeInfo& attr, const Variant& src);
    /// Apply attribute changes that can not be applied immediately. Called after scene load or a network update.
    virtual void ApplyAttributes();
    /// Handle enabled/disabled state change.
    virtual void OnSetEnabled();
    /// Return initial world transform to Bullet.
    virtual void getWorldTransform(btTransform& worldTrans) const;
    /// Update world transform from Bullet.
    virtual void setWorldTransform(const btTransform& worldTrans);
    /// Visualize the component as debug geometry.
    virtual void DrawDebugGeometry(DebugRenderer* debug, bool depthTest);

    /// Set mass. Zero mass makes the body static.
    void SetMass(float mass);
    /// Set rigid body position in world space.
    void SetPosition(const Vector3& position);
    /// Set rigid body rotation in world space.
    void SetRotation(const Quaternion& rotation);
    /// Set rigid body position and rotation in world space as an atomic operation.
    void SetTransform(const Vector3& position, const Quaternion& rotation);
    /// Set linear velocity.
    void SetLinearVelocity(const Vector3& velocity);
    /// Set linear degrees of freedom. Use 1 to enable an axis or 0 to disable. Default is all axes enabled (1, 1, 1).
    void SetLinearFactor(const Vector3& factor);
    /// Set linear velocity deactivation threshold.
    void SetLinearRestThreshold(float threshold);
    /// Set linear velocity damping factor.
    void SetLinearDamping(float damping);
    /// Set angular velocity.
    void SetAngularVelocity(const Vector3& angularVelocity);
    /// Set angular degrees of freedom. Use 1 to enable an axis or 0 to disable. Default is all axes enabled (1, 1, 1).
    void SetAngularFactor(const Vector3& factor);
    /// Set angular velocity deactivation threshold.
    void SetAngularRestThreshold(float threshold);
    /// Set angular velocity damping factor.
    void SetAngularDamping(float factor);
    /// Set friction coefficient.
    void SetFriction(float friction);
    /// Set anisotropic friction.
    void SetAnisotropicFriction(const Vector3& friction);
    /// Set rolling friction coefficient.
    void SetRollingFriction(float friction);
    /// Set restitution coefficient.
    void SetRestitution(float restitution);
    /// Set contact processing threshold.
    void SetContactProcessingThreshold(float threshold);
    /// Set continuous collision detection swept sphere radius.
    void SetCcdRadius(float radius);
    /// Set continuous collision detection motion-per-simulation-step threshold. 0 disables, which is the default.
    void SetCcdMotionThreshold(float threshold);
    /// Set whether gravity is applied to rigid body.
    void SetUseGravity(bool enable);
    /// Set gravity override. If zero, uses physics world's gravity.
    void SetGravityOverride(const Vector3& gravity);
    /// Set rigid body kinematic mode. In kinematic mode forces are not applied to the rigid body.
    void SetKinematic(bool enable);
    /// Set rigid body trigger mode. In trigger mode collisions are reported but do not apply forces.
    void SetTrigger(bool enable);
    /// Set collision layer.
    void SetCollisionLayer(unsigned layer);
    /// Set collision mask.
    void SetCollisionMask(unsigned mask);
    /// Set collision group and mask.
    void SetCollisionLayerAndMask(unsigned layer, unsigned mask);
    /// Set collision event signaling mode. Default is to signal when rigid bodies are active.
    void SetCollisionEventMode(CollisionEventMode mode);
    /// Apply force to center of mass.
    void ApplyForce(const Vector3& force);
    /// Apply force at local position.
    void ApplyForce(const Vector3& force, const Vector3& position);
    /// Apply torque.
    void ApplyTorque(const Vector3& torque);
    /// Apply impulse to center of mass.
    void ApplyImpulse(const Vector3& impulse);
    /// Apply impulse at local position.
    void ApplyImpulse(const Vector3& impulse, const Vector3& position);
    /// Apply torque impulse.
    void ApplyTorqueImpulse(const Vector3& torque);
    /// Reset accumulated forces.
    void ResetForces();
    /// Activate rigid body if it was resting.
    void Activate();
    /// Readd rigid body to the physics world to clean up internal state like stale contacts.
    void ReAddBodyToWorld();
    /// Disable mass update. Call this to optimize performance when adding or editing multiple collision shapes in the same node.
    void DisableMassUpdate();
    /// Re-enable mass update and recalculate the mass/inertia by calling UpdateMass(). Call when collision shape changes are finished.
    void EnableMassUpdate();

    /// Return physics world.
    PhysicsWorld* GetPhysicsWorld() const { return physicsWorld_; }

    /// Return Bullet rigid body.
    btRigidBody* GetBody() const { return body_; }

    /// Return Bullet compound collision shape.
    btCompoundShape* GetCompoundShape() const { return compoundShape_; }

    /// Return mass.
    float GetMass() const { return mass_; }

    /// Return rigid body position in world space.
    Vector3 GetPosition() const;
    /// Return rigid body rotation in world space.
    Quaternion GetRotation() const;
    /// Return linear velocity.
    Vector3 GetLinearVelocity() const;
    /// Return linear degrees of freedom.
    Vector3 GetLinearFactor() const;
    /// Return linear velocity at local point.
    Vector3 GetVelocityAtPoint(const Vector3& position) const;
    /// Return linear velocity deactivation threshold.
    float GetLinearRestThreshold() const;
    /// Return linear velocity damping factor.
    float GetLinearDamping() const;
    /// Return angular velocity.
    Vector3 GetAngularVelocity() const;
    /// Return angular degrees of freedom.
    Vector3 GetAngularFactor() const;
    /// Return angular velocity deactivation threshold.
    float GetAngularRestThreshold() const;
    /// Return angular velocity damping factor.
    float GetAngularDamping() const;
    /// Return friction coefficient.
    float GetFriction() const;
    /// Return anisotropic friction.
    Vector3 GetAnisotropicFriction() const;
    /// Return rolling friction coefficient.
    float GetRollingFriction() const;
    /// Return restitution coefficient.
    float GetRestitution() const;
    /// Return contact processing threshold.
    float GetContactProcessingThreshold() const;
    /// Return continuous collision detection swept sphere radius.
    float GetCcdRadius() const;
    /// Return continuous collision detection motion-per-simulation-step threshold.
    float GetCcdMotionThreshold() const;

    /// Return whether rigid body uses gravity.
    bool GetUseGravity() const { return useGravity_; }

    /// Return gravity override. If zero (default), uses the physics world's gravity.
    const Vector3& GetGravityOverride() const { return gravityOverride_; }

    /// Return center of mass offset.
    const Vector3& GetCenterOfMass() const { return centerOfMass_; }

    /// Return kinematic mode flag.
    bool IsKinematic() const { return kinematic_; }

    /// Return whether this RigidBody is acting as a trigger.
    bool IsTrigger() const { return trigger_; }

    /// Return whether rigid body is active (not sleeping.)
    bool IsActive() const;

    /// Return collision layer.
    unsigned GetCollisionLayer() const { return collisionLayer_; }

    /// Return collision mask.
    unsigned GetCollisionMask() const { return collisionMask_; }

    /// Return collision event signaling mode.
    CollisionEventMode GetCollisionEventMode() const { return collisionEventMode_; }

    /// Return colliding rigid bodies from the last simulation step. Only returns collisions that were sent as events (depends on collision event mode) and excludes e.g. static-static collisions.
    void GetCollidingBodies(PODVector<RigidBody*>& result) const;

    /// Apply new world transform after a simulation step. Called internally.
    void ApplyWorldTransform(const Vector3& newWorldPosition, const Quaternion& newWorldRotation);
    /// Update mass and inertia to the Bullet rigid body.
    void UpdateMass();
    /// Update gravity parameters to the Bullet rigid body.
    void UpdateGravity();
    /// Set network angular velocity attribute.
    void SetNetAngularVelocityAttr(const PODVector<unsigned char>& value);
    /// Return network angular velocity attribute.
    const PODVector<unsigned char>& GetNetAngularVelocityAttr() const;
    /// Add a constraint that refers to this rigid body.
    void AddConstraint(Constraint* constraint);
    /// Remove a constraint that refers to this rigid body.
    void RemoveConstraint(Constraint* constraint);
    /// Remove the rigid body.
    void ReleaseBody();

protected:
    /// Handle node being assigned.
    virtual void OnNodeSet(Node* node);
    /// Handle scene being assigned.
    virtual void OnSceneSet(Scene* scene);
    /// Handle node transform being dirtied.
    virtual void OnMarkedDirty(Node* node);

private:
    /// Create the rigid body, or re-add to the physics world with changed flags. Calls UpdateMass().
    void AddBodyToWorld();
    /// Remove the rigid body from the physics world.
    void RemoveBodyFromWorld();
    /// Handle SmoothedTransform target position update.
    void HandleTargetPosition(StringHash eventType, VariantMap& eventData);
    /// Handle SmoothedTransform target rotation update.
    void HandleTargetRotation(StringHash eventType, VariantMap& eventData);

    /// Bullet rigid body.
    btRigidBody* body_;
    /// Bullet compound collision shape.
    btCompoundShape* compoundShape_;
    /// Compound collision shape with center of mass offset applied.
    btCompoundShape* shiftedCompoundShape_;
    /// Physics world.
    WeakPtr<PhysicsWorld> physicsWorld_;
    /// Smoothed transform, if has one.
    WeakPtr<SmoothedTransform> smoothedTransform_;
    /// Constraints that refer to this rigid body.
    PODVector<Constraint*> constraints_;
    /// Gravity override vector.
    Vector3 gravityOverride_;
    /// Center of mass offset.
    Vector3 centerOfMass_;
    /// Mass.
    float mass_;
    /// Attribute buffer for network replication.
    mutable VectorBuffer attrBuffer_;
    /// Collision layer.
    unsigned collisionLayer_;
    /// Collision mask.
    unsigned collisionMask_;
    /// Collision event signaling mode.
    CollisionEventMode collisionEventMode_;
    /// Last interpolated position from the simulation.
    mutable Vector3 lastPosition_;
    /// Last interpolated rotation from the simulation.
    mutable Quaternion lastRotation_;
    /// Kinematic flag.
    bool kinematic_;
    /// Trigger flag.
    bool trigger_;
    /// Use gravity flag.
    bool useGravity_;
    /// Readd body to world flag.
    bool readdBody_;
    /// Body exists in world flag.
    bool inWorld_;
    /// Mass update enable flag.
    bool enableMassUpdate_;
    /// Internal flag whether has simulated at least once.
    mutable bool hasSimulated_;
};

}
