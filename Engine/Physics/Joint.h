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

#pragma once

#include "Component.h"
#include "PhysicsDefs.h"
#include "Vector3.h"

/// Supported joint types.
enum JointType
{
    JOINT_NONE = 0,
    JOINT_BALL,
    JOINT_HINGE
};

class PhysicsWorld;
class RigidBody;

/// Physics joint component. Connects two rigid bodies together, or one rigid body to a static point.
class Joint : public Component
{
    OBJECT(Joint);
    
public:
    /// Construct.
    Joint(Context* context);
    /// Destruct.
    ~Joint();
    /// Register object factory.
    static void RegisterObject(Context* context);
    
    /// Handle attribute write access.
    virtual void OnSetAttribute(const AttributeInfo& attr, const Variant& src);
    /// Apply attribute changes that can not be applied immediately. Called after scene load or a network update.
    virtual void ApplyAttributes();
    /// Return the depended on nodes to order network updates.
    virtual void GetDependencyNodes(PODVector<Node*>& dest);
    
    /// Remove the joint.
    void Clear();
    /// %Set a ball joint.
    bool SetBall(const Vector3& position, RigidBody* otherBody = 0);
    /// %Set a hinge joint.
    bool SetHinge(const Vector3& position, const Vector3& axis, RigidBody* otherBody = 0);
    /// %Set joint world position.
    void SetPosition(Vector3 position);
    /// %Set joint world axis if applicable.
    void SetAxis(Vector3 axis);
    
    /// Return physics world.
    PhysicsWorld* GetPhysicsWorld() const { return physicsWorld_; }
    /// Return rigid body in own scene node.
    RigidBody* GetOwnBody() const { return ownBody_; }
    /// Return the other rigid body. May be null if connected to the static world.
    RigidBody* GetOtherBody() const { return otherBody_; }
    /// Return joint type.
    JointType GetJointType() const { return type_; }
    /// Return the ODE joint ID.
    dJointID GetJoint() const { return joint_; }
    /// Return joint world position.
    Vector3 GetPosition() const;
    /// Return joint world axis.
    Vector3 GetAxis() const;
    
    /// %Set other body attribute.
    void SetOtherBodyAttr(int value);
    /// Return other body attribute.
    int GetOtherBodyAttr() const;
    
protected:
    /// Handle node being assigned.
    virtual void OnNodeSet(Node* node);
    
private:
    /// Physics world.
    WeakPtr<PhysicsWorld> physicsWorld_;
    /// Own rigid body.
    WeakPtr<RigidBody> ownBody_;
    /// Other rigid body.
    WeakPtr<RigidBody> otherBody_;
    /// Joint type.
    JointType type_;
    /// ODE joint ID.
    dJointID joint_;
    /// Joint position for creation during post-load.
    Vector3 position_;
    /// Joint axis for creation during post-load.
    Vector3 axis_;
    /// Other body node ID for pending joint recreation.
    int otherBodyNodeID_;
    /// Recreate joint flag.
    bool recreateJoint_;
};
