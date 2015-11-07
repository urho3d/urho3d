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

/// 2D gear constraint component.
class URHO3D_API ConstraintGear2D : public Constraint2D
{
    URHO3D_OBJECT(ConstraintGear2D, Constraint2D);

public:
    /// Construct.
    ConstraintGear2D(Context* context);
    /// Destruct.
    virtual ~ConstraintGear2D();
    /// Register object factory.
    static void RegisterObject(Context* context);

    /// Set owner constraint.
    void SetOwnerConstraint(Constraint2D* constraint);
    /// Set other constraint.
    void SetOtherConstraint(Constraint2D* constraint);
    /// Set ratio.
    void SetRatio(float ratio);

    /// Return owner constraint.
    Constraint2D* GetOwnerConstraint() const { return ownerConstraint_; }

    /// Return other constraint.
    Constraint2D* GetOtherConstraint() const { return otherConstraint_; }

    /// Return ratio.
    float GetRatio() const { return jointDef_.ratio; }

private:
    /// Return joint def.
    virtual b2JointDef* GetJointDef();

    /// Box2D joint def.
    b2GearJointDef jointDef_;
    /// Owner body constraint.
    WeakPtr<Constraint2D> ownerConstraint_;
    /// Other body constraint.
    WeakPtr<Constraint2D> otherConstraint_;
};

}
