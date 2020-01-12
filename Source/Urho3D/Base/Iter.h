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

#include "../Urho3DConfig.h"

namespace Urho3D
{

/// Random access iterator.
template <class T> struct RandomAccessIterator
{
    /// Construct.
    constexpr RandomAccessIterator() :
        ptr_(nullptr)
    {
    }

    /// Construct with an object pointer.
    explicit constexpr RandomAccessIterator(T* ptr) :
        ptr_(ptr)
    {
    }

    /// Point to the object.
    constexpr T* operator ->() const { return ptr_; }

    /// Dereference the object.
    constexpr T& operator *() const { return *ptr_; }

    /// Preincrement the pointer.
    URHO_CPP14(constexpr) RandomAccessIterator<T>& operator ++()
    {
        ++ptr_;
        return *this;
    }

    /// Postincrement the pointer.
    URHO_CPP14(constexpr) RandomAccessIterator<T> operator ++(int)
    {
        RandomAccessIterator<T> it = *this;
        ++ptr_;
        return it;
    }

    /// Predecrement the pointer.
    URHO_CPP14(constexpr) RandomAccessIterator<T>& operator --()
    {
        --ptr_;
        return *this;
    }

    /// Postdecrement the pointer.
    URHO_CPP14(constexpr) RandomAccessIterator<T> operator --(int)
    {
        RandomAccessIterator<T> it = *this;
        --ptr_;
        return it;
    }

    /// Add an offset to the pointer.
    URHO_CPP14(constexpr) RandomAccessIterator<T>& operator +=(int value)
    {
        ptr_ += value;
        return *this;
    }

    /// Subtract an offset from the pointer.
    URHO_CPP14(constexpr) RandomAccessIterator<T>& operator -=(int value)
    {
        ptr_ -= value;
        return *this;
    }

    /// Add an offset to the pointer.
    constexpr RandomAccessIterator<T> operator +(int value) const { return RandomAccessIterator<T>(ptr_ + value); }

    /// Subtract an offset from the pointer.
    constexpr RandomAccessIterator<T> operator -(int value) const { return RandomAccessIterator<T>(ptr_ - value); }

    /// Calculate offset to another iterator.
    constexpr int operator -(const RandomAccessIterator& rhs) const { return (int)(ptr_ - rhs.ptr_); }

    /// Test for equality with another iterator.
    constexpr bool operator ==(const RandomAccessIterator& rhs) const { return ptr_ == rhs.ptr_; }

    /// Test for inequality with another iterator.
    constexpr bool operator !=(const RandomAccessIterator& rhs) const { return ptr_ != rhs.ptr_; }

    /// Test for less than with another iterator.
    constexpr bool operator <(const RandomAccessIterator& rhs) const { return ptr_ < rhs.ptr_; }

    /// Test for greater than with another iterator.
    constexpr bool operator >(const RandomAccessIterator& rhs) const { return ptr_ > rhs.ptr_; }

    /// Test for less than or equal with another iterator.
    constexpr bool operator <=(const RandomAccessIterator& rhs) const { return ptr_ <= rhs.ptr_; }

    /// Test for greater than or equal with another iterator.
    constexpr bool operator >=(const RandomAccessIterator& rhs) const { return ptr_ >= rhs.ptr_; }

    /// Pointer.
    T* ptr_;
};

/// Random access const iterator.
template <class T> struct RandomAccessConstIterator
{
    /// Construct.
    constexpr RandomAccessConstIterator() :
        ptr_(0)
    {
    }

    /// Construct with an object pointer.
    constexpr explicit RandomAccessConstIterator(const T* ptr) :
        ptr_(ptr)
    {
    }

    /// Construct from a non-const iterator.
    constexpr RandomAccessConstIterator(const RandomAccessIterator<T>& rhs) :     // NOLINT(google-explicit-constructor)
        ptr_(rhs.ptr_)
    {
    }

    /// Assign from a non-const iterator.
    URHO_CPP14(constexpr) RandomAccessConstIterator<T>& operator =(const RandomAccessIterator<T>& rhs)
    {
        ptr_ = rhs.ptr_;
        return *this;
    }

    /// Point to the object.
    constexpr const T* operator ->() const { return ptr_; }

    /// Dereference the object.
    constexpr const T& operator *() const { return *ptr_; }

    /// Preincrement the pointer.
    URHO_CPP14(constexpr) RandomAccessConstIterator<T>& operator ++()
    {
        ++ptr_;
        return *this;
    }

    /// Postincrement the pointer.
    URHO_CPP14(constexpr) RandomAccessConstIterator<T> operator ++(int)
    {
        RandomAccessConstIterator<T> it = *this;
        ++ptr_;
        return it;
    }

    /// Predecrement the pointer.
    URHO_CPP14(constexpr) RandomAccessConstIterator<T>& operator --()
    {
        --ptr_;
        return *this;
    }

    /// Postdecrement the pointer.
    URHO_CPP14(constexpr) RandomAccessConstIterator<T> operator --(int)
    {
        RandomAccessConstIterator<T> it = *this;
        --ptr_;
        return it;
    }

    /// Add an offset to the pointer.
    URHO_CPP14(constexpr) RandomAccessConstIterator<T>& operator +=(int value)
    {
        ptr_ += value;
        return *this;
    }

    /// Subtract an offset from the pointer.
    URHO_CPP14(constexpr) RandomAccessConstIterator<T>& operator -=(int value)
    {
        ptr_ -= value;
        return *this;
    }

    /// Add an offset to the pointer.
    constexpr RandomAccessConstIterator<T> operator +(int value) const { return RandomAccessConstIterator<T>(ptr_ + value); }

    /// Subtract an offset from the pointer.
    constexpr RandomAccessConstIterator<T> operator -(int value) const { return RandomAccessConstIterator<T>(ptr_ - value); }

    /// Calculate offset to another iterator.
    constexpr int operator -(const RandomAccessConstIterator& rhs) const { return (int)(ptr_ - rhs.ptr_); }

    /// Test for equality with another iterator.
    constexpr bool operator ==(const RandomAccessConstIterator& rhs) const { return ptr_ == rhs.ptr_; }

    /// Test for inequality with another iterator.
    constexpr bool operator !=(const RandomAccessConstIterator& rhs) const { return ptr_ != rhs.ptr_; }

    /// Test for less than with another iterator.
    constexpr bool operator <(const RandomAccessConstIterator& rhs) const { return ptr_ < rhs.ptr_; }

    /// Test for greater than with another iterator.
    constexpr bool operator >(const RandomAccessConstIterator& rhs) const { return ptr_ > rhs.ptr_; }

    /// Test for less than or equal with another iterator.
    constexpr bool operator <=(const RandomAccessConstIterator& rhs) const { return ptr_ <= rhs.ptr_; }

    /// Test for greater than or equal with another iterator.
    constexpr bool operator >=(const RandomAccessConstIterator& rhs) const { return ptr_ >= rhs.ptr_; }

    /// Pointer.
    const T* ptr_;
};

}
