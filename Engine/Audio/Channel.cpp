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
#include "Sound.h"

#include <cstring>

#include "DebugNew.h"

#define INC_POS_LOOPED()        \
    pos += intAdd;              \
    fractPos += fractAdd;       \
    if (fractPos > 65535)       \
    {                           \
        fractPos &= 65535;      \
        ++pos;                  \
    }                           \
    while (pos >= end)          \
        pos -= (end - repeat);  \

#define INC_POS_ONESHOT()       \
    pos += intAdd;              \
    fractPos += fractAdd;       \
    if (fractPos > 65535)       \
    {                           \
        fractPos &= 65535;      \
        ++pos;                  \
    }                           \
    if (pos >= end)             \
    {                           \
        pos = 0;                \
        break;                  \
    }                           \

#define INC_POS_STEREO_LOOPED() \
    pos += (intAdd << 1);       \
    fractPos += fractAdd;       \
    if (fractPos > 65535)       \
    {                           \
        fractPos &= 65535;      \
        pos += 2;               \
    }                           \
    while (pos >= end)          \
        pos -= (end - repeat);  \

#define INC_POS_STEREO_ONESHOT()\
    pos += (intAdd << 1);       \
    fractPos += fractAdd;       \
    if (fractPos > 65535)       \
    {                           \
        fractPos &= 65535;      \
        pos += 2;               \
    }                           \
    if (pos >= end)             \
    {                           \
        pos = 0;                \
        break;                  \
    }                           \

#define GET_IP_SAMPLE() (((((int)pos[1] - (int)pos[0]) * fractPos) / 65536) + (int)pos[0])

#define GET_IP_SAMPLE_LEFT() (((((int)pos[2] - (int)pos[0]) * fractPos) / 65536) + (int)pos[0])

#define GET_IP_SAMPLE_RIGHT() (((((int)pos[3] - (int)pos[1]) * fractPos) / 65536) + (int)pos[1])

// Compressed audio decode buffer length in milliseconds
static const int DECODE_BUFFER_LENGTH = 100;

Channel::Channel(Audio* audio) :
    mAudio(audio),
    mPos(0),
    mFractPos(0),
    mChannelType(CHANNEL_EFFECT),
    mFrequency(0.0f),
    mGain(1.0f),
    mAttenuation(1.0f),
    mPanning(0.0f),
    mDecoder(0),
    mDecodePos(0)
{
    if (mAudio)
        mAudio->addChannel(this);
}

Channel::~Channel()
{
    if (mAudio)
        mAudio->removeChannel(this);
    
    freeDecoder();
}

void Channel::play(Sound* sound)
{
    if (!mAudio)
        return;
    
    // If channel is currently playing, have to lock the audio mutex
    if (mPos)
    {
        MutexLock lock(mAudio->getMutex());
        playLockless(sound);
    }
    else
        playLockless(sound);
}

void Channel::play(Sound* sound, float frequency)
{
    setFrequency(frequency);
    play(sound);
}

void Channel::play(Sound* sound, float frequency, float gain)
{
    setFrequency(frequency);
    setGain(gain);
    play(sound);
}

void Channel::play(Sound* sound, float frequency, float gain, float panning)
{
    setFrequency(frequency);
    setGain(gain);
    setPanning(panning);
    play(sound);
}

void Channel::stop()
{
    if (!mAudio)
        return;
    
    // If channel is currently playing, have to lock the audio mutex
    if (mPos)
    {
        MutexLock lock(mAudio->getMutex());
        stopLockless();
    }
    
    // Free the compressed sound decoder now if any
    freeDecoder();
    mSound.reset();
}

void Channel::setChannelType(ChannelType type)
{
    if ((type == CHANNEL_MASTER) || (type >= MAX_CHANNEL_TYPES))
        return;
    
    mChannelType = type;
}

void Channel::setFrequency(float frequency)
{
    mFrequency = clamp(frequency, 0.0f, 535232.0f);
}

void Channel::setGain(float gain)
{
    mGain = max(gain, 0.0f);
}

void Channel::setAttenuation(float attenuation)
{
    mAttenuation = clamp(attenuation, 0.0f, 1.0f);
}

void Channel::setPanning(float panning)
{
    mPanning = clamp(panning, -1.0f, 1.0f);
}

