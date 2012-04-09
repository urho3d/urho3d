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
    type_ = JOINT_NONE;
}

bool Joint::SetJointType(JointType type)
{
    Clear();
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
    }
}

void Joint::SetPosition(const Vector3& position)
{
}

void Joint::SetAxis(const Vector3& axis)
{
}

const Vector3& Joint::GetPosition() const
{
    return position_;
}

const Vector3& Joint::GetAxis() const
{
    return axis_;
}

void Joint::DrawDebugGeometry(DebugRenderer* debug, bool depthTest)
{
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
