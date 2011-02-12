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
#include "Camera.h"
#include "DebugRenderer.h"
#include "Octree.h"
#include "OctreeQuery.h"
#include "ReplicationUtils.h"
#include "XMLElement.h"

#include "DebugNew.h"

VolumeNode::VolumeNode(unsigned flags, Octant* octant, const std::string& name) :
    Node(flags, name),
    mOctant(0),
    mCastShadows(false),
    mOccluder(false),
    mVisible(true),
    mDrawDistance(0.0f),
    mShadowDistance(0.0f),
    mViewMask(VIEW_ALL),
    mLightMask(VIEW_ALL),
    mDistance(0.0f),
    mSortValue(0.0f),
    mViewFrameNumber(M_MAX_UNSIGNED),
    mViewCamera(0),
    mWorldBoundingBoxDirty(true)
{
    // Insert initially into the specified octant; the node does not have correct
    // bounding box size yet, so it will be moved in any case
    if (octant)
    {
        octant->addNode(this);
        octant->getRoot()->markNodeForReinsertion(this);
    }
}

VolumeNode::~VolumeNode()
{
    // If was in octree and is being deleted now, make sure to clear any reference in the update/reinsertion lists
    if (mOctant)
    {
        Octree* octree = mOctant->getRoot();
        octree->clearNodeUpdate(this);
        octree->clearNodeReinsertion(this);
        mOctant->removeNode(this);
    }
}

void VolumeNode::save(Serializer& dest)
{
    // Write Node properties
    Node::save(dest);
    
    // Write VolumeNode properties
    dest.writeBool(mCastShadows);
    dest.writeBool(mOccluder);
    dest.writeBool(mVisible);
    dest.writeFloat(mDrawDistance);
    dest.writeFloat(mShadowDistance);
    dest.writeUInt(mViewMask);
    dest.writeUInt(mLightMask);
}

void VolumeNode::load(Deserializer& source, ResourceCache* cache)
{
    // Read Node properties
    Node::load(source, cache);
    
    // Read VolumeNode properties
    mCastShadows = source.readBool();
    mOccluder = source.readBool();
    mVisible = source.readBool();
    mDrawDistance = source.readFloat();
    mShadowDistance = source.readFloat();
    mViewMask = source.readUInt();
    mLightMask = source.readUInt();
}

void VolumeNode::saveXML(XMLElement& dest)
{
    // Write Node properties
    Node::saveXML(dest);
    
    // Write VolumeNode properties
    XMLElement renderElem = dest.createChildElement("render");
    renderElem.setBool("castshadows", mCastShadows);
    renderElem.setBool("occluder", mOccluder);
    renderElem.setBool("visible", mVisible);
    
    XMLElement lodElem = dest.createChildElement("lod");
    lodElem.setFloat("drawdistance", mDrawDistance);
    lodElem.setFloat("shadowdistance", mShadowDistance);
    lodElem.setInt("viewmask", mViewMask);
    lodElem.setInt("lightmask", mLightMask);
}

void VolumeNode::loadXML(const XMLElement& source, ResourceCache* cache)
{
    // Read Node properties
    Node::loadXML(source, cache);
    
    // Read VolumeNode properties
    XMLElement renderElem = source.getChildElement("render");
    mCastShadows = renderElem.getBool("castshadows");
    mOccluder = renderElem.getBool("occluder");
    mVisible = renderElem.getBool("visible");
    
    XMLElement lodElem = source.getChildElement("lod");
    mDrawDistance = lodElem.getFloat("drawdistance");
    mShadowDistance = lodElem.getFloat("shadowdistance");
    mViewMask = lodElem.getInt("viewmask");
    mLightMask = lodElem.getInt("lightmask");
}

bool VolumeNode::writeNetUpdate(Serializer& dest, Serializer& destRevision, Deserializer& baseRevision, const NetUpdateInfo& info)
{
    // Use possibly modified transform in case the parent component is not to be replicated
    Vector3 position;
    Quaternion rotation;
    Vector3 scale;
    ComponentRef parentRef;
    getNetTransform(position, rotation, scale, parentRef, info);
    
    // Build bitmask of changed properties
    unsigned char bits = 0;
    checkVector3(position, Vector3::sZero, baseRevision, bits, 1);
    checkQuaternion(rotation, Quaternion::sIdentity, baseRevision, bits, 2);
    checkVector3(scale, Vector3::sUnity, baseRevision, bits, 4);
    checkComponentRef(parentRef, ComponentRef(), baseRevision, bits, 8);
    checkBool(mCastShadows, false, baseRevision, bits, 16);
    checkBool(mOccluder, false, baseRevision, bits, 16);
    checkBool(mVisible, true, baseRevision, bits, 16);
    checkFloat(mDrawDistance, 0.0f, baseRevision, bits, 32);
    checkFloat(mShadowDistance, 0.0f, baseRevision, bits, 32);
    checkUInt(mViewMask, VIEW_ALL, baseRevision, bits, 64);
    checkUInt(mLightMask, VIEW_ALL, baseRevision, bits, 64);
    
    // Update replication state fully, and network stream by delta
    dest.writeUByte(bits);
    writeVector3Delta(position, dest, destRevision, bits & 1);
    writePackedQuaternionDelta(rotation, dest, destRevision, bits & 2);
    writeVector3Delta(scale, dest, destRevision, bits & 4);
    writeComponentRefDelta(parentRef, dest, destRevision, bits & 8);
    writeBoolDelta(mCastShadows, dest, destRevision, bits & 16);
    writeBoolDelta(mOccluder, dest, destRevision, bits & 16);
    writeBoolDelta(mVisible, dest, destRevision, bits & 16);
    writeFloatDelta(mDrawDistance, dest, destRevision, bits & 32);
    writeFloatDelta(mShadowDistance, dest, destRevision, bits & 32);
    writeUIntDelta(mViewMask, dest, destRevision, bits & 64);
    writeUIntDelta(mLightMask, dest, destRevision, bits & 64);
    
    return bits != 0;
}

