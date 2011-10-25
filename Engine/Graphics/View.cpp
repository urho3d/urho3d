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
#include "Profiler.h"
#include "Scene.h"
#include "ShaderVariation.h"
#include "Sort.h"
#include "Technique.h"
#include "Texture2D.h"
#include "TextureCube.h"
#include "VertexBuffer.h"
#include "View.h"
#include "Zone.h"

#include "DebugNew.h"

static const Vector3 directions[] =
{
    Vector3(1.0f, 0.0f, 0.0f),
    Vector3(-1.0f, 0.0f, 0.0f),
    Vector3(0.0f, 1.0f, 0.0f),
    Vector3(0.0f, -1.0f, 0.0f),
    Vector3(0.0f, 0.0f, 1.0f),
    Vector3(0.0f, 0.0f, -1.0f)
};

OBJECTTYPESTATIC(View);

View::View(Context* context) :
    Object(context),
    graphics_(GetSubsystem<Graphics>()),
    renderer_(GetSubsystem<Renderer>()),
    octree_(0),
    camera_(0),
    cameraZone_(0),
    farClipZone_(0),
    renderTarget_(0),
    depthStencil_(0)
{
    frame_.camera_ = 0;
}

View::~View()
{
}

bool View::Define(RenderSurface* renderTarget, const Viewport& viewport)
{
    if (!viewport.scene_ || !viewport.camera_)
        return false;
    
    // If scene is loading asynchronously, it is incomplete and should not be rendered
    if (viewport.scene_->IsAsyncLoading())
        return false;
    
    Octree* octree = viewport.scene_->GetComponent<Octree>();
    if (!octree)
        return false;
    
    octree_ = octree;
    camera_ = viewport.camera_;
    renderTarget_ = renderTarget;
    
    if (!renderTarget)
        depthStencil_ = 0;
    else
        depthStencil_ = renderTarget->GetLinkedDepthBuffer();
    
    // Validate the rect and calculate size. If zero rect, use whole render target size
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
    if (viewOverrideFlags & VO_LOW_MATERIAL_QUALITY)
        materialQuality_ = QUALITY_LOW;
    if (viewOverrideFlags & VO_DISABLE_SHADOWS)
        drawShadows_ = false;
    if (viewOverrideFlags & VO_DISABLE_OCCLUSION)
        maxOccluderTriangles_ = 0;
    
    return true;
}

void View::Update(const FrameInfo& frame)
{
    if (!camera_ || !octree_)
        return;
    
    frame_.camera_ = camera_;
    frame_.timeStep_ = frame.timeStep_;
    frame_.frameNumber_ = frame.frameNumber_;
    frame_.viewSize_ = IntVector2(width_, height_);
    
    shadowFrame_ = frame_;
    
    // Clear old light scissor cache, geometry, light, occluder & batch lists
    lightScissorCache_.Clear();
    geometries_.Clear();
    geometryDepthBounds_.Clear();
    lights_.Clear();
    occluders_.Clear();
    shadowOccluders_.Clear();
    baseQueue_.Clear();
    preAlphaQueue_.Clear();
    alphaQueue_.Clear();
    postAlphaQueue_.Clear();
    lightQueues_.Clear();
    
    // Do not update if camera projection is illegal
    // (there is a possibility of crash if occlusion is used and it can not clip properly)
    if (!camera_->IsProjectionValid())
        return;
    
    // Set automatic aspect ratio if required
    if (camera_->GetAutoAspectRatio())
        camera_->SetAspectRatio((float)frame_.viewSize_.x_ / (float)frame_.viewSize_.y_);
    
    // Cache the camera frustum to avoid recalculating it constantly
    frustum_ = camera_->GetFrustum();
    
    // Reset shadow map allocations; they can be reused between views as each is rendered completely at a time
    renderer_->ResetShadowMapAllocations();
    
    GetDrawables();
    GetBatches();
}

void View::Render()
{
    if (!octree_ || !camera_)
        return;
    
    // Forget parameter sources from the previous view
    graphics_->ClearParameterSources();
    
    // If stream offset is supported, write all instance transforms to a single large buffer
    // Else we must lock the instance buffer for each batch group
    if (renderer_->GetDynamicInstancing() && graphics_->GetStreamOffsetSupport())
        PrepareInstancingBuffer();
    
    // It is possible, though not recommended, that the same camera is used for multiple main views. Set automatic aspect ratio
    // again to ensure correct projection will be used
    if (camera_->GetAutoAspectRatio())
        camera_->SetAspectRatio((float)(screenRect_.right_ - screenRect_.left_) / (float)(screenRect_.bottom_ - screenRect_.top_));
    
    graphics_->SetColorWrite(true);
    graphics_->SetFillMode(FILL_SOLID);
    
    // Bind the face selection and indirection cube maps for point light shadows
    graphics_->SetTexture(TU_FACESELECT, renderer_->GetFaceSelectCubeMap());
    graphics_->SetTexture(TU_INDIRECTION, renderer_->GetIndirectionCubeMap());
    
    // Reset the light optimization stencil reference value
    lightStencilValue_ = 1;
    
    // Render
    RenderBatches();
    
    graphics_->SetScissorTest(false);
    graphics_->SetStencilTest(false);
    graphics_->ResetStreamFrequencies();
    
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
    cameraZone_ = 0;
    farClipZone_ = 0;
    frame_.camera_ = 0;
}

