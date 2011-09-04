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

#pragma once

#include "Color.h"
#include "Drawable.h"
#include "Frustum.h"

class Camera;
class Texture;
class Texture2D;
class TextureCube;

/// %Light types.
enum LightType
{
    LIGHT_DIRECTIONAL = 0,
    LIGHT_SPOT,
    LIGHT_POINT,
    LIGHT_SPLITPOINT
};

/// Shadow depth bias parameters.
struct BiasParameters
{
    /// Construct undefined.
    BiasParameters()
    {
    }
    
    /// Construct with initial values.
    BiasParameters(float constantBias, float slopeScaledBias) :
        constantBias_(constantBias),
        slopeScaledBias_(slopeScaledBias)
    {
    }
    
    /// Validate parameters.
    void Validate();
    
    /// Constant bias.
    float constantBias_;
    /// Slope scaled bias.
    float slopeScaledBias_;
};

/// Cascaded shadow map parameters.
struct CascadeParameters
{
    /// Construct undefined.
    CascadeParameters()
    {
    }
    
    /// Construct with initial values.
    CascadeParameters(unsigned splits, float lambda, float splitFadeRange, float shadowRange) :
        splits_(splits),
        lambda_(lambda),
        splitFadeRange_(splitFadeRange),
        shadowRange_(shadowRange)
    {
    }
    
    /// Validate parameters.
    void Validate();
    
    /// Number of splits.
    unsigned splits_;
    /// Split lambda.
    float lambda_;
    /// Fade range between splits.
    float splitFadeRange_;
    /// Maximum shadow distance.
    float shadowRange_;
};

/// Shadow map focusing parameters.
struct FocusParameters
{
    /// Construct undefined.
    FocusParameters()
    {
    }
    
    /// Construct with initial values.
    FocusParameters(bool focus, bool nonUniform, bool zoomOut, float quantize, float minView) :
        focus_(focus),
        nonUniform_(nonUniform),
        zoomOut_(zoomOut),
        quantize_(quantize),
        minView_(minView)
    {
    }
    
    /// Validate parameters.
    void Validate();
    
    /// Focus flag.
    bool focus_;
    /// Non-uniform focusing flag.
    bool nonUniform_;
    /// Zoom out flag.
    bool zoomOut_;
    /// Focus quantization.
    float quantize_;
    /// Minimum view size.
    float minView_;
};

static const float SHADOW_MIN_QUANTIZE = 0.1f;
static const float SHADOW_MIN_VIEW = 1.0f;
static const float SHADOW_DEFAULT_NEARCLIP = 0.1f;
static const int MAX_LIGHT_SPLITS = 6;

/// %Light component.
class Light : public Drawable
{
    OBJECT(Light);
    
public:
    /// Construct.
    Light(Context* context);
    /// Destruct.
    virtual ~Light();
    /// Register object factory. Drawable must be registered first.
    static void RegisterObject(Context* context);
    
    /// Handle attribute change.
    virtual void OnSetAttribute(const AttributeInfo& attr, const Variant& src);
    /// Calculate distance for rendering.
    virtual void UpdateDistance(const FrameInfo& frame);
    /// Add debug geometry to the debug graphics.
    virtual void DrawDebugGeometry(DebugRenderer* debug, bool depthTest);
    
    /// %Set light type.
    void SetLightType(LightType type);
    /// %Set color.
    void SetColor(const Color& color);
    /// %Set specular intensity.
    void SetSpecularIntensity(float intensity);
    /// %Set range.
    void SetRange(float range);
    /// %Set spotlight field of view.
    void SetFov(float fov);
    /// %Set spotlight aspect ratio.
    void SetAspectRatio(float aspectRatio);
    /// %Set fade out start distance.
    void SetFadeDistance(float distance);
    /// %Set shadow fade out start distance. Only has effect if shadow distance is also non-zero.
    void SetShadowFadeDistance(float distance);
    /// %Set shadow depth bias parameters.
    void SetShadowBias(const BiasParameters& parameters);
    /// %Set directional light cascaded shadow parameters.
    void SetShadowCascade(const CascadeParameters& parameters);
    /// %Set shadow map focusing parameters.
    void SetShadowFocus(const FocusParameters& parameters);
    /// %Set shadow intensity between 0.0 - 1.0. 0.0 (the default) gives fully dark shadows.
    void SetShadowIntensity(float intensity);
    /// %Set shadow resolution between 0.25 - 1.0. Determines the shadow map to use.
    void SetShadowResolution(float resolution);
    /// %Set shadow camera near/far clip distance ratio.
    void SetShadowNearFarRatio(float nearFarRatio);
    /// %Set range attenuation texture.
    void SetRampTexture(Texture* texture);
    /// %Set spotlight attenuation texture.
    void SetShapeTexture(Texture* texture);
    