void VolumeNode::readNetUpdate(Deserializer& source, ResourceCache* cache, const NetUpdateInfo& info)
{
    unsigned char bits = source.readUByte();
    // Interpolate if just position/rotation/scale changes, snap if parent changes
    bool interpolate = (bits & 7) && (!(bits & 8));
    if (!interpolate)
    {
        if (bits & 1)
            setPosition(source.readVector3());
        if (bits & 2)
            setRotation(source.readPackedQuaternion());
        if (bits & 4)
            setScale(source.readVector3());
    }
    else
    {
        if (bits & 1)
        {
            mInterpolationPosition = source.readVector3();
            mInterpolationFlags |= INTERP_POS;
        }
        if (bits & 2)
        {
            mInterpolationRotation = source.readPackedQuaternion();
            mInterpolationFlags |= INTERP_ROT;
        }
        if (bits & 4)
        {
            mInterpolationScale = source.readVector3();
            mInterpolationFlags |= INTERP_SCALE;
        }
    }
    
    readComponentRefDelta(mParentRef, source, bits & 8);
    readBoolDelta(mCastShadows, source, bits & 16);
    readBoolDelta(mOccluder, source, bits & 16);
    readBoolDelta(mVisible, source, bits & 16);
    readFloatDelta(mDrawDistance, source, bits & 32);
    readFloatDelta(mShadowDistance, source, bits & 32);
    readUIntDelta(mViewMask, source, bits & 64);
    readUIntDelta(mLightMask, source, bits & 64);
}

void VolumeNode::updateNode(const FrameInfo& frame)
{
}

void VolumeNode::updateDistance(const FrameInfo& frame)
{
    mDistance = frame.mCamera->getDistance(getWorldPosition());
}

void VolumeNode::overrideTransforms(unsigned batchIndex, Camera& camera, const Matrix4x3** model, const Matrix4x3** view)
{
}

void VolumeNode::processRayQuery(RayOctreeQuery& query, float initialDistance)
{
    // By default just store the result from the bounding box raycast
    RayQueryResult result;
    result.mNode = this;
    result.mDistance = initialDistance;
    query.mResult.push_back(result);
}

void VolumeNode::drawDebugGeometry(DebugRenderer* debug)
{
    debug->addBoundingBox(getWorldBoundingBox(), Color(0.0f, 1.0f, 0.0f), false);
}

void VolumeNode::setCastShadows(bool enable)
{
    mCastShadows = enable;
}

void VolumeNode::setOccluder(bool enable)
{
    mOccluder = enable;
}

void VolumeNode::setVisible(bool visible)
{
    mVisible = visible;
}

void VolumeNode::setDrawDistance(float distance)
{
    mDrawDistance = max(distance, 0.0f);
}

void VolumeNode::setShadowDistance(float distance)
{
    mShadowDistance = max(distance, 0.0f);
}

void VolumeNode::setViewMask(unsigned mask)
{
    mViewMask = mask;
}

void VolumeNode::setLightMask(unsigned mask)
{
    mLightMask = mask;
}

float VolumeNode::calculateDrawDistance(const Camera& camera, float minScreenSize)
{
    const BoundingBox& box = getWorldBoundingBox();
    float diagonal = (box.mMax - box.mMin).getLengthFast();
    float halfViewSize = camera.getHalfViewSize();
    
    return diagonal * halfViewSize / minScreenSize;
}

const BoundingBox& VolumeNode::getWorldBoundingBox()
{
    if (mWorldBoundingBoxDirty)
    {
        onWorldBoundingBoxUpdate(mWorldBoundingBox);
        mWorldBoundingBoxDirty = false;
    }
    
    return mWorldBoundingBox;
}

void VolumeNode::markInView(const FrameInfo& frame)
{
    mViewFrameNumber = frame.mFrameNumber;
    mViewCamera = frame.mCamera;
}

void VolumeNode::markInShadowView(const FrameInfo& frame)
{
    if (mViewFrameNumber != frame.mFrameNumber)
    {
        mViewFrameNumber = frame.mFrameNumber;
        mViewCamera = 0;
    }
}

void VolumeNode::setSortValue(float value)
{
    mSortValue = value;
}

bool VolumeNode::isInView(unsigned frameNumber) const
{
    return mViewFrameNumber == frameNumber;
}

bool VolumeNode::isInView(const FrameInfo& frame) const
{
    return (mViewFrameNumber == frame.mFrameNumber) && (mViewCamera == frame.mCamera);
}

void VolumeNode::onMarkedDirty()
{
    mWorldBoundingBoxDirty = true;
    
    if (mOctant)
        mOctant->getRoot()->markNodeForReinsertion(this);
}

void VolumeNode::markForUpdate()
{
    if (mOctant)
        mOctant->getRoot()->markNodeForUpdate(this);
}
