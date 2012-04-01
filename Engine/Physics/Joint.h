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
    /// %Set joint type and recreate the joint. Return true if successful.
    bool SetJointType(JointType type);
    /// %Set other body to connect to.
    void SetOtherBody(RigidBody* body);
    /// %Set joint local-space position.
    void SetPosition(Vector3 position);
    /// %Set joint local-space axis.
    void SetAxis(Vector3 axis);
    
    /// Return physics world.
    PhysicsWorld* GetPhysicsWorld() const { return physicsWorld_; }
    /// Return joint type.
    JointType GetJointType() const { return type_; }
    /// Return rigid body in own scene node.
    RigidBody* GetOwnBody() const { return ownBody_; }
    /// Return the other rigid body. May be null if connected to the static world.
    RigidBody* GetOtherBody() const { return otherBody_; }
    /// Return the ODE joint ID.
    dJointID GetJoint() const { return joint_; }
    /// Return joint local-space position.
    Vector3 GetPosition() const { return position_; }
    /// Return joint local-space axis.
    Vector3 GetAxis() const { return axis_; }
    /// Return joint world-space position.
    Vector3 GetWorldPosition() const;
    /// Return joint world-space axis.
    Vector3 GetWorldAxis() const;
    
protected:
    /// Handle node being assigned.
    virtual void OnNodeSet(Node* node);
    /// Handle node transform being dirtied.
    virtual void OnMarkedDirty(Node* node);
    
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
    /// Joint local-space position.
    Vector3 position_;
    /// Joint local-space axis.
    Vector3 axis_;
    /// Cached world scale of node.
    Vector3 jointScale_;
    /// Other body node ID for pending joint recreation.
    int otherBodyNodeID_;
    /// Recreate joint flag.
    bool recreateJoint_;
};
