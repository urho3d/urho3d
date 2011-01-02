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

#ifndef COMMON_MUTEX_H
#define COMMON_MUTEX_H

class MutexImpl;

//! A mutual exclusion primitive
class Mutex
{
public:
    //! Construct
    Mutex();
    //! Destruct
    ~Mutex();
    
    //! Acquire the mutex. Blocks if already acquired
    void get();
    //! Release the mutex
    void release();
    
private:
    //! Implementation
    MutexImpl* mImpl;
};

//! A lock which automatically acquires and releases a mutex
class MutexLock
{
public:
    //! Construct and acquire the mutex
    MutexLock(Mutex& mutex);
    //! Destruct. Release the mutex
    ~MutexLock();
    
private:
    //! Mutex reference
    Mutex& mMutex;
};

#endif // COMMON_MUTEX_H
