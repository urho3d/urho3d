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
#include "ConstraintMotor2D.h"
#include "Context.h"
#include "PhysicsUtils2D.h"
#include "RigidBody2D.h"

#include "DebugNew.h"

namespace Urho3D
{

ConstraintMotor2D::ConstraintMotor2D(Context* context) :
    Constraint2D(context),
    ownerBodyAnchor_(Vector2::ZERO),
    otherBodyAnchor_(Vector2::ZERO),
    maxLength_(0.0f)
{

}

ConstraintMotor2D::~ConstraintMotor2D()
{
}

void ConstraintMotor2D::RegisterObject(Context* context)
{
    context->RegisterFactory<ConstraintMotor2D>();
    
    REF_ACCESSOR_ATTRIBUTE(ConstraintMotor2D, VAR_VECTOR2, "Owner Body Anchor", GetOwnerBodyAnchor, SetOwnerBodyAnchor, Vector2, Vector2::ZERO, AM_DEFAULT);
    REF_ACCESSOR_ATTRIBUTE(ConstraintMotor2D, VAR_VECTOR2, "Other Body Anchor", GetOtherBodyAnchor, SetOtherBodyAnchor, Vector2, Vector2::ZERO, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(ConstraintMotor2D, VAR_FLOAT, "Max Length", GetMaxLength, SetMaxLength, float, 0.0f, AM_DEFAULT);
    COPY_BASE_ATTRIBUTES(ConstraintMotor2D, Constraint2D);
}

void ConstraintMotor2D::SetOwnerBodyAnchor(const Vector2& anchor)
{
    if (anchor == ownerBodyAnchor_)
        return;

    ownerBodyAnchor_ = anchor;

    RecreateJoint();
    MarkNetworkUpdate();
}

void ConstraintMotor2D::SetOtherBodyAnchor(const Vector2& anchor)
{
    if (anchor == otherBodyAnchor_)
        return;

    otherBodyAnchor_ = anchor;

    RecreateJoint();
    MarkNetworkUpdate();
}

void ConstraintMotor2D::SetMaxLength(float maxLength)
{
    maxLength = Max(0.0f, maxLength);
    if (maxLength == maxLength_)
        return;

    maxLength_ = maxLength;

    RecreateJoint();
    MarkNetworkUpdate();
}

b2JointDef* ConstraintMotor2D::CreateJointDef()
{
    if (!ownerBody_ || !otherBody_)
        return 0;

    b2Body* bodyA = ownerBody_->GetBody();
    b2Body* bodyB = otherBody_->GetBody();
    if (!bodyA || !bodyB)
        return 0;

    b2RopeJointDef* jointDef = new b2RopeJointDef;
    InitializeJointDef(jointDef);

    jointDef->localAnchorA = ToB2Vec2(ownerBodyAnchor_);
    jointDef->localAnchorB = ToB2Vec2(otherBodyAnchor_);
    jointDef->maxLength = maxLength_;

    return jointDef;
}

}
