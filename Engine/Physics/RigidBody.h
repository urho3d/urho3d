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

#ifndef PHYSICS_RIGIDBODY_H
#define PHYSICS_RIGIDBODY_H

#include "CollisionShape.h"
#include "Node.h"
#include "PhysicsDefs.h"

#include <map>

class DebugRenderer;
class PhysicsWorld;

//! Rigid body motion mode
enum PhysicsMode
{
    PHYS_STATIC = 0,
    PHYS_DYNAMIC,
    PHYS_KINEMATIC
};

//! Rigid body scene node
class RigidBody : public Node
{
    DEFINE_TYPE(RigidBody);
    
    friend class PhysicsWorld;
    
public:
    //! Construct with physics world pointer and name
    RigidBody(PhysicsWorld* world, const std::string& name = std::string());
    //! Destruct. Free the rigid body and geometries
    virtual ~RigidBody();
    
    //! Write component state to a stream
    virtual void save(Serializer& dest);
    //! Read component state from a stream
    virtual void load(Deserializer& source, ResourceCache* cache);
    //! Write component state to an XML element
    virtual void saveXML(XMLElement& dest);
    //! Read component state from an XML element
    virtual void loadXML(const XMLElement& source, ResourceCache* cache);
    //! Write a network update
    virtual bool writeNetUpdate(Serializer& dest, Serializer& destRevision, Deserializer& baseRevision, const NetUpdateInfo& info);
    //! Read a network update
    virtual void readNetUpdate(Deserializer& source, ResourceCache* cache, const NetUpdateInfo& info);
    //! Perform client-side visual smoothing
    virtual void interpolate(bool snapToEnd);
    
    //! Set motion mode
    void setMode(PhysicsMode mode);
    //! Set mass
    void setMass(float mass);
    //! Set friction coefficient
    void setFriction(float friction);
    //! Set bounce coefficient
    void setBounce(float bounce);
    //! Set collision shape
    void setCollisionShape(CollisionShape* shape);
    //! Set collision group bits
    void setCollisionGroup(unsigned group);
    //! Set collision mask bits
    void setCollisionMask(unsigned mask);
    //! Set both physics and rendering position (network client sets only physics position because of smoothing)
    void setPosition(const Vector3& position);
    //! Set both physics and rendering rotation (network client sets only physics rotation because of smoothing)
    void setRotation(const Quaternion& rotation);
    //! Set uniform scale
    void setScale(float scale);
    //! Set scale
    void setScale(const Vector3& scale);
    //! Set both physics and rendering transform (network client sets only physics rotation because of smoothing)
    void setTransform(const Vector3& position, const Quaternion& rotation);
    //! Set both physics and rendering transform (network client sets only physics rotation because of smoothing)
    void setTransform(const Vector3& position, const Quaternion& rotation, float scale);
    //! Set both physics and rendering transform (network client sets only physics rotation because of smoothing)
    void setTransform(const Vector3& position, const Quaternion& rotation, const Vector3& scale);
    //! Modify scale uniformly
    void scale(float scale);
    //! Modify scale
    void scale(const Vector3& scale);
    //! Set linear velocity
    void setLinearVelocity(const Vector3& velocity);
    //! Set linear velocity deactivation threshold
    void setLinearRestThreshold(float threshold);
    //! Set linear velocity damping threshold (apply damping if above) and scale
    void setLinearDamping(float threshold, float scale);
    //! Set angular velocity
    void setAngularVelocity(const Vector3& angularVelocity);
    //! Set angular velocity deactivation threshold
    void setAngularRestThreshold(float threshold);
    //! Set angular velocity damping threshold (apply damping if above) and scale
    void setAngularDamping(float threshold, float scale);
    //! Set maximum angular velocity. Set to 0 to disable rotation
    void setAngularMaxVelocity(float velocity);
    //! Set rigid body active/inactive state
    void setActive(bool active);
    //! Apply force to center of mass
    void applyForce(const Vector3& force);
    //! Apply force at position
    void applyForceAtPosition(const Vector3& force, const Vector3& position);
    //! Apply torque
    void applyTorque(const Vector3& torque);
    //! Reset accumulated forces
    void resetForces();
    
