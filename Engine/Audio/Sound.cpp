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
#include "Profiler.h"
#include "ResourceCache.h"
#include "Sound.h"
#include "XMLFile.h"

#include <cstring>
#include <stb_vorbis.h>

#include "DebugNew.h"

//! WAV format header
struct WavHeader
{
    unsigned char mRiffText[4];
    unsigned mTotalLength;
    unsigned char mWaveText[4];
    unsigned char mFormatText[4];
    unsigned mFormatLength;
    unsigned short mFormat;
    unsigned short mChannels;
    unsigned mFrequency;
    unsigned mAvgBytes;
    unsigned short mBlockAlign;
    unsigned short mBits;
    unsigned char mDataText[4];
    unsigned mDataLength;
};

static const unsigned IP_SAFETY = 4;

Sound::Sound(const std::string& name) :
    Resource(name),
    mRepeat(0),
    mEnd(0),
    mFrequency(44100),
    mLooped(false),
    mSixteenBit(false),
    mStereo(false),
    mCompressed(false),
    mCompressedLength(0.0f)
{
}

Sound::~Sound()
{
}

void Sound::load(Deserializer& source, ResourceCache* cache)
{
    PROFILE(Sound_Load);
    
    if (getExtension(source.getName()) == ".ogg")
        loadOggVorbis(source);
    else if (getExtension(source.getName()) == ".wav")
        loadWav(source);
    else
        loadRaw(source);
    
    // Load optional parameters
    loadParameters(cache);
}

void Sound::loadOggVorbis(Deserializer& source)
{
    unsigned dataSize = source.getSize();
    SharedArrayPtr<signed char> data(new signed char[dataSize]);
    source.read(data.getPtr(), dataSize);
    
    // Check for validity of data
    int error;
    stb_vorbis* vorbis = stb_vorbis_open_memory((unsigned char*)data.getPtr(), dataSize, &error, 0);
    if (!vorbis)
        EXCEPTION("Could not read Ogg Vorbis data from " + source.getName());
    
    // Store length, frequency and stereo flag
    stb_vorbis_info info = stb_vorbis_get_info(vorbis);
    mCompressedLength = stb_vorbis_stream_length_in_seconds(vorbis);
    mFrequency = info.sample_rate;
    mStereo = info.channels > 1;
    stb_vorbis_close(vorbis);
    
    mData = data;
    mDataSize = dataSize;
    mSixteenBit = true;
    mCompressed = true;
    
    setMemoryUse(dataSize);
}

void Sound::loadWav(Deserializer& source)
{
    WavHeader header;
    
    // Try to open
    memset(&header, 0, sizeof header);
    source.read(&header.mRiffText, 4);
    header.mTotalLength = source.readUInt();
    source.read(&header.mWaveText, 4);
    
    if ((memcmp("RIFF", header.mRiffText, 4)) || (memcmp("WAVE", header.mWaveText, 4)))
        EXCEPTION("Could not read WAV data from " + source.getName());
    
    // Search for the FORMAT chunk
    for (;;)
    {
        source.read(&header.mFormatText, 4);
        header.mFormatLength = source.readUInt();
        if (!memcmp("fmt ", &header.mFormatText, 4))
            break;
        
        source.seek(source.getPosition() + header.mFormatLength);
        if ((!header.mFormatLength) || (source.getPosition() >= source.getSize()))
            EXCEPTION("Could not read WAV data from " + source.getName());
    }
    
    // Read the FORMAT chunk
    header.mFormat = source.readUShort();
    header.mChannels = source.readUShort();
    header.mFrequency = source.readUInt();
    header.mAvgBytes = source.readUInt();
    header.mBlockAlign = source.readUShort();
    header.mBits = source.readUShort();
    
    // Skip data if the format chunk was bigger than what we use
    source.seek(source.getPosition() + header.mFormatLength - 16);
    
    // Check for correct format
    if (header.mFormat != 1)
        EXCEPTION("Could not read WAV data from " + source.getName());
    
    // Search for the DATA chunk
    for (;;)
    {
        source.read(&header.mDataText, 4);
        header.mDataLength = source.readUInt();
        if (!memcmp("data", &header.mDataText, 4))
            break;
        
        source.seek(source.getPosition() + header.mDataLength);
        if ((!header.mDataLength) || (source.getPosition() >= source.getSize()))
            EXCEPTION("Could not read WAV data from " + source.getName());
    }
    
    // Allocate sound and load audio data
    unsigned length = header.mDataLength;
    setSize(length);
    setFormat(header.mFrequency, header.mBits == 16, header.mChannels == 2);
    source.read(mData.getPtr(), length);
    
    // Convert 8-bit audio to signed
    if (!mSixteenBit)
    {
        for (unsigned i = 0; i < length; ++i)
            mData[i] -= 128;
    }
}

void Sound::loadRaw(Deserializer& source)
{
    unsigned dataSize = source.getSize();
    setSize(dataSize);
    source.read(mData.getPtr(), dataSize);
}

