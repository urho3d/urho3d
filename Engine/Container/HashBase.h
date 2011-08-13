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

#include "Allocator.h"
#include "Hash.h"
#include "Swap.h"

/// Hash set/map node base.
struct HashNodeBase
{
    /// Construct.
    HashNodeBase() :
        prev_(0),
        next_(0),
        down_(0)
    {
    }
    
    /// Previous node.
    HashNodeBase* prev_;
    /// Next node.
    HashNodeBase* next_;
    /// Next node in the bucket.
    HashNodeBase* down_;
};

/// Hash set/map iterator base class.
class HashIteratorBase
{
public:
    /// Construct.
    explicit HashIteratorBase(HashNodeBase* ptr) :
        ptr_(ptr)
    {
    }

    /// Test for equality with another iterator.
    bool operator == (const HashIteratorBase& rhs) const { return ptr_ == rhs.ptr_; }
    /// Test for inequality with another iterator.
    bool operator != (const HashIteratorBase& rhs) const { return ptr_ != rhs.ptr_; }

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
class HashBase
{
public:
    /// Initial amount of buckets.
    static const unsigned MIN_BUCKETS = 8;
    /// Maximum load factor.
    static const unsigned MAX_LOAD_FACTOR = 4;
    
    /// Construct.
    HashBase() :
        ptrs_(0),
        allocator_(0),
        size_(0),
        numBuckets_(0)
    {
    }

    /// Swap with another hash set or map.
    void Swap(HashBase& rhs)
    {
        ::Swap(head_, rhs.head_);
        ::Swap(tail_, rhs.tail_);
        ::Swap(ptrs_, rhs.ptrs_);
        ::Swap(allocator_, rhs.allocator_);
        ::Swap(size_, rhs.size_);
        ::Swap(numBuckets_, rhs.numBuckets_);
    }

protected:
    /// List head node pointer.
    HashNodeBase* head_;
    /// List tail node pointer.
    HashNodeBase* tail_;
    /// Bucket head pointers.
    HashNodeBase** ptrs_;
    /// Node allocator.
    AllocatorBlock* allocator_;
    /// Number of nodes.
    unsigned size_;
    /// Number of buckets.
    unsigned numBuckets_;
};
