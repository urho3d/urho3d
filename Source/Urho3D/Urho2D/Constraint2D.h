//
// Copyright (c) 2008-2015 the Urho3D project.
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

#include "../Scene/Component.h"

#include <Box2D/Box2D.h>

namespace Urho3D
{

class RigidBody2D;
class PhysicsWorld2D;

/// 2D physics constraint component.
class URHO3D_API Constraint2D : public Component
{
    URHO3D_OBJECT(Constraint2D, Component);

public:
    /// Construct.
    Constraint2D(Context* context);
    /// Destruct.
    virtual ~Constraint2D();
    /// Register object factory.
    static void RegisterObject(Context* context);

    /// Handle enabled/disabled state change.
    virtual void OnSetEnabled();
    /// Create Joint.
    void CreateJoint();
    /// Release Joint.
    void ReleaseJoint();

    /// Set other rigid body.
    void SetOtherBody(RigidBody2D* body);
    /// Set collide connected.
    void SetCollideConnected(bool collideConnected);
    /// Set attached constriant (for gear).
    void SetAttachedConstraint(Constraint2D* constraint);

    /// Return owner body.
    RigidBody2D* GetOwnerBody() const { return ownerBody_; }

    /// Return other body.
    RigidBody2D* GetOtherBody() const { return otherBody_; }

    /// Return collide connected.
    bool GetCollideConnected() const { return collideConnected_; }

    /// Return attached constraint (for gear).
    Constraint2D* GetAttachedConstraint() const { return attachedConstraint_; }

    /// Return Box2D joint.
    b2Joint* GetJoint() const { return joint_; }

protected:
    /// Handle node being assigned.
    virtual void OnNodeSet(Node* node);
    /// Handle scene being assigned.
    virtual void OnSceneSet(Scene* scene);
    /// Return joint def.
    virtual b2JointDef* GetJointDef() { return 0; };
    /// Recreate joint.
    void RecreateJoint();
    /// Initialize joint def.
    void InitializeJointDef(b2JointDef* jointDef);

    /// Physics world.
    WeakPtr<PhysicsWorld2D> physicsWorld_;
    /// Box2D joint.
    b2Joint* joint_;
    /// Owner body.
    WeakPtr<RigidBody2D> ownerBody_;
    /// Other body.
    WeakPtr<RigidBody2D> otherBody_;
    /// Collide connected.
    bool collideConnected_;
    /// Attached constraint.
    WeakPtr<Constraint2D> attachedConstraint_;
};

}
