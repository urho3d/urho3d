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
#include "Node.h"
#include "GraphicsDefs.h"

static const unsigned DRAWABLE_GEOMETRY = 0x1;
static const unsigned DRAWABLE_LIGHT = 0x2;
static const unsigned DRAWABLE_ZONE = 0x4;
static const unsigned DEFAULT_VIEWMASK = M_MAX_UNSIGNED;
static const unsigned DEFAULT_LIGHTMASK = M_MAX_UNSIGNED;

struct Batch;
class Camera;
class DebugRenderer;
class Geometry;
class Light;
class Material;
class OcclusionBuffer;
class Octant;
class RayOctreeQuery;

/// Rendering frame update parameters
struct FrameInfo
{
    /// Frame number
    unsigned frameNumber_;
    /// Time elapsed since last frame
    float timeStep_;
    /// Viewport size
    IntVector2 viewSize_;
    /// Camera being used
    Camera* camera_;
};

/// Base class for visible components
class Drawable : public Component
{
    OBJECT(Drawable);
    
    friend class Octant;
    
public:
    /// Construct
    Drawable(Context* context);
    /// Destruct
    virtual ~Drawable();
    /// Register object attributes
    static void RegisterObject(Context* context);
    
    /// Process octree raycast
    virtual void ProcessRayQuery(RayOctreeQuery& query, float initialDistance);
    /// Update before octree reinsertion. Needs to be requested with MarkForUpdate()
    virtual void Update(const FrameInfo& frame) {}
    /// Calculate distance for rendering
    virtual void UpdateDistance(const FrameInfo& frame);
    /// Prepare geometry for rendering
    virtual void UpdateGeometry(const FrameInfo& frame) {}
    /// Return number of rendering batches
    virtual unsigned GetNumBatches() { return 0; }
    /// Return rendering batch
    virtual void GetBatch(const FrameInfo& frame, unsigned batchIndex, Batch& batch) {}
    /// Draw to occlusion buffer
    virtual bool DrawOcclusion(OcclusionBuffer* buffer) { return true; }
    /// Draw debug geometry
    virtual void DrawDebugGeometry(DebugRenderer* debug, bool depthTest);
    
    /// Set draw distance
    void SetDrawDistance(float distance);
    /// Set shadow draw distance
    void SetShadowDistance(float distance);
    /// Set LOD bias
    void SetLodBias(float bias);
    /// Set view mask. Will be and'ed with camera's view mask to see if the object should be rendered
    void SetViewMask(unsigned mask);
    /// Set light mask. Will be and'ed with light's light mask to see if the object should be lit
    void SetLightMask(unsigned mask);
    /// Set maximum number of lights (forward lighting only). Default 0 is unlimited
    void SetMaxLights(unsigned num);
    /// Set visible flag
    void SetVisible(bool enable);
    /// Set shadowcaster flag
    void SetCastShadows(bool enable);
    /// Set occlusion flag
    void SetOccluder(bool enable);
    /// Mark for update before octree reinsertion
    void MarkForUpdate();
    
    /// Return world bounding box
    const BoundingBox& GetWorldBoundingBox();
    /// Return drawable flags
    unsigned char GetDrawableFlags() const { return drawableFlags_; }
    /// Return draw distance
    float GetDrawDistance() const { return drawDistance_; }
    /// Return shadow draw distance
    float GetShadowDistance() const { return shadowDistance_; }
    /// Return LOD bias
    float GetLodBias() const { return lodBias_; }
    /// Return view mask
    unsigned GetViewMask() const { return viewMask_; }
    /// Return light mask
    unsigned GetLightMask() const { return lightMask_; }
    /// Return maximum number of lights
    unsigned GetMaxLights() const { return maxLights_; }
    /// Return visible flag
    bool IsVisible() const { return visible_; }
    /// Return shadowcaster flag
    bool GetCastShadows() const { return castShadows_; }
    /// Return occlusion flag
    bool IsOccluder() const { return occluder_; }
    
    /// Return octree octant
    Octant* GetOctant() const { return octant_; }
    /// Set sorting value. Called by View
    void SetSortValue(float value);
    /// Mark in view this frame. Called by View
    void MarkInView(const FrameInfo& frame);
    /// Mark in a shadow camera view this frame. If an actual view is already set, does not override it. Called by View
    void MarkInShadowView(const FrameInfo& frame);
    /// Clear base pass flags. Also resets light vector
    void ClearBasePass();
    /// Set base pass flag for a batch
    void SetBasePass(unsigned batchIndex);
    /// Add a light, for drawables that limit the maximum light count
    void AddLight(Light* light);
    /// Sort and limit lights to maximum allowed
    void LimitLights();
    /// Return distance from camera
    float GetDistance() const { return distance_; }
    /// Return LOD scaled distance from camera
    float GetLodDistance() const { return lodDistance_; }
    /// Return sorting value
    float GetSortValue() const { return sortValue_; }
    /// Return whether is in view this frame
    bool IsInView(unsigned frameNumber) const;
    /// Return whether is visible in a specific view this frame
    bool IsInView(const FrameInfo& frame) const;
    /// Return whether has a base pass
    bool HasBasePass(unsigned batchIndex) const { return (basePassFlags_ & (1 << batchIndex)) != 0; }
    /// Return lights
    const std::vector<Light*>& GetLights() const { return lights_; }
    
protected:
    /// Handle node being assigned
    virtual void OnNodeSet(Node* node);
    /// Handle node transform being dirtied
    virtual void OnMarkedDirty(Node* node);
    /// Recalculate world bounding box
    virtual void OnWorldBoundingBoxUpdate() = 0;
    /// Add to octree
    void AddToOctree();
    /// Remove from octree
    void RemoveFromOctree();
    /// Move into another octree octant
    void SetOctant(Octant* octant) { octant_ = octant; }
    
    /// Octree octant
    Octant* octant_;
    /// World bounding box
    BoundingBox worldBoundingBox_;
    /// Draw distance
    float drawDistance_;
    /// Shadow distance
    float shadowDistance_;
    /// LOD bias
    float lodBias_;
    /// View mask
    unsigned viewMask_;
    /// Light mask
    unsigned lightMask_;
    /// Maximum lights
    unsigned maxLights_;
    /// Drawable flags
    unsigned char drawableFlags_;
    /// Visible flag
    bool visible_;
    /// Shadowcaster flag
    bool castShadows_;
    /// Occluder flag
    bool occluder_;
    /// Current distance to camera
    float distance_;
    /// LOD scaled distance
    float lodDistance_;
    /// Current sort value
    float sortValue_;
    /// Last visible frame number
    unsigned viewFrameNumber_;
    /// Base pass flags per batch index
    unsigned basePassFlags_;
    /// Last camera rendered from. Not safe to dereference
    Camera* viewCamera_;
    /// Lights affecting this drawable, when light count is limited
    std::vector<Light*> lights_;
    /// Bounding box dirty flag
    bool worldBoundingBoxDirty_;
    /// Lod levels dirty flag
    bool lodLevelsDirty_;
};

bool CompareDrawables(const Drawable* lhs, const Drawable* rhs);
