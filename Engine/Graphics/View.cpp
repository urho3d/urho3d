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

#include "Precompiled.h"
#include "Camera.h"
#include "DebugRenderer.h"
#include "Geometry.h"
#include "Graphics.h"
#include "Light.h"
#include "Log.h"
#include "Material.h"
#include "OcclusionBuffer.h"
#include "Octree.h"
#include "OctreeQuery.h"
#include "Renderer.h"
#include "PixelShader.h"
#include "Profiler.h"
#include "Scene.h"
#include "Technique.h"
#include "Texture2D.h"
#include "TextureCube.h"
#include "Time.h"
#include "VertexBuffer.h"
#include "VertexShader.h"
#include "View.h"
#include "Zone.h"

#include <algorithm>

#include "DebugNew.h"

#include "StringUtils.h"

static const std::string aaVariation[] = {
    "",
    "Ortho"
};

static const Vector3 directions[] =
{
    Vector3::RIGHT,
    Vector3::LEFT,
    Vector3::UP,
    Vector3::DOWN,
    Vector3::FORWARD,
    Vector3::BACK,
};

OBJECTTYPESTATIC(View);

View::View(Context* context) :
    Object(context),
    graphics_(GetSubsystem<Graphics>()),
    renderer_(GetSubsystem<Renderer>()),
    octree_(0),
    camera_(0),
    zone_(0),
    renderTarget_(0),
    depthStencil_(0),
    jitterCounter_(0),
    hasSM3_(graphics_->GetSM3Support())
{
    frame_.camera_ = 0;
}

View::~View()
{
}

bool View::Define(RenderSurface* renderTarget, const Viewport& viewport)
{
    if ((!viewport.scene_) || (!viewport.camera_))
        return false;
    
    // If scene is loading asynchronously, it is incomplete and should not be rendered
    //if (viewport.scene_->isAsyncLoading())
    //    return false;
    
    Octree* octree = viewport.scene_->GetComponent<Octree>();
    if (!octree)
        return false;
    
    mode_ = graphics_->GetRenderMode();
    
    // In deferred mode, check for the render texture being too large
    if ((mode_ != RENDER_FORWARD) && (renderTarget))
    {
        if ((renderTarget->GetWidth() > graphics_->GetWidth()) || (renderTarget->GetHeight() > graphics_->GetHeight()))
        {
            // Display message only once per rendertarget, do not spam each frame
            if (gBufferErrorDisplayed_.find(renderTarget) == gBufferErrorDisplayed_.end())
            {
                gBufferErrorDisplayed_.insert(renderTarget);
                LOGERROR("Render texture is larger than the G-buffer, can not render");
            }
            return false;
        }
    }
    
    octree_ = octree;
    camera_ = viewport.camera_;
    renderTarget_ = renderTarget;
    
    // If not rendering to the back buffer, get the depth buffer linked to the color render target
    if (renderTarget)
        depthStencil_ = renderTarget->GetLinkedDepthBuffer();
    else
        depthStencil_ = 0;
    
    zone_ = renderer_->GetDefaultZone();
    
    // Validate the rect and Calculate size. If zero rect, use whole render target size
    int rtWidth = renderTarget ? renderTarget->GetWidth() : graphics_->GetWidth();
    int rtHeight = renderTarget ? renderTarget->GetHeight() : graphics_->GetHeight();
    if (viewport.rect_ != IntRect::ZERO)
    {
        screenRect_.left_ = Clamp(viewport.rect_.left_, 0, rtWidth - 1);
        screenRect_.top_ = Clamp(viewport.rect_.top_, 0, rtHeight - 1);
        screenRect_.right_ = Clamp(viewport.rect_.right_, screenRect_.left_ + 1, rtWidth);
        screenRect_.bottom_ = Clamp(viewport.rect_.bottom_, screenRect_.top_ + 1, rtHeight);
    }
    else
        screenRect_ = IntRect(0, 0, rtWidth, rtHeight);
    width_ = screenRect_.right_ - screenRect_.left_;
    height_ = screenRect_.bottom_ - screenRect_.top_;
    
    // Set possible quality overrides from the camera
    drawShadows_ = renderer_->GetDrawShadows();
    materialQuality_ = renderer_->GetMaterialQuality();
    maxOccluderTriangles_ = renderer_->GetMaxOccluderTriangles();
    
    unsigned viewOverrideFlags = camera_->GetViewOverrideFlags();
    if (viewOverrideFlags & VOF_LOW_MATERIAL_QUALITY)
        materialQuality_ = QUALITY_LOW;
    if (viewOverrideFlags & VOF_DISABLE_SHADOWS)
        drawShadows_ = false;
    if (viewOverrideFlags & VOF_DISABLE_OCCLUSION)
        maxOccluderTriangles_ = 0;
    
    return true;
}

void View::Update(const FrameUpdate& frame)
{
    if ((!camera_) || (!octree_))
        return;
    
    frame_.camera_ = camera_;
    frame_.timeStep_ = frame.timeStep_;
    frame_.frameNumber_ = frame.frameNumber_;
    frame_.viewSize_ = IntVector2(width_, height_);
    
    // Clear old light scissor cache, geometry, light, occluder & batch lists
    lightScissorCache_.clear();
    geometries_.clear();
    geometryDepthBounds_.clear();
    lights_.clear();
    occluders_.clear();
    shadowOccluders_.clear();
    gBufferQueue_.Clear();
    baseQueue_.Clear();
    extraQueue_.Clear();
    transparentQueue_.Clear();
    noShadowLightQueue_.Clear();
    lightQueues_.clear();
    
    // Set automatic aspect ratio if required
    if (camera_->GetAutoAspectRatio())
        camera_->SetAspectRatio((float)frame_.viewSize_.x_ / (float)frame_.viewSize_.y_);
    
    // Reset projection jitter if was used last frame
    camera_->SetProjectionOffset(Vector2::ZERO);
    
    // Reset shadow map use count; they can be reused between views as each is rendered completely at a time
    renderer_->ResetShadowMapUseCount();
    
    GetDrawables();
    GetBatches();
}

void View::Render()
{
    if ((!octree_) || (!camera_))
        return;
    
    // If stream offset is supported, pre-set all instance transforms to a single large buffer
    // Else we must lock the instance buffer for each batch group
    if ((renderer_->GetDynamicInstancing()) && (graphics_->GetStreamOffsetSupport()))
        PrepareInstancingBuffer();
    
    // It is possible, though not recommended, that the same camera is used for multiple main views. Set automatic aspect ratio
    // again to ensure correct projection will be used
    if (camera_->GetAutoAspectRatio())
        camera_->SetAspectRatio((float)(screenRect_.right_ - screenRect_.left_) / (float)(screenRect_.bottom_ - screenRect_.top_));
    
    // Set the "view texture" to ensure the rendertarget will not be bound as a texture during rendering
    if (renderTarget_)
        graphics_->SetViewTexture(renderTarget_->GetParentTexture());
    else
        graphics_->SetViewTexture(0);
    
    graphics_->SetFillMode(FILL_SOLID);
    
    // Set per-view shader parameters
    SetShaderParameters();
    
    // If not reusing shadowmaps, render all of them first
    if (!renderer_->reuseShadowMaps_)
    {
        for (unsigned i = 0; i < lightQueues_.size(); ++i)
        {
            LightBatchQueue& queue = lightQueues_[i];
            if (queue.light_->GetShadowMap())
                RenderShadowMap(queue);
        }
    }
    
    if (mode_ == RENDER_FORWARD)
        RenderBatcheforward();
    else
        RenderBatchesDeferred();
    
    graphics_->SetViewTexture(0);
    
    // If this is a main view, draw the associated debug geometry now
    if (!renderTarget_)
    {
        Scene* scene = static_cast<Scene*>(octree_->GetNode());
        if (scene)
        {
            DebugRenderer* debug = scene->GetComponent<DebugRenderer>();
            if (debug)
            {
                debug->SetView(camera_);
                debug->Render();
            }
        }
    }
    
    // "Forget" the camera, octree and zone after rendering
    camera_ = 0;
    octree_ = 0;
    zone_ = 0;
    frame_.camera_ = 0;
}

void View::GetDrawables()
{
    PROFILE(GetDrawables);
    
    Vector3 cameraPos = camera_->GetWorldPosition();
    
    // Get zones & find the zone camera is in
    std::vector<Zone*> zones;
    PointOctreeQuery query(reinterpret_cast<std::vector<Drawable*>& >(zones), cameraPos, DRAWABLE_ZONE);
    octree_->GetDrawables(query);
    
    int highestZonePriority = M_MIN_INT;
    for (unsigned i = 0; i < zones.size(); ++i)
    {
        Zone* zone = zones[i];
        if ((zone->IsInside(cameraPos)) && (zone->GetPriority() > highestZonePriority))
        {
            zone_ = zone;
            highestZonePriority = zone->GetPriority();
        }
    }
    
    // If occlusion in use, get & render the occluders, then build the depth buffer hierarchy
    bool useOcclusion = false;
    OcclusionBuffer* buffer = 0;
    
    if (maxOccluderTriangles_ > 0)
    {
        FrustumOctreeQuery query(reinterpret_cast<std::vector<Drawable*>& >(occluders_), camera_->GetFrustum(),
            DRAWABLE_GEOMETRY, true, false);
        
        octree_->GetDrawables(query);
        UpdateOccluders(occluders_, camera_);
        
        if (occluders_.size())
        {
            buffer = renderer_->GetOrCreateOcclusionBuffer(camera_, maxOccluderTriangles_);
            
            DrawOccluders(buffer, occluders_);
            buffer->BuildDepthHierarchy();
            useOcclusion = true;
        }
    }
    
    if (!useOcclusion)
    {
        // Get geometries & lights without occlusion
        FrustumOctreeQuery query(tempDrawables_, camera_->GetFrustum(), DRAWABLE_GEOMETRY | DRAWABLE_LIGHT);
        octree_->GetDrawables(query);
    }
    else
    {
        // Get geometries & lights using occlusion
        OccludedFrustumOctreeQuery query(tempDrawables_, camera_->GetFrustum(), buffer, DRAWABLE_GEOMETRY | DRAWABLE_LIGHT);
        octree_->GetDrawables(query);
    }
    
    // Sort into geometries & lights, and build visible scene bounding boxes in world and view space
    sceneBox_.min_ = sceneBox_.max_ = Vector3::ZERO;
    sceneBox_.defined_ = false;
    sceneViewBox_.min_ = sceneViewBox_.max_ = Vector3::ZERO;
    sceneViewBox_.defined_ = false;
    Matrix4x3 view(camera_->GetInverseWorldTransform());
    unsigned cameraViewMask = camera_->GetViewMask();
    
    for (unsigned i = 0; i < tempDrawables_.size(); ++i)
    {
        Drawable* drawable = tempDrawables_[i];
        
        // Check view mask
        if (!(cameraViewMask & drawable->GetViewMask()))
            continue;
        
        drawable->UpdateDistance(frame_);
        
        // If draw distance non-zero, check it
        float maxDistance = drawable->GetDrawDistance();
        if ((maxDistance > 0.0f) && (drawable->GetDistance() > maxDistance))
            continue;
        
        unsigned flags = drawable->GetDrawableFlags();
        if (flags & DRAWABLE_GEOMETRY)
        {
            drawable->ClearBasePass();
            drawable->MarkInView(frame_);
            drawable->UpdateGeometry(frame_);
            
            // Expand the scene bounding boxes
            const BoundingBox& geomBox = drawable->GetWorldBoundingBox();
            BoundingBox geoview_Box = geomBox.GetTransformed(view);
            sceneBox_.Merge(geomBox);
            sceneViewBox_.Merge(geoview_Box);
            
            // Store depth info to speed up split directional light queries
            GeometryDepthBounds bounds;
            bounds.min_ = geoview_Box.min_.z_;
            bounds.max_ = geoview_Box.max_.z_;
            
            geometryDepthBounds_.push_back(bounds);
            geometries_.push_back(drawable);
        }
        else if (flags & DRAWABLE_LIGHT)
        {
            Light* light = static_cast<Light*>(drawable);
            
            // Skip if light is culled by the zone
            if (!(light->GetViewMask() & zone_->GetViewMask()))
                continue;
            
            light->MarkInView(frame_);
            lights_.push_back(light);
        }
    }
    
    // Sort the lights to brightest/closest first
    for (unsigned i = 0; i < lights_.size(); ++i)
        lights_[i]->SetIntensitySortValue(cameraPos);
    
    std::sort(lights_.begin(), lights_.end(), CompareDrawables);
}


