//
// Copyright (c) 2008-2015 the Urho3D project.
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

#pragma once

#include "../Graphics/StaticModel.h"

namespace Urho3D
{

/// Renders several object instances while culling and receiving light as one unit. Can be used as a CPU-side optimization, but note that also regular StaticModels will use instanced rendering if possible.
class URHO3D_API StaticModelGroup : public StaticModel
{
    URHO3D_OBJECT(StaticModelGroup, StaticModel);

public:
    /// Construct.
    StaticModelGroup(Context* context);
    /// Destruct.
    virtual ~StaticModelGroup();
    /// Register object factory. StaticModel must be registered first.
    static void RegisterObject(Context* context);

    /// Apply attribute changes that can not be applied immediately. Called after scene load or a network update.
    void ApplyAttributes();
    /// Process octree raycast. May be called from a worker thread.
    virtual void ProcessRayQuery(const RayOctreeQuery& query, PODVector<RayQueryResult>& results);
    /// Calculate distance and prepare batches for rendering. May be called from worker thread(s), possibly re-entrantly.
    virtual void UpdateBatches(const FrameInfo& frame);
    /// Return number of occlusion geometry triangles.
    virtual unsigned GetNumOccluderTriangles();
    /// Draw to occlusion buffer. Return true if did not run out of triangles.
    virtual bool DrawOcclusion(OcclusionBuffer* buffer);

    /// Add an instance scene node. It does not need any drawable components of its own.
    void AddInstanceNode(Node* node);
    /// Remove an instance scene node.
    void RemoveInstanceNode(Node* node);
    /// Remove all instance scene nodes.
    void RemoveAllInstanceNodes();

    /// Return number of instance nodes.
    unsigned GetNumInstanceNodes() const { return instanceNodes_.Size(); }

    /// Return instance node by index.
    Node* GetInstanceNode(unsigned index) const;

    /// Set node IDs attribute.
    void SetNodeIDsAttr(const VariantVector& value);

    /// Return node IDs attribute.
    const VariantVector& GetNodeIDsAttr() const { return nodeIDsAttr_; }

protected:
    /// Handle scene node enabled status changing.
    virtual void OnNodeSetEnabled(Node* node);
    /// Recalculate the world-space bounding box.
    virtual void OnWorldBoundingBoxUpdate();

private:
    /// Update node IDs attribute and ensure the transforms vector has the right size.
    void UpdateNodeIDs();

    /// Instance nodes.
    Vector<WeakPtr<Node> > instanceNodes_;
    /// World transforms of valid (existing and visible) instances.
    PODVector<Matrix3x4> worldTransforms_;
    /// IDs of instance nodes for serialization.
    mutable VariantVector nodeIDsAttr_;
    /// Number of valid instance node transforms.
    unsigned numWorldTransforms_;
    /// Whether node IDs have been set and nodes should be searched for during ApplyAttributes.
    bool nodeIDsDirty_;
};

}
