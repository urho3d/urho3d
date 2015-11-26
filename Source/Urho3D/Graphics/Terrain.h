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
    Terrain(Context* context);
    /// Destruct.
    ~Terrain();
    /// Register object factory.
    static void RegisterObject(Context* context);

    /// Handle attribute write access.
    virtual void OnSetAttribute(const AttributeInfo& attr, const Variant& src);
    /// Apply attribute changes that can not be applied immediately. Called after scene load or a network update.
    virtual void ApplyAttributes();
    /// Handle enabled/disabled state change.
    virtual void OnSetEnabled();

    /// Set patch quads per side. Must be a power of two.
    void SetPatchSize(int size);
    /// Set vertex (XZ) and height (Y) spacing.
    void SetSpacing(const Vector3& spacing);
    /// Set maximum number of LOD levels for terrain patches. This can be between 1-4.
    void SetMaxLodLevels(unsigned levels);
    /// Set LOD level used for terrain patch occlusion. By default (M_MAX_UNSIGNED) the coarsest. Since the LOD level used needs to be fixed, using finer LOD levels may result in false positive occlusion in cases where the actual rendered geometry is coarser, so use with caution.
    void SetOcclusionLodLevel(unsigned level);
    /// Set smoothing of heightmap.
    void SetSmoothing(bool enable);
    /// Set heightmap image. Dimensions should be a power of two + 1. Uses 8-bit grayscale, or optionally red as MSB and green as LSB for 16-bit accuracy. Return true if successful.
    bool SetHeightMap(Image* image);
    /// Set material.
    void SetMaterial(Material* material);
    /// Set draw distance for patches.
    void SetDrawDistance(float distance);
    /// Set shadow draw distance for patches.
    void SetShadowDistance(float distance);
    /// Set LOD bias for patches. Affects which terrain LOD to display.
    void SetLodBias(float bias);
    /// Set view mask for patches. Is and'ed with camera's view mask to see if the object should be rendered.
    void SetViewMask(unsigned mask);
    /// Set light mask for patches. Is and'ed with light's and zone's light mask to see if the object should be lit.
    void SetLightMask(unsigned mask);
    /// Set shadow mask for patches. Is and'ed with light's light mask and zone's shadow mask to see if the object should be rendered to a shadow map.
    void SetShadowMask(unsigned mask);
    /// Set zone mask for patches. Is and'ed with zone's zone mask to see if the object should belong to the zone.
    void SetZoneMask(unsigned mask);
    /// Set maximum number of per-pixel lights for patches. Default 0 is unlimited.
    void SetMaxLights(unsigned num);
    /// Set shadowcaster flag for patches.
    void SetCastShadows(bool enable);
    /// Set occlusion flag for patches. Occlusion uses the coarsest LOD by default.
    void SetOccluder(bool enable);
    /// Set occludee flag for patches.
    void SetOccludee(bool enable);
    /// Apply changes from the heightmap image.
    void ApplyHeightMap();

    /// Return patch quads per side.
    int GetPatchSize() const { return patchSize_; }

    /// Return vertex and height spacing.
    const Vector3& GetSpacing() const { return spacing_; }

    /// Return heightmap size in vertices.
    const IntVector2& GetNumVertices() const { return numVertices_; }

    /// Return heightmap size in patches.
    const IntVector2& GetNumPatches() const { return numPatches_; }

    /// Return maximum number of LOD levels for terrain patches. This can be between 1-4.
    unsigned GetMaxLodLevels() const { return maxLodLevels_; }
    
    /// Return LOD level used for occlusion.
    unsigned GetOcclusionLodLevel() const { return occlusionLodLevel_; }
    
    /// Return whether smoothing is in use.
    bool GetSmoothing() const { return smoothing_; }

    /// Return heightmap image.
    Image* GetHeightMap() const;
    /// Return material.
    Material* GetMaterial() const;
    /// Return patch by index.
    TerrainPatch* GetPatch(unsigned index) const;
    /// Return patch by patch coordinates.
    TerrainPatch* GetPatch(int x, int z) const;
    /// Return height at world coordinates.
    float GetHeight(const Vector3& worldPosition) const;
    /// Return normal at world coordinates.
    Vector3 GetNormal(const Vector3& worldPosition) const;
    /// Convert world position to heightmap pixel position. Note that the internal height data representation is reversed vertically, but in the heightmap image north is at the top.
    IntVector2 WorldToHeightMap(const Vector3& worldPosition) const;

    /// Return raw height data.
    SharedArrayPtr<float> GetHeightData() const { return heightData_; }

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

    /// Return maximum number of per-pixel lights.
    unsigned GetMaxLights() const { return maxLights_; }

    /// Return visible flag.
    bool IsVisible() const { return visible_; }

    /// Return shadowcaster flag.
    bool GetCastShadows() const { return castShadows_; }

    /// Return occluder flag.
    bool IsOccluder() const { return occluder_; }

    /// Return occludee flag.
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
    void SetOcclusionLodLevelAttr(unsigned value);
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
    void SetNeighbors(TerrainPatch* patch);
    /// Set heightmap image and optionally recreate the geometry immediately. Return true if successful.
    bool SetHeightMapInternal(Image* image, bool recreateNow);
    /// Handle heightmap image reload finished.
    void HandleHeightMapReloadFinished(StringHash eventType, VariantMap& eventData);

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
    Vector<WeakPtr<TerrainPatch> > patches_;
    /// Draw ranges for different LODs and stitching combinations.
    PODVector<Pair<unsigned, unsigned> > drawRanges_;
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
    unsigned occlusionLodLevel_;
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
    /// Terrain needs regeneration flag.
    bool recreateTerrain_;
};

}
