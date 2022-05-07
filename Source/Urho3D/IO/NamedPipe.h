// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include "../Container/ArrayPtr.h"
#include "../Core/Object.h"
#include "../IO/AbstractFile.h"

#ifdef __ANDROID__
#include <SDL/SDL_rwops.h>
#endif

namespace Urho3D
{

/// Named pipe for interprocess communication.
class URHO3D_API NamedPipe : public Object, public AbstractFile
{
    URHO3D_OBJECT(NamedPipe, Object);

public:
    /// Construct.
    explicit NamedPipe(Context* context);
    /// Construct and open in either server or client mode.
    NamedPipe(Context* context, const String& name, bool isServer);
    /// Destruct and close.
    ~NamedPipe() override;

    /// Read bytes from the pipe without blocking if there is less data available. Return number of bytes actually read.
    unsigned Read(void* dest, unsigned size) override;
    /// Set position. No-op for pipes.
    unsigned Seek(unsigned position) override;
    /// Write bytes to the pipe. Return number of bytes actually written.
    unsigned Write(const void* data, unsigned size) override;
    /// Return whether pipe has no data available.
    bool IsEof() const override;
    /// Not supported.
    void SetName(const String& name) override;

    /// Open the pipe in either server or client mode. If already open, the existing pipe is closed. For a client end to open successfully the server end must already to be open. Return true if successful.
    bool Open(const String& name, bool isServer);
    /// Close the pipe. Note that once a client has disconnected, the server needs to close and reopen the pipe so that another client can connect. At least on Windows this is not possible to detect automatically, so the communication protocol should include a "bye" message to handle this situation.
    void Close();

    /// Return whether is open.
    /// @property
    bool IsOpen() const;
    /// Return whether is in server mode.
    /// @property
    bool IsServer() const { return isServer_; }

private:
    /// Server mode flag.
    bool isServer_;
    /// Pipe handle.
#ifdef _WIN32
    void* handle_;
#else
    mutable int readHandle_;
    mutable int writeHandle_;
#endif
};

}
