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

#include "../Graphics/Batch.h"
#include "../Math/Color.h"
#include "../Graphics/Drawable.h"
#include "../Container/HashSet.h"
#include "../Core/Mutex.h"
#include "../Graphics/Viewport.h"

namespace Urho3D
{

class Geometry;
class Drawable;
class Light;
class Material;
class Pass;
class Technique;
class Octree;
class Graphics;
class RenderPath;
class RenderSurface;
class ResourceCache;
class Skeleton;
class OcclusionBuffer;
class Texture2D;
class TextureCube;
class View;
class Zone;

static const int SHADOW_MIN_PIXELS = 64;
static const int INSTANCING_BUFFER_DEFAULT_SIZE = 1024;

/// Light vertex shader variations.
enum LightVSVariation
{
    LVS_DIR = 0,
    LVS_SPOT,
    LVS_POINT,
    LVS_SHADOW,
    LVS_SPOTSHADOW,
    LVS_POINTSHADOW,
    MAX_LIGHT_VS_VARIATIONS
};

/// Per-vertex light vertex shader variations.
enum VertexLightVSVariation
{
    VLVS_NOLIGHTS = 0,
    VLVS_1LIGHT,
    VLVS_2LIGHTS,
    VLVS_3LIGHTS,
    VLVS_4LIGHTS,
    MAX_VERTEXLIGHT_VS_VARIATIONS
};

/// Light pixel shader variations.
enum LightPSVariation
{
    LPS_NONE = 0,
    LPS_SPOT,
    LPS_POINT,
    LPS_POINTMASK,
    LPS_SPEC,
    LPS_SPOTSPEC,
    LPS_POINTSPEC,
    LPS_POINTMASKSPEC,
    LPS_SHADOW,
    LPS_SPOTSHADOW,
    LPS_POINTSHADOW,
    LPS_POINTMASKSHADOW,
    LPS_SHADOWSPEC,
    LPS_SPOTSHADOWSPEC,
    LPS_POINTSHADOWSPEC,
    LPS_POINTMASKSHADOWSPEC,
    MAX_LIGHT_PS_VARIATIONS
};

/// Deferred light volume vertex shader variations.
enum DeferredLightVSVariation
{
    DLVS_NONE = 0,
    DLVS_DIR,
    DLVS_ORTHO,
    DLVS_ORTHODIR,
    MAX_DEFERRED_LIGHT_VS_VARIATIONS
};

/// Deferred light volume pixels shader variations.
enum DeferredLightPSVariation
{
    DLPS_NONE = 0,
    DLPS_SPOT,
    DLPS_POINT,
    DLPS_POINTMASK,
    DLPS_SPEC,
    DLPS_SPOTSPEC,
    DLPS_POINTSPEC,
    DLPS_POINTMASKSPEC,
    DLPS_SHADOW,
    DLPS_SPOTSHADOW,
    DLPS_POINTSHADOW,
    DLPS_POINTMASKSHADOW,
    DLPS_SHADOWSPEC,
    DLPS_SPOTSHADOWSPEC,
    DLPS_POINTSHADOWSPEC,
    DLPS_POINTMASKSHADOWSPEC,
    DLPS_ORTHO,
    DLPS_ORTHOSPOT,
    DLPS_ORTHOPOINT,
    DLPS_ORTHOPOINTMASK,
    DLPS_ORTHOSPEC,
    DLPS_ORTHOSPOTSPEC,
    DLPS_ORTHOPOINTSPEC,
    DLPS_ORTHOPOINTMASKSPEC,
    DLPS_ORTHOSHADOW,
    DLPS_ORTHOSPOTSHADOW,
    DLPS_ORTHOPOINTSHADOW,
    DLPS_ORTHOPOINTMASKSHADOW,
    DLPS_ORTHOSHADOWSPEC,
    DLPS_ORTHOSPOTSHADOWSPEC,
    DLPS_ORTHOPOINTSHADOWSPEC,
    DLPS_ORTHOPOINTMASKSHADOWSPEC,
    MAX_DEFERRED_LIGHT_PS_VARIATIONS
};

/// High-level rendering subsystem. Manages drawing of 3D views.
class URHO3D_API Renderer : public Object
{
    OBJECT(Renderer);
    
public:
    /// Construct.
    Renderer(Context* context);
    /// Destruct.
    virtual ~Renderer();
    
