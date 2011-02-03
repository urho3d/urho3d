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
#include "CustomObject.h"
#include "Geometry.h"
#include "IndexBuffer.h"
#include "Log.h"
#include "Material.h"
#include "OcclusionBuffer.h"
#include "OctreeQuery.h"
#include "Profiler.h"
#include "Renderer.h"
#include "ResourceCache.h"
#include "VertexBuffer.h"
#include "XMLElement.h"

#include <algorithm>
#include <cstring>

#include "DebugNew.h"

static bool compareCustomGeometries(const CustomGeometry& lhs, const CustomGeometry& rhs)
{
    return lhs.mMaterial.getPtr() < rhs.mMaterial.getPtr();
}

float CustomGeometry::getDistance(const Ray& ray) const
{
    if ((!mVertexCount) || (!mIndexCount))
        return M_INFINITY;
    
    return ray.getDistance(mVertexData, mVertexSize, mIndexData, mIndexSize, 0, mIndexCount);
}

CustomObject::CustomObject(Octant* octant, const std::string& name) :
    GeometryNode(NODE_CUSTOMOBJECT, octant, name),
    mVertexElementMask(MASK_POSITION),
    mGeometriesDirty(false),
    mOptimization(true)
{
}

CustomObject::~CustomObject()
{
}

void CustomObject::save(Serializer& dest)
{
    // Write GeometryNode properties
    GeometryNode::save(dest);
    
    // Write CustomObject properties
    dest.writeBool(mOptimization);
    dest.writeUInt(mVertexElementMask);
    dest.writeVLE(mCustomGeometries.size());
    unsigned vertexSize = VertexBuffer::getVertexSize(mVertexElementMask);
    for (unsigned i = 0; i < mCustomGeometries.size(); ++i)
    {
        const CustomGeometry& geometry = mCustomGeometries[i];
        dest.writeStringHash(getResourceHash(geometry.mMaterial));
        
        dest.writeBoundingBox(geometry.mBoundingBox);
        dest.writeVLE(geometry.mVertexCount);
        dest.writeVLE(geometry.mIndexCount);
        dest.writeUByte(geometry.mIndexSize);
        
        unsigned vertexDataSize = geometry.mVertexCount * vertexSize;
        unsigned indexDataSize = geometry.mIndexCount * geometry.mIndexSize;
        if (vertexDataSize)
            dest.write(&geometry.mVertexData[0], vertexDataSize);
        if (indexDataSize)
            dest.write(&geometry.mIndexData[0], indexDataSize);
    }
}

void CustomObject::load(Deserializer& source, ResourceCache* cache)
{
    // Read GeometryNode properties
    GeometryNode::load(source, cache);
    
    // Read CustomObject properties
    mOptimization = source.readBool();
    mVertexElementMask = source.readUInt();
    setNumGeometries(source.readVLE());
    unsigned vertexSize = VertexBuffer::getVertexSize(mVertexElementMask);
    for (unsigned i = 0; i < mCustomGeometries.size(); ++i)
    {
        CustomGeometry& geometry = mCustomGeometries[i];
        geometry.mMaterial = cache->getResource<Material>(source.readStringHash());
        geometry.mBoundingBox = source.readBoundingBox();
        geometry.mVertexCount = source.readVLE();
        geometry.mIndexCount = source.readVLE();
        geometry.mIndexSize = source.readUByte();
        
        unsigned vertexDataSize = geometry.mVertexCount * vertexSize;
        unsigned indexDataSize = geometry.mIndexCount * geometry.mIndexSize;
        geometry.mVertexData = SharedArrayPtr<unsigned char>(new unsigned char[vertexDataSize]);
        geometry.mIndexData = SharedArrayPtr<unsigned char>(new unsigned char[indexDataSize]);
        source.read(&geometry.mVertexData[0], vertexDataSize);
        source.read(&geometry.mIndexData[0], indexDataSize);
    }
}

