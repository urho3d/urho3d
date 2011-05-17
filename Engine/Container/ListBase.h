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

#include "Swap.h"

#include <cstdlib>

/// List node base
struct ListNodeBase
{
    ListNodeBase() :
        prev_(0),
        next_(0)
    {
    }
    
    /// Previous node
    ListNodeBase* prev_;
    /// Next node
    ListNodeBase* next_;
};

/// List iterator base class
class ListIteratorBase
{
public:
    explicit ListIteratorBase(ListNodeBase* ptr) :
        ptr_(ptr)
    {
    }
    
    /// Test for equality with another iterator
    bool operator == (const ListIteratorBase& rhs) const { return ptr_ == rhs.ptr_; }
    /// Test for inequality with another iterator
    bool operator != (const ListIteratorBase& rhs) const { return ptr_ != rhs.ptr_; }
    
    /// Go to the next node
    void GotoNext()
    {
        if (ptr_->next_)
            ptr_ = ptr_->next_;
    }
    
    /// Go to the previous node
    void GotoPrev()
    {
        if (ptr_->prev_)
            ptr_ = ptr_->prev_;
    }
    
    /// Node pointer
    ListNodeBase* ptr_;
};

/// Linked list base class
class ListBase
{
public:
    ListBase() :
        size_(0)
    {
    }
    
    /// Swap with another linked list
    void Swap(ListBase& rhs)
    {
        ::Swap(head_, rhs.head_);
        ::Swap(tail_, rhs.tail_);
        ::Swap(size_, rhs.size_);
    }
    
protected:
    /// Head node pointer
    ListNodeBase* head_;
    /// Tail node pointer
    ListNodeBase* tail_;
    /// Number of nodes
    unsigned size_;
};

/// Skip list node base
struct SkipListNodeBase : public ListNodeBase
{
    /// Node height
    unsigned height_;
    /// Skip list pointers for heights > 1
    SkipListNodeBase** levels_;
    
    /// Return next node on a specific height
    SkipListNodeBase* GetNext(unsigned height) const
    {
        if (!height)
            return static_cast<SkipListNodeBase*>(next_);
        else
            return levels_[height - 1];
    }
    
    /// Return previous node
    SkipListNodeBase* GetPrev() const { return static_cast<SkipListNodeBase*>(prev_); }
    
    // Set next node on a specific height
    void SetNext(unsigned height, SkipListNodeBase* node)
    {
        if (!height)
            next_ = node;
        else
            levels_[height - 1] = node;
    }
    
    /// Set previous node
    void SetPrev(SkipListNodeBase* node) { prev_ = node; }
};

/// Skip list base class
class SkipListBase
{
public:
    SkipListBase(unsigned maxHeight = MAX_HEIGHT) :
        maxHeight_(maxHeight < MAX_HEIGHT ? maxHeight : MAX_HEIGHT),
        height_(0),
        size_(0),
        bitsLeft_(0)
    {
    }
    
    /// Swap with another skip list
    void Swap(SkipListBase& rhs)
    {
        ::Swap(head_, rhs.head_);
        ::Swap(tail_, rhs.tail_);
        ::Swap(fix_, rhs.fix_);
        ::Swap(maxHeight_, rhs.maxHeight_);
        ::Swap(height_, rhs.height_);
        ::Swap(size_, rhs.size_);
        ::Swap(random_, rhs.random_);
        ::Swap(bitsLeft_, rhs.bitsLeft_);
    }
    
    static const unsigned MAX_HEIGHT = 15;
    
protected:
    /// Generate a random height for a new node
    unsigned GetHeight()
    {
        unsigned height = 1;
        while ((height < maxHeight_) && (GetBit()))
            ++height;
        
        return height;
    }
    
    /// Return a random true/false result
    bool GetBit()
    {
        if (!bitsLeft_)
        {
            random_ = rand();
            bitsLeft_ = 15;
        }
        
        bool ret = (random_ & 1) != 0;
        random_ >>= 1;
        --bitsLeft_;
        
        return ret;
    }
    
    /// Head node pointer
    void* head_;
    /// Tail node pointer
    void* tail_;
    /// Fixup pointers for insert & erase
    void** fix_;
    /// Maximum height
    unsigned maxHeight_;
    /// Current height
    unsigned height_;
    /// Number of keys
    unsigned size_;
    /// Random bits
    unsigned short random_;
    /// Random bits remaining
    unsigned short bitsLeft_;
};
