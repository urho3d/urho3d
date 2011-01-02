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
#include "Song.h"

#include "DebugNew.h"

const unsigned char Song::sVibratoTypeTable[] =
{
    0, 2, 1, 0
};

const unsigned char Song::sPanningTable[] =
{
    64, 191, 191, 64
};

const signed char Song::sVibratoTable[4][256] =
{
    {
        0, -2, -3, -5, -6, -8, -9, -11, -12, -14, -16, -17, -19, -20, -22, -23,
        -24, -26, -27, -29, -30, -32, -33, -34, -36, -37, -38, -39, -41, -42, -43, -44,
        -45, -46, -47, -48, -49, -50, -51, -52, -53, -54, -55, -56, -56, -57, -58, -59,
        -59, -60, -60, -61, -61, -62, -62, -62, -63, -63, -63, -64, -64, -64, -64, -64,
        -64, -64, -64, -64, -64, -64, -63, -63, -63, -62, -62, -62, -61, -61, -60, -60,
        -59, -59, -58, -57, -56, -56, -55, -54, -53, -52, -51, -50, -49, -48, -47, -46,
        -45, -44, -43, -42, -41, -39, -38, -37, -36, -34, -33, -32, -30, -29, -27, -26,
        -24, -23, -22, -20, -19, -17, -16, -14, -12, -11, -9, -8, -6, -5, -3, -2,
        0, 2, 3, 5, 6, 8, 9, 11, 12, 14, 16, 17, 19, 20, 22, 23,
        24, 26, 27, 29, 30, 32, 33, 34, 36, 37, 38, 39, 41, 42, 43, 44,
        45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 56, 57, 58, 59,
        59, 60, 60, 61, 61, 62, 62, 62, 63, 63, 63, 64, 64, 64, 64, 64,
        64, 64, 64, 64, 64, 64, 63, 63, 63, 62, 62, 62, 61, 61, 60, 60,
        59, 59, 58, 57, 56, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46,
        45, 44, 43, 42, 41, 39, 38, 37, 36, 34, 33, 32, 30, 29, 27, 26,
        24, 23, 22, 20, 19, 17, 16, 14, 12, 11, 9, 8, 6, 5, 3, 2
    },
    {
        64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
        64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
        64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
        64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
        64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
        64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
        64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
        64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
        -64, -64, -64, -64, -64, -64, -64, -64, -64, -64, -64, -64, -64, -64, -64, -64,
        -64, -64, -64, -64, -64, -64, -64, -64, -64, -64, -64, -64, -64, -64, -64, -64,
        -64, -64, -64, -64, -64, -64, -64, -64, -64, -64, -64, -64, -64, -64, -64, -64,
        -64, -64, -64, -64, -64, -64, -64, -64, -64, -64, -64, -64, -64, -64, -64, -64,
        -64, -64, -64, -64, -64, -64, -64, -64, -64, -64, -64, -64, -64, -64, -64, -64,
        -64, -64, -64, -64, -64, -64, -64, -64, -64, -64, -64, -64, -64, -64, -64, -64,
        -64, -64, -64, -64, -64, -64, -64, -64, -64, -64, -64, -64, -64, -64, -64, -64,
        -64, -64, -64, -64, -64, -64, -64, -64, -64, -64, -64, -64, -64, -64, -64, -64
    },
    {
        0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7,
        8, 8, 9, 9, 10, 10, 11, 11, 12, 12, 13, 13, 14, 14, 15, 15,
        16, 16, 17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 23,
        24, 24, 25, 25, 26, 26, 27, 27, 28, 28, 29, 29, 30, 30, 31, 31,
        32, 32, 33, 33, 34, 34, 35, 35, 36, 36, 37, 37, 38, 38, 39, 39,
        40, 40, 41, 41, 42, 42, 43, 43, 44, 44, 45, 45, 46, 46, 47, 47,
        48, 48, 49, 49, 50, 50, 51, 51, 52, 52, 53, 53, 54, 54, 55, 55,
        56, 56, 57, 57, 58, 58, 59, 59, 60, 60, 61, 61, 62, 62, 63, 63,
        -64, -64, -63, -63, -62, -62, -61, -61, -60, -60, -59, -59, -58, -58, -57, -57,
        -56, -56, -55, -55, -54, -54, -53, -53, -52, -52, -51, -51, -50, -50, -49, -49,
        -48, -48, -47, -47, -46, -46, -45, -45, -44, -44, -43, -43, -42, -42, -41, -41,
        -40, -40, -39, -39, -38, -38, -37, -37, -36, -36, -35, -35, -34, -34, -33, -33,
        -32, -32, -31, -31, -30, -30, -29, -29, -28, -28, -27, -27, -26, -26, -25, -25,
        -24, -24, -23, -23, -22, -22, -21, -21, -20, -20, -19, -19, -18, -18, -17, -17,
        -16, -16, -15, -15, -14, -14, -13, -13, -12, -12, -11, -11, -10, -10, -9, -9,
        -8, -8, -7, -7, -6, -6, -5, -5, -4, -4, -3, -3, -2, -2, -1, -1
    },
    {
        0, 0, -1, -1, -2, -2, -3, -3, -4, -4, -5, -5, -6, -6, -7, -7,
        -8, -8, -9, -9, -10, -10, -11, -11, -12, -12, -13, -13, -14, -14, -15, -15,
        -16, -16, -17, -17, -18, -18, -19, -19, -20, -20, -21, -21, -22, -22, -23, -23,
        -24, -24, -25, -25, -26, -26, -27, -27, -28, -28, -29, -29, -30, -30, -31, -31,
        -32, -32, -33, -33, -34, -34, -35, -35, -36, -36, -37, -37, -38, -38, -39, -39,
        -40, -40, -41, -41, -42, -42, -43, -43, -44, -44, -45, -45, -46, -46, -47, -47,
        -48, -48, -49, -49, -50, -50, -51, -51, -52, -52, -53, -53, -54, -54, -55, -55,
        -56, -56, -57, -57, -58, -58, -59, -59, -60, -60, -61, -61, -62, -62, -63, -63,
        64, 64, 63, 63, 62, 62, 61, 61, 60, 60, 59, 59, 58, 58, 57, 57,
        56, 56, 55, 55, 54, 54, 53, 53, 52, 52, 51, 51, 50, 50, 49, 49,
        48, 48, 47, 47, 46, 46, 45, 45, 44, 44, 43, 43, 42, 42, 41, 41,
        40, 40, 39, 39, 38, 38, 37, 37, 36, 36, 35, 35, 34, 34, 33, 33,
        32, 32, 31, 31, 30, 30, 29, 29, 28, 28, 27, 27, 26, 26, 25, 25,
        24, 24, 23, 23, 22, 22, 21, 21, 20, 20, 19, 19, 18, 18, 17, 17,
        16, 16, 15, 15, 14, 14, 13, 13, 12, 12, 11, 11, 10, 10, 9, 9,
        8, 8, 7, 7, 6, 6, 5, 5, 4, 4, 3, 3, 2, 2, 1, 1
    }
};