void Channel::setIntFrequency(unsigned frequency)
{
    mFrequency = clamp((float)frequency, 0.0f, 535232.0f);
}

void Channel::setIntVolume(int volume)
{
    mGain = max((float)volume / 64.0f, 0.0f);
}

void Channel::setIntPanning(int panning)
{
    mPanning = clamp(((float)panning / 255.0f) * 2.0f - 1.0f, -1.0f, 1.0f);
}

bool Channel::isPlaying() const
{
    return mSound.getPtr() != 0;
}

void Channel::setPlayPosition(signed char* pos)
{
    if ((!mAudio) || (!mSound))
        return;
    
    MutexLock lock(mAudio->getMutex());
    setPlayPositionLockless(pos);
}

void Channel::playLockless(Sound* sound)
{
    if (sound)
    {
        if (!sound->isCompressed())
        {
            // Uncompressed sound start
            signed char* start = sound->getStart();
            if (start)
            {
                // Free decoder in case previous sound was compressed
                freeDecoder();
                mSound = sound;
                mPos = start;
                mFractPos = 0;
                return;
            }
        }
        else
        {
            // Compressed sound start
            if (sound == mSound)
            {
                // If same compressed sound is already playing, rewind the decoder
                mSound->rewindDecoder(mDecoder);
                return;
            }
            else
            {
                // Else just set the new sound with a dummy start position. The mixing routine will allocate the new decoder
                freeDecoder();
                mSound = sound;
                mPos = sound->getStart();
                return;
            }
        }
    }
    
    // If sound pointer is null or if sound has no data, stop playback
    freeDecoder();
    mSound.reset();
    mPos = 0;
}

void Channel::stopLockless()
{
    mPos = 0;
}

void Channel::setPlayPositionLockless(signed char* pos)
{
    // Setting position on a compressed sound is not supported
    if ((!mSound) || (mSound->isCompressed()))
        return;
    
    signed char* start = mSound->getStart();
    signed char* end = mSound->getEnd();
    if (pos < start)
        pos = start;
    if ((mSound->isSixteenBit()) && ((pos - start) & 1))
        ++pos;
    if (pos > end)
        pos = end;
    
    mPos = pos;
}

void Channel::update(float timeStep)
{
    if (!mAudio)
        return;
    
    // If there is no actual audio output, perform fake mixing into a nonexistent buffer to check stopping/looping
    if (!mAudio->hasBuffer())
        mixNull(timeStep);
    
    // Free the sound if playback has stopped
    if ((mSound) && (!mPos))
    {
        freeDecoder();
        mSound.reset();
    }
}

