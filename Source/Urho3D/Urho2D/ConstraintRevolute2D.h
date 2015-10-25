//
// Copyright (c) 2008-2015 the Urho3D project.
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
    ConstraintRevolute2D(Context* context);
    /// Destruct.
    virtual ~ConstraintRevolute2D();
    /// Register object factory.
    static void RegisterObject(Context* context);

    /// Set anchor.
    void SetAnchor(const Vector2& anchor);
    /// Set enable limit.
    void SetEnableLimit(bool enableLimit);
    /// Set lower angle.
    void SetLowerAngle(float lowerAngle);
    /// Set upper angle.
    void SetUpperAngle(float upperAngle);
    /// Set enable motor.
    void SetEnableMotor(bool enableMotor);
    /// Set motor speed.
    void SetMotorSpeed(float motorSpeed);
    /// Set max motor torque.
    void SetMaxMotorTorque(float maxMotorTorque);

    /// Return anchor.
    const Vector2& GetAnchor() const { return anchor_; }

    /// Return enable limit.
    bool GetEnableLimit() const { return jointDef_.enableLimit; }

    /// Return lower angle.
    float GetLowerAngle() const { return jointDef_.lowerAngle; }

    /// Return upper angle.
    float GetUpperAngle() const { return jointDef_.upperAngle; }

    /// Return enable motor.
    bool GetEnableMotor() const { return jointDef_.enableMotor; }

    /// Return motor speed.
    float GetMotorSpeed() const { return jointDef_.motorSpeed; }

    /// Return max motor torque.
    float GetMaxMotorTorque() const { return jointDef_.maxMotorTorque; }

private:
    /// Return joint def.
    virtual b2JointDef* GetJointDef();

    /// Box2D joint def.
    b2RevoluteJointDef jointDef_;
    /// Anchor.
    Vector2 anchor_;
};

}
