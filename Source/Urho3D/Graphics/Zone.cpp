// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include "../Precompiled.h"

#include "../Core/Context.h"
#include "../Graphics/DebugRenderer.h"
#include "../Graphics/Octree.h"
#include "../Graphics/Zone.h"
#include "../GraphicsAPI/TextureCube.h"
#include "../Resource/ResourceCache.h"
#include "../Scene/Node.h"
#include "../Scene/Scene.h"

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
    Drawable(context, DrawableTypes::Zone),
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

Zone::~Zone() = default;

void Zone::RegisterObject(Context* context)
{
    context->RegisterFactory<Zone>(SCENE_CATEGORY);

    URHO3D_ACCESSOR_ATTRIBUTE("Is Enabled", IsEnabled, SetEnabled, bool, true, AM_DEFAULT);
    URHO3D_ATTRIBUTE_EX("Bounding Box Min", Vector3, boundingBox_.min_, MarkNodeDirty, DEFAULT_BOUNDING_BOX_MIN, AM_DEFAULT);
    URHO3D_ATTRIBUTE_EX("Bounding Box Max", Vector3, boundingBox_.max_, MarkNodeDirty, DEFAULT_BOUNDING_BOX_MAX, AM_DEFAULT);
    URHO3D_ATTRIBUTE("Ambient Color", Color, ambientColor_, DEFAULT_AMBIENT_COLOR, AM_DEFAULT);
    URHO3D_ATTRIBUTE("Fog Color", Color, fogColor_, DEFAULT_FOG_COLOR, AM_DEFAULT);
    URHO3D_ATTRIBUTE("Fog Start", float, fogStart_, DEFAULT_FOG_START, AM_DEFAULT);
    URHO3D_ATTRIBUTE("Fog End", float, fogEnd_, DEFAULT_FOG_END, AM_DEFAULT);
    URHO3D_ATTRIBUTE("Fog Height", float, fogHeight_, DEFAULT_FOG_HEIGHT, AM_DEFAULT);
    URHO3D_ATTRIBUTE("Fog Height Scale", float, fogHeightScale_, DEFAULT_FOG_HEIGHT_SCALE, AM_DEFAULT);
    URHO3D_ATTRIBUTE("Height Fog Mode", bool, heightFog_, false, AM_DEFAULT);
    URHO3D_ATTRIBUTE("Override Mode", bool, override_, false, AM_DEFAULT);
    URHO3D_ATTRIBUTE("Ambient Gradient", bool, ambientGradient_, false, AM_DEFAULT);
    URHO3D_ATTRIBUTE_EX("Priority", int, priority_, MarkNodeDirty, 0, AM_DEFAULT);
    URHO3D_MIXED_ACCESSOR_ATTRIBUTE("Zone Texture", GetZoneTextureAttr, SetZoneTextureAttr, ResourceRef,
        ResourceRef(TextureCube::GetTypeStatic()), AM_DEFAULT);
    URHO3D_ATTRIBUTE("Light Mask", u32, lightMask_, DEFAULT_LIGHTMASK, AM_DEFAULT);
    URHO3D_ATTRIBUTE("Shadow Mask", u32, shadowMask_, DEFAULT_SHADOWMASK, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Zone Mask", GetZoneMask, SetZoneMask, u32, DEFAULT_ZONEMASK, AM_DEFAULT);
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
    ambientColor_ = color;
    MarkNetworkUpdate();
}

void Zone::SetFogColor(const Color& color)
{
    fogColor_ = color;
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
    auto* cache = GetSubsystem<ResourceCache>();
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

        Vector<Zone*> result;
        {
            PointOctreeQuery query(reinterpret_cast<Vector<Drawable*>&>(result), minZPosition, DrawableTypes::Zone);
            octant_->GetRoot()->GetDrawables(query);
        }

        // Gradient start position: get the highest priority zone that is not this zone
        int bestPriority = M_MIN_INT;
        Zone* bestZone = nullptr;
        for (Vector<Zone*>::ConstIterator i = result.Begin(); i != result.End(); ++i)
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
            PointOctreeQuery query(reinterpret_cast<Vector<Drawable*>&>(result), maxZPosition, DrawableTypes::Zone);
            octant_->GetRoot()->GetDrawables(query);
        }
        bestPriority = M_MIN_INT;
        bestZone = nullptr;

        for (Vector<Zone*>::ConstIterator i = result.Begin(); i != result.End(); ++i)
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
    if (octant_ && lastWorldBoundingBox_.Defined())
    {
        Vector<Drawable*> result;
        BoxOctreeQuery query(result, lastWorldBoundingBox_, DrawableTypes::Geometry | DrawableTypes::Zone);
        octant_->GetRoot()->GetDrawables(query);

        for (Vector<Drawable*>::Iterator i = result.Begin(); i != result.End(); ++i)
        {
            Drawable* drawable = *i;
            DrawableTypes drawableType = drawable->GetDrawableType();
            if (drawableType == DrawableTypes::Geometry)
                drawable->SetZone(nullptr);
            else // drawableType == DrawableTypes::Zone
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
