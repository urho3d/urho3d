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
#include "Deserializer.h"
#include "Geometry.h"
#include "IndexBuffer.h"
#include "Log.h"
#include "Model.h"
#include "Profiler.h"
#include "Renderer.h"
#include "Serializer.h"
#include "VertexBuffer.h"

#include <cstring>

#include "DebugNew.h"

unsigned storeOrLookupVertexBuffer(VertexBuffer* buffer, std::vector<VertexBuffer*>& dest)
{
    for (unsigned i = 0; i < dest.size(); ++i)
    {
        if (dest[i] == buffer)
            return i;
    }
    dest.push_back(buffer);
    return dest.size() - 1;
}

unsigned storeOrLookupIndexBuffer(IndexBuffer* buffer, std::vector<IndexBuffer*>& dest)
{
    for (unsigned i = 0; i < dest.size(); ++i)
    {
        if (dest[i] == buffer)
            return i;
    }
    dest.push_back(buffer);
    return dest.size() - 1;
}

Model::Model(Renderer* renderer, const std::string& name) :
    Resource(name),
    mRenderer(renderer),
    mCollisionLodLevel(M_MAX_UNSIGNED),
    mRaycastLodLevel(M_MAX_UNSIGNED),
    mOcclusionLodLevel(M_MAX_UNSIGNED)
{
}

Model::~Model()
{
}

void Model::load(Deserializer& source, ResourceCache* cache)
{
    PROFILE(Model_Load);
    
    mGeometries.clear();
    mGeometryBoneMappings.clear();
    mMorphs.clear();
    mVertexBuffers.clear();
    mIndexBuffers.clear();
    
    setMemoryUse(source.getSize());
    
    // Read vertex buffers
    unsigned numVertexBuffers = source.readUInt();
    for (unsigned i = 0; i < numVertexBuffers; ++i)
    {
        unsigned vertexCount = source.readUInt();
        unsigned elementMask = source.readUInt();
        unsigned morphStart = source.readUInt();
        unsigned morphCount = source.readUInt();
        
        SharedPtr<VertexBuffer> buffer(new VertexBuffer(mRenderer, false));
        buffer->setSize(vertexCount, elementMask);
        buffer->setMorphRange(morphStart, morphCount);
        
        unsigned vertexSize = buffer->getVertexSize();
        
        SharedArrayPtr<unsigned char> data(new unsigned char[vertexCount * vertexSize]);
        source.read(data.getPtr(), vertexCount * buffer->getVertexSize());
        buffer->setData(data.getPtr());
        // If there is a morph range, make a copy of the data so that the morph range can be reset
        if (morphCount)
        {
            SharedArrayPtr<unsigned char> morphResetData(new unsigned char[morphCount * vertexSize]);
            memcpy(morphResetData.getPtr(), &data[morphStart * vertexSize], morphCount * vertexSize);
            buffer->setMorphRangeResetData(morphResetData);
        }
        
        mVertexBuffers.push_back(buffer);
    }
    
    // Read index buffers
    unsigned numIndexBuffers = source.readUInt();
    for (unsigned i = 0; i < numIndexBuffers; ++i)
    {
        unsigned indexCount = source.readUInt();
        unsigned indexSize = source.readUInt();
        
        SharedPtr<IndexBuffer> buffer(new IndexBuffer(mRenderer, false));
        buffer->setSize(indexCount, indexSize);
        SharedArrayPtr<unsigned char> data(new unsigned char[indexCount * indexSize]);
        source.read(data.getPtr(), indexCount * indexSize);
        buffer->setData(data.getPtr());
        
        mIndexBuffers.push_back(buffer);
    }
    
    // Read geometries
    unsigned numGeometries = source.readUInt();
    for (unsigned i = 0; i < numGeometries; ++i)
    {
        // Read bone mappings
        unsigned boneMappingCount = source.readUInt();
        std::vector<unsigned> boneMapping;
        for (unsigned j = 0; j < boneMappingCount; ++j)
            boneMapping.push_back(source.readUInt());
        mGeometryBoneMappings.push_back(boneMapping);
        
        unsigned numLodLevels = source.readUInt();
        std::vector<SharedPtr<Geometry> > geometryLodLevels;
        
        for (unsigned j = 0; j < numLodLevels; ++j)
        {
            float distance = source.readFloat();
            PrimitiveType type = (PrimitiveType)source.readUInt();
        
            unsigned vertexBufferRef = source.readUInt();
            unsigned indexBufferRef = source.readUInt();
            unsigned indexStart = source.readUInt();
            unsigned indexCount = source.readUInt();
            
            if (vertexBufferRef >= mVertexBuffers.size())
                EXCEPTION("Illegal vertex buffer index");
            if (indexBufferRef >= mIndexBuffers.size())
                EXCEPTION("Illegal index buffer index");
            
            SharedPtr<Geometry> geometry(new Geometry());
            geometry->setNumVertexBuffers(1);
            geometry->setVertexBuffer(0, mVertexBuffers[vertexBufferRef]);
            geometry->setIndexBuffer(mIndexBuffers[indexBufferRef]);
            geometry->setDrawRange(type, indexStart, indexCount);
            geometry->setLodDistance(distance);
            
            geometryLodLevels.push_back(geometry);
        }
        
        mGeometries.push_back(geometryLodLevels);
    }
    
    // Read morphs
    unsigned numMorphs = source.readUInt();
    for (unsigned i = 0; i < numMorphs; ++i)
    {
        ModelMorph newMorph;
        
        newMorph.mName = source.readString();
        newMorph.mNameHash = StringHash(newMorph.mName);
        newMorph.mWeight = 0.0f;
        unsigned numBuffers = source.readUInt();
        
        for (unsigned j = 0; j < numBuffers; ++j)
        {
            VertexBufferMorph newBuffer;
            unsigned bufferIndex = source.readUInt();
            
            newBuffer.mElementMask = source.readUInt();
            newBuffer.mVertexCount = source.readUInt();
            
            // Base size: size of each vertex index
            unsigned vertexSize = sizeof(unsigned);
            // Add size of individual elements
            if (newBuffer.mElementMask & MASK_POSITION)
                vertexSize += sizeof(Vector3);
            if (newBuffer.mElementMask & MASK_NORMAL)
                vertexSize += sizeof(Vector3);
            if (newBuffer.mElementMask & MASK_TANGENT)
                vertexSize += sizeof(Vector3);
            newBuffer.mMorphData = new unsigned char[newBuffer.mVertexCount * vertexSize];
            
            source.read(&newBuffer.mMorphData[0], newBuffer.mVertexCount * vertexSize);
            
            newMorph.mBuffers[bufferIndex] = newBuffer;
        }
        
        mMorphs.push_back(newMorph);
    }
    
    // Read skeleton
    mSkeleton.load(source);
    
    // Read bounding box
    mBoundingBox = source.readBoundingBox();
    
    // Read collision/raycast/occlusion LOD levels
    mCollisionLodLevel = source.readUInt();
    mRaycastLodLevel = source.readUInt();
    mOcclusionLodLevel = source.readUInt();
}

