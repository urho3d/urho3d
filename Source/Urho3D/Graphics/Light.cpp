//
// Copyright (c) 2008-2020 the Urho3D project.
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

#include "../Precompiled.h"

#include "../Core/Context.h"
#include "../Core/Profiler.h"
#include "../Graphics/Camera.h"
#include "../Graphics/DebugRenderer.h"
#include "../Graphics/Graphics.h"
#include "../Graphics/Light.h"
#include "../Graphics/OctreeQuery.h"
#include "../Graphics/Texture2D.h"
#include "../Graphics/TextureCube.h"
#include "../IO/Log.h"
#include "../Resource/ResourceCache.h"
#include "../Scene/Node.h"

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
static const float DEFAULT_NORMALOFFSET = 0.0f;
static const float DEFAULT_BIASAUTOADJUST = 1.0f;
static const float DEFAULT_SHADOWFADESTART = 0.8f;
static const float DEFAULT_SHADOWQUANTIZE = 0.5f;
static const float DEFAULT_SHADOWMINVIEW = 3.0f;
static const float DEFAULT_SHADOWNEARFARRATIO = 0.002f;
static const float DEFAULT_SHADOWMAXEXTRUSION = 1000.0f;
static const float DEFAULT_SHADOWSPLIT = 1000.0f;
static const float DEFAULT_TEMPERATURE = 6590.0f;
static const float DEFAULT_RADIUS = 0.0f;
static const float DEFAULT_LENGTH = 0.0f;

static const char* typeNames[] =
{
    "Directional",
    "Spot",
    "Point",
    nullptr
};

