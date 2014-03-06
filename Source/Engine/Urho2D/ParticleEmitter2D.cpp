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
#include "ParticleModel2D.h"
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
    lifeTime_(0.0f),
    numParticles_(0),
    emitParticleTime_(0.0f),
    timeBetweenParticles_(1.0f)
{
}

ParticleEmitter2D::~ParticleEmitter2D()
{
}

void ParticleEmitter2D::RegisterObject(Context* context)
{
    context->RegisterFactory<ParticleEmitter2D>(URHO2D_CATEGORY);

    ACCESSOR_ATTRIBUTE(ParticleEmitter2D, VAR_RESOURCEREF, "Particle Model", GetParticleModelAttr, SetParticleModelAttr, ResourceRef, ResourceRef(ParticleModel2D::GetTypeStatic()), AM_DEFAULT);
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

void ParticleEmitter2D::UpdateBatches(const FrameInfo& frame)
{
    // const Matrix3x4& worldTransform = node_->GetWorldTransform();
    distance_ = frame.camera_->GetDistance(GetWorldBoundingBox().Center());

    batches_[0].distance_ = distance_;
    batches_[0].worldTransform_ = &Matrix3x4::IDENTITY;
}

void ParticleEmitter2D::Update(const FrameInfo& frame)
{
    if (!model_)
        return;

    float timeStep = frame.timeStep_;
    float worldScale = GetNode()->GetWorldScale().x_;

    unsigned particleIndex = 0;
    while (particleIndex < numParticles_)
    {
        Particle2D& currentParticle = particles_[particleIndex];
        if (currentParticle.timeToLive_ > timeStep) 
        {
            UpdateParticle(currentParticle, timeStep, worldScale);
            ++particleIndex;
        } 
        else 
        {            
            if (particleIndex != numParticles_ - 1)
                particles_[particleIndex] = particles_[numParticles_ - 1];
            --numParticles_;
        }
    }

    if (lifeTime_< 0.0f || lifeTime_ > 0.0f)
    {
        Vector3 worldPosition = GetNode()->GetWorldPosition();
        float worldAngle = GetNode()->GetWorldRotation().RollAngle();

        emitParticleTime_ += timeStep;        
        while (emitParticleTime_ > 0.0f)
        {
            EmitParticle(worldPosition, worldAngle, worldScale);
            emitParticleTime_ -= timeBetweenParticles_;
        }

        if (lifeTime_ > 0.0f)
            lifeTime_ = Max(0.0f, lifeTime_ - timeStep);
    }

    verticesDirty_ = true;
    OnMarkedDirty(node_);
}

void ParticleEmitter2D::SetModel(ParticleModel2D* model)
{
    if (model == model_)
        return;

    model_ = model;
    MarkNetworkUpdate();

    if (!model_)
        return;

    SetSprite(model_->GetSprite());
    SetBlendMode(model_->GetBlendMode());

    lifeTime_ = model_->GetDuration();

    numParticles_ = Min((int)model_->GetMaxParticles(), (int)numParticles_);    
    particles_.Resize(model_->GetMaxParticles());
    vertices_.Reserve(model_->GetMaxParticles() * 4);

    emitParticleTime_ = 0.0f;
    timeBetweenParticles_ = model_->GetParticleLifeSpan() / model_->GetMaxParticles();
}

ParticleModel2D* ParticleEmitter2D::GetModel() const
{
    return model_;
}

void ParticleEmitter2D::SetParticleModelAttr(ResourceRef value)
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    SetModel(cache->GetResource<ParticleModel2D>(value.name_));
}

Urho3D::ResourceRef ParticleEmitter2D::GetParticleModelAttr() const
{
    return GetResourceRef(model_, ParticleModel2D::GetTypeStatic());
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
    if (verticesDirty_)
    {
        UpdateVertices();

        boundingBox_.Clear();
        for (unsigned i = 0; i < vertices_.Size(); ++i)
            boundingBox_.Merge(vertices_[i].position_);
    }

    worldBoundingBox_ = boundingBox_;
}

void ParticleEmitter2D::UpdateVertices()
{
    if (!verticesDirty_)
        return;

    vertices_.Clear();

    if (!sprite_)
        return;

    Texture2D* texture = sprite_->GetTexture();
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

    for (unsigned i = 0; i < numParticles_; ++i)
    {
        Particle2D& p = particles_[i];

        float c = Cos(p.rotation_);
        float s = Sin(p.rotation_);
        float add = (c + s) * p.size_ * 0.5f;
        float sub = (c - s) * p.size_ * 0.5f;

        vertex0.position_ = Vector3(p.position_.x_ - sub, p.position_.y_ - add, zValue_) * unitPerPixel_;
        vertex1.position_ = Vector3(p.position_.x_ - add, p.position_.y_ + sub, zValue_) * unitPerPixel_;
        vertex2.position_ = Vector3(p.position_.x_ + sub, p.position_.y_ + add, zValue_) * unitPerPixel_;
        vertex3.position_ = Vector3(p.position_.x_ + add, p.position_.y_ - sub, zValue_) * unitPerPixel_;

        vertex0.color_ = vertex1.color_ = vertex2.color_  = vertex3.color_ = p.color_.ToUInt();

        vertices_.Push(vertex0);
        vertices_.Push(vertex1);
        vertices_.Push(vertex2);
        vertices_.Push(vertex3);
    }

    geometryDirty_ = true;
    verticesDirty_ = false;
}

void ParticleEmitter2D::HandleScenePostUpdate(StringHash eventType, VariantMap& eventData)
{
    MarkForUpdate();
}

