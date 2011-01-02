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
#include "Channel.h"
#include "Log.h"
#include "Song.h"
#include "Sound.h"
#include "StringUtils.h"

#define DIRECTSOUND_VERSION 0x0800

#include <windows.h>
#include <dsound.h>
#include <mmsystem.h>
#include <process.h>

#include "DebugNew.h"

static Audio* instance = 0;

//! Holds the DirectSound buffer and audio thread handle
class AudioImpl
{
    friend class Audio;
    
public:
    //! Construct with a window handle
    AudioImpl(HWND windowHandle) :
        mDSObject(0),
        mDSBuffer(0),
        mAudioThread(0),
        mWindow(windowHandle)
    {
    }

private:
    //! DirectSound interface
    IDirectSound* mDSObject;
    //! DirectSound buffer
    IDirectSoundBuffer* mDSBuffer;
    //! Audio thread handle
    HANDLE mAudioThread;
    //! Window handle
    HWND mWindow;
    
    //! Runs the audio mixing loop
    static DWORD WINAPI threadFunction(void* data);
};

Audio::Audio(unsigned windowHandle) :
    mImpl(0),
    mPlaying(false),
    mBufferSamples(0),
    mBufferSize(0),
    mSampleSize(0),
    mListenerPosition(Vector3::sZero),
    mListenerRotation(Quaternion::sIdentity)
{
    if (instance)
        EXCEPTION("Audio already exists");
    
    LOGINFO("Audio created");
    
    mImpl = new AudioImpl((HWND)windowHandle);
    
    for (unsigned i = 0; i < MAX_CHANNEL_TYPES; ++i)
        mMasterGain[i] = 1.0f;
    
    instance = this;
}

Audio::~Audio()
{
    releaseBuffer();
    
    if (mImpl->mDSObject)
    {
        mImpl->mDSObject->Release();
        mImpl->mDSObject = 0;
    }
    
    delete mImpl;
    mImpl = 0;
    
    LOGINFO("Audio shut down");
    
    if (instance == this)
        instance = 0;
}

bool Audio::setMode(int bufferLengthMSec, int mixRate, bool sixteenBit, bool stereo, bool interpolate)
{
    releaseBuffer();
    
    if (mImpl->mWindow == INVALID_HANDLE_VALUE)
        return false;
    
    if (!mImpl->mDSObject)
    {
        if (DirectSoundCreate(0, &mImpl->mDSObject, 0) != DS_OK)
        {
            LOGERROR("Could not create DirectSound object");
            return false;
        }
    }
    
    if (mImpl->mDSObject->SetCooperativeLevel(mImpl->mWindow, DSSCL_PRIORITY) != DS_OK)
    {
        LOGERROR("Could not set DirectSound cooperative level");
        return false;
    }
    DSCAPS dsCaps;
    dsCaps.dwSize = sizeof(dsCaps);
    if (mImpl->mDSObject->GetCaps(&dsCaps) != DS_OK)
    {
        LOGERROR("Could not get DirectSound capabilities");
        return false;
    }
    
    if (!(dsCaps.dwFlags & (DSCAPS_SECONDARY16BIT|DSCAPS_PRIMARY16BIT)))
        sixteenBit = false;
    if (!(dsCaps.dwFlags & (DSCAPS_SECONDARYSTEREO|DSCAPS_PRIMARYSTEREO)))
        stereo = false;
    
    bufferLengthMSec = max(bufferLengthMSec, 50);
    mixRate = clamp(mixRate, 11025, 48000);
    
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
    unsigned numSounds = (bufferLengthMSec * mixRate) / 1000;
    
    waveFormat.nAvgBytesPerSec = mixRate * sampleSize;
    waveFormat.nBlockAlign = sampleSize;
    waveFormat.cbSize = 0;
    
    DSBUFFERDESC bufferDesc;
    memset(&bufferDesc, 0, sizeof(bufferDesc));
    bufferDesc.dwSize = sizeof(bufferDesc);
    bufferDesc.dwFlags = DSBCAPS_STICKYFOCUS;
    bufferDesc.dwBufferBytes = numSounds * sampleSize;
    bufferDesc.lpwfxFormat = &waveFormat;
    
    if (mImpl->mDSObject->CreateSoundBuffer(&bufferDesc, &mImpl->mDSBuffer, 0) != DS_OK)
    {
        LOGERROR("Could not create DirectSound buffer");
        return false;
    }
    
    mClipBuffer = new int[numSounds * waveFormat.nChannels];
    mBufferSamples = numSounds;
    mBufferSize = numSounds * sampleSize;
    mSampleSize = sampleSize;
    mMixRate = mixRate;
    mSixteenBit = sixteenBit;
    mStereo = stereo;
    mInterpolate = interpolate;
    
    LOGINFO("Set audio mode " + toString(mMixRate) + " Hz " + (mStereo ? "stereo" : "mono") + " " + (mSixteenBit ? "16-bit" : "8-bit") + " " +
        (mInterpolate ? "interpolated" : ""));
    
    return play();
}

