//
// Copyright (c) 2008-2022 the Urho3D project.
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

/// \file

#pragma once

#include "../Scene/Component.h"

#include <Box2D/Box2D.h>

namespace Urho3D
{

class CollisionShape2D;
class Constraint2D;
class PhysicsWorld2D;

/// Rigid body type.
enum BodyType2D
{
    BT_STATIC = b2_staticBody,
    BT_KINEMATIC = b2_kinematicBody,
    BT_DYNAMIC = b2_dynamicBody
};

/// 2D rigid body component.
class URHO3D_API RigidBody2D : public Component
{
    URHO3D_OBJECT(RigidBody2D, Component);

public:
    /// Construct.
    explicit RigidBody2D(Context* context);
    /// Destruct.
    ~RigidBody2D() override;
    /// Register object factory.
    /// @nobind
    static void RegisterObject(Context* context);

    /// Handle enabled/disabled state change.
    void OnSetEnabled() override;

    /// Set body type.
    /// @property
    void SetBodyType(BodyType2D type);
    /// Set mass.
    /// @property
    void SetMass(float mass);
    /// Set inertia.
    /// @property
    void SetInertia(float inertia);
    /// Set mass center.
    /// @property
    void SetMassCenter(const Vector2& center);
    /// Set whether to automatically calculate mass and inertia from collision shapes. Default true.
    /// @property
    void SetUseFixtureMass(bool useFixtureMass);
    /// Set linear damping.
    /// @property
    void SetLinearDamping(float linearDamping);
    /// Set angular damping.
    /// @property
    void SetAngularDamping(float angularDamping);
    /// Set allow sleep.
    /// @property
    void SetAllowSleep(bool allowSleep);
    /// Set fixed rotation.
    /// @property
    void SetFixedRotation(bool fixedRotation);
    /// Set bullet mode.
    /// @property
    void SetBullet(bool bullet);
    /// Set gravity scale.
    /// @property
    void SetGravityScale(float gravityScale);
    /// Set awake.
    /// @property
    void SetAwake(bool awake);
    /// Set linear velocity.
    /// @property
    void SetLinearVelocity(const Vector2& linearVelocity);
    /// Set angular velocity.
    void SetAngularVelocity(float angularVelocity);
    /// Apply force.
    void ApplyForce(const Vector2& force, const Vector2& point, bool wake);
    /// Apply force to center.
    void ApplyForceToCenter(const Vector2& force, bool wake);
    /// Apply Torque.
    void ApplyTorque(float torque, bool wake);
    /// Apply linear impulse.
    void ApplyLinearImpulse(const Vector2& impulse, const Vector2& point, bool wake);
    /// Apply linear impulse to center.
    void ApplyLinearImpulseToCenter(const Vector2& impulse, bool wake);
    /// Apply angular impulse.
    void ApplyAngularImpulse(float impulse, bool wake);

    /// Create body.
    void CreateBody();
    /// Release body.
    void ReleaseBody();

    /// Apply world transform from the Box2D body. Called by PhysicsWorld2D.
    void ApplyWorldTransform();
    /// Apply specified world position & rotation. Called by PhysicsWorld2D.
    void ApplyWorldTransform(const Vector3& newWorldPosition, const Quaternion& newWorldRotation);
    /// Add collision shape.
    void AddCollisionShape2D(CollisionShape2D* collisionShape);
    /// Remove collision shape.
    void RemoveCollisionShape2D(CollisionShape2D* collisionShape);
    /// Add constraint.
    void AddConstraint2D(Constraint2D* constraint);
    /// Remove constraint.
    void RemoveConstraint2D(Constraint2D* constraint);

    /// Return body type.
    /// @property
    BodyType2D GetBodyType() const { return body_ ? (BodyType2D)body_->GetType() : (BodyType2D)bodyDef_.type; }

    /// Return mass.
    /// @property
    float GetMass() const;
    /// Return inertia.
    /// @property
    float GetInertia() const;
    /// Return mass center.
    /// @property
    Vector2 GetMassCenter() const;

    /// Return whether to calculate mass and inertia from collision shapes automatically.
    /// @property
    bool GetUseFixtureMass() const { return useFixtureMass_; }

    /// Return linear damping.
    /// @property
    float GetLinearDamping() const { return body_ ? body_->GetLinearDamping() : bodyDef_.linearDamping; }

    /// Return angular damping.
    /// @property
    float GetAngularDamping() const { return body_ ? body_->GetAngularDamping() : bodyDef_.angularDamping; }

    /// Return allow sleep.
    /// @property
    bool IsAllowSleep() const { return body_ ? body_->IsSleepingAllowed() : bodyDef_.allowSleep; }

    /// Return fixed rotation.
    /// @property
    bool IsFixedRotation() const { return body_ ? body_->IsFixedRotation() : bodyDef_.fixedRotation; }

    /// Return bullet mode.
    /// @property
    bool IsBullet() const { return body_ ? body_->IsBullet() : bodyDef_.bullet; }

    /// Return gravity scale.
    /// @property
    float GetGravityScale() const { return body_ ? body_->GetGravityScale() : bodyDef_.gravityScale; }

    /// Return awake.
    /// @property
    bool IsAwake() const;
    /// Return linear velocity.
    /// @property
    Vector2 GetLinearVelocity() const;
    /// Return angular velocity.
    float GetAngularVelocity() const;

    /// Return Box2D body.
    b2Body* GetBody() const { return body_; }

private:
    /// Handle node being assigned.
    void OnNodeSet(Node* node) override;
    /// Handle scene being assigned.
    void OnSceneSet(Scene* scene) override;
    /// Handle node transform being dirtied.
    void OnMarkedDirty(Node* node) override;

    /// Physics world.
    WeakPtr<PhysicsWorld2D> physicsWorld_;
    /// Box2D body define.
    b2BodyDef bodyDef_;
    /// Box2D mass data.
    b2MassData massData_;
    /// Use fixture mass (calculate mass & inertia from collision shapes automatically).
    bool useFixtureMass_;
    /// Box2D body.
    b2Body* body_;
    /// Collision shapes.
    Vector<WeakPtr<CollisionShape2D> > collisionShapes_;
    /// Constraints.
    Vector<WeakPtr<Constraint2D> > constraints_;
};

}
