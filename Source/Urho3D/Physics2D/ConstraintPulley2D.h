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

/// 2D pulley constraint component.
class URHO3D_API ConstraintPulley2D : public Constraint2D
{
    URHO3D_OBJECT(ConstraintPulley2D, Constraint2D);

public:
    /// Construct.
    explicit ConstraintPulley2D(Context* context);
    /// Destruct.
    ~ConstraintPulley2D() override;
    /// Register object factory.
    /// @nobind
    static void RegisterObject(Context* context);

    /// Set other body ground anchor point.
    /// @property
    void SetOwnerBodyGroundAnchor(const Vector2& groundAnchor);
    /// Set other body ground anchor point.
    /// @property
    void SetOtherBodyGroundAnchor(const Vector2& groundAnchor);
    /// Set owner body anchor point.
    /// @property
    void SetOwnerBodyAnchor(const Vector2& anchor);
    /// Set other body anchor point.
    /// @property
    void SetOtherBodyAnchor(const Vector2& anchor);
    /// Set ratio.
    /// @property
    void SetRatio(float ratio);

    /// Return owner body ground anchor.
    /// @property
    const Vector2& GetOwnerBodyGroundAnchor() const { return ownerBodyGroundAnchor_; }

    /// return other body ground anchor.
    /// @property
    const Vector2& GetOtherBodyGroundAnchor() const { return otherBodyGroundAnchor_; }

    /// Return owner body anchor.
    /// @property
    const Vector2& GetOwnerBodyAnchor() const { return ownerBodyAnchor_; }

    /// Return other body anchor.
    /// @property
    const Vector2& GetOtherBodyAnchor() const { return otherBodyAnchor_; }

    /// Return ratio.
    /// @property
    float GetRatio() const { return jointDef_.ratio; }


private:
    /// Return Joint def.
    b2JointDef* GetJointDef() override;

    /// Box2D joint def.
    b2PulleyJointDef jointDef_;
    /// Owner body ground anchor.
    Vector2 ownerBodyGroundAnchor_;
    /// Other body ground anchor.
    Vector2 otherBodyGroundAnchor_;
    /// Owner body anchor.
    Vector2 ownerBodyAnchor_;
    /// Other body anchor.
    Vector2 otherBodyAnchor_;
};

}
