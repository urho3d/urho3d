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

#pragma once

/// Non-reentrant userspace mutual exclusion primitive.
class SpinLock
{
public:
    /// Construct.
    SpinLock() :
        locked_(0)
    {
    }
    
    /// Acquire the lock. Spin in a loop while waiting.
    void Acquire()
    {
        for (;;)
        {
            if (TestAndSet(&locked_, 1) == 0)
                break;
        }
    }
    
    /// Try to acquire the lock without waiting. Return true if successfully acquired.
    bool TryAcquire()
    {
        return TestAndSet(&locked_, 1) == 0;
    }
    
    /// Release the lock.
    void Release()
    {
        locked_ = 0;
    }
    
private:
    /// Test-and-set a value atomically and return the previous value.
    static unsigned TestAndSet(unsigned* dest, unsigned newValue)
    {
        #ifdef _MSC_VER
        __asm
        {
            mov edx, dest
            mov eax, newValue
            lock xchg eax, dword ptr [edx]
        }
        #else
        return __sync_lock_test_and_set(ptr, newValue);
        #endif
    }
    
    /// Locked flag.
    unsigned locked_;
};

