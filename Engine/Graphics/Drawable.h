//
// Urho3D Engine
// Copyright (c) 2008-2011 Lasse Öörni
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

#include "BoundingBox.h"
#include "Component.h"
#include "GraphicsDefs.h"
#include "Node.h"

static const unsigned DRAWABLE_GEOMETRY = 0x1;
static const unsigned DRAWABLE_LIGHT = 0x2;
static const unsigned DRAWABLE_ZONE = 0x4;
static const unsigned DRAWABLE_ANY = 0xff;
static const unsigned DEFAULT_VIEWMASK = M_MAX_UNSIGNED;
static const unsigned DEFAULT_LIGHTMASK = M_MAX_UNSIGNED;
static const unsigned DEFAULT_SHADOWMASK = M_MAX_UNSIGNED;
static const unsigned DEFAULT_ZONEMASK = M_MAX_UNSIGNED;
static const int DRAWABLES_PER_WORK_ITEM = 16;
static const int MAX_VERTEX_LIGHTS = 6;

struct Batch;
class Camera;
class DebugRenderer;
class Geometry;
class Light;
class Material;
class OcclusionBuffer;
class Octant;
class RayOctreeQuery;
class Zone;
struct RayQueryResult;
struct WorkItem;

/// Geometry update type.
enum UpdateGeometryType
{
    UPDATE_NONE = 0,
    UPDATE_MAIN_THREAD,
    UPDATE_WORKER_THREAD
};

/// Rendering frame update parameters.
struct FrameInfo
{
    /// Frame number.
    unsigned frameNumber_;
    /// Time elapsed since last frame.
    float timeStep_;
    /// Viewport size.
    IntVector2 viewSize_;
    /// Camera being used.
    Camera* camera_;
};

/// Base class for visible components.
class Drawable : public Component
{
    OBJECT(Drawable);
    
    friend class Octant;
    friend class Octree;
    friend void UpdateDrawablesWork(const WorkItem* item, unsigned threadIndex);
    
public:
    /// Construct.
    Drawable(Context* context);
    /// Destruct.
    virtual ~Drawable();
    /// Register object attributes. Drawable must be registered first.
    static void RegisterObject(Context* context);
    
    /// Process octree raycast. May be called from a worker thread.
    virtual void ProcessRayQuery(const RayOctreeQuery& query, PODVector<RayQueryResult>& results);
    /// Update before octree reinsertion. Is called from a worker thread. Needs to be requested with MarkForUpdate().
    virtual void Update(const FrameInfo& frame) {}
    /// Calculate distance and LOD level for rendering.  May be called from worker thread(s), possibly re-entrantly.
    virtual void UpdateDistance(const FrameInfo& frame);
    /// Prepare geometry for rendering.
    virtual void UpdateGeometry(const FrameInfo& frame) {}
    /// Return whether a geometry update is necessary, and if it should happen in a worker thread.
    virtual UpdateGeometryType GetUpdateGeometryType() { return UPDATE_NONE; }
    /// Return number of rendering batches.
    virtual unsigned GetNumBatches() { return 0; }
    /// Fill rendering batch with distance, geometry, material and world transform.
    virtual void GetBatch(Batch& batch, const FrameInfo& frame, unsigned batchIndex) {}
    /// Return number of occlusion geometry triangles.
    virtual unsigned GetNumOccluderTriangles() { return 0; }
    /// Draw to occlusion buffer. Return true if did not run out of triangles.
    virtual bool DrawOcclusion(OcclusionBuffer* buffer) { return true; }
    /// Add debug geometry to the debug renderer.
    virtual void DrawDebugGeometry(DebugRenderer* debug, bool depthTest);
    
    /// %Set draw distance.
    void SetDrawDistance(float distance);
    /// %Set shadow draw distance.
    void SetShadowDistance(float distance);
    /// %Set LOD bias.
    void SetLodBias(float bias);
    /// %Set view mask. Is and'ed with camera's view mask to see if the object should be rendered.
    void SetViewMask(unsigned mask);
    /// %Set light mask. Is and'ed with light's and zone's light mask to see if the object should be lit.
    void SetLightMask(unsigned mask);
    /// %Set shadow mask. Is and'ed with light's light mask and zone's shadow mask to see if the object should be rendered to a shadow map.
    void SetShadowMask(unsigned mask);
    /// %Set zone mask. Is and'ed with zone's zone mask to see if the object should belong to the zone.
    void SetZoneMask(unsigned mask);
    /// %Set maximum number of lights. Default 0 is unlimited.
    void SetMaxLights(unsigned num);
    /// %Set visible flag.
    void SetVisible(bool enable);
    /// %Set shadowcaster flag.
    void SetCastShadows(bool enable);
    /// %Set occlusion flag.
    void SetOccluder(bool enable);
    /// Mark for update before octree reinsertion.
    void MarkForUpdate();
    