void View::GetDrawables()
{
    int highestZonePriority = M_MIN_INT;
    
    {
        PROFILE(GetZones);
        
        // Get default zone first in case we do not have zones defined
        Zone* defaultZone = renderer_->GetDefaultZone();
        cameraZone_ = farClipZone_ = defaultZone;
        
        FrustumOctreeQuery query(reinterpret_cast<PODVector<Drawable*>&>(zones_), frustum_, DRAWABLE_ZONE);
        octree_->GetDrawables(query);
        
        // Find the visible zones, and the zone the camera is in. Determine also the highest zone priority to aid in seeing
        // whether a zone query result for a drawable is conclusive
        int bestPriority = M_MIN_INT;
        Vector3 cameraPos = camera_->GetWorldPosition();
        
        for (PODVector<Zone*>::Iterator i = zones_.Begin(); i != zones_.End(); ++i)
        {
            int priority = (*i)->GetPriority();
            if (priority > highestZonePriority)
                highestZonePriority = priority;
            if ((*i)->IsInside(cameraPos) && priority > bestPriority)
            {
                cameraZone_ = *i;
                bestPriority = priority;
            }
        }
        
        // Determine the zone at far clip distance. If not found, or camera zone has override mode, use camera zone
        cameraZoneOverride_ = cameraZone_->GetOverride();
        if (!cameraZoneOverride_)
        {
            Vector3 farClipPos = cameraPos + camera_->GetNode()->GetWorldDirection() * Vector3(0, 0, camera_->GetFarClip());
            bestPriority = M_MIN_INT;
            
            for (PODVector<Zone*>::Iterator i = zones_.Begin(); i != zones_.End(); ++i)
            {
                int priority = (*i)->GetPriority();
                if ((*i)->IsInside(farClipPos) && priority > bestPriority)
                {
                    farClipZone_ = *i;
                    bestPriority = priority;
                }
            }
        }
        if (farClipZone_ == defaultZone)
            farClipZone_ = cameraZone_;
    }
    
    {
        PROFILE(GetDrawables);
        
        // If occlusion in use, get & render the occluders, then build the depth buffer hierarchy
        OcclusionBuffer* buffer = 0;
        
        if (maxOccluderTriangles_ > 0)
        {
            FrustumOctreeQuery query(occluders_, frustum_, DRAWABLE_GEOMETRY, camera_->GetViewMask(), true, false);
            octree_->GetDrawables(query);
            UpdateOccluders(occluders_, camera_);
            
            if (occluders_.Size())
            {
                buffer = renderer_->GetOrCreateOcclusionBuffer(camera_, maxOccluderTriangles_);
                DrawOccluders(buffer, occluders_);
                buffer->BuildDepthHierarchy();
            }
        }
        
        if (!buffer)
        {
            // Get geometries & lights without occlusion
            FrustumOctreeQuery query(tempDrawables_, frustum_, DRAWABLE_GEOMETRY | DRAWABLE_LIGHT);
            octree_->GetDrawables(query);
        }
        else
        {
            // Get geometries & lights using occlusion
            OccludedFrustumOctreeQuery query(tempDrawables_, frustum_, buffer, DRAWABLE_GEOMETRY | DRAWABLE_LIGHT,
                camera_->GetViewMask());
            octree_->GetDrawables(query);
        }
        
        // Add unculled geometries & lights
        octree_->GetUnculledDrawables(tempDrawables_, DRAWABLE_GEOMETRY | DRAWABLE_LIGHT);
        
        // Sort into geometries & lights, and build visible scene bounding boxes in world and view space
        sceneBox_.min_ = sceneBox_.max_ = Vector3::ZERO;
        sceneBox_.defined_ = false;
        sceneViewBox_.min_ = sceneViewBox_.max_ = Vector3::ZERO;
        sceneViewBox_.defined_ = false;
        Matrix3x4 view(camera_->GetInverseWorldTransform());
        
        for (unsigned i = 0; i < tempDrawables_.Size(); ++i)
        {
            Drawable* drawable = tempDrawables_[i];
            drawable->UpdateDistance(frame_);
            
            // If draw distance non-zero, check it
            float maxDistance = drawable->GetDrawDistance();
            if (maxDistance > 0.0f && drawable->GetDistance() > maxDistance)
                continue;
            
            unsigned flags = drawable->GetDrawableFlags();
            if (flags & DRAWABLE_GEOMETRY)
            {
                // Find new zone for the drawable if necessary
                if (!drawable->GetZone() && !cameraZoneOverride_)
                    FindZone(drawable, highestZonePriority);
                
                drawable->ClearLights();
                drawable->MarkInView(frame_);
                drawable->UpdateGeometry(frame_);
                
                // Expand the scene bounding boxes. However, do not take "infinite" objects such as the skybox into account,
                // as the bounding boxes are also used for shadow focusing
                const BoundingBox& geomBox = drawable->GetWorldBoundingBox();
                BoundingBox geomViewBox = geomBox.Transformed(view);
                if (geomBox.Size().LengthFast() < M_LARGE_VALUE)
                {
                    sceneBox_.Merge(geomBox);
                    sceneViewBox_.Merge(geomViewBox);
                }
                
                // Store depth info for split directional light queries
                GeometryDepthBounds bounds;
                bounds.min_ = geomViewBox.min_.z_;
                bounds.max_ = geomViewBox.max_.z_;
                
                geometryDepthBounds_.Push(bounds);
                geometries_.Push(drawable);
            }
            else if (flags & DRAWABLE_LIGHT)
            {
                Light* light = static_cast<Light*>(drawable);
                light->MarkInView(frame_);
                lights_.Push(light);
            }
        }
        
        // Sort the lights to brightest/closest first
        for (unsigned i = 0; i < lights_.Size(); ++i)
        {
            Light* light = lights_[i];
            light->SetIntensitySortValue(camera_->GetDistance(light->GetWorldPosition()));
        }
        
        Sort(lights_.Begin(), lights_.End(), CompareDrawables);
    }
}

void View::GetBatches()
{
    maxLightsDrawables_.Clear();
    lightQueueIndex_.Clear();
    
    bool fallback = graphics_->GetFallback();
    
    // Go through lights
    {
        PROFILE_MULTIPLE(GetLightBatches, lights_.Size());
        
        // Preallocate enough light queues so that we can store pointers to them without having to worry about the
        // vector reallocating itself
        lightQueues_.Resize(lights_.Size());
        
        unsigned lightQueueCount = 0;
        for (unsigned i = 0; i < lights_.Size(); ++i)
        {
            Light* light = lights_[i];
            unsigned shadowSplits = ProcessLight(light);
            if (litGeometries_.Empty())
                continue;
            
            // Initialize light queue. Store pointer-to-index mapping so that the queue can be found later
            LightBatchQueue& lightQueue = lightQueues_[lightQueueCount];
            lightQueueIndex_[light] = lightQueueCount;
            lightQueue.light_ = light;
            lightQueue.litBatches_.Clear();
            
            // Allocate shadow map now
            lightQueue.shadowMap_ = 0;
            if (shadowSplits > 0)
            {
                lightQueue.shadowMap_ = renderer_->GetShadowMap(light, camera_, width_, height_);
                // If did not manage to get a shadow map, convert the light to unshadowed
                if (!lightQueue.shadowMap_)
                    shadowSplits = 0;
            }
            
            // Setup shadow batch queues
            lightQueue.shadowSplits_.Resize(shadowSplits);
            for (unsigned j = 0; j < shadowSplits; ++j)
            {
                ShadowBatchQueue& shadowQueue = lightQueue.shadowSplits_[j];
                Camera* shadowCamera = shadowCameras_[j];
                shadowQueue.shadowCamera_ = shadowCameras_[j];
                shadowQueue.nearSplit_ = shadowNearSplits_[j];
                shadowQueue.farSplit_ = shadowFarSplits_[j];
                shadowFrame_.camera_ = shadowCamera;
                
                // Setup the shadow split viewport and finalize shadow camera parameters
                shadowQueue.shadowViewport_ = GetShadowMapViewport(light, j, lightQueue.shadowMap_);
                FinalizeShadowCamera(shadowCamera, light, shadowQueue.shadowViewport_, shadowCasterBox_[j]);
                
                // Loop through shadow casters
                for (unsigned k = 0; k < shadowCasters_[j].Size(); ++k)
                {
                    Drawable* drawable = shadowCasters_[j][k];
                    unsigned numBatches = drawable->GetNumBatches();
                    
                    for (unsigned l = 0; l < numBatches; ++l)
                    {
                        Batch shadowBatch;
                        drawable->GetBatch(shadowBatch, shadowFrame_, l);
                        
                        Technique* tech = GetTechnique(drawable, shadowBatch.material_);
                        if (!shadowBatch.geometry_ || !tech)
                            continue;
                        
                        Pass* pass = tech->GetPass(PASS_SHADOW);
                        // Skip if material has no shadow pass
                        if (!pass)
                            continue;
                        
                        // Fill the rest of the batch
                        shadowBatch.camera_ = shadowCamera;
                        shadowBatch.lightQueue_ = &lightQueue;
                        
                        FinalizeBatch(shadowBatch, tech, pass);
                        shadowQueue.shadowBatches_.AddBatch(shadowBatch);
                    }
                }
            }
            
            // Loop through lit geometries
            for (unsigned j = 0; j < litGeometries_.Size(); ++j)
            {
                Drawable* drawable = litGeometries_[j];
                drawable->AddLight(light);
                
                // If drawable limits maximum lights, only record the light, and check maximum count / build batches later
                if (!drawable->GetMaxLights())
                    GetLitBatches(drawable, lightQueue);
                else
                    maxLightsDrawables_.Insert(drawable);
            }
            
            ++lightQueueCount;
        }
        
        // Resize the light queue vector now that final size is known
        lightQueues_.Resize(lightQueueCount);
    }
    
    // Process drawables with limited light count
    if (maxLightsDrawables_.Size())
    {
        PROFILE(GetMaxLightsBatches);
        
        for (HashSet<Drawable*>::Iterator i = maxLightsDrawables_.Begin(); i != maxLightsDrawables_.End(); ++i)
        {
            Drawable* drawable = *i;
            drawable->LimitLights();
            const PODVector<Light*>& lights = drawable->GetLights();
            
            for (unsigned i = 0; i < lights.Size(); ++i)
            {
                Light* light = lights[i];
                // Find the correct light queue again
                Map<Light*, unsigned>::Iterator j = lightQueueIndex_.Find(light);
                if (j != lightQueueIndex_.End())
                    GetLitBatches(drawable, lightQueues_[j->second_]);
            }
        }
    }
    
    // Go through geometries for base pass batches
    {
        PROFILE(GetBaseBatches);
        for (unsigned i = 0; i < geometries_.Size(); ++i)
        {
            Drawable* drawable = geometries_[i];
            unsigned numBatches = drawable->GetNumBatches();
            
            for (unsigned j = 0; j < numBatches; ++j)
            {
                Batch baseBatch;
                drawable->GetBatch(baseBatch, frame_, j);
                
                Technique* tech = GetTechnique(drawable, baseBatch.material_);
                if (!baseBatch.geometry_ || !tech)
                    continue;
                
                // Check here if the material technique refers to a render target texture with camera(s) attached
                // Only check this for the main view (null rendertarget)
                if (!renderTarget_ && baseBatch.material_ && baseBatch.material_->GetAuxViewFrameNumber() != frame_.frameNumber_)
                    CheckMaterialForAuxView(baseBatch.material_);
                
                // If object already has a lit base pass, can skip the unlit base pass
                if (drawable->HasBasePass(j))
                    continue;
                
                // Fill the rest of the batch
                baseBatch.camera_ = camera_;
                baseBatch.zone_ = GetZone(drawable);
                baseBatch.isBase_ = true;
                
                Pass* pass = 0;
                
                // Check for unlit base pass
                pass = tech->GetPass(PASS_BASE);
                if (pass)
                {
                    if (pass->GetBlendMode() == BLEND_REPLACE)
                    {
                        FinalizeBatch(baseBatch, tech, pass);
                        baseQueue_.AddBatch(baseBatch);
                    }
                    else
                    {
                        // Transparent batches can not be instanced
                        FinalizeBatch(baseBatch, tech, pass, false);
                        alphaQueue_.AddBatch(baseBatch);
                    }
                    continue;
                }
                
                // If no base pass, finally check for pre-alpha / post-alpha custom passes
                pass = tech->GetPass(PASS_PREALPHA);
                if (pass)
                {
                    FinalizeBatch(baseBatch, tech, pass);
                    preAlphaQueue_.AddBatch(baseBatch);
                    continue;
                }
                
                pass = tech->GetPass(PASS_POSTALPHA);
                if (pass)
                {
                    // Post-alpha pass is treated similarly as alpha, and is not instanced
                    FinalizeBatch(baseBatch, tech, pass, false);
                    postAlphaQueue_.AddBatch(baseBatch);
                    continue;
                }
            }
        }
    }
    
    // All batches have been collected. Sort them now
    SortBatches();
}

