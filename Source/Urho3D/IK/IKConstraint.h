// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include "../Scene/Component.h"

struct ik_node_t;

namespace Urho3D
{

class Context;
class Node;

class URHO3D_API IKConstraint : public Component
{
    URHO3D_OBJECT(IKConstraint, Component);

public:

    /// Constructs a new IK constraint.
    explicit IKConstraint(Context* context);

    /// Destructs he IK constraint.
    ~IKConstraint() override;

    /// Registers this class as an object factory.
    /// @nobind
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