    //! Return physics world
    PhysicsWorld* getPhysicsWorld() const { return mWorld; }
    //! Return collision shape
    CollisionShape* getCollisionShape() const { return mCollisionShape; }
    //! Return motion mode
    PhysicsMode getMode() const { return mMode; }
    //! Return mass
    float getMass() const { return mMass; }
    //! Return friction coefficient
    float getFriction() const { return mFriction; }
    //! Return bounce coefficient
    float getBounce() const { return mBounce; }
    //! Return collision group bits
    unsigned getCollisionGroup() const { return mCollisionGroup; }
    //! Return collision mask bits
    unsigned getCollisionMask() const { return mCollisionMask; }
    //! Return ODE body ID
    dBodyID getBody() const { return mBody; }
    //! Return ODE geometry ID's
    const std::vector<dGeomID>& getGeometries() const { return mGeometries; }
    //! Return physics position
    Vector3 getPhysicsPosition() const;
    //! Return physics rotation
    Quaternion getPhysicsRotation() const;
    //! Return linear velocity
    Vector3 getLinearVelocity() const;
    //! Return linear velocity deactivation threshold
    float getLinearRestThreshold() const;
    //! Return linear velocity damping threshold
    float getLinearDampingThreshold() const;
    //! Return linear velocity damping scale
    float getLinearDampingScale() const;
    //! Return angular velocity
    Vector3 getAngularVelocity() const;
    //! Return angular velocity deactivation threshold
    float getAngularRestThreshold() const;
    //! Return angular velocity damping threshold
    float getAngularDampingThreshold() const;
    //! Return angular velocity damping scale
    float getAngularDampingScale() const;
    //! Return maximum angular velocity
    float getAngularMaxVelocity() const;
    //! Return whether body is active
    bool isActive() const;
    
    //! Draw debug geometry
    void drawDebugGeometry(DebugRenderer* debug);
    
private:
    //! Store previous transform for rendering interpolation
    void preStep();
    //! Interpolate between previous and current transform and store as rendering transform
    void postStep(float t);
    //! Create the body
    void createBody();
    //! Remove the body
    void removeBody();
    //! Remove geometries
    void removeGeometries();
    //! Update geometries when collision shape or motion mode changes
    void updateGeometries();
    //! Recalculate mass
    void updateMass();
    //! Set temporary disable for optimizing client-side prediction
    void setTempDisabled(bool disable);
    
    //! Physics world
    SharedPtr<PhysicsWorld> mWorld;
    //! Collision shape
    SharedPtr<CollisionShape> mCollisionShape;
    //! Motion mode
    PhysicsMode mMode;
    //! Mass
    float mMass;
    //! Friction coefficient
    float mFriction;
    //! Bounce coefficient
    float mBounce;
    //! Collision group bits
    unsigned mCollisionGroup;
    //! Collision mask bits
    unsigned mCollisionMask;
    //! ODE body ID
    dBodyID mBody;
    //! ODE geometry ID's
    std::vector<dGeomID> mGeometries;
    //! Unique (scaled) copies of collision geometry data
    std::vector<SharedPtr<CollisionGeometryData> > mUniqueGeometryDatas;
    //! Previous position for rendering interpolation
    Vector3 mPreviousPosition;
    //! Previous rotation for rendering interpolation
    Quaternion mPreviousRotation;
    //! Temp disable flag
    bool mTempDisabled;
    //! Saved active/inactive flag
    bool mSavedActiveFlag;
    //! Saved linear velocity
    Vector3 mSavedLinearVelocity;
    //! Saved angular velocity
    Vector3 mSavedAngularVelocity;
};

#endif // PHYSICS_RIGIDBODY_H
