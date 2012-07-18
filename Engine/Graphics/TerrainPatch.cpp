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
#include "Camera.h"
#include "Context.h"
#include "Geometry.h"
#include "IndexBuffer.h"
#include "Node.h"
#include "OcclusionBuffer.h"
#include "OctreeQuery.h"
#include "Terrain.h"
#include "TerrainPatch.h"
#include "VertexBuffer.h"

#include "DebugNew.h"

static const Vector3 DOT_SCALE(1 / 3.0f, 1 / 3.0f, 1 / 3.0f);
static const float LOD_CONSTANT = 1.0f;

OBJECTTYPESTATIC(TerrainPatch);

TerrainPatch::TerrainPatch(Context* context) :
    Drawable(context),
    geometry_(new Geometry(context)),
    vertexBuffer_(new VertexBuffer(context)),
    owner_(0),
    north_(0),
    south_(0),
    west_(0),
    east_(0),
    lodLevel_(0),
    lodDirty_(true)
{
    drawableFlags_ = DRAWABLE_GEOMETRY;
    
    geometry_->SetVertexBuffer(0, vertexBuffer_, MASK_POSITION | MASK_NORMAL | MASK_TEXCOORD1 | MASK_TANGENT);
    
    batches_.Resize(1);
    batches_[0].geometry_ = geometry_;
    batches_[0].geometryType_ = GEOM_STATIC_NOINSTANCING;
}

TerrainPatch::~TerrainPatch()
{
}

void TerrainPatch::ProcessRayQuery(const RayOctreeQuery& query, PODVector<RayQueryResult>& results)
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
                const void* indexData = geometry_->GetIndexBuffer() ? geometry_->GetIndexBuffer()->GetShadowData() : 0;
                if (indexData && cpuVertexData_)
                {
                    distance = localRay.HitDistance(cpuVertexData_.Get(), sizeof(Vector3), indexData, sizeof(unsigned short),
                        geometry_->GetIndexStart(), geometry_->GetIndexCount());
                    
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
        break;
    }
}

void TerrainPatch::UpdateBatches(const FrameInfo& frame)
{
    const Matrix3x4& worldTransform = node_->GetWorldTransform();
    distance_ = frame.camera_->GetDistance(GetWorldBoundingBox().Center());
    
    float scale = GetWorldBoundingBox().Size().DotProduct(DOT_SCALE);
    lodDistance_ = frame.camera_->GetLodDistance(distance_, scale, lodBias_);
    
    batches_[0].distance_ = distance_;
    batches_[0].worldTransform_ = &worldTransform;
    
    unsigned newLodLevel = 0;
    for (unsigned i = 0; i < lodErrors_.Size(); ++i)
    {
        if (lodErrors_[i] / lodDistance_ > LOD_CONSTANT)
            break;
        else
            newLodLevel = i;
    }
    
    if (newLodLevel != lodLevel_)
    {
        lodLevel_ = newLodLevel;
        lodDirty_ = true;
    }
}

void TerrainPatch::UpdateGeometry(const FrameInfo& frame)
{
    if (vertexBuffer_->IsDataLost())
        owner_->UpdatePatchGeometry(this);
    
    unsigned northLod = north_ ? north_->lodLevel_ : lodLevel_;
    unsigned southLod = south_ ? south_->lodLevel_ : lodLevel_;
    unsigned westLod = west_ ? west_->lodLevel_ : lodLevel_;
    unsigned eastLod = east_ ? east_->lodLevel_ : lodLevel_;
    
    owner_->UpdatePatchLOD(this, lodLevel_, northLod, southLod, westLod, eastLod);
    
    lodDirty_ = false;
}


unsigned TerrainPatch::GetNumOccluderTriangles()
{
    // Check that the material is suitable for occlusion (default material always is)
    Material* mat = batches_[0].material_;
    if (mat && !mat->GetOcclusion())
        return 0;
    else
        return geometry_->GetIndexCount() / 3;
}

bool TerrainPatch::DrawOcclusion(OcclusionBuffer* buffer)
{
    bool success = true;
    
    // Check that the material is suitable for occlusion (default material always is) and set culling mode
    Material* material = batches_[0].material_;
    if (material)
    {
        if (!material->GetOcclusion())
            return success;
        buffer->SetCullMode(material->GetCullMode());
    }
    else
        buffer->SetCullMode(CULL_CCW);
    
    const unsigned char* indexData = geometry_->GetIndexBuffer() ? geometry_->GetIndexBuffer()->GetShadowData() : 0;
    if (!indexData || !cpuVertexData_)
        return success;
    
    // Draw and check for running out of triangles
    if (!buffer->Draw(node_->GetWorldTransform(), cpuVertexData_.Get(), sizeof(Vector3), indexData, sizeof(unsigned short),
        geometry_->GetIndexStart(), geometry_->GetIndexCount()))
        success = false;
    
    return success;
}

UpdateGeometryType TerrainPatch::GetUpdateGeometryType()
{
    // If any of the neighbour patches have changed LOD, must update stitching
    if (vertexBuffer_->IsDataLost())
        return UPDATE_MAIN_THREAD;
    else if (lodDirty_ || (north_ && north_->lodDirty_) || (south_ && south_->lodDirty_) || (west_ && west_->lodDirty_) ||
        (east_ && east_->lodDirty_))
        return UPDATE_WORKER_THREAD;
    else
        return UPDATE_NONE;
}

void TerrainPatch::OnWorldBoundingBoxUpdate()
{
    worldBoundingBox_ = boundingBox_.Transformed(node_->GetWorldTransform());
}
