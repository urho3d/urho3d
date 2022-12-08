// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include "../Precompiled.h"

#include "../Core/Context.h"
#include "../Core/Profiler.h"
#include "../Graphics/AnimatedModel.h"
#include "../Graphics/Batch.h"
#include "../Graphics/Camera.h"
#include "../Graphics/Geometry.h"
#include "../Graphics/Material.h"
#include "../Graphics/OcclusionBuffer.h"
#include "../Graphics/OctreeQuery.h"
#include "../GraphicsAPI/VertexBuffer.h"
#include "../IO/FileSystem.h"
#include "../IO/Log.h"
#include "../Resource/ResourceCache.h"
#include "../Resource/ResourceEvents.h"

#include "../DebugNew.h"

namespace Urho3D
{

extern const char* GEOMETRY_CATEGORY;

StaticModel::StaticModel(Context* context) :
    Drawable(context, DrawableTypes::Geometry),
    occlusionLodLevel_(NINDEX),
    materialsAttr_(Material::GetTypeStatic())
{
}

StaticModel::~StaticModel() = default;

void StaticModel::RegisterObject(Context* context)
{
    context->RegisterFactory<StaticModel>(GEOMETRY_CATEGORY);

    URHO3D_ACCESSOR_ATTRIBUTE("Is Enabled", IsEnabled, SetEnabled, true, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Model", GetModelAttr, SetModelAttr, ResourceRef(Model::GetTypeStatic()), AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Material", GetMaterialsAttr, SetMaterialsAttr, ResourceRefList(Material::GetTypeStatic()),
        AM_DEFAULT);
    URHO3D_ATTRIBUTE("Is Occluder", occluder_, false, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Can Be Occluded", IsOccludee, SetOccludee, true, AM_DEFAULT);
    URHO3D_ATTRIBUTE("Cast Shadows", castShadows_, false, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Draw Distance", GetDrawDistance, SetDrawDistance, 0.0f, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Shadow Distance", GetShadowDistance, SetShadowDistance, 0.0f, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("LOD Bias", GetLodBias, SetLodBias, 1.0f, AM_DEFAULT);
    URHO3D_COPY_BASE_ATTRIBUTES(Drawable);
    URHO3D_ATTRIBUTE("Occlusion LOD Level", occlusionLodLevel_, NINDEX, AM_DEFAULT);
}

void StaticModel::ProcessRayQuery(const RayOctreeQuery& query, Vector<RayQueryResult>& results)
{
    RayQueryLevel level = query.level_;

    switch (level)
    {
    case RAY_AABB:
        Drawable::ProcessRayQuery(query, results);
        break;

    case RAY_OBB:
    case RAY_TRIANGLE:
    case RAY_TRIANGLE_UV:
        Matrix3x4 inverse(node_->GetWorldTransform().Inverse());
        Ray localRay = query.ray_.Transformed(inverse);
        float distance = localRay.HitDistance(boundingBox_);
        Vector3 normal = -query.ray_.direction_;
        Vector2 geometryUV;
        i32 hitBatch = NINDEX;

        if (level >= RAY_TRIANGLE && distance < query.maxDistance_)
        {
            distance = M_INFINITY;

            for (i32 i = 0; i < batches_.Size(); ++i)
            {
                Geometry* geometry = batches_[i].geometry_;
                if (geometry)
                {
                    Vector3 geometryNormal;
                    float geometryDistance = level == RAY_TRIANGLE ? geometry->GetHitDistance(localRay, &geometryNormal) :
                        geometry->GetHitDistance(localRay, &geometryNormal, &geometryUV);
                    if (geometryDistance < query.maxDistance_ && geometryDistance < distance)
                    {
                        distance = geometryDistance;
                        normal = (node_->GetWorldTransform() * Vector4(geometryNormal, 0.0f)).Normalized();
                        hitBatch = i;
                    }
                }
            }
        }

        if (distance < query.maxDistance_)
        {
            RayQueryResult result;
            result.position_ = query.ray_.origin_ + distance * query.ray_.direction_;
            result.normal_ = normal;
            result.textureUV_ = geometryUV;
            result.distance_ = distance;
            result.drawable_ = this;
            result.node_ = node_;
            result.subObject_ = hitBatch;
            results.Push(result);
        }
        break;
    }
}

void StaticModel::UpdateBatches(const FrameInfo& frame)
{
    const BoundingBox& worldBoundingBox = GetWorldBoundingBox();
    distance_ = frame.camera_->GetDistance(worldBoundingBox.Center());

    if (batches_.Size() == 1)
        batches_[0].distance_ = distance_;
    else
    {
        const Matrix3x4& worldTransform = node_->GetWorldTransform();
        for (unsigned i = 0; i < batches_.Size(); ++i)
            batches_[i].distance_ = frame.camera_->GetDistance(worldTransform * geometryData_[i].center_);
    }

    float scale = worldBoundingBox.Size().DotProduct(DOT_SCALE);
    float newLodDistance = frame.camera_->GetLodDistance(distance_, scale, lodBias_);

    if (newLodDistance != lodDistance_)
    {
        lodDistance_ = newLodDistance;
        CalculateLodLevels();
    }
}

Geometry* StaticModel::GetLodGeometry(i32 batchIndex, i32 level)
{
    assert(batchIndex >= 0);
    assert(level >= 0 || level == NINDEX);

    if (batchIndex >= geometries_.Size())
        return nullptr;

    // If level is out of range, use visible geometry
    if (level >= 0 && level < geometries_[batchIndex].Size())
        return geometries_[batchIndex][level];
    else
        return batches_[batchIndex].geometry_;
}

i32 StaticModel::GetNumOccluderTriangles()
{
    i32 triangles = 0;

    for (i32 i = 0; i < batches_.Size(); ++i)
    {
        Geometry* geometry = GetLodGeometry(i, occlusionLodLevel_);
        if (!geometry)
            continue;

        // Check that the material is suitable for occlusion (default material always is)
        Material* mat = batches_[i].material_;
        if (mat && !mat->GetOcclusion())
            continue;

        triangles += geometry->GetIndexCount() / 3;
    }

    return triangles;
}

bool StaticModel::DrawOcclusion(OcclusionBuffer* buffer)
{
    for (unsigned i = 0; i < batches_.Size(); ++i)
    {
        Geometry* geometry = GetLodGeometry(i, occlusionLodLevel_);
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
        if (!vertexData || !indexData || !elements || VertexBuffer::GetElementOffset(*elements, TYPE_VECTOR3, SEM_POSITION) != 0)
            continue;

        unsigned indexStart = geometry->GetIndexStart();
        unsigned indexCount = geometry->GetIndexCount();

        // Draw and check for running out of triangles
        if (!buffer->AddTriangles(node_->GetWorldTransform(), vertexData, vertexSize, indexData, indexSize, indexStart, indexCount))
            return false;
    }

    return true;
}

void StaticModel::SetModel(Model* model)
{
    if (model == model_)
        return;

    if (!node_)
    {
        URHO3D_LOGERROR("Can not set model while model component is not attached to a scene node");
        return;
    }

    // Unsubscribe from the reload event of previous model (if any), then subscribe to the new
    if (model_)
        UnsubscribeFromEvent(model_, E_RELOADFINISHED);

    model_ = model;

    if (model)
    {
        SubscribeToEvent(model, E_RELOADFINISHED, URHO3D_HANDLER(StaticModel, HandleModelReloadFinished));

        // Copy the subgeometry & LOD level structure
        SetNumGeometries(model->GetNumGeometries());
        const Vector<Vector<SharedPtr<Geometry>>>& geometries = model->GetGeometries();
        const Vector<Vector3>& geometryCenters = model->GetGeometryCenters();
        const Matrix3x4* worldTransform = node_ ? &node_->GetWorldTransform() : nullptr;
        for (unsigned i = 0; i < geometries.Size(); ++i)
        {
            batches_[i].worldTransform_ = worldTransform;
            geometries_[i] = geometries[i];
            geometryData_[i].center_ = geometryCenters[i];
        }

        SetBoundingBox(model->GetBoundingBox());
        ResetLodLevels();
    }
    else
    {
        SetNumGeometries(0);
        SetBoundingBox(BoundingBox());
    }

    MarkNetworkUpdate();
}

void StaticModel::SetMaterial(Material* material)
{
    for (unsigned i = 0; i < batches_.Size(); ++i)
        batches_[i].material_ = material;

    MarkNetworkUpdate();
}

bool StaticModel::SetMaterial(unsigned index, Material* material)
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

void StaticModel::SetOcclusionLodLevel(i32 level)
{
    assert(level >= 0 || level == NINDEX);

    occlusionLodLevel_ = level;
    MarkNetworkUpdate();
}

void StaticModel::ApplyMaterialList(const String& fileName)
{
    String useFileName = fileName;
    if (useFileName.Trimmed().Empty() && model_)
        useFileName = ReplaceExtension(model_->GetName(), ".txt");

    auto* cache = GetSubsystem<ResourceCache>();
    SharedPtr<File> file = cache->GetFile(useFileName, false);
    if (!file)
        return;

    unsigned index = 0;
    while (!file->IsEof() && index < batches_.Size())
    {
        auto* material = cache->GetResource<Material>(file->ReadLine());
        if (material)
            SetMaterial(index, material);

        ++index;
    }
}

Material* StaticModel::GetMaterial(unsigned index) const
{
    return index < batches_.Size() ? batches_[index].material_ : nullptr;
}

bool StaticModel::IsInside(const Vector3& point) const
{
    if (!node_)
        return false;

    Vector3 localPosition = node_->GetWorldTransform().Inverse() * point;
    return IsInsideLocal(localPosition);
}

bool StaticModel::IsInsideLocal(const Vector3& point) const
{
    // Early-out if point is not inside bounding box
    if (boundingBox_.IsInside(point) == OUTSIDE)
        return false;

    Ray localRay(point, Vector3(1.0f, -1.0f, 1.0f));

    for (unsigned i = 0; i < batches_.Size(); ++i)
    {
        Geometry* geometry = batches_[i].geometry_;
        if (geometry)
        {
            if (geometry->IsInside(localRay))
                return true;
        }
    }

    return false;
}

void StaticModel::SetBoundingBox(const BoundingBox& box)
{
    boundingBox_ = box;
    OnMarkedDirty(node_);
}

void StaticModel::SetNumGeometries(unsigned num)
{
    batches_.Resize(num);
    geometries_.Resize(num);
    geometryData_.Resize(num);
    ResetLodLevels();
}

void StaticModel::SetModelAttr(const ResourceRef& value)
{
    auto* cache = GetSubsystem<ResourceCache>();
    SetModel(cache->GetResource<Model>(value.name_));
}

void StaticModel::SetMaterialsAttr(const ResourceRefList& value)
{
    auto* cache = GetSubsystem<ResourceCache>();
    for (unsigned i = 0; i < value.names_.Size(); ++i)
        SetMaterial(i, cache->GetResource<Material>(value.names_[i]));
}

ResourceRef StaticModel::GetModelAttr() const
{
    return GetResourceRef(model_, Model::GetTypeStatic());
}

const ResourceRefList& StaticModel::GetMaterialsAttr() const
{
    materialsAttr_.names_.Resize(batches_.Size());
    for (unsigned i = 0; i < batches_.Size(); ++i)
        materialsAttr_.names_[i] = GetResourceName(GetMaterial(i));

    return materialsAttr_;
}

void StaticModel::OnWorldBoundingBoxUpdate()
{
    worldBoundingBox_ = boundingBox_.Transformed(node_->GetWorldTransform());
}

void StaticModel::ResetLodLevels()
{
    // Ensure that each subgeometry has at least one LOD level, and reset the current LOD level
    for (unsigned i = 0; i < batches_.Size(); ++i)
    {
        if (!geometries_[i].Size())
            geometries_[i].Resize(1);
        batches_[i].geometry_ = geometries_[i][0];
        geometryData_[i].lodLevel_ = 0;
    }

    // Find out the real LOD levels on next geometry update
    lodDistance_ = M_INFINITY;
}

void StaticModel::CalculateLodLevels()
{
    for (unsigned i = 0; i < batches_.Size(); ++i)
    {
        const Vector<SharedPtr<Geometry>>& batchGeometries = geometries_[i];
        // If only one LOD geometry, no reason to go through the LOD calculation
        if (batchGeometries.Size() <= 1)
            continue;

        unsigned j;

        for (j = 1; j < batchGeometries.Size(); ++j)
        {
            if (batchGeometries[j] && lodDistance_ <= batchGeometries[j]->GetLodDistance())
                break;
        }

        unsigned newLodLevel = j - 1;
        if (geometryData_[i].lodLevel_ != newLodLevel)
        {
            geometryData_[i].lodLevel_ = newLodLevel;
            batches_[i].geometry_ = batchGeometries[newLodLevel];
        }
    }
}

void StaticModel::HandleModelReloadFinished(StringHash eventType, VariantMap& eventData)
{
    Model* currentModel = model_;
    model_.Reset(); // Set null to allow to be re-set
    SetModel(currentModel);
}

}