void BiasParameters::Validate()
{
    constantBias_ = Clamp(constantBias_, -1.0f, 1.0f);
    slopeScaledBias_ = Clamp(slopeScaledBias_, -16.0f, 16.0f);
    normalOffset_ = Max(normalOffset_, 0.0f);
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
    lightQueue_(nullptr),
    temperature_(DEFAULT_TEMPERATURE),
    lightRad_(DEFAULT_RADIUS),
    lightLength_(DEFAULT_LENGTH),
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
    shadowMaxExtrusion_(DEFAULT_SHADOWMAXEXTRUSION),
    perVertex_(false),
    usePhysicalValues_(false)
{
}

Light::~Light() = default;

void Light::RegisterObject(Context* context)
{
    context->RegisterFactory<Light>(SCENE_CATEGORY);

    URHO3D_ACCESSOR_ATTRIBUTE("Is Enabled", IsEnabled, SetEnabled, bool, true, AM_DEFAULT);
    URHO3D_ENUM_ACCESSOR_ATTRIBUTE("Light Type", GetLightType, SetLightType, LightType, typeNames, DEFAULT_LIGHTTYPE, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Color", GetColor, SetColor, Color, Color::WHITE, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Specular Intensity", GetSpecularIntensity, SetSpecularIntensity, float, DEFAULT_SPECULARINTENSITY,
        AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Brightness Multiplier", GetBrightness, SetBrightness, float, DEFAULT_BRIGHTNESS, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Temperature", GetTemperature, SetTemperature, float, DEFAULT_TEMPERATURE, AM_DEFAULT);
    URHO3D_ATTRIBUTE("Use Physical Values", bool, usePhysicalValues_, false, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Radius", GetRadius, SetRadius, float, DEFAULT_RADIUS, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Length", GetLength, SetLength, float, DEFAULT_LENGTH, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Range", GetRange, SetRange, float, DEFAULT_RANGE, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Spot FOV", GetFov, SetFov, float, DEFAULT_LIGHT_FOV, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Spot Aspect Ratio", GetAspectRatio, SetAspectRatio, float, 1.0f, AM_DEFAULT);
    URHO3D_MIXED_ACCESSOR_ATTRIBUTE("Attenuation Texture", GetRampTextureAttr, SetRampTextureAttr, ResourceRef,
        ResourceRef(Texture2D::GetTypeStatic()), AM_DEFAULT);
    URHO3D_MIXED_ACCESSOR_ATTRIBUTE("Light Shape Texture", GetShapeTextureAttr, SetShapeTextureAttr, ResourceRef,
        ResourceRef(Texture2D::GetTypeStatic()), AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Can Be Occluded", IsOccludee, SetOccludee, bool, true, AM_DEFAULT);
    URHO3D_ATTRIBUTE("Cast Shadows", bool, castShadows_, false, AM_DEFAULT);
    URHO3D_ATTRIBUTE("Per Vertex", bool, perVertex_, false, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Draw Distance", GetDrawDistance, SetDrawDistance, float, 0.0f, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Fade Distance", GetFadeDistance, SetFadeDistance, float, 0.0f, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Shadow Distance", GetShadowDistance, SetShadowDistance, float, 0.0f, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Shadow Fade Distance", GetShadowFadeDistance, SetShadowFadeDistance, float, 0.0f, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Shadow Intensity", GetShadowIntensity, SetShadowIntensity, float, 0.0f, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Shadow Resolution", GetShadowResolution, SetShadowResolution, float, 1.0f, AM_DEFAULT);
    URHO3D_ATTRIBUTE_EX("Focus To Scene", bool, shadowFocus_.focus_, ValidateShadowFocus, true, AM_DEFAULT);
    URHO3D_ATTRIBUTE_EX("Non-uniform View", bool, shadowFocus_.nonUniform_, ValidateShadowFocus, true, AM_DEFAULT);
    URHO3D_ATTRIBUTE_EX("Auto-Reduce Size", bool, shadowFocus_.autoSize_, ValidateShadowFocus, true, AM_DEFAULT);
    URHO3D_ATTRIBUTE_EX("CSM Splits", Vector4, shadowCascade_.splits_, ValidateShadowCascade, Vector4(DEFAULT_SHADOWSPLIT, 0.0f, 0.0f, 0.0f), AM_DEFAULT);
    URHO3D_ATTRIBUTE_EX("CSM Fade Start", float, shadowCascade_.fadeStart_, ValidateShadowCascade, DEFAULT_SHADOWFADESTART, AM_DEFAULT);
    URHO3D_ATTRIBUTE_EX("CSM Bias Auto Adjust", float, shadowCascade_.biasAutoAdjust_, ValidateShadowCascade, DEFAULT_BIASAUTOADJUST, AM_DEFAULT);
    URHO3D_ATTRIBUTE_EX("View Size Quantize", float, shadowFocus_.quantize_, ValidateShadowFocus, DEFAULT_SHADOWQUANTIZE, AM_DEFAULT);
    URHO3D_ATTRIBUTE_EX("View Size Minimum", float, shadowFocus_.minView_, ValidateShadowFocus, DEFAULT_SHADOWMINVIEW, AM_DEFAULT);
    URHO3D_ATTRIBUTE_EX("Depth Constant Bias", float, shadowBias_.constantBias_, ValidateShadowBias, DEFAULT_CONSTANTBIAS, AM_DEFAULT);
    URHO3D_ATTRIBUTE_EX("Depth Slope Bias", float, shadowBias_.slopeScaledBias_, ValidateShadowBias, DEFAULT_SLOPESCALEDBIAS, AM_DEFAULT);
    URHO3D_ATTRIBUTE_EX("Normal Offset", float, shadowBias_.normalOffset_, ValidateShadowBias, DEFAULT_NORMALOFFSET, AM_DEFAULT);
    URHO3D_ATTRIBUTE("Near/Farclip Ratio", float, shadowNearFarRatio_, DEFAULT_SHADOWNEARFARRATIO, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Max Extrusion", GetShadowMaxExtrusion, SetShadowMaxExtrusion, float, DEFAULT_SHADOWMAXEXTRUSION, AM_DEFAULT);
    URHO3D_ATTRIBUTE("View Mask", int, viewMask_, DEFAULT_VIEWMASK, AM_DEFAULT);
    URHO3D_ATTRIBUTE("Light Mask", int, lightMask_, DEFAULT_LIGHTMASK, AM_DEFAULT);
}

void Light::ProcessRayQuery(const RayOctreeQuery& query, PODVector<RayQueryResult>& results)
{
    // Do not record a raycast result for a directional light, as it would block all other results
    if (lightType_ == LIGHT_DIRECTIONAL)
        return;

    float distance = query.maxDistance_;
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

    case RAY_TRIANGLE_UV:
        URHO3D_LOGWARNING("RAY_TRIANGLE_UV query level is not supported for Light component");
        return;
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

void Light::SetTemperature(float temperature)
{
    temperature_ = Clamp(temperature, 1000.0f, 10000.0f);
    MarkNetworkUpdate();
}

void Light::SetRadius(float radius)
{
    lightRad_ = radius;
    MarkNetworkUpdate();
}

void Light::SetLength(float length)
{
    lightLength_ = length;
    MarkNetworkUpdate();
}

void Light::SetUsePhysicalValues(bool enable)
{
    usePhysicalValues_ = enable;
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

void Light::SetShadowMaxExtrusion(float extrusion)
{
    shadowMaxExtrusion_ = Max(extrusion, 0.0f);
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

Color Light::GetColorFromTemperature() const
{
    // Approximate Planckian locus in CIE 1960 UCS
    float u = (0.860117757f + 1.54118254e-4f * temperature_ + 1.28641212e-7f * temperature_ * temperature_) /
        (1.0f + 8.42420235e-4f * temperature_ + 7.08145163e-7f * temperature_ * temperature_);
    float v = (0.317398726f + 4.22806245e-5f * temperature_ + 4.20481691e-8f * temperature_ * temperature_) /
        (1.0f - 2.89741816e-5f * temperature_ + 1.61456053e-7f * temperature_ * temperature_);

    float x = 3.0f * u / (2.0f * u - 8.0f * v + 4.0f);
    float y = 2.0f * v / (2.0f * u - 8.0f * v + 4.0f);
    float z = 1.0f - x - y;

    float y_ = 1.0f;
    float x_ = y_ / y * x;
    float z_ = y_ / y * z;

    float red = 3.2404542f * x_ + -1.5371385f * y_ + -0.4985314f * z_;
    float green = -0.9692660f * x_ + 1.8760108f * y_ + 0.0415560f * z_;
    float blue = 0.0556434f * x_ + -0.2040259f * y_ + 1.0572252f * z_;

    return Color(red, green, blue);
}

Color Light::GetEffectiveColor() const
{
    if (usePhysicalValues_)
    {
        // Light color in kelvin.
        Color tempColor = GetColorFromTemperature();
        // Light brightness in lumens
        float energy = (brightness_ * 4.0f * M_PI) * 16.0f / (100.0f * 100.0f) / M_PI;
        return Color(tempColor.r_ * color_.r_ * energy, tempColor.g_ * color_.g_ * energy, tempColor.b_ * color_.b_ * energy, 1.0f);
    }
    else
    {
        return Color(color_ * brightness_, 1.0f);
    }
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

Frustum Light::GetViewSpaceFrustum(const Matrix3x4& view) const
{
    // Note: frustum is unaffected by node or parent scale
    Matrix3x4 frustumTransform(node_ ? Matrix3x4(node_->GetWorldPosition(), node_->GetWorldRotation(), 1.0f) :
                               Matrix3x4::IDENTITY);
    Frustum ret;
    ret.Define(fov_, aspectRatio_, 1.0f, M_MIN_NEARCLIP, range_, view * frustumTransform);
    return ret;
}

int Light::GetNumShadowSplits() const
{
    unsigned ret = 1;

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

    return (int)Min(ret, MAX_CASCADE_SPLITS);
}

const Matrix3x4& Light::GetVolumeTransform(Camera* camera)
{
    if (!node_)
        return Matrix3x4::IDENTITY;

    switch (lightType_)
    {
    case LIGHT_DIRECTIONAL:
        volumeTransform_ = GetFullscreenQuadTransform(camera);
        break;

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
    auto* cache = GetSubsystem<ResourceCache>();
    rampTexture_ = static_cast<Texture*>(cache->GetResource(value.type_, value.name_));
}

void Light::SetShapeTextureAttr(const ResourceRef& value)
{
    auto* cache = GetSubsystem<ResourceCache>();
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
            sortValue_ = 1.0f / GetIntensityDivisor(att);
        }
        break;
    }
}

void Light::SetLightQueue(LightBatchQueue* queue)
{
    lightQueue_ = queue;
}

Matrix3x4 Light::GetFullscreenQuadTransform(Camera* camera)
{
    Matrix3x4 quadTransform;
    Vector3 near, far;
    // Position the directional light quad in halfway between far & near planes to prevent depth clipping
    camera->GetFrustumSize(near, far);
    quadTransform.SetTranslation(Vector3(0.0f, 0.0f, (camera->GetNearClip() + camera->GetFarClip()) * 0.5f));
    quadTransform.SetScale(Vector3(far.x_, far.y_, 1.0f)); // Will be oversized, but doesn't matter (gets frustum clipped)
    return camera->GetEffectiveWorldTransform() * quadTransform;
}

}
