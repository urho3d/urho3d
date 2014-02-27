//
// Copyright (c) 2008-2014 the Urho3D project.
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

#include "Resource.h"
#include "GraphicsDefs.h"

namespace Urho3D
{

class Sprite2D;

/// 2D particle emitter types.
enum EmitterType2D
{
    EMITTER_TYPE_GRAVITY = 0,
    EMITTER_TYPE_RADIAL
};

/// 2D particle emitter component.
class URHO3D_API ParticleModel2D : public Resource
{
    OBJECT(ParticleModel2D);

public:
    /// Construct.
    ParticleModel2D(Context* context);
    /// Destruct.
    ~ParticleModel2D();
    /// Register object factory. drawable2d must be registered first.
    static void RegisterObject(Context* context);

    /// Load resource. Return true if successful.
    virtual bool Load(Deserializer& source);
    /// Save resource. Return true if successful.
    virtual bool Save(Serializer& dest) const;

    /// Return sprite.
    Sprite2D* GetSprite() const;
    /// Return blend mode.
    BlendMode GetBlendMode() const { return blendMode_; }
    /// Return duration.
    float GetDuration() const { return duration_; }
    /// Return emitter type.
    EmitterType2D GetEmitterType() const { return emitterType_; }
    /// Return source position variance.
    const Vector2& GetSourcePositionVariance() const { return sourcePositionVariance_; }
    /// Return max particles.
    int GetMaxParticles() const { return maxParticles_; }
    /// Return particle lifespan
    float GetParticleLifeSpan() const { return particleLifeSpan_; }
    /// Return particle lifespan variance.
    float GetParticleLifeSpanVariance() const { return particleLifeSpanVariance_; }
    /// Return start particle size.
    float GetStartParticleSize() const { return startParticleSize_; }
    /// Return start particle size variance.
    float GetStartParticleSizeVariance() const { return startParticleSizeVariance_; }
    /// Return end particle size.
    float GetEndParticleSize() const { return endParticleSize_; }
    /// Return end particle size variance.
    float GetEndParticleSizeVariance() const { return endParticleSizeVariance_; }
    /// Return angle.
    float GetEmitAngle() const { return emitAngle_; }
    /// Return angle variance.
    float GetEmitAngleVariance() const { return emitAngleVariance_; }
    /// Return speed.
    float GetSpeed() const { return speed_; }
    /// Return speed variance.
    float GetSpeedVariance() const { return speedVariance_; }
    /// Return gravity.
    const Vector2& GetGravity() const { return gravity_; }
    /// Return radial acceleration.
    float GetRadialAcceleration() const { return radialAcceleration_; }
    /// Return radial acceleration variance.
    float GetRadialAccelerationVariance() const { return radialAccelerationVariance_; }
    /// Return tangential acceleration.
    float GetTangentialAcceleration() const { return tangentialAcceleration_; }
    /// Return tangential acceleration variance.
    float GetTangentialAccelerationVariance() const { return tangentialAccelerationVariance_; }
    /// Return max radius.
    float GetMaxRadius() const { return maxRadius_; }
    /// Return max radius variance.
    float GetMaxRadiusVariance() const { return maxRadiusVariance_; }
    /// Return min radius.
    float GetMinRadius() const { return minRadius_; }
    /// Return rotate per second.
    float GetRotatePerSecond() const { return rotatePerSecond_; }
    /// Return rotate per second variance.
    float GetRotatePerSecondVariance() const { return rotatePerSecondVariance_; }
    /// Return start color.
    const Color& GetStartColor() const { return startColor_; }
    /// Return start color variance.
    const Color& GetStartColorVariance() const { return startColorVariance_; }
    /// Return end color.
    const Color& GetEndColor() const { return endColor_; }
    /// Return end color variance.
    const Color& GetEndColorVariance() const { return endColorVariance_; }

private:
    /// Texture.
    SharedPtr<Sprite2D> sprite_;
    /// Blend mode.
    BlendMode blendMode_;
    /// Duration.
    float duration_;
    /// Emitter type.
    EmitterType2D emitterType_;
    /// Source position variance.
    Vector2 sourcePositionVariance_;
    /// Max particles.
    int maxParticles_;
    /// Particle lifespan
    float particleLifeSpan_;
    /// Particle lifespan variance.
    float particleLifeSpanVariance_;
    /// Start particle size.
    float startParticleSize_;
    /// Start particle size variance.
    float startParticleSizeVariance_;
    /// End particle size.
    float endParticleSize_;
    /// End particle size variance.
    float endParticleSizeVariance_;
    /// Angle.
    float emitAngle_;
    /// Angle variance.
    float emitAngleVariance_;
    /// Speed.
    float speed_;
    /// Speed variance.
    float speedVariance_;
    /// Gravity.
    Vector2 gravity_;
    /// Radial acceleration.
    float radialAcceleration_;
    /// Radial acceleration variance.
    float radialAccelerationVariance_;
    /// Tangential acceleration.
    float tangentialAcceleration_;
    /// Tangential acceleration variance.
    float tangentialAccelerationVariance_;
    /// Max radius.
    float maxRadius_;
    /// Max radius variance.
    float maxRadiusVariance_;
    /// Min radius.
    float minRadius_;
    /// Rotate per second.
    float rotatePerSecond_;
    /// Rotate per second variance.
    float rotatePerSecondVariance_;
    /// Start color.
    Color startColor_;
    /// Start color variance.
    Color startColorVariance_;
    /// End color.
    Color endColor_;
    /// End color variance.
    Color endColorVariance_;
};

}

