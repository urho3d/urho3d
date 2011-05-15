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

#include "Iterator.h"

#include <cstring>

/// Vector template class
template <class T> class Vector
{
public:
    typedef RandomAccessIterator<T> Iterator;
    typedef RandomAccessConstIterator<T> ConstIterator;
    
    /// Construct empty
    Vector() :
        size_(0),
        capacity_(0),
        buffer_(0)
    {
    }
    
    /// Construct with initial size
    explicit Vector(unsigned size) :
        size_(0),
        capacity_(0),
        buffer_(0)
    {
        Resize(size);
    }
    
    /// Construct from another vector
    Vector(const Vector<T>& vector) :
        size_(0),
        capacity_(0),
        buffer_(0)
    {
        *this = vector;
    }
    
    /// Destruct
    ~Vector()
    {
        delete[] buffer_;
    }
    
    /// Assign from another vector
    Vector<T>& operator = (const Vector<T>& rhs)
    {
        Resize(rhs.size_);
        CopyElements(buffer_, rhs.buffer_, rhs.size_);
        
        return *this;
    }
    
    /// Add-assign an element
    Vector<T>& operator += (const T& rhs)
    {
        Push(rhs);
        return *this;
    }
    
    /// Add-assign another vector
    Vector<T>& operator += (const Vector<T>& rhs)
    {
        Push(rhs);
        return *this;
    }
    
    /// Add an element
    Vector<T> operator + (const T& rhs) const
    {
        Vector<T> ret(*this);
        ret.Push(rhs);
        
        return ret;
    }
    
    /// Add another vector
    Vector<T> operator + (const Vector<T>& rhs) const
    {
        Vector<T> ret(*this);
        ret.Push(rhs);
        
        return ret;
    }
    
    /// Test for equality with another vector
    bool operator == (const Vector<T>& rhs)
    {
        if (rhs.size_ != size_)
            return false;
        
        for (unsigned i = 0; i < size_; ++i)
        {
            if (buffer_[i] != rhs.buffer_[i])
                return false;
        }
        
        return true;
    }
    
    /// Test for inequality with another vector
    bool operator != (const Vector<T>& rhs)
    {
        if (rhs.size_ != size_)
            return true;
        
        for (unsigned i = 0; i < size_; ++i)
        {
            if (buffer_[i] != rhs.buffer_[i])
                return true;
        }
        
        return false;
    }
    
    /// Return element at index
    T& operator [] (unsigned index) { return buffer_[index]; }
    /// Return const element at index
    const T& operator [] (unsigned index) const { return buffer_[index]; }
    
    /// Add an element at the end
    void Push(const T& value)
    {
        unsigned oldSize = size_;
        Resize(size_ + 1);
        buffer_[oldSize] = value;
    }
    
    /// Add another vector at the end
    void Push(const Vector<T>& vector)
    {
        if (!vector.size_)
            return;
        
        unsigned oldSize = size_;
        Resize(size_ + vector.size_);
        CopyElements(buffer_ + oldSize, vector.buffer_, vector.size_);
    }
    
    /// Remove the last element
    void Pop()
    {
        if (size_)
            Resize(size_ - 1);
    }
    
    /// Insert an element at position
    void Insert(unsigned pos, const T& value)
    {
        if (!size_)
        {
            Add(value);
            return;
        }
        
        if (pos > size_)
            pos = size_;
        
        unsigned oldSize = size_;
        Resize(size_ + 1);
        MoveRange(pos + 1, pos, oldSize - pos);
        buffer_[pos] = value;
    }
    
    /// Insert another vector at position
    void Insert(unsigned pos, const Vector<T>& vector)
    {
        if (!vector.size_)
            return;
            
        if (!size_)
        {
            *this = vector;
            return;
        }
        
        if (pos > size_)
            pos = size_;
        
        unsigned oldSize = size_;
        Resize(size_ + vector.size_);
        MoveRange(pos + vector.size_, pos, oldSize - pos);
        CopyElements(buffer_ + pos, vector.buffer_, vector.size_);
    }
    
    /// Insert an element using an iterator
    Iterator Insert(const Iterator& dest, const T& value)
    {
        unsigned pos = dest - Begin();
        if (pos > size_)
            pos = size_;
        Insert(pos, value);
        
        return Begin() + pos;
    }
    
    /// Insert a vector using an iterator
    Iterator Insert(const Iterator& dest, const Vector<T>& vector)
    {
        unsigned pos = dest - Begin();
        if (pos > size_)
            pos = size_;
        Insert(pos, vector);
        
        return Begin() + pos;
    }
    
    /// Insert a vector partially using iterators
    Iterator Insert(const Iterator& dest, const Iterator& start, const Iterator& end)
    {
        unsigned pos = dest - Begin();
        if (pos > size_)
            pos = size_;
        unsigned length = end - start;
        Resize(size_ + length);
        MoveRange(pos + length, pos, size_ - pos - length);
        
        T* destPtr = buffer_ + pos;
        for (Iterator i = start; i != end; ++i)
            *destPtr++ = *i;
        
        return Begin() + pos;
    }
    
    /// Erase a range of elements
    void Erase(unsigned pos, unsigned length = 1)
    {
        // Return if the range is illegal
        if ((!length) || (pos + length > size_))
            return;
        
        MoveRange(pos, pos + length, size_ - pos - length);
        Resize(size_ - length);
    }
    
    /// Erase an element using an iterator
    Iterator Erase(const Iterator& it)
    {
        unsigned pos = it - Begin();
        if (pos >= size_)
            return End();
        Erase(pos);
        
        return Begin() + pos;
    }
    
    /// Erase a range of values using iterators
    Iterator Erase(const Iterator& start, const Iterator& end)
    {
        unsigned pos = start - Begin();
        if (pos >= size_)
            return End();
        unsigned length = end - start;
        Erase(pos, length);
        
        return Begin() + pos;
    }
    
    /// Clear the vector
    void Clear()
    {
        Resize(0);
    }
    
    /// Resize the vector
    void Resize(unsigned newSize)
    {
        if (newSize == size_)
            return;
        
        if (newSize > capacity_)
        {
            if (!capacity_)
                capacity_ = newSize;
            else
            {
                while (capacity_ < newSize)
                {
                    unsigned increment = capacity_ >> 1;
                    if (!increment)
                        increment = 1;
                    capacity_ += increment;
                }
            }
            
            T* newBuffer = new T[capacity_];
            // Move the data into the new buffer and delete the old
            if (buffer_)
            {
                CopyElements(newBuffer, buffer_, size_);
                delete[] buffer_;
            }
            buffer_ = newBuffer;
        }
        
        size_ = newSize;
    }
    
    /// Set new capacity
    void Reserve(unsigned newCapacity)
    {
        if (newCapacity < size_)
            newCapacity = size_;
        if (newCapacity == capacity_)
            return;
        
        T* newBuffer = 0;
        capacity_ = newCapacity;
        
        if (capacity_)
        {
            newBuffer = new T[capacity_];
            // Move the data into the new buffer
            CopyElements(newBuffer, buffer_, size_);
        }
        
        // Delete the old buffer
        delete[] buffer_;
        buffer_ = newBuffer;
    }
    
    /// Reallocate so that no extra memory is used
    void Compact()
    {
        Reserve(size_);
    }
    
    /// Return iterator to the beginning
    Iterator Begin() { return Iterator(buffer_); }
    /// Return const iterator to the beginning
    ConstIterator Begin() const { return ConstIterator(buffer_); }
    /// Return iterator to the end
    Iterator End() { return Iterator(buffer_ + size_); }
    /// Return const iterator to the end
    ConstIterator End() const { return ConstIterator(buffer_ + size_); }
    /// Return size of vector
    unsigned Size() const { return size_; }
    /// Return capacity of vector
    unsigned Capacity() const { return capacity_; }
    /// Return whether vector is empty
    bool Empty() const { return size_ == 0; }
    
    /// Minimum dynamic allocation size
    static const unsigned MIN_CAPACITY = 1;
    
private:
    /// Move a range of elements within the vector
    void MoveRange(unsigned dest, unsigned src, unsigned count)
    {
        if (src < dest)
        {
            for (unsigned i = count - 1; i < count; --i)
                buffer_[dest + i] = buffer_[src + i];
        }
        if (src > dest)
        {
            for (unsigned i = 0; i < count; ++i)
                buffer_[dest + i] = buffer_[src + i];
        }
    }
    
    /// Copy elements from one buffer to another
    static void CopyElements(T* dest, const T* src, unsigned count)
    {
        for (unsigned i = 0; i < count; ++i)
            dest[i] = src[i];
    }
    
    /// Size of vector
    unsigned size_;
    /// Buffer capacity
    unsigned capacity_;
    /// Buffer
    T* buffer_;
};
