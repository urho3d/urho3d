//
// Copyright (c) 2008-2014 the Urho3D project.
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
#include "../Container/HashSet.h"
#include "../Graphics/Light.h"
#include "../Container/List.h"
#include "../Core/Object.h"
#include "../Math/Polyhedron.h"
#include "../Graphics/Zone.h"

namespace Urho3D
{

class Camera;
class DebugRenderer;
class Light;
class Drawable;
class Graphics;
class OcclusionBuffer;
class Octree;
class Renderer;
class RenderPath;
class RenderSurface;
class Technique;
class Texture2D;
class Viewport;
class Zone;
struct RenderPathCommand;
struct WorkItem;

/// Intermediate light processing result.
struct LightQueryResult
{
    /// Light.
    Light* light_;
    /// Lit geometries.
    PODVector<Drawable*> litGeometries_;
    /// Shadow casters.
    PODVector<Drawable*> shadowCasters_;
    /// Shadow cameras.
    Camera* shadowCameras_[MAX_LIGHT_SPLITS];
    /// Shadow caster start indices.
    unsigned shadowCasterBegin_[MAX_LIGHT_SPLITS];
    /// Shadow caster end indices.
    unsigned shadowCasterEnd_[MAX_LIGHT_SPLITS];
    /// Combined bounding box of shadow casters in light view or projection space.
    BoundingBox shadowCasterBox_[MAX_LIGHT_SPLITS];
    /// Shadow camera near splits (directional lights only.)
    float shadowNearSplits_[MAX_LIGHT_SPLITS];
    /// Shadow camera far splits (directional lights only.)
    float shadowFarSplits_[MAX_LIGHT_SPLITS];
    /// Shadow map split count.
    unsigned numSplits_;
};

/// Scene render pass info.
struct ScenePassInfo
{
    /// Pass name hash.
    StringHash pass_;
    /// Allow instancing flag.
    bool allowInstancing_;
    /// Mark to stencil flag.
    bool markToStencil_;
    /// Light scissor optimization flag.
    bool useScissor_;
    /// Vertex light flag.
    bool vertexLights_;
    /// Batch queue.
    BatchQueue* batchQueue_;
};

/// Per-thread geometry, light and scene range collection structure.
struct PerThreadSceneResult
{
    /// Geometry objects.
    PODVector<Drawable*> geometries_;
    /// Lights.
    PODVector<Light*> lights_;
    /// Scene minimum Z value.
    float minZ_;
    /// Scene maximum Z value.
    float maxZ_;
};

static const unsigned MAX_VIEWPORT_TEXTURES = 2;

/// Internal structure for 3D rendering work. Created for each backbuffer and texture viewport, but not for shadow cameras.
class URHO3D_API View : public Object
{
    friend void CheckVisibilityWork(const WorkItem* item, unsigned threadIndex);
    friend void ProcessLightWork(const WorkItem* item, unsigned threadIndex);
    
    OBJECT(View);
    
public:
    /// Construct.
    View(Context* context);
    /// Destruct.
    virtual ~View();
    
    /// Define with rendertarget and viewport. Return true if successful.
    bool Define(RenderSurface* renderTarget, Viewport* viewport);
    /// Update and cull objects and construct rendering batches.
    void Update(const FrameInfo& frame);
    /// Render batches.
    void Render();
    
