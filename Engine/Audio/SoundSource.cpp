//
// Urho3D Engine
// Copyright (c) 2008-2012 Lasse Öörni
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
#include "Audio.h"
#include "Context.h"
#include "ResourceCache.h"
#include "Sound.h"
#include "SoundSource.h"

#include <cstring>

#include "DebugNew.h"

namespace Urho3D
{

#define INC_POS_LOOPED() \
    pos += intAdd; \
    fractPos += fractAdd; \
    if (fractPos > 65535) \
    { \
        fractPos &= 65535; \
        ++pos; \
    } \
    while (pos >= end) \
        pos -= (end - repeat); \

#define INC_POS_ONESHOT() \
    pos += intAdd; \
    fractPos += fractAdd; \
    if (fractPos > 65535) \
    { \
        fractPos &= 65535; \
        ++pos; \
    } \
    if (pos >= end) \
    { \
        pos = 0; \
        break; \
    } \

#define INC_POS_STEREO_LOOPED() \
    pos += (intAdd << 1); \
    fractPos += fractAdd; \
    if (fractPos > 65535) \
    { \
        fractPos &= 65535; \
        pos += 2; \
    } \
    while (pos >= end) \
        pos -= (end - repeat); \

#define INC_POS_STEREO_ONESHOT() \
    pos += (intAdd << 1); \
    fractPos += fractAdd; \
    if (fractPos > 65535) \
    { \
        fractPos &= 65535; \
        pos += 2; \
    } \
    if (pos >= end) \
    { \
        pos = 0; \
        break; \
    } \

#define GET_IP_SAMPLE() (((((int)pos[1] - (int)pos[0]) * fractPos) / 65536) + (int)pos[0])

#define GET_IP_SAMPLE_LEFT() (((((int)pos[2] - (int)pos[0]) * fractPos) / 65536) + (int)pos[0])

#define GET_IP_SAMPLE_RIGHT() (((((int)pos[3] - (int)pos[1]) * fractPos) / 65536) + (int)pos[1])

static const char* typeNames[] =
{
    "Effect",
    "Ambient",
    "Voice",
    "Music",
    0
};

static const float AUTOREMOVE_DELAY = 0.25f;

OBJECTTYPESTATIC(SoundSource);

SoundSource::SoundSource(Context* context) :
    Component(context),
    position_(0),
    fractPosition_(0),
    timePosition_(0.0f),
    soundType_(SOUND_EFFECT),
    frequency_(0.0f),
    gain_(1.0f),
    attenuation_(1.0f),
    panning_(0.0f),
    autoRemoveTimer_(0.0f),
    autoRemove_(false),
    decoder_(0),
    decodePosition_(0)
{
    audio_ = GetSubsystem<Audio>();
    
    if (audio_)
        audio_->AddSoundSource(this);
}

SoundSource::~SoundSource()
{
    if (audio_)
        audio_->RemoveSoundSource(this);
    
    FreeDecoder();
}

void SoundSource::RegisterObject(Context* context)
{
    context->RegisterFactory<SoundSource>();
    
    ENUM_ATTRIBUTE(SoundSource, "Sound Type", soundType_, typeNames, SOUND_EFFECT, AM_DEFAULT);
    ATTRIBUTE(SoundSource, VAR_FLOAT, "Frequency", frequency_, 0.0f, AM_DEFAULT);
    ATTRIBUTE(SoundSource, VAR_FLOAT, "Gain", gain_, 1.0f, AM_DEFAULT);
    ATTRIBUTE(SoundSource, VAR_FLOAT, "Attenuation", attenuation_, 1.0f, AM_DEFAULT);
    ATTRIBUTE(SoundSource, VAR_FLOAT, "Panning", panning_, 0.0f, AM_DEFAULT);
    ATTRIBUTE(SoundSource, VAR_BOOL, "Autoremove on Stop", autoRemove_, false, AM_FILE);
    ACCESSOR_ATTRIBUTE(SoundSource, VAR_RESOURCEREF, "Sound", GetSoundAttr, SetSoundAttr, ResourceRef, ResourceRef(Sound::GetTypeStatic()), AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(SoundSource, VAR_INT, "Play Position", GetPositionAttr, SetPositionAttr, int, 0, AM_FILE);
}

void SoundSource::Play(Sound* sound)
{
    if (!audio_)
        return;
    
    // If no frequency set yet, set from the sound's default
    if (frequency_ == 0.0f && sound)
        SetFrequency(sound->GetFrequency());
    
    // If sound source is currently playing, have to lock the audio mutex
    if (position_)
    {
        MutexLock lock(audio_->GetMutex());
        PlayLockless(sound);
    }
    else
        PlayLockless(sound);
    
    MarkNetworkUpdate();
}

void SoundSource::Play(Sound* sound, float frequency)
{
    SetFrequency(frequency);
    Play(sound);
}

void SoundSource::Play(Sound* sound, float frequency, float gain)
{
    SetFrequency(frequency);
    SetGain(gain);
    Play(sound);
}

void SoundSource::Play(Sound* sound, float frequency, float gain, float panning)
{
    SetFrequency(frequency);
    SetGain(gain);
    SetPanning(panning);
    Play(sound);
}

void SoundSource::Stop()
{
    if (!audio_)
        return;
    
    // If sound source is currently playing, have to lock the audio mutex
    if (position_)
    {
        MutexLock lock(audio_->GetMutex());
        StopLockless();
    }
    
    // Free the compressed sound decoder now if any
    FreeDecoder();
    sound_.Reset();
    
    MarkNetworkUpdate();
}

void SoundSource::SetSoundType(SoundType type)
{
    if (type == SOUND_MASTER || type >= MAX_SOUND_TYPES)
        return;
    
    soundType_ = type;
    MarkNetworkUpdate();
}

void SoundSource::SetFrequency(float frequency)
{
    frequency_ = Clamp(frequency, 0.0f, 535232.0f);
    MarkNetworkUpdate();
}

void SoundSource::SetGain(float gain)
{
    gain_ = Max(gain, 0.0f);
    MarkNetworkUpdate();
}

void SoundSource::SetAttenuation(float attenuation)
{
    attenuation_ = Clamp(attenuation, 0.0f, 1.0f);
    MarkNetworkUpdate();
}

void SoundSource::SetPanning(float panning)
{
    panning_ = Clamp(panning, -1.0f, 1.0f);
    MarkNetworkUpdate();
}

void SoundSource::SetAutoRemove(bool enable)
{
    autoRemove_ = enable;
}

bool SoundSource::IsPlaying() const
{
    return sound_.Get() != 0;
}

void SoundSource::SetPlayPosition(signed char* pos)
{
    if (!audio_ || !sound_)
        return;
    
    MutexLock lock(audio_->GetMutex());
    SetPlayPositionLockless(pos);
}

void SoundSource::PlayLockless(Sound* sound)
{
    // Reset the time position in any case
    timePosition_ = 0.0f;
    
    if (sound)
    {
        if (!sound->IsCompressed())
        {
            // Uncompressed sound start
            signed char* start = sound->GetStart();
            if (start)
            {
                // Free Decoder in case previous sound was compressed
                FreeDecoder();
                sound_ = sound;
                position_ = start;
                fractPosition_ = 0;
                return;
            }
        }
        else
        {
            // Compressed sound start
            if (sound == sound_)
            {
                // If same compressed sound is already playing, rewind the Decoder
                sound_->RewindDecoder(decoder_);
                return;
            }
            else
            {
                // Else just set the new sound with a dummy start position. The mixing routine will allocate the new Decoder
                FreeDecoder();
                sound_ = sound;
                position_ = sound->GetStart();
                return;
            }
        }
    }
    
    // If sound pointer is null or if sound has no data, stop playback
    FreeDecoder();
    sound_.Reset();
    position_ = 0;
}

void SoundSource::StopLockless()
{
    position_ = 0;
    timePosition_ = 0.0f;
}

void SoundSource::SetPlayPositionLockless(signed char* pos)
{
    // Setting position on a compressed sound is not supported
    if (!sound_ || sound_->IsCompressed())
        return;
    
    signed char* start = sound_->GetStart();
    signed char* end = sound_->GetEnd();
    if (pos < start)
        pos = start;
    if (sound_->IsSixteenBit() && (pos - start) & 1)
        ++pos;
    if (pos > end)
        pos = end;
    
    position_ = pos;
    timePosition_ = (float)((int)pos - (int)sound_->GetStart()) / (sound_->GetSampleSize() * sound_->GetFrequency());
}

void SoundSource::Update(float timeStep)
{
    if (!audio_)
        return;
    
    // If there is no actual audio output, perform fake mixing into a nonexistent buffer to check stopping/looping
    if (!audio_->IsInitialized())
        MixNull(timeStep);
    
    // Free the sound if playback has stopped
    if (sound_ && !position_)
    {
        FreeDecoder();
        sound_.Reset();
    }
    
    // Check for autoremove
    if (autoRemove_)
    {
        if (!IsPlaying())
        {
            autoRemoveTimer_ += timeStep;
            if (autoRemoveTimer_ > AUTOREMOVE_DELAY)
            {
                Remove();
                // Note: this object is now deleted, so only returning immediately is safe
                return;
            }
        }
        else
            autoRemoveTimer_ = 0.0f;
    }
}

void SoundSource::Mix(int* dest, unsigned samples, int mixRate, bool stereo, bool interpolation)
{
    if (!position_ || !sound_)
        return;
    
    if (sound_->IsCompressed())
    {
        if (decoder_)
        {
            // If Decoder already exists, Decode new compressed audio
            bool eof = false;
            unsigned currentPos = position_ - decodeBuffer_->GetStart();
            if (currentPos != decodePosition_)
            {
                // If buffer has wrapped, Decode first to the end
                if (currentPos < decodePosition_)
                {
                    unsigned bytes = decodeBuffer_->GetDataSize() - decodePosition_;
                    unsigned outBytes = sound_->Decode(decoder_, decodeBuffer_->GetStart() + decodePosition_, bytes);
                    // If produced less output, end of sound encountered. Fill rest with zero
                    if (outBytes < bytes)
                    {
                        memset(decodeBuffer_->GetStart() + decodePosition_ + outBytes, 0, bytes - outBytes);
                        eof = true;
                    }
                    decodePosition_ = 0;
                }
                if (currentPos > decodePosition_)
                {
                    unsigned bytes = currentPos - decodePosition_;
                    unsigned outBytes = sound_->Decode(decoder_, decodeBuffer_->GetStart() + decodePosition_, bytes);
                    // If produced less output, end of sound encountered. Fill rest with zero
                    if (outBytes < bytes)
                    {
                        memset(decodeBuffer_->GetStart() + decodePosition_ + outBytes, 0, bytes - outBytes);
                        if (sound_->IsLooped())
                            eof = true;
                    }
                    
                    // If wrote to buffer start, correct interpolation wraparound
                    if (!decodePosition_)
                        decodeBuffer_->FixInterpolation();
                }
            }
            
            // If end of stream encountered, check whether we should rewind or stop
            if (eof)
            {
                if (sound_->IsLooped())
                {
                    sound_->RewindDecoder(decoder_);
                    timePosition_ = 0.0f;
                }
                else
                    decodeBuffer_->SetLooped(false); // Stop after the current decode buffer has been played
            }
            
            decodePosition_ = currentPos;
        }
        else
        {
            // Setup the decoder and decode buffer
            decoder_ = sound_->AllocateDecoder();
            unsigned sampleSize = sound_->GetSampleSize();
            unsigned DecodeBufferSize = sampleSize * sound_->GetIntFrequency() * DECODE_BUFFER_LENGTH / 1000;
            decodeBuffer_ = new Sound(context_);
            decodeBuffer_->SetSize(DecodeBufferSize);
            decodeBuffer_->SetFormat(sound_->GetIntFrequency(), true, sound_->IsStereo());
            
            // Clear the decode buffer, then fill with initial audio data and set it to loop
            memset(decodeBuffer_->GetStart(), 0, DecodeBufferSize);
            sound_->Decode(decoder_, decodeBuffer_->GetStart(), DecodeBufferSize);
            decodeBuffer_->SetLooped(true);
            decodePosition_ = 0;
            
            // Start playing the decode buffer
            position_ = decodeBuffer_->GetStart();
            fractPosition_ = 0;
        }
    }
    
    // If compressed, play the decode buffer. Otherwise play the original sound
    Sound* sound = sound_->IsCompressed() ? decodeBuffer_ : sound_;
    if (!sound)
        return;
    
    // Choose the correct mixing routine
    if (!sound->IsStereo())
    {
        if (interpolation)
        {
            if (stereo)
                MixMonoToStereoIP(sound, dest, samples, mixRate);
            else
                MixMonoToMonoIP(sound, dest, samples, mixRate);
        }
        else
        {
            if (stereo)
                MixMonoToStereo(sound, dest, samples, mixRate);
            else
                MixMonoToMono(sound, dest, samples, mixRate);
        }
    }
    else
    {
        if (interpolation)
        {
            if (stereo)
                MixStereoToStereoIP(sound, dest, samples, mixRate);
            else
                MixStereoToMonoIP(sound, dest, samples, mixRate);
        }
        else
        {
            if (stereo)
                MixStereoToStereo(sound, dest, samples, mixRate);
            else
                MixStereoToMono(sound, dest, samples, mixRate);
        }
    }
    
    // Update the time position
    if (!sound_->IsCompressed())
        timePosition_ = (float)((int)position_ - (int)sound_->GetStart()) / (sound_->GetSampleSize() * sound_->GetFrequency());
    else
        timePosition_ += ((float)samples / (float)mixRate) * frequency_ / sound_->GetFrequency();
}

void SoundSource::SetSoundAttr(ResourceRef value)
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    Play(cache->GetResource<Sound>(value.id_));
}

void SoundSource::SetPositionAttr(int value)
{
    if (sound_)
        SetPlayPosition(sound_->GetStart() + value);
}

ResourceRef SoundSource::GetSoundAttr() const
{
    return GetResourceRef(sound_, Sound::GetTypeStatic());
}

int SoundSource::GetPositionAttr() const
{
    if (sound_)
        return (int)(GetPlayPosition() - sound_->GetStart());
    else
        return 0;
}

void SoundSource::MixMonoToMono(Sound* sound, int* dest, unsigned samples, int mixRate)
{
    float totalGain = audio_->GetSoundSourceMasterGain(soundType_) * attenuation_ * gain_;
    int vol = (int)(256.0f * totalGain + 0.5f);
    if (!vol)
    {
        MixZeroVolume(sound, samples, mixRate);
        return;
    }
    
    float add = frequency_ / (float)mixRate;
    int intAdd = (int)add;
    int fractAdd = (int)((add - floorf(add)) * 65536.0f);
    int fractPos = fractPosition_;
    
    if (sound->IsSixteenBit())
    {
        short* pos = (short*)position_;
        short* end = (short*)sound->GetEnd();
        short* repeat = (short*)sound->GetRepeat();
        
        if (sound->IsLooped())
        {
            while (--samples)
            {
                *dest = *dest + (*pos * vol) / 256;
                ++dest;
                INC_POS_LOOPED();
            }
            position_ = (signed char*)pos;
        }
        else
        {
            while (--samples)
            {
                *dest = *dest + (*pos * vol) / 256;
                ++dest;
                INC_POS_ONESHOT();
            }
            position_ = (signed char*)pos;
        }
    }
    else
    {
        signed char* pos = (signed char*)position_;
        signed char* end = sound->GetEnd();
        signed char* repeat = sound->GetRepeat();
        
        if (sound->IsLooped())
        {
            while (--samples)
            {
                *dest = *dest + *pos * vol;
                ++dest;
                INC_POS_LOOPED();
            }
            position_ = pos;
        }
        else
        {
            while (--samples)
            {
                *dest = *dest + *pos * vol;
                ++dest;
                INC_POS_ONESHOT();
            }
            position_ = pos;
        }
    }
    
    fractPosition_ = fractPos;
}

void SoundSource::MixMonoToStereo(Sound* sound, int* dest, unsigned samples, int mixRate)
{
    float totalGain = audio_->GetSoundSourceMasterGain(soundType_) * attenuation_ * gain_;
    int leftVol = (int)((-panning_ + 1.0f) * (256.0f * totalGain + 0.5f));
    int rightVol = (int)((panning_ + 1.0f) * (256.0f * totalGain + 0.5f));
    if (!leftVol && !rightVol)
    {
        MixZeroVolume(sound, samples, mixRate);
        return;
    }
    
    float add = frequency_ / (float)mixRate;
    int intAdd = (int)add;
    int fractAdd = (int)((add - floorf(add)) * 65536.0f);
    int fractPos = fractPosition_;
    
    if (sound->IsSixteenBit())
    {
        short* pos = (short*)position_;
        short* end = (short*)sound->GetEnd();
        short* repeat = (short*)sound->GetRepeat();
        
        if (sound->IsLooped())
        {
            while (--samples)
            {
                *dest = *dest + (*pos * leftVol) / 256;
                ++dest;
                *dest = *dest + (*pos * rightVol) / 256;
                ++dest;
                INC_POS_LOOPED();
            }
            position_ = (signed char*)pos;
        }
        else
        {
            while (--samples)
            {
                *dest = *dest + (*pos * leftVol) / 256;
                ++dest;
                *dest = *dest + (*pos * rightVol) / 256;
                ++dest;
                INC_POS_ONESHOT();
            }
            position_ = (signed char*)pos;
        }
    }
    else
    {
        signed char* pos = (signed char*)position_;
        signed char* end = sound->GetEnd();
        signed char* repeat = sound->GetRepeat();
        
        if (sound->IsLooped())
        {
            while (--samples)
            {
                *dest = *dest + *pos * leftVol;
                ++dest;
                *dest = *dest + *pos * rightVol;
                ++dest;
                INC_POS_LOOPED();
            }
            position_ = pos;
        }
        else
        {
            while (--samples)
            {
                *dest = *dest + *pos * leftVol;
                ++dest;
                *dest = *dest + *pos * rightVol;
                ++dest;
                INC_POS_ONESHOT();
            }
            position_ = pos;
        }
    }
    
    fractPosition_ = fractPos;
}

void SoundSource::MixMonoToMonoIP(Sound* sound, int* dest, unsigned samples, int mixRate)
{
    float totalGain = audio_->GetSoundSourceMasterGain(soundType_) * attenuation_ * gain_;
    int vol = (int)(256.0f * totalGain + 0.5f);
    if (!vol)
    {
        MixZeroVolume(sound, samples, mixRate);
        return;
    }
    
    float add = frequency_ / (float)mixRate;
    int intAdd = (int)add;
    int fractAdd = (int)((add - floorf(add)) * 65536.0f);
    int fractPos = fractPosition_;
    
    if (sound->IsSixteenBit())
    {
        short* pos = (short*)position_;
        short* end = (short*)sound->GetEnd();
        short* repeat = (short*)sound->GetRepeat();
        
        if (sound->IsLooped())
        {
            while (--samples)
            {
                *dest = *dest + (GET_IP_SAMPLE() * vol) / 256;
                ++dest;
                INC_POS_LOOPED();
            }
            position_ = (signed char*)pos;
        }
        else
        {
            while (--samples)
            {
                *dest = *dest + (GET_IP_SAMPLE() * vol) / 256;
                ++dest;
                INC_POS_ONESHOT();
            }
            position_ = (signed char*)pos;
        }
    }
    else
    {
        signed char* pos = (signed char*)position_;
        signed char* end = sound->GetEnd();
        signed char* repeat = sound->GetRepeat();
        
        if (sound->IsLooped())
        {
            while (--samples)
            {
                *dest = *dest + GET_IP_SAMPLE() * vol;
                ++dest;
                INC_POS_LOOPED();
            }
            position_ = pos;
        }
        else
        {
            while (--samples)
            {
                *dest = *dest + GET_IP_SAMPLE() * vol;
                ++dest;
                INC_POS_ONESHOT();
            }
            position_ = pos;
        }
    }
    
    fractPosition_ = fractPos;
}

void SoundSource::MixMonoToStereoIP(Sound* sound, int* dest, unsigned samples, int mixRate)
{
    float totalGain = audio_->GetSoundSourceMasterGain(soundType_) * attenuation_ * gain_;
    int leftVol = (int)((-panning_ + 1.0f) * (256.0f * totalGain + 0.5f));
    int rightVol = (int)((panning_ + 1.0f) * (256.0f * totalGain + 0.5f));
    if (!leftVol && !rightVol)
    {
        MixZeroVolume(sound, samples, mixRate);
        return;
    }
    
    float add = frequency_ / (float)mixRate;
    int intAdd = (int)add;
    int fractAdd = (int)((add - floorf(add)) * 65536.0f);
    int fractPos = fractPosition_;
    
    if (sound->IsSixteenBit())
    {
        short* pos = (short*)position_;
        short* end = (short*)sound->GetEnd();
        short* repeat = (short*)sound->GetRepeat();
        
        if (sound->IsLooped())
        {
            while (--samples)
            {
                int s = GET_IP_SAMPLE();
                *dest = *dest + (s * leftVol) / 256;
                ++dest;
                *dest = *dest + (s * rightVol) / 256;
                ++dest;
                INC_POS_LOOPED();
            }
            position_ = (signed char*)pos;
        }
        else
        {
            while (--samples)
            {
                int s = GET_IP_SAMPLE();
                *dest = *dest + (s * leftVol) / 256;
                ++dest;
                *dest = *dest + (s * rightVol) / 256;
                ++dest;
                INC_POS_ONESHOT();
            }
            position_ = (signed char*)pos;
        }
    }
    else
    {
        signed char* pos = (signed char*)position_;
        signed char* end = sound->GetEnd();
        signed char* repeat = sound->GetRepeat();
        
        if (sound->IsLooped())
        {
            while (--samples)
            {
                int s = GET_IP_SAMPLE();
                *dest = *dest + s * leftVol;
                ++dest;
                *dest = *dest + s * rightVol;
                ++dest;
                INC_POS_LOOPED();
            }
            position_ = pos;
        }
        else
        {
            while (--samples)
            {
                int s = GET_IP_SAMPLE();
                *dest = *dest + s * leftVol;
                ++dest;
                *dest = *dest + s * rightVol;
                ++dest;
                INC_POS_ONESHOT();
            }
            position_ = pos;
        }
    }
    
    fractPosition_ = fractPos;
}

void SoundSource::MixStereoToMono(Sound* sound, int* dest, unsigned samples, int mixRate)
{
    float totalGain = audio_->GetSoundSourceMasterGain(soundType_) * attenuation_ * gain_;
    int vol = (int)(256.0f * totalGain + 0.5f);
    if (!vol)
    {
        MixZeroVolume(sound, samples, mixRate);
        return;
    }
    
    float add = frequency_ / (float)mixRate;
    int intAdd = (int)add;
    int fractAdd = (int)((add - floorf(add)) * 65536.0f);
    int fractPos = fractPosition_;
    
    if (sound->IsSixteenBit())
    {
        short* pos = (short*)position_;
        short* end = (short*)sound->GetEnd();
        short* repeat = (short*)sound->GetRepeat();
        
        if (sound->IsLooped())
        {
            while (--samples)
            {
                int s = ((int)pos[0] + (int)pos[1]) / 2;
                *dest = *dest + (s * vol) / 256;
                ++dest;
                INC_POS_STEREO_LOOPED();
            }
            position_ = (signed char*)pos;
        }
        else
        {
            while (--samples)
            {
                int s = ((int)pos[0] + (int)pos[1]) / 2;
                *dest = *dest + (s * vol) / 256;
                ++dest;
                INC_POS_STEREO_ONESHOT();
            }
            position_ = (signed char*)pos;
        }
    }
    else
    {
        signed char* pos = (signed char*)position_;
        signed char* end = sound->GetEnd();
        signed char* repeat = sound->GetRepeat();
        
        if (sound->IsLooped())
        {
            while (--samples)
            {
                int s = ((int)pos[0] + (int)pos[1]) / 2;
                *dest = *dest + s * vol;
                ++dest;
                INC_POS_STEREO_LOOPED();
            }
            position_ = pos;
        }
        else
        {
            while (--samples)
            {
                int s = ((int)pos[0] + (int)pos[1]) / 2;
                *dest = *dest + s * vol;
                ++dest;
                INC_POS_STEREO_ONESHOT();
            }
            position_ = pos;
        }
    }
    
    fractPosition_ = fractPos;
}

void SoundSource::MixStereoToStereo(Sound* sound, int* dest, unsigned samples, int mixRate)
{
    float totalGain = audio_->GetSoundSourceMasterGain(soundType_) * attenuation_ * gain_;
    int vol = (int)(256.0f * totalGain + 0.5f);
    if (!vol)
    {
        MixZeroVolume(sound, samples, mixRate);
        return;
    }
    
    float add = frequency_ / (float)mixRate;
    int intAdd = (int)add;
    int fractAdd = (int)((add - floorf(add)) * 65536.0f);
    int fractPos = fractPosition_;
    
    if (sound->IsSixteenBit())
    {
        short* pos = (short*)position_;
        short* end = (short*)sound->GetEnd();
        short* repeat = (short*)sound->GetRepeat();
        
        if (sound->IsLooped())
        {
            while (--samples)
            {
                *dest = *dest + (pos[0] * vol) / 256;
                ++dest;
                *dest = *dest + (pos[1] * vol) / 256;
                ++dest;
                INC_POS_STEREO_LOOPED();
            }
            position_ = (signed char*)pos;
        }
        else
        {
            while (--samples)
            {
                *dest = *dest + (pos[0] * vol) / 256;
                ++dest;
                *dest = *dest + (pos[1] * vol) / 256;
                ++dest;
                INC_POS_STEREO_ONESHOT();
            }
            position_ = (signed char*)pos;
        }
    }
    else
    {
        signed char* pos = (signed char*)position_;
        signed char* end = sound->GetEnd();
        signed char* repeat = sound->GetRepeat();
        
        if (sound->IsLooped())
        {
            while (--samples)
            {
                *dest = *dest + pos[0] * vol;
                ++dest;
                *dest = *dest + pos[1] * vol;
                ++dest;
                INC_POS_STEREO_LOOPED();
            }
            position_ = pos;
        }
        else
        {
            while (--samples)
            {
                *dest = *dest + pos[0] * vol;
                ++dest;
                *dest = *dest + pos[1] * vol;
                ++dest;
                INC_POS_STEREO_ONESHOT();
            }
            position_ = pos;
        }
    }
    
    fractPosition_ = fractPos;
}

void SoundSource::MixStereoToMonoIP(Sound* sound, int* dest, unsigned samples, int mixRate)
{
    float totalGain = audio_->GetSoundSourceMasterGain(soundType_) * attenuation_ * gain_;
    int vol = (int)(256.0f * totalGain + 0.5f);
    if (!vol)
    {
        MixZeroVolume(sound, samples, mixRate);
        return;
    }
    
    float add = frequency_ / (float)mixRate;
    int intAdd = (int)add;
    int fractAdd = (int)((add - floorf(add)) * 65536.0f);
    int fractPos = fractPosition_;
    
    if (sound->IsSixteenBit())
    {
        short* pos = (short*)position_;
        short* end = (short*)sound->GetEnd();
        short* repeat = (short*)sound->GetRepeat();
        
        if (sound->IsLooped())
        {
            while (--samples)
            {
                int s = (GET_IP_SAMPLE_LEFT() + GET_IP_SAMPLE_RIGHT()) / 2;
                *dest = *dest + (s * vol) / 256;
                ++dest;
                INC_POS_STEREO_LOOPED();
            }
            position_ = (signed char*)pos;
        }
        else
        {
            while (--samples)
            {
                int s = (GET_IP_SAMPLE_LEFT() + GET_IP_SAMPLE_RIGHT()) / 2;
                *dest = *dest + (s * vol) / 256;
                ++dest;
                INC_POS_STEREO_ONESHOT();
            }
            position_ = (signed char*)pos;
        }
    }
    else
    {
        signed char* pos = (signed char*)position_;
        signed char* end = sound->GetEnd();
        signed char* repeat = sound->GetRepeat();
        
        if (sound->IsLooped())
        {
            while (--samples)
            {
                int s = (GET_IP_SAMPLE_LEFT() + GET_IP_SAMPLE_RIGHT()) / 2;
                *dest = *dest + s * vol;
                ++dest;
                INC_POS_STEREO_LOOPED();
            }
            position_ = pos;
        }
        else
        {
            while (--samples)
            {
                int s = (GET_IP_SAMPLE_LEFT() + GET_IP_SAMPLE_RIGHT()) / 2;
                *dest = *dest + s * vol;
                ++dest;
                INC_POS_STEREO_ONESHOT();
            }
            position_ = pos;
        }
    }
    
    fractPosition_ = fractPos;
}

void SoundSource::MixStereoToStereoIP(Sound* sound, int* dest, unsigned samples, int mixRate)
{
    float totalGain = audio_->GetSoundSourceMasterGain(soundType_) * attenuation_ * gain_;
    int vol = (int)(256.0f * totalGain + 0.5f);
    if (!vol)
    {
        MixZeroVolume(sound, samples, mixRate);
        return;
    }
    
    float add = frequency_ / (float)mixRate;
    int intAdd = (int)add;
    int fractAdd = (int)((add - floorf(add)) * 65536.0f);
    int fractPos = fractPosition_;
    
    if (sound->IsSixteenBit())
    {
        short* pos = (short*)position_;
        short* end = (short*)sound->GetEnd();
        short* repeat = (short*)sound->GetRepeat();
        
        if (sound->IsLooped())
        {
            while (--samples)
            {
                *dest = *dest + (GET_IP_SAMPLE_LEFT() * vol) / 256;
                ++dest;
                *dest = *dest + (GET_IP_SAMPLE_RIGHT() * vol) / 256;
                ++dest;
                INC_POS_STEREO_LOOPED();
            }
            position_ = (signed char*)pos;
        }
        else
        {
            while (--samples)
            {
                *dest = *dest + (GET_IP_SAMPLE_LEFT() * vol) / 256;
                ++dest;
                *dest = *dest + (GET_IP_SAMPLE_RIGHT() * vol) / 256;
                ++dest;
                INC_POS_STEREO_ONESHOT();
            }
            position_ = (signed char*)pos;
        }
    }
    else
    {
        signed char* pos = (signed char*)position_;
        signed char* end = sound->GetEnd();
        signed char* repeat = sound->GetRepeat();
        
        if (sound->IsLooped())
        {
            while (--samples)
            {
                *dest = *dest + GET_IP_SAMPLE_LEFT() * vol;
                ++dest;
                *dest = *dest + GET_IP_SAMPLE_RIGHT() * vol;
                ++dest;
                INC_POS_STEREO_LOOPED();
            }
            position_ = pos;
        }
        else
        {
            while (--samples)
            {
                *dest = *dest + GET_IP_SAMPLE_LEFT() * vol;
                ++dest;
                *dest = *dest + GET_IP_SAMPLE_RIGHT() * vol;
                ++dest;
                INC_POS_STEREO_ONESHOT();
            }
            position_ = pos;
        }
    }
    
    fractPosition_ = fractPos;
}

void SoundSource::MixZeroVolume(Sound* sound, unsigned samples, int mixRate)
{
    float add = frequency_ * (float)samples / (float)mixRate;
    int intAdd = (int)add;
    int fractAdd = (int)((add - floorf(add)) * 65536.0f);
    unsigned sampleSize = sound->GetSampleSize();
    
    fractPosition_ += fractAdd;
    if (fractPosition_ > 65535)
    {
        fractPosition_ &= 65535;
        position_ += sampleSize;
    }
    position_ += intAdd * sampleSize;
    
    if (position_ > sound->GetEnd())
    {
        if (sound->IsLooped())
        {
            while (position_ >= sound->GetEnd())
            {
                position_ -= (sound->GetEnd() - sound->GetRepeat());
            }
        }
        else
            position_ = 0;
    }
}

void SoundSource::MixNull(float timeStep)
{
    if (!position_ || !sound_)
        return;
    
    // Advance only the time position
    timePosition_ += timeStep * frequency_ / sound_->GetFrequency();
    
    if (sound_->IsLooped())
    {
        // For simulated playback, simply reset the time position to zero when the sound loops
        if (timePosition_ >= sound_->GetLength())
            timePosition_ -= sound_->GetLength();
    }
    else
    {
        if (timePosition_ >= sound_->GetLength())
        {
            position_ = 0;
            timePosition_ = 0.0f;
        }
    }
}

void SoundSource::FreeDecoder()
{
    if (sound_ && decoder_)
    {
        sound_->FreeDecoder(decoder_);
        decoder_ = 0;
    }
    
    decodeBuffer_.Reset();
}

}