    /// Return world bounding box.
    const BoundingBox& GetWorldBoundingBox();
    /// Return drawable flags.
    unsigned char GetDrawableFlags() const { return drawableFlags_; }
    /// Return draw distance.
    float GetDrawDistance() const { return drawDistance_; }
    /// Return shadow draw distance.
    float GetShadowDistance() const { return shadowDistance_; }
    /// Return LOD bias.
    float GetLodBias() const { return lodBias_; }
    /// Return view mask.
    unsigned GetViewMask() const { return viewMask_; }
    /// Return light mask.
    unsigned GetLightMask() const { return lightMask_; }
    /// Return shadow mask.
    unsigned GetShadowMask() const { return shadowMask_; }
    /// Return zone mask.
    unsigned GetZoneMask() const { return zoneMask_; }
    /// Return maximum number of lights.
    unsigned GetMaxLights() const { return maxLights_; }
    /// Return visible flag.
    bool IsVisible() const { return visible_; }
    /// Return shadowcaster flag.
    bool GetCastShadows() const { return castShadows_; }
    /// Return occlusion flag.
    bool IsOccluder() const { return occluder_; }
    
    /// %Set new zone.
    void SetZone(Zone* zone);
    /// %Set sorting value.
    void SetSortValue(float value);
    /// Mark in view (either the main camera, or a shadow camera view) this frame.
    void MarkInView(const FrameInfo& frame, bool mainView = true);
    /// Clear lights and base pass flags for a new frame.
    void ClearLights();
    /// Add a per-pixel light.
    void AddLight(Light* light);
    /// Add a per-vertex light.
    void AddVertexLight(Light* light);
    /// Sort and limit per-pixel lights to maximum allowed.
    void LimitLights();
    /// Sort and limit per-vertex lights to maximum allowed.
    void LimitVertexLights();
    /// %Set base pass flag for a batch.
    void SetBasePass(unsigned batchIndex);
    /// Return octree octant.
    Octant* GetOctant() const { return octant_; }
    /// Return current zone.
    Zone* GetZone() const;
    /// Return previous zone.
    Zone* GetLastZone() const;
    /// Return distance from camera.
    float GetDistance() const { return distance_; }
    /// Return LOD scaled distance from camera.
    float GetLodDistance() const { return lodDistance_; }
    /// Return sorting value.
    float GetSortValue() const { return sortValue_; }
    /// Return whether is in view this frame.
    bool IsInView(unsigned frameNumber) const { return viewFrameNumber_ == frameNumber; }
    /// Return whether is visible in a specific view this frame.
    bool IsInView(const FrameInfo& frame, bool mainView = true) const { return viewFrameNumber_ == frame.frameNumber_ && viewFrame_ == &frame && (!mainView || viewCamera_ == frame.camera_); }
    /// Return whether has a base pass.
    bool HasBasePass(unsigned batchIndex) const;
    /// Return per-pixel lights.
    const PODVector<Light*>& GetLights() const { return lights_; }
    /// Return per-vertex lights.
    const PODVector<Light*>& GetVertexLights() const { return vertexLights_; }
    /// Return the first added per-pixel light.
    Light* GetFirstLight() const { return firstLight_; }
    
protected:
    /// Handle node being assigned.
    virtual void OnNodeSet(Node* node);
    /// Handle node transform being dirtied.
    virtual void OnMarkedDirty(Node* node);
    /// Recalculate the world-space bounding box.
    virtual void OnWorldBoundingBoxUpdate() = 0;
    /// Add to octree.
    void AddToOctree();
    /// Remove from octree.
    void RemoveFromOctree();
    /// Move into another octree octant.
    void SetOctant(Octant* octant) { octant_ = octant; }
    
    /// Octree octant.
    Octant* octant_;
    /// World bounding box.
    BoundingBox worldBoundingBox_;
    /// Base pass flags per batch index.
    PODVector<unsigned> basePassFlags_;
    /// Last view's frameinfo. Not safe to dereference.
    const FrameInfo* viewFrame_;
    /// Last view's camera. Not safe to dereference.
    Camera* viewCamera_;
    /// Per-pixel lights affecting this drawable.
    PODVector<Light*> lights_;
    /// Per-vertex lights affecting this drawable.
    PODVector<Light*> vertexLights_;
    /// First per-pixel light added this frame.
    Light* firstLight_;
    /// Current zone.
    WeakPtr<Zone> zone_;
    /// Previous zone.
    WeakPtr<Zone> lastZone_;
    /// Draw distance.
    float drawDistance_;
    /// Shadow distance.
    float shadowDistance_;
    /// LOD bias.
    float lodBias_;
    /// View mask.
    unsigned viewMask_;
    /// Light mask.
    unsigned lightMask_;
    /// Shadow mask.
    unsigned shadowMask_;
    /// Zone mask.
    unsigned zoneMask_;
    /// Maximum lights.
    unsigned maxLights_;
    /// Current distance to camera.
    float distance_;
    /// LOD scaled distance.
    float lodDistance_;
    /// Current sort value.
    float sortValue_;
    /// Last visible frame number.
    unsigned viewFrameNumber_;
    /// Drawable flags.
    unsigned char drawableFlags_;
    /// Visible flag.
    bool visible_;
    /// Shadowcaster flag.
    bool castShadows_;
    /// Occluder flag.
    bool occluder_;
    /// Bounding box dirty flag.
    bool worldBoundingBoxDirty_;
    /// Octree update queued flag.
    bool updateQueued_;
    /// Octree reinsertion queued flag.
    bool reinsertionQueued_;
};

inline bool CompareDrawables(Drawable* lhs, Drawable* rhs)
{
    return lhs->GetSortValue() < rhs->GetSortValue();
}
