// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include "../Precompiled.h"

#include "../Base/Utils.h"
#include "../Core/Context.h"
#include "../Core/Profiler.h"
#include "../Graphics/Batch.h"
#include "../Graphics/Camera.h"
#include "../Graphics/CustomGeometry.h"
#include "../Graphics/Geometry.h"
#include "../Graphics/Material.h"
#include "../Graphics/OcclusionBuffer.h"
#include "../Graphics/OctreeQuery.h"
#include "../GraphicsAPI/VertexBuffer.h"
#include "../IO/Log.h"
#include "../IO/MemoryBuffer.h"
#include "../Resource/ResourceCache.h"
#include "../Scene/Node.h"

#include "../DebugNew.h"

namespace Urho3D
{

extern const char* GEOMETRY_CATEGORY;

CustomGeometry::CustomGeometry(Context* context)
    : Drawable(context, DrawableTypes::Geometry)
    , vertexBuffer_(new VertexBuffer(context))
    , elementMask_(VertexElements::Position)
    , geometryIndex_(0)
    , materialsAttr_(Material::GetTypeStatic())
    , dynamic_(false)
{
    vertexBuffer_->SetShadowed(true);
    SetNumGeometries(1);
}

CustomGeometry::~CustomGeometry() = default;

void CustomGeometry::RegisterObject(Context* context)
{
    context->RegisterFactory<CustomGeometry>(GEOMETRY_CATEGORY);

    URHO3D_ACCESSOR_ATTRIBUTE("Is Enabled", IsEnabled, SetEnabled, true, AM_DEFAULT);
    URHO3D_ATTRIBUTE("Dynamic Vertex Buffer", dynamic_, false, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Geometry Data", GetGeometryDataAttr, SetGeometryDataAttr,
                                    Variant::emptyBuffer, AM_FILE | AM_NOEDIT);
    URHO3D_ACCESSOR_ATTRIBUTE("Materials", GetMaterialsAttr, SetMaterialsAttr,
                              ResourceRefList(Material::GetTypeStatic()), AM_DEFAULT);
    URHO3D_ATTRIBUTE("Is Occluder", occluder_, false, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Can Be Occluded", IsOccludee, SetOccludee, true, AM_DEFAULT);
    URHO3D_ATTRIBUTE("Cast Shadows", castShadows_, false, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Draw Distance", GetDrawDistance, SetDrawDistance, 0.0f, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Shadow Distance", GetShadowDistance, SetShadowDistance, 0.0f, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("LOD Bias", GetLodBias, SetLodBias, 1.0f, AM_DEFAULT);
    URHO3D_COPY_BASE_ATTRIBUTES(Drawable);
}

void CustomGeometry::ProcessRayQuery(const RayOctreeQuery& query, Vector<RayQueryResult>& results)
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

            for (i32 i = 0; i < batches_.Size(); ++i)
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
            result.subObject_ = NINDEX;
            results.Push(result);
        }
    }
    break;

    case RAY_TRIANGLE_UV:
        URHO3D_LOGWARNING("RAY_TRIANGLE_UV query level is not supported for CustomGeometry component");
        break;
    }
}

Geometry* CustomGeometry::GetLodGeometry(i32 batchIndex, i32 level)
{
    assert(batchIndex >= 0);
    assert(level >= 0 || level == NINDEX);

    return batchIndex < geometries_.Size() ? geometries_[batchIndex] : nullptr;
}

i32 CustomGeometry::GetNumOccluderTriangles()
{
    i32 triangles = 0;

    for (i32 i = 0; i < batches_.Size(); ++i)
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

        const byte* vertexData;
        i32 vertexSize;
        const byte* indexData;
        i32 indexSize;
        const Vector<VertexElement>* elements;

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
    elementMask_ = VertexElements::Position;
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
        elementMask_ = VertexElements::Position;
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
    elementMask_ |= VertexElements::Normal;
}

void CustomGeometry::DefineColor(const Color& color)
{
    if (vertices_.Size() < geometryIndex_ || vertices_[geometryIndex_].Empty())
        return;

    vertices_[geometryIndex_].Back().color_ = color.ToU32();
    elementMask_ |= VertexElements::Color;
}

void CustomGeometry::DefineTexCoord(const Vector2& texCoord)
{
    if (vertices_.Size() < geometryIndex_ || vertices_[geometryIndex_].Empty())
        return;

    vertices_[geometryIndex_].Back().texCoord_ = texCoord;
    elementMask_ |= VertexElements::TexCoord1;
}