void View::GetLitBatches(Drawable* drawable, LightBatchQueue& lightQueue)
{
    Light* light = lightQueue.light_;
    Light* firstLight = drawable->GetFirstLight();
    
    // Shadows on transparencies can only be rendered if shadow maps are not reused
    bool allowTransparentShadows = !renderer_->GetReuseShadowMaps();
    unsigned numBatches = drawable->GetNumBatches();
    
    for (unsigned i = 0; i < numBatches; ++i)
    {
        Batch litBatch;
        drawable->GetBatch(litBatch, frame_, i);
        
        Technique* tech = GetTechnique(drawable, litBatch.material_);
        if (!litBatch.geometry_ || !tech)
            continue;
        
        Pass* pass = 0;
        
        // Check for lit base pass. Because it uses the replace blend mode, it must be ensured to be the first light
        if (light == firstLight && !drawable->HasBasePass(i))
        {
            pass = tech->GetPass(PASS_LITBASE);
            if (pass)
            {
                litBatch.isBase_ = true;
                drawable->SetBasePass(i);
            }
        }
        
        // If no lit base pass, get ordinary light pass
        if (!pass)
            pass = tech->GetPass(PASS_LIGHT);
        // Skip if material does not receive light at all
        if (!pass)
            continue;
        
        // Fill the rest of the batch
        litBatch.camera_ = camera_;
        litBatch.lightQueue_ = &lightQueue;
        litBatch.zone_ = GetZone(drawable);
        
        // Check from the ambient pass whether the object is opaque or transparent
        Pass* ambientPass = tech->GetPass(PASS_BASE);
        if (!ambientPass || ambientPass->GetBlendMode() == BLEND_REPLACE)
        {
            FinalizeBatch(litBatch, tech, pass);
            lightQueue.litBatches_.AddBatch(litBatch);
        }
        else
        {
            // Transparent batches can not be instanced
            FinalizeBatch(litBatch, tech, pass, false, allowTransparentShadows);
            alphaQueue_.AddBatch(litBatch);
        }
    }
}

void View::RenderBatches()
{
    // If not reusing shadowmaps, render all of them first
    if (!renderer_->GetReuseShadowMaps() && renderer_->GetDrawShadows() && !lightQueues_.Empty())
    {
        PROFILE(RenderShadowMaps);
        
        for (unsigned i = 0; i < lightQueues_.Size(); ++i)
        {
            LightBatchQueue& queue = lightQueues_[i];
            if (queue.shadowMap_)
                RenderShadowMap(queue);
        }
    }
    
    graphics_->SetRenderTarget(0, renderTarget_);
    graphics_->SetDepthStencil(depthStencil_);
    graphics_->SetViewport(screenRect_);
    graphics_->Clear(CLEAR_COLOR | CLEAR_DEPTH | CLEAR_STENCIL, farClipZone_->GetFogColor());
    
    if (!baseQueue_.IsEmpty())
    {
        // Render opaque object unlit base pass
        PROFILE(RenderBase);
        
        RenderBatchQueue(baseQueue_);
    }
    
    if (!lightQueues_.Empty())
    {
        // Render shadow maps + opaque objects' shadowed additive lighting
        PROFILE(RenderLights);
        
        for (unsigned i = 0; i < lightQueues_.Size(); ++i)
        {
            LightBatchQueue& queue = lightQueues_[i];
            
            // If reusing shadowmaps, render each of them before the lit batches
            if (renderer_->GetReuseShadowMaps() && queue.shadowMap_)
            {
                RenderShadowMap(queue);
                graphics_->SetRenderTarget(0, renderTarget_);
                graphics_->SetDepthStencil(depthStencil_);
                graphics_->SetViewport(screenRect_);
            }
            
            RenderLightBatchQueue(queue.litBatches_, queue.light_);
        }
    }
    
    graphics_->SetScissorTest(false);
    graphics_->SetStencilTest(false);
    graphics_->SetRenderTarget(0, renderTarget_);
    graphics_->SetDepthStencil(depthStencil_);
    graphics_->SetViewport(screenRect_);
    
    if (!preAlphaQueue_.IsEmpty())
    {
        // Render pre-alpha custom pass
        PROFILE(RenderPreAlpha);
        
        RenderBatchQueue(preAlphaQueue_);
    }
    
    if (!alphaQueue_.IsEmpty())
    {
        // Render transparent objects (both base passes & additive lighting)
        PROFILE(RenderAlpha);
        
        RenderBatchQueue(alphaQueue_, true);
    }
    
    if (!postAlphaQueue_.IsEmpty())
    {
        // Render pre-alpha custom pass
        PROFILE(RenderPostAlpha);
        
        RenderBatchQueue(postAlphaQueue_);
    }
}

