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
    ACCESSOR_ATTRIBUTE(Joint, VAR_VECTOR3, "Position", GetPosition, SetPosition, Vector3, Vector3::ZERO, AM_DEFAULT | AM_LATESTDATA);
    ACCESSOR_ATTRIBUTE(Joint, VAR_VECTOR3, "Axis", GetAxis, SetAxis, Vector3, Vector3::ZERO, AM_DEFAULT | AM_LATESTDATA);
    ACCESSOR_ATTRIBUTE(Joint, VAR_INT, "Other Body NodeID", GetOtherBodyAttr, SetOtherBodyAttr, int, 0, AM_DEFAULT | AM_NODEID);
}

void Joint::OnSetAttribute(const AttributeInfo& attr, const Variant& src)
{
    Serializable::OnSetAttribute(attr, src);
    
    // Change of the joint type requires the joint to be recreated
    if (attr.offset_ == offsetof(Joint, type_))
    {
        otherBodyNodeID_ = GetOtherBodyAttr();
        recreateJoint_ = true;
    }
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
        
        switch (type_)
        {
        case JOINT_NONE:
            Clear();
            break;
            
        case JOINT_BALL:
            SetBall(position_, otherBody_);
            break;
            
        case JOINT_HINGE:
            SetHinge(position_, axis_, otherBody_);
            break;
        }
        
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
    }
    
    type_ = JOINT_NONE;
}

bool Joint::SetBall(const Vector3& position, RigidBody* otherBody)
{
    Clear();
    
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
    
    otherBody_ = otherBody;
    type_ = JOINT_BALL;
    
    joint_ = dJointCreateBall(physicsWorld_->GetWorld(), 0);
    dJointSetData(joint_, this);
    dJointSetBallAnchor(joint_, position.x_, position.y_, position.z_);
    dJointAttach(joint_, ownBody_->GetBody(), otherBody_ ? otherBody_->GetBody() : 0);
    
    return true;
}

bool Joint::SetHinge(const Vector3& position, const Vector3& axis, RigidBody* otherBody)
{
    Clear();
    
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
    
    otherBody_ = otherBody;
    type_ = JOINT_HINGE;
    
    Vector3 normalizedAxis = axis.Normalized();
    
    joint_ = dJointCreateHinge(physicsWorld_->GetWorld(), 0);
    dJointSetData(joint_, this);
    dJointSetHingeAnchor(joint_, position.x_, position.y_, position.z_);
    dJointSetHingeAxis(joint_, normalizedAxis.x_, normalizedAxis.y_, normalizedAxis.z_);
    dJointAttach(joint_, ownBody_->GetBody(), otherBody_ ? otherBody_->GetBody() : 0);
    
    return true;
}

void Joint::SetPosition(Vector3 position)
{
    if (joint_)
    {
        dJointType type = dJointGetType(joint_);
        
        switch (type)
        {
        case dJointTypeBall:
            dJointSetBallAnchor(joint_, position.x_, position.y_, position.z_);
            break;
            
        case dJointTypeHinge:
            dJointSetHingeAnchor(joint_, position.x_, position.y_, position.z_);
            break;
        }
    }
}

void Joint::SetAxis(Vector3 axis)
{
    if (joint_)
    {
        dJointType type = dJointGetType(joint_);
        
        switch (type)
        {
        case dJointTypeHinge:
            dJointSetHingeAxis(joint_, axis.x_, axis.y_, axis.z_);
            break;
        }
    }
}

Vector3 Joint::GetPosition() const
{
    dVector3 pos;
    
    if (joint_)
    {
        dJointType type = dJointGetType(joint_);
        
        switch (type)
        {
        case dJointTypeBall:
            dJointGetBallAnchor(joint_, pos);
            return Vector3(pos[0], pos[1], pos[2]);
            
        case dJointTypeHinge:
            dJointGetHingeAnchor(joint_, pos);
            return Vector3(pos[0], pos[1], pos[2]);
        }
    }
    
    return Vector3::ZERO;
}

Vector3 Joint::GetAxis() const
{
    dVector3 axis;
    
    if (joint_)
    {
        dJointType type = dJointGetType(joint_);
        
        switch (type)
        {
        case dJointTypeHinge:
            dJointGetHingeAxis(joint_, axis);
            return Vector3(axis[0], axis[1], axis[2]);
        }
    }
    
    return Vector3::ZERO;
}

void Joint::SetOtherBodyAttr(int value)
{
    otherBodyNodeID_ = value;
    recreateJoint_ = true;
}

int Joint::GetOtherBodyAttr() const
{
    if (!otherBody_)
        return 0;
    
    Node* otherNode = otherBody_->GetNode();
    return otherNode ? otherNode->GetID() : 0;
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
    }
}
