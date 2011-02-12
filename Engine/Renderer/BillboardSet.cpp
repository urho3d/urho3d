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
#include "BillboardSet.h"
#include "Camera.h"
#include "Geometry.h"
#include "IndexBuffer.h"
#include "Material.h"
#include "Profiler.h"
#include "Renderer.h"
#include "RendererImpl.h"
#include "ReplicationUtils.h"
#include "ResourceCache.h"
#include "VertexBuffer.h"
#include "XMLElement.h"

#include <algorithm>

#include "DebugNew.h"

std::vector<float> sortDistances;

static bool compareBillboards(unsigned lhs, unsigned rhs)
{
    return sortDistances[lhs] > sortDistances[rhs];
}

BillboardSet::BillboardSet(Octant* octant, const std::string& name) :
    GeometryNode(NODE_BILLBOARDSET, octant, name),
    mAnimationLodBias(1.0f),
    mAnimationLodTimer(0.0f),
    mBillboardsRelative(true),
    mBillboardsSorted(false),
    mScaleBillboards(true),
    mBufferSizeDirty(true),
    mBufferDirty(true),
    mForceUpdate(false),
    mPreviousOffset(Vector3::sZero),
    mSortFrameNumber(M_MAX_UNSIGNED)
{
    mGeometry = new Geometry();
}

BillboardSet::~BillboardSet()
{
}

void BillboardSet::save(Serializer& dest)
{
    // Write GeometryNode properties
    GeometryNode::save(dest);
    
    // Write BillboardSet properties
    dest.writeStringHash(getResourceHash(mMaterial));
    
    dest.writeFloat(mAnimationLodBias);
    dest.writeBool(mBillboardsRelative);
    dest.writeBool(mBillboardsSorted);
    dest.writeBool(mScaleBillboards);
    dest.writeVLE(mBillboards.size());
    for (unsigned i = 0; i < mBillboards.size(); ++i)
    {
        const Billboard& billboard = mBillboards[i];
        dest.writeBool(billboard.mEnabled);
        // Optimization: write only enabled billboards
        if (billboard.mEnabled)
        {
            dest.writeVector3(billboard.mPosition);
            dest.writeVector2(billboard.mSize);
            dest.writeRect(billboard.mUV);
            dest.writeColor(billboard.mColor);
            dest.writeFloat(billboard.mRotation);
        }
    }
}

void BillboardSet::load(Deserializer& source, ResourceCache* cache)
{
    // Read GeometryNode properties
    GeometryNode::load(source, cache);
    
    // Read BillboardSet properties
    mMaterial = cache->getResource<Material>(source.readStringHash());
    
    mAnimationLodBias = source.readFloat();
    mBillboardsRelative = source.readBool();
    mBillboardsSorted = source.readBool();
    mScaleBillboards = source.readBool();
    setNumBillboards(source.readVLE());
    for (unsigned i = 0; i < mBillboards.size(); ++i)
    {
        Billboard& billboard = mBillboards[i];
        billboard.mEnabled = source.readBool();
        if (billboard.mEnabled)
        {
            billboard.mPosition = source.readVector3();
            billboard.mSize = source.readVector2();
            billboard.mUV = source.readRect();
            billboard.mColor = source.readColor();
            billboard.mRotation = source.readFloat();
        }
        else
        {
            billboard.mPosition = Vector3::sZero;
            billboard.mSize = Vector2::sZero;
            billboard.mUV = Rect::sPositiveRect;
            billboard.mColor = Color();
            billboard.mRotation = 0.0f;
        }
    }
    
    markPositionsDirty();
}

