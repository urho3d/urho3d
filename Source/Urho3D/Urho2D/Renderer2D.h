// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include "../Graphics/Drawable.h"
#include "../Math/Frustum.h"

namespace Urho3D
{

class Drawable2D;
class IndexBuffer;
class Material;
class Technique;
class VertexBuffer;
struct FrameInfo;
struct SourceBatch2D;

/// 2D view batch info.
/// @nobind
struct ViewBatchInfo2D
{
    /// Construct.
    ViewBatchInfo2D();

    /// Vertex buffer update frame number.
    unsigned vertexBufferUpdateFrameNumber_;
    /// Index count.
    unsigned indexCount_;
    /// Vertex count.
    unsigned vertexCount_;
    /// Vertex buffer.
    SharedPtr<VertexBuffer> vertexBuffer_;
    /// Batch updated frame number.
    unsigned batchUpdatedFrameNumber_;
    /// Source batches.
    PODVector<const SourceBatch2D*> sourceBatches_;
    /// Batch count.
    unsigned batchCount_;
    /// Distances.
    PODVector<float> distances_;
    /// Materials.
    Vector<SharedPtr<Material> > materials_;
    /// Geometries.
    Vector<SharedPtr<Geometry> > geometries_;
};

/// 2D renderer component.
class URHO3D_API Renderer2D : public Drawable
{
    URHO3D_OBJECT(Renderer2D, Drawable);

    friend void CheckDrawableVisibilityWork(const WorkItem* item, unsigned threadIndex);

public:
    /// Construct.
    explicit Renderer2D(Context* context);
    /// Destruct.
    ~Renderer2D() override;
    /// Register object factory.
    /// @nobind
    static void RegisterObject(Context* context);

    /// Process octree raycast. May be called from a worker thread.
    void ProcessRayQuery(const RayOctreeQuery& query, PODVector<RayQueryResult>& results) override;
    /// Calculate distance and prepare batches for rendering. May be called from worker thread(s), possibly re-entrantly.
    void UpdateBatches(const FrameInfo& frame) override;
    /// Prepare geometry for rendering. Called from a worker thread if possible (no GPU update).
    void UpdateGeometry(const FrameInfo& frame) override;
    /// Return whether a geometry update is necessary, and if it can happen in a worker thread.
    UpdateGeometryType GetUpdateGeometryType() override;

    /// Add Drawable2D.
    void AddDrawable(Drawable2D* drawable);
    /// Remove Drawable2D.
    void RemoveDrawable(Drawable2D* drawable);
    /// Return material by texture and blend mode.
    Material* GetMaterial(Texture2D* texture, BlendMode blendMode);

    /// Check visibility.
    bool CheckVisibility(Drawable2D* drawable) const;

private:
    /// Recalculate the world-space bounding box.
    void OnWorldBoundingBoxUpdate() override;
    /// Create material by texture and blend mode.
    SharedPtr<Material> CreateMaterial(Texture2D* texture, BlendMode blendMode);
    /// Handle view update begin event. Determine Drawable2D's and their batches here.
    void HandleBeginViewUpdate(StringHash eventType, VariantMap& eventData);
    /// Get all drawables in node.
    void GetDrawables(PODVector<Drawable2D*>& drawables, Node* node);
    /// Update view batch info.
    void UpdateViewBatchInfo(ViewBatchInfo2D& viewBatchInfo, Camera* camera);
    /// Add view batch.
    void AddViewBatch(ViewBatchInfo2D& viewBatchInfo, Material* material,
        unsigned indexStart, unsigned indexCount, unsigned vertexStart, unsigned vertexCount, float distance);

    /// Index buffer.
    SharedPtr<IndexBuffer> indexBuffer_;
    /// Material.
    SharedPtr<Material> material_;
    /// Drawables.
    PODVector<Drawable2D*> drawables_;
    /// View frame info for current frame.
    FrameInfo frame_;
    /// View batch info.
    HashMap<Camera*, ViewBatchInfo2D> viewBatchInfos_;
    /// Frustum for current frame.
    Frustum frustum_;
    /// View mask of current camera for visibility checking.
    unsigned viewMask_;
    /// Cached materials.
    HashMap<Texture2D*, HashMap<int, SharedPtr<Material> > > cachedMaterials_;
    /// Cached techniques per blend mode.
    HashMap<int, SharedPtr<Technique> > cachedTechniques_;
};

}
