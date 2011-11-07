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
#include "Mutex.h"
#include "Object.h"
#include "Signal.h"

class WorkerThread;

/// Work queue item.
struct WorkItem
{
    /// Work function. Called with the work item and thread index (0 = main thread) as parameters.
    void (*workFunction_)(const WorkItem*, unsigned);
    /// Data start pointer.
    void* start_;
    /// Data end pointer.
    void* end_;
    /// Auxiliary data pointer.
    void* aux_;
};

/// Work queue subsystem for multithreading.
class WorkQueue : public Object
{
    OBJECT(WorkQueue);
    
    friend class WorkerThread;
    
public:
    /// Construct.
    WorkQueue(Context* context);
    /// Destruct.
    ~WorkQueue();
    
    /// Create worker threads. Can only be called once.
    void CreateThreads(unsigned numThreads);
    /// Add a work item and resume work. If no threads, will process it immediately.
    void AddWorkItem(const WorkItem& item);
    /// Pause work.
    void Pause();
    /// Resume work.
    void Resume();
    /// Finish all queued work, then pause.
    void Complete();
    
    /// Return number of worker threads.
    unsigned GetNumThreads() const { return threads_.Size(); }
    /// Return whether all work is completed.
    bool IsCompleted() const;
    
private:
    /// Process work items until shut down. Called by the worker threads.
    void ProcessItems(unsigned threadIndex);
    
    /// Worker threads.
    Vector<SharedPtr<WorkerThread> > threads_;
    /// Work item queue.
    List<WorkItem> queue_;
    /// Queue mutex.
    Mutex queueMutex_;
    /// Number of threads working on an item.
    volatile unsigned numActive_;
    /// Shutting down flag.
    volatile bool shutDown_;
    /// Paused flag. Indicates the queue mutex being locked to prevent worker threads using up CPU time.
    bool paused_;
};
