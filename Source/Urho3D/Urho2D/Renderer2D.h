//
// Copyright (c) 2008-2014 the Urho3D project.
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

#include "../Graphics/Drawable.h"

namespace Urho3D
{

class Drawable2D;
class IndexBuffer;
class Material;
class VertexBuffer;
struct FrameInfo;

/// 2D renderer components.
class URHO3D_API Renderer2D : public Drawable
{
    OBJECT(Renderer2D);

    friend void CheckDrawableVisibility(const WorkItem* item, unsigned threadIndex);

public:
    /// Construct.
    Renderer2D(Context* context);
    /// Destruct.
    ~Renderer2D();
    /// Register object factory.
    static void RegisterObject(Context* context);

    /// Process octree raycast. May be called from a worker thread.
    virtual void ProcessRayQuery(const RayOctreeQuery& query, PODVector<RayQueryResult>& results);
    /// Calculate distance and prepare batches for rendering. May be called from worker thread(s), possibly re-entrantly.
    virtual void UpdateBatches(const FrameInfo& frame);
    /// Prepare geometry for rendering. Called from a worker thread if possible (no GPU update.)
    virtual void UpdateGeometry(const FrameInfo& frame);
    /// Return whether a geometry update is necessary, and if it can happen in a worker thread.
    virtual UpdateGeometryType GetUpdateGeometryType();

    /// Add Drawable2D.
    void AddDrawable(Drawable2D* drawable);
    /// Remove Drawable2D.
    void RemoveDrawable(Drawable2D* drawable);
    /// Mark material dirty.
    void MarkMaterialDirty(Drawable2D* drawable);
    /// Mark order dirty.
    void MarkOrderDirty(){ orderDirty_ = true; }
    /// Check visibility.
    bool CheckVisibility(Drawable2D* drawable) const;

private:
    /// Recalculate the world-space bounding box.
    virtual void OnWorldBoundingBoxUpdate();
    /// Handle view update begin event. Determine Drawable2D's and their batches here.
    void HandleBeginViewUpdate(StringHash eventType, VariantMap& eventData);
    /// Get all drawables in node.
    void GetDrawables(PODVector<Drawable2D*>& drawables, Node* node);
    /// Return material by texture and blend mode.
    Material* GetMaterial(Texture2D* texture, BlendMode blendMode);
    /// Create new material by texture and blend mode.
    Material* CreateMaterial(Texture2D* Texture, BlendMode blendMode);
    /// Add batch.
    void AddBatch(Material* material, unsigned indexStart, unsigned indexCount, unsigned vertexStart, unsigned vertexCount);

    /// Index buffer.
    SharedPtr<IndexBuffer> indexBuffer_;
    /// Vertex buffer.
    SharedPtr<VertexBuffer> vertexBuffer_;
    /// Drawables.
    PODVector<Drawable2D*> drawables_;
    /// Material dirty drawables.
    PODVector<Drawable2D*> materialDirtyDrawables_;
    /// Order dirty.
    bool orderDirty_;
    /// View frameinfo for current frame.
    FrameInfo frame_;
    /// Used geometry count. Shared by all views and reset when a new frame begins.
    unsigned geometryCount_;
    /// Vertex count by view.
    HashMap<Camera*, unsigned> vertexCount_;
    /// Index count by view.
    HashMap<Camera*, unsigned> indexCount_;
    /// Geometries used in all views.
    Vector<SharedPtr<Geometry> > geometries_;
    /// Frustum for current frame.
    const Frustum* frustum_;
    /// Frustum bounding box for current frame.
    BoundingBox frustumBoundingBox_;
    /// Cached materials.
    HashMap<Texture2D*, HashMap<int, SharedPtr<Material> > > cachedMaterials_;
};

}
