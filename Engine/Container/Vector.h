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

#include "VectorBase.h"

#include <cstring>
#include <new>

/// Vector template class
template <class T> class Vector : public VectorBase
{
public:
    typedef RandomAccessIterator<T> Iterator;
    typedef RandomAccessConstIterator<T> ConstIterator;
    
    /// Construct empty
    Vector()
    {
    }
    
    /// Construct with initial size
    explicit Vector(unsigned size)
    {
        Resize(size, 0);
    }
    
    /// Construct from another vector
    Vector(const Vector<T>& vector)
    {
        *this = vector;
    }
    
    /// Destruct
    ~Vector()
    {
        Clear();
        delete[] buffer_;
    }
    
    /// Assign from another vector
    Vector<T>& operator = (const Vector<T>& rhs)
    {
        Clear();
        Resize(rhs.size_, rhs.GetBuffer());
        
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
    bool operator == (const Vector<T>& rhs) const
    {
        if (rhs.size_ != size_)
            return false;
        
        T* buffer = GetBuffer();
        T* rhsBuffer = rhs.GetBuffer();
        for (unsigned i = 0; i < size_; ++i)
        {
            if (buffer[i] != rhsBuffer[i])
                return false;
        }
        
        return true;
    }
    
    /// Test for inequality with another vector
    bool operator != (const Vector<T>& rhs) const
    {
        if (rhs.size_ != size_)
            return true;
        
        T* buffer = GetBuffer();
        T* rhsBuffer = rhs.GetBuffer();
        for (unsigned i = 0; i < size_; ++i)
        {
            if (buffer[i] != rhsBuffer[i])
                return true;
        }
        
        return false;
    }
    
    /// Return element at index
    T& operator [] (unsigned index) { return GetBuffer()[index]; }
    /// Return const element at index
    const T& operator [] (unsigned index) const { return GetBuffer()[index]; }
    /// Return element at index
    T& At(unsigned index) { return GetBuffer()[index]; }
    /// Return const element at index
    const T& At(unsigned index) const { return GetBuffer()[index]; }

    /// Add an element at the end
    void Push(const T& value)
    {
        Resize(size_ + 1, &value);
    }
    
    /// Add another vector at the end
    void Push(const Vector<T>& vector)
    {
        Resize(size_ + vector.size_, vector.GetBuffer());
    }
    
    /// Remove the last element
    void Pop()
    {
        if (size_)
            Resize(size_ - 1, 0);
    }
    
    /// Insert an element at position
    void Insert(unsigned pos, const T& value)
    {
        if (pos > size_)
            pos = size_;
        
        unsigned oldSize = size_;
        Resize(size_ + 1, 0);
        MoveRange(pos + 1, pos, oldSize - pos);
        GetBuffer()[pos] = value;
    }
    
    /// Insert another vector at position
    void Insert(unsigned pos, const Vector<T>& vector)
    {
        if (pos > size_)
            pos = size_;
        
        unsigned oldSize = size_;
        Resize(size_ + vector.size_, 0);
        MoveRange(pos + vector.size_, pos, oldSize - pos);
        CopyElements(GetBuffer() + pos, vector.GetBuffer(), vector.size_);
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
        Resize(size_ + length, 0);
        MoveRange(pos + length, pos, size_ - pos - length);
        
        T* destPtr = GetBuffer() + pos;
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
        Resize(size_ - length, 0);
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
        Resize(newSize, 0);
    }
    
    /// Set new capacity
    void Reserve(unsigned newCapacity)
    {
        if (newCapacity < size_)
            newCapacity = size_;
        
        if (newCapacity != capacity_)
        {
            T* newBuffer = 0;
            capacity_ = newCapacity;
            
            if (capacity_)
            {
                newBuffer = reinterpret_cast<T*>(new unsigned char[capacity_ * sizeof(T)]);
                // Move the data into the new buffer
                ConstructElements(newBuffer, GetBuffer(), size_);
            }
            
            // Delete the old buffer
            DestructElements(GetBuffer(), size_);
            delete[] buffer_;
            buffer_ = reinterpret_cast<unsigned char*>(newBuffer);
        }
    }
    
    /// Reallocate so that no extra memory is used
    void Compact()
    {
        Reserve(size_);
    }
    
    /// Return iterator to the beginning
    Iterator Begin() { return Iterator(GetBuffer()); }
    /// Return const iterator to the beginning
    ConstIterator Begin() const { return ConstIterator(GetBuffer()); }
    /// Return iterator to the end
    Iterator End() { return Iterator(GetBuffer() + size_); }
    /// Return const iterator to the end
    ConstIterator End() const { return ConstIterator(GetBuffer() + size_); }
    /// Return first element
    T& Front() { return GetBuffer()[0]; }
    /// Return const first element
    const T& Front() const { return GetBuffer()[0]; }
    /// Return last element
    T& Back() { return GetBuffer()[size_ - 1]; }
    /// Return const last element
    const T& Back() const { return GetBuffer()[size_ - 1]; }
    /// Return size of vector
    unsigned Size() const { return size_; }
    /// Return capacity of vector
    unsigned Capacity() const { return capacity_; }
    /// Return whether vector is empty
    bool Empty() const { return size_ == 0; }

    
private:
    /// Return the buffer with right type
    T* GetBuffer() const { return reinterpret_cast<T*>(buffer_); }
    
   /// Resize the vector and create/remove new elements as necessary
    void Resize(unsigned newSize, const T* src)
    {
        // If size shrinks, destruct the removed elements
        if (newSize < size_)
            DestructElements(GetBuffer() + newSize, size_ - newSize);
        else
        {
            // Allocate new buffer if necessary and copy the current elements
            if (newSize > capacity_)
            {
                if (!capacity_)
                    capacity_ = newSize;
                else
                {
                    while (capacity_ < newSize)
                        capacity_ += (capacity_ + 1) >> 1;
                }
                
                unsigned char* newBuffer = new unsigned char[capacity_ * sizeof(T)];
                if (buffer_)
                {
                    ConstructElements(reinterpret_cast<T*>(newBuffer), GetBuffer(), size_);
                    DestructElements(GetBuffer(), size_);
                    delete[] buffer_;
                }
                buffer_ = newBuffer;
            }
            
            // Initialize the new elements
            ConstructElements(GetBuffer() + size_, src, newSize - size_);
        }
        
        size_ = newSize;
    }
    
    /// Move a range of elements within the vector
    void MoveRange(unsigned dest, unsigned src, unsigned count)
    {
        T* buffer = GetBuffer();
        if (src < dest)
        {
            for (unsigned i = count - 1; i < count; --i)
                buffer[dest + i] = buffer[src + i];
        }
        if (src > dest)
        {
            for (unsigned i = 0; i < count; ++i)
                buffer[dest + i] = buffer[src + i];
        }
    }
    
    /// Construct elements, optionally with source data
    static void ConstructElements(T* dest, const T* src, unsigned count)
    {
        if (!src)
        {
            for (unsigned i = 0; i < count; ++i)
                new(dest + i) T();
        }
        else
        {
            for (unsigned i = 0; i < count; ++i)
                new(dest + i) T(*(src + i));
        }
    }
    
    /// Copy elements from one buffer to another
    static void CopyElements(T* dest, const T* src, unsigned count)
    {
        for (unsigned i = 0; i < count; ++i)
            dest[i] = src[i];
    }
    
    // Call the elements' destructors
    static void DestructElements(T* dest, unsigned count)
    {
        for (unsigned i = 0; i < count; ++i)
            (dest + i)->~T();
    }
};