void ParticleEmitter2D::EmitParticle(const Vector3& worldPosition, float worldAngle, float worldScale)
{
    if (numParticles_ >= model_->GetMaxParticles())
        return;

    float lifespan = model_->GetParticleLifeSpan() + model_->GetParticleLifeSpanVariance() * Random(-1.0f, 1.0f);
    if (lifespan <= 0.0f) 
        return;

    float invLifespan = 1.0f / lifespan;

    Particle2D& particle = particles_[numParticles_++];    
    particle.timeToLive_ = lifespan;
    particle.startPos_.x_ = worldPosition.x_;
    particle.startPos_.y_ = worldPosition.y_;
    particle.position_.x_ = worldPosition.x_ + model_->GetSourcePositionVariance().x_ * Random(-1.0f, 1.0f);
    particle.position_.y_ = worldPosition.y_ + model_->GetSourcePositionVariance().y_ * Random(-1.0f, 1.0f);

    float angle = worldAngle + model_->GetEmitAngle() + model_->GetEmitAngleVariance() * Random(-1.0f, 1.0f);
    float speed = worldScale * (model_->GetSpeed() + model_->GetSpeedVariance() * Random(-1.0f, 1.0f));
    particle.velocity_.x_ = speed * Cos(angle);
    particle.velocity_.y_ = speed * Sin(angle);

    particle.radius_ = worldScale * (model_->GetMaxRadius() + model_->GetMaxRadiusVariance() * Random(-1.0f, 1.0f));
    particle.radiusDelta_ = worldScale * (model_->GetMaxRadius() * invLifespan);

    particle.rotation_ = worldAngle + model_->GetEmitAngle() + model_->GetEmitAngleVariance() * Random(-1.0f, 1.0f);
    particle.rotationDelta_ = model_->GetRotatePerSecond() + model_->GetRotatePerSecondVariance() * Random(-1.0f, 1.0f);

    particle.radialAccel_ = worldScale * (model_->GetRadialAcceleration() + model_->GetRadialAccelerationVariance() * Random(-1.0f, 1.0f));
    particle.tangentialAccel_ = worldScale * (model_->GetTangentialAcceleration() + model_->GetTangentialAccelerationVariance() * Random(-1.0f, 1.0f));

    float particleStartSize  = worldScale * Max(0.1f, model_->GetStartParticleSize() + model_->GetStartParticleSizeVariance() * Random(-1.0f, 1.0f));
    float particleFinishSize = worldScale * Max(0.1f, model_->GetEndParticleSize() + model_->GetEndParticleSizeVariance() * Random(-1.0f, 1.0f)); 
    particle.size_ = particleStartSize;
    particle.sizeDelta_ = (particleFinishSize - particleStartSize) * invLifespan;

    Color startColor = model_->GetStartColor() + model_->GetStartColorVariance() * Random(-1.0f, 1.0f);
    Color endColor = model_->GetEndColor() +   model_->GetEndColorVariance() * Random(-1.0f, 1.0f);

    Color colorDelta;
    colorDelta.r_ = (endColor.r_ - startColor.r_) * invLifespan;
    colorDelta.g_ = (endColor.g_ - startColor.g_) * invLifespan;
    colorDelta.b_ = (endColor.b_ - startColor.b_) * invLifespan;
    colorDelta.a_ = (endColor.a_ - startColor.a_) * invLifespan;

    particle.color_ = startColor;
    particle.colorDelta_ = colorDelta;
}

void ParticleEmitter2D::UpdateParticle(Particle2D& particle, float timeStep, float worldScale)
{
    timeStep = Min(timeStep, particle.timeToLive_);
    particle.timeToLive_ -= timeStep;

    if (model_->GetEmitterType() == EMITTER_TYPE_RADIAL) 
    {
        particle.rotation_ += particle.rotationDelta_ * timeStep;
        particle.radius_   -= particle.radiusDelta_   * timeStep;

        Vector3 worldPosition = GetNode()->GetWorldPosition();
        particle.position_.x_ = worldPosition.x_ - cosf(particle.rotation_) * particle.radius_;
        particle.position_.y_ = worldPosition.y_ - sinf(particle.rotation_) * particle.radius_;

        if (particle.radius_ < model_->GetMinRadius() * worldScale)
            particle.timeToLive_ = 0.0f;                
    } 
    else 
    {
        float distanceX = particle.position_.x_ - particle.startPos_.x_;
        float distanceY = particle.position_.y_ - particle.startPos_.y_;
        float distanceScalar = Max(0.01f, sqrtf(distanceX * distanceX + distanceY * distanceY));

        float radialX = distanceX / distanceScalar;
        float radialY = distanceY / distanceScalar;
        float tangentialX = radialX;
        float tangentialY = radialY;

        radialX *= particle.radialAccel_;
        radialY *= particle.radialAccel_;

        float newY = tangentialX;
        tangentialX = -tangentialY * particle.tangentialAccel_;
        tangentialY = newY * particle.tangentialAccel_;

        particle.velocity_.x_ += timeStep * (model_->GetGravity().x_ + radialX + tangentialX);
        particle.velocity_.y_ += timeStep * (model_->GetGravity().y_ + radialY + tangentialY);
        particle.position_.x_ += particle.velocity_.x_ * timeStep;
        particle.position_.y_ += particle.velocity_.y_ * timeStep;
    }

    particle.size_ += particle.sizeDelta_ * timeStep;

    particle.color_.r_ += particle.colorDelta_.r_ * timeStep;
    particle.color_.g_ += particle.colorDelta_.g_ * timeStep;
    particle.color_.b_ += particle.colorDelta_.b_ * timeStep;
    particle.color_.a_ += particle.colorDelta_.a_ * timeStep;
}

}
