// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include "../Precompiled.h"

#include "../IO/MemoryBuffer.h"

namespace Urho3D
{

MemoryBuffer::MemoryBuffer(void* data, unsigned size) :
    AbstractFile(size),
    buffer_((unsigned char*)data),
    readOnly_(false)
{
    if (!buffer_)
        size_ = 0;
}

MemoryBuffer::MemoryBuffer(const void* data, unsigned size) :
    AbstractFile(size),
    buffer_((unsigned char*)data),
    readOnly_(true)
{
    if (!buffer_)
        size_ = 0;
}

MemoryBuffer::MemoryBuffer(PODVector<unsigned char>& data) :
    AbstractFile(data.Size()),
    buffer_(data.Begin().ptr_),
    readOnly_(false)
{
}

MemoryBuffer::MemoryBuffer(const PODVector<unsigned char>& data) :
    AbstractFile(data.Size()),
    buffer_(const_cast<unsigned char*>(data.Begin().ptr_)),
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
    auto* destPtr = (unsigned char*)dest;
    position_ += size;

    memcpy(destPtr, srcPtr, size);

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

    auto* srcPtr = (unsigned char*)data;
    unsigned char* destPtr = &buffer_[position_];
    position_ += size;

    memcpy(destPtr, srcPtr, size);

    return size;
}

}