void Channel::mix(int* dest, unsigned samples, int mixRate, bool stereo, bool interpolate)
{
    if ((!mPos) || (!mSound))
        return;
    
    if (mSound->isCompressed())
    {
        if (mDecoder)
        {
            // If decoder already exists, decode new compressed audio
            bool eof = false;
            unsigned currentPos = mPos - mDecodeBuffer->getStart();
            if (currentPos != mDecodePos)
            {
                // If buffer has wrapped, decode first to the end
                if (currentPos < mDecodePos)
                {
                    unsigned bytes = mDecodeBuffer->getDataSize() - mDecodePos;
                    unsigned outBytes = mSound->decode(mDecoder, mDecodeBuffer->getStart() + mDecodePos, bytes);
                    // If produced less output, end of sound encountered. Fill rest with zero
                    if (outBytes < bytes)
                    {
                        memset(mDecodeBuffer->getStart() + mDecodePos + outBytes, 0, bytes - outBytes);
                        eof = true;
                    }
                    mDecodePos = 0;
                }
                if (currentPos > mDecodePos)
                {
                    unsigned bytes = currentPos - mDecodePos;
                    unsigned outBytes = mSound->decode(mDecoder, mDecodeBuffer->getStart() + mDecodePos, bytes);
                    // If produced less output, end of sound encountered. Fill rest with zero
                    if (outBytes < bytes)
                    {
                        memset(mDecodeBuffer->getStart() + mDecodePos + outBytes, 0, bytes - outBytes);
                        if (mSound->isLooped())
                            eof = true;
                    }
                    
                    // If wrote to buffer start, correct interpolation wraparound
                    if (!mDecodePos)
                        mDecodeBuffer->fixInterpolation();
                }
            }
            
            // If end of stream encountered, check whether we should rewind or stop
            if (eof)
            {
                if (mSound->isLooped())
                    mSound->rewindDecoder(mDecoder);
                else
                    mDecodeBuffer->setOneshot(); // Stop after the current decode buffer has been played
            }
            
            mDecodePos = currentPos;
        }
        else
        {
            // Setup the decoder and decode buffer
            mDecoder = mSound->allocateDecoder();
            unsigned sampleSize = mSound->getSampleSize();
            unsigned decodeBufferSize = sampleSize * mSound->getIntFrequency() * DECODE_BUFFER_LENGTH / 1000;
            mDecodeBuffer = new Sound();
            mDecodeBuffer->setSize(decodeBufferSize);
            mDecodeBuffer->setFormat(mSound->getIntFrequency(), true, mSound->isStereo());
            
            // Clear the decode buffer, then fill with initial audio data and set it to loop
            memset(mDecodeBuffer->getStart(), 0, decodeBufferSize);
            mSound->decode(mDecoder, mDecodeBuffer->getStart(), decodeBufferSize);
            mDecodeBuffer->setLooped();
            mDecodePos = 0;
            
            // Start playing the decode buffer
            mPos = mDecodeBuffer->getStart();
            mFractPos = 0;
        }
    }
    
    // If compressed, play the decode buffer. Otherwise play the original sound
    Sound* sound = mSound->isCompressed() ? mDecodeBuffer : mSound;
    if (!sound)
        return;
    
    // Choose the correct mixing routine
    if (!sound->isStereo())
    {
        if (interpolate)
        {
            if (stereo)
                mixMonoToStereoIP(sound, dest, samples, mixRate);
            else
                mixMonoToMonoIP(sound, dest, samples, mixRate);
        }
        else
        {
            if (stereo)
                mixMonoToStereo(sound, dest, samples, mixRate);
            else
                mixMonoToMono(sound, dest, samples, mixRate);
        }
    }
    else
    {
        if (interpolate)
        {
            if (stereo)
                mixStereoToStereoIP(sound, dest, samples, mixRate);
            else
                mixStereoToMonoIP(sound, dest, samples, mixRate);
        }
        else
        {
            if (stereo)
                mixStereoToStereo(sound, dest, samples, mixRate);
            else
                mixStereoToMono(sound, dest, samples, mixRate);
        }
    }
}

void Channel::mixMonoToMono(Sound* sound, int* dest, unsigned samples, int mixRate)
{
    float totalGain = mAudio->getChannelMasterGain(mChannelType) * mAttenuation * mGain;
    int vol = (int)(256.0f * totalGain + 0.5f);
    if (!vol)
    {
        mixZeroVolume(sound, samples, mixRate);
        return;
    }
    
    float add = mFrequency / (float)mixRate;
    int intAdd = (int)add;
    int fractAdd = (int)((add - floorf(add)) * 65536.0f);
    int fractPos = mFractPos;
    
    if (sound->isSixteenBit())
    {
        short* pos = (short*)mPos;
        short* end = (short*)sound->getEnd();
        short* repeat = (short*)sound->getRepeat();
        
        if (sound->isLooped())
        {
            while (samples--)
            {
                *dest = *dest + (*pos * vol) / 256;
                ++dest;
                INC_POS_LOOPED();
            }
            mPos = (signed char*)pos;
        }
        else
        {
            while (samples--)
            {
                *dest = *dest + (*pos * vol) / 256;
                ++dest;
                INC_POS_ONESHOT();
            }
            mPos = (signed char*)pos;
        }
    }
    else
    {
        signed char* pos = (signed char*)mPos;
        signed char* end = sound->getEnd();
        signed char* repeat = sound->getRepeat();
        
        if (sound->isLooped())
        {
            while (samples--)
            {
                *dest = *dest + *pos * vol;
                ++dest;
                INC_POS_LOOPED();
            }
            mPos = pos;
        }
        else
        {
            while (samples--)
            {
                *dest = *dest + *pos * vol;
                ++dest;
                INC_POS_ONESHOT();
            }
            mPos = pos;
        }
    }
    
    mFractPos = fractPos;
}

