// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include "../Precompiled.h"

#include "../IO/VectorBuffer.h"

namespace Urho3D
{

VectorBuffer::VectorBuffer() = default;

VectorBuffer::VectorBuffer(const Vector<u8>& data)
{
    SetData(data);
}

VectorBuffer::VectorBuffer(const void* data, unsigned size)
{
    SetData(data, size);
}

VectorBuffer::VectorBuffer(Deserializer& source, unsigned size)
{
    SetData(source, size);
}

unsigned VectorBuffer::Read(void* dest, unsigned size)
{
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

unsigned VectorBuffer::Seek(unsigned position)
{
    if (position > size_)
        position = size_;

    position_ = position;
    return position_;
}

i32 VectorBuffer::Write(const void* data, i32 size)
{
    assert(size >= 0);

    if (!size)
        return 0;

    if (size + position_ > size_)
    {
        size_ = size + position_;
        buffer_.Resize(size_);
    }

    u8* srcPtr = (u8*)data;
    u8* destPtr = &buffer_[position_];
    position_ += size;

    memcpy(destPtr, srcPtr, size);

    return size;
}

void VectorBuffer::SetData(const Vector<u8>& data)
{
    buffer_ = data;
    position_ = 0;
    size_ = data.Size();
}

void VectorBuffer::SetData(const void* data, unsigned size)
{
    if (!data)
        size = 0;

    buffer_.Resize(size);
    if (size)
        memcpy(&buffer_[0], data, size);

    position_ = 0;
    size_ = size;
}

void VectorBuffer::SetData(Deserializer& source, unsigned size)
{
    buffer_.Resize(size);
    unsigned actualSize = source.Read(&buffer_[0], size);
    if (actualSize != size)
        buffer_.Resize(actualSize);

    position_ = 0;
    size_ = actualSize;
}

void VectorBuffer::Clear()
{
    buffer_.Clear();
    position_ = 0;
    size_ = 0;
}

void VectorBuffer::Resize(unsigned size)
{
    buffer_.Resize(size);
    size_ = size;
    if (position_ > size_)
        position_ = size_;
}

}
