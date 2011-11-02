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

#include "Batch.h"
#include "Color.h"
#include "Drawable.h"
#include "HashMap.h"
#include "HashSet.h"
#include "Mutex.h"
#include "RenderSurface.h"

class DebugRenderer;
class Geometry;
class Drawable;
class Light;
class Material;
class Pass;
class Technique;
class Octree;
class Graphics;
class ResourceCache;
class Skeleton;
class OcclusionBuffer;
class Texture2D;
class TextureCube;
class View;
class Zone;

static const int SHADOW_MIN_PIXELS = 64;
static const int NUM_LIGHT_TYPES = 3;
static const int NUM_SHADOWMAP_RESOLUTIONS = 3;
static const int INSTANCING_BUFFER_DEFAULT_SIZE = 1024;

/// Light vertex shader variations.
enum LightVSVariation
{
    LVS_DIR = 0,
    LVS_SPOT,
    LVS_POINT,
    LVS_SPEC,
    LVS_SPOTSPEC,
    LVS_POINTSPEC,
    LVS_SHADOW,
    LVS_SPOTSHADOW,
    LVS_POINTSHADOW,
    LVS_DIRSPECSHADOW,
    LVS_SPOTSPECSHADOW,
    LVS_POINTSPECSHADOW,
    MAX_LIGHT_VS_VARIATIONS
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

/// High-level rendering subsystem. Manages drawing of 3D views.
class Renderer : public Object
{
    OBJECT(Object);
    
public:
    /// Construct.
    Renderer(Context* context);
    /// Destruct.
    virtual ~Renderer();
    
    /// %Set number of viewports to render.
    void SetNumViewports(unsigned num);
    /// %Set a viewport.
    void SetViewport(unsigned index, const Viewport& viewport);
    /// %Set specular lighting on/off.
    void SetSpecularLighting(bool enable);
    /// %Set texture anisotropy.
    void SetTextureAnisotropy(int level);
    /// %Set texture filtering.
    void SetTextureFilterMode(TextureFilterMode mode);
    /// %Set texture quality level.
    void SetTextureQuality(int quality);
    /// %Set material quality level.
    void SetMaterialQuality(int quality);
    /// %Set shadows on/off.
    void SetDrawShadows(bool enable);
    /// %Set shadow map resolution.
    void SetShadowMapSize(int size);
    /// %Set shadow quality (amount of samples and bit depth.)
    void SetShadowQuality(int quality);
    /// %Set reuse of shadow maps. Default is true. If disabled, also transparent geometry can be shadowed.
    void SetReuseShadowMaps(bool enable);
    /// %Set maximum number of shadow maps created for one resolution. Only has effect if reuse of shadow maps is disabled.
    void SetMaxShadowMaps(int shadowMaps);
    /// %Set maximum number of directional light shadow map cascades. Affects the size of directional light shadow maps.
    void SetMaxShadowCascades(int cascades);
    /// %Set light stencil optimization on/off.
    void SetLightStencilMasking(bool enable);
    /// %Set dynamic instancing on/off.
    void SetDynamicInstancing(bool enable);
    /// %Set maximum number of triangles per object for instancing.
    void SetMaxInstanceTriangles(int triangles);
    /// %Set maximum number of occluder trianges.
    void SetMaxOccluderTriangles(int triangles);
    /// %Set occluder buffer width.
    void SetOcclusionBufferSize(int size);
    /// %Set required screen size (1.0 = full screen) for occluders.
    void SetOccluderSizeThreshold(float screenSize);
    /// Return number of viewports.
    unsigned GetNumViewports() const { return viewports_.Size(); }
    /// Return viewport.
    const Viewport& GetViewport(unsigned index) const;
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
    /// Return maximum number of directional light shadow map cascades.
    int GetMaxShadowCascades() const { return maxShadowCascades_; }
    /// Return whether light stencil optimization is in use.
    bool GetLightStencilMasking() const { return lightStencilMasking_; }
    /// Return whether dynamic instancing is in use.
    bool GetDynamicInstancing() const { return dynamicInstancing_; }
    /// Return maximum number of triangles per object for instancing.
    int GetMaxInstanceTriangles() { return maxInstanceTriangles_; }
    /// Return maximum number of occluder triangles.
    int GetMaxOccluderTriangles() const { return maxOccluderTriangles_; }
    /// Return occlusion buffer width.
    int GetOcclusionBufferSize() const { return occlusionBufferSize_; }
    /// Return occluder screen size threshold.
    float GetOccluderSizeThreshold() const { return occluderSizeThreshold_; }
    /// Return number of views rendered.
    unsigned GetNumViews() const { return numViews_; }
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
    /// Return a vertex shader by name.
    ShaderVariation* GetVertexShader(const String& name, bool checkExists = false) const;
    /// Return a pixel shader by name.
    ShaderVariation* GetPixelShader(const String& name, bool checkExists = false) const;
    /// Return the stencil vertex shader.
    ShaderVariation* GetStencilVS() const { return stencilVS_; }
    /// Return the stencil pixel shader.
    ShaderVariation* GetStencilPS() const { return stencilPS_; }
    /// Return the frame update parameters.
    const FrameInfo& GetFrameInfo() { return frame_; }
    