void CustomObject::saveXML(XMLElement& dest)
{
    // Write GeometryNode properties
    GeometryNode::saveXML(dest);
    
    // Write CustomObject properties
    XMLElement geometriesElem = dest.createChildElement("geometries");
    geometriesElem.setBool("optimization", mOptimization);
    geometriesElem.setInt("elementmask", mVertexElementMask);
    geometriesElem.setInt("count", mCustomGeometries.size());
    
    unsigned vertexSize = VertexBuffer::getVertexSize(mVertexElementMask);
    for (unsigned i = 0; i < mCustomGeometries.size(); ++i)
    {
        XMLElement geometryElem = dest.createChildElement("geometry");
        const CustomGeometry& geometry = mCustomGeometries[i];
        geometryElem.setBoundingBox(geometry.mBoundingBox);
        geometryElem.setString("materialname", getResourceName(geometry.mMaterial));
        geometryElem.setInt("vertexcount", geometry.mVertexCount);
        geometryElem.setInt("indexcount", geometry.mIndexCount);
        geometryElem.setInt("indexsize", geometry.mIndexSize);
        
        unsigned vertexDataSize = geometry.mVertexCount * vertexSize;
        unsigned indexDataSize = geometry.mIndexCount * geometry.mIndexSize;
        if (vertexDataSize)
        {
            XMLElement vertexDataElem = geometryElem.createChildElement("vertexdata");
            vertexDataElem.setBuffer("bytes", &geometry.mVertexData[0], vertexDataSize);
        }
        if (indexDataSize)
        {
            XMLElement indexDataElem = geometryElem.createChildElement("indexdata");
            indexDataElem.setBuffer("bytes", &geometry.mIndexData[0], indexDataSize);
        }
    }
}

void CustomObject::loadXML(const XMLElement& source, ResourceCache* cache)
{
    // Read GeometryNode properties
    GeometryNode::loadXML(source, cache);
    
    // Read CustomObject properties
    XMLElement geometriesElem = source.getChildElement("geometries");
    mOptimization = geometriesElem.getBool("optimization");
    mVertexElementMask = geometriesElem.getInt("elementmask");
    setNumGeometries(geometriesElem.getInt("count"));
    
    unsigned vertexSize = VertexBuffer::getVertexSize(mVertexElementMask);
    XMLElement geometryElem = source.getChildElement("geometry");
    unsigned index = 0;
    while ((geometryElem) && (index < mGeometries.size()))
    {
        CustomGeometry& geometry = mCustomGeometries[index];
        geometry.mBoundingBox = geometryElem.getBoundingBox();
        geometry.mMaterial = cache->getResource<Material>(geometryElem.getString("materialname"));
        geometry.mVertexCount = geometryElem.getInt("vertexcount");
        geometry.mIndexCount = geometryElem.getInt("indexcount");
        geometry.mIndexSize = geometryElem.getInt("indexsize");
        
        unsigned vertexDataSize = geometry.mVertexCount * vertexSize;
        unsigned indexDataSize = geometry.mIndexCount * geometry.mIndexSize;
        geometry.mVertexData = SharedArrayPtr<unsigned char>(new unsigned char[vertexDataSize]);
        geometry.mIndexData = SharedArrayPtr<unsigned char>(new unsigned char[indexDataSize]);
        if (vertexDataSize)
        {
            XMLElement vertexDataElem = geometryElem.getChildElement("vertexdata");
            vertexDataElem.getBuffer("bytes", &geometry.mVertexData[0], vertexDataSize);
        }
        if (indexDataSize)
        {
            XMLElement indexDataElem = geometryElem.getChildElement("indexdata");
            indexDataElem.getBuffer("bytes", &geometry.mIndexData[0], indexDataSize);
        }
        
        geometryElem = geometryElem.getNextElement("geometry");
        ++index;
    }
}

void CustomObject::getResourceRefs(std::vector<Resource*>& dest)
{
    for (unsigned i = 0; i < mCustomGeometries.size(); ++i)
    {
        if (mCustomGeometries[i].mMaterial)
            dest.push_back(mCustomGeometries[i].mMaterial);
    }
}

