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

#include "Precompiled.h"
#include "DebugRenderer.h"
#include "Log.h"
#include "PhysicsWorld.h"
#include "ReplicationUtils.h"
#include "ResourceCache.h"
#include "RigidBody.h"
#include "StringUtils.h"
#include "XMLElement.h"

#include <ode/ode.h>
#include <../ode/src/heightfield.h>
#include <../ode/src/collision_std.h>

#include "DebugNew.h"

static const std::string modeNames[] =
{
    "static",
    "dynamic",
    "kinematic"
};

RigidBody::RigidBody(PhysicsWorld* world, const std::string& name) :
    Node(NODE_RIGIDBODY, name),
    mWorld(world),
    mMode(PHYS_STATIC),
    mMass(1.0f),
    mFriction(0.5f),
    mBounce(0.0f),
    mCollisionGroup(M_MAX_UNSIGNED),
    mCollisionMask(M_MAX_UNSIGNED),
    mBody(0),
    mTempDisabled(false)
{
    if (!mWorld)
        EXCEPTION("Null physics world for RigidBody");
    
    mWorld->addRigidBody(this);
}

RigidBody::~RigidBody()
{
    removeGeometries();
    removeBody();
    
    mWorld->removeRigidBody(this);
}

void RigidBody::save(Serializer& dest)
{
    // Write Component properties
    Component::save(dest);
    
    // Write transform
    dest.writeVector3(getPhysicsPosition());
    dest.writeQuaternion(getPhysicsRotation());
    dest.writeVector3(Node::getScale());
    
    // Write parent node reference (should be no parent)
    ComponentRef parentRef(mParent);
    parentRef.write(dest);
    
    // Write the RigidBody properties we store ourselves
    dest.writeUByte((unsigned char)mMode);
    dest.writeFloat(mMass);
    dest.writeFloat(mFriction);
    dest.writeFloat(mBounce);
    dest.writeStringHash(getResourceHash(mCollisionShape));
    dest.writeUInt(mCollisionGroup);
    dest.writeUInt(mCollisionMask);
    
    // Write the RigidBody properties contained within the body object
    dest.writeVector3(getLinearVelocity());
    dest.writeFloat(getLinearRestThreshold());
    dest.writeFloat(getLinearDampingThreshold());
    dest.writeFloat(getLinearDampingScale());
    dest.writeVector3(getAngularVelocity());
    dest.writeFloat(getAngularRestThreshold());
    dest.writeFloat(getAngularDampingThreshold());
    dest.writeFloat(getAngularDampingScale());
    dest.writeFloat(getAngularMaxVelocity());
    dest.writeBool(isActive());
}

void RigidBody::load(Deserializer& source, ResourceCache* cache)
{
    // Read Component properties
    Component::load(source, cache);
    
    // Read transform
    Vector3 position = source.readVector3();
    Quaternion rotation = source.readQuaternion();
    setTransform(position, rotation);
    setScale(source.readVector3());
    
    // Read parent node reference
    mParentRef.read(source);
    
    // Read the RigidBody properties we store ourselves
    setMode((PhysicsMode)source.readUByte());
    setMass(source.readFloat());
    mFriction = source.readFloat();
    mBounce = source.readFloat();
    setCollisionShape(cache->getResource<CollisionShape>(source.readStringHash()));
    setCollisionGroup(source.readUInt());
    setCollisionMask(source.readUInt());
    
    // Read the RigidBody properties contained within the body object
    setLinearVelocity(source.readVector3());
    setLinearRestThreshold(source.readFloat());
    float threshold = source.readFloat();
    float scale = source.readFloat();
    setLinearDamping(threshold, scale);
    setAngularVelocity(source.readVector3());
    setAngularRestThreshold(source.readFloat());
    threshold = source.readFloat();
    scale = source.readFloat();
    setAngularDamping(threshold, scale);
    setAngularMaxVelocity(source.readFloat());
    setActive(source.readBool());
    
    resetForces();
}

