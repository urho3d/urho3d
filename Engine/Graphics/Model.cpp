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

unsigned StoreOrLookupVertexBuffer(VertexBuffer* buffer, Vector<VertexBuffer*>& dest)
{
    for (unsigned i = 0; i < dest.Size(); ++i)
    {
        if (dest[i] == buffer)
            return i;
    }
    dest.Push(buffer);
    return dest.Size() - 1;
}

unsigned StoreOrLookupIndexBuffer(IndexBuffer* buffer, Vector<IndexBuffer*>& dest)
{
    for (unsigned i = 0; i < dest.Size(); ++i)
    {
        if (dest[i] == buffer)
            return i;
    }
    dest.Push(buffer);
    return dest.Size() - 1;
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
    if (source.ReadID() != "UMDL")
    {
        LOGERROR(source.GetName() + " is not a valid model file");
        return false;
    }
    
    geometries_.Clear();
    geometryBoneMappings_.Clear();
    morphs_.Clear();
    vertexBuffers_.Clear();
    indexBuffers_.Clear();
    
    SetMemoryUse(source.GetSize());
    
    // Read vertex buffers
    unsigned numVertexBuffers = source.ReadUInt();
    for (unsigned i = 0; i < numVertexBuffers; ++i)
    {
        unsigned vertexCount = source.ReadUInt();
        unsigned elementMask = source.ReadUInt();
        unsigned morphStart = source.ReadUInt();
        unsigned morphCount = source.ReadUInt();
        
        SharedPtr<VertexBuffer> buffer(new VertexBuffer(context_));
        buffer->SetSize(vertexCount, elementMask);
        buffer->SetMorphRange(morphStart, morphCount);
        
        unsigned vertexSize = buffer->GetVertexSize();
        unsigned char* data = (unsigned char*)buffer->Lock(0, vertexCount, LOCK_NORMAL);
        if (data)
        {
            source.Read(data, vertexCount * vertexSize);
            // If there is a morph range, make a copy of the data so that the morph range can be reset
            if (morphCount)
            {
                SharedArrayPtr<unsigned char> morphResetData(new unsigned char[morphCount * vertexSize]);
                memcpy(morphResetData.GetPtr(), &data[morphStart * vertexSize], morphCount * vertexSize);
                buffer->SetMorphRangeResetData(morphResetData);
            }
            buffer->Unlock();
        }
        else
            return false;
        
        vertexBuffers_.Push(buffer);
    }
    
    // Read index buffers
    unsigned numIndexBuffers = source.ReadUInt();
    for (unsigned i = 0; i < numIndexBuffers; ++i)
    {
        unsigned indexCount = source.ReadUInt();
        unsigned indexSize = source.ReadUInt();
        
        SharedPtr<IndexBuffer> buffer(new IndexBuffer(context_));
        buffer->SetSize(indexCount, indexSize);
        
        unsigned char* data = (unsigned char*)buffer->Lock(0, indexCount, LOCK_NORMAL);
        if (data)
        {
            source.Read(data, indexCount * indexSize);
            buffer->Unlock();
        }
        else
            return false;
        
        indexBuffers_.Push(buffer);
    }
    
    // Read geometries
    unsigned numGeometries = source.ReadUInt();
    for (unsigned i = 0; i < numGeometries; ++i)
    {
        // Read bone mappings
        unsigned boneMappingCount = source.ReadUInt();
        PODVector<unsigned> boneMapping;
        for (unsigned j = 0; j < boneMappingCount; ++j)
            boneMapping.Push(source.ReadUInt());
        geometryBoneMappings_.Push(boneMapping);
        
        unsigned numLodLevels = source.ReadUInt();
        Vector<SharedPtr<Geometry> > geometryLodLevels;
        
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
            geometry->SetNumVertexBuffers(1);
            geometry->SetVertexBuffer(0, vertexBuffers_[vertexBufferRef]);
            geometry->SetIndexBuffer(indexBuffers_[indexBufferRef]);
            geometry->SetDrawRange(type, indexStart, indexCount);
            geometry->SetLodDistance(distance);
            
            geometryLodLevels.Push(geometry);
        }
        
        geometries_.Push(geometryLodLevels);
    }
    
    // Read morphs
    unsigned numMorphs = source.ReadUInt();
    for (unsigned i = 0; i < numMorphs; ++i)
    {
        ModelMorph newMorph;
        
        newMorph.name_ = source.ReadString();
        newMorph.nameHash_ = StringHash(newMorph.name_);
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
        }
        
        morphs_.Push(newMorph);
    }
    
    // Read skeleton
    skeleton_.Load(source);
    
    // Read bounding box
    boundingBox_ = source.ReadBoundingBox();
    
    return true;
}