    /// Set number of backbuffer viewports to render.
    void SetNumViewports(unsigned num);
    /// Set a backbuffer viewport.
    void SetViewport(unsigned index, Viewport* viewport);
    /// Set default renderpath.
    void SetDefaultRenderPath(RenderPath* renderPath);
    /// Set default renderpath from an XML file.
    void SetDefaultRenderPath(XMLFile* file);
    /// Set HDR rendering on/off.
    void SetHDRRendering(bool enable);
    /// Set specular lighting on/off.
    void SetSpecularLighting(bool enable);
    /// Set texture anisotropy.
    void SetTextureAnisotropy(int level);
    /// Set texture filtering.
    void SetTextureFilterMode(TextureFilterMode mode);
    /// Set texture quality level.
    void SetTextureQuality(int quality);
    /// Set material quality level.
    void SetMaterialQuality(int quality);
    /// Set shadows on/off.
    void SetDrawShadows(bool enable);
    /// Set shadow map resolution.
    void SetShadowMapSize(int size);
    /// Set shadow quality (amount of samples and bit depth.)
    void SetShadowQuality(int quality);
    /// Set reuse of shadow maps. Default is true. If disabled, also transparent geometry can be shadowed.
    void SetReuseShadowMaps(bool enable);
    /// Set maximum number of shadow maps created for one resolution. Only has effect if reuse of shadow maps is disabled.
    void SetMaxShadowMaps(int shadowMaps);
    /// Set dynamic instancing on/off.
    void SetDynamicInstancing(bool enable);
    /// Set minimum number of instances required in a batch group to render as instanced.
    void SetMinInstances(int instances);
    /// Set maximum number of triangles per object for instancing.
    void SetMaxInstanceTriangles(int triangles);
    /// Set maximum number of sorted instances per batch group. If exceeded, instances are rendered unsorted.
    void SetMaxSortedInstances(int instances);
    /// Set maximum number of occluder trianges.
    void SetMaxOccluderTriangles(int triangles);
    /// Set occluder buffer width.
    void SetOcclusionBufferSize(int size);
    /// Set required screen size (1.0 = full screen) for occluders.
    void SetOccluderSizeThreshold(float screenSize);
    /// Set shadow depth bias multiplier for mobile platforms (OpenGL ES.) No effect on desktops. Default 2.
    void SetMobileShadowBiasMul(float mul);
    /// Set shadow depth bias addition for mobile platforms (OpenGL ES.)  No effect on desktops. Default 0.0001.
    void SetMobileShadowBiasAdd(float add);
    /// Force reload of shaders.
    void ReloadShaders();
    
