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

#ifndef RENDERER_PIPELINE_H
#define RENDERER_PIPELINE_H

#include "Batch.h"
#include "Camera.h"
#include "Color.h"
#include "EventListener.h"
#include "ShaderDefs.h"
#include "Rect.h"
#include "SharedPtr.h"
#include "Zone.h"

#include <map>
#include <string>

class DebugRenderer;
class Geometry;
class GeometryNode;
class Light;
class Material;
class MaterialPass;
class MaterialTechnique;
class Octree;
class Renderer;
class RenderSurface;
class ResourceCache;
class Skeleton;
class OcclusionBuffer;
class Texture;
class Texture2D;
class TextureCube;
class TiXmlElement;
class View;

static const int SHADOW_MIN_PIXELS = 64;
static const float MAX_ELAPSED_TIME = 2048.0f; // In seconds

//! Deferred rendering edge filter parameters
struct EdgeFilterParameters
{
    //! Construct as undefined
    EdgeFilterParameters()
    {
    }
    
    //! Construct with initial values
    EdgeFilterParameters(float threshold, float filterStep, float maxFilter, float maxScale) :
        mThreshold(threshold),
        mFilterStep(filterStep),
        mMaxFilter(maxFilter),
        mMaxScale(maxScale)
    {
    }
    
    //! Validate parameters
    void validate();
    
    //! Intensity difference threshold needed to pass pixel
    float mThreshold;
    //! Filter increase step for each passed neighbor pixel
    float mFilterStep;
    //! Max filter level
    float mMaxFilter;
    //! Scaling factor for intensity difference
    float mMaxScale;
};

//! High-level rendering pipeline
class Pipeline : public RefCounted, public EventListener
{
    friend class View;
    
public:
    //! Construct with renderer subsystem and resource cache pointers
    Pipeline(Renderer* renderer, ResourceCache* cache);
    //! Destruct
    virtual ~Pipeline();
    
    //! Update for rendering
    bool update(float timeStep, Octree* octree, Camera* camera);
    //! Render
    bool render();
    //! Render debug geometry
    void drawDebugGeometry(DebugRenderer* debug);
    
    //! Set specular lighting on/off
    void setSpecularLighting(bool enable);
    //! Set shadows on/off
    void setDrawShadows(bool enable);
    //! Set texture anisotropy
    void setTextureAnisotropy(int level);
    //! Set texture filtering
    void setTextureFilterMode(TextureFilterMode mode);
    //! Set texture quality level
    void setTextureQuality(int quality);
    //! Set material quality level
    void setMaterialQuality(int quality);
    //! Set light detail level
    void setLightDetailLevel(int detailLevel);
    //! Set shadow map resolution
    void setShadowMapSize(int size);
    //! Set shadow map 24-bit depth on/off
    void setShadowMapHiresDepth(bool enable);
    //! Set maximum number of occluder trianges
    void setMaxOccluderTriangles(int triangles);
    //! Set occluder buffer width
    void setOcclusionBufferSize(int size);
    //! Set required size (1.0 = full screen) for occluders
    void setOccluderSizeThreshold(float screenSize);
    //! Set deferred rendering edge filter parameters. Only has effect if nonzero multisample level is set in Renderer::setMode().
    void setEdgeFilter(const EdgeFilterParameters& parameters);
    
