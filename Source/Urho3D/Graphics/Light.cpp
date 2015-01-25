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

#include "../Graphics/Camera.h"
#include "../Core/Context.h"
#include "../Graphics/DebugRenderer.h"
#include "../Graphics/Graphics.h"
#include "../Graphics/Light.h"
#include "../Scene/Node.h"
#include "../Graphics/OctreeQuery.h"
#include "../Core/Profiler.h"
#include "../Resource/ResourceCache.h"
#include "../Graphics/Texture2D.h"
#include "../Graphics/TextureCube.h"

#include "../DebugNew.h"

namespace Urho3D
{

extern const char* SCENE_CATEGORY;

static const LightType DEFAULT_LIGHTTYPE = LIGHT_POINT;
static const float DEFAULT_RANGE = 10.0f;
static const float DEFAULT_LIGHT_FOV = 30.0f;
static const float DEFAULT_SPECULARINTENSITY = 1.0f;
static const float DEFAULT_BRIGHTNESS = 1.0f;
static const float DEFAULT_CONSTANTBIAS = 0.0002f;
static const float DEFAULT_SLOPESCALEDBIAS = 0.5f;
static const float DEFAULT_BIASAUTOADJUST = 1.0f;
static const float DEFAULT_SHADOWFADESTART = 0.8f;
static const float DEFAULT_SHADOWQUANTIZE = 0.5f;
static const float DEFAULT_SHADOWMINVIEW = 3.0f;
static const float DEFAULT_SHADOWNEARFARRATIO = 0.002f;
static const float DEFAULT_SHADOWSPLIT = 1000.0f;

static const char* typeNames[] =
{
    "Directional",
    "Spot",
    "Point",
    0
};

void BiasParameters::Validate()
{
    constantBias_ = Clamp(constantBias_, -1.0f, 1.0f);
    slopeScaledBias_ = Clamp(slopeScaledBias_, -16.0f, 16.0f);
}

void CascadeParameters::Validate()
{
    for (unsigned i = 0; i < MAX_CASCADE_SPLITS; ++i)
        splits_[i] = Max(splits_[i], 0.0f);
    fadeStart_ = Clamp(fadeStart_, M_EPSILON, 1.0f);
}

void FocusParameters::Validate()
{
    quantize_ = Max(quantize_, SHADOW_MIN_QUANTIZE);
    minView_ = Max(minView_, SHADOW_MIN_VIEW);
}

Light::Light(Context* context) :
    Drawable(context, DRAWABLE_LIGHT),
    lightType_(DEFAULT_LIGHTTYPE),
    shadowBias_(BiasParameters(DEFAULT_CONSTANTBIAS, DEFAULT_SLOPESCALEDBIAS)),
    shadowCascade_(CascadeParameters(DEFAULT_SHADOWSPLIT, 0.0f, 0.0f, 0.0f, DEFAULT_SHADOWFADESTART)),
    shadowFocus_(FocusParameters(true, true, true, DEFAULT_SHADOWQUANTIZE, DEFAULT_SHADOWMINVIEW)),
    lightQueue_(0),
    specularIntensity_(DEFAULT_SPECULARINTENSITY),
    brightness_(DEFAULT_BRIGHTNESS),
    range_(DEFAULT_RANGE),
    fov_(DEFAULT_LIGHT_FOV),
    aspectRatio_(1.0f),
    fadeDistance_(0.0f),
    shadowFadeDistance_(0.0f),
    shadowIntensity_(0.0f),
    shadowResolution_(1.0f),
    shadowNearFarRatio_(DEFAULT_SHADOWNEARFARRATIO),
    perVertex_(false)
{
}

Light::~Light()
{
}

void Light::RegisterObject(Context* context)
{
    context->RegisterFactory<Light>(SCENE_CATEGORY);

    ACCESSOR_ATTRIBUTE("Is Enabled", IsEnabled, SetEnabled, bool, true, AM_DEFAULT);
    ENUM_ACCESSOR_ATTRIBUTE("Light Type", GetLightType, SetLightType, LightType, typeNames, DEFAULT_LIGHTTYPE, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE("Color", GetColor, SetColor, Color, Color::WHITE, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE("Specular Intensity", GetSpecularIntensity, SetSpecularIntensity, float, DEFAULT_SPECULARINTENSITY, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE("Brightness Multiplier", GetBrightness, SetBrightness, float, DEFAULT_BRIGHTNESS, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE("Range", GetRange, SetRange, float, DEFAULT_RANGE, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE("Spot FOV", GetFov, SetFov, float, DEFAULT_LIGHT_FOV, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE("Spot Aspect Ratio", GetAspectRatio, SetAspectRatio, float, 1.0f, AM_DEFAULT);
    MIXED_ACCESSOR_ATTRIBUTE("Attenuation Texture", GetRampTextureAttr, SetRampTextureAttr, ResourceRef, ResourceRef(Texture2D::GetTypeStatic()), AM_DEFAULT);
    MIXED_ACCESSOR_ATTRIBUTE("Light Shape Texture", GetShapeTextureAttr, SetShapeTextureAttr, ResourceRef, ResourceRef(Texture2D::GetTypeStatic()), AM_DEFAULT);
    ACCESSOR_ATTRIBUTE("Can Be Occluded", IsOccludee, SetOccludee, bool, true, AM_DEFAULT);
    ATTRIBUTE("Cast Shadows", bool, castShadows_, false, AM_DEFAULT);
    ATTRIBUTE("Per Vertex", bool, perVertex_, false, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE("Draw Distance", GetDrawDistance, SetDrawDistance, float, 0.0f, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE("Fade Distance", GetFadeDistance, SetFadeDistance, float, 0.0f, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE("Shadow Distance", GetShadowDistance, SetShadowDistance, float, 0.0f, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE("Shadow Fade Distance", GetShadowFadeDistance, SetShadowFadeDistance, float, 0.0f, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE("Shadow Intensity", GetShadowIntensity, SetShadowIntensity, float, 0.0f, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE("Shadow Resolution", GetShadowResolution, SetShadowResolution, float, 1.0f, AM_DEFAULT);
    ATTRIBUTE("Focus To Scene", bool, shadowFocus_.focus_, true, AM_DEFAULT);
    ATTRIBUTE("Non-uniform View", bool, shadowFocus_.nonUniform_, true, AM_DEFAULT);
    ATTRIBUTE("Auto-Reduce Size", bool, shadowFocus_.autoSize_, true, AM_DEFAULT);
    ATTRIBUTE("CSM Splits", Vector4, shadowCascade_.splits_, Vector4(DEFAULT_SHADOWSPLIT, 0.0f, 0.0f, 0.0f), AM_DEFAULT);
    ATTRIBUTE("CSM Fade Start", float, shadowCascade_.fadeStart_, DEFAULT_SHADOWFADESTART, AM_DEFAULT);
    ATTRIBUTE("CSM Bias Auto Adjust", float, shadowCascade_.biasAutoAdjust_, DEFAULT_BIASAUTOADJUST, AM_DEFAULT);
    ATTRIBUTE("View Size Quantize", float, shadowFocus_.quantize_, DEFAULT_SHADOWQUANTIZE, AM_DEFAULT);
    ATTRIBUTE("View Size Minimum", float, shadowFocus_.minView_, DEFAULT_SHADOWMINVIEW, AM_DEFAULT);
    ATTRIBUTE("Depth Constant Bias", float, shadowBias_.constantBias_, DEFAULT_CONSTANTBIAS, AM_DEFAULT);
    ATTRIBUTE("Depth Slope Bias", float, shadowBias_.slopeScaledBias_, DEFAULT_SLOPESCALEDBIAS, AM_DEFAULT);
    ATTRIBUTE("Near/Farclip Ratio", float, shadowNearFarRatio_, DEFAULT_SHADOWNEARFARRATIO, AM_DEFAULT);
    ATTRIBUTE("View Mask", int, viewMask_, DEFAULT_VIEWMASK, AM_DEFAULT);
    ATTRIBUTE("Light Mask", int, lightMask_, DEFAULT_LIGHTMASK, AM_DEFAULT);
}

void Light::OnSetAttribute(const AttributeInfo& attr, const Variant& src)
{
    Serializable::OnSetAttribute(attr, src);

    // Validate the bias, cascade & focus parameters
    if (attr.offset_ >= offsetof(Light, shadowBias_) && attr.offset_ < (offsetof(Light, shadowBias_) + sizeof(BiasParameters)))
        shadowBias_.Validate();
    else if (attr.offset_ >= offsetof(Light, shadowCascade_) && attr.offset_ < (offsetof(Light, shadowCascade_) + sizeof(CascadeParameters)))
        shadowCascade_.Validate();
    else if (attr.offset_ >= offsetof(Light, shadowFocus_) && attr.offset_ < (offsetof(Light, shadowFocus_) + sizeof(FocusParameters)))
        shadowFocus_.Validate();
}

void Light::ProcessRayQuery(const RayOctreeQuery& query, PODVector<RayQueryResult>& results)
{
    // Do not record a raycast result for a directional light, as it would block all other results
    if (lightType_ == LIGHT_DIRECTIONAL)
        return;

    float distance;
    switch (query.level_)
    {
    case RAY_AABB:
        Drawable::ProcessRayQuery(query, results);
        return;

    case RAY_OBB:
        {
            Matrix3x4 inverse(node_->GetWorldTransform().Inverse());
            Ray localRay = query.ray_.Transformed(inverse);
            distance = localRay.HitDistance(GetWorldBoundingBox().Transformed(inverse));
            if (distance >= query.maxDistance_)
                return;
        }
        break;

    case RAY_TRIANGLE:
        if (lightType_ == LIGHT_SPOT)
        {
            distance = query.ray_.HitDistance(GetFrustum());
            if (distance >= query.maxDistance_)
                return;
        }
        else
        {
            distance = query.ray_.HitDistance(Sphere(node_->GetWorldPosition(), range_));
            if (distance >= query.maxDistance_)
                return;
        }
        break;
    }

    // If the code reaches here then we have a hit
    RayQueryResult result;
    result.position_ = query.ray_.origin_ + distance * query.ray_.direction_;
    result.normal_ = -query.ray_.direction_;
    result.distance_ = distance;
    result.drawable_ = this;
    result.node_ = node_;
    result.subObject_ = M_MAX_UNSIGNED;
    results.Push(result);
}

void Light::UpdateBatches(const FrameInfo& frame)
{
    switch (lightType_)
    {
    case LIGHT_DIRECTIONAL:
        // Directional light affects the whole scene, so it is always "closest"
        distance_ = 0.0f;
        break;

    default:
        distance_ = frame.camera_->GetDistance(node_->GetWorldPosition());
        break;
    }
}

void Light::DrawDebugGeometry(DebugRenderer* debug, bool depthTest)
{
    Color color = GetEffectiveColor();

    if (debug && IsEnabledEffective())
    {
        switch (lightType_)
        {
        case LIGHT_DIRECTIONAL:
            {
                Vector3 start = node_->GetWorldPosition();
                Vector3 end = start + node_->GetWorldDirection() * 10.f;
                for (int i = -1; i < 2; ++i)
                {
                    for (int j = -1; j < 2; ++j)
                    {
                        Vector3 offset = Vector3::UP * (5.f * i) + Vector3::RIGHT * (5.f * j);
                        debug->AddSphere(Sphere(start + offset, 0.1f), color, depthTest);
                        debug->AddLine(start + offset, end + offset, color, depthTest);
                    }
                }
            }
            break;

        case LIGHT_SPOT:
            debug->AddFrustum(GetFrustum(), color, depthTest);
            break;

        case LIGHT_POINT:
            debug->AddSphere(Sphere(node_->GetWorldPosition(), range_), color, depthTest);
            break;
        }
    }
}

void Light::SetLightType(LightType type)
{
    lightType_ = type;
    OnMarkedDirty(node_);
    MarkNetworkUpdate();
}

void Light::SetPerVertex(bool enable)
{
    perVertex_ = enable;
    MarkNetworkUpdate();
}

void Light::SetColor(const Color& color)
{
    color_ = Color(color.r_, color.g_, color.b_, 1.0f);
    MarkNetworkUpdate();
}

void Light::SetSpecularIntensity(float intensity)
{
    specularIntensity_ = Max(intensity, 0.0f);
    MarkNetworkUpdate();
}

void Light::SetBrightness(float brightness)
{
    brightness_ = brightness;
    MarkNetworkUpdate();
}

void Light::SetRange(float range)
{
    range_ = Max(range, 0.0f);
    OnMarkedDirty(node_);
    MarkNetworkUpdate();
}

void Light::SetFov(float fov)
{
    fov_ = Clamp(fov, 0.0f, M_MAX_FOV);
    OnMarkedDirty(node_);
    MarkNetworkUpdate();
}

void Light::SetAspectRatio(float aspectRatio)
{
    aspectRatio_ = Max(aspectRatio, M_EPSILON);
    OnMarkedDirty(node_);
    MarkNetworkUpdate();
}

void Light::SetShadowNearFarRatio(float nearFarRatio)
{
    shadowNearFarRatio_ = Clamp(nearFarRatio, 0.0f, 0.5f);
    MarkNetworkUpdate();
}

void Light::SetFadeDistance(float distance)
{
    fadeDistance_ = Max(distance, 0.0f);
    MarkNetworkUpdate();
}

void Light::SetShadowBias(const BiasParameters& parameters)
{
    shadowBias_ = parameters;
    shadowBias_.Validate();
    MarkNetworkUpdate();
}

void Light::SetShadowCascade(const CascadeParameters& parameters)
{
    shadowCascade_ = parameters;
    shadowCascade_.Validate();
    MarkNetworkUpdate();
}

void Light::SetShadowFocus(const FocusParameters& parameters)
{
    shadowFocus_ = parameters;
    shadowFocus_.Validate();
    MarkNetworkUpdate();
}

void Light::SetShadowFadeDistance(float distance)
{
    shadowFadeDistance_ = Max(distance, 0.0f);
    MarkNetworkUpdate();
}

void Light::SetShadowIntensity(float intensity)
{
    shadowIntensity_ = Clamp(intensity, 0.0f, 1.0f);
    MarkNetworkUpdate();
}

void Light::SetShadowResolution(float resolution)
{
    shadowResolution_ = Clamp(resolution, 0.125f, 1.0f);
    MarkNetworkUpdate();
}

void Light::SetRampTexture(Texture* texture)
{
    rampTexture_ = texture;
    MarkNetworkUpdate();
}

void Light::SetShapeTexture(Texture* texture)
{
    shapeTexture_ = texture;
    MarkNetworkUpdate();
}

Frustum Light::GetFrustum() const
{
    // Note: frustum is unaffected by node or parent scale
    Matrix3x4 frustumTransform(node_ ? Matrix3x4(node_->GetWorldPosition(), node_->GetWorldRotation(), 1.0f) :
        Matrix3x4::IDENTITY);
    Frustum ret;
    ret.Define(fov_, aspectRatio_, 1.0f, M_MIN_NEARCLIP, range_, frustumTransform);
    return ret;
}

int Light::GetNumShadowSplits() const
{
    int ret = 1;

    if (shadowCascade_.splits_[1] > shadowCascade_.splits_[0])
    {
        ++ret;
        if (shadowCascade_.splits_[2] > shadowCascade_.splits_[1])
        {
            ++ret;
            if (shadowCascade_.splits_[3] > shadowCascade_.splits_[2])
                ++ret;
        }
    }

    ret = Min(ret, MAX_CASCADE_SPLITS);
    // Shader Model 2 can only support 3 splits max. due to pixel shader instruction count limits
    if (ret == 4)
    {
        Graphics* graphics = GetSubsystem<Graphics>();
        if (graphics && !graphics->GetSM3Support())
            --ret;
    }

    return ret;
}

const Matrix3x4& Light::GetVolumeTransform(Camera* camera)
{
    if (!node_)
        return Matrix3x4::IDENTITY;

    switch (lightType_)
    {
    case LIGHT_DIRECTIONAL:
        {
            Matrix3x4 quadTransform;
            Vector3 near, far;
            // Position the directional light quad in halfway between far & near planes to prevent depth clipping
            camera->GetFrustumSize(near, far);
            quadTransform.SetTranslation(Vector3(0.0f, 0.0f, (camera->GetNearClip() + camera->GetFarClip()) * 0.5f));
            quadTransform.SetScale(Vector3(far.x_, far.y_, 1.0f)); // Will be oversized, but doesn't matter (gets frustum clipped)
            volumeTransform_ = camera->GetEffectiveWorldTransform() * quadTransform;
            break;
        }

    case LIGHT_SPOT:
        {
            float yScale = tanf(fov_ * M_DEGTORAD * 0.5f) * range_;
            float xScale = aspectRatio_ * yScale;
            volumeTransform_ = Matrix3x4(node_->GetWorldPosition(), node_->GetWorldRotation(), Vector3(xScale, yScale, range_));
        }
        break;

    case LIGHT_POINT:
        volumeTransform_ = Matrix3x4(node_->GetWorldPosition(), Quaternion::IDENTITY, range_);
        break;
    }

    return volumeTransform_;
}

void Light::SetRampTextureAttr(const ResourceRef& value)
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    rampTexture_ = static_cast<Texture*>(cache->GetResource(value.type_, value.name_));
}

void Light::SetShapeTextureAttr(const ResourceRef& value)
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    shapeTexture_ = static_cast<Texture*>(cache->GetResource(value.type_, value.name_));
}

ResourceRef Light::GetRampTextureAttr() const
{
    return GetResourceRef(rampTexture_, Texture2D::GetTypeStatic());
}

ResourceRef Light::GetShapeTextureAttr() const
{
    return GetResourceRef(shapeTexture_, lightType_ == LIGHT_POINT ? TextureCube::GetTypeStatic() : Texture2D::GetTypeStatic());
}

void Light::OnWorldBoundingBoxUpdate()
{
    switch (lightType_)
    {
    case LIGHT_DIRECTIONAL:
        // Directional light always sets humongous bounding box not affected by transform
        worldBoundingBox_.Define(-M_LARGE_VALUE, M_LARGE_VALUE);
        break;

    case LIGHT_SPOT:
        // Frustum is already transformed into world space
        worldBoundingBox_.Define(GetFrustum());
        break;

    case LIGHT_POINT:
        {
            const Vector3& center = node_->GetWorldPosition();
            Vector3 edge(range_, range_, range_);
            worldBoundingBox_.Define(center - edge, center + edge);
        }
        break;
    }
}

void Light::SetIntensitySortValue(float distance)
{
    // When sorting lights globally, give priority to directional lights so that they will be combined into the ambient pass
    if (!IsNegative())
    {
        if (lightType_ != LIGHT_DIRECTIONAL)
            sortValue_ = Max(distance, M_MIN_NEARCLIP) / GetIntensityDivisor();
        else
            sortValue_ = M_EPSILON / GetIntensityDivisor();
    }
    else
    {
        // Give extra priority to negative lights in the global sorting order so that they're handled first, right after ambient.
        // Positive lights are added after them
        if (lightType_ != LIGHT_DIRECTIONAL)
            sortValue_ = -Max(distance, M_MIN_NEARCLIP) * GetIntensityDivisor();
        else
            sortValue_ = -M_LARGE_VALUE * GetIntensityDivisor();
    }
}

void Light::SetIntensitySortValue(const BoundingBox& box)
{
    // When sorting lights for object's maximum light cap, give priority based on attenuation and intensity
    switch (lightType_)
    {
    case LIGHT_DIRECTIONAL:
        sortValue_ = 1.0f / GetIntensityDivisor();
        break;

    case LIGHT_SPOT:
        {
            Vector3 centerPos = box.Center();
            Vector3 lightPos = node_->GetWorldPosition();
            Vector3 lightDir = node_->GetWorldDirection();
            Ray lightRay(lightPos, lightDir);

            Vector3 centerProj = lightRay.Project(centerPos);
            float centerDistance = (centerProj - lightPos).Length();
            Ray centerRay(centerProj, centerPos - centerProj);
            float centerAngle = centerRay.HitDistance(box) / centerDistance;

            // Check if a corner of the bounding box is closer to the light ray than the center, use its angle in that case
            Vector3 cornerPos = centerPos + box.HalfSize() * Vector3(centerPos.x_ < centerProj.x_ ? 1.0f : -1.0f,
                centerPos.y_ < centerProj.y_ ? 1.0f : -1.0f, centerPos.z_ < centerProj.z_ ? 1.0f : -1.0f);
            Vector3 cornerProj = lightRay.Project(cornerPos);
            float cornerDistance = (cornerProj - lightPos).Length();
            float cornerAngle = (cornerPos - cornerProj).Length() / cornerDistance;

            float spotAngle = Min(centerAngle, cornerAngle);
            float maxAngle = tanf(fov_ * M_DEGTORAD * 0.5f);
            float spotFactor = Min(spotAngle / maxAngle, 1.0f);
            // We do not know the actual range attenuation ramp, so take only spot attenuation into account
            float att = Max(1.0f - spotFactor * spotFactor, M_EPSILON);
            sortValue_ = 1.0f / GetIntensityDivisor(att);
        }
        break;

    case LIGHT_POINT:
        {
            Vector3 centerPos = box.Center();
            Vector3 lightPos = node_->GetWorldPosition();
            Vector3 lightDir = (centerPos - lightPos).Normalized();
            Ray lightRay(lightPos, lightDir);
            float distance = lightRay.HitDistance(box);
            float normDistance = distance / range_;
            float att = Max(1.0f - normDistance * normDistance, M_EPSILON);
            sortValue_ = 1.0f / (Max(color_.SumRGB(), 0.0f) * att + M_EPSILON);
        }
        break;
    }
}

void Light::SetLightQueue(LightBatchQueue* queue)
{
    lightQueue_ = queue;
}

}
