//
// Urho3D Engine
// Copyright (c) 2008-2012 Lasse Öörni
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
#include "Context.h"
#include "DebugRenderer.h"
#include "Constraint.h"
#include "Log.h"
#include "PhysicsUtils.h"
#include "PhysicsWorld.h"
#include "Profiler.h"
#include "RigidBody.h"
#include "Scene.h"

#include "BulletDynamics/ConstraintSolver/btPoint2PointConstraint.h"
#include "BulletDynamics/ConstraintSolver/btHingeConstraint.h"
#include <BulletDynamics/Dynamics/btDiscreteDynamicsWorld.h>

#include "DebugNew.h"

static const String typeNames[] =
{
    "Point",
    "Hinge",
    ""
};

static const float DEFAULT_LOW_LIMIT = -180.0f;
static const float DEFAULT_HIGH_LIMIT = 180.0f;

OBJECTTYPESTATIC(Constraint);

Constraint::Constraint(Context* context) :
    Component(context),
    constraint_(0),
    type_(CONSTRAINT_POINT),
    position_(Vector3::ZERO),
    axis_(Vector3::RIGHT),
    otherBodyPosition_(Vector3::ZERO),
    otherBodyAxis_(Vector3::RIGHT),
    lowLimit_(DEFAULT_LOW_LIMIT),
    highLimit_(DEFAULT_HIGH_LIMIT),
    otherBodyNodeID_(0),
    disableCollision_(false),
    recreateConstraint_(false),
    otherBodyPositionValid_(false)
{
}

Constraint::~Constraint()
{
    ReleaseConstraint();
    
    if (physicsWorld_)
        physicsWorld_->RemoveConstraint(this);
}

