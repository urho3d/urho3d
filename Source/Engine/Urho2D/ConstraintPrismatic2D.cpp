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
#include "ConstraintPrismatic2D.h"
#include "Context.h"
#include "PhysicsUtils2D.h"
#include "RigidBody2D.h"

#include "DebugNew.h"

namespace Urho3D
{

ConstraintPrismatic2D::ConstraintPrismatic2D(Context* context) :
    Constraint2D(context),
    anchor_(Vector2::ZERO),
    axis_(Vector2::RIGHT),
    enableLimit_(false),
    lowerTranslation_(0),
    upperTranslation_(0),
    enableMotor_(false),
    maxMotorForce_(0),
    motorSpeed_(0)
{
}

ConstraintPrismatic2D::~ConstraintPrismatic2D()
{    
}

void ConstraintPrismatic2D::RegisterObject(Context* context)
{
    context->RegisterFactory<ConstraintPrismatic2D>();
    
    REF_ACCESSOR_ATTRIBUTE(ConstraintPrismatic2D, VAR_VECTOR2, "Anchor", GetAnchor, SetAnchor, Vector2, Vector2::ZERO, AM_DEFAULT);
    REF_ACCESSOR_ATTRIBUTE(ConstraintPrismatic2D, VAR_VECTOR2, "Axis", GetAxis, SetAxis, Vector2, Vector2::RIGHT, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(ConstraintPrismatic2D, VAR_BOOL, "Enable Limit", GetEnableLimit, SetEnableLimit, bool, false, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(ConstraintPrismatic2D, VAR_FLOAT, "Lower translation", GetLowerTranslation, SetLowerTranslation, float, 0.0f, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(ConstraintPrismatic2D, VAR_FLOAT, "Upper translation", GetUpperTranslation, SetUpperTranslation, float, 0.0f, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(ConstraintPrismatic2D, VAR_BOOL, "Enable Motor", GetEnableMotor, SetEnableMotor, bool, false, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(ConstraintPrismatic2D, VAR_FLOAT, "Max Motor Force", GetMaxMotorForce, SetMaxMotorForce, float, 2.0f, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(ConstraintPrismatic2D, VAR_FLOAT, "Motor Speed", GetMotorSpeed, SetMotorSpeed, float, 0.7f, AM_DEFAULT);

    COPY_BASE_ATTRIBUTES(ConstraintPrismatic2D, Constraint2D);
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
}void ConstraintPrismatic2D::SetEnableLimit(bool enableLimit)
{
    if (enableLimit == enableLimit_)
        return;

    enableLimit_ = enableLimit;

    RecreateJoint();
    MarkNetworkUpdate();
}

void ConstraintPrismatic2D::SetLowerTranslation(float lowerTranslation)
{
    if (lowerTranslation == lowerTranslation_)
        return;

    lowerTranslation_ = lowerTranslation;

    RecreateJoint();
    MarkNetworkUpdate();
}

void ConstraintPrismatic2D::SetUpperTranslation(float upperTranslation)
{
    if (upperTranslation == upperTranslation_)
        return;

    upperTranslation_ = upperTranslation;

    RecreateJoint();
    MarkNetworkUpdate();
}

void ConstraintPrismatic2D::SetEnableMotor(bool enableMotor)
{
    if (enableMotor == enableMotor_)
        return;

    enableMotor_ = enableMotor;

    RecreateJoint();
    MarkNetworkUpdate();
}

void ConstraintPrismatic2D::SetMaxMotorForce(float maxMotorForce)
{
    if (maxMotorForce == maxMotorForce_)
        return;

    maxMotorForce_ = maxMotorForce;

    RecreateJoint();
    MarkNetworkUpdate();
}

void ConstraintPrismatic2D::SetMotorSpeed(float motorSpeed)
{
    if (motorSpeed == motorSpeed_)
        return;

    motorSpeed_ = motorSpeed;

    RecreateJoint();
    MarkNetworkUpdate();
}


b2JointDef* ConstraintPrismatic2D::CreateJointDef()
{
    if (!ownerBody_ || !otherBody_)
        return 0;

    b2Body* bodyA = ownerBody_->GetBody();
    b2Body* bodyB = otherBody_->GetBody();
    if (!bodyA || !bodyB)
        return 0;

    b2PrismaticJointDef* jointDef = new b2PrismaticJointDef;
    jointDef->Initialize(bodyA, bodyB, ToB2Vec2(anchor_), ToB2Vec2(axis_));
    jointDef->enableLimit = enableLimit_;
    jointDef->lowerTranslation = lowerTranslation_;
    jointDef->upperTranslation = upperTranslation_;
    jointDef->enableMotor = enableMotor_;
    jointDef->maxMotorForce = maxMotorForce_;
    jointDef->motorSpeed = motorSpeed_;    

    return jointDef;
}

}