void View::GetBatches()
{
    std::set<LitTransparencyCheck> litTransparencies;
    std::set<Drawable*> maxLightsDrawables;
    std::map<Light*, unsigned> lightQueueIndex;
    
    PassType gBufferPass = PASS_DEFERRED;
    PassType additionalPass = PASS_EXTRA;
    if (mode_ == RENDER_PREPASS)
    {
        gBufferPass = PASS_PREPASS;
        additionalPass = PASS_MATERIAL;
    }
    
    // Go through lights
    {
        PROFILE_MULTIPLE(GetLightBatches, lights_.size());
        
        unsigned lightQueueCount = 0;
        for (unsigned i = 0; i < lights_.size(); ++i)
        {
            Light* light = lights_[i];
            unsigned splits = ProcessLight(light);
            
            if (!splits)
                continue;
            
            // Prepare lit object + shadow caster queues for each split
            if (lightQueues_.size() < lightQueueCount + splits)
                lightQueues_.resize(lightQueueCount + splits);
            unsigned prevLightQueueCount = lightQueueCount;
            
            for (unsigned j = 0; j < splits; ++j)
            {
                Light* SplitLight = splitLights_[j];
                LightBatchQueue& lightQueue = lightQueues_[lightQueueCount];
                lightQueue.light_ = SplitLight;
                lightQueue.shadowBatches_.Clear();
                lightQueue.litBatches_.Clear();
                lightQueue.volumeBatches_.clear();
                lightQueue.lastSplit_ = false;
                
                // Loop through shadow casters
                Camera* shadowCamera = SplitLight->GetShadowCamera();
                for (unsigned k = 0; k < shadowCasters_[j].size(); ++k)
                {
                    Drawable* drawable = shadowCasters_[j][k];
                    unsigned numBatches = drawable->GetNumBatches();
                    
                    for (unsigned l = 0; l < numBatches; ++l)
                    {
                        Batch shadowBatch;
                        drawable->GetBatch(frame_, l, shadowBatch);
                        
                        Technique* tech = GetTechnique(drawable, shadowBatch.material_);
                        if ((!shadowBatch.geometry_) || (!tech))
                            continue;
                        
                        Pass* pass = tech->GetPass(PASS_SHADOW);
                        // Skip if material has no shadow pass
                        if (!pass)
                            continue;
                        
                        // Fill the rest of the batch
                        shadowBatch.camera_ = shadowCamera;
                        shadowBatch.distance_ = shadowCamera->GetDistance(drawable->GetWorldPosition());
                        shadowBatch.light_ = SplitLight;
                        shadowBatch.hasPriority_ = (!pass->GetAlphaTest()) && (!pass->GetAlphaMask());
                        
                        renderer_->setBatchShaders(shadowBatch, tech, pass);
                        lightQueue.shadowBatches_.AddBatch(shadowBatch);
                    }
                }
                
                // Loop through lit geometries
                if (litGeometries_[j].size())
                {
                    bool storeLightQueue = true;
                    
                    for (unsigned k = 0; k < litGeometries_[j].size(); ++k)
                    {
                        Drawable* drawable = litGeometries_[j][k];
                        
                        // If drawable limits maximum lights, only record the light, and check maximum count / build batches later
                        if (!drawable->GetMaxLights())
                            GetLitBatches(drawable, light, SplitLight, &lightQueue, litTransparencies, gBufferPass);
                        else
                        {
                            drawable->AddLight(SplitLight);
                            maxLightsDrawables.insert(drawable);
                        }
                    }
                    
                    // Store the light queue, and light volume batch in deferred mode
                    if (mode_ != RENDER_FORWARD)
                    {
                        Batch volumeBatch;
                        volumeBatch.geometry_ = renderer_->GetLightGeometry(SplitLight);
                        volumeBatch.worldTransform_ = &SplitLight->GetVolumeTransform(*camera_);
                        volumeBatch.overrideView_ = SplitLight->GetLightType() == LIGHT_DIRECTIONAL;
                        volumeBatch.camera_ = camera_;
                        volumeBatch.light_ = SplitLight;
                        volumeBatch.distance_ = SplitLight->GetDistance();
                        
                        renderer_->SetLightVolumeShaders(volumeBatch);
                        
                        // If light is a split point light, it must be treated as shadowed in any case for correct stencil clearing
                        if ((SplitLight->GetShadowMap()) || (SplitLight->GetLightType() == LIGHT_SPLITPOINT))
                            lightQueue.volumeBatches_.push_back(volumeBatch);
                        else
                        {
                            storeLightQueue = false;
                            noShadowLightQueue_.AddBatch(volumeBatch, true);
                        }
                    }
                    
                    if (storeLightQueue)
                    {
                        lightQueueIndex[SplitLight] = lightQueueCount;
                        ++lightQueueCount;
                    }
                }
            }
            
            // Mark the last split
            if (lightQueueCount != prevLightQueueCount)
                lightQueues_[lightQueueCount - 1].lastSplit_ = true;
        }
        
        // Resize the light queue vector now that final size is known
        lightQueues_.resize(lightQueueCount);
    }
    
    // Process drawables with limited light count
    if (maxLightsDrawables.size())
    {
        PROFILE(GetMaxLightsBatches);
        
        for (std::set<Drawable*>::iterator i = maxLightsDrawables.begin(); i != maxLightsDrawables.end(); ++i)
        {
            Drawable* drawable = *i;
            drawable->LimitLights();
            const std::vector<Light*>& lights = drawable->GetLights();
            
            for (unsigned i = 0; i < lights.size(); ++i)
            {
                Light* SplitLight = lights[i];
                Light* light = SplitLight->GetOriginalLight();
                if (!light)
                    light = SplitLight;
                
                // Find the correct light queue again
                LightBatchQueue* queue = 0;
                std::map<Light*, unsigned>::iterator j = lightQueueIndex.find(SplitLight);
                if (j != lightQueueIndex.end())
                    queue = &lightQueues_[j->second];
                
                GetLitBatches(drawable, light, SplitLight, queue, litTransparencies, gBufferPass);
            }
        }
    }
    
    // Go through geometries for base pass batches
    {
        PROFILE(GetBaseBatches);
        for (unsigned i = 0; i < geometries_.size(); ++i)
        {
            Drawable* drawable = geometries_[i];
            unsigned numBatches = drawable->GetNumBatches();
            
            for (unsigned j = 0; j < numBatches; ++j)
            {
                Batch baseBatch;
                drawable->GetBatch(frame_, j, baseBatch);
                
                Technique* tech = GetTechnique(drawable, baseBatch.material_);
                if ((!baseBatch.geometry_) || (!tech))
                    continue;
                
                // Check here if the material technique refers to a render target texture with camera(s) attached
                // Only check this for the main view (null rendertarget)
                if ((!renderTarget_) && (baseBatch.material_) && (baseBatch.material_->GetAuxViewFrameNumber() != frame_.frameNumber_))
                    CheckMaterialForAuxView(baseBatch.material_);
                
                // If object already has a lit base pass, can skip the unlit base pass
                if (drawable->HasBasePass(j))
                    continue;
                
                // Fill the rest of the batch
                baseBatch.camera_ = camera_;
                baseBatch.distance_ = drawable->GetDistance();
                
                Pass* pass = 0;
                // In deferred mode, check for a G-buffer batch first
                if (mode_ != RENDER_FORWARD)
                {
                    pass = tech->GetPass(gBufferPass);
                    if (pass)
                    {
                        renderer_->setBatchShaders(baseBatch, tech, pass);
                        baseBatch.hasPriority_ = (!pass->GetAlphaTest()) && (!pass->GetAlphaMask());
                        gBufferQueue_.AddBatch(baseBatch);
                        
                        // Check also for an additional pass. In light prepass mode this actually renders the visible geometry
                        pass = tech->GetPass(additionalPass);
                        if (pass)
                        {
                            renderer_->setBatchShaders(baseBatch, tech, pass);
                            baseQueue_.AddBatch(baseBatch);
                        }
                        
                        continue;
                    }
                }
                
                // Then check for forward rendering base pass
                pass = tech->GetPass(PASS_BASE);
                if (pass)
                {
                    renderer_->setBatchShaders(baseBatch, tech, pass);
                    if (pass->GetBlendMode() == BLEND_REPLACE)
                    {
                        baseBatch.hasPriority_ = (!pass->GetAlphaTest()) && (!pass->GetAlphaMask());
                        baseQueue_.AddBatch(baseBatch);
                    }
                    else
                    {
                        baseBatch.hasPriority_ = true;
                        transparentQueue_.AddBatch(baseBatch, true);
                    }
                    continue;
                }
                else
                {
                    // If no base pass, finally check for extra / custom pass
                    pass = tech->GetPass(PASS_EXTRA);
                    if (pass)
                    {
                        baseBatch.hasPriority_ = false;
                        renderer_->setBatchShaders(baseBatch, tech, pass);
                        extraQueue_.AddBatch(baseBatch);
                    }
                }
            }
        }
    }
    
    // All batches have been collected. Sort them now
    SortBatches();
}

