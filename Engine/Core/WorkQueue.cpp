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
#include "WorkerThread.h"
#include "WorkQueue.h"

#ifdef WIN32
#include <windows.h>
#else
#include <pthread.h>
#endif

OBJECTTYPESTATIC(WorkQueue);

WorkQueue::WorkQueue(Context* context) :
    Object(context),
    shutDown_(false),
    numWaiting_(0)
{
}

WorkQueue::~WorkQueue()
{
    // Stop the worker threads. First make sure they are not waiting for work items.
    if (!threads_.Empty())
    {
        shutDown_ = true;
        
        for (unsigned i = 0; i < threads_.Size(); ++i)
            queueSignal_.Set();
        for (unsigned i = 0; i < threads_.Size(); ++i)
            threads_[i]->Stop();
    }
}

void WorkQueue::CreateThreads(unsigned numThreads)
{
    // Other subsystems may initialize themselves according to the number of threads.
    // Therefore allow creating the threads only once, after which the amount is fixed.
    if (!threads_.Empty())
        return;
    
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
        queueMutex_.Acquire();
        queue_.Push(item);
        bool isWaiting = numWaiting_ > 0;
        queueMutex_.Release();
        if (isWaiting)
            queueSignal_.Set();
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
            queueMutex_.Acquire();
            if (!queue_.Empty())
            {
                WorkItem item = queue_.Front();
                queue_.PopFront();
                queueMutex_.Release();
                item.workFunction_(&item, 0);
            }
            else
            {
                queueMutex_.Release();
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
        queueMutex_.Acquire();
        bool completed = queue_.Empty() && numWaiting_ == threads_.Size();
        queueMutex_.Release();
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
        
        queueMutex_.Acquire();
        if (wasWaiting)
        {
            --numWaiting_;
            wasWaiting = false;
        }
        if (!queue_.Empty())
        {
            WorkItem item = queue_.Front();
            queue_.PopFront();
            queueMutex_.Release();
            item.workFunction_(&item, threadIndex);
        }
        else
        {
            ++numWaiting_;
            queueMutex_.Release();
            queueSignal_.Wait();
            wasWaiting = true;
        }
    }
}
