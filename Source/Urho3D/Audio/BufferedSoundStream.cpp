//
// Copyright (c) 2008-2020 the Urho3D project.
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
