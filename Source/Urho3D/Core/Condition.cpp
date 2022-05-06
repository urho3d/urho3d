// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include "../Precompiled.h"

#include "../Core/Condition.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <pthread.h>
#endif

namespace Urho3D
{

#ifdef _WIN32

Condition::Condition() :
    event_(nullptr)
{
    event_ = CreateEvent(nullptr, FALSE, FALSE, nullptr);
}

Condition::~Condition()
{
    CloseHandle((HANDLE)event_);
    event_ = nullptr;
}

void Condition::Set()
{
    SetEvent((HANDLE)event_);
}

void Condition::Wait()
{
    WaitForSingleObject((HANDLE)event_, INFINITE);
}

#else

Condition::Condition() :
    mutex_(new pthread_mutex_t),
    event_(new pthread_cond_t)
{
    pthread_mutex_init((pthread_mutex_t*)mutex_, nullptr);
    pthread_cond_init((pthread_cond_t*)event_, nullptr);
}

Condition::~Condition()
{
    auto* cond = (pthread_cond_t*)event_;
    auto* mutex = (pthread_mutex_t*)mutex_;

    pthread_cond_destroy(cond);
    pthread_mutex_destroy(mutex);
    delete cond;
    delete mutex;
    event_ = nullptr;
    mutex_ = nullptr;
}

void Condition::Set()
{
    pthread_cond_signal((pthread_cond_t*)event_);
}

void Condition::Wait()
{
    auto* cond = (pthread_cond_t*)event_;
    auto* mutex = (pthread_mutex_t*)mutex_;

    pthread_mutex_lock(mutex);
    pthread_cond_wait(cond, mutex);
    pthread_mutex_unlock(mutex);
}

#endif

}