void RigidBody::saveXML(XMLElement& dest)
{
    // Write Component properties
    Component::saveXML(dest);
    
    // Write transform
    XMLElement transformElem = dest.createChildElement("transform");
    transformElem.setVector3("pos", getPosition());
    transformElem.setQuaternion("rot", getRotation());
    transformElem.setVector3("scale", getScale());
    
    // Write parent node reference
    ComponentRef parentRef(mParent, true);
    if (parentRef.mEntityID)
    {
        XMLElement parentElem = dest.createChildElement("parent");
        parentRef.writeXML(parentElem);
    }
    
    // Write the RigidBody properties
    XMLElement bodyElem = dest.createChildElement("body");
    bodyElem.setString("mode", modeNames[mMode]);
    bodyElem.setFloat("mass", mMass);
    bodyElem.setFloat("friction", mFriction);
    bodyElem.setFloat("bounce", mBounce);
    bodyElem.setBool("active", isActive());
    
    XMLElement collisionElem = dest.createChildElement("collision");
    collisionElem.setString("shape", getResourceName(mCollisionShape));
    collisionElem.setInt("group", mCollisionGroup);
    collisionElem.setInt("mask", mCollisionMask);
    
    XMLElement linearElem = dest.createChildElement("linear");
    linearElem.setVector3("velocity", getLinearVelocity());
    linearElem.setFloat("restthreshold", getLinearRestThreshold());
    linearElem.setFloat("dampingthreshold", getLinearDampingThreshold());
    linearElem.setFloat("dampingscale", getLinearDampingScale());
    XMLElement angularElem = dest.createChildElement("angular");
    angularElem.setVector3("velocity", getAngularVelocity());
    angularElem.setFloat("restthreshold", getAngularRestThreshold());
    angularElem.setFloat("dampingthreshold", getAngularDampingThreshold());
    angularElem.setFloat("dampingscale", getAngularDampingScale());
    angularElem.setFloat("maxvelocity", getAngularMaxVelocity());
}

void RigidBody::loadXML(const XMLElement& source, ResourceCache* cache)
{
    // Read Component properties
    Component::loadXML(source, cache);
    
    // Read transform
    XMLElement transformElem = source.getChildElement("transform");
    Vector3 position = transformElem.getVector3("pos");
    Quaternion rotation = transformElem.getQuaternion("rot");
    setTransform(position, rotation);
    setScale(transformElem.getVector3("scale"));
    
    // Read parent node reference
    if (source.hasChildElement("parent"))
    {
        XMLElement parentElem = source.getChildElement("parent");
        mParentRef.readXML(parentElem);
    }
    else
        mParentRef = ComponentRef();
    
    // Read the RigidBody properties we store ourselves
    XMLElement bodyElem = source.getChildElement("body");
    setMode((PhysicsMode)getIndexFromStringList(bodyElem.getStringLower("mode"), modeNames, 3, 0));
    setMass(bodyElem.getFloat("mass"));
    mFriction = bodyElem.getFloat("friction");
    mBounce = bodyElem.getFloat("bounce");
    
    XMLElement collisionElem = source.getChildElement("collision");
    setCollisionShape(cache->getResource<CollisionShape>(collisionElem.getString("shape")));
    setCollisionGroup(collisionElem.getInt("group"));
    setCollisionMask(collisionElem.getInt("mask"));
    
    // Read the RigidBody properties contained within the body object
    if (source.hasChildElement("linear"))
    {
        XMLElement linearElem = source.getChildElement("linear");
        setLinearVelocity(linearElem.getVector3("velocity"));
        setLinearRestThreshold(linearElem.getFloat("restthreshold"));
        setLinearDamping(linearElem.getFloat("dampingthreshold"), linearElem.getFloat("dampingscale"));
    }
    
    if (source.hasChildElement("angular"))
    {
        XMLElement angularElem = source.getChildElement("angular");
        setAngularVelocity(angularElem.getVector3("velocity"));
        setAngularRestThreshold(angularElem.getFloat("restthreshold"));
        setAngularDamping(angularElem.getFloat("dampingthreshold"), angularElem.getFloat("dampingscale"));
        setAngularMaxVelocity(angularElem.getFloat("maxvelocity"));
    }
    
    setActive(bodyElem.getBool("active"));
    
    resetForces();
}

