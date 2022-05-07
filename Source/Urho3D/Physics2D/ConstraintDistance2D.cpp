// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include "../Precompiled.h"

#include "../Core/Context.h"
#include "../Physics2D/ConstraintDistance2D.h"
#include "../Physics2D/PhysicsUtils2D.h"
#include "../Physics2D/RigidBody2D.h"

#include "../DebugNew.h"

namespace Urho3D
{

extern const char* PHYSICS2D_CATEGORY;

ConstraintDistance2D::ConstraintDistance2D(Context* context) :
    Constraint2D(context),
    ownerBodyAnchor_(Vector2::ZERO),
    otherBodyAnchor_(Vector2::ZERO)
{

}

ConstraintDistance2D::~ConstraintDistance2D() = default;

void ConstraintDistance2D::RegisterObject(Context* context)
{
    context->RegisterFactory<ConstraintDistance2D>(PHYSICS2D_CATEGORY);

    URHO3D_ACCESSOR_ATTRIBUTE("Is Enabled", IsEnabled, SetEnabled, bool, true, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Owner Body Anchor", GetOwnerBodyAnchor, SetOwnerBodyAnchor, Vector2, Vector2::ZERO, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Other Body Anchor", GetOtherBodyAnchor, SetOtherBodyAnchor, Vector2, Vector2::ZERO, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Stiffness", GetStiffness, SetStiffness, float, 0.0f, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Damping", GetDamping, SetDamping, float, 0.0f, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Length", GetLength, SetLength, float, 1.0f, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Min Length", GetMinLength, SetMinLength, float, 0.0f, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Max Length", GetMaxLength, SetMaxLength, float, FLT_MAX, AM_DEFAULT);
    URHO3D_COPY_BASE_ATTRIBUTES(Constraint2D);
}

void ConstraintDistance2D::SetOwnerBodyAnchor(const Vector2& anchor)
{
    if (anchor == ownerBodyAnchor_)
        return;

    ownerBodyAnchor_ = anchor;

    RecreateJoint();
    MarkNetworkUpdate();
}

void ConstraintDistance2D::SetOtherBodyAnchor(const Vector2& anchor)
{
    if (anchor == otherBodyAnchor_)
        return;

    otherBodyAnchor_ = anchor;

    RecreateJoint();
    MarkNetworkUpdate();
}

void ConstraintDistance2D::SetStiffness(float stiffness)
{
    if (stiffness == jointDef_.stiffness)
        return;

    jointDef_.stiffness = stiffness;

    if (joint_)
        static_cast<b2DistanceJoint*>(joint_)->SetStiffness(stiffness);
    else
        RecreateJoint();

    MarkNetworkUpdate();
}

void ConstraintDistance2D::SetDamping(float damping)
{
    if (damping == jointDef_.damping)
        return;

    jointDef_.damping = damping;

    if (joint_)
        static_cast<b2DistanceJoint*>(joint_)->SetDamping(damping);
    else
        RecreateJoint();

    MarkNetworkUpdate();
}

void ConstraintDistance2D::SetLength(float length)
{
    if (length == jointDef_.length)
        return;

    jointDef_.length = length;

    if (joint_)
        static_cast<b2DistanceJoint*>(joint_)->SetLength(length);
    else
        RecreateJoint();

    MarkNetworkUpdate();
}

b2JointDef* ConstraintDistance2D::GetJointDef()
{
    if (!ownerBody_ || !otherBody_)
        return nullptr;

    b2Body* bodyA = ownerBody_->GetBody();
    b2Body* bodyB = otherBody_->GetBody();
    if (!bodyA || !bodyB)
        return nullptr;

    jointDef_.Initialize(bodyA, bodyB, ToB2Vec2(ownerBodyAnchor_), ToB2Vec2(otherBodyAnchor_));

    return &jointDef_;
}

bool ConstraintDistance2D::SetLinearStiffness(float frequencyHertz, float dampingRatio)
{
    if (!ownerBody_ || !otherBody_)
        return false;

    b2Body* bodyA = ownerBody_->GetBody();
    b2Body* bodyB = otherBody_->GetBody();
    if (!bodyA || !bodyB)
        return false;

    float stiffness, damping;
    b2LinearStiffness(stiffness, damping, frequencyHertz, dampingRatio, bodyA, bodyB);

    if (joint_)
    {
        static_cast<b2DistanceJoint*>(joint_)->SetDamping(damping);
        static_cast<b2DistanceJoint*>(joint_)->SetStiffness(stiffness);
    }
    else
    {
        RecreateJoint();
    }

    MarkNetworkUpdate();

    return true;
}

void ConstraintDistance2D::SetMinLength(float minLength)
{
    if (minLength == jointDef_.minLength)
        return;

    jointDef_.minLength = minLength;

    if (joint_)
        static_cast<b2DistanceJoint*>(joint_)->SetMinLength(minLength);
    else
        RecreateJoint();

    MarkNetworkUpdate();
}

void ConstraintDistance2D::SetMaxLength(float maxLength)
{
    if (maxLength == jointDef_.maxLength)
        return;

    jointDef_.maxLength = maxLength;

    if (joint_)
        static_cast<b2DistanceJoint*>(joint_)->SetMaxLength(maxLength);
    else
        RecreateJoint();

    MarkNetworkUpdate();
}

}
