// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include "../Graphics/BillboardSet.h"

namespace Urho3D
{

class ParticleEffect;

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
    i32 colorIndex_;
    /// Current texture animation index.
    i32 texIndex_;
};

/// %Particle emitter component.
class URHO3D_API ParticleEmitter : public BillboardSet
{
    URHO3D_OBJECT(ParticleEmitter, BillboardSet);

public:
    /// Construct.
    explicit ParticleEmitter(Context* context);
    /// Destruct.
    ~ParticleEmitter() override;
    /// Register object factory.
    /// @nobind
    static void RegisterObject(Context* context);

    /// Handle enabled/disabled state change.
    void OnSetEnabled() override;
    /// Update before octree reinsertion. Is called from a worker thread.
    void Update(const FrameInfo& frame) override;

    /// Set particle effect.
    /// @property
    void SetEffect(ParticleEffect* effect);
    /// Set maximum number of particles.
    /// @property
    void SetNumParticles(i32 num);
    /// Set whether should be emitting. If the state was changed, also resets the emission period timer.
    /// @property
    void SetEmitting(bool enable);
    /// Set whether particles should be serialized. Default true, set false to reduce scene file size.
    /// @property
    void SetSerializeParticles(bool enable);
    /// Set to remove either the emitter component or its owner node from the scene automatically on particle effect completion. Disabled by default.
    /// @property
    void SetAutoRemoveMode(AutoRemoveMode mode);
    /// Reset the emission period timer.
    void ResetEmissionTimer();
    /// Remove all current particles.
    void RemoveAllParticles();
    /// Reset the particle emitter completely. Removes current particles, sets emitting state on, and resets the emission timer.
    void Reset();
    /// Apply not continuously updated values such as the material, the number of particles and sorting mode from the particle effect. Call this if you change the effect programmatically.
    void ApplyEffect();

    /// Return particle effect.
    /// @property
    ParticleEffect* GetEffect() const;

    /// Return maximum number of particles.
    /// @property
    i32 GetNumParticles() const { return particles_.Size(); }

    /// Return whether is currently emitting.
    /// @property
    bool IsEmitting() const { return emitting_; }

    /// Return whether particles are to be serialized.
    /// @property
    bool GetSerializeParticles() const { return serializeParticles_; }

    /// Return automatic removal mode on particle effect completion.
    /// @property
    AutoRemoveMode GetAutoRemoveMode() const { return autoRemove_; }

    /// Set particles effect attribute.
    void SetEffectAttr(const ResourceRef& value);
    /// Set particles effect attribute.
    ResourceRef GetEffectAttr() const;
    /// Set particles attribute.
    void SetParticlesAttr(const VariantVector& value);
    /// Return particles attribute. Returns particle amount only if particles are not to be serialized.
    VariantVector GetParticlesAttr() const;
    /// Return billboards attribute. Returns billboard amount only if particles are not to be serialized.
    VariantVector GetParticleBillboardsAttr() const;

protected:
    /// Handle scene being assigned.
    void OnSceneSet(Scene* scene) override;

    /// Create a new particle. Return true if there was room.
    bool EmitNewParticle();
    /// Return a free particle index.
    i32 GetFreeParticle() const;
    /// Return whether has active particles.
    bool CheckActiveParticles() const;

private:
    /// Handle scene post-update event.
    void HandleScenePostUpdate(StringHash eventType, VariantMap& eventData);
    /// Handle live reload of the particle effect.
    void HandleEffectReloadFinished(StringHash eventType, VariantMap& eventData);

    /// Particle effect.
    SharedPtr<ParticleEffect> effect_;
    /// Particles.
    Vector<Particle> particles_;
    /// Active/inactive period timer.
    float periodTimer_;
    /// New particle emission timer.
    float emissionTimer_;
    /// Last scene timestep.
    float lastTimeStep_;
    /// Rendering framenumber on which was last updated.
    i32 lastUpdateFrameNumber_;
    /// Currently emitting flag.
    bool emitting_;
    /// Need update flag.
    bool needUpdate_;
    /// Serialize particles flag.
    bool serializeParticles_;
    /// Ready to send effect finish event flag.
    bool sendFinishedEvent_;
    /// Automatic removal mode.
    AutoRemoveMode autoRemove_;
};

}