    /// Return graphics subsystem.
    Graphics* GetGraphics() const;
    /// Return renderer subsystem.
    Renderer* GetRenderer() const;
    /// Return scene.
    Scene* GetScene() const { return scene_; }
    /// Return octree.
    Octree* GetOctree() const { return octree_; }
    /// Return camera.
    Camera* GetCamera() const { return camera_; }
    /// Return information of the frame being rendered.
    const FrameInfo& GetFrameInfo() const { return frame_; }
    /// Return the rendertarget. 0 if using the backbuffer.
    RenderSurface* GetRenderTarget() const { return renderTarget_; }
    /// Return whether should draw debug geometry.
    bool GetDrawDebug() const { return drawDebug_; }
    /// Return geometry objects.
    const PODVector<Drawable*>& GetGeometries() const { return geometries_; }
    /// Return occluder objects.
    const PODVector<Drawable*>& GetOccluders() const { return occluders_; }
    /// Return lights.
    const PODVector<Light*>& GetLights() const { return lights_; }
    /// Return light batch queues.
    const Vector<LightBatchQueue>& GetLightQueues() const { return lightQueues_; }
    /// Set global (per-frame) shader parameters. Called by Batch and internally by View.
    void SetGlobalShaderParameters();
    /// Set camera-specific shader parameters. Called by Batch and internally by View.
    void SetCameraShaderParameters(Camera* camera, bool setProjectionMatrix);
    /// Set G-buffer offset and inverse size shader parameters. Called by Batch and internally by View.
    void SetGBufferShaderParameters(const IntVector2& texSize, const IntRect& viewRect);
    
private:
    /// Query the octree for drawable objects.
    void GetDrawables();
    /// Construct batches from the drawable objects.
    void GetBatches();
    /// Update geometries and sort batches.
    void UpdateGeometries();
    /// Get pixel lit batches for a certain light and drawable.
    void GetLitBatches(Drawable* drawable, LightBatchQueue& lightQueue, BatchQueue* alphaQueue);
    /// Execute render commands.
    void ExecuteRenderPathCommands();
    /// Set rendertargets for current render command.
    void SetRenderTargets(RenderPathCommand& command);
    /// Set textures for current render command. Return whether depth write is allowed (depth-stencil not bound as a texture.)
    bool SetTextures(RenderPathCommand& command);
    /// Perform a quad rendering command.
    void RenderQuad(RenderPathCommand& command);
    /// Check if a command is enabled and has content to render. To be called only after render update has completed for the frame.
    bool IsNecessary(const RenderPathCommand& command);
    /// Check if a command reads the destination render target.
    bool CheckViewportRead(const RenderPathCommand& command);
    /// Check if a command writes into the destination render target.
    bool CheckViewportWrite(const RenderPathCommand& command);
    /// Check whether a command should use pingponging instead of resolve from destination render target to viewport texture.
    bool CheckPingpong(unsigned index);
    /// Allocate needed screen buffers.
    void AllocateScreenBuffers();
    /// Blit the viewport from one surface to another.
    void BlitFramebuffer(Texture2D* source, RenderSurface* destination, bool depthWrite);
    /// Draw a fullscreen quad. Shaders and renderstates must have been set beforehand.
    void DrawFullscreenQuad(bool nearQuad);
    /// Query for occluders as seen from a camera.
    void UpdateOccluders(PODVector<Drawable*>& occluders, Camera* camera);
    /// Draw occluders to occlusion buffer.
    void DrawOccluders(OcclusionBuffer* buffer, const PODVector<Drawable*>& occluders);
    /// Query for lit geometries and shadow casters for a light.
    void ProcessLight(LightQueryResult& query, unsigned threadIndex);
    /// Process shadow casters' visibilities and build their combined view- or projection-space bounding box.
    void ProcessShadowCasters(LightQueryResult& query, const PODVector<Drawable*>& drawables, unsigned splitIndex);
    /// Set up initial shadow camera view(s).
    void SetupShadowCameras(LightQueryResult& query);
    /// Set up a directional light shadow camera
    void SetupDirLightShadowCamera(Camera* shadowCamera, Light* light, float nearSplit, float farSplit);
    /// Finalize shadow camera view after shadow casters and the shadow map are known.
    void FinalizeShadowCamera(Camera* shadowCamera, Light* light, const IntRect& shadowViewport, const BoundingBox& shadowCasterBox);
    /// Quantize a directional light shadow camera view to eliminate swimming.
    void QuantizeDirLightShadowCamera(Camera* shadowCamera, Light* light, const IntRect& shadowViewport, const BoundingBox& viewBox);
    /// Check visibility of one shadow caster.
    bool IsShadowCasterVisible(Drawable* drawable, BoundingBox lightViewBox, Camera* shadowCamera, const Matrix3x4& lightView, const Frustum& lightViewFrustum, const BoundingBox& lightViewFrustumBox);
    /// Return the viewport for a shadow map split.
    IntRect GetShadowMapViewport(Light* light, unsigned splitIndex, Texture2D* shadowMap);
    /// Find and set a new zone for a drawable when it has moved.
    void FindZone(Drawable* drawable);
    /// Return material technique, considering the drawable's LOD distance.
    Technique* GetTechnique(Drawable* drawable, Material* material);
    /// Check if material should render an auxiliary view (if it has a camera attached.)
    void CheckMaterialForAuxView(Material* material);
    /// Choose shaders for a batch and add it to queue.
    void AddBatchToQueue(BatchQueue& queue, Batch& batch, Technique* tech, bool allowInstancing = true, bool allowShadows = true);
    /// Prepare instancing buffer by filling it with all instance transforms.
    void PrepareInstancingBuffer();
    /// Set up a light volume rendering batch.
    void SetupLightVolumeBatch(Batch& batch);
    /// Render a shadow map.
    void RenderShadowMap(const LightBatchQueue& queue);
    /// Return the proper depth-stencil surface to use for a rendertarget.
    RenderSurface* GetDepthStencil(RenderSurface* renderTarget);
    
    /// Return the drawable's zone, or camera zone if it has override mode enabled.
    Zone* GetZone(Drawable* drawable)
    {
        if (cameraZoneOverride_)
            return cameraZone_;
        Zone* drawableZone = drawable->GetZone();
        return drawableZone ? drawableZone : cameraZone_;
    }

    /// Return the drawable's light mask, considering also its zone.
    unsigned GetLightMask(Drawable* drawable)
    {
        return drawable->GetLightMask() & GetZone(drawable)->GetLightMask();
    }

    /// Return the drawable's shadow mask, considering also its zone.
    unsigned GetShadowMask(Drawable* drawable)
    {
        return drawable->GetShadowMask() & GetZone(drawable)->GetShadowMask();
    }