bool RigidBody::writeNetUpdate(Serializer& dest, Serializer& destRevision, Deserializer& baseRevision, const NetUpdateInfo& info)
{
    Vector3 position = getPhysicsPosition();
    Quaternion rotation = getPhysicsRotation();
    Vector3 scale = getScale();
    ComponentRef parentRef(mParent);
    
    // Build bitmask of changed properties
    unsigned char bits = 0;
    unsigned char bits2 = 0;
    checkVector3(position, Vector3::sZero, baseRevision, bits, 1);
    checkQuaternion(rotation, Quaternion::sIdentity, baseRevision, bits, 2);
    checkVector3(scale, Vector3::sUnity, baseRevision, bits, 4);
    checkComponentRef(parentRef, ComponentRef(), baseRevision, bits, 8);
    checkUByte((unsigned char)mMode, (unsigned char)PHYS_STATIC, baseRevision, bits, 16);
    checkFloat(mMass, 1.0f, baseRevision, bits, 32);
    checkVector3(getLinearVelocity(), Vector3::sZero, baseRevision, bits, 64);
    checkVector3(getAngularVelocity(), Vector3::sZero, baseRevision, bits, 128);
    checkStringHash(getResourceHash(mCollisionShape), baseRevision, bits2, 1);
    checkUInt(mCollisionGroup, M_MAX_UNSIGNED, baseRevision, bits2, 2);
    checkUInt(mCollisionMask, M_MAX_UNSIGNED, baseRevision, bits2, 2);
    checkFloat(mFriction, 0.5f, baseRevision, bits, 4);
    checkFloat(mBounce, 0.0f, baseRevision, bits, 8);
    checkFloat(getLinearRestThreshold(), 0.01f, baseRevision, bits2, 16);
    checkFloat(getLinearDampingThreshold(), 0.01f, baseRevision, bits2, 16);
    checkFloat(getLinearDampingScale(), 0.0f, baseRevision, bits2, 16);
    checkFloat(getAngularRestThreshold(), 0.01f, baseRevision, bits2, 32);
    checkFloat(getAngularDampingThreshold(), 0.01f, baseRevision, bits2, 32);
    checkFloat(getAngularDampingScale(), 0.0f, baseRevision, bits2, 32);
    checkFloat(getAngularMaxVelocity(), M_INFINITY, baseRevision, bits2, 64);
    
    // If body is active and dynamic, keep sending the physics state
    // This is because clients will extrapolate, and need to be snapped to the right state
    if ((mMode == PHYS_DYNAMIC) && (isActive()))
        bits |= (1 | 2 | 64 | 128);
    
    // Remove unnecessary properties
    if (mMode == PHYS_STATIC)
    {
        bits &= ~(64 | 128);
        bits2 &= ~(16 | 32 | 64);
    }
    if (getAngularMaxVelocity() == 0.0f)
        bits &= ~128;
    
    // Update replication state fully, and network stream by delta
    dest.writeUByte(bits);
    dest.writeUByte(bits2);
    writeVector3Delta(position, dest, destRevision, bits & 1);
    writePackedQuaternionDelta(rotation, dest, destRevision, bits & 2);
    writeVector3Delta(scale, dest, destRevision, bits & 4);
    writeComponentRefDelta(parentRef, dest, destRevision, bits & 8);
    writeUByteDelta((unsigned char)mMode, dest, destRevision, bits & 16);
    writeFloatDelta(mMass, dest, destRevision, bits & 32);
    writeVector3Delta(getLinearVelocity(), dest, destRevision, bits & 64);
    writePackedVector3Delta(getAngularVelocity(), mWorld->getAngularMaxNetVelocity(), dest, destRevision, bits & 128);
    writeStringHashDelta(getResourceHash(mCollisionShape), dest, destRevision, bits2 & 1);
    writeUIntDelta(mCollisionGroup, dest, destRevision, bits2 & 2);
    writeUIntDelta(mCollisionMask, dest, destRevision, bits2 & 2);
    writeFloatDelta(mFriction, dest, destRevision, bits2 & 4);
    writeFloatDelta(mBounce, dest, destRevision, bits2 & 8);
    writeFloatDelta(getLinearRestThreshold(), dest, destRevision, bits2 & 16);
    writeFloatDelta(getLinearDampingThreshold(), dest, destRevision, bits2 & 16);
    writeFloatDelta(getLinearDampingScale(), dest, destRevision, bits2 & 16);
    writeFloatDelta(getAngularRestThreshold(), dest, destRevision, bits2 & 32);
    writeFloatDelta(getAngularDampingThreshold(), dest, destRevision, bits2 & 32);
    writeFloatDelta(getAngularDampingScale(), dest, destRevision, bits2 & 32);
    writeFloatDelta(getAngularMaxVelocity(), dest, destRevision, bits2 & 64);
    
    return (bits | bits2) != 0;
}

void RigidBody::readNetUpdate(Deserializer& source, ResourceCache* cache, const NetUpdateInfo& info)
{
    unsigned char bits = source.readUByte();
    unsigned char bits2 = source.readUByte();
    if (bits & 1)
        setPosition(source.readVector3());
    if (bits & 2)
        setRotation(source.readPackedQuaternion());
    if (bits & 4)
        setScale(source.readVector3());
    if (bits & 8)
        mParentRef.readPacked(source);
    if (bits & 16)
        setMode((PhysicsMode)source.readUByte());
    if (bits & 32)
        setMass(source.readFloat());
    if (bits & 64)
        setLinearVelocity(source.readVector3());
    if (bits & 128)
        setAngularVelocity(source.readPackedVector3(mWorld->getAngularMaxNetVelocity()));
    if (bits2 & 1)
        setCollisionShape(cache->getResource<CollisionShape>(source.readStringHash()));
    if (bits2 & 2)
    {
        setCollisionGroup(source.readUInt());
        setCollisionMask(source.readUInt());
    }
    if (bits2 & 4)
        mFriction = source.readFloat();
    if (bits2 & 8)
        mBounce = source.readFloat();
    if (bits2 & 16)
    {
        setLinearRestThreshold(source.readFloat());
        float threshold = source.readFloat();
        float scale = source.readFloat();
        setLinearDamping(threshold, scale);
    }
    if (bits2 & 32)
    {
        setAngularRestThreshold(source.readFloat());
        float threshold = source.readFloat();
        float scale = source.readFloat();
        setAngularDamping(threshold, scale);
    }
    if (bits2 & 64)
        setAngularMaxVelocity(source.readFloat());
    
    resetForces();
    
    if (bits & (1 | 2 | 64 | 128))
    {
        // If the last network update was stationary, forcibly disable the body so it will not start drifting
        bool active = (getLinearVelocity().getLengthFast() > getLinearRestThreshold()) ||
            (getAngularVelocity().getLengthFast() > getAngularRestThreshold());
        
        if (!active)
        {
            setLinearVelocity(Vector3::sZero);
            setAngularVelocity(Vector3::sZero);
            setActive(false);
        }
    }
}

