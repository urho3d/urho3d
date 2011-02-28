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

#ifndef RENDERER_VIEW_H
#define RENDERER_VIEW_H

#include "Batch.h"
#include "RefCount.h"

class Camera;
class DebugRenderer;
class Light;
class GeometryNode;
class OcclusionBuffer;
class RenderSurface;
class Zone;

static const int MAX_LIGHT_SPLITS = 6;

//! Geometry view space depth minimum and maximum values
struct GeometryDepthBounds
{
    float mMin;
    float mMax;
};

//! Shadowed light batch queue
struct LightBatchQueue
{
    //! Light scene node
    Light* mLight;
    //! Shadow rendering batches
    std::vector<Batch> mShadowBatches;
    //! Light volume or opaque rendering batches
    std::vector<Batch> mBatches;
    //! Sorted shadow batch pointers
    std::vector<Batch*> mSortedShadowBatches;
    //! Sorted batch pointers
    std::vector<Batch*> mSortedBatches;
    //! Last split flag (for clearing the stencil buffer)
    bool mLastSplit;
};

//! A rendering view. Includes the main view(s) and any auxiliary views, but not shadow cameras
class View : public RefCounted
{
public:
    //! Construct with pipeline pointer
    View(Pipeline* pipeline);
    //! Destruct
    virtual ~View();
    
    //! Define with octree, camera and render target pointers and a viewport rectangle
    void define(Octree* octree, Camera* camera, RenderSurface* renderTarget, IntRect screenRect);
    //! Update culling and construct rendering batches
    void update(const FrameInfo& frame);
    //! Render batches
    void render();
    
    //! Return octree
    Octree* getOctree() const { return mOctree; }
    //! Return camera
    Camera* getCamera() const { return mCamera; }
    //! Return zone
    Zone* getZone() const { return mZone; }
    //! Return the render target. 0 if using the backbuffer
    RenderSurface* getRenderTarget() const { return mRenderTarget; }
    //! Return the depth stencil. 0 if using the backbuffer's depth stencil
    RenderSurface* getDepthStencil() const { return mDepthStencil; }
    //! Return geometry scene nodes
    const std::vector<GeometryNode*>& getGeometries() const { return mGeometries; }
    //! Return occluder scene nodes
    const std::vector<GeometryNode*>& getOccluders() const { return mOccluders; }
    //! Return directional light shadow rendering occluders
    const std::vector<GeometryNode*>& getShadowOccluders() const { return mShadowOccluders; }
    //! Return light scene nodes
    const std::vector<Light*>& getLights() const { return mLights; }
    //! Return light batch queues
    const std::vector<LightBatchQueue>& getLightQueues() const { return mLightQueues; }
    
private:
    //! Query the octree for scene nodes
    void getNodes();
    //! Construct batches from the scene nodes
    void getBatches();
    //! Construct batches for deferred or light prepass rendering
    void getBatchesDeferred();
    //! Construct batches for forward rendering
    void getBatchesForward();
    //! Render in deferred or light prepass mode
    void renderBatchesDeferred();
    //! Render in forward mode
    void renderBatchesForward();
    //! Clear shader parameter sources
    void clearLastParameterSources();
    //! Query for occluders as seen from a camera
    void updateOccluders(std::vector<GeometryNode*>& occluders, Camera& camera);
    //! Draw occluders to occlusion buffer
    void drawOccluders(OcclusionBuffer* buffer, const std::vector<GeometryNode*>& occluders);
    //! Query for lit geometries and shadow casters for a light
    unsigned processLight(Light* light);
    //! Generate combined bounding boxes for lit geometries and shadow casters and check shadow caster visibility
    void processLightQuery(unsigned splitIndex, const std::vector<VolumeNode*>& result, BoundingBox& geometryBox, BoundingBox& shadowSpaceBox, bool getLitGeometries, bool getShadowCasters);
    //! Check visibility of one shadow caster
    bool isShadowCasterVisible(GeometryNode* geom, BoundingBox lightViewBox, const Camera& shadowCamera, const Matrix4x3& lightView, const Frustum& lightViewFrustum, const BoundingBox& lightViewFrustumBox);
    //! Set up initial shadow camera view
    void setupShadowCamera(Light* light, bool shadowOcclusion = false);
    //! Focus shadow camera to use shadow map texture space more optimally
    void focusShadowCamera(Light* light, const BoundingBox& geometryBox, const BoundingBox& shadowCasterBox);
    //! Quantize the directional light shadow camera view to eliminate artefacts
    void quantizeDirShadowCamera(Light* light, const BoundingBox& viewBox);
    //! Optimize light rendering by setting up a scissor rectangle
    void optimizeLightByScissor(Light* light);
    //! Return scissor rectangle for a light
    const Rect& getLightScissor(Light* light);
    //! Split directional or point light for shadow rendering
    unsigned splitLight(Light* light);
    //! Return material technique for a scene node's geometry
    MaterialTechnique* getMaterialTechnique(GeometryNode* node, unsigned index);
    //! Check if material technique should render an auxiliary view (if it has a camera attached)
    void checkTechniqueForAuxView(MaterialTechnique* technique);
    
