// Copyright (c) 2008-2023 the Urho3D project
// License: MIT

/// \file

#pragma once

#include "../GraphicsAPI/GraphicsDefs.h"
#include "../Math/BoundingBox.h"
#include "../Scene/Component.h"

namespace Urho3D
{

enum class DrawableTypes : u8
{
    Undefined  = 0,
    Geometry   = 1 << 0,
    Light      = 1 << 1,
    Zone       = 1 << 2,
    Geometry2D = 1 << 3,
    Any        = 0xFF
};
URHO3D_FLAGS(DrawableTypes);

inline constexpr mask32 DEFAULT_VIEWMASK = M_U32_MASK_ALL_BITS;
inline constexpr mask32 DEFAULT_LIGHTMASK = M_U32_MASK_ALL_BITS;
inline constexpr mask32 DEFAULT_SHADOWMASK = M_U32_MASK_ALL_BITS;
inline constexpr mask32 DEFAULT_ZONEMASK = M_U32_MASK_ALL_BITS;
inline constexpr i32 MAX_VERTEX_LIGHTS = 4;
inline constexpr float ANIMATION_LOD_BASESCALE = 2500.0f;

class Camera;
class File;
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
    i32 frameNumber_;
    /// Time elapsed since last frame.
    float timeStep_;
    /// Viewport size.
    IntVector2 viewSize_;
    /// Camera being used.
    Camera* camera_;
};

/// Source data for a 3D geometry draw call.
struct URHO3D_API SourceBatch
{
    /// Construct with defaults.
    SourceBatch();
    /// Copy-construct.
    SourceBatch(const SourceBatch& batch);
    /// Destruct.
    ~SourceBatch();

    /// Assignment operator.
    SourceBatch& operator =(const SourceBatch& rhs);

    /// Distance from camera.
    float distance_{};
    /// Geometry.
    Geometry* geometry_{};
    /// Material.
    SharedPtr<Material> material_;
    /// World transform(s). For a skinned model, these are the bone transforms.
    const Matrix3x4* worldTransform_{&Matrix3x4::IDENTITY};
    /// Number of world transforms.
    i32 numWorldTransforms_{1};
    /// Per-instance data. If not null, must contain enough data to fill instancing buffer.
    void* instancingData_{};
    /// %Geometry type.
    GeometryType geometryType_{GEOM_STATIC};
};

/// Base class for visible components.
class URHO3D_API Drawable : public Component
{
    URHO3D_OBJECT(Drawable, Component);

    friend class Octant;
    friend class Octree;
    friend void UpdateDrawablesWork(const WorkItem* item, i32 threadIndex);

public:
    /// Construct.
    Drawable(Context* context, DrawableTypes drawableType);
    /// Destruct.
    ~Drawable() override;
    /// Register object attributes. Drawable must be registered first.
    /// @nobind
    static void RegisterObject(Context* context);

    /// Handle enabled/disabled state change.
    void OnSetEnabled() override;
    /// Process octree raycast. May be called from a worker thread.
    virtual void ProcessRayQuery(const RayOctreeQuery& query, Vector<RayQueryResult>& results);
    /// Update before octree reinsertion. Is called from a worker thread.
    virtual void Update(const FrameInfo& frame) { }
    /// Calculate distance and prepare batches for rendering. May be called from worker thread(s), possibly re-entrantly.
    virtual void UpdateBatches(const FrameInfo& frame);
    /// Prepare geometry for rendering.
    virtual void UpdateGeometry(const FrameInfo& frame) { }

    /// Return whether a geometry update is necessary, and if it can happen in a worker thread.
    virtual UpdateGeometryType GetUpdateGeometryType() { return UPDATE_NONE; }

    /// Return the geometry for a specific LOD level.
    virtual Geometry* GetLodGeometry(i32 batchIndex, i32 level);

    /// Return number of occlusion geometry triangles.
    virtual i32 GetNumOccluderTriangles() { return 0; }

    /// Draw to occlusion buffer. Return true if did not run out of triangles.
    virtual bool DrawOcclusion(OcclusionBuffer* buffer);
    /// Visualize the component as debug geometry.
    void DrawDebugGeometry(DebugRenderer* debug, bool depthTest) override;