void View::UpdateOccluders(PODVector<Drawable*>& occluders, Camera* camera)
{
    float occluderSizeThreshold_ = renderer_->GetOccluderSizeThreshold();
    float halfViewSize = camera->GetHalfViewSize();
    float invOrthoSize = 1.0f / camera->GetOrthoSize();
    Vector3 cameraPos = camera->GetWorldPosition();
    
    for (unsigned i = 0; i < occluders.Size(); ++i)
    {
        Drawable* occluder = occluders[i];
        occluder->UpdateDistance(frame_);
        bool erase = false;
        
        // Check occluder's draw distance (in main camera view)
        float maxDistance = occluder->GetDrawDistance();
        if (maxDistance > 0.0f && occluder->GetDistance() > maxDistance)
            erase = true;
        
        // Check that occluder is big enough on the screen
        const BoundingBox& box = occluder->GetWorldBoundingBox();
        float diagonal = (box.max_ - box.min_).LengthFast();
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
                occluder->GetBatch(tempBatch, frame_, j);
                if (tempBatch.geometry_)
                    totalTriangles += tempBatch.geometry_->GetIndexCount() / 3;
            }
            
            // Store amount of triangles divided by screen size as a sorting key
            // (best occluders are big and have few triangles)
            occluder->SetSortValue((float)totalTriangles / compare);
        }
        else
        {
            occluders.Erase(occluders.Begin() + i);
            --i;
        }
    }
    
    // Sort occluders so that if triangle budget is exceeded, best occluders have been drawn
    if (occluders.Size())
        Sort(occluders.Begin(), occluders.End(), CompareDrawables);
}

void View::DrawOccluders(OcclusionBuffer* buffer, const PODVector<Drawable*>& occluders)
{
    for (unsigned i = 0; i < occluders.Size(); ++i)
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
    // Check if light should be shadowed
    bool isShadowed = drawShadows_ && light->GetCastShadows() && light->GetShadowIntensity() < 1.0f;
    unsigned shadowSplits = 0;
    // If shadow distance non-zero, check it
    if (isShadowed && light->GetShadowDistance() > 0.0f && light->GetDistance() > light->GetShadowDistance())
        isShadowed = false;
    
    LightType type = light->GetLightType();
    
    // Get lit geometries. They must match the light mask and be inside the main camera frustum to be considered
    litGeometries_.Clear();
    
    switch (type)
    {
    case LIGHT_DIRECTIONAL:
        for (unsigned i = 0; i < geometries_.Size(); ++i)
        {
            if (GetLightMask(geometries_[i]) & light->GetLightMask())
                litGeometries_.Push(geometries_[i]);
        }
        break;
        
    case LIGHT_SPOT:
        {
            FrustumOctreeQuery query(tempDrawables_, light->GetFrustum(), DRAWABLE_GEOMETRY, camera_->GetViewMask());
            octree_->GetDrawables(query);
            for (unsigned i = 0; i < tempDrawables_.Size(); ++i)
            {
                if (tempDrawables_[i]->IsInView(frame_) && (GetLightMask(tempDrawables_[i]) & light->GetLightMask()))
                    litGeometries_.Push(tempDrawables_[i]);
            }
        }
        break;
        
    case LIGHT_POINT:
        {
            SphereOctreeQuery query(tempDrawables_, Sphere(light->GetWorldPosition(), light->GetRange()), DRAWABLE_GEOMETRY,
                camera_->GetViewMask());
            octree_->GetDrawables(query);
            for (unsigned i = 0; i < tempDrawables_.Size(); ++i)
            {
                if (tempDrawables_[i]->IsInView(frame_) && (GetLightMask(tempDrawables_[i]) & light->GetLightMask()))
                    litGeometries_.Push(tempDrawables_[i]);
            }
        }
        break;
    }
    
    // If no lit geometries or not shadowed, no need to process shadow cameras
    if (litGeometries_.Empty() || !isShadowed)
        return 0;
    
    // Determine number of shadow cameras and setup their initial positions
    shadowSplits = SetupShadowCameras(light);
    
    // For a shadowed directional light, get occluders once using the whole (non-split) light frustum
    bool useOcclusion = false;
    OcclusionBuffer* buffer = 0;
    
    if (maxOccluderTriangles_ > 0 && isShadowed && light->GetLightType() == LIGHT_DIRECTIONAL)
    {
        // This shadow camera is never used for actually querying shadow casters, just occluders
        Camera* shadowCamera = renderer_->CreateShadowCamera();
        SetupDirLightShadowCamera(shadowCamera, light, 0.0f, Min(light->GetShadowCascade().GetShadowRange(), camera_->GetFarClip()),
            true);
        
        // Get occluders, which must be shadow-casting themselves
        FrustumOctreeQuery query(shadowOccluders_, shadowCamera->GetFrustum(), DRAWABLE_GEOMETRY, camera_->GetViewMask(),
            true, true);
        octree_->GetDrawables(query);
        
        UpdateOccluders(shadowOccluders_, shadowCamera);
        
        if (shadowOccluders_.Size())
        {
            // Shadow viewport is rectangular and consumes more CPU fillrate, so halve size
            buffer = renderer_->GetOrCreateOcclusionBuffer(shadowCamera, maxOccluderTriangles_, true);
            
            DrawOccluders(buffer, shadowOccluders_);
            buffer->BuildDepthHierarchy();
            useOcclusion = true;
        }
    }
    
    // Process each split for shadow casters
    bool hasShadowCasters = false;
    for (unsigned i = 0; i < shadowSplits; ++i)
    {
        shadowCasters_[i].Clear();
        shadowCasterBox_[i].defined_ = false;
        Camera* shadowCamera = shadowCameras_[i];
        Frustum shadowCameraFrustum = shadowCamera->GetFrustum();
        
        // For point light check that the face is visible: if not, can skip the split
        if (type == LIGHT_POINT)
        {
            BoundingBox shadowCameraBox(shadowCameraFrustum);
            if (frustum_.IsInsideFast(shadowCameraBox) == OUTSIDE)
                continue;
        }
        
        // For directional light check that the split is inside the visible scene: if not, can skip the split
        if (type == LIGHT_DIRECTIONAL)
        {
            if (sceneViewBox_.min_.z_ > shadowFarSplits_[i])
                continue;
            if (sceneViewBox_.max_.z_ < shadowNearSplits_[i])
                continue;
        }
        
        if (!useOcclusion)
        {
            // For spot light (which has only one shadow split) we can optimize by reusing the query for
            // lit geometries, whose result still exists in tempDrawables_
            if (type != LIGHT_SPOT)
            {
                FrustumOctreeQuery query(tempDrawables_, shadowCameraFrustum, DRAWABLE_GEOMETRY, camera_->GetViewMask(),
                    false, true);
                octree_->GetDrawables(query);
            }
        }
        else
        {
            OccludedFrustumOctreeQuery query(tempDrawables_, shadowCamera->GetFrustum(), buffer,
                DRAWABLE_GEOMETRY, camera_->GetViewMask(), false, true);
            octree_->GetDrawables(query);
        }
        
        // Check which shadow casters actually contribute to the shadowing
        ProcessShadowCasters(light, i, tempDrawables_, shadowCasterBox_[i]);
        if (shadowCasters_[i].Size())
            hasShadowCasters = true;
    }
    
    // If no shadow casters, the light can be rendered unshadowed. At this point we have not allocated a shadow map yet, so the
    // only cost has been the shadow camera setup & queries
    if (!hasShadowCasters)
        shadowSplits = 0;
    
    return shadowSplits;
}