void CustomObject::processRayQuery(RayOctreeQuery& query, float initialDistance)
{
    PROFILE(CustomObject_Raycast);
    
    RayQueryLevel level = query.mLevel;
    const Matrix4x3& worldTransform = getWorldTransform();
    
    float nearest = M_INFINITY;
    unsigned nearestGeometry = 0;
    
    switch (level)
    {
    case RAY_AABB_NOSUBOBJECTS:
        {
            RayQueryResult result;
            result.mNode = this;
            result.mDistance = initialDistance;
            query.mResult.push_back(result);
            return;
        }
        
    case RAY_AABB:
        for (unsigned i = 0; i < mCustomGeometries.size(); ++i)
        {
            const CustomGeometry& geom = mCustomGeometries[i];
            BoundingBox geometryBox = geom.mBoundingBox.getTransformed(worldTransform);
            float distance = geometryBox.getDistance(query.mRay);
            if ((distance < query.mMaxDistance) && (distance < nearest))
            {
                nearest = distance;
                nearestGeometry = i;
            }
        }
        break;
        
    case RAY_OBB:
        {
            Matrix4x3 inverse = worldTransform.getInverse();
            Ray localRay(inverse * query.mRay.mOrigin, inverse * Vector4(query.mRay.mDirection, 0.0f));
            for (unsigned i = 0; i < mCustomGeometries.size(); ++i)
            {
                const CustomGeometry& geom = mCustomGeometries[i];
                float distance = geom.mBoundingBox.getDistance(localRay);
                if ((distance < query.mMaxDistance) && (distance < nearest))
                {
                    nearest = distance;
                    nearestGeometry = i;
                }
            }
        }
        break;
        
    case RAY_TRIANGLE:
        {
            Matrix4x3 inverse = worldTransform.getInverse();
            Ray localRay(inverse * query.mRay.mOrigin, inverse * Vector4(query.mRay.mDirection, 0.0f));
            for (unsigned i = 0; i < mCustomGeometries.size(); ++i)
            {
                // Do an initial OBB test
                const CustomGeometry& geom = mCustomGeometries[i];
                float distance = geom.mBoundingBox.getDistance(localRay);
                if ((distance < query.mMaxDistance) && (distance < nearest))
                {
                    // Then a triangle-level test
                    distance = geom.getDistance(localRay);
                    if ((distance < query.mMaxDistance) && (distance < nearest))
                    {
                        nearest = distance;
                        nearestGeometry = i;
                    }
                }
            }
        }
        break;
    }
    
    // Return the nearest hit against a geometry
    if (nearest < M_INFINITY)
    {
        RayQueryResult result;
        result.mNode = this;
        result.mDistance = nearest;
        result.mSubObject = nearestGeometry;
        query.mResult.push_back(result);
    }
}

void CustomObject::updateGeometry(const FrameInfo& frame, Renderer* renderer)
{
    if (mGeometriesDirty)
        updateBuffer(renderer);
}

unsigned CustomObject::getNumBatches()
{
    return mGeometries.size();
}

Geometry* CustomObject::getBatchGeometry(unsigned batchIndex)
{
    return mGeometries[batchIndex];
}

Material* CustomObject::getBatchMaterial(unsigned batchIndex)
{
    return mMaterials[batchIndex];
}

bool CustomObject::drawOcclusion(OcclusionBuffer* buffer)
{
    bool success = true;
    
    for (unsigned i = 0; i < mGeometries.size(); ++i)
    {
        Geometry* geom = mGeometries[i];
        if (!geom)
            continue;
        
        // Check that the material is suitable for occlusion (default material always is)
        // and set culling mode
        Material* mat = mMaterials[i];
        if (mat)
        {
            if (!mat->getOcclusion())
                continue;
            buffer->setCullMode(mat->getOcclusionCullMode());
        }
        else
            buffer->setCullMode(CULL_CCW);
        
        const unsigned char* vertexData;
        unsigned vertexSize;
        const unsigned char* indexData;
        unsigned indexSize;
        
        geom->lockRawData(vertexData, vertexSize, indexData, indexSize);
        // Check for valid geometry data
        if ((!vertexData) || (!indexData))
            continue;
        
        unsigned indexStart = geom->getIndexStart();
        unsigned indexCount = geom->getIndexCount();
        
        // Draw and check for running out of triangles
        if (!buffer->draw(getWorldTransform(), vertexData, vertexSize, indexData, indexSize, indexStart, indexCount))
            success = false;
        
        geom->unlockRawData();
        
        if (!success)
            break;
    }
    
    return success;
}

bool CustomObject::setVertexElementMask(unsigned mask)
{
    if (!(mask & MASK_POSITION))
    {
        LOGERROR("Custom object vertex data must contain positions");
        return false;
    }
    
    if (mask == mVertexElementMask)
        return true;
    
    mVertexElementMask = mask;
    
    // If geometries exist, clear their contents, but retain the amount
    unsigned numGeometries = mCustomGeometries.size();
    if (numGeometries)
    {
        mCustomGeometries.clear();
        mCustomGeometries.resize(numGeometries);
        mGeometriesDirty = true;
    }
    
    return true;
}

