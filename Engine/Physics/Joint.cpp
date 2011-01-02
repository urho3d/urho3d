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
#include "Joint.h"
#include "Log.h"
#include "PhysicsWorld.h"
#include "ReplicationUtils.h"
#include "RigidBody.h"
#include "Scene.h"
#include "StringUtils.h"

#include <ode/ode.h>

#include "DebugNew.h"

static const std::string typeNames[] =
{
    "none",
    "ball",
    "hinge",
};

Joint::Joint(PhysicsWorld* world, const std::string& name) :
    Component(name),
    mWorld(world),
    mType(JOINT_NONE),
    mJoint(0),
    mNetDirty(false)
{
    if (!mWorld)
        EXCEPTION("Null physics world");
}

Joint::~Joint()
{
    reset();
}

void Joint::save(Serializer& dest)
{
    // Write Component properties
    Component::save(dest);
    
    // Write Joint properties
    dest.writeUByte((unsigned char)mType);
    
    ComponentRef bodyARef(mBodyA);
    ComponentRef bodyBRef(mBodyB);
    bodyARef.write(dest);
    bodyBRef.write(dest);
    
    switch (mType)
    {
    case JOINT_BALL:
        dest.writeVector3(getPosition());
        break;
        
    case JOINT_HINGE:
        dest.writeVector3(getPosition());
        dest.writeVector3(getAxis());
        break;
    }
}

void Joint::load(Deserializer& source, ResourceCache* cache)
{
    // Read Component properties
    Component::load(source, cache);
    
    // Read Joint properties
    mType = (JointType)source.readUByte();
    mBodyARef.read(source);
    mBodyBRef.read(source);
    
    switch (mType)
    {
    case JOINT_BALL:
        mPosition = source.readVector3();
        break;
        
    case JOINT_HINGE:
        mPosition = source.readVector3();
        mAxis = source.readVector3();
        break;
    }
}

void Joint::saveXML(XMLElement& dest)
{
    // Write Component properties
    Component::saveXML(dest);
    
    // Write Joint properties
    XMLElement jointElem = dest.createChildElement("joint");
    jointElem.setString("type", typeNames[mType]);
    
    XMLElement bodyAElem = dest.createChildElement("body_a");
    XMLElement bodyBElem = dest.createChildElement("body_b");
    ComponentRef bodyARef(mBodyA, true);
    ComponentRef bodyBRef(mBodyB, true);
    bodyARef.writeXML(bodyAElem);
    bodyBRef.writeXML(bodyBElem);
    
    switch (mType)
    {
    case JOINT_BALL:
        jointElem.setVector3("pos", getPosition());
        break;
        
    case JOINT_HINGE:
        jointElem.setVector3("pos", getPosition());
        jointElem.setVector3("axis", getAxis());
        break;
    }
}

void Joint::loadXML(const XMLElement& source, ResourceCache* cache)
{
    // Read Component properties
    Component::loadXML(source, cache);
    
    // Read Joint properties
    XMLElement jointElem = source.getChildElement("joint");
    XMLElement bodyAElem = source.getChildElement("body_a");
    XMLElement bodyBElem = source.getChildElement("body_b");
    
    mType = (JointType)getIndexFromStringList(jointElem.getStringLower("type"), typeNames, 3, 0);
    mBodyARef.readXML(bodyAElem);
    mBodyBRef.readXML(bodyBElem);
    
    switch (mType)
    {
    case JOINT_BALL:
        mPosition = jointElem.getVector3("pos");
        break;
        
    case JOINT_HINGE:
        mPosition = jointElem.getVector3("pos");
        mAxis = jointElem.getVector3("axis");
        break;
    }
}

void Joint::postLoad(ResourceCache* cache)
{
    RigidBody* bodyA = static_cast<RigidBody*>(mEntity->getScene()->getComponent(mBodyARef));
    RigidBody* bodyB = static_cast<RigidBody*>(mEntity->getScene()->getComponent(mBodyBRef));
    
    switch (mType)
    {
    case JOINT_BALL:
        if (!setBall(mPosition, bodyA, bodyB))
            mType = JOINT_NONE;
        break;
        
    case JOINT_HINGE:
        if (!setHinge(mPosition, mAxis, bodyA, bodyB))
            mType = JOINT_NONE;
        break;
    }
}

bool Joint::writeNetUpdate(Serializer& dest, Serializer& destRevision, Deserializer& baseRevision, const NetUpdateInfo& info)
{
    unsigned char bits = 0;
    
    ComponentRef bodyARef(mBodyA);
    ComponentRef bodyBRef(mBodyB);
    JointType type = mType;
    
    checkUByte((unsigned char)type, (unsigned char)JOINT_NONE, baseRevision, bits, 1);
    checkComponentRef(bodyARef, ComponentRef(), baseRevision, bits, 2);
    checkComponentRef(bodyBRef, ComponentRef(), baseRevision, bits, 2);
    
    switch (type)
    {
    case JOINT_BALL:
        checkVector3(getPosition(), baseRevision, bits, 4);
        // If whole joint will be recreated, also send position
        if (bits & 3)
            bits |= 4;
        break;
        
    case JOINT_HINGE:
        checkVector3(getPosition(), baseRevision, bits, 4);
        checkVector3(getAxis(), baseRevision, bits, 8);
        // If whole joint will be recreated, also send position and axis
        if (bits & 3)
            bits |= 12;
        break;
    }
    
    // Update replication state fully, and network stream by delta
    dest.writeUByte(bits);
    writeUByteDelta((unsigned char)type, dest, destRevision, bits & 1);
    writeComponentRefDelta(bodyARef, dest, destRevision, bits & 2);
    writeComponentRefDelta(bodyBRef, dest, destRevision, bits & 2);
    writeVector3Delta(getPosition(), dest, destRevision, bits & 4);
    writeVector3Delta(getAxis(), dest, destRevision, bits & 8);
    
    return bits != 0;
}

