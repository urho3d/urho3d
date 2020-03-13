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

/// \file

#pragma once

#include "../Math/Vector3.h"
#include "../Scene/Component.h"

class btTypedConstraint;

namespace Urho3D
{

/// Supported constraint types.
enum ConstraintType
{
    CONSTRAINT_POINT = 0,
    CONSTRAINT_HINGE,
    CONSTRAINT_SLIDER,
    CONSTRAINT_CONETWIST
};

class PhysicsWorld;
class RigidBody;

/// Physics constraint component. Connects two rigid bodies together, or one rigid body to a static point.
class URHO3D_API Constraint : public Component
{
    URHO3D_OBJECT(Constraint, Component);

    friend class RigidBody;

public:
    /// Construct.
    explicit Constraint(Context* context);
    /// Destruct.
    ~Constraint() override;
    /// Register object factory.
    static void RegisterObject(Context* context);

    /// Apply attribute changes that can not be applied immediately. Called after scene load or a network update.
    void ApplyAttributes() override;
    /// Handle enabled/disabled state change.
    void OnSetEnabled() override;
    /// Return the depended on nodes to order network updates.
    void GetDependencyNodes(PODVector<Node*>& dest) override;
    /// Visualize the component as debug geometry.
    void DrawDebugGeometry(DebugRenderer* debug, bool depthTest) override;

    /// Set constraint type and recreate the constraint.
    void SetConstraintType(ConstraintType type);
    /// Set other body to connect to. Set to null to connect to the static world.
    void SetOtherBody(RigidBody* body);
    /// Set constraint position relative to own body.
    void SetPosition(const Vector3& position);
    /// Set constraint rotation relative to own body.
    void SetRotation(const Quaternion& rotation);
    /// Set constraint rotation relative to own body by specifying the axis.
    void SetAxis(const Vector3& axis);
    /// Set constraint position relative to the other body. If connected to the static world, is a world space position.
    void SetOtherPosition(const Vector3& position);
    /// Set constraint rotation relative to the other body. If connected to the static world, is a world space rotation.
    void SetOtherRotation(const Quaternion& rotation);
    /// Set constraint rotation relative to the other body by specifying the axis.
    void SetOtherAxis(const Vector3& axis);
    /// Set constraint world space position. Resets both own and other body relative position, ie. zeroes the constraint error.
    void SetWorldPosition(const Vector3& position);
    /// Set high limit. Interpretation is constraint type specific.
    void SetHighLimit(const Vector2& limit);
    /// Set low limit. Interpretation is constraint type specific.
    void SetLowLimit(const Vector2& limit);
    /// Set constraint error reduction parameter. Zero = leave to default.
    void SetERP(float erp);
    /// Set constraint force mixing parameter. Zero = leave to default.
    void SetCFM(float cfm);
    /// Set whether to disable collisions between connected bodies.
    void SetDisableCollision(bool disable);

    /// Return physics world.
    PhysicsWorld* GetPhysicsWorld() const { return physicsWorld_; }

    /// Return Bullet constraint.
    btTypedConstraint* GetConstraint() const { return constraint_.Get(); }

    /// Return constraint type.
    ConstraintType GetConstraintType() const { return constraintType_; }

    /// Return rigid body in own scene node.
    RigidBody* GetOwnBody() const { return ownBody_; }

    /// Return the other rigid body. May be null if connected to the static world.
    RigidBody* GetOtherBody() const { return otherBody_; }

    /// Return constraint position relative to own body.
    const Vector3& GetPosition() const { return position_; }

    /// Return constraint rotation relative to own body.
    const Quaternion& GetRotation() const { return rotation_; }

    /// Return constraint position relative to other body.
    const Vector3& GetOtherPosition() const { return otherPosition_; }

    /// Return constraint rotation relative to other body.
    const Quaternion& GetOtherRotation() const { return otherRotation_; }

    /// Return constraint world position, calculated from own body.
    Vector3 GetWorldPosition() const;

    /// Return high limit.
    const Vector2& GetHighLimit() const { return highLimit_; }

    /// Return low limit.
    const Vector2& GetLowLimit() const { return lowLimit_; }

    /// Return constraint error reduction parameter.
    float GetERP() const { return erp_; }

    /// Return constraint force mixing parameter.
    float GetCFM() const { return cfm_; }

    /// Return whether collisions between connected bodies are disabled.
    bool GetDisableCollision() const { return disableCollision_; }

    /// Release the constraint.
    void ReleaseConstraint();
    /// Apply constraint frames.
    void ApplyFrames();

protected:
    /// Handle node being assigned.
    void OnNodeSet(Node* node) override;
    /// Handle scene being assigned.
    void OnSceneSet(Scene* scene) override;
    /// Handle node transform being dirtied.
    void OnMarkedDirty(Node* node) override;

private:
    /// Create the constraint.
    void CreateConstraint();
    /// Apply high and low constraint limits.
    void ApplyLimits();
    /// Adjust other body position.
    void AdjustOtherBodyPosition();
    /// Mark constraint dirty.
    void MarkConstraintDirty() { recreateConstraint_ = true; }
    /// Mark frames dirty.
    void MarkFramesDirty() { framesDirty_ = true; }

    /// Physics world.
    WeakPtr<PhysicsWorld> physicsWorld_;
    /// Own rigid body.
    WeakPtr<RigidBody> ownBody_;
    /// Other rigid body.
    WeakPtr<RigidBody> otherBody_;
    /// Bullet constraint.
    UniquePtr<btTypedConstraint> constraint_;
    /// Constraint type.
    ConstraintType constraintType_;
    /// Constraint position.
    Vector3 position_;
    /// Constraint rotation.
    Quaternion rotation_;
    /// Constraint other body position.
    Vector3 otherPosition_;
    /// Constraint other body axis.
    Quaternion otherRotation_;
    /// Cached world scale for determining if the constraint position needs update.
    Vector3 cachedWorldScale_;
    /// High limit.
    Vector2 highLimit_;
    /// Low limit.
    Vector2 lowLimit_;
    /// Error reduction parameter.
    float erp_;
    /// Constraint force mixing parameter.
    float cfm_;
    /// Other body node ID for pending constraint recreation.
    unsigned otherBodyNodeID_;
    /// Disable collision between connected bodies flag.
    bool disableCollision_;
    /// Recreate constraint flag.
    bool recreateConstraint_;
    /// Coordinate frames dirty flag.
    bool framesDirty_;
    /// Constraint creation retry flag if attributes initially set without scene.
    bool retryCreation_;
};

}
