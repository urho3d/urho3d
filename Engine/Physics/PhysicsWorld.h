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

#pragma once

#include "Component.h"
#include "HashSet.h"
#include "PhysicsDefs.h"
#include "Vector3.h"

class CollisionShape;
class DebugRenderer;
class Deserializer;
class Node;
class Ray;
class RigidBody;
class Scene;
class Serializer;
class XMLElement;

struct HeightfieldData;
struct TriangleMeshData;

/// Physics raycast hit
struct PhysicsRaycastResult
{
    /// Hit position
    Vector3 position_;
    /// Hit normal
    Vector3 normal_;
    /// Hit distance from ray origin
    float distance_;
    /// Scene node
    Node* node_;
};

/// Internal physics contact info
struct PhysicsContactInfo
{
    /// World position
    Vector3 position_;
    /// World normal from perspective of first rigid body
    Vector3 normal_;
    /// Penetration depth
    float depth_;
    /// Velocity
    float velocity_;
};

/// Internal physics collision info
struct PhysicsCollisionInfo
{
    /// First scene node
    WeakPtr<Node> nodeA_;
    /// Second scene node
    WeakPtr<Node> nodeB_;
    /// First collision shape
    WeakPtr<CollisionShape> shapeA_;
    /// Second collision shape
    WeakPtr<CollisionShape> shapeB_;
    /// New collision flag
    bool newCollision_;
    /// Contacts
    PODVector<PhysicsContactInfo> contacts_;
};

static const float DEFAULT_MAX_NETWORK_ANGULAR_VELOCITY = 100.0f;

/// A physics simulation world
class PhysicsWorld : public Component
{
    OBJECT(PhysicsWorld);
    
public:
    /// Construct
    PhysicsWorld(Context* context);
    /// Destruct
    virtual ~PhysicsWorld();
    /// Register object factory
    static void RegisterObject(Context* context);
    
    /// Step the simulation forward
    void Update(float timeStep);
    /// Set simulation steps per second
    void SetFps(int fps);
    /// Set maximum contacts in one collision
    void SetMaxContacts(unsigned num);
    /// Set gravity
    void SetGravity(Vector3 gravity);
    /// Set default linear velocity deactivation threshold for new rigid bodies
    void SetLinearRestThreshold(float threshold);
    /// Set default linear velocity damping threshold
    void SetLinearDampingThreshold(float threshold);
    /// Set default linear velocity damping scale
    void SetLinearDampingScale(float scale);
    /// Set default angular velocity deactivation threshold for new rigid bodies
    void SetAngularRestThreshold(float threshold);
    /// Set default angular velocity damping threshold
    void SetAngularDampingThreshold(float threshold);
    /// Set default angular velocity damping scale
    void SetAngularDampingScale(float scale);
    /// Set collision bounce velocity threshold (apply bounce if above)
    void SetBounceThreshold(float threshold);
    /// Set maximum angular velocity for network replication
    void SetMaxNetworkAngularVelocity(float velocity);
    /// Set simulation ERP parameter
    void SetERP(float erp);
    /// Set simulation CFM parameter
    void SetCFM(float cfm);
    /// Set depth of contact surface
    void SetContactSurfaceLayer(float depth);
    /// Set simulation step time accumulator
    void SetTimeAccumulator(float time);
    /// Perform a physics world raycast
    void Raycast(PODVector<PhysicsRaycastResult>& result, const Ray& ray, float maxDistance, unsigned collisionMask =
        M_MAX_UNSIGNED);
    
