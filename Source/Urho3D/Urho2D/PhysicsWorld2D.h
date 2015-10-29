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

class Camera;
class RigidBody2D;

/// 2D Physics raycast hit.
struct URHO3D_API PhysicsRaycastResult2D
{
    /// Construct with defaults.
    PhysicsRaycastResult2D() :
        body_(0)
    {
    }

    /// Test for inequality, added to prevent GCC from complaining.
    bool operator !=(const PhysicsRaycastResult2D& rhs) const
    {
        return position_ != rhs.position_ || normal_ != rhs.normal_ || distance_ != rhs.distance_ || body_ != rhs.body_;
    }

    /// Hit worldspace position.
    Vector2 position_;
    /// Hit worldspace normal.
    Vector2 normal_;
    /// Hit distance from ray origin.
    float distance_;
    /// Rigid body that was hit.
    RigidBody2D* body_;
};

/// 2D physics simulation world component. Should be added only to the root scene node.
class URHO3D_API PhysicsWorld2D : public Component, public b2ContactListener, public b2Draw
{
    URHO3D_OBJECT(PhysicsWorld2D, Component);

public:
    /// Construct.
    PhysicsWorld2D(Context* context);
    /// Destruct.
    virtual ~PhysicsWorld2D();
    /// Register object factory.
    static void RegisterObject(Context* context);

    /// Visualize the component as debug geometry.
    virtual void DrawDebugGeometry(DebugRenderer* debug, bool depthTest);

    // Implement b2ContactListener.
    /// Called when two fixtures begin to touch.
    virtual void BeginContact(b2Contact* contact);
    /// Called when two fixtures cease to touch.
    virtual void EndContact(b2Contact* contact);

    // Implement b2Draw.
    /// Draw a closed polygon provided in CCW order.
    virtual void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);
    /// Draw a solid closed polygon provided in CCW order.
    virtual void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);
    /// Draw a circle.
    virtual void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color);
    /// Draw a solid circle.
    virtual void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color);
    /// Draw a line segment.
    virtual void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color);
    /// Draw a transform. Choose your own length scale.
    virtual void DrawTransform(const b2Transform& xf);

    /// Step the simulation forward.
    void Update(float timeStep);
    /// Add debug geometry to the debug renderer.
    void DrawDebugGeometry();
    /// Enable or disable automatic physics simulation during scene update. Enabled by default.
    void SetUpdateEnabled(bool enable);
    /// Set draw shape.
    void SetDrawShape(bool drawShape);
    /// Set draw joint.
    void SetDrawJoint(bool drawJoint);
    /// Set draw aabb.
    void SetDrawAabb(bool drawAabb);
    /// Set draw pair.
    void SetDrawPair(bool drawPair);
    /// Set draw center of mass.
    void SetDrawCenterOfMass(bool drawCenterOfMass);
    /// Set allow sleeping.
    void SetAllowSleeping(bool enable);
    /// Set warm starting.
    void SetWarmStarting(bool enable);
    /// Set continuous physics.
    void SetContinuousPhysics(bool enable);
    /// Set sub stepping.
    void SetSubStepping(bool enable);
    /// Set gravity.
    void SetGravity(const Vector2& gravity);
    /// Set auto clear forces.
    void SetAutoClearForces(bool enable);
    /// Set velocity iterations.
    void SetVelocityIterations(int velocityIterations);
    /// Set position iterations.
    void SetPositionIterations(int positionIterations);
    /// Add rigid body.
    void AddRigidBody(RigidBody2D* rigidBody);
    /// Remove rigid body.
    void RemoveRigidBody(RigidBody2D* rigidBody);

    /// Perform a physics world raycast and return all hits.
    void Raycast(PODVector<PhysicsRaycastResult2D>& results, const Vector2& startPoint, const Vector2& endPoint,
        unsigned collisionMask = M_MAX_UNSIGNED);
    /// Perform a physics world raycast and return the closest hit.
    void RaycastSingle(PhysicsRaycastResult2D& result, const Vector2& startPoint, const Vector2& endPoint,
        unsigned collisionMask = M_MAX_UNSIGNED);
    /// Return rigid body at point.
    RigidBody2D* GetRigidBody(const Vector2& point, unsigned collisionMask = M_MAX_UNSIGNED);
    /// Return rigid body at screen point.
    RigidBody2D* GetRigidBody(int screenX, int screenY, unsigned collisionMask = M_MAX_UNSIGNED);
    /// Return rigid bodies by a box query.
    void GetRigidBodies(PODVector<RigidBody2D*>& result, const Rect& aabb, unsigned collisionMask = M_MAX_UNSIGNED);

    /// Return whether physics world will automatically simulate during scene update.
    bool IsUpdateEnabled() const { return updateEnabled_; }

    /// Return draw shape.
    bool GetDrawShape() const { return (m_drawFlags & e_shapeBit) != 0; }

    /// Return draw joint.
    bool GetDrawJoint() const { return (m_drawFlags & e_jointBit) != 0; }

    /// Return draw aabb.
    bool GetDrawAabb() const { return (m_drawFlags & e_aabbBit) != 0; }

    /// Return draw pair.
    bool GetDrawPair() const { return (m_drawFlags & e_pairBit) != 0; }

    /// Return draw center of mass.
    bool GetDrawCenterOfMass() const { return (m_drawFlags & e_centerOfMassBit) != 0; }

    /// Return allow sleeping.
    bool GetAllowSleeping() const;
    /// Return warm starting.
    bool GetWarmStarting() const;
    /// Return continuous physics.
    bool GetContinuousPhysics() const;
    /// Return sub stepping.
    bool GetSubStepping() const;
    /// Return auto clear forces.
    bool GetAutoClearForces() const;

    /// Return gravity.
    const Vector2& GetGravity() const { return gravity_; }

    /// Return velocity iterations.
    int GetVelocityIterations() const { return velocityIterations_; }

    /// Return position iterations.
    int GetPositionIterations() const { return positionIterations_; }

    /// Return the Box2D physics world.
    b2World* GetWorld() { return world_; }

    /// Set node dirtying to be disregarded.
    void SetApplyingTransforms(bool enable) { applyingTransforms_ = enable; }

    /// Return whether node dirtying should be disregarded.
    bool IsApplyingTransforms() const { return applyingTransforms_; }