void CustomObject::setNumGeometries(unsigned num)
{
    if (num != mCustomGeometries.size())
    {
        mCustomGeometries.resize(num);
        mGeometriesDirty = true;
    }
}

bool CustomObject::setGeometryData(unsigned index, const void* vertexData, unsigned vertexCount, const void* indexData, unsigned indexCount, bool largeIndices)
{
    if (index >= mCustomGeometries.size())
    {
        LOGERROR("Illegal geometry index");
        return false;
    }
    
    CustomGeometry& geom = mCustomGeometries[index];
    geom.mVertexSize = VertexBuffer::getVertexSize(mVertexElementMask);
    
    if (vertexCount)
    {
        geom.mVertexData = new unsigned char[vertexCount * mVertexElementMask];
        geom.mVertexCount = vertexCount;
        memcpy(&geom.mVertexData[0], vertexData, vertexCount * geom.mVertexSize);
        
        geom.mBoundingBox.mDefined = false;
        for (unsigned i = 0; i < vertexCount; ++i)
        {
            Vector3 point((float*)&geom.mVertexData[i * geom.mVertexSize]);
            geom.mBoundingBox.merge(point);
        }
    }
    else
    {
        geom.mVertexData.reset();
        geom.mVertexCount = 0;
    }
    
    geom.mIndexSize = largeIndices ? sizeof(unsigned) : sizeof(unsigned short);
    geom.mIndexCount = indexCount;
    if (indexCount)
    {
        geom.mIndexData = new unsigned char[geom.mIndexCount * geom.mIndexSize];
        memcpy(&geom.mIndexData[0], indexData, geom.mIndexCount * geom.mIndexSize);
    }
    else
        geom.mIndexData.reset();
    
    calculateBoundingBox();
    mGeometriesDirty = true;
    return true;
}

void CustomObject::setMaterial(Material* material)
{
    for (unsigned i = 0; i < mCustomGeometries.size(); ++i)
        setMaterial(i, material);
}

bool CustomObject::setMaterial(unsigned index, Material* material)
{
    if (index >= mCustomGeometries.size())
    {
        LOGERROR("Illegal material index");
        return false;
    }
    
    mCustomGeometries[index].mMaterial = material;
    
    if ((!mOptimization) && (!mGeometriesDirty) && (mMaterials.size() == mCustomGeometries.size()))
        mMaterials[index] = material;
    else
        mGeometriesDirty = true;
    
    return true;
}

void CustomObject::setOptimization(bool enable)
{
    if (enable != mOptimization)
    {
        mOptimization = enable;
        mGeometriesDirty = true;
    }
}

const CustomGeometry* CustomObject::getGeometry(unsigned index) const
{
    if (index >= mCustomGeometries.size())
        return 0;
    
    return &mCustomGeometries[index];
}

Material* CustomObject::getMaterial(unsigned index) const
{
    if (index >= mCustomGeometries.size())
        return 0;
    
    return mCustomGeometries[index].mMaterial;
}

void CustomObject::onWorldBoundingBoxUpdate(BoundingBox& worldBoundingBox)
{
    worldBoundingBox = mBoundingBox.getTransformed(getWorldTransform());
}

void CustomObject::calculateBoundingBox()
{
    mBoundingBox.mMin = Vector3::sZero;
    mBoundingBox.mMax = Vector3::sZero;
    mBoundingBox.mDefined = false;
    
    for (unsigned i = 0; i < mCustomGeometries.size(); ++i)
    {
        const CustomGeometry& geom = mCustomGeometries[i];
        if ((geom.mVertexCount) && (geom.mIndexCount))
            mBoundingBox.merge(geom.mBoundingBox);
    }
    
    VolumeNode::onMarkedDirty();
}