void View::GetLitBatches(Drawable* drawable, Light* light, Light* SplitLight, LightBatchQueue* lightQueue,
    std::set<LitTransparencyCheck>& litTransparencies, PassType gBufferPass)
{
    bool splitPointLight = SplitLight->GetLightType() == LIGHT_SPLITPOINT;
    // Whether to allow shadows for transparencies, or for forward lit objects in deferred mode
    bool allowShadows = (!renderer_->reuseShadowMaps_) && (!splitPointLight);
    unsigned numBatches = drawable->GetNumBatches();
    
    for (unsigned i = 0; i < numBatches; ++i)
    {
        Batch litBatch;
        drawable->GetBatch(frame_, i, litBatch);
        
        Technique* tech = GetTechnique(drawable, litBatch.material_);
        if ((!litBatch.geometry_) || (!tech))
            continue;
        
        // If material uses opaque G-buffer rendering, skip
        if ((mode_ != RENDER_FORWARD) && (tech->HasPass(gBufferPass)))
            continue;
        
        Pass* pass = 0;
        bool priority = false;
        
        // For directional light, check for lit base pass
        if (SplitLight->GetLightType() == LIGHT_DIRECTIONAL)
        {
            if (!drawable->HasBasePass(i))
            {
                pass = tech->GetPass(PASS_LITBASE);
                if (pass)
                {
                    priority = true;
                    drawable->SetBasePass(i);
                }
            }
        }
        
        // If no first light pass, get ordinary light pass
        if (!pass)
            pass = tech->GetPass(PASS_LIGHT);
        // Skip if material does not receive light at all
        if (!pass)
            continue;
        
        // Fill the rest of the batch
        litBatch.camera_ = camera_;
        litBatch.distance_ = drawable->GetDistance();
        litBatch.light_ = SplitLight;
        litBatch.hasPriority_ = priority;
        
        // Check from the ambient pass whether the object is opaque
        Pass* ambientPass = tech->GetPass(PASS_BASE);
        if ((!ambientPass) || (ambientPass->GetBlendMode() == BLEND_REPLACE))
        {
            if (mode_ == RENDER_FORWARD)
            {
                if (lightQueue)
                {
                    renderer_->setBatchShaders(litBatch, tech, pass);
                    lightQueue->litBatches_.AddBatch(litBatch);
                }
            }
            else
            {
                renderer_->setBatchShaders(litBatch, tech, pass, allowShadows);
                baseQueue_.AddBatch(litBatch);
            }
        }
        else
        {
            if (splitPointLight)
            {
                // Check if already lit
                LitTransparencyCheck check(light, drawable, i);
                if (litTransparencies.find(check) != litTransparencies.end())
                    continue;
                // Use the original light instead of the split one, to choose correct scissor
                litBatch.light_ = light;
                litTransparencies.insert(check);
            }
            
            renderer_->setBatchShaders(litBatch, tech, pass, allowShadows);
            transparentQueue_.AddBatch(litBatch, true);
        }
    }
}

void View::RenderBatcheforward()
{
    {
        // Render opaque objects' base passes
        PROFILE(RenderBasePass);
        
        graphics_->ClearLastParameterSources();
        graphics_->SetColorWrite(true);
        graphics_->SetStencilTest(false);
        graphics_->SetRenderTarget(0, renderTarget_);
        graphics_->SetDepthStencil(depthStencil_);
        graphics_->SetViewport(screenRect_);
        graphics_->Clear(CLEAR_COLOR | CLEAR_DEPTH | CLEAR_STENCIL, zone_->GetFogColor());
        
        RenderBatchQueue(baseQueue_);
    }
    
    {
        // Render shadow maps + opaque objects' shadowed additive lighting
        PROFILE(RenderLights);
        
        for (unsigned i = 0; i < lightQueues_.size(); ++i)
        {
            LightBatchQueue& queue = lightQueues_[i];
            
            // If reusing shadowmaps, render each of them before the lit batches
            if ((renderer_->reuseShadowMaps_) && (queue.light_->GetShadowMap()))
                RenderShadowMap(queue);
            
            graphics_->ClearLastParameterSources();
            graphics_->SetRenderTarget(0, renderTarget_);
            graphics_->SetDepthStencil(depthStencil_);
            graphics_->SetViewport(screenRect_);
            
            RenderForwardLightBatchQueue(queue.litBatches_, queue.light_);
            
            // Clear the stencil buffer after the last split
            if (queue.lastSplit_)
            {
                LightType type = queue.light_->GetLightType();
                if ((type == LIGHT_SPLITPOINT) || (type == LIGHT_DIRECTIONAL))
                    DrawSplitLightToStencil(*camera_, queue.light_, true);
            }
        }
    }
    
    {
        // Render extra / custom passes
        PROFILE(RenderExtraPass);
        
        graphics_->ClearLastParameterSources();
        graphics_->SetRenderTarget(0, renderTarget_);
        graphics_->SetDepthStencil(depthStencil_);
        graphics_->SetViewport(screenRect_);
        
        RenderBatchQueue(extraQueue_);
    }
    
    {
        // Render transparent objects last (both base passes & additive lighting)
        PROFILE(RenderTransparent);
        
        RenderBatchQueue(transparentQueue_, true);
    }
}

void View::RenderBatchesDeferred()
{
    bool deferred = mode_ != RENDER_PREPASS;
    
    Texture2D* diffBuffer = graphics_->GetDiffBuffer();
    Texture2D* normalBuffer = graphics_->GetNormalBuffer();
    Texture2D* depthBuffer = graphics_->GetDepthBuffer();
    
    // Check for temporal antialiasing in deferred mode. Only use it on the main view (null rendertarget)
    bool temporalAA = (!renderTarget_) && (graphics_->GetMultiSample() > 0);
    if (temporalAA)
    {
        ++jitterCounter_;
        if (jitterCounter_ > 3)
            jitterCounter_ = 2;
        
        Vector2 jitter(-0.25f, -0.25f);
        if (jitterCounter_ & 1)
            jitter = -jitter;
        jitter.x_ /= width_;
        jitter.y_ /= height_;
        
        camera_->SetProjectionOffset(jitter);
    }
    
    RenderSurface* renderBuffer = temporalAA ? graphics_->GetScreenBuffer(jitterCounter_ & 1)->GetRenderSurface() : renderTarget_;
    
    // Set shader parameters needed only in deferred rendering
    Vector3 nearVector, farVector;
    camera_->GetFrustumSize(nearVector, farVector);
    Vector4 viewportParams(farVector.x_, farVector.y_, farVector.z_, 0.0f);
    
    float gBufferWidth = (float)diffBuffer->GetWidth();
    float gBufferHeight = (float)diffBuffer->GetHeight();
    float widthRange = 0.5f * width_ / gBufferWidth;
    float heightRange = 0.5f * height_ / gBufferHeight;
    Vector4 bufferUVOffset((0.5f + (float)screenRect_.left_) / gBufferWidth + widthRange,
        (0.5f + (float)screenRect_.top_) / gBufferHeight + heightRange, widthRange, heightRange);
    
    Vector4 viewportSize((float)screenRect_.left_ / gBufferWidth, (float)screenRect_.top_ / gBufferHeight,
        (float)screenRect_.right_ / gBufferWidth, (float)screenRect_.bottom_ / gBufferHeight);
    
    graphics_->SetVertexShaderParameter(VSP_FRUSTUMSIZE, viewportParams);
    graphics_->SetVertexShaderParameter(VSP_GBUFFEROFFSETS, bufferUVOffset);
    graphics_->SetPixelShaderParameter(PSP_GBUFFEROFFSETS, bufferUVOffset);
    graphics_->SetPixelShaderParameter(PSP_GBUFFERVIEWPORT, viewportSize);
    
    {
        // Render G-buffer
        PROFILE(RenderGBuffer);
        
        graphics_->ClearLastParameterSources();
        
        // Use always the default depth stencil, so that it matches the G-buffer size, and is in the expected format
        // Enable depth rendertarget only if hardware depth not supported
        graphics_->SetColorWrite(true);
        graphics_->SetScissorTest(false);
        graphics_->SetStencilTest(false);
        graphics_->ResetDepthStencil();
        if (deferred)
        {
            graphics_->SetRenderTarget(0, diffBuffer);
            graphics_->SetRenderTarget(1, normalBuffer);
            graphics_->SetRenderTarget(2, depthBuffer);
        }
        else
        {
            graphics_->SetRenderTarget(0, normalBuffer);
            graphics_->SetRenderTarget(1, depthBuffer);
        }
        graphics_->SetViewport(screenRect_);
        
        // Clear only depth and stencil at first, render the G-buffer batches
        graphics_->Clear(CLEAR_DEPTH | CLEAR_STENCIL);
        RenderBatchQueue(gBufferQueue_);
        
        // Then fill the untouched parts of the G-buffer with defaults: black diffuse + specular (deferred only), far depth
        graphics_->SetAlphaTest(false);
        graphics_->SetBlendMode(BLEND_REPLACE);
        graphics_->SetDepthTest(CMP_LESSEQUAL);
        graphics_->SetDepthWrite(false);
        if (deferred)
        {
            graphics_->ResetRenderTarget(2);
            graphics_->SetRenderTarget(1, depthBuffer);
            
            renderer_->DrawFullScreenQuad(*camera_, renderer_->GetVertexShader("Deferred/GBufferFill"),
                renderer_->GetPixelShader("Deferred/GBufferFill"), false);
        }
        else
        {
            graphics_->ResetRenderTarget(1);
            graphics_->SetRenderTarget(0, depthBuffer);
            graphics_->SetViewport(screenRect_);
            
            // The stencil shader writes color 1.0, which equals far depth
            renderer_->DrawFullScreenQuad(*camera_, renderer_->GetVertexShader("Stencil"),
                renderer_->GetPixelShader("Stencil"), false);
        }
    }
    
    if (deferred)
    {
        // Render ambient color & fog
        graphics_->ClearLastParameterSources();
        graphics_->SetDepthTest(CMP_ALWAYS);
        graphics_->SetRenderTarget(0, renderBuffer);
        graphics_->ResetRenderTarget(1);
        graphics_->ResetRenderTarget(2);
        graphics_->SetTexture(TU_DIFFBUFFER, diffBuffer);
        graphics_->SetTexture(TU_DEPTHBUFFER, depthBuffer);
        graphics_->SetViewport(screenRect_);
        
        renderer_->DrawFullScreenQuad(*camera_, renderer_->GetVertexShader("Deferred/Ambient"),
            renderer_->GetPixelShader("Deferred/Ambient"), false);
    }
    else
    {
        // Light prepass: reset the light accumulation buffer with black color
        graphics_->SetRenderTarget(0, diffBuffer);
        graphics_->ResetRenderTarget(1);
        graphics_->SetViewport(screenRect_);
        graphics_->Clear(CLEAR_COLOR);
    }
    
    {
        // Render lights
        PROFILE(RenderLights);
        
        // Shadowed lights
        for (unsigned i = 0; i < lightQueues_.size(); ++i)
        {
            LightBatchQueue& queue = lightQueues_[i];
            
            // If reusing shadowmaps, render each of them before the lit batches
            if ((renderer_->reuseShadowMaps_) && (queue.light_->GetShadowMap()))
                RenderShadowMap(queue);
            
            // Light volume batches are not sorted as there should be only one of them
            if (queue.volumeBatches_.size())
            {
                graphics_->ClearLastParameterSources();
                
                if (deferred)
                {
                    graphics_->SetRenderTarget(0, renderBuffer);
                    graphics_->SetTexture(TU_DIFFBUFFER, diffBuffer);
                }
                else
                    graphics_->SetRenderTarget(0, diffBuffer);
                
                graphics_->SetTexture(TU_NORMALBUFFER, normalBuffer);
                graphics_->SetTexture(TU_DEPTHBUFFER, depthBuffer);
                graphics_->ResetDepthStencil();
                graphics_->SetViewport(screenRect_);
                
                for (unsigned j = 0; j < queue.volumeBatches_.size(); ++j)
                {
                    renderer_->SetupLightBatch(queue.volumeBatches_[j]);
                    queue.volumeBatches_[j].Draw(graphics_);
                }
                
                // If was the last split of a split point light, clear the stencil by rendering the point light again
                if ((queue.lastSplit_) && (queue.light_->GetLightType() == LIGHT_SPLITPOINT))
                    DrawSplitLightToStencil(*camera_, queue.light_, true);
            }
        }
        
        // Non-shadowed lights
        if (noShadowLightQueue_.sortedBatches_.size())
        {
            graphics_->ClearLastParameterSources();
            
            if (deferred)
            {
                graphics_->SetRenderTarget(0, renderBuffer);
                graphics_->SetTexture(TU_DIFFBUFFER, diffBuffer);
            }
            else
                graphics_->SetRenderTarget(0, diffBuffer);
            
            graphics_->SetTexture(TU_NORMALBUFFER, normalBuffer);
            graphics_->SetTexture(TU_DEPTHBUFFER, depthBuffer);
            graphics_->ResetDepthStencil();
            graphics_->SetViewport(screenRect_);
            
            for (unsigned i = 0; i < noShadowLightQueue_.sortedBatches_.size(); ++i)
            {
                renderer_->SetupLightBatch(*noShadowLightQueue_.sortedBatches_[i]);
                noShadowLightQueue_.sortedBatches_[i]->Draw(graphics_);
            }
        }
    }
    
    {
        // Render base passes
        PROFILE(RenderBasePass);
        
        graphics_->ClearLastParameterSources();
        graphics_->SetStencilTest(false);
        graphics_->SetRenderTarget(0, renderBuffer);
        graphics_->SetTexture(TU_DIFFBUFFER, 0);
        graphics_->SetTexture(TU_NORMALBUFFER, 0);
        graphics_->SetTexture(TU_DEPTHBUFFER, 0);
        graphics_->SetViewport(screenRect_);
        
        if (!deferred)
            graphics_->Clear(CLEAR_COLOR, zone_->GetFogColor());
        
        // Remember to bind the light buffer in prepass mode
        RenderBatchQueue(baseQueue_, true, !deferred);
    }
    
    {
        // Render extra / custom passes
        PROFILE(RenderExtraPass);
        
        RenderBatchQueue(extraQueue_);
    }
    
    {
        // Render transparent objects last (both ambient & additive lighting)
        PROFILE(RenderTransparent);
        
        RenderBatchQueue(transparentQueue_, true);
    }
    
    // Render temporal antialiasing now if enabled
    if (temporalAA)
    {
        PROFILE(RenderTemporalAA);
        
        // Disable averaging if it is the first frame rendered in this view
        float thisFrameWeight = jitterCounter_ < 2 ? 1.0f : 0.5f;
        
        Vector4 depthMode = Vector4::ZERO;
        if (camera_->IsOrthographic())
            depthMode.z_ = 1.0f;
        else
            depthMode.w_ = 1.0f / camera_->GetFarClip();
        
        graphics_->SetAlphaTest(false);
        graphics_->SetBlendMode(BLEND_REPLACE);
        graphics_->SetDepthTest(CMP_ALWAYS);
        graphics_->SetDepthWrite(false);
        graphics_->SetScissorTest(false);
        graphics_->SetStencilTest(false);
        graphics_->SetRenderTarget(0, renderTarget_);
        graphics_->SetViewport(screenRect_);
        graphics_->SetTexture(TU_DIFFBUFFER, graphics_->GetScreenBuffer(jitterCounter_ & 1));
        graphics_->SetTexture(TU_NORMALBUFFER, graphics_->GetScreenBuffer((jitterCounter_ + 1) & 1));
        graphics_->SetTexture(TU_DEPTHBUFFER, graphics_->GetDepthBuffer());
        graphics_->SetVertexShaderParameter(VSP_CAMERAROT, camera_->GetWorldTransform().GetRotationMatrix());
        graphics_->SetVertexShaderParameter(VSP_DEPTHMODE, depthMode);
        graphics_->SetPixelShaderParameter(PSP_CAMERAPOS, camera_->GetWorldPosition());
        graphics_->SetPixelShaderParameter(PSP_ANTIALIASWEIGHTS, Vector4(thisFrameWeight, 1.0f - thisFrameWeight, 0.0f, 0.0f));
        graphics_->SetPixelShaderParameter(PSP_SAMPLEOFFSETS, Vector4(1.0f / gBufferWidth, 1.0f / gBufferHeight, 0.0f, 0.0f));
        graphics_->SetPixelShaderParameter(PSP_VIEWPROJ, camera_->GetProjection(false) * lastCameraView_);
        
        unsigned index = camera_->IsOrthographic() ? 1 : 0;
        std::string shaderName = "TemporalAA_" + aaVariation[index];
        
        renderer_->DrawFullScreenQuad(*camera_, renderer_->GetVertexShader(shaderName),
            renderer_->GetPixelShader(shaderName), false);
        
        // Store view transform for next frame
        lastCameraView_ = camera_->GetInverseWorldTransform();
    }
}

