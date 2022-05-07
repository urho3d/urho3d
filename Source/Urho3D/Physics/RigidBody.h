// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

/// \file

#pragma once

#include "../IO/VectorBuffer.h"
#include "../Scene/Component.h"

#include <Bullet/LinearMath/btMotionState.h>

#include <memory>

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
    explicit RigidBody(Context* context);
    /// Destruct. Free the rigid body and geometries.
    ~RigidBody() override;
    /// Register object factory.
    /// @nobind
    static void RegisterObject(Context* context);

    /// Apply attribute changes that can not be applied immediately. Called after scene load or a network update.
    void ApplyAttributes() override;
    /// Handle enabled/disabled state change.
    void OnSetEnabled() override;
    /// Return initial world transform to Bullet.
    /// @nobind
    void getWorldTransform(btTransform& worldTrans) const override;
    /// Update world transform from Bullet.
    /// @nobind
    void setWorldTransform(const btTransform& worldTrans) override;
    /// Visualize the component as debug geometry.
    void DrawDebugGeometry(DebugRenderer* debug, bool depthTest) override;

    /// Set mass. Zero mass makes the body static.
    /// @property
    void SetMass(float mass);
    /// Set rigid body position in world space.
    /// @property
    void SetPosition(const Vector3& position);
    /// Set rigid body rotation in world space.
    /// @property
    void SetRotation(const Quaternion& rotation);
    /// Set rigid body position and rotation in world space as an atomic operation.
    void SetTransform(const Vector3& position, const Quaternion& rotation);
    /// Set linear velocity.
    /// @property
    void SetLinearVelocity(const Vector3& velocity);
    /// Set linear degrees of freedom. Use 1 to enable an axis or 0 to disable. Default is all axes enabled (1, 1, 1).
    /// @property
    void SetLinearFactor(const Vector3& factor);
    /// Set linear velocity deactivation threshold.
    /// @property
    void SetLinearRestThreshold(float threshold);
    /// Set linear velocity damping factor.
    /// @property
    void SetLinearDamping(float damping);
    /// Set angular velocity.
    /// @property
    void SetAngularVelocity(const Vector3& velocity);
    /// Set angular degrees of freedom. Use 1 to enable an axis or 0 to disable. Default is all axes enabled (1, 1, 1).
    /// @property
    void SetAngularFactor(const Vector3& factor);
    /// Set angular velocity deactivation threshold.
    /// @property
    void SetAngularRestThreshold(float threshold);
    /// Set angular velocity damping factor.
    /// @property
    void SetAngularDamping(float damping);
    /// Set friction coefficient.
    /// @property
    void SetFriction(float friction);
    /// Set anisotropic friction.
    /// @property
    void SetAnisotropicFriction(const Vector3& friction);
    /// Set rolling friction coefficient.
    /// @property
    void SetRollingFriction(float friction);
    /// Set restitution coefficient.
    /// @property
    void SetRestitution(float restitution);
    /// Set contact processing threshold.
    /// @property
    void SetContactProcessingThreshold(float threshold);
    /// Set continuous collision detection swept sphere radius.
    /// @property
    void SetCcdRadius(float radius);
    /// Set continuous collision detection motion-per-simulation-step threshold. 0 disables, which is the default.
    /// @property
    void SetCcdMotionThreshold(float threshold);
    /// Set whether gravity is applied to rigid body.
    /// @property
    void SetUseGravity(bool enable);
    /// Set gravity override. If zero, uses physics world's gravity.
    /// @property
    void SetGravityOverride(const Vector3& gravity);
    /// Set rigid body kinematic mode. In kinematic mode forces are not applied to the rigid body.
    /// @property
    void SetKinematic(bool enable);
    /// Set rigid body trigger mode. In trigger mode collisions are reported but do not apply forces.
    /// @property
    void SetTrigger(bool enable);
    /// Set collision layer.
    /// @property
    void SetCollisionLayer(unsigned layer);
    /// Set collision mask.
    /// @property
    void SetCollisionMask(unsigned mask);
    /// Set collision group and mask.
    void SetCollisionLayerAndMask(unsigned layer, unsigned mask);
    /// Set collision event signaling mode. Default is to signal when rigid bodies are active.
    /// @property
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
    btRigidBody* GetBody() const { return body_.get(); }

    /// Return Bullet compound collision shape.
    btCompoundShape* GetCompoundShape() const { return compoundShape_.get(); }

    /// Return mass.
    /// @property
    float GetMass() const { return mass_; }

    /// Return rigid body position in world space.
    /// @property
    Vector3 GetPosition() const;
    /// Return rigid body rotation in world space.
    /// @property
    Quaternion GetRotation() const;
    /// Return linear velocity.
    /// @property
    Vector3 GetLinearVelocity() const;
    /// Return linear degrees of freedom.
    /// @property
    Vector3 GetLinearFactor() const;
    /// Return linear velocity at local point.
    Vector3 GetVelocityAtPoint(const Vector3& position) const;
    /// Return linear velocity deactivation threshold.
    /// @property
    float GetLinearRestThreshold() const;
    /// Return linear velocity damping factor.
    /// @property
    float GetLinearDamping() const;
    /// Return angular velocity.
    /// @property
    Vector3 GetAngularVelocity() const;
    /// Return angular degrees of freedom.
    /// @property
    Vector3 GetAngularFactor() const;
    /// Return angular velocity deactivation threshold.
    /// @property
    float GetAngularRestThreshold() const;
    /// Return angular velocity damping factor.
    /// @property
    float GetAngularDamping() const;
    /// Return friction coefficient.
    /// @property
    float GetFriction() const;
    /// Return anisotropic friction.
    /// @property
    Vector3 GetAnisotropicFriction() const;
    /// Return rolling friction coefficient.
    /// @property
    float GetRollingFriction() const;
    /// Return restitution coefficient.
    /// @property
    float GetRestitution() const;
    /// Return contact processing threshold.
    /// @property
    float GetContactProcessingThreshold() const;
    /// Return continuous collision detection swept sphere radius.
    /// @property
    float GetCcdRadius() const;
    /// Return continuous collision detection motion-per-simulation-step threshold.
    /// @property
    float GetCcdMotionThreshold() const;

    /// Return whether rigid body uses gravity.
    /// @property
    bool GetUseGravity() const { return useGravity_; }

    /// Return gravity override. If zero (default), uses the physics world's gravity.
    /// @property
    const Vector3& GetGravityOverride() const { return gravityOverride_; }

    /// Return center of mass offset.
    /// @property
    const Vector3& GetCenterOfMass() const { return centerOfMass_; }

    /// Return kinematic mode flag.
    /// @property
    bool IsKinematic() const { return kinematic_; }

    /// Return whether this RigidBody is acting as a trigger.
    /// @property
    bool IsTrigger() const { return trigger_; }

    /// Return whether rigid body is active (not sleeping).
    /// @property
    bool IsActive() const;

    /// Return collision layer.
    /// @property
    unsigned GetCollisionLayer() const { return collisionLayer_; }

    /// Return collision mask.
    /// @property
    unsigned GetCollisionMask() const { return collisionMask_; }

    /// Return collision event signaling mode.
    /// @property
    CollisionEventMode GetCollisionEventMode() const { return collisionEventMode_; }

    /// Return colliding rigid bodies from the last simulation step. Only returns collisions that were sent as events (depends on collision event mode) and excludes e.g. static-static collisions.
    void GetCollidingBodies(PODVector<RigidBody*>& result) const;

    /// Apply new world transform after a simulation step. Called internally.
    void ApplyWorldTransform(const Vector3& newWorldPosition, const Quaternion& newWorldRotation);
    /// Update mass and inertia to the Bullet rigid body. Readd body to world if necessary: if was in world and the Bullet collision shape to use changed.
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
    void OnNodeSet(Node* node) override;
    /// Handle scene being assigned.
    void OnSceneSet(Scene* scene) override;
    /// Handle node transform being dirtied.
    void OnMarkedDirty(Node* node) override;

private:
    /// Create the rigid body, or re-add to the physics world with changed flags. Calls UpdateMass().
    void AddBodyToWorld();
    /// Remove the rigid body from the physics world.
    void RemoveBodyFromWorld();
    /// Handle SmoothedTransform target position update.
    void HandleTargetPosition(StringHash eventType, VariantMap& eventData);
    /// Handle SmoothedTransform target rotation update.
    void HandleTargetRotation(StringHash eventType, VariantMap& eventData);
    /// Mark body dirty.
    void MarkBodyDirty() { readdBody_ = true; }

    /// Bullet rigid body.
    std::unique_ptr<btRigidBody> body_;
    
    /// Bullet compound collision shape.
    std::unique_ptr<btCompoundShape> compoundShape_;
    
    /// Compound collision shape with center of mass offset applied.
    std::unique_ptr<btCompoundShape> shiftedCompoundShape_;
    
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
