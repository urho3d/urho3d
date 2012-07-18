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
#include "Context.h"
#include "DebugRenderer.h"
#include "Light.h"
#include "Octree.h"
#include "Scene.h"
#include "Sort.h"
#include "Zone.h"

#include "DebugNew.h"

static const Vector3 DOT_SCALE(1 / 3.0f, 1 / 3.0f, 1 / 3.0f);

OBJECTTYPESTATIC(Drawable);

Drawable::Drawable(Context* context) :
    Component(context),
    drawableFlags_(0),
    worldBoundingBoxDirty_(true),
    visible_(true),
    castShadows_(false),
    occluder_(false),
    occludee_(true),
    updateQueued_(false),
    reinsertionQueued_(false),
    viewMask_(DEFAULT_VIEWMASK),
    lightMask_(DEFAULT_LIGHTMASK),
    shadowMask_(DEFAULT_SHADOWMASK),
    zoneMask_(DEFAULT_ZONEMASK),
    viewFrameNumber_(0),
    distance_(0.0f),
    lodDistance_(0.0f),
    drawDistance_(0.0f),
    shadowDistance_(0.0f),
    sortValue_(0.0f),
    minZ_(0.0f),
    maxZ_(0.0f),
    lodBias_(1.0f),
    basePassFlags_(0),
    maxLights_(0),
    octant_(0),
    firstLight_(0),
    viewFrame_(0),
    viewCamera_(0),
    temporaryZone_(false)
{
}

Drawable::~Drawable()
{
    RemoveFromOctree();
}

