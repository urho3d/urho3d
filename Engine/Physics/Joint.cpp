//
// Urho3D Engine
// Copyright (c) 2008-2011 Lasse Öörni
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
    "none",
    "ball",
    "hinge",
    ""
};

OBJECTTYPESTATIC(Joint);

Joint::Joint(Context* context) :
    Component(context),
    type_(JOINT_NONE),
    joint_(0),
    position_(Vector3::ZERO),
    axis_(Vector3::ZERO),
    recreateJoint_(false)
{
}

Joint::~Joint()
{
    Clear();
}

void Joint::RegisterObject(Context* context)
{
    context->RegisterFactory<Joint>();
    
    ENUM_ATTRIBUTE(Joint, "Joint Type", type_, typeNames, JOINT_NONE, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(Joint, VAR_INT, "Body A", GetBodyAAttr, SetBodyAAttr, int, 0, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(Joint, VAR_INT, "Body B", GetBodyBAttr, SetBodyBAttr, int, 0, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(Joint, VAR_VECTOR3, "Position", GetPosition, SetPosition, Vector3, Vector3::ZERO, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(Joint, VAR_VECTOR3, "Axis", GetAxis, SetAxis, Vector3, Vector3::ZERO, AM_DEFAULT);
}

void Joint::OnSetAttribute(const AttributeInfo& attr, const Variant& value)
{
    Serializable::OnSetAttribute(attr, value);
    
    // Change of the joint type requires the joint to be recreated
    if (attr.offset_ == offsetof(Joint, type_))
        recreateJoint_ = true;
}

void Joint::FinishUpdate()
{
    if (recreateJoint_)
    {
        switch (type_)
        {
        case JOINT_NONE:
            Clear();
            break;
            
        case JOINT_BALL:
            SetBall(position_, bodyA_, bodyB_);
            break;
            
        case JOINT_HINGE:
            SetHinge(position_, axis_, bodyA_, bodyB_);
            break;
        }
        
        recreateJoint_ = false;
    }
}

void Joint::GetDependencyNodes(PODVector<Node*>& dest)
{
    if (bodyA_ && bodyA_->GetNode())
        dest.Push(bodyA_->GetNode());
    if (bodyB_ && bodyB_->GetNode())
        dest.Push(bodyB_->GetNode());
}

void Joint::Clear()
{
    if (joint_)
    {
        dJointDestroy(joint_);
        joint_ = 0;
    }
    
    bodyA_.Reset();
    bodyB_.Reset();
    type_ = JOINT_NONE;
}

bool Joint::SetBall(const Vector3& position, RigidBody* bodyA, RigidBody* bodyB)
{
    Clear();
    
    if (!physicsWorld_)
    {
        LOGERROR("Null physics world, can not set joint type");
        return false;
    }
    
    if (!bodyA && !bodyB)
    {
        LOGERROR("Both bodies null, can not create joint");
        return false;
    }
    
    joint_ = dJointCreateBall(physicsWorld_->GetWorld(), 0);
    dJointSetData(joint_, this);
    dJointSetBallAnchor(joint_, position.x_, position.y_, position.z_);
    dJointAttach(joint_, bodyA ? bodyA->GetBody() : 0, bodyB ? bodyB->GetBody() : 0);
    
    type_ = JOINT_BALL;
    bodyA_ = bodyA;
    bodyB_ = bodyB;
    
    return true;
}

bool Joint::SetHinge(const Vector3& position, const Vector3& axis, RigidBody* bodyA, RigidBody* bodyB)
{
    Clear();
    
    if (!physicsWorld_)
    {
        LOGERROR("Null physics world, can not set joint type");
        return false;
    }
    
    if (!bodyA && !bodyB)
    {
        LOGERROR("Both bodies null, can not create joint");
        return false;
    }
    
    Vector3 NormalizedAxis = axis.Normalized();
    
    joint_ = dJointCreateHinge(physicsWorld_->GetWorld(), 0);
    dJointSetData(joint_, this);
    dJointSetHingeAnchor(joint_, position.x_, position.y_, position.z_);
    dJointSetHingeAxis(joint_, NormalizedAxis.x_, NormalizedAxis.y_, NormalizedAxis.z_);
    dJointAttach(joint_, bodyA ? bodyA->GetBody() : 0, bodyB ? bodyB->GetBody() : 0);
    
    type_ = JOINT_HINGE;
    bodyA_ = bodyA;
    bodyB_ = bodyB;
    
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

void Joint::SetBodyAAttr(int value)
{
    Scene* scene = node_ ? node_->GetScene() : 0;
    bodyA_ = scene ? dynamic_cast<RigidBody*>(scene->GetComponentByID(value)) : (RigidBody*)0;
    recreateJoint_ = true;
}

void Joint::SetBodyBAttr(int value)
{
    Scene* scene = node_ ? node_->GetScene() : 0;
    bodyB_ = scene ? dynamic_cast<RigidBody*>(scene->GetComponentByID(value)) : (RigidBody*)0;
    recreateJoint_ = true;
}

int Joint::GetBodyAAttr() const
{
    return bodyA_ ? bodyA_->GetID() : 0;
}

int Joint::GetBodyBAttr() const
{
    return bodyB_ ? bodyB_->GetID() : 0;
}

void Joint::OnNodeSet(Node* node)
{
    if (node)
    {
        Scene* scene = node->GetScene();
        if (scene)
            physicsWorld_ = scene->GetComponent<PhysicsWorld>();
    }
}