void BillboardSet::saveXML(XMLElement& dest)
{
    // Write GeometryNode properties
    GeometryNode::saveXML(dest);
    
    // Write BillboardSet properties
    XMLElement billboardsElem = dest.createChildElement("billboards");
    billboardsElem.setString("materialname", getResourceName(mMaterial));
    billboardsElem.setBool("relative", mBillboardsRelative);
    billboardsElem.setBool("sort", mBillboardsSorted);
    billboardsElem.setBool("scale", mScaleBillboards);
    billboardsElem.setInt("count", mBillboards.size());
    
    XMLElement lodElem = dest.getChildElement("lod");
    lodElem.setFloat("animlodbias", mAnimationLodBias);
    
    for (unsigned i = 0; i < mBillboards.size(); ++i)
    {
        XMLElement billboardElem = dest.createChildElement("billboard");
        const Billboard& billboard = mBillboards[i];
        
        // Optimization: write only enabled billboards
        if (billboard.mEnabled)
        {
            billboardElem.setVector3("pos", billboard.mPosition);
            billboardElem.setVector2("size", billboard.mSize);
            billboardElem.setRect("uv", billboard.mUV);
            billboardElem.setColor("color", billboard.mColor);
            billboardElem.setFloat("rot", billboard.mRotation);
        }
    }
}

void BillboardSet::loadXML(const XMLElement& source, ResourceCache* cache)
{
    // Read GeometryNode properties
    GeometryNode::loadXML(source, cache);
    
    // Read BillboardSet properties
    XMLElement billboardsElem = source.getChildElement("billboards");
    mMaterial = cache->getResource<Material>(billboardsElem.getString("materialname"));
    mBillboardsRelative = billboardsElem.getBool("relative");
    mBillboardsSorted = billboardsElem.getBool("sort");
    mScaleBillboards = billboardsElem.getBool("scale");
    setNumBillboards(billboardsElem.getInt("count"));
    
    XMLElement lodElem = source.getChildElement("lod");
    mAnimationLodBias = lodElem.getFloat("animlodbias");
    
    XMLElement billboardElem = source.getChildElement("billboard");
    unsigned index = 0;
    while ((billboardElem) && (index < mBillboards.size()))
    {
        Billboard& billboard = mBillboards[index];
        billboard.mEnabled = billboardElem.hasAttribute("pos");
        if (billboard.mEnabled)
        {
            billboard.mPosition = billboardElem.getVector3("pos");
            billboard.mSize = billboardElem.getVector2("size");
            billboard.mUV = billboardElem.getRect("uv");
            billboard.mColor = billboardElem.getColor("color");
            billboard.mRotation = billboardElem.getFloat("rot");
        }
        billboardElem = billboardElem.getNextElement("billboard");
        ++index;
    }
    
    markPositionsDirty();
}

bool BillboardSet::writeNetUpdate(Serializer& dest, Serializer& destRevision, Deserializer& baseRevision, const NetUpdateInfo& info)
{
    // Write GeometryNode properties and see if there were any changes
    bool prevBits = GeometryNode::writeNetUpdate(dest, destRevision, baseRevision, info);
    
    // Build bitmask of changed properties
    unsigned char bits = 0;
    // Note: material is not serialized here. The assumption is that network serialized billboard sets are
    // ParticleEmitters, which have their own description resource
    checkFloat(mAnimationLodBias, baseRevision, bits, 1);
    checkBool(mBillboardsRelative, baseRevision, bits, 2);
    checkBool(mBillboardsSorted, baseRevision, bits, 4);
    checkBool(mScaleBillboards, baseRevision, bits, 8);
    
    // Update replication state fully, and network stream by delta
    dest.writeUByte(bits);
    writeFloatDelta(mAnimationLodBias, dest, destRevision, bits & 1);
    writeBoolDelta(mBillboardsRelative, dest, destRevision, bits & 2);
    writeBoolDelta(mBillboardsSorted, dest, destRevision, bits & 4);
    writeBoolDelta(mScaleBillboards, dest, destRevision, bits & 8);
    
    return prevBits || (bits != 0);
}

void BillboardSet::readNetUpdate(Deserializer& source, ResourceCache* cache, const NetUpdateInfo& info)
{
    // Read GeometryNode properties
    GeometryNode::readNetUpdate(source, cache, info);
    
    unsigned char bits = source.readUByte();
    readFloatDelta(mAnimationLodBias, source, bits & 1);
    readBoolDelta(mBillboardsRelative, source, bits & 2);
    readBoolDelta(mBillboardsSorted, source, bits & 4);
    readBoolDelta(mScaleBillboards, source, bits & 8);
    
    if (bits)
        markPositionsDirty();
}

