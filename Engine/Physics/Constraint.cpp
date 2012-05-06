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

#include <BulletDynamics/ConstraintSolver/btConeTwistConstraint.h>
#include <BulletDynamics/ConstraintSolver/btHingeConstraint.h>
#include <BulletDynamics/ConstraintSolver/btPoint2PointConstraint.h>
#include <BulletDynamics/ConstraintSolver/btSliderConstraint.h>
#include <BulletDynamics/Dynamics/btDiscreteDynamicsWorld.h>

#include "DebugNew.h"

static const String typeNames[] =
{
    "Point",
    "Hinge",
    "Slider",
    "ConeTwist",
    ""
};

OBJECTTYPESTATIC(Constraint);

Constraint::Constraint(Context* context) :
    Component(context),
    constraint_(0),
    type_(CONSTRAINT_POINT),
    position_(Vector3::ZERO),
    axis_(Vector3::RIGHT),
    otherBodyPosition_(Vector3::ZERO),
    otherBodyAxis_(Vector3::RIGHT),
    lowLimit_(Vector3::ZERO),
    highLimit_(Vector3::ZERO),
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
    REF_ACCESSOR_ATTRIBUTE(Constraint, VAR_VECTOR3, "High Limit", GetHighLimit, SetHighLimit, Vector3, Vector3::ZERO, AM_DEFAULT);
    REF_ACCESSOR_ATTRIBUTE(Constraint, VAR_VECTOR3, "Low Limit", GetLowLimit, SetLowLimit, Vector3, Vector3::ZERO, AM_DEFAULT);
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
        if (otherBody_)
            otherBody_->RemoveConstraint(this);
        
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
        MarkNetworkUpdate();
    }
}

void Constraint::SetOtherBody(RigidBody* body)
{
    if (otherBody_ != body)
    {
        if (otherBody_)
            otherBody_->RemoveConstraint(this);
        
        otherBody_ = body;
        
        // Update the connected body attribute
        Node* otherNode = otherBody_ ? otherBody_->GetNode() : 0;
        otherBodyNodeID_ = otherNode ? otherNode->GetID() : 0;
        
        CreateConstraint();
        MarkNetworkUpdate();
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
        MarkNetworkUpdate();
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
        MarkNetworkUpdate();
    }
}

void Constraint::SetHighLimit(const Vector3& limit)
{
    if (limit != highLimit_)
    {
        highLimit_ = limit;
        ApplyLimits();
        MarkNetworkUpdate();
    }
}

void Constraint::SetLowLimit(const Vector3& limit)
{
    if (limit != lowLimit_)
    {
        lowLimit_ = limit;
        ApplyLimits();
        MarkNetworkUpdate();
    }
}

void Constraint::ReleaseConstraint()
{
    if (constraint_)
    {
        if (ownBody_)
            ownBody_->RemoveConstraint(this);
        if (otherBody_)
            otherBody_->RemoveConstraint(this);
        
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
            constraint_ = new btPoint2PointConstraint(*ownBody, *otherBody, ToBtVector3(position_ * cachedWorldScale_),
                ToBtVector3(otherBodyPosition_));
        }
        break;
        
    case CONSTRAINT_HINGE:
        {
            Quaternion ownRotation(Vector3::FORWARD, axis_);
            Quaternion otherRotation(Vector3::FORWARD, otherBodyAxis_);
            btTransform ownFrame(ToBtQuaternion(ownRotation), ToBtVector3(position_ * cachedWorldScale_));
            btTransform otherFrame(ToBtQuaternion(otherRotation), ToBtVector3(otherBodyPosition_));
            constraint_ = new btHingeConstraint(*ownBody, *otherBody, ownFrame, otherFrame);
        }
        break;
        
    case CONSTRAINT_SLIDER:
        {
            Quaternion ownRotation(Vector3::RIGHT, axis_);
            Quaternion otherRotation(Vector3::RIGHT, otherBodyAxis_);
            btTransform ownFrame(ToBtQuaternion(ownRotation), ToBtVector3(position_ * cachedWorldScale_));
            btTransform otherFrame(ToBtQuaternion(otherRotation), ToBtVector3(otherBodyPosition_));
            constraint_ = new btSliderConstraint(*ownBody, *otherBody, ownFrame, otherFrame, false);
        }
        break;
        
    case CONSTRAINT_CONETWIST:
        {
            Quaternion ownRotation(Vector3::RIGHT, axis_);
            Quaternion otherRotation(Vector3::RIGHT, otherBodyAxis_);
            btTransform ownFrame(ToBtQuaternion(ownRotation), ToBtVector3(position_ * cachedWorldScale_));
            btTransform otherFrame(ToBtQuaternion(otherRotation), ToBtVector3(otherBodyPosition_));
            constraint_ = new btConeTwistConstraint(*ownBody, *otherBody, ownFrame, otherFrame);
        }
        break;
    }
    
    constraint_->setUserConstraintPtr(this);
    ownBody_->AddConstraint(this);
    if (otherBody_)
        otherBody_->AddConstraint(this);
    
    ApplyLimits();
    physicsWorld_->GetWorld()->addConstraint(constraint_, disableCollision_);
}

void Constraint::ApplyLimits()
{
    if (!constraint_)
        return;
    
    switch (constraint_->getConstraintType())
    {
    case HINGE_CONSTRAINT_TYPE:
        {
            btHingeConstraint* hingeConstraint = static_cast<btHingeConstraint*>(constraint_);
            hingeConstraint->setLimit(lowLimit_.x_ * M_DEGTORAD, highLimit_.x_ * M_DEGTORAD);
        }
        break;
        
    case SLIDER_CONSTRAINT_TYPE:
        {
            btSliderConstraint* sliderConstraint = static_cast<btSliderConstraint*>(constraint_);
            sliderConstraint->setUpperLinLimit(highLimit_.x_);
            sliderConstraint->setUpperAngLimit(highLimit_.y_ * M_DEGTORAD);
            sliderConstraint->setLowerLinLimit(lowLimit_.x_);
            sliderConstraint->setLowerAngLimit(lowLimit_.y_ * M_DEGTORAD);
        }
        break;
        
    case CONETWIST_CONSTRAINT_TYPE:
        {
            btConeTwistConstraint* coneTwistConstraint = static_cast<btConeTwistConstraint*>(constraint_);
            coneTwistConstraint->setLimit(highLimit_.y_ * M_DEGTORAD, highLimit_.z_ * M_DEGTORAD, highLimit_.x_ * M_DEGTORAD);
        }
        break;
    }
}
