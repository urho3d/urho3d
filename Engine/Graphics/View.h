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
#include "HashSet.h"
#include "Object.h"
#include "Polyhedron.h"

class Camera;
class DebugRenderer;
class Light;
class Drawable;
class OcclusionBuffer;
class Octree;
class RenderSurface;
class Technique;
class Texture2D;
class Zone;
struct Viewport;

/// %Geometry view space depth minimum and maximum values.
struct GeometryDepthBounds
{
    /// Minimum value.
    float min_;
    /// Maximum value.
    float max_;
};

/// 3D rendering view. Includes the main view(s) and any auxiliary views, but not shadow cameras.
class View : public Object
{
    OBJECT(View);
    
public:
    /// Construct.
    View(Context* context);
    /// Destruct.
    virtual ~View();
    
    /// Define with rendertarget and viewport. Return true if successful.
    bool Define(RenderSurface* renderTarget, const Viewport& viewport);
    /// Update culling and construct rendering batches.
    void Update(const FrameInfo& frame);
    /// Render batches.
    void Render();
    
    /// Return octree.
    Octree* GetOctree() const { return octree_; }
    /// Return camera.
    Camera* GetCamera() const { return camera_; }
    /// Return the render target. 0 if using the backbuffer.
    RenderSurface* GetRenderTarget() const { return renderTarget_; }
    /// Return the depth stencil. 0 if using the backbuffer's depth stencil.
    RenderSurface* GetDepthStencil() const { return depthStencil_; }
    /// Return geometry objects.
    const PODVector<Drawable*>& GetGeometries() const { return geometries_; }
    /// Return occluder objects.
    const PODVector<Drawable*>& GetOccluders() const { return occluders_; }
    /// Return directional light shadow rendering occluders.
    const PODVector<Drawable*>& GetShadowOccluders() const { return shadowOccluders_; }
    /// Return lights.
    const PODVector<Light*>& GetLights() const { return lights_; }
    /// Return light batch queues.
    const Vector<LightBatchQueue>& GetLightQueues() const { return lightQueues_; }
    
private:
    /// Query the octree for drawable objects.
    void GetDrawables();
    /// Construct batches from the drawable objects.
    void GetBatches();
    /// Get lit batches for a certain light and drawable.
    void GetLitBatches(Drawable* drawable, LightBatchQueue& lightQueue);
    /// Render batches.
    void RenderBatches();
    /// Query for occluders as seen from a camera.
    void UpdateOccluders(PODVector<Drawable*>& occluders, Camera* camera);
    /// Draw occluders to occlusion buffer.
    void DrawOccluders(OcclusionBuffer* buffer, const PODVector<Drawable*>& occluders);
    /// Query for lit geometries and shadow casters for a light.
    unsigned ProcessLight(Light* light);
    /// Process shadow casters' visibilities and build their combined view- or projection-space bounding box.
    void ProcessShadowCasters(Light* light, unsigned splitIndex, const PODVector<Drawable*>& drawables, BoundingBox& shadowCasterBox);
    /// %Set up initial shadow camera view(s). Returns the number of splits used.
    unsigned SetupShadowCameras(Light* light);
    /// %Set up a directional light shadow camera
    void SetupDirLightShadowCamera(Camera* shadowCamera, Light* light, float nearSplit, float farSplit, bool shadowOcclusion);
    /// Finalize shadow camera view after shadow casters and the shadow map are known.
    void FinalizeShadowCamera(Camera* shadowCamera, Light* light, const IntRect& shadowViewport, const BoundingBox& shadowCasterBox);
    /// Quantize a directional light shadow camera view to eliminate swimming.
    void QuantizeDirLightShadowCamera(Camera* shadowCamera, Light* light, const IntRect& shadowViewport, const BoundingBox& viewBox);
    /// Check visibility of one shadow caster.
    bool IsShadowCasterVisible(Drawable* drawable, BoundingBox lightViewBox, Camera* shadowCamera, const Matrix3x4& lightView, const Frustum& lightViewFrustum, const BoundingBox& lightViewFrustumBox);
    /// Return the viewport for a shadow map split.
    IntRect GetShadowMapViewport(Light* light, unsigned splitIndex, Texture2D* shadowMap);
    /// Optimize light rendering by setting up a scissor rectangle.
    void OptimizeLightByScissor(Light* light);
    /// Optimize spot or point light rendering by drawing its volume to the stencil buffer.
    void OptimizeLightByStencil(Light* light);
    /// Return scissor rectangle for a light.
    const Rect& GetLightScissor(Light* light);
    /// Split directional or point light for shadow rendering.
    unsigned SplitLight(Light* light);
    /// Find and set a new zone for a drawable when it has moved.
    void FindZone(Drawable* drawable, int highestZonePriority);
    /// Return the drawable's zone, or camera zone if it has override mode enabled.
    Zone* GetZone(Drawable* drawable);
    /// Return the drawable's light mask, considering also its zone.
    unsigned GetLightMask(Drawable* drawable);
    /// Return material technique, considering the drawable's LOD distance.
    Technique* GetTechnique(Drawable* drawable, Material*& material);
    /// Check if material should render an auxiliary view (if it has a camera attached.)
    void CheckMaterialForAuxView(Material* material);
    /// Sort all batches.
    void SortBatches();
    /// Prepare instancing buffer by filling it with all instance transforms.
    void PrepareInstancingBuffer();
    /// Render everything in a batch queue, priority batches first.
    void RenderBatchQueue(const BatchQueue& queue, bool useScissor = false);
    /// Render batches lit by a specific light.
    void RenderLightBatchQueue(const BatchQueue& queue, Light* forwardQueueLight);
    /// Render a shadow map.
    void RenderShadowMap(const LightBatchQueue& queue);
    
