//
// Copyright (c) 2008-2022 the Urho3D project.
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

#ifdef URHO3D_IS_BUILDING
#include "Urho3D.h"
#else
#include <Urho3D/Urho3D.h>
#endif

#include <cassert>

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
private:
    /// Reference count. If below zero, the object has been destroyed.
    int refs_;

    /// Pointer to weak reference counter. Only created the first time WeakPtr is used.
    /// If negative, the object has been destroyed.
    int* weakRefsPtr_;

public:
    /// Construct.
    RefCounted()
       : refs_(0)
       , weakRefsPtr_(nullptr)
    {
    }
    
    /// Destruct.
    virtual ~RefCounted()
    {
        assert(refs_ == 0);

        // Mark object as destroyed to fire asserts if this object is still accessed
        refs_ = -1;

        if (weakRefsPtr_)
        {
            if (*weakRefsPtr_ == 0) // If no WeakPtr
                delete weakRefsPtr_;
            else
                *weakRefsPtr_ = -(*weakRefsPtr_); // Mark object as destroyed. Will be deleted by the last WeakPtr
        }
    }

    /// Prevent copy construction.
    RefCounted(const RefCounted& rhs) = delete;
    
    /// Prevent assignment.
    RefCounted& operator =(const RefCounted& rhs) = delete;

    /// Increment reference count.
    /// @manualbind
    void AddRef()
    {
        assert(refs_ >= 0);
        refs_++;
    }

    /// Decrement reference count and delete self if no more references.
    /// @manualbind
    void ReleaseRef()
    {
        assert(refs_ > 0);
        refs_--;
        
        if (!refs_)
            delete this;
    }
    
    /// Return reference count.
    /// @property
    int Refs() const
    {
        assert(refs_ >= 0);
        return refs_;
    }

    /// Set reference count manually.
    void SetRefs(int value)
    {
        assert(value >= 0);
        refs_ = value;
    }
    
    /// Return weak reference count.
    /// @property
    int WeakRefs() const
    {
        assert(refs_ >= 0);
        return weakRefsPtr_ ? *weakRefsPtr_ : 0;
    }

    /// Return pointer to weak reference counter. Allocate if it doesn't already exist.
    int* GetOrCreateWeakRefs()
    {
        assert(refs_ >= 0);
        
        if (!weakRefsPtr_)
            weakRefsPtr_ = new int(0);

        return weakRefsPtr_;
    }
};

}
