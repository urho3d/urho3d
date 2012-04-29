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
#include "OctreeQuery.h"
#include "Profiler.h"
#include "ResourceCache.h"
#include "Texture2D.h"
#include "TextureCube.h"
#include "XMLElement.h"

#include "DebugNew.h"

static const LightType DEFAULT_LIGHTTYPE = LIGHT_POINT;
static const float DEFAULT_RANGE = 10.0f;
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
    shadowBias_(BiasParameters(DEFAULT_CONSTANTBIAS, DEFAULT_SLOPESCALEDBIAS)),
    shadowCascade_(CascadeParameters(M_LARGE_VALUE, 0.0f, 0.0f, 0.0f, DEFAULT_SHADOWFADESTART)),
    shadowFocus_(FocusParameters(true, true, true, DEFAULT_SHADOWQUANTIZE, DEFAULT_SHADOWMINVIEW)),
    lightQueue_(0),
    specularIntensity_(0.0f),
    range_(DEFAULT_RANGE),
    fov_(DEFAULT_FOV),
    aspectRatio_(1.0f),
    fadeDistance_(0.0f),
    shadowFadeDistance_(0.0f),
    shadowIntensity_(0.0f),
    shadowResolution_(1.0f),
    shadowNearFarRatio_(DEFAULT_SHADOWNEARFARRATIO),
    perVertex_(false)
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
    REF_ACCESSOR_ATTRIBUTE(Light, VAR_COLOR, "Color", GetColor, SetColor, Color, Color(), AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(Light, VAR_FLOAT, "Specular Intensity", GetSpecularIntensity, SetSpecularIntensity, float, 0.0f, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(Light, VAR_FLOAT, "Range", GetRange, SetRange, float, DEFAULT_RANGE, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(Light, VAR_FLOAT, "Spot FOV", GetFov, SetFov, float, DEFAULT_FOV, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(Light, VAR_FLOAT, "Spot Aspect Ratio", GetAspectRatio, SetAspectRatio, float, 1.0f, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(Light, VAR_RESOURCEREF, "Attenuation Texture", GetRampTextureAttr, SetRampTextureAttr, ResourceRef, ResourceRef(Texture2D::GetTypeStatic()), AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(Light, VAR_RESOURCEREF, "Light Shape Texture", GetShapeTextureAttr, SetShapeTextureAttr, ResourceRef, ResourceRef(Texture2D::GetTypeStatic()), AM_DEFAULT);
    ATTRIBUTE(Light, VAR_BOOL, "Is Visible", visible_, true, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(Light, VAR_BOOL, "Can Be Occluded", IsOccludee, SetOccludee, bool, true, AM_DEFAULT);
    ATTRIBUTE(Light, VAR_BOOL, "Cast Shadows", castShadows_, false, AM_DEFAULT);
    ATTRIBUTE(Light, VAR_BOOL, "Per Vertex", perVertex_, false, AM_DEFAULT);
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
    Component::OnSetAttribute(attr, src);
    
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

void Light::ProcessRayQuery(const RayOctreeQuery& query, PODVector<RayQueryResult>& results)
{
    RayQueryLevel level = query.level_;
    
    switch (level)
    {
    case RAY_AABB_NOSUBOBJECTS:
    case RAY_AABB:
        // Do not record a raycast result for a directional light, as they would overwhelm all other results
        if (lightType_ != LIGHT_DIRECTIONAL)
            Drawable::ProcessRayQuery(query, results);
        break;
        
    case RAY_OBB:
        if (lightType_ != LIGHT_DIRECTIONAL)
        {
            Matrix3x4 inverse(node_->GetWorldTransform().Inverse());
            Ray localRay(inverse * query.ray_.origin_, inverse * Vector4(query.ray_.direction_, 0.0f));
            float distance = localRay.HitDistance(GetWorldBoundingBox());
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
        break;
        
    case RAY_TRIANGLE:
        if (lightType_ == LIGHT_SPOT)
        {
            float distance = query.ray_.HitDistance(GetFrustum());
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
        if (lightType_ == LIGHT_POINT)
        {
            float distance = query.ray_.HitDistance(Sphere(node_->GetWorldPosition(), range_));
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
        break;
    }
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
    if (debug)
    {
        switch (lightType_)
        {
        case LIGHT_SPOT:
            debug->AddFrustum(GetFrustum(), color_, depthTest);
            break;
            
        case LIGHT_POINT:
            debug->AddSphere(Sphere(node_->GetWorldPosition(), range_), GetColor(), depthTest);
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
    // Clamp RGB values to positive, as negative values behave erratically depending on whether the pass uses
    // replace or additive blend mode
    color_ = Color(Max(color.r_, 0.0f), Max(color.g_, 0.0f), Max(color.b_, 0.0f), 1.0f);
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

void Light::SetSpecularIntensity(float intensity)
{
    specularIntensity_ = Max(intensity, 0.0f);
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
    const Matrix3x4& transform = node_ ? node_->GetWorldTransform() : Matrix3x4::IDENTITY;
    Matrix3x4 frustumTransform(transform.Translation(), transform.Rotation(), 1.0f);
    Frustum ret;
    ret.Define(fov_, aspectRatio_, 1.0f, M_MIN_NEARCLIP, range_, frustumTransform);
    return ret;
}

Matrix3x4 Light::GetDirLightTransform(Camera* camera, bool getNearQuad)
{
    if (!camera)
        return Matrix3x4::IDENTITY;
    
    Vector3 nearVector, farVector;
    camera->GetFrustumSize(nearVector, farVector);
    float nearClip = camera->GetNearClip();
    float farClip = camera->GetFarClip();
    
    float distance = getNearQuad ? nearClip : farClip;
    if (!camera->IsOrthographic())
        farVector *= (distance / farClip);
    else
        farVector.z_ *= (distance / farClip);
    
    // Set an epsilon from clip planes due to possible inaccuracy
    /// \todo Rather set an identity projection matrix
    farVector.z_ = Clamp(farVector.z_, (1.0f + M_LARGE_EPSILON) * nearClip, (1.0f - M_LARGE_EPSILON) * farClip);
    
    return  Matrix3x4(Vector3(0.0f, 0.0f, farVector.z_), Quaternion::IDENTITY, Vector3(farVector.x_, farVector.y_, 1.0f));
}

const Matrix3x4& Light::GetVolumeTransform(Camera* camera)
{
    const Matrix3x4& transform = node_->GetWorldTransform();
    
    switch (lightType_)
    {
    case LIGHT_DIRECTIONAL:
        volumeTransform_ = GetDirLightTransform(camera);
        break;
        
    case LIGHT_SPOT:
        {
            float yScale = tanf(fov_ * M_DEGTORAD * 0.5f) * range_;
            float xScale = aspectRatio_ * yScale;
            volumeTransform_ = Matrix3x4(transform.Translation(), transform.Rotation(), Vector3(xScale, yScale, range_));
        }
        break;
        
    case LIGHT_POINT:
        volumeTransform_ = Matrix3x4(transform.Translation(), Quaternion::IDENTITY, range_);
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
            const Vector3& center = node_->GetWorldPosition();
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

void Light::SetIntensitySortValue(float distance)
{
    // When sorting lights globally, give priority to directional lights so that they will be combined into the ambient pass
    if (lightType_ != LIGHT_DIRECTIONAL)
        sortValue_ = Max(distance, M_MIN_NEARCLIP) / (color_.Intensity() + M_EPSILON);
    else
        sortValue_ = M_EPSILON / (color_.Intensity() + M_EPSILON);
    
    // Additionally, give priority to vertex lights so that vertex light base passes can be determined before per pixel lights
    if (perVertex_)
        sortValue_ -= M_LARGE_VALUE;
}

void Light::SetIntensitySortValue(const BoundingBox& box)
{
    // When sorting lights for object's maximum light cap, give priority based on attenuation and intensity
    switch (lightType_)
    {
    case LIGHT_DIRECTIONAL:
        sortValue_ = 1.0f / (color_.Intensity() + M_EPSILON);
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
            sortValue_ = 1.0f / (color_.Intensity() * att + M_EPSILON);
        }
        break;
        
    case LIGHT_SPOT:
        {
            Vector3 centerPos = box.Center();
            Vector3 lightPos = node_->GetWorldPosition();
            Vector3 lightDir = node_->GetWorldRotation() * Vector3::FORWARD;
            Ray lightRay(lightPos, lightDir);
            
            Vector3 centerProj = lightRay.Project(centerPos);
            float centerDistance = (centerProj - lightPos).Length();
            Ray centerRay(centerProj, (centerPos - centerProj).Normalized());
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
            sortValue_ = 1.0f / (color_.Intensity() * att + M_EPSILON);
        }
        break;
    }
}

void Light::SetLightQueue(LightBatchQueue* queue)
{
    lightQueue_ = queue;
}
