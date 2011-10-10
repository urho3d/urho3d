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
#include "ResourceCache.h"
#include "Texture2D.h"
#include "TextureCube.h"
#include "XMLElement.h"

#include "DebugNew.h"

static const LightType DEFAULT_LIGHTTYPE = LIGHT_POINT;
static const float DEFAULT_FOV = 30.0f;
static const float DEFAULT_CONSTANTBIAS = 0.0001f;
static const float DEFAULT_SLOPESCALEDBIAS = 0.5f;
static const float DEFAULT_SHADOWFADESTART = 0.8f;
static const float DEFAULT_SHADOWQUANTIZE = 0.5f;
static const float DEFAULT_SHADOWMINVIEW = 3.0f;
static const float DEFAULT_SHADOWNEARFARRATIO = 0.002f;

static const String typeNames[] =
{
    "Directional",
    "Spot",
    "Point",
    ""
};

void BiasParameters::Validate()
{
    constantBias_ = Clamp(constantBias_, 0.0f, 1.0f);
    slopeScaledBias_ = Clamp(slopeScaledBias_, 0.0f, 16.0f);
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

template<> LightType Variant::Get<LightType>() const
{
    return (LightType)GetInt();
}

OBJECTTYPESTATIC(Light);

Light::Light(Context* context) :
    Drawable(context),
    lightType_(DEFAULT_LIGHTTYPE),
    specularIntensity_(0.0f),
    range_(0.0f),
    fov_(DEFAULT_FOV),
    aspectRatio_(1.0f),
    fadeDistance_(0.0f),
    shadowFadeDistance_(0.0f),
    shadowBias_(BiasParameters(DEFAULT_CONSTANTBIAS, DEFAULT_SLOPESCALEDBIAS)),
    shadowCascade_(CascadeParameters(M_LARGE_VALUE, 0.0f, 0.0f, 0.0f, DEFAULT_SHADOWFADESTART)),
    shadowFocus_(FocusParameters(true, true, true, DEFAULT_SHADOWQUANTIZE, DEFAULT_SHADOWMINVIEW)),
    shadowIntensity_(0.0f),
    shadowResolution_(1.0f),
    shadowNearFarRatio_(DEFAULT_SHADOWNEARFARRATIO)
{
    drawableFlags_ =  DRAWABLE_LIGHT;
}

Light::~Light()
{
}

void Light::RegisterObject(Context* context)
{
    context->RegisterFactory<Light>();
    
    ENUM_ACCESSOR_ATTRIBUTE(Light, "Light Type", GetLightType, SetLightType, LightType, typeNames, DEFAULT_LIGHTTYPE, AM_DEFAULT);
    ATTRIBUTE(Light, VAR_COLOR, "Color", color_, Color(), AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(Light, VAR_FLOAT, "Specular Intensity", GetSpecularIntensity, SetSpecularIntensity, float, 0.0f, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(Light, VAR_FLOAT, "Range", GetRange, SetRange, float, 0.0f, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(Light, VAR_FLOAT, "Spot FOV", GetFov, SetFov, float, DEFAULT_FOV, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(Light, VAR_FLOAT, "Spot Aspect Ratio", GetAspectRatio, SetAspectRatio, float, 1.0f, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(Light, VAR_RESOURCEREF, "Attenuation Texture", GetRampTextureAttr, SetRampTextureAttr, ResourceRef, ResourceRef(Texture2D::GetTypeStatic()), AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(Light, VAR_RESOURCEREF, "Light Shape Texture", GetShapeTextureAttr, SetShapeTextureAttr, ResourceRef, ResourceRef(Texture2D::GetTypeStatic()), AM_DEFAULT);
    ATTRIBUTE(Light, VAR_BOOL, "Is Visible", visible_, true, AM_DEFAULT);
    ATTRIBUTE(Light, VAR_BOOL, "Cast Shadows", castShadows_, false, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(Light, VAR_FLOAT, "Draw Distance", GetDrawDistance, SetDrawDistance, float, 0.0f, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(Light, VAR_FLOAT, "Fade Distance", GetFadeDistance, SetFadeDistance, float, 0.0f, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(Light, VAR_FLOAT, "Shadow Distance", GetShadowDistance, SetShadowDistance, float, 0.0f, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(Light, VAR_FLOAT, "Shadow Fade Distance", GetShadowFadeDistance, SetShadowFadeDistance, float, 0.0f, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(Light, VAR_FLOAT, "Shadow Intensity", GetShadowIntensity, SetShadowIntensity, float, 0.0f, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(Light, VAR_FLOAT, "Shadow Resolution", GetShadowResolution, SetShadowResolution, float, 1.0f, AM_DEFAULT);
    ATTRIBUTE(Light, VAR_BOOL, "Focus To Scene", shadowFocus_.focus_, true, AM_DEFAULT);
    ATTRIBUTE(Light, VAR_BOOL, "Non-uniform View", shadowFocus_.nonUniform_, true, AM_DEFAULT);
    ATTRIBUTE(Light, VAR_BOOL, "Auto-Reduce Size", shadowFocus_.autoSize_, true, AM_DEFAULT);
    ATTRIBUTE(Light, VAR_VECTOR4, "CSM Splits", shadowCascade_.splits_, Vector4(M_LARGE_VALUE, 0.0f, 0.0f, 0.0f), AM_DEFAULT);
    ATTRIBUTE(Light, VAR_FLOAT, "CSM Fade Start", shadowCascade_.fadeStart_, DEFAULT_SHADOWFADESTART, AM_DEFAULT);
    ATTRIBUTE(Light, VAR_FLOAT, "View Size Quantize", shadowFocus_.quantize_, DEFAULT_SHADOWQUANTIZE, AM_DEFAULT);
    ATTRIBUTE(Light, VAR_FLOAT, "View Size Minimum", shadowFocus_.minView_, DEFAULT_SHADOWMINVIEW, AM_DEFAULT);
    ATTRIBUTE(Light, VAR_FLOAT, "Depth Constant Bias", shadowBias_.constantBias_, DEFAULT_CONSTANTBIAS, AM_DEFAULT);
    ATTRIBUTE(Light, VAR_FLOAT, "Depth Slope Bias", shadowBias_.slopeScaledBias_, DEFAULT_SLOPESCALEDBIAS, AM_DEFAULT);
    ATTRIBUTE(Light, VAR_FLOAT, "Near/Farclip Ratio", shadowNearFarRatio_, DEFAULT_SHADOWNEARFARRATIO, AM_DEFAULT);
    ATTRIBUTE(Light, VAR_INT, "View Mask", viewMask_, DEFAULT_VIEWMASK, AM_DEFAULT);
    ATTRIBUTE(Light, VAR_INT, "Light Mask", lightMask_, DEFAULT_LIGHTMASK, AM_DEFAULT);
}

void Light::OnSetAttribute(const AttributeInfo& attr, const Variant& src)
{
    Serializable::OnSetAttribute(attr, src);
    
    // Validate the bias, cascade & focus parameters
    switch (attr.offset_)
    {
    case offsetof(Light, shadowBias_.constantBias_):
    case offsetof(Light, shadowBias_.slopeScaledBias_):
        shadowBias_.Validate();
        break;
    
    case offsetof(Light, shadowCascade_.start_):
    case offsetof(Light, shadowCascade_.splits_):
    case offsetof(Light, shadowCascade_.splits_) + sizeof(float):
    case offsetof(Light, shadowCascade_.splits_) + sizeof(float) * 2:
    case offsetof(Light, shadowCascade_.splits_) + sizeof(float) * 3:
    case offsetof(Light, shadowCascade_.fadeStart_):
        shadowCascade_.Validate();
        break;
        
    case offsetof(Light, shadowFocus_.quantize_):
    case offsetof(Light, shadowFocus_.minView_):
        shadowFocus_.Validate();
        break;
    }
}

void Light::UpdateDistance(const FrameInfo& frame)
{
    switch (lightType_)
    {
    case LIGHT_DIRECTIONAL:
        // Directional light affects the whole scene, so it is always "closest"
        distance_ = 0.0f;
        break;
        
    default:
        distance_ = frame.camera_->GetDistance(GetWorldPosition());
        break;
    }
}

void Light::DrawDebugGeometry(DebugRenderer* debug, bool depthTest)
{
    switch (lightType_)
    {
    case LIGHT_SPOT:
        debug->AddFrustum(GetFrustum(), color_, depthTest);
        break;
        
    case LIGHT_POINT:
        debug->AddBoundingBox(GetWorldBoundingBox(), GetColor(), depthTest);
        break;
    }
}

void Light::SetLightType(LightType type)
{
    lightType_ = type;
    OnMarkedDirty(node_);
}

void Light::SetColor(const Color& color)
{
    color_ = color;
}

void Light::SetRange(float range)
{
    range_ = Max(range, 0.0f);
    OnMarkedDirty(node_);
}

void Light::SetFov(float fov)
{
    fov_ = Clamp(fov, 0.0f, M_MAX_FOV);
    OnMarkedDirty(node_);
}

void Light::SetAspectRatio(float aspectRatio)
{
    aspectRatio_ = Max(aspectRatio, M_EPSILON);
    OnMarkedDirty(node_);
}

void Light::SetShadowNearFarRatio(float nearFarRatio)
{
    shadowNearFarRatio_ = Clamp(nearFarRatio, 0.0f, 0.5f);
}

void Light::SetSpecularIntensity(float intensity)
{
    specularIntensity_ = Max(intensity, 0.0f);
}

void Light::SetFadeDistance(float distance)
{
    fadeDistance_ = Max(distance, 0.0f);
}

void Light::SetShadowBias(const BiasParameters& parameters)
{
    shadowBias_ = parameters;
    shadowBias_.Validate();
}

void Light::SetShadowCascade(const CascadeParameters& parameters)
{
    shadowCascade_ = parameters;
    shadowCascade_.Validate();
}

void Light::SetShadowFocus(const FocusParameters& parameters)
{
    shadowFocus_ = parameters;
    shadowFocus_.Validate();
}

void Light::SetShadowFadeDistance(float distance)
{
    shadowFadeDistance_ = Max(distance, 0.0f);
}

void Light::SetShadowIntensity(float intensity)
{
    shadowIntensity_ = Clamp(intensity, 0.0f, 1.0f);
}

void Light::SetShadowResolution(float resolution)
{
    shadowResolution_ = Clamp(resolution, 0.125f, 1.0f);
}

void Light::SetRampTexture(Texture* texture)
{
    rampTexture_ = texture;
}

void Light::SetShapeTexture(Texture* texture)
{
    shapeTexture_ = texture;
}

Frustum Light::GetFrustum() const
{
    const Matrix3x4& transform = GetWorldTransform();
    Matrix3x4 frustumTransform(transform.Translation(), transform.Rotation(), 1.0f);
    Frustum ret;
    ret.Define(fov_, aspectRatio_, 1.0f, M_MIN_NEARCLIP, range_, frustumTransform);
    return ret;
}

const Matrix3x4& Light::GetVolumeTransform()
{
    const Matrix3x4& transform = GetWorldTransform();
    
    switch (lightType_)
    {
    case LIGHT_POINT:
        volumeTransform_ = Matrix3x4(transform.Translation(), Quaternion::IDENTITY, range_);
        break;
        
    case LIGHT_SPOT:
        {
            float yScale = tanf(fov_ * M_DEGTORAD * 0.5f) * range_;
            float xScale = aspectRatio_ * yScale;
            volumeTransform_ = Matrix3x4(transform.Translation(), transform.Rotation(), Vector3(xScale, yScale, range_));
        }
        break;
    }
    
    return volumeTransform_;
}

void Light::SetRampTextureAttr(ResourceRef value)
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    rampTexture_ = static_cast<Texture*>(cache->GetResource(value.type_, value.id_));
}

void Light::SetShapeTextureAttr(ResourceRef value)
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    shapeTexture_ = static_cast<Texture*>(cache->GetResource(value.type_, value.id_));
}

ResourceRef Light::GetRampTextureAttr() const
{
    return GetResourceRef(rampTexture_, Texture2D::GetTypeStatic());
}

ResourceRef Light::GetShapeTextureAttr() const
{
    return GetResourceRef(shapeTexture_, Texture2D::GetTypeStatic());
}

void Light::OnWorldBoundingBoxUpdate()
{
    switch (lightType_)
    {
    case LIGHT_DIRECTIONAL:
        // Directional light always sets humongous bounding box not affected by transform
        worldBoundingBox_.Define(-M_LARGE_VALUE, M_LARGE_VALUE);
        break;
        
    case LIGHT_POINT:
        {
            const Vector3& center = GetWorldPosition();
            Vector3 edge(range_, range_, range_);
            worldBoundingBox_.Define(center - edge, center + edge);
        }
        break;
        
    case LIGHT_SPOT:
        // Frustum is already transformed into world space
        worldBoundingBox_.Define(GetFrustum());
        break;
    }
}

void Light::SetIntensitySortValue(const Vector3& position, bool forDrawable)
{
    // Directional lights are always assumed to be "infinitely" close, while point and spot lights take distance into account
    float invIntensity = 1.0f / color_.Intensity();
    if (lightType_ == LIGHT_DIRECTIONAL)
        // If sorting lights for a drawable's maximum lights sorting, use the actual intensity
        // Else (when sorting lights globally for the view) ensure directional lights always have a fixed first priority
        // so that the lit base pass optimization has the most benefit
        sortValue_ = forDrawable ? invIntensity : 0.0f;
    else
        sortValue_ = invIntensity * (1.0f + (GetWorldPosition() - position).LengthFast() / range_);
}