void CustomGeometry::DefineTangent(const Vector4& tangent)
{
    if (vertices_.Size() < geometryIndex_ || vertices_[geometryIndex_].Empty())
        return;

    vertices_[geometryIndex_].Back().tangent_ = tangent;
    elementMask_ |= VertexElements::Tangent;
}

void CustomGeometry::DefineGeometry(unsigned index, PrimitiveType type, unsigned numVertices, bool hasNormals,
                                    bool hasColors, bool hasTexCoords, bool hasTangents)
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
        elementMask_ = VertexElements::Position;
    if (hasNormals)
        elementMask_ |= VertexElements::Normal;
    if (hasColors)
        elementMask_ |= VertexElements::Color;
    if (hasTexCoords)
        elementMask_ |= VertexElements::TexCoord1;
    if (hasTangents)
        elementMask_ |= VertexElements::Tangent;
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
        auto* dest = (unsigned char*)vertexBuffer_->Lock(0, totalVertices, true);
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

                    if (!!(elementMask_ & VertexElements::Normal))
                    {
                        *((Vector3*)dest) = vertices_[i][j].normal_;
                        dest += sizeof(Vector3);
                    }
                    if (!!(elementMask_ & VertexElements::Color))
                    {
                        *((unsigned*)dest) = vertices_[i][j].color_;
                        dest += sizeof(unsigned);
                    }
                    if (!!(elementMask_ & VertexElements::TexCoord1))
                    {
                        *((Vector2*)dest) = vertices_[i][j].texCoord_;
                        dest += sizeof(Vector2);
                    }
                    if (!!(elementMask_ & VertexElements::Tangent))
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
    return index < batches_.Size() ? batches_[index].material_ : nullptr;
}

CustomGeometryVertex* CustomGeometry::GetVertex(unsigned geometryIndex, unsigned vertexNum)
{
    return (geometryIndex < vertices_.Size() && vertexNum < vertices_[geometryIndex].Size())
               ? &vertices_[geometryIndex][vertexNum]
               : nullptr;
}

void CustomGeometry::SetGeometryDataAttr(const Vector<byte>& value)
{
    if (value.Empty())
        return;

    MemoryBuffer buffer(value);

    SetNumGeometries(buffer.ReadVLE());
    elementMask_ = VertexElements{buffer.ReadU32()};

    for (unsigned i = 0; i < geometries_.Size(); ++i)
    {
        unsigned numVertices = buffer.ReadVLE();
        vertices_[i].Resize(numVertices);
        primitiveTypes_[i] = (PrimitiveType)buffer.ReadU8();

        for (unsigned j = 0; j < numVertices; ++j)
        {
            if (!!(elementMask_ & VertexElements::Position))
                vertices_[i][j].position_ = buffer.ReadVector3();
            if (!!(elementMask_ & VertexElements::Normal))
                vertices_[i][j].normal_ = buffer.ReadVector3();
            if (!!(elementMask_ & VertexElements::Color))
                vertices_[i][j].color_ = buffer.ReadU32();
            if (!!(elementMask_ & VertexElements::TexCoord1))
                vertices_[i][j].texCoord_ = buffer.ReadVector2();
            if (!!(elementMask_ & VertexElements::Tangent))
                vertices_[i][j].tangent_ = buffer.ReadVector4();
        }
    }

    Commit();
}

void CustomGeometry::SetMaterialsAttr(const ResourceRefList& value)
{
    auto* cache = GetSubsystem<ResourceCache>();
    for (unsigned i = 0; i < value.names_.Size(); ++i)
        SetMaterial(i, cache->GetResource<Material>(value.names_[i]));
}

Vector<byte> CustomGeometry::GetGeometryDataAttr() const
{
    VectorBuffer ret;

    ret.WriteVLE(geometries_.Size());
    ret.WriteU32(ToU32(elementMask_));

    for (unsigned i = 0; i < geometries_.Size(); ++i)
    {
        unsigned numVertices = vertices_[i].Size();
        ret.WriteVLE(numVertices);
        ret.WriteU8(primitiveTypes_[i]);

        for (unsigned j = 0; j < numVertices; ++j)
        {
            if (!!(elementMask_ & VertexElements::Position))
                ret.WriteVector3(vertices_[i][j].position_);
            if (!!(elementMask_ & VertexElements::Normal))
                ret.WriteVector3(vertices_[i][j].normal_);
            if (!!(elementMask_ & VertexElements::Color))
                ret.WriteU32(vertices_[i][j].color_);
            if (!!(elementMask_ & VertexElements::TexCoord1))
                ret.WriteVector2(vertices_[i][j].texCoord_);
            if (!!(elementMask_ & VertexElements::Tangent))
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

} // namespace Urho3D
