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

#include "HashSet.h"
#include "Node.h"
#include "PhysicsDefs.h"

class DebugRenderer;
class PhysicsWorld;

/// Physics rigid body component.
class RigidBody : public Component
{
    OBJECT(RigidBody);
    
    friend class PhysicsWorld;
    
public:
    /// Construct.
    RigidBody(Context* context);
    /// Destruct. Free the rigid body and geometries.
    virtual ~RigidBody();
    /// Register object factory.
    static void RegisterObject(Context* context);
    
    /// %Set mass. Zero mass (or the lack of collision shapes) makes the body kinematic.
    void SetMass(float mass);
    /// %Set mass axis for the cylinder and capsule shapes. By default 1 (Y-axis.)
    void SetMassAxis(int axis);
    /// %Set rigid body world-space position.
    void SetPosition(const Vector3& position);
    /// %Set rigid body world-space rotation.
    void SetRotation(const Quaternion& rotation);
    /// %Set rigid body world-space position and rotation.
    void SetTransform(const Vector3& position, const Quaternion& rotation);
    /// %Set linear velocity.
    void SetLinearVelocity(const Vector3& velocity);
    /// %Set linear velocity deactivation threshold.
    void SetLinearRestThreshold(float threshold);
    /// %Set linear velocity damping threshold.
    void SetLinearDampingThreshold(float threshold);
    /// %Set linear velocity damping scale.
    void SetLinearDampingScale(float scale);
    /// %Set angular velocity.
    void SetAngularVelocity(const Vector3& angularVelocity);
    /// %Set angular velocity deactivation threshold.
    void SetAngularRestThreshold(float threshold);
    /// %Set angular velocity damping threshold.
    void SetAngularDampingThreshold(float threshold);
    /// %Set angular velocity damping scale.
    void SetAngularDampingScale(float scale);
    /// %Set maximum angular velocity. Set to 0 to disable rotation.
    void SetAngularMaxVelocity(float velocity);
    /// %Set whether gravity is applied to rigid body.
    void SetUseGravity(bool enable);
    /// %Set rigid body active/inactive state.
    void SetActive(bool active);
    /// Apply force to center of mass.
    void ApplyForce(const Vector3& force);
    /// Apply force at position.
    void ApplyForceAtPosition(const Vector3& force, const Vector3& position);
    /// Apply torque.
    void ApplyTorque(const Vector3& torque);
    /// Reset accumulated forces.
    void ResetForces();
    
    /// Return physics world.
    PhysicsWorld* GetPhysicsWorld() const { return physicsWorld_; }
    /// Return mass.
    float GetMass() const { return mass_; }
    /// Return mass axis for cylinder and capsule shapes.
    int GetMassAxis() const { return massAxis_; }
    /// Return ODE body ID.
    dBodyID GetBody() const { return body_; }
    /// Return rigid body world-space position.
    const Vector3& GetPosition() const;
    /// Return rigid body world-space rotation.
    const Quaternion& GetRotation() const;
    /// Return linear velocity.
    const Vector3& GetLinearVelocity() const;
    /// Return linear velocity deactivation threshold.
    float GetLinearRestThreshold() const;
    /// Return linear velocity damping threshold.
    float GetLinearDampingThreshold() const;
    /// Return linear velocity damping scale.
    float GetLinearDampingScale() const;
    /// Return angular velocity.
    const Vector3& GetAngularVelocity() const;
    /// Return angular velocity deactivation threshold.
    float GetAngularRestThreshold() const;
    /// Return angular velocity damping threshold.
    float GetAngularDampingThreshold() const;
    /// Return angular velocity damping scale.
    float GetAngularDampingScale() const;
    /// Return maximum angular velocity.
    float GetAngularMaxVelocity() const;
    /// Return whether rigid body uses gravity.
    bool GetUseGravity() const;
    /// Return whether rigid body is active.
    bool IsActive() const;
    
    /// Recalculate mass.
    void UpdateMass();
    /// %Set network angular velocity attribute.
    void SetNetAngularVelocityAttr(const PODVector<unsigned char>& value);
    /// Return network angular velocity attribute.
    const PODVector<unsigned char>& GetNetAngularVelocityAttr() const;
    
protected:
    /// Handle node being assigned.
    virtual void OnNodeSet(Node* node);
    /// Handle node transform being dirtied.
    virtual void OnMarkedDirty(Node* node);
    
private:
    /// Store previous transform for rendering interpolation.
    void PreStep();
    /// Interpolate between previous and current transform and store as rendering transform.
    void PostStep(float t, HashSet<RigidBody*>& processedBodies);
    /// Create the body.
    void CreateBody();
    /// Remove the body.
    void ReleaseBody();
    
    /// Physics world.
    WeakPtr<PhysicsWorld> physicsWorld_;
    /// Mass.
    float mass_;
    /// Mass axis for cylinder and capsule shapes.
    int massAxis_;
    /// ODE body ID.
    dBodyID body_;
    /// Previous physics position for rendering interpolation.
    Vector3 previousPosition_;
    /// Previous physics rotation for rendering interpolation.
    Quaternion previousRotation_;
    /// Last interpolated position set during PostStep.
    Vector3 lastInterpolatedPosition_;
    /// Last interpolated rotation set during PostStep.
    Quaternion lastInterpolatedRotation_;
    /// Attribute buffer for network replication.
    mutable VectorBuffer attrBuffer_;
    /// Poststep flag.
    bool inPostStep_;
};
