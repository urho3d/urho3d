// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include "../Container/ArrayPtr.h"
#include "../Scene/Component.h"

namespace Urho3D
{

class Image;
class IndexBuffer;
class Material;
class Node;
class TerrainPatch;

/// Heightmap terrain component.
class URHO3D_API Terrain : public Component
{
    URHO3D_OBJECT(Terrain, Component);

public:
    /// Construct.
    explicit Terrain(Context* context);
    /// Destruct.
    ~Terrain() override;
    /// Register object factory.
    /// @nobind
    static void RegisterObject(Context* context);

    /// Apply attribute changes that can not be applied immediately. Called after scene load or a network update.
    void ApplyAttributes() override;
    /// Handle enabled/disabled state change.
    void OnSetEnabled() override;

    /// Set patch quads per side. Must be a power of two.
    /// @property
    void SetPatchSize(int size);
    /// Set vertex (XZ) and height (Y) spacing.
    /// @property
    void SetSpacing(const Vector3& spacing);
    /// Set maximum number of LOD levels for terrain patches. This can be between 1-4.
    /// @property
    void SetMaxLodLevels(unsigned levels);
    /// Set LOD level used for terrain patch occlusion. By default (NINDEX) the coarsest. Since the LOD level used needs to be fixed, using finer LOD levels may result in false positive occlusion in cases where the actual rendered geometry is coarser, so use with caution.
    /// @property
    void SetOcclusionLodLevel(i32 level);
    /// Set smoothing of heightmap.
    /// @property
    void SetSmoothing(bool enable);
    /// Set heightmap image. Dimensions should be a power of two + 1. Uses 8-bit grayscale, or optionally red as MSB and green as LSB for 16-bit accuracy. Return true if successful.
    /// @property
    bool SetHeightMap(Image* image);
    /// Set material.
    /// @property
    void SetMaterial(Material* material);
    /// Set north (positive Z) neighbor terrain for seamless LOD changes across terrains.
    /// @property
    void SetNorthNeighbor(Terrain* north);
    /// Set south (negative Z) neighbor terrain for seamless LOD changes across terrains.
    /// @property
    void SetSouthNeighbor(Terrain* south);
    /// Set west (negative X) neighbor terrain for seamless LOD changes across terrains.
    /// @property
    void SetWestNeighbor(Terrain* west);
    /// Set east (positive X) neighbor terrain for seamless LOD changes across terrains.
    /// @property
    void SetEastNeighbor(Terrain* east);
    /// Set all neighbor terrains at once.
    void SetNeighbors(Terrain* north, Terrain* south, Terrain* west, Terrain* east);
    /// Set draw distance for patches.
    /// @property
    void SetDrawDistance(float distance);
    /// Set shadow draw distance for patches.
    /// @property
    void SetShadowDistance(float distance);
    /// Set LOD bias for patches. Affects which terrain LOD to display.
    /// @property
    void SetLodBias(float bias);
    /// Set view mask for patches. Is and'ed with camera's view mask to see if the object should be rendered.
    /// @property
    void SetViewMask(unsigned mask);
    /// Set light mask for patches. Is and'ed with light's and zone's light mask to see if the object should be lit.
    /// @property
    void SetLightMask(unsigned mask);
    /// Set shadow mask for patches. Is and'ed with light's light mask and zone's shadow mask to see if the object should be rendered to a shadow map.
    /// @property
    void SetShadowMask(unsigned mask);
    /// Set zone mask for patches. Is and'ed with zone's zone mask to see if the object should belong to the zone.
    /// @property
    void SetZoneMask(unsigned mask);
    /// Set maximum number of per-pixel lights for patches. Default 0 is unlimited.
    /// @property
    void SetMaxLights(unsigned num);
    /// Set shadowcaster flag for patches.
    /// @property
    void SetCastShadows(bool enable);
    /// Set occlusion flag for patches. Occlusion uses the coarsest LOD by default.
    /// @property
    void SetOccluder(bool enable);
    /// Set occludee flag for patches.
    /// @property
    void SetOccludee(bool enable);
    /// Apply changes from the heightmap image.
    void ApplyHeightMap();

    /// Return patch quads per side.
    /// @property
    int GetPatchSize() const { return patchSize_; }

    /// Return vertex and height spacing.
    /// @property
    const Vector3& GetSpacing() const { return spacing_; }

