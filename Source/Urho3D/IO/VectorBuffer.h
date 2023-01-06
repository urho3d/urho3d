// Copyright (c) 2008-2023 the Urho3D project
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
    explicit VectorBuffer(const Vector<byte>& data);
    /// Construct from a memory area.
    VectorBuffer(const void* data, i32 size);
    /// Construct from a stream.
    VectorBuffer(Deserializer& source, i32 size);

    /// Read bytes from the buffer. Return number of bytes actually read.
    i32 Read(void* dest, i32 size) override;
    /// Set position from the beginning of the buffer. Return actual new position.
    i64 Seek(i64 position) override;
    /// Write bytes to the buffer. Return number of bytes actually written.
    i32 Write(const void* data, i32 size) override;

    /// Set data from another buffer.
    void SetData(const Vector<byte>& data);
    /// Set data from a memory area.
    void SetData(const void* data, i32 size);
    /// Set data from a stream.
    void SetData(Deserializer& source, i32 size);
    /// Reset to zero size.
    void Clear();
    /// Set size.
    void Resize(i32 size);

    /// Return data.
    const byte* GetData() const { return size_ ? &buffer_[0] : nullptr; }

    /// Return non-const data.
    byte* GetModifiableData() { return size_ ? &buffer_[0] : nullptr; }

    /// Return the buffer.
    const Vector<byte>& GetBuffer() const { return buffer_; }

private:
    /// Dynamic data buffer.
    Vector<byte> buffer_;
};

}
