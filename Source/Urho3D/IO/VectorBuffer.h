// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include "../IO/AbstractFile.h"

namespace Urho3D
{

/// Dynamically sized buffer that can be read and written to as a stream.
class URHO3D_API VectorBuffer : public AbstractFile
{
public:
    /// Construct an empty buffer.
    VectorBuffer();
    /// Construct from another buffer.
    explicit VectorBuffer(const Vector<u8>& data);
    /// Construct from a memory area.
    VectorBuffer(const void* data, i32 size);
    /// Construct from a stream.
    VectorBuffer(Deserializer& source, i32 size);

    /// Read bytes from the buffer. Return number of bytes actually read.
    unsigned Read(void* dest, unsigned size) override;
    /// Set position from the beginning of the buffer. Return actual new position.
    unsigned Seek(unsigned position) override;
    /// Write bytes to the buffer. Return number of bytes actually written.
    i32 Write(const void* data, i32 size) override;

    /// Set data from another buffer.
    void SetData(const Vector<u8>& data);
    /// Set data from a memory area.
    void SetData(const void* data, i32 size);
    /// Set data from a stream.
    void SetData(Deserializer& source, i32 size);
    /// Reset to zero size.
    void Clear();
    /// Set size.
    void Resize(i32 size);

    /// Return data.
    const u8* GetData() const { return size_ ? &buffer_[0] : nullptr; }

    /// Return non-const data.
    u8* GetModifiableData() { return size_ ? &buffer_[0] : nullptr; }

    /// Return the buffer.
    const Vector<u8>& GetBuffer() const { return buffer_; }

private:
    /// Dynamic data buffer.
    Vector<u8> buffer_;
};

}
