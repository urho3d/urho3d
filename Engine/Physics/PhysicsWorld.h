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
#include "HashSet.h"
#include "Vector3.h"

#include <LinearMath/btIDebugDraw.h>

class CollisionShape;
class DebugRenderer;
class Deserializer;
class Joint;
class Node;
class Ray;
class RigidBody;
class Scene;
class Serializer;
class XMLElement;

class btCollisionConfiguration;
class btBroadphaseInterface;
class btConstraintSolver;
class btDiscreteDynamicsWorld;
class btDispatcher;
class btDynamicsWorld;

struct HeightfieldData;
struct TriangleMeshData;

/// Physics raycast hit.
struct PhysicsRaycastResult
{
    /// Hit position.
    Vector3 position_;
    /// Hit normal.
    Vector3 normal_;
    /// Hit distance from ray origin.
    float distance_;
    /// Rigid body that was hit.
    RigidBody* body_;
};

/// Internal physics contact info
struct PhysicsContactInfo
{
    /// World position.
    Vector3 position_;
    /// World normal from perspective of first rigid body.
    Vector3 normal_;
    /// Penetration depth.
    float depth_;
    /// Velocity.
    float velocity_;
};

/// Internal physics collision info.
struct PhysicsCollisionInfo
{
    /// First rigid body.
    WeakPtr<RigidBody> bodyA_;
    /// Second rigid body.
    WeakPtr<RigidBody> bodyB_;
    /// New collision flag.
    bool newCollision_;
    /// Contacts.
    PODVector<PhysicsContactInfo> contacts_;
};

static const float DEFAULT_MAX_NETWORK_ANGULAR_VELOCITY = 100.0f;

/// Physics simulation world component. Should be added only to the root scene node.
class PhysicsWorld : public Component, public btIDebugDraw
{
    friend void InternalPreTickCallback(btDynamicsWorld *world, btScalar timeStep);
    friend void InternalTickCallback(btDynamicsWorld *world, btScalar timeStep);
    
    OBJECT(PhysicsWorld);
    
public:
    /// Construct.
    PhysicsWorld(Context* scontext);
    /// Destruct.
    virtual ~PhysicsWorld();
    /// Register object factory.
    static void RegisterObject(Context* context);
    
    /// Draw a physics debug line.
    virtual void drawLine(const btVector3& from, const btVector3& to, const btVector3& color);
    /// Log warning from the physics engine.
    virtual void reportErrorWarning(const char* warningString);
    /// Draw a physics debug contact point. Not implemented.
    virtual void drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color) {}
    /// Draw physics debug 3D text. Not implemented.
    virtual void draw3dText(const btVector3& location,const char* textString) {}
    /// %Set debug draw flags.
    virtual void setDebugMode(int debugMode) { debugMode_ = debugMode; }
    /// Return debug draw flags.
    virtual int getDebugMode() const { return debugMode_; }
    
    /// Step the simulation forward.
    void Update(float timeStep);
    /// %Set simulation steps per second.
    void SetFps(int fps);
    /// %Set gravity.
    void SetGravity(Vector3 gravity);
    /// %Set whether to interpolate between simulation steps.
    void SetInterpolation(bool enable);
    /// %Set maximum angular velocity for network replication.
    void SetMaxNetworkAngularVelocity(float velocity);
    /// %Set simulation step time accumulator.
    void SetTimeAccumulator(float time);
    /// Perform a physics world raycast.
    void Raycast(PODVector<PhysicsRaycastResult>& result, const Ray& ray, float maxDistance, unsigned collisionMask =
        M_MAX_UNSIGNED);
    /// Perform a physics world raycast and return the closest result.
    void RaycastSingle(PhysicsRaycastResult& result, const Ray& ray, float maxDistance, unsigned collisionMask =
        M_MAX_UNSIGNED);
    
    /// Return gravity.
    Vector3 GetGravity() const;
    /// Return whether interpolation between simulation steps is enabled.
    bool GetInterpolation() const { return interpolation_; }
    /// Return simulation steps per second.
    int GetFps() const { return fps_; }
    /// Return maximum angular velocity for network replication.
    float GetMaxNetworkAngularVelocity() const { return maxNetworkAngularVelocity_; }
    
    /// Add a rigid body to keep track of. Called by RigidBody.
    void AddRigidBody(RigidBody* body);
    /// Remove a rigid body. Called by RigidBody.
    void RemoveRigidBody(RigidBody* body);
    /// Add a collision shape to keep track of. Called by CollisionShape.
    void AddCollisionShape(CollisionShape* shape);
    /// Remove a collision shape. Called by CollisionShape.
    void RemoveCollisionShape(CollisionShape* shape);
    /// Add a joint to keep track of. Called by Joint.
    void AddJoint(Joint* joint);
    /// Remove a joint. Called by Joint.
    void RemoveJoint(Joint* joint);
    /// Add debug geometry to the debug renderer.
    void DrawDebugGeometry(bool depthTest);
    
    /// Return the Bullet physics world.
    btDiscreteDynamicsWorld* GetWorld() { return world_; }
    /// Clean up the geometry cache.
    void CleanupGeometryCache();
    /// Return the triangle mesh cache.
    Map<String, SharedPtr<TriangleMeshData> >& GetTriangleMeshCache() { return triangleMeshCache_; }
    /// Return the heightfield cache.
    Map<String, SharedPtr<HeightfieldData> >& GetHeightfieldCache() { return heightfieldCache_; }
    