    /// Update for rendering. Called by HandleRenderUpdate().
    void Update(float timeStep);
    /// Render. Called by Engine.
    void Render();
    /// Add debug geometry to the debug renderer(s).
    void DrawDebugGeometry(bool depthTest);
    /// Add a view. Return true if successful.
    bool AddView(RenderSurface* renderTarget, const Viewport& viewport);
    /// Return volume geometry for a light.
    Geometry* GetLightGeometry(Light* light);
    /// Allocate a shadow map. If shadow map reuse is disabled, a different map is returned each time.
    Texture2D* GetShadowMap(Light* light, Camera* camera, unsigned viewWidth, unsigned viewHeight);
    /// Allocate an occlusion buffer.
    OcclusionBuffer* GetOcclusionBuffer(Camera* camera);
    /// Allocate a temporary shadow camera and a scene node for it. Is thread-safe.
    Camera* GetShadowCamera();
    /// Get a shader program.
    ShaderVariation* GetShader(const String& name, const String& extension, bool checkExists) const;
    /// Choose shaders for a batch.
    void SetBatchShaders(Batch& batch, Technique* technique, Pass* pass, bool allowShadows = true);
    /// Ensure sufficient size of the instancing vertex buffer. Return true if successful.
    bool ResizeInstancingBuffer(unsigned numInstances);
    /// Reset shadow map allocation counts.
    void ResetShadowMapAllocations();
    
private:
    /// Initialize when screen mode initially set.
    void Initialize();
    /// Clear views from previous frame.
    void ResetViews();
    /// Reload shaders.
    void LoadShaders();
    /// Reload shaders for a material technique.
    void LoadMaterialShaders(Technique* technique);
    /// Reload shaders for a material pass.
    void LoadPassShaders(Technique* technique, PassType type, bool allowShadows = true);
    /// Release shaders used in materials.
    void ReleaseMaterialShaders();
    /// Reload textures.
    void ReloadTextures();
    /// Create light volume geometries.
    void CreateGeometries();
    /// Create instancing vertex buffer.
    void CreateInstancingBuffer();
    /// Remove all shadow maps. Called when global shadow map resolution or format is changed.
    void ResetShadowMaps();
    /// Handle screen mode event.
    void HandleScreenMode(StringHash eventType, VariantMap& eventData);
    /// Handle graphics features (re)check event.
    void HandleGraphicsFeatures(StringHash eventType, VariantMap& eventData);
    /// Handle render update event.
    void HandleRenderUpdate(StringHash eventType, VariantMap& eventData);
    
    /// Graphics subsystem.
    WeakPtr<Graphics> graphics_;
    /// Resource cache subsystem.
    WeakPtr<ResourceCache> cache_;
    /// Default zone.
    SharedPtr<Zone> defaultZone_;
    /// Point light volume geometry.
    SharedPtr<Geometry> pointLightGeometry_;
    /// Spot light volume geometry.
    SharedPtr<Geometry> spotLightGeometry_;
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
    /// Stencil rendering vertex shader.
    SharedPtr<ShaderVariation> stencilVS_;
    /// Stencil rendering pixel shader.
    SharedPtr<ShaderVariation> stencilPS_;
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
    /// Shadow map stencil buffer, fallback mode only.
    SharedPtr<Texture2D> shadowDepthStencil_;
    /// Viewports.
    Vector<Viewport> viewports_;
    /// Views.
    Vector<SharedPtr<View> > views_;
    /// Octrees that have been updated during the frame.
    HashSet<Octree*> updateOctrees_;
    /// Techniques for which missing shader error has been displayed.
    HashSet<Technique*> shaderErrorDisplayed_;
    /// Mutex for shadow camera allocation.
    Mutex rendererMutex_;
    /// Vertex shader format.
    String vsFormat_;
    /// Pixel shader format.
    String psFormat_;
    /// Base directory for shaders.
    String shaderPath_;
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
    /// Maximum number of directional light shadow cascades.
    int maxShadowCascades_;
    /// Maximum triangles per object for instancing.
    int maxInstanceTriangles_;
    /// Maximum occluder triangles.
    int maxOccluderTriangles_;
    /// Occlusion buffer width.
    int occlusionBufferSize_;
    /// Occluder screen size threshold.
    float occluderSizeThreshold_;
    /// Number of views.
    unsigned numViews_;
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
    /// Specular lighting flag.
    bool specularLighting_;
    /// Draw shadows flag.
    bool drawShadows_;
    /// Shadow map reuse flag.
    bool reuseShadowMaps_;
    /// Light stencil optimization flag.
    bool lightStencilMasking_;
    /// Dynamic instancing flag.
    bool dynamicInstancing_;
    /// Shaders need reloading flag.
    bool shadersDirty_;
    /// Initialized flag.
    bool initialized_;
};
