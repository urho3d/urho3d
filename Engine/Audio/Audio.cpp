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
#include "Profiler.h"
#include "Sound.h"
#include "SoundSource3D.h"
#include "StringUtils.h"

#define DIRECTSOUND_VERSION 0x0800

#include <windows.h>
#include <dsound.h>
#include <mmsystem.h>
#include <process.h>

#include "DebugNew.h"

static const int AUDIO_FPS = 100;

/// Audio implementation. Contains the DirectSound buffer
class AudioImpl
{
    friend class Audio;
    
public:
    /// Construct
    AudioImpl() :
        dsObject_(0),
        dsBuffer_(0)
    {
    }
    
private:
    /// DirectSound interface
    IDirectSound* dsObject_;
    /// DirectSound buffer
    IDirectSoundBuffer* dsBuffer_;
};

OBJECTTYPESTATIC(Audio);

Audio::Audio(Context* context) :
    Object(context),
    impl_(new AudioImpl()),
    playing_(false),
    windowHandle_(0),
    bufferSamples_(0),
    bufferSize_(0),
    sampleSize_(0),
    listenerPosition_(Vector3::ZERO),
    listenerRotation_(Quaternion::IDENTITY)
{
    SubscribeToEvent(E_SCREENMODE, HANDLER(Audio, HandleScreenMode));
    SubscribeToEvent(E_RENDERUPDATE, HANDLER(Audio, HandleRenderUpdate));
    
    for (unsigned i = 0; i < MAX_SOUND_TYPES; ++i)
        masterGain_[i] = 1.0f;
    
    // Try to initialize right now, but skip if screen mode is not yet set
    Initialize();
}

Audio::~Audio()
{
    ReleaseBuffer();
    
    if (impl_->dsObject_)
    {
        impl_->dsObject_->Release();
        impl_->dsObject_ = 0;
    }
    
    delete impl_;
    impl_ = 0;
}

bool Audio::SetMode(int bufferLengthMSec, int mixRate, bool sixteenBit, bool stereo, bool interpolate)
{
    ReleaseBuffer();
    
    if (!impl_->dsObject_)
    {
        if (DirectSoundCreate(0, &impl_->dsObject_, 0) != DS_OK)
        {
            LOGERROR("Could not create DirectSound object");
            return false;
        }
    }
    
    if (impl_->dsObject_->SetCooperativeLevel((HWND)windowHandle_, DSSCL_PRIORITY) != DS_OK)
    {
        LOGERROR("Could not set DirectSound cooperative level");
        return false;
    }
    DSCAPS dsCaps;
    dsCaps.dwSize = sizeof(dsCaps);
    if (impl_->dsObject_->GetCaps(&dsCaps) != DS_OK)
    {
        LOGERROR("Could not get DirectSound capabilities");
        return false;
    }
    
    if (!(dsCaps.dwFlags & (DSCAPS_SECONDARY16BIT|DSCAPS_PRIMARY16BIT)))
        sixteenBit = false;
    if (!(dsCaps.dwFlags & (DSCAPS_SECONDARYSTEREO|DSCAPS_PRIMARYSTEREO)))
        stereo = false;
    
    bufferLengthMSec = Max(bufferLengthMSec, 50);
    mixRate = Clamp(mixRate, 11025, 48000);
    
    WAVEFORMATEX waveFormat;
    waveFormat.wFormatTag = WAVE_FORMAT_PCM;
    waveFormat.nSamplesPerSec = mixRate;
    
    if (sixteenBit)
        waveFormat.wBitsPerSample = 16;
    else
        waveFormat.wBitsPerSample = 8;
    
    if (stereo)
        waveFormat.nChannels = 2;
    else
        waveFormat.nChannels = 1;
    
    unsigned sampleSize = waveFormat.nChannels * waveFormat.wBitsPerSample / 8;
    unsigned numSamples = (bufferLengthMSec * mixRate) / 1000;
    
    waveFormat.nAvgBytesPerSec = mixRate * sampleSize;
    waveFormat.nBlockAlign = sampleSize;
    waveFormat.cbSize = 0;
    
    DSBUFFERDESC bufferDesc;
    memset(&bufferDesc, 0, sizeof(bufferDesc));
    bufferDesc.dwSize = sizeof(bufferDesc);
    bufferDesc.dwFlags = DSBCAPS_STICKYFOCUS;
    bufferDesc.dwBufferBytes = numSamples * sampleSize;
    bufferDesc.lpwfxFormat = &waveFormat;
    
    if (impl_->dsObject_->CreateSoundBuffer(&bufferDesc, &impl_->dsBuffer_, 0) != DS_OK)
    {
        LOGERROR("Could not create DirectSound buffer");
        return false;
    }
    
    clipBuffer_ = new int[numSamples * waveFormat.nChannels];
    bufferSamples_ = numSamples;
    bufferSize_ = numSamples * sampleSize;
    sampleSize_ = sampleSize;
    mixRate_ = mixRate;
    sixteenBit_ = sixteenBit;
    stereo_ = stereo;
    interpolate_ = interpolate;
    
    LOGINFO("Set audio mode " + ToString(mixRate_) + " Hz " + (stereo_ ? "stereo" : "mono") + " " + (sixteenBit_ ? "16-bit" : "8-bit") + " " +
        (interpolate_ ? "interpolated" : ""));
    
    return Play();
}