    /// Return hash code for a vertex light queue.
    unsigned long long GetVertexLightQueueHash(const PODVector<Light*>& vertexLights)
    {
        unsigned long long hash = 0;
        for (PODVector<Light*>::ConstIterator i = vertexLights.Begin(); i != vertexLights.End(); ++i)
            hash += (unsigned long long)(*i);
        return hash;
    }

    /// Graphics subsystem.
    WeakPtr<Graphics> graphics_;
    /// Renderer subsystem.
    WeakPtr<Renderer> renderer_;
    /// Scene to use.
    Scene* scene_;
    /// Octree to use.
    Octree* octree_;
    /// Camera to use.
    Camera* camera_;
    /// Camera's scene node.
    Node* cameraNode_;
    /// Zone the camera is inside, or default zone if not assigned.
    Zone* cameraZone_;
    /// Zone at far clip plane.
    Zone* farClipZone_;
    /// Occlusion buffer for the main camera.
    OcclusionBuffer* occlusionBuffer_;
    /// Destination color rendertarget.
    RenderSurface* renderTarget_;
    /// Substitute rendertarget for deferred rendering. Allocated if necessary.
    RenderSurface* substituteRenderTarget_;
    /// Texture(s) for sampling the viewport contents. Allocated if necessary.
    Texture2D* viewportTextures_[MAX_VIEWPORT_TEXTURES];
    /// Color rendertarget active for the current renderpath command.
    RenderSurface* currentRenderTarget_;
    /// Texture containing the latest viewport texture.
    Texture2D* currentViewportTexture_;
    /// Dummy texture for D3D9 depth only rendering.
    Texture2D* depthOnlyDummyTexture_;
    /// Viewport rectangle.
    IntRect viewRect_;
    /// Viewport size.
    IntVector2 viewSize_;
    /// Destination rendertarget size.
    IntVector2 rtSize_;
    /// Information of the frame being rendered.
    FrameInfo frame_;
    /// Minimum Z value of the visible scene.
    float minZ_;
    /// Maximum Z value of the visible scene.
    float maxZ_;
    /// Material quality level.
    int materialQuality_;
    /// Maximum number of occluder triangles.
    int maxOccluderTriangles_;
    /// Minimum number of instances required in a batch group to render as instanced.
    int minInstances_;
    /// Highest zone priority currently visible.
    int highestZonePriority_;
    /// Camera zone's override flag.
    bool cameraZoneOverride_;
    /// Draw shadows flag.
    bool drawShadows_;
    /// Deferred flag. Inferred from the existence of a light volume command in the renderpath.
    bool deferred_;
    /// Deferred ambient pass flag. This means that the destination rendertarget is being written to at the same time as albedo/normal/depth buffers, and needs to be RGBA on OpenGL.
    bool deferredAmbient_;
    /// Forward light base pass optimization flag. If in use, combine the base pass and first light for all opaque objects.
    bool useLitBase_;
    /// Has scene passes flag. If no scene passes, view can be defined without a valid scene or camera to only perform quad rendering.
    bool hasScenePasses_;
    /// Whether is using a custom readable depth texture without a stencil channel.
    bool noStencil_;
    /// Draw debug geometry flag. Copied from the viewport.
    bool drawDebug_;
    /// Renderpath.
    RenderPath* renderPath_;
    /// Per-thread octree query results.
    Vector<PODVector<Drawable*> > tempDrawables_;
    /// Per-thread geometries, lights and Z range collection results.
    Vector<PerThreadSceneResult> sceneResults_;
    /// Visible zones.
    PODVector<Zone*> zones_;
    /// Visible geometry objects.
    PODVector<Drawable*> geometries_;
    /// Geometry objects that will be updated in the main thread.
    PODVector<Drawable*> nonThreadedGeometries_;
    /// Geometry objects that will be updated in worker threads.
    PODVector<Drawable*> threadedGeometries_;
    /// Occluder objects.
    PODVector<Drawable*> occluders_;
    /// Lights.
    PODVector<Light*> lights_;
    /// Drawables that limit their maximum light count.
    HashSet<Drawable*> maxLightsDrawables_;
    /// Rendertargets defined by the renderpath.
    HashMap<StringHash, Texture2D*> renderTargets_;
    /// Intermediate light processing results.
    Vector<LightQueryResult> lightQueryResults_;
    /// Info for scene render passes defined by the renderpath.
    Vector<ScenePassInfo> scenePasses_;
    /// Per-pixel light queues.
    Vector<LightBatchQueue> lightQueues_;
    /// Per-vertex light queues.
    HashMap<unsigned long long, LightBatchQueue> vertexLightQueues_;
    /// Batch queues.
    HashMap<StringHash, BatchQueue> batchQueues_;
    /// Hash of the GBuffer pass, or null if none.
    StringHash gBufferPassName_;
    /// Hash of the opaque forward base pass.
    StringHash basePassName_;
    /// Hash of the alpha pass.
    StringHash alphaPassName_;
    /// Hash of the forward light pass.
    StringHash lightPassName_;
    /// Hash of the litbase pass.
    StringHash litBasePassName_;
    /// Hash of the litalpha pass.
    StringHash litAlphaPassName_;
    /// Pointer to the light volume command if any.
    const RenderPathCommand* lightVolumeCommand_;
};

}
