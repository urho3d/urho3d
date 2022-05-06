// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include "../Physics2D/Constraint2D.h"

namespace Urho3D
{

/// 2D distance constraint component.
class URHO3D_API ConstraintDistance2D : public Constraint2D
{
    URHO3D_OBJECT(ConstraintDistance2D, Constraint2D);

public:
    /// Construct.
    explicit ConstraintDistance2D(Context* context);
    
    /// Destruct.
    ~ConstraintDistance2D() override;
    
    /// Register object factory.
    /// @nobind
    static void RegisterObject(Context* context);

    /// Set owner body anchor.
    /// @property
    void SetOwnerBodyAnchor(const Vector2& anchor);

    /// Return owner body anchor.
    /// @property
    const Vector2& GetOwnerBodyAnchor() const { return ownerBodyAnchor_; }

    /// Set other body anchor.
    /// @property
    void SetOtherBodyAnchor(const Vector2& anchor);

    /// Return other body anchor.
    /// @property
    const Vector2& GetOtherBodyAnchor() const { return otherBodyAnchor_; }

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

    /// Set length.
    /// @property
    void SetLength(float length);

    /// Return length.
    /// @property
    float GetLength() const { return jointDef_.length; }

    /// Set min length.
    /// @property
    void SetMinLength(float minLength);

    /// Return min length.
    /// @property
    float GetMinLength() const { return jointDef_.minLength; }

    /// Set max length.
    /// @property
    void SetMaxLength(float maxLength);

    /// Return max length.
    /// @property
    float GetMaxLength() const { return jointDef_.maxLength; }

    /// Calc and set stiffness and damping. Must be used after set owner and other bodies.
    bool SetLinearStiffness(float frequencyHertz, float dampingRatio);

private:
    /// Return joint def.
    b2JointDef* GetJointDef() override;

    /// Box2D joint def.
    b2DistanceJointDef jointDef_;
    
    /// Owner body anchor.
    Vector2 ownerBodyAnchor_;
    
    /// Other body anchor.
    Vector2 otherBodyAnchor_;
};

}
