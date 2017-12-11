//=============================================================================
// Copyright (c) 2017
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
//=============================================================================

#pragma once

#include "../Core/Thread.h"
#include "../Core/Mutex.h"
#include "../Container/RefCounted.h"

namespace Urho3D
{

template<class T>
class HelperThread : public Thread, public RefCounted
{
public:
    typedef void (T::*ProcessFn)(void *);

    HelperThread(T *parent, ProcessFn pFn, bool looping=true, int priority=M_MAX_INT) 
        : parent_(parent), processFn_(pFn), looping_(looping), priority_(priority), fnExited_(true)
    {
    }

    virtual ~HelperThread()
    {
        WaitExit();
    }

    void Start()
    {
        Run();
        SetPriority(priority_);
    }

    virtual void ThreadFunction()
    {
        SetFnExit(false);

        while (true)
        {
            // process callback
            (parent_->*processFn_)(parent_);

            if (!IsLooping())
                break;

            Time::Sleep(0);
        }

        SetFnExit(true);
    }

    bool HasFnExited()
    {
        MutexLock lock(mutexLock_);
        return fnExited_;
    }

protected:
    void WaitExit()
    {
        SetLooping(false);

        do 
        { 
            Time::Sleep(1); 
        }
        while (!HasFnExited());
    }

    void SetLooping(bool bset)
    {
        MutexLock lock(mutexLock_);
        looping_ = bset;
    }

    bool IsLooping()
    {
        MutexLock lock(mutexLock_);
        return looping_;
    }

    void SetFnExit(bool bset)
    {
        MutexLock lock(mutexLock_);
        fnExited_ = bset;
    }

protected:
    T           *parent_;
    ProcessFn   processFn_;
    Mutex       mutexLock_;
    int         priority_;

    bool        looping_;
    bool        fnExited_;
};

}


