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
#include "Joint.h"
#include "Log.h"
#include "PhysicsWorld.h"
#include "RigidBody.h"
#include "Scene.h"

#include <ode/ode.h>

#include "DebugNew.h"

static const String typeNames[] =
{
    "None",
    "Ball",
    "Hinge",
    ""
};

OBJECTTYPESTATIC(Joint);

Joint::Joint(Context* context) :
    Component(context),
    type_(JOINT_NONE),
    joint_(0),
    position_(Vector3::ZERO),
    axis_(Vector3::ZERO),
    otherBodyNodeID_(0),
    recreateJoint_(false)
{
}

Joint::~Joint()
{
    Clear();
    
    if (physicsWorld_)
        physicsWorld_->RemoveJoint(this);
}

void Joint::RegisterObject(Context* context)
{
    context->RegisterFactory<Joint>();
    
    ENUM_ATTRIBUTE(Joint, "Joint Type", type_, typeNames, JOINT_NONE, AM_DEFAULT);
    REF_ACCESSOR_ATTRIBUTE(Joint, VAR_VECTOR3, "Position", GetPosition, SetPosition, Vector3, Vector3::ZERO, AM_DEFAULT | AM_LATESTDATA);
    REF_ACCESSOR_ATTRIBUTE(Joint, VAR_VECTOR3, "Axis", GetAxis, SetAxis, Vector3, Vector3::ZERO, AM_DEFAULT | AM_LATESTDATA);
    ATTRIBUTE(Joint, VAR_INT, "Other Body NodeID", otherBodyNodeID_, 0, AM_DEFAULT | AM_NODEID);
}

void Joint::OnSetAttribute(const AttributeInfo& attr, const Variant& src)
{
    Serializable::OnSetAttribute(attr, src);
    
    // Change of the joint type or connected body requires the joint to be recreated
    if (attr.offset_ == offsetof(Joint, type_) || attr.offset_ == offsetof(Joint, otherBodyNodeID_))
        recreateJoint_ = true;
}

void Joint::ApplyAttributes()
{
    if (recreateJoint_)
    {
        otherBody_.Reset();
        
        Scene* scene = node_ ? node_->GetScene() : 0;
        if (scene && otherBodyNodeID_)
        {
            Node* otherNode = scene->GetNode(otherBodyNodeID_);
            if (otherNode)
                otherBody_ = otherNode->GetComponent<RigidBody>();
        }
        
        SetJointType(type_);
        recreateJoint_ = false;
    }
}

void Joint::GetDependencyNodes(PODVector<Node*>& dest)
{
    if (otherBody_ && otherBody_->GetNode())
        dest.Push(otherBody_->GetNode());
}

void Joint::Clear()
{
    if (joint_ && physicsWorld_)
    {
        dJointDestroy(joint_);
        joint_ = 0;
        type_ = JOINT_NONE;
    }
}

bool Joint::SetJointType(JointType type)
{
    Clear();
    
    if (type == JOINT_NONE)
        return true;
    
    if (!physicsWorld_)
    {
        LOGERROR("Null physics world, can not set joint type");
        return false;
    }
    
    ownBody_ = static_cast<RigidBody*>(GetComponent(RigidBody::GetTypeStatic()));
    if (!ownBody_)
    {
        LOGERROR("No rigid body in node, can not set joint type");
        return false;
    }
    
    type_ = type;
    
    switch (type)
    {
    case JOINT_NONE:
        break;
        
    case JOINT_BALL:
        joint_ = dJointCreateBall(physicsWorld_->GetWorld(), 0);
        dJointSetData(joint_, this);
        dJointAttach(joint_, ownBody_->GetBody(), otherBody_ ? otherBody_->GetBody() : 0);
        SetPosition(position_);
        break;
        
    case JOINT_HINGE:
        joint_ = dJointCreateHinge(physicsWorld_->GetWorld(), 0);
        dJointSetData(joint_, this);
        dJointAttach(joint_, ownBody_->GetBody(), otherBody_ ? otherBody_->GetBody() : 0);
        SetPosition(position_);
        SetAxis(axis_);
        break;
    }
    
    return true;
}

