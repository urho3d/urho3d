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
#include "WorkQueue.h"
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

static const int CHECK_DRAWABLES_PER_WORK_ITEM = 64;

void CheckVisibilityWork(const WorkItem* item, unsigned threadIndex)
{
    View* view = reinterpret_cast<View*>(item->aux_);
    Drawable** start = reinterpret_cast<Drawable**>(item->start_);
    Drawable** end = reinterpret_cast<Drawable**>(item->end_);
    Drawable** unculledStart = &view->tempDrawables_[0][0] + view->unculledDrawableStart_;
    OcclusionBuffer* buffer = view->occlusionBuffer_;
    
    while (start != end)
    {
        Drawable* drawable = *start;
        bool useOcclusion = start < unculledStart;
        unsigned char flags = drawable->GetDrawableFlags();
        ++start;
        
        if (flags & DRAWABLE_ZONE)
            continue;
        
        drawable->UpdateDistance(view->frame_);
        
        // If draw distance non-zero, check it
        float maxDistance = drawable->GetDrawDistance();
        if (maxDistance > 0.0f && drawable->GetDistance() > maxDistance)
            continue;
        
        if (buffer && useOcclusion && !buffer->IsVisible(drawable->GetWorldBoundingBox()))
            continue;
        
        drawable->MarkInView(view->frame_);
        
        // For geometries, clear lights and find new zone if necessary
        if (flags & DRAWABLE_GEOMETRY)
        {
            drawable->ClearLights();
            if (!drawable->GetZone() && !view->cameraZoneOverride_)
                view->FindZone(drawable, threadIndex);
        }
    }
}

void ProcessLightWork(const WorkItem* item, unsigned threadIndex)
{
    View* view = reinterpret_cast<View*>(item->aux_);
    LightQueryResult* query = reinterpret_cast<LightQueryResult*>(item->start_);
    
    view->ProcessLight(*query, threadIndex);
}

void UpdateDrawableGeometriesWork(const WorkItem* item, unsigned threadIndex)
{
    const FrameInfo& frame = *(reinterpret_cast<FrameInfo*>(item->aux_));
    Drawable** start = reinterpret_cast<Drawable**>(item->start_);
    Drawable** end = reinterpret_cast<Drawable**>(item->end_);
    
    while (start != end)
    {
        Drawable* drawable = *start;
        drawable->UpdateGeometry(frame);
        ++start;
    }
}

void SortBatchQueueFrontToBackWork(const WorkItem* item, unsigned threadIndex)
{
    BatchQueue* queue = reinterpret_cast<BatchQueue*>(item->start_);
    
    queue->SortFrontToBack();
}

void SortBatchQueueBackToFrontWork(const WorkItem* item, unsigned threadIndex)
{
    BatchQueue* queue = reinterpret_cast<BatchQueue*>(item->start_);
    
    queue->SortBackToFront();
}

void SortLightQueueWork(const WorkItem* item, unsigned threadIndex)
{
    LightBatchQueue* start = reinterpret_cast<LightBatchQueue*>(item->start_);
    for (unsigned i = 0; i < start->shadowSplits_.Size(); ++i)
        start->shadowSplits_[i].shadowBatches_.SortFrontToBack();
    start->litBatches_.SortFrontToBack();
}

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
    
    // Create octree query vectors for each thread
    tempDrawables_.Resize(GetSubsystem<WorkQueue>()->GetNumThreads() + 1);
    tempZones_.Resize(GetSubsystem<WorkQueue>()->GetNumThreads() + 1);
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
    
    // Check for the render texture being too large
    if (renderer_->GetLightPrepass() && renderTarget)
    {
        if (renderTarget->GetWidth() > graphics_->GetWidth() || renderTarget->GetHeight() > graphics_->GetHeight())
        {
            // Display message only once per render target, do not spam each frame
            if (gBufferErrorDisplayed_.Find(renderTarget) == gBufferErrorDisplayed_.End())
            {
                gBufferErrorDisplayed_.Insert(renderTarget);
                LOGERROR("Render texture is larger than the G-buffer, can not render");
            }
            return false;
        }
    }
    
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
    
    // Clear old light scissor cache, geometry, light, occluder & batch lists
    lightScissorCache_.Clear();
    geometries_.Clear();
    allGeometries_.Clear();
    geometryDepthBounds_.Clear();
    lights_.Clear();
    zones_.Clear();
    occluders_.Clear();
    baseQueue_.Clear();
    preAlphaQueue_.Clear();
    gbufferQueue_.Clear();
    alphaQueue_.Clear();
    postAlphaQueue_.Clear();
    lightQueues_.Clear();
    vertexLightQueues_.Clear();
    
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
    UpdateGeometries();
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
    
    // Render
    if (renderer_->GetLightPrepass())
        RenderBatchesLightPrepass();
    else
        RenderBatchesForward();
    
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
    occlusionBuffer_ = 0;
    frame_.camera_ = 0;
}

