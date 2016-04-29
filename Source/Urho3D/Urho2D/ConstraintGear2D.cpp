//
// Copyright (c) 2008-2016 the Urho3D project.
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
#include "../Urho2D/ConstraintGear2D.h"
#include "../Urho2D/PhysicsUtils2D.h"
#include "../Urho2D/RigidBody2D.h"

#include "../DebugNew.h"

namespace Urho3D
{

extern const char* URHO2D_CATEGORY;

ConstraintGear2D::ConstraintGear2D(Context* context) :
    Constraint2D(context)
{
}

ConstraintGear2D::~ConstraintGear2D()
{
}

void ConstraintGear2D::RegisterObject(Context* context)
{
    context->RegisterFactory<ConstraintGear2D>(URHO2D_CATEGORY);

    URHO3D_ACCESSOR_ATTRIBUTE("Is Enabled", IsEnabled, SetEnabled, bool, true, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Ratio", GetRatio, SetRatio, float, 0.0f, AM_DEFAULT);
    URHO3D_COPY_BASE_ATTRIBUTES(Constraint2D);
}

void ConstraintGear2D::SetOwnerConstraint(Constraint2D* constraint)
{
    if (constraint == ownerConstraint_)
        return;

    if (ownerConstraint_)
        ownerConstraint_->SetAttachedConstraint(0);

    ownerConstraint_ = constraint;

    if (ownerConstraint_)
        ownerConstraint_->SetAttachedConstraint(this);

    RecreateJoint();
    MarkNetworkUpdate();
}

void ConstraintGear2D::SetOtherConstraint(Constraint2D* constraint)
{
    WeakPtr<Constraint2D> constraintPtr(constraint);
    if (constraintPtr == otherConstraint_)
        return;

    if (otherConstraint_)
        otherConstraint_->SetAttachedConstraint(0);

    otherConstraint_ = constraintPtr;

    if (otherConstraint_)
        otherConstraint_->SetAttachedConstraint(this);

    RecreateJoint();
    MarkNetworkUpdate();
}

void ConstraintGear2D::SetRatio(float ratio)
{
    if (ratio == jointDef_.ratio)
        return;

    jointDef_.ratio = ratio;

    RecreateJoint();
    MarkNetworkUpdate();
}

b2JointDef* ConstraintGear2D::GetJointDef()
{
    if (!ownerBody_ || !otherBody_)
        return 0;

    b2Body* bodyA = ownerBody_->GetBody();
    b2Body* bodyB = otherBody_->GetBody();
    if (!bodyA || !bodyB)
        return 0;

    if (!ownerConstraint_ || !otherConstraint_)
        return 0;

    b2Joint* jointA = ownerConstraint_->GetJoint();
    b2Joint* jointB = otherConstraint_->GetJoint();
    if (!jointA || !jointB)
        return 0;

    InitializeJointDef(&jointDef_);
    jointDef_.joint1 = jointA;
    jointDef_.joint2 = jointB;

    return &jointDef_;
}

}
