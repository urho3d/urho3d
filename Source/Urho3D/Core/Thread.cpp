//
// Copyright (c) 2008-2015 the Urho3D project.
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

#include "../Core/Thread.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <pthread.h>
#endif

#include "../DebugNew.h"

namespace Urho3D
{

#ifdef URHO3D_THREADING
#ifdef _WIN32

DWORD WINAPI ThreadFunctionStatic(void* data)
{
    Thread* thread = static_cast<Thread*>(data);
    thread->ThreadFunction();
    return 0;
}

#else

void* ThreadFunctionStatic(void* data)
{
    Thread* thread = static_cast<Thread*>(data);
    thread->ThreadFunction();
    pthread_exit((void*)0);
    return 0;
}

#endif
#endif

ThreadID Thread::mainThreadID;

Thread::Thread() :
    handle_(0),
    shouldRun_(false)
{
}

Thread::~Thread()
{
    Stop();
}

bool Thread::Run()
{
#ifdef URHO3D_THREADING
    // Check if already running
    if (handle_)
        return false;

    shouldRun_ = true;
#ifdef _WIN32
    handle_ = CreateThread(0, 0, ThreadFunctionStatic, this, 0, 0);
#else
    handle_ = new pthread_t;
    pthread_attr_t type;
    pthread_attr_init(&type);
    pthread_attr_setdetachstate(&type, PTHREAD_CREATE_JOINABLE);
    pthread_create((pthread_t*)handle_, &type, ThreadFunctionStatic, this);
#endif
    return handle_ != 0;
#else
    return false;
#endif
}

void Thread::Stop()
{
#ifdef URHO3D_THREADING
    // Check if already stopped
    if (!handle_)
        return;

    shouldRun_ = false;
#ifdef _WIN32
    WaitForSingleObject((HANDLE)handle_, INFINITE);
    CloseHandle((HANDLE)handle_);
#else
    pthread_t* thread = (pthread_t*)handle_;
    if (thread)
        pthread_join(*thread, 0);
    delete thread;
#endif
    handle_ = 0;
#endif
}

void Thread::SetPriority(int priority)
{
#ifdef URHO3D_THREADING
#ifdef _WIN32
    if (handle_)
        SetThreadPriority((HANDLE)handle_, priority);
#endif
#if defined(__linux__) && !defined(ANDROID) && !defined(__EMSCRIPTEN__)
    pthread_t* thread = (pthread_t*)handle_;
    if (thread)
        pthread_setschedprio(*thread, priority);
#endif
#endif
}

void Thread::SetMainThread()
{
    mainThreadID = GetCurrentThreadID();
}

ThreadID Thread::GetCurrentThreadID()
{
#ifdef _WIN32
    return GetCurrentThreadId();
#else
    return pthread_self();
#endif
}

bool Thread::IsMainThread()
{
#ifdef URHO3D_THREADING
    return GetCurrentThreadID() == mainThreadID;
#else
    return true;
#endif
}

}
