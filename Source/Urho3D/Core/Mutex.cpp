// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

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
    handle_ = nullptr;
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
    auto* mutex = (pthread_mutex_t*)handle_;
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
    pthread_mutex_init(mutex, &attr);
}

Mutex::~Mutex()
{
    auto* mutex = (pthread_mutex_t*)handle_;
    pthread_mutex_destroy(mutex);
    delete mutex;
    handle_ = nullptr;
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
