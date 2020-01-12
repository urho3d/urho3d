//
// Copyright (c) 2008-2020 the Urho3D project.
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
#include "../IO/VectorBuffer.h"

#include <Box2D/Box2D.h>

namespace Urho3D
{

class Camera;
class CollisionShape2D;
class RigidBody2D;

/// 2D Physics raycast hit.
struct URHO3D_API PhysicsRaycastResult2D
{
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
    float distance_{};
    /// Rigid body that was hit.
    RigidBody2D* body_{};
};

/// Delayed world transform assignment for parented 2D rigidbodies.
struct DelayedWorldTransform2D
{
    /// Rigid body.
    RigidBody2D* rigidBody_;
    /// Parent rigid body.
    RigidBody2D* parentRigidBody_;
    /// New world position.
    Vector3 worldPosition_;
    /// New world rotation.
    Quaternion worldRotation_;
};

/// 2D physics simulation world component. Should be added only to the root scene node.
class URHO3D_API PhysicsWorld2D : public Component, public b2ContactListener, public b2Draw
{
    URHO3D_OBJECT(PhysicsWorld2D, Component);

public:
    /// Construct.
    explicit PhysicsWorld2D(Context* context);
    /// Destruct.
    ~PhysicsWorld2D() override;
    /// Register object factory.
    static void RegisterObject(Context* context);

    /// Visualize the component as debug geometry.
    void DrawDebugGeometry(DebugRenderer* debug, bool depthTest) override;

    // Implement b2ContactListener
    /// Called when two fixtures begin to touch.
    void BeginContact(b2Contact* contact) override;
    /// Called when two fixtures cease to touch.
    void EndContact(b2Contact* contact) override;
    /// Called when contact is updated.
    void PreSolve(b2Contact* contact, const b2Manifold* oldManifold) override;

    // Implement b2Draw
    /// Draw a closed polygon provided in CCW order.
    void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) override;
    /// Draw a solid closed polygon provided in CCW order.
    void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) override;
    /// Draw a circle.
    void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color) override;
    /// Draw a solid circle.
    void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color) override;
    /// Draw a line segment.
    void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) override;
    /// Draw a transform. Choose your own length scale.
    void DrawTransform(const b2Transform& xf) override;
    /// Draw a point.
    void DrawPoint(const b2Vec2& p, float32 size, const b2Color& color) override;

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
    /// Add a delayed world transform assignment. Called by RigidBody2D.
    void AddDelayedWorldTransform(const DelayedWorldTransform2D& transform);

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
    void GetRigidBodies(PODVector<RigidBody2D*>& results, const Rect& aabb, unsigned collisionMask = M_MAX_UNSIGNED);

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
    b2World* GetWorld() { return world_.Get(); }

    /// Set node dirtying to be disregarded.
    void SetApplyingTransforms(bool enable) { applyingTransforms_ = enable; }

    /// Return whether node dirtying should be disregarded.
    bool IsApplyingTransforms() const { return applyingTransforms_; }

protected:
    /// Handle scene being assigned.
    void OnSceneSet(Scene* scene) override;

    /// Handle the scene subsystem update event, step simulation here.
    void HandleSceneSubsystemUpdate(StringHash eventType, VariantMap& eventData);
    /// Send begin contact events.
    void SendBeginContactEvents();
    /// Send end contact events.
    void SendEndContactEvents();

    /// Box2D physics world.
    UniquePtr<b2World> world_;
    /// Gravity.
    Vector2 gravity_;
    /// Velocity iterations.
    int velocityIterations_{};
    /// Position iterations.
    int positionIterations_{};

    /// Extra weak pointer to scene to allow for cleanup in case the world is destroyed before other components.
    WeakPtr<Scene> scene_;
    /// Debug renderer.
    DebugRenderer* debugRenderer_{};
    /// Debug draw depth test mode.
    bool debugDepthTest_{};

    /// Automatic simulation update enabled flag.
    bool updateEnabled_{true};
    /// Whether is currently stepping the world. Used internally.
    bool physicsStepping_{};
    /// Applying transforms.
    bool applyingTransforms_{};
    /// Rigid bodies.
    Vector<WeakPtr<RigidBody2D> > rigidBodies_;
    /// Delayed (parented) world transform assignments.
    HashMap<RigidBody2D*, DelayedWorldTransform2D> delayedWorldTransforms_;

    /// Contact info.
    struct ContactInfo
    {
        /// Construct.
        ContactInfo();
        /// Construct.
        explicit ContactInfo(b2Contact* contact);
        /// Write contact info to buffer.
        const PODVector<unsigned char>& Serialize(VectorBuffer& buffer) const;

        /// Rigid body A.
        SharedPtr<RigidBody2D> bodyA_;
        /// Rigid body B.
        SharedPtr<RigidBody2D> bodyB_;
        /// Node A.
        SharedPtr<Node> nodeA_;
        /// Node B.
        SharedPtr<Node> nodeB_;
        /// Shape A.
        SharedPtr<CollisionShape2D> shapeA_;
        /// Shape B.
        SharedPtr<CollisionShape2D> shapeB_;
        /// Number of contact points.
        int numPoints_{};
        /// Contact normal in world space.
        Vector2 worldNormal_;
        /// Contact positions in world space.
        Vector2 worldPositions_[b2_maxManifoldPoints];
        /// Contact overlap values.
        float separations_[b2_maxManifoldPoints]{};
    };
    /// Begin contact infos.
    Vector<ContactInfo> beginContactInfos_;
    /// End contact infos.
    Vector<ContactInfo> endContactInfos_;
    /// Temporary buffer with contact data.
    VectorBuffer contacts_;
};

}
