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

#include "../Graphics/GraphicsDefs.h"
#include "../Resource/Resource.h"

namespace Urho3D
{

/// Particle emitter shapes.
enum EmitterType
{
    EMITTER_SPHERE = 0,
    EMITTER_BOX,
    EMITTER_SPHEREVOLUME,
    EMITTER_CYLINDER,
    EMITTER_RING
};

/// %Color animation frame definition.
/// @fakeref
struct ColorFrame
{
    /// Construct with default values.
    ColorFrame() :
        time_(0.0f)
    {
    }

    /// Construct with a color and zero time.
    explicit ColorFrame(const Color& color) :
        color_(color),
        time_(0.0f)
    {
    }

    /// Construct from a color and time.
    ColorFrame(const Color& color, float time) :
        color_(color),
        time_(time)
    {
    }

    /// Return interpolated value with another color-time pair at the time specified.
    Color Interpolate(const ColorFrame& next, float time) const
    {
        float timeInterval = next.time_ - time_;
        if (timeInterval > 0.0f)
        {
            float t = (time - time_) / timeInterval;
            return color_.Lerp(next.color_, t);
        }
        else
            return next.color_;
    }

    /// Color.
    Color color_;
    /// Time.
    float time_;
};

/// %Texture animation frame definition.
/// @fakeref
struct TextureFrame
{
    /// Construct with default values.
    TextureFrame() :
        uv_(0.0f, 0.0f, 1.0f, 1.0f),
        time_(0.0f)
    {
    }

    /// UV coordinates.
    Rect uv_;
    /// Time.
    float time_;
};

static const unsigned DEFAULT_NUM_PARTICLES = 10;

class Material;
class XMLFile;
class XMLElement;

/// %Particle effect definition.
class URHO3D_API ParticleEffect : public Resource
{
    URHO3D_OBJECT(ParticleEffect, Resource);

public:
    /// Construct.
    explicit ParticleEffect(Context* context);
    /// Destruct.
    ~ParticleEffect() override;
    /// Register object factory.
    /// @nobind
    static void RegisterObject(Context* context);

    /// Load resource from stream. May be called from a worker thread. Return true if successful.
    bool BeginLoad(Deserializer& source) override;
    /// Finish resource loading. Always called from the main thread. Return true if successful.
    bool EndLoad() override;
    /// Save resource. Return true if successful.
    bool Save(Serializer& dest) const override;

    /// Save resource to XMLElement. Return true if successful.
    bool Save(XMLElement& dest) const;
    /// Load resource from XMLElement synchronously. Return true if successful.
    bool Load(const XMLElement& source);
    /// Set material.
    /// @property
    void SetMaterial(Material* material);
    /// Set maximum number of particles.
    /// @property
    void SetNumParticles(unsigned num);
    /// Set whether to update when particles are not visible.
    /// @property
    void SetUpdateInvisible(bool enable);
    /// Set whether billboards are relative to the scene node.
    /// @property
    void SetRelative(bool enable);
    /// Set whether scene node scale affects billboards' size.
    /// @property
    void SetScaled(bool enable);
    /// Set whether billboards are sorted by distance.
    /// @property
    void SetSorted(bool enable);
    /// Set whether billboards have fixed size on screen (measured in pixels) regardless of distance to camera.
    /// @property
    void SetFixedScreenSize(bool enable);
    /// Set animation LOD bias.
    /// @property
    void SetAnimationLodBias(float lodBias);
    /// Set emitter type.
    /// @property
    void SetEmitterType(EmitterType type);
    /// Set emitter size.
    /// @property
    void SetEmitterSize(const Vector3& size);
    /// Set negative direction limit.
    /// @property
    void SetMinDirection(const Vector3& direction);
    /// Set positive direction limit.
    /// @property
    void SetMaxDirection(const Vector3& direction);
    /// Set constant force acting on particles.
    /// @property
    void SetConstantForce(const Vector3& force);
    /// Set particle velocity damping force.
    /// @property
    void SetDampingForce(float force);
    /// Set emission active period length (0 = infinite).
    /// @property
    void SetActiveTime(float time);
    /// Set emission inactive period length (0 = infinite).
    /// @property
    void SetInactiveTime(float time);
    /// Set minimum emission rate.
    /// @property
    void SetMinEmissionRate(float rate);
    /// Set maximum emission rate.
    /// @property
    void SetMaxEmissionRate(float rate);
    /// Set particle minimum size.
    /// @property
    void SetMinParticleSize(const Vector2& size);
    /// Set particle maximum size.
    /// @property
    void SetMaxParticleSize(const Vector2& size);
    /// Set particle minimum time to live.
    /// @property
    void SetMinTimeToLive(float time);
    /// Set particle maximum time to live.
    /// @property
    void SetMaxTimeToLive(float time);
    /// Set particle minimum velocity.
    /// @property
    void SetMinVelocity(float velocity);
    /// Set particle maximum velocity.
    /// @property
    void SetMaxVelocity(float velocity);
    /// Set particle minimum rotation.
    /// @property
    void SetMinRotation(float rotation);
    /// Set particle maximum rotation.
    /// @property
    void SetMaxRotation(float rotation);
    /// Set particle minimum rotation speed.
    /// @property
    void SetMinRotationSpeed(float speed);
    /// Set particle maximum rotation speed.
    /// @property
    void SetMaxRotationSpeed(float speed);
    /// Set particle size additive modifier.
    /// @property
    void SetSizeAdd(float sizeAdd);
    /// Set particle size multiplicative modifier.
    /// @property
    void SetSizeMul(float sizeMul);
    /// Set how the particles should rotate in relation to the camera. Default is to follow camera rotation on all axes (FC_ROTATE_XYZ).
    /// @property
    void SetFaceCameraMode(FaceCameraMode mode);

