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

#include "List.h"
#include "Object.h"
#include "SpinLock.h"

class WorkerThread;
class WorkItem;
class WorkQueueImpl;

/// Work queue subsystem.
class WorkQueue : public Object
{
    OBJECT(WorkQueue);
    
    friend class WorkerThread;
    
public:
    /// Construct.
    WorkQueue(Context* context);
    /// Destruct.
    ~WorkQueue();
    
    /// Add a work item. If no threads, will process it immediately.
    void AddWorkItem(WorkItem* item);
    /// Finish all current work items.
    void Complete();
    
    /// Return number of worker threads.
    unsigned GetNumThreads() const { return threads_.Size(); }
    /// Return whether all work is completed.
    bool IsCompleted();
    
private:
    /// Block until a work item is available and return it. May return null. Called by the worker threads.
    WorkItem* GetNextWorkItem();
    
    /// Work queue implementation. Contains the operating system-specific signaling mechanism.
    WorkQueueImpl* impl_;
    /// Worker threads.
    Vector<SharedPtr<WorkerThread> > threads_;
    /// Work item queue.
    List<WorkItem*> queue_;
    /// Queue lock.
    SpinLock queueLock_;
    /// Number of waiting threads.
    unsigned numWaiting_;
    /// Shutting down flag.
    volatile bool shutDown_;
};
