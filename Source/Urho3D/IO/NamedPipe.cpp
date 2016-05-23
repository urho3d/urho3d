//
// Copyright (c) 2008-2016 the Urho3D project.
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

#include "../Precompiled.h"

#include "../Core/Profiler.h"
#include "../IO/NamedPipe.h"
#include "../IO/Log.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <fcntl.h>
#include <sys/stat.h>
#include <signal.h>
#include <unistd.h>
#endif

#include "../DebugNew.h"

namespace Urho3D
{

static const unsigned PIPE_BUFFER_SIZE = 65536;

NamedPipe::NamedPipe(Context* context) :
    Object(context),
    isServer_(false),
#ifdef _WIN32
    handle_(INVALID_HANDLE_VALUE)
#else
    readHandle_(-1),
    writeHandle_(-1)
#endif
{
}

NamedPipe::NamedPipe(Context* context, const String& pipeName, bool isServer) :
    Object(context),
    isServer_(false),
#ifdef _WIN32
    handle_(INVALID_HANDLE_VALUE)
#else
    readHandle_(-1),
    writeHandle_(-1)
#endif
{
    Open(pipeName, isServer);
}

NamedPipe::~NamedPipe()
{
    Close();
}

unsigned NamedPipe::Seek(unsigned position)
{
    return 0;
}

#ifdef _WIN32

static const String pipePath("\\\\.\\pipe\\");

bool NamedPipe::Open(const String& pipeName, bool isServer)
{
    URHO3D_PROFILE(OpenNamedPipe);

    Close();

    isServer_ = false;

    if (isServer)
    {
        handle_ = CreateNamedPipeW(WString(pipePath + pipeName).CString(),
            PIPE_ACCESS_DUPLEX,
            PIPE_TYPE_BYTE | PIPE_READMODE_BYTE | PIPE_NOWAIT,
            1,
            PIPE_BUFFER_SIZE,
            PIPE_BUFFER_SIZE,
            0,
            0
        );

        if (handle_ == INVALID_HANDLE_VALUE)
        {
            URHO3D_LOGERROR("Failed to create named pipe " + pipeName);
            return false;
        }
        else
        {
            URHO3D_LOGDEBUG("Created named pipe " + pipeName);
            pipeName_ = pipeName;
            isServer_ = true;
            return true;
        }
    }
    else
    {
        handle_ = CreateFileW(
            WString(pipePath + pipeName).CString(),
            GENERIC_READ | GENERIC_WRITE,
            0,
            0,
            OPEN_EXISTING,
            0,
            0
        );

        if (handle_ == INVALID_HANDLE_VALUE)
        {
            URHO3D_LOGERROR("Failed to connect to named pipe " + pipeName);
            return false;
        }
        else
        {
            URHO3D_LOGDEBUG("Connected to named pipe " + pipeName);
            pipeName_ = pipeName;
            return true;
        }
    }
}

unsigned NamedPipe::Read(void* dest, unsigned size)
{
    if (handle_ != INVALID_HANDLE_VALUE)
    {
        DWORD read = 0;
        ReadFile(handle_, dest, size, &read, 0);
        return read;
    }

    return 0;
}

unsigned NamedPipe::Write(const void* data, unsigned size)
{
    if (handle_ != INVALID_HANDLE_VALUE)
    {
        DWORD written = 0;
        WriteFile(handle_, data, size, &written, 0);
        return written;
    }

    return 0;
}

void NamedPipe::Close()
{
    if (handle_ != INVALID_HANDLE_VALUE)
    {
        URHO3D_PROFILE(CloseNamedPipe);

        if (isServer_)
        {
            DisconnectNamedPipe(handle_);
            isServer_ = false;
        }

        CloseHandle(handle_);
        handle_ = INVALID_HANDLE_VALUE;
        pipeName_.Clear();

        URHO3D_LOGDEBUG("Closed named pipe " + pipeName_);
    }
}

bool NamedPipe::IsOpen() const
{
    return handle_ != INVALID_HANDLE_VALUE;
}

bool NamedPipe::IsEof() const
{
    if (handle_ != INVALID_HANDLE_VALUE)
    {
        DWORD bytesAvailable = 0;
        PeekNamedPipe(handle_, 0, 0, 0, &bytesAvailable, 0);
        return bytesAvailable == 0;
    }
    else
        return true;
}

#else

static const String pipePath("/tmp/");

#define SAFE_CLOSE(handle) if (handle != -1) { close(handle); handle = -1; }

bool NamedPipe::Open(const String& pipeName, bool isServer)
{
#ifdef __EMSCRIPTEN__
    URHO3D_LOGERROR("Opening a named pipe not supported on Web platform");
    return false;
#else
    URHO3D_PROFILE(OpenNamedPipe);

    Close();

    isServer_ = false;

    String serverReadName = pipePath + pipeName + "SR";
    String clientReadName = pipePath + pipeName + "CR";

    // Make sure SIGPIPE is ignored and will not lead to process termination
    signal(SIGPIPE, SIG_IGN);

    if (isServer)
    {
        mkfifo(serverReadName.CString(), 0660);
        mkfifo(clientReadName.CString(), 0660);

        readHandle_ = open(serverReadName.CString(), O_RDONLY | O_NDELAY);
        writeHandle_ = open(clientReadName.CString(), O_WRONLY | O_NDELAY);

        if (readHandle_ == -1 && writeHandle_ == -1)
        {
            URHO3D_LOGERROR("Failed to create named pipe " + pipeName);
            SAFE_CLOSE(readHandle_);
            SAFE_CLOSE(writeHandle_);
            unlink(serverReadName.CString());
            unlink(clientReadName.CString());
            return false;
        }
        else
        {
            URHO3D_LOGDEBUG("Created named pipe " + pipeName);
            pipeName_ = pipeName;
            isServer_ = true;
            return true;
        }
    }
    else
    {
        readHandle_ = open(clientReadName.CString(), O_RDONLY | O_NDELAY);
        writeHandle_ = open(serverReadName.CString(), O_WRONLY | O_NDELAY);
        if (readHandle_ == -1 && writeHandle_ == -1)
        {
            URHO3D_LOGERROR("Failed to connect to named pipe " + pipeName);
            SAFE_CLOSE(readHandle_);
            SAFE_CLOSE(writeHandle_);
            return false;
        }
        else
        {
            URHO3D_LOGDEBUG("Connected to named pipe " + pipeName);
            pipeName_ = pipeName;
            return true;
        }
    }
#endif
}

unsigned NamedPipe::Read(void* dest, unsigned size)
{
    // Attempt to open late if only the write handle is open yet
    if (readHandle_ == -1 && writeHandle_ != -1)
    {
        if (isServer_)
            readHandle_ = open((pipePath + pipeName_ + "SR").CString(), O_RDONLY | O_NDELAY);
        else
            readHandle_ = open((pipePath + pipeName_ + "CR").CString(), O_RDONLY | O_NDELAY);
    }

    if (readHandle_ != -1)
    {
        ssize_t readNow = read(readHandle_, dest, size);
        return readNow < 0 ? 0 : (unsigned)readNow;
    }
    else
        return 0;
}

unsigned NamedPipe::Write(const void* data, unsigned size)
{
    // Attempt to open late if only the read handle is open yet
    if (writeHandle_ == -1 && readHandle_ != -1)
    {
        if (isServer_)
            writeHandle_ = open((pipePath + pipeName_ + "CR").CString(), O_WRONLY | O_NDELAY);
        else
            writeHandle_ = open((pipePath + pipeName_ + "SR").CString(), O_WRONLY | O_NDELAY);
    }

    // Loop until all bytes written in case of partial write
    if (writeHandle_ != -1)
    {
        ssize_t written = 0;
        while (written < (ssize_t)size)
        {
            ssize_t writtenNow = write(writeHandle_, ((const unsigned char*)data) + written, size - written);
            if (writtenNow < 0)
                return 0; // Error while writing
            written += writtenNow;
        }

        return (unsigned)written;
    }
    else
        return 0;
}

void NamedPipe::Close()
{
    if (readHandle_ != -1 || writeHandle_ != -1)
    {
        URHO3D_PROFILE(CloseNamedPipe);
        SAFE_CLOSE(readHandle_);
        SAFE_CLOSE(writeHandle_);

        if (isServer_)
        {
            String serverReadName = pipePath + pipeName_ + "SR";
            String clientReadName = pipePath + pipeName_ + "CR";
            unlink(serverReadName.CString());
            unlink(clientReadName.CString());
            isServer_ = false;
        }

        pipeName_.Clear();
    }
}

bool NamedPipe::IsOpen() const
{
    return readHandle_ != -1 || writeHandle_ != -1;
}

bool NamedPipe::IsEof() const
{
#ifdef __EMSCRIPTEN__
    return true;
#else
    // Attempt to open late if only the write handle is open yet
    if (readHandle_ == -1 && writeHandle_ != -1)
    {
        if (isServer_)
            readHandle_ = open((pipePath + pipeName_ + "SR").CString(), O_RDONLY | O_NDELAY);
        else
            readHandle_ = open((pipePath + pipeName_ + "CR").CString(), O_RDONLY | O_NDELAY);
    }

    if (readHandle_ != -1)
    {
        fd_set set;
        FD_ZERO(&set);
        FD_SET(readHandle_, &set);

        struct timeval timeout;
        timeout.tv_sec = 0;
        timeout.tv_usec = 1000; // 1ms timeout for select

        return select(readHandle_ + 1, &set, 0, 0, &timeout) <= 0;
    }
    else
        return true;
#endif
}
#endif

}
