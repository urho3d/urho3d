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

#pragma once

#include "../Container/ArrayPtr.h"
#include "../Resource/Resource.h"

namespace Urho3D
{

class SoundStream;

/// %Sound resource.
class URHO3D_API Sound : public Resource
{
    OBJECT(Sound);
    
public:
    /// Construct.
    Sound(Context* context);
    /// Destruct and free sound data.
    virtual ~Sound();
    /// Register object factory.
    static void RegisterObject(Context* context);
    
    /// Load resource from stream. May be called from a worker thread. Return true if successful.
    virtual bool BeginLoad(Deserializer& source);
    
    /// Load raw sound data.
    bool LoadRaw(Deserializer& source);
    /// Load WAV format sound data.
    bool LoadWav(Deserializer& source);
    /// Load Ogg Vorbis format sound data. Does not decode at load, but will rather be decoded while playing.
    bool LoadOggVorbis(Deserializer& source);
    /// Set sound size in bytes. Also resets the sound to be uncompressed and one-shot.
    void SetSize(unsigned dataSize);
    /// Set uncompressed sound data.
    void SetData(const void* data, unsigned dataSize);
    /// Set uncompressed sound data format.
    void SetFormat(unsigned frequency, bool sixteenBit, bool stereo);
    /// Set loop on/off. If loop is enabled, sets the full sound as loop range.
    void SetLooped(bool enable);
    /// Define loop.
    void SetLoop(unsigned repeatOffset, unsigned endOffset);
    /// Fix interpolation by copying data from loop start to loop end (looped), or adding silence (oneshot.)
    void FixInterpolation();
    
    /// Return a new instance of a decoder sound stream. Used by compressed sounds.
    SharedPtr<SoundStream> GetDecoderStream() const;
    /// Return shared sound data.
    SharedArrayPtr<signed char> GetData() const { return data_; }
    /// Return sound data start.
    signed char* GetStart() const { return data_.Get(); }
    /// Return loop start.
    signed char* GetRepeat() const { return repeat_; }
    /// Return sound data end.
    signed char* GetEnd() const { return end_; }
    /// Return length in seconds.
    float GetLength() const;
    /// Return total sound data size.
    unsigned GetDataSize() const { return dataSize_; }
    /// Return sample size.
    unsigned GetSampleSize() const;
    /// Return default frequency as a float.
    float GetFrequency() const { return (float)frequency_; }
    /// Return default frequency as an integer.
    unsigned GetIntFrequency() const { return frequency_; }
    /// Return whether is looped.
    bool IsLooped() const { return looped_; }
    /// Return whether data is sixteen bit.
    bool IsSixteenBit() const { return sixteenBit_; }
    /// Return whether data is stereo.
    bool IsStereo() const { return stereo_; }
    /// Return whether is compressed.
    bool IsCompressed() const { return compressed_; }
    
private:
    /// Load optional parameters from an XML file.
    void LoadParameters();
    
    /// Sound data.
    SharedArrayPtr<signed char> data_;
    /// Loop start.
    signed char* repeat_;
    /// Sound data end.
    signed char* end_;
    /// Sound data size in bytes.
    unsigned dataSize_;
    /// Default frequency.
    unsigned frequency_;
    /// Looped flag.
    bool looped_;
    /// Sixteen bit flag.
    bool sixteenBit_;
    /// Stereo flag.
    bool stereo_;
    /// Compressed flag.
    bool compressed_;
    /// Compressed sound length.
    float compressedLength_;
};

}
