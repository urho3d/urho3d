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

#pragma once

#include "../Urho2D/Constraint2D.h"

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