void Audio::update(float timeStep)
{
    MutexLock lock(mAudioMutex);
    
    // Update in reverse order, because channels might remove themselves
    for (unsigned i = mChannels.size() - 1; i < mChannels.size(); --i)
        mChannels[i]->update(timeStep);
}

bool Audio::play()
{
    if (mImpl->mAudioThread)
        return true;
    
    if (!mImpl->mDSBuffer)
    {
        LOGERROR("No audio buffer, can not start playback");
        return false;
    }
    
    // Clear buffer before starting playback
    DWORD bytes1, bytes2;
    void *ptr1, *ptr2;
    unsigned char value = mSixteenBit ? 0 : 128;
    if (mImpl->mDSBuffer->Lock(0, mBufferSize, &ptr1, &bytes1, &ptr2, &bytes2, 0) == DS_OK)
    {
        if (bytes1)
            memset(ptr1, value, bytes1);
        if (bytes2)
            memset(ptr2, value, bytes2);
        mImpl->mDSBuffer->Unlock(ptr1, bytes1, ptr2, bytes2);
    }
    
    // Create thread for playback
    mPlaying = true;
    
    mImpl->mAudioThread = CreateThread(0, 0, AudioImpl::threadFunction, this, 0, 0);
    if (!mImpl->mAudioThread)
    {
        LOGERROR("Could not create audio thread");
        mPlaying = false;
        return false;
    }
    
    // Set thread priority
    SetThreadPriority(mImpl->mAudioThread, THREAD_PRIORITY_ABOVE_NORMAL);
    return true;
}

void Audio::stop()
{
    mPlaying = false;
    
    if (mImpl->mAudioThread)
    {
        WaitForSingleObject(mImpl->mAudioThread, INFINITE);
        CloseHandle(mImpl->mAudioThread);
        mImpl->mAudioThread = 0;
    }
}

void Audio::setMasterGain(ChannelType type, float gain)
{
    if (type >= MAX_CHANNEL_TYPES)
        return;
    
    mMasterGain[type] = clamp(gain, 0.0f, 1.0f);
}

void Audio::setListenerPosition(const Vector3& position)
{
    mListenerPosition = position;
}

void Audio::setListenerRotation(const Quaternion& rotation)
{
    mListenerRotation = rotation;
}

void Audio::setListenerTransform(const Vector3& position, const Quaternion& rotation)
{
    mListenerPosition = position;
    mListenerRotation = rotation;
}

void Audio::stopSound(Sound* sound)
{
    for (std::vector<Channel*>::iterator i = mChannels.begin(); i != mChannels.end(); ++i)
    {
        if ((*i)->getSound() == sound)
            (*i)->stop();
    }
}

bool Audio::hasBuffer() const
{
    return mImpl->mDSBuffer != 0;
}

float Audio::getMasterGain(ChannelType type) const
{
    if (type >= MAX_CHANNEL_TYPES)
        return 0.0f;
    
    return mMasterGain[type];
}


void Audio::addChannel(Channel* channel)
{
    MutexLock lock(mAudioMutex);
    
    mChannels.push_back(channel);
}

void Audio::removeChannel(Channel* channel)
{
    MutexLock lock(mAudioMutex);
    
    for (std::vector<Channel*>::iterator i = mChannels.begin(); i != mChannels.end(); ++i)
    {
        if (*i == channel)
        {
            mChannels.erase(i);
            return;
        }
    }
}

void Audio::addSong(Song* song)
{
    MutexLock lock(mAudioMutex);
    
    mSongs.push_back(song);
}

void Audio::removeSong(Song* song)
{
    MutexLock lock(mAudioMutex);
    
    for (std::vector<Song*>::iterator i = mSongs.begin(); i != mSongs.end(); ++i)
    {
        if (*i == song)
        {
            mSongs.erase(i);
            return;
        }
    }
}

void Audio::releaseBuffer()
{
    stop();
    
    if (mImpl->mDSBuffer)
    {
        mImpl->mDSBuffer->Release();
        mImpl->mDSBuffer = 0;
    }
}