void Audio::Update(float timeStep)
{
    PROFILE(UpdateAudio);
    
    MutexLock Lock(audioMutex_);
    
    // Update in reverse order, because sound sources might remove themselves
    for (unsigned i = soundSources_.size() - 1; i < soundSources_.size(); --i)
        soundSources_[i]->Update(timeStep);
}

bool Audio::Play()
{
    if (playing_)
        return true;
    
    if (!impl_->dsBuffer_)
    {
        LOGERROR("No audio buffer, can not start playback");
        return false;
    }
    
    // Clear buffer before starting playback
    DWORD bytes1, bytes2;
    void *ptr1, *ptr2;
    unsigned char value = sixteenBit_ ? 0 : 128;
    if (impl_->dsBuffer_->Lock(0, bufferSize_, &ptr1, &bytes1, &ptr2, &bytes2, 0) == DS_OK)
    {
        if (bytes1)
            memset(ptr1, value, bytes1);
        if (bytes2)
            memset(ptr2, value, bytes2);
        impl_->dsBuffer_->Unlock(ptr1, bytes1, ptr2, bytes2);
    }
    
    // Create playback thread
    if (!Start())
    {
        LOGERROR("Could not create audio thread");
        return false;
    }
    
    // Adjust playback thread priority
    SetPriority(THREAD_PRIORITY_ABOVE_NORMAL);
    playing_ = true;
    return true;
}

void Audio::Stop()
{
    Thread::Stop();
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
    for (std::vector<SoundSource*>::iterator i = soundSources_.begin(); i != soundSources_.end(); ++i)
    {
        if ((*i)->GetSound() == soundClip)
            (*i)->Stop();
    }
}

bool Audio::IsInitialized() const
{
    return impl_->dsBuffer_ != 0;
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
    
    soundSources_.push_back(channel);
}

void Audio::RemoveSoundSource(SoundSource* channel)
{
    MutexLock Lock(audioMutex_);
    
    for (std::vector<SoundSource*>::iterator i = soundSources_.begin(); i != soundSources_.end(); ++i)
    {
        if (*i == channel)
        {
            soundSources_.erase(i);
            return;
        }
    }
}

