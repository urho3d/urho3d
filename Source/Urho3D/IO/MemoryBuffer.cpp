// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include "../Precompiled.h"

#include "../IO/MemoryBuffer.h"

namespace Urho3D
{

MemoryBuffer::MemoryBuffer(void* data, i32 size) :
    AbstractFile(size),
    buffer_((u8*)data),
    readOnly_(false)
{
    assert(size >= 0);

    if (!buffer_)
        size_ = 0;
}

MemoryBuffer::MemoryBuffer(const void* data, i32 size) :
    AbstractFile(size),
    buffer_((u8*)data),
    readOnly_(true)
{
    assert(size >= 0);

    if (!buffer_)
        size_ = 0;
}

MemoryBuffer::MemoryBuffer(Vector<u8>& data) :
    AbstractFile(data.Size()),
    buffer_(data.Begin().ptr_),
    readOnly_(false)
{
}

MemoryBuffer::MemoryBuffer(const Vector<u8>& data) :
    AbstractFile(data.Size()),
    buffer_(const_cast<u8*>(data.Begin().ptr_)),
    readOnly_(true)
{
}

i32 MemoryBuffer::Read(void* dest, i32 size)
{
    assert(size >= 0);

    if (size + position_ > size_)
        size = size_ - position_;
    if (!size)
        return 0;

    u8* srcPtr = &buffer_[position_];
    u8* destPtr = (u8*)dest;
    position_ += size;

    memcpy(destPtr, srcPtr, size);

    return size;
}

i64 MemoryBuffer::Seek(i64 position)
{
    assert(position >= 0 && position <= M_MAX_INT);

    if (position > size_)
        position = size_;

    position_ = position;
    return position_;
}

i32 MemoryBuffer::Write(const void* data, i32 size)
{
    assert(size >= 0);

    if (size + position_ > size_)
        size = size_ - position_;
    if (!size)
        return 0;

    u8* srcPtr = (u8*)data;
    u8* destPtr = &buffer_[position_];
    position_ += size;

    memcpy(destPtr, srcPtr, size);

    return size;
}

}
