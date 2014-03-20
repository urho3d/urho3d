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
#include "ConstraintPulley2D.h"
#include "Context.h"
#include "PhysicsUtils2D.h"
#include "RigidBody2D.h"

#include "DebugNew.h"

namespace Urho3D
{

extern const char* URHO2D_CATEGORY;

ConstraintPulley2D::ConstraintPulley2D(Context* context) : 
    Constraint2D(context),
    ownerBodyGroundAnchor_(-1.0f, 1.0f),
    otherBodyGroundAnchor_(1.0f, 1.0f),
    ownerBodyAnchor_(-1.0f, 0.0f),
    otherBodyAnchor_(1.0f, 0.0f),
    ratio_(1.0f)
{

}

ConstraintPulley2D::~ConstraintPulley2D()
{
}

void ConstraintPulley2D::RegisterObject(Context* context)
{
    context->RegisterFactory<ConstraintPulley2D>(URHO2D_CATEGORY);
    
    REF_ACCESSOR_ATTRIBUTE(ConstraintPulley2D, VAR_VECTOR2, "Owner Body Ground Anchor", GetOwnerBodyGroundAnchor, SetOwnerBodyGroundAnchor, Vector2, Vector2::ZERO, AM_DEFAULT);
    REF_ACCESSOR_ATTRIBUTE(ConstraintPulley2D, VAR_VECTOR2, "Other Body Ground Anchor", GetOtherBodyGroundAnchor, SetOtherBodyGroundAnchor, Vector2, Vector2::ZERO, AM_DEFAULT);
    REF_ACCESSOR_ATTRIBUTE(ConstraintPulley2D, VAR_VECTOR2, "Owner Body Anchor", GetOwnerBodyAnchor, SetOwnerBodyAnchor, Vector2, Vector2::ZERO, AM_DEFAULT);
    REF_ACCESSOR_ATTRIBUTE(ConstraintPulley2D, VAR_VECTOR2, "Other Body Anchor", GetOtherBodyAnchor, SetOtherBodyAnchor, Vector2, Vector2::ZERO, AM_DEFAULT);    
    ACCESSOR_ATTRIBUTE(ConstraintPulley2D, VAR_FLOAT, "Ratio", GetRatio, SetRatio, float, 0.0f, AM_DEFAULT);
    COPY_BASE_ATTRIBUTES(ConstraintPulley2D, Constraint2D);
}

void ConstraintPulley2D::SetOwnerBodyGroundAnchor(const Vector2& groundAnchor)
{
    if (groundAnchor == ownerBodyGroundAnchor_)
        return;

    ownerBodyGroundAnchor_ = groundAnchor;

    RecreateJoint();
    MarkNetworkUpdate();
}

void ConstraintPulley2D::SetOtherBodyGroundAnchor(const Vector2& groundAnchor)
{
    if (groundAnchor == otherBodyGroundAnchor_)
        return;

    otherBodyGroundAnchor_ = groundAnchor;

    RecreateJoint();
    MarkNetworkUpdate();
}

void ConstraintPulley2D::SetOwnerBodyAnchor(const Vector2& anchor)
{
    if (anchor == ownerBodyAnchor_)
        return;

    ownerBodyAnchor_ = anchor;

    RecreateJoint();
    MarkNetworkUpdate();
}

void ConstraintPulley2D::SetOtherBodyAnchor(const Vector2& anchor)
{
    if (anchor == otherBodyAnchor_)
        return;

    otherBodyAnchor_ = anchor;

    RecreateJoint();
    MarkNetworkUpdate();
}

void ConstraintPulley2D::SetRatio(float ratio)
{
    if (ratio == ratio)
        return;

    ratio_ = ratio;

    RecreateJoint();
    MarkNetworkUpdate();
}

b2JointDef* ConstraintPulley2D::CreateJointDef()
{
    if (!ownerBody_ || !otherBody_)
        return 0;

    b2Body* bodyA = ownerBody_->GetBody();
    b2Body* bodyB = otherBody_->GetBody();
    if (!bodyA || !bodyB)
        return 0;

    b2PulleyJointDef* jointDef = new b2PulleyJointDef;
    jointDef->Initialize(bodyA, bodyB, ToB2Vec2(ownerBodyGroundAnchor_), ToB2Vec2(otherBodyGroundAnchor_), ToB2Vec2(ownerBodyAnchor_), ToB2Vec2(otherBodyAnchor_), ratio_);

    return jointDef;
}

}