void Joint::readNetUpdate(Deserializer& source, ResourceCache* cache, const NetUpdateInfo& info)
{
    unsigned char bits = source.readUByte();
    if (bits & 1)
        mType = (JointType)source.readUByte();
    if (bits & 2)
    {
        mBodyARef.readPacked(source);
        mBodyBRef.readPacked(source);
    }
    if (bits & 4)
        mPosition = source.readVector3();
    if (bits & 8)
        mAxis = source.readVector3();
    
    // If joint type or body refs changed, recreate whole joint
    if (bits & 3)
        mNetDirty = true;
    else
    {
        // Otherwise just reset the position or axis as applicable
        if (bits & 4)
            setPosition(mPosition);
        if (bits & 8)
            setAxis(mAxis);
    }
}

void Joint::postNetUpdate(ResourceCache* cache)
{
    if (mNetDirty)
    {
        postLoad(cache);
        mNetDirty = false;
    }
}

void Joint::getComponentRefs(std::vector<ComponentRef>& dest)
{
    if (mBodyA)
        dest.push_back(ComponentRef(mBodyA));
    if (mBodyB)
        dest.push_back(ComponentRef(mBodyB));
}

void Joint::reset()
{
    if (mJoint)
    {
        dJointDestroy(mJoint);
        mJoint = 0;
    }
    
    mBodyA.reset();
    mBodyB.reset();
    mType = JOINT_NONE;
}

bool Joint::setBall(const Vector3& position, RigidBody* bodyA, RigidBody* bodyB)
{
    reset();
    
    if ((!bodyA) && (!bodyB))
        return false;
    
    mJoint = dJointCreateBall(mWorld->getWorld(), 0);
    dJointSetData(mJoint, this);
    dJointSetBallAnchor(mJoint, position.mX, position.mY, position.mZ);
    dJointAttach(mJoint, bodyA ? bodyA->getBody() : 0, bodyB ? bodyB->getBody() : 0);
    
    mType = JOINT_BALL;
    mBodyA = bodyA;
    mBodyB = bodyB;
    
    return true;
}

bool Joint::setHinge(const Vector3& position, const Vector3& axis, RigidBody* bodyA, RigidBody* bodyB)
{
    reset();
    
    if ((!bodyA) && (!bodyB))
        return false;
    
    Vector3 normalizedAxis = axis.getNormalized();
    
    mJoint = dJointCreateHinge(mWorld->getWorld(), 0);
    dJointSetData(mJoint, this);
    dJointSetHingeAnchor(mJoint, position.mX, position.mY, position.mZ);
    dJointSetHingeAxis(mJoint, normalizedAxis.mX, normalizedAxis.mY, normalizedAxis.mZ);
    dJointAttach(mJoint, bodyA ? bodyA->getBody() : 0, bodyB ? bodyB->getBody() : 0);
    
    mType = JOINT_HINGE;
    mBodyA = bodyA;
    mBodyB = bodyB;
    
    return true;
}

void Joint::setPosition(const Vector3& position)
{
    switch (mType)
    {
    case JOINT_BALL:
        dJointSetBallAnchor(mJoint, position.mX, position.mY, position.mZ);
        break;
        
    case JOINT_HINGE:
        dJointSetHingeAnchor(mJoint, position.mX, position.mY, position.mZ);
        break;
    }
}

void Joint::setAxis(const Vector3& axis)
{
    switch (mType)
    {
    case JOINT_HINGE:
        dJointSetHingeAxis(mJoint, axis.mX, axis.mY, axis.mZ);
        break;
    }
}

Vector3 Joint::getPosition() const
{
    dVector3 pos;
    
    switch (mType)
    {
    case JOINT_BALL:
        dJointGetBallAnchor(mJoint, pos);
        return Vector3(pos[0], pos[1], pos[2]);
        
    case JOINT_HINGE:
        dJointGetHingeAnchor(mJoint, pos);
        return Vector3(pos[0], pos[1], pos[2]);
    }
    
    return Vector3::sZero;
}

Vector3 Joint::getAxis() const
{
    dVector3 axis;
    
    switch (mType)
    {
    case JOINT_HINGE:
        dJointGetHingeAxis(mJoint, axis);
        return Vector3(axis[0], axis[1], axis[2]);
    }
    
    return Vector3::sZero;
}

