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

/// 2D distance constraint component.
class URHO3D_API ConstraintDistance2D : public Constraint2D
{
    OBJECT(ConstraintDistance2D);

public:
    /// Construct.
    ConstraintDistance2D(Context* scontext);
    /// Destruct.
    virtual ~ConstraintDistance2D();
    /// Register object factory.
    static void RegisterObject(Context* context);

    /// Set owner body anchor point.
    void SetOwnerBodyAnchor(const Vector2& anchor);
    /// Set other body anchor point.
    void SetOtherBodyAnchor(const Vector2& anchor);
    /// Set frequency Hz.
    void SetFrequencyHz(float frequencyHz);
    /// Set damping ratio.
    void SetDampingRatio(float dampingRatio);

    /// Return owner body anchor point.
    const Vector2& GetOwnerBodyAnchor() const { return ownerBodyAnchor_; }
    /// Return other body anchor point.
    const Vector2& GetOtherBodyAnchor() const { return otherBodyAnchor_; }
    /// Return frequency Hz.
    float GetFrequencyHz() const { return frequencyHz_; }
    /// Return damping ratio.
    float GetDampingRatio() const { return dampingRatio_; }

private:
    /// Create Joint def.
    virtual b2JointDef* CreateJointDef();

    /// Owner body anchor.
    Vector2 ownerBodyAnchor_;
    /// Other body anchor.
    Vector2 otherBodyAnchor_;
    /// Frequency Hz.
    float frequencyHz_;
    /// Damping ratio.
    float dampingRatio_;
};

}