void Constraint::RegisterObject(Context* context)
{
    context->RegisterFactory<Constraint>();
    
    ENUM_ATTRIBUTE(Constraint, "Constraint Type", type_, typeNames, CONSTRAINT_POINT, AM_DEFAULT);
    ATTRIBUTE(Constraint, VAR_VECTOR3, "Position", position_, Vector3::ZERO, AM_DEFAULT);
    ATTRIBUTE(Constraint, VAR_VECTOR3, "Axis", axis_, Vector3::RIGHT, AM_DEFAULT);
    ATTRIBUTE(Constraint, VAR_VECTOR3, "Other Body Position", otherBodyPosition_, Vector3::ZERO, AM_DEFAULT | AM_NOEDIT);
    ATTRIBUTE(Constraint, VAR_VECTOR3, "Other Body Axis", otherBodyAxis_, Vector3::RIGHT, AM_DEFAULT | AM_NOEDIT);
    ACCESSOR_ATTRIBUTE(Constraint, VAR_FLOAT, "Low Limit", GetLowLimit, SetLowLimit, float, DEFAULT_LOW_LIMIT, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(Constraint, VAR_FLOAT, "High Limit", GetHighLimit, SetHighLimit, float, DEFAULT_HIGH_LIMIT, AM_DEFAULT);
    ATTRIBUTE(Constraint, VAR_INT, "Other Body NodeID", otherBodyNodeID_, 0, AM_DEFAULT | AM_NODEID);
    ATTRIBUTE(Constraint, VAR_BOOL, "Disable Collision", disableCollision_, false, AM_DEFAULT);
}

void Constraint::OnSetAttribute(const AttributeInfo& attr, const Variant& src)
{
    Component::OnSetAttribute(attr, src);
    
    // Change of any non-accessor attribute requires recreation of the constraint
    if (!attr.accessor_)
    {
        recreateConstraint_ = true;
        if (attr.offset_ == offsetof(Constraint, otherBodyPosition_) || attr.offset_ == offsetof(Constraint, otherBodyAxis_))
            otherBodyPositionValid_ = true;
    }
}

void Constraint::ApplyAttributes()
{
    if (recreateConstraint_)
    {
        otherBody_.Reset();
        
        Scene* scene = GetScene();
        if (scene && otherBodyNodeID_)
        {
            Node* otherNode = scene->GetNode(otherBodyNodeID_);
            if (otherNode)
                otherBody_ = otherNode->GetComponent<RigidBody>();
        }
        
        CreateConstraint();
        recreateConstraint_ = false;
    }
}

void Constraint::GetDependencyNodes(PODVector<Node*>& dest)
{
    if (otherBody_ && otherBody_->GetNode())
        dest.Push(otherBody_->GetNode());
}

void Constraint::DrawDebugGeometry(DebugRenderer* debug, bool depthTest)
{
    if (debug && physicsWorld_ && constraint_)
    {
        physicsWorld_->SetDebugRenderer(debug);
        physicsWorld_->SetDebugDepthTest(depthTest);
        physicsWorld_->GetWorld()->debugDrawConstraint(constraint_);
        physicsWorld_->SetDebugRenderer(0);
    }
}

void Constraint::SetConstraintType(ConstraintType type)
{
    if (type != type_)
    {
        type_ = type;
        CreateConstraint();
    }
}

void Constraint::SetOtherBody(RigidBody* body)
{
    if (otherBody_ != body)
    {
        otherBody_ = body;
        
        // Update the connected body attribute
        Node* otherNode = otherBody_ ? otherBody_->GetNode() : 0;
        otherBodyNodeID_ = otherNode ? otherNode->GetID() : 0;
        
        CreateConstraint();
    }
}

void Constraint::SetPosition(const Vector3& position)
{
    if (position != position_)
    {
        position_ = position;
        /// \todo Optimize and do not recreate the constraint
        if (constraint_)
            CreateConstraint();
    }
}

void Constraint::SetAxis(const Vector3& axis)
{
    if (axis != axis_)
    {
        axis_ = axis;
        /// \todo Optimize and do not recreate the constraint
        if (constraint_ && constraint_->getConstraintType() == HINGE_CONSTRAINT_TYPE)
            CreateConstraint();
    }
}

void Constraint::SetLowLimit(float limit)
{
    if (limit != lowLimit_)
    {
        lowLimit_ = limit;
        
        if (constraint_ && constraint_->getConstraintType() == HINGE_CONSTRAINT_TYPE)
        {
            btHingeConstraint* hingeConstraint = static_cast<btHingeConstraint*>(constraint_);
            hingeConstraint->setLimit(lowLimit_ * M_DEGTORAD, highLimit_ * M_DEGTORAD);
        }
    }
}

void Constraint::SetHighLimit(float limit)
{
    if (limit != highLimit_)
    {
        highLimit_ = limit;
        
        if (constraint_ && constraint_->getConstraintType() == HINGE_CONSTRAINT_TYPE)
        {
            btHingeConstraint* hingeConstraint = static_cast<btHingeConstraint*>(constraint_);
            hingeConstraint->setLimit(lowLimit_ * M_DEGTORAD, highLimit_ * M_DEGTORAD);
        }
    }
}

void Constraint::ReleaseConstraint()
{
    if (constraint_)
    {
        if (physicsWorld_)
            physicsWorld_->GetWorld()->removeConstraint(constraint_);
        
        delete constraint_;
        constraint_ = 0;
    }
}

void Constraint::OnNodeSet(Node* node)
{
    if (node)
    {
        Scene* scene = GetScene();
        if (scene)
        {
            physicsWorld_ = scene->GetComponent<PhysicsWorld>();
            if (physicsWorld_)
                physicsWorld_->AddConstraint(this);
            else
                LOGERROR("No physics world component in scene, can not create constraint");
        }
        node->AddListener(this);
        
        // Try to create constraint immediately, may fail if the rigid body component does not exist yet
        CreateConstraint();
    }
}

void Constraint::OnMarkedDirty(Node* node)
{
    if (!node->GetWorldScale().Equals(cachedWorldScale_))
        CreateConstraint();
}

void Constraint::CreateConstraint()
{
    PROFILE(CreateConstraint);
    
    cachedWorldScale_ = node_->GetWorldScale();
    
    ReleaseConstraint();
    
    ownBody_ = GetComponent<RigidBody>();
    btRigidBody* ownBody = ownBody_ ? ownBody_->GetBody() : 0;
    btRigidBody* otherBody = otherBody_ ? otherBody_->GetBody() : 0;
    
    if (!physicsWorld_ || !ownBody)
        return;
    
    if (!otherBody)
        otherBody = &btTypedConstraint::getFixedBody();
    
    btTransform ownInverse = ownBody->getWorldTransform().inverse();
    btTransform otherInverse = otherBody->getWorldTransform().inverse();
    
    // If the deserialized constraint other body position is valid, use it, but only this time
    if (otherBodyPositionValid_)
        otherBodyPositionValid_ = false;
    else
    {
        // Otherwise calculate it from own body's position
        otherBodyPosition_ = ToVector3(otherInverse * (ownBody->getWorldTransform() * ToBtVector3(position_ *
            cachedWorldScale_)));
        otherBodyAxis_ = ToVector3(otherInverse.getBasis() * (ownBody->getWorldTransform().getBasis() *
            ToBtVector3(axis_)));
    }
    
    switch (type_)
    {
    case CONSTRAINT_POINT:
        {
            btPoint2PointConstraint* pointConstraint;
            constraint_ = pointConstraint = new btPoint2PointConstraint(*ownBody, *otherBody, ToBtVector3(position_ *
                cachedWorldScale_), ToBtVector3(otherBodyPosition_));
        }
        break;
        
    case CONSTRAINT_HINGE:
        {
            btHingeConstraint* hingeConstraint;
            constraint_ = hingeConstraint = new btHingeConstraint(*ownBody, *otherBody, ToBtVector3(position_ *
                cachedWorldScale_), ToBtVector3(otherBodyPosition_), ToBtVector3(axis_.Normalized()),
                ToBtVector3(otherBodyAxis_.Normalized()));
            hingeConstraint->setLimit(lowLimit_ * M_DEGTORAD, highLimit_ * M_DEGTORAD);
        }
        break;
    }
    
    constraint_->setUserConstraintPtr(this);
    physicsWorld_->GetWorld()->addConstraint(constraint_, disableCollision_);
}
