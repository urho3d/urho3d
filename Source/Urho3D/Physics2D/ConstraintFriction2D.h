// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include "../Physics2D/Constraint2D.h"

namespace Urho3D
{

/// 2D friction constraint component.
class URHO3D_API ConstraintFriction2D : public Constraint2D
{
    URHO3D_OBJECT(ConstraintFriction2D, Constraint2D);

public:
    /// Construct.
    explicit ConstraintFriction2D(Context* context);
    /// Destruct.
    ~ConstraintFriction2D() override;
    /// Register object factory.
    /// @nobind
    static void RegisterObject(Context* context);

    /// Set anchor.
    /// @property
    void SetAnchor(const Vector2& anchor);
    /// Set max force.
    /// @property
    void SetMaxForce(float maxForce);
    /// Set max torque.
    /// @property
    void SetMaxTorque(float maxTorque);

    /// Return anchor.
    /// @property
    const Vector2& GetAnchor() const { return anchor_; }

    /// Set max force.
    /// @property
    float GetMaxForce() const { return jointDef_.maxForce; }

    /// Set max torque.
    /// @property
    float GetMaxTorque() const { return jointDef_.maxTorque; }

private:
    /// Return joint def.
    b2JointDef* GetJointDef() override;

    /// Box2D joint def.
    b2FrictionJointDef jointDef_;
    /// Anchor.
    Vector2 anchor_;
};

}
