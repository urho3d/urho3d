//
// Copyright (c) 2008-2014 the Urho3D project.
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

#include "Constraint2D.h"

namespace Urho3D
{

/// 2D friction constraint component.
class URHO3D_API ConstraintFriction2D : public Constraint2D
{
    OBJECT(ConstraintFriction2D);

public:
    /// Construct.
    ConstraintFriction2D(Context* scontext);
    /// Destruct.
    virtual ~ConstraintFriction2D();
    /// Register object factory.
    static void RegisterObject(Context* context);

    /// Set anchor point.
    void SetAnchorPoint(const Vector2& anchor);
    /// Set max force.
    void SetMaxForce(float maxForce);
    /// Set max torque.
    void SetMaxTorque(float maxTorque);

    /// Return anchor point.
    const Vector2& GetAnchorPoint() const { return anchorPoint_; }
    /// Set max force.
    float GetMaxForce() const { return maxForce_; }
    /// Set max torque.
    float GetMaxTorque() const { return maxTorque_; }

private:
    /// Create Joint def.
    virtual b2JointDef* CreateJointDef();

    /// Anchor point.
    Vector2 anchorPoint_;
    /// Max force.
    float maxForce_;
    /// Max torque.
    float maxTorque_;
};

}