// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include "../Precompiled.h"

#include "../Core/Context.h"
#include "../Physics2D/ConstraintWeld2D.h"
#include "../Physics2D/PhysicsUtils2D.h"
#include "../Physics2D/RigidBody2D.h"

#include "../DebugNew.h"

namespace Urho3D
{

extern const char* PHYSICS2D_CATEGORY;

ConstraintWeld2D::ConstraintWeld2D(Context* context) :
    Constraint2D(context),
    anchor_(Vector2::ZERO)
{
}

ConstraintWeld2D::~ConstraintWeld2D() = default;

void ConstraintWeld2D::RegisterObject(Context* context)
{
    context->RegisterFactory<ConstraintWeld2D>(PHYSICS2D_CATEGORY);

    URHO3D_ACCESSOR_ATTRIBUTE("Is Enabled", IsEnabled, SetEnabled, bool, true, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Anchor", GetAnchor, SetAnchor, Vector2, Vector2::ZERO, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Stiffness", GetStiffness, SetStiffness, float, 0.0f, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Damping", GetDamping, SetDamping, float, 0.0f, AM_DEFAULT);
    URHO3D_COPY_BASE_ATTRIBUTES(Constraint2D);
}

void ConstraintWeld2D::SetAnchor(const Vector2& anchor)
{
    if (anchor == anchor_)
        return;

    anchor_ = anchor;

    RecreateJoint();
    MarkNetworkUpdate();
}

void ConstraintWeld2D::SetStiffness(float stiffness)
{
    if (stiffness == jointDef_.stiffness)
        return;

    jointDef_.stiffness = stiffness;

    if (joint_)
        static_cast<b2WeldJoint*>(joint_)->SetStiffness(stiffness);
    else
        RecreateJoint();

    MarkNetworkUpdate();
}

void ConstraintWeld2D::SetDamping(float damping)
{
    if (damping == jointDef_.damping)
        return;

    jointDef_.damping = damping;

    if (joint_)
        static_cast<b2WeldJoint*>(joint_)->SetDamping(damping);
    else
        RecreateJoint();

    MarkNetworkUpdate();
}

b2JointDef* ConstraintWeld2D::GetJointDef()
{
    if (!ownerBody_ || !otherBody_)
        return nullptr;

    b2Body* bodyA = ownerBody_->GetBody();
    b2Body* bodyB = otherBody_->GetBody();
    if (!bodyA || !bodyB)
        return nullptr;

    jointDef_.Initialize(bodyA, bodyB, ToB2Vec2(anchor_));

    return &jointDef_;
}


bool ConstraintWeld2D::SetAngularStiffness(float frequencyHertz, float dampingRatio)
{
    if (!ownerBody_ || !otherBody_)
        return false;

    b2Body* bodyA = ownerBody_->GetBody();
    b2Body* bodyB = otherBody_->GetBody();
    if (!bodyA || !bodyB)
        return false;

    float stiffness, damping;
    b2AngularStiffness(stiffness, damping, frequencyHertz, dampingRatio, bodyA, bodyB);

    if (joint_)
    {
        static_cast<b2WeldJoint*>(joint_)->SetDamping(damping);
        static_cast<b2WeldJoint*>(joint_)->SetStiffness(stiffness);
    }
    else
    {
        RecreateJoint();
    }

    MarkNetworkUpdate();

    return true;
}

}
