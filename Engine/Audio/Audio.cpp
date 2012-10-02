//
// Urho3D Engine
// Copyright (c) 2008-2012 Lasse Oorni
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
#include "CoreEvents.h"
#include "Graphics.h"
#include "GraphicsEvents.h"
#include "Log.h"
#include "Mutex.h"
#include "ProcessUtils.h"
#include "Profiler.h"
#include "Sound.h"
#include "SoundListener.h"
#include "SoundSource3D.h"

#include <SDL.h>

#include "DebugNew.h"

namespace Urho3D
{

static const int MIN_BUFFERLENGTH = 20;
static const int MIN_MIXRATE = 11025;
static const int MAX_MIXRATE = 48000;
static const int AUDIO_FPS = 100;

static void SDLAudioCallback(void *userdata, Uint8 *stream, int len);

OBJECTTYPESTATIC(Audio);

Audio::Audio(Context* context) :
    Object(context),
    deviceID_(0),
    sampleSize_(0),
    playing_(false)
{
    SubscribeToEvent(E_RENDERUPDATE, HANDLER(Audio, HandleRenderUpdate));
    
    for (unsigned i = 0; i < MAX_SOUND_TYPES; ++i)
        masterGain_[i] = 1.0f;
}

Audio::~Audio()
{
    Release();
}

bool Audio::SetMode(int bufferLengthMSec, int mixRate, bool stereo, bool interpolation)
{
    Release();
    
    bufferLengthMSec = Max(bufferLengthMSec, MIN_BUFFERLENGTH);
    mixRate = Clamp(mixRate, MIN_MIXRATE, MAX_MIXRATE);
    
    // Guarantee a fragment size that is low enough so that Vorbis decoding buffers do not wrap
    fragmentSize_ = NextPowerOfTwo(mixRate >> 6);
    
    SDL_AudioSpec desired;
    SDL_AudioSpec obtained;
    
    desired.freq = mixRate;
    desired.format = AUDIO_S16SYS;
    desired.channels = 1;
    if (stereo)
        desired.channels = 2;
    
    // For SDL, do not actually use the buffer length, but calculate a suitable power-of-two size from the mixrate
    if (desired.freq <= 11025)
        desired.samples = 512;
    else if (desired.freq <= 22050)
        desired.samples = 1024;
    else if (desired.freq <= 44100)
        desired.samples = 2048;
    else
        desired.samples = 4096;
    
    desired.callback = SDLAudioCallback;
    desired.userdata = this;
    
    {
        MutexLock lock(GetStaticMutex());
        
        deviceID_ = SDL_OpenAudioDevice(0, SDL_FALSE, &desired, &obtained, SDL_AUDIO_ALLOW_ANY_CHANGE);
        if (!deviceID_)
        {
            LOGERROR("Could not initialize audio output");
            return false;
        }
        
        if (obtained.format != AUDIO_S16SYS && obtained.format != AUDIO_S16LSB && obtained.format != AUDIO_S16MSB)
        {
            LOGERROR("Could not initialize audio output, 16-bit buffer format not supported");
            SDL_CloseAudioDevice(deviceID_);
            deviceID_ = 0;
            return false;
        }
    }
    
    stereo_ = obtained.channels == 2;
    sampleSize_ = stereo_ ? sizeof(int) : sizeof(short);
    fragmentSize_ = obtained.samples;
    mixRate_ = mixRate;
    interpolation_ = interpolation;
    clipBuffer_ = new int[stereo ? fragmentSize_ << 1 : fragmentSize_];
    
    LOGINFO("Set audio mode " + String(mixRate_) + " Hz " + (stereo_ ? "stereo" : "mono") + " " +
        (interpolation_ ? "interpolated" : ""));
    
    return Play();
}

void Audio::Update(float timeStep)
{
    PROFILE(UpdateAudio);
    
    // Update in reverse order, because sound sources might remove themselves
    for (unsigned i = soundSources_.Size() - 1; i < soundSources_.Size(); --i)
        soundSources_[i]->Update(timeStep);
}

bool Audio::Play()
{
    if (playing_)
        return true;
    
    if (!deviceID_)
    {
        LOGERROR("No audio mode set, can not start playback");
        return false;
    }
    
    SDL_PauseAudioDevice(deviceID_, 0);
    
    playing_ = true;
    return true;
}

void Audio::Stop()
{
    playing_ = false;
}

void Audio::SetMasterGain(SoundType type, float gain)
{
    if (type >= MAX_SOUND_TYPES)
        return;
    
    masterGain_[type] = Clamp(gain, 0.0f, 1.0f);
}

void Audio::SetListener(SoundListener* listener)
{
    listener_ = listener;
}

void Audio::StopSound(Sound* soundClip)
{
    for (PODVector<SoundSource*>::Iterator i = soundSources_.Begin(); i != soundSources_.End(); ++i)
    {
        if ((*i)->GetSound() == soundClip)
            (*i)->Stop();
    }
}

float Audio::GetMasterGain(SoundType type) const
{
    if (type >= MAX_SOUND_TYPES)
        return 0.0f;
    
    return masterGain_[type];
}

SoundListener* Audio::GetListener() const
{
    return listener_;
}

void Audio::AddSoundSource(SoundSource* channel)
{
    MutexLock lock(audioMutex_);
    soundSources_.Push(channel);
}

void Audio::RemoveSoundSource(SoundSource* channel)
{
    PODVector<SoundSource*>::Iterator i = soundSources_.Find(channel);
    if (i != soundSources_.End())
    {
        MutexLock lock(audioMutex_);
        soundSources_.Erase(i);
    }
}

void SDLAudioCallback(void *userdata, Uint8* stream, int len)
{
    Audio* audio = static_cast<Audio*>(userdata);
    
    {
        MutexLock Lock(audio->GetMutex());
        audio->MixOutput(stream, len / audio->GetSampleSize());
    }
}

void Audio::MixOutput(void *dest, unsigned samples)
{
    if (!playing_ || !clipBuffer_)
    {
        memset(dest, 0, samples * sampleSize_);
        return;
    }
    
    while (samples)
    {
        // If sample count exceeds the fragment (clip buffer) size, split the work
        unsigned workSamples = Min((int)samples, (int)fragmentSize_);
        unsigned clipSamples = workSamples;
        if (stereo_)
            clipSamples <<= 1;
        
        // Clear clip buffer
        memset(clipBuffer_.Get(), 0, clipSamples * sizeof(int));
        int* clipPtr = clipBuffer_.Get();
        
        // Mix samples to clip buffer
        for (PODVector<SoundSource*>::Iterator i = soundSources_.Begin(); i != soundSources_.End(); ++i)
            (*i)->Mix(clipPtr, workSamples, mixRate_, stereo_, interpolation_);
        
        // Copy output from clip buffer to destination
        clipPtr = clipBuffer_.Get();
        short* destPtr = (short*)dest;
        while (clipSamples--)
            *destPtr++ = Clamp(*clipPtr++, -32768, 32767);
        
        samples -= workSamples;
        ((unsigned char*&)destPtr) += sampleSize_ * workSamples;
    }
}

void Audio::HandleRenderUpdate(StringHash eventType, VariantMap& eventData)
{
    using namespace RenderUpdate;
    
    Update(eventData[P_TIMESTEP].GetFloat());
}

void Audio::Release()
{
    Stop();
    
    if (deviceID_)
    {
        MutexLock lock(GetStaticMutex());
        
        SDL_CloseAudioDevice(deviceID_);
        deviceID_ = 0;
        clipBuffer_.Reset();
    }
}

void RegisterAudioLibrary(Context* context)
{
    Sound::RegisterObject(context);
    SoundSource::RegisterObject(context);
    SoundSource3D::RegisterObject(context);
    SoundListener::RegisterObject(context);
}

}
