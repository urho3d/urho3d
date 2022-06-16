// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include "../Container/Str.h"
#include "../Core/Thread.h"
#include "../Core/Timer.h"

#ifdef URHO3D_TRACY_PROFILING
#define TRACY_ENABLE 1
#include "Tracy/Tracy.hpp"
#endif

namespace Urho3D
{

/// Profiling data for one block in the profiling tree.
/// @nobind
class URHO3D_API ProfilerBlock
{
public:
    /// Construct with the specified parent block and name.
    ProfilerBlock(ProfilerBlock* parent, const char* name) :
        name_(nullptr),
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
        if (name)
        {
            size_t size = (size_t)String::CStringLength(name) + 1;
            name_ = new char[size];
            memcpy(name_, name, size);
        }
    }

    /// Destruct. Free the child blocks.
    virtual ~ProfilerBlock()
    {
        for (Vector<ProfilerBlock*>::Iterator i = children_.Begin(); i != children_.End(); ++i)
        {
            delete *i;
            *i = nullptr;
        }

        delete [] name_;
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

        for (Vector<ProfilerBlock*>::Iterator i = children_.Begin(); i != children_.End(); ++i)
            (*i)->EndFrame();
    }

    /// Begin new profiling interval.
    void BeginInterval()
    {
        intervalTime_ = 0;
        intervalMaxTime_ = 0;
        intervalCount_ = 0;

        for (Vector<ProfilerBlock*>::Iterator i = children_.Begin(); i != children_.End(); ++i)
            (*i)->BeginInterval();
    }

    /// Return child block with the specified name.
    ProfilerBlock* GetChild(const char* name)
    {
        for (Vector<ProfilerBlock*>::Iterator i = children_.Begin(); i != children_.End(); ++i)
        {
            if (!String::Compare((*i)->name_, name, true))
                return *i;
        }

        auto* newBlock = new ProfilerBlock(this, name);
        children_.Push(newBlock);

        return newBlock;
    }

    /// Block name.
    char* name_;
    /// High-resolution timer for measuring the block duration.
    HiresTimer timer_;
    /// Time on current frame.
    long long time_;
    /// Maximum time on current frame.
    long long maxTime_;
    /// Calls on current frame.
    unsigned count_;
    /// Parent block.
    ProfilerBlock* parent_;
    /// Child blocks.
    Vector<ProfilerBlock*> children_;
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

/// Hierarchical performance profiler subsystem.
class URHO3D_API Profiler : public Object
{
    URHO3D_OBJECT(Profiler, Object);

public:
    /// Construct.
    explicit Profiler(Context* context);
    /// Destruct.
    ~Profiler() override;

    /// Begin timing a profiling block.
    void BeginBlock(const char* name)
    {
        // Profiler supports only the main thread currently
        if (!Thread::IsMainThread())
            return;

        current_ = current_->GetChild(name);
        current_->Begin();
    }

    /// End timing the current profiling block.
    void EndBlock()
    {
        if (!Thread::IsMainThread())
            return;

        current_->End();
        if (current_->parent_)
            current_ = current_->parent_;
    }

    /// Begin the profiling frame. Called by HandleBeginFrame().
    void BeginFrame();
    /// End the profiling frame. Called by HandleEndFrame().
    void EndFrame();
    /// Begin a new interval.
    void BeginInterval();

    /// Return profiling data as text output. This method is not thread-safe.
    const String& PrintData(bool showUnused = false, bool showTotal = false, unsigned maxDepth = M_MAX_UNSIGNED) const;
    /// Return the current profiling block.
    const ProfilerBlock* GetCurrentBlock() { return current_; }
    /// Return the root profiling block.
    const ProfilerBlock* GetRootBlock() { return root_; }

protected:
    /// Return profiling data as text output for a specified profiling block.
    void PrintData(ProfilerBlock* block, String& output, unsigned depth, unsigned maxDepth, bool showUnused, bool showTotal) const;

    /// Current profiling block.
    ProfilerBlock* current_;
    /// Root profiling block.
    ProfilerBlock* root_;
    /// Frames in the current interval.
    unsigned intervalFrames_;
};

/// Helper class for automatically beginning and ending a profiling block.
/// @nobind
class URHO3D_API AutoProfileBlock
{
public:
    /// Construct. Begin a profiling block with the specified name and optional call count.
    AutoProfileBlock(Profiler* profiler, const char* name) :
        profiler_(profiler)
    {
        if (profiler_)
            profiler_->BeginBlock(name);
    }

    /// Destruct. End the profiling block.
    ~AutoProfileBlock()
    {
        if (profiler_)
            profiler_->EndBlock();
    }

private:
    /// Profiler.
    Profiler* profiler_;
};

#ifdef URHO3D_TRACY_PROFILING // Use Tracy profiler
    /// Macro for scoped profiling with a name.
    #define URHO3D_PROFILE(name) ZoneScopedN(#name)
#elif defined(URHO3D_PROFILING) // Use default profiler
    /// Macro for scoped profiling with a name.
    #define URHO3D_PROFILE(name) Urho3D::AutoProfileBlock profile_ ## name (GetSubsystem<Urho3D::Profiler>(), #name)
#else // Profiling off
    #define URHO3D_PROFILE(name)
#endif

#ifdef URHO3D_TRACY_PROFILING // Use Tracy profiler
    /// Macro for scoped profiling with a name and color.
    #define URHO3D_PROFILE_COLOR(name, color) ZoneScopedNC(#name, color)
    /// Macro for scoped profiling with a dynamic string name.
    #define URHO3D_PROFILE_STR(nameStr, size) ZoneName(nameStr, size)
    /// Macro for marking a game frame.
    #define URHO3D_PROFILE_FRAME() FrameMark
    /// Macro for recording name of current thread.
    #define URHO3D_PROFILE_THREAD(name) tracy::SetThreadName(name)
    /// Macro for scoped profiling of a function.
    #define URHO3D_PROFILE_FUNCTION() ZoneScopedN(__FUNCTION__)

    /// Color used for highlighting event.
    #define URHO3D_PROFILE_EVENT_COLOR tracy::Color::OrangeRed
    /// Color used for highlighting resource.
    #define URHO3D_PROFILE_RESOURCE_COLOR tracy::Color::MediumSeaGreen
#else // Tracy profiler off
    #define URHO3D_PROFILE_COLOR(name, color)
    #define URHO3D_PROFILE_STR(nameStr, size)
    #define URHO3D_PROFILE_FRAME()
    #define URHO3D_PROFILE_THREAD(name)
    #define URHO3D_PROFILE_FUNCTION()

    #define URHO3D_PROFILE_EVENT_COLOR
    #define URHO3D_PROFILE_RESOURCE_COLOR
#endif

}
