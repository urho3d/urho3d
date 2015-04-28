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

#include "../Core/Context.h"
#include "../Graphics/DebugRenderer.h"
#include "../Scene/Node.h"
#include "../Graphics/Octree.h"
#include "../Resource/ResourceCache.h"
#include "../Scene/Scene.h"
#include "../Graphics/TextureCube.h"
#include "../Graphics/Zone.h"

#include "../DebugNew.h"

namespace Urho3D
{

static const Vector3 DEFAULT_BOUNDING_BOX_MIN(-10.0f, -10.0f, -10.0f);
static const Vector3 DEFAULT_BOUNDING_BOX_MAX(10.0f, 10.0f, 10.0f);
static const Color DEFAULT_AMBIENT_COLOR(0.1f, 0.1f, 0.1f);
static const Color DEFAULT_FOG_COLOR(0.0f, 0.0f, 0.0f);
static const float DEFAULT_FOG_START = 250.0f;
static const float DEFAULT_FOG_END = 1000.0f;
static const float DEFAULT_FOG_HEIGHT = 0.0f;
static const float DEFAULT_FOG_HEIGHT_SCALE = 0.5f;

extern const char* SCENE_CATEGORY;

Zone::Zone(Context* context) :
    Drawable(context, DRAWABLE_ZONE),
    inverseWorldDirty_(true),
    heightFog_(false),
    override_(false),
    ambientGradient_(false),
    ambientColor_(DEFAULT_AMBIENT_COLOR),
    fogColor_(DEFAULT_FOG_COLOR),
    fogStart_(DEFAULT_FOG_START),
    fogEnd_(DEFAULT_FOG_END),
    fogHeight_(DEFAULT_FOG_HEIGHT),
    fogHeightScale_(DEFAULT_FOG_HEIGHT_SCALE),
    priority_(0)
{
    boundingBox_ = BoundingBox(DEFAULT_BOUNDING_BOX_MIN, DEFAULT_BOUNDING_BOX_MAX);
}

Zone::~Zone()
{
}

void Zone::RegisterObject(Context* context)
{
    context->RegisterFactory<Zone>(SCENE_CATEGORY);

    ACCESSOR_ATTRIBUTE("Is Enabled", IsEnabled, SetEnabled, bool, true, AM_DEFAULT);
    ATTRIBUTE("Bounding Box Min", Vector3, boundingBox_.min_, DEFAULT_BOUNDING_BOX_MIN, AM_DEFAULT);
    ATTRIBUTE("Bounding Box Max", Vector3, boundingBox_.max_, DEFAULT_BOUNDING_BOX_MAX, AM_DEFAULT);
    ATTRIBUTE("Ambient Color", Color, ambientColor_, DEFAULT_AMBIENT_COLOR, AM_DEFAULT);
    ATTRIBUTE("Fog Color", Color, fogColor_, DEFAULT_FOG_COLOR, AM_DEFAULT);
    ATTRIBUTE("Fog Start", float, fogStart_, DEFAULT_FOG_START, AM_DEFAULT);
    ATTRIBUTE("Fog End", float, fogEnd_, DEFAULT_FOG_END, AM_DEFAULT);
    ATTRIBUTE("Fog Height", float, fogHeight_, DEFAULT_FOG_HEIGHT, AM_DEFAULT);
    ATTRIBUTE("Fog Height Scale", float, fogHeightScale_, DEFAULT_FOG_HEIGHT_SCALE, AM_DEFAULT);
    ATTRIBUTE("Height Fog Mode", bool, heightFog_, false, AM_DEFAULT);
    ATTRIBUTE("Override Mode", bool, override_, false, AM_DEFAULT);
    ATTRIBUTE("Ambient Gradient", bool, ambientGradient_, false, AM_DEFAULT);
    ATTRIBUTE("Priority", int, priority_, 0, AM_DEFAULT);
    MIXED_ACCESSOR_ATTRIBUTE("Zone Texture", GetZoneTextureAttr, SetZoneTextureAttr, ResourceRef, ResourceRef(TextureCube::GetTypeStatic()), AM_DEFAULT);
    ATTRIBUTE("Light Mask", int, lightMask_, DEFAULT_LIGHTMASK, AM_DEFAULT);
    ATTRIBUTE("Shadow Mask", int, shadowMask_, DEFAULT_SHADOWMASK, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE("Zone Mask", GetZoneMask, SetZoneMask, unsigned, DEFAULT_ZONEMASK, AM_DEFAULT);
}

void Zone::OnSetAttribute(const AttributeInfo& attr, const Variant& src)
{
    Serializable::OnSetAttribute(attr, src);

    // If bounding box or priority changes, dirty the drawable as applicable
    if ((attr.offset_ >= offsetof(Zone, boundingBox_) && attr.offset_ < (offsetof(Zone, boundingBox_) + sizeof(BoundingBox))) ||
        attr.offset_ == offsetof(Zone, priority_))
        OnMarkedDirty(node_);
}

void Zone::DrawDebugGeometry(DebugRenderer* debug, bool depthTest)
{
    if (debug && IsEnabledEffective())
        debug->AddBoundingBox(boundingBox_, node_->GetWorldTransform(), Color::GREEN, depthTest);
}

void Zone::SetBoundingBox(const BoundingBox& box)
{
    boundingBox_ = box;
    OnMarkedDirty(node_);
    MarkNetworkUpdate();
}

void Zone::SetAmbientColor(const Color& color)
{
    ambientColor_ = Color(color, 1.0f);
    MarkNetworkUpdate();
}

void Zone::SetFogColor(const Color& color)
{
    fogColor_ = Color(color, 1.0f);
    MarkNetworkUpdate();
}

void Zone::SetFogStart(float start)
{
    if (start < 0.0f)
        start = 0.0f;

    fogStart_ = start;
    MarkNetworkUpdate();
}

void Zone::SetFogEnd(float end)
{
    if (end < 0.0f)
        end = 0.0f;

    fogEnd_ = end;
    MarkNetworkUpdate();
}

void Zone::SetFogHeight(float height)
{
    fogHeight_ = height;
    MarkNetworkUpdate();
}

void Zone::SetFogHeightScale(float scale)
{
    fogHeightScale_ = scale;
    MarkNetworkUpdate();
}

void Zone::SetPriority(int priority)
{
    priority_ = priority;
    MarkNetworkUpdate();
}

void Zone::SetZoneTexture(Texture* texture)
{
    zoneTexture_ = texture;
    MarkNetworkUpdate();
}

void Zone::SetHeightFog(bool enable)
{
    heightFog_ = enable;
    MarkNetworkUpdate();
}

void Zone::SetOverride(bool enable)
{
    override_ = enable;
    MarkNetworkUpdate();
}

void Zone::SetAmbientGradient(bool enable)
{
    ambientGradient_ = enable;
    MarkNetworkUpdate();
}

const Matrix3x4& Zone::GetInverseWorldTransform() const
{
    if (inverseWorldDirty_)
    {
        inverseWorld_ = node_ ? node_->GetWorldTransform().Inverse() : Matrix3x4::IDENTITY;
        inverseWorldDirty_ = false;
    }

    return inverseWorld_;
}

const Color& Zone::GetAmbientStartColor()
{
    if (!ambientGradient_)
        return ambientColor_;

    if (!lastAmbientStartZone_ || !lastAmbientEndZone_)
        UpdateAmbientGradient();

    return ambientStartColor_;
}

const Color& Zone::GetAmbientEndColor()
{
    if (!ambientGradient_)
        return ambientColor_;

    if (!lastAmbientStartZone_ || !lastAmbientEndZone_)
        UpdateAmbientGradient();

    return ambientEndColor_;
}

bool Zone::IsInside(const Vector3& point) const
{
    // Use an oriented bounding box test
    Vector3 localPoint(GetInverseWorldTransform() * point);
    return boundingBox_.IsInside(localPoint) != OUTSIDE;
}

void Zone::SetZoneTextureAttr(const ResourceRef& value)
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    zoneTexture_ = static_cast<Texture*>(cache->GetResource(value.type_, value.name_));
}

ResourceRef Zone::GetZoneTextureAttr() const
{
    return GetResourceRef(zoneTexture_, TextureCube::GetTypeStatic());
}

void Zone::OnMarkedDirty(Node* node)
{
    // Due to the octree query and weak pointer manipulation, is not safe from worker threads
    Scene* scene = GetScene();
    if (scene && scene->IsThreadedUpdate())
    {
        scene->DelayedMarkedDirty(this);
        return;
    }

    Drawable::OnMarkedDirty(node);

    // Clear zone reference from all drawables inside the bounding box, and mark gradient dirty in neighbor zones
    ClearDrawablesZone();

    inverseWorldDirty_ = true;
}

void Zone::OnWorldBoundingBoxUpdate()
{
    worldBoundingBox_ = boundingBox_.Transformed(node_->GetWorldTransform());
}

void Zone::UpdateAmbientGradient()
{
    // In case no neighbor zones are found, reset ambient start/end with own ambient color
    ambientStartColor_ = ambientColor_;
    ambientEndColor_ = ambientColor_;
    lastAmbientStartZone_ = this;
    lastAmbientEndZone_ = this;

    if (octant_)
    {
        const Matrix3x4& worldTransform = node_->GetWorldTransform();
        Vector3 center = boundingBox_.Center();
        Vector3 minZPosition = worldTransform * Vector3(center.x_, center.y_, boundingBox_.min_.z_);
        Vector3 maxZPosition = worldTransform * Vector3(center.x_, center.y_, boundingBox_.max_.z_);

        PODVector<Zone*> result;
        {
            PointOctreeQuery query(reinterpret_cast<PODVector<Drawable*>&>(result), minZPosition, DRAWABLE_ZONE);
            octant_->GetRoot()->GetDrawables(query);
        }

        // Gradient start position: get the highest priority zone that is not this zone
        int bestPriority = M_MIN_INT;
        Zone* bestZone = 0;
        for (PODVector<Zone*>::ConstIterator i = result.Begin(); i != result.End(); ++i)
        {
            Zone* zone = *i;
            int priority = zone->GetPriority();
            if (priority > bestPriority && zone != this && zone->IsInside(minZPosition))
            {
                bestZone = zone;
                bestPriority = priority;
            }
        }

        if (bestZone)
        {
            ambientStartColor_ = bestZone->GetAmbientColor();
            lastAmbientStartZone_ = bestZone;
        }

        // Do the same for gradient end position
        {
            PointOctreeQuery query(reinterpret_cast<PODVector<Drawable*>&>(result), maxZPosition, DRAWABLE_ZONE);
            octant_->GetRoot()->GetDrawables(query);
        }
        bestPriority = M_MIN_INT;
        bestZone = 0;

        for (PODVector<Zone*>::ConstIterator i = result.Begin(); i != result.End(); ++i)
        {
            Zone* zone = *i;
            int priority = zone->GetPriority();
            if (priority > bestPriority && zone != this && zone->IsInside(maxZPosition))
            {
                bestZone = zone;
                bestPriority = priority;
            }
        }

        if (bestZone)
        {
            ambientEndColor_ = bestZone->GetAmbientColor();
            lastAmbientEndZone_ = bestZone;
        }
    }
}

void Zone::OnRemoveFromOctree()
{
    ClearDrawablesZone();
}

void Zone::ClearDrawablesZone()
{
    if (octant_ && lastWorldBoundingBox_.defined_)
    {
        PODVector<Drawable*> result;
        BoxOctreeQuery query(result, lastWorldBoundingBox_, DRAWABLE_GEOMETRY | DRAWABLE_ZONE);
        octant_->GetRoot()->GetDrawables(query);

        for (PODVector<Drawable*>::Iterator i = result.Begin(); i != result.End(); ++i)
        {
            Drawable* drawable = *i;
            unsigned drawableFlags = drawable->GetDrawableFlags();
            if (drawableFlags & DRAWABLE_GEOMETRY)
                drawable->SetZone(0);
            else if (drawableFlags & DRAWABLE_ZONE)
            {
                Zone* zone = static_cast<Zone*>(drawable);
                zone->lastAmbientStartZone_.Reset();
                zone->lastAmbientEndZone_.Reset();
            }
        }
    }

    lastWorldBoundingBox_ = GetWorldBoundingBox();
    lastAmbientStartZone_.Reset();
    lastAmbientEndZone_.Reset();
}

}
