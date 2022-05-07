// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include "../Precompiled.h"

#include "../Core/EventProfiler.h"

#include "../DebugNew.h"

namespace Urho3D
{

bool EventProfiler::active = false;

EventProfiler::EventProfiler(Context* context) :
    Profiler(context)
{
    // FIXME: Is there a cleaner way?
    delete root_;
    current_ = root_ = new EventProfilerBlock(nullptr, "RunFrame");
    delete [] root_->name_;
    root_->name_ = new char[sizeof("RunFrame")];
    memcpy(root_->name_, "RunFrame", sizeof("RunFrame"));
}

}
