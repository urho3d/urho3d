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

/// \file

#pragma once

#include "../Math/Color.h"
#include "../Graphics/Drawable.h"
#include "../Math/Frustum.h"
#include "../Graphics/Texture.h"

namespace Urho3D
{

class Camera;
struct LightBatchQueue;

/// %Light types.
enum LightType
{
    LIGHT_DIRECTIONAL = 0,
    LIGHT_SPOT,
    LIGHT_POINT
};

static const float SHADOW_MIN_QUANTIZE = 0.1f;
static const float SHADOW_MIN_VIEW = 1.0f;
static const int MAX_LIGHT_SPLITS = 6;
#ifdef DESKTOP_GRAPHICS
static const unsigned MAX_CASCADE_SPLITS = 4;
#else
static const unsigned MAX_CASCADE_SPLITS = 1;
#endif

/// Depth bias parameters. Used both by lights (for shadow mapping) and materials.
struct URHO3D_API BiasParameters
{
    /// Construct undefined.
    BiasParameters() = default;

    /// Construct with initial values.
    BiasParameters(float constantBias, float slopeScaledBias, float normalOffset = 0.0f) :
        constantBias_(constantBias),
        slopeScaledBias_(slopeScaledBias),
        normalOffset_(normalOffset)
    {
    }

    /// Validate parameters.
    void Validate();

    /// Constant bias.
    float constantBias_;
    /// Slope scaled bias.
    float slopeScaledBias_;
    /// Normal offset multiplier.
    float normalOffset_;
};

/// Cascaded shadow map parameters.
struct URHO3D_API CascadeParameters
{
    /// Construct undefined.
    CascadeParameters() = default;

    /// Construct with initial values.
    CascadeParameters(float split1, float split2, float split3, float split4, float fadeStart, float biasAutoAdjust = 1.0f) :
        fadeStart_(fadeStart),
        biasAutoAdjust_(biasAutoAdjust)
    {
        splits_[0] = split1;
        splits_[1] = split2;
        splits_[2] = split3;
        splits_[3] = split4;
    }

    /// Validate parameters.
    void Validate();

    /// Return shadow maximum range.
    float GetShadowRange() const
    {
        float ret = 0.0f;
        for (unsigned i = 0; i < MAX_CASCADE_SPLITS; ++i)
            ret = Max(ret, splits_[i]);

        return ret;
    }

    /// Far clip values of the splits.
    Vector4 splits_;
    /// The point relative to the total shadow range where shadow fade begins (0.0 - 1.0)
    float fadeStart_{};
    /// Automatic depth bias adjustment strength.
    float biasAutoAdjust_{};
};

/// Shadow map focusing parameters.
struct URHO3D_API FocusParameters
{
    /// Construct undefined.
    FocusParameters() = default;

    /// Construct with initial values.
    FocusParameters(bool focus, bool nonUniform, bool autoSize, float quantize, float minView) :
        focus_(focus),
        nonUniform_(nonUniform),
        autoSize_(autoSize),
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
    /// Auto-size (reduce resolution when far away) flag.
    bool autoSize_;
    /// Focus quantization.
    float quantize_;
    /// Minimum view size.
    float minView_;
};

/// %Light component.
class URHO3D_API Light : public Drawable
{
    URHO3D_OBJECT(Light, Drawable);

public:
    /// Construct.
    explicit Light(Context* context);
    /// Destruct.
    ~Light() override;
    /// Register object factory. Drawable must be registered first.
    static void RegisterObject(Context* context);

    /// Process octree raycast. May be called from a worker thread.
    void ProcessRayQuery(const RayOctreeQuery& query, PODVector<RayQueryResult>& results) override;
    /// Calculate distance and prepare batches for rendering. May be called from worker thread(s), possibly re-entrantly.
    void UpdateBatches(const FrameInfo& frame) override;
    /// Visualize the component as debug geometry.
    void DrawDebugGeometry(DebugRenderer* debug, bool depthTest) override;