void View::GetDrawables()
{
    PROFILE(GetDrawables);
    
    WorkQueue* queue = GetSubsystem<WorkQueue>();
    PODVector<Drawable*>& tempDrawables = tempDrawables_[0];
    
    // Perform one octree query to get everything, then examine the results
    FrustumOctreeQuery query(tempDrawables, frustum_, DRAWABLE_GEOMETRY | DRAWABLE_LIGHT | DRAWABLE_ZONE);
    octree_->GetDrawables(query);
    
    // Add unculled geometries & lights
    unculledDrawableStart_ = tempDrawables.Size();
    octree_->GetUnculledDrawables(tempDrawables, DRAWABLE_GEOMETRY | DRAWABLE_LIGHT);
    
    // Get zones and occluders first
    highestZonePriority_ = M_MIN_INT;
    int bestPriority = M_MIN_INT;
    Vector3 cameraPos = camera_->GetWorldPosition();
    
    // Get default zone first in case we do not have zones defined
    Zone* defaultZone = renderer_->GetDefaultZone();
    cameraZone_ = farClipZone_ = defaultZone;
    
    for (PODVector<Drawable*>::ConstIterator i = tempDrawables.Begin(); i != tempDrawables.End(); ++i)
    {
        Drawable* drawable = *i;
        unsigned char flags = drawable->GetDrawableFlags();
        
        if (flags & DRAWABLE_ZONE)
        {
            Zone* zone = static_cast<Zone*>(drawable);
            zones_.Push(zone);
            int priority = zone->GetPriority();
            if (priority > highestZonePriority_)
                highestZonePriority_ = priority;
            if (zone->IsInside(cameraPos) && priority > bestPriority)
            {
                cameraZone_ = zone;
                bestPriority = priority;
            }
        }
        else if (flags & DRAWABLE_GEOMETRY && drawable->IsOccluder())
            occluders_.Push(drawable);
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
    
    // If occlusion in use, get & render the occluders
    occlusionBuffer_ = 0;
    if (maxOccluderTriangles_ > 0)
    {
        UpdateOccluders(occluders_, camera_);
        if (occluders_.Size())
        {
            PROFILE(DrawOcclusion);
            
            occlusionBuffer_ = renderer_->GetOcclusionBuffer(camera_);
            DrawOccluders(occlusionBuffer_, occluders_);
        }
    }
    
    // Check visibility and find zones for moved drawables in worker threads
    {
        WorkItem item;
        item.workFunction_ = CheckVisibilityWork;
        item.aux_ = this;
        
        PODVector<Drawable*>::Iterator start = tempDrawables.Begin();
        while (start != tempDrawables.End())
        {
            PODVector<Drawable*>::Iterator end = tempDrawables.End();
            if (end - start > CHECK_DRAWABLES_PER_WORK_ITEM)
                end = start + CHECK_DRAWABLES_PER_WORK_ITEM;
            
            item.start_ = &(*start);
            item.end_ = &(*end);
            queue->AddWorkItem(item);
            
            start = end;
        }
        
        queue->Complete();
    }
    
    // Sort into geometries & lights, and build visible scene bounding boxes in world and view space
    sceneBox_.min_ = sceneBox_.max_ = Vector3::ZERO;
    sceneBox_.defined_ = false;
    sceneViewBox_.min_ = sceneViewBox_.max_ = Vector3::ZERO;
    sceneViewBox_.defined_ = false;
    Matrix3x4 view(camera_->GetInverseWorldTransform());
    
    for (unsigned i = 0; i < tempDrawables.Size(); ++i)
    {
        Drawable* drawable = tempDrawables[i];
        unsigned char flags = drawable->GetDrawableFlags();
        if (flags & DRAWABLE_ZONE || !drawable->IsInView(frame_))
            continue;
        
        if (flags & DRAWABLE_GEOMETRY)
        {
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
            allGeometries_.Push(drawable);
        }
        else if (flags & DRAWABLE_LIGHT)
        {
            Light* light = static_cast<Light*>(drawable);
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

void View::GetBatches()
{
    WorkQueue* queue = GetSubsystem<WorkQueue>();
    bool prepass = renderer_->GetLightPrepass();
    
    // Process lit geometries and shadow casters for each light
    {
        PROFILE_MULTIPLE(ProcessLights, lights_.Size());
        
        lightQueryResults_.Resize(lights_.Size());
        
        WorkItem item;
        item.workFunction_ = ProcessLightWork;
        item.aux_ = this;
        
        for (unsigned i = 0; i < lightQueryResults_.Size(); ++i)
        {
            LightQueryResult& query = lightQueryResults_[i];
            query.light_ = lights_[i];
            
            item.start_ = &query;
            queue->AddWorkItem(item);
        }
        
        // Ensure all lights have been processed before proceeding
        queue->Complete();
    }
    
    // Build light queues and lit batches
    {
        bool fallback = graphics_->GetFallback();
        
        maxLightsDrawables_.Clear();
        lightQueueMapping_.Clear();
        
        for (Vector<LightQueryResult>::ConstIterator i = lightQueryResults_.Begin(); i != lightQueryResults_.End(); ++i)
        {
            const LightQueryResult& query = *i;
            // If light has no affected geometries, no need to process further
            if (query.litGeometries_.Empty())
                continue;
            
            PROFILE(GetLightBatches);
            
            Light* light = query.light_;
            
            // Per-pixel light
            if (!light->GetPerVertex())
            {
                unsigned shadowSplits = query.numSplits_;
                
                // Initialize light queue. Store light-to-queue mapping so that the queue can be found later
                lightQueues_.Resize(lightQueues_.Size() + 1);
                LightBatchQueue& lightQueue = lightQueues_.Back();
                lightQueueMapping_[light] = &lightQueue;
                lightQueue.light_ = light;
                lightQueue.litBatches_.Clear();
                lightQueue.volumeBatches_.Clear();
                
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
                    Camera* shadowCamera = query.shadowCameras_[j];
                    shadowQueue.shadowCamera_ = shadowCamera;
                    shadowQueue.nearSplit_ = query.shadowNearSplits_[j];
                    shadowQueue.farSplit_ = query.shadowFarSplits_[j];
                    
                    // Setup the shadow split viewport and finalize shadow camera parameters
                    shadowQueue.shadowViewport_ = GetShadowMapViewport(light, j, lightQueue.shadowMap_);
                    FinalizeShadowCamera(shadowCamera, light, shadowQueue.shadowViewport_, query.shadowCasterBox_[j]);
                    
                    // Loop through shadow casters
                    for (PODVector<Drawable*>::ConstIterator k = query.shadowCasters_.Begin() + query.shadowCasterBegin_[j];
                        k < query.shadowCasters_.Begin() + query.shadowCasterEnd_[j]; ++k)
                    {
                        Drawable* drawable = *k;
                        if (!drawable->IsInView(frame_, false))
                        {
                            drawable->MarkInView(frame_, false);
                            allGeometries_.Push(drawable);
                        }
                        
                        unsigned numBatches = drawable->GetNumBatches();
                        
                        for (unsigned l = 0; l < numBatches; ++l)
                        {
                            Batch shadowBatch;
                            drawable->GetBatch(shadowBatch, frame_, l);
                            
                            Technique* tech = GetTechnique(drawable, shadowBatch.material_);
                            if (!shadowBatch.geometry_ || !tech)
                                continue;
                            
                            Pass* pass = tech->GetPass(PASS_SHADOW);
                            // Skip if material has no shadow pass
                            if (!pass)
                                continue;
                            
                            // Fill the rest of the batch
                            shadowBatch.camera_ = shadowCamera;
                            shadowBatch.zone_ = GetZone(drawable);
                            shadowBatch.lightQueue_ = &lightQueue;
                            
                            FinalizeBatch(shadowBatch, tech, pass);
                            shadowQueue.shadowBatches_.AddBatch(shadowBatch);
                        }
                    }
                }
                
                // Process lit geometries
                for (PODVector<Drawable*>::ConstIterator j = query.litGeometries_.Begin(); j != query.litGeometries_.End(); ++j)
                {
                    Drawable* drawable = *j;
                    drawable->AddLight(light);
                    
                    // If drawable limits maximum lights, only record the light, and check maximum count / build batches later
                    if (!drawable->GetMaxLights())
                        GetLitBatches(drawable, lightQueue);
                    else
                        maxLightsDrawables_.Insert(drawable);
                }
                
                // In light pre-pass mode, store the light volume batch now
                if (prepass)
                {
                    Batch volumeBatch;
                    volumeBatch.geometry_ = renderer_->GetLightGeometry(light);
                    volumeBatch.worldTransform_ = &light->GetVolumeTransform(camera_);
                    volumeBatch.overrideView_ = light->GetLightType() == LIGHT_DIRECTIONAL;
                    volumeBatch.camera_ = camera_;
                    volumeBatch.lightQueue_ = &lightQueue;
                    volumeBatch.distance_ = light->GetDistance();
                    volumeBatch.material_ = 0;
                    volumeBatch.pass_ = 0;
                    volumeBatch.zone_ = 0;
                    renderer_->SetLightVolumeBatchShaders(volumeBatch);
                    lightQueue.volumeBatches_.Push(volumeBatch);
                }
            }
            // Per-vertex light
            else
            {
                // Add the vertex light to lit drawables. It will be processed later during base pass batch generation
                for (PODVector<Drawable*>::ConstIterator j = query.litGeometries_.Begin(); j != query.litGeometries_.End(); ++j)
                {
                    Drawable* drawable = *j;
                    drawable->AddVertexLight(light);
                }
            }
        }
    }
    
    // Process drawables with limited per-pixel light count
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
                Map<Light*, LightBatchQueue*>::Iterator j = lightQueueMapping_.Find(light);
                if (j != lightQueueMapping_.End())
                    GetLitBatches(drawable, *(j->second_));
            }
        }
    }
    
    // Build base pass batches
    {
        PROFILE(GetBaseBatches);
        for (PODVector<Drawable*>::ConstIterator i = geometries_.Begin(); i != geometries_.End(); ++i)
        {
            Drawable* drawable = *i;
            unsigned numBatches = drawable->GetNumBatches();
            
            for (unsigned j = 0; j < numBatches; ++j)
            {
                Batch baseBatch;
                drawable->GetBatch(baseBatch, frame_, j);
                
                Technique* tech = GetTechnique(drawable, baseBatch.material_);
                if (!baseBatch.geometry_ || !tech)
                    continue;
                
                // Check here if the material technique refers to a render target texture with camera(s) attached
                // Only check this for the main view (null render target)
                if (!renderTarget_ && baseBatch.material_ && baseBatch.material_->GetAuxViewFrameNumber() != frame_.frameNumber_)
                    CheckMaterialForAuxView(baseBatch.material_);
                
                // Fill the rest of the batch
                baseBatch.camera_ = camera_;
                baseBatch.zone_ = GetZone(drawable);
                baseBatch.isBase_ = true;
                
                Pass* pass = 0;
                
                // In light prepass mode check for G-buffer and material passes first
                if (prepass)
                {
                    pass = tech->GetPass(PASS_GBUFFER);
                    if (pass)
                    {
                        // Allow G-buffer pass instancing only if lightmask matches zone lightmask
                        baseBatch.lightMask_ = GetLightMask(drawable);
                        FinalizeBatch(baseBatch, tech, pass, baseBatch.lightMask_ == (baseBatch.zone_->GetLightMask() & 0xff));
                        gbufferQueue_.AddBatch(baseBatch);
                        
                        pass = tech->GetPass(PASS_MATERIAL);
                    }
                }
                
                // Next check for forward base pass
                if (!pass)
                    pass = tech->GetPass(PASS_BASE);
                
                if (pass)
                {
                    // Check for vertex lights (both forward unlit and light pre-pass material pass)
                    const PODVector<Light*>& vertexLights = drawable->GetVertexLights();
                    if (!vertexLights.Empty())
                    {
                        drawable->LimitVertexLights();
                        
                        // Find a vertex light queue. If not found, create new
                        unsigned long long hash = GetVertexLightQueueHash(vertexLights);
                        HashMap<unsigned long long, LightBatchQueue>::Iterator i = vertexLightQueues_.Find(hash);
                        if (i == vertexLightQueues_.End())
                        {
                            vertexLightQueues_[hash].vertexLights_ = vertexLights;
                            i = vertexLightQueues_.Find(hash);
                        }
                        
                        baseBatch.lightQueue_ = &(i->second_);
                    }
                    
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
}

void View::UpdateGeometries()
{
    PROFILE(UpdateGeometries);
    
    WorkQueue* queue = GetSubsystem<WorkQueue>();
    
    // Sort batches
    {
        WorkItem item;
        
        item.workFunction_ = SortBatchQueueFrontToBackWork;
        item.start_ = &baseQueue_;
        queue->AddWorkItem(item);
        item.start_ = &preAlphaQueue_;
        queue->AddWorkItem(item);
        if (renderer_->GetLightPrepass())
        {
            item.start_ = &gbufferQueue_;
            queue->AddWorkItem(item);
        }
        
        item.workFunction_ = SortBatchQueueBackToFrontWork;
        item.start_ = &alphaQueue_;
        queue->AddWorkItem(item);
        item.start_ = &postAlphaQueue_;
        queue->AddWorkItem(item);
        
        for (List<LightBatchQueue>::Iterator i = lightQueues_.Begin(); i != lightQueues_.End(); ++i)
        {
            item.workFunction_ = SortLightQueueWork;
            item.start_ = &(*i);
            queue->AddWorkItem(item);
        }
    }
    
    // Update geometries. Split into threaded and non-threaded updates.
    {
        nonThreadedGeometries_.Clear();
        threadedGeometries_.Clear();
        for (PODVector<Drawable*>::Iterator i = allGeometries_.Begin(); i != allGeometries_.End(); ++i)
        {
            UpdateGeometryType type = (*i)->GetUpdateGeometryType();
            if (type == UPDATE_MAIN_THREAD)
                nonThreadedGeometries_.Push(*i);
            else if (type == UPDATE_WORKER_THREAD)
                threadedGeometries_.Push(*i);
        }
        
        if (threadedGeometries_.Size())
        {
            WorkItem item;
            item.workFunction_ = UpdateDrawableGeometriesWork;
            item.aux_ = const_cast<FrameInfo*>(&frame_);
            
            PODVector<Drawable*>::Iterator start = threadedGeometries_.Begin();
            while (start != threadedGeometries_.End())
            {
                PODVector<Drawable*>::Iterator end = threadedGeometries_.End();
                if (end - start > DRAWABLES_PER_WORK_ITEM)
                    end = start + DRAWABLES_PER_WORK_ITEM;
                
                item.start_ = &(*start);
                item.end_ = &(*end);
                queue->AddWorkItem(item);
                
                start = end;
            }
        }
        
        // While the work queue is processed, update non-threaded geometries
        for (PODVector<Drawable*>::ConstIterator i = nonThreadedGeometries_.Begin(); i != nonThreadedGeometries_.End(); ++i)
            (*i)->UpdateGeometry(frame_);
    }
    
    // Finally ensure all threaded work has completed
    queue->Complete();
}

void View::GetLitBatches(Drawable* drawable, LightBatchQueue& lightQueue)
{
    Light* light = lightQueue.light_;
    // Shadows on transparencies can only be rendered if shadow maps are not reused
    bool allowTransparentShadows = !renderer_->GetReuseShadowMaps();
    bool hasVertexLights = drawable->GetVertexLights().Size() > 0;
    bool prepass = renderer_->GetLightPrepass();
    unsigned numBatches = drawable->GetNumBatches();
    
    for (unsigned i = 0; i < numBatches; ++i)
    {
        Batch litBatch;
        drawable->GetBatch(litBatch, frame_, i);
        
        Technique* tech = GetTechnique(drawable, litBatch.material_);
        if (!litBatch.geometry_ || !tech)
            continue;
        
        // Do not create pixel lit forward passes for materials that render into the G-buffer
        if (prepass && tech->HasPass(PASS_GBUFFER))
            continue;
        
        Pass* pass = tech->GetPass(PASS_LIGHT);
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

void View::RenderBatchesForward()
{
    // Reset the light optimization stencil reference value
    lightStencilValue_ = 1;
    
    // If not reusing shadowmaps, render all of them first
    if (!renderer_->GetReuseShadowMaps() && renderer_->GetDrawShadows() && !lightQueues_.Empty())
    {
        PROFILE(RenderShadowMaps);
        
        for (List<LightBatchQueue>::Iterator i = lightQueues_.Begin(); i != lightQueues_.End(); ++i)
        {
            if (i->shadowMap_)
                RenderShadowMap(*i);
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
        // Render shadow maps + opaque objects' additive lighting
        PROFILE(RenderLights);
        
        for (List<LightBatchQueue>::Iterator i = lightQueues_.Begin(); i != lightQueues_.End(); ++i)
        {
            // If reusing shadowmaps, render each of them before the lit batches
            if (renderer_->GetReuseShadowMaps() && i->shadowMap_)
            {
                RenderShadowMap(*i);
                graphics_->SetRenderTarget(0, renderTarget_);
                graphics_->SetDepthStencil(depthStencil_);
                graphics_->SetViewport(screenRect_);
            }
            
            RenderLightBatchQueue(i->litBatches_, i->light_);
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

void View::RenderBatchesLightPrepass()
{
    // If not reusing shadowmaps, render all of them first
    if (!renderer_->GetReuseShadowMaps() && renderer_->GetDrawShadows() && !lightQueues_.Empty())
    {
        PROFILE(RenderShadowMaps);
        
        for (List<LightBatchQueue>::Iterator i = lightQueues_.Begin(); i != lightQueues_.End(); ++i)
        {
            if (i->shadowMap_)
                RenderShadowMap(*i);
        }
    }
    
    Texture2D* normalBuffer = renderer_->GetNormalBuffer();
    Texture2D* depthBuffer = renderer_->GetDepthBuffer();
    RenderSurface* depthStencil = 0;
    
    // Hardware depth support: render to RGBA normal buffer and read hardware depth
    if (graphics_->GetHardwareDepthSupport())
    {
        depthStencil = depthBuffer->GetRenderSurface();
        
        graphics_->SetRenderTarget(0, normalBuffer);
        graphics_->SetDepthStencil(depthStencil);
        graphics_->SetViewport(screenRect_);
        graphics_->Clear(CLEAR_DEPTH | CLEAR_STENCIL);
    }
    // No hardware depth support: render to R32F depth and RGBA normal buffers
    else
    {
        graphics_->SetRenderTarget(0, depthBuffer);
        graphics_->SetRenderTarget(1, normalBuffer);
        graphics_->SetDepthStencil(depthStencil);
        graphics_->SetViewport(screenRect_);
        graphics_->Clear(CLEAR_DEPTH | CLEAR_STENCIL);
    }
    
    if (!gbufferQueue_.IsEmpty())
    {
        // Render G-buffer batches
        PROFILE(RenderGBuffer);
        
        RenderBatchQueue(gbufferQueue_);
    }
    
    // Clear the light accumulation buffer
    Texture2D* lightBuffer = renderer_->GetLightBuffer();
    graphics_->ResetRenderTarget(1);
    graphics_->SetRenderTarget(0, lightBuffer);
    graphics_->SetDepthStencil(depthStencil);
    graphics_->SetViewport(screenRect_);
    graphics_->Clear(CLEAR_COLOR);
    
    if (!lightQueues_.Empty())
    {
        // Render shadow maps + light volumes
        PROFILE(RenderLights);
        
        for (List<LightBatchQueue>::Iterator i = lightQueues_.Begin(); i != lightQueues_.End(); ++i)
        {
            // If reusing shadowmaps, render each of them before the lit batches
            if (renderer_->GetReuseShadowMaps() && i->shadowMap_)
            {
                RenderShadowMap(*i);
                graphics_->SetRenderTarget(0, lightBuffer);
                graphics_->SetDepthStencil(depthStencil);
                graphics_->SetViewport(screenRect_);
            }
            
            graphics_->SetTexture(TU_DEPTHBUFFER, depthBuffer);
            graphics_->SetTexture(TU_NORMALBUFFER, normalBuffer);
            
            for (unsigned j = 0; j < i->volumeBatches_.Size(); ++j)
            {
                SetupLightVolumeBatch(i->volumeBatches_[j]);
                i->volumeBatches_[j].Draw(graphics_, renderer_);
            }
        }
    }
    
    // Clear destination render target with fog color
    graphics_->SetScissorTest(false);
    graphics_->SetStencilTest(false);
    graphics_->SetRenderTarget(0, renderTarget_);
    graphics_->SetDepthStencil(depthStencil);
    graphics_->SetViewport(screenRect_);
    graphics_->Clear(CLEAR_COLOR, farClipZone_->GetFogColor());
    
    if (!baseQueue_.IsEmpty())
    {
        // Render opaque objects with deferred lighting result
        PROFILE(RenderBase);
        
        graphics_->SetTexture(TU_LIGHTBUFFER, lightBuffer);
        
        RenderBatchQueue(baseQueue_);
    }
    
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
    
    for (PODVector<Drawable*>::Iterator i = occluders.Begin(); i != occluders.End();)
    {
        Drawable* occluder = *i;
        bool erase = false;
        
        if (!occluder->IsInView(frame_, false))
            occluder->UpdateDistance(frame_);
        
        // Check occluder's draw distance (in main camera view)
        float maxDistance = occluder->GetDrawDistance();
        if (maxDistance > 0.0f && occluder->GetDistance() > maxDistance)
            erase = true;
        else
        {
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
            else
            {
                // Store amount of triangles divided by screen size as a sorting key
                // (best occluders are big and have few triangles)
                occluder->SetSortValue((float)occluder->GetNumOccluderTriangles() / compare);
            }
        }
        
        if (erase)
            i = occluders.Erase(i);
        else
            ++i;
    }
    
    // Sort occluders so that if triangle budget is exceeded, best occluders have been drawn
    if (occluders.Size())
        Sort(occluders.Begin(), occluders.End(), CompareDrawables);
}

void View::DrawOccluders(OcclusionBuffer* buffer, const PODVector<Drawable*>& occluders)
{
    buffer->SetMaxTriangles(maxOccluderTriangles_);
    buffer->Clear();
    
    for (unsigned i = 0; i < occluders.Size(); ++i)
    {
        Drawable* occluder = occluders[i];
        if (i > 0)
        {
            // For subsequent occluders, do a test against the pixel-level occlusion buffer to see if rendering is necessary
            if (!buffer->IsVisible(occluder->GetWorldBoundingBox()))
                continue;
        }
        
        // Check for running out of triangles
        if (!occluder->DrawOcclusion(buffer))
            break;
    }
    
    buffer->BuildDepthHierarchy();
}

void View::ProcessLight(LightQueryResult& query, unsigned threadIndex)
{
    Light* light = query.light_;
    LightType type = light->GetLightType();
    
    // Check if light should be shadowed
    bool isShadowed = drawShadows_ && light->GetCastShadows() && !light->GetPerVertex() && light->GetShadowIntensity() < 1.0f;
    // If shadow distance non-zero, check it
    if (isShadowed && light->GetShadowDistance() > 0.0f && light->GetDistance() > light->GetShadowDistance())
        isShadowed = false;
    
    // Get lit geometries. They must match the light mask and be inside the main camera frustum to be considered
    PODVector<Drawable*>& tempDrawables = tempDrawables_[threadIndex];
    query.litGeometries_.Clear();
    
    switch (type)
    {
    case LIGHT_DIRECTIONAL:
        for (unsigned i = 0; i < geometries_.Size(); ++i)
        {
            if (GetLightMask(geometries_[i]) & light->GetLightMask())
                query.litGeometries_.Push(geometries_[i]);
        }
        break;
        
    case LIGHT_SPOT:
        {
            FrustumOctreeQuery octreeQuery(tempDrawables, light->GetFrustum(), DRAWABLE_GEOMETRY, camera_->GetViewMask());
            octree_->GetDrawables(octreeQuery);
            for (unsigned i = 0; i < tempDrawables.Size(); ++i)
            {
                if (tempDrawables[i]->IsInView(frame_) && (GetLightMask(tempDrawables[i]) & light->GetLightMask()))
                    query.litGeometries_.Push(tempDrawables[i]);
            }
        }
        break;
        
    case LIGHT_POINT:
        {
            SphereOctreeQuery octreeQuery(tempDrawables, Sphere(light->GetWorldPosition(), light->GetRange()),
                DRAWABLE_GEOMETRY, camera_->GetViewMask());
            octree_->GetDrawables(octreeQuery);
            for (unsigned i = 0; i < tempDrawables.Size(); ++i)
            {
                if (tempDrawables[i]->IsInView(frame_) && (GetLightMask(tempDrawables[i]) & light->GetLightMask()))
                    query.litGeometries_.Push(tempDrawables[i]);
            }
        }
        break;
    }
    
    // If no lit geometries or not shadowed, no need to process shadow cameras
    if (query.litGeometries_.Empty() || !isShadowed)
    {
        query.numSplits_ = 0;
        return;
    }
    
    // Determine number of shadow cameras and setup their initial positions
    SetupShadowCameras(query);
    
    // Process each split for shadow casters
    query.shadowCasters_.Clear();
    for (unsigned i = 0; i < query.numSplits_; ++i)
    {
        Camera* shadowCamera = query.shadowCameras_[i];
        Frustum shadowCameraFrustum = shadowCamera->GetFrustum();
        query.shadowCasterBegin_[i] = query.shadowCasterEnd_[i] = query.shadowCasters_.Size();
        
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
            if (sceneViewBox_.min_.z_ > query.shadowFarSplits_[i])
                continue;
            if (sceneViewBox_.max_.z_ < query.shadowNearSplits_[i])
                continue;
        }
        
        // For spot light (which has only one shadow split) we can optimize by reusing the query for
        // lit geometries, whose result still exists in tempDrawables
        if (type != LIGHT_SPOT)
        {
            FrustumOctreeQuery octreeQuery(tempDrawables, shadowCameraFrustum, DRAWABLE_GEOMETRY,
                camera_->GetViewMask(), true);
            octree_->GetDrawables(octreeQuery);
        }
        
        // Check which shadow casters actually contribute to the shadowing
        ProcessShadowCasters(query, tempDrawables, i);
    }
    
    // If no shadow casters, the light can be rendered unshadowed. At this point we have not allocated a shadow map yet, so the
    // only cost has been the shadow camera setup & queries
    if (query.shadowCasters_.Empty())
        query.numSplits_ = 0;
}

void View::ProcessShadowCasters(LightQueryResult& query, const PODVector<Drawable*>& drawables, unsigned splitIndex)
{
    Light* light = query.light_;
    Matrix3x4 lightView;
    Matrix4 lightProj;
    
    Camera* shadowCamera = query.shadowCameras_[splitIndex];
    lightView = shadowCamera->GetInverseWorldTransform();
    lightProj = shadowCamera->GetProjection();
    bool dirLight = shadowCamera->IsOrthographic();
    
    query.shadowCasterBox_[splitIndex].defined_ = false;
    
    // Transform scene frustum into shadow camera's view space for shadow caster visibility check. For point & spot lights,
    // we can use the whole scene frustum. For directional lights, use the intersection of the scene frustum and the split
    // frustum, so that shadow casters do not get rendered into unnecessary splits
    Frustum lightViewFrustum;
    if (!dirLight)
        lightViewFrustum = camera_->GetSplitFrustum(sceneViewBox_.min_.z_, sceneViewBox_.max_.z_).Transformed(lightView);
    else
        lightViewFrustum = camera_->GetSplitFrustum(Max(sceneViewBox_.min_.z_, query.shadowNearSplits_[splitIndex]),
            Min(sceneViewBox_.max_.z_, query.shadowFarSplits_[splitIndex])).Transformed(lightView);
    
    BoundingBox lightViewFrustumBox(lightViewFrustum);
     
    // Check for degenerate split frustum: in that case there is no need to get shadow casters
    if (lightViewFrustum.vertices_[0] == lightViewFrustum.vertices_[4])
        return;
    
    BoundingBox lightViewBox;
    BoundingBox lightProjBox;
    
    for (PODVector<Drawable*>::ConstIterator i = drawables.Begin(); i != drawables.End(); ++i)
    {
        Drawable* drawable = *i;
        // In case this is a spot light query result reused for optimization, we may have non-shadowcasters included.
        // Check for that first
        if (!drawable->GetCastShadows())
            continue;
        
        // Note: as lights are processed threaded, it is possible a drawable's UpdateDistance() function is called several
        // times. However, this should not cause problems as no scene modification happens at this point.
        if (!drawable->IsInView(frame_, false))
            drawable->UpdateDistance(frame_);
        
        // Check shadow distance
        float maxShadowDistance = drawable->GetShadowDistance();
        if (maxShadowDistance > 0.0f && drawable->GetDistance() > maxShadowDistance)
            continue;
        
        // Check shadow mask
        if (!(GetShadowMask(drawable) & light->GetLightMask()))
            continue;
        
        // Project shadow caster bounding box to light view space for visibility check
        lightViewBox = drawable->GetWorldBoundingBox().Transformed(lightView);
        
        if (IsShadowCasterVisible(drawable, lightViewBox, shadowCamera, lightView, lightViewFrustum, lightViewFrustumBox))
        {
            // Merge to shadow caster bounding box and add to the list
            if (dirLight)
                query.shadowCasterBox_[splitIndex].Merge(lightViewBox);
            else
            {
                lightProjBox = lightViewBox.Projected(lightProj);
                query.shadowCasterBox_[splitIndex].Merge(lightProjBox);
            }
            query.shadowCasters_.Push(drawable);
        }
    }
    
    query.shadowCasterEnd_[splitIndex] = query.shadowCasters_.Size();
}

bool View::IsShadowCasterVisible(Drawable* drawable, BoundingBox lightViewBox, Camera* shadowCamera, const Matrix3x4& lightView,
    const Frustum& lightViewFrustum, const BoundingBox& lightViewFrustumBox)
{
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
    // Due to instruction count limits, light prepass in SM2.0 can only support up to 3 cascades
    if (renderer_->GetLightPrepass() && !graphics_->GetSM3Support())
        maxCascades = Max(maxCascades, 3);
    
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
    if (light && light->GetLightType() != LIGHT_DIRECTIONAL)
        graphics_->SetScissorTest(true, GetLightScissor(light));
    else
        graphics_->SetScissorTest(false);
}

void View::OptimizeLightByStencil(Light* light)
{
    if (light)
    {
        LightType type = light->GetLightType();
        if (type == LIGHT_DIRECTIONAL)
        {
            graphics_->SetStencilTest(false);
            return;
        }
        
        Geometry* geometry = renderer_->GetLightGeometry(light);
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
        graphics_->SetShaderParameter(VSP_MODEL, light->GetVolumeTransform(camera_));
        
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

void View::SetupShadowCameras(LightQueryResult& query)
{
    Light* light = query.light_;
    
    LightType type = light->GetLightType();
    int splits = 0;
    
    if (type == LIGHT_DIRECTIONAL)
    {
        const CascadeParameters& cascade = light->GetShadowCascade();
        
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
            Camera* shadowCamera = renderer_->GetShadowCamera();
            query.shadowCameras_[splits] = shadowCamera;
            query.shadowNearSplits_[splits] = nearSplit;
            query.shadowFarSplits_[splits] = farSplit;
            SetupDirLightShadowCamera(shadowCamera, light, nearSplit, farSplit);
            
            nearSplit = farSplit;
            ++splits;
        }
    }
    
    if (type == LIGHT_SPOT)
    {
        Camera* shadowCamera = renderer_->GetShadowCamera();
        query.shadowCameras_[0] = shadowCamera;
        Node* cameraNode = shadowCamera->GetNode();
        
        cameraNode->SetTransform(light->GetWorldPosition(), light->GetWorldRotation());
        shadowCamera->SetNearClip(light->GetShadowNearFarRatio() * light->GetRange());
        shadowCamera->SetFarClip(light->GetRange());
        shadowCamera->SetFov(light->GetFov());
        shadowCamera->SetAspectRatio(light->GetAspectRatio());
        
        splits = 1;
    }
    
    if (type == LIGHT_POINT)
    {
        for (unsigned i = 0; i < MAX_CUBEMAP_FACES; ++i)
        {
            Camera* shadowCamera = renderer_->GetShadowCamera();
            query.shadowCameras_[i] = shadowCamera;
            Node* cameraNode = shadowCamera->GetNode();
            
            // When making a shadowed point light, align the splits along X, Y and Z axes regardless of light rotation
            cameraNode->SetPosition(light->GetWorldPosition());
            cameraNode->SetDirection(directions[i]);
            shadowCamera->SetNearClip(light->GetShadowNearFarRatio() * light->GetRange());
            shadowCamera->SetFarClip(light->GetRange());
            shadowCamera->SetFov(90.0f);
            shadowCamera->SetAspectRatio(1.0f);
        }
        
        splits = MAX_CUBEMAP_FACES;
    }
    
    query.numSplits_ = splits;
}

void View::SetupDirLightShadowCamera(Camera* shadowCamera, Light* light, float nearSplit, float farSplit)
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
    if (parameters.focus_)
    {
        nearSplit = Max(sceneViewBox_.min_.z_, nearSplit);
        farSplit = Min(sceneViewBox_.max_.z_, farSplit);
    }
    
    Frustum splitFrustum = camera_->GetSplitFrustum(nearSplit, farSplit);
    frustumVolume_.Define(splitFrustum);
    // If focusing enabled, clip the frustum volume by the combined bounding box of the lit geometries within the frustum
    if (parameters.focus_)
    {
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
    if (!parameters.nonUniform_)
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

void View::FindZone(Drawable* drawable, unsigned threadIndex)
{
    Vector3 center = drawable->GetWorldBoundingBox().Center();
    int bestPriority = M_MIN_INT;
    Zone* newZone = 0;
    
    // If bounding box center is in view, can use the visible zones. Else must query via the octree
    if (frustum_.IsInside(center))
    {
        // First check if the last zone remains a conclusive result
        Zone* lastZone = drawable->GetLastZone();
        if (lastZone && lastZone->IsInside(center) && (drawable->GetZoneMask() & lastZone->GetZoneMask()) &&
            lastZone->GetPriority() >= highestZonePriority_)
            newZone = lastZone;
        else
        {
            for (PODVector<Zone*>::Iterator i = zones_.Begin(); i != zones_.End(); ++i)
            {
                int priority = (*i)->GetPriority();
                if ((*i)->IsInside(center) && (drawable->GetZoneMask() & (*i)->GetZoneMask()) && priority > bestPriority)
                {
                    newZone = *i;
                    bestPriority = priority;
                }
            }
        }
    }
    else
    {
        PODVector<Zone*>& tempZones = tempZones_[threadIndex];
        PointOctreeQuery query(reinterpret_cast<PODVector<Drawable*>&>(tempZones), center, DRAWABLE_ZONE);
        octree_->GetDrawables(query);
        
        bestPriority = M_MIN_INT;
        for (PODVector<Zone*>::Iterator i = tempZones.Begin(); i != tempZones.End(); ++i)
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

unsigned View::GetShadowMask(Drawable* drawable)
{
    return drawable->GetShadowMask() & GetZone(drawable)->GetShadowMask();
}

unsigned long long View::GetVertexLightQueueHash(const PODVector<Light*>& vertexLights)
{
    unsigned long long hash = 0;
    for (PODVector<Light*>::ConstIterator i = vertexLights.Begin(); i != vertexLights.End(); ++i)
        hash += (unsigned long long)(*i);
    return hash;
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

void View::PrepareInstancingBuffer()
{
    PROFILE(PrepareInstancingBuffer);
    
    unsigned totalInstances = 0;
    bool prepass = renderer_->GetLightPrepass();
    
    totalInstances += baseQueue_.GetNumInstances(renderer_);
    totalInstances += preAlphaQueue_.GetNumInstances(renderer_);
    if (prepass)
        totalInstances += gbufferQueue_.GetNumInstances(renderer_);
    
    for (List<LightBatchQueue>::Iterator i = lightQueues_.Begin(); i != lightQueues_.End(); ++i)
    {
        for (unsigned j = 0; j < i->shadowSplits_.Size(); ++j)
            totalInstances += i->shadowSplits_[j].shadowBatches_.GetNumInstances(renderer_);
        totalInstances += i->litBatches_.GetNumInstances(renderer_);
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
            if (prepass)
                gbufferQueue_.SetTransforms(renderer_, lockedData, freeIndex);
            
            for (List<LightBatchQueue>::Iterator i = lightQueues_.Begin(); i != lightQueues_.End(); ++i)
            {
                for (unsigned j = 0; j < i->shadowSplits_.Size(); ++j)
                    i->shadowSplits_[j].shadowBatches_.SetTransforms(renderer_, lockedData, freeIndex);
                i->litBatches_.SetTransforms(renderer_, lockedData, freeIndex);
            }
            
            instancingBuffer->Unlock();
        }
    }
}

void View::SetupLightVolumeBatch(Batch& batch)
{
    Light* light = batch.lightQueue_->light_;
    LightType type = light->GetLightType();
    float lightDist;
    
    graphics_->SetAlphaTest(false);
    graphics_->SetBlendMode(BLEND_ADD);
    graphics_->SetDepthWrite(false);
    
    if (type != LIGHT_DIRECTIONAL)
    {
        if (type == LIGHT_POINT)
            lightDist = Sphere(light->GetWorldPosition(), light->GetRange() * 1.25f).DistanceFast(camera_->GetWorldPosition());
        else
            lightDist = light->GetFrustum().Distance(camera_->GetWorldPosition());
        
        // Draw front faces if not inside light volume
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
    }
    else
    {
        graphics_->SetCullMode(CULL_NONE);
        graphics_->SetDepthTest(CMP_ALWAYS);
    }
    
    graphics_->SetScissorTest(false);
    graphics_->SetStencilTest(true, CMP_LESS, OP_KEEP, OP_KEEP, OP_KEEP, 0, light->GetLightMask());
}

void View::DrawFullscreenQuad(Camera* camera, bool nearQuad)
{
    Light quadDirLight(context_);
    quadDirLight.SetLightType(LIGHT_DIRECTIONAL);
    Matrix3x4 model(quadDirLight.GetDirLightTransform(camera, nearQuad));
    
    graphics_->SetCullMode(CULL_NONE);
    graphics_->SetShaderParameter(VSP_MODEL, model);
    graphics_->SetShaderParameter(VSP_VIEWPROJ, camera->GetProjection());
    graphics_->ClearTransformSources();
    
    renderer_->GetLightGeometry(&quadDirLight)->Draw(graphics_);
}

void View::RenderBatchQueue(const BatchQueue& queue, bool useScissor)
{
    graphics_->SetScissorTest(false);
    
    // During G-buffer rendering, mark opaque pixels to stencil buffer
    bool isGBuffer = &queue == &gbufferQueue_;
    if (!isGBuffer)
        graphics_->SetStencilTest(false);
    
    // Base instanced
    for (PODVector<BatchGroup*>::ConstIterator i = queue.sortedBaseBatchGroups_.Begin(); i !=
        queue.sortedBaseBatchGroups_.End(); ++i)
    {
        BatchGroup* group = *i;
        if (isGBuffer)
            graphics_->SetStencilTest(true, CMP_ALWAYS, OP_REF, OP_KEEP, OP_KEEP, group->lightMask_);
        
        group->Draw(graphics_, renderer_);
    }
    // Base non-instanced
    for (PODVector<Batch*>::ConstIterator i = queue.sortedBaseBatches_.Begin(); i != queue.sortedBaseBatches_.End(); ++i)
    {
        Batch* batch = *i;
        if (isGBuffer)
            graphics_->SetStencilTest(true, CMP_ALWAYS, OP_REF, OP_KEEP, OP_KEEP, batch->lightMask_);
        
        batch->Draw(graphics_, renderer_);
    }
    
    // Non-base instanced
    for (PODVector<BatchGroup*>::ConstIterator i = queue.sortedBatchGroups_.Begin(); i != queue.sortedBatchGroups_.End(); ++i)
    {
        BatchGroup* group = *i;
        if (useScissor && group->lightQueue_)
            OptimizeLightByScissor(group->lightQueue_->light_);
        if (isGBuffer)
            graphics_->SetStencilTest(true, CMP_ALWAYS, OP_REF, OP_KEEP, OP_KEEP, group->lightMask_);
        
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
        if (isGBuffer)
            graphics_->SetStencilTest(true, CMP_ALWAYS, OP_REF, OP_KEEP, OP_KEEP, batch->lightMask_);
        
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