void View::ProcessShadowCasters(Light* light, unsigned splitIndex, const PODVector<Drawable*>& result, BoundingBox& shadowCasterBox)
{
    Matrix3x4 lightView;
    Matrix4 lightProj;
    
    Camera* shadowCamera = shadowCameras_[splitIndex];
    lightView = shadowCamera->GetInverseWorldTransform();
    lightProj = shadowCamera->GetProjection();
    bool dirLight = shadowCamera->IsOrthographic();
    
    // Transform scene frustum into shadow camera's view space for shadow caster visibility check. For point & spot lights,
    // we can use the whole scene frustum. For directional lights, use the intersection of the scene frustum and the split
    // frustum, so that shadow casters do not get rendered into unnecessary splits
    Frustum lightViewFrustum;
    if (!dirLight)
        lightViewFrustum = camera_->GetSplitFrustum(sceneViewBox_.min_.z_, sceneViewBox_.max_.z_).Transformed(lightView);
    else
        lightViewFrustum = camera_->GetSplitFrustum(Max(sceneViewBox_.min_.z_, shadowNearSplits_[splitIndex]),
            Min(sceneViewBox_.max_.z_, shadowFarSplits_[splitIndex])).Transformed(lightView);
    
    BoundingBox lightViewFrustumBox(lightViewFrustum);
     
    // Check for degenerate split frustum: in that case there is no need to get shadow casters
    if (lightViewFrustum.vertices_[0] == lightViewFrustum.vertices_[4])
        return;
    
    BoundingBox lightViewBox;
    BoundingBox lightProjBox;
    
    for (unsigned i = 0; i < result.Size(); ++i)
    {
        Drawable* drawable = static_cast<Drawable*>(result[i]);
        // In case this is a spot light query result reused for optimization, we may have non-shadowcasters included.
        // Check for that first
        if (!drawable->GetCastShadows())
            continue;
        
        drawable->UpdateDistance(frame_);
        
        // Check shadow distance
        float maxShadowDistance = drawable->GetShadowDistance();
        if (maxShadowDistance > 0.0f && drawable->GetDistance() > maxShadowDistance)
            continue;
        
        // Check light mask
        if (!(GetLightMask(drawable) & light->GetLightMask()))
            continue;
        
        // Project shadow caster bounding box to light view space for visibility check
        lightViewBox = drawable->GetWorldBoundingBox().Transformed(lightView);
        
        if (IsShadowCasterVisible(drawable, lightViewBox, shadowCamera, lightView, lightViewFrustum, lightViewFrustumBox))
        {
            // Update geometry now if not updated yet
            if (!drawable->IsInView(frame_))
            {
                drawable->MarkInShadowView(frame_);
                drawable->UpdateGeometry(frame_);
            }
            
            // Merge to shadow caster bounding box and add to the list
            if (dirLight)
                shadowCasterBox.Merge(lightViewBox);
            else
            {
                lightProjBox = lightViewBox.Projected(lightProj);
                shadowCasterBox.Merge(lightProjBox);
            }
            shadowCasters_[splitIndex].Push(drawable);
        }
    }
}

bool View::IsShadowCasterVisible(Drawable* drawable, BoundingBox lightViewBox, Camera* shadowCamera, const Matrix3x4& lightView,
    const Frustum& lightViewFrustum, const BoundingBox& lightViewFrustumBox)
{
    if (shadowCamera->IsOrthographic())
    {
        // If shadow caster is also an occluder, must let it be visible, because it has potentially already culled
        // away other shadow casters (could also check the actual shadow occluder vector, but that would be slower)
        if (drawable->IsOccluder())
            return true;
        
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
        Vector3 center = lightViewBox.Center();
        Ray extrusionRay(center, center.Normalized());
        
        float extrusionDistance = shadowCamera->GetFarClip();
        float originalDistance = Clamp(center.LengthFast(), M_EPSILON, extrusionDistance);
        
        // Because of the perspective, the bounding box must also grow when it is extruded to the distance
        float sizeFactor = extrusionDistance / originalDistance;
        
        // Calculate the endpoint box and merge it to the original. Because it's axis-aligned, it will be larger
        // than necessary, so the test will be conservative
        Vector3 newCenter = extrusionDistance * extrusionRay.direction_;
        Vector3 newHalfSize = lightViewBox.Size() * sizeFactor * 0.5f;
        BoundingBox extrudedBox(newCenter - newHalfSize, newCenter + newHalfSize);
        lightViewBox.Merge(extrudedBox);
        
        return lightViewFrustum.IsInsideFast(lightViewBox) != OUTSIDE;
    }
}

IntRect View::GetShadowMapViewport(Light* light, unsigned splitIndex, Texture2D* shadowMap)
{
    unsigned width = shadowMap->GetWidth();
    unsigned height = shadowMap->GetHeight();
    int maxCascades = renderer_->GetMaxShadowCascades();
    
    switch (light->GetLightType())
    {
    case LIGHT_DIRECTIONAL:
        if (maxCascades == 1)
            return IntRect(0, 0, width, height);
        else if (maxCascades == 2)
            return IntRect(splitIndex * width / 2, 0, (splitIndex + 1) * width / 2, height);
        else
            return IntRect((splitIndex & 1) * width / 2, (splitIndex / 2) * height / 2, ((splitIndex & 1) + 1) * width / 2,
                (splitIndex / 2 + 1) * height / 2);
        
    case LIGHT_SPOT:
        return IntRect(0, 0, width, height);
        
    case LIGHT_POINT:
        return IntRect((splitIndex & 1) * width / 2, (splitIndex / 2) * height / 3, ((splitIndex & 1) + 1) * width / 2,
            (splitIndex / 2 + 1) * height / 3);
    }
    
    return IntRect();
}

void View::OptimizeLightByScissor(Light* light)
{
    if (light)
        graphics_->SetScissorTest(true, GetLightScissor(light));
    else
        graphics_->SetScissorTest(false);
}

void View::OptimizeLightByStencil(Light* light)
{
    if (light && renderer_->GetLightStencilMasking())
    {
        Geometry* geometry = renderer_->GetLightGeometry(light);
        if (!geometry)
        {
            graphics_->SetStencilTest(false);
            return;
        }
        
        LightType type = light->GetLightType();
        Matrix3x4 view(camera_->GetInverseWorldTransform());
        Matrix4 projection(camera_->GetProjection());
        float lightDist;
        
        if (type == LIGHT_POINT)
            lightDist = Sphere(light->GetWorldPosition(), light->GetRange() * 1.25f).DistanceFast(camera_->GetWorldPosition());
        else
            lightDist = light->GetFrustum().Distance(camera_->GetWorldPosition());
        
        // If the camera is actually inside the light volume, do not draw to stencil as it would waste fillrate
        if (lightDist < M_EPSILON)
        {
            graphics_->SetStencilTest(false);
            return;
        }
        
        // If the stencil value has wrapped, clear the whole stencil first
        if (!lightStencilValue_)
        {
            graphics_->Clear(CLEAR_STENCIL);
            lightStencilValue_ = 1;
        }
        
        // If possible, render the stencil volume front faces. However, close to the near clip plane render back faces instead
        // to avoid clipping the front faces.
        if (lightDist < camera_->GetNearClip() * 2.0f)
        {
            graphics_->SetCullMode(CULL_CW);
            graphics_->SetDepthTest(CMP_GREATER);
        }
        else
        {
            graphics_->SetCullMode(CULL_CCW);
            graphics_->SetDepthTest(CMP_LESSEQUAL);
        }
        
        graphics_->SetColorWrite(false);
        graphics_->SetDepthWrite(false);
        graphics_->SetStencilTest(true, CMP_ALWAYS, OP_REF, OP_KEEP, OP_KEEP, lightStencilValue_);
        graphics_->SetShaders(renderer_->GetStencilVS(), renderer_->GetStencilPS());
        graphics_->SetShaderParameter(VSP_VIEWPROJ, projection * view);
        graphics_->SetShaderParameter(VSP_MODEL, light->GetVolumeTransform());
        
        geometry->Draw(graphics_);
        
        graphics_->ClearTransformSources();
        graphics_->SetColorWrite(true);
        graphics_->SetStencilTest(true, CMP_EQUAL, OP_KEEP, OP_KEEP, OP_KEEP, lightStencilValue_);
        
        // Increase stencil value for next light
        ++lightStencilValue_;
    }
    else
        graphics_->SetStencilTest(false);
}

