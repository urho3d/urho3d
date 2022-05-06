// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include "../Container/VectorBase.h"

#include <algorithm>
#include <cassert>
#include <cstring>
#include <initializer_list>
#include <new>
#include <type_traits>
#include <utility>

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:6293)
#endif

namespace Urho3D
{

/// %Vector template class.
template <class T> class Vector : public VectorBase
{
    struct CopyTag {};
    struct MoveTag {};

public:
    using ValueType = T;
    using Iterator = RandomAccessIterator<T>;
    using ConstIterator = RandomAccessConstIterator<T>;

    /// Construct empty.
    Vector() noexcept = default;

    /// Construct with initial size.
    explicit Vector(unsigned size)
    {
        Resize(size);
    }

    /// Construct with initial size and default value.
    Vector(unsigned size, const T& value)
    {
        Resize(size);
        for (unsigned i = 0; i < size; ++i)
            At(i) = value;
    }

    /// Construct with initial data.
    Vector(const T* data, unsigned size)
    {
        if constexpr (std::is_trivial<T>::value && std::is_standard_layout<T>::value)
        {
            Resize(size);
            CopyElements(Buffer(), data, size);
        }
        else
        {
            DoInsertElements(0, data, data + size, CopyTag{});
        }
    }

    /// Copy-construct from another vector.
    Vector(const Vector<T>& vector)
    {
        if constexpr (std::is_trivial<T>::value && std::is_standard_layout<T>::value)
            *this = vector;
        else
            DoInsertElements(0, vector.Begin(), vector.End(), CopyTag{});
    }

    /// Copy-construct from another vector (iterator version).
    Vector(ConstIterator start, ConstIterator end)
    {
        DoInsertElements(0, start, end, CopyTag{});
    }

    /// Move-construct from another vector.
    Vector(Vector<T> && vector)
    {
        Swap(vector);
    }

    /// Aggregate initialization constructor.
    Vector(const std::initializer_list<T>& list) : Vector()
    {
        for (auto it = list.begin(); it != list.end(); it++)
        {
            Push(*it);
        }
    }

    /// Destruct.
    ~Vector()
    {
        if constexpr (!std::is_trivial<T>::value)
            DestructElements(Buffer(), size_);

        delete[] buffer_;
    }

    /// Assign from another vector.
    Vector<T>& operator =(const Vector<T>& rhs)
    {
        // In case of self-assignment do nothing
        if (&rhs != this)
        {
            if constexpr (std::is_trivial<T>::value && std::is_standard_layout<T>::value)
            {
                Resize(rhs.size_);
                CopyElements(Buffer(), rhs.Buffer(), rhs.size_);
            }
            else
            {
                Vector<T> copy(rhs);
                Swap(copy);
            }
        }

        return *this;
    }

    /// Move-assign from another vector.
    Vector<T>& operator =(Vector<T> && rhs)
    {
        Swap(rhs);
        return *this;
    }

    /// Add-assign an element.
    Vector<T>& operator +=(const T& rhs)
    {
        Push(rhs);
        return *this;
    }

    /// Add-assign another vector.
    Vector<T>& operator +=(const Vector<T>& rhs)
    {
        Push(rhs);
        return *this;
    }

    /// Add an element.
    Vector<T> operator +(const T& rhs) const
    {
        Vector<T> ret(*this);
        ret.Push(rhs);
        return ret;
    }

    /// Add another vector.
    Vector<T> operator +(const Vector<T>& rhs) const
    {
        Vector<T> ret(*this);
        ret.Push(rhs);
        return ret;
    }

    /// Test for equality with another vector.
    bool operator ==(const Vector<T>& rhs) const
    {
        if (rhs.size_ != size_)
            return false;

        T* buffer = Buffer();
        T* rhsBuffer = rhs.Buffer();
        for (unsigned i = 0; i < size_; ++i)
        {
            if (buffer[i] != rhsBuffer[i])
                return false;
        }

        return true;
    }

    /// Test for inequality with another vector.
    bool operator !=(const Vector<T>& rhs) const
    {
        if (rhs.size_ != size_)
            return true;

        T* buffer = Buffer();
        T* rhsBuffer = rhs.Buffer();
        for (unsigned i = 0; i < size_; ++i)
        {
            if (buffer[i] != rhsBuffer[i])
                return true;
        }

        return false;
    }

    /// Return element at index.
    T& operator [](unsigned index)
    {
        assert(index < size_);
        return Buffer()[index];
    }

    /// Return const element at index.
    const T& operator [](unsigned index) const
    {
        assert(index < size_);
        return Buffer()[index];
    }

    /// Return element at index.
    T& At(unsigned index)
    {
        assert(index < size_);
        return Buffer()[index];
    }

    /// Return const element at index.
    const T& At(unsigned index) const
    {
        assert(index < size_);
        return Buffer()[index];
    }

    /// Create an element at the end.
    template <class... Args> T& EmplaceBack(Args&&... args)
    {
        if (size_ < capacity_)
        {
            // Optimize common case
            ++size_;
            new (&Back()) T(std::forward<Args>(args)...);
        }
        else
        {
            T value(std::forward<Args>(args)...);
            Push(std::move(value));
        }
        return Back();
    }

    /// Add an element at the end.
#ifndef COVERITY_SCAN_MODEL
    void Push(const T& value)
    {
        if constexpr (std::is_trivial<T>::value && std::is_standard_layout<T>::value)
        {
            if (size_ < capacity_)
                ++size_;
            else
                Resize(size_ + 1);
            
            Back() = value;
        }
        else
        {
            if (size_ < capacity_)
            {
                // Optimize common case
                ++size_;
                new (&Back()) T(value);
            }
            else
            {
                DoInsertElements(size_, &value, &value + 1, CopyTag{});
            }
        }
    }

    /// Move-add an element at the end.
    void Push(T && value)
    {
        if (size_ < capacity_)
        {
            // Optimize common case
            ++size_;
            new (&Back()) T(std::move(value));
        }
        else
            DoInsertElements(size_, &value, &value + 1, MoveTag{});
    }
#else
    // FIXME: Attempt had been made to use this model in the Coverity-Scan model file without any success
    // Probably because the model had generated a different mangled name than the one used by static analyzer
    void Push(const T& value)
    {
        T array[] = {value};
        DoInsertElements(size_, array, array + 1, CopyTag{});
    }
#endif

    /// Add another vector at the end.
    void Push(const Vector<T>& vector)
    {
        if constexpr (std::is_trivial<T>::value && std::is_standard_layout<T>::value)
        {
            // Obtain the size before resizing, in case the other vector is another reference to this vector
            unsigned thisSize = size_;
            unsigned vectorSize = vector.size_;
            Resize(thisSize + vectorSize);
            CopyElements(Buffer() + thisSize, vector.Buffer(), vectorSize);
        }
        else
        {
            DoInsertElements(size_, vector.Begin(), vector.End(), CopyTag{});
        }
    }

    /// Remove the last element.
    void Pop()
    {
        if (size_)
            Resize(size_ - 1);
    }

    /// Insert an element at position.
    void Insert(unsigned pos, const T& value)
    {
        DoInsertElements(pos, &value, &value + 1, CopyTag{});
    }

    /// Insert an element at position.
    void Insert(unsigned pos, T && value)
    {
        if constexpr (std::is_trivial<T>::value && std::is_standard_layout<T>::value)
        {
            if (pos > size_)
                pos = size_;

            unsigned oldSize = size_;
            Resize(size_ + 1);
            MoveRange(pos + 1, pos, oldSize - pos);
            Buffer()[pos] = value;
        }
        else
        {
            DoInsertElements(pos, &value, &value + 1, MoveTag{});
        }
    }

    /// Insert another vector at position.
    void Insert(unsigned pos, const Vector<T>& vector)
    {
        if constexpr (std::is_trivial<T>::value && std::is_standard_layout<T>::value)
        {
            if (pos > size_)
                pos = size_;

            unsigned oldSize = size_;
            Resize(size_ + vector.size_);
            MoveRange(pos + vector.size_, pos, oldSize - pos);
            CopyElements(Buffer() + pos, vector.Buffer(), vector.size_);
        }
        else
        {
            DoInsertElements(pos, vector.Begin(), vector.End(), CopyTag{});
        }
    }

    /// Insert an element by iterator.
    Iterator Insert(const Iterator& dest, const T& value)
    {
        if constexpr (std::is_trivial<T>::value && std::is_standard_layout<T>::value)
        {
            auto pos = (unsigned)(dest - Begin());
            if (pos > size_)
                pos = size_;
            Insert(pos, value);

            return Begin() + pos;
        }
        else
        {
            auto pos = (unsigned)(dest - Begin());
            return DoInsertElements(pos, &value, &value + 1, CopyTag{});
        }
    }

    /// Move-insert an element by iterator.
    Iterator Insert(const Iterator& dest, T && value)
    {
        auto pos = (unsigned)(dest - Begin());
        return DoInsertElements(pos, &value, &value + 1, MoveTag{});
    }

    /// Insert a vector by iterator.
    Iterator Insert(const Iterator& dest, const Vector<T>& vector)
    {
        if constexpr (std::is_trivial<T>::value && std::is_standard_layout<T>::value)
        {
            auto pos = (unsigned)(dest - Begin());
            if (pos > size_)
                pos = size_;
            Insert(pos, vector);

            return Begin() + pos;
        }
        else
        {
            auto pos = (unsigned)(dest - Begin());
            return DoInsertElements(pos, vector.Begin(), vector.End(), CopyTag{});
        }
    }

    /// Insert a vector partially by iterators.
    Iterator Insert(const Iterator& dest, const ConstIterator& start, const ConstIterator& end)
    {
        if constexpr (std::is_trivial<T>::value && std::is_standard_layout<T>::value)
        {
            auto pos = (unsigned)(dest - Begin());
            if (pos > size_)
                pos = size_;
            auto length = (unsigned)(end - start);
            Resize(size_ + length);
            MoveRange(pos + length, pos, size_ - pos - length);
            CopyElements(Buffer() + pos, &(*start), length);

            return Begin() + pos;
        }
        else
        {
            auto pos = (unsigned)(dest - Begin());
            return DoInsertElements(pos, start, end, CopyTag{});
        }
    }

    /// Insert elements.
    Iterator Insert(const Iterator& dest, const T* start, const T* end)
    {
        if constexpr (std::is_trivial<T>::value && std::is_standard_layout<T>::value)
        {
            auto pos = (unsigned)(dest - Begin());
            if (pos > size_)
                pos = size_;
            auto length = (unsigned)(end - start);
            Resize(size_ + length);
            MoveRange(pos + length, pos, size_ - pos - length);

            T* destPtr = Buffer() + pos;
            for (const T* i = start; i != end; ++i)
                *destPtr++ = *i;

            return Begin() + pos;
        }
        else
        {
            auto pos = (unsigned)(dest - Begin());
            return DoInsertElements(pos, start, end, CopyTag{});
        }
    }

    /// Erase a range of elements.
    void Erase(unsigned pos, unsigned length = 1)
    {
        // Return if the range is illegal
        if (pos + length > size_ || !length)
            return;

        if constexpr (std::is_trivial<T>::value && std::is_standard_layout<T>::value)
        {
            MoveRange(pos, pos + length, size_ - pos - length);
            Resize(size_ - length);
        }
        else
        {
            DoEraseElements(pos, length);
        }
    }

    /// Erase a range of elements by swapping elements from the end of the array.
    void EraseSwap(unsigned pos, unsigned length = 1)
    {
        unsigned shiftStartIndex = pos + length;
        // Return if the range is illegal
        if (shiftStartIndex > size_ || !length)
            return;

        unsigned newSize = size_ - length;
        unsigned trailingCount = size_ - shiftStartIndex;

        if constexpr (std::is_trivial<T>::value && std::is_standard_layout<T>::value)
        {
            if (trailingCount <= length)
            {
                // We're removing more elements from the array than exist past the end of the range being removed, so perform a normal shift and destroy
                MoveRange(pos, shiftStartIndex, trailingCount);
            }
            else
            {
                // Swap elements from the end of the array into the empty space
                CopyElements(Buffer() + pos, Buffer() + newSize, length);
            }
            Resize(newSize);
        }
        else
        {
            if (trailingCount <= length)
            {
                // We're removing more elements from the array than exist past the end of the range being removed, so perform a normal shift and destroy
                DoEraseElements(pos, length);
            }
            else
            {
                // Swap elements from the end of the array into the empty space
                T* buffer = Buffer();
                std::move(buffer + newSize, buffer + size_, buffer + pos);
                Resize(newSize);
            }
        }
    }

    /// Erase an element by iterator. Return iterator to the next element.
    Iterator Erase(const Iterator& it)
    {
        auto pos = (unsigned)(it - Begin());
        if (pos >= size_)
            return End();
        Erase(pos);

        return Begin() + pos;
    }

    /// Erase a range by iterators. Return iterator to the next element.
    Iterator Erase(const Iterator& start, const Iterator& end)
    {
        auto pos = (unsigned)(start - Begin());
        if (pos >= size_)
            return End();
        auto length = (unsigned)(end - start);
        Erase(pos, length);

        return Begin() + pos;
    }

    /// Erase an element by value. Return true if was found and erased.
    bool Remove(const T& value)
    {
        Iterator i = Find(value);
        if (i != End())
        {
            Erase(i);
            return true;
        }
        else
        {
            return false;
        }
    }

    /// Erase an element by value by swapping with the last element. Return true if was found and erased.
    bool RemoveSwap(const T& value)
    {
        Iterator i = Find(value);
        if (i != End())
        {
            EraseSwap(i - Begin());
            return true;
        }
        else
        {
            return false;
        }
    }

    /// Clear the vector.
    void Clear() { Resize(0); }

    /// Resize the vector.
    void Resize(unsigned newSize)
    {
        if constexpr (std::is_trivial<T>::value && std::is_standard_layout<T>::value)
        {
            if (newSize > capacity_)
            {
                if (!capacity_)
                    capacity_ = newSize;
                else
                {
                    while (capacity_ < newSize)
                        capacity_ += (capacity_ + 1) >> 1;
                }

                unsigned char* newBuffer = AllocateBuffer((unsigned)(capacity_ * sizeof(T)));
                // Move the data into the new buffer and delete the old
                if (buffer_)
                {
                    CopyElements(reinterpret_cast<T*>(newBuffer), Buffer(), size_);
                    delete[] buffer_;
                }
                buffer_ = newBuffer;
            }

            size_ = newSize;
        }
        else
        {
            DoResize(newSize);
        }
    }

    /// Resize the vector and fill new elements with default value.
    void Resize(unsigned newSize, const T& value)
    {
        unsigned oldSize = Size();
        Resize(newSize);
        for (unsigned i = oldSize; i < newSize; ++i)
            At(i) = value;
    }

    /// Set new capacity.
    void Reserve(unsigned newCapacity)
    {
        if (newCapacity < size_)
            newCapacity = size_;

        if constexpr (std::is_trivial<T>::value && std::is_standard_layout<T>::value)
        {
            if (newCapacity != capacity_)
            {
                unsigned char* newBuffer = nullptr;
                capacity_ = newCapacity;

                if (capacity_)
                {
                    newBuffer = AllocateBuffer((unsigned)(capacity_ * sizeof(T)));
                    // Move the data into the new buffer
                    CopyElements(reinterpret_cast<T*>(newBuffer), Buffer(), size_);
                }

                // Delete the old buffer
                delete[] buffer_;
                buffer_ = newBuffer;
            }
        }
        else
        {
            if (newCapacity != capacity_)
            {
                T* newBuffer = nullptr;
                capacity_ = newCapacity;

                if (capacity_)
                {
                    newBuffer = reinterpret_cast<T*>(AllocateBuffer((unsigned)(capacity_ * sizeof(T))));
                    // Move the data into the new buffer
                    ConstructElements(newBuffer, Begin(), End(), MoveTag{});
                }

                // Delete the old buffer
                DestructElements(Buffer(), size_);
                delete[] buffer_;
                buffer_ = reinterpret_cast<unsigned char*>(newBuffer);
            }
        }
    }

    /// Reallocate so that no extra memory is used.
    void Compact() { Reserve(size_); }

    /// Return iterator to value, or to the end if not found.
    Iterator Find(const T& value)
    {
        Iterator it = Begin();
        while (it != End() && *it != value)
            ++it;
        return it;
    }

    /// Return const iterator to value, or to the end if not found.
    ConstIterator Find(const T& value) const
    {
        ConstIterator it = Begin();
        while (it != End() && *it != value)
            ++it;
        return it;
    }

    /// Return index of value in vector, or size if not found.
    unsigned IndexOf(const T& value) const
    {
        return Find(value) - Begin();
    }

    /// Return whether contains a specific value.
    bool Contains(const T& value) const { return Find(value) != End(); }

    /// Return iterator to the beginning.
    Iterator Begin() { return Iterator(Buffer()); }

    /// Return const iterator to the beginning.
    ConstIterator Begin() const { return ConstIterator(Buffer()); }

    /// Return iterator to the end.
    Iterator End() { return Iterator(Buffer() + size_); }

    /// Return const iterator to the end.
    ConstIterator End() const { return ConstIterator(Buffer() + size_); }

    /// Return first element.
    T& Front()
    {
        assert(size_);
        return Buffer()[0];
    }

    /// Return const first element.
    const T& Front() const
    {
        assert(size_);
        return Buffer()[0];
    }

    /// Return last element.
    T& Back()
    {
        assert(size_);
        return Buffer()[size_ - 1];
    }

    /// Return const last element.
    const T& Back() const
    {
        assert(size_);
        return Buffer()[size_ - 1];
    }

    /// Return number of elements.
    unsigned Size() const { return size_; }

    /// Return capacity of vector.
    unsigned Capacity() const { return capacity_; }

    /// Return whether vector is empty.
    bool Empty() const { return size_ == 0; }

    /// Return the buffer with right type.
    T* Buffer() const { return reinterpret_cast<T*>(buffer_); }

private:
    /// Construct elements using default ctor.
    static void ConstructElements(T* dest, unsigned count)
    {
        for (unsigned i = 0; i < count; ++i)
            new(dest + i) T();
    }

    /// Copy-construct elements.
    template <class RandomIteratorT>
    static void ConstructElements(T* dest, RandomIteratorT start, RandomIteratorT end, CopyTag)
    {
        const auto count = (unsigned)(end - start);
        for (unsigned i = 0; i < count; ++i)
            new(dest + i) T(*(start + i));
    }

    /// Move-construct elements.
    template <class RandomIteratorT>
    static void ConstructElements(T* dest, RandomIteratorT start, RandomIteratorT end, MoveTag)
    {
        const auto count = (unsigned)(end - start);
        for (unsigned i = 0; i < count; ++i)
            new(dest + i) T(std::move(*(start + i)));
    }

    /// Calculate new vector capacity.
    static unsigned CalculateCapacity(unsigned size, unsigned capacity)
    {
        if (!capacity)
        {
            return size;
        }
        else
        {
            while (capacity < size)
                capacity += (capacity + 1) >> 1;
            return capacity;
        }
    }

    /// Resize the vector and create/remove new elements as necessary.
    void DoResize(unsigned newSize)
    {
        // If size shrinks, destruct the removed elements
        if (newSize < size_)
        {
            DestructElements(Buffer() + newSize, size_ - newSize);
        }
        else
        {
            // Allocate new buffer if necessary and copy the current elements
            if (newSize > capacity_)
            {
                T* src = Buffer();

                // Reallocate vector
                Vector<T> newVector;
                newVector.Reserve(CalculateCapacity(newSize, capacity_));
                newVector.size_ = size_;
                T* dest = newVector.Buffer();

                // Move old elements
                ConstructElements(dest, src, src + size_, MoveTag{});

                Swap(newVector);
            }

            // Initialize the new elements
            ConstructElements(Buffer() + size_, newSize - size_);
        }

        size_ = newSize;
    }

    /// Insert elements into the vector using copy or move constructor.
    template <class Tag, class RandomIteratorT>
    Iterator DoInsertElements(unsigned pos, RandomIteratorT start, RandomIteratorT end, Tag)
    {
        if (pos > size_)
            pos = size_;

        const auto numElements = (unsigned)(end - start);
        if (size_ + numElements > capacity_)
        {
            T* src = Buffer();

            // Reallocate vector
            Vector<T> newVector;
            newVector.Reserve(CalculateCapacity(size_ + numElements, capacity_));
            newVector.size_ = size_ + numElements;
            T* dest = newVector.Buffer();

            // Copy or move new elements
            ConstructElements(dest + pos, start, end, Tag{});

            // Move old elements
            if (pos > 0)
                ConstructElements(dest, src, src + pos, MoveTag{});
            if (pos < size_)
                ConstructElements(dest + pos + numElements, src + pos, src + size_, MoveTag{});

            Swap(newVector);
        }
        else if (numElements > 0)
        {
            T* buffer = Buffer();

            // Copy or move new elements
            ConstructElements(buffer + size_, start, end, Tag{});

            // Rotate buffer
            if (pos < size_)
            {
                std::rotate(buffer + pos, buffer + size_, buffer + size_ + numElements);
            }

            // Update size
            size_ += numElements;
        }

        return Begin() + pos;
    }

    /// Erase elements from the vector.
    Iterator DoEraseElements(unsigned pos, unsigned count)
    {
        assert(count > 0);
        assert(pos + count <= size_);
        T* buffer = Buffer();
        std::move(buffer + pos + count, buffer + size_, buffer + pos);
        Resize(size_ - count);
        return Begin() + pos;
    }

    /// Call the elements' destructors.
    static void DestructElements(T* dest, unsigned count)
    {
        while (count--)
        {
            dest->~T();
            ++dest;
        }
    }

    /// Move a range of elements within the vector. Only for PODVector.
    void MoveRange(unsigned dest, unsigned src, unsigned count)
    {
        if constexpr (std::is_trivial<T>::value && std::is_standard_layout<T>::value)
        {
            if (count)
                memmove(Buffer() + dest, Buffer() + src, count * sizeof(T));
        }
        else
        {
            static_assert(true);
        }
    }

    /// Copy elements from one buffer to another. Only for PODVector.
    static void CopyElements(T* dest, const T* src, unsigned count)
    {
        if constexpr (std::is_trivial<T>::value && std::is_standard_layout<T>::value)
        {
            if (count)
                memcpy(dest, src, count * sizeof(T));
        }
        else
        {
            static_assert(true);
        }
    }
};

/// For backwards compatibility.
template <typename T>
using PODVector = Vector<T>;

template <class T> typename Urho3D::Vector<T>::ConstIterator begin(const Urho3D::Vector<T>& v) { return v.Begin(); }

template <class T> typename Urho3D::Vector<T>::ConstIterator end(const Urho3D::Vector<T>& v) { return v.End(); }

template <class T> typename Urho3D::Vector<T>::Iterator begin(Urho3D::Vector<T>& v) { return v.Begin(); }

template <class T> typename Urho3D::Vector<T>::Iterator end(Urho3D::Vector<T>& v) { return v.End(); }

}

#ifdef _MSC_VER
#pragma warning(pop)
#endif