    //! Return current frame number
    unsigned getFrameNumber() const { return mFrameNumber; }
    //! Return elapsed time
    float getElapsedTime() const { return mElapsedTime; }
    //! Return specular lighting flag
    bool getSpecularLighting() const { return mSpecularLighting; }
    //! Return draw shadows flag
    bool getDrawShadows() const { return mDrawShadows; }
    //! Return texture anisotropy
    int getTextureAnisotropy() const { return mTextureAnisotropy; }
    //! Return texture filtering
    TextureFilterMode getTextureFilterMode() const { return mTextureFilterMode; }
    //! Return texture quality level
    int getTextureQuality() const { return mTextureQuality; }
    //! Return material quality level
    int getMaterialQuality() const { return mMaterialQuality; }
    //! Return light detail level
    int getLightDetailLevel() const { return mLightDetailLevel; }
    //! Return shadow map resolution
    int getShadowMapSize() const { return mShadowMapSize; }
    //! Return shadow map 24-bit depth flag
    bool getShadowMapHiresDepth() const { return mShadowMapHiresDepth; }
    //! Return maximum number of occluder triangles
    int getMaxOccluderTriangles() const { return mMaxOccluderTriangles; }
    //! Return occlusion buffer width
    int getOcclusionBufferSize() const { return mOcclusionBufferSize; }
    //! Return occluder screen size threshold
    float getOccluderSizeThreshold() const { return mOccluderSizeThreshold; }
    //! Return deferred rendering edge filter parameters
    const EdgeFilterParameters& getEdgeFilter() const { return mEdgeFilter; }
    //! Return number of views rendered
    unsigned getNumViews() const { return mNumViews; }
    //! Return number of geometries rendered
    unsigned getNumGeometries(bool allViews = false) const;
    //! Return number of lights rendered
    unsigned getNumLights(bool allViews = false) const;
    //! Return number of shadow maps rendered
    unsigned getNumShadowMaps(bool allViews = false) const;
    //! Return number of occluders rendered
    unsigned getNumOccluders(bool allViews = false) const;
    //! Return number of directional light shadow occluders rendered
    unsigned getNumShadowOccluders(bool allViews = false) const;
    //! Return an occlusion buffer for inspection
    const OcclusionBuffer* getOcclusionBuffer(float aspectRatio, bool halfResolution = false);
    //! Return the default material
    Material* getDefaultMaterial() const { return mDefaultMaterial; }
    //! Return the default range attenuation texture
    Texture* getDefaultLightRamp() const { return mDefaultLightRamp; }
    //! Return the default spotlight attenuation texture
    Texture* getDefaultLightSpot() const { return mDefaultLightSpot; }
    //! Return a vertex shader by name
    VertexShader* getVertexShader(const std::string& name) const;
    //! Return a pixel shader by name
    PixelShader* getPixelShader(const std::string& name) const;
    //! Return the renderer subsystem
    Renderer* getRenderer() const { return mRenderer; }
    
private:
    //! Begin new frame
    void beginFrame(float timeStep);
    //! Clear views from previous frame
    void resetViews();
    //! Add a view
    void addView(Octree* octree, Camera* camera, RenderSurface* renderTarget);
    //! Return an occlusion buffer for use
    OcclusionBuffer* getOrCreateOcclusionBuffer(Camera& camera, int maxOccluderTriangles, bool halfResolution = false);
    //! Return a material technique for a scene node, considering material LOD
    MaterialTechnique* getMaterialTechnique(GeometryNode* node, unsigned index, int maxQuality);
    //! Return volume geometry for a light
    Geometry* getLightGeometry(Light* light);
    //! Return shadow map by resolution
    Texture2D* getShadowMap(float resolution);
    //! Choose shaders for a batch
    void setBatchShaders(Batch& batch, MaterialTechnique* technique, MaterialPass* pass, bool allowShadows = true);
    //! Choose light volume shaders for a batch
    void setLightVolumeShaders(Batch& batch);
    //! Reload shaders
    void loadShaders();
    //! Reload shaders for a material technique
    void loadMaterialShaders(MaterialTechnique* technique);
    //! Reload shaders for a material pass
    void loadMaterialPassShaders(MaterialTechnique* technique, PassType pass, bool allowShadows = true);
    //! Release shaders used in materials
    void releaseMaterialShaders();
    //! Reload textures
    void reloadTextures();
    //! Create light volume geometries
    void createGeometries();
    //! Create shadow maps
    bool createShadowMaps();
    //! Split a light into several for shadow mapping
    unsigned splitLight(Light* light);
    //! Internal function to create a light copy
    Light* createSplitLight(Light* original);
    //! Set up a light volume rendering batch
    void setupLightBatch(Batch& batch);
    //! Draw a full screen quad (either near or far)
    void drawFullScreenQuad(Camera& camera, VertexShader* vs, PixelShader* ps, bool nearQuad);
    //! Draw a split light to stencil buffer
    void drawSplitLightToStencil(Camera& camera, Light* light, bool clear = false);
    //! Handle window resized event
    void handleWindowResized(StringHash eventType, VariantMap& eventData);
    //! Return light vertex shaders
    const std::vector<SharedPtr<VertexShader> >& getLightVS() const { return mLightVS; }
    //! Return light pixel shaders
    const std::vector<SharedPtr<PixelShader> >& getLightPS() const { return mLightPS; }
    