void Channel::mixMonoToStereo(Sound* sound, int* dest, unsigned samples, int mixRate)
{
    float totalGain = mAudio->getChannelMasterGain(mChannelType) * mAttenuation * mGain;
    int leftVol = (int)((-mPanning + 1.0f) * (256.0f * totalGain + 0.5f));
    int rightVol = (int)((mPanning + 1.0f) * (256.0f * totalGain + 0.5f));
    if ((!leftVol) && (!rightVol))
    {
        mixZeroVolume(sound, samples, mixRate);
        return;
    }
    
    float add = mFrequency / (float)mixRate;
    int intAdd = (int)add;
    int fractAdd = (int)((add - floorf(add)) * 65536.0f);
    int fractPos = mFractPos;
    
    if (sound->isSixteenBit())
    {
        short* pos = (short*)mPos;
        short* end = (short*)sound->getEnd();
        short* repeat = (short*)sound->getRepeat();
        
        if (sound->isLooped())
        {
            while (samples--)
            {
                *dest = *dest + (*pos * leftVol) / 256;
                ++dest;
                *dest = *dest + (*pos * rightVol) / 256;
                ++dest;
                INC_POS_LOOPED();
            }
            mPos = (signed char*)pos;
        }
        else
        {
            while (samples--)
            {
                *dest = *dest + (*pos * leftVol) / 256;
                ++dest;
                *dest = *dest + (*pos * rightVol) / 256;
                ++dest;
                INC_POS_ONESHOT();
            }
            mPos = (signed char*)pos;
        }
    }
    else
    {
        signed char* pos = (signed char*)mPos;
        signed char* end = sound->getEnd();
        signed char* repeat = sound->getRepeat();
        
        if (sound->isLooped())
        {
            while (samples--)
            {
                *dest = *dest + *pos * leftVol;
                ++dest;
                *dest = *dest + *pos * rightVol;
                ++dest;
                INC_POS_LOOPED();
            }
            mPos = pos;
        }
        else
        {
            while (samples--)
            {
                *dest = *dest + *pos * leftVol;
                ++dest;
                *dest = *dest + *pos * rightVol;
                ++dest;
                INC_POS_ONESHOT();
            }
            mPos = pos;
        }
    }
    
    mFractPos = fractPos;
}

void Channel::mixMonoToMonoIP(Sound* sound, int* dest, unsigned samples, int mixRate)
{
    float totalGain = mAudio->getChannelMasterGain(mChannelType) * mAttenuation * mGain;
    int vol = (int)(256.0f * totalGain + 0.5f);
    if (!vol)
    {
        mixZeroVolume(sound, samples, mixRate);
        return;
    }
    
    float add = mFrequency / (float)mixRate;
    int intAdd = (int)add;
    int fractAdd = (int)((add - floorf(add)) * 65536.0f);
    int fractPos = mFractPos;
    
    if (sound->isSixteenBit())
    {
        short* pos = (short*)mPos;
        short* end = (short*)sound->getEnd();
        short* repeat = (short*)sound->getRepeat();
        
        if (sound->isLooped())
        {
            while (samples--)
            {
                *dest = *dest + (GET_IP_SAMPLE() * vol) / 256;
                ++dest;
                INC_POS_LOOPED();
            }
            mPos = (signed char*)pos;
        }
        else
        {
            while (samples--)
            {
                *dest = *dest + (GET_IP_SAMPLE() * vol) / 256;
                ++dest;
                INC_POS_ONESHOT();
            }
            mPos = (signed char*)pos;
        }
    }
    else
    {
        signed char* pos = (signed char*)mPos;
        signed char* end = sound->getEnd();
        signed char* repeat = sound->getRepeat();
        
        if (sound->isLooped())
        {
            while (samples--)
            {
                *dest = *dest + GET_IP_SAMPLE() * vol;
                ++dest;
                INC_POS_LOOPED();
            }
            mPos = pos;
        }
        else
        {
            while (samples--)
            {
                *dest = *dest + GET_IP_SAMPLE() * vol;
                ++dest;
                INC_POS_ONESHOT();
            }
            mPos = pos;
        }
    }
    
    mFractPos = fractPos;
}

