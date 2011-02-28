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

#ifndef RENDERER_LIGHT_H
#define RENDERER_LIGHT_H

#include "Camera.h"
#include "Color.h"
#include "Frustum.h"
#include "VolumeNode.h"

class Texture;
class Texture2D;
class TextureCube;

//! Light types
enum LightType
{
    LIGHT_DIRECTIONAL = 0,
    LIGHT_POINT,
    LIGHT_SPOT,
    LIGHT_SPLITPOINT
};

//! Shadow depth bias parameters
struct BiasParameters
{
    //! Construct as undefined
    BiasParameters()
    {
    }
    
    //! Construct with initial values
    BiasParameters(float constantBias, float slopeScaledBias) :
        mConstantBias(constantBias),
        mSlopeScaledBias(slopeScaledBias)
    {
    }
    
    //! Validate parameters
    void validate();
    
    //! Constant bias
    float mConstantBias;
    //! Slope scaled bias
    float mSlopeScaledBias;
};

//! Cascaded shadow map parameters
struct CascadeParameters
{
    //! Construct as undefined
    CascadeParameters()
    {
    }
    
    //! Construct with initial values
    CascadeParameters(unsigned splits, float lambda, float splitFadeRange, float shadowRange) :
        mSplits(splits),
        mLambda(lambda),
        mSplitFadeRange(splitFadeRange),
        mShadowRange(shadowRange)
    {
    }
    
    //! Validate parameters
    void validate();
    
    //! Number of splits
    unsigned mSplits;
    //! Split lambda
    float mLambda;
    //! Fade range between splits
    float mSplitFadeRange;
    //! Maximum shadow distance
    float mShadowRange;
};

//! Shadow map focusing parameters
struct FocusParameters
{
    //! Construct as undefined
    FocusParameters()
    {
    }
    
    //! Construct with initial values
    FocusParameters(bool focus, bool nonUniform, bool zoomOut, float quantize, float minView) :
        mFocus(focus),
        mNonUniform(nonUniform),
        mZoomOut(zoomOut),
        mQuantize(quantize),
        mMinView(minView)
    {
    }
    
    //! Validate parameters
    void validate();
    
    //! Focus flag
    bool mFocus;
    //! Non-uniform focusing flag
    bool mNonUniform;
    //! Zoom out flag
    bool mZoomOut;
    //! Focus quantization
    float mQuantize;
    //! Minimum view size
    float mMinView;
};

static const float SHADOW_MIN_QUANTIZE = 0.1f;
static const float SHADOW_MIN_VIEW = 1.0f;
static const float SHADOW_DEFAULT_NEARCLIP = 0.1f;

//! A light scene node
class Light : public VolumeNode
{
    DEFINE_TYPE(Light);
    
public:
    //! Construct with initial octant pointer and name
    Light(Octant* octant = 0, const std::string& name = std::string());
    //! Destruct
    virtual ~Light();
    
    //! Write component state to a stream
    virtual void save(Serializer& dest);
    //! Read component state from a stream
    virtual void load(Deserializer& source, ResourceCache* cache);
    //! Write component state to an XML element
    virtual void saveXML(XMLElement& dest);
    //! Read component state from an XML element
    virtual void loadXML(const XMLElement& source, ResourceCache* cache);
    //! Write a network update
    virtual bool writeNetUpdate(Serializer& dest, Serializer& destRevision, Deserializer& baseRevision, const NetUpdateInfo& info);
    //! Read a network update
    virtual void readNetUpdate(Deserializer& source, ResourceCache* cache, const NetUpdateInfo& info);
    //! Return resource references
    virtual void getResourceRefs(std::vector<Resource*>& dest);
    
    //! Calculate distance for rendering
    virtual void updateDistance(const FrameInfo& frame);
    //! Override model and view transforms for rendering
    virtual void overrideTransforms(unsigned batchIndex, Camera& camera, const Matrix4x3** model, const Matrix4x3** view);
    //! Add debug geometry to the debug renderer
    virtual void drawDebugGeometry(DebugRenderer* debug);
    
    //! Set light type
    void setLightType(LightType type);
    //! Set direction
    void setDirection(const Vector3& direction);
    //! Set color
    void setColor(const Color& color);
    //! Set specular intensity
    void setSpecularIntensity(float intensity);
    //! Set range
    void setRange(float range);
    //! Set spotlight field of view
    void setFov(float fov);
    //! Set spotlight aspect ratio
    void setAspectRatio(float aspectRatio);
    //! Set fade out start distance
    void setFadeDistance(float distance);
    //! Set required detail levels to render light, and render light shadowed
    void setDetailLevel(int detailLevel, int shadowDetailLevel);
    //! Set shadow depth bias parameters
    void setShadowBias(const BiasParameters& parameters);
    //! Set directional light cascaded shadow parameters
    void setShadowCascade(const CascadeParameters& parameters);
    //! Set shadow map focusing parameters
    void setShadowFocus(const FocusParameters& parameters);
    //! Set shadow fade out start distance. Only has effect if shadow distance is also non-zero
    void setShadowFadeDistance(float distance);
    //! Set shadow intensity between 0.0 - 1.0. 0.0 (the default) gives fully dark shadows.
    void setShadowIntensity(float intensity);
    //! Set shadow resolution between 0.25 - 1.0. Determines the shadow map to use
    void setShadowResolution(float resolution);
    //! Set shadow camera near/far clip distance ratio
    void setShadowNearFarRatio(float nearFarRatio);
    //! Set range attenuation texture
    void setRampTexture(Texture* texture);
    //! Set spotlight attenuation texture
    void setSpotTexture(Texture* texture);
    
