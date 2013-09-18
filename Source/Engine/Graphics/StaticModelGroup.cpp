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
#include "Batch.h"
#include "Camera.h"
#include "Context.h"
#include "Geometry.h"
#include "Material.h"
#include "OcclusionBuffer.h"
#include "OctreeQuery.h"
#include "Scene.h"
#include "StaticModelGroup.h"

#include "DebugNew.h"

namespace Urho3D
{

extern const char* GEOMETRY_CATEGORY;

StaticModelGroup::StaticModelGroup(Context* context) :
    StaticModel(context),
    nodeIDsDirty_(false)
{
    // Initialize the default node IDs attribute
    nodeIDsAttr_.Push(0);
}

StaticModelGroup::~StaticModelGroup()
{
}

void StaticModelGroup::RegisterObject(Context* context)
{
    context->RegisterFactory<StaticModelGroup>(GEOMETRY_CATEGORY);

    COPY_BASE_ATTRIBUTES(StaticModelGroup, StaticModel);
    REF_ACCESSOR_ATTRIBUTE(StaticModelGroup, VAR_VARIANTVECTOR, "Instance Nodes", GetNodeIDsAttr, SetNodeIDsAttr, VariantVector, Variant::emptyVariantVector, AM_DEFAULT | AM_NODEIDVECTOR);
}

void StaticModelGroup::ApplyAttributes()
{
    if (!nodeIDsDirty_)
        return;
    
    // Remove all old instance nodes before searching for new. Can not call RemoveAllInstances() as that would modify
    // the ID list on its own
    for (unsigned i = 0; i < instanceNodes_.Size(); ++i)
    {
        Node* node = instanceNodes_[i];
        if (node)
            node->RemoveListener(this);
    }
    instanceNodes_.Clear();
    
    Scene* scene = GetScene();
    
    if (scene)
    {
        // The first index stores the number of IDs redundantly. This is for editing
        for (unsigned i = 1; i < nodeIDsAttr_.Size(); ++i)
        {
            Node* node = scene->GetNode(nodeIDsAttr_[i].GetUInt());
            if (node)
            {
                WeakPtr<Node> instanceWeak(node);
                node->AddListener(this);
                instanceNodes_.Push(instanceWeak);
            }
        }
    }
    
    OnMarkedDirty(GetNode());
    nodeIDsDirty_ = false;
}

void StaticModelGroup::ProcessRayQuery(const RayOctreeQuery& query, PODVector<RayQueryResult>& results)
{
    // If no bones or no bone-level testing, use the Drawable test
    RayQueryLevel level = query.level_;
    if (level < RAY_AABB)
    {
        Drawable::ProcessRayQuery(query, results);
        return;
    }

    // Check ray hit distance to AABB before proceeding with more accurate tests
    // GetWorldBoundingBox() updates the world transforms
    if (query.ray_.HitDistance(GetWorldBoundingBox()) >= query.maxDistance_)
        return;
    
    for (unsigned i = 0; i < worldTransforms_.Size(); ++i)
    {
        // Initial test using AABB
        float distance = query.ray_.HitDistance(boundingBox_.Transformed(worldTransforms_[i]));
        if (distance >= query.maxDistance_)
            continue;
        // Then proceed to OBB and triangle-level tests if necessary
        if (level >= RAY_OBB)
        {
            Matrix3x4 inverse = worldTransforms_[i].Inverse();
            Ray localRay = query.ray_.Transformed(inverse);
            distance = localRay.HitDistance(boundingBox_);
            if (distance >= query.maxDistance_)
                continue;
            if (level == RAY_TRIANGLE)
            {
                distance = M_INFINITY;
                
                for (unsigned i = 0; i < batches_.Size(); ++i)
                {
                    Geometry* geometry = batches_[i].geometry_;
                    if (geometry)
                    {
                        distance = geometry->GetHitDistance(localRay);
                        if (distance < query.maxDistance_)
                            break;
                    }
                }
            }
        }
        
        if (distance < query.maxDistance_)
        {
            RayQueryResult result;
            result.drawable_ = this;
            result.node_ = node_;
            result.distance_ = distance;
            result.subObject_ = i;
            results.Push(result);
        }
    }
}

void StaticModelGroup::UpdateBatches(const FrameInfo& frame)
{
    // Getting the world bounding box ensures the transforms are updated
    const BoundingBox& worldBoundingBox = GetWorldBoundingBox();
    const Matrix3x4& worldTransform = node_->GetWorldTransform();
    distance_ = frame.camera_->GetDistance(worldBoundingBox.Center());
    
    if (batches_.Size() > 1)
    {
        for (unsigned i = 0; i < batches_.Size(); ++i)
        {
            batches_[i].distance_ = frame.camera_->GetDistance(worldTransform * geometryData_[i].center_);
            batches_[i].worldTransform_ = worldTransforms_.Size() ? &worldTransforms_[0] : &Matrix3x4::IDENTITY;
            batches_[i].numWorldTransforms_ = worldTransforms_.Size();
        }
    }
    else if (batches_.Size() == 1)
    {
        batches_[0].distance_ = distance_;
        batches_[0].worldTransform_ = worldTransforms_.Size() ? &worldTransforms_[0] : &Matrix3x4::IDENTITY;
        batches_[0].numWorldTransforms_ = worldTransforms_.Size();
    }
    
    float scale = worldBoundingBox.Size().DotProduct(DOT_SCALE);
    float newLodDistance = frame.camera_->GetLodDistance(distance_, scale, lodBias_);
    
    if (newLodDistance != lodDistance_)
    {
        lodDistance_ = newLodDistance;
        CalculateLodLevels();
    }
}

unsigned StaticModelGroup::GetNumOccluderTriangles()
{
    // Make sure instance transforms are up-to-date
    GetWorldBoundingBox();
    
    unsigned triangles = 0;
    
    for (unsigned i = 0; i < batches_.Size(); ++i)
    {
        Geometry* geometry = GetLodGeometry(i, occlusionLodLevel_);
        if (!geometry)
            continue;
        
        // Check that the material is suitable for occlusion (default material always is)
        Material* mat = batches_[i].material_;
        if (mat && !mat->GetOcclusion())
            continue;
        
        triangles += worldTransforms_.Size() * geometry->GetIndexCount() / 3;
    }
    
    return triangles;
}

bool StaticModelGroup::DrawOcclusion(OcclusionBuffer* buffer)
{
    // Make sure instance transforms are up-to-date
    GetWorldBoundingBox();
    
    for (unsigned i = 0; i < worldTransforms_.Size(); ++i)
    {
        for (unsigned j = 0; j < batches_.Size(); ++j)
        {
            Geometry* geometry = GetLodGeometry(j, occlusionLodLevel_);
            if (!geometry)
                continue;
            
            // Check that the material is suitable for occlusion (default material always is) and set culling mode
            Material* material = batches_[j].material_;
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
            if (!vertexData || !indexData)
                continue;
            
            unsigned indexStart = geometry->GetIndexStart();
            unsigned indexCount = geometry->GetIndexCount();
            
            // Draw and check for running out of triangles
            if (!buffer->Draw(worldTransforms_[i], vertexData, vertexSize, indexData, indexSize, indexStart, indexCount))
                return false;
        }
    }
    
    return true;
}

void StaticModelGroup::AddInstanceNode(Node* node)
{
    if (!node)
        return;

    WeakPtr<Node> instanceWeak(node);
    if (instanceNodes_.Contains(instanceWeak))
        return;
    
    // Add as a listener for the instance node, so that we know to dirty the transforms when the node moves or is enabled/disabled
    node->AddListener(this);
    instanceNodes_.Push(instanceWeak);
    
    OnMarkedDirty(GetNode());
    UpdateNodeIDs();
    MarkNetworkUpdate();
}

void StaticModelGroup::RemoveInstanceNode(Node* node)
{
    if (!node)
        return;

    WeakPtr<Node> instanceWeak(node);
    node->RemoveListener(this);
    instanceNodes_.Remove(instanceWeak);
    
    OnMarkedDirty(GetNode());
    UpdateNodeIDs();
    MarkNetworkUpdate();
}

void StaticModelGroup::RemoveAllInstanceNodes()
{
    for (unsigned i = 0; i < instanceNodes_.Size(); ++i)
    {
        Node* node = instanceNodes_[i];
        if (node)
            node->RemoveListener(this);
    }
    
    instanceNodes_.Clear();
    OnMarkedDirty(GetNode());
    UpdateNodeIDs();
    MarkNetworkUpdate();
}

Node* StaticModelGroup::GetInstanceNode(unsigned index) const
{
    return index < instanceNodes_.Size() ? instanceNodes_[index] : (Node*)0;
}

void StaticModelGroup::SetNodeIDsAttr(const VariantVector& value)
{
    // Just remember the node IDs. They need to go through the SceneResolver, and we actually find the nodes during
    // ApplyAttributes()
    if (value.Size())
    {
        nodeIDsAttr_.Clear();
        
        unsigned index = 0;
        unsigned numInstances = value[index++].GetUInt();
        // Prevent crash on entering negative value in the editor
        if (numInstances > M_MAX_INT)
            numInstances = 0;
        
        nodeIDsAttr_.Push(numInstances);
        while (numInstances--)
        {
            // If vector contains less IDs than should, fill the rest with zeroes
            if (index < value.Size())
                nodeIDsAttr_.Push(value[index++].GetUInt());
            else
                nodeIDsAttr_.Push(0);
        }
    }
    else
    {
        nodeIDsAttr_.Clear();
        nodeIDsAttr_.Push(0);
    }
    nodeIDsDirty_ = true;
}

void StaticModelGroup::OnNodeSetEnabled(Node* node)
{
    Drawable::OnMarkedDirty(node);
}

void StaticModelGroup::OnWorldBoundingBoxUpdate()
{
    // Update transforms and bounding box at the same time to have to go through the objects only once
    worldBoundingBox_.defined_ = false;
    worldTransforms_.Resize(instanceNodes_.Size());
    unsigned index = 0;

    for (unsigned i = 0; i < instanceNodes_.Size(); ++i)
    {
        Node* node = instanceNodes_[i];
        if (!node || !node->IsEnabled())
            continue;
        
        const Matrix3x4& worldTransform = node->GetWorldTransform();
        worldTransforms_[index++] = worldTransform;
        worldBoundingBox_.Merge(boundingBox_.Transformed(worldTransform));
    }
    
    worldTransforms_.Resize(index);
}

void StaticModelGroup::UpdateNodeIDs()
{
    nodeIDsAttr_.Clear();
    nodeIDsAttr_.Push(instanceNodes_.Size());
    
    for (unsigned i = 0; i < instanceNodes_.Size(); ++i)
    {
        Node* node = instanceNodes_[i];
        nodeIDsAttr_.Push(node ? node->GetID() : 0);
    }
}

}
