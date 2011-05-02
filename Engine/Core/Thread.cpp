//
// Urho3D Engine
// Copyright (c) 2008-2011 Lasse Öörni
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

#include "Precompiled.h"
#include "Thread.h"

#include <windows.h>

#include "DebugNew.h"

DWORD WINAPI ThreadFunctionStatic(void* data)
{
    Thread* thread = static_cast<Thread*>(data);
    thread->ThreadFunction();
    return 0;
}

Thread::Thread() :
    handle_(0),
    shouldRun_(false)
{
}

Thread::~Thread()
{
    Stop();
}

bool Thread::Start()
{
    // Check if already running
    if (handle_)
        return false;
    
    shouldRun_ = true;
    handle_ = CreateThread(0, 0, ThreadFunctionStatic, this, 0, 0);
    return handle_ != 0;
}

void Thread::Stop()
{
    shouldRun_ = false;
    WaitForSingleObject((HANDLE)handle_, INFINITE);
    CloseHandle((HANDLE)handle_);
    handle_ = 0;
}

void Thread::SetPriority(int priority)
{
    if (handle_)
        SetThreadPriority((HANDLE)handle_, priority);
}