void BillboardSet::getResourceRefs(std::vector<Resource*>& dest)
{
    if (mMaterial)
        dest.push_back(mMaterial);
}

void BillboardSet::updateDistance(const FrameInfo& frame)
{
    // Check if position relative to camera has changed, and re-sort in that case
    const Vector3& worldPos = getWorldPosition();
    Vector3 offset = (worldPos - frame.mCamera->getWorldPosition());
    if (offset != mPreviousOffset)
    {
        mPreviousOffset = offset;
        if (mBillboardsSorted)
        {
            // Sort billboards only once per frame. This means that secondary views will get
            // the same sorting as the main view
            if (frame.mFrameNumber != mSortFrameNumber)
            {
                mSortFrameNumber = frame.mFrameNumber;
                mBufferDirty = true;
            }
        }
    }
    
    mDistance = frame.mCamera->getDistance(worldPos);
    
    // Calculate scaled distance for animation LOD
    static const Vector3 dotScale(1 / 3.0f, 1 / 3.0f, 1 / 3.0f);
    float scale = getWorldBoundingBox().getSize().dotProduct(dotScale);
    // If there are no billboards, the size becomes zero, and updates no longer happen. Prevent this
    if (scale < M_EPSILON)
        scale = 1.0f;
    mLodDistance = frame.mCamera->getLodDistance(mDistance, scale, mLodBias);
}

void BillboardSet::updateGeometry(const FrameInfo& frame, Renderer* renderer)
{
    if (mBufferSizeDirty)
    {
        updateBufferSize(renderer);
        mForceUpdate = true;
    }
    if (mVertexBuffer->isDataLost())
    {
        mVertexBuffer->clearDataLost();
        mForceUpdate = true;
    }
    
    if ((mBufferDirty) || (mForceUpdate))
        updateVertexBuffer(frame);
}

unsigned BillboardSet::getNumBatches()
{
    return 1;
}

Geometry* BillboardSet::getBatchGeometry(unsigned batchIndex)
{
    return mGeometry;
}

Material* BillboardSet::getBatchMaterial(unsigned batchIndex)
{
    return mMaterial;
}

void BillboardSet::setMaterial(Material* material)
{
    mMaterial = material;
}

void BillboardSet::setNumBillboards(unsigned num)
{
    unsigned oldNum = mBillboards.size();
    
    mBillboards.resize(num);
    mSortOrder.resize(num);
    
    // Set default values to new billboards
    for (unsigned i = oldNum; i < num; ++i)
    {
        mBillboards[i].mPosition = Vector3::sZero;
        mBillboards[i].mSize = Vector2::sUnity;
        mBillboards[i].mUV = Rect::sPositiveRect;
        mBillboards[i].mColor = Color(1.0f, 1.0f, 1.0f);
        mBillboards[i].mRotation = 0.0f;
        mBillboards[i].mEnabled = false;
    }

    // Set default sort order
    for (unsigned i = 0; i < num; ++i)
        mSortOrder[i] = i;
    
    mBufferSizeDirty = true;
    markPositionsDirty();
}

void BillboardSet::setBillboardsRelative(bool enable)
{
    mBillboardsRelative = enable;
    markPositionsDirty();
}

void BillboardSet::setBillboardsSorted(bool enable)
{
    mBillboardsSorted = enable;
    if (!enable)
    {
        // Set default sort order
        for (unsigned i = 0; i < mBillboards.size(); ++i)
            mSortOrder[i] = i;
    }
    
    markPositionsDirty();
}

void BillboardSet::setScaleBillboards(bool enable)
{
    mScaleBillboards = enable;
    markPositionsDirty();
}

void BillboardSet::setAnimationLodBias(float bias)
{
    mAnimationLodBias = max(bias, 0.0f);
}

void BillboardSet::updated()
{
    markPositionsDirty();
}

Billboard* BillboardSet::getBillboard(unsigned index)
{
    if (index >= mBillboards.size())
        return 0;
    
    return &mBillboards[index];
}