void View::UpdateOccluders(std::vector<Drawable*>& occluders, Camera* camera)
{
    float occluderSizeThreshold_ = renderer_->GetOccluderSizeThreshold();
    float halfViewSize = camera->GetHalfViewSize();
    float invOrthoSize = 1.0f / camera->GetOrthoSize();
    Vector3 cameraPos = camera->GetWorldPosition();
    unsigned cameraViewMask = camera->GetViewMask();
    
    for (unsigned i = 0; i < occluders.size(); ++i)
    {
        Drawable* occluder = occluders[i];
        occluder->UpdateDistance(frame_);
        bool erase = false;
        
        // Check view mask
        if (!(cameraViewMask & occluder->GetViewMask()))
            erase = true;
        
        // Check occluder's draw distance (in main camera view)
        float maxDistance = occluder->GetDrawDistance();
        if ((maxDistance > 0.0f) && (occluder->GetDistance() > maxDistance))
            erase = true;
        
        // Check that occluder is big enough on the screen
        const BoundingBox& box = occluder->GetWorldBoundingBox();
        float diagonal = (box.max_ - box.min_).GetLengthFast();
        float compare;
        if (!camera->IsOrthographic())
            compare = diagonal * halfViewSize / occluder->GetDistance();
        else
            compare = diagonal * invOrthoSize;
        
        if (compare < occluderSizeThreshold_)
            erase = true;
        
        if (!erase)
        {
            unsigned totalTriangles = 0;
            unsigned batches = occluder->GetNumBatches();
            Batch tempBatch;
            
            for (unsigned j = 0; j < batches; ++j)
            {
                occluder->GetBatch(frame_, j, tempBatch);
                if (tempBatch.geometry_)
                    totalTriangles += tempBatch.geometry_->GetIndexCount() / 3;
            }
            
            // Store amount of triangles divided by screen size as a sorting key
            // (best occluders are big and have few triangles)
            occluder->SetSortValue((float)totalTriangles / compare);
        }
        else
        {
            occluders.erase(occluders.begin() + i);
            --i;
        }
    }
    
    // Sort occluders so that if triangle budget is exceeded, best occluders have been drawn
    if (occluders.size())
        std::sort(occluders.begin(), occluders.end(), CompareDrawables);
}

void View::DrawOccluders(OcclusionBuffer* buffer, const std::vector<Drawable*>& occluders)
{
    for (unsigned i = 0; i < occluders.size(); ++i)
    {
        Drawable* occluder = occluders[i];
        if (i > 0)
        {
            // For subsequent occluders, do a test against the pixel-level occlusion buffer to see if rendering is necessary
            if (!buffer->IsVisible(occluder->GetWorldBoundingBox()))
                continue;
        }
        
        occluder->UpdateGeometry(frame_);
        // Check for running out of triangles
        if (!occluder->DrawOcclusion(buffer))
            return;
    }
}