    /// Add a color frame sorted in the correct position based on time.
    void AddColorTime(const Color& color, float time);
    /// Add a color frame sorted in the correct position based on time.
    void AddColorFrame(const ColorFrame& colorFrame);
    /// Remove color frame at index.
    void RemoveColorFrame(unsigned index);
    /// Set color animation of particles.
    void SetColorFrames(const Vector<ColorFrame>& colorFrames);
    /// Set color animation frame at index. If index is greater than number of color frames, new color frames are added.
    void SetColorFrame(unsigned index, const ColorFrame& colorFrame);
    /// Set number of color frames.
    /// @property
    void SetNumColorFrames(unsigned number);
    /// Sort the list of color frames based on time.
    void SortColorFrames();

    /// Add a texture frame sorted in the correct position based on time.
    void AddTextureTime(const Rect& uv, float time);
    /// Add a texture frame sorted in the correct position based on time.
    void AddTextureFrame(const TextureFrame& textureFrame);
    /// Remove texture frame at index.
    void RemoveTextureFrame(unsigned index);
    /// Set particle texture animation.
    void SetTextureFrames(const Vector<TextureFrame>& textureFrames);
    /// Set number of texture animation frames.
    void SetTextureFrame(unsigned index, const TextureFrame& textureFrame);
    /// Set number of texture frames.
    /// @property
    void SetNumTextureFrames(unsigned number);
    /// Sort the list of texture frames based on time.
    void SortTextureFrames();
    /// Clone the particle effect.
    SharedPtr<ParticleEffect> Clone(const String& cloneName = String::EMPTY) const;

    /// Return material.
    /// @property
    Material* GetMaterial() const { return material_; }

    /// Return maximum number of particles.
    /// @property
    unsigned GetNumParticles() const { return numParticles_; }

    /// Return whether to update when particles are not visible.
    /// @property
    bool GetUpdateInvisible() const { return updateInvisible_; }

    /// Return whether billboards are relative to the scene node.
    /// @property
    bool IsRelative() const { return relative_; }

    /// Return whether scene node scale affects billboards' size.
    /// @property
    bool IsScaled() const { return scaled_; }

    /// Return whether billboards are sorted.
    /// @property
    bool IsSorted() const { return sorted_; }

    /// Return whether billboards are fixed screen size.
    /// @property
    bool IsFixedScreenSize() const { return fixedScreenSize_; }

    /// Return animation Lod bias.
    /// @property
    float GetAnimationLodBias() const { return animationLodBias_; }

    /// Return emitter type.
    /// @property
    EmitterType GetEmitterType() const { return emitterType_; }

    /// Return emitter size.
    /// @property
    const Vector3& GetEmitterSize() const { return emitterSize_; }

    /// Return negative direction limit.
    /// @property
    const Vector3& GetMinDirection() const { return directionMin_; }

    /// Return positive direction limit.
    /// @property
    const Vector3& GetMaxDirection() const { return directionMax_; }

    /// Return constant force acting on particles.
    /// @property
    const Vector3& GetConstantForce() const { return constantForce_; }

    /// Return particle velocity damping force.
    /// @property
    float GetDampingForce() const { return dampingForce_; }

    /// Return emission active period length (0 = infinite).
    /// @property
    float GetActiveTime() const { return activeTime_; }

    /// Return emission inactive period length (0 = infinite).
    /// @property
    float GetInactiveTime() const { return inactiveTime_; }

    /// Return minimum emission rate.
    /// @property
    float GetMinEmissionRate() const { return emissionRateMin_; }

    /// Return maximum emission rate.
    /// @property
    float GetMaxEmissionRate() const { return emissionRateMax_; }

    /// Return particle minimum size.
    /// @property
    const Vector2& GetMinParticleSize() const { return sizeMin_; }

    /// Return particle maximum size.
    /// @property
    const Vector2& GetMaxParticleSize() const { return sizeMax_; }

    /// Return particle minimum time to live.
    /// @property
    float GetMinTimeToLive() const { return timeToLiveMin_; }

    /// Return particle maximum time to live.
    /// @property
    float GetMaxTimeToLive() const { return timeToLiveMax_; }