Song::Song(Audio* audio, const std::string& name) :
    Resource(name),
    mAudio(audio),
    mLoaded(false),
    mPlaying(false),
    mSampleCount(0),
    mBpmTempo(125),
    mGain(0.25f),
    mFader(1.0f),
    mFaderTarget(1.0f),
    mFadeSpeed(0.0f)
{
}

Song::~Song()
{
    stop();
}

void Song::stop()
{
    if (mPlaying)
    {
        if (mAudio)
            mAudio->removeSong(this);
        mPlaying = false;
    }
    
    setNumChannels(0);
}

void Song::setGain(float gain)
{
    mGain = clamp(gain, 0.0f, 1.0f);
    
    for (unsigned i = 0; i < mChannels.size(); ++i)
        mChannels[i]->setAttenuation(mFader * mGain);
}

void Song::fade(float target, float speed)
{
    mFaderTarget = clamp(target, 0.0f, 1.0f);
    mFadeSpeed = speed;
}

void Song::setBpmTempo(unsigned tempo)
{
    if (tempo) 
        mBpmTempo = tempo;
}

void Song::update()
{
    if (!mAudio)
        return;
    
    if ((mLoaded) && (mPlaying))
        updatePlayer();
    
    updateMasterFade();
    mSampleCount = ((mAudio->getMixRate() * 5) >> 1) / mBpmTempo;
}

void Song::setNumChannels(unsigned numChannels)
{
    if (!mAudio)
    {
        releaseChannels();
        return;
    }
    
    MutexLock lock(mAudio->getMutex());
    
    releaseChannels();
    
    for (unsigned i = 0; i < numChannels; ++i)
    {
        Channel* newChannel = new Channel(mAudio);
        newChannel->setChannelType(CHANNEL_MUSIC);
        newChannel->setAttenuation(mFader * mGain);
        mChannels.push_back(newChannel);
    }
}

void Song::updateMasterFade()
{
    if (mFadeSpeed)
    {
        if (mFader > mFaderTarget)
        {
            mFader -= mFadeSpeed * 2.5f / mBpmTempo;
            if (mFader < mFaderTarget)
            {
                mFader = mFaderTarget;
                mFadeSpeed = 0.0f;
            }
        }
        else if (mFader < mFaderTarget)
        {
            mFader += mFadeSpeed * 2.5f / mBpmTempo;
            if (mFader > mFaderTarget)
            {
                mFader = (float)mFaderTarget;
                mFadeSpeed = 0.0f;
            }
        }
        else
            mFadeSpeed = 0.0f;
        
        for (unsigned i = 0; i < mChannels.size(); ++i)
            mChannels[i]->setAttenuation(mFader * mGain);
    }
}

void Song::decSampleCount(unsigned played)
{
    mSampleCount -= played;
}

void Song::releaseChannels()
{
    for (std::vector<Channel*>::iterator i = mChannels.begin(); i != mChannels.end(); ++i)
        delete *i;
    mChannels.clear();
}
