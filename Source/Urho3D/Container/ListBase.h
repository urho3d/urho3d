// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#ifdef URHO3D_IS_BUILDING
#include "Urho3D.h"
#else
#include <Urho3D/Urho3D.h>
#endif

#include "../Container/Allocator.h"
#include "../Container/Swap.h"

namespace Urho3D
{

/// Doubly-linked list node base class.
struct ListNodeBase
{
    /// Construct.
    ListNodeBase() :
        prev_(nullptr),
        next_(nullptr)
    {
    }

    /// Previous node.
    ListNodeBase* prev_;
    /// Next node.
    ListNodeBase* next_;
};

/// Doubly-linked list iterator base class.
struct ListIteratorBase
{
    /// Construct.
    ListIteratorBase() :
        ptr_(nullptr)
    {
    }

    /// Construct with a node pointer.
    explicit ListIteratorBase(ListNodeBase* ptr) :
        ptr_(ptr)
    {
    }

    /// Test for equality with another iterator.
    bool operator ==(const ListIteratorBase& rhs) const { return ptr_ == rhs.ptr_; }

    /// Test for inequality with another iterator.
    bool operator !=(const ListIteratorBase& rhs) const { return ptr_ != rhs.ptr_; }

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
    ListNodeBase* ptr_;
};

/// Doubly-linked list base class.
class URHO3D_API ListBase
{
public:
    /// Construct.
    ListBase() :
        head_(nullptr),
        tail_(nullptr),
        allocator_(nullptr),
        size_(0)
    {
    }

    /// Swap with another linked list.
    void Swap(ListBase& rhs)
    {
        Urho3D::Swap(head_, rhs.head_);
        Urho3D::Swap(tail_, rhs.tail_);
        Urho3D::Swap(allocator_, rhs.allocator_);
        Urho3D::Swap(size_, rhs.size_);
    }

protected:
    /// Head node pointer.
    ListNodeBase* head_;
    /// Tail node pointer.
    ListNodeBase* tail_;
    /// Node allocator.
    AllocatorBlock* allocator_;
    /// Number of nodes.
    i32 size_;
};

}
