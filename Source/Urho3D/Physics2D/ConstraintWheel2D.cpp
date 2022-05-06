// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include "../Precompiled.h"

#include "../Core/Context.h"
#include "../Physics2D/ConstraintWheel2D.h"
#include "../Physics2D/PhysicsUtils2D.h"
#include "../Physics2D/RigidBody2D.h"

#include "../DebugNew.h"

namespace Urho3D
{

extern const char* PHYSICS2D_CATEGORY;

ConstraintWheel2D::ConstraintWheel2D(Context* context) :
    Constraint2D(context),
    anchor_(Vector2::ZERO),
    axis_(Vector2::RIGHT)
{
}

ConstraintWheel2D::~ConstraintWheel2D() = default;

void ConstraintWheel2D::RegisterObject(Context* context)
{
    context->RegisterFactory<ConstraintWheel2D>(PHYSICS2D_CATEGORY);

    URHO3D_ACCESSOR_ATTRIBUTE("Is Enabled", IsEnabled, SetEnabled, bool, true, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Anchor", GetAnchor, SetAnchor, Vector2, Vector2::ZERO, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Axis", GetAxis, SetAxis, Vector2, Vector2::RIGHT, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Enable Motor", GetEnableMotor, SetEnableMotor, bool, false, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Max Motor Torque", GetMaxMotorTorque, SetMaxMotorTorque, float, 0.0f, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Motor Speed", GetMotorSpeed, SetMotorSpeed, float, 0.0f, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Stiffness", GetStiffness, SetStiffness, float, 0.0f, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Damping", GetDamping, SetDamping, float, 0.0f, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Enable Limit", GetEnableLimit, SetEnableLimit, bool, false, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Lower Translation", GetLowerTranslation, SetLowerTranslation, float, 0.0f, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Upper Translation", GetUpperTranslation, SetUpperTranslation, float, 0.0f, AM_DEFAULT);
    URHO3D_COPY_BASE_ATTRIBUTES(Constraint2D);
}

void ConstraintWheel2D::SetAnchor(const Vector2& anchor)
{
    if (anchor == anchor_)
        return;

    anchor_ = anchor;

    RecreateJoint();
    MarkNetworkUpdate();
}

void ConstraintWheel2D::SetAxis(const Vector2& axis)
{
    if (axis == axis_)
        return;

    axis_ = axis;

    RecreateJoint();
    MarkNetworkUpdate();
}


void ConstraintWheel2D::SetEnableMotor(bool enableMotor)
{
    if (enableMotor == jointDef_.enableMotor)
        return;

    jointDef_.enableMotor = enableMotor;

    if (joint_)
        static_cast<b2WheelJoint*>(joint_)->EnableMotor(enableMotor);
    else
        RecreateJoint();

    MarkNetworkUpdate();
}

void ConstraintWheel2D::SetMaxMotorTorque(float maxMotorTorque)
{
    if (maxMotorTorque == jointDef_.maxMotorTorque)
        return;

    jointDef_.maxMotorTorque = maxMotorTorque;

    if (joint_)
        static_cast<b2WheelJoint*>(joint_)->SetMaxMotorTorque(maxMotorTorque);
    else
        RecreateJoint();

    MarkNetworkUpdate();
}

void ConstraintWheel2D::SetMotorSpeed(float motorSpeed)
{
    if (motorSpeed == jointDef_.motorSpeed)
        return;

    jointDef_.motorSpeed = motorSpeed;

    if (joint_)
        static_cast<b2WheelJoint*>(joint_)->SetMotorSpeed(motorSpeed);
    else
        RecreateJoint();

    MarkNetworkUpdate();
}

void ConstraintWheel2D::SetStiffness(float stiffness)
{
    if (stiffness == jointDef_.stiffness)
        return;

    jointDef_.stiffness = stiffness;

    if (joint_)
        static_cast<b2WheelJoint*>(joint_)->SetStiffness(stiffness);
    else
        RecreateJoint();

    MarkNetworkUpdate();
}

void ConstraintWheel2D::SetDamping(float damping)
{
    if (damping == jointDef_.damping)
        return;

    jointDef_.damping = damping;

    if (joint_)
        static_cast<b2WheelJoint*>(joint_)->SetDamping(damping);
    else
        RecreateJoint();

    MarkNetworkUpdate();
}

b2JointDef* ConstraintWheel2D::GetJointDef()
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


bool ConstraintWheel2D::SetLinearStiffness(float frequencyHertz, float dampingRatio)
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
        static_cast<b2WheelJoint*>(joint_)->SetDamping(damping);
        static_cast<b2WheelJoint*>(joint_)->SetStiffness(stiffness);
    }
    else
    {
        RecreateJoint();
    }

    MarkNetworkUpdate();

    return true;
}

void ConstraintWheel2D::SetLowerTranslation(float lowerTranslation)
{
    if (lowerTranslation == jointDef_.lowerTranslation)
        return;

    jointDef_.lowerTranslation = lowerTranslation;

    if (joint_)
        static_cast<b2WheelJoint*>(joint_)->SetLimits(lowerTranslation, jointDef_.upperTranslation);
    else
        RecreateJoint();

    MarkNetworkUpdate();
}

void ConstraintWheel2D::SetUpperTranslation(float upperTranslation)
{
    if (upperTranslation == jointDef_.upperTranslation)
        return;

    jointDef_.upperTranslation = upperTranslation;

    if (joint_)
        static_cast<b2WheelJoint*>(joint_)->SetLimits(jointDef_.lowerTranslation, upperTranslation);
    else
        RecreateJoint();

    MarkNetworkUpdate();
}

void ConstraintWheel2D::SetEnableLimit(bool enableLimit)
{
    if (enableLimit == jointDef_.enableLimit)
        return;

    jointDef_.enableLimit = enableLimit;

    if (joint_)
        static_cast<b2WheelJoint*>(joint_)->EnableLimit(enableLimit);
    else
        RecreateJoint();

    MarkNetworkUpdate();
}

}
