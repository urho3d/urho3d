//
// Copyright (c) 2008-2015 the Urho3D project.
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

#include "../Audio/Audio.h"
#include "../Core/Context.h"
#include "../Core/CoreEvents.h"
#include "../IO/Log.h"
#include "../Core/Mutex.h"
#include "../Core/ProcessUtils.h"
#include "../Core/Profiler.h"
#include "../Audio/Sound.h"
#include "../Audio/SoundListener.h"
#include "../Audio/SoundSource3D.h"

#include <SDL/SDL.h>

#include "../DebugNew.h"

namespace Urho3D
{

const char* AUDIO_CATEGORY = "Audio";

static const int MIN_BUFFERLENGTH = 20;
static const int MIN_MIXRATE = 11025;
static const int MAX_MIXRATE = 48000;
static const StringHash SOUND_MASTER_HASH("MASTER");

static void SDLAudioCallback(void *userdata, Uint8 *stream, int len);

Audio::Audio(Context* context) :
    Object(context),
    deviceID_(0),
    sampleSize_(0),
    playing_(false)
{
    // Set the master to the default value
    masterGain_[SOUND_MASTER_HASH] = 1.0f;
    
    // Register Audio library object factories
    RegisterAudioLibrary(context_);
    
    SubscribeToEvent(E_RENDERUPDATE, HANDLER(Audio, HandleRenderUpdate));
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
    
    SDL_AudioSpec desired;
    SDL_AudioSpec obtained;
    
    desired.freq = mixRate;
    desired.format = AUDIO_S16SYS;
    desired.channels = stereo ? 2 : 1;
    desired.callback = SDLAudioCallback;
    desired.userdata = this;
    
    // SDL uses power of two audio fragments. Determine the closest match
    int bufferSamples = mixRate * bufferLengthMSec / 1000;
    desired.samples = NextPowerOfTwo(bufferSamples);
    if (Abs((int)desired.samples / 2 - bufferSamples) < Abs((int)desired.samples - bufferSamples))
        desired.samples /= 2;
    
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
    
    stereo_ = obtained.channels == 2;
    sampleSize_ = stereo_ ? sizeof(int) : sizeof(short);
    // Guarantee a fragment size that is low enough so that Vorbis decoding buffers do not wrap
    fragmentSize_ = Min((int)NextPowerOfTwo(mixRate >> 6), (int)obtained.samples);
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

void Audio::SetMasterGain(const String& type, float gain)
{
    masterGain_[type] = Clamp(gain, 0.0f, 1.0f);

    for (PODVector<SoundSource*>::Iterator i = soundSources_.Begin(); i != soundSources_.End(); ++i)
        (*i)->UpdateMasterGain();
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

float Audio::GetMasterGain(const String& type) const
{
    // By definition previously unknown types return full volume
    HashMap<StringHash, Variant>::ConstIterator findIt = masterGain_.Find(type);
    if (findIt == masterGain_.End())
        return 1.0f;

    return findIt->second_.GetFloat();
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

float Audio::GetSoundSourceMasterGain(StringHash typeHash) const
{
    HashMap<StringHash, Variant>::ConstIterator masterIt = masterGain_.Find(SOUND_MASTER_HASH);

    if (!typeHash)
        return masterIt->second_.GetFloat();

    HashMap<StringHash, Variant>::ConstIterator typeIt = masterGain_.Find(typeHash);

    if (typeIt == masterGain_.End() || typeIt == masterIt)
        return masterIt->second_.GetFloat();

    return masterIt->second_.GetFloat() * typeIt->second_.GetFloat();
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
        int* clipPtr = clipBuffer_.Get();
        memset(clipPtr, 0, clipSamples * sizeof(int));
        
        // Mix samples to clip buffer
        for (PODVector<SoundSource*>::Iterator i = soundSources_.Begin(); i != soundSources_.End(); ++i)
            (*i)->Mix(clipPtr, workSamples, mixRate_, stereo_, interpolation_);
        
        // Copy output from clip buffer to destination
        short* destPtr = (short*)dest;
        while (clipSamples--)
            *destPtr++ = Clamp(*clipPtr++, -32768, 32767);
        
        samples -= workSamples;
        ((unsigned char*&)dest) += sampleSize_ * workSamples;
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