bool Model::Save(Serializer& dest)
{
    // Build lists of vertex and index buffers used by the geometries
    Vector<VertexBuffer*> vertexBuffers;
    Vector<IndexBuffer*> indexBuffers;
    
    for (unsigned i = 0; i < geometries_.Size(); ++i)
    {
        for (unsigned j = 0; j < geometries_[i].Size(); ++j)
        {
            StoreOrLookupVertexBuffer(geometries_[i][j]->GetVertexBuffer(0), vertexBuffers);
            StoreOrLookupIndexBuffer(geometries_[i][j]->GetIndexBuffer(), indexBuffers);
        }
    }
    
    // Write ID
    if (!dest.WriteID("UMDL"))
        return false;
    
    // Write vertex buffers
    dest.WriteUInt(vertexBuffers.Size());
    for (unsigned i = 0; i < vertexBuffers.Size(); ++i)
    {
        VertexBuffer* buffer = vertexBuffers[i];
        dest.WriteUInt(buffer->GetVertexCount());
        dest.WriteUInt(buffer->GetElementMask());
        dest.WriteUInt(buffer->GetMorphRangeStart());
        dest.WriteUInt(buffer->GetMorphRangeCount());
        void* data = buffer->Lock(0, buffer->GetVertexCount(), LOCK_READONLY);
        if (!data)
            return false;
        dest.Write(data, buffer->GetVertexCount() * buffer->GetVertexSize());
        buffer->Unlock();
    }
    // Write index buffers
    dest.WriteUInt(indexBuffers.Size());
    for (unsigned i = 0; i < indexBuffers.Size(); ++i)
    {
        IndexBuffer* buffer = indexBuffers[i];
        dest.WriteUInt(buffer->GetIndexCount());
        dest.WriteUInt(buffer->GetIndexSize());
        void* data = buffer->Lock(0, buffer->GetIndexCount(), LOCK_READONLY);
        if (!data)
            return false;
        dest.Write(data, buffer->GetIndexCount() * buffer->GetIndexSize());
        buffer->Unlock();
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
            dest.WriteUInt(StoreOrLookupVertexBuffer(geometry->GetVertexBuffer(0), vertexBuffers));
            dest.WriteUInt(StoreOrLookupIndexBuffer(geometry->GetIndexBuffer(), indexBuffers));
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
        for (Map<unsigned int, VertexBufferMorph>::ConstIterator j = morphs_[i].buffers_.Begin();
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
            
            dest.Write(j->second_.morphData_.GetPtr(), vertexSize * j->second_.vertexCount_);
        }
    }
    
    // Write skeleton
    skeleton_.Save(dest);
    
    // Write bounding box
    dest.WriteBoundingBox(boundingBox_);
    
    return true;
}

void Model::SetBoundingBox(const BoundingBox& box)
{
    boundingBox_ = box;
}

void Model::SetNumGeometries(unsigned num)
{
    geometries_.Resize(num);
    geometryBoneMappings_.Resize(num);
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
    if ((index >= geometries_.Size()) || (lodLevel >= geometries_[index].Size()))
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
