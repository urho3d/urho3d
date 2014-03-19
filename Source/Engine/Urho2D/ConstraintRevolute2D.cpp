//
// Copyright (c) 2008-2014 the Urho3D project.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#include "Precompiled.h"
#include "ConstraintRevolute2D.h"
#include "Context.h"
#include "PhysicsUtils2D.h"
#include "RigidBody2D.h"

#include "DebugNew.h"

namespace Urho3D
{

extern const char* URHO2D_CATEGORY;

ConstraintRevolute2D::ConstraintRevolute2D(Context* context) : Constraint2D(context),
    anchorPoint_(Vector2::ZERO),
    lowerAngle_(0.0f),
    upperAngle_(0.0f),
    maxMotorTorque_(0.0f),
    motorSpeed_(0.0f),
    enableLimit_(false),
    enableMotor_(false)
{
}

ConstraintRevolute2D::~ConstraintRevolute2D()
{
}

void ConstraintRevolute2D::RegisterObject(Context* context)
{
    context->RegisterFactory<ConstraintRevolute2D>(URHO2D_CATEGORY);
    
    REF_ACCESSOR_ATTRIBUTE(ConstraintRevolute2D, VAR_VECTOR2, "Anchor Point", GetAnchorPoint, SetAnchorPoint, Vector2, Vector2::ZERO, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(ConstraintRevolute2D, VAR_BOOL, "Enable Limit", GetEnableLimit, SetEnableLimit, bool, false, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(ConstraintRevolute2D, VAR_FLOAT, "Lower Angle", GetLowerAngle, SetLowerAngle, float, 0.0f, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(ConstraintRevolute2D, VAR_FLOAT, "Upper Angle", GetUpperAngle, SetUpperAngle, float, 0.0f, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(ConstraintRevolute2D, VAR_BOOL, "Enable Motor", GetEnableMotor, SetEnableMotor, bool, false, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(ConstraintRevolute2D, VAR_FLOAT, "Motor Speed", GetMotorSpeed, SetMotorSpeed, float, 0.0f, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(ConstraintRevolute2D, VAR_FLOAT, "Max Motor Torque", GetMaxMotorTorque, SetMaxMotorTorque, float, 0.0f, AM_DEFAULT);
    COPY_BASE_ATTRIBUTES(ConstraintRevolute2D, Constraint2D);
}

void ConstraintRevolute2D::SetAnchorPoint(const Vector2& anchor)
{
    if (anchor == anchorPoint_)
        return;

    anchorPoint_ = anchor;

    RecreateJoint();
    MarkNetworkUpdate();
}

void ConstraintRevolute2D::SetEnableLimit(bool enableLimit)
{
    if (enableLimit == enableLimit_)
        return;

    enableLimit_ = enableLimit;

    RecreateJoint();
    MarkNetworkUpdate();
}

void ConstraintRevolute2D::SetLowerAngle(float lowerAngle)
{
    if (lowerAngle == lowerAngle_)
        return;

    lowerAngle_ = lowerAngle;

    RecreateJoint();
    MarkNetworkUpdate();
}

void ConstraintRevolute2D::SetUpperAngle(float upperAngle)
{
    if (upperAngle == upperAngle_)
        return;

    upperAngle_ = upperAngle;

    RecreateJoint();
    MarkNetworkUpdate();
}

void ConstraintRevolute2D::SetEnableMotor(bool enableMotor)
{
    if (enableMotor == enableMotor_)
        return;

    enableMotor_ = enableMotor;

    RecreateJoint();
    MarkNetworkUpdate();
}

void ConstraintRevolute2D::SetMotorSpeed(float motorSpeed)
{
    if (motorSpeed == motorSpeed_)
        return;

    motorSpeed_ = motorSpeed;

    RecreateJoint();
    MarkNetworkUpdate();
}

void ConstraintRevolute2D::SetMaxMotorTorque(float maxMotorTorque)
{
    if (maxMotorTorque == maxMotorTorque_)
        return;

    maxMotorTorque_ = maxMotorTorque;

    RecreateJoint();
    MarkNetworkUpdate();
}

b2JointDef* ConstraintRevolute2D::CreateJointDef()
{
    if (!ownerBody_ || !otherBody_)
        return 0;

    b2Body* bodyA = ownerBody_->GetBody();
    b2Body* bodyB = otherBody_->GetBody();
    if (!bodyA || !bodyB)
        return 0;

    b2RevoluteJointDef* jointDef = new b2RevoluteJointDef;
    jointDef->Initialize(bodyA, bodyB, ToB2Vec2(anchorPoint_));
    jointDef->enableLimit = enableLimit_;
    jointDef->lowerAngle = lowerAngle_;
    jointDef->upperAngle = upperAngle_;
    jointDef->enableMotor = enableMotor_;
    jointDef->motorSpeed = motorSpeed_;
    jointDef->maxMotorTorque = maxMotorTorque_;

    return jointDef;
}

}
