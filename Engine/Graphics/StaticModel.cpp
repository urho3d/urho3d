//
// Urho3D Engine
// Copyright (c) 2008-2012 Lasse Öörni
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
#include "Geometry.h"
#include "Log.h"
#include "Material.h"
#include "Model.h"
#include "OcclusionBuffer.h"
#include "OctreeQuery.h"
#include "Profiler.h"
#include "ResourceCache.h"
#include "ResourceEvents.h"
#include "StaticModel.h"
#include "XMLElement.h"

#include "DebugNew.h"

static const Vector3 DOT_SCALE(1 / 3.0f, 1 / 3.0f, 1 / 3.0f);

OBJECTTYPESTATIC(StaticModel);

StaticModel::StaticModel(Context* context) :
    Drawable(context),
    softwareLodLevel_(M_MAX_UNSIGNED)
{
    drawableFlags_ = DRAWABLE_GEOMETRY;
}

StaticModel::~StaticModel()
{
}

void StaticModel::RegisterObject(Context* context)
{
    context->RegisterFactory<StaticModel>();
    
    ACCESSOR_ATTRIBUTE(StaticModel, VAR_RESOURCEREF, "Model", GetModelAttr, SetModelAttr, ResourceRef, ResourceRef(Model::GetTypeStatic()), AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(StaticModel, VAR_RESOURCEREFLIST, "Material", GetMaterialsAttr, SetMaterialsAttr, ResourceRefList, ResourceRefList(Material::GetTypeStatic()), AM_DEFAULT);
    ATTRIBUTE(StaticModel, VAR_BOOL, "Is Visible", visible_, true, AM_DEFAULT);
    ATTRIBUTE(StaticModel, VAR_BOOL, "Is Occluder", occluder_, false, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(StaticModel, VAR_BOOL, "Can Be Occluded", IsOccludee, SetOccludee, bool, true, AM_DEFAULT);
    ATTRIBUTE(StaticModel, VAR_BOOL, "Cast Shadows", castShadows_, false, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(StaticModel, VAR_FLOAT, "Draw Distance", GetDrawDistance, SetDrawDistance, float, 0.0f, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(StaticModel, VAR_FLOAT, "Shadow Distance", GetShadowDistance, SetShadowDistance, float, 0.0f, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(StaticModel, VAR_FLOAT, "LOD Bias", GetLodBias, SetLodBias, float, 1.0f, AM_DEFAULT);
    COPY_BASE_ATTRIBUTES(StaticModel, Drawable);
    ATTRIBUTE(StaticModel, VAR_INT, "Ray/Occl. LOD Level", softwareLodLevel_, M_MAX_UNSIGNED, AM_DEFAULT);
}

void StaticModel::ProcessRayQuery(const RayOctreeQuery& query, PODVector<RayQueryResult>& results)
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
            Matrix3x4 inverse(GetWorldTransform().Inverse());
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
            Matrix3x4 inverse(GetWorldTransform().Inverse());
            Ray localRay(inverse * query.ray_.origin_, inverse * Vector4(query.ray_.direction_, 0.0f));
            float distance = localRay.HitDistance(boundingBox_);
            if (distance <= query.maxDistance_)
            {
                // Then the actual test using triangle geometry
                for (unsigned i = 0; i < geometries_.Size(); ++i)
                {
                    unsigned lodLevel;
                    // Check whether to use same LOD as visible, or a specific LOD
                    if (softwareLodLevel_ == M_MAX_UNSIGNED)
                        lodLevel = lodLevels_[i];
                    else
                        lodLevel = Clamp(softwareLodLevel_, 0, geometries_[i].Size());
                    
                    Geometry* geom = geometries_[i][lodLevel];
                    if (geom)
                    {
                        distance = geom->GetDistance(localRay);
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

void StaticModel::UpdateDistance(const FrameInfo& frame)
{
    const Matrix3x4& worldTransform = node_->GetWorldTransform();
    distance_ = frame.camera_->GetDistance(worldTransform.Translation());
    
    for (unsigned i = 0; i < geometryCenters_.Size(); ++i)
        geometryDistances_[i] = frame.camera_->GetDistance(worldTransform * geometryCenters_[i]);
    
    float scale = GetWorldBoundingBox().Size().DotProduct(DOT_SCALE);
    float newLodDistance = frame.camera_->GetLodDistance(distance_, scale, lodBias_);
    
    if (newLodDistance != lodDistance_)
    {
        lodDistance_ = newLodDistance;
        CalculateLodLevels();
    }
}

unsigned StaticModel::GetNumBatches()
{
    return geometries_.Size();
}

void StaticModel::GetBatch(Batch& batch, const FrameInfo& frame, unsigned batchIndex)
{
    batch.distance_ = geometryDistances_[batchIndex];
    batch.geometry_ = currentGeometries_[batchIndex];
    batch.worldTransform_ = &node_->GetWorldTransform();
    batch.material_ = materials_[batchIndex];
}

unsigned StaticModel::GetNumOccluderTriangles()
{
    unsigned triangles = 0;
    
    for (unsigned i = 0; i < geometries_.Size(); ++i)
    {
        unsigned lodLevel;
        // Check whether to use same LOD as visible, or a specific LOD
        if (softwareLodLevel_ == M_MAX_UNSIGNED)
            lodLevel = lodLevels_[i];
        else
            lodLevel = Clamp(softwareLodLevel_, 0, geometries_[i].Size());
        
        Geometry* geom = geometries_[i][lodLevel];
        if (!geom)
            continue;
        
        // Check that the material is suitable for occlusion (default material always is)
        Material* mat = materials_[i];
        if (mat && !mat->GetOcclusion())
            continue;
        
        triangles += geom->GetIndexCount() / 3;
    }
    
    return triangles;
}

bool StaticModel::DrawOcclusion(OcclusionBuffer* buffer)
{
    bool success = true;
    
    for (unsigned i = 0; i < geometries_.Size(); ++i)
    {
        unsigned lodLevel;
        // Check whether to use same LOD as visible, or a specific LOD
        if (softwareLodLevel_ == M_MAX_UNSIGNED)
            lodLevel = lodLevels_[i];
        else
            lodLevel = Clamp(softwareLodLevel_, 0, geometries_[i].Size());
        
        Geometry* geom = geometries_[i][lodLevel];
        if (!geom)
            continue;
        
        // Check that the material is suitable for occlusion (default material always is)
        // and set culling mode
        Material* mat = materials_[i];
        if (mat)
        {
            if (!mat->GetOcclusion())
                continue;
            buffer->SetCullMode(mat->GetCullMode());
        }
        else
            buffer->SetCullMode(CULL_CCW);
        
        const unsigned char* vertexData;
        unsigned vertexSize;
        const unsigned char* indexData;
        unsigned indexSize;
        
        geom->GetRawData(vertexData, vertexSize, indexData, indexSize);
        // Check for valid geometry data
        if (!vertexData || !indexData)
            continue;
        
        unsigned indexStart = geom->GetIndexStart();
        unsigned indexCount = geom->GetIndexCount();
        
        // Draw and check for running out of triangles
        if (!buffer->Draw(GetWorldTransform(), vertexData, vertexSize, indexData, indexSize, indexStart, indexCount))
            success = false;
        
        if (!success)
            break;
    }
    
    return success;
}

void StaticModel::SetModel(Model* model)
{
    if (!model || model == model_)
        return;
    
    // Unsubscribe from the reload event of previous model (if any), then subscribe to the new
    if (model_)
        UnsubscribeFromEvent(model_, E_RELOADFINISHED);
    if (model)
        SubscribeToEvent(model, E_RELOADFINISHED, HANDLER(StaticModel, HandleModelReloadFinished));
    
    model_ = model;
    
    // Copy the subgeometry & LOD level structure
    SetNumGeometries(model->GetNumGeometries());
    const Vector<Vector<SharedPtr<Geometry> > >& geometries = model->GetGeometries();
    for (unsigned i = 0; i < geometries.Size(); ++i)
        geometries_[i] = geometries[i];
    geometryCenters_ = model->GetGeometryCenters();
    geometryDistances_.Resize(geometryCenters_.Size());
    
    SetBoundingBox(model->GetBoundingBox());
    ResetLodLevels();
    MarkNetworkUpdate();
}

void StaticModel::SetMaterial(Material* material)
{
    for (unsigned i = 0; i < materials_.Size(); ++i)
        materials_[i] = material;
    
    MarkNetworkUpdate();
}

bool StaticModel::SetMaterial(unsigned index, Material* material)
{
    if (index >= materials_.Size())
    {
        LOGERROR("Material index out of bounds");
        return false;
    }
    
    materials_[index] = material;
    MarkNetworkUpdate();
    return true;
}

void StaticModel::SetSoftwareLodLevel(unsigned level)
{
    softwareLodLevel_ = level;
    MarkNetworkUpdate();
}

Material* StaticModel::GetMaterial(unsigned index) const
{
    return index < materials_.Size() ? materials_[index] : (Material*)0;
}

void StaticModel::SetBoundingBox(const BoundingBox& box)
{
    boundingBox_ = box;
    OnMarkedDirty(node_);
}

void StaticModel::SetNumGeometries(unsigned num)
{
    geometries_.Resize(num);
    materials_.Resize(num);
    ResetLodLevels();
}

void StaticModel::SetModelAttr(ResourceRef value)
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    SetModel(cache->GetResource<Model>(value.id_));
}

void StaticModel::SetMaterialsAttr(ResourceRefList value)
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    for (unsigned i = 0; i < value.ids_.Size(); ++i)
        SetMaterial(i, cache->GetResource<Material>(value.ids_[i]));
}

ResourceRef StaticModel::GetModelAttr() const
{
    return GetResourceRef(model_, Model::GetTypeStatic());
}

ResourceRefList StaticModel::GetMaterialsAttr() const
{
    return GetResourceRefList(materials_);
}

void StaticModel::OnWorldBoundingBoxUpdate()
{
    worldBoundingBox_ = boundingBox_.Transformed(GetWorldTransform());
}

void StaticModel::ResetLodLevels()
{
    // Ensure that each subgeometry has at least one LOD level, and reset the current LOD level
    lodLevels_.Resize(geometries_.Size());
    currentGeometries_.Resize(geometries_.Size());
    for (unsigned i = 0; i < geometries_.Size(); ++i)
    {
        if (!geometries_[i].Size())
            geometries_[i].Resize(1);
        lodLevels_[i] = 0;
        currentGeometries_[i] = geometries_[i][0];
    }
    
    // Find out the real LOD levels on next geometry update
    lodDistance_ = M_INFINITY;
}

void StaticModel::CalculateLodLevels()
{
    for (unsigned i = 0; i < geometries_.Size(); ++i)
    {
        unsigned j;
        for (j = 1; j < geometries_[i].Size(); ++j)
        {
            if (geometries_[i][j] && lodDistance_ <= geometries_[i][j]->GetLodDistance())
                break;
        }
        lodLevels_[i] = j - 1;
        currentGeometries_[i] = geometries_[i][lodLevels_[i]];
    }
}

void StaticModel::HandleModelReloadFinished(StringHash eventType, VariantMap& eventData)
{
    Model* currentModel = model_;
    model_ = 0; // Set null to allow to be re-set
    SetModel(currentModel);
}