void Drawable::RegisterObject(Context* context)
{
    ATTRIBUTE(Drawable, VAR_INT, "Max Lights", maxLights_, 0, AM_DEFAULT);
    ATTRIBUTE(Drawable, VAR_INT, "View Mask", viewMask_, DEFAULT_VIEWMASK, AM_DEFAULT);
    ATTRIBUTE(Drawable, VAR_INT, "Light Mask", lightMask_, DEFAULT_LIGHTMASK, AM_DEFAULT);
    ATTRIBUTE(Drawable, VAR_INT, "Shadow Mask", shadowMask_, DEFAULT_SHADOWMASK, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(Drawable, VAR_INT, "Zone Mask", GetZoneMask, SetZoneMask, unsigned, DEFAULT_ZONEMASK, AM_DEFAULT);
}

void Drawable::ProcessRayQuery(const RayOctreeQuery& query, PODVector<RayQueryResult>& results)
{
    float distance = query.ray_.HitDistance(GetWorldBoundingBox());
    if (distance <= query.maxDistance_)
    {
        RayQueryResult result;
        result.drawable_ = this;
        result.node_ = GetNode();
        result.distance_ = distance;
        result.subObject_ = M_MAX_UNSIGNED;
        results.Push(result);
    }
}

void Drawable::UpdateBatches(const FrameInfo& frame)
{
    distance_ = frame.camera_->GetDistance(node_->GetWorldPosition());
    
    float scale = GetWorldBoundingBox().Size().DotProduct(DOT_SCALE);
    float newLodDistance = frame.camera_->GetLodDistance(distance_, scale, lodBias_);
    
    if (newLodDistance != lodDistance_)
        lodDistance_ = newLodDistance;
}

Geometry* Drawable::GetLodGeometry(unsigned batchIndex, unsigned level)
{
    // By default return just the batch geometry
    if (batchIndex < batches_.Size())
        return batches_[batchIndex].geometry_;
    else
        return 0;
}

void Drawable::DrawDebugGeometry(DebugRenderer* debug, bool depthTest)
{
    if (debug)
        debug->AddBoundingBox(GetWorldBoundingBox(), Color(0.0f, 1.0f, 0.0f), depthTest);
}

void Drawable::SetDrawDistance(float distance)
{
    drawDistance_ = distance;
    MarkNetworkUpdate();
}

void Drawable::SetShadowDistance(float distance)
{
    shadowDistance_ = distance;
    MarkNetworkUpdate();
}

void Drawable::SetLodBias(float bias)
{
    lodBias_ = Max(bias, M_EPSILON);
    MarkNetworkUpdate();
}

void Drawable::SetViewMask(unsigned mask)
{
    viewMask_ = mask;
    MarkNetworkUpdate();
}

void Drawable::SetLightMask(unsigned mask)
{
    lightMask_ = mask;
    MarkNetworkUpdate();
}

void Drawable::SetShadowMask(unsigned mask)
{
    shadowMask_ = mask;
    MarkNetworkUpdate();
}

void Drawable::SetZoneMask(unsigned mask)
{
    zoneMask_ = mask;
    // Mark dirty to reset cached zone
    OnMarkedDirty(node_);
    MarkNetworkUpdate();
}

void Drawable::SetMaxLights(unsigned num)
{
    maxLights_ = num;
    MarkNetworkUpdate();
}

void Drawable::SetVisible(bool enable)
{
    visible_ = enable;
    MarkNetworkUpdate();
}

void Drawable::SetCastShadows(bool enable)
{
    castShadows_ = enable;
    MarkNetworkUpdate();
}

void Drawable::SetOccluder(bool enable)
{
    occluder_ = enable;
    MarkNetworkUpdate();
}

void Drawable::SetOccludee(bool enable)
{
    if (enable != occludee_)
    {
        occludee_ = enable;
        // Reinsert to octree to make sure octant occlusion does not erroneously hide this drawable
        if (octant_ && !reinsertionQueued_)
            octant_->GetRoot()->QueueReinsertion(this);
        MarkNetworkUpdate();
    }
}

void Drawable::MarkForUpdate()
{
    if (octant_ && !updateQueued_)
        octant_->GetRoot()->QueueUpdate(this);
}

const BoundingBox& Drawable::GetWorldBoundingBox()
{
    if (worldBoundingBoxDirty_)
    {
        OnWorldBoundingBoxUpdate();
        worldBoundingBoxDirty_ = false;
    }
    
    return worldBoundingBox_;
}

void Drawable::SetZone(Zone* zone, bool temporary)
{
    zone_ = zone;
    lastZone_ = zone;
    temporaryZone_ = temporary;
}

void Drawable::SetSortValue(float value)
{
    sortValue_ = value;
}

void Drawable::SetMinMaxZ(float minZ, float maxZ)
{
    minZ_ = minZ;
    maxZ_ = maxZ;
}

void Drawable::MarkInView(const FrameInfo& frame, bool mainView)
{
    if (mainView)
    {
        // Reset zone assignment now if was temporary
        if (temporaryZone_)
        {
            zone_.Reset();
            temporaryZone_ = false;
        }
        
        viewFrameNumber_ = frame.frameNumber_;
        viewFrame_ = &frame;
        viewCamera_ = frame.camera_;
    }
    else
    {
        if (viewFrameNumber_ != frame.frameNumber_ || viewFrame_ != &frame)
        {
            viewFrameNumber_ = frame.frameNumber_;
            viewFrame_ = &frame;
            viewCamera_ = 0;
        }
    }
}

void Drawable::ClearLights()
{
    basePassFlags_ = 0;
    firstLight_ = 0;
    lights_.Clear();
    vertexLights_.Clear();
}

void Drawable::AddLight(Light* light)
{
    if (lights_.Empty())
        firstLight_ = light;
    lights_.Push(light);
}

void Drawable::AddVertexLight(Light* light)
{
    vertexLights_.Push(light);
}

void Drawable::LimitLights()
{
    // Maximum lights value 0 means unlimited
    if (!maxLights_ || lights_.Size() <= maxLights_)
        return;
    
    // If more lights than allowed, move to vertex lights and cut the list
    const BoundingBox& box = GetWorldBoundingBox();
    for (unsigned i = 0; i < lights_.Size(); ++i)
        lights_[i]->SetIntensitySortValue(box);
    
    Sort(lights_.Begin(), lights_.End(), CompareDrawables);
    vertexLights_.Insert(vertexLights_.End(), lights_.Begin() + maxLights_, lights_.End());
    lights_.Resize(maxLights_);
}

void Drawable::LimitVertexLights()
{
    if (vertexLights_.Size() <= MAX_VERTEX_LIGHTS)
        return;
    
    const BoundingBox& box = GetWorldBoundingBox();
    for (unsigned i = vertexLights_.Size() - 1; i < vertexLights_.Size(); --i)
        vertexLights_[i]->SetIntensitySortValue(box);
    
    Sort(vertexLights_.Begin(), vertexLights_.End(), CompareDrawables);
    vertexLights_.Resize(MAX_VERTEX_LIGHTS);
}

Zone* Drawable::GetZone() const
{
    return zone_;
}

Zone* Drawable::GetLastZone() const
{
    return lastZone_;
}

void Drawable::OnNodeSet(Node* node)
{
    if (node)
    {
        AddToOctree();
        node->AddListener(this);
    }
    else
        RemoveFromOctree();
}

void Drawable::OnMarkedDirty(Node* node)
{
    worldBoundingBoxDirty_ = true;
    if (octant_ && !reinsertionQueued_)
        octant_->GetRoot()->QueueReinsertion(this);
    
    if (node == node_)
        zone_.Reset();
}

void Drawable::AddToOctree()
{
    Scene* scene = GetScene();
    if (scene)
    {
        Octree* octree = scene->GetComponent<Octree>();
        if (octree)
        {
            const BoundingBox& box = GetWorldBoundingBox();
            octree->InsertDrawable(this, box.Center(), box.Size());
        }
    }
}

void Drawable::RemoveFromOctree()
{
    if (octant_)
        octant_->RemoveDrawable(this);
}
