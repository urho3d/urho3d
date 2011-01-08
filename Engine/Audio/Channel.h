//
// Urho3D Engine
// Copyright (c) 2008-2011 Lasse Öörni
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

#ifndef AUDIO_CHANNEL_H
#define AUDIO_CHANNEL_H

#include "AudioDefs.h"
#include "SharedPtr.h"

class Audio;
class Sound;

static const float CHANNEL_AUTOREMOVE_DELAY = 0.25f;

//! A software-mixed sound channel
class Channel
{
public:
    //! Construct with audio subsystem pointer
    Channel(Audio* audio);
    //! Destruct. Remove self from the audio subsystem
    virtual ~Channel();
    
    //! Play a sound
    void play(Sound* sound);
    //! Play a sound with specified frequency
    void play(Sound* sound, float frequency);
    //! Play a sound with specified frequency and gain
    void play(Sound* sound, float frequency, float gain);
    //! Play a sound with specified frequency, gain and panning
    void play(Sound* sound, float frequency, float gain, float panning);
    //! Stop playback
    void stop();
    //! Set channel type, determines which master gain control it uses
    void setChannelType(ChannelType type);
    //! Set frequency
    void setFrequency(float frequency);
    //! Set gain. 0.0 is silence, 1.0 is full volume
    void setGain(float gain);
    //! Set attenuation. 1.0 is unaltered. Used for distance attenuated playback
    void setAttenuation(float attenuation);
    //! Set stereo panning. -1.0 is full left and 1.0 is full right
    void setPanning(float panning);
    //! Set frequency with an integer value for MOD/XM playback
    void setIntFrequency(unsigned frequency);
    //! Set gain with an integer value for MOD/XM playback
    void setIntVolume(int volume);
    //! Set panning with an integer value for MOD/XM playback
    void setIntPanning(int panning);
    //! Set new playback position
    void setPlayPosition(signed char* pos);
    
    //! Return sound
    Sound* getSound() const { return mSound; }
    //! Return playback position
    volatile signed char* getPlayPosition() const { return mPos; }
    //! Return channel type
    ChannelType getChannelType() const { return mChannelType; }
    //! Return playback time position
    float getTimePosition() const { return mTimePos; }
    //! Return frequency
    float getFrequency() const { return mFrequency; }
    //! Return gain
    float getGain() const { return mGain; }
    //! Return attenuation
    float getAttenuation() const { return mAttenuation; }
    //! Return stereo panning
    float getPanning() const { return mPanning; }
    //! Return whether playing
    bool isPlaying() const;
    
    //! Play a sound without locking the audio mutex. Called internally by songs
    void playLockless(Sound* sound);
    //! Stop sound without locking the audio mutex. Called internally by songs
    void stopLockless();
    //! Set new playback position without locking the audio mutex. Called internally by songs
    void setPlayPositionLockless(signed char* pos);
    //! Update channel. Perform subclass specific operations. Called by Audio
    virtual void update(float timeStep);
    //! Mix channel output to a 32-bit clipping buffer. Called by Audio
    void mix(int* dest, unsigned samples, int mixRate, bool stereo, bool interpolate);
    
protected:
    //! Audio subsystem
    WeakPtr<Audio> mAudio;
    //! Channel type
    ChannelType mChannelType;
    //! Frequency
    float mFrequency;
    //! Gain
    float mGain;
    //! Attenuation
    float mAttenuation;
    //! Stereo panning
    float mPanning;
    
private:
    //! Mix mono sample to mono buffer
    void mixMonoToMono(Sound* sound, int* dest, unsigned samples, int mixRate);
    //! Mix mono sample to stereo buffer
    void mixMonoToStereo(Sound* sound, int* dest, unsigned samples, int mixRate);
    //! Mix mono sample to mono buffer interpolated
    void mixMonoToMonoIP(Sound* sound, int* dest, unsigned samples, int mixRate);
    //! Mix mono sample to stereo buffer interpolated
    void mixMonoToStereoIP(Sound* sound, int* dest, unsigned samples, int mixRate);
    //! Mix stereo sample to mono buffer
    void mixStereoToMono(Sound* sound, int* dest, unsigned samples, int mixRate);
    //! Mix stereo sample to stereo buffer
    void mixStereoToStereo(Sound* sound, int* dest, unsigned samples, int mixRate);
    //! Mix stereo sample to mono buffer interpolated
    void mixStereoToMonoIP(Sound* sound, int* dest, unsigned samples, int mixRate);
    //! Mix stereo sample to stereo buffer interpolated
    void mixStereoToStereoIP(Sound* sound, int* dest, unsigned samples, int mixRate);
    //! Advance playback pointer without producing audible output
    void mixZeroVolume(Sound* sound, unsigned samples, int mixRate);
    //! Advance playback pointer to simulate audio playback in headless mode
    void mixNull(float timeStep);
    //! Free decoder if any
    void freeDecoder();
    
    //! Sound
    SharedPtr<Sound> mSound;
    //! Playback position
    volatile signed char *mPos;
    //! Playback fractional position
    volatile int mFractPos;
    //! Playback time position
    volatile float mTimePos;
    //! Audio data decoder
    void* mDecoder;
    //! Decode buffer
    SharedPtr<Sound> mDecodeBuffer;
    //! Previous decode buffer position
    unsigned mDecodePos;
};

#endif // AUDIO_CHANNEL_H