unsigned View::ProcessLight(Light* light)
{
    unsigned numLitGeometries = 0;
    unsigned numShadowCasters = 0;
    
    unsigned numSplits;
    // Check if light should be shadowed
    bool isShadowed = (drawShadows_) && (light->GetCastShadows());
    // If shadow distance non-zero, check it
    if ((isShadowed) && (light->GetShadowDistance() > 0.0f) && (light->GetDistance() > light->GetShadowDistance()))
        isShadowed = false;
    
    // If light has no ramp textures defined, set defaults
    if ((light->GetLightType() != LIGHT_DIRECTIONAL) && (!light->GetRampTexture()))
        light->SetRampTexture(renderer_->GetDefaultLightRamp());
    if ((light->GetLightType() == LIGHT_SPOT) && (!light->GetShapeTexture()))
        light->SetShapeTexture(renderer_->GetDefaultLightSpot());
    
    // Split the light if necessary
    if (isShadowed)
        numSplits = SplitLight(light);
    else
    {
        // No splitting, use the original light
        splitLights_[0] = light;
        numSplits = 1;
    }
    
    // For a shadowed directional light, get occluders once using the whole (non-split) light frustum
    bool useOcclusion = false;
    OcclusionBuffer* buffer = 0;
    
    if ((maxOccluderTriangles_ > 0) && (isShadowed) && (light->GetLightType() == LIGHT_DIRECTIONAL))
    {
        // This shadow camera is never used for actually querying shadow casters, just occluders
        Camera* shadowCamera = renderer_->CreateShadowCamera();
        light->SetShadowCamera(shadowCamera);
        SetupShadowCamera(light, true);
        
        // Get occluders, which must be shadow-casting themselves
        FrustumOctreeQuery query(reinterpret_cast<std::vector<Drawable*>& >(shadowOccluders_), shadowCamera->GetFrustum(),
            DRAWABLE_GEOMETRY, true, true);
        octree_->GetDrawables(query);
        
        UpdateOccluders(shadowOccluders_, shadowCamera);
        
        if (shadowOccluders_.size())
        {
            // Shadow viewport is rectangular and consumes more CPU fillrate, so halve size
            buffer = renderer_->GetOrCreateOcclusionBuffer(shadowCamera, maxOccluderTriangles_, true);
            
            DrawOccluders(buffer, shadowOccluders_);
            buffer->BuildDepthHierarchy();
            useOcclusion = true;
        }
    }
    
    // Process each split for shadow camera update, lit geometries, and shadow casters
    for (unsigned i = 0; i < numSplits; ++i)
    {
        litGeometries_[i].clear();
        shadowCasters_[i].clear();
    }
    
    for (unsigned i = 0; i < numSplits; ++i)
    {
        Light* split = splitLights_[i];
        LightType type = split->GetLightType();
        bool isSplitShadowed = (isShadowed) && (split->GetCastShadows());
        Camera* shadowCamera = 0;
        
        // If shadow casting, choose the shadow map & update shadow camera
        if (isSplitShadowed)
        {
            shadowCamera = renderer_->CreateShadowCamera();
            split->SetShadowMap(renderer_->GetShadowMap(splitLights_[i]->GetShadowResolution()));
            // Check if managed to get a shadow map. Otherwise must convert to non-shadowed
            if (split->GetShadowMap())
            {
                split->SetShadowCamera(shadowCamera);
                SetupShadowCamera(split);
            }
            else
            {
                isSplitShadowed = false;
                split->SetShadowCamera(0);
            }
        }
        else
        {
            split->SetShadowCamera(0);
            split->SetShadowMap(0);
        }
        
        BoundingBox geometryBox;
        BoundingBox shadowCasterBox;
        
        switch (type)
        {
        case LIGHT_DIRECTIONAL:
            // Loop through visible geometries and check if they belong to this split
            {
                float nearSplit = split->GetNearSplit() - split->GetNearFadeRange();
                float farSplit = split->GetFarSplit();
                // If split extends to the whole visible frustum, no depth check necessary
                bool optimize = (nearSplit <= camera_->GetNearClip()) && (farSplit >= camera_->GetFarClip());
                
                // If whole visible scene is outside the split, can reject trivially
                if ((sceneViewBox_.min_.z_ > farSplit) || (sceneViewBox_.max_.z_ < nearSplit))
                {
                    split->SetShadowMap(0);
                    continue;
                }
                
                bool generateBoxes = (isSplitShadowed) && (split->GetShadowFocus().focus_);
                Matrix4x3 lightView;
                if (shadowCamera)
                    lightView = shadowCamera->GetInverseWorldTransform();
                
                if (!optimize)
                {
                    for (unsigned j = 0; j < geometries_.size(); ++j)
                    {
                        Drawable* drawable = geometries_[j];
                        const GeometryDepthBounds& bounds = geometryDepthBounds_[j];
                        
                        // Check bounds and light mask
                        if ((bounds.min_ <= farSplit) && (bounds.max_ >= nearSplit) && (drawable->GetLightMask() &
                            split->GetLightMask()))
                        {
                            litGeometries_[i].push_back(drawable);
                            if (generateBoxes)
                                geometryBox.Merge(drawable->GetWorldBoundingBox().GetTransformed(lightView));
                        }
                    }
                }
                else
                {
                    for (unsigned j = 0; j < geometries_.size(); ++j)
                    {
                        Drawable* drawable = geometries_[j];
                        
                        // Need to check light mask only
                        if (drawable->GetLightMask() & split->GetLightMask())
                        {
                            litGeometries_[i].push_back(drawable);
                            if (generateBoxes)
                                geometryBox.Merge(drawable->GetWorldBoundingBox().GetTransformed(lightView));
                        }
                    }
                }
            }
            
            // Then get shadow casters by shadow camera frustum query. Use occlusion because of potentially many geometries
            if ((isSplitShadowed) && (litGeometries_[i].size()))
            {
                Camera* shadowCamera = split->GetShadowCamera();
                
                if (!useOcclusion)
                {
                    // Get potential shadow casters without occlusion
                    FrustumOctreeQuery query(tempDrawables_, shadowCamera->GetFrustum(), DRAWABLE_GEOMETRY);
                    octree_->GetDrawables(query);
                }
                else
                {
                    // Get potential shadow casters with occlusion
                    OccludedFrustumOctreeQuery query(tempDrawables_, shadowCamera->GetFrustum(), buffer,
                        DRAWABLE_GEOMETRY);
                    octree_->GetDrawables(query);
                }
                
                ProcessLightQuery(i, tempDrawables_, geometryBox, shadowCasterBox, false, isSplitShadowed);
            }
            break;
            
        case LIGHT_POINT:
            {
                SphereOctreeQuery query(tempDrawables_, Sphere(split->GetWorldPosition(), split->GetRange()), DRAWABLE_GEOMETRY);
                octree_->GetDrawables(query);
                ProcessLightQuery(i, tempDrawables_, geometryBox, shadowCasterBox, true, false);
            }
            break;
            
        case LIGHT_SPOT:
        case LIGHT_SPLITPOINT:
            {
                FrustumOctreeQuery query(tempDrawables_, splitLights_[i]->GetFrustum(), DRAWABLE_GEOMETRY);
                octree_->GetDrawables(query);
                ProcessLightQuery(i, tempDrawables_, geometryBox, shadowCasterBox, true, isSplitShadowed);
            }
            break;
        }
        
        // Optimization: if a particular split has no shadow casters, render as unshadowed
        if (!shadowCasters_[i].size())
            split->SetShadowMap(0);
        
        // Focus shadow camera as applicable
        if (split->GetShadowMap())
        {
            if (split->GetShadowFocus().focus_)
                FocusShadowCamera(split, geometryBox, shadowCasterBox);
            
            // Set a zoom factor to ensure that we do not render to the shadow map border
            // (clamp addressing is necessary because border mode /w hardware shadow maps is not supported by all GPUs)
            Camera* shadowCamera = split->GetShadowCamera();
            Texture2D* shadowMap = split->GetShadowMap();
            if (shadowCamera->GetZoom() >= 1.0f)
                shadowCamera->SetZoom(shadowCamera->GetZoom() * ((float)(shadowMap->GetWidth() - 2) / (float)shadowMap->GetWidth()));
        }
        
        // Update count of total lit geometries & shadow casters
        numLitGeometries += litGeometries_[i].size();
        numShadowCasters += shadowCasters_[i].size();
    }
    
    // If no lit geometries at all, no need to process further
    if (!numLitGeometries)
        numSplits = 0;
    // If no shadow casters at all, concatenate lit geometries into one & return the original light
    else if (!numShadowCasters)
    {
        if (numSplits > 1)
        {
            // Make sure there are no duplicates
            std::set<Drawable*> allLitGeometries;
            for (unsigned i = 0; i < numSplits; ++i)
            {
                for (std::vector<Drawable*>::iterator j = litGeometries_[i].begin(); j != litGeometries_[i].end(); ++j)
                    allLitGeometries.insert(*j);
            }
            
            litGeometries_[0].resize(allLitGeometries.size());
            unsigned index = 0;
            for (std::set<Drawable*>::iterator i = allLitGeometries.begin(); i != allLitGeometries.end(); ++i)
                litGeometries_[0][index++] = *i;
        }
        
        splitLights_[0] = light;
        splitLights_[0]->SetShadowMap(0);
        numSplits = 1;
    }
    
    return numSplits;
}

void View::ProcessLightQuery(unsigned splitIndex, const std::vector<Drawable*>& result, BoundingBox& geometryBox,
    BoundingBox& shadowCasterBox, bool getLitGeometries, bool GetShadowCasters)
{
    Light* light = splitLights_[splitIndex];
    
    Matrix4x3 lightView;
    Matrix4 lightProj;
    Frustum lightViewFrustum;
    BoundingBox lightViewFrustumBox;
    bool mergeBoxes = (light->GetLightType() != LIGHT_SPLITPOINT) && (light->GetShadowMap()) && (light->GetShadowFocus().focus_);
    bool projectBoxes = false;
    
    Camera* shadowCamera = light->GetShadowCamera();
    if (shadowCamera)
    {
        bool projectBoxes = !shadowCamera->IsOrthographic();
        lightView = shadowCamera->GetInverseWorldTransform();
        lightProj = shadowCamera->GetProjection();
        
        // Transform scene frustum into shadow camera's view space for shadow caster visibility check
        // For point & spot lights, we can use the whole scene frustum. For directional lights, use the
        // intersection of the scene frustum and the split frustum, so that shadow casters do not get
        // rendered into unnecessary splits
        if (light->GetLightType() != LIGHT_DIRECTIONAL)
            lightViewFrustum = camera_->GetSplitFrustum(sceneViewBox_.min_.z_, sceneViewBox_.max_.z_).GetTransformed(lightView);
        else
            lightViewFrustum = camera_->GetSplitFrustum(Max(sceneViewBox_.min_.z_, light->GetNearSplit() - light->GetNearFadeRange()),
                Min(sceneViewBox_.max_.z_, light->GetFarSplit())).GetTransformed(lightView);
        lightViewFrustumBox.Define(lightViewFrustum);
        
        // Check for degenerate split frustum: in that case there is no need to get shadow casters
        if (lightViewFrustum.vertices_[0] == lightViewFrustum.vertices_[4])
            GetShadowCasters = false;
    }
    else
        GetShadowCasters = false;
    
    BoundingBox lightViewBox;
    BoundingBox lightProjBox;
    
    for (unsigned i = 0; i < result.size(); ++i)
    {
        Drawable* drawable = static_cast<Drawable*>(result[i]);
        drawable->UpdateDistance(frame_);
        bool boxGenerated = false;
        
        // If draw distance non-zero, check it
        float maxDistance = drawable->GetDrawDistance();
        if ((maxDistance > 0.0f) && (drawable->GetDistance() > maxDistance))
            continue;
        
        // Check light mask
        if (!(drawable->GetLightMask() & light->GetLightMask()))
            continue;
        
        // Get lit geometry only if inside main camera frustum this frame
        if ((getLitGeometries) && (drawable->IsInView(frame_)))
        {
            if (mergeBoxes)
            {
                // Transform bounding box into light view space, and to projection space if needed
                lightViewBox = drawable->GetWorldBoundingBox().GetTransformed(lightView);
                
                if (!projectBoxes)
                    geometryBox.Merge(lightViewBox);
                else
                {
                    lightProjBox = lightViewBox.GetProjected(lightProj);
                    geometryBox.Merge(lightProjBox);
                }
                
                boxGenerated = true;
            }
            
            litGeometries_[splitIndex].push_back(drawable);
        }
        
        // Shadow caster need not be inside main camera frustum: in that case try to detect whether
        // the shadow projection intersects the view
        if ((GetShadowCasters) && (drawable->GetCastShadows()))
        {
            // If shadow distance non-zero, check it
            float maxShadowDistance = drawable->GetShadowDistance();
            if ((maxShadowDistance > 0.0f) && (drawable->GetDistance() > maxShadowDistance))
                continue;
            
            if (!boxGenerated)
                lightViewBox = drawable->GetWorldBoundingBox().GetTransformed(lightView);
            
            if (IsShadowCasterVisible(drawable, lightViewBox, shadowCamera, lightView, lightViewFrustum, lightViewFrustumBox))
            {
                if (mergeBoxes)
                {
                    if (!projectBoxes)
                        shadowCasterBox.Merge(lightViewBox);
                    else
                    {
                        if (!boxGenerated)
                            lightProjBox = lightViewBox.GetProjected(lightProj);
                        shadowCasterBox.Merge(lightProjBox);
                    }
                }
                
                // Update geometry now if not updated yet
                if (!drawable->IsInView(frame_))
                {
                    drawable->MarkInShadowView(frame_);
                    drawable->UpdateGeometry(frame_);
                }
                shadowCasters_[splitIndex].push_back(drawable);
            }
        }
    }
}

