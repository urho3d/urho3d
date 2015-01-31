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

#include "../Urho2D/ConstraintMotor2D.h"
#include "../Core/Context.h"
#include "../Urho2D/PhysicsUtils2D.h"
#include "../Urho2D/RigidBody2D.h"

#include "../DebugNew.h"

namespace Urho3D
{

ConstraintMotor2D::ConstraintMotor2D(Context* context) :
    Constraint2D(context),
    linearOffset_(Vector2::ZERO)
{

}

ConstraintMotor2D::~ConstraintMotor2D()
{
}

void ConstraintMotor2D::RegisterObject(Context* context)
{
    context->RegisterFactory<ConstraintMotor2D>();
    
    ACCESSOR_ATTRIBUTE("Is Enabled", IsEnabled, SetEnabled, bool, true, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE("Linear Offset", GetLinearOffset, SetLinearOffset, Vector2, Vector2::ZERO, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE("Angular Offset", GetAngularOffset, SetAngularOffset, float, 0.0f, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE("Max Force", GetMaxForce, SetMaxForce, float, 1.0f, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE("Max Torque", GetMaxTorque, SetMaxTorque, float, 1.0f, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE("Correction Factor", GetCorrectionFactor, SetCorrectionFactor, float, 0.3f, AM_DEFAULT);
    COPY_BASE_ATTRIBUTES(Constraint2D);
}

void ConstraintMotor2D::SetLinearOffset(const Vector2& linearOffset)
{
    if (linearOffset == linearOffset_)
        return;

    linearOffset_ = linearOffset;
    
    RecreateJoint();
    MarkNetworkUpdate();
}

void ConstraintMotor2D::SetAngularOffset(float angularOffset)
{
    if (angularOffset == jointDef_.angularOffset)
        return;

    jointDef_.angularOffset = angularOffset;

    RecreateJoint();
    MarkNetworkUpdate();
}

void ConstraintMotor2D::SetMaxForce(float maxForce)
{
    if (maxForce == jointDef_.maxForce)
        return;

    jointDef_.maxForce = maxForce;

    RecreateJoint();
    MarkNetworkUpdate();
}

void ConstraintMotor2D::SetMaxTorque(float maxTorque)
{
    if (maxTorque == jointDef_.maxTorque)
        return;

    jointDef_.maxTorque = maxTorque;

    RecreateJoint();
    MarkNetworkUpdate();
}

void ConstraintMotor2D::SetCorrectionFactor(float correctionFactor)
{
    if (correctionFactor == jointDef_.correctionFactor)
        return;

    jointDef_.correctionFactor = correctionFactor;

    RecreateJoint();
    MarkNetworkUpdate();
}

b2JointDef* ConstraintMotor2D::GetJointDef()
{
    if (!ownerBody_ || !otherBody_)
        return 0;

    b2Body* bodyA = ownerBody_->GetBody();
    b2Body* bodyB = otherBody_->GetBody();
    if (!bodyA || !bodyB)
        return 0;

    jointDef_.Initialize(bodyA, bodyB);
    jointDef_.linearOffset = ToB2Vec2(linearOffset_);

    return &jointDef_;
}

}
