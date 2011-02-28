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

#ifndef PHYSICS_PHYSICSWORLD_H
#define PHYSICS_PHYSICSWORLD_H

#include "EventListener.h"
#include "PhysicsDefs.h"
#include "SceneExtension.h"
#include "SharedPtr.h"
#include "Vector3.h"

#include <set>

class DebugRenderer;
class Deserializer;
class Entity;
class Ray;
class RigidBody;
class Scene;
class Serializer;
class XMLElement;

//! Physics raycast hit
struct PhysicsRaycastResult
{
    //! Hit position
    Vector3 mPosition;
    //! Hit normal
    Vector3 mNormal;
    //! Hit distance from ray origin
    float mDistance;
    //! Rigid body
    RigidBody* mBody;
};

//! Internal physics contact info
struct PhysicsContactInfo
{
    //! World position
    Vector3 mPosition;
    //! World normal from perspective of first rigid body
    Vector3 mNormal;
    //! Penetration depth
    float mDepth;
    //! Velocity
    float mVelocity;
};

//! Internal physics collision info
struct PhysicsCollisionInfo
{
    //! First entity
    WeakPtr<Entity> mEntityA;
    //! Second entity
    WeakPtr<Entity> mEntityB;
    //! First rigid body
    WeakPtr<RigidBody> mRigidBodyA;
    //! Second rigid body
    WeakPtr<RigidBody> mRigidBodyB;
    //! New collision flag
    bool mNewCollision;
    //! Contacts
    std::vector<PhysicsContactInfo> mContacts;
};

static const float PHYSICS_MIN_TIMESTEP = 0.001f;

//! A physics simulation world
class PhysicsWorld : public SceneExtension, public EventListener
{
    DEFINE_TYPE(PhysicsWorld);
    
public:
    //! Construct
    PhysicsWorld();
    //! Destruct
    virtual ~PhysicsWorld();
    
    //! Write extension properties to a stream
    virtual void save(Serializer& dest);
    //! Read extension properties from a stream
    virtual void load(Deserializer& source);
    //! Write extension properties into an XML element
    virtual void saveXML(XMLElement& dest);
    //! Read extension properties from an XML element
    virtual void loadXML(const XMLElement& source);
    //! Scene extension update. Step the physics simulation
    virtual void update(float timeStep);
    //! Set client-side prediction playback mode
    virtual void setPlayback(bool enable);
    
    //! Set gravity
    void setGravity(const Vector3& gravity);
    //! Set simulation steps per second
    void setFps(int fps);
    //! Set maximum contacts in one collision
    void setMaxContacts(unsigned contacts);
    //! Set default linear velocity deactivation threshold for new rigid bodies
    void setLinearRestThreshold(float threshold);
    //! Set default linear velocity damping threshold (apply damping if above) and scale for new rigid bodies
    void setLinearDamping(float threshold, float scale);
    //! Set default angular velocity deactivation threshold for new rigid bodies
    void setAngularRestThreshold(float threshold);
    //! Set default angular velocity damping threshold (apply damping if above) and scale for new rigid bodies
    void setAngularDamping(float threshold, float scale);
    //! Set maximum angular velocity that can be transmitted over network (scaled to 16 bits)
    void setAngularMaxNetVelocity(float velocity);
    //! Set collision bounce velocity threshold (apply bounce if above)
    void setBounceThreshold(float threshold);
    //! Set simulation ERP parameter
    void setERP(float erp);
    //! Set simulation CFM parameter
    void setCFM(float cfm);
    //! Set depth of contact surface
    void setContactSurfaceLayer(float depth);
    //! Set simulation step time accumulator
    void setTimeAccumulator(float time);
    //! Set simulation random seed
    void setRandomSeed(unsigned seed);
    //! Set whether to draw debug geometry
    void setDrawDebugGeometry(bool enable);
    //! Perform a physics world raycast
    void raycast(std::vector<PhysicsRaycastResult>& result, const Ray& ray, float maxDistance, unsigned collisionMask =
        M_MAX_UNSIGNED);
    
    //! Return ODE world ID
    dWorldID getWorld() const { return mWorld; }
    //! Return ODE space ID
    dSpaceID getSpace() const { return mSpace; }
    //! Return gravity
    Vector3 getGravity() const;
    //! Return simulation steps per second
    int getFps() const { return mFps; }
    //! Return maximum contacts per collision
    unsigned getMaxContacts() const { return mMaxContacts; }
    //! Return default linear velocity deactivation threshold
    float getLinearRestThreshold() const;
    //! Return default linear velocity damping threshold
    float getLinearDampingThreshold() const;
    //! Return default linear velocity damping scale
    float getLinearDampingScale() const;
    //! Return default angular velocity damping threshold
    float getAngularRestThreshold() const;
    //! Return default angular velocity damping threshold
    float getAngularDampingThreshold() const;
    //! Return default angular velocity damping scale
    float getAngularDampingScale() const;
    //! Return maximum angular velocity transmitted over the network
    float getAngularMaxNetVelocity() const { return mAngularMaxNetVelocity; }
    //! Return collision bounce velocity threshold
    float getBounceThreshold() const { return mBounceThreshold; }
    //! Return simulation ERP parameter
    float getERP() const;
    //! Return simulation CFM parameter
    float getCFM() const;
    //! Return depth of contact surface
    float getContactSurfaceLayer() const;
    //! Return simulation step time accumulator
    float getTimeAccumulator() const { return mTimeAcc; }
    //! Return simulation random seed
    unsigned getRandomSeed() const;
    //! Return whether to draw debug geometry
    bool getDrawDebugGeometry() const { return mDrawDebugGeometry; }
    
    //! Add a rigid body to keep track of. Called by RigidBody
    void addRigidBody(RigidBody* body);
    //! Remove a rigid body. Called by RigidBody
    void removeRigidBody(RigidBody* body);
    //! Send accumulated collision events
    void sendCollisionEvents();
    //! Add debug geometry to the debug renderer
    void drawDebugGeometry();
    
private:
    //! ODE collision callback
    static void nearCallback(void *userData, dGeomID geomA, dGeomID geomB);
    //! ODE raycast callback
    static void raycastCallback(void *userData, dGeomID geomA, dGeomID geomB);
    //! Handle post render update event. Draw debug geometry here if enabled
    void handlePostRenderUpdate(StringHash eventType, VariantMap& eventData);
    
    //! ODE world ID
    dWorldID mWorld;
    //! ODE space ID
    dSpaceID mSpace;
    //! ODE ray geometry ID (for raycast)
    dGeomID mRayGeometry;
    //! ODE contact joint group ID
    dJointGroupID mContactJoints;
    //! Simulation steps per second
    unsigned mFps;
    //! Maximum contacts per collision
    unsigned mMaxContacts;
    //! Collision bounce velocity threshold
    float mBounceThreshold;
    //! Maximum angular velocity to be sent over the network
    float mAngularMaxNetVelocity;
    //! Simulation step time accumulator
    float mTimeAcc;
    //! Debug draw flag
    bool mDrawDebugGeometry;
    //! Rigid bodies
    std::vector<RigidBody*> mRigidBodies;
    //! Collision pairs on this frame
    std::set<std::pair<RigidBody*, RigidBody*> > mCurrentCollisions;
    //! Collision pairs on the previous frame. Used to check if a collision is "new"
    std::set<std::pair<RigidBody*, RigidBody*> > mPreviousCollisions;
    //! Collision infos to be sent as events
    std::vector<PhysicsCollisionInfo> mCollisionInfos;
};

#endif // PHYSICS_PHYSICSWORLD_H