bool View::IsShadowCasterVisible(Drawable* drawable, BoundingBox lightViewBox, Camera* shadowCamera, const Matrix4x3& lightView,
    const Frustum& lightViewFrustum, const BoundingBox& lightViewFrustumBox)
{
    // If shadow caster is also an occluder, must let it be visible, because it has potentially already culled
    // away other shadow casters (could also check the actual shadow occluder vector, but that would be slower)
    if (drawable->IsOccluder())
        return true;
    
    if (shadowCamera->IsOrthographic())
    {
        // Extrude the light space bounding box up to the far edge of the frustum's light space bounding box
        lightViewBox.max_.z_ = Max(lightViewBox.max_.z_,lightViewFrustumBox.max_.z_);
        return lightViewFrustum.IsInsideFast(lightViewBox) != OUTSIDE;
    }
    else
    {
        // If light is not directional, can do a simple check: if object is visible, its shadow is too
        if (drawable->IsInView(frame_))
            return true;
        
        // For perspective lights, extrusion direction depends on the position of the shadow caster
        Vector3 center = lightViewBox.GetCenter();
        Ray extrusionRay(center, center.GetNormalized());
        
        float extrusionDistance = shadowCamera->GetFarClip();
        float originalDistance = Clamp(center.GetLengthFast(), M_EPSILON, extrusionDistance);
        
        // Because of the perspective, the bounding box must also grow when it is extruded to the distance
        float sizeFactor = extrusionDistance / originalDistance;
        
        // Calculate the endpoint box and merge it to the original. Because it's axis-aligned, it will be larger
        // than necessary, so the test will be conservative
        Vector3 newCenter = extrusionDistance * extrusionRay.direction_;
        Vector3 newHalfSize = lightViewBox.GetSize() * sizeFactor * 0.5f;
        BoundingBox extrudedBox(newCenter - newHalfSize, newCenter + newHalfSize);
        lightViewBox.Merge(extrudedBox);
        
        return lightViewFrustum.IsInsideFast(lightViewBox) != OUTSIDE;
    }
}

void View::SetupShadowCamera(Light* light, bool shadowOcclusion)
{
    Camera* shadowCamera = light->GetShadowCamera();
    Node* cameraNode = shadowCamera->GetNode();
    const FocusParameters& parameters = light->GetShadowFocus();
    
    // Reset zoom
    shadowCamera->SetZoom(1.0f);
    
    switch(light->GetLightType())
    {
    case LIGHT_DIRECTIONAL:
        {
            float extrusionDistance = camera_->GetFarClip();
            
            // Calculate initial position & rotation
            Vector3 lightWorldDirection = light->GetWorldRotation() * Vector3::FORWARD;
            Vector3 pos = camera_->GetWorldPosition() - extrusionDistance * lightWorldDirection;
            Quaternion rot(Vector3::FORWARD, lightWorldDirection);
            cameraNode->SetTransform(pos, rot);
            
            // Calculate main camera shadowed frustum in light's view space
            float sceneMaxZ = camera_->GetFarClip();
            // When shadow focusing is enabled, use the scene far Z to limit maximum frustum size
            if ((shadowOcclusion) || (parameters.focus_))
                sceneMaxZ = Min(sceneViewBox_.max_.z_, sceneMaxZ);
            
            Matrix4x3 lightView(shadowCamera->GetInverseWorldTransform());
            Frustum lightViewSplitFrustum = camera_->GetSplitFrustum(light->GetNearSplit() - light->GetNearFadeRange(),
                Min(light->GetFarSplit(), sceneMaxZ)).GetTransformed(lightView);
            
            // Fit the frustum inside a bounding box. If uniform size, use a sphere instead
            BoundingBox shadowBox;
            if ((!shadowOcclusion) && (parameters.nonUniform_))
                shadowBox.Define(lightViewSplitFrustum);
            else
            {
                Sphere shadowSphere;
                shadowSphere.Define(lightViewSplitFrustum);
                shadowBox.Define(shadowSphere);
            }
            
            shadowCamera->SetOrthographic(true);
            shadowCamera->SetNearClip(0.0f);
            shadowCamera->SetFarClip(shadowBox.max_.z_);
            
            // Center shadow camera on the bounding box, snap to whole texels
            QuantizeDirShadowCamera(light, shadowBox);
        }
        break;
        
    case LIGHT_SPOT:
    case LIGHT_SPLITPOINT:
        {
            cameraNode->SetTransform(light->GetWorldPosition(), light->GetWorldRotation());
            shadowCamera->SetNearClip(light->GetShadowNearFarRatio() * light->GetRange());
            shadowCamera->SetFarClip(light->GetRange());
            shadowCamera->SetOrthographic(false);
            shadowCamera->SetFov(light->GetFov());
            shadowCamera->SetAspectRatio(light->GetAspectRatio());
            
            // For spot lights, zoom out shadowmap if far away (reduces fillrate)
            if ((light->GetLightType() == LIGHT_SPOT) && (parameters.zoomOut_))
            {
                // Make sure the out-zooming does not start while we are inside the spot
                float distance = Max((camera_->GetInverseWorldTransform() * light->GetWorldPosition()).z_ - light->GetRange(), 1.0f);
                float lightPixels = (((float)height_ * light->GetRange() * camera_->GetZoom() * 0.5f) / distance);
                
                // Clamp pixel amount to a sufficient minimum to avoid self-shadowing artifacts due to loss of precision
                if (lightPixels < SHADOW_MIN_PIXELS)
                    lightPixels = SHADOW_MIN_PIXELS;
                
                float zoolevel_ = Min(lightPixels / (float)light->GetShadowMap()->GetHeight(), 1.0f);
                
                shadowCamera->SetZoom(zoolevel_);
            }
        }
        break;
    }
}

void View::FocusShadowCamera(Light* light, const BoundingBox& geometryBox, const BoundingBox& shadowCasterBox)
{
    // If either no geometries or no shadow casters, do nothing
    if ((!geometryBox.defined_) || (!shadowCasterBox.defined_))
        return;
    
    Camera* shadowCamera = light->GetShadowCamera();
    const FocusParameters& parameters = light->GetShadowFocus();
    
    switch (light->GetLightType())
    {
    case LIGHT_DIRECTIONAL:
        {
            BoundingBox combinedBox;
            combinedBox.max_.y_ = shadowCamera->GetOrthoSize() * 0.5f;
            combinedBox.max_.x_ = shadowCamera->GetAspectRatio() * combinedBox.max_.y_;
            combinedBox.min_.y_ = -combinedBox.max_.y_;
            combinedBox.min_.x_ = -combinedBox.max_.x_;
            combinedBox.Intersect(geometryBox);
            combinedBox.Intersect(shadowCasterBox);
            QuantizeDirShadowCamera(light, combinedBox);
        }
        break;
        
    case LIGHT_SPOT:
        // Can not move, but can zoom the shadow camera. Check for out-zooming (distant shadow map), do nothing in that case
        if (shadowCamera->GetZoom() >= 1.0f)
        {
            BoundingBox combinedBox(-1.0f, 1.0f);
            combinedBox.Intersect(geometryBox);
            combinedBox.Intersect(shadowCasterBox);
            
            float viewSizeX = Max(fabsf(combinedBox.min_.x_), fabsf(combinedBox.max_.x_));
            float viewSizeY = Max(fabsf(combinedBox.min_.y_), fabsf(combinedBox.max_.y_));
            float viewSize = Max(viewSizeX, viewSizeY);
            // Scale the quantization parameters, because view size is in projection space (-1.0 - 1.0)
            float invOrthoSize = 1.0f / shadowCamera->GetOrthoSize();
            float quantize = parameters.quantize_ * invOrthoSize;
            float minView = parameters.minView_ * invOrthoSize;
            viewSize = Max(ceilf(viewSize / quantize) * quantize, minView);
            
            if (viewSize < 1.0f)
                shadowCamera->SetZoom(1.0f / viewSize);
        }
        break;
    }
}

void View::QuantizeDirShadowCamera(Light* light, const BoundingBox& viewBox)
{
    Camera* shadowCamera = light->GetShadowCamera();
    Node* cameraNode = shadowCamera->GetNode();
    const FocusParameters& parameters = light->GetShadowFocus();
    
    float minX = viewBox.min_.x_;
    float minY = viewBox.min_.y_;
    float maxX = viewBox.max_.x_;
    float maxY = viewBox.max_.y_;
    
    Vector2 center((minX + maxX) * 0.5f, (minY + maxY) * 0.5f);
    Vector2 viewSize(maxX - minX, maxY - minY);
    
    // Quantize size to reduce swimming
    // Note: if size is uniform and there is no focusing, quantization is unnecessary
    if (parameters.nonUniform_)
    {
        viewSize.x_ = ceilf(sqrtf(viewSize.x_ / parameters.quantize_));
        viewSize.y_ = ceilf(sqrtf(viewSize.y_ / parameters.quantize_));
        viewSize.x_ = Max(viewSize.x_ * viewSize.x_ * parameters.quantize_, parameters.minView_);
        viewSize.y_ = Max(viewSize.y_ * viewSize.y_ * parameters.quantize_, parameters.minView_);
    }
    else if (parameters.focus_)
    {
        viewSize.x_ = Max(viewSize.x_, viewSize.y_);
        viewSize.x_ = ceilf(sqrtf(viewSize.x_ / parameters.quantize_));
        viewSize.x_ = Max(viewSize.x_ * viewSize.x_ * parameters.quantize_, parameters.minView_);
        viewSize.y_ = viewSize.x_;
    }
    
    shadowCamera->SetOrthoSize(viewSize);
    
    // Center shadow camera to the view space bounding box
    Vector3 pos = shadowCamera->GetWorldPosition();
    Quaternion rot = shadowCamera->GetWorldRotation();
    Vector3 adjust(center.x_, center.y_, 0.0f);
    cameraNode->Translate(rot * adjust);
    
    // If there is a shadow map, snap to its whole texels
    Texture2D* shadowMap = light->GetShadowMap();
    if (shadowMap)
    {
        Vector3 viewPos(rot.GetInverse() * shadowCamera->GetWorldPosition());
        // Take into account that shadow map border will not be used
        float invActualSize = 1.0f / (float)(shadowMap->GetWidth() - 2);
        Vector2 texelSize(viewSize.x_ * invActualSize, viewSize.y_ * invActualSize);
        Vector3 snap(-fmodf(viewPos.x_, texelSize.x_), -fmodf(viewPos.y_, texelSize.y_), 0.0f);
        cameraNode->Translate(rot * snap);
    }
}

