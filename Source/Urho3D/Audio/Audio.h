// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include "../Audio/AudioDefs.h"
#include "../Container/ArrayPtr.h"
#include "../Container/HashSet.h"
#include "../Core/Mutex.h"
#include "../Core/Object.h"

namespace Urho3D
{

class AudioImpl;
class Sound;
class SoundListener;
class SoundSource;

/// %Audio subsystem.
class URHO3D_API Audio : public Object
{
    URHO3D_OBJECT(Audio, Object);

public:
    /// Construct.
    explicit Audio(Context* context);
    /// Destruct. Terminate the audio thread and free the audio buffer.
    ~Audio() override;

    /// Initialize sound output with specified buffer length and output mode.
    bool SetMode(i32 bufferLengthMSec, i32 mixRate, bool stereo, bool interpolation = true);
    /// Run update on sound sources. Not required for continued playback, but frees unused sound sources & sounds and updates 3D positions.
    void Update(float timeStep);
    /// Restart sound output.
    bool Play();
    /// Suspend sound output.
    void Stop();
    /// Set master gain on a specific sound type such as sound effects, music or voice.
    /// @property
    void SetMasterGain(const String& type, float gain);
    /// Pause playback of specific sound type. This allows to suspend e.g. sound effects or voice when the game is paused. By default all sound types are unpaused.
    void PauseSoundType(const String& type);
    /// Resume playback of specific sound type.
    void ResumeSoundType(const String& type);
    /// Resume playback of all sound types.
    void ResumeAll();
    /// Set active sound listener for 3D sounds.
    /// @property
    void SetListener(SoundListener* listener);
    /// Stop any sound source playing a certain sound clip.
    void StopSound(Sound* sound);

    /// Return byte size of one sample.
    /// @property
    u32 GetSampleSize() const { return sampleSize_; }

    /// Return mixing rate.
    /// @property
    i32 GetMixRate() const { return mixRate_; }

    /// Return whether output is interpolated.
    /// @property
    bool GetInterpolation() const { return interpolation_; }

    /// Return whether output is stereo.
    /// @property
    bool IsStereo() const { return stereo_; }

    /// Return whether audio is being output.
    /// @property
    bool IsPlaying() const { return playing_; }

    /// Return whether an audio stream has been reserved.
    /// @property
    bool IsInitialized() const { return deviceID_ != 0; }

    /// Return master gain for a specific sound source type. Unknown sound types will return full gain (1).
    /// @property
    float GetMasterGain(const String& type) const;

    /// Return whether specific sound type has been paused.
    bool IsSoundTypePaused(const String& type) const;

    /// Return active sound listener.
    /// @property
    SoundListener* GetListener() const;

    /// Return all sound sources.
    const PODVector<SoundSource*>& GetSoundSources() const { return soundSources_; }

    /// Return whether the specified master gain has been defined.
    bool HasMasterGain(const String& type) const { return masterGain_.Contains(type); }

    /// Add a sound source to keep track of. Called by SoundSource.
    void AddSoundSource(SoundSource* soundSource);
    /// Remove a sound source. Called by SoundSource.
    void RemoveSoundSource(SoundSource* soundSource);

    /// Return audio thread mutex.
    Mutex& GetMutex() { return audioMutex_; }

    /// Return sound type specific gain multiplied by master gain.
    float GetSoundSourceMasterGain(StringHash typeHash) const;

    /// Mix sound sources into the buffer.
    void MixOutput(void* dest, u32 samples);

private:
    /// Handle render update event.
    void HandleRenderUpdate(StringHash eventType, VariantMap& eventData);
    /// Stop sound output and release the sound buffer.
    void Release();
    /// Actually update sound sources with the specific timestep. Called internally.
    void UpdateInternal(float timeStep);

    /// Clipping buffer for mixing.
    SharedArrayPtr<i32> clipBuffer_;
    /// Audio thread mutex.
    Mutex audioMutex_;
    /// SDL audio device ID.
    u32 deviceID_{};
    /// Sample size.
    u32 sampleSize_{};
    /// Clip buffer size in samples.
    u32 fragmentSize_{};
    /// Mixing rate.
    i32 mixRate_{};
    /// Mixing interpolation flag.
    bool interpolation_{};
    /// Stereo flag.
    bool stereo_{};
    /// Playing flag.
    bool playing_{};
    /// Master gain by sound source type.
    HashMap<StringHash, Variant> masterGain_;
    /// Paused sound types.
    HashSet<StringHash> pausedSoundTypes_;
    /// Sound sources.
    PODVector<SoundSource*> soundSources_;
    /// Sound listener.
    WeakPtr<SoundListener> listener_;
};

/// Register Audio library objects.
/// @nobind
void URHO3D_API RegisterAudioLibrary(Context* context);

}