void Model::save(Serializer& dest)
{
    // Build lists of vertex and index buffers used by the geometries
    std::vector<VertexBuffer*> vertexBuffers;
    std::vector<IndexBuffer*> indexBuffers;
    
    for (unsigned i = 0; i < mGeometries.size(); ++i)
    {
        for (unsigned j = 0; j < mGeometries[i].size(); ++j)
        {
            storeOrLookupVertexBuffer(mGeometries[i][j]->getVertexBuffer(0), vertexBuffers);
            storeOrLookupIndexBuffer(mGeometries[i][j]->getIndexBuffer(), indexBuffers);
        }
    }
    
    // Write vertex buffers
    dest.writeUInt(vertexBuffers.size());
    for (unsigned i = 0; i < vertexBuffers.size(); ++i)
    {
        VertexBuffer* buffer = vertexBuffers[i];
        dest.writeUInt(buffer->getVertexCount());
        dest.writeUInt(buffer->getElementMask());
        dest.writeUInt(buffer->getMorphRangeStart());
        dest.writeUInt(buffer->getMorphRangeCount());
        void* data = buffer->lock(0, buffer->getVertexCount(), LOCK_READONLY);
        dest.write(data, buffer->getVertexCount() * buffer->getVertexSize());
        buffer->unlock();
    }
    // Write index buffers
    dest.writeUInt(indexBuffers.size());
    for (unsigned i = 0; i < indexBuffers.size(); ++i)
    {
        IndexBuffer* buffer = indexBuffers[i];
        dest.writeUInt(buffer->getIndexCount());
        dest.writeUInt(buffer->getIndexSize());
        void* data = buffer->lock(0, buffer->getIndexCount(), LOCK_READONLY);
        dest.write(data, buffer->getIndexCount() * buffer->getIndexSize());
        buffer->unlock();
    }
    // Write geometries
    dest.writeUInt(mGeometries.size());
    for (unsigned i = 0; i < mGeometries.size(); ++i)
    {
        // Write bone mappings
        dest.writeUInt(mGeometryBoneMappings[i].size());
        for (unsigned j = 0; j < mGeometryBoneMappings[i].size(); ++j)
            dest.writeUInt(mGeometryBoneMappings[i][j]);;
        
        // Write the LOD levels
        dest.writeUInt(mGeometries[i].size());
        for (unsigned j = 0; j < mGeometries[i].size(); ++j)
        {
            Geometry* geometry = mGeometries[i][j];
            dest.writeFloat(geometry->getLodDistance());
            dest.writeUInt(geometry->getPrimitiveType());
            dest.writeUInt(storeOrLookupVertexBuffer(geometry->getVertexBuffer(0), vertexBuffers));
            dest.writeUInt(storeOrLookupIndexBuffer(geometry->getIndexBuffer(), indexBuffers));
            dest.writeUInt(geometry->getIndexStart());
            dest.writeUInt(geometry->getIndexCount());
        }
    }
    
    // Write morphs
    dest.writeUInt(mMorphs.size());
    for (unsigned i = 0; i < mMorphs.size(); ++i)
    {
        dest.writeString(mMorphs[i].mName);
        dest.writeUInt(mMorphs[i].mBuffers.size());
        
        // Write morph vertex buffers
        for (std::map<unsigned int, VertexBufferMorph>::const_iterator j = mMorphs[i].mBuffers.begin();
            j != mMorphs[i].mBuffers.end(); ++j)
        {
            dest.writeUInt(j->first);
            dest.writeUInt(j->second.mElementMask);
            dest.writeUInt(j->second.mVertexCount);
            
            // Base size: size of each vertex index
            unsigned vertexSize = sizeof(unsigned);
            // Add size of individual elements
            if (j->second.mElementMask & MASK_POSITION)
                vertexSize += sizeof(Vector3);
            if (j->second.mElementMask & MASK_NORMAL)
                vertexSize += sizeof(Vector3);
            if (j->second.mElementMask & MASK_TANGENT)
                vertexSize += sizeof(Vector3);
            
            dest.write(j->second.mMorphData.getPtr(), vertexSize * j->second.mVertexCount);
        }
    }
    
    // Write skeleton
    mSkeleton.save(dest);
    
    // Write bounding box
    dest.writeBoundingBox(mBoundingBox);
    
    // Write collision/raycast/occlusion LOD levels
    dest.writeUInt(mCollisionLodLevel);
    dest.writeUInt(mRaycastLodLevel);
    dest.writeUInt(mOcclusionLodLevel);
}

