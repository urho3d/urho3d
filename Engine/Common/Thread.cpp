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

DWORD WINAPI threadFunctionStatic(void* data)
{
    Thread* thread = static_cast<Thread*>(data);
    thread->threadFunction();
    return 0;
}

Thread::Thread() :
    mThreadHandle(0),
    mShouldRun(false)
{
}

Thread::~Thread()
{
    stopThread();
}

bool Thread::startThread()
{
    // Check if already running
    if (mThreadHandle)
        return false;
    
    mShouldRun = true;
    mThreadHandle = CreateThread(0, 0, threadFunctionStatic, this, 0, 0);
    return mThreadHandle != 0;
}

void Thread::stopThread()
{
    mShouldRun = false;
    WaitForSingleObject((HANDLE)mThreadHandle, INFINITE);
    CloseHandle((HANDLE)mThreadHandle);
    mThreadHandle = 0;
}

void Thread::setThreadPriority(int priority)
{
    if (mThreadHandle)
        SetThreadPriority((HANDLE)mThreadHandle, priority);
}
