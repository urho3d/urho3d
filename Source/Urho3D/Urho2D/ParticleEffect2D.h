//
// Copyright (c) 2008-2016 the Urho3D project.
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

#include "../Graphics/GraphicsDefs.h"
#include "../Resource/Resource.h"

namespace Urho3D
{

class XMLElement;
class Sprite2D;

/// 2D particle emitter types.
enum EmitterType2D
{
    EMITTER_TYPE_GRAVITY = 0,
    EMITTER_TYPE_RADIAL
};

/// 2D particle effect resource.
class URHO3D_API ParticleEffect2D : public Resource
{
    URHO3D_OBJECT(ParticleEffect2D, Resource);

public:
    /// Construct.
    ParticleEffect2D(Context* context);
    /// Destruct.
    ~ParticleEffect2D();
    /// Register object factory. Drawable2D must be registered first.
    static void RegisterObject(Context* context);

    /// Load resource from stream. May be called from a worker thread. Return true if successful.
    virtual bool BeginLoad(Deserializer& source);
    /// Finish resource loading. Always called from the main thread. Return true if successful.
    virtual bool EndLoad();
    /// Save resource. Return true if successful.
    virtual bool Save(Serializer& dest) const;

    /// Set sprite.
    void SetSprite(Sprite2D* sprite);
    /// Set source position variance.
    void SetSourcePositionVariance(const Vector2& sourcePositionVariance);
    /// Set speed.
    void SetSpeed(float speed);
    /// Set speed variance.
    void SetSpeedVariance(float speedVariance);
    /// Set particle lifespan.
    void SetParticleLifeSpan(float particleLifeSpan);
    /// Set particle lifespan variance.
    void SetParticleLifespanVariance(float particleLifespanVariance);
    /// Set angle.
    void SetAngle(float angle);
    /// Set angle variance.
    void SetAngleVariance(float angleVariance);
    /// Set gravity.
    void SetGravity(const Vector2& gravity);
    /// Set radial acceleration.
    void SetRadialAcceleration(float radialAcceleration);
    /// Set tangential acceleration.
    void SetTangentialAcceleration(float tangentialAcceleration);
    /// Set radial acceleration variance.
    void SetRadialAccelVariance(float radialAccelVariance);
    /// Set tangential acceleration variance.
    void SetTangentialAccelVariance(float tangentialAccelVariance);
    /// Set start color.
    void SetStartColor(const Color& startColor);
    /// Set start color variance.
    void SetStartColorVariance(const Color& startColorVariance);
    /// Set finish color.
    void SetFinishColor(const Color& finishColor);
    /// Set finish color variance.
    void SetFinishColorVariance(const Color& finishColorVariance);
    /// Set max particles.
    void SetMaxParticles(int maxParticles);
    /// Set start particle size.
    void SetStartParticleSize(float startParticleSize);
    /// Set start particle size variance.
    void SetStartParticleSizeVariance(float startParticleSizeVariance);
    /// Set finish particle size.
    void SetFinishParticleSize(float finishParticleSize);
    /// Set finish particle size variance.
    void SetFinishParticleSizeVariance(float FinishParticleSizeVariance);
    /// Set duration.
    void SetDuration(float duration);
    /// Set emitter type.
    void SetEmitterType(EmitterType2D emitterType);
    /// Set max radius.
    void SetMaxRadius(float maxRadius);
    /// Set max radius variance.
    void SetMaxRadiusVariance(float maxRadiusVariance);
    /// Set min radius.
    void SetMinRadius(float minRadius);
    /// Set min radius variance.
    void SetMinRadiusVariance(float minRadiusVariance);
    /// Set rotate per second.
    void SetRotatePerSecond(float rotatePerSecond);
    /// Set rotate per second variance.
    void SetRotatePerSecondVariance(float rotatePerSecondVariance);
    /// Set blend mode.
    void SetBlendMode(BlendMode blendMode);
    /// Set rotation start.
    void SetRotationStart(float rotationStart);
    /// Set rotation start variance.
    void SetRotationStartVariance(float rotationStartVariance);
    /// Set rotation end.
    void SetRotationEnd(float rotationEnd);
    /// Set rotation end variance.
    void SetRotationEndVariance(float rotationEndVariance);

    /// Return sprite.
    Sprite2D* GetSprite() const { return sprite_; }

    /// Return source position variance.
    const Vector2& GetSourcePositionVariance() const { return sourcePositionVariance_; }

    /// Return speed.
    float GetSpeed() const { return speed_; }

    /// Return speed variance.
    float GetSpeedVariance() const { return speedVariance_; }

    /// Return particle lifespan.
    float GetParticleLifeSpan() const { return particleLifeSpan_; }

    /// Return particle lifespan variance.
    float GetParticleLifespanVariance() const { return particleLifespanVariance_; }

    /// Return angle.
    float GetAngle() const { return angle_; }

    /// Return angle variance.
    float GetAngleVariance() const { return angleVariance_; }

    /// Return gravity.
    const Vector2& GetGravity() const { return gravity_; }

    /// Return radial acceleration.
    float GetRadialAcceleration() const { return radialAcceleration_; }

    /// Return tangential acceleration.
    float GetTangentialAcceleration() const { return tangentialAcceleration_; }

