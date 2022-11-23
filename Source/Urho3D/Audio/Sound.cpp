// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include "../Precompiled.h"

#include "../Audio/OggVorbisSoundStream.h"
#include "../Audio/Sound.h"
#include "../Core/Context.h"
#include "../Core/Profiler.h"
#include "../IO/FileSystem.h"
#include "../IO/Log.h"
#include "../Resource/ResourceCache.h"
#include "../Resource/XMLFile.h"
#ifndef STB_VORBIS_HEADER_ONLY
#define STB_VORBIS_HEADER_ONLY
#endif
#include <STB/stb_vorbis.h>

#include "../DebugNew.h"

namespace Urho3D
{

/// WAV format header.
struct WavHeader
{
    unsigned char riffText_[4];
    unsigned totalLength_;
    unsigned char waveText_[4];
    unsigned char formatText_[4];
    unsigned formatLength_;
    unsigned short format_;
    unsigned short channels_;
    unsigned frequency_;
    unsigned avgBytes_;
    unsigned short blockAlign_;
    unsigned short bits_;
    unsigned char dataText_[4];
    unsigned dataLength_;
};

static const unsigned IP_SAFETY = 4;

Sound::Sound(Context* context) :
    ResourceWithMetadata(context),
    repeat_(nullptr),
    end_(nullptr),
    dataSize_(0),
    frequency_(44100),
    looped_(false),
    sixteenBit_(false),
    stereo_(false),
    compressed_(false),
    compressedLength_(0.0f)
{
}

Sound::~Sound() = default;

void Sound::RegisterObject(Context* context)
{
    context->RegisterFactory<Sound>();
}

bool Sound::BeginLoad(Deserializer& source)
{
    URHO3D_PROFILE(LoadSound);

    bool success;
    if (GetExtension(source.GetName()) == ".ogg")
        success = LoadOggVorbis(source);
    else if (GetExtension(source.GetName()) == ".wav")
        success = LoadWav(source);
    else
        success = LoadRaw(source);

    // Load optional parameters
    if (success)
        LoadParameters();

    return success;
}

bool Sound::LoadOggVorbis(Deserializer& source)
{
    unsigned dataSize = source.GetSize();
    SharedArrayPtr<signed char> data(new signed char[dataSize]);
    source.Read(data.Get(), dataSize);

    // Check for validity of data
    int error;
    stb_vorbis* vorbis = stb_vorbis_open_memory((unsigned char*)data.Get(), dataSize, &error, nullptr);
    if (!vorbis)
    {
        URHO3D_LOGERROR("Could not read Ogg Vorbis data from " + source.GetName());
        return false;
    }

    // Store length, frequency and stereo flag
    stb_vorbis_info info = stb_vorbis_get_info(vorbis);
    compressedLength_ = stb_vorbis_stream_length_in_seconds(vorbis);
    frequency_ = info.sample_rate;
    stereo_ = info.channels > 1;
    stb_vorbis_close(vorbis);

    data_ = data;
    dataSize_ = dataSize;
    sixteenBit_ = true;
    compressed_ = true;

    SetMemoryUse(dataSize);
    return true;
}

bool Sound::LoadWav(Deserializer& source)
{
    WavHeader header{};

    // Try to open
    memset(&header, 0, sizeof header);
    source.Read(&header.riffText_, 4);
    header.totalLength_ = source.ReadU32();
    source.Read(&header.waveText_, 4);

    if (memcmp("RIFF", header.riffText_, 4) != 0 || memcmp("WAVE", header.waveText_, 4) != 0)
    {
        URHO3D_LOGERROR("Could not read WAV data from " + source.GetName());
        return false;
    }

    // Search for the FORMAT chunk
    for (;;)
    {
        source.Read(&header.formatText_, 4);
        header.formatLength_ = source.ReadU32();
        if (!memcmp("fmt ", &header.formatText_, 4))
            break;

        source.Seek(source.GetPosition() + header.formatLength_);
        if (!header.formatLength_ || source.GetPosition() >= source.GetSize())
        {
            URHO3D_LOGERROR("Could not read WAV data from " + source.GetName());
            return false;
        }
    }

    // Read the FORMAT chunk
    header.format_ = source.ReadU16();
    header.channels_ = source.ReadU16();
    header.frequency_ = source.ReadU32();
    header.avgBytes_ = source.ReadU32();
    header.blockAlign_ = source.ReadU16();
    header.bits_ = source.ReadU16();

    // Skip data if the format chunk was bigger than what we use
    source.Seek(source.GetPosition() + header.formatLength_ - 16);

    // Check for correct format
    if (header.format_ != 1)
    {
        URHO3D_LOGERROR("Could not read WAV data from " + source.GetName());
        return false;
    }

    // Search for the DATA chunk
    for (;;)
    {
        source.Read(&header.dataText_, 4);
        header.dataLength_ = source.ReadU32();
        if (!memcmp("data", &header.dataText_, 4))
            break;

        source.Seek(source.GetPosition() + header.dataLength_);
        if (!header.dataLength_ || source.GetPosition() >= source.GetSize())
        {
            URHO3D_LOGERROR("Could not read WAV data from " + source.GetName());
            return false;
        }
    }

    // Allocate sound and load audio data
    unsigned length = header.dataLength_;
    SetSize(length);
    SetFormat(header.frequency_, header.bits_ == 16, header.channels_ == 2);
    source.Read(data_.Get(), length);

    // Convert 8-bit audio to signed
    if (!sixteenBit_)
    {
        for (unsigned i = 0; i < length; ++i)
            data_[i] -= 128;
    }

    return true;
}

bool Sound::LoadRaw(Deserializer& source)
{
    unsigned dataSize = source.GetSize();
    SetSize(dataSize);
    return source.Read(data_.Get(), dataSize) == dataSize;
}

void Sound::SetSize(unsigned dataSize)
{
    if (!dataSize)
        return;

    data_ = new signed char[dataSize + IP_SAFETY];
    dataSize_ = dataSize;
    compressed_ = false;
    SetLooped(false);

    SetMemoryUse(dataSize + IP_SAFETY);
}

void Sound::SetData(const void* data, unsigned dataSize)
{
    if (!dataSize)
        return;

    SetSize(dataSize);
    memcpy(data_.Get(), data, dataSize);
}

void Sound::SetFormat(unsigned frequency, bool sixteenBit, bool stereo)
{
    frequency_ = frequency;
    sixteenBit_ = sixteenBit;
    stereo_ = stereo;
    compressed_ = false;
}

void Sound::SetLooped(bool enable)
{
    if (enable)
        SetLoop(0, dataSize_);
    else
    {
        if (!compressed_)
        {
            end_ = data_.Get() + dataSize_;
            looped_ = false;

            FixInterpolation();
        }
        else
            looped_ = false;
    }
}

void Sound::SetLoop(unsigned repeatOffset, unsigned endOffset)
{
    if (!compressed_)
    {
        if (repeatOffset > dataSize_)
            repeatOffset = dataSize_;
        if (endOffset > dataSize_)
            endOffset = dataSize_;

        // Align repeat and end on sample boundaries
        int sampleSize = GetSampleSize();
        repeatOffset &= -sampleSize;
        endOffset &= -sampleSize;

        repeat_ = data_.Get() + repeatOffset;
        end_ = data_.Get() + endOffset;
        looped_ = true;

        FixInterpolation();
    }
    else
        looped_ = true;
}

void Sound::FixInterpolation()
{
    if (!data_ || compressed_)
        return;

    // If looped, copy loop start to loop end. If oneshot, insert silence to end
    if (looped_)
    {
        for (unsigned i = 0; i < IP_SAFETY; ++i)
            end_[i] = repeat_[i];
    }
    else
    {
        for (unsigned i = 0; i < IP_SAFETY; ++i)
            end_[i] = 0;
    }
}

SharedPtr<SoundStream> Sound::GetDecoderStream() const
{
    return compressed_ ? SharedPtr<SoundStream>(new OggVorbisSoundStream(this)) : SharedPtr<SoundStream>();
}

float Sound::GetLength() const
{
    if (!compressed_)
    {
        if (!frequency_)
            return 0.0f;
        else
            return ((float)dataSize_) / GetSampleSize() / frequency_;
    }
    else
        return compressedLength_;
}

unsigned Sound::GetSampleSize() const
{
    unsigned size = 1;
    if (sixteenBit_)
        size <<= 1;
    if (stereo_)
        size <<= 1;
    return size;
}

void Sound::LoadParameters()
{
    auto* cache = GetSubsystem<ResourceCache>();
    String xmlName = ReplaceExtension(GetName(), ".xml");

    SharedPtr<XMLFile> file(cache->GetTempResource<XMLFile>(xmlName, false));
    if (!file)
        return;

    XMLElement rootElem = file->GetRoot();
    LoadMetadataFromXML(rootElem);

    for (XMLElement paramElem = rootElem.GetChild(); paramElem; paramElem = paramElem.GetNext())
    {
        String name = paramElem.GetName();

        if (name == "format" && !compressed_)
        {
            if (paramElem.HasAttribute("frequency"))
                frequency_ = (unsigned)paramElem.GetI32("frequency");
            if (paramElem.HasAttribute("sixteenbit"))
                sixteenBit_ = paramElem.GetBool("sixteenbit");
            if (paramElem.HasAttribute("16bit"))
                sixteenBit_ = paramElem.GetBool("16bit");
            if (paramElem.HasAttribute("stereo"))
                stereo_ = paramElem.GetBool("stereo");
        }

        if (name == "loop")
        {
            if (paramElem.HasAttribute("enable"))
                SetLooped(paramElem.GetBool("enable"));
            if (paramElem.HasAttribute("start") && paramElem.HasAttribute("end"))
                SetLoop((unsigned)paramElem.GetI32("start"), (unsigned)paramElem.GetI32("end"));
        }
    }
}

}