const Rect& View::GetLightScissor(Light* light)
{
    HashMap<Light*, Rect>::Iterator i = lightScissorCache_.Find(light);
    if (i != lightScissorCache_.End())
        return i->second_;
    
    Matrix3x4 view(camera_->GetInverseWorldTransform());
    Matrix4 projection(camera_->GetProjection());
    
    switch (light->GetLightType())
    {
    case LIGHT_POINT:
        {
            BoundingBox viewBox(light->GetWorldBoundingBox().Transformed(view));
            return lightScissorCache_[light] = viewBox.Projected(projection);
        }
        
    case LIGHT_SPOT:
        {
            Frustum viewFrustum(light->GetFrustum().Transformed(view));
            return lightScissorCache_[light] = viewFrustum.Projected(projection);
        }
        
    default:
        return lightScissorCache_[light] = Rect::FULL;
    }
}

unsigned View::SetupShadowCameras(Light* light)
{
    LightType type = light->GetLightType();
    if (type == LIGHT_DIRECTIONAL)
    {
        const CascadeParameters& cascade = light->GetShadowCascade();
        int splits = 0;
        
        float nearSplit = camera_->GetNearClip();
        float farSplit;
        
        while (splits < renderer_->GetMaxShadowCascades())
        {
            // If split is completely beyond camera far clip, we are done
            if (nearSplit > camera_->GetFarClip())
                break;
            
            farSplit = Min(camera_->GetFarClip(), cascade.splits_[splits]);
            if (farSplit <= nearSplit)
                break;
            
            // Setup the shadow camera for the split
            Camera* shadowCamera = renderer_->CreateShadowCamera();
            shadowCameras_[splits] = shadowCamera;
            shadowNearSplits_[splits] = nearSplit;
            shadowFarSplits_[splits] = farSplit;
            SetupDirLightShadowCamera(shadowCamera, light, nearSplit, farSplit, false);
            
            nearSplit = farSplit;
            ++splits;
        }
        
        return splits;
    }
    
    if (type == LIGHT_SPOT)
    {
        Camera* shadowCamera = renderer_->CreateShadowCamera();
        shadowCameras_[0] = shadowCamera;
        Node* cameraNode = shadowCamera->GetNode();
        
        cameraNode->SetTransform(light->GetWorldPosition(), light->GetWorldRotation());
        shadowCamera->SetNearClip(light->GetShadowNearFarRatio() * light->GetRange());
        shadowCamera->SetFarClip(light->GetRange());
        shadowCamera->SetFov(light->GetFov());
        shadowCamera->SetAspectRatio(light->GetAspectRatio());
        
        return 1;
    }
    
    if (type == LIGHT_POINT)
    {
        for (unsigned i = 0; i < MAX_CUBEMAP_FACES; ++i)
        {
            Camera* shadowCamera = renderer_->CreateShadowCamera();
            shadowCameras_[i] = shadowCamera;
            Node* cameraNode = shadowCamera->GetNode();
            
            // When making a shadowed point light, align the splits along X, Y and Z axes regardless of light rotation
            cameraNode->SetPosition(light->GetWorldPosition());
            cameraNode->SetDirection(directions[i]);
            shadowCamera->SetNearClip(light->GetShadowNearFarRatio() * light->GetRange());
            shadowCamera->SetFarClip(light->GetRange());
            shadowCamera->SetFov(90.0f);
            shadowCamera->SetAspectRatio(1.0f);
        }
        
        return MAX_CUBEMAP_FACES;
    }
    
    return 0;
}

void View::SetupDirLightShadowCamera(Camera* shadowCamera, Light* light, float nearSplit, float farSplit, bool shadowOcclusion)
{
    Node* cameraNode = shadowCamera->GetNode();
    float extrusionDistance = camera_->GetFarClip();
    const FocusParameters& parameters = light->GetShadowFocus();
    
    // Calculate initial position & rotation
    Vector3 lightWorldDirection = light->GetWorldRotation() * Vector3::FORWARD;
    Vector3 pos = camera_->GetWorldPosition() - extrusionDistance * lightWorldDirection;
    cameraNode->SetTransform(pos, light->GetWorldRotation());
    
    // Calculate main camera shadowed frustum in light's view space
    farSplit = Min(farSplit, camera_->GetFarClip());
    // Use the scene Z bounds to limit frustum size if applicable
    if (shadowOcclusion || parameters.focus_)
    {
        nearSplit = Max(sceneViewBox_.min_.z_, nearSplit);
        farSplit = Min(sceneViewBox_.max_.z_, farSplit);
    }
    
    Frustum splitFrustum = camera_->GetSplitFrustum(nearSplit, farSplit);
    frustumVolume_.Define(splitFrustum);
    // If focusing enabled, clip the frustum volume by the combined bounding box of the lit geometries within the frustum
    if (!shadowOcclusion && parameters.focus_)
    {
        PROFILE(ClipFrustumVolume);
        
        BoundingBox litGeometriesBox;
        for (unsigned i = 0; i < geometries_.Size(); ++i)
        {
            // Skip "infinite" objects like the skybox
            const BoundingBox& geomBox = geometries_[i]->GetWorldBoundingBox();
            if (geomBox.Size().LengthFast() < M_LARGE_VALUE)
            {
                if (geometryDepthBounds_[i].min_ <= farSplit && geometryDepthBounds_[i].max_ >= nearSplit &&
                    (GetLightMask(geometries_[i]) & light->GetLightMask()))
                    litGeometriesBox.Merge(geomBox);
            }
        }
        if (litGeometriesBox.defined_)
        {
            frustumVolume_.Clip(litGeometriesBox);
            // If volume became empty, restore it to avoid zero size
            if (frustumVolume_.Empty())
                frustumVolume_.Define(splitFrustum);
        }
    }
    
    // Transform frustum volume to light space
    Matrix3x4 lightView(shadowCamera->GetInverseWorldTransform());
    frustumVolume_.Transform(lightView);
    
    // Fit the frustum volume inside a bounding box. If uniform size, use a sphere instead
    BoundingBox shadowBox;
    if (shadowOcclusion || !parameters.nonUniform_)
        shadowBox.Define(Sphere(frustumVolume_));
    else
        shadowBox.Define(frustumVolume_);
    
    shadowCamera->SetOrthographic(true);
    shadowCamera->SetAspectRatio(1.0f);
    shadowCamera->SetNearClip(0.0f);
    shadowCamera->SetFarClip(shadowBox.max_.z_);
    
    // Center shadow camera on the bounding box. Can not snap to texels yet as the shadow map viewport is unknown
    QuantizeDirLightShadowCamera(shadowCamera, light, IntRect(0, 0, 0, 0), shadowBox);
}

