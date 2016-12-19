//
// Copyright (c) 2008-2016 the Urho3D project.
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

#include "../Precompiled.h"

#include "../Core/Context.h"
#include "../Core/Profiler.h"
#include "../Graphics/Batch.h"
#include "../Graphics/Camera.h"
#include "../Graphics/CustomGeometry.h"
#include "../Graphics/Geometry.h"
#include "../Graphics/Material.h"
#include "../Graphics/OcclusionBuffer.h"
#include "../Graphics/OctreeQuery.h"
#include "../Graphics/VertexBuffer.h"
#include "../IO/Log.h"
#include "../IO/MemoryBuffer.h"
#include "../Resource/ResourceCache.h"
#include "../Scene/Node.h"

#include "../DebugNew.h"

namespace Urho3D
{

extern const char* GEOMETRY_CATEGORY;

CustomGeometry::CustomGeometry(Context* context) :
    Drawable(context, DRAWABLE_GEOMETRY),
    vertexBuffer_(new VertexBuffer(context)),
    elementMask_(MASK_POSITION),
    geometryIndex_(0),
    materialsAttr_(Material::GetTypeStatic()),
    dynamic_(false)
{
    vertexBuffer_->SetShadowed(true);
    SetNumGeometries(1);
}

CustomGeometry::~CustomGeometry()
{
}

void CustomGeometry::RegisterObject(Context* context)
{
    context->RegisterFactory<CustomGeometry>(GEOMETRY_CATEGORY);

    URHO3D_ACCESSOR_ATTRIBUTE("Is Enabled", IsEnabled, SetEnabled, bool, true, AM_DEFAULT);
    URHO3D_ATTRIBUTE("Dynamic Vertex Buffer", bool, dynamic_, false, AM_DEFAULT);
    URHO3D_MIXED_ACCESSOR_ATTRIBUTE("Geometry Data", GetGeometryDataAttr, SetGeometryDataAttr, PODVector<unsigned char>,
        Variant::emptyBuffer, AM_FILE | AM_NOEDIT);
    URHO3D_ACCESSOR_ATTRIBUTE("Materials", GetMaterialsAttr, SetMaterialsAttr, ResourceRefList, ResourceRefList(Material::GetTypeStatic()),
        AM_DEFAULT);
    URHO3D_ATTRIBUTE("Is Occluder", bool, occluder_, false, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Can Be Occluded", IsOccludee, SetOccludee, bool, true, AM_DEFAULT);
    URHO3D_ATTRIBUTE("Cast Shadows", bool, castShadows_, false, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Draw Distance", GetDrawDistance, SetDrawDistance, float, 0.0f, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Shadow Distance", GetShadowDistance, SetShadowDistance, float, 0.0f, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("LOD Bias", GetLodBias, SetLodBias, float, 1.0f, AM_DEFAULT);
    URHO3D_COPY_BASE_ATTRIBUTES(Drawable);
}

void CustomGeometry::ProcessRayQuery(const RayOctreeQuery& query, PODVector<RayQueryResult>& results)
{
    RayQueryLevel level = query.level_;

    switch (level)
    {
    case RAY_AABB:
        Drawable::ProcessRayQuery(query, results);
        break;

    case RAY_OBB:
    case RAY_TRIANGLE:
        {
            Matrix3x4 inverse(node_->GetWorldTransform().Inverse());
            Ray localRay = query.ray_.Transformed(inverse);
            float distance = localRay.HitDistance(boundingBox_);
            Vector3 normal = -query.ray_.direction_;

            if (level == RAY_TRIANGLE && distance < query.maxDistance_)
            {
                distance = M_INFINITY;

                for (unsigned i = 0; i < batches_.Size(); ++i)
                {
                    Geometry* geometry = batches_[i].geometry_;
                    if (geometry)
                    {
                        Vector3 geometryNormal;
                        float geometryDistance = geometry->GetHitDistance(localRay, &geometryNormal);
                        if (geometryDistance < query.maxDistance_ && geometryDistance < distance)
                        {
                            distance = geometryDistance;
                            normal = (node_->GetWorldTransform() * Vector4(geometryNormal, 0.0f)).Normalized();
                        }
                    }
                }
            }

            if (distance < query.maxDistance_)
            {
                RayQueryResult result;
                result.position_ = query.ray_.origin_ + distance * query.ray_.direction_;
                result.normal_ = normal;
                result.distance_ = distance;
                result.drawable_ = this;
                result.node_ = node_;
                result.subObject_ = M_MAX_UNSIGNED;
                results.Push(result);
            }
        }
        break;

    case RAY_TRIANGLE_UV:
        URHO3D_LOGWARNING("RAY_TRIANGLE_UV query level is not supported for CustomGeometry component");
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
        const PODVector<VertexElement>* elements;

        geometry->GetRawData(vertexData, vertexSize, indexData, indexSize, elements);
        // Check for valid geometry data
        if (!vertexData || !elements || VertexBuffer::GetElementOffset(*elements, TYPE_VECTOR3, SEM_POSITION) != 0)
            continue;

        // Draw and check for running out of triangles
        success = buffer->AddTriangles(node_->GetWorldTransform(), vertexData, vertexSize, geometry->GetVertexStart(),
            geometry->GetVertexCount());

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

void CustomGeometry::SetDynamic(bool enable)
{
    dynamic_ = enable;

    MarkNetworkUpdate();
}

void CustomGeometry::BeginGeometry(unsigned index, PrimitiveType type)
{
    if (index > geometries_.Size())
    {
        URHO3D_LOGERROR("Geometry index out of bounds");
        return;
    }

    geometryIndex_ = index;
    primitiveTypes_[index] = type;
    vertices_[index].Clear();

    // If beginning the first geometry, reset the element mask
    if (!index)
        elementMask_ = MASK_POSITION;
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

void CustomGeometry::DefineGeometry(unsigned index, PrimitiveType type, unsigned numVertices, bool hasNormals, bool hasColors,
    bool hasTexCoords, bool hasTangents)
{
    if (index > geometries_.Size())
    {
        URHO3D_LOGERROR("Geometry index out of bounds");
        return;
    }

    geometryIndex_ = index;
    primitiveTypes_[index] = type;
    vertices_[index].Resize(numVertices);

    // If defining the first geometry, reset the element mask
    if (!index)
        elementMask_ = MASK_POSITION;
    if (hasNormals)
        elementMask_ |= MASK_NORMAL;
    if (hasColors)
        elementMask_ |= MASK_COLOR;
    if (hasTexCoords)
        elementMask_ |= MASK_TEXCOORD1;
    if (hasTangents)
        elementMask_ |= MASK_TANGENT;
}

void CustomGeometry::Commit()
{
    URHO3D_PROFILE(CommitCustomGeometry);

    unsigned totalVertices = 0;
    boundingBox_.Clear();

    for (unsigned i = 0; i < vertices_.Size(); ++i)
    {
        totalVertices += vertices_[i].Size();

        for (unsigned j = 0; j < vertices_[i].Size(); ++j)
            boundingBox_.Merge(vertices_[i][j].position_);
    }

    // Make sure world-space bounding box will be updated
    OnMarkedDirty(node_);

    // Resize (recreate) the vertex buffer only if necessary
    if (vertexBuffer_->GetVertexCount() != totalVertices || vertexBuffer_->GetElementMask() != elementMask_ ||
        vertexBuffer_->IsDynamic() != dynamic_)
        vertexBuffer_->SetSize(totalVertices, elementMask_, dynamic_);

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

                geometries_[i]->SetVertexBuffer(0, vertexBuffer_);
                geometries_[i]->SetDrawRange(primitiveTypes_[i], 0, 0, vertexStart, vertexCount);
                vertexStart += vertexCount;
            }

            vertexBuffer_->Unlock();
        }
        else
            URHO3D_LOGERROR("Failed to lock custom geometry vertex buffer");
    }
    else
    {
        for (unsigned i = 0; i < geometries_.Size(); ++i)
        {
            geometries_[i]->SetVertexBuffer(0, vertexBuffer_);
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
        URHO3D_LOGERROR("Material index out of bounds");
        return false;
    }

    batches_[index].material_ = material;
    MarkNetworkUpdate();
    return true;
}

unsigned CustomGeometry::GetNumVertices(unsigned index) const
{
    return index < vertices_.Size() ? vertices_[index].Size() : 0;
}

Material* CustomGeometry::GetMaterial(unsigned index) const
{
    return index < batches_.Size() ? batches_[index].material_ : (Material*)0;
}

CustomGeometryVertex* CustomGeometry::GetVertex(unsigned geometryIndex, unsigned vertexNum)
{
    return (geometryIndex < vertices_.Size() && vertexNum < vertices_[geometryIndex].Size()) ?
           &vertices_[geometryIndex][vertexNum] : (CustomGeometryVertex*)0;
}

void CustomGeometry::SetGeometryDataAttr(const PODVector<unsigned char>& value)
{
    if (value.Empty())
        return;

    MemoryBuffer buffer(value);

    SetNumGeometries(buffer.ReadVLE());
    elementMask_ = buffer.ReadUInt();

    for (unsigned i = 0; i < geometries_.Size(); ++i)
    {
        unsigned numVertices = buffer.ReadVLE();
        vertices_[i].Resize(numVertices);
        primitiveTypes_[i] = (PrimitiveType)buffer.ReadUByte();

        for (unsigned j = 0; j < numVertices; ++j)
        {
            if (elementMask_ & MASK_POSITION)
                vertices_[i][j].position_ = buffer.ReadVector3();
            if (elementMask_ & MASK_NORMAL)
                vertices_[i][j].normal_ = buffer.ReadVector3();
            if (elementMask_ & MASK_COLOR)
                vertices_[i][j].color_ = buffer.ReadUInt();
            if (elementMask_ & MASK_TEXCOORD1)
                vertices_[i][j].texCoord_ = buffer.ReadVector2();
            if (elementMask_ & MASK_TANGENT)
                vertices_[i][j].tangent_ = buffer.ReadVector4();
        }
    }

    Commit();
}

void CustomGeometry::SetMaterialsAttr(const ResourceRefList& value)
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    for (unsigned i = 0; i < value.names_.Size(); ++i)
        SetMaterial(i, cache->GetResource<Material>(value.names_[i]));
}

PODVector<unsigned char> CustomGeometry::GetGeometryDataAttr() const
{
    VectorBuffer ret;

    ret.WriteVLE(geometries_.Size());
    ret.WriteUInt(elementMask_);

    for (unsigned i = 0; i < geometries_.Size(); ++i)
    {
        unsigned numVertices = vertices_[i].Size();
        ret.WriteVLE(numVertices);
        ret.WriteUByte(primitiveTypes_[i]);

        for (unsigned j = 0; j < numVertices; ++j)
        {
            if (elementMask_ & MASK_POSITION)
                ret.WriteVector3(vertices_[i][j].position_);
            if (elementMask_ & MASK_NORMAL)
                ret.WriteVector3(vertices_[i][j].normal_);
            if (elementMask_ & MASK_COLOR)
                ret.WriteUInt(vertices_[i][j].color_);
            if (elementMask_ & MASK_TEXCOORD1)
                ret.WriteVector2(vertices_[i][j].texCoord_);
            if (elementMask_ & MASK_TANGENT)
                ret.WriteVector4(vertices_[i][j].tangent_);
        }
    }

    return ret.GetBuffer();
}

const ResourceRefList& CustomGeometry::GetMaterialsAttr() const
{
    materialsAttr_.names_.Resize(batches_.Size());
    for (unsigned i = 0; i < batches_.Size(); ++i)
        materialsAttr_.names_[i] = GetResourceName(batches_[i].material_);

    return materialsAttr_;
}

void CustomGeometry::OnWorldBoundingBoxUpdate()
{
    worldBoundingBox_ = boundingBox_.Transformed(node_->GetWorldTransform());
}

}
