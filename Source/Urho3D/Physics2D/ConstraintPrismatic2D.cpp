// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include "../Precompiled.h"

#include "../Core/Context.h"
#include "../Physics2D/ConstraintPrismatic2D.h"
#include "../Physics2D/PhysicsUtils2D.h"
#include "../Physics2D/RigidBody2D.h"

#include "../DebugNew.h"

namespace Urho3D
{

extern const char* PHYSICS2D_CATEGORY;

ConstraintPrismatic2D::ConstraintPrismatic2D(Context* context) :
    Constraint2D(context),
    anchor_(Vector2::ZERO),
    axis_(Vector2::RIGHT)
{
}

ConstraintPrismatic2D::~ConstraintPrismatic2D() = default;

void ConstraintPrismatic2D::RegisterObject(Context* context)
{
    context->RegisterFactory<ConstraintPrismatic2D>(PHYSICS2D_CATEGORY);

    URHO3D_ACCESSOR_ATTRIBUTE("Is Enabled", IsEnabled, SetEnabled, bool, true, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Anchor", GetAnchor, SetAnchor, Vector2, Vector2::ZERO, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Axis", GetAxis, SetAxis, Vector2, Vector2::RIGHT, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Enable Limit", GetEnableLimit, SetEnableLimit, bool, false, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Lower translation", GetLowerTranslation, SetLowerTranslation, float, 0.0f, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Upper translation", GetUpperTranslation, SetUpperTranslation, float, 0.0f, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Enable Motor", GetEnableMotor, SetEnableMotor, bool, false, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Max Motor Force", GetMaxMotorForce, SetMaxMotorForce, float, 2.0f, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Motor Speed", GetMotorSpeed, SetMotorSpeed, float, 0.7f, AM_DEFAULT);
    URHO3D_COPY_BASE_ATTRIBUTES(Constraint2D);
}

void ConstraintPrismatic2D::SetAnchor(const Vector2& anchor)
{
    if (anchor == anchor_)
        return;

    anchor_ = anchor;

    RecreateJoint();
    MarkNetworkUpdate();
}

void ConstraintPrismatic2D::SetAxis(const Vector2& axis)
{
    if (axis == axis_)
        return;

    axis_ = axis;

    RecreateJoint();
    MarkNetworkUpdate();
}

void ConstraintPrismatic2D::SetEnableLimit(bool enableLimit)
{
    if (enableLimit == jointDef_.enableLimit)
        return;

    jointDef_.enableLimit = enableLimit;

    if (joint_)
        static_cast<b2PrismaticJoint*>(joint_)->EnableLimit(enableLimit);
    else
        RecreateJoint();

    MarkNetworkUpdate();
}

void ConstraintPrismatic2D::SetLowerTranslation(float lowerTranslation)
{
    if (lowerTranslation == jointDef_.lowerTranslation)
        return;

    jointDef_.lowerTranslation = lowerTranslation;

    if (joint_)
        static_cast<b2PrismaticJoint*>(joint_)->SetLimits(lowerTranslation, jointDef_.upperTranslation);
    else
        RecreateJoint();

    MarkNetworkUpdate();
}

void ConstraintPrismatic2D::SetUpperTranslation(float upperTranslation)
{
    if (upperTranslation == jointDef_.upperTranslation)
        return;

    jointDef_.upperTranslation = upperTranslation;

    if (joint_)
        static_cast<b2PrismaticJoint*>(joint_)->SetLimits(jointDef_.lowerTranslation, upperTranslation);
    else
        RecreateJoint();

    MarkNetworkUpdate();
}

void ConstraintPrismatic2D::SetEnableMotor(bool enableMotor)
{
    if (enableMotor == jointDef_.enableMotor)
        return;

    jointDef_.enableMotor = enableMotor;

    if (joint_)
        static_cast<b2PrismaticJoint*>(joint_)->EnableMotor(enableMotor);
    else
        RecreateJoint();

    MarkNetworkUpdate();
}

void ConstraintPrismatic2D::SetMaxMotorForce(float maxMotorForce)
{
    if (maxMotorForce == jointDef_.maxMotorForce)
        return;

    jointDef_.maxMotorForce = maxMotorForce;

    if (joint_)
        static_cast<b2PrismaticJoint*>(joint_)->SetMaxMotorForce(maxMotorForce);
    else
        RecreateJoint();

    MarkNetworkUpdate();
}

void ConstraintPrismatic2D::SetMotorSpeed(float motorSpeed)
{
    if (motorSpeed == jointDef_.motorSpeed)
        return;

    jointDef_.motorSpeed = motorSpeed;

    if (joint_)
        static_cast<b2PrismaticJoint*>(joint_)->SetMotorSpeed(motorSpeed);
    else
        RecreateJoint();

    MarkNetworkUpdate();
}

b2JointDef* ConstraintPrismatic2D::GetJointDef()
{
    if (!ownerBody_ || !otherBody_)
        return nullptr;

    b2Body* bodyA = ownerBody_->GetBody();
    b2Body* bodyB = otherBody_->GetBody();
    if (!bodyA || !bodyB)
        return nullptr;

    jointDef_.Initialize(bodyA, bodyB, ToB2Vec2(anchor_), ToB2Vec2(axis_));

    return &jointDef_;
}

}
