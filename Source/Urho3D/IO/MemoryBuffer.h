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
    MemoryBuffer(void* data, unsigned size);
    /// Construct as read-only with a pointer and size.
    MemoryBuffer(const void* data, unsigned size);
    /// Construct from a vector, which must not go out of scope before MemoryBuffer.
    explicit MemoryBuffer(PODVector<unsigned char>& data);
    /// Construct from a read-only vector, which must not go out of scope before MemoryBuffer.
    explicit MemoryBuffer(const PODVector<unsigned char>& data);

    /// Read bytes from the memory area. Return number of bytes actually read.
    unsigned Read(void* dest, unsigned size) override;
    /// Set position from the beginning of the memory area. Return actual new position.
    unsigned Seek(unsigned position) override;
    /// Write bytes to the memory area.
    unsigned Write(const void* data, unsigned size) override;

    /// Return memory area.
    unsigned char* GetData() { return buffer_; }

    /// Return whether buffer is read-only.
    bool IsReadOnly() { return readOnly_; }

private:
    /// Pointer to the memory area.
    unsigned char* buffer_;
    /// Read-only flag.
    bool readOnly_;
};

}
