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
#include "Vector3.h"

/// Supported constraint types.
enum ConstraintType
{
    CONSTRAINT_POINT = 0,
    CONSTRAINT_HINGE
};

class PhysicsWorld;
class RigidBody;
class btTypedConstraint;

/// Physics constraint component. Connects two rigid bodies together, or one rigid body to a static point.
class Constraint : public Component
{
    OBJECT(Constraint);
    
public:
    /// Construct.
    Constraint(Context* context);
    /// Destruct.
    ~Constraint();
    /// Register object factory.
    static void RegisterObject(Context* context);
    
    /// Handle attribute write access.
    virtual void OnSetAttribute(const AttributeInfo& attr, const Variant& src);
    /// Apply attribute changes that can not be applied immediately. Called after scene load or a network update.
    virtual void ApplyAttributes();
    /// Return the depended on nodes to order network updates.
    virtual void GetDependencyNodes(PODVector<Node*>& dest);
    /// Visualize the component as debug geometry.
    virtual void DrawDebugGeometry(DebugRenderer* debug, bool depthTest);
    
    /// %Set constraint type and recreate the constraint.
    void SetConstraintType(ConstraintType type);
    /// %Set other body to connect to. Set to null to connect to the static world.
    void SetOtherBody(RigidBody* body);
    /// %Set position relative to own body.
    void SetPosition(const Vector3& position);
    /// %Set position relative to other body.
    void SetOtherPosition(const Vector3& position);
    /// %Set axis relative to own body.
    void SetAxis(const Vector3& axis);
    /// %Set axis relative to other body.
    void SetOtherAxis(const Vector3& axis);
    /// %Set low limit.
    void SetLowLimit(float limit);
    /// %Set high limit.
    void SetHighLimit(float limit);
    
    /// Return physics world.
    PhysicsWorld* GetPhysicsWorld() const { return physicsWorld_; }
    /// Return Bullet constraint.
    btTypedConstraint* GetConstraint() const { return constraint_; }
    /// Return constraint type.
    ConstraintType GetConstraintType() const { return type_; }
    /// Return rigid body in own scene node.
    RigidBody* GetOwnBody() const { return ownBody_; }
    /// Return the other rigid body. May be null if connected to the static world.
    RigidBody* GetOtherBody() const { return otherBody_; }
    /// Return position relative to own body.
    const Vector3& GetPosition() const { return position_; }
    /// Return position relative to other body.
    const Vector3& GetOtherPosition() const { return otherPosition_; }
    /// Return axis relative to own body.
    const Vector3& GetAxis() const { return axis_; }
    /// Return axis relative to other body.
    const Vector3& GetOtherAxis() const { return otherAxis_; }
    /// Return low limit.
    float GetLowLimit() const { return lowLimit_; }
    /// Return high limit.
    float GetHighLimit() const { return highLimit_; }
    
    /// Release the constraint.
    void ReleaseConstraint();
    
protected:
    /// Handle node being assigned.
    virtual void OnNodeSet(Node* node);
    
private:
    /// Create the constraint.
    void CreateConstraint();
    
    /// Physics world.
    WeakPtr<PhysicsWorld> physicsWorld_;
    /// Own rigid body.
    WeakPtr<RigidBody> ownBody_;
    /// Other rigid body.
    WeakPtr<RigidBody> otherBody_;
    /// Bullet constraint.
    btTypedConstraint* constraint_;
    /// Constraint type.
    ConstraintType type_;
    /// Constraint position relative to own body.
    Vector3 position_;
    /// Constraint position relative to other body.
    Vector3 otherPosition_;
    /// Constraint axis relative to own body.
    Vector3 axis_;
    /// Constraint axis relative to other body.
    Vector3 otherAxis_;
    /// Low limit.
    float lowLimit_;
    /// High limit.
    float highLimit_;
    /// Other body node ID for pending constraint recreation.
    int otherBodyNodeID_;
    /// Disable collision between connected bodies flag.
    bool disableCollision_;
    /// Recreate constraint flag.
    bool recreateConstraint_;
};