    /// Set draw distance.
    /// @property
    void SetDrawDistance(float distance);
    /// Set shadow draw distance.
    /// @property
    void SetShadowDistance(float distance);
    /// Set LOD bias.
    /// @property
    void SetLodBias(float bias);
    /// Set view mask. Is and'ed with camera's view mask to see if the object should be rendered.
    /// @property
    void SetViewMask(mask32 mask);
    /// Set light mask. Is and'ed with light's and zone's light mask to see if the object should be lit.
    /// @property
    void SetLightMask(mask32 mask);
    /// Set shadow mask. Is and'ed with light's light mask and zone's shadow mask to see if the object should be rendered to a shadow map.
    /// @property
    void SetShadowMask(mask32 mask);
    /// Set zone mask. Is and'ed with zone's zone mask to see if the object should belong to the zone.
    /// @property
    void SetZoneMask(mask32 mask);
    /// Set maximum number of per-pixel lights. Default 0 is unlimited.
    /// @property
    void SetMaxLights(i32 num);
    /// Set shadowcaster flag.
    /// @property
    void SetCastShadows(bool enable);
    /// Set occlusion flag.
    /// @property
    void SetOccluder(bool enable);
    /// Set occludee flag.
    /// @property
    void SetOccludee(bool enable);
    /// Mark for update and octree reinsertion. Update is automatically queued when the drawable's scene node moves or changes scale.
    void MarkForUpdate();

    /// Return local space bounding box. May not be applicable or properly updated on all drawables.
    /// @property
    const BoundingBox& GetBoundingBox() const { return boundingBox_; }

    /// Return world-space bounding box.
    /// @property
    const BoundingBox& GetWorldBoundingBox();

    /// Return drawable type.
    DrawableTypes GetDrawableType() const { return drawableType_; }

    /// Return draw distance.
    /// @property
    float GetDrawDistance() const { return drawDistance_; }

    /// Return shadow draw distance.
    /// @property
    float GetShadowDistance() const { return shadowDistance_; }

    /// Return LOD bias.
    /// @property
    float GetLodBias() const { return lodBias_; }

    /// Return view mask.
    /// @property
    mask32 GetViewMask() const { return viewMask_; }

    /// Return light mask.
    /// @property
    mask32 GetLightMask() const { return lightMask_; }

    /// Return shadow mask.
    /// @property
    mask32 GetShadowMask() const { return shadowMask_; }

    /// Return zone mask.
    /// @property
    mask32 GetZoneMask() const { return zoneMask_; }

    /// Return maximum number of per-pixel lights.
    /// @property
    i32 GetMaxLights() const { return maxLights_; }

    /// Return shadowcaster flag.
    /// @property
    bool GetCastShadows() const { return castShadows_; }

    /// Return occluder flag.
    /// @property
    bool IsOccluder() const { return occluder_; }

    /// Return occludee flag.
    /// @property
    bool IsOccludee() const { return occludee_; }

    /// Return whether is in view this frame from any viewport camera. Excludes shadow map cameras.
    /// @property
    bool IsInView() const;
    /// Return whether is in view of a specific camera this frame. Pass in a null camera to allow any camera, including shadow map cameras.
    bool IsInView(Camera* camera) const;

    /// Return draw call source data.
    const Vector<SourceBatch>& GetBatches() const { return batches_; }

    /// Set new zone. Zone assignment may optionally be temporary, meaning it needs to be re-evaluated on the next frame.
    void SetZone(Zone* zone, bool temporary = false);
    /// Set sorting value.
    void SetSortValue(float value);

    /// Set view-space depth bounds.
    void SetMinMaxZ(float minZ, float maxZ)
    {
        minZ_ = minZ;
        maxZ_ = maxZ;
    }

    /// Mark in view. Also clear the light list.
    void MarkInView(const FrameInfo& frame);
    /// Mark in view without specifying a camera. Used for shadow casters.
    void MarkInView(i32 frameNumber);
    /// Sort and limit per-pixel lights to maximum allowed. Convert extra lights into vertex lights.
    void LimitLights();
    /// Sort and limit per-vertex lights to maximum allowed.
    void LimitVertexLights(bool removeConvertedLights);

    /// Set base pass flag for a batch.
    void SetBasePass(i32 batchIndex)
    {
        assert(batchIndex >= 0 && batchIndex < 32);
        basePassFlags_ |= (1u << batchIndex);
    }

    /// Return octree octant.
    Octant* GetOctant() const { return octant_; }

    /// Return current zone.
    /// @property
    Zone* GetZone() const { return zone_; }

    /// Return whether current zone is inconclusive or dirty due to the drawable moving.
    bool IsZoneDirty() const { return zoneDirty_; }

    /// Return distance from camera.
    float GetDistance() const { return distance_; }

