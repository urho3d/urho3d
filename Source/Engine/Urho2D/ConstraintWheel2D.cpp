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
#include "ConstraintWheel2D.h"
#include "Context.h"
#include "PhysicsUtils2D.h"
#include "RigidBody2D.h"

#include "DebugNew.h"

namespace Urho3D
{

ConstraintWheel2D::ConstraintWheel2D(Context* context) :
    Constraint2D(context),
    anchor_(Vector2::ZERO),
    axis_(Vector2::RIGHT),    
    enableMotor_(false), 
    maxMotorTorque_(0.0f),
    motorSpeed_(0.0f),
    frequencyHz_(2.0f),
    dampingRatio_(0.7f)
{
}

ConstraintWheel2D::~ConstraintWheel2D()
{
}

void ConstraintWheel2D::RegisterObject(Context* context)
{
    context->RegisterFactory<ConstraintWheel2D>();
    
    REF_ACCESSOR_ATTRIBUTE(ConstraintWheel2D, VAR_VECTOR2, "Anchor", GetAnchor, SetAnchor, Vector2, Vector2::ZERO, AM_DEFAULT);
    REF_ACCESSOR_ATTRIBUTE(ConstraintWheel2D, VAR_VECTOR2, "Axis", GetAxis, SetAxis, Vector2, Vector2::RIGHT, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(ConstraintWheel2D, VAR_BOOL, "Enable Motor", GetEnableMotor, SetEnableMotor, bool, false, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(ConstraintWheel2D, VAR_FLOAT, "Max Motor Torque", GetMaxMotorTorque, SetMaxMotorTorque, float, 0.0f, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(ConstraintWheel2D, VAR_FLOAT, "Motor Speed", GetMotorSpeed, SetMotorSpeed, float, 0.0f, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(ConstraintWheel2D, VAR_FLOAT, "Frequency Hz", GetFrequencyHz, SetFrequencyHz, float, 2.0f, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(ConstraintWheel2D, VAR_FLOAT, "Damping Ratio", GetDampingRatio, SetDampingRatio, float, 0.7f, AM_DEFAULT);

    COPY_BASE_ATTRIBUTES(ConstraintWheel2D, Constraint2D);
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
    if (enableMotor == enableMotor_)
        return;

    enableMotor_ = enableMotor;

    RecreateJoint();
    MarkNetworkUpdate();
}

void ConstraintWheel2D::SetMaxMotorTorque(float maxMotorTorque)
{
    if (maxMotorTorque == maxMotorTorque_)
        return;

    maxMotorTorque_ = maxMotorTorque;

    RecreateJoint();
    MarkNetworkUpdate();
}

void ConstraintWheel2D::SetMotorSpeed(float motorSpeed)
{
    if (motorSpeed == motorSpeed_)
        return;

    motorSpeed_ = motorSpeed;

    RecreateJoint();
    MarkNetworkUpdate();
}

void ConstraintWheel2D::SetFrequencyHz(float frequencyHz)
{
    if (frequencyHz == frequencyHz_)
        return;

    frequencyHz_ = frequencyHz;

    RecreateJoint();
    MarkNetworkUpdate();
}

void ConstraintWheel2D::SetDampingRatio(float dampingRatio)
{
    if (dampingRatio == dampingRatio_)
        return;

    dampingRatio_ = dampingRatio;

    RecreateJoint();
    MarkNetworkUpdate();
}

b2JointDef* ConstraintWheel2D::CreateJointDef()
{
    if (!ownerBody_ || !otherBody_)
        return 0;

    b2Body* bodyA = ownerBody_->GetBody();
    b2Body* bodyB = otherBody_->GetBody();
    if (!bodyA || !bodyB)
        return 0;

    b2WheelJointDef* jointDef = new b2WheelJointDef;
    jointDef->Initialize(bodyA, bodyB, ToB2Vec2(anchor_), ToB2Vec2(axis_));
    jointDef->enableMotor = enableMotor_;
    jointDef->maxMotorTorque = maxMotorTorque_;
    jointDef->motorSpeed = motorSpeed_;
    jointDef->frequencyHz = frequencyHz_;
    jointDef->dampingRatio = dampingRatio_;    

    return jointDef;
}

}
