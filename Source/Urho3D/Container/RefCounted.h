// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#ifdef URHO3D_IS_BUILDING
#include "Urho3D.h"
#else
#include <Urho3D/Urho3D.h>
#endif

namespace Urho3D
{

/// Reference count structure.
struct RefCount
{
    /// Construct.
    RefCount() :
        refs_(0),
        weakRefs_(0)
    {
    }

    /// Destruct.
    ~RefCount()
    {
        // Set reference counts below zero to fire asserts if this object is still accessed
        refs_ = -1;
        weakRefs_ = -1;
    }

    /// Reference count. If below zero, the object has been destroyed.
    int refs_;
    /// Weak reference count.
    int weakRefs_;
};

/// Base class for intrusively reference-counted objects. These are noncopyable and non-assignable.
class URHO3D_API RefCounted
{
public:
    /// Construct. Allocate the reference count structure and set an initial self weak reference.
    RefCounted();
    /// Destruct. Mark as expired and also delete the reference count structure if no outside weak references exist.
    virtual ~RefCounted();

    /// Prevent copy construction.
    RefCounted(const RefCounted& rhs) = delete;
    /// Prevent assignment.
    RefCounted& operator =(const RefCounted& rhs) = delete;

    /// Increment reference count. Can also be called outside of a SharedPtr for traditional reference counting.
    /// @manualbind
    void AddRef();
    /// Decrement reference count and delete self if no more references. Can also be called outside of a SharedPtr for traditional reference counting.
    /// @manualbind
    void ReleaseRef();
    /// Return reference count.
    /// @property
    int Refs() const;
    /// Return weak reference count.
    /// @property
    int WeakRefs() const;

    /// Return pointer to the reference count structure.
    RefCount* RefCountPtr() { return refCount_; }

private:
    /// Pointer to the reference count structure.
    RefCount* refCount_;
};

}
