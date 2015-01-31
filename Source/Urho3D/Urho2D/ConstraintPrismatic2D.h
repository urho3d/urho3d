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

/// 2D prismatic constraint component.
class URHO3D_API ConstraintPrismatic2D : public Constraint2D
{
    OBJECT(ConstraintPrismatic2D);

public:
    /// Construct.
    ConstraintPrismatic2D(Context* scontext);
    /// Destruct.
    virtual ~ConstraintPrismatic2D();
    /// Register object factory.
    static void RegisterObject(Context* context);

    /// Set anchor.
    void SetAnchor(const Vector2& anchor);
    /// Set axis.
    void SetAxis(const Vector2& axis);
    /// Set enable limit.
    void SetEnableLimit(bool enableLimit);
    /// Set lower translation.
    void SetLowerTranslation(float lowerTranslation);
    /// Set upper translation.
    void SetUpperTranslation(float upperTranslation);
    /// Set enable motor.
    void SetEnableMotor(bool enableMotor);
    /// Set maxmotor force.
    void SetMaxMotorForce(float maxMotorForce);
    /// Set motor speed.
    void SetMotorSpeed(float motorSpeed);

    /// Return anchor.
    const Vector2& GetAnchor() const { return anchor_; }
    /// Return axis.
    const Vector2& GetAxis() const { return axis_; }
    /// Return enable limit.
    bool GetEnableLimit() const { return jointDef_.enableLimit; }
    /// Return lower translation.
    float GetLowerTranslation() const { return jointDef_.lowerTranslation; }
    /// Return upper translation.
    float GetUpperTranslation() const { return jointDef_.upperTranslation; }
    /// Return enable motor.
    bool GetEnableMotor() const { return jointDef_.enableMotor; }
    /// Return maxmotor force.
    float GetMaxMotorForce() const { return jointDef_.maxMotorForce; }
    /// Return motor speed.
    float GetMotorSpeed() const { return jointDef_.motorSpeed; }

private:
    /// Return joint def.
    virtual b2JointDef* GetJointDef();

    /// Box2D joint def.
    b2PrismaticJointDef jointDef_;
    /// Anchor.
    Vector2 anchor_;
    /// Axis.
    Vector2 axis_;
};

}