void RigidBody::interpolate(bool snapToEnd)
{
    // Set the current physics position/rotation as the new interpolation target
    Vector3 position = getPhysicsPosition();
    Quaternion rotation = getPhysicsRotation();
    if ((isActive()) || (position != mInterpolationPosition) || (rotation != mInterpolationRotation))
    {
        mInterpolationPosition = position;
        mInterpolationRotation = rotation;
        mInterpolationFlags |= (INTERP_POS | INTERP_ROT);
    }
    
    Node::interpolate(snapToEnd);
}

void RigidBody::setMode(PhysicsMode mode)
{
    mMode = mode;
    
    switch (mMode)
    {
    case PHYS_STATIC:
        removeBody();
        break;
        
    case PHYS_DYNAMIC:
    case PHYS_KINEMATIC:
        createBody();
        break;
    }
}

void RigidBody::setMass(float mass)
{
    // Zero mass causes ODE assert on dynamic body. So rather set it very small
    mMass = max(mass, M_EPSILON);
    updateMass();
}

void RigidBody::setFriction(float friction)
{
    mFriction = max(friction, 0.0f);
}

void RigidBody::setBounce(float bounce)
{
    mBounce = max(bounce, 0.0f);
}

void RigidBody::setCollisionShape(CollisionShape* shape)
{
    if (shape == mCollisionShape)
        return;
    
    mCollisionShape = shape;
    updateGeometries();
}

void RigidBody::setCollisionGroup(unsigned group)
{
    mCollisionGroup = group;
    
    for (unsigned i = 0; i < mGeometries.size(); ++i)
        dGeomSetCategoryBits(mGeometries[i], group);
}

void RigidBody::setCollisionMask(unsigned mask)
{
    mCollisionMask = mask;
    
    for (unsigned i = 0; i < mGeometries.size(); ++i)
        dGeomSetCollideBits(mGeometries[i], mask);
}

void RigidBody::setPosition(const Vector3& position)
{
    // For clients all physics motion is smoothed, so do not set transform directly if already have a body
    if ((!isProxy()) || (!mBody))
        Node::setPosition(position);
    
    if (mBody)
    {
        if (getPhysicsPosition() != position)
        {
            setActive(true);
            dBodySetPosition(mBody, position.mX, position.mY, position.mZ);
        }
        mPreviousPosition = position;
    }
    else
    {
        // If no body, must set the geometry transforms manually
        if (mCollisionShape)
            mCollisionShape->setBodyAndTransforms(mGeometries, 0, Node::getPosition(), Node::getRotation(), Node::getScale());
    }
}

void RigidBody::setRotation(const Quaternion& rotation)
{
    // For clients all physics motion is smoothed, so do not set transform directly if already have a body
    if ((!isProxy()) || (!mBody))
        Node::setRotation(rotation);
    
    if (mBody)
    {
        if (getPhysicsRotation() != rotation)
        {
            // As a convention, if the body has angular velocity disabled (player controllers and such)
            // setting the rotation only will not cause activation
            if (getAngularMaxVelocity() > 0.0f)
                setActive(true);
            dBodySetQuaternion(mBody, rotation.getData());
        }
        mPreviousRotation = rotation;
    }
    else
    {
        // If no body, must set the geometry transforms manually
        if (mCollisionShape)
            mCollisionShape->setBodyAndTransforms(mGeometries, 0, Node::getPosition(), Node::getRotation(), Node::getScale());
    }
}

void RigidBody::setScale(float scale)
{
    Vector3 scaleVec(scale, scale, scale);
    if (Node::getScale() == scaleVec)
        return;
    
    Node::setScale(scale);
    updateGeometries();
}

void RigidBody::setScale(const Vector3& scale)
{
    if (Node::getScale() == scale)
        return;
    
    Node::setScale(scale);
    updateGeometries();
}

