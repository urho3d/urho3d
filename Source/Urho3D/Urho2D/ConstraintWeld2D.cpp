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

#include "../Urho2D/ConstraintWeld2D.h"
#include "../Core/Context.h"
#include "../Urho2D/PhysicsUtils2D.h"
#include "../Urho2D/RigidBody2D.h"

#include "../DebugNew.h"

namespace Urho3D
{

ConstraintWeld2D::ConstraintWeld2D(Context* context) :
    Constraint2D(context),
    anchor_(Vector2::ZERO)
{
}

ConstraintWeld2D::~ConstraintWeld2D()
{
}

void ConstraintWeld2D::RegisterObject(Context* context)
{
    context->RegisterFactory<ConstraintWeld2D>();

    ACCESSOR_ATTRIBUTE("Is Enabled", IsEnabled, SetEnabled, bool, true, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE("Anchor", GetAnchor, SetAnchor, Vector2, Vector2::ZERO, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE("Frequency Hz", GetFrequencyHz, SetFrequencyHz, float, 0.0f, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE("Damping Ratio", GetDampingRatio, SetDampingRatio, float, 0.0f, AM_DEFAULT);
    COPY_BASE_ATTRIBUTES(Constraint2D);
}

void ConstraintWeld2D::SetAnchor(const Vector2& anchor)
{
    if (anchor == anchor_)
        return;

    anchor_ = anchor;

    RecreateJoint();
    MarkNetworkUpdate();
}

void ConstraintWeld2D::SetFrequencyHz(float frequencyHz)
{
    if (frequencyHz == jointDef_.frequencyHz)
        return;

    jointDef_.frequencyHz = frequencyHz;

    RecreateJoint();
    MarkNetworkUpdate();
}

void ConstraintWeld2D::SetDampingRatio(float dampingRatio)
{
    if (dampingRatio == jointDef_.dampingRatio)
        return;

    jointDef_.dampingRatio = dampingRatio;

    RecreateJoint();
    MarkNetworkUpdate();
}

b2JointDef* ConstraintWeld2D::GetJointDef()
{
    if (!ownerBody_ || !otherBody_)
        return 0;

    b2Body* bodyA = ownerBody_->GetBody();
    b2Body* bodyB = otherBody_->GetBody();
    if (!bodyA || !bodyB)
        return 0;

    jointDef_.Initialize(bodyA, bodyB, ToB2Vec2(anchor_));

    return &jointDef_;
}

}