    /// Set light type.
    void SetLightType(LightType type);
    /// Set vertex lighting mode.
    void SetPerVertex(bool enable);
    /// Set color.
    void SetColor(const Color& color);
    /// Set temperature of the light in Kelvin. Modulates the light color when "use physical values" is enabled.
    void SetTemperature(float temperature);
    /// Set area light radius. Greater than zero activates area light mode. Works only with PBR shaders.
    void SetRadius(float radius);
    /// Set tube area light length. Works only with PBR shaders.
    void SetLength(float length);
    /// Set use physical light values.
    void SetUsePhysicalValues(bool enable);
    /// Set specular intensity. Zero disables specular calculations.
    void SetSpecularIntensity(float intensity);
    /// Set light brightness multiplier. Both the color and specular intensity are multiplied with this. When "use physical values" is enabled, the value is specified in lumens.
    void SetBrightness(float brightness);
    /// Set range.
    void SetRange(float range);
    /// Set spotlight field of view.
    void SetFov(float fov);
    /// Set spotlight aspect ratio.
    void SetAspectRatio(float aspectRatio);
    /// Set fade out start distance.
    void SetFadeDistance(float distance);
    /// Set shadow fade out start distance. Only has effect if shadow distance is also non-zero.
    void SetShadowFadeDistance(float distance);
    /// Set shadow depth bias parameters.
    void SetShadowBias(const BiasParameters& parameters);
    /// Set directional light cascaded shadow parameters.
    void SetShadowCascade(const CascadeParameters& parameters);
    /// Set shadow map focusing parameters.
    void SetShadowFocus(const FocusParameters& parameters);
    /// Set light intensity in shadow between 0.0 - 1.0. 0.0 (the default) gives fully dark shadows.
    void SetShadowIntensity(float intensity);
    /// Set shadow resolution between 0.25 - 1.0. Determines the shadow map to use.
    void SetShadowResolution(float resolution);
    /// Set shadow camera near/far clip distance ratio for spot and point lights. Does not affect directional lights, since they are orthographic and have near clip 0.
    void SetShadowNearFarRatio(float nearFarRatio);
    /// Set maximum shadow extrusion for directional lights. The actual extrusion will be the smaller of this and camera far clip. Default 1000.
    void SetShadowMaxExtrusion(float extrusion);
    /// Set range attenuation texture.
    void SetRampTexture(Texture* texture);
    /// Set spotlight attenuation texture.
    void SetShapeTexture(Texture* texture);

    /// Return light type.
    LightType GetLightType() const { return lightType_; }

    /// Return vertex lighting mode.
    bool GetPerVertex() const { return perVertex_; }

    /// Return color.
    const Color& GetColor() const { return color_; }

    /// Return the temperature of the light in Kelvin.
    float GetTemperature() const { return temperature_; }

    /// Return area light mode radius. Works only with PBR shaders.
    float GetRadius() const { return lightRad_; }

    /// Return area tube light length. Works only with PBR shaders.
    float GetLength() const { return lightLength_; }

    /// Return if light uses temperature and brightness in lumens.
    bool GetUsePhysicalValues() const { return usePhysicalValues_; }

    /// Return the color value of the temperature in Kelvin.
    Color GetColorFromTemperature() const;

    /// Return specular intensity.
    float GetSpecularIntensity() const { return specularIntensity_; }

    /// Return brightness multiplier. Specified in lumens when "use physical values" is enabled.
    float GetBrightness() const { return brightness_; }

    /// Return effective color, multiplied by brightness and affected by temperature when "use physical values" is enabled. Alpha is always 1 so that can compare against the default black color to detect a light with no effect.
    Color GetEffectiveColor() const;

    /// Return effective specular intensity, multiplied by absolute value of brightness.
    float GetEffectiveSpecularIntensity() const { return specularIntensity_ * Abs(brightness_); }

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

    /// Return light intensity in shadow.
    float GetShadowIntensity() const { return shadowIntensity_; }

    /// Return shadow resolution.
    float GetShadowResolution() const { return shadowResolution_; }

    /// Return shadow camera near/far clip distance ratio.
    float GetShadowNearFarRatio() const { return shadowNearFarRatio_; }

    /// Return maximum shadow extrusion distance for directional lights.
    float GetShadowMaxExtrusion() const { return shadowMaxExtrusion_; }

    /// Return range attenuation texture.
    Texture* GetRampTexture() const { return rampTexture_; }