    //! Sort a batch list
    static void sortBatches(std::vector<Batch>& originalBatches, std::vector<Batch*>& sortedBatches);
    
    //! Pipeline
    Pipeline* mPipeline;
    //! Octree to use
    Octree* mOctree;
    //! Camera to use
    Camera* mCamera;
    //! Zone to get global rendering settings from
    Zone* mZone;
    //! Color buffer to use
    RenderSurface* mRenderTarget;
    //! Depth buffer to use
    RenderSurface* mDepthStencil;
    //! Screen rectangle. For texture render targets it is the full texture size
    IntRect mScreenRect;
    //! Render target width
    int mWidth;
    //! Render target height
    int mHeight;
    //! Draw shadows flag
    bool mDrawShadows;
    //! Shader Model 3 support flag
    bool mSM3Support;
    //! Light detail level
    int mLightDetailLevel;
    //! Material quality level
    int mMaterialQuality;
    //! Maximum number of occluder triangles
    int mMaxOccluderTriangles;
    //! Information of the frame being rendered
    FrameInfo mFrame;
    //! Combined bounding box of visible geometries
    BoundingBox mSceneBox;
    //! Combined bounding box of visible geometries in view space
    BoundingBox mSceneViewBox;
    //! Cache for light scissor queries
    std::map<Light*, Rect> mLightScissorCache;
    
    //! Geometry scene nodes
    std::vector<GeometryNode*> mGeometries;
    //! Occluder scene nodes
    std::vector<GeometryNode*> mOccluders;
    //! Directional light shadow rendering occluder scene nodes
    std::vector<GeometryNode*> mShadowOccluders;
    //! Depth minimum and maximum values for visible geometries
    std::vector<GeometryDepthBounds> mGeometryDepthBounds;
    //! Light scene nodes
    std::vector<Light*> mLights;
    
    //! G-buffer batch queue
    std::vector<Batch> mGBufferQueue;
    //! Negative light volumes batch queue
    std::vector<Batch> mNegativeLightQueue;
    //! Non-shadowcasting light volumes batch queue
    std::vector<Batch> mNoShadowLightQueue;
    //! Ambient pass batch queue
    std::vector<Batch> mAmbientQueue;
    //! Negative ambient pass batch queue
    std::vector<Batch> mNegativeQueue;
    //! Forward pass batch queue
    std::vector<Batch> mForwardQueue;
    //! Post-opaque pass batch queue
    std::vector<Batch> mPostOpaqueQueue;
    //! Transparent geometries batch queue
    std::vector<Batch> mTransparentQueue;
    //! Shadowed light batch queues
    std::vector<LightBatchQueue> mLightQueues;
    
    //! Sorted G-buffer batch queue
    std::vector<Batch*> mGBufferQueueSorted;
    //! Sorted negative light volumes batch queue
    std::vector<Batch*> mNegativeLightQueueSorted;
    //! Sorted non-shadowcasting light volumes batch queue
    std::vector<Batch*> mNoShadowLightQueueSorted;
    //! Sorted ambient pass batch queue
    std::vector<Batch*> mAmbientQueueSorted;
    //! Sorted negative ambient pass batch queue
    std::vector<Batch*> mNegativeQueueSorted;
    //! Sorted forward pass batch queue
    std::vector<Batch*> mForwardQueueSorted;
    //! Sorted post-opaque pass batch queue
    std::vector<Batch*> mPostOpaqueQueueSorted;
    //! Sorted transparent geometries batch queue
    std::vector<Batch*> mTransparentQueueSorted;
    
    //! Default zone if no other zone found
    static Zone sDefaultZone;
    //! Current split lights
    static Light* sSplitLights[MAX_LIGHT_SPLITS];
    //! Current light's lit geometries
    static std::vector<GeometryNode*> sLitGeometries[MAX_LIGHT_SPLITS];
    //! Current light's shadow casters
    static std::vector<GeometryNode*> sShadowCasters[MAX_LIGHT_SPLITS];
};

#endif // RENDERER_VIEW_H
