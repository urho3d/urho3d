//

// Copyright (c) 2008-2015 the Urho3D project.
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

#include "../Graphics/Camera.h"
#include "../Core/Context.h"
#include "../Graphics/DebugRenderer.h"
#include "../IO/Log.h"
#include "../Graphics/Material.h"
#include "../Graphics/Octree.h"
#include "../Graphics/Renderer.h"
#include "../Scene/Scene.h"
#include "../Container/Sort.h"
#include "../Graphics/Zone.h"

#include "../DebugNew.h"

namespace Urho3D
{

const char* GEOMETRY_CATEGORY = "Geometry";

SourceBatch::SourceBatch() :
    distance_(0.0f),
    geometry_(0),
    worldTransform_(&Matrix3x4::IDENTITY),
    numWorldTransforms_(1),
    geometryType_(GEOM_STATIC)
{
}

SourceBatch::~SourceBatch()
{
}

Drawable::Drawable(Context* context, unsigned char drawableFlags) :
    Component(context),
    drawableFlags_(drawableFlags),
    worldBoundingBoxDirty_(true),
    castShadows_(false),
    occluder_(false),
    occludee_(true),
    updateQueued_(false),
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
    zone_(0),
    zoneDirty_(false)
{
}

Drawable::~Drawable()
{
    RemoveFromOctree();
}

void Drawable::RegisterObject(Context* context)
{
    ATTRIBUTE("Max Lights", int, maxLights_, 0, AM_DEFAULT);
    ATTRIBUTE("View Mask", int, viewMask_, DEFAULT_VIEWMASK, AM_DEFAULT);
    ATTRIBUTE("Light Mask", int, lightMask_, DEFAULT_LIGHTMASK, AM_DEFAULT);
    ATTRIBUTE("Shadow Mask", int, shadowMask_, DEFAULT_SHADOWMASK, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE("Zone Mask", GetZoneMask, SetZoneMask, unsigned, DEFAULT_ZONEMASK, AM_DEFAULT);
}

void Drawable::OnSetEnabled()
{
    bool enabled = IsEnabledEffective();

    if (enabled && !octant_)
        AddToOctree();
    else if (!enabled && octant_)
        RemoveFromOctree();
}

void Drawable::ProcessRayQuery(const RayOctreeQuery& query, PODVector<RayQueryResult>& results)
{
    float distance = query.ray_.HitDistance(GetWorldBoundingBox());
    if (distance < query.maxDistance_)
    {
        RayQueryResult result;
        result.position_ = query.ray_.origin_ + distance * query.ray_.direction_;
        result.normal_ = -query.ray_.direction_;
        result.distance_ = distance;
        result.drawable_ = this;
        result.node_ = GetNode();
        result.subObject_ = M_MAX_UNSIGNED;
        results.Push(result);
    }
}

void Drawable::Update(const FrameInfo& frame)
{
}

void Drawable::UpdateBatches(const FrameInfo& frame)
{
    const BoundingBox& worldBoundingBox = GetWorldBoundingBox();
    const Matrix3x4& worldTransform = node_->GetWorldTransform();
    distance_ = frame.camera_->GetDistance(worldBoundingBox.Center());

    for (unsigned i = 0; i < batches_.Size(); ++i)
    {
        batches_[i].distance_ = distance_;
        batches_[i].worldTransform_ = &worldTransform;
    }

    float scale = worldBoundingBox.Size().DotProduct(DOT_SCALE);
    float newLodDistance = frame.camera_->GetLodDistance(distance_, scale, lodBias_);

    if (newLodDistance != lodDistance_)
        lodDistance_ = newLodDistance;
}

void Drawable::UpdateGeometry(const FrameInfo& frame)
{
}

Geometry* Drawable::GetLodGeometry(unsigned batchIndex, unsigned level)
{
    // By default return the visible batch geometry
    if (batchIndex < batches_.Size())
        return batches_[batchIndex].geometry_;
    else
        return 0;
}

bool Drawable::DrawOcclusion(OcclusionBuffer* buffer)
{
    return true;
}

void Drawable::DrawDebugGeometry(DebugRenderer* debug, bool depthTest)
{
    if (debug && IsEnabledEffective())
        debug->AddBoundingBox(GetWorldBoundingBox(), Color::GREEN, depthTest);
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
        if (octant_ && !updateQueued_)
            octant_->GetRoot()->QueueUpdate(this);
        MarkNetworkUpdate();
    }
}

void Drawable::MarkForUpdate()
{
    if (!updateQueued_ && octant_)
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

bool Drawable::IsInView() const
{
    // Note: in headless mode there is no renderer subsystem and no view frustum tests are performed, so return
    // always false in that case
    Renderer* renderer = GetSubsystem<Renderer>();
    return renderer && viewFrameNumber_ == renderer->GetFrameInfo().frameNumber_ && !viewCameras_.Empty();
}

bool Drawable::IsInView(Camera* camera) const
{
    Renderer* renderer = GetSubsystem<Renderer>();
    return renderer && viewFrameNumber_ == renderer->GetFrameInfo().frameNumber_ && (!camera || viewCameras_.Contains(camera));
}

bool Drawable::IsInView(const FrameInfo& frame, bool anyCamera) const
{
    return viewFrameNumber_ == frame.frameNumber_ && (anyCamera || viewCameras_.Contains(frame.camera_));
}

void Drawable::SetZone(Zone* zone, bool temporary)
{
    zone_ = zone;

    // If the zone assignment was temporary (inconclusive) set the dirty flag so that it will be re-evaluated on the next frame
    zoneDirty_ = temporary;
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

void Drawable::MarkInView(const FrameInfo& frame)
{
    if (frame.frameNumber_ != viewFrameNumber_)
    {
        viewFrameNumber_ = frame.frameNumber_;
        viewCameras_.Clear();
    }
    
    viewCameras_.Insert(frame.camera_);
}

void Drawable::MarkInView(unsigned frameNumber, Camera* camera)
{
    if (frameNumber != viewFrameNumber_)
    {
        viewFrameNumber_ = frameNumber;
        viewCameras_.Clear();
    }
    
    if (camera)
        viewCameras_.Insert(camera);
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
    if (!updateQueued_ && octant_)
        octant_->GetRoot()->QueueUpdate(this);

    // Mark zone assignment dirty when transform changes
    if (node == node_)
        zoneDirty_ = true;
}

void Drawable::AddToOctree()
{
    // Do not add to octree when disabled
    if (!IsEnabledEffective())
        return;

    Scene* scene = GetScene();
    if (scene)
    {
        Octree* octree = scene->GetComponent<Octree>();
        if (octree)
            octree->InsertDrawable(this);
        else
            LOGERROR("No Octree component in scene, drawable will not render");
    }
    else
    {
        // We have a mechanism for adding detached nodes to an octree manually, so do not log this error
        //LOGERROR("Node is detached from scene, drawable will not render");
    }
}

void Drawable::RemoveFromOctree()
{
    if (octant_)
    {
        Octree* octree = octant_->GetRoot();
        if (updateQueued_)
            octree->CancelUpdate(this);
        
        // Perform subclass specific deinitialization if necessary
        OnRemoveFromOctree();
        
        octant_->RemoveDrawable(this);
    }
}

}