    /// Return number of backbuffer viewports.
    unsigned GetNumViewports() const { return viewports_.Size(); }
    /// Return backbuffer viewport by index.
    Viewport* GetViewport(unsigned index) const;
    /// Return default renderpath.
    RenderPath* GetDefaultRenderPath() const;
    /// Return whether HDR rendering is enabled.
    bool GetHDRRendering() const { return hdrRendering_; }
    /// Return whether specular lighting is enabled.
    bool GetSpecularLighting() const { return specularLighting_; }
    /// Return whether drawing shadows is enabled.
    bool GetDrawShadows() const { return drawShadows_; }
    /// Return texture anisotropy.
    int GetTextureAnisotropy() const { return textureAnisotropy_; }
    /// Return texture filtering.
    TextureFilterMode GetTextureFilterMode() const { return textureFilterMode_; }
    /// Return texture quality level.
    int GetTextureQuality() const { return textureQuality_; }
    /// Return material quality level.
    int GetMaterialQuality() const { return materialQuality_; }
    /// Return shadow map resolution.
    int GetShadowMapSize() const { return shadowMapSize_; }
    /// Return shadow quality.
    int GetShadowQuality() const { return shadowQuality_; }
    /// Return whether shadow maps are reused.
    bool GetReuseShadowMaps() const { return reuseShadowMaps_; }
    /// Return maximum number of shadow maps per resolution.
    int GetMaxShadowMaps() const { return maxShadowMaps_; }
    /// Return whether dynamic instancing is in use.
    bool GetDynamicInstancing() const { return dynamicInstancing_; }
    /// Return minimum number of instances required in a batch group to render as instanced.
    int GetMinInstances() const { return minInstances_; }
    /// Return maximum number of triangles per object for instancing.
    int GetMaxInstanceTriangles() const { return maxInstanceTriangles_; }
    /// Return maximum number of sorted instances per batch group.
    int GetMaxSortedInstances() const { return maxSortedInstances_; }
    /// Return maximum number of occluder triangles.
    int GetMaxOccluderTriangles() const { return maxOccluderTriangles_; }
    /// Return occlusion buffer width.
    int GetOcclusionBufferSize() const { return occlusionBufferSize_; }
    /// Return occluder screen size threshold.
    float GetOccluderSizeThreshold() const { return occluderSizeThreshold_; }
    /// Return shadow depth bias multiplier for mobile platforms.
    float GetMobileShadowBiasMul() const { return mobileShadowBiasMul_; }
    /// Return shadow depth bias addition for mobile platforms.
    float GetMobileShadowBiasAdd() const { return mobileShadowBiasAdd_; }
    /// Return number of views rendered.
    unsigned GetNumViews() const { return views_.Size(); }
    /// Return number of primitives rendered.
    unsigned GetNumPrimitives() const { return numPrimitives_; }
    /// Return number of batches rendered.
    unsigned GetNumBatches() const { return numBatches_; }
    /// Return number of geometries rendered.
    unsigned GetNumGeometries(bool allViews = false) const;
    /// Return number of lights rendered.
    unsigned GetNumLights(bool allViews = false) const;
    /// Return number of shadow maps rendered.
    unsigned GetNumShadowMaps(bool allViews = false) const;
    /// Return number of occluders rendered.
    unsigned GetNumOccluders(bool allViews = false) const;
    /// Return the default zone.
    Zone* GetDefaultZone() const { return defaultZone_; }
    /// Return the default material.
    Material* GetDefaultMaterial() const { return defaultMaterial_; }
    /// Return the default range attenuation texture.
    Texture2D* GetDefaultLightRamp() const { return defaultLightRamp_; }
    /// Return the default spotlight attenuation texture.
    Texture2D* GetDefaultLightSpot() const { return defaultLightSpot_; }
    /// Return the shadowed pointlight face selection cube map.
    TextureCube* GetFaceSelectCubeMap() const { return faceSelectCubeMap_; }
    /// Return the shadowed pointlight indirection cube map.
    TextureCube* GetIndirectionCubeMap() const { return indirectionCubeMap_; }
    /// Return the instancing vertex buffer
    VertexBuffer* GetInstancingBuffer() const { return dynamicInstancing_ ? instancingBuffer_ : (VertexBuffer*)0; }
    /// Return the frame update parameters.
    const FrameInfo& GetFrameInfo() const { return frame_; }
    
    /// Update for rendering. Called by HandleRenderUpdate().
    void Update(float timeStep);
    /// Render. Called by Engine.
    void Render();
    /// Add debug geometry to the debug renderer.
    void DrawDebugGeometry(bool depthTest);
    /// Queue a render surface's viewports for rendering. Called by the surface, or by View.
    void QueueRenderSurface(RenderSurface* renderTarget);
    /// Queue a viewport for rendering. Null surface means backbuffer.
    void QueueViewport(RenderSurface* renderTarget, Viewport* viewport);
    
