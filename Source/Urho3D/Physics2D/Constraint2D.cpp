// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include "../Precompiled.h"

#include "../Core/Context.h"
#include "../IO/Log.h"
#include "../Physics2D/Constraint2D.h"
#include "../Physics2D/PhysicsUtils2D.h"
#include "../Physics2D/PhysicsWorld2D.h"
#include "../Physics2D/RigidBody2D.h"
#include "../Scene/Node.h"
#include "../Scene/Scene.h"

#include "../DebugNew.h"

namespace Urho3D
{

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
        joint_->GetUserData().pointer = (uintptr_t)this;

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