void CustomObject::updateBuffer(Renderer* renderer)
{
    PROFILE(CustomObject_UpdateBuffer);
    
    if (!mVertexBuffer)
        mVertexBuffer = new VertexBuffer(renderer);
    if (!mIndexBuffer)
        mIndexBuffer = new IndexBuffer(renderer);
    
    unsigned totalVertexCount = 0;
    unsigned totalIndexCount = 0;
    mGeometries.clear();
    mMaterials.clear();
    
    std::vector<CustomGeometry>* customGeometries;
    static std::vector<CustomGeometry> sortedGeometries;
    
    if (mOptimization)
    {
        // For optimization to work, sort batches per material first
        sortedGeometries.resize(mCustomGeometries.size());
        sortedGeometries = mCustomGeometries;
        std::sort(sortedGeometries.begin(), sortedGeometries.end(), compareCustomGeometries);
        customGeometries = &sortedGeometries;
    }
    else
        customGeometries = &mCustomGeometries;
    
    for (unsigned i = 0; i < customGeometries->size(); ++i)
    {
        const CustomGeometry& src = (*customGeometries)[i];
        
        if ((!src.mVertexCount) || (!src.mIndexCount))
            continue;
        
        totalVertexCount += src.mVertexCount;
        totalIndexCount += src.mIndexCount;
    }
    
    // Use 16-bit indices if possible
    unsigned indexSize = totalVertexCount >= 65536 ? sizeof(unsigned) : sizeof(short);
    unsigned vertexCount = 0;
    unsigned indexCount = 0;
    
    mVertexBuffer->setSize(totalVertexCount, mVertexElementMask);
    mIndexBuffer->setSize(totalIndexCount, indexSize);
    
    unsigned char* vertexData = (unsigned char*)mVertexBuffer->lock(0, totalVertexCount, LOCK_NORMAL);
    unsigned char* indexData = (unsigned char*)mIndexBuffer->lock(0, totalIndexCount, LOCK_NORMAL);
    
    for (unsigned i = 0; i < customGeometries->size(); ++i)
    {
        const CustomGeometry& src = (*customGeometries)[i];
        
        if ((!src.mVertexCount) || (!src.mIndexCount))
            continue;
        
        SharedPtr<Geometry> dest;
        // If not optimized, build a new geometry for each batch
        // Otherwise check if the material is same, and expand the draw range in that case
        bool newGeometry = true;
        if ((mOptimization) && (mGeometries.size()) && (mMaterials.back() == src.mMaterial))
            newGeometry = false;
        
        if (newGeometry)
        {
            dest = new Geometry();
            dest->setIndexBuffer(mIndexBuffer);
            dest->setVertexBuffer(0, mVertexBuffer);
            dest->setDrawRange(TRIANGLE_LIST, indexCount, src.mIndexCount, vertexCount, src.mVertexCount);
            
            mGeometries.push_back(dest);
            mMaterials.push_back(src.mMaterial);
        }
        else
        {
            dest = mGeometries.back();
            dest->setDrawRange(TRIANGLE_LIST, dest->getIndexStart(), dest->getIndexCount() + src.mIndexCount,
                dest->getVertexStart(), dest->getVertexCount() + src.mVertexCount);
        }
        
        memcpy(&vertexData[vertexCount * src.mVertexSize], &src.mVertexData[0], src.mVertexCount * src.mVertexSize);
        
        if (src.mIndexSize == sizeof(unsigned))
        {
            unsigned* srcIndices = (unsigned*)&src.mIndexData[0];
            if (indexSize == sizeof(unsigned))
            {
                unsigned* destIndices = (unsigned*)&indexData[indexCount * indexSize];
                for (unsigned j = 0; j < src.mIndexCount; ++j)
                {
                    *destIndices = *srcIndices + vertexCount;
                    ++srcIndices;
                    ++destIndices;
                }
            }
            else
            {
                unsigned short* destIndices = (unsigned short*)&indexData[indexCount * indexSize];
                for (unsigned j = 0; j < src.mIndexCount; ++j)
                {
                    *destIndices = *srcIndices + vertexCount;
                    ++srcIndices;
                    ++destIndices;
                }
            }
        }
        else
        {
            unsigned short* srcIndices = (unsigned short*)&src.mIndexData[0];
            if (indexSize == sizeof(unsigned))
            {
                unsigned* destIndices = (unsigned*)&indexData[indexCount * indexSize];
                for (unsigned j = 0; j < src.mIndexCount; ++j)
                {
                    *destIndices = *srcIndices + vertexCount;
                    ++srcIndices;
                    ++destIndices;
                }
            }
            else
            {
                unsigned short* destIndices = (unsigned short*)&indexData[indexCount * indexSize];
                for (unsigned j = 0; j < src.mIndexCount; ++j)
                {
                    *destIndices = *srcIndices + vertexCount;
                    ++srcIndices;
                    ++destIndices;
                }
            }
        }
        
        vertexCount += src.mVertexCount;
        indexCount += src.mIndexCount;
    }
    
    mVertexBuffer->unlock();
    mIndexBuffer->unlock();
    mGeometriesDirty = false;
}
