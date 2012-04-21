//
// Urho3D Engine
// Copyright (c) 2008-2012 Lasse Öörni
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
#include "ResourceCache.h"
#include "PostProcess.h"
#include "Profiler.h"
#include "Scene.h"
#include "ShaderVariation.h"
#include "Skybox.h"
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
static const float LIGHT_INTENSITY_THRESHOLD = 0.001f;

/// %Frustum octree query for shadowcasters.
class ShadowCasterOctreeQuery : public OctreeQuery
{
public:
    /// Construct with frustum and query parameters.
    ShadowCasterOctreeQuery(PODVector<Drawable*>& result, const Frustum& frustum, unsigned char drawableFlags = DRAWABLE_ANY,
        unsigned viewMask = DEFAULT_VIEWMASK) :
        OctreeQuery(result, drawableFlags, viewMask),
        frustum_(frustum)
    {
    }
    
    /// Intersection test for an octant.
    virtual Intersection TestOctant(const BoundingBox& box, bool inside)
    {
        if (inside)
            return INSIDE;
        else
            return frustum_.IsInside(box);
    }
    
    /// Intersection test for drawables.
    virtual void TestDrawables(const PODVector<Drawable*>& drawables, bool inside)
    {
        for (PODVector<Drawable*>::ConstIterator i = drawables.Begin(); i != drawables.End(); ++i)
        {
            Drawable* drawable = *i;
            
            if ((drawable->GetDrawableFlags() & drawableFlags_) && drawable->GetCastShadows() && drawable->IsVisible() &&
                (drawable->GetViewMask() & viewMask_))
            {
                if (inside || frustum_.IsInsideFast(drawable->GetWorldBoundingBox()))
                    result_.Push(drawable);
            }
        }
    }
    
    /// Frustum.
    Frustum frustum_;
};

/// %Frustum octree query for zones and occluders.
class ZoneOccluderOctreeQuery : public OctreeQuery
{
public:
    /// Construct with frustum and query parameters.
    ZoneOccluderOctreeQuery(PODVector<Drawable*>& result, const Frustum& frustum, unsigned char drawableFlags = DRAWABLE_ANY,
        unsigned viewMask = DEFAULT_VIEWMASK) :
        OctreeQuery(result, drawableFlags, viewMask),
        frustum_(frustum)
    {
    }
    
    /// Intersection test for an octant.
    virtual Intersection TestOctant(const BoundingBox& box, bool inside)
    {
        if (inside)
            return INSIDE;
        else
            return frustum_.IsInside(box);
    }
    
    /// Intersection test for drawables.
    virtual void TestDrawables(const PODVector<Drawable*>& drawables, bool inside)
    {
        for (PODVector<Drawable*>::ConstIterator i = drawables.Begin(); i != drawables.End(); ++i)
        {
            Drawable* drawable = *i;
            unsigned char flags = drawable->GetDrawableFlags();
            
            if ((flags == DRAWABLE_ZONE || (flags == DRAWABLE_GEOMETRY && drawable->IsOccluder())) && drawable->IsVisible() &&
                (drawable->GetViewMask() & viewMask_))
            {
                if (inside || frustum_.IsInsideFast(drawable->GetWorldBoundingBox()))
                    result_.Push(drawable);
            }
        }
    }
    
    /// Frustum.
    Frustum frustum_;
};

/// %Frustum octree query with occlusion.
class OccludedFrustumOctreeQuery : public OctreeQuery
{
public:
    /// Construct with frustum, occlusion buffer and query parameters.
    OccludedFrustumOctreeQuery(PODVector<Drawable*>& result, const Frustum& frustum, OcclusionBuffer* buffer, unsigned char
        drawableFlags = DRAWABLE_ANY, unsigned viewMask = DEFAULT_VIEWMASK) :
        OctreeQuery(result, drawableFlags, viewMask),
        frustum_(frustum),
        buffer_(buffer)
    {
    }
    
    /// Intersection test for an octant.
    virtual Intersection TestOctant(const BoundingBox& box, bool inside)
    {
        if (inside)
            return buffer_->IsVisible(box) ? INSIDE : OUTSIDE;
        else
        {
            Intersection result = frustum_.IsInside(box);
            if (result != OUTSIDE && !buffer_->IsVisible(box))
                result = OUTSIDE;
            return result;
        }
    }
    
    /// Intersection test for drawables. Note: drawable occlusion is performed later in worker threads.
    virtual void TestDrawables(const PODVector<Drawable*>& drawables, bool inside)
    {
        for (PODVector<Drawable*>::ConstIterator i = drawables.Begin(); i != drawables.End(); ++i)
        {
            Drawable* drawable = *i;
        
            if ((drawable->GetDrawableFlags() & drawableFlags_) && drawable->IsVisible() && (drawable->GetViewMask() & viewMask_))
            {
                if (inside || frustum_.IsInsideFast(drawable->GetWorldBoundingBox()))
                    result_.Push(drawable);
            }
        }
    }
    
    /// Frustum.
    Frustum frustum_;
    /// Occlusion buffer.
    OcclusionBuffer* buffer_;
};