void RigidBody::setTransform(const Vector3& position, const Quaternion& rotation)
{
    // For clients all physics motion is smoothed, so do not set transform directly if already have a body
    if ((!isProxy()) || (!mBody))
    {
        Node::setPosition(position);
        Node::setRotation(rotation);
    }
    
    if (mBody)
    {
        if ((getPhysicsPosition() != position) || (getPhysicsRotation() != rotation))
        {
            setActive(true);
            dBodySetPosition(mBody, position.mX, position.mY, position.mZ);
            dBodySetQuaternion(mBody, rotation.getData());
        }
        mPreviousPosition = position;
        mPreviousRotation = rotation;
    }
    else
    {
        // If no body, must set the geometry transforms manually
        if (mCollisionShape)
            mCollisionShape->setBodyAndTransforms(mGeometries, 0, Node::getPosition(), Node::getRotation(), Node::getScale());
    }
}

void RigidBody::setTransform(const Vector3& position, const Quaternion& rotation, float scale)
{
    setTransform(position, rotation);
    setScale(scale);
}

void RigidBody::setTransform(const Vector3& position, const Quaternion& rotation, const Vector3& scale)
{
    setTransform(position, rotation);
    setScale(scale);
}

void RigidBody::scale(float scale)
{
    if (scale == 1.0f)
        return;
    
    Node::scale(scale);
    updateGeometries();
}

void RigidBody::scale(const Vector3& scale)
{
    if (scale == Vector3::sUnity)
        return;
    
    Node::scale(scale);
    updateGeometries();
}

void RigidBody::setLinearVelocity(const Vector3& velocity)
{
    if (mBody)
        dBodySetLinearVel(mBody, velocity.mX, velocity.mY, velocity.mZ);
}

void RigidBody::setLinearRestThreshold(float threshold)
{
    if (mBody)
        dBodySetAutoDisableLinearThreshold(mBody, threshold);
}

void RigidBody::setLinearDamping(float threshold, float scale)
{
    if (mBody)
    {
        dBodySetLinearDampingThreshold(mBody, threshold);
        dBodySetLinearDamping(mBody, scale);
    }
}

void RigidBody::setAngularVelocity(const Vector3& velocity)
{
    if (mBody)
        dBodySetAngularVel(mBody, velocity.mX, velocity.mY, velocity.mZ);
}

void RigidBody::setAngularRestThreshold(float threshold)
{
    if (mBody)
        dBodySetAutoDisableAngularThreshold(mBody, threshold);
}

void RigidBody::setAngularDamping(float threshold, float scale)
{
    if (mBody)
    {
        dBodySetAngularDampingThreshold(mBody, threshold);
        dBodySetAngularDamping(mBody, scale);
    }
}

void RigidBody::setAngularMaxVelocity(float velocity)
{
    if (mBody)
        dBodySetMaxAngularSpeed(mBody, velocity);
}

void RigidBody::setActive(bool active)
{
    if (mTempDisabled)
        active = false;
    
    if (mBody)
    {
        if ((active) && (!dBodyIsEnabled(mBody)))
            dBodyEnable(mBody);
        else if ((!active) && (dBodyIsEnabled(mBody)))
            dBodyDisable(mBody);
    }
}

void RigidBody::applyForce(const Vector3& force)
{
    if (force == Vector3::sZero)
        return;
    
    if (mBody)
    {
        setActive(true);
        dBodyAddForce(mBody, force.mX, force.mY, force.mZ);
    }
}

void RigidBody::applyForceAtPosition(const Vector3& force, const Vector3& position)
{
    if (force == Vector3::sZero)
        return;
    
    if (mBody)
    {
        setActive(true);
        dBodyAddForceAtRelPos(mBody, force.mX, force.mY, force.mZ, position.mX, position.mY, position.mZ);
    }
}

void RigidBody::applyTorque(const Vector3& torque)
{
    if (torque == Vector3::sZero)
        return;
    
    if (mBody)
    {
        setActive(true);
        dBodyAddTorque(mBody, torque.mX, torque.mY, torque.mZ);
    }
}

void RigidBody::resetForces()
{
    if (mBody)
    {
        dBodySetForce(mBody, 0.0f, 0.0f, 0.0f);
        dBodySetTorque(mBody, 0.0f, 0.0f, 0.0f);
    }
}

Vector3 RigidBody::getPhysicsPosition() const
{
    if (mBody)
    {
        const dReal* pos = dBodyGetPosition(mBody);
        return Vector3(pos[0], pos[1], pos[2]);
    }
    else return Node::getPosition();
}

Quaternion RigidBody::getPhysicsRotation() const
{
    if (mBody)
    {
        const dReal* quat = dBodyGetQuaternion(mBody);
        return Quaternion(quat[0], quat[1], quat[2], quat[3]);
    }
    else return Node::getRotation();
}

Vector3 RigidBody::getLinearVelocity() const
{
    if (mBody)
    {
        const dReal* vel = dBodyGetLinearVel(mBody);
        return Vector3(vel[0], vel[1], vel[2]);
    }
    else
        return Vector3::sZero;
}


