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

#ifndef AUDIO_SOUND_H
#define AUDIO_SOUND_H

#include "Resource.h"
#include "SharedArrayPtr.h"

//! A sound resource
class Sound : public Resource
{
    DEFINE_TYPE(Sound);
    
public:
    //! Construct with name
    Sound(const std::string& name = std::string());
    //! Destruct and free sound data
    virtual ~Sound();
    
    //! Load resource. Throw exception on error
    virtual void load(Deserializer& source, ResourceCache* cache = 0);
    
    //! Load raw sound data
    void loadRaw(Deserializer& source);
    //! Load WAV format sound data
    void loadWav(Deserializer& source);
    //! Load Ogg Vorbis format sound data. Does not decode at load, will be decoded while playing
    void loadOggVorbis(Deserializer& source);
    //! Set sound size in bytes. Also resets the sound to be uncompressed and one-shot
    void setSize(unsigned dataSize);
    //! Set uncompressed sound data
    void setData(const void* data, unsigned dataSize);
    //! Set uncompressed sound data format
    void setFormat(unsigned frequency, bool sixteenBit, bool stereo);
    //! Set sound to be one-shot
    void setOneshot();
    //! Set sound to be looping
    void setLooped();
    //! Define loop
    void setLoop(unsigned repeatOffset, unsigned endOffset);
    //! Fix interpolation by copying data from loop start to loop end (looped), or adding silence (oneshot)
    void fixInterpolation();
    
    //! Create and return a decoder. Return null if fails
    void* allocateDecoder();
    //! Decode compressed audio data. Return number of actually decoded bytes
    unsigned decode(void* decoder, signed char* dest, unsigned bytes);
    //! Rewind decoder to beginning of audio data
    void rewindDecoder(void* decoder);
    //! Free decoder
    void freeDecoder(void* decoder);
    
    //! Return sound data start
    signed char* getStart() const { return mData.getPtr(); }
    //! Return loop start
    signed char* getRepeat() const { return mRepeat; }
    //! Return sound data end
    signed char* getEnd() const { return mEnd; }
    //! Return length in seconds
    float getLength() const;
    //! Return total sound data size
    unsigned getDataSize() const { return mDataSize; }
    //! Return sample size
    unsigned getSampleSize() const;
    //! Return default frequency
    float getFrequency() { return (float)mFrequency; }
    //! Return default frequency
    unsigned getIntFrequency() { return mFrequency; }
    //! Return whether is looped
    bool isLooped() const { return mLooped; }
    //! Return whether data is sixteen bit
    bool isSixteenBit() const { return mSixteenBit; }
    //! Return whether data is stereo
    bool isStereo() const { return mStereo; }
    //! Return whether is compressed in Ogg Vorbis format
    bool isCompressed() const { return mCompressed; }
    
private:
    //! Load optional parameters from an XML file
    void loadParameters(ResourceCache* cache);
    
    //! Sound data
    SharedArrayPtr<signed char> mData;
    //! Loop start
    signed char* mRepeat;
    //! Sound data end
    signed char* mEnd;
    //! Sound data size in bytes
    unsigned mDataSize;
    //! Default frequency
    unsigned mFrequency;
    //! Looped flag
    bool mLooped;
    //! Sixteen bit flag
    bool mSixteenBit;
    //! Stereo flag
    bool mStereo;
    //! Compressed flag
    bool mCompressed;
    //! Compressed sound length
    float mCompressedLength;
};

#endif // AUDIO_SOUND_H
