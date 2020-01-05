//
// Copyright (c) 2008-2020 the Urho3D project.
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
    NamedPipe(Context* context, const String& pipeName, bool isServer);
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
    /// Return the pipe name.
    const String& GetName() const override { return pipeName_; }

    /// Open the pipe in either server or client mode. If already open, the existing pipe is closed. For a client end to open successfully the server end must already to be open. Return true if successful.
    bool Open(const String& pipeName, bool isServer);
    /// Close the pipe. Note that once a client has disconnected, the server needs to close and reopen the pipe so that another client can connect. At least on Windows this is not possible to detect automatically, so the communication protocol should include a "bye" message to handle this situation.
    void Close();

    /// Return whether is open.
    bool IsOpen() const;
    /// Return whether is in server mode.
    bool IsServer() const { return isServer_; }

private:
    /// Pipe name.
    String pipeName_;
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
