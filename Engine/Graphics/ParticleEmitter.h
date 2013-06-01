//
// Copyright (c) 2008-2013 the Urho3D project.
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

#include "BillboardSet.h"

namespace Urho3D
{

/// Determines the emitter shape.
enum EmitterType
{
    EMITTER_SPHERE,
    EMITTER_BOX
};

/// One particle in the particle system.
struct Particle
{
    /// Velocity.
    Vector3 velocity_;
    /// Original billboard size.
    Vector2 size_;
    /// Time elapsed from creation.
    float timer_;
    /// Lifetime.
    float timeToLive_;
    /// Size scaling value.
    float scale_;
    /// Rotation speed.
    float rotationSpeed_;
    /// Current color fade index.
    unsigned colorIndex_;
    /// Current texture animation index.
    unsigned texIndex_;
};

/// %Texture animation definition.
struct TextureAnimation
{
    /// UV coordinates.
    Rect uv_;
    /// Time.
    float time_;
};

class XMLFile;
class XMLElement;

/// %Particle emitter component.
class ParticleEmitter : public BillboardSet
{
    OBJECT(ParticleEmitter);
    
public:
    /// Construct.
    ParticleEmitter(Context* context);
    /// Destruct.
    virtual ~ParticleEmitter();
    /// Register object factory.
    static void RegisterObject(Context* context);
    
    /// Handle enabled/disabled state change.
    virtual void OnSetEnabled();
    /// Update before octree reinsertion. Is called from a worker thread. Needs to be requested with MarkForUpdate().
    virtual void Update(const FrameInfo& frame);
    
    /// Load emitter parameters from an XML file.
    bool Load(XMLFile* file);
    /// Set maximum number of particles.
    void SetNumParticles(unsigned num);
    /// Set emission rate (both minimum and maximum.)
    void SetEmissionRate(float rate);
    /// Set minimum emission rate.
    void SetMinEmissionRate(float rate);
    /// Set maximum emission rate.
    void SetMaxEmissionRate(float rate);
    /// Set emitter type.
    void SetEmitterType(EmitterType type);
    /// Set emitter size.
    void SetEmitterSize(const Vector3& size);
    /// Set emission active period length (0 = infinite.)
    void SetActiveTime(float time);
    /// Set emission inactive period length (0 = infinite.)
    void SetInactiveTime(float time);
    /// Set whether should be emitting and optionally reset emission period.
    void SetEmitting(bool enable, bool resetPeriod = false);
    /// Set particle time to live (both minimum and maximum.)
    void SetTimeToLive(float time);
    /// Set particle minimum time to live.
    void SetMinTimeToLive(float time);
    /// Set particle maximum time to live.
    void SetMaxTimeToLive(float time);
    /// Set particle size (both minimum and maximum.)
    void SetParticleSize(const Vector2& size);
    /// Set particle minimum size.
    void SetMinParticleSize(const Vector2& size);
    /// Set particle maximum size.
    void SetMaxParticleSize(const Vector2& size);
    /// Set negative direction limit.
    void SetMinDirection(const Vector3& direction);
    /// Set positive direction limit.
    void SetMaxDirection(const Vector3& direction);
    /// Set particle velocity (both minimum and maximum.)
    void SetVelocity(float velocity);
    /// Set particle minimum velocity.
    void SetMinVelocity(float velocity);
    /// Set particle maximum velocity.
    void SetMaxVelocity(float velocity);
    /// Set particle rotation (both minimum and maximum.)
    void SetRotation(float rotation);
    /// Set particle minimum rotation.
    void SetMinRotation(float rotation);
    /// Set particle maximum rotation.
    void SetMaxRotation(float rotation);
    /// Set particle rotation speed (both minimum and maximum.)
    void SetRotationSpeed(float speed);
    /// Set particle minimum rotation speed.
    void SetMinRotationSpeed(float speed);
    /// Set particle maximum rotation speed.
    void SetMaxRotationSpeed(float speed);
    /// Set constant force acting on particles.
    void SetConstantForce(const Vector3& force);
    /// Set particle velocity damping force.
    void SetDampingForce(float force);
    /// Set particle size additive modifier.
    void SetSizeAdd(float sizeAdd);
    /// Set particle size multiplicative modifier.
    void SetSizeMul(float sizeMul);
    /// Set color of particles.
    void SetParticleColor(const Color& color);
    /// Set color fade of particles.
    void SetParticleColors(const Vector<ColorFade>& colors);
    /// Set number of color fade frames.
    void SetNumParticleColors(unsigned num);
    /// Set particle texture animations.
    void SetTextureAnimation(const Vector<TextureAnimation>& animation);
    /// Set number of particle texture animation frames.
    void SetNumTextureAnimation(unsigned num);
    