void View::OptimizeLightByScissor(Light* light)
{
    if (light)
        graphics_->SetScissorTest(true, GetLightScissor(light));
    else
        graphics_->SetScissorTest(false);
}

const Rect& View::GetLightScissor(Light* light)
{
    std::map<Light*, Rect>::iterator i = lightScissorCache_.find(light);
    if (i != lightScissorCache_.end())
        return i->second;
    
    Matrix4x3 view(camera_->GetInverseWorldTransform());
    Matrix4 projection(camera_->GetProjection());
    
    switch (light->GetLightType())
    {
    case LIGHT_POINT:
        {
            BoundingBox viewBox = light->GetWorldBoundingBox().GetTransformed(view);
            return lightScissorCache_[light] = viewBox.GetProjected(projection);
        }
        
    case LIGHT_SPOT:
    case LIGHT_SPLITPOINT:
        {
            Frustum viewFrustum = light->GetFrustum().GetTransformed(view);
            return lightScissorCache_[light] = viewFrustum.GetProjected(projection);
        }
        
    default:
        return lightScissorCache_[light] = Rect::FULL;
    }
}

unsigned View::SplitLight(Light* light)
{
    LightType type = light->GetLightType();
    
    if (type == LIGHT_DIRECTIONAL)
    {
        const CascadeParameters& cascade = light->GetShadowCascade();
        
        unsigned splits = cascade.splits_;
        if (splits > MAX_LIGHT_SPLITS - 1)
            splits = MAX_LIGHT_SPLITS;
        
        // Orthographic view actually has near clip 0, but clamp it to a theoretical minimum
        float farClip = Min(cascade.shadowRange_, camera_->GetFarClip()); // Shadow range end
        float nearClip = Max(camera_->GetNearClip(), M_MIN_NEARCLIP); // Shadow range start
        bool CreateExtraSplit = farClip < camera_->GetFarClip();
        
        // Practical split scheme (Zhang et al.)
        unsigned i;
        for (i = 0; i < splits; ++i)
        {
            // Set a minimum for the fade range to avoid boundary artifacts (missing lighting)
            float splitFadeRange = Max(cascade.splitFadeRange_, 0.001f);
            
            float iPerM = (float)i / (float)splits;
            float log = nearClip * powf(farClip / nearClip, iPerM);
            float uniform = nearClip + (farClip - nearClip) * iPerM;
            float nearSplit = log * cascade.lambda_ + uniform * (1.0f - cascade.lambda_);
            float nearFadeRange = nearSplit * splitFadeRange;
            
            iPerM = (float)(i + 1) / (float)splits;
            log = nearClip * powf(farClip / nearClip, iPerM);
            uniform = nearClip + (farClip - nearClip) * iPerM;
            float farSplit = log * cascade.lambda_ + uniform * (1.0f - cascade.lambda_);
            float farFadeRange = farSplit * splitFadeRange;
            
            // If split is completely beyond camera far clip, we are done
            if ((nearSplit - nearFadeRange) > camera_->GetFarClip())
                break;
            
            Light* SplitLight = renderer_->CreateSplitLight(light);
            splitLights_[i] = SplitLight;
            
            // Though the near clip was previously clamped, use the real near clip value for the first split,
            // so that there are no unlit portions
            if (i)
                SplitLight->SetNearSplit(nearSplit);
            else
                SplitLight->SetNearSplit(camera_->GetNearClip());
            
            SplitLight->SetNearFadeRange(nearFadeRange);
            SplitLight->SetFarSplit(farSplit);
            
            // The final split will not fade
            if ((CreateExtraSplit) || (i < splits - 1))
                SplitLight->SetFarFadeRange(farFadeRange);
            
            // Create an extra unshadowed split if necessary
            if ((CreateExtraSplit) && (i == splits - 1))
            {
                Light* SplitLight = renderer_->CreateSplitLight(light);
                splitLights_[i + 1] = SplitLight;
                
                SplitLight->SetNearSplit(farSplit);
                SplitLight->SetNearFadeRange(farFadeRange);
                SplitLight->SetCastShadows(false);
            }
        }
        
        if (CreateExtraSplit)
            return i + 1;
        else
            return i;
    }
    
    if (type == LIGHT_POINT)
    {
        for (unsigned i = 0; i < MAX_CUBEMAP_FACES; ++i)
        {
            Light* SplitLight = renderer_->CreateSplitLight(light);
            Node* lightNode = SplitLight->GetNode();
            splitLights_[i] = SplitLight;
            
            SplitLight->SetLightType(LIGHT_SPLITPOINT);
            // When making a shadowed point light, align the splits along X, Y and Z axes regardless of light rotation
            lightNode->SetDirection(directions[i]);
            SplitLight->SetFov(90.0f);
            SplitLight->SetAspectRatio(1.0f);
        }
        
        return MAX_CUBEMAP_FACES;
    }
    
    // A spot light does not actually need splitting. However, we may be rendering several views,
    // and in some the light might be unshadowed, so better create an unique copy
    Light* SplitLight = renderer_->CreateSplitLight(light);
    splitLights_[0] = SplitLight;
    return 1;
}

Technique* View::GetTechnique(Drawable* drawable, Material*& material)
{
    if (!material)
        material = renderer_->GetDefaultMaterial();
    if (!material)
        return 0;
    
    float lodDistance = drawable->GetLodDistance();
    const std::vector<TechniqueEntry>& techniques = material->GetTechniques();
    if (!techniques.size())
        return 0;
    
    // Check for suitable technique. Techniques should be ordered like this:
    // Most distant & highest quality
    // Most distant & lowest quality
    // Second most distant & highest quality
    // ...
    for (unsigned i = 0; i < techniques.size(); ++i)
    {
        const TechniqueEntry& entry = techniques[i];
        Technique* technique = entry.technique_;
        if ((!technique) || ((!hasSM3_) && (technique->IsSM3())) || (materialQuality_ < entry.qualityLevel_))
            continue;
        if (lodDistance >= entry.lodDistance_)
            return technique;
    }
    
    // If no suitable technique found, fallback to the last
    return techniques[techniques.size() - 1].technique_;
}

void View::CheckMaterialForAuxView(Material* material)
{
    const std::vector<SharedPtr<Texture> >& textures = material->GetTextures();
    
    for (unsigned i = 0; i < textures.size(); ++i)
    {
        // Have to check cube & 2D textures separately
        Texture* texture = textures[i];
        if (texture)
        {
            if (texture->GetType() == Texture2D::GetTypeStatic())
            {
                Texture2D* tex2D = static_cast<Texture2D*>(texture);
                RenderSurface* target = tex2D->GetRenderSurface();
                if (target)
                {
                    const Viewport& viewport = target->GetViewport();
                    if ((viewport.scene_) && (viewport.camera_))
                        renderer_->AddView(target, viewport);
                }
            }
            else if (texture->GetType() == TextureCube::GetTypeStatic())
            {
                TextureCube* texCube = static_cast<TextureCube*>(texture);
                for (unsigned j = 0; j < MAX_CUBEMAP_FACES; ++j)
                {
                    RenderSurface* target = texCube->GetRenderSurface((CubeMapFace)j);
                    if (target)
                    {
                        const Viewport& viewport = target->GetViewport();
                        if ((viewport.scene_) && (viewport.camera_))
                            renderer_->AddView(target, viewport);
                    }
                }
            }
        }
    }
    
    // Set frame number so that we can early-out next time we come across this material on the same frame
    material->MarkForAuxView(frame_.frameNumber_);
}

void View::SortBatches()
{
    PROFILE(SortBatches);
    
    if (mode_ != RENDER_FORWARD)
    {
        gBufferQueue_.SortFrontToBack();
        noShadowLightQueue_.SortFrontToBack();
    }
    
    baseQueue_.SortFrontToBack();
    extraQueue_.SortFrontToBack();
    transparentQueue_.SortBackToFront();
    
    for (unsigned i = 0; i < lightQueues_.size(); ++i)
    {
        lightQueues_[i].shadowBatches_.SortFrontToBack();
        lightQueues_[i].litBatches_.SortFrontToBack();
    }
}

void View::PrepareInstancingBuffer()
{
    PROFILE(PrepareInstancingBuffer);
    
    unsigned totalInstances = 0;
    
    if (mode_ != RENDER_FORWARD)
        totalInstances += gBufferQueue_.GetNumInstances();
    totalInstances += baseQueue_.GetNumInstances();
    totalInstances += extraQueue_.GetNumInstances();
    
    for (unsigned i = 0; i < lightQueues_.size(); ++i)
    {
        totalInstances += lightQueues_[i].shadowBatches_.GetNumInstances();
        totalInstances += lightQueues_[i].litBatches_.GetNumInstances();
    }
    
    // If fail to set buffer size, fall back to per-group locking
    if ((totalInstances) && (renderer_->ResizeInstancingBuffer(totalInstances)))
    {
        unsigned freeIndex = 0;
        void* lockedData = renderer_->instancingBuffer_->Lock(0, totalInstances, LOCK_DISCARD);
        if (lockedData)
        {
            if (mode_ != RENDER_FORWARD)
                gBufferQueue_.SetTransforms(lockedData, freeIndex);
            baseQueue_.SetTransforms(lockedData, freeIndex);
            extraQueue_.SetTransforms(lockedData, freeIndex);
            
            for (unsigned i = 0; i < lightQueues_.size(); ++i)
            {
                lightQueues_[i].shadowBatches_.SetTransforms(lockedData, freeIndex);
                lightQueues_[i].litBatches_.SetTransforms(lockedData, freeIndex);
            }
            
            renderer_->instancingBuffer_->Unlock();
        }
    }
}

void View::SetShaderParameters()
{
    Time* time = GetSubsystem<Time>();
    
    float fogStart = zone_->GetFogStart();
    float fogEnd = zone_->GetFogEnd();
    float fogRange = Max(fogEnd - fogStart, M_EPSILON);
    float farClip = camera_->GetFarClip();
    float nearClip = camera_->GetNearClip();
    Vector4 fogParams(fogStart / farClip, fogEnd / farClip, 1.0f / (fogRange / farClip), 0.0f);
    Vector4 elapsedTime((time->GetTotalMSec() & 0x3fffff) / 1000.0f, 0.0f, 0.0f, 0.0f);
    
    graphics_->SetVertexShaderParameter(VSP_ELAPSEDTIME, elapsedTime);
    graphics_->SetPixelShaderParameter(PSP_AMBIENTCOLOR, zone_->GetAmbientColor());
    graphics_->SetPixelShaderParameter(PSP_ELAPSEDTIME, elapsedTime);
    graphics_->SetPixelShaderParameter(PSP_FOGCOLOR, zone_->GetFogColor());
    graphics_->SetPixelShaderParameter(PSP_FOGPARAMS, fogParams);
}

