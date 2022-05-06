// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include "../Precompiled.h"

#include "../Container/RefCounted.h"

#include "../DebugNew.h"

namespace Urho3D
{

RefCounted::RefCounted() :
    refCount_(new RefCount())
{
    // Hold a weak ref to self to avoid possible double delete of the refcount
    (refCount_->weakRefs_)++;
}

RefCounted::~RefCounted()
{
    assert(refCount_);
    assert(refCount_->refs_ == 0);
    assert(refCount_->weakRefs_ > 0);

    // Mark object as expired, release the self weak ref and delete the refcount if no other weak refs exist
    refCount_->refs_ = -1;
    (refCount_->weakRefs_)--;
    if (!refCount_->weakRefs_)
        delete refCount_;

    refCount_ = nullptr;
}

void RefCounted::AddRef()
{
    assert(refCount_->refs_ >= 0);
    (refCount_->refs_)++;
}

void RefCounted::ReleaseRef()
{
    assert(refCount_->refs_ > 0);
    (refCount_->refs_)--;
    if (!refCount_->refs_)
        delete this;
}

int RefCounted::Refs() const
{
    return refCount_->refs_;
}

int RefCounted::WeakRefs() const
{
    // Subtract one to not return the internally held reference
    return refCount_->weakRefs_ - 1;
}

}
