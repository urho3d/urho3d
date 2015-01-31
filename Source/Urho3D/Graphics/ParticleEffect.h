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

#pragma once

#include "../Resource/Resource.h"

namespace Urho3D
{

/// Particle emitter shapes.
enum EmitterType
{
    EMITTER_SPHERE,
    EMITTER_BOX
};

/// %Color animation frame definition.
struct ColorFrame
{
    /// Construct with default values.
    ColorFrame() :
        time_(0.0f)
    {
    }

    /// Construct with a color and zero time.
    ColorFrame(const Color& color) :
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
    OBJECT(ParticleEffect);

public:
    /// Construct.
    ParticleEffect(Context* context);
    /// Destruct.
    virtual ~ParticleEffect();
    /// Register object factory.
    static void RegisterObject(Context* context);

    /// Load resource from stream. May be called from a worker thread. Return true if successful.
    virtual bool BeginLoad(Deserializer& source);
    /// Finish resource loading. Always called from the main thread. Return true if successful.
    virtual bool EndLoad();
    /// Save resource. Return true if successful.
    virtual bool Save(Serializer& dest) const;
    
    /// Save resource to XMLElement. Return true if successful.
    bool Save(XMLElement& dest) const;
    /// Load resource from XMLElement synchronously. Return true if successful.
    bool Load(const XMLElement& source);
    /// Set material.
    void SetMaterial(Material* material);
    /// Set maximum number of particles.
    void SetNumParticles(unsigned num);
    /// Set whether to update when particles are not visible.
    void SetUpdateInvisible(bool enable);
    /// Set whether billboards are relative to the scene node. Default true.
    void SetRelative(bool enable);
    /// Set scaled.
    void SetScaled(bool enable);
    /// Set sorted.
    void SetSorted(bool enable);
    /// Set animation LOD bias.
    void SetAnimationLodBias(float lodBias);
    /// Set emitter type.
    void SetEmitterType(EmitterType type);
    /// Set emitter size.
    void SetEmitterSize(const Vector3& size);
    /// Set negative direction limit.
    void SetMinDirection(const Vector3& direction);
    /// Set positive direction limit.
    void SetMaxDirection(const Vector3& direction);
    /// Set constant force acting on particles.
    void SetConstantForce(const Vector3& force);
    /// Set particle velocity damping force.
    void SetDampingForce(float force);
    /// Set emission active period length (0 = infinite.)
    void SetActiveTime(float time);
    /// Set emission inactive period length (0 = infinite.)
    void SetInactiveTime(float time);
    /// Set minimum emission rate.
    void SetMinEmissionRate(float rate);
    /// Set maximum emission rate.
    void SetMaxEmissionRate(float rate);
    /// Set particle minimum size.
    void SetMinParticleSize(const Vector2& size);
    /// Set particle maximum size.
    void SetMaxParticleSize(const Vector2& size);
    /// Set particle minimum time to live.
    void SetMinTimeToLive(float time);
    /// Set particle maximum time to live.
    void SetMaxTimeToLive(float time);
    /// Set particle minimum velocity.
    void SetMinVelocity(float velocity);
    /// Set particle maximum velocity.
    void SetMaxVelocity(float velocity);
    /// Set particle minimum rotation.
    void SetMinRotation(float rotation);
    /// Set particle maximum rotation.
    void SetMaxRotation(float rotation);
    /// Set particle minimum rotation speed.
    void SetMinRotationSpeed(float speed);
    /// Set particle maximum rotation speed.
    void SetMaxRotationSpeed(float speed);    
    /// Set particle size additive modifier.
    void SetSizeAdd(float sizeAdd);
    /// Set particle size multiplicative modifier.
    void SetSizeMul(float sizeMul);

    /// Add a color frame sorted in the correct position based on time.
    void AddColorTime(const Color& color, const float time);
    /// Add a color frame sorted in the correct position based on time.
    void AddColorFrame(const ColorFrame& colorFrame);
    /// Remove color frame at index
    void RemoveColorFrame(unsigned index);
    /// Set color animation of particles.
    void SetColorFrames(const Vector<ColorFrame>& colorFrames);
    /// Set color animation frame at index. If index is greater than number of color frames, new color frames are added.
    void SetColorFrame(unsigned index, const ColorFrame& colorFrame);
    /// Set number of color frames.
    void SetNumColorFrames(unsigned number);
    /// Sort the list of color frames based on time.
    void SortColorFrames();

