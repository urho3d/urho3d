// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include "../Container/List.h"
#include "../Core/Mutex.h"
#include "../Core/Object.h"

#include <atomic>

namespace Urho3D
{

/// Work item completed event.
URHO3D_EVENT(E_WORKITEMCOMPLETED, WorkItemCompleted)
{
    URHO3D_PARAM(P_ITEM, Item);                        // WorkItem ptr
}

inline constexpr i32 WI_MAX_PRIORITY = M_MAX_INT;

class WorkerThread;

/// Work queue item.
/// @nobind
struct WorkItem : public RefCounted
{
    friend class WorkQueue;

public:
    /// Work function. Called with the work item and thread index (0 = main thread) as parameters.
    void (* workFunction_)(const WorkItem*, i32){};
    /// Data start pointer.
    void* start_{};
    /// Data end pointer.
    void* end_{};
    /// Auxiliary data pointer.
    void* aux_{};
    /// Priority. Higher value = will be completed first.
    i32 priority_{};
    /// Whether to send event on completion.
    bool sendEvent_{};
    /// Completed flag.
    std::atomic<bool> completed_{};

private:
    bool pooled_{};
};

/// Work queue subsystem for multithreading.
class URHO3D_API WorkQueue : public Object
{
    URHO3D_OBJECT(WorkQueue, Object);

    friend class WorkerThread;

public:
    /// Construct.
    explicit WorkQueue(Context* context);
    /// Destruct.
    ~WorkQueue() override;

    /// Create worker threads. Can only be called once.
    void CreateThreads(i32 numThreads);
    /// Get pointer to an usable WorkItem from the item pool. Allocate one if no more free items.
    SharedPtr<WorkItem> GetFreeItem();
    /// Add a work item and resume worker threads.
    void AddWorkItem(const SharedPtr<WorkItem>& item);
    /// Remove a work item before it has started executing. Return true if successfully removed.
    bool RemoveWorkItem(SharedPtr<WorkItem> item);
    /// Remove a number of work items before they have started executing. Return the number of items successfully removed.
    i32 RemoveWorkItems(const Vector<SharedPtr<WorkItem>>& items);
    /// Pause worker threads.
    void Pause();
    /// Resume worker threads.
    void Resume();
    /// Finish all queued work which has at least the specified priority. Main thread will also execute priority work. Pause worker threads if no more work remains.
    void Complete(i32 priority);

    /// Set the pool telerance before it starts deleting pool items.
    void SetTolerance(int tolerance) { tolerance_ = tolerance; }

    /// Set how many milliseconds maximum per frame to spend on low-priority work, when there are no worker threads.
    void SetNonThreadedWorkMs(int ms) { maxNonThreadedWorkMs_ = Max(ms, 1); }

    /// Return number of worker threads.
    i32 GetNumThreads() const { return threads_.Size(); }

    /// Return whether all work with at least the specified priority is finished.
    bool IsCompleted(i32 priority) const;
    /// Return whether the queue is currently completing work in the main thread.
    bool IsCompleting() const { return completing_; }

    /// Return the pool tolerance.
    int GetTolerance() const { return tolerance_; }

    /// Return how many milliseconds maximum to spend on non-threaded low-priority work.
    int GetNonThreadedWorkMs() const { return maxNonThreadedWorkMs_; }

private:
    /// Process work items until shut down. Called by the worker threads.
    void ProcessItems(i32 threadIndex);
    /// Purge completed work items which have at least the specified priority, and send completion events as necessary.
    void PurgeCompleted(i32 priority);
    /// Purge the pool to reduce allocation where its unneeded.
    void PurgePool();
    /// Return a work item to the pool.
    void ReturnToPool(SharedPtr<WorkItem>& item);
    /// Handle frame start event. Purge completed work from the main thread queue, and perform work if no threads at all.
    void HandleBeginFrame(StringHash eventType, VariantMap& eventData);

    /// Worker threads.
    Vector<SharedPtr<WorkerThread>> threads_;
    /// Work item pool for reuse to cut down on allocation. The bool is a flag for item pooling and whether it is available or not.
    List<SharedPtr<WorkItem>> poolItems_;
    /// Work item collection. Accessed only by the main thread.
    List<SharedPtr<WorkItem>> workItems_;
    /// Work item prioritized queue for worker threads. Pointers are guaranteed to be valid (point to workItems).
    List<WorkItem*> queue_;
    /// Worker queue mutex.
    Mutex queueMutex_;
    /// Shutting down flag.
    std::atomic<bool> shutDown_;
    /// Pausing flag. Indicates the worker threads should not contend for the queue mutex.
    std::atomic<bool> pausing_;
    /// Paused flag. Indicates the queue mutex being locked to prevent worker threads using up CPU time.
    bool paused_;
    /// Completing work in the main thread flag.
    bool completing_;
    /// Tolerance for the shared pool before it begins to deallocate.
    int tolerance_;
    /// Last size of the shared pool.
    i32 lastSize_;
    /// Maximum milliseconds per frame to spend on low-priority work, when there are no worker threads.
    int maxNonThreadedWorkMs_;
};

}
