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
#include <Windows.h>
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
    handle_(0)
#endif
{
}

NamedPipe::NamedPipe(Context* context, const String& pipeName, bool isServer) :
    Object(context),
    isServer_(false),
#ifdef _WIN32
    handle_(INVALID_HANDLE_VALUE)
#else
    handle_(0)
#endif
{
    Open(pipeName, isServer);
}

NamedPipe::~NamedPipe()
{
    Close();
}

#ifdef _WIN32

bool NamedPipe::Open(const String& pipeName, bool isServer)
{
    URHO3D_PROFILE(OpenNamedPipe);

    const String pipePath("\\\\.\\pipe\\");

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
            isServer_ = true;
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
            URHO3D_LOGDEBUG("Connected to named pipe " + pipeName);
    }

    return true;
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

unsigned NamedPipe::Seek(unsigned position)
{
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
        
        URHO3D_LOGDEBUG("Closed named pipe " + pipeName_);
    }
}

bool NamedPipe::IsOpen() const
{
    return handle_ != INVALID_HANDLE_VALUE;
}

unsigned NamedPipe::GetAvailableSize() const
{
    if (handle_ != INVALID_HANDLE_VALUE)
    {
        DWORD bytesAvailable = 0;
        PeekNamedPipe(handle_, 0, 0, 0, &bytesAvailable, 0);
        return bytesAvailable;
    }
    
    return 0;
}

#endif

}