    /// Return maximum number of particles.
    unsigned GetNumParticles() const { return particles_.Size(); }
    /// Return whether is currently emitting.
    bool IsEmitting() const { return emitting_; }
    /// Return minimum emission rate.
    float GetMinEmissionRate() const { return emissionRateMin_; }
    /// Return maximum emission rate.
    float GetMaxEmissionRate() const { return emissionRateMax_; }
    /// Return emitter type.
    EmitterType GetEmitterType() const { return emitterType_; }
    /// Return emitter size.
    const Vector3& GetEmitterSize() const { return emitterSize_; }
    /// Return emission active period length (0 = infinite.)
    float GetActiveTime() const { return activeTime_; }
    /// Return emission inactive period length (0 = infinite.)
    float GetInactiveTime() const { return inactiveTime_; }
    /// Return particle minimum time to live.
    float GetMinTimeToLive() const { return timeToLiveMin_; }
    /// Return particle maximum time to live.
    float GetMaxTimeToLive() const { return timeToLiveMax_; }
    /// Return particle minimum size.
    const Vector2& GetMinParticleSize() const { return sizeMin_; }
    /// Return particle maximum size.
    const Vector2& GetMaxParticleSize() const { return sizeMax_; }
    /// Return negative direction limit.
    const Vector3& GetMinDirection() const { return directionMin_; }
    /// Return positive direction limit.
    const Vector3& GetMaxDirection() const { return directionMax_; }
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
    /// Return constant force acting on particles.
    const Vector3& GetConstantForce() const { return constantForce_; }
    /// Return particle velocity damping force.
    float GetDampingForce() const { return dampingForce_; }
    /// Return particle size additive modifier.
    float GetSizeAdd() const { return sizeAdd_; }
    /// Return particle size multiplicative modifier.
    float GetSizeMul() const { return sizeMul_; }
    /// Return all color fade frames.
    Vector<ColorFade>& GetParticleColors() { return colors_; }
    /// Return number of color fade frames.
    unsigned GetNumParticleColors() const { return colors_.Size(); }
    /// Return one color fade frame, or null if outside range.
    ColorFade* GetParticleColors(unsigned index) { return index < colors_.Size() ? &colors_[index] : (ColorFade*)0; }
    /// Return all texture animation frames.
    Vector<TextureAnimation>& GetTextureAnimation() { return textureAnimation_; }
    /// Return number of texture animation frames.
    unsigned GetNumTextureAnimation() const { return textureAnimation_.Size(); }
    /// Return one texture animation frame, or null if outside range.
    TextureAnimation* GetTextureAnimation(unsigned index) { return index < colors_.Size() ? &textureAnimation_[index] : (TextureAnimation*)0; }
    
    /// Set particles attribute.
    void SetParticlesAttr(VariantVector value);
    /// Return particles attribute.
    VariantVector GetParticlesAttr() const;
    /// Set particle colors attribute.
    void SetParticleColorsAttr(VariantVector value);
    /// Return particle colors attribute.
    VariantVector GetParticleColorsAttr() const;
    /// Set texture animation attribute.
    void SetTextureAnimationAttr(VariantVector value);
    /// Return texture animation attribute.
    VariantVector GetTextureAnimationAttr() const;
    
protected:
    /// Handle node being assigned.
    virtual void OnNodeSet(Node* node);
    
    /// Create a new particle. Return true if there was room.
    bool EmitNewParticle();
    /// Return a free particle index.
    unsigned GetFreeParticle() const;
    /// Read a float range from an XML element.
    void GetFloatMinMax(const XMLElement& element, float& minValue, float& maxValue);
    /// Read a Vector2 range from an XML element.
    void GetVector2MinMax(const XMLElement& element, Vector2& minValue, Vector2& maxValue);
    /// Read a Vector3 from an XML element.
    void GetVector3MinMax(const XMLElement& element, Vector3& minValue, Vector3& maxValue);
    
private:
    /// Handle scene post-update event.
    void HandleScenePostUpdate(StringHash eventType, VariantMap& eventData);
    
    /// Particles.
    PODVector<Particle> particles_;
    /// Color fade range.
    Vector<ColorFade> colors_;
    /// Texture animation.
    Vector<TextureAnimation> textureAnimation_;
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
    /// Particle size minimum.
    Vector2 sizeMin_;
    /// Particle size maximum.
    Vector2 sizeMax_;
    /// Particle velocity damping force.
    float dampingForce_;
    /// Active/inactive period timer.
    float periodTimer_;
    /// New particle emission timer.
    float emissionTimer_;
    /// Active period.
    float activeTime_;
    /// Inactive period.
    float inactiveTime_;
    /// Particles per second minimum.
    float emissionRateMin_;
    /// Particles per second maximum.
    float emissionRateMax_;
    /// Particle time to live minimum.
    float timeToLiveMin_;
    /// Particle time to live maximum.
    float timeToLiveMax_;
    /// Particle velocity minimum.
    float velocityMin_;
    /// Particle velocityy maximum.
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
    /// Currently emitting flag.
    bool emitting_;
    /// Update when invisible flag.
    bool updateInvisible_;
    /// Last scene timestep.
    float lastTimeStep_;
    /// Rendering framenumber on which was last updated.
    unsigned lastUpdateFrameNumber_;
};

}
