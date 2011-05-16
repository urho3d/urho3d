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
