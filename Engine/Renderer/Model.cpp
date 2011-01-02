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
#include "VertexBuffer.h"

#include <cstring>

#include "DebugNew.h"

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

void Model::setBoundingBox(const BoundingBox& box)
{
    mBoundingBox = box;
}

void Model::setNumGeometries(unsigned num)
{
    mGeometries.resize(num);
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
    if (index >= mGeometries.size())
        return 0;
    return mGeometries[index].size();
}

Geometry* Model::getGeometry(unsigned index, unsigned lodLevel) const
{
    if ((index >= mGeometries.size()) || (lodLevel >= mGeometries[index].size()))
        return 0;
    
    return mGeometries[index][lodLevel];
}

const ModelMorph* Model::getMorph(unsigned index) const
{
    if (index >= mMorphs.size())
        return 0;
    return &mMorphs[index];
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