protected:
    /// Handle scene being assigned.
    virtual void OnSceneSet(Scene* scene);

private:
    /// Handle the scene subsystem update event, step simulation here.
    void HandleSceneSubsystemUpdate(StringHash eventType, VariantMap& eventData);
    /// Send begin contact events.
    void SendBeginContactEvents();
    /// Send end contact events.
    void SendEndContactEvents();

    /// Box2D physics world.
    b2World* world_;
    /// Gravity.
    Vector2 gravity_;
    /// Velocity iterations.
    int velocityIterations_;
    /// Position iterations.
    int positionIterations_;

    /// Extra weak pointer to scene to allow for cleanup in case the world is destroyed before other components.
    WeakPtr<Scene> scene_;
    /// Debug renderer.
    DebugRenderer* debugRenderer_;
    /// Debug draw depth test mode.
    bool debugDepthTest_;

    /// Automatic simulation update enabled flag.
    bool updateEnabled_;
    /// Whether is currently stepping the world. Used internally.
    bool physicsStepping_;
    /// Applying transforms.
    bool applyingTransforms_;
    /// Rigid bodies.
    Vector<WeakPtr<RigidBody2D> > rigidBodies_;

    /// Contact info.
    struct ContactInfo
    {
        /// Construct.
        ContactInfo();
        /// Construct.
        ContactInfo(b2Contact* contract);
        /// Copy construct.
        ContactInfo(const ContactInfo& other);

        /// Rigid body A.
        SharedPtr<RigidBody2D> bodyA_;
        /// Rigid body B.
        SharedPtr<RigidBody2D> bodyB_;
        /// Node A.
        SharedPtr<Node> nodeA_;
        /// Node B.
        SharedPtr<Node> nodeB_;
    };
    /// Begin contact infos.
    Vector<ContactInfo> beginContactInfos_;
    /// End contact infos.
    Vector<ContactInfo> endContactInfos_;
};

}
