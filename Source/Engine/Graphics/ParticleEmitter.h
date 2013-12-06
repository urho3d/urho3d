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

/// Particle emitter shapes.
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
    /// Current color animation index.
    unsigned colorIndex_;
    /// Current texture animation index.
    unsigned texIndex_;
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
    Color Interpolate(const ColorFrame& next, float time)
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

class XMLFile;
class XMLElement;

/// %Particle emitter component.
class URHO3D_API ParticleEmitter : public BillboardSet
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
    /// Update before octree reinsertion. Is called from a worker thread.
    virtual void Update(const FrameInfo& frame);
    
    /// Load emitter parameters from an XML file.
    bool Load(XMLFile* file);
    /// Save particle emitter parameters to an XML file. Return true if successful.
    bool Save(XMLFile* file) const;
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
    /// Set whether to update when particles are not visible.
    void SetUpdateInvisible(bool enable);
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
    void SetColor(const Color& color);
    /// Set color animation of particles.
    void SetColors(const Vector<ColorFrame>& colors);
    /// Set number of color animation frames.
    void SetNumColors(unsigned num);
    /// Set particle texture animation.
    void SetTextureFrames(const Vector<TextureFrame>& animation);
    /// Set number of texture animation frames.
    void SetNumTextureFrames(unsigned num);
    
    /// Return maximum number of particles.
    unsigned GetNumParticles() const { return particles_.Size(); }
    /// Return whether is currently emitting.
    bool IsEmitting() const { return emitting_; }
    /// Return whether to update when particles are not visible.
    bool GetUpdateInvisible() const { return updateInvisible_; }
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
    /// Return all color animation frames.
    Vector<ColorFrame>& GetColors() { return colorFrames_; }
    /// Return number of color animation frames.
    unsigned GetNumColors() const { return colorFrames_.Size(); }
    /// Return a color animation frame, or null if outside range.
    ColorFrame* GetColor(unsigned index) { return index < colorFrames_.Size() ? &colorFrames_[index] : (ColorFrame*)0; }
    /// Return all texture animation frames.
    Vector<TextureFrame>& GetTextureFrame() { return textureFrames_; }
    /// Return number of texture animation frames.
    unsigned GetNumTextureFrames() const { return textureFrames_.Size(); }
    /// Return a texture animation frame, or null if outside range.
    TextureFrame* GetTextureFrame(unsigned index) { return index < colorFrames_.Size() ? &textureFrames_[index] : (TextureFrame*)0; }
    
    /// Set particles attribute.
    void SetParticlesAttr(VariantVector value);
    /// Return particles attribute.
    VariantVector GetParticlesAttr() const;
    /// Set particle colors attribute.
    void SetColorsAttr(VariantVector value);
    /// Return particle colors attribute.
    VariantVector GetColorsAttr() const;
    /// Set texture animation attribute.
    void SetTextureFramesAttr(VariantVector value);
    /// Return texture animation attribute.
    VariantVector GetTextureFramesAttr() const;
    
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
    /// Particle color animation frames.
    Vector<ColorFrame> colorFrames_;
    /// Texture animation frames.
    Vector<TextureFrame> textureFrames_;
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
    /// Last scene timestep.
    float lastTimeStep_;
    /// Rendering framenumber on which was last updated.
    unsigned lastUpdateFrameNumber_;
    /// Currently emitting flag.
    bool emitting_;
    /// Update when invisible flag.
    bool updateInvisible_;
    /// Need update flag.
    bool needUpdate_;
};

}
