//
// Copyright (c) 2008-2015 the Urho3D project.
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

#include "../Precompiled.h"

#include "../Core/Context.h"
#include "../Urho2D/ConstraintPrismatic2D.h"
#include "../Urho2D/PhysicsUtils2D.h"
#include "../Urho2D/RigidBody2D.h"

#include "../DebugNew.h"

namespace Urho3D
{

extern const char* URHO2D_CATEGORY;

ConstraintPrismatic2D::ConstraintPrismatic2D(Context* context) :
    Constraint2D(context),
    anchor_(Vector2::ZERO),
    axis_(Vector2::RIGHT)
{
}

ConstraintPrismatic2D::~ConstraintPrismatic2D()
{
}

void ConstraintPrismatic2D::RegisterObject(Context* context)
{
    context->RegisterFactory<ConstraintPrismatic2D>(URHO2D_CATEGORY);

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

    RecreateJoint();
    MarkNetworkUpdate();
}

void ConstraintPrismatic2D::SetLowerTranslation(float lowerTranslation)
{
    if (lowerTranslation == jointDef_.lowerTranslation)
        return;

    jointDef_.lowerTranslation = lowerTranslation;

    RecreateJoint();
    MarkNetworkUpdate();
}

void ConstraintPrismatic2D::SetUpperTranslation(float upperTranslation)
{
    if (upperTranslation == jointDef_.upperTranslation)
        return;

    jointDef_.upperTranslation = upperTranslation;

    RecreateJoint();
    MarkNetworkUpdate();
}

void ConstraintPrismatic2D::SetEnableMotor(bool enableMotor)
{
    if (enableMotor == jointDef_.enableMotor)
        return;

    jointDef_.enableMotor = enableMotor;

    RecreateJoint();
    MarkNetworkUpdate();
}

void ConstraintPrismatic2D::SetMaxMotorForce(float maxMotorForce)
{
    if (maxMotorForce == jointDef_.maxMotorForce)
        return;

    jointDef_.maxMotorForce = maxMotorForce;

    RecreateJoint();
    MarkNetworkUpdate();
}

void ConstraintPrismatic2D::SetMotorSpeed(float motorSpeed)
{
    if (motorSpeed == jointDef_.motorSpeed)
        return;

    jointDef_.motorSpeed = motorSpeed;

    RecreateJoint();
    MarkNetworkUpdate();
}

b2JointDef* ConstraintPrismatic2D::GetJointDef()
{
    if (!ownerBody_ || !otherBody_)
        return 0;

    b2Body* bodyA = ownerBody_->GetBody();
    b2Body* bodyB = otherBody_->GetBody();
    if (!bodyA || !bodyB)
        return 0;

    jointDef_.Initialize(bodyA, bodyB, ToB2Vec2(anchor_), ToB2Vec2(axis_));

    return &jointDef_;
}

}