void Channel::mixMonoToStereoIP(Sound* sound, int* dest, unsigned samples, int mixRate)
{
    float totalGain = mAudio->getChannelMasterGain(mChannelType) * mAttenuation * mGain;
    int leftVol = (int)((-mPanning + 1.0f) * (256.0f * totalGain + 0.5f));
    int rightVol = (int)((mPanning + 1.0f) * (256.0f * totalGain + 0.5f));
    if ((!leftVol) && (!rightVol))
    {
        mixZeroVolume(sound, samples, mixRate);
        return;
    }
    
    float add = mFrequency / (float)mixRate;
    int intAdd = (int)add;
    int fractAdd = (int)((add - floorf(add)) * 65536.0f);
    int fractPos = mFractPos;
    
    if (sound->isSixteenBit())
    {
        short* pos = (short*)mPos;
        short* end = (short*)sound->getEnd();
        short* repeat = (short*)sound->getRepeat();
        
        if (sound->isLooped())
        {
            while (samples--)
            {
                int s = GET_IP_SAMPLE();
                *dest = *dest + (s * leftVol) / 256;
                ++dest;
                *dest = *dest + (s * rightVol) / 256;
                ++dest;
                INC_POS_LOOPED();
            }
            mPos = (signed char*)pos;
        }
        else
        {
            while (samples--)
            {
                int s = GET_IP_SAMPLE();
                *dest = *dest + (s * leftVol) / 256;
                ++dest;
                *dest = *dest + (s * rightVol) / 256;
                ++dest;
                INC_POS_ONESHOT();
            }
            mPos = (signed char*)pos;
        }
    }
    else
    {
        signed char* pos = (signed char*)mPos;
        signed char* end = sound->getEnd();
        signed char* repeat = sound->getRepeat();
        
        if (sound->isLooped())
        {
            while (samples--)
            {
                int s = GET_IP_SAMPLE();
                *dest = *dest + s * leftVol;
                ++dest;
                *dest = *dest + s * rightVol;
                ++dest;
                INC_POS_LOOPED();
            }
            mPos = pos;
        }
        else
        {
            while (samples--)
            {
                int s = GET_IP_SAMPLE();
                *dest = *dest + s * leftVol;
                ++dest;
                *dest = *dest + s * rightVol;
                ++dest;
                INC_POS_ONESHOT();
            }
            mPos = pos;
        }
    }
    
    mFractPos = fractPos;
}

void Channel::mixStereoToMono(Sound* sound, int* dest, unsigned samples, int mixRate)
{
    float totalGain = mAudio->getChannelMasterGain(mChannelType) * mAttenuation * mGain;
    int vol = (int)(256.0f * totalGain + 0.5f);
    if (!vol)
    {
        mixZeroVolume(sound, samples, mixRate);
        return;
    }
    
    float add = mFrequency / (float)mixRate;
    int intAdd = (int)add;
    int fractAdd = (int)((add - floorf(add)) * 65536.0f);
    int fractPos = mFractPos;
    
    if (sound->isSixteenBit())
    {
        short* pos = (short*)mPos;
        short* end = (short*)sound->getEnd();
        short* repeat = (short*)sound->getRepeat();
        
        if (sound->isLooped())
        {
            while (samples--)
            {
                int s = ((int)pos[0] + (int)pos[1]) / 2;
                *dest = *dest + (s * vol) / 256;
                ++dest;
                INC_POS_STEREO_LOOPED();
            }
            mPos = (signed char*)pos;
        }
        else
        {
            while (samples--)
            {
                int s = ((int)pos[0] + (int)pos[1]) / 2;
                *dest = *dest + (s * vol) / 256;
                ++dest;
                INC_POS_STEREO_ONESHOT();
            }
            mPos = (signed char*)pos;
        }
    }
    else
    {
        signed char* pos = (signed char*)mPos;
        signed char* end = sound->getEnd();
        signed char* repeat = sound->getRepeat();
        
        if (sound->isLooped())
        {
            while (samples--)
            {
                int s = ((int)pos[0] + (int)pos[1]) / 2;
                *dest = *dest + s * vol;
                ++dest;
                INC_POS_STEREO_LOOPED();
            }
            mPos = pos;
        }
        else
        {
            while (samples--)
            {
                int s = ((int)pos[0] + (int)pos[1]) / 2;
                *dest = *dest + s * vol;
                ++dest;
                INC_POS_STEREO_ONESHOT();
            }
            mPos = pos;
        }
    }
    
    mFractPos = fractPos;
}

