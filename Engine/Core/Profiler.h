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

#include "Timer.h"

/// Profiling data for one block in the profiling tree
class ProfilerBlock
{
public:
    /// Construct with the specified parent block and name
    ProfilerBlock(ProfilerBlock* parent, const char* name) :
        name_(name),
        time_(0),
        count_(0),
        parent_(parent),
        lastSearchName_(0),
        lastSearchBlock_(0),
        frameTime_(0),
        frameCount_(0),
        accumulatedTime_(0),
        accumulatedCount_(0),
        totalTime_(0),
        totalCount_(0)
    {
    }
    
    /// Destruct. Free the child blocks
    ~ProfilerBlock()
    {
        for (PODVector<ProfilerBlock*>::Iterator i = children_.Begin(); i != children_.End(); ++i)
        {
            delete *i;
            *i = 0;
        }
    }
    
    /// Begin timing. Call count can also be specified if known to reduce overhead
    void Begin(unsigned count = 1)
    {
        timer_.Reset();
        count_ += count;
    }
    
    /// End timing
    void End()
    {
        time_ += timer_.GetUSec(false);
    }
    
    /// End profiling frame and update accumulation period and total values
    void EndFrame()
    {
        frameTime_ = time_;
        frameCount_ = count_;
        accumulatedTime_ += time_;
        accumulatedCount_ += count_;
        totalTime_ += time_;
        totalCount_ += count_;
        time_ = 0;
        count_ = 0;
        
        for (PODVector<ProfilerBlock*>::Iterator i = children_.Begin(); i != children_.End(); ++i)
            (*i)->EndFrame();
    }
    
    /// Clear accumulation period data
    void ClearAccumulated()
    {
        accumulatedTime_ = 0;
        accumulatedCount_ = 0;
        
        for (PODVector<ProfilerBlock*>::Iterator i = children_.Begin(); i != children_.End(); ++i)
            (*i)->ClearAccumulated();
    }
    
    /// Return child block with the specified name
    ProfilerBlock* GetChild(const char* name)
    {
        if (name == lastSearchName_)
            return lastSearchBlock_;
        
        lastSearchName_ = name;
        
        for (PODVector<ProfilerBlock*>::Iterator i = children_.Begin(); i != children_.End(); ++i)
        {
            if ((*i)->name_ == name)
            {
                lastSearchBlock_ = *i;
                return *i;
            }
        }
        
        ProfilerBlock* newBlock = new ProfilerBlock(this, name);
        children_.Push(newBlock);
        
        lastSearchBlock_ = newBlock;
        return newBlock;
    }
    
    /// Return name of block
    const char* GetName() const { return name_; }
    
    /// Return accumulated time during last frame
    long long GetFrameTime() const { return frameTime_; }
    /// Return number of calls during last frame
    unsigned GetFrameCount() const { return frameCount_; }
    /// Return accumulated time during the current accumulation period
    long long GetAccumulatedTime() const { return accumulatedTime_; }
    /// Return number of calls during the current accumulation period
    unsigned GetAccumulatedCount() const { return accumulatedCount_; }
    /// Return total accumulated time
    long long GetTotalTime() const { return totalTime_; }
    /// Return total number of calls
    unsigned GetTotalCount() const { return totalCount_; }
    /// Return parent block
    ProfilerBlock* GetParent() const { return parent_; }
    /// Return child blocks
    const PODVector<ProfilerBlock*>& GetChildren() const { return children_; }
    
private:
    /// Block name
    const char* name_;
    /// High-resolution timer for measuring the block duration
    HiresTimer timer_;
    /// Time on current frame
    long long time_;
    /// Calls on current frame
    unsigned count_;

    /// Parent block
    ProfilerBlock* parent_;    
    /// Last queried child block name (optimization)
    const char* lastSearchName_;
    /// Last queried child block (optimization)
    ProfilerBlock* lastSearchBlock_;
    /// Child blocks
    PODVector<ProfilerBlock*> children_;
    
    /// Time on the previous frame
    long long frameTime_;
    /// Calls on the previous frame
    unsigned frameCount_;
    /// Time on the accumulation period
    long long accumulatedTime_;
    /// Calls on the accumulation period
    unsigned accumulatedCount_;
    /// Total time
    long long totalTime_;
    /// Total calls
    unsigned totalCount_;
};

/// Hierarchical performance profiler subsystem
class Profiler : public Object
{
    OBJECT(Profiler);
    
public:
    /// Construct
    Profiler(Context* context);
    /// Destruct
    virtual ~Profiler();
    
    /// Begin timing a profiling block. Call count can also be specified if known to reduce overhead
    void BeginBlock(const char* name, unsigned count = 1)
    {
        current_ = current_->GetChild(name);
        current_->Begin(count);
    }
    
    /// End timing the current profiling block
    void EndBlock()
    {
        if (current_ != root_)
        {
            current_->End();
            current_ = current_->GetParent();
        }
    }
    
    /// Begin the profiling frame. Called by HandleBeginFrame()
    void BeginFrame();
    /// End the profiling frame. Called by HandleEndFrame()
    void EndFrame();
    /// Begin a new accumulation period
    void ClearAccumulated();
    
    /// Return profiling data as text output
    String GetData(bool showUnused = false, bool showAccumulated = false, bool showTotal = false) const;
    /// Return the current profiling block
    const ProfilerBlock* GetCurrentBlock() { return current_; }
    
private:
    /// Return profiling data as text output for a specified profiling block
    void GetData(ProfilerBlock* block, String& output, unsigned indent, bool showUnused, bool showAccumulated, bool showTotal) const;
    /// Handle begin frame event
    void HandleBeginFrame(StringHash eventType, VariantMap& eventData);
    /// Handle end frame event
    void HandleEndFrame(StringHash eventType, VariantMap& eventData);
    
    /// Current profiling block
    ProfilerBlock* current_;
    /// Root profiling block
    ProfilerBlock* root_;
    /// Frames in the current accumulation period
    unsigned accumulatedFrames_;
    /// Total frames
    unsigned totalFrames_;
};

/// Helper class for automatically beginning and ending a profiling block
class AutoProfileBlock
{
public:
    /// Construct. Begin a profiling block with the specified name and optional call count
    AutoProfileBlock(Profiler* profiler, const char* name, unsigned count = 1) :
        profiler_(profiler)
    {
        if (profiler_)
            profiler_->BeginBlock(name, count);
    }
    
    /// Destruct. End the profiling block
    ~AutoProfileBlock()
    {
        if (profiler_)
            profiler_->EndBlock();
    }
    
private:
    /// Profiler
    Profiler* profiler_;
};

#ifdef ENABLE_PROFILING
#define PROFILE(name) AutoProfileBlock profile_ ## name (GetSubsystem<Profiler>(), #name)
#define PROFILE_MULTIPLE(name, count) AutoProfileBlock profile_ ## name (GetSubsystem<Profiler>(), #name, count)
#else
#define PROFILE(name)
#define PROFILE_MULTIPLE(name, count)
#endif
