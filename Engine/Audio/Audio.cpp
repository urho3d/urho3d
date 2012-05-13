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
#include "CoreEvents.h"
#include "Graphics.h"
#include "GraphicsEvents.h"
#include "Log.h"
#include "Mutex.h"
#include "ProcessUtils.h"
#include "Profiler.h"
#include "Sound.h"
#include "SoundSource3D.h"

#ifndef USE_OPENGL
#define DIRECTSOUND_VERSION 0x0800

#include "Thread.h"
#include "Timer.h"

#include <windows.h>
#include <mmsystem.h>
#include <dsound.h>
#else
#include <SDL.h>
#endif

#include "DebugNew.h"

static const int MIN_BUFFERLENGTH = 20;
static const int MIN_MIXRATE = 11025;
static const int MAX_MIXRATE = 48000;
static const int AUDIO_FPS = 100;

#ifdef USE_OPENGL
static unsigned numInstances = 0;

static void SDLAudioCallback(void *userdata, Uint8 *stream, int len);
#else
/// DirectSound audio output stream.
class AudioStream : public Thread
{
public:
    /// Construct.
    AudioStream(Audio* owner) :
        owner_(owner),
        dsObject_(0),
        dsBuffer_(0)
    {
    }
    
    /// Destruct.
    ~AudioStream()
    {
        Close();
        
        if (dsObject_)
        {
            dsObject_->Release();
            dsObject_ = 0;
        }
    }
    
    /// Create the DirectSound buffer.
    bool Open(unsigned windowHandle, int bufferLengthMSec, int mixRate, bool stereo)
    {
        Close();
        
        if (!dsObject_)
        {
            if (DirectSoundCreate(0, &dsObject_, 0) != DS_OK)
                return false;
        }
        
        if (dsObject_->SetCooperativeLevel((HWND)windowHandle, DSSCL_PRIORITY) != DS_OK)
            return false;
        
        WAVEFORMATEX waveFormat;
        waveFormat.wFormatTag = WAVE_FORMAT_PCM;
        waveFormat.nSamplesPerSec = mixRate;
        waveFormat.wBitsPerSample = 16;
        
        if (stereo)
            waveFormat.nChannels = 2;
        else
            waveFormat.nChannels = 1;
        
        sampleSize_ = waveFormat.nChannels * waveFormat.wBitsPerSample / 8;
        unsigned numSamples = (bufferLengthMSec * mixRate) / 1000;
        
        waveFormat.nAvgBytesPerSec = mixRate * sampleSize_;
        waveFormat.nBlockAlign = sampleSize_;
        waveFormat.cbSize = 0;
        
        DSBUFFERDESC bufferDesc;
        memset(&bufferDesc, 0, sizeof(bufferDesc));
        bufferDesc.dwSize = sizeof(bufferDesc);
        bufferDesc.dwFlags = DSBCAPS_STICKYFOCUS;
        bufferDesc.dwBufferBytes = numSamples * sampleSize_;
        bufferDesc.lpwfxFormat = &waveFormat;
        bufferSize_ = bufferDesc.dwBufferBytes;
        
        return dsObject_->CreateSoundBuffer(&bufferDesc, &dsBuffer_, 0) == DS_OK;
    }
    
    /// Destroy the DirectSound buffer.
    void Close()
    {
        StopPlayback();
        
        if (dsBuffer_)
        {
            dsBuffer_->Release();
            dsBuffer_ = 0;
        }
    }
    
    /// Start playback.
    bool StartPlayback()
    {
        if (IsStarted())
            return true;
        if (!dsBuffer_)
            return false;
        
        // Clear the buffer before starting playback
        DWORD bytes1, bytes2;
        void *ptr1, *ptr2;
        if (dsBuffer_->Lock(0, bufferSize_, &ptr1, &bytes1, &ptr2, &bytes2, 0) == DS_OK)
        {
            if (bytes1)
                memset(ptr1, 0, bytes1);
            if (bytes2)
                memset(ptr2, 0, bytes2);
            dsBuffer_->Unlock(ptr1, bytes1, ptr2, bytes2);
        }
        
        if (Start())
        {
            SetPriority(THREAD_PRIORITY_ABOVE_NORMAL);
            return true;
        }
        else
            return false;
    }
    
    /// Stop playback.
    void StopPlayback()
    {
        if (dsBuffer_ && IsStarted())
            Stop();
    }
    
    /// Mixing thread function.
    void ThreadFunction()
    {
        DWORD playCursor = 0;
        DWORD writeCursor = 0;
        
        while (shouldRun_)
        {
            Timer audioUpdateTimer;
            
            // Restore buffer / restart playback if necessary
            DWORD status;
            dsBuffer_->GetStatus(&status);
            if (status == DSBSTATUS_BUFFERLOST)
            {
                dsBuffer_->Restore();
                dsBuffer_->GetStatus(&status);
            }
            if (!(status & DSBSTATUS_PLAYING))
            {
                dsBuffer_->Play(0, 0, DSBPLAY_LOOPING);
                writeCursor = 0;
            }
            
            // Get current buffer position
            dsBuffer_->GetCurrentPosition(&playCursor, 0);
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
                if (dsBuffer_->Lock(writeCursor, writeBytes, &ptr1, &bytes1, &ptr2, &bytes2, 0) == DS_OK)
                {
                    // Mix sound to locked positions
                    {
                        MutexLock lock(owner_->GetMutex());
                        if (bytes1)
                            owner_->MixOutput(ptr1, bytes1 / sampleSize_);
                        if (bytes2)
                            owner_->MixOutput(ptr2, bytes2 / sampleSize_);
                    }
                    
                    // Unlock buffer and update write cursor
                    dsBuffer_->Unlock(ptr1, bytes1, ptr2, bytes2);
                    writeCursor += writeBytes;
                    if (writeCursor >= bufferSize_)
                        writeCursor -= bufferSize_;
                }
            }
            
            // Sleep the remaining time of the audio update period
            int audioSleepTime = Max(1000 / AUDIO_FPS - (int)audioUpdateTimer.GetMSec(false), 0);
            Sleep(audioSleepTime);
        }
        