void Model::setBoundingBox(const BoundingBox& box)
{
    mBoundingBox = box;
}

void Model::setNumGeometries(unsigned num)
{
    mGeometries.resize(num);
    mGeometryBoneMappings.resize(num);
}

bool Model::setNumGeometryLodLevels(unsigned index, unsigned num)
{
    if (index >= mGeometries.size())
    {
        LOGERROR("Illegal geometry index");
        return false;
    }
    if (!num)
    {
        LOGERROR("Zero LOD levels not allowed");
        return false;
    }
    
    mGeometries[index].resize(num);
    return true;
}

bool Model::setGeometry(unsigned index, unsigned lodLevel, Geometry* geometry)
{
    if (index >= mGeometries.size())
    {
        LOGERROR("Illegal geometry index");
        return false;
    }
    if (lodLevel >= mGeometries[index].size())
    {
        LOGERROR("Illegal LOD level index");
        return false;
    }
    
    mGeometries[index][lodLevel] = geometry;
    return true;
}

void Model::setSkeleton(const Skeleton& skeleton)
{
    mSkeleton.define(skeleton.getBones());
}

void Model::setGeometryBoneMappings(const std::vector<std::vector<unsigned> >& geometryBoneMappings)
{
    mGeometryBoneMappings = geometryBoneMappings;
}

void Model::setMorphs(const std::vector<ModelMorph>& morphs)
{
    mMorphs = morphs;
}

void Model::setCollisionLodLevel(unsigned lodLevel)
{
    mCollisionLodLevel = lodLevel;
}

void Model::setRaycastLodLevel(unsigned lodLevel)
{
    mRaycastLodLevel = lodLevel;
}

void Model::setOcclusionLodLevel(unsigned lodLevel)
{
    mOcclusionLodLevel = lodLevel;
}

unsigned Model::getNumGeometryLodLevels(unsigned index) const
{
    return index < mGeometries.size() ? mGeometries[index].size() : 0;
}

Geometry* Model::getGeometry(unsigned index, unsigned lodLevel) const
{
    if ((index >= mGeometries.size()) || (lodLevel >= mGeometries[index].size()))
        return 0;
    
    return mGeometries[index][lodLevel];
}

const ModelMorph* Model::getMorph(unsigned index) const
{
    return index < mMorphs.size() ? &mMorphs[index] : 0;
}

const ModelMorph* Model::getMorph(const std::string& name) const
{
    return getMorph(StringHash(name));
}

const ModelMorph* Model::getMorph(StringHash nameHash) const
{
    for (std::vector<ModelMorph>::const_iterator i = mMorphs.begin(); i != mMorphs.end(); ++i)
    {
        if (i->mNameHash == nameHash)
            return &(*i);
    }
    
    return 0;
}
