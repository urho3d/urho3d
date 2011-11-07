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
    octant_(0),
    drawDistance_(0.0f),
    shadowDistance_(0.0f),
    lodBias_(1.0f),
    viewMask_(DEFAULT_VIEWMASK),
    lightMask_(DEFAULT_LIGHTMASK),
    shadowMask_(DEFAULT_SHADOWMASK),
    zoneMask_(DEFAULT_ZONEMASK),
    maxLights_(0),
    distance_(0.0f),
    lodDistance_(0.0f),
    sortValue_(0.0f),
    viewFrameNumber_(0),
    viewFrame_(0),
    viewCamera_(0),
    firstLight_(0),
    drawableFlags_(0),
    visible_(true),
    castShadows_(false),
    occluder_(false),
    worldBoundingBoxDirty_(true),
    updateQueued_(false),
    reinsertionQueued_(false)
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
    if (distance < query.maxDistance_)
    {
        RayQueryResult result;
        result.drawable_ = this;
        result.node_ = GetNode();
        result.distance_ = distance;
        result.subObject_ = M_MAX_UNSIGNED;
        results.Push(result);
    }
}

void Drawable::UpdateDistance(const FrameInfo& frame)
{
    distance_ = frame.camera_->GetDistance(GetWorldPosition());
    
    float scale = GetWorldBoundingBox().Size().DotProduct(DOT_SCALE);
    float newLodDistance = frame.camera_->GetLodDistance(distance_, scale, lodBias_);
    
    if (newLodDistance != lodDistance_)
        lodDistance_ = newLodDistance;
}

void Drawable::DrawDebugGeometry(DebugRenderer* debug, bool depthTest)
{
    debug->AddBoundingBox(GetWorldBoundingBox(), Color(0.0f, 1.0f, 0.0f), depthTest);
}

void Drawable::SetDrawDistance(float distance)
{
    drawDistance_ = distance;
}

void Drawable::SetShadowDistance(float distance)
{
    shadowDistance_ = distance;
}

void Drawable::SetLodBias(float bias)
{
    lodBias_ = Max(bias, M_EPSILON);
}

void Drawable::SetViewMask(unsigned mask)
{
    viewMask_ = mask;
}

void Drawable::SetLightMask(unsigned mask)
{
    lightMask_ = mask;
}

void Drawable::SetShadowMask(unsigned mask)
{
    shadowMask_ = mask;
}

void Drawable::SetZoneMask(unsigned mask)
{
    zoneMask_ = mask;
    // Mark dirty to reset cached zone
    OnMarkedDirty(node_);
}

void Drawable::SetMaxLights(unsigned num)
{
    maxLights_ = num;
}

void Drawable::SetVisible(bool enable)
{
    visible_ = enable;
}

void Drawable::SetCastShadows(bool enable)
{
    castShadows_ = enable;
}

void Drawable::SetOccluder(bool enable)
{
    occluder_ = enable;
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

void Drawable::SetZone(Zone* zone)
{
    zone_ = zone;
    lastZone_ = zone;
}

void Drawable::SetSortValue(float value)
{
    sortValue_ = value;
}

void Drawable::MarkInView(const FrameInfo& frame, bool mainView)
{
    if (mainView)
    {
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
    for (unsigned i = 0; i < basePassFlags_.Size(); ++i)
        basePassFlags_[i] = 0;
    firstLight_ = 0;
    lights_.Clear();
}

void Drawable::AddLight(Light* light)
{
    if (lights_.Empty())
        firstLight_ = light;
    lights_.Push(light);
}

void Drawable::LimitLights()
{
    // Maximum lights value 0 means unlimited
    if (!maxLights_)
        return;
    
    for (unsigned i = 0; i < lights_.Size(); ++i)
        lights_[i]->SetIntensitySortValue(GetWorldBoundingBox());
    
    Sort(lights_.Begin(), lights_.End(), CompareDrawables);
    
    // If more lights than allowed, cut the list
    if (lights_.Size() > maxLights_)
        lights_.Resize(maxLights_);
}

void Drawable::SetBasePass(unsigned batchIndex)
{
    unsigned index = batchIndex >> 5;
    if (basePassFlags_.Size() <= index)
    {
        unsigned oldSize = basePassFlags_.Size();
        basePassFlags_.Resize(index + 1);
        for (unsigned i = oldSize; i <= index; ++i)
            basePassFlags_[i] = 0;
    }
    basePassFlags_[index] |= (1 << (batchIndex & 31));
}

Zone* Drawable::GetZone() const
{
    return zone_;
}

Zone* Drawable::GetLastZone() const
{
    return lastZone_;
}

bool Drawable::HasBasePass(unsigned batchIndex) const
{
    unsigned index = batchIndex >> 5;
    if (index < basePassFlags_.Size())
        return (basePassFlags_[index] & (1 << (batchIndex & 31))) != 0;
    else
        return false;
}

void Drawable::OnNodeSet(Node* node)
{
    // Insert initially into the root octant
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
    if (node == node_)
    {
        worldBoundingBoxDirty_ = true;
        zone_.Reset();
        if (octant_ && !reinsertionQueued_)
            octant_->GetRoot()->QueueReinsertion(this);
    }
}

void Drawable::AddToOctree()
{
    Scene* scene = node_->GetScene();
    if (scene)
    {
        Octree* octree = scene->GetComponent<Octree>();
        if (octree)
            octree->AddDrawable(this);
    }
}

void Drawable::RemoveFromOctree()
{
    if (octant_)
    {
        Octree* octree = octant_->GetRoot();
        octree->CancelUpdate(this);
        octree->CancelReinsertion(this);
        octant_->RemoveDrawable(this);
    }
}
