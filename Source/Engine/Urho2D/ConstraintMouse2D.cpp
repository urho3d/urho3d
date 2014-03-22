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
#include "ConstraintMouse2D.h"
#include "Context.h"
#include "PhysicsUtils2D.h"
#include "RigidBody2D.h"

#include "DebugNew.h"

namespace Urho3D
{

ConstraintMouse2D::ConstraintMouse2D(Context* context) :
    Constraint2D(context),
    target_(Vector2::ZERO),
    maxForce_(0.0f),
    frequencyHz_(5.0f),
    dampingRatio_(0.7f)
{
}

ConstraintMouse2D::~ConstraintMouse2D()
{
}

void ConstraintMouse2D::RegisterObject(Context* context)
{
    context->RegisterFactory<ConstraintMouse2D>();

    REF_ACCESSOR_ATTRIBUTE(ConstraintMouse2D, VAR_VECTOR2, "Target", GetTarget, SetTarget, Vector2, Vector2::ZERO, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(ConstraintMouse2D, VAR_FLOAT, "Max Force", GetMaxForce, SetMaxForce, float, 0.0f, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(ConstraintMouse2D, VAR_FLOAT, "Frequency Hz", GetFrequencyHz, SetFrequencyHz, float, 0.0f, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(ConstraintMouse2D, VAR_FLOAT, "Damping Ratio", GetDampingRatio, SetDampingRatio, float, 0.0f, AM_DEFAULT);
    COPY_BASE_ATTRIBUTES(ConstraintMouse2D, Constraint2D);
}

void ConstraintMouse2D::SetTarget(const Vector2& target)
{
    if (target == target_)
        return;

    target_ = target;

    RecreateJoint();
    MarkNetworkUpdate();
}

void ConstraintMouse2D::SetMaxForce(float maxForce)
{
    if (maxForce == maxForce_)
        return;

    maxForce_ = maxForce;

    RecreateJoint();
    MarkNetworkUpdate();
}

void ConstraintMouse2D::SetFrequencyHz(float frequencyHz)
{
    if (frequencyHz == frequencyHz_)
        return;

    frequencyHz_ = frequencyHz;

    RecreateJoint();
    MarkNetworkUpdate();
}

void ConstraintMouse2D::SetDampingRatio(float dampingRatio)
{
    if (dampingRatio == dampingRatio_)
        return;

    dampingRatio_ = dampingRatio;

    RecreateJoint();
    MarkNetworkUpdate();
}

b2JointDef* ConstraintMouse2D::CreateJointDef()
{
    if (!ownerBody_ || !otherBody_)
        return 0;

    b2Body* bodyA = ownerBody_->GetBody();
    b2Body* bodyB = otherBody_->GetBody();
    if (!bodyA || !bodyB)
        return 0;

    b2MouseJointDef* jointDef = new b2MouseJointDef;
    InitializeJointDef(jointDef);

    jointDef->target = ToB2Vec2(target_);
    jointDef->maxForce = maxForce_;
    jointDef->frequencyHz = frequencyHz_;
    jointDef->dampingRatio = dampingRatio_;

    return jointDef;
}

}