void BillboardSet::onMarkedDirty()
{
    VolumeNode::onMarkedDirty();
    
    if (mBillboardsRelative)
        mBufferDirty = true;
}

void BillboardSet::onWorldBoundingBoxUpdate(BoundingBox& worldBoundingBox)
{
    worldBoundingBox.mDefined = false;
    
    unsigned enabledBillboards = 0;
    const Matrix4x3& worldTransform = getWorldTransform();
    const Vector3& worldScale = getWorldScale();
    
    for (unsigned i = 0; i < mBillboards.size(); ++i)
    {
        if (!mBillboards[i].mEnabled)
            continue;
        
        float maxSize;
        if (!mScaleBillboards)
            maxSize = max(mBillboards[i].mSize.mX, mBillboards[i].mSize.mY);
        else
            maxSize = max(mBillboards[i].mSize.mX * worldScale.mX, mBillboards[i].mSize.mY * worldScale.mY);
        
        if (!mBillboardsRelative)
            worldBoundingBox.merge(Sphere(mBillboards[i].mPosition, maxSize));
        else
            worldBoundingBox.merge(Sphere(worldTransform * mBillboards[i].mPosition, maxSize));
        
        ++enabledBillboards;
    }
    
    // If no billboards enabled, the bounding box is just the node's world position
    if (!enabledBillboards)
        worldBoundingBox.merge(getWorldPosition());
}

void BillboardSet::updateBufferSize(Renderer* renderer)
{
    PROFILE(BillboardSet_ResizeBuffer);
    
    if ((!mVertexBuffer) || (!mIndexBuffer))
    {
        mVertexBuffer = new VertexBuffer(renderer, true);
        mIndexBuffer = new IndexBuffer(renderer);
        
        mGeometry->setVertexBuffer(0, mVertexBuffer, MASK_POSITION | MASK_COLOR | MASK_TEXCOORD1 | MASK_TEXCOORD2);
        mGeometry->setIndexBuffer(mIndexBuffer);
    }
    
    unsigned numBillboards = mBillboards.size();
    
    mVertexBuffer->setSize(numBillboards * 4, MASK_POSITION | MASK_COLOR | MASK_TEXCOORD1 | MASK_TEXCOORD2);
    mIndexBuffer->setSize(numBillboards * 6, false);
    
    mBufferSizeDirty = false;
    mBufferDirty = true;
    if (!numBillboards)
        return;
    
    // Indices do not change for a given billboard capacity
    unsigned short* dest = (unsigned short*)mIndexBuffer->lock(0, numBillboards * 6, LOCK_DISCARD);
    unsigned vertexIndex = 0;
    while (numBillboards--)
    {
        *dest++ = vertexIndex; *dest++ = vertexIndex + 1; *dest++ = vertexIndex + 2;
        *dest++ = vertexIndex + 2; *dest++ = vertexIndex + 3; *dest++ = vertexIndex;
        
        vertexIndex += 4;
    }
    mIndexBuffer->unlock();
}

