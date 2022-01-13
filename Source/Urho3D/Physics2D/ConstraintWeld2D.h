//
// Copyright (c) 2008-2022 the Urho3D project.
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

#include "../Physics2D/Constraint2D.h"

namespace Urho3D
{

/// 2D weld constraint component.
class URHO3D_API ConstraintWeld2D : public Constraint2D
{
    URHO3D_OBJECT(ConstraintWeld2D, Constraint2D);

public:
    /// Construct.
    explicit ConstraintWeld2D(Context* context);
    /// Destruct.
    ~ConstraintWeld2D() override;
    /// Register object factory.
    /// @nobind
    static void RegisterObject(Context* context);

    /// Set anchor.
    /// @property
    void SetAnchor(const Vector2& anchor);
    /// Set frequency Hz.
    /// @property
    void SetFrequencyHz(float frequencyHz);
    /// Set damping ratio.
    /// @property
    void SetDampingRatio(float dampingRatio);

    /// Return anchor.
    /// @property
    const Vector2& GetAnchor() const { return anchor_; }

    /// Return frequency Hz.
    /// @property
    float GetFrequencyHz() const { return jointDef_.frequencyHz; }

    /// Return damping ratio.
    /// @property
    float GetDampingRatio() const { return jointDef_.dampingRatio; }

private:
    /// Return joint def.
    b2JointDef* GetJointDef() override;

    /// Box2D joint def.
    b2WeldJointDef jointDef_;
    /// Anchor.
    Vector2 anchor_;
};

}
