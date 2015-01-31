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

#include "../Core/Condition.h"

#ifdef WIN32
#include <windows.h>
#else
#include <pthread.h>
#endif

namespace Urho3D
{

#ifdef WIN32
Condition::Condition() :
    event_(0)
{
    event_ = CreateEvent(0, FALSE, FALSE, 0);
}

Condition::~Condition()
{
    CloseHandle((HANDLE)event_);
    event_ = 0;
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
    pthread_mutex_init((pthread_mutex_t*)mutex_, 0);
    pthread_cond_init((pthread_cond_t*)event_, 0);
}

Condition::~Condition()
{
    pthread_cond_t* cond = (pthread_cond_t*)event_;
    pthread_mutex_t* mutex = (pthread_mutex_t*)mutex_;
    
    pthread_cond_destroy(cond);
    pthread_mutex_destroy(mutex);
    delete cond;
    delete mutex;
    event_ = 0;
    mutex_ = 0;
}

void Condition::Set()
{
    pthread_cond_signal((pthread_cond_t*)event_);
}

void Condition::Wait()
{
    pthread_cond_t* cond = (pthread_cond_t*)event_;
    pthread_mutex_t* mutex = (pthread_mutex_t*)mutex_;
    
    pthread_mutex_lock(mutex);
    pthread_cond_wait(cond, mutex);
    pthread_mutex_unlock(mutex);
}
#endif

}