        dsBuffer_->Stop();
    }
    
private:
    /// Audio subsystem.
    Audio* owner_;
    /// DirectSound interface.
    IDirectSound* dsObject_;
    /// DirectSound buffer.
    IDirectSoundBuffer* dsBuffer_;
    /// Sound buffer size in bytes.
    unsigned bufferSize_;
    /// Sound buffer sample size.
    unsigned sampleSize_;
    /// Playing flag.
    bool playing_;
};
#endif

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
    
    // Initialize SDL audio under static mutex in case this is the first instance
    #ifdef USE_OPENGL
    {
        MutexLock lock(GetStaticMutex());
        
        if (!numInstances)
            SDL_InitSubSystem(SDL_INIT_AUDIO);
        ++numInstances;
    }
    #endif
}

Audio::~Audio()
{
    Release();
    
    // Uninitialize SDL audio under static mutex in case this is the last instance
    #ifdef USE_OPENGL
    {
        MutexLock lock(GetStaticMutex());
        
        --numInstances;
        if (!numInstances)
            SDL_QuitSubSystem(SDL_INIT_AUDIO);
    }
    #else
    delete (AudioStream*)stream_;
    stream_ = 0;
    #endif
}

bool Audio::SetMode(int bufferLengthMSec, int mixRate, bool stereo, bool interpolation)
{
    Release();
    
    bufferLengthMSec = Max(bufferLengthMSec, MIN_BUFFERLENGTH);
    mixRate = Clamp(mixRate, MIN_MIXRATE, MAX_MIXRATE);
    
    // Guarantee a fragment size that is low enough so that Vorbis decoding buffers do not wrap
    fragmentSize_ = NextPowerOfTwo(mixRate >> 6);
    
    #ifdef USE_OPENGL
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
    
    stream_ = SDL_OpenAudioDevice(0, SDL_FALSE, &desired, &obtained, SDL_AUDIO_ALLOW_ANY_CHANGE);
    if (!stream_)
    {
        LOGERROR("Could not initialize audio output");
        return false;
    }
    if (obtained.format != AUDIO_S16SYS && obtained.format != AUDIO_S16LSB && obtained.format != AUDIO_S16MSB)
    {
        LOGERROR("Could not initialize audio output, 16-bit buffer format not supported");
        SDL_CloseAudioDevice(stream_);
        stream_ = 0;
        return false;
    }
    
    if (obtained.channels == 2)
        stereo_ = true;
    
    fragmentSize_ = obtained.samples;
    #else
    if (!stream_)
        stream_ = new AudioStream(this);
    
    unsigned windowHandle = 0;
    Graphics* graphics = GetSubsystem<Graphics>();
    if (graphics)
        windowHandle = graphics->GetWindowHandle();
    
    if (!((AudioStream*)stream_)->Open(windowHandle, bufferLengthMSec, mixRate, stereo))
    {
        LOGERROR("Failed to open audio stream");
        return false;
    }
    
    #endif
    
    clipBuffer_ = new int[stereo ? fragmentSize_ << 1 : fragmentSize_];
    sampleSize_ = sizeof(short);
    if (stereo)
        sampleSize_ <<= 1;
    
    mixRate_ = mixRate;
    stereo_ = stereo;
    interpolation_ = interpolation;
    
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
    
    if (!stream_)
    {
        LOGERROR("No audio mode set, can not start playback");
        return false;
    }
    
    #ifdef USE_OPENGL
    if (!clipBuffer_)
    {
        LOGERROR("No audio buffer, can not start playback");
        return false;
    }
    SDL_PauseAudioDevice(stream_, 0);
    #else
    if (!((AudioStream*)stream_)->StartPlayback())
    {
        LOGERROR("Failed to start playback");
        return false;
    }
    #endif
    
    playing_ = true;
    return true;
}

void Audio::Stop()
{
    if (!playing_)
        return;
    
    #ifdef USE_OPENGL
    SDL_PauseAudioDevice(stream_, 1);
    #else
    if (stream_)
        ((AudioStream*)stream_)->StopPlayback();
    #endif
    
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

#ifdef USE_OPENGL

void SDLAudioCallback(void *userdata, Uint8* stream, int len)
{
    Audio* audio = static_cast<Audio*>(userdata);
    
    {
        MutexLock Lock(audio->GetMutex());
        audio->MixOutput(stream, len / audio->GetSampleSize());
    }
}
#endif

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
    
    if (stream_)
    {
        #ifdef USE_OPENGL
        if (clipBuffer_)
        {
            SDL_CloseAudioDevice(stream_);
            stream_ = 0;
            clipBuffer_.Reset();
        }
        #else
        ((AudioStream*)stream_)->Close();
        #endif
        
        clipBuffer_.Reset();
    }
}

void RegisterAudioLibrary(Context* context)
{
    Sound::RegisterObject(context);
    SoundSource::RegisterObject(context);
    SoundSource3D::RegisterObject(context);
}
