// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include "../Precompiled.h"

#include "../Core/Context.h"
#include "../Physics2D/ConstraintFriction2D.h"
#include "../Physics2D/PhysicsUtils2D.h"
#include "../Physics2D/RigidBody2D.h"

#include "../DebugNew.h"

namespace Urho3D
{

extern const char* PHYSICS2D_CATEGORY;

ConstraintFriction2D::ConstraintFriction2D(Context* context) :
    Constraint2D(context),
    anchor_(Vector2::ZERO)
{

}

ConstraintFriction2D::~ConstraintFriction2D() = default;

void ConstraintFriction2D::RegisterObject(Context* context)
{
    context->RegisterFactory<ConstraintFriction2D>(PHYSICS2D_CATEGORY);

    URHO3D_ACCESSOR_ATTRIBUTE("Is Enabled", IsEnabled, SetEnabled, bool, true, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Anchor", GetAnchor, SetAnchor, Vector2, Vector2::ZERO, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Max Force", GetMaxForce, SetMaxForce, float, 0.0f, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Max Torque", GetMaxTorque, SetMaxTorque, float, 0.0f, AM_DEFAULT);
    URHO3D_COPY_BASE_ATTRIBUTES(Constraint2D);
}

void ConstraintFriction2D::SetAnchor(const Vector2& anchor)
{
    if (anchor == anchor_)
        return;

    anchor_ = anchor;

    RecreateJoint();
    MarkNetworkUpdate();
}

void ConstraintFriction2D::SetMaxForce(float maxForce)
{
    if (maxForce == jointDef_.maxForce)
        return;

    jointDef_.maxForce = maxForce;

    if (joint_)
        static_cast<b2FrictionJoint*>(joint_)->SetMaxForce(maxForce);
    else
        RecreateJoint();

    MarkNetworkUpdate();
}


void ConstraintFriction2D::SetMaxTorque(float maxTorque)
{
    if (maxTorque == jointDef_.maxTorque)
        return;

    jointDef_.maxTorque = maxTorque;

    if (joint_)
        static_cast<b2FrictionJoint*>(joint_)->SetMaxTorque(maxTorque);
    else
        RecreateJoint();

    MarkNetworkUpdate();
}

b2JointDef* ConstraintFriction2D::GetJointDef()
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

}
