// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include "../Precompiled.h"

#include "../Core/Context.h"
#include "../Physics2D/ConstraintRevolute2D.h"
#include "../Physics2D/PhysicsUtils2D.h"
#include "../Physics2D/RigidBody2D.h"

#include "../DebugNew.h"

namespace Urho3D
{

extern const char* PHYSICS2D_CATEGORY;

ConstraintRevolute2D::ConstraintRevolute2D(Context* context) :
    Constraint2D(context),
    anchor_(Vector2::ZERO)
{
}

ConstraintRevolute2D::~ConstraintRevolute2D() = default;

void ConstraintRevolute2D::RegisterObject(Context* context)
{
    context->RegisterFactory<ConstraintRevolute2D>(PHYSICS2D_CATEGORY);

    URHO3D_ACCESSOR_ATTRIBUTE("Is Enabled", IsEnabled, SetEnabled, bool, true, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Anchor", GetAnchor, SetAnchor, Vector2, Vector2::ZERO, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Enable Limit", GetEnableLimit, SetEnableLimit, bool, false, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Lower Angle", GetLowerAngle, SetLowerAngle, float, 0.0f, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Upper Angle", GetUpperAngle, SetUpperAngle, float, 0.0f, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Enable Motor", GetEnableMotor, SetEnableMotor, bool, false, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Motor Speed", GetMotorSpeed, SetMotorSpeed, float, 0.0f, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Max Motor Torque", GetMaxMotorTorque, SetMaxMotorTorque, float, 0.0f, AM_DEFAULT);
    URHO3D_COPY_BASE_ATTRIBUTES(Constraint2D);
}

void ConstraintRevolute2D::SetAnchor(const Vector2& anchor)
{
    if (anchor == anchor_)
        return;

    anchor_ = anchor;

    RecreateJoint();
    MarkNetworkUpdate();
}

void ConstraintRevolute2D::SetEnableLimit(bool enableLimit)
{
    if (enableLimit == jointDef_.enableLimit)
        return;

    jointDef_.enableLimit = enableLimit;

    if (joint_)
        static_cast<b2RevoluteJoint*>(joint_)->EnableLimit(enableLimit);
    else
        RecreateJoint();

    MarkNetworkUpdate();
}

void ConstraintRevolute2D::SetLowerAngle(float lowerAngle)
{
    if (lowerAngle == jointDef_.lowerAngle)
        return;

    jointDef_.lowerAngle = lowerAngle;

    if (joint_)
        static_cast<b2RevoluteJoint*>(joint_)->SetLimits(lowerAngle, jointDef_.upperAngle);
    else
        RecreateJoint();

    MarkNetworkUpdate();
}

void ConstraintRevolute2D::SetUpperAngle(float upperAngle)
{
    if (upperAngle == jointDef_.upperAngle)
        return;

    jointDef_.upperAngle = upperAngle;

    if (joint_)
        static_cast<b2RevoluteJoint*>(joint_)->SetLimits(jointDef_.lowerAngle, upperAngle);
    else
        RecreateJoint();

    MarkNetworkUpdate();
}

void ConstraintRevolute2D::SetEnableMotor(bool enableMotor)
{
    if (enableMotor == jointDef_.enableMotor)
        return;

    jointDef_.enableMotor = enableMotor;

    if (joint_)
        static_cast<b2RevoluteJoint*>(joint_)->EnableMotor(enableMotor);
    else
        RecreateJoint();

    MarkNetworkUpdate();
}

void ConstraintRevolute2D::SetMotorSpeed(float motorSpeed)
{
    if (motorSpeed == jointDef_.motorSpeed)
        return;

    jointDef_.motorSpeed = motorSpeed;

    if (joint_)
        static_cast<b2RevoluteJoint*>(joint_)->SetMotorSpeed(motorSpeed);
    else
        RecreateJoint();

    MarkNetworkUpdate();
}

void ConstraintRevolute2D::SetMaxMotorTorque(float maxMotorTorque)
{
    if (maxMotorTorque == jointDef_.maxMotorTorque)
        return;

    jointDef_.maxMotorTorque = maxMotorTorque;

    if (joint_)
        static_cast<b2RevoluteJoint*>(joint_)->SetMaxMotorTorque(maxMotorTorque);
    else
        RecreateJoint();

    MarkNetworkUpdate();
}

b2JointDef* ConstraintRevolute2D::GetJointDef()
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