void View::FinalizeShadowCamera(Camera* shadowCamera, Light* light, const IntRect& shadowViewport,
    const BoundingBox& shadowCasterBox)
{
    const FocusParameters& parameters = light->GetShadowFocus();
    float shadowMapWidth = (float)(shadowViewport.right_ - shadowViewport.left_);
    LightType type = light->GetLightType();
    
    if (type == LIGHT_DIRECTIONAL)
    {
        BoundingBox shadowBox;
        shadowBox.max_.y_ = shadowCamera->GetOrthoSize() * 0.5f;
        shadowBox.max_.x_ = shadowCamera->GetAspectRatio() * shadowBox.max_.y_;
        shadowBox.min_.y_ = -shadowBox.max_.y_;
        shadowBox.min_.x_ = -shadowBox.max_.x_;
        
        // Requantize and snap to shadow map texels
        QuantizeDirLightShadowCamera(shadowCamera, light, shadowViewport, shadowBox);
    }
    
    if (type == LIGHT_SPOT)
    {
        if (parameters.focus_)
        {
            float viewSizeX = Max(fabsf(shadowCasterBox.min_.x_), fabsf(shadowCasterBox.max_.x_));
            float viewSizeY = Max(fabsf(shadowCasterBox.min_.y_), fabsf(shadowCasterBox.max_.y_));
            float viewSize = Max(viewSizeX, viewSizeY);
            // Scale the quantization parameters, because view size is in projection space (-1.0 - 1.0)
            float invOrthoSize = 1.0f / shadowCamera->GetOrthoSize();
            float quantize = parameters.quantize_ * invOrthoSize;
            float minView = parameters.minView_ * invOrthoSize;
            
            viewSize = Max(ceilf(viewSize / quantize) * quantize, minView);
            if (viewSize < 1.0f)
                shadowCamera->SetZoom(1.0f / viewSize);
        }
    }
    
    // Perform a finalization step for all lights: ensure zoom out of 2 pixels to eliminate border filtering issues
    // For point lights use 4 pixels, as they must not cross sides of the virtual cube map (maximum 3x3 PCF)
    if (shadowCamera->GetZoom() >= 1.0f)
    {
        if (light->GetLightType() != LIGHT_POINT)
            shadowCamera->SetZoom(shadowCamera->GetZoom() * ((shadowMapWidth - 2.0f) / shadowMapWidth));
        else
        {
            #ifdef USE_OPENGL
                shadowCamera->SetZoom(shadowCamera->GetZoom() * ((shadowMapWidth - 3.0f) / shadowMapWidth));
            #else
                shadowCamera->SetZoom(shadowCamera->GetZoom() * ((shadowMapWidth - 4.0f) / shadowMapWidth));
            #endif
        }
    }
}

void View::QuantizeDirLightShadowCamera(Camera* shadowCamera, Light* light, const IntRect& shadowViewport,
    const BoundingBox& viewBox)
{
    Node* cameraNode = shadowCamera->GetNode();
    const FocusParameters& parameters = light->GetShadowFocus();
    float shadowMapWidth = (float)(shadowViewport.right_ - shadowViewport.left_);
    
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
    Vector3 pos(shadowCamera->GetWorldPosition());
    Quaternion rot(shadowCamera->GetWorldRotation());
    Vector3 adjust(center.x_, center.y_, 0.0f);
    cameraNode->Translate(rot * adjust);
    
    // If the shadow map viewport is known, snap to whole texels
    if (shadowMapWidth > 0.0f)
    {
        Vector3 viewPos(rot.Inverse() * cameraNode->GetWorldPosition());
        // Take into account that shadow map border will not be used
        float invActualSize = 1.0f / (shadowMapWidth - 2.0f);
        Vector2 texelSize(viewSize.x_ * invActualSize, viewSize.y_ * invActualSize);
        Vector3 snap(-fmodf(viewPos.x_, texelSize.x_), -fmodf(viewPos.y_, texelSize.y_), 0.0f);
        cameraNode->Translate(rot * snap);
    }
}

void View::FindZone(Drawable* drawable, int highestZonePriority)
{
    Vector3 center = drawable->GetWorldBoundingBox().Center();
    
    // First check if the last zone remains a conclusive result
    Zone* lastZone = drawable->GetLastZone();
    if (lastZone && lastZone->IsInside(center) && (drawable->GetZoneMask() & lastZone->GetZoneMask()) && lastZone->GetPriority()
        >= highestZonePriority)
        drawable->SetZone(lastZone);
    // Then check if the visible zones contain the node center
    else
    {
        int bestPriority = M_MIN_INT;
        Zone* newZone = 0;
        for (PODVector<Zone*>::Iterator i = zones_.Begin(); i != zones_.End(); ++i)
        {
            int priority = (*i)->GetPriority();
            if ((*i)->IsInside(center) && (drawable->GetZoneMask() & (*i)->GetZoneMask()) && priority > bestPriority)
            {
                newZone = *i;
                bestPriority = priority;
            }
        }
        
        // Finally, if no zone found yet, query the octree for zones at node center
        if (!newZone)
        {
            PointOctreeQuery query(reinterpret_cast<PODVector<Drawable*>&>(tempZones_), center, DRAWABLE_ZONE);
            octree_->GetDrawables(query);
            
            bestPriority = M_MIN_INT;
            for (PODVector<Zone*>::Iterator i = tempZones_.Begin(); i != tempZones_.End(); ++i)
            {
                int priority = (*i)->GetPriority();
                if ((*i)->IsInside(center) && (drawable->GetZoneMask() & (*i)->GetZoneMask()) && priority > bestPriority)
                {
                    newZone = *i;
                    bestPriority = priority;
                }
            }
        }
        
        drawable->SetZone(newZone);
    }
}

Zone* View::GetZone(Drawable* drawable)
{
    if (cameraZoneOverride_)
        return cameraZone_;
    Zone* drawableZone = drawable->GetZone();
    return drawableZone ? drawableZone : cameraZone_;
}

unsigned View::GetLightMask(Drawable* drawable)
{
    return drawable->GetLightMask() & GetZone(drawable)->GetLightMask();
}

Technique* View::GetTechnique(Drawable* drawable, Material*& material)
{
    if (!material)
        material = renderer_->GetDefaultMaterial();
    if (!material)
        return 0;
    
    float lodDistance = drawable->GetLodDistance();
    const Vector<TechniqueEntry>& techniques = material->GetTechniques();
    if (techniques.Empty())
        return 0;
    
    // Check for suitable technique. Techniques should be ordered like this:
    // Most distant & highest quality
    // Most distant & lowest quality
    // Second most distant & highest quality
    // ...
    for (unsigned i = 0; i < techniques.Size(); ++i)
    {
        const TechniqueEntry& entry = techniques[i];
        Technique* technique = entry.technique_;
        if (!technique || (technique->IsSM3() && !graphics_->GetSM3Support()) || materialQuality_ < entry.qualityLevel_)
            continue;
        if (lodDistance >= entry.lodDistance_)
            return technique;
    }
    
    // If no suitable technique found, fallback to the last
    return techniques.Back().technique_;
}

void View::CheckMaterialForAuxView(Material* material)
{
    const Vector<SharedPtr<Texture> >& textures = material->GetTextures();
    
    for (unsigned i = 0; i < textures.Size(); ++i)
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
                    if (viewport.scene_ && viewport.camera_)
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
                        if (viewport.scene_ && viewport.camera_)
                            renderer_->AddView(target, viewport);
                    }
                }
            }
        }
    }
    
    // Set frame number so that we can early-out next time we come across this material on the same frame
    material->MarkForAuxView(frame_.frameNumber_);
}

void View::FinalizeBatch(Batch& batch, Technique* tech, Pass* pass, bool allowInstancing, bool allowShadows)
{
    // Convert to instanced if possible
    if (allowInstancing && batch.geometryType_ == GEOM_STATIC && !batch.shaderData_ && !batch.overrideView_)
        batch.geometryType_ = GEOM_INSTANCED;
    
    batch.pass_ = pass;
    renderer_->SetBatchShaders(batch, tech, pass, allowShadows);
    batch.CalculateSortKey();
}

void View::SortBatches()
{
    PROFILE(SortBatches);
    
    baseQueue_.SortFrontToBack();
    preAlphaQueue_.SortFrontToBack();
    alphaQueue_.SortBackToFront();
    postAlphaQueue_.SortBackToFront();
    
    for (unsigned i = 0; i < lightQueues_.Size(); ++i)
    {
        for (unsigned j = 0; j < lightQueues_[i].shadowSplits_.Size(); ++j)
            lightQueues_[i].shadowSplits_[j].shadowBatches_.SortFrontToBack();
        lightQueues_[i].litBatches_.SortFrontToBack();
    }
}