    /// Return radial acceleration variance.
    float GetRadialAccelVariance() const { return radialAccelVariance_; }

    /// Return tangential acceleration variance.
    float GetTangentialAccelVariance() const { return tangentialAccelVariance_; }

    /// Return start color.
    const Color& GetStartColor() const { return startColor_; }

    /// Return start color variance.
    const Color& GetStartColorVariance() const { return startColorVariance_; }

    /// Return finish color.
    const Color& GetFinishColor() const { return finishColor_; }

    /// Return finish color variance.
    const Color& GetFinishColorVariance() const { return finishColorVariance_; }

    /// Return max particles.
    int GetMaxParticles() const { return maxParticles_; }

    /// Return start particle size.
    float GetStartParticleSize() const { return startParticleSize_; }

    /// Return start particle size variance.
    float GetStartParticleSizeVariance() const { return startParticleSizeVariance_; }

    /// Return finish particle size.
    float GetFinishParticleSize() const { return finishParticleSize_; }

    /// Return finish particle size variance.
    float GetFinishParticleSizeVariance() const { return FinishParticleSizeVariance_; }

    /// Return duration.
    float GetDuration() const { return duration_; }

    /// Return emitter type.
    EmitterType2D GetEmitterType() const { return emitterType_; }

    /// Return max radius.
    float GetMaxRadius() const { return maxRadius_; }

    /// Return max radius variance.
    float GetMaxRadiusVariance() const { return maxRadiusVariance_; }

    /// Return min radius.
    float GetMinRadius() const { return minRadius_; }

    /// Return min radius variance.
    float GetMinRadiusVariance() const { return minRadiusVariance_; }

    /// Return rotate per second.
    float GetRotatePerSecond() const { return rotatePerSecond_; }

    /// Return rotate per second variance.
    float GetRotatePerSecondVariance() const { return rotatePerSecondVariance_; }

    /// Return blend mode.
    BlendMode GetBlendMode() const { return blendMode_; }

    /// Return rotation start.
    float GetRotationStart() const { return rotationStart_; }

    /// Return rotation start variance.
    float GetRotationStartVariance() const { return rotationStartVariance_; }

    /// Return rotation end.
    float GetRotationEnd() const { return rotationEnd_; }

    /// Return rotation end variance.
    float GetRotationEndVariance() const { return rotationEndVariance_; }

private:
    /// Read integer.
    int ReadInt(const XMLElement& element, const String& name) const;
    /// Read float.
    float ReadFloat(const XMLElement& element, const String& name) const;
    /// Read Color.
    Color ReadColor(const XMLElement& element, const String& name) const;
    /// Read Vector2.
    Vector2 ReadVector2(const XMLElement& element, const String& name) const;
    /// Write integer.
    void WriteInt(XMLElement& element, const String& name, int value) const;
    /// Write float.
    void WriteFloat(XMLElement& element, const String& name, float value) const;
    /// Write Color.
    void WriteColor(XMLElement& element, const String& name, const Color& color) const;
    /// Write Vector2.
    void WriteVector2(XMLElement& element, const String& name, const Vector2& value) const;

    /// Sprite.
    SharedPtr<Sprite2D> sprite_;
    /// Source position variance.
    Vector2 sourcePositionVariance_;
    /// Speed.
    float speed_;
    /// Speed variance.
    float speedVariance_;
    /// Particle lifespan.
    float particleLifeSpan_;
    /// Particle lifespan variance.
    float particleLifespanVariance_;
    /// Angle.
    float angle_;
    /// Angle variance.
    float angleVariance_;
    /// Gravity.
    Vector2 gravity_;
    /// Radial acceleration.
    float radialAcceleration_;
    /// Tangential acceleration.
    float tangentialAcceleration_;
    /// Radial acceleration variance.
    float radialAccelVariance_;
    /// Tangential acceleration variance.
    float tangentialAccelVariance_;
    /// Start color.
    Color startColor_;
    /// Start color variance.
    Color startColorVariance_;
    /// Finish color.
    Color finishColor_;
    /// Finish color variance.
    Color finishColorVariance_;
    /// Max particles.
    int maxParticles_;
    /// Start particle size.
    float startParticleSize_;
    /// Start particle size variance.
    float startParticleSizeVariance_;
    /// Finish particle size.
    float finishParticleSize_;
    /// Finish particle size variance.
    float FinishParticleSizeVariance_;
    /// Duration.
    float duration_;
    /// Emitter type.
    EmitterType2D emitterType_;
    /// Max radius.
    float maxRadius_;
    /// Max radius variance.
    float maxRadiusVariance_;
    /// Min radius.
    float minRadius_;
    /// Min radius variance.
    float minRadiusVariance_;
    /// Rotate per second.
    float rotatePerSecond_;
    /// Rotate per second variance.
    float rotatePerSecondVariance_;
    /// Blend mode.
    BlendMode blendMode_;
    /// Rotation start.
    float rotationStart_;
    /// Rotation start variance.
    float rotationStartVariance_;
    /// Rotation end.
    float rotationEnd_;
    /// Rotation end variance.
    float rotationEndVariance_;
    /// Sprite name acquired during BeginLoad().
    String loadSpriteName_;
};

}
