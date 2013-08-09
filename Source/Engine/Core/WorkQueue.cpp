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
#include "CoreEvents.h"
#include "ProcessUtils.h"
#include "Profiler.h"
#include "Thread.h"
#include "Timer.h"
#include "WorkQueue.h"

namespace Urho3D
{

const unsigned MAX_NONTHREADED_WORK_USEC = 1000;

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

WorkQueue::WorkQueue(Context* context) :
    Object(context),
    shutDown_(false),
    pausing_(false),
    paused_(false)
{
    SubscribeToEvent(E_BEGINFRAME, HANDLER(WorkQueue, HandleBeginFrame));
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
        thread->Run();
        threads_.Push(thread);
    }
}

void WorkQueue::AddWorkItem(const WorkItem& item)
{
    // Push to the main thread list to keep item alive
    // Clear completed flag in case item is reused
    workItems_.Push(item);
    WorkItem* itemPtr = &workItems_.Back();
    itemPtr->completed_ = false;
    
    // Make sure worker threads' list is safe to modify
    if (threads_.Size() && !paused_)
        queueMutex_.Acquire();
    
    // Find position for new item
    if (queue_.Empty())
        queue_.Push(itemPtr);
    else
    {
        for (List<WorkItem*>::Iterator i = queue_.Begin(); i != queue_.End(); ++i)
        {
            if ((*i)->priority_ <= itemPtr->priority_)
            {
                queue_.Insert(i, itemPtr);
                break;
            }
        }
    }
    
    if (threads_.Size())
    {
        queueMutex_.Release();
        paused_ = false;
    }
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


void WorkQueue::Complete(unsigned priority)
{
    if (threads_.Size())
    {
        Resume();
        
        // Take work items also in the main thread until queue empty or no high-priority items anymore
        while (!queue_.Empty())
        {
            queueMutex_.Acquire();
            if (!queue_.Empty() && queue_.Front()->priority_ >= priority)
            {
                WorkItem* item = queue_.Front();
                queue_.PopFront();
                queueMutex_.Release();
                item->workFunction_(item, 0);
                item->completed_ = true;
            }
            else
            {
                queueMutex_.Release();
                break;
            }
        }
        
        // Wait for threaded work to complete
        while (!IsCompleted(priority))
        {
        }
        
        // If no work at all remaining, pause worker threads by leaving the mutex locked
        if (queue_.Empty())
            Pause();
    }
    else
    {
        // No worker threads: ensure all high-priority items are completed in the main thread
        while (!queue_.Empty() && queue_.Front()->priority_ >= priority)
        {
            WorkItem* item = queue_.Front();
            queue_.PopFront();
            item->workFunction_(item, 0);
            item->completed_ = true;
        }
    }
    
    PurgeCompleted();
}

bool WorkQueue::IsCompleted(unsigned priority) const
{
    for (List<WorkItem>::ConstIterator i = workItems_.Begin(); i != workItems_.End(); ++i)
    {
        if (i->priority_ >= priority && !i->completed_)
            return false;
    }
    
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
                wasActive = true;
                
                WorkItem* item = queue_.Front();
                queue_.PopFront();
                queueMutex_.Release();
                item->workFunction_(item, threadIndex);
                item->completed_ = true;
            }
            else
            {
                wasActive = false;
                
                queueMutex_.Release();
                Time::Sleep(0);
            }
        }
    }
}

void WorkQueue::PurgeCompleted()
{
    using namespace WorkItemCompleted;
    
    VariantMap eventData;
    
    // Purge completed work items and send completion events.
    for (List<WorkItem>::Iterator i = workItems_.Begin(); i != workItems_.End();)
    {
        if (i->completed_)
        {
            if (i->sendEvent_)
            {
                eventData[P_ITEM] = (void*)(&(*i));
                SendEvent(E_WORKITEMCOMPLETED, eventData);
            }
            
            i = workItems_.Erase(i);
        }
        else
            ++i;
    }
}

void WorkQueue::HandleBeginFrame(StringHash eventType, VariantMap& eventData)
{
    // If no worker threads, complete low-priority work here
    if (threads_.Empty() && !queue_.Empty())
    {
        PROFILE(CompleteWorkNonthreaded);
        
        HiresTimer timer;
        
        while (!queue_.Empty() && timer.GetUSec(false) < MAX_NONTHREADED_WORK_USEC)
        {
            WorkItem* item = queue_.Front();
            queue_.PopFront();
            item->workFunction_(item, 0);
            item->completed_ = true;
        }
    }
    
    PurgeCompleted();
}

}
