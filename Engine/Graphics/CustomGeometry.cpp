//
// Urho3D Engine
// Copyright (c) 2008-2012 Lasse Oorni
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
#include "Batch.h"
#include "Camera.h"
#include "Context.h"
#include "CustomGeometry.h"
#include "Geometry.h"
#include "Log.h"
#include "Material.h"
#include "Node.h"
#include "OcclusionBuffer.h"
#include "OctreeQuery.h"
#include "Profiler.h"
#include "VertexBuffer.h"

#include "DebugNew.h"

namespace Urho3D
{

OBJECTTYPESTATIC(CustomGeometry);

CustomGeometry::CustomGeometry(Context* context) :
    Drawable(context),
    geometryIndex_(0),
    elementMask_(MASK_POSITION)
{
    drawableFlags_ = DRAWABLE_GEOMETRY;
    
    vertexBuffer_ = new VertexBuffer(context_);
    vertexBuffer_->SetShadowed(true);
    SetNumGeometries(1);
}

CustomGeometry::~CustomGeometry()
{
}

void CustomGeometry::RegisterObject(Context* context)
{
    context->RegisterFactory<CustomGeometry>();
    
    ATTRIBUTE(CustomGeometry, VAR_BOOL, "Is Visible", visible_, true, AM_DEFAULT);
    ATTRIBUTE(CustomGeometry, VAR_BOOL, "Is Occluder", occluder_, false, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(CustomGeometry, VAR_BOOL, "Can Be Occluded", IsOccludee, SetOccludee, bool, true, AM_DEFAULT);
    ATTRIBUTE(CustomGeometry, VAR_BOOL, "Cast Shadows", castShadows_, false, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(CustomGeometry, VAR_FLOAT, "Draw Distance", GetDrawDistance, SetDrawDistance, float, 0.0f, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(CustomGeometry, VAR_FLOAT, "Shadow Distance", GetShadowDistance, SetShadowDistance, float, 0.0f, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(CustomGeometry, VAR_FLOAT, "LOD Bias", GetLodBias, SetLodBias, float, 1.0f, AM_DEFAULT);
    COPY_BASE_ATTRIBUTES(CustomGeometry, Drawable);
}

void CustomGeometry::ProcessRayQuery(const RayOctreeQuery& query, PODVector<RayQueryResult>& results)
{
    RayQueryLevel level = query.level_;
    
    switch (level)
    {
    case RAY_AABB_NOSUBOBJECTS:
    case RAY_AABB:
        Drawable::ProcessRayQuery(query, results);
        break;
        
    case RAY_OBB:
        {
            Matrix3x4 inverse(node_->GetWorldTransform().Inverse());
            Ray localRay(inverse * query.ray_.origin_, inverse * Vector4(query.ray_.direction_, 0.0f));
            float distance = localRay.HitDistance(boundingBox_);
            if (distance <= query.maxDistance_)
            {
                RayQueryResult result;
                result.drawable_ = this;
                result.node_ = GetNode();
                result.distance_ = distance;
                result.subObject_ = M_MAX_UNSIGNED;
                results.Push(result);
            }
        }
        break;
        
    case RAY_TRIANGLE:
        {
            // Do a pretest using the OBB
            Matrix3x4 inverse(node_->GetWorldTransform().Inverse());
            Ray localRay(inverse * query.ray_.origin_, inverse * Vector4(query.ray_.direction_, 0.0f));
            float distance = localRay.HitDistance(boundingBox_);
            if (distance <= query.maxDistance_)
            {
                // Then the actual test using triangle geometry
                for (unsigned i = 0; i < batches_.Size(); ++i)
                {
                    Geometry* geometry = batches_[i].geometry_;
                    if (geometry)
                    {
                        distance = geometry->GetHitDistance(localRay);
                        if (distance <= query.maxDistance_)
                        {
                            RayQueryResult result;
                            result.drawable_ = this;
                            result.node_ = GetNode();
                            result.distance_ = distance;
                            result.subObject_ = M_MAX_UNSIGNED;
                            results.Push(result);
                            break;
                        }
                    }
                }
            }
        }
        break;
    }
}

Geometry* CustomGeometry::GetLodGeometry(unsigned batchIndex, unsigned level)
{
    return batchIndex < geometries_.Size() ? geometries_[batchIndex] : (Geometry*)0;
}

unsigned CustomGeometry::GetNumOccluderTriangles()
{
    unsigned triangles = 0;
    
    for (unsigned i = 0; i < batches_.Size(); ++i)
    {
        Geometry* geometry = GetLodGeometry(i, 0);
        if (!geometry)
            continue;
        
        // Check that the material is suitable for occlusion (default material always is)
        Material* mat = batches_[i].material_;
        if (mat && !mat->GetOcclusion())
            continue;
        
        triangles += geometry->GetVertexCount() / 3;
    }
    
    return triangles;
}

bool CustomGeometry::DrawOcclusion(OcclusionBuffer* buffer)
{
    bool success = true;
    
    for (unsigned i = 0; i < batches_.Size(); ++i)
    {
        Geometry* geometry = GetLodGeometry(i, 0);
        if (!geometry)
            continue;
        
        // Check that the material is suitable for occlusion (default material always is) and set culling mode
        Material* material = batches_[i].material_;
        if (material)
        {
            if (!material->GetOcclusion())
                continue;
            buffer->SetCullMode(material->GetCullMode());
        }
        else
            buffer->SetCullMode(CULL_CCW);
        
        const unsigned char* vertexData;
        unsigned vertexSize;
        const unsigned char* indexData;
        unsigned indexSize;
        unsigned elementMask;
        
        geometry->GetRawData(vertexData, vertexSize, indexData, indexSize, elementMask);
        // Check for valid geometry data
        if (!vertexData)
            continue;
        
        // Draw and check for running out of triangles
        success = buffer->Draw(node_->GetWorldTransform(), vertexData, vertexSize, geometry->GetVertexStart(), geometry->GetVertexCount());
        
        if (!success)
            break;
    }
    
    return success;
}

void CustomGeometry::Clear()
{
    elementMask_ = MASK_POSITION;
    batches_.Clear();
    geometries_.Clear();
    primitiveTypes_.Clear();
    vertices_.Clear();
}

void CustomGeometry::SetNumGeometries(unsigned num)
{
    batches_.Resize(num);
    geometries_.Resize(num);
    primitiveTypes_.Resize(num);
    vertices_.Resize(num);
    
    for (unsigned i = 0; i < geometries_.Size(); ++i)
    {
        if (!geometries_[i])
            geometries_[i] = new Geometry(context_);
        
        batches_[i].geometry_ = geometries_[i];
    }
}

void CustomGeometry::BeginGeometry(unsigned index, PrimitiveType type)
{
    if (index > geometries_.Size())
    {
        LOGERROR("Geometry index out of bounds");
        return;
    }
    
    geometryIndex_ = index;
    primitiveTypes_[index] = type;
    vertices_[index].Clear();
}

void CustomGeometry::DefineVertex(const Vector3& position)
{
    if (vertices_.Size() < geometryIndex_)
        return;
    
    vertices_[geometryIndex_].Resize(vertices_[geometryIndex_].Size() + 1);
    vertices_[geometryIndex_].Back().position_ = position;
}

void CustomGeometry::DefineNormal(const Vector3& normal)
{
    if (vertices_.Size() < geometryIndex_ || vertices_[geometryIndex_].Empty())
        return;
    
    vertices_[geometryIndex_].Back().normal_ = normal;
    elementMask_ |= MASK_NORMAL;
}

void CustomGeometry::DefineColor(const Color& color)
{
    if (vertices_.Size() < geometryIndex_ || vertices_[geometryIndex_].Empty())
        return;
    
    vertices_[geometryIndex_].Back().color_ = color.ToUInt();
    elementMask_ |= MASK_COLOR;
}

void CustomGeometry::DefineTexCoord(const Vector2& texCoord)
{
    if (vertices_.Size() < geometryIndex_ || vertices_[geometryIndex_].Empty())
        return;
    
    vertices_[geometryIndex_].Back().texCoord_ = texCoord;
    elementMask_ |= MASK_TEXCOORD1;
}

void CustomGeometry::DefineTangent(const Vector4& tangent)
{
    if (vertices_.Size() < geometryIndex_ || vertices_[geometryIndex_].Empty())
        return;
    
    vertices_[geometryIndex_].Back().tangent_ = tangent;
    elementMask_ |= MASK_TANGENT;
}

void CustomGeometry::Commit()
{
    PROFILE(CommitCustomGeometry);
    
    unsigned totalVertices = 0;
    boundingBox_.Clear();
    
    for (unsigned i = 0; i < vertices_.Size(); ++i)
    {
        totalVertices += vertices_[i].Size();
        
        for (unsigned j = 0; j < vertices_[i].Size(); ++j)
            boundingBox_.Merge(vertices_[i][j].position_);
    }
    
    vertexBuffer_->SetSize(totalVertices, elementMask_);
    
    if (totalVertices)
    {
        unsigned char* dest = (unsigned char*)vertexBuffer_->Lock(0, totalVertices, true);
        if (dest)
        {
            unsigned vertexStart = 0;
            
            for (unsigned i = 0; i < vertices_.Size(); ++i)
            {
                unsigned vertexCount = 0;
                
                for (unsigned j = 0; j < vertices_[i].Size(); ++j)
                {
                    *((Vector3*)dest) = vertices_[i][j].position_;
                    dest += sizeof(Vector3);
                    
                    if (elementMask_ & MASK_NORMAL)
                    {
                        *((Vector3*)dest) = vertices_[i][j].normal_;
                        dest += sizeof(Vector3);
                    }
                    if (elementMask_ & MASK_COLOR)
                    {
                        *((unsigned*)dest) = vertices_[i][j].color_;
                        dest += sizeof(unsigned);
                    }
                    if (elementMask_ & MASK_TEXCOORD1)
                    {
                        *((Vector2*)dest) = vertices_[i][j].texCoord_;
                        dest += sizeof(Vector2);
                    }
                    if (elementMask_ & MASK_TANGENT)
                    {
                        *((Vector4*)dest) = vertices_[i][j].tangent_;
                        dest += sizeof(Vector4);
                    }
                    
                    ++vertexCount;
                }
                
                geometries_[i]->SetVertexBuffer(0, vertexBuffer_, elementMask_);
                geometries_[i]->SetDrawRange(primitiveTypes_[i], 0, 0, vertexStart, vertexCount);
                vertexStart += vertexCount;
            }
            
            vertexBuffer_->Unlock();
        }
        else
            LOGERROR("Failed to lock custom geometry vertex buffer");
    }
    else
    {
        for (unsigned i = 0; i < geometries_.Size(); ++i)
        {
            geometries_[i]->SetVertexBuffer(0, vertexBuffer_, elementMask_);
            geometries_[i]->SetDrawRange(primitiveTypes_[i], 0, 0, 0, 0);
        }
    }
    
    vertexBuffer_->ClearDataLost();
}

void CustomGeometry::SetMaterial(Material* material)
{
    for (unsigned i = 0; i < batches_.Size(); ++i)
        batches_[i].material_ = material;
    
    MarkNetworkUpdate();
}

bool CustomGeometry::SetMaterial(unsigned index, Material* material)
{
    if (index >= batches_.Size())
    {
        LOGERROR("Material index out of bounds");
        return false;
    }
    
    batches_[index].material_ = material;
    MarkNetworkUpdate();
    return true;
}

Material* CustomGeometry::GetMaterial(unsigned index) const
{
    return index < batches_.Size() ? batches_[index].material_ : (Material*)0;
}

void CustomGeometry::OnWorldBoundingBoxUpdate()
{
    worldBoundingBox_ = boundingBox_.Transformed(node_->GetWorldTransform());
}

}
