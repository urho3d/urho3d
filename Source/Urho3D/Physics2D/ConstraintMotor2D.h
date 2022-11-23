// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include "../Physics2D/Constraint2D.h"

namespace Urho3D
{

/// 2D motor constraint component.
class URHO3D_API ConstraintMotor2D : public Constraint2D
{
    URHO3D_OBJECT(ConstraintMotor2D, Constraint2D);

public:
    /// Construct.
    explicit ConstraintMotor2D(Context* context);
    /// Destruct.
    ~ConstraintMotor2D() override;
    /// Register object factory.
    /// @nobind
    static void RegisterObject(Context* context);

    /// Set linear offset.
    /// @property
    void SetLinearOffset(const Vector2& linearOffset);
    /// Set angular offset.
    /// @property
    void SetAngularOffset(float angularOffset);
    /// Set max force.
    /// @property
    void SetMaxForce(float maxForce);
    /// Set max torque.
    /// @property
    void SetMaxTorque(float maxTorque);
    /// Set correction factor.
    /// @property
    void SetCorrectionFactor(float correctionFactor);

    /// Return linear offset.
    /// @property
    const Vector2& GetLinearOffset() const { return linearOffset_; }

    /// Return angular offset.
    /// @property
    float GetAngularOffset() const { return jointDef_.angularOffset; }

    /// Return max force.
    /// @property
    float GetMaxForce() const { return jointDef_.maxForce; }

    /// Return max torque.
    /// @property
    float GetMaxTorque() const { return jointDef_.maxTorque; }

    /// Return correction factor.
    /// @property
    float GetCorrectionFactor() const { return jointDef_.correctionFactor; }

private:
    /// Return joint def.
    b2JointDef* GetJointDef() override;

    /// Box2D joint def.
    b2MotorJointDef jointDef_;
    /// Linear offset.
    Vector2 linearOffset_;
};

}