    //! Renderer subsystem
    SharedPtr<Renderer> mRenderer;
    //! Resource cache
    SharedPtr<ResourceCache> mCache;
    //! Directional light geometry
    SharedPtr<Geometry> mDirLightGeometry;
    //! Point light volume geometry
    SharedPtr<Geometry> mPointLightGeometry;
    //! Spot light volume geometry
    SharedPtr<Geometry> mSpotLightGeometry;
    //! Default material
    SharedPtr<Material> mDefaultMaterial;
    //! Default range attenuation texture
    SharedPtr<Texture> mDefaultLightRamp;
    //! Default spotlight attenuation texture
    SharedPtr<Texture> mDefaultLightSpot;
    //! Full resolution shadow map
    SharedPtr<Texture2D> mFullShadowMap;
    //! Half resolution shadow map
    SharedPtr<Texture2D> mHalfShadowMap;
    //! Quarter resolution shadow map
    SharedPtr<Texture2D> mQuarterShadowMap;
    //! Full resolution shadow map dummy color texture
    SharedPtr<Texture2D> mFullShadowMapColor;
    //! Half resolution shadow map dummy color texture
    SharedPtr<Texture2D> mHalfShadowMapColor;
    //! Quarter resolution shadow map dummy color texture
    SharedPtr<Texture2D> mQuarterShadowMapColor;
    //! Stencil rendering vertex shader
    SharedPtr<VertexShader> mStencilVS;
    //! Stencil rendering pixel shader
    SharedPtr<PixelShader> mStencilPS;
    //! Light vertex shaders
    std::vector<SharedPtr<VertexShader> > mLightVS;
    //! Light pixel shaders
    std::vector<SharedPtr<PixelShader> > mLightPS;
    //! Reusable split lights
    std::vector<SharedPtr<Light> > mSplitLightStore;
    //! Occlusion buffers
    std::map<int, SharedPtr<OcclusionBuffer> > mOcclusionBuffers;
    //! Frame number
    unsigned mFrameNumber;
    //! Number of views
    unsigned mNumViews;
    //! Number of split lights
    unsigned mNumSplitLights;
    //! Elapsed time
    float mElapsedTime;
    //! Specular lighting flag
    bool mSpecularLighting;
    //! Draw shadows flag
    bool mDrawShadows;
    //! Texture anisotropy level
    int mTextureAnisotropy;
    //! Texture filtering mode
    TextureFilterMode mTextureFilterMode;
    //! Texture quality level
    int mTextureQuality;
    //! Material quality level
    int mMaterialQuality;
    //! Light detail level
    int mLightDetailLevel;
    //! Shadow map resolution
    int mShadowMapSize;
    //! Shadow map 24-bit depth flag
    bool mShadowMapHiresDepth;
    //! Maximum occluder triangles
    int mMaxOccluderTriangles;
    //! Occlusion buffer width
    int mOcclusionBufferSize;
    //! Occluder screen size threshold
    float mOccluderSizeThreshold;
    //! Deferred rendering edge filter parameters
    EdgeFilterParameters mEdgeFilter;
    //! Frame number on which shaders last changed
    unsigned mShadersChangedFrameNumber;
    //! Shaders need reloading flag
    bool mShadersDirty;
    //! Vertex shader format
    std::string mVSFormat;
    //! Pixel shader format
    std::string mPSFormat;
    //! Base directory for shaders
    std::string mShaderPath;
    //! Light shader base name (deferred and prepass have different light shaders)
    std::string mLightShaderName;
    //! Views
    std::vector<SharedPtr<View> > mViews;
    //! Frame info for rendering
    FrameInfo mFrame;
};

//! Return Pipeline instance
Pipeline* getPipeline();

#endif // RENDERER_PIPELINE_H
