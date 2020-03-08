//
// Copyright (c) 2008-2020 the Urho3D project.
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

#include "../Container/Allocator.h"
#include "../Container/Hash.h"
#include "../Container/Swap.h"

namespace Urho3D
{

/// Hash set/map node base class.
struct HashNodeBase
{
    /// Construct.
    HashNodeBase() :
        down_(nullptr),
        prev_(nullptr),
        next_(nullptr)
    {
    }

    /// Next node in the bucket.
    HashNodeBase* down_;
    /// Previous node.
    HashNodeBase* prev_;
    /// Next node.
    HashNodeBase* next_;
};

/// Hash set/map iterator base class.
struct HashIteratorBase
{
    /// Construct.
    HashIteratorBase() :
        ptr_(nullptr)
    {
    }

    /// Construct with a node pointer.
    explicit HashIteratorBase(HashNodeBase* ptr) :
        ptr_(ptr)
    {
    }

    /// Test for equality with another iterator.
    bool operator ==(const HashIteratorBase& rhs) const { return ptr_ == rhs.ptr_; }

    /// Test for inequality with another iterator.
    bool operator !=(const HashIteratorBase& rhs) const { return ptr_ != rhs.ptr_; }

    /// Go to the next node.
    void GotoNext()
    {
        if (ptr_)
            ptr_ = ptr_->next_;
    }

    /// Go to the previous node.
    void GotoPrev()
    {
        if (ptr_)
            ptr_ = ptr_->prev_;
    }

    /// Node pointer.
    HashNodeBase* ptr_;
};

/// Hash set/map base class.
/** Note that to prevent extra memory use due to vtable pointer, %HashBase intentionally does not declare a virtual destructor
    and therefore %HashBase pointers should never be used.
  */
class URHO3D_API HashBase
{
public:
    /// Initial amount of buckets.
    static const unsigned MIN_BUCKETS = 8;
    /// Maximum load factor.
    static const unsigned MAX_LOAD_FACTOR = 4;

    /// Construct.
    HashBase() :
        head_(nullptr),
        tail_(nullptr),
        ptrs_(nullptr),
        allocator_(nullptr)
    {
    }

    /// Swap with another hash set or map.
    void Swap(HashBase& rhs)
    {
        Urho3D::Swap(head_, rhs.head_);
        Urho3D::Swap(tail_, rhs.tail_);
        Urho3D::Swap(ptrs_, rhs.ptrs_);
        Urho3D::Swap(allocator_, rhs.allocator_);
    }

    /// Return number of elements.
    unsigned Size() const { return ptrs_ ? (reinterpret_cast<unsigned*>(ptrs_))[0] : 0; }

    /// Return number of buckets.
    unsigned NumBuckets() const { return ptrs_ ? (reinterpret_cast<unsigned*>(ptrs_))[1] : 0; }

    /// Return whether has no elements.
    bool Empty() const { return Size() == 0; }

protected:
    /// Allocate bucket head pointers + room for size and bucket count variables.
    void AllocateBuckets(unsigned size, unsigned numBuckets);

    /// Reset bucket head pointers.
    void ResetPtrs();

    /// Set new size.
    void SetSize(unsigned size) { if (ptrs_) (reinterpret_cast<unsigned*>(ptrs_))[0] = size; }

    /// Return bucket head pointers.
    HashNodeBase** Ptrs() const { return ptrs_ ? ptrs_ + 2 : nullptr; }

    /// List head node pointer.
    HashNodeBase* head_;
    /// List tail node pointer.
    HashNodeBase* tail_;
    /// Bucket head pointers.
    HashNodeBase** ptrs_;
    /// Node allocator.
    AllocatorBlock* allocator_;
};

}