    /// Add a texture frame sorted in the correct position based on time.
    void AddTextureTime(const Rect& uv, const float time);
    /// Add a texture frame sorted in the correct position based on time.
    void AddTextureFrame(const TextureFrame& textureFrame);
    /// Remove texture frame at index
    void RemoveTextureFrame(unsigned index);
    /// Set particle texture animation.
    void SetTextureFrames(const Vector<TextureFrame>& animation);
    /// Set number of texture animation frames.
    void SetTextureFrame(unsigned index, const TextureFrame& textureFrame);
    /// Set number of texture frames.
    void SetNumTextureFrames(unsigned number);
    /// Sort the list of texture frames based on time.
    void SortTextureFrames();

    /// Return material.
    Material* GetMaterial() const { return material_; }
    /// Return maximum number of particles.
    unsigned GetNumParticles() const { return numParticles_; }
    /// Return whether to update when particles are not visible.
    bool GetUpdateInvisible() const { return updateInvisible_; }
    /// Return whether billboards are relative to the scene node.
    bool IsRelative() const { return relative_; }
    /// Return whether scene node scale affects billboards' size.
    bool IsScaled() const { return scaled_; }
    /// Return whether billboards are sorted.
    bool IsSorted() const { return sorted_; }
    /// Return animation Lod bias.
    float GetAnimationLodBias() const { return animationLodBias_; }
    /// Return emitter type.
    EmitterType GetEmitterType() const { return emitterType_; }
    /// Return emitter size.
    const Vector3& GetEmitterSize() const { return emitterSize_; }
    /// Return negative direction limit.
    const Vector3& GetMinDirection() const { return directionMin_; }
    /// Return positive direction limit.
    const Vector3& GetMaxDirection() const { return directionMax_; }
    /// Return constant force acting on particles.
    const Vector3& GetConstantForce() const { return constantForce_; }
    /// Return particle velocity damping force.
    float GetDampingForce() const { return dampingForce_; }
    /// Return emission active period length (0 = infinite.)
    float GetActiveTime() const { return activeTime_; }
    /// Return emission inactive period length (0 = infinite.)
    float GetInactiveTime() const { return inactiveTime_; }
    /// Return minimum emission rate.
    float GetMinEmissionRate() const { return emissionRateMin_; }
    /// Return maximum emission rate.
    float GetMaxEmissionRate() const { return emissionRateMax_; }
    /// Return particle minimum size.
    const Vector2& GetMinParticleSize() const { return sizeMin_; }
    /// Return particle maximum size.
    const Vector2& GetMaxParticleSize() const { return sizeMax_; }
    /// Return particle minimum time to live.
    float GetMinTimeToLive() const { return timeToLiveMin_; }
    /// Return particle maximum time to live.
    float GetMaxTimeToLive() const { return timeToLiveMax_; }
    /// Return particle minimum velocity.
    float GetMinVelocity() const { return velocityMin_; }
    /// Return particle maximum velocity.
    float GetMaxVelocity() const { return velocityMax_; }
    /// Return particle minimum rotation.
    float GetMinRotation() const { return rotationMin_; }
    /// Return particle maximum rotation.
    float GetMaxRotation() const { return rotationMax_; }
    /// Return particle minimum rotation speed.
    float GetMinRotationSpeed() const { return rotationSpeedMin_; }
    /// Return particle maximum rotation speed.
    float GetMaxRotationSpeed() const { return rotationSpeedMax_; }   
    /// Return particle size additive modifier.
    float GetSizeAdd() const { return sizeAdd_; }
    /// Return particle size multiplicative modifier.
    float GetSizeMul() const { return sizeMul_; }
    /// Return all color animation frames.
    const Vector<ColorFrame>& GetColorFrames() const { return colorFrames_; }
    /// Return number of color animation frames.
    unsigned GetNumColorFrames() const { return colorFrames_.Size(); }
    /// Return a color animation frame, or null if outside range.
    const ColorFrame* GetColorFrame(unsigned index) const;
    /// Return all texture animation frames.
    const Vector<TextureFrame>& GetTextureFrames() const { return textureFrames_; }
    /// Return number of texture animation frames.
    unsigned GetNumTextureFrames() const { return textureFrames_.Size(); }
    /// Return a texture animation frame, or null if outside range.
    const TextureFrame* GetTextureFrame(unsigned index) const;

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
};

}
