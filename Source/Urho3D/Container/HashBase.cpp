// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include "../Precompiled.h"

#include "../DebugNew.h"

namespace Urho3D
{

void HashBase::AllocateBuckets(i32 size, i32 numBuckets)
{
    assert(size >= 0 && numBuckets > 0);

    delete[] ptrs_;

    HashNodeBase** ptrs = new HashNodeBase* [numBuckets + 2];
    i32* data = reinterpret_cast<i32*>(ptrs);
    data[0] = size;
    data[1] = numBuckets;
    ptrs_ = ptrs;

    ResetPtrs();
}

void HashBase::ResetPtrs()
{
    // Reset bucket pointers
    if (!ptrs_)
        return;

    i32 numBuckets = NumBuckets();
    HashNodeBase** ptrs = Ptrs();
    for (i32 i = 0; i < numBuckets; ++i)
        ptrs[i] = nullptr;
}

void HashBase::SetSize(i32 size)
{
    assert(size >= 0);

    if (ptrs_)
        (reinterpret_cast<i32*>(ptrs_))[0] = size;
}

}