float RigidBody::getLinearRestThreshold() const
{
    if (mBody)
        return dBodyGetAutoDisableLinearThreshold(mBody);
    else
        return 0.0f;
}

float RigidBody::getLinearDampingThreshold() const
{
    if (mBody)
        return dBodyGetLinearDampingThreshold(mBody);
    else
        return 0.0f;
}

float RigidBody::getLinearDampingScale() const
{
    if (mBody)
        return dBodyGetLinearDamping(mBody);
    else
        return 0.0f;
}

Vector3 RigidBody::getAngularVelocity() const
{
    if (mBody)
    {
        const dReal* vel = dBodyGetAngularVel(mBody);
        return Vector3(vel[0], vel[1], vel[2]);
    }
    else
        return Vector3::sZero;
}

float RigidBody::getAngularRestThreshold() const
{
    if (mBody)
        return dBodyGetAutoDisableAngularThreshold(mBody);
    else
        return 0.0f;
}

float RigidBody::getAngularDampingThreshold() const
{
    if (mBody)
        return dBodyGetAngularDampingThreshold(mBody);
    else
        return 0.0f;
}

float RigidBody::getAngularDampingScale() const
{
    if (mBody)
        return dBodyGetAngularDamping(mBody);
    else
        return 0.0f;
}

float RigidBody::getAngularMaxVelocity() const
{
    if (mBody)
        return dBodyGetMaxAngularSpeed(mBody);
    else
        return 0.0f;
}

bool RigidBody::isActive() const
{
    if (mBody)
        return dBodyIsEnabled(mBody) != 0;
    else
        return false;
}

