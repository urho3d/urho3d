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
#include "Geometry.h"
#include "GeometryNode.h"
#include "Light.h"
#include "ReplicationUtils.h"
#include "XMLElement.h"

#include <algorithm>

#include "DebugNew.h"

GeometryNode::GeometryNode(unsigned flags, Octant* octant, const std::string& name) :
    VolumeNode(flags | NODE_GEOMETRY, octant, name),
    mLodBias(1.0f),
    mLodDistance(0.0f),
    mLodLevelsDirty(true)
{
}

void GeometryNode::save(Serializer& dest)
{
    // Write VolumeNode properties
    VolumeNode::save(dest);
    
    // Write GeometryNode properties
    dest.writeFloat(mLodBias);
}

void GeometryNode::load(Deserializer& source, ResourceCache* cache)
{
    // Read VolumeNode properties
    VolumeNode::load(source, cache);
    
    // Read GeometryNode properties
    mLodBias = source.readFloat();
}

void GeometryNode::saveXML(XMLElement& dest)
{
    // Write VolumeNode properties
    VolumeNode::saveXML(dest);
    
    // Write GeometryNode properties
    XMLElement lodElem = dest.getChildElement("lod");
    lodElem.setFloat("lodbias", mLodBias);
}

void GeometryNode::loadXML(const XMLElement& source, ResourceCache* cache)
{
    // Read VolumeNode properties
    VolumeNode::loadXML(source, cache);
    
    // Read GeometryNode properties
    XMLElement lodElem = source.getChildElement("lod");
    mLodBias = lodElem.getFloat("lodbias");
}

bool GeometryNode::writeNetUpdate(Serializer& dest, Serializer& destRevision, Deserializer& baseRevision, const NetUpdateInfo& info)
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
    checkFloat(mLodBias, 1.0f, baseRevision, bits, 128);
    
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
    writeFloatDelta(mLodBias, dest, destRevision, bits & 128);
    
    return bits != 0;
}

void GeometryNode::readNetUpdate(Deserializer& source, ResourceCache* cache, const NetUpdateInfo& info)
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
    readFloatDelta(mLodBias, source, bits & 128);
}

void GeometryNode::updateDistance(const FrameInfo& frame)
{
    mDistance = frame.mCamera->getDistance(getWorldPosition());
    
    static const Vector3 dotScale(1 / 3.0f, 1 / 3.0f, 1 / 3.0f);
    float scale = getWorldScale().dotProduct(dotScale);
    float newLodDistance = frame.mCamera->getLodDistance(mDistance, scale, mLodBias);
    
    if (newLodDistance != mLodDistance)
    {
        mLodDistance = newLodDistance;
        mLodLevelsDirty = true;
    }
}

bool GeometryNode::getVertexShaderParameter(unsigned batchIndex, VSParameter parameter, const float** data, unsigned* count)
{
    return false;
}

bool GeometryNode::drawOcclusion(OcclusionBuffer* buffer)
{
    return true;
}

void GeometryNode::setLodBias(float bias)
{
    mLodBias = max(bias, M_EPSILON);
}
