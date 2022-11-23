// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include "../Precompiled.h"

#include "../IO/VectorBuffer.h"

namespace Urho3D
{

VectorBuffer::VectorBuffer() = default;

VectorBuffer::VectorBuffer(const Vector<byte>& data)
{
    SetData(data);
}

VectorBuffer::VectorBuffer(const void* data, i32 size)
{
    assert(size >= 0);

    SetData(data, size);
}

VectorBuffer::VectorBuffer(Deserializer& source, i32 size)
{
    assert(size >= 0);

    SetData(source, size);
}

i32 VectorBuffer::Read(void* dest, i32 size)
{
    assert(size >= 0);

    if (size + position_ > size_)
        size = size_ - position_;
    if (!size)
        return 0;

    byte* srcPtr = &buffer_[position_];
    byte* destPtr = (byte*)dest;
    position_ += size;

    memcpy(destPtr, srcPtr, size);

    return size;
}

i64 VectorBuffer::Seek(i64 position)
{
    assert(position >= 0 && position <= M_MAX_INT);

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

    byte* srcPtr = (byte*)data;
    byte* destPtr = &buffer_[position_];
    position_ += size;

    memcpy(destPtr, srcPtr, size);

    return size;
}

void VectorBuffer::SetData(const Vector<byte>& data)
{
    buffer_ = data;
    position_ = 0;
    size_ = data.Size();
}

void VectorBuffer::SetData(const void* data, i32 size)
{
    assert(size >= 0);

    if (!data)
        size = 0;

    buffer_.Resize(size);
    if (size)
        memcpy(&buffer_[0], data, size);

    position_ = 0;
    size_ = size;
}

void VectorBuffer::SetData(Deserializer& source, i32 size)
{
    assert(size >= 0);

    buffer_.Resize(size);
    i32 actualSize = (i32)source.Read(&buffer_[0], size);
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

void VectorBuffer::Resize(i32 size)
{
    assert(size >= 0);

    buffer_.Resize(size);
    size_ = size;
    if (position_ > size_)
        position_ = size_;
}

}
