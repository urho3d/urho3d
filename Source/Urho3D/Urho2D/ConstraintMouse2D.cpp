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

#include "../Urho2D/ConstraintMouse2D.h"
#include "../Core/Context.h"
#include "../Urho2D/PhysicsUtils2D.h"
#include "../Urho2D/RigidBody2D.h"

#include "../DebugNew.h"

namespace Urho3D
{

ConstraintMouse2D::ConstraintMouse2D(Context* context) :
    Constraint2D(context),
    target_(Vector2::ZERO),
    targetSetted_(false)
{
}

ConstraintMouse2D::~ConstraintMouse2D()
{
}

void ConstraintMouse2D::RegisterObject(Context* context)
{
    context->RegisterFactory<ConstraintMouse2D>();

    ACCESSOR_ATTRIBUTE("Is Enabled", IsEnabled, SetEnabled, bool, true, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE("Target", GetTarget, SetTarget, Vector2, Vector2::ZERO, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE("Max Force", GetMaxForce, SetMaxForce, float, 0.0f, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE("Frequency Hz", GetFrequencyHz, SetFrequencyHz, float, 5.0f, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE("Damping Ratio", GetDampingRatio, SetDampingRatio, float, 0.7f, AM_DEFAULT);
    COPY_BASE_ATTRIBUTES(Constraint2D);
}

void ConstraintMouse2D::SetTarget(const Vector2& target)
{
    if (target == target_)
        return;

    target_ = target;
    if (joint_ && targetSetted_)
    {
        b2MouseJoint* mouseJoint = (b2MouseJoint*)joint_;
        mouseJoint->SetTarget(ToB2Vec2(target_));

        MarkNetworkUpdate();
        return;
    }

    targetSetted_ = true;

    RecreateJoint();
    MarkNetworkUpdate();
}

void ConstraintMouse2D::SetMaxForce(float maxForce)
{
    if (maxForce == jointDef_.maxForce)
        return;

    jointDef_.maxForce = maxForce;

    RecreateJoint();
    MarkNetworkUpdate();
}

void ConstraintMouse2D::SetFrequencyHz(float frequencyHz)
{
    if (frequencyHz == jointDef_.frequencyHz)
        return;

    jointDef_.frequencyHz = frequencyHz;

    RecreateJoint();
    MarkNetworkUpdate();
}

void ConstraintMouse2D::SetDampingRatio(float dampingRatio)
{
    if (dampingRatio == jointDef_.dampingRatio)
        return;

    jointDef_.dampingRatio = dampingRatio;

    RecreateJoint();
    MarkNetworkUpdate();
}

b2JointDef* ConstraintMouse2D::GetJointDef()
{
    if (!ownerBody_ || !otherBody_)
        return 0;

    b2Body* bodyA = otherBody_->GetBody();
    b2Body* bodyB = ownerBody_->GetBody();
    if (!bodyA || !bodyB)
        return 0;

    jointDef_.bodyA = bodyA;
    jointDef_.bodyB = bodyB;
    jointDef_.collideConnected = collideConnected_;

    jointDef_.target = ToB2Vec2(target_);

    return &jointDef_;
}

}