void Channel::mixStereoToStereo(Sound* sound, int* dest, unsigned samples, int mixRate)
{
    float totalGain = mAudio->getChannelMasterGain(mChannelType) * mAttenuation * mGain;
    int vol = (int)(256.0f * totalGain + 0.5f);
    if (!vol)
    {
        mixZeroVolume(sound, samples, mixRate);
        return;
    }
    
    float add = mFrequency / (float)mixRate;
    int intAdd = (int)add;
    int fractAdd = (int)((add - floorf(add)) * 65536.0f);
    int fractPos = mFractPos;
    
    if (sound->isSixteenBit())
    {
        short* pos = (short*)mPos;
        short* end = (short*)sound->getEnd();
        short* repeat = (short*)sound->getRepeat();
        
        if (sound->isLooped())
        {
            while (samples--)
            {
                *dest = *dest + (pos[0] * vol) / 256;
                ++dest;
                *dest = *dest + (pos[1] * vol) / 256;
                ++dest;
                INC_POS_STEREO_LOOPED();
            }
            mPos = (signed char*)pos;
        }
        else
        {
            while (samples--)
            {
                *dest = *dest + (pos[0] * vol) / 256;
                ++dest;
                *dest = *dest + (pos[1] * vol) / 256;
                ++dest;
                INC_POS_STEREO_ONESHOT();
            }
            mPos = (signed char*)pos;
        }
    }
    else
    {
        signed char* pos = (signed char*)mPos;
        signed char* end = sound->getEnd();
        signed char* repeat = sound->getRepeat();
        
        if (sound->isLooped())
        {
            while (samples--)
            {
                *dest = *dest + pos[0] * vol;
                ++dest;
                *dest = *dest + pos[1] * vol;
                ++dest;
                INC_POS_STEREO_LOOPED();
            }
            mPos = pos;
        }
        else
        {
            while (samples--)
            {
                *dest = *dest + pos[0] * vol;
                ++dest;
                *dest = *dest + pos[1] * vol;
                ++dest;
                INC_POS_STEREO_ONESHOT();
            }
            mPos = pos;
        }
    }
    
    mFractPos = fractPos;
}

void Channel::mixStereoToMonoIP(Sound* sound, int* dest, unsigned samples, int mixRate)
{
    float totalGain = mAudio->getChannelMasterGain(mChannelType) * mAttenuation * mGain;
    int vol = (int)(256.0f * totalGain + 0.5f);
    if (!vol)
    {
        mixZeroVolume(sound, samples, mixRate);
        return;
    }
    
    float add = mFrequency / (float)mixRate;
    int intAdd = (int)add;
    int fractAdd = (int)((add - floorf(add)) * 65536.0f);
    int fractPos = mFractPos;
    
    if (sound->isSixteenBit())
    {
        short* pos = (short*)mPos;
        short* end = (short*)sound->getEnd();
        short* repeat = (short*)sound->getRepeat();
        
        if (sound->isLooped())
        {
            while (samples--)
            {
                int s = (GET_IP_SAMPLE_LEFT() + GET_IP_SAMPLE_RIGHT()) / 2;
                *dest = *dest + (s * vol) / 256;
                ++dest;
                INC_POS_STEREO_LOOPED();
            }
            mPos = (signed char*)pos;
        }
        else
        {
            while (samples--)
            {
                int s = (GET_IP_SAMPLE_LEFT() + GET_IP_SAMPLE_RIGHT()) / 2;
                *dest = *dest + (s * vol) / 256;
                ++dest;
                INC_POS_STEREO_ONESHOT();
            }
            mPos = (signed char*)pos;
        }
    }
    else
    {
        signed char* pos = (signed char*)mPos;
        signed char* end = sound->getEnd();
        signed char* repeat = sound->getRepeat();
        
        if (sound->isLooped())
        {
            while (samples--)
            {
                int s = (GET_IP_SAMPLE_LEFT() + GET_IP_SAMPLE_RIGHT()) / 2;
                *dest = *dest + s * vol;
                ++dest;
                INC_POS_STEREO_LOOPED();
            }
            mPos = pos;
        }
        else
        {
            while (samples--)
            {
                int s = (GET_IP_SAMPLE_LEFT() + GET_IP_SAMPLE_RIGHT()) / 2;
                *dest = *dest + s * vol;
                ++dest;
                INC_POS_STEREO_ONESHOT();
            }
            mPos = pos;
        }
    }
    
    mFractPos = fractPos;
}