    /// Graphics subsystem.
    WeakPtr<Graphics> graphics_;
    /// Renderer subsystem.
    WeakPtr<Renderer> renderer_;
    /// Octree to use.
    Octree* octree_;
    /// Camera to use.
    Camera* camera_;
    /// Zone the camera is inside, or default zone if not assigned.
    Zone* cameraZone_;
    /// Color buffer to use.
    RenderSurface* renderTarget_;
    /// Depth buffer to use.
    RenderSurface* depthStencil_;
    /// Screen rectangle.
    IntRect screenRect_;
    /// Render target width.
    int width_;
    /// Render target height.
    int height_;
    /// Draw shadows flag.
    bool drawShadows_;
    /// Material quality level.
    int materialQuality_;
    /// Maximum number of occluder triangles.
    int maxOccluderTriangles_;
    /// Information of the frame being rendered.
    FrameInfo frame_;
    /// Information of the frame being rendered, with shadow camera.
    FrameInfo shadowFrame_;
    /// Camera frustum.
    Frustum frustum_;
    /// Combined bounding box of visible geometries.
    BoundingBox sceneBox_;
    /// Combined bounding box of visible geometries in view space.
    BoundingBox sceneViewBox_;
    /// Volume for frustum clipping.
    Polyhedron frustumVolume_;
    /// Current shadow cameras being processed.
    Camera* shadowCameras_[MAX_LIGHT_SPLITS];
    /// Current shadow casters being processed.
    PODVector<Drawable*> shadowCasters_[MAX_LIGHT_SPLITS];
    /// Combined bounding box of shadow casters in light view or projection space.
    BoundingBox shadowCasterBox_[MAX_LIGHT_SPLITS];
    /// Shadow camera near splits (directional lights only.)
    float shadowNearSplits_[MAX_LIGHT_SPLITS];
    /// Shadow camera far splits (directional lights only.)
    float shadowFarSplits_[MAX_LIGHT_SPLITS];
    /// Current lit geometries being processed.
    PODVector<Drawable*> litGeometries_;
    /// Temporary drawable query result.
    PODVector<Drawable*> tempDrawables_;
    /// Temporary zone query result.
    PODVector<Zone*> tempZones_;
    /// Visible zones query result.
    PODVector<Zone*> zones_;
    /// Geometry objects.
    PODVector<Drawable*> geometries_;
    /// Occluder objects.
    PODVector<Drawable*> occluders_;
    /// Directional light shadow rendering occluders.
    PODVector<Drawable*> shadowOccluders_;
    /// Depth minimum and maximum values for visible geometries.
    PODVector<GeometryDepthBounds> geometryDepthBounds_;
    /// Lights.
    PODVector<Light*> lights_;
    /// Drawables that limit their maximum light count.
    HashSet<Drawable*> maxLightsDrawables_;
    /// Light queue indices of processed lights.
    Map<Light*, unsigned> lightQueueIndex_;
    /// Cache for light scissor queries.
    HashMap<Light*, Rect> lightScissorCache_;
    /// Base pass batches.
    BatchQueue baseQueue_;
    /// Pre-transparent pass batches.
    BatchQueue preAlphaQueue_;
    /// Transparent geometry batches.
    BatchQueue alphaQueue_;
    /// Post-transparent pass batches.
    BatchQueue postAlphaQueue_;
    /// Light queues.
    Vector<LightBatchQueue> lightQueues_;
    /// Current stencil value for light optimization.
    unsigned char lightStencilValue_;
    /// Camera zone's override flag.
    bool cameraZoneOverride_;
};