    /// Return volume geometry for a light.
    Geometry* GetLightGeometry(Light* light);
    /// Return quad geometry used in postprocessing.
    Geometry* GetQuadGeometry();
    /// Allocate a shadow map. If shadow map reuse is disabled, a different map is returned each time.
    Texture2D* GetShadowMap(Light* light, Camera* camera, unsigned viewWidth, unsigned viewHeight);
    /// Allocate a rendertarget or depth-stencil texture for deferred rendering or postprocessing. Should only be called during actual rendering, not before.
    Texture2D* GetScreenBuffer(int width, int height, unsigned format, bool filtered, bool srgb, unsigned persistentKey = 0);
    /// Allocate a depth-stencil surface that does not need to be readable. Should only be called during actual rendering, not before.
    RenderSurface* GetDepthStencil(int width, int height);
    /// Allocate an occlusion buffer.
    OcclusionBuffer* GetOcclusionBuffer(Camera* camera);
    /// Allocate a temporary shadow camera and a scene node for it. Is thread-safe.
    Camera* GetShadowCamera();
    /// Choose shaders for a forward rendering batch.
    void SetBatchShaders(Batch& batch, Technique* tech, bool allowShadows = true);
    /// Choose shaders for a deferred light volume batch.
    void SetLightVolumeBatchShaders(Batch& batch, const String& vsName, const String& psName, const String& vsDefines, const String& psDefines);
    /// Set cull mode while taking possible projection flipping into account.
    void SetCullMode(CullMode mode, Camera* camera);
    /// Ensure sufficient size of the instancing vertex buffer. Return true if successful.
    bool ResizeInstancingBuffer(unsigned numInstances);
    /// Save the screen buffer allocation status. Called by View.
    void SaveScreenBufferAllocations();
    /// Restore the screen buffer allocation status. Called by View.
    void RestoreScreenBufferAllocations();
    /// Optimize a light by scissor rectangle.
    void OptimizeLightByScissor(Light* light, Camera* camera);
    /// Optimize a light by marking it to the stencil buffer and setting a stencil test.
    void OptimizeLightByStencil(Light* light, Camera* camera);
    /// Return a scissor rectangle for a light.
    const Rect& GetLightScissor(Light* light, Camera* camera);
    
private:
    /// Initialize when screen mode initially set.
    void Initialize();
    /// Reload shaders.
    void LoadShaders();
    /// Reload shaders for a material pass.
    void LoadPassShaders(Technique* tech, StringHash passType);
    /// Release shaders used in materials.
    void ReleaseMaterialShaders();
    /// Reload textures.
    void ReloadTextures();
    /// Create light volume geometries.
    void CreateGeometries();
    /// Create instancing vertex buffer.
    void CreateInstancingBuffer();
    /// Create point light shadow indirection texture data.
    void SetIndirectionTextureData();
    /// Prepare for rendering of a new view.
    void PrepareViewRender();
    /// Remove unused occlusion and screen buffers.
    void RemoveUnusedBuffers();
    /// Reset shadow map allocation counts.
    void ResetShadowMapAllocations();
    /// Reset screem buffer allocation counts.
    void ResetScreenBufferAllocations();
    /// Remove all shadow maps. Called when global shadow map resolution or format is changed.
    void ResetShadowMaps();
    /// Remove all occlusion and screen buffers.
    void ResetBuffers();
    /// Handle screen mode event.
    void HandleScreenMode(StringHash eventType, VariantMap& eventData);
    /// Handle graphics features (re)check event. Event only sent by D3D9Graphics class.
    void HandleGraphicsFeatures(StringHash eventType, VariantMap& eventData);
    /// Handle render update event.
    void HandleRenderUpdate(StringHash eventType, VariantMap& eventData);
    
