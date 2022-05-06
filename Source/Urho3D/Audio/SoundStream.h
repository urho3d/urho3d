// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

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
    ~SoundStream() override;

    /// Seek to sample number. Return true on success. Need not be implemented by all streams.
    virtual bool Seek(unsigned sample_number);

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
