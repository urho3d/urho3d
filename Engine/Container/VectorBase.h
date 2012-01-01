//
// Urho3D Engine
// Copyright (c) 2008-2012 Lasse Öörni
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

/// Random access iterator.
template <class T> class RandomAccessIterator
{
public:
    /// Construct.
    RandomAccessIterator() :
        ptr_(0)
    {
    }
    
    /// Construct with an object pointer.
    explicit RandomAccessIterator(T* ptr) :
        ptr_(ptr)
    {
    }
    
    /// Point to the object.
    T* operator -> () const { return ptr_; }
    /// Dereference the object.
    T& operator * () const { return *ptr_; }
    /// Preincrement the pointer.
    RandomAccessIterator<T>& operator ++ () { ++ptr_; return *this; }
    /// Postincrement the pointer.
    RandomAccessIterator<T> operator ++ (int) { RandomAccessIterator<T> it = *this; ++ptr_; return it; }
    /// Predecrement the pointer.
    RandomAccessIterator<T>& operator -- () { --ptr_; return *this; }
    /// Postdecrement the pointer.
    RandomAccessIterator<T> operator -- (int) { RandomAccessIterator<T> it = *this; --ptr_; return it; }
    /// Add an offset to the pointer.
    RandomAccessIterator<T>& operator += (int value) { ptr_ += value; return *this; }
    /// Subtract an offset from the pointer.
    RandomAccessIterator<T>& operator -= (int value) { ptr_ -= value; return *this; }
    /// Add an offset to the pointer.
    RandomAccessIterator<T> operator + (int value) const { return RandomAccessIterator<T>(ptr_ + value); }
    /// Subtract an offset from the pointer.
    RandomAccessIterator<T> operator - (int value) const { return RandomAccessIterator<T>(ptr_ - value); }
    /// Calculate offset to another iterator.
    int operator - (const RandomAccessIterator& rhs) const { return ptr_ - rhs.ptr_; }
    /// Test for equality with another iterator.
    bool operator == (const RandomAccessIterator& rhs) const { return ptr_ == rhs.ptr_; }
    /// Test for inequality with another iterator.
    bool operator != (const RandomAccessIterator& rhs) const { return ptr_ != rhs.ptr_; }
    /// Test for less than with another iterator.
    bool operator < (const RandomAccessIterator& rhs) const { return ptr_ < rhs.ptr_; }
    /// Test for greater than with another iterator.
    bool operator > (const RandomAccessIterator& rhs) const { return ptr_ > rhs.ptr_; }
    /// Test for less than or equal with another iterator.
    bool operator <= (const RandomAccessIterator& rhs) const { return ptr_ <= rhs.ptr_; }
    /// Test for greater than or equal with another iterator.
    bool operator >= (const RandomAccessIterator& rhs) const { return ptr_ >= rhs.ptr_; }
    
    /// Pointer.
    T* ptr_;
};

/// Random access const iterator.
template <class T> class RandomAccessConstIterator
{
public:
    /// Construct.
    RandomAccessConstIterator() :
        ptr_(0)
    {
    }
    
    /// Construct with an object pointer.
    explicit RandomAccessConstIterator(T* ptr) :
        ptr_(ptr)
    {
    }
    
    /// Construct from a non-const iterator.
    RandomAccessConstIterator(const RandomAccessIterator<T>& rhs) :
        ptr_(rhs.ptr_)
    {
    }
    
    /// Assign from a non-const iterator.
    RandomAccessConstIterator<T>& operator = (const RandomAccessIterator<T>& rhs) { ptr_ = rhs.ptr_; return *this; }
    /// Point to the object.
    const T* operator -> () const { return ptr_; }
    /// Dereference the object.
    const T& operator * () const { return *ptr_; }
    /// Preincrement the pointer.
    RandomAccessConstIterator<T>& operator ++ () { ++ptr_; return *this; }
    /// Postincrement the pointer.
    RandomAccessConstIterator<T> operator ++ (int) { RandomAccessConstIterator<T> it = *this; ++ptr_; return it; }
    /// Predecrement the pointer.
    RandomAccessConstIterator<T>& operator -- () { --ptr_; return *this; }
    /// Postdecrement the pointer.
    RandomAccessConstIterator<T> operator -- (int) { RandomAccessConstIterator<T> it = *this; --ptr_; return it; }
    /// Add an offset to the pointer.
    RandomAccessConstIterator<T>& operator += (int value) { ptr_ += value; return *this; }
    /// Subtract an offset from the pointer.
    RandomAccessConstIterator<T>& operator -= (int value) { ptr_ -= value; return *this; }
    /// Add an offset to the pointer.
    RandomAccessConstIterator<T> operator + (int value) const { return RandomAccessConstIterator<T>(ptr_ + value); }
    /// Subtract an offset from the pointer.
    RandomAccessConstIterator<T> operator - (int value) const { return RandomAccessConstIterator<T>(ptr_ - value); }
    /// Calculate offset to another iterator.
    int operator - (const RandomAccessConstIterator& rhs) const { return ptr_ - rhs.ptr_; }
    /// Test for equality with another iterator.
    bool operator == (const RandomAccessConstIterator& rhs) const { return ptr_ == rhs.ptr_; }
    /// Test for inequality with another iterator.
    bool operator != (const RandomAccessConstIterator& rhs) const { return ptr_ != rhs.ptr_; }
    /// Test for less than with another iterator.
    bool operator < (const RandomAccessConstIterator& rhs) const { return ptr_ < rhs.ptr_; }
    /// Test for greater than with another iterator.
    bool operator > (const RandomAccessConstIterator& rhs) const { return ptr_ > rhs.ptr_; }
    /// Test for less than or equal with another iterator.
    bool operator <= (const RandomAccessConstIterator& rhs) const { return ptr_ <= rhs.ptr_; }
    /// Test for greater than or equal with another iterator.
    bool operator >= (const RandomAccessConstIterator& rhs) const { return ptr_ >= rhs.ptr_; }
    
    /// Pointer.
    T* ptr_;
};

/// %Vector base class.
class VectorBase
{
public:
    /// Construct.
    VectorBase() :
        size_(0),
        capacity_(0),
        buffer_(0)
    {
    }
    
    /// Swap with another vector.
    void Swap(VectorBase& rhs)
    {
        ::Swap(size_, rhs.size_);
        ::Swap(capacity_, rhs.capacity_);
        ::Swap(buffer_, rhs.buffer_);
    }
    
protected:
    /// Size of vector.
    unsigned size_;
    /// Buffer capacity.
    unsigned capacity_;
    /// Buffer.
    unsigned char* buffer_;
};
