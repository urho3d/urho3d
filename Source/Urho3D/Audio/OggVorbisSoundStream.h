//
// Copyright (c) 2008-2016 the Urho3D project.
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

#include "../Audio/SoundStream.h"
#include "../Container/ArrayPtr.h"

namespace Urho3D
{

class Sound;

/// Ogg Vorbis sound stream.
class URHO3D_API OggVorbisSoundStream : public SoundStream
{
public:
    /// Construct from an Ogg Vorbis compressed sound.
    OggVorbisSoundStream(const Sound* sound);
    /// Destruct.
    ~OggVorbisSoundStream();

    /// Produce sound data into destination. Return number of bytes produced. Called by SoundSource from the mixing thread.
    virtual unsigned GetData(signed char* dest, unsigned numBytes);

protected:
    /// Decoder state.
    void* decoder_;
    /// Compressed sound data.
    SharedArrayPtr<signed char> data_;
    /// Compressed sound data size in bytes.
    unsigned dataSize_;
};

}
