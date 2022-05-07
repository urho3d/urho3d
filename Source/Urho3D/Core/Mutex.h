// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#ifdef URHO3D_IS_BUILDING
#include "Urho3D.h"
#else
#include <Urho3D/Urho3D.h>
#endif

namespace Urho3D
{

/// Operating system mutual exclusion primitive.
class URHO3D_API Mutex
{
public:
    /// Construct.
    Mutex();
    /// Destruct.
    ~Mutex();

    /// Acquire the mutex. Block if already acquired.
    void Acquire();
    /// Try to acquire the mutex without locking. Return true if successful.
    bool TryAcquire();
    /// Release the mutex.
    void Release();

private:
    /// Mutex handle.
    void* handle_;
};

/// Lock that automatically acquires and releases a mutex.
class URHO3D_API MutexLock
{
public:
    /// Construct and acquire the mutex.
    explicit MutexLock(Mutex& mutex);
    /// Destruct. Release the mutex.
    ~MutexLock();

    /// Prevent copy construction.
    MutexLock(const MutexLock& rhs) = delete;
    /// Prevent assignment.
    MutexLock& operator =(const MutexLock& rhs) = delete;

private:
    /// Mutex reference.
    Mutex& mutex_;
};

}