    //! Return light type
    LightType getLightType() const { return mLightType; }
    //! Return direction
    const Vector3& getDirection() const { return mDirection; }
    //! Return color
    const Color& getColor() const { return mColor; }
    //! Return specular intensity
    float getSpecularIntensity() const { return mSpecularIntensity; }
    //! Return whether light color is negative
    bool isNegative() const;
    //! Return range
    float getRange() const { return mRange; }
    //! Return spotlight field of view
    float getFov() const { return mFov; }
    //! Return spotlight aspect ratio
    float getAspectRatio() const { return mAspectRatio; }
    //! Return fade start distance
    float getFadeDistance() const { return mFadeDistance; }
    //! Return required detail level to render light
    int getDetailLevel() const { return mDetailLevel; }
    //! Return required detail level to render light shadowed
    int getShadowDetailLevel() const { return mShadowDetailLevel; }
    //! Return shadow depth bias parameters
    const BiasParameters& getShadowBias() const { return mShadowBias; }
    //! Return directional light cascaded shadow parameters
    const CascadeParameters& getShadowCascade() const { return mShadowCascade; }
    //! Return shadow map focus parameters
    const FocusParameters& getShadowFocus() const { return mShadowFocus; }
    //! Return shadow fade start distance
    float getShadowFadeDistance() const { return mShadowFadeDistance; }
    //! Return shadow intensity
    float getShadowIntensity() const { return mShadowIntensity; }
    //! Return shadow resolution
    float getShadowResolution() const { return mShadowResolution; }
    //! Return shadow camera near/far clip distance ratio
    float getShadowNearFarRatio() const { return mShadowNearFarRatio; }
    //! Return range attenuation texture
    Texture* getRampTexture() const { return mRampTexture; }
    //! Return spotlight attenuation texture
    Texture* getSpotTexture() const { return mSpotTexture; }
    //! Return spotlight frustum
    const Frustum& getFrustum();
    
    //! Set near split distance for directional light
    void setNearSplit(float near);
    //! Set far split distance for directional light
    void setFarSplit(float far);
    //! Set near fade range for directional light
    void setNearFadeRange(float range);
    //! Set far fade range for directional light
    void setFarFadeRange(float range);
    //! Set shadow map depth texture
    void setShadowMap(Texture2D* shadowMap);
    //! Copy values from another light
    void copyFrom(Light* original);
    //! Return near split distance
    float getNearSplit() const { return mNearSplit; }
    //! Return far split distance
    float getFarSplit() const { return mFarSplit; }
    //! Return near fade range
    float getNearFadeRange() const { return mNearFadeRange; }
    //! Return far fade range
    float getFarFadeRange() const { return mFarFadeRange; }
    //! Return shadow camera
    Camera& getShadowCamera() { return mShadowCamera; }
    //! Return shadow map
    Texture2D* getShadowMap() const { return mShadowMap; }
    //! Return volume safety extent of spot or point light
    float getVolumeExtent() const;
    //! Return directional light near or far quad transform
    Matrix4x3 getDirLightTransform(Camera& camera, bool getNearQuad) const;
    
protected:
    //! Transform has changed. Mark spotlight frustum dirty
    virtual void onMarkedDirty();
    //! Update world-space bounding box
    virtual void onWorldBoundingBoxUpdate(BoundingBox& worldBoundingBox);
    
private:
    //! Light type
    LightType mLightType;
    //! Direction
    Vector3 mDirection;
    //! Color
    Color mColor;
    //! Specular intensity
    float mSpecularIntensity;
    //! Range
    float mRange;
    //! Spotlight field of view
    float mFov;
    //! Spotlight aspect ratio
    float mAspectRatio;
    //! Fade start distance
    float mFadeDistance;
    //! Required detail level to render light
    int mDetailLevel;
    //! Required detail level to render light shadowed
    int mShadowDetailLevel;
    //! Shadow depth bias parameters
    BiasParameters mShadowBias;
    //! Directional light cascaded shadow parameters
    CascadeParameters mShadowCascade;
    //! Shadow map focus parameters
    FocusParameters mShadowFocus;
    //! Shadow fade start distance
    float mShadowFadeDistance;
    //! Shadow intensity
    float mShadowIntensity;
    //! Shadow resolution
    float mShadowResolution;
    //! Shadow camera near/far clip distance ratio
    float mShadowNearFarRatio;
    //! Directional light near split distance
    float mNearSplit;
    //! Directional light far split distance
    float mFarSplit;
    //! Directional light near fade range
    float mNearFadeRange;
    //! Directional light far fade range
    float mFarFadeRange;
    //! Frustum needs update flag
    bool mFrustumDirty;
    //! Spotlight frustum
    Frustum mFrustum;
    //! Shadow camera
    Camera mShadowCamera;
    //! Shadow map
    Texture2D* mShadowMap;
    //! Range attenuation texture
    SharedPtr<Texture> mRampTexture;
    //! Spotlight attenuation texture
    SharedPtr<Texture> mSpotTexture;
};

#endif // RENDERER_LIGHT_H