    /// Graphics subsystem.
    WeakPtr<Graphics> graphics_;
    /// Default renderpath.
    SharedPtr<RenderPath> defaultRenderPath_;
    /// Default zone.
    SharedPtr<Zone> defaultZone_;
    /// Directional light quad geometry.
    SharedPtr<Geometry> dirLightGeometry_;
    /// Spot light volume geometry.
    SharedPtr<Geometry> spotLightGeometry_;
    /// Point light volume geometry.
    SharedPtr<Geometry> pointLightGeometry_;
    /// Instance stream vertex buffer.
    SharedPtr<VertexBuffer> instancingBuffer_;
    /// Default material.
    SharedPtr<Material> defaultMaterial_;
    /// Default range attenuation texture.
    SharedPtr<Texture2D> defaultLightRamp_;
    /// Default spotlight attenuation texture.
    SharedPtr<Texture2D> defaultLightSpot_;
    /// Face selection cube map for shadowed pointlights.
    SharedPtr<TextureCube> faceSelectCubeMap_;
    /// Indirection cube map for shadowed pointlights.
    SharedPtr<TextureCube> indirectionCubeMap_;
    /// Reusable scene nodes with shadow camera components.
    Vector<SharedPtr<Node> > shadowCameraNodes_;
    /// Reusable occlusion buffers.
    Vector<SharedPtr<OcclusionBuffer> > occlusionBuffers_;
    /// Shadow maps by resolution.
    HashMap<int, Vector<SharedPtr<Texture2D> > > shadowMaps_;
    /// Shadow map dummy color buffers by resolution.
    HashMap<int, SharedPtr<Texture2D> > colorShadowMaps_;
    /// Shadow map allocations by resolution.
    HashMap<int, PODVector<Light*> > shadowMapAllocations_;
    /// Screen buffers by resolution and format.
    HashMap<long long, Vector<SharedPtr<Texture2D> > > screenBuffers_;
    /// Current screen buffer allocations by resolution and format.
    HashMap<long long, unsigned> screenBufferAllocations_;
    /// Saved status of screen buffer allocations for restoring.
    HashMap<long long, unsigned> savedScreenBufferAllocations_;
    /// Cache for light scissor queries.
    HashMap<Pair<Light*, Camera*>, Rect> lightScissorCache_;
    /// Backbuffer viewports.
    Vector<SharedPtr<Viewport> > viewports_;
    /// Render surface viewports queued for update.
    Vector<Pair<WeakPtr<RenderSurface>, WeakPtr<Viewport> > > queuedViewports_;
    /// Views that have been processed this frame.
    Vector<WeakPtr<View> > views_;
    /// Octrees that have been updated during the frame.
    HashSet<Octree*> updatedOctrees_;
    /// Techniques for which missing shader error has been displayed.
    HashSet<Technique*> shaderErrorDisplayed_;
    /// Mutex for shadow camera allocation.
    Mutex rendererMutex_;
    /// Current variation names for deferred light volume shaders.
    Vector<String> deferredLightPSVariations_;
    /// Frame info for rendering.
    FrameInfo frame_;
    /// Texture anisotropy level.
    int textureAnisotropy_;
    /// Texture filtering mode.
    TextureFilterMode textureFilterMode_;
    /// Texture quality level.
    int textureQuality_;
    /// Material quality level.
    int materialQuality_;
    /// Shadow map resolution.
    int shadowMapSize_;
    /// Shadow quality.
    int shadowQuality_;
    /// Maximum number of shadow maps per resolution.
    int maxShadowMaps_;
    /// Minimum number of instances required in a batch group to render as instanced.
    int minInstances_;
    /// Maximum triangles per object for instancing.
    int maxInstanceTriangles_;
    /// Maximum sorted instances per batch group.
    int maxSortedInstances_;
    /// Maximum occluder triangles.
    int maxOccluderTriangles_;
    /// Occlusion buffer width.
    int occlusionBufferSize_;
    /// Occluder screen size threshold.
    float occluderSizeThreshold_;
    /// Mobile platform shadow depth bias multiplier.
    float mobileShadowBiasMul_;
    /// Mobile platform shadow depth bias addition.
    float mobileShadowBiasAdd_;
    /// Number of occlusion buffers in use.
    unsigned numOcclusionBuffers_;
    /// Number of temporary shadow cameras in use.
    unsigned numShadowCameras_;
    /// Number of primitives (3D geometry only.)
    unsigned numPrimitives_;
    /// Number of batches (3D geometry only.)
    unsigned numBatches_;
    /// Frame number on which shaders last changed.
    unsigned shadersChangedFrameNumber_;
    /// Current stencil value for light optimization.
    unsigned char lightStencilValue_;
    /// HDR rendering flag.
    bool hdrRendering_;
    /// Specular lighting flag.
    bool specularLighting_;
    /// Draw shadows flag.
    bool drawShadows_;
    /// Shadow map reuse flag.
    bool reuseShadowMaps_;
    /// Dynamic instancing flag.
    bool dynamicInstancing_;
    /// Shaders need reloading flag.
    bool shadersDirty_;
    /// Initialized flag.
    bool initialized_;
    /// Flag for views needing reset.
    bool resetViews_;
};

}
