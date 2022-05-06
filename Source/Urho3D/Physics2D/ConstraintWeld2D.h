// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

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
    
    /// Return anchor.
    /// @property
    const Vector2& GetAnchor() const { return anchor_; }

    /// Set linear stiffness in N/m.
    /// @property
    void SetStiffness(float stiffness);

    /// Return linear stiffness in N/m.
    /// @property
    float GetStiffness() const { return jointDef_.stiffness; }

    /// Set linear damping in N*s/m.
    /// @property
    void SetDamping(float damping);

    /// Return linear damping in N*s/m.
    /// @property
    float GetDamping() const { return jointDef_.damping; }

    /// Calc and set stiffness and damping. Must be used after set owner and other bodies.
    bool SetAngularStiffness(float frequencyHertz, float dampingRatio);

private:
    /// Return joint def.
    b2JointDef* GetJointDef() override;

    /// Box2D joint def.
    b2WeldJointDef jointDef_;
    
    /// Anchor.
    Vector2 anchor_;
};

}