    /// Return particle minimum velocity.
    /// @property
    float GetMinVelocity() const { return velocityMin_; }

    /// Return particle maximum velocity.
    /// @property
    float GetMaxVelocity() const { return velocityMax_; }

    /// Return particle minimum rotation.
    /// @property
    float GetMinRotation() const { return rotationMin_; }

    /// Return particle maximum rotation.
    /// @property
    float GetMaxRotation() const { return rotationMax_; }

    /// Return particle minimum rotation speed.
    /// @property
    float GetMinRotationSpeed() const { return rotationSpeedMin_; }

    /// Return particle maximum rotation speed.
    /// @property
    float GetMaxRotationSpeed() const { return rotationSpeedMax_; }

    /// Return particle size additive modifier.
    /// @property
    float GetSizeAdd() const { return sizeAdd_; }

    /// Return particle size multiplicative modifier.
    /// @property
    float GetSizeMul() const { return sizeMul_; }

    /// Return all color animation frames.
    const Vector<ColorFrame>& GetColorFrames() const { return colorFrames_; }

    /// Return number of color animation frames.
    /// @property
    unsigned GetNumColorFrames() const { return colorFrames_.Size(); }

    /// Return a color animation frame, or null if outside range.
    const ColorFrame* GetColorFrame(unsigned index) const;

    /// Return all texture animation frames.
    const Vector<TextureFrame>& GetTextureFrames() const { return textureFrames_; }

    /// Return number of texture animation frames.
    /// @property
    unsigned GetNumTextureFrames() const { return textureFrames_.Size(); }

    /// Return a texture animation frame, or null if outside range.
    const TextureFrame* GetTextureFrame(unsigned index) const;

    /// Return how the particles rotate in relation to the camera.
    /// @property
    FaceCameraMode GetFaceCameraMode() const { return faceCameraMode_; }

    /// Return random direction.
    Vector3 GetRandomDirection() const;
    /// Return random size.
    Vector2 GetRandomSize() const;
    /// Return random velocity.
    float GetRandomVelocity() const;
    /// Return random timetolive.
    float GetRandomTimeToLive() const;
    /// Return random rotationspeed.
    float GetRandomRotationSpeed() const;
    /// Return random rotation.
    float GetRandomRotation() const;

private:
    /// Read a float range from an XML element.
    void GetFloatMinMax(const XMLElement& element, float& minValue, float& maxValue);
    /// Read a Vector2 range from an XML element.
    void GetVector2MinMax(const XMLElement& element, Vector2& minValue, Vector2& maxValue);
    /// Read a Vector3 from an XML element.
    void GetVector3MinMax(const XMLElement& element, Vector3& minValue, Vector3& maxValue);

    /// Material.
    SharedPtr<Material> material_;
    /// Number of particles.
    unsigned numParticles_;
    /// Update when invisible flag.
    bool updateInvisible_;
    /// Billboards relative flag.
    bool relative_;
    /// Scale affects billboard scale flag.
    bool scaled_;
    /// Billboards sorted flag.
    bool sorted_;
    /// Billboards fixed screen size flag.
    bool fixedScreenSize_;
    /// Animation LOD bias.
    float animationLodBias_;
    /// Emitter shape.
    EmitterType emitterType_;
    /// Emitter size.
    Vector3 emitterSize_;
    /// Particle direction minimum.
    Vector3 directionMin_;
    /// Particle direction maximum.
    Vector3 directionMax_;
    /// Particle constant force.
    Vector3 constantForce_;
    /// Particle velocity damping force.
    float dampingForce_;
    /// Active period.
    float activeTime_;
    /// Inactive period.
    float inactiveTime_;
    /// Particles per second minimum.
    float emissionRateMin_;
    /// Particles per second maximum.
    float emissionRateMax_;
    /// Particle size minimum.
    Vector2 sizeMin_;
    /// Particle size maximum.
    Vector2 sizeMax_;
    /// Particle time to live minimum.
    float timeToLiveMin_;
    /// Particle time to live maximum.
    float timeToLiveMax_;
    /// Particle velocity minimum.
    float velocityMin_;
    /// Particle velocity maximum.
    float velocityMax_;
    /// Particle rotation angle minimum.
    float rotationMin_;
    /// Particle rotation angle maximum.
    float rotationMax_;
    /// Particle rotation speed minimum.
    float rotationSpeedMin_;
    /// Particle rotation speed maximum.
    float rotationSpeedMax_;
    /// Particle size additive parameter.
    float sizeAdd_;
    /// Particle size multiplicative parameter.
    float sizeMul_;
    /// Particle color animation frames.
    Vector<ColorFrame> colorFrames_;
    /// Texture animation frames.
    Vector<TextureFrame> textureFrames_;
    /// Material name acquired during BeginLoad().
    String loadMaterialName_;
    /// Particle rotation mode in relation to the camera.
    FaceCameraMode faceCameraMode_;
};

}
