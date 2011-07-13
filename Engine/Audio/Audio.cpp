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

#include "Precompiled.h"
#include "Audio.h"
#include "Context.h"
#include "CoreEvents.h"
#include "Graphics.h"
#include "GraphicsEvents.h"
#include "Log.h"
#include "ProcessUtils.h"
#include "Profiler.h"
#include "Sound.h"
#include "SoundSource3D.h"

#include <portaudio.h>

#include "DebugNew.h"

static const int MIN_BUFFERLENGTH = 20;
static const int MIN_MIXRATE = 11025;
static const int MAX_MIXRATE = 48000;

static unsigned numInstances = 0;

static int AudioCallback(const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer,
    const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void *userData);

OBJECTTYPESTATIC(Audio);

Audio::Audio(Context* context) :
    Object(context),
    stream_(0),
    sampleSize_(0),
    playing_(false),
    listenerPosition_(Vector3::ZERO),
    listenerRotation_(Quaternion::IDENTITY)
{
    SubscribeToEvent(E_RENDERUPDATE, HANDLER(Audio, HandleRenderUpdate));
    
    for (unsigned i = 0; i < MAX_SOUND_TYPES; ++i)
        masterGain_[i] = 1.0f;
    
    // Initialize PortAudio under static mutex in case this is the first instance
    {
        MutexLock lock(GetStaticMutex());
        if (!numInstances)
        {
            if (Pa_Initialize() != paNoError)
                LOGERROR("Could not initialize PortAudio");
        }
        ++numInstances;
    }
}

Audio::~Audio()
{
    Release();
    
    // Uninitialize PortAudio under static mutex in case this is the last instance
    {
        MutexLock lock(GetStaticMutex());
        
        --numInstances;
        if (!numInstances)
            Pa_Terminate();
    }
}

bool Audio::SetMode(int bufferLengthMSec, int mixRate, bool stereo, bool interpolate)
{
    Release();
    
    bufferLengthMSec = Max(bufferLengthMSec, MIN_BUFFERLENGTH);
    mixRate = Clamp(mixRate, MIN_MIXRATE, MAX_MIXRATE);
    
    // Guarantee a fragment size that is low enough so that Vorbis decoding buffers do not wrap
    unsigned fragmentSize = NextPowerOfTwo(mixRate >> 6);
    
    PaStreamParameters outputParams;
    outputParams.device = Pa_GetDefaultOutputDevice();
    outputParams.channelCount = stereo ? 2 : 1;
    outputParams.sampleFormat = paInt16;
    outputParams.suggestedLatency = bufferLengthMSec / 1000.0;
    outputParams.hostApiSpecificStreamInfo = 0;
    
    if (Pa_OpenStream(&stream_, 0, &outputParams, mixRate, fragmentSize, 0, AudioCallback, this) != paNoError)
    {
        LOGERROR("Failed to open audio stream");
        return false;
    }
    
    sampleSize_ = sizeof(short);
    if (stereo)
        sampleSize_ <<= 1;
    
    // Allocate the clipping buffer
    clipBuffer_ = new int[stereo ? fragmentSize << 1 : fragmentSize];
    
    mixRate_ = mixRate;
    stereo_ = stereo;
    interpolate_ = interpolate;
    
    LOGINFO("Set audio mode " + String(mixRate_) + " Hz " + (stereo_ ? "stereo" : "mono") + " " +
        (interpolate_ ? "interpolated" : ""));
    
    return Play();
}

void Audio::Update(float timeStep)
{
    PROFILE(UpdateAudio);
    
    MutexLock Lock(audioMutex_);
    
    // Update in reverse order, because sound sources might remove themselves
    for (unsigned i = soundSources_.Size() - 1; i < soundSources_.Size(); --i)
        soundSources_[i]->Update(timeStep);
}

bool Audio::Play()
{
    if (playing_)
        return true;
    
    if (!stream_)
    {
        LOGERROR("No audio mode set, can not start playback");
        return false;
    }
    
    if (Pa_StartStream(stream_) != paNoError)
    {
        LOGERROR("Failed to start playback");
        return false;
    }
    
    playing_ = true;
    return true;
}

void Audio::Stop()
{
    if (!stream_ || !playing_)
        return;
    
    Pa_StopStream(stream_);
    playing_ = false;
}

void Audio::SetMasterGain(SoundType type, float gain)
{
    if (type >= MAX_SOUND_TYPES)
        return;
    
    masterGain_[type] = Clamp(gain, 0.0f, 1.0f);
}

void Audio::SetListenerPosition(const Vector3& position)
{
    listenerPosition_ = position;
}

void Audio::SetListenerRotation(const Quaternion& rotation)
{
    listenerRotation_ = rotation;
}

void Audio::SetListenerTransform(const Vector3& position, const Quaternion& rotation)
{
    listenerPosition_ = position;
    listenerRotation_ = rotation;
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

void Audio::AddSoundSource(SoundSource* channel)
{
    MutexLock Lock(audioMutex_);
    
    soundSources_.Push(channel);
}

void Audio::RemoveSoundSource(SoundSource* channel)
{
    MutexLock Lock(audioMutex_);
    
    for (PODVector<SoundSource*>::Iterator i = soundSources_.Begin(); i != soundSources_.End(); ++i)
    {
        if (*i == channel)
        {
            soundSources_.Erase(i);
            return;
        }
    }
}

int AudioCallback(const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo*
    timeInfo, PaStreamCallbackFlags statusFlags, void *userData)
{
    Audio* audio = static_cast<Audio*>(userData);
    
    {
        MutexLock Lock(audio->GetMutex());
        audio->MixOutput(outputBuffer, framesPerBuffer);
    }
    
    return 0;
}

void Audio::MixOutput(void *dest, unsigned mixSamples)
{
    unsigned clipSamples = mixSamples;
    if (stereo_)
        clipSamples <<= 1;
    
    // Clear clip buffer
    memset(clipBuffer_.RawPtr(), 0, clipSamples * sizeof(int));
    int* clipPtr = clipBuffer_.RawPtr();
    
    // Mix samples to clip buffer
    for (PODVector<SoundSource*>::Iterator i = soundSources_.Begin(); i != soundSources_.End(); ++i)
        (*i)->Mix(clipPtr, mixSamples, mixRate_, stereo_, interpolate_);
    
    // Copy output from clip buffer to destination
    clipPtr = clipBuffer_.RawPtr();
    short* destPtr = (short*)dest;
    while (clipSamples--)
        *destPtr++ = Clamp(*clipPtr++, -32768, 32767);
}

void Audio::HandleRenderUpdate(StringHash eventType, VariantMap& eventData)
{
    using namespace RenderUpdate;
    
    Update(eventData[P_TIMESTEP].GetFloat());
}

void Audio::Release()
{
    Stop();
    
    if (stream_)
    {
        Pa_CloseStream(stream_);
        
        stream_ = 0;
        clipBuffer_.Reset();
    }
}

void RegisterAudioLibrary(Context* context)
{
    Sound::RegisterObject(context);
    SoundSource::RegisterObject(context);
    SoundSource3D::RegisterObject(context);
}