void Joint::SetOtherBody(RigidBody* body)
{
    if (otherBody_ != body)
    {
        otherBody_ = body;
        
        // Update the connected body attribute
        Node* otherNode = otherBody_ ? otherBody_->GetNode() : 0;
        otherBodyNodeID_ = otherNode ? otherNode->GetID() : 0;
        
        if (joint_)
            dJointAttach(joint_, ownBody_->GetBody(), otherBody_ ? otherBody_->GetBody() : 0);
    }
}

void Joint::SetPosition(const Vector3& position)
{
    position_ = position;
   
    if (joint_)
    {
        dJointType type = dJointGetType(joint_);
        
        switch (type)
        {
        case dJointTypeBall:
            dJointSetBallAnchor(joint_, position_.x_, position_.y_, position_.z_);
            break;
            
        case dJointTypeHinge:
            dJointSetHingeAnchor(joint_, position_.x_, position_.y_, position_.z_);
            break;
        }
    }
}

void Joint::SetAxis(const Vector3& axis)
{
    axis_ = axis.Normalized();
    
    if (joint_)
    {
        dJointType type = dJointGetType(joint_);
        
        switch (type)
        {
        case dJointTypeHinge:
            dJointSetHingeAxis(joint_, axis_.x_, axis_.y_, axis_.z_);
            break;
        }
    }
}

const Vector3& Joint::GetPosition() const
{
    dVector3 pos;
    
    if (joint_)
    {
        dJointType type = dJointGetType(joint_);
        
        switch (type)
        {
        case dJointTypeBall:
            dJointGetBallAnchor(joint_, pos);
            position_ = Vector3(pos[0], pos[1], pos[2]);
            break;
            
        case dJointTypeHinge:
            dJointGetHingeAnchor(joint_, pos);
            position_ = Vector3(pos[0], pos[1], pos[2]);
            break;
        }
    }
    
    return position_;
}

const Vector3& Joint::GetAxis() const
{
    dVector3 axis;
    
    if (joint_)
    {
        dJointType type = dJointGetType(joint_);
        
        switch (type)
        {
        case dJointTypeHinge:
            dJointGetHingeAxis(joint_, axis);
            axis_ = Vector3(axis[0], axis[1], axis[2]);
            break;
        }
    }
    
    return axis_;
}

void Joint::DrawDebugGeometry(DebugRenderer* debug, bool depthTest)
{
    if (debug && joint_ && ownBody_)
    {
        const Vector3& jointPos = GetPosition();
        const Vector3& ownBodyPos = ownBody_->GetPosition();
        const Vector3& otherBodyPos = otherBody_ ? otherBody_->GetPosition() : Vector3::ZERO;
        
        BoundingBox jointBox;
        jointBox.Merge(jointPos);
        jointBox.Merge(ownBodyPos);
        if (otherBody_)
            jointBox.Merge(otherBodyPos);
        
        if (debug->IsInside(jointBox))
        {
            debug->AddLine(jointPos, ownBodyPos, Color::YELLOW, depthTest);
            if (otherBody_)
                debug->AddLine(jointPos, otherBodyPos, Color::YELLOW, depthTest);
            
            if (type_ == JOINT_HINGE)
            {
                const Vector3& axis = GetAxis();
                debug->AddLine(jointPos + 0.1f * axis, jointPos - 0.1f * axis, Color::WHITE, depthTest);
            }
        }
    }
}

void Joint::OnNodeSet(Node* node)
{
    if (node)
    {
        Scene* scene = node->GetScene();
        if (scene)
        {
            physicsWorld_ = scene->GetComponent<PhysicsWorld>();
            if (physicsWorld_)
                physicsWorld_->AddJoint(this);
        }
        node->AddListener(this);
        
        // Set default position at the node
        position_ = node->GetWorldPosition();
    }
}