void Audio::ThreadFunction()
{
    AudioImpl* impl = impl_;
    
    DWORD playCursor = 0;
    DWORD writeCursor = 0;
    
    while (shouldRun_)
    {
        Timer audioUpdateTimer;
        
        // Restore buffer / restart playback if necessary
        DWORD status;
        impl->dsBuffer_->GetStatus(&status);
        if (status == DSBSTATUS_BUFFERLOST)
        {
            impl->dsBuffer_->Restore();
            impl->dsBuffer_->GetStatus(&status);
        }
        if (!(status & DSBSTATUS_PLAYING))
        {
            impl->dsBuffer_->Play(0, 0, DSBPLAY_LOOPING);
            writeCursor = 0;
        }
        
        // Get current buffer position
        impl->dsBuffer_->GetCurrentPosition(&playCursor, 0);
        playCursor %= bufferSize_;
        playCursor &= -((int)sampleSize_);
        
        if (playCursor != writeCursor)
        {
            int writeBytes = playCursor - writeCursor;
            if (writeBytes < 0)
                writeBytes += bufferSize_;
            
            // Try to lock buffer
            DWORD bytes1, bytes2;
            void *ptr1, *ptr2;
            if (impl->dsBuffer_->Lock(writeCursor, writeBytes, &ptr1, &bytes1, &ptr2, &bytes2, 0) == DS_OK)
            {
                // Mix sound to locked positions
                {
                    MutexLock Lock(audioMutex_);
                    
                    if (bytes1)
                        MixOutput(ptr1, bytes1);
                    if (bytes2)
                        MixOutput(ptr2, bytes2);
                }
                
                // Unlock buffer and update write cursor
                impl->dsBuffer_->Unlock(ptr1, bytes1, ptr2, bytes2);
                writeCursor += writeBytes;
                if (writeCursor >= bufferSize_)
                    writeCursor -= bufferSize_;
            }
        }
        
        // Sleep the remaining time of the audio update period
        int audioSleepTime = Max(1000 / AUDIO_FPS - (int)audioUpdateTimer.GetMSec(false), 0);
        Sleep(audioSleepTime);
    }
    
    impl->dsBuffer_->Stop();
}

void Audio::Initialize()
{
    Graphics* graphics = GetSubsystem<Graphics>();
    if ((!graphics) || (!graphics->IsInitialized()))
        return;
    
    windowHandle_ = graphics->GetWindowHandle();
}

void Audio::MixOutput(void *dest, unsigned bytes)
{
    unsigned mixSamples = bytes;
    unsigned clipSamples = bytes;
    
    if (stereo_)
        mixSamples >>= 1;
    
    if (sixteenBit_)
    {
        clipSamples >>= 1;
        mixSamples >>= 1;
    }
    
    // Clear clip buffer
    memset(clipBuffer_.GetPtr(), 0, clipSamples * sizeof(int));
    int* clipPtr = clipBuffer_.GetPtr();
    
    // Mix samples to clip buffer
    for (std::vector<SoundSource*>::iterator i = soundSources_.begin(); i != soundSources_.end(); ++i)
        (*i)->Mix(clipPtr, mixSamples, mixRate_, stereo_, interpolate_);
    
    // Copy output from clip buffer to destination
    clipPtr = clipBuffer_.GetPtr();
    if (sixteenBit_)
    {
        short* destPtr = (short*)dest;
        while (clipSamples--)
            *destPtr++ = Clamp(*clipPtr++, -32768, 32767);
    }
    else
    {
        unsigned char* destPtr = (unsigned char*)dest;
        while (clipSamples--)
            *destPtr++ = Clamp(((*clipPtr++) >> 8) + 128, 0, 255);
    }
}

void Audio::ReleaseBuffer()
{
    Stop();
    
    if (impl_->dsBuffer_)
    {
        impl_->dsBuffer_->Release();
        impl_->dsBuffer_ = 0;
    }
}

void Audio::HandleScreenMode(StringHash eventType, VariantMap& eventData)
{
    if (!windowHandle_)
        Initialize();
}

void Audio::HandleRenderUpdate(StringHash eventType, VariantMap& eventData)
{
    using namespace RenderUpdate;
    
    Update(eventData[P_TIMESTEP].GetFloat());
}

void RegisterAudioLibrary(Context* context)
{
    Sound::RegisterObject(context);
    SoundSource::RegisterObject(context);
    SoundSource3D::RegisterObject(context);
}
