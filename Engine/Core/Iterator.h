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

/// Random access iterator
template <class T> class RandomAccessIterator
{
public:
    /// Construct
    explicit RandomAccessIterator(T* ptr) :
        ptr_(ptr)
    {
    }
    
    /// Point to the object
    T* operator -> () const { return ptr_; }
    /// Dereference the object
    T& operator * () const { return *ptr_; }
    /// Convert to a raw pointer
    operator T* () const { return ptr_; }
    /// Increment the pointer
    void operator ++ () { ++ptr_; }
    /// Decrement the pointer
    void operator -- () { --ptr_; }
    /// Add an offset to the pointer
    void operator += (unsigned value) { ptr_ += value; }
    /// Subtract an offset from the pointer
    void operator -= (unsigned value) { ptr_ -= value; }
    /// Add an offset to the pointer
    RandomAccessIterator operator + (unsigned value) { return RandomAccessIterator(ptr_ + value); }
    /// Subtract an offset from the pointer
    RandomAccessIterator operator - (unsigned value) { return RandomAccessIterator(ptr_ - value); }
    /// Calculate offset to another iterator
    int operator - (const RandomAccessIterator& rhs) const { return ptr_ - rhs.ptr_; }
    /// Test for equality with another iterator
    bool operator == (const RandomAccessIterator& rhs) const { return ptr_ == rhs.ptr_; }
    /// Test for inequality with another iterator
    bool operator != (const RandomAccessIterator& rhs) const { return ptr_ != rhs.ptr_; }
    
private:
    /// Pointer
    T* ptr_;
};

/// Random access const iterator
template <class T> class RandomAccessConstIterator
{
public:
    /// Construct
    explicit RandomAccessConstIterator(const T* ptr) :
        ptr_(ptr)
    {
    }
    
    /// Point to the object
    const T* operator -> () const { return ptr_; }
    /// Dereference the object
    const T& operator * () const { return *ptr_; }
    /// Convert to a raw pointer
    operator const T* () const { return ptr_; }
    /// Increment the pointer
    void operator ++ () { ++ptr_; }
    /// Decrement the pointer
    void operator -- () { --ptr_; }
    /// Add an offset to the pointer
    void operator += (unsigned value) { ptr_ += value; }
    /// Subtract an offset from the pointer
    void operator -= (unsigned value) { ptr_ -= value; }
    /// Add an offset to the pointer
    RandomAccessConstIterator operator + (unsigned value) { return RandomAccessConstIterator(ptr_ + value); }
    /// Subtract an offset from the pointer
    RandomAccessConstIterator operator - (unsigned value) { return RandomAccessConstIterator(ptr_ - value); }
    /// Calculate offset to another iterator
    int operator - (const RandomAccessConstIterator& rhs) const { return ptr_ - rhs.ptr_; }
    /// Test for equality with another iterator
    bool operator == (const RandomAccessConstIterator& rhs) const { return ptr_ == rhs.ptr_; }
    /// Test for inequality with another iterator
    bool operator != (const RandomAccessConstIterator& rhs) const { return ptr_ != rhs.ptr_; }
    
private:
    /// Pointer
    const T* ptr_;
};

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

/// List iterator base class
class ListIteratorBase
{
public:
    /// Test for equality with another iterator
    bool operator == (const ListIteratorBase& rhs) const { return ptr_ == rhs.ptr_; }
    /// Test for inequality with another iterator
    bool operator != (const ListIteratorBase& rhs) const { return ptr_ != rhs.ptr_; }
    
    /// Go to the next node
    void operator ++ ()
    {
        if (ptr_->next_)
            ptr_ = ptr_->next_;
    }
    
    /// Go to the previous node
    void operator -- ()
    {
        if (ptr_->prev_)
            ptr_ = ptr_->prev_;
    }
    
protected:
    /// Node pointer
    ListNodeBase* ptr_;
};