void Channel::mixStereoToStereoIP(Sound* sound, int* dest, unsigned samples, int mixRate)
{
    float totalGain = mAudio->getChannelMasterGain(mChannelType) * mAttenuation * mGain;
    int vol = (int)(256.0f * totalGain + 0.5f);
    if (!vol)
    {
        mixZeroVolume(sound, samples, mixRate);
        return;
    }
    
    float add = mFrequency / (float)mixRate;
    int intAdd = (int)add;
    int fractAdd = (int)((add - floorf(add)) * 65536.0f);
    int fractPos = mFractPos;
    
    if (sound->isSixteenBit())
    {
        short* pos = (short*)mPos;
        short* end = (short*)sound->getEnd();
        short* repeat = (short*)sound->getRepeat();
        
        if (sound->isLooped())
        {
            while (samples--)
            {
                *dest = *dest + (GET_IP_SAMPLE_LEFT() * vol) / 256;
                ++dest;
                *dest = *dest + (GET_IP_SAMPLE_RIGHT() * vol) / 256;
                ++dest;
                INC_POS_STEREO_LOOPED();
            }
            mPos = (signed char*)pos;
        }
        else
        {
            while (samples--)
            {
                *dest = *dest + (GET_IP_SAMPLE_LEFT() * vol) / 256;
                ++dest;
                *dest = *dest + (GET_IP_SAMPLE_RIGHT() * vol) / 256;
                ++dest;
                INC_POS_STEREO_ONESHOT();
            }
            mPos = (signed char*)pos;
        }
    }
    else
    {
        signed char* pos = (signed char*)mPos;
        signed char* end = sound->getEnd();
        signed char* repeat = sound->getRepeat();
        
        if (sound->isLooped())
        {
            while (samples--)
            {
                *dest = *dest + GET_IP_SAMPLE_LEFT() * vol;
                ++dest;
                *dest = *dest + GET_IP_SAMPLE_RIGHT() * vol;
                ++dest;
                INC_POS_STEREO_LOOPED();
            }
            mPos = pos;
        }
        else
        {
            while (samples--)
            {
                *dest = *dest + GET_IP_SAMPLE_LEFT() * vol;
                ++dest;
                *dest = *dest + GET_IP_SAMPLE_RIGHT() * vol;
                ++dest;
                INC_POS_STEREO_ONESHOT();
            }
            mPos = pos;
        }
    }
    
    mFractPos = fractPos;
}

void Channel::mixZeroVolume(Sound* sound, unsigned samples, int mixRate)
{
    float add = mFrequency * (float)samples / (float)mixRate;
    int intAdd = (int)add;
    int fractAdd = (int)((add - floorf(add)) * 65536.0f);
    unsigned sampleSize = sound->getSampleSize();
    
    mFractPos += fractAdd;
    if (mFractPos > 65535)
    {
        mFractPos &= 65535;
        mPos += sampleSize;
    }
    mPos += intAdd * sampleSize;
    
    if (mPos > sound->getEnd())
    {
        if (sound->isLooped())
        {
            while (mPos >= sound->getEnd())
            {
                mPos -= (sound->getEnd() - sound->getRepeat());
            }
        }
        else
            mPos = 0;
    }
}

void Channel::mixNull(float timeStep)
{
    if ((!mPos) || (!mSound))
        return;
    
    // Can not support simulated playback of compressed sounds
    if (mSound->isCompressed())
        return;
    
    // Calculate approximate advance to sample pos
    int advance = (int)(mFrequency * timeStep) * mSound->getSampleSize();
    signed char* end = mSound->getEnd();
    signed char* repeat = mSound->getRepeat();
    
    mPos += advance;
    if (mSound->isLooped())
    {
        while (mPos >= end)
            mPos -= (end - repeat);
    }
    else
    {
        if (mPos >= end)
            mPos = 0;
    }
}

void Channel::freeDecoder()
{
    if ((mSound) && (mDecoder))
    {
        mSound->freeDecoder(mDecoder);
        mDecoder = 0;
    }
    
    mDecodeBuffer.reset();
}