void Audio::mixOutput(void *dest, unsigned bytes)
{
    unsigned mixSounds = bytes;
    unsigned clipSounds = bytes;
    
    if (mStereo)
        mixSounds >>= 1;
    
    if (mSixteenBit)
    {
        clipSounds >>= 1;
        mixSounds >>= 1;
    }
    
    // Clear clip buffer
    memset(mClipBuffer.getPtr(), 0, clipSounds * sizeof(int));
    int* clipPtr = mClipBuffer.getPtr();
    
    // Mix samples to clip buffer / call players as necessary
    while (mixSounds)
    {
        unsigned samplesUntilPlay = mixSounds;
        
        // See which song's tempo counter will expire soonest
        for (std::vector<Song*>::iterator i = mSongs.begin(); i != mSongs.end(); ++i)
        {
            Song* song = *i;
            if (!song->getSampleCount())
                song->update();
            if (song->getSampleCount() < samplesUntilPlay)
                samplesUntilPlay = song->getSampleCount();
        }
        
        // Mix channels until next player call
        for (std::vector<Channel*>::iterator i = mChannels.begin(); i != mChannels.end(); ++i)
            (*i)->mix(clipPtr, samplesUntilPlay, mMixRate, mStereo, mInterpolate);
        
        mixSounds -= samplesUntilPlay;
        if (mStereo)
            clipPtr += samplesUntilPlay * 2;
        else
            clipPtr += samplesUntilPlay;
        
        for (std::vector<Song*>::iterator i = mSongs.begin(); i != mSongs.end(); ++i)
            (*i)->decSampleCount(samplesUntilPlay);
    }
    
    // Copy output from clip buffer to destination
    clipPtr = mClipBuffer.getPtr();
    if (mSixteenBit)
    {
        short* destPtr = (short*)dest;
        while (clipSounds--)
        {
            int sample = *clipPtr++;
            if (sample > 32767) sample = 32767;
            if (sample < -32768) sample = -32768;
            *destPtr++ = sample;
        }
    }
    else
    {
        unsigned char* destPtr = (unsigned char*)dest;
        while (clipSounds--)
        {
            int sample = ((*clipPtr++) >> 8) + 128;
            if (sample > 255) sample = 255;
            if (sample < 0) sample = 0;
            *destPtr++ = sample;
        }
    }
}

DWORD WINAPI AudioImpl::threadFunction(void* data)
{
    Audio* audio = (Audio*)data;
    AudioImpl* impl = audio->getImpl();
    
    DWORD playCursor = 0;
    DWORD writeCursor = 0;
    
    while (audio->isPlaying())
    {
        // Restore buffer / restart playback if necessary
        DWORD status;
        impl->mDSBuffer->GetStatus(&status);
        if (status == DSBSTATUS_BUFFERLOST)
        {
            impl->mDSBuffer->Restore();
            impl->mDSBuffer->GetStatus(&status);
        }
        if (!(status & DSBSTATUS_PLAYING))
        {
            impl->mDSBuffer->Play(0, 0, DSBPLAY_LOOPING);
            writeCursor = 0;
        }
        
        // Get current buffer position
        impl->mDSBuffer->GetCurrentPosition(&playCursor, 0);
        playCursor %= audio->getBufferSize(); // Paranoia
        playCursor &= -((int)audio->getSampleSize());
        
        if (playCursor != writeCursor)
        {
            int writeBytes = playCursor - writeCursor;
            if (writeBytes < 0)
                writeBytes += audio->getBufferSize();
            
            // Try to lock buffer
            DWORD bytes1, bytes2;
            void *ptr1, *ptr2;
            if (impl->mDSBuffer->Lock(writeCursor, writeBytes, &ptr1, &bytes1, &ptr2, &bytes2, 0) == DS_OK)
            {
                // Mix sound to locked positions
                {
                    MutexLock lock(audio->getMutex());
                    
                    if (bytes1)
                        audio->mixOutput(ptr1, bytes1);
                    if (bytes2)
                        audio->mixOutput(ptr2, bytes2);
                }
                
                // Unlock buffer and update write cursor
                impl->mDSBuffer->Unlock(ptr1, bytes1, ptr2, bytes2);
                writeCursor += writeBytes;
                if (writeCursor >= audio->getBufferSize())
                    writeCursor -= audio->getBufferSize();
            }
        }
        
        Sleep(10);
    }
    
    impl->mDSBuffer->Stop();
    return 0;
}

Audio* getAudio()
{
    return instance;
}
