// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include "../Precompiled.h"

#include "../Core/Context.h"
#include "../Core/Profiler.h"
#include "../Graphics/DrawableEvents.h"
#include "../Graphics/ParticleEffect.h"
#include "../Graphics/ParticleEmitter.h"
#include "../Resource/ResourceCache.h"
#include "../Resource/ResourceEvents.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneEvents.h"

#include "../DebugNew.h"

namespace Urho3D
{

extern const char* GEOMETRY_CATEGORY;
extern const char* faceCameraModeNames[];
static const i32 MAX_PARTICLES_IN_FRAME = 100;

extern const char* autoRemoveModeNames[];

ParticleEmitter::ParticleEmitter(Context* context) :
    BillboardSet(context),
    periodTimer_(0.0f),
    emissionTimer_(0.0f),
    lastTimeStep_(0.0f),
    lastUpdateFrameNumber_(NINDEX),
    emitting_(true),
    needUpdate_(false),
    serializeParticles_(true),
    sendFinishedEvent_(true),
    autoRemove_(REMOVE_DISABLED)
{
    SetNumParticles(DEFAULT_NUM_PARTICLES);
}

ParticleEmitter::~ParticleEmitter() = default;

void ParticleEmitter::RegisterObject(Context* context)
{
    context->RegisterFactory<ParticleEmitter>(GEOMETRY_CATEGORY);

    URHO3D_ACCESSOR_ATTRIBUTE("Is Enabled", IsEnabled, SetEnabled, true, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Effect", GetEffectAttr, SetEffectAttr, ResourceRef(ParticleEffect::GetTypeStatic()),
        AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Can Be Occluded", IsOccludee, SetOccludee, true, AM_DEFAULT);
    URHO3D_ATTRIBUTE("Cast Shadows", castShadows_, false, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Draw Distance", GetDrawDistance, SetDrawDistance, 0.0f, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Shadow Distance", GetShadowDistance, SetShadowDistance, 0.0f, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Animation LOD Bias", GetAnimationLodBias, SetAnimationLodBias, 1.0f, AM_DEFAULT);
    URHO3D_ATTRIBUTE("Is Emitting", emitting_, true, AM_FILE);
    URHO3D_ATTRIBUTE("Period Timer", periodTimer_, 0.0f, AM_FILE | AM_NOEDIT);
    URHO3D_ATTRIBUTE("Emission Timer", emissionTimer_, 0.0f, AM_FILE | AM_NOEDIT);
    URHO3D_ENUM_ATTRIBUTE("Autoremove Mode", autoRemove_, autoRemoveModeNames, REMOVE_DISABLED, AM_DEFAULT);
    URHO3D_COPY_BASE_ATTRIBUTES(Drawable);
    URHO3D_ACCESSOR_ATTRIBUTE("Particles", GetParticlesAttr, SetParticlesAttr, Variant::emptyVariantVector,
        AM_FILE | AM_NOEDIT);
    URHO3D_ACCESSOR_ATTRIBUTE("Billboards", GetParticleBillboardsAttr, SetBillboardsAttr, Variant::emptyVariantVector,
        AM_FILE | AM_NOEDIT);
    URHO3D_ATTRIBUTE("Serialize Particles", serializeParticles_, true, AM_FILE);
}

void ParticleEmitter::OnSetEnabled()
{
    BillboardSet::OnSetEnabled();

    Scene* scene = GetScene();
    if (scene)
    {
        if (IsEnabledEffective())
            SubscribeToEvent(scene, E_SCENEPOSTUPDATE, URHO3D_HANDLER(ParticleEmitter, HandleScenePostUpdate));
        else
            UnsubscribeFromEvent(scene, E_SCENEPOSTUPDATE);
    }
}

void ParticleEmitter::Update(const FrameInfo& frame)
{
    if (!effect_)
        return;

    // Cancel update if has only moved but does not actually need to animate the particles
    if (!needUpdate_)
        return;

    // If there is an amount mismatch between particles and billboards, correct it
    if (particles_.Size() != billboards_.Size())
        SetNumBillboards(particles_.Size());

    bool needCommit = false;

    // Check active/inactive period switching
    periodTimer_ += lastTimeStep_;
    if (emitting_)
    {
        float activeTime = effect_->GetActiveTime();
        if (activeTime && periodTimer_ >= activeTime)
        {
            emitting_ = false;
            periodTimer_ -= activeTime;
        }
    }
    else
    {
        float inactiveTime = effect_->GetInactiveTime();
        if (inactiveTime && periodTimer_ >= inactiveTime)
        {
            emitting_ = true;
            sendFinishedEvent_ = true;
            periodTimer_ -= inactiveTime;
        }
        // If emitter has an indefinite stop interval, keep period timer reset to allow restarting emission in the editor
        if (inactiveTime == 0.0f)
            periodTimer_ = 0.0f;
    }

    // Check for emitting new particles
    if (emitting_)
    {
        emissionTimer_ += lastTimeStep_;

        float intervalMin = 1.0f / effect_->GetMaxEmissionRate();
        float intervalMax = 1.0f / effect_->GetMinEmissionRate();

        // If emission timer has a longer delay than max. interval, clamp it
        if (emissionTimer_ < -intervalMax)
            emissionTimer_ = -intervalMax;

        i32 counter = MAX_PARTICLES_IN_FRAME;

        while (emissionTimer_ > 0.0f && counter)
        {
            emissionTimer_ -= Lerp(intervalMin, intervalMax, Random(1.0f));
            if (EmitNewParticle())
            {
                --counter;
                needCommit = true;
            }
            else
                break;
        }
    }

    // Update existing particles
    Vector3 relativeConstantForce = node_->GetWorldRotation().Inverse() * effect_->GetConstantForce();
    // If billboards are not relative, apply scaling to the position update
    Vector3 scaleVector = Vector3::ONE;
    if (scaled_ && !relative_)
        scaleVector = node_->GetWorldScale();

    for (i32 i = 0; i < particles_.Size(); ++i)
    {
        Particle& particle = particles_[i];
        Billboard& billboard = billboards_[i];

        if (billboard.enabled_)
        {
            needCommit = true;

            // Time to live
            if (particle.timer_ >= particle.timeToLive_)
            {
                billboard.enabled_ = false;
                continue;
            }
            particle.timer_ += lastTimeStep_;

            // Velocity & position
            const Vector3& constantForce = effect_->GetConstantForce();
            if (constantForce != Vector3::ZERO)
            {
                if (relative_)
                    particle.velocity_ += lastTimeStep_ * relativeConstantForce;
                else
                    particle.velocity_ += lastTimeStep_ * constantForce;
            }

            float dampingForce = effect_->GetDampingForce();
            if (dampingForce != 0.0f)
            {
                Vector3 force = -dampingForce * particle.velocity_;
                particle.velocity_ += lastTimeStep_ * force;
            }
            billboard.position_ += lastTimeStep_ * particle.velocity_ * scaleVector;
            billboard.direction_ = particle.velocity_.Normalized();

            // Rotation
            billboard.rotation_ += lastTimeStep_ * particle.rotationSpeed_;

            // Scaling
            float sizeAdd = effect_->GetSizeAdd();
            float sizeMul = effect_->GetSizeMul();
            if (sizeAdd != 0.0f || sizeMul != 1.0f)
            {
                particle.scale_ += lastTimeStep_ * sizeAdd;
                if (particle.scale_ < 0.0f)
                    particle.scale_ = 0.0f;
                if (sizeMul != 1.0f)
                    particle.scale_ *= (lastTimeStep_ * (sizeMul - 1.0f)) + 1.0f;
                billboard.size_ = particle.size_ * particle.scale_;
            }

            // Color interpolation
            i32& index = particle.colorIndex_;
            const Vector<ColorFrame>& colorFrames_ = effect_->GetColorFrames();
            if (index < colorFrames_.Size())
            {
                if (index < colorFrames_.Size() - 1)
                {
                    if (particle.timer_ >= colorFrames_[index + 1].time_)
                        ++index;
                }
                if (index < colorFrames_.Size() - 1)
                    billboard.color_ = colorFrames_[index].Interpolate(colorFrames_[index + 1], particle.timer_);
                else
                    billboard.color_ = colorFrames_[index].color_;
            }

            // Texture animation
            i32& texIndex = particle.texIndex_;
            const Vector<TextureFrame>& textureFrames_ = effect_->GetTextureFrames();
            if (textureFrames_.Size() && texIndex < textureFrames_.Size() - 1)
            {
                if (particle.timer_ >= textureFrames_[texIndex + 1].time_)
                {
                    billboard.uv_ = textureFrames_[texIndex + 1].uv_;
                    ++texIndex;
                }
            }
        }
    }

    if (needCommit)
        Commit();

    needUpdate_ = false;
}

void ParticleEmitter::SetEffect(ParticleEffect* effect)
{
    if (effect == effect_)
        return;

    Reset();

    // Unsubscribe from the reload event of previous effect (if any), then subscribe to the new
    if (effect_)
        UnsubscribeFromEvent(effect_, E_RELOADFINISHED);

    effect_ = effect;

    if (effect_)
        SubscribeToEvent(effect_, E_RELOADFINISHED, URHO3D_HANDLER(ParticleEmitter, HandleEffectReloadFinished));

    ApplyEffect();
    MarkNetworkUpdate();
}

void ParticleEmitter::SetNumParticles(i32 num)
{
    // Prevent negative value being assigned from the editor
    if (num < 0)
        num = 0;

    particles_.Resize(num);
    SetNumBillboards(num);
}

void ParticleEmitter::SetEmitting(bool enable)
{
    if (enable != emitting_)
    {
        emitting_ = enable;

        // If stopping emission now, and there are active particles, send finish event once they are gone
        sendFinishedEvent_ = enable || CheckActiveParticles();
        periodTimer_ = 0.0f;
        // Note: network update does not need to be marked as this is a file only attribute
    }
}

void ParticleEmitter::SetSerializeParticles(bool enable)
{
    serializeParticles_ = enable;
    // Note: network update does not need to be marked as this is a file only attribute
}

void ParticleEmitter::SetAutoRemoveMode(AutoRemoveMode mode)
{
    autoRemove_ = mode;
    MarkNetworkUpdate();
}

void ParticleEmitter::ResetEmissionTimer()
{
    emissionTimer_ = 0.0f;
}

void ParticleEmitter::RemoveAllParticles()
{
    for (Vector<Billboard>::Iterator i = billboards_.Begin(); i != billboards_.End(); ++i)
        i->enabled_ = false;

    Commit();
}

void ParticleEmitter::Reset()
{
    RemoveAllParticles();
    ResetEmissionTimer();
    SetEmitting(true);
}

void ParticleEmitter::ApplyEffect()
{
    if (!effect_)
        return;

    SetMaterial(effect_->GetMaterial());
    SetNumParticles(effect_->GetNumParticles());
    SetRelative(effect_->IsRelative());
    SetScaled(effect_->IsScaled());
    SetSorted(effect_->IsSorted());
    SetFixedScreenSize(effect_->IsFixedScreenSize());
    SetAnimationLodBias(effect_->GetAnimationLodBias());
    SetFaceCameraMode(effect_->GetFaceCameraMode());
}

ParticleEffect* ParticleEmitter::GetEffect() const
{
    return effect_;
}

void ParticleEmitter::SetEffectAttr(const ResourceRef& value)
{
    auto* cache = GetSubsystem<ResourceCache>();
    SetEffect(cache->GetResource<ParticleEffect>(value.name_));
}

ResourceRef ParticleEmitter::GetEffectAttr() const
{
    return GetResourceRef(effect_, ParticleEffect::GetTypeStatic());
}

void ParticleEmitter::SetParticlesAttr(const VariantVector& value)
{
    i32 index = 0;
    SetNumParticles(index < value.Size() ? value[index++].GetU32() : 0);

    for (Vector<Particle>::Iterator i = particles_.Begin(); i != particles_.End() && index < value.Size(); ++i)
    {
        i->velocity_ = value[index++].GetVector3();
        i->size_ = value[index++].GetVector2();
        i->timer_ = value[index++].GetFloat();
        i->timeToLive_ = value[index++].GetFloat();
        i->scale_ = value[index++].GetFloat();
        i->rotationSpeed_ = value[index++].GetFloat();
        i->colorIndex_ = value[index++].GetI32();
        i->texIndex_ = value[index++].GetI32();
    }
}

VariantVector ParticleEmitter::GetParticlesAttr() const
{
    VariantVector ret;
    if (!serializeParticles_)
    {
        ret.Push(particles_.Size());
        return ret;
    }

    ret.Reserve(particles_.Size() * 8 + 1);
    ret.Push(particles_.Size());
    for (Vector<Particle>::ConstIterator i = particles_.Begin(); i != particles_.End(); ++i)
    {
        ret.Push(i->velocity_);
        ret.Push(i->size_);
        ret.Push(i->timer_);
        ret.Push(i->timeToLive_);
        ret.Push(i->scale_);
        ret.Push(i->rotationSpeed_);
        ret.Push(i->colorIndex_);
        ret.Push(i->texIndex_);
    }
    return ret;
}

VariantVector ParticleEmitter::GetParticleBillboardsAttr() const
{
    VariantVector ret;
    if (!serializeParticles_)
    {
        ret.Push(billboards_.Size());
        return ret;
    }

    ret.Reserve(billboards_.Size() * 7 + 1);
    ret.Push(billboards_.Size());

    for (Vector<Billboard>::ConstIterator i = billboards_.Begin(); i != billboards_.End(); ++i)
    {
        ret.Push(i->position_);
        ret.Push(i->size_);
        ret.Push(Vector4(i->uv_.min_.x_, i->uv_.min_.y_, i->uv_.max_.x_, i->uv_.max_.y_));
        ret.Push(i->color_);
        ret.Push(i->rotation_);
        ret.Push(i->direction_);
        ret.Push(i->enabled_);
    }

    return ret;
}

void ParticleEmitter::OnSceneSet(Scene* scene)
{
    BillboardSet::OnSceneSet(scene);

    if (scene && IsEnabledEffective())
        SubscribeToEvent(scene, E_SCENEPOSTUPDATE, URHO3D_HANDLER(ParticleEmitter, HandleScenePostUpdate));
    else if (!scene)
         UnsubscribeFromEvent(E_SCENEPOSTUPDATE);
}

bool ParticleEmitter::EmitNewParticle()
{
    i32 index = GetFreeParticle();
    if (index == NINDEX)
        return false;
    assert(index < particles_.Size());
    Particle& particle = particles_[index];
    Billboard& billboard = billboards_[index];

    Vector3 startDir;
    Vector3 startPos;

    startDir = effect_->GetRandomDirection();
    startDir.Normalize();

    switch (effect_->GetEmitterType())
    {
    case EMITTER_SPHERE:
        {
            Vector3 dir(
                Random(2.0f) - 1.0f,
                Random(2.0f) - 1.0f,
                Random(2.0f) - 1.0f
            );
            dir.Normalize();
            startPos = effect_->GetEmitterSize() * dir * 0.5f;
        }
        break;

    case EMITTER_BOX:
        {
            const Vector3& emitterSize = effect_->GetEmitterSize();
            startPos = Vector3(
                Random(emitterSize.x_) - emitterSize.x_ * 0.5f,
                Random(emitterSize.y_) - emitterSize.y_ * 0.5f,
                Random(emitterSize.z_) - emitterSize.z_ * 0.5f
            );
        }
        break;

    case EMITTER_SPHEREVOLUME:
        {
            Vector3 dir(
                Random(2.0f) - 1.0f,
                Random(2.0f) - 1.0f,
                Random(2.0f) - 1.0f
            );
            dir.Normalize();
            startPos = effect_->GetEmitterSize() * dir * Pow(Random(), 1.0f / 3.0f) * 0.5f;
        }
        break;

    case EMITTER_CYLINDER:
        {
            float angle = Random(360.0f);
            float radius = Sqrt(Random()) * 0.5f;
            startPos = Vector3(Cos(angle) * radius, Random() - 0.5f, Sin(angle) * radius) * effect_->GetEmitterSize();
        }
        break;

    case EMITTER_RING:
        {
            float angle = Random(360.0f);
            startPos = Vector3(Cos(angle), Random(2.0f) - 1.0f, Sin(angle)) * effect_->GetEmitterSize() * 0.5f;
        }
        break;
    }

    particle.size_ = effect_->GetRandomSize();
    particle.timer_ = 0.0f;
    particle.timeToLive_ = effect_->GetRandomTimeToLive();
    particle.scale_ = 1.0f;
    particle.rotationSpeed_ = effect_->GetRandomRotationSpeed();
    particle.colorIndex_ = 0;
    particle.texIndex_ = 0;

    if (faceCameraMode_ == FC_DIRECTION)
    {
        startPos += startDir * particle.size_.y_;
    }

    if (!relative_)
    {
        startPos = node_->GetWorldTransform() * startPos;
        startDir = node_->GetWorldRotation() * startDir;
    };

    particle.velocity_ = effect_->GetRandomVelocity() * startDir;

    billboard.position_ = startPos;
    billboard.size_ = particles_[index].size_;
    const Vector<TextureFrame>& textureFrames_ = effect_->GetTextureFrames();
    billboard.uv_ = textureFrames_.Size() ? textureFrames_[0].uv_ : Rect::POSITIVE;
    billboard.rotation_ = effect_->GetRandomRotation();
    const Vector<ColorFrame>& colorFrames_ = effect_->GetColorFrames();
    billboard.color_ = colorFrames_.Size() ? colorFrames_[0].color_ : Color();
    billboard.enabled_ = true;
    billboard.direction_ = startDir;

    return true;
}

i32 ParticleEmitter::GetFreeParticle() const
{
    for (i32 i = 0; i < billboards_.Size(); ++i)
    {
        if (!billboards_[i].enabled_)
            return i;
    }

    return NINDEX;
}

bool ParticleEmitter::CheckActiveParticles() const
{
    for (i32 i = 0; i < billboards_.Size(); ++i)
    {
        if (billboards_[i].enabled_)
        {
            return true;
            break;
        }
    }

    return false;
}

void ParticleEmitter::HandleScenePostUpdate(StringHash eventType, VariantMap& eventData)
{
    // Store scene's timestep and use it instead of global timestep, as time scale may be other than 1
    using namespace ScenePostUpdate;

    lastTimeStep_ = eventData[P_TIMESTEP].GetFloat();

    // If no invisible update, check that the billboardset is in view (framenumber has changed)
    if ((effect_ && effect_->GetUpdateInvisible()) || viewFrameNumber_ != lastUpdateFrameNumber_)
    {
        lastUpdateFrameNumber_ = viewFrameNumber_;
        needUpdate_ = true;
        MarkForUpdate();
    }

    // Send finished event only once all particles are gone
    if (node_ && !emitting_ && sendFinishedEvent_ && !CheckActiveParticles())
    {
        sendFinishedEvent_ = false;

        // Make a weak pointer to self to check for destruction during event handling
        WeakPtr<ParticleEmitter> self(this);

        using namespace ParticleEffectFinished;

        VariantMap& eventData = GetEventDataMap();
        eventData[P_NODE] = node_;
        eventData[P_EFFECT] = effect_;

        node_->SendEvent(E_PARTICLEEFFECTFINISHED, eventData);

        if (self.Expired())
            return;

        DoAutoRemove(autoRemove_);
    }
}

void ParticleEmitter::HandleEffectReloadFinished(StringHash eventType, VariantMap& eventData)
{
    // When particle effect file is live-edited, remove existing particles and reapply the effect parameters
    Reset();
    ApplyEffect();
}

}
