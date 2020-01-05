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
