//
// Copyright (c) 2008-2020 the Urho3D project.
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
#include "../IO/Log.h"
#include "../Scene/Node.h"
#include "../Scene/Scene.h"
#include "../Urho2D/Constraint2D.h"
#include "../Urho2D/PhysicsUtils2D.h"
#include "../Urho2D/RigidBody2D.h"
#include "../Urho2D/PhysicsWorld2D.h"

#include "../DebugNew.h"

namespace Urho3D
{

extern const char* URHO2D_CATEGORY;

Constraint2D::Constraint2D(Context* context) :
    Component(context)
{

}

Constraint2D::~Constraint2D()
{
    ReleaseJoint();
}

void Constraint2D::RegisterObject(Context* context)
{
    URHO3D_ACCESSOR_ATTRIBUTE("Collide Connected", GetCollideConnected, SetCollideConnected, bool, false, AM_DEFAULT);
    URHO3D_ATTRIBUTE_EX("Other Body NodeID", unsigned, otherBodyNodeID_, MarkOtherBodyNodeIDDirty, 0, AM_DEFAULT | AM_NODEID);
}

void Constraint2D::ApplyAttributes()
{
    // If other body node ID dirty, try to find it now and apply
    if (otherBodyNodeIDDirty_)
    {
        Scene* scene = GetScene();
        if (scene)
        {
            Node* otherNode = scene->GetNode(otherBodyNodeID_);
            if (otherNode)
                SetOtherBody(otherNode->GetComponent<RigidBody2D>());
        }
        otherBodyNodeIDDirty_ = false;
    }
}

void Constraint2D::OnSetEnabled()
{
    if (IsEnabledEffective())
        CreateJoint();
    else
        ReleaseJoint();
}

void Constraint2D::CreateJoint()
{
    if (joint_)
        return;

    b2JointDef* jointDef = GetJointDef();
    if (jointDef)
    {
        joint_ = physicsWorld_->GetWorld()->CreateJoint(jointDef);
        joint_->SetUserData(this);

        if (ownerBody_)
            ownerBody_->AddConstraint2D(this);

        if (otherBody_)
            otherBody_->AddConstraint2D(this);
    }
}

void Constraint2D::ReleaseJoint()
{
    if (!joint_)
        return;

    if (ownerBody_)
        ownerBody_->RemoveConstraint2D(this);

    if (otherBody_)
        otherBody_->RemoveConstraint2D(this);

    if (physicsWorld_)
        physicsWorld_->GetWorld()->DestroyJoint(joint_);

    joint_ = nullptr;
}

void Constraint2D::SetOtherBody(RigidBody2D* body)
{
    if (body == otherBody_)
        return;

    otherBody_ = body;

    Node* otherNode = body ? body->GetNode() : nullptr;
    otherBodyNodeID_ = otherNode ? otherNode->GetID() : 0;

    RecreateJoint();
    MarkNetworkUpdate();
}

void Constraint2D::SetCollideConnected(bool collideConnected)
{
    if (collideConnected == collideConnected_)
        return;

    collideConnected_ = collideConnected;

    RecreateJoint();
    MarkNetworkUpdate();
}

void Constraint2D::SetAttachedConstraint(Constraint2D* constraint)
{
    attachedConstraint_ = constraint;
}

void Constraint2D::OnNodeSet(Node* node)
{
    Component::OnNodeSet(node);

    if (node)
    {
        ownerBody_ = node->GetComponent<RigidBody2D>();
        if (!ownerBody_)
        {
            URHO3D_LOGERROR("No right body component in node, can not create constraint");
            return;
        }
    }
}

void Constraint2D::OnSceneSet(Scene* scene)
{
    if (scene)
    {
        physicsWorld_ = scene->GetDerivedComponent<PhysicsWorld2D>();
        if (!physicsWorld_)
            physicsWorld_ = scene->CreateComponent<PhysicsWorld2D>();
    }
}

void Constraint2D::InitializeJointDef(b2JointDef* jointDef)
{
    jointDef->bodyA = ownerBody_->GetBody();
    jointDef->bodyB = otherBody_->GetBody();
    jointDef->collideConnected = collideConnected_;
}

void Constraint2D::RecreateJoint()
{
    if (attachedConstraint_)
        attachedConstraint_->ReleaseJoint();

    ReleaseJoint();
    CreateJoint();

    if (attachedConstraint_)
        attachedConstraint_->CreateJoint();
}

}
