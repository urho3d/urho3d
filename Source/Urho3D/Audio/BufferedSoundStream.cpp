// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include "../Precompiled.h"

#include "../Audio/BufferedSoundStream.h"

#include "../DebugNew.h"

namespace Urho3D
{

BufferedSoundStream::BufferedSoundStream() :
    position_(0)
{
}

BufferedSoundStream::~BufferedSoundStream() = default;

unsigned BufferedSoundStream::GetData(signed char* dest, unsigned numBytes)
{
    MutexLock lock(bufferMutex_);

    unsigned outBytes = 0;

    while (numBytes && buffers_.Size())
    {
        // Copy as much from the front buffer as possible, then discard it and move to the next
        List<Pair<SharedArrayPtr<signed char>, unsigned> >::Iterator front = buffers_.Begin();

        unsigned copySize = front->second_ - position_;
        if (copySize > numBytes)
            copySize = numBytes;

        memcpy(dest, front->first_.Get() + position_, copySize);
        position_ += copySize;
        if (position_ >= front->second_)
        {
            buffers_.PopFront();
            position_ = 0;
        }

        dest += copySize;
        outBytes += copySize;
        numBytes -= copySize;
    }

    return outBytes;
}

void BufferedSoundStream::AddData(void* data, unsigned numBytes)
{
    if (data && numBytes)
    {
        MutexLock lock(bufferMutex_);

        SharedArrayPtr<signed char> newBuffer(new signed char[numBytes]);
        memcpy(newBuffer.Get(), data, numBytes);
        buffers_.Push(MakePair(newBuffer, numBytes));
    }
}

void BufferedSoundStream::AddData(const SharedArrayPtr<signed char>& data, unsigned numBytes)
{
    if (data && numBytes)
    {
        MutexLock lock(bufferMutex_);

        buffers_.Push(MakePair(data, numBytes));
    }
}

void BufferedSoundStream::AddData(const SharedArrayPtr<signed short>& data, unsigned numBytes)
{
    if (data && numBytes)
    {
        MutexLock lock(bufferMutex_);

        buffers_.Push(MakePair(ReinterpretCast<signed char>(data), numBytes));
    }
}

void BufferedSoundStream::Clear()
{
    MutexLock lock(bufferMutex_);

    buffers_.Clear();
    position_ = 0;
}

unsigned BufferedSoundStream::GetBufferNumBytes() const
{
    MutexLock lock(bufferMutex_);

    unsigned ret = 0;
    for (List<Pair<SharedArrayPtr<signed char>, unsigned> >::ConstIterator i = buffers_.Begin(); i != buffers_.End(); ++i)
        ret += i->second_;
    // Subtract amount of sound data played from the front buffer
    ret -= position_;

    return ret;
}

float BufferedSoundStream::GetBufferLength() const
{
    return (float)GetBufferNumBytes() / (GetFrequency() * (float)GetSampleSize());
}

}