void Sound::setSize(unsigned dataSize)
{
    if (!dataSize)
        return;
    
    mData = new signed char[dataSize + IP_SAFETY];
    mDataSize = dataSize;
    mCompressed = false;
    setOneshot();
    
    setMemoryUse(dataSize + IP_SAFETY);
}

void Sound::setData(const void* data, unsigned dataSize)
{
    if (!dataSize)
        return;
    
    setSize(dataSize);
    memcpy(mData.getPtr(), data, dataSize);
}

void Sound::setFormat(unsigned frequency, bool sixteenBit, bool stereo)
{
    mFrequency = frequency;
    mSixteenBit = sixteenBit;
    mStereo = stereo;
    mCompressed = false;
}

void Sound::setOneshot()
{
    if (!mCompressed)
    {
        mEnd = mData.getPtr() + mDataSize;
        mLooped = false;
        
        fixInterpolation();
    }
    else
        mLooped = false;
}

void Sound::setLooped()
{
    setLoop(0, mDataSize);
}

void Sound::setLoop(unsigned repeatOffset, unsigned endOffset)
{
    if (!mCompressed)
    {
        if (repeatOffset > mDataSize)
            repeatOffset = mDataSize;
        if (endOffset > mDataSize)
            endOffset = mDataSize;
        
        // Align repeat and end on sample boundaries
        int sampleSize = getSampleSize();
        repeatOffset &= -sampleSize;
        endOffset &= -sampleSize;
        
        mRepeat = mData.getPtr() + repeatOffset;
        mEnd = mData.getPtr() + endOffset;
        mLooped = true;
        
        fixInterpolation();
    }
    else
        mLooped = true;
}

void Sound::fixInterpolation()
{
    if (!mData)
        return;
    
    // If looped, copy loop start to loop end. If oneshot, insert silence to end
    if (mLooped)
    {
        for (unsigned i = 0; i < IP_SAFETY; ++i)
            mEnd[i] = mRepeat[i];
    }
    else
    {
        for (unsigned i = 0; i < IP_SAFETY; ++i)
            mEnd[i] = 0;
    }
}

void* Sound::allocateDecoder()
{
    if (!mCompressed)
        return 0;
    
    int error;
    stb_vorbis* vorbis = stb_vorbis_open_memory((unsigned char*)mData.getPtr(), mDataSize, &error, 0);
    return vorbis;
}

unsigned Sound::decode(void* decoder, signed char* dest, unsigned bytes)
{
    if (!decoder)
        return 0;
    
    unsigned channels = mStereo ? 2 : 1;
    stb_vorbis* vorbis = static_cast<stb_vorbis*>(decoder);
    unsigned outSamples = stb_vorbis_get_samples_short_interleaved(vorbis, channels, (short*)dest, bytes >> 1);
    return (outSamples * channels) << 1;
}

void Sound::rewindDecoder(void* decoder)
{
    if (!decoder)
        return;
    
    stb_vorbis* vorbis = static_cast<stb_vorbis*>(decoder);
    stb_vorbis_seek_start(vorbis);
}

void Sound::freeDecoder(void* decoder)
{
    if (!decoder)
        return;
    
    stb_vorbis* vorbis = static_cast<stb_vorbis*>(decoder);
    stb_vorbis_close(vorbis);
}

float Sound::getLength() const
{
    if (!mCompressed)
    {
        if (!mFrequency)
            return 0.0f;
        else
            return ((float)mDataSize) / getSampleSize() / mFrequency;
    }
    else
        return mCompressedLength;
}

unsigned Sound::getSampleSize() const
{
    unsigned size = 1;
    if (mSixteenBit)
        size <<= 1;
    if (mStereo)
        size <<= 1;
    return size;
}

void Sound::loadParameters(ResourceCache* cache)
{
    if (!cache)
        return;
    
    std::string soundPath, soundName, soundExt;
    splitPath(getName(), soundPath, soundName, soundExt);
    std::string xmlName = soundPath + soundName + ".xml";
    
    if (!cache->exists(xmlName))
        return;
    
    XMLFile* xml = cache->getResource<XMLFile>(xmlName);
    XMLElement rootElem = xml->getRootElement();
    XMLElement paramElem = rootElem.getChildElement("");
    
    while (paramElem)
    {
        std::string name = paramElem.getName();
        
        if ((name == "format") && (!mCompressed))
        {
            if (paramElem.hasAttribute("frequency"))
                mFrequency = paramElem.getInt("frequency");
            if (paramElem.hasAttribute("sixteenbit"))
                mSixteenBit = paramElem.getBool("sixteenbit");
            if (paramElem.hasAttribute("16bit"))
                mSixteenBit = paramElem.getBool("16bit");
            if (paramElem.hasAttribute("stereo"))
                mStereo = paramElem.getBool("stereo");
        }
        
        if (name == "loop")
        {
            if (paramElem.hasAttribute("enable"))
            {
                if (paramElem.getBool("enable"))
                    setLooped();
                else
                    setOneshot();
            }
            if ((paramElem.hasAttribute("start")) && (paramElem.hasAttribute("end")))
                setLoop(paramElem.getInt("start"), paramElem.getInt("end"));
        }
        
        paramElem = paramElem.getNextElement();
    }
}