    /// Return heightmap size in vertices.
    /// @property
    const IntVector2& GetNumVertices() const { return numVertices_; }

    /// Return heightmap size in patches.
    /// @property
    const IntVector2& GetNumPatches() const { return numPatches_; }

    /// Return maximum number of LOD levels for terrain patches. This can be between 1-4.
    /// @property
    unsigned GetMaxLodLevels() const { return maxLodLevels_; }

    /// Return LOD level used for occlusion.
    /// @property
    i32 GetOcclusionLodLevel() const { return occlusionLodLevel_; }

    /// Return whether smoothing is in use.
    /// @property
    bool GetSmoothing() const { return smoothing_; }

    /// Return heightmap image.
    /// @property
    Image* GetHeightMap() const;
    /// Return material.
    /// @property
    Material* GetMaterial() const;
    /// Return patch by index.
    /// @property{get_patches}
    TerrainPatch* GetPatch(i32 index) const;
    /// Return patch by patch coordinates.
    TerrainPatch* GetPatch(int x, int z) const;
    /// Return patch by patch coordinates including neighbor terrains.
    TerrainPatch* GetNeighborPatch(int x, int z) const;
    /// Return height at world coordinates.
    float GetHeight(const Vector3& worldPosition) const;
    /// Return normal at world coordinates.
    Vector3 GetNormal(const Vector3& worldPosition) const;
    /// Convert world position to heightmap pixel position. Note that the internal height data representation is reversed vertically, but in the heightmap image north is at the top.
    IntVector2 WorldToHeightMap(const Vector3& worldPosition) const;
    /// Convert heightmap pixel position to world position.
    Vector3 HeightMapToWorld(const IntVector2& pixelPosition) const;

    /// Return north neighbor terrain.
    /// @property
    Terrain* GetNorthNeighbor() const { return north_; }

    /// Return south neighbor terrain.
    /// @property
    Terrain* GetSouthNeighbor() const { return south_; }

    /// Return west neighbor terrain.
    /// @property
    Terrain* GetWestNeighbor() const { return west_; }

    /// Return east neighbor terrain.
    /// @property
    Terrain* GetEastNeighbor() const { return east_; }

    /// Return raw height data.
    SharedArrayPtr<float> GetHeightData() const { return heightData_; }

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
    unsigned GetViewMask() const { return viewMask_; }

    /// Return light mask.
    /// @property
    unsigned GetLightMask() const { return lightMask_; }

    /// Return shadow mask.
    /// @property
    unsigned GetShadowMask() const { return shadowMask_; }

    /// Return zone mask.
    /// @property
    unsigned GetZoneMask() const { return zoneMask_; }

    /// Return maximum number of per-pixel lights.
    /// @property
    unsigned GetMaxLights() const { return maxLights_; }

    /// Return visible flag.
    bool IsVisible() const { return visible_; }

    /// Return shadowcaster flag.
    /// @property
    bool GetCastShadows() const { return castShadows_; }

    /// Return occluder flag.
    /// @property
    bool IsOccluder() const { return occluder_; }

    /// Return occludee flag.
    /// @property
    bool IsOccludee() const { return occludee_; }

