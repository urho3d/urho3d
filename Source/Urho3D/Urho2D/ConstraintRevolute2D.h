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

/// 2D revolute constraint component.
class URHO3D_API ConstraintRevolute2D : public Constraint2D
{
    URHO3D_OBJECT(ConstraintRevolute2D, Constraint2D);

public:
    /// Construct.
    explicit ConstraintRevolute2D(Context* context);
    /// Destruct.
    ~ConstraintRevolute2D() override;
    /// Register object factory.
    /// @nobind
    static void RegisterObject(Context* context);

    /// Set anchor.
    /// @property
    void SetAnchor(const Vector2& anchor);
    /// Set enable limit.
    /// @property
    void SetEnableLimit(bool enableLimit);
    /// Set lower angle.
    /// @property
    void SetLowerAngle(float lowerAngle);
    /// Set upper angle.
    /// @property
    void SetUpperAngle(float upperAngle);
    /// Set enable motor.
    /// @property
    void SetEnableMotor(bool enableMotor);
    /// Set motor speed.
    /// @property
    void SetMotorSpeed(float motorSpeed);
    /// Set max motor torque.
    /// @property
    void SetMaxMotorTorque(float maxMotorTorque);

    /// Return anchor.
    /// @property
    const Vector2& GetAnchor() const { return anchor_; }

    /// Return enable limit.
    /// @property
    bool GetEnableLimit() const { return jointDef_.enableLimit; }

    /// Return lower angle.
    /// @property
    float GetLowerAngle() const { return jointDef_.lowerAngle; }

    /// Return upper angle.
    /// @property
    float GetUpperAngle() const { return jointDef_.upperAngle; }

    /// Return enable motor.
    /// @property
    bool GetEnableMotor() const { return jointDef_.enableMotor; }

    /// Return motor speed.
    /// @property
    float GetMotorSpeed() const { return jointDef_.motorSpeed; }

    /// Return max motor torque.
    /// @property
    float GetMaxMotorTorque() const { return jointDef_.maxMotorTorque; }

private:
    /// Return joint def.
    b2JointDef* GetJointDef() override;

    /// Box2D joint def.
    b2RevoluteJointDef jointDef_;
    /// Anchor.
    Vector2 anchor_;
};

}
