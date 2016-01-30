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

#include "../Container/RefCounted.h"

namespace Urho3D
{

/// Base class for sound streams.
class URHO3D_API SoundStream : public RefCounted
{
public:
    /// Construct.
    SoundStream();
    /// Destruct.
    ~SoundStream();

    /// Produce sound data into destination. Return number of bytes produced. Called by SoundSource from the mixing thread.
    virtual unsigned GetData(signed char* dest, unsigned numBytes) = 0;

    /// Set sound data format.
    void SetFormat(unsigned frequency, bool sixteenBit, bool stereo);
    /// Set whether playback should stop when no more data. Default false.
    void SetStopAtEnd(bool enable);

    /// Return sample size.
    unsigned GetSampleSize() const;

    /// Return default frequency as a float.
    float GetFrequency() const { return (float)frequency_; }

    /// Return default frequency as an integer.
    unsigned GetIntFrequency() const { return frequency_; }

    /// Return whether playback should stop when no more data.
    bool GetStopAtEnd() const { return stopAtEnd_; }

    /// Return whether data is sixteen bit.
    bool IsSixteenBit() const { return sixteenBit_; }

    /// Return whether data is stereo.
    bool IsStereo() const { return stereo_; }

protected:
    /// Default frequency.
    unsigned frequency_;
    /// Stop when no more data flag.
    bool stopAtEnd_;
    /// Sixteen bit flag.
    bool sixteenBit_;
    /// Stereo flag.
    bool stereo_;
};

}