    /// Return light type.
    LightType GetLightType() const { return lightType_; }
    /// Return color.
    const Color& GetColor() const { return color_; }
    /// Return specular intensity.
    float GetSpecularIntensity() const { return specularIntensity_; }
    /// Return range.
    float GetRange() const { return range_; }
    /// Return spotlight field of view.
    float GetFov() const { return fov_; }
    /// Return spotlight aspect ratio.
    float GetAspectRatio() const { return aspectRatio_; }
    /// Return fade start distance.
    float GetFadeDistance() const { return fadeDistance_; }
   /// Return shadow fade start distance.
    float GetShadowFadeDistance() const { return shadowFadeDistance_; }
    /// Return shadow depth bias parameters.
    const BiasParameters& GetShadowBias() const { return shadowBias_; }
    /// Return directional light cascaded shadow parameters.
    const CascadeParameters& GetShadowCascade() const { return shadowCascade_; }
    /// Return shadow map focus parameters.
    const FocusParameters& GetShadowFocus() const { return shadowFocus_; }
    /// Return shadow intensity.
    float GetShadowIntensity() const { return shadowIntensity_; }
    /// Return shadow resolution.
    float GetShadowResolution() const { return shadowResolution_; }
    /// Return shadow camera near/far clip distance ratio.
    float GetShadowNearFarRatio() const { return shadowNearFarRatio_; }
    /// Return range attenuation texture.
    Texture* GetRampTexture() const { return rampTexture_; }
    /// Return spotlight attenuation texture.
    Texture* GetShapeTexture() const { return shapeTexture_; }
    /// Return spotlight frustum.
    Frustum GetFrustum() const;
    
    /// %Set near split distance for directional light.
    void SetNearSplit(float near);
    /// %Set far split distance for directional light.
    void SetFarSplit(float far);
    /// %Set near fade range for directional light.
    void SetNearFadeRange(float range);
    /// %Set far fade range for directional light.
    void SetFarFadeRange(float range);
    /// %Set shadow camera.
    void SetShadowCamera(Camera* camera);
    /// %Set shadow map depth texture.
    void SetShadowMap(Texture2D* shadowMap);
    /// %Set sort value based on intensity at given world position.
    void SetIntensitySortValue(const Vector3& position, bool forDrawable = false);
    /// Copy values from another light.
    void CopyFrom(Light* original);
    /// Return near split distance.
    float GetNearSplit() const { return nearSplit_; }
    /// Return far split distance.
    float GetFarSplit() const { return farSplit_; }
    /// Return near fade range.
    float GetNearFadeRange() const { return nearFadeRange_; }
    /// Return far fade range.
    float GetFarFadeRange() const { return farFadeRange_; }
    /// Return shadow camera. Not safe to dereference outside rendering.
    Camera* GetShadowCamera() { return shadowCamera_; }
    /// Return shadow map.
    Texture2D* GetShadowMap() const { return shadowMap_; }
    /// Return original light (split lights only.)
    Light* GetOriginalLight() const { return originalLight_; }
    /// Return volume safety extent of spot or point light.
    float GetVolumeExtent() const;
    /// Return directional light quad transform for either near or far split.
    Matrix3x4 GetDirLightTransform(Camera& camera, bool getNearQuad = false);
    /// Return light volume model transform. For directional lights, the view transform must be overridden.
    const Matrix3x4& GetVolumeTransform(Camera& camera);
    
    /// %Set ramp texture attribute.
    void SetRampTextureAttr(ResourceRef value);
    /// %Set shape texture attribute.
    void SetShapeTextureAttr(ResourceRef value);
    /// Return ramp texture attribute.
    ResourceRef GetRampTextureAttr() const;
    /// Return shape texture attribute.
    ResourceRef GetShapeTextureAttr() const;
    
protected:
    /// Update world-space bounding box.
    virtual void OnWorldBoundingBoxUpdate();
    
private:
    /// Light type.
    LightType lightType_;
    /// Color.
    Color color_;
    /// Specular intensity.
    float specularIntensity_;
    /// Range.
    float range_;
    /// Spotlight field of view.
    float fov_;
    /// Spotlight aspect ratio.
    float aspectRatio_;
    /// Fade start distance.
    float fadeDistance_;
    /// Shadow fade start distance.
    float shadowFadeDistance_;
    /// Shadow depth bias parameters.
    BiasParameters shadowBias_;
    /// Directional light cascaded shadow parameters.
    CascadeParameters shadowCascade_;
    /// Shadow map focus parameters.
    FocusParameters shadowFocus_;
    /// Custom world transform for the light volume.
    Matrix3x4 volumeTransform_;
    /// Shadow intensity.
    float shadowIntensity_;
    /// Shadow resolution.
    float shadowResolution_;
    /// Shadow camera near/far clip distance ratio.
    float shadowNearFarRatio_;
    /// Directional light near split distance.
    float nearSplit_;
    /// Directional light far split distance.
    float farSplit_;
    /// Directional light near fade range.
    float nearFadeRange_;
    /// Directional light far fade range.
    float farFadeRange_;
    /// Range attenuation texture.
    SharedPtr<Texture> rampTexture_;
    /// Spotlight attenuation texture.
    SharedPtr<Texture> shapeTexture_;
    /// Shadow camera.
    Camera* shadowCamera_;
    /// Shadow map.
    Texture2D* shadowMap_;
    /// Original light for splitting.
    Light* originalLight_;
};
