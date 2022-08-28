// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include "../IO/AbstractFile.h"

namespace Urho3D
{

/// Memory area that can be read and written to as a stream.
/// @nobind
class URHO3D_API MemoryBuffer : public AbstractFile
{
public:
    /// Construct with a pointer and size.
    MemoryBuffer(void* data, i32 size);
    /// Construct as read-only with a pointer and size.
    MemoryBuffer(const void* data, i32 size);
    /// Construct from a vector, which must not go out of scope before MemoryBuffer.
    explicit MemoryBuffer(Vector<u8>& data);
    /// Construct from a read-only vector, which must not go out of scope before MemoryBuffer.
    explicit MemoryBuffer(const Vector<u8>& data);

    /// Read bytes from the memory area. Return number of bytes actually read.
    i32 Read(void* dest, i32 size) override;
    /// Set position from the beginning of the memory area. Return actual new position.
    i64 Seek(i64 position) override;
    /// Write bytes to the memory area.
    i32 Write(const void* data, i32 size) override;

    /// Return memory area.
    u8* GetData() { return buffer_; }

    /// Return whether buffer is read-only.
    bool IsReadOnly() { return readOnly_; }

private:
    /// Pointer to the memory area.
    u8* buffer_;
    /// Read-only flag.
    bool readOnly_;
};

}
