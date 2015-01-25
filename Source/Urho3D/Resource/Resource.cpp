//
// Copyright (c) 2008-2014 the Urho3D project.
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

#include "../IO/Log.h"
#include "../Core/Profiler.h"
#include "../Resource/Resource.h"

namespace Urho3D
{

Resource::Resource(Context* context) :
    Object(context),
    memoryUse_(0),
    asyncLoadState_(ASYNC_DONE)
{
}

bool Resource::Load(Deserializer& source)
{
    // Because BeginLoad() / EndLoad() can be called from worker threads, where profiling would be a no-op,
    // create a type name -based profile block here
#ifdef URHO3D_PROFILING
    String profileBlockName("Load" + GetTypeName());
    
    Profiler* profiler = GetSubsystem<Profiler>();
    if (profiler)
        profiler->BeginBlock(profileBlockName.CString());
#endif

    // Make sure any previous async state is cancelled
    SetAsyncLoadState(ASYNC_DONE);

    bool success = BeginLoad(source);
    if (success)
        success &= EndLoad();

#ifdef URHO3D_PROFILING
    if (profiler)
        profiler->EndBlock();
#endif

    return success;
}

bool Resource::BeginLoad(Deserializer& source)
{
    // This always needs to be overridden by subclasses
    return false;
}

bool Resource::EndLoad()
{
    // If no GPU upload step is necessary, no override is necessary
    return true;
}

bool Resource::Save(Serializer& dest) const
{
    LOGERROR("Save not supported for " + GetTypeName());
    return false;
}

void Resource::SetName(const String& name)
{
    name_ = name;
    nameHash_ = name;
}

void Resource::SetMemoryUse(unsigned size)
{
    memoryUse_ = size;
}

void Resource::ResetUseTimer()
{
    useTimer_.Reset();
}

void Resource::SetAsyncLoadState(AsyncLoadState newState)
{
    asyncLoadState_ = newState;
}

unsigned Resource::GetUseTimer()
{
    // If more references than the resource cache, return always 0 & reset the timer
    if (Refs() > 1)
    {
        useTimer_.Reset();
        return 0;
    }
    else
        return useTimer_.GetMSec(false);
}

}
