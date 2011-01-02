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

#ifndef COMMON_PROFILER_H
#define COMMON_PROFILER_H

#include "RefCount.h"
#include "Timer.h"

#include <string>
#include <vector>

//! Profiling data for one block in the profiling tree
class ProfilerBlock
{
public:
    //! Construct with the specified parent block and name
    ProfilerBlock(ProfilerBlock* parent, const char* name) :
        mName(name),
        mParent(parent),
        mTime(0),
        mCount(0),
        mFrameTime(0),
        mFrameCount(0),
        mAccumulatedTime(0),
        mAccumulatedCount(0),
        mTotalTime(0),
        mTotalCount(0),
        mLastSearchName(0),
        mLastSearchBlock(0)
    {
    }
    
    //! Destruct. Free the child blocks
    ~ProfilerBlock()
    {
        for (std::vector<ProfilerBlock*>::iterator i = mChildren.begin(); i != mChildren.end(); ++i)
        {
            delete *i;
            *i = 0;
        }
    }
    
    //! Begin timing. Call count can also be specified if known to reduce overhead
    void begin(unsigned count = 1)
    {
        mTimer.reset();
        mCount += count;
    }
    
    //! End timing
    void end()
    {
        mTime += mTimer.getUSec(false);
    }
    
    //! End profiling frame and update accumulation period and total values
    void endFrame()
    {
        mFrameTime = mTime;
        mFrameCount = mCount;
        mAccumulatedTime += mTime;
        mAccumulatedCount += mCount;
        mTotalTime += mTime;
        mTotalCount += mCount;
        mTime = 0;
        mCount = 0;
        
        for (std::vector<ProfilerBlock*>::iterator i = mChildren.begin(); i != mChildren.end(); ++i)
            (*i)->endFrame();
    }
    
    //! Clear accumulation period data
    void clearAccumulated()
    {
        mAccumulatedTime = 0;
        mAccumulatedCount = 0;
        
        for (std::vector<ProfilerBlock*>::iterator i = mChildren.begin(); i != mChildren.end(); ++i)
            (*i)->clearAccumulated();
    }
    
    //! Return child block with the specified name
    ProfilerBlock* getChild(const char* name)
    {
        if (name == mLastSearchName)
            return mLastSearchBlock;
        
        mLastSearchName = name;
        
        for (std::vector<ProfilerBlock*>::iterator i = mChildren.begin(); i != mChildren.end(); ++i)
        {
            if ((*i)->mName == name)
            {
                mLastSearchBlock = *i;
                return *i;
            }
        }
        
        ProfilerBlock* newBlock = new ProfilerBlock(this, name);
        mChildren.push_back(newBlock);
        
        mLastSearchBlock = newBlock;
        return newBlock;
    }
    
    //! Return name of block
    const char* getName() const { return mName; }
    
    //! Return accumulated time during last frame
    long long getFrameTime() const { return mFrameTime; }
    //! Return number of calls during last frame
    unsigned getFrameCount() const { return mFrameCount; }
    //! Return accumulated time during the current accumulation period
    long long getAccumulatedTime() const { return mAccumulatedTime; }
    //! Return number of calls during the current accumulation period
    unsigned getAccumulatedCount() const { return mAccumulatedCount; }
    //! Return total accumulated time
    long long getTotalTime() const { return mTotalTime; }
    //! Return total number of calls
    unsigned getTotalCount() const { return mTotalCount; }
    //! Return parent block
    ProfilerBlock* getParent() const { return mParent; }
    //! Return child blocks
    const std::vector<ProfilerBlock*>& getChildren() const { return mChildren; }
    
private:
    //! Prevent copy construction
    ProfilerBlock(const ProfilerBlock& rhs);
    //! Prevent assignment
    ProfilerBlock& operator = (const ProfilerBlock& rhs);
    
    //! Block name
    const char* mName;
    //! Hires timer for measuring the block duration
    HiresTimer mTimer;
    //! Time on current frame
    long long mTime;
    //! Calls on current frame
    unsigned mCount;
    
    //! Last queried child block name(optimization)
    const char* mLastSearchName;
    //! Last queried child block (optimization)
    ProfilerBlock* mLastSearchBlock;
    //! Parent block
    ProfilerBlock* mParent;
    //! Child blocks
    std::vector<ProfilerBlock*> mChildren;
    
    //! Time on the previous frame
    long long mFrameTime;
    //! Calls on the previous frame
    unsigned mFrameCount;
    //! Time on the accumulation period
    long long mAccumulatedTime;
    //! Calls on the accumulation period
    unsigned mAccumulatedCount;
    //! Total time
    long long mTotalTime;
    //! Total calls
    unsigned mTotalCount;
};

//! A hierarchical performance profiler
class Profiler : public RefCounted
{
    friend Profiler* getProfiler();
    
public:
    //! Construct
    Profiler();
    //! Destruct
    virtual ~Profiler();
    
    //! Begin timing a profiling block. Call count can also be specified if known to reduce overhead
    void beginBlock(const char* name, unsigned count = 1)
    {
        mCurrent = mCurrent->getChild(name);
        mCurrent->begin(count);
    }
    
    //! End timing the current profiling block
    void endBlock()
    {
        if (mCurrent != mRoot)
        {
            mCurrent->end();
            mCurrent = mCurrent->getParent();
        }
    }
    
    //! Begin the profiling frame
    void beginFrame();
    //! End the profiling frame and calculate frame results
    void endFrame();
    //! Begin a new accumulation period
    void clearAccumulated();
    
    //! Return profiling data as text output
    std::string getData(bool showUnused = false, bool showAccumulated = false, bool showTotal = false) const;
    //! Return the current profiling block
    const ProfilerBlock* getCurrentBlock() { return mCurrent; }
    
private:
    //! Return profiling data as text output for a specified profiling block
    void getData(ProfilerBlock* block, std::string& output, unsigned indent, bool showUnused, bool showAccumulated, bool showTotal) const;
    
    //! Current profiling block
    ProfilerBlock* mCurrent;
    //! Root profiling block
    ProfilerBlock* mRoot;
    //! Frames in the current accumulation period
    unsigned mAccumulatedFrames;
    //! Total frames
    unsigned mTotalFrames;
    
    //! Profiler instance
    static Profiler* sInstance;
};

//! Return the Profiler instance
inline Profiler* getProfiler()
{
    return Profiler::sInstance;
}

//! A helper class for automatically beginning and ending a profiling block
class AutoProfileBlock
{
public:
    //! Construct. Begin a profiling block with the specified name and optional call count
    AutoProfileBlock(const char* name, unsigned count = 1)
    {
        Profiler* profiler = getProfiler();
        if (profiler)
            profiler->beginBlock(name, count);
    }
    
    //! Destruct. End the profiling block
    ~AutoProfileBlock()
    {
        Profiler* profiler = getProfiler();
        if (profiler)
            profiler->endBlock();
    }
};

#ifdef ENABLE_PROFILING
#define PROFILE(name) AutoProfileBlock profile_ ## name (#name)
#define PROFILE_MULTIPLE(name, count) AutoProfileBlock profile_ ## name (#name, count)
#else
#define PROFILE(name)
#define PROFILE_MULTIPLE(name, count)
#endif

#endif // COMMON_PROFILER_H