    /// Return LOD scaled distance from camera.
    float GetLodDistance() const { return lodDistance_; }

    /// Return sorting value.
    float GetSortValue() const { return sortValue_; }

    /// Return whether is in view on the current frame. Called by View.
    bool IsInView(const FrameInfo& frame, bool anyCamera = false) const;

    /// Return whether has a base pass.
    bool HasBasePass(i32 batchIndex) const
    {
        assert(batchIndex >= 0 && batchIndex < 32);
        return (basePassFlags_ & (1u << batchIndex)) != 0;
    }

    /// Return per-pixel lights.
    const Vector<Light*>& GetLights() const { return lights_; }

    /// Return per-vertex lights.
    const Vector<Light*>& GetVertexLights() const { return vertexLights_; }

    /// Return the first added per-pixel light.
    Light* GetFirstLight() const { return firstLight_; }

    /// Return the minimum view-space depth.
    float GetMinZ() const { return minZ_; }

    /// Return the maximum view-space depth.
    float GetMaxZ() const { return maxZ_; }

    /// Add a per-pixel light affecting the object this frame.
    void AddLight(Light* light)
    {
        if (!firstLight_)
            firstLight_ = light;

        // Need to store into the light list only if the per-pixel lights are being limited
        // Otherwise recording the first light is enough
        if (maxLights_)
            lights_.Push(light);
    }

    /// Add a per-vertex light affecting the object this frame.
    void AddVertexLight(Light* light)
    {
        vertexLights_.Push(light);
    }

protected:
    /// Handle node being assigned.
    void OnNodeSet(Node* node) override;
    /// Handle scene being assigned.
    void OnSceneSet(Scene* scene) override;
    /// Handle node transform being dirtied.
    void OnMarkedDirty(Node* node) override;
    /// Recalculate the world-space bounding box.
    virtual void OnWorldBoundingBoxUpdate() = 0;

    /// Handle removal from octree.
    virtual void OnRemoveFromOctree() { }

    /// Add to octree.
    void AddToOctree();
    /// Remove from octree.
    void RemoveFromOctree();

    /// Move into another octree octant.
    void SetOctant(Octant* octant) { octant_ = octant; }

    /// World-space bounding box.
    BoundingBox worldBoundingBox_;
    /// Local-space bounding box.
    BoundingBox boundingBox_;
    /// Draw call source data.
    Vector<SourceBatch> batches_;
    /// Drawable type
    DrawableTypes drawableType_;
    /// Bounding box dirty flag.
    bool worldBoundingBoxDirty_;
    /// Shadowcaster flag.
    bool castShadows_;
    /// Occluder flag.
    bool occluder_;
    /// Occludee flag.
    bool occludee_;
    /// Octree update queued flag.
    bool updateQueued_;
    /// Zone inconclusive or dirtied flag.
    bool zoneDirty_;
    /// Octree octant.
    Octant* octant_;
    /// Current zone.
    Zone* zone_;
    /// View mask.
    mask32 viewMask_;
    /// Light mask.
    mask32 lightMask_;
    /// Shadow mask.
    mask32 shadowMask_;
    /// Zone mask.
    mask32 zoneMask_;
    /// Last visible frame number.
    i32 viewFrameNumber_;
    /// Current distance to camera.
    float distance_;
    /// LOD scaled distance.
    float lodDistance_;
    /// Draw distance.
    float drawDistance_;
    /// Shadow distance.
    float shadowDistance_;
    /// Current sort value.
    float sortValue_;
    /// Current minimum view space depth.
    float minZ_;
    /// Current maximum view space depth.
    float maxZ_;
    /// LOD bias.
    float lodBias_;
    /// Base pass flags, bit per batch.
    flagset32 basePassFlags_;
    /// Maximum per-pixel lights.
    i32 maxLights_;
    /// List of cameras from which is seen on the current frame.
    Vector<Camera*> viewCameras_;
    /// First per-pixel light added this frame.
    Light* firstLight_;
    /// Per-pixel lights affecting this drawable.
    Vector<Light*> lights_;
    /// Per-vertex lights affecting this drawable.
    Vector<Light*> vertexLights_;
};

inline bool CompareDrawables(Drawable* lhs, Drawable* rhs)
{
    return lhs->GetSortValue() < rhs->GetSortValue();
}

URHO3D_API bool WriteDrawablesToOBJ(const Vector<Drawable*>& drawables, File* outputFile, bool asZUp, bool asRightHanded, bool writeLightmapUV = false);

}
