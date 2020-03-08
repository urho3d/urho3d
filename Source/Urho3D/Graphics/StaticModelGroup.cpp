//
// Copyright (c) 2008-2020 the Urho3D project.
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
#include "../Graphics/Batch.h"
#include "../Graphics/Camera.h"
#include "../Graphics/Geometry.h"
#include "../Graphics/Material.h"
#include "../Graphics/OcclusionBuffer.h"
#include "../Graphics/OctreeQuery.h"
#include "../Graphics/StaticModelGroup.h"
#include "../Graphics/VertexBuffer.h"
#include "../Scene/Scene.h"

#include "../DebugNew.h"

namespace Urho3D
{

extern const char* GEOMETRY_CATEGORY;

static const StringVector instanceNodesStructureElementNames =
{
    "Instance Count",
    "   NodeID"
};

StaticModelGroup::StaticModelGroup(Context* context) :
    StaticModel(context)
{
    // Initialize the default node IDs attribute
    UpdateNodeIDs();
}

StaticModelGroup::~StaticModelGroup() = default;

void StaticModelGroup::RegisterObject(Context* context)
{
    context->RegisterFactory<StaticModelGroup>(GEOMETRY_CATEGORY);

    URHO3D_COPY_BASE_ATTRIBUTES(StaticModel);
    URHO3D_ACCESSOR_ATTRIBUTE("Instance Nodes", GetNodeIDsAttr, SetNodeIDsAttr,
        VariantVector, Variant::emptyVariantVector, AM_DEFAULT | AM_NODEIDVECTOR)
        .SetMetadata(AttributeMetadata::P_VECTOR_STRUCT_ELEMENTS, instanceNodesStructureElementNames);
}

void StaticModelGroup::ApplyAttributes()
{
    if (!nodesDirty_)
        return;

    // Remove all old instance nodes before searching for new
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

    worldTransforms_.Resize(instanceNodes_.Size());
    numWorldTransforms_ = 0; // Correct amount will be found during world bounding box update
    nodesDirty_ = false;

    OnMarkedDirty(GetNode());
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

    for (unsigned i = 0; i < numWorldTransforms_; ++i)
    {
        // Initial test using AABB
        float distance = query.ray_.HitDistance(boundingBox_.Transformed(worldTransforms_[i]));
        Vector3 normal = -query.ray_.direction_;

        // Then proceed to OBB and triangle-level tests if necessary
        if (level >= RAY_OBB && distance < query.maxDistance_)
        {
            Matrix3x4 inverse = worldTransforms_[i].Inverse();
            Ray localRay = query.ray_.Transformed(inverse);
            distance = localRay.HitDistance(boundingBox_);

            if (level == RAY_TRIANGLE && distance < query.maxDistance_)
            {
                distance = M_INFINITY;

                for (unsigned j = 0; j < batches_.Size(); ++j)
                {
                    Geometry* geometry = batches_[j].geometry_;
                    if (geometry)
                    {
                        Vector3 geometryNormal;
                        float geometryDistance = geometry->GetHitDistance(localRay, &geometryNormal);
                        if (geometryDistance < query.maxDistance_ && geometryDistance < distance)
                        {
                            distance = geometryDistance;
                            normal = (worldTransforms_[i] * Vector4(geometryNormal, 0.0f)).Normalized();
                        }
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
            batches_[i].worldTransform_ = numWorldTransforms_ ? &worldTransforms_[0] : &Matrix3x4::IDENTITY;
            batches_[i].numWorldTransforms_ = numWorldTransforms_;
        }
    }
    else if (batches_.Size() == 1)
    {
        batches_[0].distance_ = distance_;
        batches_[0].worldTransform_ = numWorldTransforms_ ? &worldTransforms_[0] : &Matrix3x4::IDENTITY;
        batches_[0].numWorldTransforms_ = numWorldTransforms_;
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

        triangles += numWorldTransforms_ * geometry->GetIndexCount() / 3;
    }

    return triangles;
}

bool StaticModelGroup::DrawOcclusion(OcclusionBuffer* buffer)
{
    // Make sure instance transforms are up-to-date
    GetWorldBoundingBox();

    for (unsigned i = 0; i < numWorldTransforms_; ++i)
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
            const PODVector<VertexElement>* elements;

            geometry->GetRawData(vertexData, vertexSize, indexData, indexSize, elements);
            // Check for valid geometry data
            if (!vertexData || !indexData || !elements || VertexBuffer::GetElementOffset(*elements, TYPE_VECTOR3, SEM_POSITION) != 0)
                continue;

            unsigned indexStart = geometry->GetIndexStart();
            unsigned indexCount = geometry->GetIndexCount();

            // Draw and check for running out of triangles
            if (!buffer->AddTriangles(worldTransforms_[i], vertexData, vertexSize, indexData, indexSize, indexStart, indexCount))
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
    UpdateNumTransforms();
}

void StaticModelGroup::RemoveInstanceNode(Node* node)
{
    if (!node)
        return;

    WeakPtr<Node> instanceWeak(node);
    Vector<WeakPtr<Node> >::Iterator i = instanceNodes_.Find(instanceWeak);
    if (i == instanceNodes_.End())
        return;

    node->RemoveListener(this);
    instanceNodes_.Erase(i);
    UpdateNumTransforms();
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
    UpdateNumTransforms();
}

Node* StaticModelGroup::GetInstanceNode(unsigned index) const
{
    return index < instanceNodes_.Size() ? instanceNodes_[index] : nullptr;
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

    nodesDirty_ = true;
    nodeIDsDirty_ = false;
}

const VariantVector& StaticModelGroup::GetNodeIDsAttr() const
{
    if (nodeIDsDirty_)
        UpdateNodeIDs();

    return nodeIDsAttr_;
}

void StaticModelGroup::OnNodeSetEnabled(Node* node)
{
    Drawable::OnMarkedDirty(node);
}

void StaticModelGroup::OnWorldBoundingBoxUpdate()
{
    // Update transforms and bounding box at the same time to have to go through the objects only once
    unsigned index = 0;

    BoundingBox worldBox;

    for (unsigned i = 0; i < instanceNodes_.Size(); ++i)
    {
        Node* node = instanceNodes_[i];
        if (!node || !node->IsEnabled())
            continue;

        const Matrix3x4& worldTransform = node->GetWorldTransform();
        worldTransforms_[index++] = worldTransform;
        worldBox.Merge(boundingBox_.Transformed(worldTransform));
    }

    worldBoundingBox_ = worldBox;

    // Store the amount of valid instances we found instead of resizing worldTransforms_. This is because this function may be
    // called from multiple worker threads simultaneously
    numWorldTransforms_ = index;
}

void StaticModelGroup::UpdateNumTransforms()
{
    worldTransforms_.Resize(instanceNodes_.Size());
    numWorldTransforms_ = 0; // Correct amount will be during world bounding box update
    nodeIDsDirty_ = true;

    OnMarkedDirty(GetNode());
    MarkNetworkUpdate();
}

void StaticModelGroup::UpdateNodeIDs() const
{
    unsigned numInstances = instanceNodes_.Size();

    nodeIDsAttr_.Clear();
    nodeIDsAttr_.Push(numInstances);

    for (unsigned i = 0; i < numInstances; ++i)
    {
        Node* node = instanceNodes_[i];
        nodeIDsAttr_.Push(node ? node->GetID() : 0);
    }

    nodeIDsDirty_ = false;
}

}
