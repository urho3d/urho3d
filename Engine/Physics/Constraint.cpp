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
    axis_(Vector3::FORWARD),
    lowLimit_(DEFAULT_LOW_LIMIT),
    highLimit_(DEFAULT_HIGH_LIMIT),
    otherBodyNodeID_(0),
    disableCollision_(false),
    recreateConstraint_(false)
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
    REF_ACCESSOR_ATTRIBUTE(Constraint, VAR_VECTOR3, "Position", GetPosition, SetPosition, Vector3, Vector3::ZERO, AM_DEFAULT | AM_LATESTDATA);
    REF_ACCESSOR_ATTRIBUTE(Constraint, VAR_VECTOR3, "Axis", GetAxis, SetAxis, Vector3, Vector3::FORWARD, AM_DEFAULT | AM_LATESTDATA);
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
        recreateConstraint_ = true;
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
    type_ = type;
    CreateConstraint();
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

const Vector3& Constraint::GetPosition() const
{
    // If the constraint exists and connects two rigid bodies, update position from it
    /// \todo If there is constraint error, the two bodies may disagree, resulting in drift with successive load/save
    if (constraint_ && ownBody_ && otherBody_)
    {
        switch (constraint_->getConstraintType())
        {
        case POINT2POINT_CONSTRAINT_TYPE:
            {
                btPoint2PointConstraint* pointConstraint = static_cast<btPoint2PointConstraint*>(constraint_);
                position_ = ToVector3(ownBody_->GetBody()->getCenterOfMassTransform() * pointConstraint->getPivotInA());
            }
            break;
            
        case HINGE_CONSTRAINT_TYPE:
            {
                btHingeConstraint* hingeConstraint = static_cast<btHingeConstraint*>(constraint_);
                position_ = ToVector3(ownBody_->GetBody()->getCenterOfMassTransform() * hingeConstraint->getAFrame().getOrigin());
            }
            break;
        }
    }
    
    return position_;
}

const Vector3& Constraint::GetAxis() const
{
    // If the constraint exists and connects two rigid bodies, update axis from it
    /// \todo If there is constraint error, the two bodies may disagree, resulting in drift with successive load/save
    if (constraint_ && ownBody_ && otherBody_ && constraint_->getConstraintType() == HINGE_CONSTRAINT_TYPE)
    {
        btHingeConstraint* hingeConstraint = static_cast<btHingeConstraint*>(constraint_);
        btTransform worldFrame = ownBody_->GetBody()->getCenterOfMassTransform() * hingeConstraint->getAFrame();
        axis_ = ToVector3(worldFrame.getBasis().getColumn(0));
    }
    
    return axis_;
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
        
        // Set node world position as initial position, then try to create the constraint initially
        position_ = node->GetWorldPosition();
        CreateConstraint();
    }
}

void Constraint::CreateConstraint()
{
    PROFILE(CreateConstraint);
    
    ReleaseConstraint();
    
    ownBody_ = GetComponent<RigidBody>();
    btRigidBody* ownBody = ownBody_ ? ownBody_->GetBody() : 0;
    btRigidBody* otherBody = otherBody_ ? otherBody_->GetBody() : 0;
    
    if (!physicsWorld_ || !ownBody)
        return;
    
    switch (type_)
    {
    case CONSTRAINT_POINT:
        if (otherBody)
        {
            constraint_ = new btPoint2PointConstraint(*ownBody, *otherBody, ownBody->getCenterOfMassTransform().inverse() *
                ToBtVector3(position_), otherBody->getCenterOfMassTransform().inverse() * ToBtVector3(position_));
        }
        else
            constraint_ = new btPoint2PointConstraint(*ownBody, ownBody->getCenterOfMassTransform().inverse() *
                ToBtVector3(position_));
        break;
        
    case CONSTRAINT_HINGE:
        {
            btHingeConstraint* hingeConstraint;
            if (otherBody)
            {
                btTransform ownBodyInverse = ownBody->getCenterOfMassTransform().inverse();
                btTransform otherBodyInverse = otherBody->getCenterOfMassTransform().inverse();
                Vector3 axis = axis_.Normalized();
                
                constraint_ = hingeConstraint = new btHingeConstraint(*ownBody, *otherBody, ownBodyInverse *
                    ToBtVector3(position_), otherBodyInverse * ToBtVector3(position_), ownBodyInverse.getBasis() *
                    ToBtVector3(axis), otherBodyInverse.getBasis() * ToBtVector3(axis));
            }
            else
            {
                btTransform ownBodyInverse = ownBody->getCenterOfMassTransform().inverse();
                Vector3 axis = axis_.Normalized();
                
                constraint_ = hingeConstraint = new btHingeConstraint(*ownBody, ownBodyInverse * ToBtVector3(position_),
                    ownBodyInverse.getBasis() * ToBtVector3(axis));
            }
            
            hingeConstraint->setLimit(lowLimit_ * M_DEGTORAD, highLimit_ * M_DEGTORAD);
        }
        break;
    }
    
    constraint_->setUserConstraintPtr(this);
    physicsWorld_->GetWorld()->addConstraint(constraint_, disableCollision_);
}