void CheckVisibilityWork(const WorkItem* item, unsigned threadIndex)
{
    View* view = reinterpret_cast<View*>(item->aux_);
    Drawable** start = reinterpret_cast<Drawable**>(item->start_);
    Drawable** end = reinterpret_cast<Drawable**>(item->end_);
    OcclusionBuffer* buffer = view->occlusionBuffer_;
    
    while (start != end)
    {
        Drawable* drawable = *start;
        unsigned char flags = drawable->GetDrawableFlags();
        ++start;
        
        if (flags & DRAWABLE_ZONE)
            continue;
        
        drawable->UpdateDistance(view->frame_);
        
        // If draw distance non-zero, check it
        float maxDistance = drawable->GetDrawDistance();
        if (maxDistance > 0.0f && drawable->GetDistance() > maxDistance)
            continue;
        
        if (buffer && drawable->IsOccludee() && !buffer->IsVisible(drawable->GetWorldBoundingBox()))
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

void ProcessShadowSplitWork(const WorkItem* item, unsigned threadIndex)
{
    View* view = reinterpret_cast<View*>(item->aux_);
    LightQueryResult* query = reinterpret_cast<LightQueryResult*>(item->start_);
    unsigned splitIndex = reinterpret_cast<unsigned>(item->end_);
    
    view->ProcessShadowSplit(*query, splitIndex, threadIndex);
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
    renderTarget_(0)
{
    frame_.camera_ = 0;
    
    // Create octree query vectors for each thread
    tempDrawables_.Resize(GetSubsystem<WorkQueue>()->GetNumThreads() + 1);
    tempZones_.Resize(GetSubsystem<WorkQueue>()->GetNumThreads() + 1);
}

View::~View()
{
}

bool View::Define(RenderSurface* renderTarget, Viewport* viewport)
{
    Scene* scene = viewport->GetScene();
    Camera* camera = viewport->GetCamera();
    if (!scene || !camera)
        return false;
    
    // If scene is loading asynchronously, it is incomplete and should not be rendered
    if (scene->IsAsyncLoading())
        return false;
    
    Octree* octree = scene->GetComponent<Octree>();
    if (!octree)
        return false;
    
    renderMode_ = renderer_->GetRenderMode();
    octree_ = octree;
    camera_ = camera;
    renderTarget_ = renderTarget;
    
    // Get active post-processing effects on the viewport
    const Vector<SharedPtr<PostProcess> >& postProcesses = viewport->GetPostProcesses();
    postProcesses_.Clear();
    for (Vector<SharedPtr<PostProcess> >::ConstIterator i = postProcesses.Begin(); i != postProcesses.End(); ++i)
    {
        PostProcess* effect = i->Get();
        if (effect && effect->IsActive())
            postProcesses_.Push(*i);
    }
    
    // Validate the rect and calculate size. If zero rect, use whole rendertarget size
    int rtWidth = renderTarget ? renderTarget->GetWidth() : graphics_->GetWidth();
    int rtHeight = renderTarget ? renderTarget->GetHeight() : graphics_->GetHeight();
    const IntRect& rect = viewport->GetRect();
    
    if (rect != IntRect::ZERO)
    {
        viewRect_.left_ = Clamp(rect.left_, 0, rtWidth - 1);
        viewRect_.top_ = Clamp(rect.top_, 0, rtHeight - 1);
        viewRect_.right_ = Clamp(rect.right_, viewRect_.left_ + 1, rtWidth);
        viewRect_.bottom_ = Clamp(rect.bottom_, viewRect_.top_ + 1, rtHeight);
    }
    else
        viewRect_ = IntRect(0, 0, rtWidth, rtHeight);
    
    viewSize_ = IntVector2(viewRect_.right_ - viewRect_.left_, viewRect_.bottom_ - viewRect_.top_);
    rtSize_ = IntVector2(rtWidth, rtHeight);
    
    // On OpenGL flip the viewport if rendering to a texture for consistent UV addressing with Direct3D9
    #ifdef USE_OPENGL
    if (renderTarget_)
    {
        viewRect_.bottom_ = rtSize_.y_ - viewRect_.top_;
        viewRect_.top_ = viewRect_.bottom_ - viewSize_.y_;
    }
    #endif
    
    drawShadows_ = renderer_->GetDrawShadows();
    materialQuality_ = renderer_->GetMaterialQuality();
    maxOccluderTriangles_ = renderer_->GetMaxOccluderTriangles();
    
    // Set possible quality overrides from the camera
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
    frame_.viewSize_ = viewSize_;
    
    // Clear screen buffers, geometry, light, occluder & batch lists
    screenBuffers_.Clear();
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
    
    GetDrawables();
    GetBatches();
    UpdateGeometries();
}

void View::Render()
{
    if (!octree_ || !camera_)
        return;
    
    // Allocate screen buffers for post-processing and blitting as necessary
    AllocateScreenBuffers();
    
    // Forget parameter sources from the previous view
    graphics_->ClearParameterSources();
    
    // If stream offset is supported, write all instance transforms to a single large buffer
    // Else we must lock the instance buffer for each batch group
    if (renderer_->GetDynamicInstancing() && graphics_->GetStreamOffsetSupport())
        PrepareInstancingBuffer();
    
    // It is possible, though not recommended, that the same camera is used for multiple main views. Set automatic aspect ratio
    // again to ensure correct projection will be used
    if (camera_->GetAutoAspectRatio())
        camera_->SetAspectRatio((float)(viewSize_.x_) / (float)(viewSize_.y_));
    
    graphics_->SetColorWrite(true);
    graphics_->SetFillMode(FILL_SOLID);
    
    // Bind the face selection and indirection cube maps for point light shadows
    graphics_->SetTexture(TU_FACESELECT, renderer_->GetFaceSelectCubeMap());
    graphics_->SetTexture(TU_INDIRECTION, renderer_->GetIndirectionCubeMap());
    
    // Set "view texture" to prevent destination texture sampling in case we do not render to the destination directly
    // ie. when using deferred rendering and/or doing post-processing
    if (renderTarget_)
        graphics_->SetViewTexture(renderTarget_->GetParentTexture());
    
    // On OpenGL, flip the projection if rendering to a texture so that the texture can be addressed in the same way
    // as a render texture produced on Direct3D9
    #ifdef USE_OPENGL
    if (renderTarget_)
        camera_->SetFlipVertical(true);
    #endif
    
    // Render
    if (renderMode_ == RENDER_FORWARD)
        RenderBatchesForward();
    else
        RenderBatchesDeferred();
    
    #ifdef USE_OPENGL
    camera_->SetFlipVertical(false);
    #endif
    
    graphics_->SetViewTexture(0);
    graphics_->SetScissorTest(false);
    graphics_->SetStencilTest(false);
    graphics_->ResetStreamFrequencies();
    
    // Run post-processes or framebuffer blitting now
    if (screenBuffers_.Size())
    {
        if (postProcesses_.Size())
            RunPostProcesses();
        else
            BlitFramebuffer();
    }
    
    // If this is a main view, draw the associated debug geometry now
    if (!renderTarget_)
    {
        DebugRenderer* debug = octree_->GetComponent<DebugRenderer>();
        if (debug)
        {
            debug->SetView(camera_);
            debug->Render();
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
    
    // Get zones and occluders first
    {
        ZoneOccluderOctreeQuery query(tempDrawables, camera_->GetFrustum(), DRAWABLE_GEOMETRY | DRAWABLE_ZONE);
        octree_->GetDrawables(query);
    }
    
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
        else
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
    
    // Get lights and geometries. Coarse occlusion for octants is used at this point
    if (occlusionBuffer_)
    {
        OccludedFrustumOctreeQuery query(tempDrawables, camera_->GetFrustum(), occlusionBuffer_, DRAWABLE_GEOMETRY |
            DRAWABLE_LIGHT);
        octree_->GetDrawables(query);
    }
    else
    {
        FrustumOctreeQuery query(tempDrawables, camera_->GetFrustum(), DRAWABLE_GEOMETRY | DRAWABLE_LIGHT);
        octree_->GetDrawables(query);
    }
    
    // Check drawable occlusion and find zones for moved drawables in worker threads
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
            // Expand the scene bounding boxes. However, do not take skyboxes into account, as they have undefinedly large size
            // and the bounding boxes are also used for shadow focusing
            const BoundingBox& geomBox = drawable->GetWorldBoundingBox();
            BoundingBox geomViewBox = geomBox.Transformed(view);
            if (drawable->GetType() != Skybox::GetTypeStatic())
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
            // Skip lights which are so dim that they can not contribute to a rendertarget
            if (light->GetColor().Intensity() > LIGHT_INTENSITY_THRESHOLD)
                lights_.Push(light);
        }
    }
    
    sceneFrustum_ = camera_->GetSplitFrustum(sceneViewBox_.min_.z_, sceneViewBox_.max_.z_);
    
    // Sort the lights to brightest/closest first
    for (unsigned i = 0; i < lights_.Size(); ++i)
    {
        Light* light = lights_[i];
        light->SetIntensitySortValue(camera_->GetDistance(light->GetWorldPosition()));
        light->SetLightQueue(0);
    }
    
    Sort(lights_.Begin(), lights_.End(), CompareDrawables);
}

void View::GetBatches()
{
    WorkQueue* queue = GetSubsystem<WorkQueue>();
    PODVector<Light*> vertexLights;
    
    // Process lit geometries and shadow casters for each light
    {
        PROFILE(ProcessLights);
        
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
        PROFILE(GetLightBatches);
        
        maxLightsDrawables_.Clear();
        
        // Preallocate light queues: per-pixel lights which have lit geometries
        unsigned numLightQueues = 0;
        unsigned usedLightQueues = 0;
        for (Vector<LightQueryResult>::ConstIterator i = lightQueryResults_.Begin(); i != lightQueryResults_.End(); ++i)
        {
            if (!i->light_->GetPerVertex() && i->litGeometries_.Size())
                ++numLightQueues;
        }
        
        lightQueues_.Resize(numLightQueues);
        
        for (Vector<LightQueryResult>::Iterator i = lightQueryResults_.Begin(); i != lightQueryResults_.End(); ++i)
        {
            LightQueryResult& query = *i;
            
            // If light has no affected geometries, no need to process further
            if (query.litGeometries_.Empty())
                continue;
            
            // If no shadow casters, the light can be rendered unshadowed. At this point we have not allocated a shadow map yet,
            // so the only cost has been the shadow camera setup & queries
            unsigned shadowSplits = query.shadowSplits_.Size();
            if (shadowSplits)
            {
                unsigned totalShadowCasters = 0;
                for (unsigned i = 0; i < query.shadowSplits_.Size(); ++i)
                    totalShadowCasters += query.shadowSplits_[i].shadowCasters_.Size();
                if (!totalShadowCasters)
                    shadowSplits = 0;
            }
            
            Light* light = query.light_;
            
            // Per-pixel light
            if (!light->GetPerVertex())
            {
                // Initialize light queue
                LightBatchQueue& lightQueue = lightQueues_[usedLightQueues++];
                light->SetLightQueue(&lightQueue);
                lightQueue.light_ = light;
                lightQueue.litBatches_.Clear();
                lightQueue.volumeBatches_.Clear();
                
                // Allocate shadow map now
                lightQueue.shadowMap_ = 0;
                if (shadowSplits > 0)
                {
                    lightQueue.shadowMap_ = renderer_->GetShadowMap(light, camera_, viewSize_.x_, viewSize_.y_);
                    // If did not manage to get a shadow map, convert the light to unshadowed
                    if (!lightQueue.shadowMap_)
                        shadowSplits = 0;
                }
                
                // Setup shadow batch queues
                lightQueue.shadowSplits_.Resize(shadowSplits);
                for (unsigned j = 0; j < shadowSplits; ++j)
                {
                    ShadowQueryResult& split = query.shadowSplits_[j];
                    ShadowBatchQueue& shadowQueue = lightQueue.shadowSplits_[j];
                    Camera* shadowCamera = split.shadowCamera_;
                    shadowQueue.shadowCamera_ = shadowCamera;
                    shadowQueue.nearSplit_ = split.shadowNearSplit_;
                    shadowQueue.farSplit_ = split.shadowFarSplit_;
                    
                    // Setup the shadow split viewport and finalize shadow camera parameters
                    shadowQueue.shadowViewport_ = GetShadowMapViewport(light, j, lightQueue.shadowMap_);
                    FinalizeShadowCamera(shadowCamera, light, shadowQueue.shadowViewport_, split.shadowCasterBox_);
                    
                    // Loop through shadow casters
                    for (PODVector<Drawable*>::ConstIterator k = split.shadowCasters_.Begin(); k != split.shadowCasters_.End();
                        ++k)
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
                
                // In deferred modes, store the light volume batch now
                if (renderMode_ != RENDER_FORWARD)
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
                LightBatchQueue* queue = light->GetLightQueue();
                if (queue)
                    GetLitBatches(drawable, *queue);
            }
        }
    }
    
    // Build base pass batches
    {
        PROFILE(GetBaseBatches);
        
        hasZeroLightMask_ = false;
        
        for (PODVector<Drawable*>::ConstIterator i = geometries_.Begin(); i != geometries_.End(); ++i)
        {
            Drawable* drawable = *i;
            unsigned numBatches = drawable->GetNumBatches();
            const PODVector<Light*>& drawableVertexLights = drawable->GetVertexLights();
            if (!drawableVertexLights.Empty())
                drawable->LimitVertexLights();
            
            for (unsigned j = 0; j < numBatches; ++j)
            {
                Batch baseBatch;
                drawable->GetBatch(baseBatch, frame_, j);
                
                Technique* tech = GetTechnique(drawable, baseBatch.material_);
                if (!baseBatch.geometry_ || !tech)
                    continue;
                
                // Check here if the material technique refers to a rendertarget texture with camera(s) attached
                // Only check this for the main view (null rendertarget)
                if (!renderTarget_ && baseBatch.material_ && baseBatch.material_->GetAuxViewFrameNumber() != frame_.frameNumber_)
                    CheckMaterialForAuxView(baseBatch.material_);
                
                // Fill the rest of the batch
                baseBatch.camera_ = camera_;
                baseBatch.zone_ = GetZone(drawable);
                baseBatch.isBase_ = true;
                
                Pass* pass = 0;
                
                // In deferred modes check for G-buffer and material passes first
                if (renderMode_ == RENDER_PREPASS)
                {
                    pass = tech->GetPass(PASS_PREPASS);
                    if (pass)
                    {
                        // If the opaque object has a zero lightmask, have to skip light buffer optimization
                        if (!hasZeroLightMask_ && (!(GetLightMask(drawable) & 0xff)))
                            hasZeroLightMask_ = true;
                        
                        // Allow G-buffer pass instancing only if lightmask matches zone lightmask
                        baseBatch.lightMask_ = GetLightMask(drawable);
                        FinalizeBatch(baseBatch, tech, pass, baseBatch.lightMask_ == (baseBatch.zone_->GetLightMask() & 0xff));
                        gbufferQueue_.AddBatch(baseBatch);
                        
                        pass = tech->GetPass(PASS_MATERIAL);
                    }
                }
                
                if (renderMode_ == RENDER_DEFERRED)
                    pass = tech->GetPass(PASS_DEFERRED);
                
                // Next check for forward base pass
                if (!pass)
                {
                    // Skip if a lit base pass already exists
                    if (j < 32 && drawable->HasBasePass(j))
                        continue;
                    pass = tech->GetPass(PASS_BASE);
                }
                
                if (pass)
                {
                    // Check for vertex lights (both forward unlit, light pre-pass material pass, and deferred G-buffer)
                    if (!drawableVertexLights.Empty())
                    {
                        // For a deferred opaque batch, check if the vertex lights include converted per-pixel lights, and remove
                        // them to prevent double-lighting
                        if (renderMode_ != RENDER_FORWARD && pass->GetBlendMode() == BLEND_REPLACE)
                        {
                            vertexLights.Clear();
                            for (unsigned i = 0; i < drawableVertexLights.Size(); ++i)
                            {
                                if (drawableVertexLights[i]->GetPerVertex())
                                    vertexLights.Push(drawableVertexLights[i]);
                            }
                        }
                        else
                            vertexLights = drawableVertexLights;
                        
                        if (!vertexLights.Empty())
                        {
                            // Find a vertex light queue. If not found, create new
                            unsigned long long hash = GetVertexLightQueueHash(vertexLights);
                            HashMap<unsigned long long, LightBatchQueue>::Iterator i = vertexLightQueues_.Find(hash);
                            if (i == vertexLightQueues_.End())
                            {
                                i = vertexLightQueues_.Insert(MakePair(hash, LightBatchQueue()));
                                i->second_.light_ = 0;
                                i->second_.shadowMap_ = 0;
                                i->second_.vertexLights_ = vertexLights;
                            }
                            
                            baseBatch.lightQueue_ = &(i->second_);
                        }
                    }
                    
                    if (pass->GetBlendMode() == BLEND_REPLACE)
                    {
                        if (pass->GetType() != PASS_DEFERRED)
                        {
                            FinalizeBatch(baseBatch, tech, pass);
                            baseQueue_.AddBatch(baseBatch);
                        }
                        else
                        {
                            // Allow G-buffer pass instancing only if lightmask matches zone lightmask
                            baseBatch.lightMask_ = GetLightMask(drawable);
                            FinalizeBatch(baseBatch, tech, pass, baseBatch.lightMask_ == (baseBatch.zone_->GetLightMask() & 0xff));
                            gbufferQueue_.AddBatch(baseBatch);
                        }
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
        if (renderMode_ != RENDER_FORWARD)
        {
            item.start_ = &gbufferQueue_;
            queue->AddWorkItem(item);
        }
        
        item.workFunction_ = SortBatchQueueBackToFrontWork;
        item.start_ = &alphaQueue_;
        queue->AddWorkItem(item);
        item.start_ = &postAlphaQueue_;
        queue->AddWorkItem(item);
        
        for (Vector<LightBatchQueue>::Iterator i = lightQueues_.Begin(); i != lightQueues_.End(); ++i)
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
    Light* firstLight = drawable->GetFirstLight();
    Zone* zone = GetZone(drawable);
    // Shadows on transparencies can only be rendered if shadow maps are not reused
    bool allowTransparentShadows = !renderer_->GetReuseShadowMaps();
    bool hasVertexLights = drawable->GetVertexLights().Size() > 0;
    bool hasAmbientGradient = zone->GetAmbientGradient() && zone->GetAmbientStartColor() != zone->GetAmbientEndColor();
    unsigned numBatches = drawable->GetNumBatches();
    
    for (unsigned i = 0; i < numBatches; ++i)
    {
        Batch litBatch;
        drawable->GetBatch(litBatch, frame_, i);
        
        Technique* tech = GetTechnique(drawable, litBatch.material_);
        if (!litBatch.geometry_ || !tech)
            continue;
        
        // Do not create pixel lit forward passes for materials that render into the G-buffer
        if ((renderMode_ == RENDER_PREPASS && tech->HasPass(PASS_PREPASS)) || (renderMode_ == RENDER_DEFERRED &&
            tech->HasPass(PASS_DEFERRED)))
            continue;
        
        Pass* pass = 0;
        
        // Check for lit base pass. Because it uses the replace blend mode, it must be ensured to be the first light
        // Also vertex lighting or ambient gradient require the non-lit base pass, so skip in those cases
        if (i < 32 && light == firstLight && !hasVertexLights && !hasAmbientGradient && !drawable->HasBasePass(i))
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

void View::RenderBatchesForward()
{
    // If using hardware multisampling with post-processing, render to the backbuffer first and then resolve
    bool resolve = screenBuffers_.Size() && !renderTarget_ && graphics_->GetMultiSample() > 1;
    RenderSurface* renderTarget = (screenBuffers_.Size() && !resolve) ? screenBuffers_[0]->GetRenderSurface() : renderTarget_;
    RenderSurface* depthStencil = GetDepthStencil(renderTarget);
    
    // If not reusing shadowmaps, render all of them first
    if (!renderer_->GetReuseShadowMaps() && renderer_->GetDrawShadows() && !lightQueues_.Empty())
    {
        PROFILE(RenderShadowMaps);
        
        for (Vector<LightBatchQueue>::Iterator i = lightQueues_.Begin(); i != lightQueues_.End(); ++i)
        {
            if (i->shadowMap_)
                RenderShadowMap(*i);
        }
    }
    
    graphics_->SetRenderTarget(0, renderTarget);
    graphics_->SetDepthStencil(depthStencil);
    graphics_->SetViewport(viewRect_);
    graphics_->Clear(CLEAR_DEPTH | CLEAR_STENCIL);
    
    // Render opaque object unlit base pass
    if (!baseQueue_.IsEmpty())
    {
        PROFILE(RenderBase);
        baseQueue_.Draw(graphics_, renderer_);
    }
    
    // Render shadow maps + opaque objects' additive lighting
    if (!lightQueues_.Empty())
    {
        PROFILE(RenderLights);
        
        for (Vector<LightBatchQueue>::Iterator i = lightQueues_.Begin(); i != lightQueues_.End(); ++i)
        {
            // If reusing shadowmaps, render each of them before the lit batches
            if (renderer_->GetReuseShadowMaps() && i->shadowMap_)
            {
                RenderShadowMap(*i);
                graphics_->SetRenderTarget(0, renderTarget);
                graphics_->SetDepthStencil(depthStencil);
                graphics_->SetViewport(viewRect_);
            }
            
            i->litBatches_.Draw(i->light_, graphics_, renderer_);
        }
    }
    
    graphics_->SetScissorTest(false);
    graphics_->SetStencilTest(false);
    
    // At this point clear the parts of viewport not occupied by opaque geometry with fog color
    graphics_->SetAlphaTest(false);
    graphics_->SetBlendMode(BLEND_REPLACE);
    graphics_->SetColorWrite(true);
    graphics_->SetDepthTest(CMP_LESSEQUAL);
    graphics_->SetDepthWrite(false);
    graphics_->SetScissorTest(false);
    graphics_->SetStencilTest(false);
    graphics_->SetShaders(renderer_->GetVertexShader("Basic"), renderer_->GetPixelShader("Basic"));
    graphics_->SetShaderParameter(PSP_MATDIFFCOLOR, farClipZone_->GetFogColor());
    graphics_->ClearParameterSource(PSP_MATDIFFCOLOR);
    DrawFullscreenQuad(camera_, false);
    
    // Render pre-alpha custom pass
    if (!preAlphaQueue_.IsEmpty())
    {
        PROFILE(RenderPreAlpha);
        preAlphaQueue_.Draw(graphics_, renderer_);
    }
    
    // Render transparent objects (both base passes & additive lighting)
    if (!alphaQueue_.IsEmpty())
    {
        PROFILE(RenderAlpha);
        alphaQueue_.Draw(graphics_, renderer_, true);
    }
    
    // Render post-alpha custom pass
    if (!postAlphaQueue_.IsEmpty())
    {
        PROFILE(RenderPostAlpha);
        postAlphaQueue_.Draw(graphics_, renderer_);
    }
    
    // Resolve multisampled backbuffer now if necessary
    if (resolve)
        graphics_->ResolveToTexture(screenBuffers_[0], viewRect_);
}

void View::RenderBatchesDeferred()
{
    // If not reusing shadowmaps, render all of them first
    if (!renderer_->GetReuseShadowMaps() && renderer_->GetDrawShadows() && !lightQueues_.Empty())
    {
        PROFILE(RenderShadowMaps);
        
        for (Vector<LightBatchQueue>::Iterator i = lightQueues_.Begin(); i != lightQueues_.End(); ++i)
        {
            if (i->shadowMap_)
                RenderShadowMap(*i);
        }
    }
    
    bool hwDepth = graphics_->GetHardwareDepthSupport();
    // In light prepass mode the albedo buffer is used for light accumulation instead
    Texture2D* albedoBuffer = renderer_->GetScreenBuffer(rtSize_.x_, rtSize_.y_, Graphics::GetRGBAFormat());
    Texture2D* normalBuffer = renderer_->GetScreenBuffer(rtSize_.x_, rtSize_.y_, Graphics::GetRGBAFormat());
    Texture2D* depthBuffer = renderer_->GetScreenBuffer(rtSize_.x_, rtSize_.y_, hwDepth ? Graphics::GetDepthStencilFormat() :
        Graphics::GetLinearDepthFormat());
    
    RenderSurface* renderTarget = screenBuffers_.Size() ? screenBuffers_[0]->GetRenderSurface() : renderTarget_;
    RenderSurface* depthStencil = hwDepth ? depthBuffer->GetRenderSurface() : renderer_->GetDepthStencil(rtSize_.x_, rtSize_.y_);
    
    if (renderMode_ == RENDER_PREPASS)
    {
        graphics_->SetRenderTarget(0, normalBuffer);
        if (!hwDepth)
            graphics_->SetRenderTarget(1, depthBuffer);
    }
    else
    {
        graphics_->SetRenderTarget(0, renderTarget);
        graphics_->SetRenderTarget(1, albedoBuffer);
        graphics_->SetRenderTarget(2, normalBuffer);
        if (!hwDepth)
            graphics_->SetRenderTarget(3, depthBuffer);
    }
    
    graphics_->SetDepthStencil(depthStencil);
    graphics_->SetViewport(viewRect_);
    graphics_->Clear(CLEAR_DEPTH | CLEAR_STENCIL);
    
    // Render G-buffer batches
    if (!gbufferQueue_.IsEmpty())
    {
        PROFILE(RenderGBuffer);
        gbufferQueue_.Draw(graphics_, renderer_, false, true);
    }
    
    // Clear the light accumulation buffer (light pre-pass only.) However, skip the clear if the first light is a directional
    // light with full mask
    RenderSurface* lightRenderTarget = renderMode_ == RENDER_PREPASS ? albedoBuffer->GetRenderSurface() : renderTarget;
    if (renderMode_ == RENDER_PREPASS)
    {
        bool optimizeLightBuffer = !hasZeroLightMask_ && !lightQueues_.Empty() && lightQueues_.Front().light_->GetLightType() ==
            LIGHT_DIRECTIONAL && (lightQueues_.Front().light_->GetLightMask() & 0xff) == 0xff;
        
        graphics_->SetRenderTarget(0, lightRenderTarget);
        graphics_->ResetRenderTarget(1);
        graphics_->SetDepthStencil(depthStencil);
        graphics_->SetViewport(viewRect_);
        if (!optimizeLightBuffer)
            graphics_->Clear(CLEAR_COLOR);
    }
    else
    {
        graphics_->ResetRenderTarget(1);
        graphics_->ResetRenderTarget(2);
        graphics_->ResetRenderTarget(3);
    }
    
    // Render shadow maps + light volumes
    if (!lightQueues_.Empty())
    {
        PROFILE(RenderLights);
        
        for (Vector<LightBatchQueue>::Iterator i = lightQueues_.Begin(); i != lightQueues_.End(); ++i)
        {
            // If reusing shadowmaps, render each of them before the lit batches
            if (renderer_->GetReuseShadowMaps() && i->shadowMap_)
            {
                RenderShadowMap(*i);
                graphics_->SetRenderTarget(0, lightRenderTarget);
                graphics_->SetDepthStencil(depthStencil);
                graphics_->SetViewport(viewRect_);
            }
            
            if (renderMode_ == RENDER_DEFERRED)
                graphics_->SetTexture(TU_ALBEDOBUFFER, albedoBuffer);
            graphics_->SetTexture(TU_NORMALBUFFER, normalBuffer);
            graphics_->SetTexture(TU_DEPTHBUFFER, depthBuffer);
            
            for (unsigned j = 0; j < i->volumeBatches_.Size(); ++j)
            {
                SetupLightVolumeBatch(i->volumeBatches_[j]);
                i->volumeBatches_[j].Draw(graphics_, renderer_);
            }
        }
    }
    
    graphics_->SetTexture(TU_ALBEDOBUFFER, 0);
    graphics_->SetTexture(TU_NORMALBUFFER, 0);
    graphics_->SetTexture(TU_DEPTHBUFFER, 0);
    
    if (renderMode_ == RENDER_PREPASS)
    {
        graphics_->SetRenderTarget(0, renderTarget);
        graphics_->SetDepthStencil(depthStencil);
        graphics_->SetViewport(viewRect_);
    }
    
    // At this point clear the parts of viewport not occupied by opaque geometry with fog color
    graphics_->SetAlphaTest(false);
    graphics_->SetBlendMode(BLEND_REPLACE);
    graphics_->SetColorWrite(true);
    graphics_->SetDepthTest(CMP_ALWAYS);
    graphics_->SetDepthWrite(false);
    graphics_->SetScissorTest(false);
    graphics_->SetStencilTest(true, CMP_EQUAL, OP_KEEP, OP_KEEP, OP_KEEP, 0);
    graphics_->SetShaders(renderer_->GetVertexShader("Basic"), renderer_->GetPixelShader("Basic"));
    graphics_->SetShaderParameter(PSP_MATDIFFCOLOR, farClipZone_->GetFogColor());
    graphics_->ClearParameterSource(PSP_MATDIFFCOLOR);
    DrawFullscreenQuad(camera_, false);
    
    // Render opaque objects with deferred lighting result (light pre-pass only)
    if (!baseQueue_.IsEmpty())
    {
        PROFILE(RenderBase);
        
        graphics_->SetTexture(TU_LIGHTBUFFER, renderMode_ == RENDER_PREPASS ? albedoBuffer : 0);
        baseQueue_.Draw(graphics_, renderer_);
        graphics_->SetTexture(TU_LIGHTBUFFER, 0);
    }
    
    // Render pre-alpha custom pass
    if (!preAlphaQueue_.IsEmpty())
    {
        PROFILE(RenderPreAlpha);
        preAlphaQueue_.Draw(graphics_, renderer_);
    }
    
    // Render transparent objects (both base passes & additive lighting)
    if (!alphaQueue_.IsEmpty())
    {
        PROFILE(RenderAlpha);
        alphaQueue_.Draw(graphics_, renderer_, true);
    }
    
    // Render post-alpha custom pass
    if (!postAlphaQueue_.IsEmpty())
    {
        PROFILE(RenderPostAlpha);
        postAlphaQueue_.Draw(graphics_, renderer_);
    }
}

void View::AllocateScreenBuffers()
{
    unsigned neededBuffers = 0;
    #ifdef USE_OPENGL
    // Due to FBO limitations, in OpenGL deferred modes need to render to texture first and then blit to the backbuffer
    // Also, if rendering to a texture with deferred rendering, it must be RGBA to comply with the rest of the buffers.
    if (renderMode_ != RENDER_FORWARD && (!renderTarget_ || (renderMode_ == RENDER_DEFERRED &&
        renderTarget_->GetParentTexture()->GetFormat() != Graphics::GetRGBAFormat())))
        neededBuffers = 1;
    #endif
    
    unsigned postProcessPasses = 0;
    for (unsigned i = 0; i < postProcesses_.Size(); ++i)
        postProcessPasses += postProcesses_[i]->GetNumPasses();
    
    // If more than one post-process pass, need 2 buffers for ping-pong rendering
    if (postProcessPasses)
        neededBuffers = Min((int)postProcessPasses, 2);
    
    unsigned format = Graphics::GetRGBFormat();
    #ifdef USE_OPENGL
    if (renderMode_ == RENDER_DEFERRED)
        format = Graphics::GetRGBAFormat();
    #endif
    
    // Allocate screen buffers with filtering active in case the post-processing effects need that
    for (unsigned i = 0; i < neededBuffers; ++i)
        screenBuffers_.Push(renderer_->GetScreenBuffer(rtSize_.x_, rtSize_.y_, format, true));
}

void View::BlitFramebuffer()
{
    // Blit the final image to destination rendertarget
    /// \todo Depth is reset to far plane, so geometry drawn after the view can not be depth tested
    graphics_->SetAlphaTest(false);
    graphics_->SetBlendMode(BLEND_REPLACE);
    graphics_->SetDepthTest(CMP_ALWAYS);
    graphics_->SetDepthWrite(true);
    graphics_->SetScissorTest(false);
    graphics_->SetStencilTest(false);
    graphics_->SetRenderTarget(0, renderTarget_);
    graphics_->SetDepthStencil(GetDepthStencil(renderTarget_));
    graphics_->SetViewport(viewRect_);
    
    String shaderName = "CopyFramebuffer";
    graphics_->SetShaders(renderer_->GetVertexShader(shaderName), renderer_->GetPixelShader(shaderName));
    
    float rtWidth = (float)rtSize_.x_;
    float rtHeight = (float)rtSize_.y_;
    float widthRange = 0.5f * viewSize_.x_ / rtWidth;
    float heightRange = 0.5f * viewSize_.y_ / rtHeight;
    
    #ifdef USE_OPENGL
    Vector4 bufferUVOffset(((float)viewRect_.left_) / rtWidth + widthRange,
        1.0f - (((float)viewRect_.top_) / rtHeight + heightRange), widthRange, heightRange);
    #else
    Vector4 bufferUVOffset((0.5f + (float)viewRect_.left_) / rtWidth + widthRange,
        (0.5f + (float)viewRect_.top_) / rtHeight + heightRange, widthRange, heightRange);
    #endif
    
    graphics_->SetShaderParameter(VSP_GBUFFEROFFSETS, bufferUVOffset);
    graphics_->SetTexture(TU_DIFFUSE, screenBuffers_[0]);
    DrawFullscreenQuad(camera_, false);
}

void View::RunPostProcesses()
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    
    // Ping-pong buffer indices for read and write
    unsigned readRtIndex = 0;
    unsigned writeRtIndex = screenBuffers_.Size() - 1;
    
    graphics_->SetAlphaTest(false);
    graphics_->SetBlendMode(BLEND_REPLACE);
    graphics_->SetDepthTest(CMP_ALWAYS);
    graphics_->SetScissorTest(false);
    graphics_->SetStencilTest(false);
    
    for (unsigned i = 0; i < postProcesses_.Size(); ++i)
    {
        PostProcess* effect = postProcesses_[i];
        
        // For each effect, rendertargets can be re-used. Allocate them now
        renderer_->SaveScreenBufferAllocations();
        const HashMap<StringHash, PostProcessRenderTarget>& renderTargetInfos = effect->GetRenderTargets();
        HashMap<StringHash, Texture2D*> renderTargets;
        for (HashMap<StringHash, PostProcessRenderTarget>::ConstIterator j = renderTargetInfos.Begin(); j !=
            renderTargetInfos.End(); ++j)
        {
            unsigned width = j->second_.size_.x_;
            unsigned height = j->second_.size_.y_;
            if (j->second_.sizeDivisor_)
            {
                width = viewSize_.x_ / width;
                height = viewSize_.y_ / height;
            }
            
            renderTargets[j->first_] = renderer_->GetScreenBuffer(width, height, j->second_.format_, j->second_.filtered_);
        }
        
        // Run each effect pass
        for (unsigned j = 0; j < effect->GetNumPasses(); ++j)
        {
            PostProcessPass* pass = effect->GetPass(j);
            bool lastPass = (i == postProcesses_.Size() - 1) && (j == effect->GetNumPasses() - 1);
            bool swapBuffers = false;
            
            // Write depth on the last pass only
            graphics_->SetDepthWrite(lastPass);
            
            // Set output rendertarget
            RenderSurface* rt = 0;
            String output = pass->GetOutput().ToLower();
            if (output == "viewport")
            {
                if (!lastPass)
                {
                    rt = screenBuffers_[writeRtIndex]->GetRenderSurface();
                    swapBuffers = true;
                }
                else
                    rt = renderTarget_;
                
                graphics_->SetRenderTarget(0, rt);
                graphics_->SetDepthStencil(GetDepthStencil(rt));
                graphics_->SetViewport(viewRect_);
            }
            else
            {
                HashMap<StringHash, Texture2D*>::ConstIterator k = renderTargets.Find(StringHash(output));
                if (k != renderTargets.End())
                    rt = k->second_->GetRenderSurface();
                else
                    continue; // Skip pass if rendertarget can not be found
                
                graphics_->SetRenderTarget(0, rt);
                graphics_->SetDepthStencil(GetDepthStencil(rt));
                graphics_->SetViewport(IntRect(0, 0, rt->GetWidth(), rt->GetHeight()));
            }
            
            // Set shaders, shader parameters and textures
            graphics_->SetShaders(renderer_->GetVertexShader(pass->GetVertexShader()),
                renderer_->GetPixelShader(pass->GetPixelShader()));
            
            const HashMap<StringHash, Vector4>& globalParameters = effect->GetShaderParameters();
            for (HashMap<StringHash, Vector4>::ConstIterator k = globalParameters.Begin(); k != globalParameters.End(); ++k)
                graphics_->SetShaderParameter(k->first_, k->second_);
            
            const HashMap<StringHash, Vector4>& parameters = pass->GetShaderParameters();
            for (HashMap<StringHash, Vector4>::ConstIterator k = parameters.Begin(); k != parameters.End(); ++k)
                graphics_->SetShaderParameter(k->first_, k->second_);
            
            float rtWidth = (float)rtSize_.x_;
            float rtHeight = (float)rtSize_.y_;
            float widthRange = 0.5f * viewSize_.x_ / rtWidth;
            float heightRange = 0.5f * viewSize_.y_ / rtHeight;
            
            #ifdef USE_OPENGL
            Vector4 bufferUVOffset(((float)viewRect_.left_) / rtWidth + widthRange,
                1.0f - (((float)viewRect_.top_) / rtHeight + heightRange), widthRange, heightRange);
            #else
            Vector4 bufferUVOffset((0.5f + (float)viewRect_.left_) / rtWidth + widthRange,
                (0.5f + (float)viewRect_.top_) / rtHeight + heightRange, widthRange, heightRange);
            #endif
            
            graphics_->SetShaderParameter(VSP_GBUFFEROFFSETS, bufferUVOffset);
            graphics_->SetShaderParameter(PSP_GBUFFERINVSIZE, Vector4(1.0f / rtWidth, 1.0f / rtHeight, 0.0f, 0.0f));
            
            // Set per-rendertarget inverse size / offset shader parameters as necessary
            for (HashMap<StringHash, PostProcessRenderTarget>::ConstIterator k = renderTargetInfos.Begin(); k !=
                renderTargetInfos.End(); ++k)
            {
                String invSizeName = k->second_.name_ + "InvSize";
                String offsetsName = k->second_.name_ + "Offsets";
                float width = (float)renderTargets[k->first_]->GetWidth();
                float height = (float)renderTargets[k->first_]->GetHeight();
                
                graphics_->SetShaderParameter(StringHash(invSizeName), Vector4(1.0f / width, 1.0f / height, 0.0f, 0.0f));
                #ifdef USE_OPENGL
                graphics_->SetShaderParameter(StringHash(offsetsName), Vector4::ZERO);
                #else
                graphics_->SetShaderParameter(StringHash(offsetsName), Vector4(0.5f / width, 0.5f / height, 0.0f, 0.0f));
                #endif
            }
            
            const String* textureNames = pass->GetTextures();
            for (unsigned k = 0; k < MAX_MATERIAL_TEXTURE_UNITS; ++k)
            {
                if (!textureNames[k].Empty())
                {
                    // Texture may either refer to a rendertarget or to a texture resource
                    if (!textureNames[k].Compare("viewport", false))
                        graphics_->SetTexture(k, screenBuffers_[readRtIndex]);
                    else
                    {
                        HashMap<StringHash, Texture2D*>::ConstIterator l = renderTargets.Find(StringHash(textureNames[k]));
                        if (l != renderTargets.End())
                            graphics_->SetTexture(k, l->second_);
                        else
                        {
                            // If requesting a texture fails, clear the texture name to prevent redundant attempts
                            Texture2D* texture = cache->GetResource<Texture2D>(textureNames[k]);
                            if (texture)
                                graphics_->SetTexture(k, texture);
                            else
                                pass->SetTexture((TextureUnit)k, String());
                        }
                    }
                }
            }
            
            DrawFullscreenQuad(camera_, false);
            
            // Swap the ping-pong buffer sides now if necessary
            if (swapBuffers)
                Swap(readRtIndex, writeRtIndex);
        }
        
        // Forget the rendertargets allocated during this effect
        renderer_->RestoreScreenBufferAllocations();
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
            float diagonal = box.Size().Length();
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
    const Frustum& frustum = camera_->GetFrustum();
    
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
        query.shadowSplits_.Clear();
        return;
    }
    
    // Determine number of shadow cameras and setup their initial positions
    SetupShadowCameras(query);
    
    // Process each split for shadow casters. Divide multiple splits into the work queue
    if (query.shadowSplits_.Size())
    {
        if (query.shadowSplits_.Size() > 1)
        {
            WorkQueue* queue = GetSubsystem<WorkQueue>();
            
            WorkItem item;
            item.workFunction_ = ProcessShadowSplitWork;
            item.start_ = &query;
            item.aux_ = this;
            
            for (unsigned i = 1; i < query.shadowSplits_.Size(); ++i)
            {
                item.end_ = (void*)i;
                queue->AddWorkItem(item);
            }
        }
        
        // Process the first split here
        ProcessShadowSplit(query, 0, threadIndex);
    }
}

void View::ProcessShadowSplit(LightQueryResult& query, unsigned splitIndex, unsigned threadIndex)
{
    ShadowQueryResult& split = query.shadowSplits_[splitIndex];
    Camera* shadowCamera = split.shadowCamera_;
    split.shadowCasters_.Clear();
    
    Light* light = query.light_;
    LightType type = light->GetLightType();
    const Frustum& frustum = camera_->GetFrustum();
    const Frustum& shadowCameraFrustum = shadowCamera->GetFrustum();
    PODVector<Drawable*>& tempDrawables = tempDrawables_[threadIndex];
    
    // For point light check that the face is visible: if not, can skip the split
    if (type == LIGHT_POINT && frustum.IsInsideFast(BoundingBox(shadowCameraFrustum)) == OUTSIDE)
        return;
    
    // For directional light check that the split is inside the visible scene: if not, can skip the split
    if (type == LIGHT_DIRECTIONAL)
    {
        if (sceneViewBox_.min_.z_ > split.shadowFarSplit_)
            return;
        if (sceneViewBox_.max_.z_ < split.shadowNearSplit_)
            return;
    }
    
    // Reuse lit geometry query for all except directional lights
    if (type == LIGHT_DIRECTIONAL)
    {
        ShadowCasterOctreeQuery query(tempDrawables, shadowCameraFrustum, DRAWABLE_GEOMETRY, camera_->GetViewMask());
        octree_->GetDrawables(query);
    }
    
    // Check which shadow casters actually contribute to the shadowing
    ProcessShadowCasters(query, tempDrawables, splitIndex);
}

void View::ProcessShadowCasters(LightQueryResult& query, const PODVector<Drawable*>& drawables, unsigned splitIndex)
{
    Light* light = query.light_;
    Matrix3x4 lightView;
    Matrix4 lightProj;
    
    ShadowQueryResult& split = query.shadowSplits_[splitIndex];
    Camera* shadowCamera = split.shadowCamera_;
    const Frustum& shadowCameraFrustum = shadowCamera->GetFrustum();
    lightView = shadowCamera->GetInverseWorldTransform();
    lightProj = shadowCamera->GetProjection();
    LightType type = light->GetLightType();
    
    split.shadowCasterBox_.defined_ = false;
    
    // Transform scene frustum into shadow camera's view space for shadow caster visibility check. For point & spot lights,
    // we can use the whole scene frustum. For directional lights, use the intersection of the scene frustum and the split
    // frustum, so that shadow casters do not get rendered into unnecessary splits
    Frustum lightViewFrustum;
    if (type != LIGHT_DIRECTIONAL)
        lightViewFrustum = sceneFrustum_.Transformed(lightView);
    else
        lightViewFrustum = camera_->GetSplitFrustum(Max(sceneViewBox_.min_.z_, split.shadowNearSplit_),
            Min(sceneViewBox_.max_.z_, split.shadowFarSplit_)).Transformed(lightView);
    
    BoundingBox lightViewFrustumBox(lightViewFrustum);
     
    // Check for degenerate split frustum: in that case there is no need to get shadow casters
    if (lightViewFrustum.vertices_[0] == lightViewFrustum.vertices_[4])
        return;
    
    BoundingBox lightViewBox;
    BoundingBox lightProjBox;
    
    for (PODVector<Drawable*>::ConstIterator i = drawables.Begin(); i != drawables.End(); ++i)
    {
        Drawable* drawable = *i;
        // In case this is a point or spot light query result reused for optimization, we may have non-shadowcasters included.
        // Check for that first
        if (!drawable->GetCastShadows())
            continue;
        // For point light, check that this drawable is inside the split shadow camera frustum
        if (type == LIGHT_POINT && shadowCameraFrustum.IsInsideFast(drawable->GetWorldBoundingBox()) == OUTSIDE)
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
            if (type == LIGHT_DIRECTIONAL)
                split.shadowCasterBox_.Merge(lightViewBox);
            else
            {
                lightProjBox = lightViewBox.Projected(lightProj);
                split.shadowCasterBox_.Merge(lightProjBox);
            }
            split.shadowCasters_.Push(drawable);
        }
    }
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
        float originalDistance = Clamp(center.Length(), M_EPSILON, extrusionDistance);
        
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
    // Due to instruction count limits, deferred modes in SM2.0 can only support up to 3 cascades
    #ifndef USE_OPENGL
    if (renderMode_ != RENDER_FORWARD && !graphics_->GetSM3Support())
        maxCascades = Max(maxCascades, 3);
    #endif
    
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

void View::SetupShadowCameras(LightQueryResult& query)
{
    Light* light = query.light_;
    
    LightType type = light->GetLightType();
    unsigned splits = 0;
    
    if (type == LIGHT_DIRECTIONAL)
    {
        const CascadeParameters& cascade = light->GetShadowCascade();
        
        float nearSplit = camera_->GetNearClip();
        float farSplit;
        
        while (splits < (unsigned)renderer_->GetMaxShadowCascades())
        {
            // If split is completely beyond camera far clip, we are done
            if (nearSplit > camera_->GetFarClip())
                break;
            
            farSplit = Min(camera_->GetFarClip(), cascade.splits_[splits]);
            if (farSplit <= nearSplit)
                break;
            
            nearSplit = farSplit;
            ++splits;
        }
        
        query.shadowSplits_.Resize(splits);
        
        for (unsigned i = 0; i < splits; ++i)
        {
            nearSplit = camera_->GetNearClip();
            farSplit = Min(camera_->GetFarClip(), cascade.splits_[i]);
            
            // Setup the shadow camera for the split
            ShadowQueryResult& split = query.shadowSplits_[i];
            Camera* shadowCamera = renderer_->GetShadowCamera();
            split.shadowCamera_ = shadowCamera;
            split.shadowNearSplit_ = nearSplit;
            split.shadowFarSplit_ = farSplit;
            SetupDirLightShadowCamera(shadowCamera, light, nearSplit, farSplit);
            
            nearSplit = farSplit;
        }
    }
    
    if (type == LIGHT_SPOT)
    {
        query.shadowSplits_.Resize(1);
        
        Camera* shadowCamera = renderer_->GetShadowCamera();
        query.shadowSplits_[0].shadowCamera_ = shadowCamera;
        Node* cameraNode = shadowCamera->GetNode();
        
        cameraNode->SetTransform(light->GetWorldPosition(), light->GetWorldRotation());
        shadowCamera->SetNearClip(light->GetShadowNearFarRatio() * light->GetRange());
        shadowCamera->SetFarClip(light->GetRange());
        shadowCamera->SetFov(light->GetFov());
        shadowCamera->SetAspectRatio(light->GetAspectRatio());
    }
    
    if (type == LIGHT_POINT)
    {
        query.shadowSplits_.Resize(MAX_CUBEMAP_FACES);
        
        for (unsigned i = 0; i < MAX_CUBEMAP_FACES; ++i)
        {
            Camera* shadowCamera = renderer_->GetShadowCamera();
            query.shadowSplits_[i].shadowCamera_ = shadowCamera;
            Node* cameraNode = shadowCamera->GetNode();
            
            // When making a shadowed point light, align the splits along X, Y and Z axes regardless of light rotation
            cameraNode->SetPosition(light->GetWorldPosition());
            cameraNode->SetDirection(directions[i]);
            shadowCamera->SetNearClip(light->GetShadowNearFarRatio() * light->GetRange());
            shadowCamera->SetFarClip(light->GetRange());
            shadowCamera->SetFov(90.0f);
            shadowCamera->SetAspectRatio(1.0f);
        }
    }
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
    Polyhedron frustumVolume;
    frustumVolume.Define(splitFrustum);
    // If focusing enabled, clip the frustum volume by the combined bounding box of the lit geometries within the frustum
    if (parameters.focus_)
    {
        BoundingBox litGeometriesBox;
        for (unsigned i = 0; i < geometries_.Size(); ++i)
        {
            // Skip skyboxes as they have undefinedly large bounding box size
            if (geometries_[i]->GetType() == Skybox::GetTypeStatic())
                continue;
            
            if (geometryDepthBounds_[i].min_ <= farSplit && geometryDepthBounds_[i].max_ >= nearSplit &&
                (GetLightMask(geometries_[i]) & light->GetLightMask()))
                litGeometriesBox.Merge(geometries_[i]->GetWorldBoundingBox());
        }
        if (litGeometriesBox.defined_)
        {
            frustumVolume.Clip(litGeometriesBox);
            // If volume became empty, restore it to avoid zero size
            if (frustumVolume.Empty())
                frustumVolume.Define(splitFrustum);
        }
    }
    
    // Transform frustum volume to light space
    Matrix3x4 lightView(shadowCamera->GetInverseWorldTransform());
    frustumVolume.Transform(lightView);
    
    // Fit the frustum volume inside a bounding box. If uniform size, use a sphere instead
    BoundingBox shadowBox;
    if (!parameters.nonUniform_)
        shadowBox.Define(Sphere(frustumVolume));
    else
        shadowBox.Define(frustumVolume);
    
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
    if (camera_->GetFrustum().IsInside(center))
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
    const SharedPtr<Texture>* textures = material->GetTextures();
    
    for (unsigned i = 0; i < MAX_MATERIAL_TEXTURE_UNITS; ++i)
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
                    Viewport* viewport = target->GetViewport();
                    if (viewport->GetScene() && viewport->GetCamera())
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
                        Viewport* viewport = target->GetViewport();
                        if (viewport->GetScene() && viewport->GetCamera())
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
    
    totalInstances += baseQueue_.GetNumInstances(renderer_);
    totalInstances += preAlphaQueue_.GetNumInstances(renderer_);
    if (renderMode_ != RENDER_FORWARD)
        totalInstances += gbufferQueue_.GetNumInstances(renderer_);
    
    for (Vector<LightBatchQueue>::Iterator i = lightQueues_.Begin(); i != lightQueues_.End(); ++i)
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
            if (renderMode_ != RENDER_FORWARD)
                gbufferQueue_.SetTransforms(renderer_, lockedData, freeIndex);
            
            for (Vector<LightBatchQueue>::Iterator i = lightQueues_.Begin(); i != lightQueues_.End(); ++i)
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
    
    // Use replace blend mode for the first pre-pass light volume, and additive for the rest
    graphics_->SetAlphaTest(false);
    graphics_->SetBlendMode(renderMode_ == RENDER_PREPASS && light == lightQueues_.Front().light_ ? BLEND_REPLACE : BLEND_ADD);
    graphics_->SetDepthWrite(false);
    
    if (type != LIGHT_DIRECTIONAL)
    {
        if (type == LIGHT_POINT)
            lightDist = Sphere(light->GetWorldPosition(), light->GetRange() * 1.25f).Distance(camera_->GetWorldPosition());
        else
            lightDist = light->GetFrustum().Distance(camera_->GetWorldPosition());
        
        // Draw front faces if not inside light volume
        if (lightDist < camera_->GetNearClip() * 2.0f)
        {
            renderer_->SetCullMode(CULL_CW, camera_);
            graphics_->SetDepthTest(CMP_GREATER);
        }
        else
        {
            renderer_->SetCullMode(CULL_CCW, camera_);
            graphics_->SetDepthTest(CMP_LESSEQUAL);
        }
    }
    else
    {
        // In case the same camera is used for multiple views with differing aspect ratios (not recommended)
        // refresh the directional light's model transform before rendering
        light->GetVolumeTransform(camera_);
        graphics_->SetCullMode(CULL_NONE);
        graphics_->SetDepthTest(CMP_ALWAYS);
    }
    
    graphics_->SetScissorTest(false);
    graphics_->SetStencilTest(true, CMP_NOTEQUAL, OP_KEEP, OP_KEEP, OP_KEEP, 0, light->GetLightMask());
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

void View::RenderShadowMap(const LightBatchQueue& queue)
{
    PROFILE(RenderShadowMap);
    
    Texture2D* shadowMap = queue.shadowMap_;
    graphics_->SetTexture(TU_SHADOWMAP, 0);
    
    graphics_->SetColorWrite(false);
    graphics_->SetStencilTest(false);
    graphics_->SetRenderTarget(0, shadowMap->GetRenderSurface()->GetLinkedRenderTarget());
    graphics_->SetDepthStencil(shadowMap);
    graphics_->SetViewport(IntRect(0, 0, shadowMap->GetWidth(), shadowMap->GetHeight()));
    graphics_->Clear(CLEAR_DEPTH);
    
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
            shadowQueue.shadowBatches_.Draw(graphics_, renderer_);
        }
    }
    
    graphics_->SetColorWrite(true);
    graphics_->SetDepthBias(0.0f, 0.0f);
}

RenderSurface* View::GetDepthStencil(RenderSurface* renderTarget)
{
    // If using the backbuffer, return the backbuffer depth-stencil
    if (!renderTarget)
        return 0;
    // Then check for linked depth-stencil
    RenderSurface* depthStencil = renderTarget->GetLinkedDepthStencil();
    // Finally get one from Renderer
    if (!depthStencil)
        depthStencil = renderer_->GetDepthStencil(renderTarget->GetWidth(), renderTarget->GetHeight());
    return depthStencil;
}