void RigidBody::drawDebugGeometry(DebugRenderer* debug)
{
    Color color;
    if (!isActive())
        color = Color(0.0f, 1.0f, 0.0f);
    
    for (unsigned i = 0; i < mGeometries.size(); ++i)
    {
        dGeomID geom = mGeometries[i];
        
        const dReal* pos = dGeomGetPosition(geom);
        dQuaternion quat;
        dGeomGetQuaternion(geom, quat);
        
        Matrix4x3 transform;
        transform.define(Vector3(pos[0], pos[1], pos[2]), Quaternion(quat[0], quat[1], quat[2], quat[3]), 1.0f);
        
        switch (dGeomGetClass(geom))
        {
        case dSphereClass:
            {
                float radius = dGeomSphereGetRadius(geom);
                
                for (unsigned i = 0; i < 360; i += 45)
                {
                    unsigned j = i + 45;
                    float a = radius * sinf(i * M_DEGTORAD);
                    float b = radius * cosf(i * M_DEGTORAD);
                    float c = radius * sinf(j * M_DEGTORAD);
                    float d = radius * cosf(j * M_DEGTORAD);
                    Vector3 start, end;
                    
                    start = transform * Vector3(a, b, 0.0f);
                    end = transform * Vector3(c, d, 0.0f);
                    debug->addLine(start, end, color);
                    start = transform * Vector3(a, 0.0f, b);
                    end = transform * Vector3(c, 0.0f, d);
                    debug->addLine(start, end, color);
                    start = transform * Vector3(0.0f, a, b);
                    end = transform * Vector3(0.0f, c, d);
                    debug->addLine(start, end, color);
                }
            }
            break;
            
        case dBoxClass:
            {
                dVector3 size;
                dGeomBoxGetLengths(geom, size);
                BoundingBox box(0.5f * Vector3(size[0], size[1], size[2]), 0.5f * Vector3(-size[0], -size[1], -size[2]));
                debug->addBoundingBox(box, transform, color);
            }
            break;
            
        case dCapsuleClass:
            {
                float radius, length;
                
                dGeomCapsuleGetParams(geom, &radius, &length);
                for (unsigned i = 0; i < 360; i += 45)
                {
                    unsigned j = i + 45;
                    
                    float a = radius * sinf(i * M_DEGTORAD);
                    float b = radius * cosf(i * M_DEGTORAD);
                    float c = radius * sinf(j * M_DEGTORAD);
                    float d = radius * cosf(j * M_DEGTORAD);
                    Vector3 start, end;
                    
                    start = transform * Vector3(a, b, 0.5f * length);
                    end = transform * Vector3(c, d, 0.5f * length);
                    debug->addLine(start, end, color);
                    start = transform * Vector3(a, b, -0.5f * length);
                    end = transform * Vector3(c, d, -0.5f * length);
                    debug->addLine(start, end, color);
                    if (!(i & 1))
                    {
                        start = transform * Vector3(a, b, 0.5f * length);
                        end = transform * Vector3(a, b, -0.5f * length);
                        debug->addLine(start, end, color);
                    }
                    if (b > -M_EPSILON)
                    {
                        start = transform * Vector3(a, 0.0f, b + 0.5f * length);
                        end = transform * Vector3(c, 0.0f, d + 0.5f * length);
                        debug->addLine(start, end, color);
                        start = transform * Vector3(0.0f, a, b + 0.5f * length);
                        end = transform * Vector3(0.0f, c, d + 0.5f * length);
                        debug->addLine(start, end, color);
                        start = transform * Vector3(a, 0.0f, -b - 0.5f * length);
                        end = transform * Vector3(c, 0.0f, -d - 0.5f * length);
                        debug->addLine(start, end, color);
                        start = transform * Vector3(0.0f, a, -b - 0.5f * length);
                        end = transform * Vector3(0.0f, c, -d - 0.5f * length);
                        debug->addLine(start, end, color);
                    }
                }
            }
            break;
            
        case dCylinderClass:
            {
                float radius, length;
                
                dGeomCylinderGetParams(geom, &radius, &length);
                for (unsigned i = 0; i < 360; i += 45)
                {
                    unsigned j = i + 45;
                    float a = radius * sinf(i * M_DEGTORAD);
                    float b = radius * cosf(i * M_DEGTORAD);
                    float c = radius * sinf(j * M_DEGTORAD);
                    float d = radius * cosf(j * M_DEGTORAD);
                    Vector3 start, end;
                    
                    start = transform * Vector3(a, b, 0.5f * length);
                    end = transform * Vector3(c, d, 0.5f * length);
                    debug->addLine(start, end, color);
                    start = transform * Vector3(a, b, -0.5f * length);
                    end = transform * Vector3(c, d, -0.5f * length);
                    debug->addLine(start, end, color);
                    start = transform * Vector3(a, b, 0.5f * length);
                    end = transform * Vector3(a, b, -0.5f * length);
                    debug->addLine(start, end, color);
                }
            }
            break;
            
        case dTriMeshClass:
            {
                unsigned numTriangles = dGeomTriMeshGetTriangleCount(geom);
                for (unsigned i = 0; i < numTriangles; ++i)
                {
                    dVector3 v0;
                    dVector3 v1;
                    dVector3 v2;
                    
                    dGeomTriMeshGetTriangle(geom, i, &v0, &v1, &v2);
                    
                    Vector3 a(v0[0], v0[1], v0[2]);
                    Vector3 b(v1[0], v1[1], v1[2]);
                    Vector3 c(v2[0], v2[1], v2[2]);
                    debug->addLine(a, b, color);
                    debug->addLine(b, c, color);
                    debug->addLine(c, a, color);
                }
            }
            break;
            
        case dHeightfieldClass:
            {
                dHeightfieldDataID heightData = dGeomHeightfieldGetHeightfieldData(geom);
                unsigned xPoints = heightData->m_nWidthSamples;
                unsigned zPoints = heightData->m_nDepthSamples;
                float xWidth = heightData->m_fWidth;
                float zWidth = heightData->m_fDepth;
                float xBase = -0.5f * xWidth;
                float zBase = -0.5f * zWidth;
                float xSpacing = xWidth / (xPoints - 1);
                float zSpacing = zWidth / (zPoints - 1);
                float* heights = (float*)heightData->m_pHeightData;
                for (unsigned z = 0; z < zPoints - 1; ++z)
                {
                    for (unsigned x = 0; x < xPoints - 1; ++x)
                    {
                        Vector3 a = transform * Vector3(xBase + x * xSpacing, heights[z * xPoints + x], zBase + z * zSpacing);
                        Vector3 b = transform * Vector3(xBase + (x + 1) * xSpacing, heights[z * xPoints + x + 1], zBase + z * zSpacing);
                        Vector3 c = transform * Vector3(xBase + x * xSpacing, heights[(z + 1) * xPoints + x], zBase + (z + 1) * zSpacing);
                        debug->addLine(a, b, color);
                        debug->addLine(a, c, color);
                    }
                }
                for (unsigned z = 0; z < zPoints - 1; ++z)
                {
                    unsigned x = xPoints - 1;
                    
                    Vector3 a = transform * Vector3(xBase + x * xSpacing, heights[z * xPoints + x], zBase + z * zSpacing);
                    Vector3 b = transform * Vector3(xBase + x * xSpacing, heights[(z + 1) * xPoints + x], zBase + (z + 1) * zSpacing);
                    debug->addLine(a, b, color);
                }
                for (unsigned x = 0; x < xPoints - 1; ++x)
                {
                    unsigned z = zPoints - 1;
                    
                    Vector3 a = transform * Vector3(xBase + x * xSpacing, heights[z * xPoints + x], zBase + z * zSpacing);
                    Vector3 b = transform * Vector3(xBase + (x + 1) * xSpacing, heights[z * xPoints + x + 1], zBase + z * zSpacing);
                    debug->addLine(a, b, color);
                }
            }
            break;
        }
    }
}

