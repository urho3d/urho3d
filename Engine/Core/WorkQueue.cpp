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

#include "Precompiled.h"
#include "ProcessUtils.h"
#include "Profiler.h"
#include "WorkerThread.h"
#include "WorkQueue.h"

#ifdef WIN32
#include <windows.h>
#else
#include <pthread.h>
#endif

/// Work queue implementation.
class WorkQueueImpl
{
public:
    /// Construct.
    WorkQueueImpl()
    {
        #ifdef WIN32
        eventHandle_ = CreateEvent(0, FALSE, FALSE, 0);
        #else
        pthread_cond_init(&condition_, 0);
        pthread_mutex_init(&mutex_, 0);
        #endif
    }
    
    /// Destruct.
    ~WorkQueueImpl()
    {
        #ifdef WIN32
        CloseHandle(eventHandle_);
        #else
        pthread_cond_destroy(&condition_);
        pthread_mutex_destroy(&mutex_);
        #endif
    }
    
    /// Signal one worker thread for available work.
    void Signal()
    {
        #ifdef WIN32
        SetEvent(eventHandle_);
        #else
        pthread_cond_signal(&condition_);
        #endif
    }
    
    /// Wait for available work.
    void Wait()
    {
        #ifdef WIN32
        WaitForSingleObject(eventHandle_, INFINITE);
        #else
        pthread_mutex_lock(&mutex_);
        pthread_cond_wait(&condition_, &mutex_);
        pthread_mutex_unlock(&mutex_);
        #endif
    }
    
private:
    #ifdef WIN32
    /// Event for signaling the worker threads.
    HANDLE eventHandle_;
    #else
    /// Condition variable for signaling the worker threads.
    pthread_cond_t condition_;
    /// Mutex for the condition variable.
    pthread_mutex_t mutex_;
    #endif
};

OBJECTTYPESTATIC(WorkQueue);

WorkQueue::WorkQueue(Context* context) :
    Object(context),
    impl_(new WorkQueueImpl()),
    shutDown_(false),
    numWaiting_(0)
{
    // Create worker threads and start them. Leave one core free for the main thread, and another for GPU & audio.
    int numCores = GetNumCPUCores();
    if (numCores == 1)
        return;
    int numThreads = Max(numCores - 2, 1);
    
    for (int i = 0; i < numThreads; ++i)
    {
        SharedPtr<WorkerThread> thread(new WorkerThread(this, i + 1));
        thread->Start();
        threads_.Push(thread);
    }
}

WorkQueue::~WorkQueue()
{
    // Stop the worker threads. First make sure they are not waiting for work items.
    if (!threads_.Empty())
    {
        shutDown_ = true;
        
        for (unsigned i = 0; i < threads_.Size(); ++i)
            impl_->Signal();
        for (unsigned i = 0; i < threads_.Size(); ++i)
            threads_[i]->Stop();
    }
    
    delete impl_;
    impl_ = 0;
}

void WorkQueue::AddWorkItem(const WorkItem& item)
{
    if (threads_.Size())
    {
        queueLock_.Acquire();
        queue_.Push(item);
        bool isWaiting = numWaiting_ > 0;
        queueLock_.Release();
        if (isWaiting)
        {
            PROFILE(SignalWorkerThreads);
            impl_->Signal();
        }
    }
    else
        item.workFunction_(&item, 0);
}

void WorkQueue::Complete()
{
    if (threads_.Size())
    {
        // Wait for work to finish while also taking work items in the main thread
        for (;;)
        {
            queueLock_.Acquire();
            if (!queue_.Empty())
            {
                WorkItem item = queue_.Front();
                queue_.PopFront();
                queueLock_.Release();
                item.workFunction_(&item, 0);
            }
            else
            {
                queueLock_.Release();
                if (numWaiting_ == threads_.Size())
                    break;
            }
        }
    }
}

bool WorkQueue::IsCompleted()
{
    if (threads_.Size())
    {
        queueLock_.Acquire();
        bool completed = queue_.Empty() && numWaiting_ == threads_.Size();
        queueLock_.Release();
        return completed;
    }
    else
        return true;
}

void WorkQueue::ProcessItems(unsigned threadIndex)
{
    bool wasWaiting = false;
    
    for (;;)
    {
        if (shutDown_)
            return;
        
        queueLock_.Acquire();
        if (wasWaiting)
        {
            --numWaiting_;
            wasWaiting = false;
        }
        if (!queue_.Empty())
        {
            WorkItem item = queue_.Front();
            queue_.PopFront();
            queueLock_.Release();
            item.workFunction_(&item, threadIndex);
        }
        else
        {
            ++numWaiting_;
            queueLock_.Release();
            impl_->Wait();
            wasWaiting = true;
        }
    }
}