void View::PrepareInstancingBuffer()
{
    PROFILE(PrepareInstancingBuffer);
    
    unsigned totalInstances = 0;
    
    totalInstances += baseQueue_.GetNumInstances(renderer_);
    totalInstances += preAlphaQueue_.GetNumInstances(renderer_);
    
    for (unsigned i = 0; i < lightQueues_.Size(); ++i)
    {
        for (unsigned j = 0; j < lightQueues_[i].shadowSplits_.Size(); ++j)
            totalInstances += lightQueues_[i].shadowSplits_[j].shadowBatches_.GetNumInstances(renderer_);
        totalInstances += lightQueues_[i].litBatches_.GetNumInstances(renderer_);
    }
    
    // If fail to set buffer size, fall back to per-group locking
    if (totalInstances && renderer_->ResizeInstancingBuffer(totalInstances))
    {
        VertexBuffer* instancingBuffer = renderer_->GetInstancingBuffer();
        unsigned freeIndex = 0;
        void* lockedData = instancingBuffer->Lock(0, totalInstances, LOCK_DISCARD);
        if (lockedData)
        {
            baseQueue_.SetTransforms(renderer_, lockedData, freeIndex);
            preAlphaQueue_.SetTransforms(renderer_, lockedData, freeIndex);
            
            for (unsigned i = 0; i < lightQueues_.Size(); ++i)
            {
                for (unsigned j = 0; j < lightQueues_[i].shadowSplits_.Size(); ++j)
                    lightQueues_[i].shadowSplits_[j].shadowBatches_.SetTransforms(renderer_, lockedData, freeIndex);
                lightQueues_[i].litBatches_.SetTransforms(renderer_, lockedData, freeIndex);
            }
            
            instancingBuffer->Unlock();
        }
    }
}

void View::RenderBatchQueue(const BatchQueue& queue, bool useScissor)
{
    graphics_->SetScissorTest(false);
    graphics_->SetStencilTest(false);
    
    // Base instanced
    for (PODVector<BatchGroup*>::ConstIterator i = queue.sortedBaseBatchGroups_.Begin(); i !=
        queue.sortedBaseBatchGroups_.End(); ++i)
    {
        BatchGroup* group = *i;
        group->Draw(graphics_, renderer_);
    }
    // Base non-instanced
    for (PODVector<Batch*>::ConstIterator i = queue.sortedBaseBatches_.Begin(); i != queue.sortedBaseBatches_.End(); ++i)
    {
        Batch* batch = *i;
        batch->Draw(graphics_, renderer_);
    }
    
    // Non-base instanced
    for (PODVector<BatchGroup*>::ConstIterator i = queue.sortedBatchGroups_.Begin(); i != queue.sortedBatchGroups_.End(); ++i)
    {
        BatchGroup* group = *i;
        if (useScissor && group->lightQueue_)
            OptimizeLightByScissor(group->lightQueue_->light_);
        group->Draw(graphics_, renderer_);
    }
    // Non-base non-instanced
    for (PODVector<Batch*>::ConstIterator i = queue.sortedBatches_.Begin(); i != queue.sortedBatches_.End(); ++i)
    {
        Batch* batch = *i;
        if (useScissor)
        {
            if (!batch->isBase_ && batch->lightQueue_)
                OptimizeLightByScissor(batch->lightQueue_->light_);
            else
                graphics_->SetScissorTest(false);
        }
        batch->Draw(graphics_, renderer_);
    }
}

void View::RenderLightBatchQueue(const BatchQueue& queue, Light* light)
{
    graphics_->SetScissorTest(false);
    graphics_->SetStencilTest(false);
    
    // Base instanced
    for (PODVector<BatchGroup*>::ConstIterator i = queue.sortedBaseBatchGroups_.Begin(); i !=
        queue.sortedBaseBatchGroups_.End(); ++i)
    {
        BatchGroup* group = *i;
        group->Draw(graphics_, renderer_);
    }
    // Base non-instanced
    for (PODVector<Batch*>::ConstIterator i = queue.sortedBaseBatches_.Begin(); i != queue.sortedBaseBatches_.End(); ++i)
    {
        Batch* batch = *i;
        batch->Draw(graphics_, renderer_);
    }
    
    // All base passes have been drawn. Optimize at this point by both stencil volume and scissor
    OptimizeLightByStencil(light);
    OptimizeLightByScissor(light);
    
    // Non-base instanced
    for (PODVector<BatchGroup*>::ConstIterator i = queue.sortedBatchGroups_.Begin(); i != queue.sortedBatchGroups_.End(); ++i)
    {
        BatchGroup* group = *i;
        group->Draw(graphics_, renderer_);
    }
    // Non-base non-instanced
    for (PODVector<Batch*>::ConstIterator i = queue.sortedBatches_.Begin(); i != queue.sortedBatches_.End(); ++i)
    {
        Batch* batch = *i;
        batch->Draw(graphics_, renderer_);
    }
}

void View::RenderShadowMap(const LightBatchQueue& queue)
{
    PROFILE(RenderShadowMap);
    
    Texture2D* shadowMap = queue.shadowMap_;
    
    graphics_->SetStencilTest(false);
    graphics_->SetTexture(TU_SHADOWMAP, 0);
    
    if (!graphics_->GetFallback())
    {
        graphics_->SetColorWrite(false);
        graphics_->SetRenderTarget(0, shadowMap->GetRenderSurface()->GetLinkedRenderTarget());
        graphics_->SetDepthStencil(shadowMap);
        graphics_->Clear(CLEAR_DEPTH);
    }
    else
    {
        graphics_->SetColorWrite(true);
        graphics_->SetRenderTarget(0, shadowMap->GetRenderSurface());
        graphics_->SetDepthStencil(shadowMap->GetRenderSurface()->GetLinkedDepthBuffer());
        graphics_->Clear(CLEAR_COLOR | CLEAR_DEPTH, Color::WHITE);
    }
    
    // Set shadow depth bias
    BiasParameters parameters = queue.light_->GetShadowBias();
    // Adjust the light's constant depth bias according to global shadow map resolution
    /// \todo Should remove this adjustment and find a more flexible solution
    unsigned shadowMapSize = renderer_->GetShadowMapSize();
    if (shadowMapSize <= 512)
        parameters.constantBias_ *= 2.0f;
    else if (shadowMapSize >= 2048)
        parameters.constantBias_ *= 0.5f;
    
    graphics_->SetDepthBias(parameters.constantBias_, parameters.slopeScaledBias_);
    
    // Render each of the splits
    for (unsigned i = 0; i < queue.shadowSplits_.Size(); ++i)
    {
        const ShadowBatchQueue& shadowQueue = queue.shadowSplits_[i];
        if (!shadowQueue.shadowBatches_.IsEmpty())
        {
            graphics_->SetViewport(shadowQueue.shadowViewport_);
            
            // Set a scissor rectangle to match possible shadow map size reduction by out-zooming
            // However, do not do this for point lights, which need to render continuously across cube faces
            float width = (float)(shadowQueue.shadowViewport_.right_ - shadowQueue.shadowViewport_.left_);
            if (queue.light_->GetLightType() != LIGHT_POINT)
            {
                float zoom = Min(shadowQueue.shadowCamera_->GetZoom(), width - 2.0f / width);
                Rect zoomRect(Vector2(-1.0f, -1.0f) * zoom, Vector2(1.0f, 1.0f) * zoom);
                graphics_->SetScissorTest(true, zoomRect, false);
            }
            else
                graphics_->SetScissorTest(false);
            
            // Draw instanced and non-instanced shadow casters
            RenderBatchQueue(shadowQueue.shadowBatches_);
        }
    }
    
    graphics_->SetColorWrite(true);
    graphics_->SetDepthBias(0.0f, 0.0f);
}