void BillboardSet::updateVertexBuffer(const FrameInfo& frame)
{
    // If using animation LOD, accumulate time and see if it is time to update
    if ((mAnimationLodBias > 0.0f) && (mLodDistance > 0.0f))
    {
        mAnimationLodTimer += mAnimationLodBias * frame.mTimeStep * ANIMATION_LOD_BASESCALE;
        if (mAnimationLodTimer >= mLodDistance)
            mAnimationLodTimer = fmodf(mAnimationLodTimer, mLodDistance);
        else
        {
            // No LOD if immediate update forced
            if (!mForceUpdate)
                return;
        }
    }
    
    PROFILE(BillboardSet_UpdateBuffer);
    
    unsigned numBillboards = mBillboards.size();
    unsigned enabledBillboards = 0;
    const Matrix4x3& worldTransform = getWorldTransform();
    
    if (mBillboardsSorted)
    {
        sortDistances.resize(numBillboards);
        
        for (unsigned i = 0; i < numBillboards; ++i)
        {
            if (mBillboards[i].mEnabled)
            {
                if (!mBillboardsRelative)
                    sortDistances[i] = frame.mCamera->getDistanceSquared(mBillboards[i].mPosition);
                else
                    sortDistances[i] = frame.mCamera->getDistanceSquared(worldTransform * mBillboards[i].mPosition);
                
                enabledBillboards++;
            }
            else
                sortDistances[i] = 0.0f;
        }
        
        std::sort(mSortOrder.begin(), mSortOrder.end(), compareBillboards);
    }
    else
    {
        // If no sorting, do a prepass to find out number of enabled billboards
        for (unsigned i = 0; i < numBillboards; ++i)
        {
            if (mBillboards[i].mEnabled)
                ++enabledBillboards;
        }
    }
    
    // Draw range is now known
    mGeometry->setDrawRange(TRIANGLE_LIST, 0, enabledBillboards * 6, false);

    mBufferDirty = false;
    mForceUpdate = false;
    if (!enabledBillboards)
        return;
    
    float* dest = (float*)mVertexBuffer->lock(0, enabledBillboards * 4, LOCK_DISCARD);
    const Vector3& worldScale = getWorldScale();
    
    for (unsigned i = 0; i < numBillboards; ++i)
    {
        unsigned index = mSortOrder[i];
        const Billboard& billboard = mBillboards[index];
        
        if (!billboard.mEnabled)
            continue;
        
        Vector3 position;
        if (!mBillboardsRelative)
            position = billboard.mPosition;
        else
            position = worldTransform * billboard.mPosition;
        
        Vector2 size;
        if (!mScaleBillboards)
            size = billboard.mSize;
        else
            size = Vector2(billboard.mSize.mX * worldScale.mX, mBillboards[index].mSize.mY * worldScale.mY);
        
        unsigned color = getD3DColor(billboard.mColor);
        
        static float rotationMatrix[2][2];
        float angleRad = billboard.mRotation * M_DEGTORAD;
        rotationMatrix[0][0] = cosf(angleRad);
        rotationMatrix[0][1] = sinf(angleRad);
        rotationMatrix[1][0] = -rotationMatrix[0][1];
        rotationMatrix[1][1] = rotationMatrix[0][0];
        
        *dest++ = position.mX; *dest++ = position.mY; *dest++ = position.mZ;
        *((unsigned*)dest) = color; dest++;
        *dest++ = billboard.mUV.mMin.mX; *dest++ = billboard.mUV.mMax.mY;
        *dest++ = -size.mX * rotationMatrix[0][0] + size.mY * rotationMatrix[0][1];
        *dest++ = -size.mX * rotationMatrix[1][0] + size.mY * rotationMatrix[1][1];
        
        *dest++ = position.mX; *dest++ = position.mY; *dest++ = position.mZ;
        *((unsigned*)dest) = color; dest++;
        *dest++ = billboard.mUV.mMax.mX; *dest++ = billboard.mUV.mMax.mY;
        *dest++ = size.mX * rotationMatrix[0][0] + size.mY * rotationMatrix[0][1];
        *dest++ = size.mX * rotationMatrix[1][0] + size.mY * rotationMatrix[1][1];
        
        *dest++ = position.mX; *dest++ = position.mY; *dest++ = position.mZ;
        *((unsigned*)dest) = color; dest++;
        *dest++ = billboard.mUV.mMax.mX; *dest++ = billboard.mUV.mMin.mY;
        *dest++ = size.mX * rotationMatrix[0][0] - size.mY * rotationMatrix[0][1];
        *dest++ = size.mX * rotationMatrix[1][0] - size.mY * rotationMatrix[1][1];
        
        *dest++ = position.mX; *dest++ = position.mY; *dest++ = position.mZ;
        *((unsigned*)dest) = color; dest++;
        *dest++ = billboard.mUV.mMin.mX; *dest++ = billboard.mUV.mMin.mY;
        *dest++ = -size.mX * rotationMatrix[0][0] - size.mY * rotationMatrix[0][1];
        *dest++ = -size.mX * rotationMatrix[1][0] - size.mY * rotationMatrix[1][1];
    }
    
    mVertexBuffer->unlock();
}

void BillboardSet::markPositionsDirty()
{
    VolumeNode::onMarkedDirty();
    mBufferDirty = true;
}
