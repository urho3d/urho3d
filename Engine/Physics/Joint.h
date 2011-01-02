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

#ifndef PHYSICS_JOINT_H
#define PHYSICS_JOINT_H

#include "Component.h"
#include "PhysicsDefs.h"
#include "SharedPtr.h"
#include "Vector3.h"

//! Supported joint types
enum JointType
{
    JOINT_NONE = 0,
    JOINT_BALL,
    JOINT_HINGE
};

class PhysicsWorld;
class RigidBody;

//! A joint component that connects two rigid bodies, or one rigid body to the world
class Joint : public Component
{
    DEFINE_TYPE(Joint);
    
public:
    //! Construct with physics world pointer and name
    Joint(PhysicsWorld* world, const std::string& name = std::string());
    //! Destruct
    ~Joint();
    
    //! Write component state to a stream
    virtual void save(Serializer& dest);
    //! Read component state from a stream
    virtual void load(Deserializer& source, ResourceCache* cache);
    //! Write component state to an XML element
    virtual void saveXML(XMLElement& dest);
    //! Read component state from an XML element
    virtual void loadXML(const XMLElement& source, ResourceCache* cache);
    //! Resolve component references after loading
    virtual void postLoad(ResourceCache* cache);
    //! Write a network update
    virtual bool writeNetUpdate(Serializer& dest, Serializer& destRevision, Deserializer& baseRevision, const NetUpdateInfo& info);
    //! Read a network update
    virtual void readNetUpdate(Deserializer& source, ResourceCache* cache, const NetUpdateInfo& info);
    //! Resolve component references after a network update
    virtual void postNetUpdate(ResourceCache* cache);
    //! Return component references
    virtual void getComponentRefs(std::vector<ComponentRef>& dest);
    
    //! Remove the joint
    void reset();
    //! Set a ball joint
    bool setBall(const Vector3& position, RigidBody* bodyA, RigidBody* bodyB = 0);
    //! Set a hinge joint
    bool setHinge(const Vector3& position, const Vector3& axis, RigidBody* bodyA, RigidBody* bodyB = 0);
    //! Set joint world position
    void setPosition(const Vector3& position);
    //! Set joint world axis if applicable
    void setAxis(const Vector3& axis);
    
    //! Return physics world
    PhysicsWorld* getPhysicsWorld() const { return mWorld; }
    //! Return the first rigid body
    RigidBody* getBodyA() const { return mBodyA; }
    //! Return the second rigid body
    RigidBody* getBodyB() const { return mBodyB; }
    //! Return joint type
    JointType getJointType() const { return mType; }
    //! Return the ODE joint ID
    dJointID getJoint() const { return mJoint; }
    //! Return joint world position
    Vector3 getPosition() const;
    //! Return joint world axis
    Vector3 getAxis() const;
    
private:
    //! Physics world
    SharedPtr<PhysicsWorld> mWorld;
    //! First rigid body
    SharedPtr<RigidBody> mBodyA;
    //! Second rigid body
    SharedPtr<RigidBody> mBodyB;
    //! Joint type
    JointType mType;
    //! ODE joint ID
    dJointID mJoint;
    //! Joint position
    Vector3 mPosition;
    //! Joint axis
    Vector3 mAxis;
    //! First rigid body component reference
    ComponentRef mBodyARef;
    //! Second rigid body component reference
    ComponentRef mBodyBRef;
    //! Network update received flag
    bool mNetDirty;
};

#endif // PHYSICS_JOINT_H
