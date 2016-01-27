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

#include "../Core/Mutex.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <pthread.h>
#endif

#include "../DebugNew.h"

namespace Urho3D
{

#ifdef _WIN32

Mutex::Mutex() :
    handle_(new CRITICAL_SECTION)
{
    InitializeCriticalSection((CRITICAL_SECTION*)handle_);
}

Mutex::~Mutex()
{
    CRITICAL_SECTION* cs = (CRITICAL_SECTION*)handle_;
    DeleteCriticalSection(cs);
    delete cs;
    handle_ = 0;
}

void Mutex::Acquire()
{
    EnterCriticalSection((CRITICAL_SECTION*)handle_);
}

bool Mutex::TryAcquire()
{
    return TryEnterCriticalSection((CRITICAL_SECTION*)handle_) != FALSE;
}

void Mutex::Release()
{
    LeaveCriticalSection((CRITICAL_SECTION*)handle_);
}

#else

Mutex::Mutex() :
    handle_(new pthread_mutex_t)
{
    pthread_mutex_t* mutex = (pthread_mutex_t*)handle_;
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
    pthread_mutex_init(mutex, &attr);
}

Mutex::~Mutex()
{
    pthread_mutex_t* mutex = (pthread_mutex_t*)handle_;
    pthread_mutex_destroy(mutex);
    delete mutex;
    handle_ = 0;
}

void Mutex::Acquire()
{
    pthread_mutex_lock((pthread_mutex_t*)handle_);
}

bool Mutex::TryAcquire()
{
    return pthread_mutex_trylock((pthread_mutex_t*)handle_) == 0;
}

void Mutex::Release()
{
    pthread_mutex_unlock((pthread_mutex_t*)handle_);
}

#endif

MutexLock::MutexLock(Mutex& mutex) :
    mutex_(mutex)
{
    mutex_.Acquire();
}

MutexLock::~MutexLock()
{
    mutex_.Release();
}

}
