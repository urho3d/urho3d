// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include "../Precompiled.h"

#include "../Core/Context.h"
#include "../Physics2D/ConstraintGear2D.h"
#include "../Physics2D/PhysicsUtils2D.h"
#include "../Physics2D/RigidBody2D.h"

#include "../DebugNew.h"

namespace Urho3D
{

extern const char* PHYSICS2D_CATEGORY;

ConstraintGear2D::ConstraintGear2D(Context* context) :
    Constraint2D(context)
{
}

ConstraintGear2D::~ConstraintGear2D() = default;

void ConstraintGear2D::RegisterObject(Context* context)
{
    context->RegisterFactory<ConstraintGear2D>(PHYSICS2D_CATEGORY);

    URHO3D_ACCESSOR_ATTRIBUTE("Is Enabled", IsEnabled, SetEnabled, bool, true, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Ratio", GetRatio, SetRatio, float, 0.0f, AM_DEFAULT);
    URHO3D_COPY_BASE_ATTRIBUTES(Constraint2D);
}

void ConstraintGear2D::SetOwnerConstraint(Constraint2D* constraint)
{
    if (constraint == ownerConstraint_)
        return;

    if (ownerConstraint_)
        ownerConstraint_->SetAttachedConstraint(nullptr);

    ownerConstraint_ = constraint;

    if (ownerConstraint_)
        ownerConstraint_->SetAttachedConstraint(this);

    RecreateJoint();
    MarkNetworkUpdate();
}

void ConstraintGear2D::SetOtherConstraint(Constraint2D* constraint)
{
    WeakPtr<Constraint2D> constraintPtr(constraint);
    if (constraintPtr == otherConstraint_)
        return;

    if (otherConstraint_)
        otherConstraint_->SetAttachedConstraint(nullptr);

    otherConstraint_ = constraintPtr;

    if (otherConstraint_)
        otherConstraint_->SetAttachedConstraint(this);

    RecreateJoint();
    MarkNetworkUpdate();
}

void ConstraintGear2D::SetRatio(float ratio)
{
    if (ratio == jointDef_.ratio)
        return;

    jointDef_.ratio = ratio;

    if (joint_)
        static_cast<b2GearJoint*>(joint_)->SetRatio(ratio);
    else
        RecreateJoint();

    MarkNetworkUpdate();
}

b2JointDef* ConstraintGear2D::GetJointDef()
{
    if (!ownerBody_ || !otherBody_)
        return nullptr;

    b2Body* bodyA = ownerBody_->GetBody();
    b2Body* bodyB = otherBody_->GetBody();
    if (!bodyA || !bodyB)
        return nullptr;

    if (!ownerConstraint_ || !otherConstraint_)
        return nullptr;

    b2Joint* jointA = ownerConstraint_->GetJoint();
    b2Joint* jointB = otherConstraint_->GetJoint();
    if (!jointA || !jointB)
        return nullptr;

    InitializeJointDef(&jointDef_);
    jointDef_.joint1 = jointA;
    jointDef_.joint2 = jointB;

    return &jointDef_;
}

}
