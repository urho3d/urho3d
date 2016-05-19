//
// Copyright (c) 2008-2016 the Urho3D project.
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

#include "../Container/Str.h"
#include "../Core/Thread.h"
#include "../Core/Timer.h"

#include "../Core/Profiler.h"


namespace Urho3D
{
/// Event profiling data for one block in the event profiling tree.
class URHO3D_API EventProfilerBlock
{
public:
    /// Construct with the specified parent block and event id.
    EventProfilerBlock(EventProfilerBlock* parent, StringHash eventID) :
        eventID_(eventID),
        name_(0),
        time_(0),
        maxTime_(0),
        count_(0),
        parent_(parent),
        frameTime_(0),
        frameMaxTime_(0),
        frameCount_(0),
        intervalTime_(0),
        intervalMaxTime_(0),
        intervalCount_(0),
        totalTime_(0),
        totalMaxTime_(0),
        totalCount_(0)
    {
        name_ = EventNameRegistrar::GetEventName(eventID);
    }

    /// Destruct. Free the child blocks.
    ~EventProfilerBlock()
    {
        for (HashMap<StringHash, EventProfilerBlock* >::Iterator i = children_.Begin(); i != children_.End(); ++i)
        {
            delete i->second_;
            i->second_ = 0;
        }
    }

    /// Begin timing.
    void Begin()
    {
        timer_.Reset();
        ++count_;
    }

    /// End timing.
    void End()
    {
        long long time = timer_.GetUSec(false);
        if (time > maxTime_)
            maxTime_ = time;
        time_ += time;
    }

    /// End profiling frame and update interval and total values.
    void EndFrame()
    {
        frameTime_ = time_;
        frameMaxTime_ = maxTime_;
        frameCount_ = count_;
        intervalTime_ += time_;
        if (maxTime_ > intervalMaxTime_)
            intervalMaxTime_ = maxTime_;
        intervalCount_ += count_;
        totalTime_ += time_;
        if (maxTime_ > totalMaxTime_)
            totalMaxTime_ = maxTime_;
        totalCount_ += count_;
        time_ = 0;
        maxTime_ = 0;
        count_ = 0;

        for (HashMap<StringHash, EventProfilerBlock* >::Iterator i = children_.Begin(); i != children_.End(); ++i)
            i->second_->EndFrame();
    }

    /// Begin new profiling interval.
    void BeginInterval()
    {
        intervalTime_ = 0;
        intervalMaxTime_ = 0;
        intervalCount_ = 0;

        for (HashMap<StringHash, EventProfilerBlock*>::Iterator i = children_.Begin(); i != children_.End(); ++i)
            i->second_->BeginInterval();
    }

    /// Return child block with the specified name.
    EventProfilerBlock* GetChild(StringHash eventID)
    {
        HashMap<StringHash, EventProfilerBlock*>::Iterator it = children_.Find(eventID);
        if (it != children_.End())
            return it->second_;

        EventProfilerBlock* newBlock = new EventProfilerBlock(this, eventID);
        children_[eventID] = newBlock;

        return newBlock;
    }
    /// Event ID.
    StringHash eventID_;
    /// Block name.
    String name_;
    /// High-resolution timer for measuring the block duration.
    HiresTimer timer_;
    /// Time on current frame.
    long long time_;
    /// Maximum time on current frame.
    long long maxTime_;
    /// Calls on current frame.
    unsigned count_;
    /// Parent block.
    EventProfilerBlock* parent_;
    /// Child blocks.
    HashMap<StringHash,EventProfilerBlock*> children_;
    /// Time on the previous frame.
    long long frameTime_;
    /// Maximum time on the previous frame.
    long long frameMaxTime_;
    /// Calls on the previous frame.
    unsigned frameCount_;
    /// Time during current profiler interval.
    long long intervalTime_;
    /// Maximum time during current profiler interval.
    long long intervalMaxTime_;
    /// Calls during current profiler interval.
    unsigned intervalCount_;
    /// Total accumulated time.
    long long totalTime_;
    /// All-time maximum time.
    long long totalMaxTime_;
    /// Total accumulated calls.
    unsigned totalCount_;
};

/// Hierarchical performance event profiler subsystem.
class URHO3D_API EventProfiler : public Object
{
    URHO3D_OBJECT(EventProfiler, Object);

public:
    /// Construct.
    EventProfiler(Context* context);
    /// Destruct.
    virtual ~EventProfiler();

    /// Activate the event profiler to collect information. This incurs slight performance hit on each SendEvent. By default inactive.
    static void SetActive(bool active);
    /// Return true if active.
    static bool IsActive() { return active; }

    /// Begin timing a profiling block.
    void BeginBlock(StringHash eventID)
    {
        // Profiler supports only the main thread currently
        if ( !Thread::IsMainThread())
            return;

        current_ = current_->GetChild(eventID);
        current_->Begin();
    }

    /// End timing the current profiling block.
    void EndBlock()
    {
        if (!Thread::IsMainThread())
            return;

        if (current_ != root_)
        {
            current_->End();
            current_ = current_->parent_;
        }
    }

    /// Begin the profiling frame. Called by Engine::RunFrame().
    void BeginFrame();
    /// End the profiling frame. Called by Engine::RunFrame().
    void EndFrame();
    /// Begin a new interval.
    void BeginInterval();
    /// Delete all blocks and recreate root block.
    void Clear();
    /// Return profiling data as text output.
    String PrintData(bool showUnused = false, bool showTotal = false, unsigned maxDepth = M_MAX_UNSIGNED) const;
    /// Return the current profiling block.
    const EventProfilerBlock* GetCurrentBlock() { return current_; }
    /// Return the root profiling block.
    const EventProfilerBlock* GetRootBlock() { return root_; }
private:
    /// Return profiling data as text output for a specified profiling block.
    void PrintData(EventProfilerBlock* block, String& output, unsigned depth, unsigned maxDepth, bool showUnused, bool showTotal) const;
    /// Current profiling block.
    EventProfilerBlock* current_;
    /// Root profiling block.
    EventProfilerBlock* root_;
    /// Frames in the current interval.
    unsigned intervalFrames_;
    /// Total frames.
    unsigned totalFrames_;
    /// Profiler active. Default false.
    static bool active;
};

}
