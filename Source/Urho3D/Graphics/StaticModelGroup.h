// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

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
    explicit StaticModelGroup(Context* context);
    /// Destruct.
    ~StaticModelGroup() override;
    /// Register object factory. StaticModel must be registered first.
    /// @nobind
    static void RegisterObject(Context* context);

    /// Apply attribute changes that can not be applied immediately. Called after scene load or a network update.
    void ApplyAttributes() override;
    /// Process octree raycast. May be called from a worker thread.
    void ProcessRayQuery(const RayOctreeQuery& query, PODVector<RayQueryResult>& results) override;
    /// Calculate distance and prepare batches for rendering. May be called from worker thread(s), possibly re-entrantly.
    void UpdateBatches(const FrameInfo& frame) override;
    /// Return number of occlusion geometry triangles.
    unsigned GetNumOccluderTriangles() override;
    /// Draw to occlusion buffer. Return true if did not run out of triangles.
    bool DrawOcclusion(OcclusionBuffer* buffer) override;

    /// Add an instance scene node. It does not need any drawable components of its own.
    void AddInstanceNode(Node* node);
    /// Remove an instance scene node.
    void RemoveInstanceNode(Node* node);
    /// Remove all instance scene nodes.
    void RemoveAllInstanceNodes();

    /// Return number of instance nodes.
    /// @property
    unsigned GetNumInstanceNodes() const { return instanceNodes_.Size(); }

    /// Return instance node by index.
    /// @property{get_instanceNodes}
    Node* GetInstanceNode(unsigned index) const;

    /// Set node IDs attribute.
    void SetNodeIDsAttr(const VariantVector& value);

    /// Return node IDs attribute.
    const VariantVector& GetNodeIDsAttr() const;

protected:
    /// Handle scene node enabled status changing.
    void OnNodeSetEnabled(Node* node) override;
    /// Recalculate the world-space bounding box.
    void OnWorldBoundingBoxUpdate() override;

private:
    /// Ensure proper size of world transforms when nodes are added/removed. Also mark node IDs dirty.
    void UpdateNumTransforms();
    /// Update node IDs attribute from the actual nodes.
    void UpdateNodeIDs() const;

    /// Instance nodes.
    Vector<WeakPtr<Node> > instanceNodes_;
    /// World transforms of valid (existing and visible) instances.
    PODVector<Matrix3x4> worldTransforms_;
    /// IDs of instance nodes for serialization.
    mutable VariantVector nodeIDsAttr_;
    /// Number of valid instance node transforms.
    unsigned numWorldTransforms_{};
    /// Whether node IDs have been set and nodes should be searched for during ApplyAttributes.
    mutable bool nodesDirty_{};
    /// Whether nodes have been manipulated by the API and node ID attribute should be refreshed.
    mutable bool nodeIDsDirty_{};
};

}