    /// Return spotlight attenuation texture.
    Texture* GetShapeTexture() const { return shapeTexture_; }

    /// Return spotlight frustum.
    Frustum GetFrustum() const;
    /// Return spotlight frustum in the specified view space.
    Frustum GetViewSpaceFrustum(const Matrix3x4& view) const;

    /// Return number of shadow map cascade splits for a directional light, considering also graphics API limitations.
    int GetNumShadowSplits() const;

    /// Return whether light has negative (darkening) color.
    bool IsNegative() const { return GetEffectiveColor().SumRGB() < 0.0f; }

    /// Set sort value based on intensity and view distance.
    void SetIntensitySortValue(float distance);
    /// Set sort value based on overall intensity over a bounding box.
    void SetIntensitySortValue(const BoundingBox& box);
    /// Set light queue used for this light. Called by View.
    void SetLightQueue(LightBatchQueue* queue);
    /// Return light volume model transform.
    const Matrix3x4& GetVolumeTransform(Camera* camera);

    /// Return light queue. Called by View.
    LightBatchQueue* GetLightQueue() const { return lightQueue_; }

    /// Return a divisor value based on intensity for calculating the sort value.
    float GetIntensityDivisor(float attenuation = 1.0f) const
    {
        return Max(GetEffectiveColor().SumRGB(), 0.0f) * attenuation + M_EPSILON;
    }

    /// Set ramp texture attribute.
    void SetRampTextureAttr(const ResourceRef& value);
    /// Set shape texture attribute.
    void SetShapeTextureAttr(const ResourceRef& value);
    /// Return ramp texture attribute.
    ResourceRef GetRampTextureAttr() const;
    /// Return shape texture attribute.
    ResourceRef GetShapeTextureAttr() const;

    /// Return a transform for deferred fullscreen quad (directional light) rendering.
    static Matrix3x4 GetFullscreenQuadTransform(Camera* camera);

protected:
    /// Recalculate the world-space bounding box.
    void OnWorldBoundingBoxUpdate() override;

private:
    /// Validate shadow focus.
    void ValidateShadowFocus() { shadowFocus_.Validate(); }
    /// Validate shadow cascade.
    void ValidateShadowCascade() { shadowCascade_.Validate(); }
    /// Validate shadow bias.
    void ValidateShadowBias() { shadowBias_.Validate(); }
    /// Light type.
    LightType lightType_;
    /// Color.
    Color color_;
    /// Light temperature.
    float temperature_;
    /// Radius of the light source. If above 0 it will turn the light into an area light.  Works only with PBR shaders.
    float lightRad_;
    /// Length of the light source. If above 0 and radius is above 0 it will create a tube light. Works only with PBR shaders.
    float lightLength_;
    /// Shadow depth bias parameters.
    BiasParameters shadowBias_;
    /// Directional light cascaded shadow parameters.
    CascadeParameters shadowCascade_;
    /// Shadow map focus parameters.
    FocusParameters shadowFocus_;
    /// Custom world transform for the light volume.
    Matrix3x4 volumeTransform_;
    /// Range attenuation texture.
    SharedPtr<Texture> rampTexture_;
    /// Spotlight attenuation texture.
    SharedPtr<Texture> shapeTexture_;
    /// Light queue.
    LightBatchQueue* lightQueue_;
    /// Specular intensity.
    float specularIntensity_;
    /// Brightness multiplier.
    float brightness_;
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
    /// Light intensity in shadow.
    float shadowIntensity_;
    /// Shadow resolution.
    float shadowResolution_;
    /// Shadow camera near/far clip distance ratio.
    float shadowNearFarRatio_;
    /// Directional shadow max. extrusion distance.
    float shadowMaxExtrusion_;
    /// Per-vertex lighting flag.
    bool perVertex_;
    /// Use physical light values flag.
    bool usePhysicalValues_;
};

inline bool CompareLights(Light* lhs, Light* rhs)
{
    // When sorting lights, give priority to per-vertex lights, so that vertex lit base pass can be evaluated first
    if (lhs->GetPerVertex() != rhs->GetPerVertex())
        return lhs->GetPerVertex();
    else
        return lhs->GetSortValue() < rhs->GetSortValue();
}

}
