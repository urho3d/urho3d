//
// Copyright (c) 2008-2013 the Urho3D project.
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
#include "Thread.h"
#include "Timer.h"
#include "WorkQueue.h"

namespace Urho3D
{

/// Worker thread managed by the work queue.
class WorkerThread : public Thread, public RefCounted
{
public:
    /// Construct.
    WorkerThread(WorkQueue* owner, unsigned index) :
        owner_(owner),
        index_(index)
    {
    }
    
    /// Process work items until stopped.
    virtual void ThreadFunction()
    {
        // Init FPU state first
        InitFPU();
        owner_->ProcessItems(index_);
    }
    
    /// Return thread index.
    unsigned GetIndex() const { return index_; }
    
private:
    /// Work queue.
    WorkQueue* owner_;
    /// Thread index.
    unsigned index_;
};

OBJECTTYPESTATIC(WorkQueue);

WorkQueue::WorkQueue(Context* context) :
    Object(context),
    numActive_(0),
    shutDown_(false),
    pausing_(false),
    paused_(false)
{
}

WorkQueue::~WorkQueue()
{
    // Stop the worker threads. First make sure they are not waiting for work items
    shutDown_ = true;
    Resume();
    
    for (unsigned i = 0; i < threads_.Size(); ++i)
        threads_[i]->Stop();
}

void WorkQueue::CreateThreads(unsigned numThreads)
{
    // Other subsystems may initialize themselves according to the number of threads.
    // Therefore allow creating the threads only once, after which the amount is fixed
    if (!threads_.Empty())
        return;
    
    // Start threads in paused mode
    Pause();
    
    for (unsigned i = 0; i < numThreads; ++i)
    {
        SharedPtr<WorkerThread> thread(new WorkerThread(this, i + 1));
        thread->Start();
        threads_.Push(thread);
    }
}

void WorkQueue::AddWorkItem(const WorkItem& item)
{
    if (threads_.Size())
    {
        if (paused_)
        {
            queue_.Push(item);
            queueMutex_.Release();
            paused_ = false;
        }
        else
        {
            queueMutex_.Acquire();
            queue_.Push(item);
            queueMutex_.Release();
        }
    }
    else
        item.workFunction_(&item, 0);
}

void WorkQueue::Pause()
{
    if (!paused_)
    {
        pausing_ = true;
        
        queueMutex_.Acquire();
        paused_ = true;
        
        pausing_ = false;
    }
}

void WorkQueue::Resume()
{
    if (paused_)
    {
        queueMutex_.Release();
        paused_ = false;
    }
}


void WorkQueue::Complete()
{
    if (threads_.Size())
    {
        Resume();
        
        // Take work items in the main thread until queue empty
        while (!queue_.Empty())
        {
            queueMutex_.Acquire();
            if (!queue_.Empty())
            {
                WorkItem item = queue_.Front();
                queue_.PopFront();
                queueMutex_.Release();
                item.workFunction_(&item, 0);
            }
            else
                queueMutex_.Release();
        }
        
        // Wait for all work to finish
        while (!IsCompleted())
        {
        }
        
        // Pause worker threads by leaving the mutex locked
        Pause();
    }
}

bool WorkQueue::IsCompleted() const
{
    if (threads_.Size())
        return !numActive_ && queue_.Empty();
    else
        return true;
}

void WorkQueue::ProcessItems(unsigned threadIndex)
{
    bool wasActive = false;
    
    for (;;)
    {
        if (shutDown_)
            return;
        
        if (pausing_ && !wasActive)
            Time::Sleep(0);
        else
        {
            queueMutex_.Acquire();
            if (!queue_.Empty())
            {
                if (!wasActive)
                {
                    ++numActive_;
                    wasActive = true;
                }
                WorkItem item = queue_.Front();
                queue_.PopFront();
                queueMutex_.Release();
                item.workFunction_(&item, threadIndex);
            }
            else
            {
                if (wasActive)
                {
                    --numActive_;
                    wasActive = false;
                }
                queueMutex_.Release();
                Time::Sleep(0);
            }
        }
    }
}

}
