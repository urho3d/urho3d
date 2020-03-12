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

#include "../Scene/Component.h"

struct ik_node_t;

namespace Urho3D
{

class Context;
class Node;

class URHO3D_API IKConstraint : public Component
{
    URHO3D_OBJECT(IKConstraint, Component)

public:

    /// Constructs a new IK constraint.
    explicit IKConstraint(Context* context);

    /// Destructs he IK constraint.
    ~IKConstraint() override;

    /// Registers this class as an object factory.
    static void RegisterObject(Context* context);

    float GetStiffness() const;
    void SetStiffness(float stiffness);

    float GetStretchiness() const;
    void SetStretchiness(float stretchiness);

    const Vector2& GetLengthConstraints() const;
    void SetLengthConstraints(const Vector2& lengthConstraints);

private:
    friend class IKSolver;

    /// Intended to be used only by IKSolver.
    void SetIKConstraintNode(ik_node_t* constraintNode);

    ik_node_t* ikConstraintNode_;

    float stiffness_;
    float stretchiness_;
    Vector2 lengthConstraints_;
};

} // namespace Urho3D