void RigidBody::preStep()
{
    if (mTempDisabled)
        return;
    
    // Store the previous position for interpolation
    if (mBody)
    {
        const dReal* pos = dBodyGetPosition(mBody);
        const dReal* quat = dBodyGetQuaternion(mBody);
        mPreviousPosition = Vector3(pos[0], pos[1], pos[2]);
        mPreviousRotation = Quaternion(quat[0], quat[1], quat[2], quat[3]);
    }
}

void RigidBody::postStep(float t)
{
    if (mTempDisabled)
        return;
    
    // If no body (static object), or body is inactive, no rendering interpolation necessary
    // Network proxies also use different kind of rendering interpolation (smoothing)
    if ((isProxy()) || (!mBody) || (!dBodyIsEnabled(mBody)))
        return;
    
    const dReal* pos = dBodyGetPosition(mBody);
    const dReal* quat = dBodyGetQuaternion(mBody);
    Vector3 currentPosition(pos[0], pos[1], pos[2]);
    Quaternion currentRotation(quat[0], quat[1], quat[2], quat[3]);
    
    Node::setPosition(mPreviousPosition.lerp(currentPosition, t));
    Node::setRotation(mPreviousRotation.slerp(currentRotation, t));
}

void RigidBody::createBody()
{
    if (!mBody)
    {
        mBody = dBodyCreate(mWorld->getWorld());
        dBodySetGyroscopicMode(mBody, 0);
        
        // Set the user data pointer
        dBodySetData(mBody, this);
        
        // Set rendering transform as the initial transform
        const Vector3& position = Node::getPosition();
        const Quaternion& rotation = Node::getRotation();
        dBodySetPosition(mBody, position.mX, position.mY, position.mZ);
        dBodySetQuaternion(mBody, rotation.getData());
        mPreviousPosition = position;
        mPreviousRotation = rotation;
        
        // Associate geometries with the body
        if (mCollisionShape)
            mCollisionShape->setBodyAndTransforms(mGeometries, mBody, Node::getPosition(), Node::getRotation(), Node::getScale());
    }
    
    if (mMode == PHYS_KINEMATIC)
        dBodySetKinematic(mBody);
    else
        dBodySetDynamic(mBody);
}

void RigidBody::removeBody()
{
    if (!mBody)
        return;
    
    // Reset geometries' body association and transforms
    if (mCollisionShape)
        mCollisionShape->setBodyAndTransforms(mGeometries, 0, Node::getPosition(), Node::getRotation(), Node::getScale());
    
    if (mBody)
    {
        dBodyDestroy(mBody);
        mBody = 0;
    }
}

void RigidBody::removeGeometries()
{
    for (unsigned i = 0; i < mGeometries.size(); ++i)
        dGeomDestroy(mGeometries[i]);
    
    mGeometries.clear();
    mUniqueGeometryDatas.clear();
    CollisionShape::cleanupCaches();
}

void RigidBody::updateGeometries()
{
    removeGeometries();
    
    if (!mCollisionShape)
        return;
    
    mCollisionShape->createGeometries(mGeometries, mUniqueGeometryDatas, mWorld->getSpace(), Node::getScale());
    mCollisionShape->setBodyAndTransforms(mGeometries, mBody, Node::getPosition(), Node::getRotation(), Node::getScale());
    
    for (unsigned i = 0; i < mGeometries.size(); ++i)
    {
        // Set the user data pointer & collision bits
        dGeomSetData(mGeometries[i], this);
        dGeomSetCategoryBits(mGeometries[i], mCollisionGroup);
        dGeomSetCollideBits(mGeometries[i], mCollisionMask);
        if (mTempDisabled)
            dGeomDisable(mGeometries[i]);
    }
    
    updateMass();
}

void RigidBody::updateMass()
{
    if ((!mBody) || (!mCollisionShape) || (mMode != PHYS_DYNAMIC))
        return;
    
    dMass mass;
    dMassSetZero(&mass);
    mCollisionShape->calculateMass(&mass, mGeometries, 1.0f, Node::getScale());
    
    dMassAdjust(&mass, mMass);
    dBodySetMass(mBody, &mass);
}

void RigidBody::setTempDisabled(bool disable)
{
    if (disable == mTempDisabled)
        return;
    
    mTempDisabled = disable;
    if (!mTempDisabled)
    {
        for (unsigned i = 0; i < mGeometries.size(); ++i)
            dGeomEnable(mGeometries[i]);
        
        setActive(mSavedActiveFlag);
        setLinearVelocity(mSavedLinearVelocity);
        setAngularVelocity(mSavedAngularVelocity);
        resetForces();
    }
    else
    {
        for (unsigned i = 0; i < mGeometries.size(); ++i)
            dGeomDisable(mGeometries[i]);
        
        mSavedActiveFlag = isActive();
        mSavedLinearVelocity = getLinearVelocity();
        mSavedAngularVelocity = getAngularVelocity();
        setActive(false);
    }
}
