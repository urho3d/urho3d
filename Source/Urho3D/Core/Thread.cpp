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

static DWORD WINAPI ThreadFunctionStatic(void* data)
{
    Thread* thread = static_cast<Thread*>(data);
    thread->ThreadFunction();
    return 0;
}

#else

static void* ThreadFunctionStatic(void* data)
{
    auto* thread = static_cast<Thread*>(data);
    thread->ThreadFunction();
    pthread_exit((void*)nullptr);
    return nullptr;
}

#endif
#endif // URHO3D_THREADING

ThreadID Thread::mainThreadID;

Thread::Thread() :
    handle_(nullptr),
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
    handle_ = CreateThread(nullptr, 0, ThreadFunctionStatic, this, 0, nullptr);
#else
    handle_ = new pthread_t;
    pthread_attr_t type;
    pthread_attr_init(&type);
    pthread_attr_setdetachstate(&type, PTHREAD_CREATE_JOINABLE);
    pthread_create((pthread_t*)handle_, &type, ThreadFunctionStatic, this);
#endif
    return handle_ != nullptr;
#else
    return false;
#endif // URHO3D_THREADING
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
    auto* thread = (pthread_t*)handle_;
    if (thread)
        pthread_join(*thread, nullptr);
    delete thread;
#endif
    handle_ = nullptr;
#endif // URHO3D_THREADING
}

void Thread::SetPriority(int priority)
{
#ifdef URHO3D_THREADING
#ifdef _WIN32
    if (handle_)
        SetThreadPriority((HANDLE)handle_, priority);
#elif defined(__linux__) && !defined(__ANDROID__) && !defined(__EMSCRIPTEN__)
    auto* thread = (pthread_t*)handle_;
    if (thread)
        pthread_setschedprio(*thread, priority);
#endif
#endif // URHO3D_THREADING
}

void Thread::SetMainThread()
{
    mainThreadID = GetCurrentThreadID();
}

ThreadID Thread::GetCurrentThreadID()
{
#ifdef URHO3D_THREADING
#ifdef _WIN32
    return GetCurrentThreadId();
#else
    return pthread_self();
#endif
#else
    return ThreadID();
#endif // URHO3D_THREADING
}

bool Thread::IsMainThread()
{
#ifdef URHO3D_THREADING
    return GetCurrentThreadID() == mainThreadID;
#else
    return true;
#endif // URHO3D_THREADING
}

}
