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

#include "Precompiled.h"
#include "Camera.h"
#include "Context.h"
#include "ParticleEffect2D.h"
#include "ParticleEmitter2D.h"
#include "ResourceCache.h"
#include "Scene.h"
#include "SceneEvents.h"

#include "DebugNew.h"

namespace Urho3D
{

extern const char* URHO2D_CATEGORY;

ParticleEmitter2D::ParticleEmitter2D(Context* context) :
    Drawable2D(context),
    numParticles_(0), 
    emissionTime_(0.0f),
    emissionRate_(1.0f),
    emitParticleTime_(0.0f),
    boundingBoxMinPoint_(Vector3::ZERO),
    boundingBoxMaxPoint_(Vector3::ZERO)
{
}

ParticleEmitter2D::~ParticleEmitter2D()
{
}

void ParticleEmitter2D::RegisterObject(Context* context)
{
    context->RegisterFactory<ParticleEmitter2D>(URHO2D_CATEGORY);

    ACCESSOR_ATTRIBUTE(ParticleEmitter2D, VAR_RESOURCEREF, "Particle Effect", GetParticleEffectAttr, SetParticleEffectAttr, ResourceRef, ResourceRef(ParticleEffect2D::GetTypeStatic()), AM_DEFAULT);
    COPY_BASE_ATTRIBUTES(ParticleEmitter2D, Drawable2D);
}

void ParticleEmitter2D::OnSetEnabled()
{
    Drawable2D::OnSetEnabled();

    Scene* scene = GetScene();
    if (scene)
    {
        if (IsEnabledEffective())
            SubscribeToEvent(scene, E_SCENEPOSTUPDATE, HANDLER(ParticleEmitter2D, HandleScenePostUpdate));
        else
            UnsubscribeFromEvent(scene, E_SCENEPOSTUPDATE);
    }
}

void ParticleEmitter2D::Update(const FrameInfo& frame)
{
    if (!effect_)
        return;

    float timeStep = frame.timeStep_;
    Vector3 worldPosition = GetNode()->GetWorldPosition();
    float worldScale = GetNode()->GetWorldScale().x_ * PIXEL_SIZE;

    boundingBoxMinPoint_ = Vector3(M_INFINITY, M_INFINITY, 0.0f);
    boundingBoxMaxPoint_ = Vector3(-M_INFINITY, -M_INFINITY, 0.0f);

    int particleIndex = 0;
    while (particleIndex < numParticles_)
    {
        Particle2D& particle = particles_[particleIndex];
        if (particle.timeToLive_ > 0.0f)
        {
            UpdateParticle(particle, timeStep, worldPosition, worldScale);
            ++particleIndex;
        }
        else
        {
            if (particleIndex != numParticles_ - 1)
                particles_[particleIndex] = particles_[numParticles_ - 1];
            --numParticles_;
        }
    }

    if (emissionTime_ >= 0.0f)
    {
        float worldAngle = GetNode()->GetWorldRotation().RollAngle();
        
        float timeBetweenParticles = 1.0f / emissionRate_;
        emitParticleTime_ += timeStep;

        while (emitParticleTime_ > 0)
        {
            if (EmitParticle(worldPosition, worldAngle, worldScale))
                UpdateParticle(particles_[numParticles_ - 1], timeStep, worldPosition, worldScale);

            emitParticleTime_ -= timeBetweenParticles;
        }

        if (emissionTime_ > 0.0f)
            emissionTime_ = Max(0.0f, emissionTime_ - timeStep);
    }

    verticesDirty_ = true;
    OnMarkedDirty(node_);
   
}

void ParticleEmitter2D::SetEffect(ParticleEffect2D* model)
{
    if (model == effect_)
        return;

    effect_ = model;
    MarkNetworkUpdate();

    if (!effect_)
        return;

    SetSprite(effect_->GetSprite());
    SetBlendMode(effect_->GetBlendMode());

    numParticles_ = Min((int)effect_->GetMaxParticles(), (int)numParticles_);    
    particles_.Resize(effect_->GetMaxParticles());
    vertices_.Reserve(effect_->GetMaxParticles() * 4);
    
    emitParticleTime_ = 0.0f;
    emissionTime_ = effect_->GetDuration();
    emissionRate_ = effect_->GetMaxParticles() / Max(0.01f, effect_->GetParticleLifeSpan());
}

ParticleEffect2D* ParticleEmitter2D::GetEffect() const
{
    return effect_;
}

void ParticleEmitter2D::SetParticleEffectAttr(ResourceRef value)
{
    materialUpdatePending_ = true;
    
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    SetEffect(cache->GetResource<ParticleEffect2D>(value.name_));
}

Urho3D::ResourceRef ParticleEmitter2D::GetParticleEffectAttr() const
{
    return GetResourceRef(effect_, ParticleEffect2D::GetTypeStatic());
}

void ParticleEmitter2D::OnNodeSet(Node* node)
{
    Drawable2D::OnNodeSet(node);

    if (node)
    {
        Scene* scene = GetScene();
        if (scene && IsEnabledEffective())
            SubscribeToEvent(scene, E_SCENEPOSTUPDATE, HANDLER(ParticleEmitter2D, HandleScenePostUpdate));
    }
}

void ParticleEmitter2D::OnWorldBoundingBoxUpdate()
{
    boundingBox_.Clear();

    boundingBox_.Merge(boundingBoxMinPoint_);
    boundingBox_.Merge(boundingBoxMaxPoint_);

    worldBoundingBox_ = boundingBox_;
}

void ParticleEmitter2D::UpdateVertices()
{
    if (!verticesDirty_)
        return;

    vertices_.Clear();

    Texture2D* texture = GetTexture();
    if (!texture)
        return;

    const IntRect& rectangle_ = sprite_->GetRectangle();
    if (rectangle_.Width() == 0 || rectangle_.Height() == 0)
        return;

    Vertex2D vertex0;
    Vertex2D vertex1;
    Vertex2D vertex2;
    Vertex2D vertex3;

    vertex0.uv_ = Vector2(0.0f, 1.0f);
    vertex1.uv_ = Vector2(0.0f, 0.0f);
    vertex2.uv_ = Vector2(1.0f, 0.0f);
    vertex3.uv_ = Vector2(1.0f, 1.0f);

    for (int i = 0; i < numParticles_; ++i)
    {
        Particle2D& p = particles_[i];
        
        float rotation = -p.rotation_;
        float c = Cos(rotation);
        float s = Sin(rotation);
        float add = (c + s) * p.size_ * 0.5f;
        float sub = (c - s) * p.size_ * 0.5f;

        vertex0.position_ = Vector3(p.position_.x_ - sub, p.position_.y_ - add, 0.0f);
        vertex1.position_ = Vector3(p.position_.x_ - add, p.position_.y_ + sub, 0.0f);
        vertex2.position_ = Vector3(p.position_.x_ + sub, p.position_.y_ + add, 0.0f);
        vertex3.position_ = Vector3(p.position_.x_ + add, p.position_.y_ - sub, 0.0f);
        
        vertex0.color_ = vertex1.color_ = vertex2.color_  = vertex3.color_ = p.color_.ToUInt();

        vertices_.Push(vertex0);
        vertices_.Push(vertex1);
        vertices_.Push(vertex2);
        vertices_.Push(vertex3);
    }

    verticesDirty_ = false;
}

void ParticleEmitter2D::HandleScenePostUpdate(StringHash eventType, VariantMap& eventData)
{
    MarkForUpdate();
}

bool ParticleEmitter2D::EmitParticle(const Vector3& worldPosition, float worldAngle, float worldScale)
{
    if (numParticles_ >= effect_->GetMaxParticles())
        return false;

    float lifespan = effect_->GetParticleLifeSpan() + effect_->GetParticleLifespanVariance() * Random(-1.0f, 1.0f);
    if (lifespan <= 0.0f)
        return false;

    float invLifespan = 1.0f / lifespan;

    Particle2D& particle = particles_[numParticles_++];
    particle.timeToLive_ = lifespan;

    particle.position_.x_ = worldPosition.x_ + worldScale * effect_->GetSourcePositionVariance().x_ * Random(-1.0f, 1.0f);
    particle.position_.y_ = worldPosition.y_ + worldScale * effect_->GetSourcePositionVariance().y_ * Random(-1.0f, 1.0f);
    particle.startPos_.x_ = worldPosition.x_;
    particle.startPos_.y_ = worldPosition.y_;

    float angle = worldAngle + effect_->GetAngle() + effect_->GetAngleVariance() * Random(-1.0f, 1.0f);
    float speed = worldScale * (effect_->GetSpeed() + effect_->GetSpeedVariance() * Random(-1.0f, 1.0f));
    particle.velocity_.x_ = speed * Cos(angle);
    particle.velocity_.y_ = speed * Sin(angle);

    particle.emitRadius_ = worldScale * (effect_->GetMaxRadius() + effect_->GetMaxRadiusVariance() * Random(-1.0f, 1.0f));
    particle.emitRadiusDelta_ = worldScale * (effect_->GetMinRadius() - effect_->GetMaxRadius()) * invLifespan;
    particle.emitRotation_ = worldAngle + effect_->GetAngle() + effect_->GetAngleVariance() * Random(-1.0f, 1.0f);
    particle.emitRotationDelta_ = effect_->GetRotatePerSecond() + effect_->GetRotatePerSecondVariance() * Random(-1.0f, 1.0f);
    particle.radialAcceleration_ = worldScale * (effect_->GetRadialAcceleration() + effect_->GetRadialAccelVariance() * Random(-1.0f, 1.0f));
    particle.tangentialAcceleration_ = worldScale * (effect_->GetTangentialAcceleration() + effect_->GetTangentialAccelVariance() * Random(-1.0f, 1.0f));

    float startSize = worldScale * Max(0.1f, effect_->GetStartParticleSize() + effect_->GetStartParticleSizeVariance() * Random(-1.0f, 1.0f));
    float finishSize = worldScale * Max(0.1f, effect_->GetFinishParticleSize() + effect_->GetFinishParticleSizeVariance() * Random(-1.0f, 1.0f));
    particle.size_ = startSize;
    particle.sizeDelta_ = (finishSize - startSize) * invLifespan;

    particle.color_ = effect_->GetStartColor() + effect_->GetStartColorVariance() * Random(-1.0f, 1.0f);
    Color endColor = effect_->GetFinishColor() + effect_->GetFinishColorVariance() * Random(-1.0f, 1.0f);
    particle.colorDelta_= (endColor - particle.color_) * invLifespan;

    particle.rotation_ = worldAngle + effect_->GetRotationStart() + effect_->GetRotationStartVariance() * Random(-1.0f, 1.0f);
    float endRotation = worldAngle + effect_->GetRotationEnd() + effect_->GetRotationEndVariance() * Random(-1.0f, 1.0f);
    particle.rotationDelta_ = (endRotation - particle.rotation_) * invLifespan;

    return true;
}

void ParticleEmitter2D::UpdateParticle(Particle2D& particle, float timeStep, const Vector3& worldPosition, float worldScale)
{
    if (timeStep > particle.timeToLive_)
        timeStep = particle.timeToLive_;
    
    particle.timeToLive_ -= timeStep;

    if (effect_->GetEmitterType() == EMITTER_TYPE_RADIAL)
    {
        particle.emitRotation_ += particle.emitRotationDelta_ * timeStep;
        particle.emitRadius_ += particle.emitRadiusDelta_ * timeStep;

        particle.position_.x_ = worldPosition.x_ - Cos(particle.emitRotation_) * particle.emitRadius_;
        particle.position_.y_ = worldPosition.y_ + Sin(particle.emitRotation_) * particle.emitRadius_;

        if (particle.emitRadius_ < effect_->GetMinRadius() * worldScale)
            particle.timeToLive_ = 0.0f;
    }
    else
    {
        float distanceX = particle.position_.x_ - particle.startPos_.x_;
        float distanceY = particle.position_.y_ - particle.startPos_.y_;
        
        float distanceScalar = Vector2(distanceX, distanceY).Length();
        if (distanceScalar < 0.0001f)
            distanceScalar = 0.0001f;

        float radialX = distanceX / distanceScalar;
        float radialY = distanceY / distanceScalar;

        float tangentialX = radialX;
        float tangentialY = radialY;

        radialX *= particle.radialAcceleration_;
        radialY *= particle.radialAcceleration_;

        float newY = tangentialX;
        tangentialX = -tangentialY * particle.tangentialAcceleration_;
        tangentialY = newY * particle.tangentialAcceleration_;

        particle.velocity_.x_ += (effect_->GetGravity().x_ * worldScale + radialX - tangentialX) * timeStep;
        particle.velocity_.y_ -= (effect_->GetGravity().y_ * worldScale - radialY + tangentialY) * timeStep;
        particle.position_.x_ += particle.velocity_.x_ * timeStep;
        particle.position_.y_ += particle.velocity_.y_ * timeStep;
    }

    particle.size_ += particle.sizeDelta_ * timeStep;
    particle.rotation_ += particle.rotationDelta_ * timeStep;
    particle.color_ += particle.colorDelta_ * timeStep;

    float halfSize = particle.size_ * 0.5f;
    boundingBoxMinPoint_.x_ = Min(boundingBoxMinPoint_.x_, particle.position_.x_ - halfSize);
    boundingBoxMinPoint_.y_ = Min(boundingBoxMinPoint_.y_, particle.position_.y_ - halfSize);
    boundingBoxMaxPoint_.x_ = Max(boundingBoxMaxPoint_.x_, particle.position_.x_ + halfSize);
    boundingBoxMaxPoint_.y_ = Max(boundingBoxMaxPoint_.y_, particle.position_.y_ + halfSize);
}

}