protected:
    /// Handle node being assigned.
    virtual void OnNodeSet(Node* node);
    
private:
    /// Handle the scene subsystem update event, step simulation here.
    void HandleSceneSubsystemUpdate(StringHash eventType, VariantMap& eventData);
    /// Trigger update before each physics simulation step.
    void PreStep(float timeStep);
    /// Trigger update after ecah physics simulation step.
    void PostStep(float timeStep);
    /// Send accumulated collision events.
    void SendCollisionEvents();
    
    /// Bullet collision configuration.
    btCollisionConfiguration* collisionConfiguration_;
    /// Bullet collision dispatcher.
    btDispatcher* collisionDispatcher_;
    /// Bullet collision broadphase.
    btBroadphaseInterface* broadphase_;
    /// Bullet constraint solver.
    btConstraintSolver* solver_;
    /// Bullet physics world.
    btDiscreteDynamicsWorld* world_;
    /// Extra weak pointer to scene to allow for cleanup in case the world is destroyed before other components.
    WeakPtr<Scene> scene_;
    /// Rigid bodies in the world.
    PODVector<RigidBody*> rigidBodies_;
    /// Collision shapes in the world.
    PODVector<CollisionShape*> collisionShapes_;
    /// Joints in the world.
    PODVector<Joint*> joints_;
    /// Collision pairs on this frame.
    HashSet<Pair<RigidBody*, RigidBody*> > currentCollisions_;
    /// Collision pairs on the previous frame. Used to check if a collision is "new."
    HashSet<Pair<RigidBody*, RigidBody*> > previousCollisions_;
    /// Already processed rigid bodies during a poststep.
    HashSet<RigidBody*> processedBodies_;
    /// Collision infos to be sent as events.
    Vector<PhysicsCollisionInfo> collisionInfos_;
    /// Cache for triangle mesh geometries.
    Map<String, SharedPtr<TriangleMeshData> > triangleMeshCache_;
    /// Cache for heightfield geometries.
    Map<String, SharedPtr<HeightfieldData> > heightfieldCache_;
    /// Simulation steps per second.
    unsigned fps_;
    /// Time accumulator for non-interpolated mode.
    float timeAcc_;
    /// Maximum angular velocity for network replication.
    float maxNetworkAngularVelocity_;
    /// Interpolation flag.
    bool interpolation_;
    /// Debug renderer.
    DebugRenderer* debugRenderer_;
    /// Debug draw flags.
    int debugMode_;
    /// Debug draw depth test mode.
    bool debugDepthTest_;
};

/// Register Physics library objects.
void RegisterPhysicsLibrary(Context* context);