void View::DrawSplitLightToStencil(Camera& camera, Light* light, bool clear)
{
    graphics_->ClearTransformSources();
    Matrix4x3 view(camera.GetInverseWorldTransform());
    
    switch (light->GetLightType())
    {
    case LIGHT_SPLITPOINT:
        if (!clear)
        {
            Matrix4 projection(camera.GetProjection());
            const Matrix4x3& model = light->GetVolumeTransform(camera);
            float lightExtent = light->GetVolumeExtent();
            float lightViewDist = (light->GetWorldPosition() - camera.GetWorldPosition()).GetLengthFast();
            bool drawBackFaces = lightViewDist < (lightExtent + camera.GetNearClip());
            
            graphics_->SetAlphaTest(false);
            graphics_->SetColorWrite(false);
            graphics_->SetDepthWrite(false);
            graphics_->SetCullMode(drawBackFaces ? CULL_CW : CULL_CCW);
            graphics_->SetDepthTest(drawBackFaces ? CMP_GREATER : CMP_LESS);
            graphics_->SetShaders(renderer_->stencilVS_, renderer_->stencilPS_);
            graphics_->SetVertexShaderParameter(VSP_MODEL, model);
            graphics_->SetVertexShaderParameter(VSP_VIEWPROJ, projection * view);
            
            // Draw the faces to stencil which we should draw (where no light has not been rendered yet)
            graphics_->SetStencilTest(true, CMP_EQUAL, OP_INCR, OP_KEEP, OP_KEEP, 0);
            renderer_->spotLightGeometry_->Draw(graphics_);
            
            // Draw the other faces to stencil to mark where we should not draw ("frees up" the pixels for other faces)
            graphics_->SetCullMode(drawBackFaces ? CULL_CCW : CULL_CW);
            graphics_->SetStencilTest(true, CMP_EQUAL, OP_DECR, OP_KEEP, OP_KEEP, 1);
            renderer_->spotLightGeometry_->Draw(graphics_);
            
            // Now set stencil test for rendering the lit geometries (also marks the pixels so that they will not be used again)
            graphics_->SetStencilTest(true, CMP_EQUAL, OP_INCR, OP_KEEP, OP_KEEP, 1);
            graphics_->SetColorWrite(true);
        }
        else
        {
            // Clear stencil with a scissored clear operation
            OptimizeLightByScissor(light->GetOriginalLight());
            graphics_->Clear(CLEAR_STENCIL);
            graphics_->SetScissorTest(false);
            graphics_->SetStencilTest(false);
        }
        break;
        
    case LIGHT_DIRECTIONAL:
        // If light encompasses whole frustum, no drawing to frustum necessary
        if ((light->GetNearSplit() <= camera.GetNearClip()) && (light->GetFarSplit() >= camera.GetFarClip()))
            return;
        else
        {
            if (!clear)
            {
                // Get projection without jitter offset to ensure the whole screen is filled
                Matrix4 projection(camera.GetProjection(false));
                Matrix4x3 nearTransform(light->GetDirLightTransform(camera, true));
                Matrix4x3 farTransform(light->GetDirLightTransform(camera, false));
                
                graphics_->SetAlphaTest(false);
                graphics_->SetColorWrite(false);
                graphics_->SetDepthWrite(false);
                graphics_->SetCullMode(CULL_NONE);
                
                // If the split begins at the near plane (first split), draw at split far plane
                if (light->GetNearSplit() <= camera.GetNearClip())
                {
                    graphics_->SetDepthTest(CMP_GREATEREQUAL);
                    graphics_->SetShaders(renderer_->stencilVS_, renderer_->stencilPS_);
                    graphics_->SetVertexShaderParameter(VSP_MODEL, farTransform);
                    graphics_->SetVertexShaderParameter(VSP_VIEWPROJ, projection);
                    graphics_->SetStencilTest(true, CMP_ALWAYS, OP_REF, OP_ZERO, OP_ZERO, 1);
                }
                // Otherwise draw at split near plane
                else
                {
                    graphics_->SetDepthTest(CMP_LESSEQUAL);
                    graphics_->SetShaders(renderer_->stencilVS_, renderer_->stencilPS_);
                    graphics_->SetVertexShaderParameter(VSP_MODEL, nearTransform);
                    graphics_->SetVertexShaderParameter(VSP_VIEWPROJ, projection);
                    graphics_->SetStencilTest(true, CMP_ALWAYS, OP_REF, OP_ZERO, OP_ZERO, 1);
                }
                
                renderer_->dirLightGeometry_->Draw(graphics_);
                graphics_->SetColorWrite(true);
                graphics_->SetStencilTest(true, CMP_EQUAL, OP_KEEP, OP_KEEP, OP_KEEP, 1);
            }
            else
            {
                // Clear the whole stencil
                graphics_->SetScissorTest(false);
                graphics_->Clear(CLEAR_STENCIL);
                graphics_->SetStencilTest(false);
            }
        }
        break;
    }
}

void View::RenderBatchQueue(const BatchQueue& queue, bool useScissor, bool useLightBuffer)
{
    Texture2D* diffBuffer = 0;
    VertexBuffer* instancingBuffer = 0;
    if (useLightBuffer)
        diffBuffer = graphics_->GetDiffBuffer();
    if (renderer_->GetDynamicInstancing())
        instancingBuffer = renderer_->instancingBuffer_;
    
    graphics_->SetScissorTest(false);
    graphics_->SetStencilTest(false);
    
    // Priority instanced
    for (std::map<BatchGroupKey, BatchGroup>::const_iterator i = queue.priorityBatchGroups_.begin(); i !=
        queue.priorityBatchGroups_.end(); ++i)
    {
        const BatchGroup& group = i->second;
        if ((useLightBuffer) && (!group.light_))
            graphics_->SetTexture(TU_LIGHTBUFFER, diffBuffer);
        group.Draw(graphics_, instancingBuffer);
    }
    // Priority non-instanced
    for (std::vector<Batch*>::const_iterator i = queue.sortedPriorityBatches_.begin(); i != queue.sortedPriorityBatches_.end(); ++i)
    {
        Batch* batch = *i;
        if ((useLightBuffer) && (!batch->light_))
            graphics_->SetTexture(TU_LIGHTBUFFER, diffBuffer);
        batch->Draw(graphics_);
    }
    
    // Non-priority instanced
    for (std::map<BatchGroupKey, BatchGroup>::const_iterator i = queue.batchGroups_.begin(); i !=
        queue.batchGroups_.end(); ++i)
    {
        const BatchGroup& group = i->second;
        if ((useScissor) && (group.light_))
            OptimizeLightByScissor(group.light_);
        else
            graphics_->SetScissorTest(false);
        if ((useLightBuffer) && (!group.light_))
            graphics_->SetTexture(TU_LIGHTBUFFER, diffBuffer);
        group.Draw(graphics_, instancingBuffer);
    }
    // Non-priority non-instanced
    for (std::vector<Batch*>::const_iterator i = queue.sortedBatches_.begin(); i != queue.sortedBatches_.end(); ++i)
    {
        Batch* batch = *i;
        // For the transparent queue, both priority and non-priority batches are copied here, so check the flag
        if ((useScissor) && (batch->light_) && (!batch->hasPriority_))
            OptimizeLightByScissor(batch->light_);
        else
            graphics_->SetScissorTest(false);
        if ((useLightBuffer) && (!batch->light_))
            graphics_->SetTexture(TU_LIGHTBUFFER, diffBuffer);
        batch->Draw(graphics_);
    }
}

void View::RenderForwardLightBatchQueue(const BatchQueue& queue, Light* light)
{
    VertexBuffer* instancingBuffer = 0;
    if (renderer_->GetDynamicInstancing())
        instancingBuffer = renderer_->instancingBuffer_;
    
    graphics_->SetScissorTest(false);
    graphics_->SetStencilTest(false);
    
    // Priority instanced
    for (std::map<BatchGroupKey, BatchGroup>::const_iterator i = queue.priorityBatchGroups_.begin(); i !=
        queue.priorityBatchGroups_.end(); ++i)
    {
        const BatchGroup& group = i->second;
        group.Draw(graphics_, instancingBuffer);
    }
    // Priority non-instanced
    for (std::vector<Batch*>::const_iterator i = queue.sortedPriorityBatches_.begin(); i != queue.sortedPriorityBatches_.end(); ++i)
    {
        Batch* batch = *i;
        batch->Draw(graphics_);
    }
    
    // All base passes have been drawn. Optimize at this point by both scissor and stencil
    if (light)
    {
        OptimizeLightByScissor(light);
        LightType type = light->GetLightType();
        if ((type == LIGHT_SPLITPOINT) || (type == LIGHT_DIRECTIONAL))
            DrawSplitLightToStencil(*camera_, light);
    }
    
    // Non-priority instanced
    for (std::map<BatchGroupKey, BatchGroup>::const_iterator i = queue.batchGroups_.begin(); i !=
        queue.batchGroups_.end(); ++i)
    {
        const BatchGroup& group = i->second;
        group.Draw(graphics_, instancingBuffer);
    }
    // Non-priority non-instanced
    for (std::vector<Batch*>::const_iterator i = queue.sortedBatches_.begin(); i != queue.sortedBatches_.end(); ++i)
    {
        Batch* batch = *i;
        batch->Draw(graphics_);
    }
}

void View::RenderShadowMap(const LightBatchQueue& queue)
{
    PROFILE(RenderShadowMap);
    
    Texture2D* shadowMap = queue.light_->GetShadowMap();
    
    graphics_->ClearLastParameterSources();
    graphics_->SetColorWrite(false);
    graphics_->SetStencilTest(false);
    graphics_->SetTexture(TU_SHADOWMAP, 0);
    graphics_->SetRenderTarget(0, shadowMap->GetRenderSurface()->GetLinkedRenderTarget());
    graphics_->SetDepthStencil(shadowMap);
    graphics_->Clear(CLEAR_DEPTH);
    
    // Set shadow depth bias
    BiasParameters parameters = queue.light_->GetShadowBias();
    graphics_->SetDepthBias(parameters.constantBias_, parameters.slopeScaledBias_);
    
    // Set a scissor rectangle to match possible shadow map size reduction by out-zooming
    // However, do not do this for point lights
    if (queue.light_->GetLightType() != LIGHT_SPLITPOINT)
    {
        float zoom = Min(queue.light_->GetShadowCamera()->GetZoom(),
            (float)(shadowMap->GetWidth() - 2) / (float)shadowMap->GetWidth());
        Rect zoorect_(Vector2(-1.0f, -1.0f) * zoom, Vector2(1.0f, 1.0f) * zoom);
        graphics_->SetScissorTest(true, zoorect_, false);
    }
    else
        graphics_->SetScissorTest(false);
    
    // Draw instanced and non-instanced shadow casters
    RenderBatchQueue(queue.shadowBatches_);
    
    graphics_->SetColorWrite(true);
    graphics_->SetDepthBias(0.0f, 0.0f);
}
