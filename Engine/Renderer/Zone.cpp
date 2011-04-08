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
#include "ReplicationUtils.h"
#include "XMLElement.h"
#include "Zone.h"

static const float DEFAULT_FOGSTART = 250.0f;
static const float DEFAULT_FOGEND = 1000.0f;
static const Color DEFAULT_COLOR(0.0f, 0.0f, 0.0f, 0.0f);

Zone::Zone(Octant* octant, const std::string& name) :
    VolumeNode(NODE_ZONE, octant, name),
    mAmbientColor(DEFAULT_COLOR),
    mFogColor(DEFAULT_COLOR),
    mFogStart(DEFAULT_FOGSTART),
    mFogEnd(DEFAULT_FOGEND),
    mPriority(0)
{
}

Zone::~Zone()
{
}

void Zone::save(Serializer& dest)
{
    // Write VolumeNode properties
    VolumeNode::save(dest);
    
    // Write Zone properties
    dest.writeBoundingBox(mBoundingBox);
    dest.writeColor(mAmbientColor);
    dest.writeColor(mFogColor);
    dest.writeFloat(mFogStart);
    dest.writeFloat(mFogEnd);
    dest.writeInt(mPriority);
}

void Zone::load(Deserializer& source, ResourceCache* cache)
{
    // Read VolumeNode properties
    VolumeNode::load(source, cache);
    
    // Read Zone properties
    mBoundingBox = source.readBoundingBox();
    mAmbientColor = source.readColor();
    mFogColor = source.readColor();
    mFogStart = source.readFloat();
    mFogEnd = source.readFloat();
    mPriority = source.readInt();
}

void Zone::saveXML(XMLElement& dest)
{
    // Write VolumeNode properties
    VolumeNode::saveXML(dest);
    
    // Write Zone properties
    XMLElement zoneElement = dest.createChildElement("zone");
    zoneElement.setBoundingBox(mBoundingBox);
    zoneElement.setColor("ambientcolor", mAmbientColor);
    zoneElement.setInt("priority", mPriority);
    
    XMLElement fogElement = dest.createChildElement("fog");
    fogElement.setColor("color", mFogColor);
    fogElement.setFloat("start", mFogStart);
    fogElement.setFloat("end", mFogEnd);
}

void Zone::loadXML(const XMLElement& source, ResourceCache* cache)
{
    // Read VolumeNode properties
    VolumeNode::loadXML(source, cache);
    
    // Read Zone properties
    XMLElement zoneElement = source.getChildElement("zone");
    mBoundingBox = zoneElement.getBoundingBox();
    mAmbientColor = zoneElement.getColor("ambientcolor");
    mPriority = zoneElement.getInt("priority");
    
    XMLElement fogElement = source.getChildElement("fog");
    mFogColor = fogElement.getColor("color");
    mFogStart = fogElement.getFloat("start");
    mFogEnd = fogElement.getFloat("end");
}

bool Zone::writeNetUpdate(Serializer& dest, Serializer& destRevision, Deserializer& baseRevision, const NetUpdateInfo& info)
{
    // Write VolumeNode properties and see if there were any changes
    bool prevBits = VolumeNode::writeNetUpdate(dest, destRevision, baseRevision, info);
    
    // Build bitmask of changed properties
    unsigned char bits = 0;
    checkVector3(mBoundingBox.mMin, baseRevision, bits, 1);
    checkVector3(mBoundingBox.mMax, baseRevision, bits, 1);
    checkColor(mAmbientColor, DEFAULT_COLOR, baseRevision, bits, 2);
    checkColor(mFogColor, DEFAULT_COLOR, baseRevision, bits, 4);
    checkFloat(mFogStart, DEFAULT_FOGSTART, baseRevision, bits, 8);
    checkFloat(mFogEnd, DEFAULT_FOGEND, baseRevision, bits, 8);
    checkInt(mPriority, 0, baseRevision, bits, 16);
    
    // Update replication state fully, and network stream by delta
    dest.writeUByte(bits);
    writeVector3Delta(mBoundingBox.mMin, dest, destRevision, bits & 1);
    writeVector3Delta(mBoundingBox.mMax, dest, destRevision, bits & 1);
    writeColorDelta(mAmbientColor, dest, destRevision, bits & 2);
    writeColorDelta(mFogColor, dest, destRevision, bits & 4);
    writeFloatDelta(mFogStart, dest, destRevision, bits & 8);
    writeFloatDelta(mFogEnd, dest, destRevision, bits & 8);
    writeIntDelta(mPriority, dest, destRevision, bits & 16);
    
    return prevBits || (bits != 0);
}

void Zone::readNetUpdate(Deserializer& source, ResourceCache* cache, const NetUpdateInfo& info)
{
    // Read VolumeNode properties
    VolumeNode::readNetUpdate(source, cache, info);
    
    unsigned char bits = source.readUByte();
    if (bits & 1)
        mBoundingBox = source.readBoundingBox();
    readColorDelta(mAmbientColor, source, bits & 2);
    readColorDelta(mFogColor, source, bits & 4);
    readFloatDelta(mFogStart, source, bits & 8);
    readFloatDelta(mFogEnd, source, bits & 8);
    readIntDelta(mPriority, source, bits & 16);
}

void Zone::setBoundingBox(const BoundingBox& box)
{
    mBoundingBox = box;
    markDirty();
}

void Zone::setAmbientColor(const Color& color)
{
    // Ensure that alpha is zero, because custom rendering may depend on it
    mAmbientColor = Color(color, 0.0f);
}

void Zone::setFogColor(const Color& color)
{
    // Ensure that alpha is zero, because custom rendering may depend on it
    mFogColor = Color(color, 0.0f);
}

void Zone::setFogStart(float start)
{
    if (start < 0.0f)
        start = 0.0f;
    
    mFogStart = start;
}

void Zone::setFogEnd(float end)
{
    if (end < 0.0f)
        end = 0.0f;
    
    mFogEnd = end;
}

void Zone::setPriority(int priority)
{
    mPriority = priority;
}

bool Zone::isInside(const Vector3& point)
{
    // Use an oriented bounding box test
    Matrix4x3 inverse = getWorldTransform().getInverse();
    Vector3 localPoint = inverse * point;
    return mBoundingBox.isInside(localPoint) != OUTSIDE;
}

void Zone::onWorldBoundingBoxUpdate(BoundingBox& worldBoundingBox)
{
    worldBoundingBox = mBoundingBox.getTransformed(getWorldTransform());
}
