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

#include "../Precompiled.h"

#include "../IO/MemoryBuffer.h"

namespace Urho3D
{

MemoryBuffer::MemoryBuffer(void* data, unsigned size) :
    Deserializer(size),
    buffer_((unsigned char*)data),
    readOnly_(false)
{
    if (!buffer_)
        size_ = 0;
}

MemoryBuffer::MemoryBuffer(const void* data, unsigned size) :
    Deserializer(size),
    buffer_((unsigned char*)data),
    readOnly_(true)
{
    if (!buffer_)
        size_ = 0;
}

MemoryBuffer::MemoryBuffer(PODVector<unsigned char>& data) :
    Deserializer(data.Size()),
    buffer_(data.Begin().ptr_),
    readOnly_(false)
{
}

MemoryBuffer::MemoryBuffer(const PODVector<unsigned char>& data) :
    Deserializer(data.Size()),
    buffer_(data.Begin().ptr_),
    readOnly_(true)
{
}

unsigned MemoryBuffer::Read(void* dest, unsigned size)
{
    if (size + position_ > size_)
        size = size_ - position_;
    if (!size)
        return 0;

    unsigned char* srcPtr = &buffer_[position_];
    unsigned char* destPtr = (unsigned char*)dest;
    position_ += size;

    unsigned copySize = size;
    while (copySize >= sizeof(unsigned))
    {
        *((unsigned*)destPtr) = *((unsigned*)srcPtr);
        srcPtr += sizeof(unsigned);
        destPtr += sizeof(unsigned);
        copySize -= sizeof(unsigned);
    }
    if (copySize & sizeof(unsigned short))
    {
        *((unsigned short*)destPtr) = *((unsigned short*)srcPtr);
        srcPtr += sizeof(unsigned short);
        destPtr += sizeof(unsigned short);
    }
    if (copySize & 1)
        *destPtr = *srcPtr;

    return size;
}

unsigned MemoryBuffer::Seek(unsigned position)
{
    if (position > size_)
        position = size_;

    position_ = position;
    return position_;
}

unsigned MemoryBuffer::Write(const void* data, unsigned size)
{
    if (size + position_ > size_)
        size = size_ - position_;
    if (!size)
        return 0;

    unsigned char* srcPtr = (unsigned char*)data;
    unsigned char* destPtr = &buffer_[position_];
    position_ += size;

    unsigned copySize = size;
    while (copySize >= sizeof(unsigned))
    {
        *((unsigned*)destPtr) = *((unsigned*)srcPtr);
        srcPtr += sizeof(unsigned);
        destPtr += sizeof(unsigned);
        copySize -= sizeof(unsigned);
    }
    if (copySize & sizeof(unsigned short))
    {
        *((unsigned short*)destPtr) = *((unsigned short*)srcPtr);
        srcPtr += sizeof(unsigned short);
        destPtr += sizeof(unsigned short);
    }
    if (copySize & 1)
        *destPtr = *srcPtr;

    return size;
}

}
