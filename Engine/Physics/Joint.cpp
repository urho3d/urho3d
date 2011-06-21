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
    axis_(Vector3::ZERO)
{
}

Joint::~Joint()
{
    Clear();
}

void Joint::RegisterObject(Context* context)
{
    context->RegisterFactory<Joint>();
    
    ENUM_ATTRIBUTE(Joint, "Joint Type", type_, typeNames, JOINT_NONE);
    ATTRIBUTE(Joint, VAR_INT, "Body A", bodyA_, 0);
    ATTRIBUTE(Joint, VAR_INT, "Body B", bodyB_, 0);
    ATTRIBUTE(Joint, VAR_VECTOR3, "Position", position_, Vector3::ZERO);
    ATTRIBUTE(Joint, VAR_VECTOR3, "Axis", axis_, Vector3::ZERO);
}

void Joint::OnSetAttribute(const AttributeInfo& attr, const Variant& value)
{
    Scene* scene = node_ ? node_->GetScene() : 0;
    
    switch (attr.offset_)
    {
    case offsetof(Joint, bodyA_):
        bodyA_ = scene ? dynamic_cast<RigidBody*>(scene->GetComponentByID(value.GetInt())) : (RigidBody*)0;
        break;
        
    case offsetof(Joint, bodyB_):
        bodyB_ = scene ? dynamic_cast<RigidBody*>(scene->GetComponentByID(value.GetInt())) : (RigidBody*)0;
        break;
        
    default:
        Serializable::OnSetAttribute(attr, value);
        break;
    }
}

Variant Joint::OnGetAttribute(const AttributeInfo& attr)
{
    switch (attr.offset_)
    {
    case offsetof(Joint, bodyA_):
        return bodyA_ ? bodyA_->GetID() : 0;
        
    case offsetof(Joint, bodyB_):
        return bodyB_ ? bodyB_->GetID() : 0;
        
    case offsetof(Joint, position_):
        return GetPosition();
        
    case offsetof(Joint, axis_):
        return GetAxis();
        
    default:
        return Serializable::OnGetAttribute(attr);
    }
}

void Joint::PostLoad()
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

void Joint::SetPosition(const Vector3& position)
{
    switch (type_)
    {
    case JOINT_BALL:
        dJointSetBallAnchor(joint_, position.x_, position.y_, position.z_);
        break;
        
    case JOINT_HINGE:
        dJointSetHingeAnchor(joint_, position.x_, position.y_, position.z_);
        break;
    }
}

void Joint::SetAxis(const Vector3& axis)
{
    switch (type_)
    {
    case JOINT_HINGE:
        dJointSetHingeAxis(joint_, axis.x_, axis.y_, axis.z_);
        break;
    }
}

Vector3 Joint::GetPosition() const
{
    dVector3 pos;
    
    switch (type_)
    {
    case JOINT_BALL:
        dJointGetBallAnchor(joint_, pos);
        return Vector3(pos[0], pos[1], pos[2]);
        
    case JOINT_HINGE:
        dJointGetHingeAnchor(joint_, pos);
        return Vector3(pos[0], pos[1], pos[2]);
    }
    
    return Vector3::ZERO;
}

Vector3 Joint::GetAxis() const
{
    dVector3 axis;
    
    switch (type_)
    {
    case JOINT_HINGE:
        dJointGetHingeAxis(joint_, axis);
        return Vector3(axis[0], axis[1], axis[2]);
    }
    
    return Vector3::ZERO;
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
