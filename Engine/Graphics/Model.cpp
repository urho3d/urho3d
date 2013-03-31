//
// Copyright (c) 2008-2013 the Urho3D project.
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
#include "Context.h"
#include "Deserializer.h"
#include "Geometry.h"
#include "IndexBuffer.h"
#include "Log.h"
#include "Model.h"
#include "Profiler.h"
#include "Graphics.h"
#include "Serializer.h"
#include "VertexBuffer.h"

#include <cstring>

#include "DebugNew.h"

namespace Urho3D
{

unsigned LookupVertexBuffer(VertexBuffer* buffer, const Vector<SharedPtr<VertexBuffer> >& buffers)
{
    for (unsigned i = 0; i < buffers.Size(); ++i)
    {
        if (buffers[i] == buffer)
            return i;
    }
    return 0;
}

unsigned LookupIndexBuffer(IndexBuffer* buffer, const Vector<SharedPtr<IndexBuffer> >& buffers)
{
    for (unsigned i = 0; i < buffers.Size(); ++i)
    {
        if (buffers[i] == buffer)
            return i;
    }
    return 0;
}

OBJECTTYPESTATIC(Model);

Model::Model(Context* context) :
    Resource(context)
{
}

Model::~Model()
{
}

void Model::RegisterObject(Context* context)
{
    context->RegisterFactory<Model>();
}

bool Model::Load(Deserializer& source)
{
    PROFILE(LoadModel);
    
    // Check ID
    if (source.ReadFileID() != "UMDL")
    {
        LOGERROR(source.GetName() + " is not a valid model file");
        return false;
    }
    
    geometries_.Clear();
    geometryBoneMappings_.Clear();
    geometryCenters_.Clear();
    morphs_.Clear();
    vertexBuffers_.Clear();
    indexBuffers_.Clear();
    
    unsigned memoryUse = sizeof(Model);
    
    // Read vertex buffers
    unsigned numVertexBuffers = source.ReadUInt();
    vertexBuffers_.Reserve(numVertexBuffers);
    morphRangeStarts_.Resize(numVertexBuffers);
    morphRangeCounts_.Resize(numVertexBuffers);
    for (unsigned i = 0; i < numVertexBuffers; ++i)
    {
        unsigned vertexCount = source.ReadUInt();
        unsigned elementMask = source.ReadUInt();
        morphRangeStarts_[i] = source.ReadUInt();
        morphRangeCounts_[i] = source.ReadUInt();
        
        SharedPtr<VertexBuffer> buffer(new VertexBuffer(context_));
        buffer->SetShadowed(true);
        buffer->SetSize(vertexCount, elementMask);
        
        void* dest = buffer->Lock(0, vertexCount);
        unsigned vertexSize = buffer->GetVertexSize();
        source.Read(dest, vertexCount * vertexSize);
        buffer->Unlock();
        
        memoryUse += sizeof(VertexBuffer) + vertexCount * vertexSize;
        vertexBuffers_.Push(buffer);
    }

    // Read index buffers
    unsigned numIndexBuffers = source.ReadUInt();
    indexBuffers_.Reserve(numIndexBuffers);
    for (unsigned i = 0; i < numIndexBuffers; ++i)
    {
        unsigned indexCount = source.ReadUInt();
        unsigned indexSize = source.ReadUInt();
        
        SharedPtr<IndexBuffer> buffer(new IndexBuffer(context_));
        buffer->SetShadowed(true);
        buffer->SetSize(indexCount, indexSize > sizeof(unsigned short));
        
        void* dest = buffer->Lock(0, indexCount);
        source.Read(dest, indexCount * indexSize);
        buffer->Unlock();
        
        memoryUse += sizeof(IndexBuffer) + indexCount * indexSize;
        indexBuffers_.Push(buffer);
    }
    
    // Read geometries
    unsigned numGeometries = source.ReadUInt();
    geometries_.Reserve(numGeometries);
    geometryBoneMappings_.Reserve(numGeometries);
    geometryCenters_.Reserve(numGeometries);
    for (unsigned i = 0; i < numGeometries; ++i)
    {
        // Read bone mappings
        unsigned boneMappingCount = source.ReadUInt();
        PODVector<unsigned> boneMapping(boneMappingCount);
        for (unsigned j = 0; j < boneMappingCount; ++j)
            boneMapping[j] = source.ReadUInt();
        geometryBoneMappings_.Push(boneMapping);
        
        unsigned numLodLevels = source.ReadUInt();
        Vector<SharedPtr<Geometry> > geometryLodLevels;
        geometryLodLevels.Reserve(numLodLevels);
        
        for (unsigned j = 0; j < numLodLevels; ++j)
        {
            float distance = source.ReadFloat();
            PrimitiveType type = (PrimitiveType)source.ReadUInt();
            
            unsigned vertexBufferRef = source.ReadUInt();
            unsigned indexBufferRef = source.ReadUInt();
            unsigned indexStart = source.ReadUInt();
            unsigned indexCount = source.ReadUInt();
            
            if (vertexBufferRef >= vertexBuffers_.Size())
            {
                LOGERROR("Vertex buffer index out of bounds");
                return false;
            }
            if (indexBufferRef >= indexBuffers_.Size())
            {
                LOGERROR("Index buffer index out of bounds");
                return false;
            }
            
            SharedPtr<Geometry> geometry(new Geometry(context_));
            geometry->SetVertexBuffer(0, vertexBuffers_[vertexBufferRef]);
            geometry->SetIndexBuffer(indexBuffers_[indexBufferRef]);
            geometry->SetDrawRange(type, indexStart, indexCount);
            geometry->SetLodDistance(distance);
            
            geometryLodLevels.Push(geometry);
            memoryUse += sizeof(Geometry);
        }
        
        geometries_.Push(geometryLodLevels);
    }
    
    // Read morphs
    unsigned numMorphs = source.ReadUInt();
    morphs_.Reserve(numMorphs);
    for (unsigned i = 0; i < numMorphs; ++i)
    {
        ModelMorph newMorph;
        
        newMorph.name_ = source.ReadString();
        newMorph.nameHash_ = newMorph.name_;
        newMorph.weight_ = 0.0f;
        unsigned nubuffers_ = source.ReadUInt();
        
        for (unsigned j = 0; j < nubuffers_; ++j)
        {
            VertexBufferMorph newBuffer;
            unsigned bufferIndex = source.ReadUInt();
            
            newBuffer.elementMask_ = source.ReadUInt();
            newBuffer.vertexCount_ = source.ReadUInt();
            
            // Base size: size of each vertex index
            unsigned vertexSize = sizeof(unsigned);
            // Add size of individual elements
            if (newBuffer.elementMask_ & MASK_POSITION)
                vertexSize += sizeof(Vector3);
            if (newBuffer.elementMask_ & MASK_NORMAL)
                vertexSize += sizeof(Vector3);
            if (newBuffer.elementMask_ & MASK_TANGENT)
                vertexSize += sizeof(Vector3);
            newBuffer.morphData_ = new unsigned char[newBuffer.vertexCount_ * vertexSize];
            
            source.Read(&newBuffer.morphData_[0], newBuffer.vertexCount_ * vertexSize);
            
            newMorph.buffers_[bufferIndex] = newBuffer;
            memoryUse += sizeof(VertexBufferMorph) + newBuffer.vertexCount_ * vertexSize;
        }
        
        morphs_.Push(newMorph);
        memoryUse += sizeof(ModelMorph);
    }
    
    // Read skeleton
    skeleton_.Load(source);
    memoryUse += skeleton_.GetNumBones() * sizeof(Bone);
    
    // Read bounding box
    boundingBox_ = source.ReadBoundingBox();
    
    // Read geometry centers
    for (unsigned i = 0; i < geometries_.Size() && !source.IsEof(); ++i)
        geometryCenters_.Push(source.ReadVector3());
    while (geometryCenters_.Size() < geometries_.Size())
        geometryCenters_.Push(Vector3::ZERO);
    memoryUse += sizeof(Vector3) * geometries_.Size();
    
    SetMemoryUse(memoryUse);
    return true;
}

bool Model::Save(Serializer& dest)
{
    // Write ID
    if (!dest.WriteFileID("UMDL"))
        return false;
    
    // Write vertex buffers
    dest.WriteUInt(vertexBuffers_.Size());
    for (unsigned i = 0; i < vertexBuffers_.Size(); ++i)
    {
        VertexBuffer* buffer = vertexBuffers_[i];
        dest.WriteUInt(buffer->GetVertexCount());
        dest.WriteUInt(buffer->GetElementMask());
        dest.WriteUInt(morphRangeStarts_[i]);
        dest.WriteUInt(morphRangeCounts_[i]);
        dest.Write(buffer->GetShadowData(), buffer->GetVertexCount() * buffer->GetVertexSize());
    }
    // Write index buffers
    dest.WriteUInt(indexBuffers_.Size());
    for (unsigned i = 0; i < indexBuffers_.Size(); ++i)
    {
        IndexBuffer* buffer = indexBuffers_[i];
        dest.WriteUInt(buffer->GetIndexCount());
        dest.WriteUInt(buffer->GetIndexSize());
        dest.Write(buffer->GetShadowData(), buffer->GetIndexCount() * buffer->GetIndexSize());
    }
    // Write geometries
    dest.WriteUInt(geometries_.Size());
    for (unsigned i = 0; i < geometries_.Size(); ++i)
    {
        // Write bone mappings
        dest.WriteUInt(geometryBoneMappings_[i].Size());
        for (unsigned j = 0; j < geometryBoneMappings_[i].Size(); ++j)
            dest.WriteUInt(geometryBoneMappings_[i][j]);
        
        // Write the LOD levels
        dest.WriteUInt(geometries_[i].Size());
        for (unsigned j = 0; j < geometries_[i].Size(); ++j)
        {
            Geometry* geometry = geometries_[i][j];
            dest.WriteFloat(geometry->GetLodDistance());
            dest.WriteUInt(geometry->GetPrimitiveType());
            dest.WriteUInt(LookupVertexBuffer(geometry->GetVertexBuffer(0), vertexBuffers_));
            dest.WriteUInt(LookupIndexBuffer(geometry->GetIndexBuffer(), indexBuffers_));
            dest.WriteUInt(geometry->GetIndexStart());
            dest.WriteUInt(geometry->GetIndexCount());
        }
    }
    
    // Write morphs
    dest.WriteUInt(morphs_.Size());
    for (unsigned i = 0; i < morphs_.Size(); ++i)
    {
        dest.WriteString(morphs_[i].name_);
        dest.WriteUInt(morphs_[i].buffers_.Size());
        
        // Write morph vertex buffers
        for (HashMap<unsigned int, VertexBufferMorph>::ConstIterator j = morphs_[i].buffers_.Begin();
            j != morphs_[i].buffers_.End(); ++j)
        {
            dest.WriteUInt(j->first_);
            dest.WriteUInt(j->second_.elementMask_);
            dest.WriteUInt(j->second_.vertexCount_);
            
            // Base size: size of each vertex index
            unsigned vertexSize = sizeof(unsigned);
            // Add size of individual elements
            if (j->second_.elementMask_ & MASK_POSITION)
                vertexSize += sizeof(Vector3);
            if (j->second_.elementMask_ & MASK_NORMAL)
                vertexSize += sizeof(Vector3);
            if (j->second_.elementMask_ & MASK_TANGENT)
                vertexSize += sizeof(Vector3);
            
            dest.Write(j->second_.morphData_.Get(), vertexSize * j->second_.vertexCount_);
        }
    }
    
    // Write skeleton
    skeleton_.Save(dest);
    
    // Write bounding box
    dest.WriteBoundingBox(boundingBox_);
    
    // Write geometry centers
    for (unsigned i = 0; i < geometryCenters_.Size(); ++i)
        dest.WriteVector3(geometryCenters_[i]);
    
    return true;
}

void Model::SetBoundingBox(const BoundingBox& box)
{
    boundingBox_ = box;
}

bool Model::SetVertexBuffers(const Vector<SharedPtr<VertexBuffer> >& buffers, const PODVector<unsigned>& morphRangeStarts, const PODVector<unsigned>& morphRangeCounts)
{
    for (unsigned i = 0; i < buffers.Size(); ++i)
    {
        if (!buffers[i])
        {
            LOGERROR("Null model vertex buffers specified");
            return false;
        }
        if (!buffers[i]->IsShadowed())
        {
            LOGERROR("Model vertex buffers must be shadowed");
            return false;
        }
    }
    
    vertexBuffers_ = buffers;
    morphRangeStarts_.Resize(buffers.Size());
    morphRangeCounts_.Resize(buffers.Size());
    
    // If morph ranges are not specified for buffers, assume to be zero
    for (unsigned i = 0; i < buffers.Size(); ++i)
    {
        morphRangeStarts_[i] = i < morphRangeStarts.Size() ? morphRangeStarts[i] : 0;
        morphRangeCounts_[i] = i < morphRangeCounts.Size() ? morphRangeCounts[i] : 0;
    }
    
    return true;
}

bool Model::SetIndexBuffers(const Vector<SharedPtr<IndexBuffer> >& buffers)
{
    for (unsigned i = 0; i < buffers.Size(); ++i)
    {
        if (!buffers[i])
        {
            LOGERROR("Null model index buffers specified");
            return false;
        }
        if (!buffers[i]->IsShadowed())
        {
            LOGERROR("Model index buffers must be shadowed");
            return false;
        }
    }
    
    indexBuffers_ = buffers;
    return true;
}

void Model::SetNumGeometries(unsigned num)
{
    geometries_.Resize(num);
    geometryBoneMappings_.Resize(num);
    geometryCenters_.Resize(num);
}

bool Model::SetNumGeometryLodLevels(unsigned index, unsigned num)
{
    if (index >= geometries_.Size())
    {
        LOGERROR("Geometry index out of bounds");
        return false;
    }
    if (!num)
    {
        LOGERROR("Zero LOD levels not allowed");
        return false;
    }
    
    geometries_[index].Resize(num);
    return true;
}

bool Model::SetGeometry(unsigned index, unsigned lodLevel, Geometry* geometry)
{
    if (index >= geometries_.Size())
    {
        LOGERROR("Geometry index out of bounds");
        return false;
    }
    if (lodLevel >= geometries_[index].Size())
    {
        LOGERROR("LOD level index out of bounds");
        return false;
    }
    
    geometries_[index][lodLevel] = geometry;
    return true;
}

bool Model::SetGeometryCenter(unsigned index, const Vector3& center)
{
    if (index >= geometryCenters_.Size())
    {
        LOGERROR("Geometry index out of bounds");
        return false;
    }
    
    geometryCenters_[index] = center;
    return true;
}

void Model::SetSkeleton(const Skeleton& skeleton)
{
    skeleton_ = skeleton;
}

void Model::SetGeometryBoneMappings(const Vector<PODVector<unsigned> >& geometryBoneMappings)
{
    geometryBoneMappings_ = geometryBoneMappings;
}

void Model::SetMorphs(const Vector<ModelMorph>& morphs)
{
    morphs_ = morphs;
}

unsigned Model::GetNumGeometryLodLevels(unsigned index) const
{
    return index < geometries_.Size() ? geometries_[index].Size() : 0;
}

Geometry* Model::GetGeometry(unsigned index, unsigned lodLevel) const
{
    if (index >= geometries_.Size() || lodLevel >= geometries_[index].Size())
        return 0;
    
    return geometries_[index][lodLevel];
}

const ModelMorph* Model::GetMorph(unsigned index) const
{
    return index < morphs_.Size() ? &morphs_[index] : 0;
}

const ModelMorph* Model::GetMorph(const String& name) const
{
    return GetMorph(StringHash(name));
}

const ModelMorph* Model::GetMorph(StringHash nameHash) const
{
    for (Vector<ModelMorph>::ConstIterator i = morphs_.Begin(); i != morphs_.End(); ++i)
    {
        if (i->nameHash_ == nameHash)
            return &(*i);
    }
    
    return 0;
}

unsigned Model::GetMorphRangeStart(unsigned bufferIndex) const
{
    return bufferIndex < vertexBuffers_.Size() ? morphRangeStarts_[bufferIndex] : 0;
}

unsigned Model::GetMorphRangeCount(unsigned bufferIndex) const
{
    return bufferIndex < vertexBuffers_.Size() ? morphRangeCounts_[bufferIndex] : 0;
}

}