    /// Return ODE world ID
    dWorldID GetWorld() const { return physicsWorld_; }
    /// Return ODE space ID
    dSpaceID GetSpace() const { return space_; }
    /// Return gravity
    Vector3 GetGravity() const;
    /// Return simulation steps per second
    int GetFps() const { return fps_; }
    /// Return maximum contacts per collision
    unsigned GetMaxContacts() const { return maxContacts_; }
    /// Return default linear velocity deactivation threshold
    float GetLinearRestThreshold() const;
    /// Return default linear velocity damping threshold
    float GetLinearDampingThreshold() const;
    /// Return default linear velocity damping scale
    float GetLinearDampingScale() const;
    /// Return default angular velocity damping threshold
    float GetAngularRestThreshold() const;
    /// Return default angular velocity damping threshold
    float GetAngularDampingThreshold() const;
    /// Return default angular velocity damping scale
    float GetAngularDampingScale() const;
    /// Return collision bounce velocity threshold
    float GetBounceThreshold() const { return bounceThreshold_; }
    /// Return maximum angular velocity for network replication
    float GetMaxNetworkAngularVelocity() const { return maxNetworkAngularVelocity_; }
    /// Return simulation ERP parameter
    float GetERP() const;
    /// Return simulation CFM parameter
    float GetCFM() const;
    /// Return depth of contact surface
    float GetContactSurfaceLayer() const;
    /// Return simulation step time accumulator
    float GetTimeAccumulator() const { return timeAcc_; }
    
    /// Add a rigid body to keep track of. Called by RigidBody
    void AddRigidBody(RigidBody* body);
    /// Remove a rigid body. Called by RigidBody
    void RemoveRigidBody(RigidBody* body);
    /// Send accumulated collision events
    void SendCollisionEvents();
    /// Add debug geometry to the debug graphics
    void DrawDebugGeometry(bool depthTest);
    
    /// Clean up the geometry cache
    void CleanupGeometryCache();
    /// Return the triangle mesh cache
    Map<String, SharedPtr<TriangleMeshData> >& GetTriangleMeshCache() { return triangleMeshCache_; }
    /// Return the heightfield cache
    Map<String, SharedPtr<HeightfieldData> >& GetHeightfieldCache() { return heightfieldCache_; }
    
protected:
    /// Handle node being assigned
    virtual void OnNodeSet(Node* node);
    
private:
    /// ODE collision callback
    static void NearCallback(void *userData, dGeomID geomA, dGeomID geomB);
    /// ODE raycast callback
    static void RaycastCallback(void *userData, dGeomID geomA, dGeomID geomB);
    /// Handle the scene subsystem update event, step simulation here
    void HandleSceneSubsystemUpdate(StringHash eventType, VariantMap& eventData);
    
    /// ODE world ID
    dWorldID physicsWorld_;
    /// ODE space ID
    dSpaceID space_;
    /// ODE ray geometry ID (for raycast)
    dGeomID rayGeometry_;
    /// ODE contact joint group ID
    dJointGroupID contactJoints_;
    /// Simulation steps per second
    unsigned fps_;
    /// Maximum contacts per collision
    unsigned maxContacts_;
    /// Collision bounce velocity threshold
    float bounceThreshold_;
    /// Maximum angular velocity for network replication
    float maxNetworkAngularVelocity_;
    /// Simulation step time accumulator
    float timeAcc_;
    /// Simulation random seed
    unsigned randomSeed_;
    /// Rigid bodies
    PODVector<RigidBody*> rigidBodies_;
    /// Collision contacts (PODVector<dContact>)
    void* contacts_;
    /// Collision pairs on this frame
    HashSet<Pair<RigidBody*, RigidBody*> > currentCollisions_;
    /// Collision pairs on the previous frame. Used to check if a collision is "new"
    HashSet<Pair<RigidBody*, RigidBody*> > previousCollisions_;
    /// Already processed rigid bodies during a poststep
    HashSet<RigidBody*> processedBodies_;
    /// Collision infos to be sent as events
    Vector<PhysicsCollisionInfo> collisionInfos_;
    /// Cache for triangle mesh geometries
    Map<String, SharedPtr<TriangleMeshData> > triangleMeshCache_;
    /// Cache for heightfield geometries
    Map<String, SharedPtr<HeightfieldData> > heightfieldCache_;
};

/// Register Physics library objects
void RegisterPhysicsLibrary(Context* context);