    /// Regenerate patch geometry.
    void CreatePatchGeometry(TerrainPatch* patch);
    /// Update patch based on LOD and neighbor LOD.
    void UpdatePatchLod(TerrainPatch* patch);
    /// Set heightmap attribute.
    void SetHeightMapAttr(const ResourceRef& value);
    /// Set material attribute.
    void SetMaterialAttr(const ResourceRef& value);
    /// Set patch size attribute.
    void SetPatchSizeAttr(int value);
    /// Set max LOD levels attribute.
    void SetMaxLodLevelsAttr(unsigned value);
    /// Set occlusion LOD level attribute.
    void SetOcclusionLodLevelAttr(i32 value);
    /// Return heightmap attribute.
    ResourceRef GetHeightMapAttr() const;
    /// Return material attribute.
    ResourceRef GetMaterialAttr() const;

private:
    /// Regenerate terrain geometry.
    void CreateGeometry();
    /// Create index data shared by all patches.
    void CreateIndexData();
    /// Return an uninterpolated terrain height value, clamping to edges.
    float GetRawHeight(int x, int z) const;
    /// Return a source terrain height value, clamping to edges. The source data is used for smoothing.
    float GetSourceHeight(int x, int z) const;
    /// Return interpolated height for a specific LOD level.
    float GetLodHeight(int x, int z, unsigned lodLevel) const;
    /// Get slope-based terrain normal at position.
    Vector3 GetRawNormal(int x, int z) const;
    /// Calculate LOD errors for a patch.
    void CalculateLodErrors(TerrainPatch* patch);
    /// Set neighbors for a patch.
    void SetPatchNeighbors(TerrainPatch* patch);
    /// Set heightmap image and optionally recreate the geometry immediately. Return true if successful.
    bool SetHeightMapInternal(Image* image, bool recreateNow);
    /// Handle heightmap image reload finished.
    void HandleHeightMapReloadFinished(StringHash eventType, VariantMap& eventData);
    /// Handle neighbor terrain geometry being created. Update the edge patch neighbors as necessary.
    void HandleNeighborTerrainCreated(StringHash eventType, VariantMap& eventData);
    /// Update edge patch neighbors when neighbor terrain(s) change or are recreated.
    void UpdateEdgePatchNeighbors();
    /// Mark neighbors dirty.
    void MarkNeighborsDirty() { neighborsDirty_ = true; }
    /// Mark terrain dirty.
    void MarkTerrainDirty() { recreateTerrain_ = true; }

    /// Shared index buffer.
    SharedPtr<IndexBuffer> indexBuffer_;
    /// Heightmap image.
    SharedPtr<Image> heightMap_;
    /// Height data.
    SharedArrayPtr<float> heightData_;
    /// Source height data for smoothing.
    SharedArrayPtr<float> sourceHeightData_;
    /// Material.
    SharedPtr<Material> material_;
    /// Terrain patches.
    Vector<WeakPtr<TerrainPatch>> patches_;
    /// Draw ranges for different LODs and stitching combinations.
    Vector<Pair<unsigned, unsigned>> drawRanges_;
    /// North neighbor terrain.
    WeakPtr<Terrain> north_;
    /// South neighbor terrain.
    WeakPtr<Terrain> south_;
    /// West neighbor terrain.
    WeakPtr<Terrain> west_;
    /// East neighbor terrain.
    WeakPtr<Terrain> east_;
    /// Vertex and height spacing.
    Vector3 spacing_;
    /// Vertex and height sacing at the time of last update.
    Vector3 lastSpacing_;
    /// Origin of patches on the XZ-plane.
    Vector2 patchWorldOrigin_;
    /// Size of a patch on the XZ-plane.
    Vector2 patchWorldSize_;
    /// Terrain size in vertices.
    IntVector2 numVertices_;
    /// Terrain size in vertices at the time of last update.
    IntVector2 lastNumVertices_;
    /// Terrain size in patches.
    IntVector2 numPatches_;
    /// Patch size, quads per side.
    int patchSize_;
    /// Patch size at the time of last update.
    int lastPatchSize_;
    /// Number of terrain LOD levels.
    unsigned numLodLevels_;
    /// Maximum number of LOD levels.
    unsigned maxLodLevels_;
    /// LOD level used for occlusion.
    i32 occlusionLodLevel_;
    /// Smoothing enable flag.
    bool smoothing_;
    /// Visible flag.
    bool visible_;
    /// Shadowcaster flag.
    bool castShadows_;
    /// Occluder flag.
    bool occluder_;
    /// Occludee flag.
    bool occludee_;
    /// View mask.
    unsigned viewMask_;
    /// Light mask.
    unsigned lightMask_;
    /// Shadow mask.
    unsigned shadowMask_;
    /// Zone mask.
    unsigned zoneMask_;
    /// Draw distance.
    float drawDistance_;
    /// Shadow distance.
    float shadowDistance_;
    /// LOD bias.
    float lodBias_;
    /// Maximum lights.
    unsigned maxLights_;
    /// Node ID of north neighbor.
    unsigned northID_;
    /// Node ID of south neighbor.
    unsigned southID_;
    /// Node ID of west neighbor.
    unsigned westID_;
    /// Node ID of east neighbor.
    unsigned eastID_;
    /// Terrain needs regeneration flag.
    bool recreateTerrain_;
    /// Terrain neighbor attributes dirty flag.
    bool neighborsDirty_;
};

}
