// Copyright (c) 2008-2023 the Urho3D project
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

namespace Urho3D
{

/// No index.
inline constexpr i32 NINDEX = -1;

/// End position.
inline constexpr i32 ENDPOS = -1;

/// https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2022/p2593r0.html
/// @nobindtemp
template <typename...> inline constexpr bool always_false = false;

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
    explicit Vector(i32 size)
    {
        assert(size >= 0);
        Resize(size);
    }

    /// Construct with initial size and default value.
    Vector(i32 size, const T& value)
    {
        assert(size >= 0);
        Resize(size);
        for (i32 i = 0; i < size; ++i)
            At(i) = value;
    }

    /// Construct with initial data.
    Vector(const T* data, i32 size)
    {
        assert((size >= 0 && data) || (!size && !data));

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
    Vector(Vector<T>&& vector)
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
    Vector<T>& operator =(Vector<T>&& rhs)
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
        for (i32 i = 0; i < size_; ++i)
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
        for (i32 i = 0; i < size_; ++i)
        {
            if (buffer[i] != rhsBuffer[i])
                return true;
        }

        return false;
    }

    /// Return element at index.
    T& operator [](i32 index)
    {
        assert(index >= 0 && index < size_);
        return Buffer()[index];
    }

    /// Return const element at index.
    const T& operator [](i32 index) const
    {
        assert(index >= 0 && index < size_);
        return Buffer()[index];
    }

    /// Return element at index.
    T& At(i32 index)
    {
        assert(index >= 0 && index < size_);
        return Buffer()[index];
    }

    /// Return const element at index.
    const T& At(i32 index) const
    {
        assert(index >= 0 && index < size_);
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
    void Push(T&& value)
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
            i32 thisSize = size_;
            i32 vectorSize = vector.size_;
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

    /// Insert an element at position. If pos is ENDPOS, append the new value at the end.
    void Insert(i32 pos, const T& value)
    {
        assert((pos >= 0 && pos <= size_) || pos == ENDPOS);
        DoInsertElements(pos, &value, &value + 1, CopyTag{});
    }

    /// Insert an element at position. If pos is ENDPOS, append the new value at the end.
    void Insert(i32 pos, T&& value)
    {
        assert((pos >= 0 && pos <= size_) || pos == ENDPOS);

        if constexpr (std::is_trivial<T>::value && std::is_standard_layout<T>::value)
        {
            if (pos == ENDPOS)
                pos = size_;

            i32 oldSize = size_;
            Resize(size_ + 1);
            MoveRange(pos + 1, pos, oldSize - pos);
            Buffer()[pos] = value;
        }
        else
        {
            DoInsertElements(pos, &value, &value + 1, MoveTag{});
        }
    }

    /// Insert another vector at position. If pos is ENDPOS, append the new elements at the end.
    void Insert(i32 pos, const Vector<T>& vector)
    {
        assert((pos >= 0 && pos <= size_) || pos == ENDPOS);

        if constexpr (std::is_trivial<T>::value && std::is_standard_layout<T>::value)
        {
            if (pos == ENDPOS)
                pos = size_;

            i32 oldSize = size_;
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
            i32 pos = (i32)(dest - Begin());
            assert(pos >= 0 && pos <= size_);
            Insert(pos, value);

            return Begin() + pos;
        }
        else
        {
            i32 pos = (i32)(dest - Begin());
            assert(pos >= 0 && pos <= size_);
            return DoInsertElements(pos, &value, &value + 1, CopyTag{});
        }
    }

    /// Move-insert an element by iterator.
    Iterator Insert(const Iterator& dest, T&& value)
    {
        i32 pos = (i32)(dest - Begin());
        assert(pos >= 0 && pos <= size_);
        return DoInsertElements(pos, &value, &value + 1, MoveTag{});
    }

    /// Insert a vector by iterator.
    Iterator Insert(const Iterator& dest, const Vector<T>& vector)
    {
        if constexpr (std::is_trivial<T>::value && std::is_standard_layout<T>::value)
        {
            i32 pos = (i32)(dest - Begin());
            assert(pos >= 0 && pos <= size_);
            Insert(pos, vector);

            return Begin() + pos;
        }
        else
        {
            i32 pos = (i32)(dest - Begin());
            assert(pos >= 0 && pos <= size_);
            return DoInsertElements(pos, vector.Begin(), vector.End(), CopyTag{});
        }
    }

    /// Insert a vector partially by iterators.
    Iterator Insert(const Iterator& dest, const ConstIterator& start, const ConstIterator& end)
    {
        if constexpr (std::is_trivial<T>::value && std::is_standard_layout<T>::value)
        {
            i32 pos = (i32)(dest - Begin());
            assert(pos >= 0 && pos <= size_);
            i32 length = (i32)(end - start);
            Resize(size_ + length);
            MoveRange(pos + length, pos, size_ - pos - length);
            CopyElements(Buffer() + pos, &(*start), length);

            return Begin() + pos;
        }
        else
        {
            i32 pos = (i32)(dest - Begin());
            assert(pos >= 0 && pos <= size_);
            return DoInsertElements(pos, start, end, CopyTag{});
        }
    }

    /// Insert elements.
    Iterator Insert(const Iterator& dest, const T* start, const T* end)
    {
        if constexpr (std::is_trivial<T>::value && std::is_standard_layout<T>::value)
        {
            i32 pos = (i32)(dest - Begin());
            assert(pos >= 0 && pos <= size_);
            i32 length = (i32)(end - start);
            Resize(size_ + length);
            MoveRange(pos + length, pos, size_ - pos - length);

            T* destPtr = Buffer() + pos;
            for (const T* i = start; i != end; ++i)
                *destPtr++ = *i;

            return Begin() + pos;
        }
        else
        {
            i32 pos = (i32)(dest - Begin());
            assert(pos >= 0 && pos <= size_);
            return DoInsertElements(pos, start, end, CopyTag{});
        }
    }

    /// Erase a range of elements.
    void Erase(i32 pos, i32 length = 1)
    {
        assert(pos >= 0 && length >= 0 && pos + length <= size_);

        if (!length)
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
    void EraseSwap(i32 pos, i32 length = 1)
    {
        assert(pos >= 0 && length >= 1 && pos + length <= size_);

        i32 shiftStartIndex = pos + length;
        i32 newSize = size_ - length;
        i32 trailingCount = size_ - shiftStartIndex;

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
        i32 pos = (i32)(it - Begin());
        assert(pos >= 0 && pos <= size_);

        if (pos == size_)
            return End();

        Erase(pos);

        return Begin() + pos;
    }

    /// Erase a range by iterators. Return iterator to the next element.
    Iterator Erase(const Iterator& start, const Iterator& end)
    {
        i32 pos = (i32)(start - Begin());
        assert(pos >= 0 && pos <= size_);

        if (pos == size_)
            return End();

        i32 length = (i32)(end - start);
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
    void Resize(i32 newSize)
    {
        assert(newSize >= 0);

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

                u8* newBuffer = AllocateBuffer((i32)(capacity_ * sizeof(T)));
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
    void Resize(i32 newSize, const T& value)
    {
        assert(newSize >= 0);
        i32 oldSize = Size();
        Resize(newSize);
        for (i32 i = oldSize; i < newSize; ++i)
            At(i) = value;
    }

    /// Set new capacity.
    void Reserve(i32 newCapacity)
    {
        assert(newCapacity >= 0);

        if (newCapacity < size_)
            newCapacity = size_;

        if constexpr (std::is_trivial<T>::value && std::is_standard_layout<T>::value)
        {
            if (newCapacity != capacity_)
            {
                u8* newBuffer = nullptr;
                capacity_ = newCapacity;

                if (capacity_)
                {
                    newBuffer = AllocateBuffer((i32)(capacity_ * sizeof(T)));
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
                    newBuffer = reinterpret_cast<T*>(AllocateBuffer((i32)(capacity_ * sizeof(T))));
                    // Move the data into the new buffer
                    ConstructElements(newBuffer, Begin(), End(), MoveTag{});
                }

                // Delete the old buffer
                DestructElements(Buffer(), size_);
                delete[] buffer_;
                buffer_ = reinterpret_cast<u8*>(newBuffer);
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
    i32 IndexOf(const T& value) const
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
    i32 Size() const { return size_; }

    /// Return capacity of vector.
    i32 Capacity() const { return capacity_; }

    /// Return whether vector is empty.
    bool Empty() const { return size_ == 0; }

    /// Return the buffer with right type.
    T* Buffer() const { return reinterpret_cast<T*>(buffer_); }

private:
    /// Construct elements using default ctor.
    static void ConstructElements(T* dest, i32 count)
    {
        assert(count >= 0);
        for (i32 i = 0; i < count; ++i)
            new(dest + i) T();
    }

    /// Copy-construct elements.
    template <class RandomIteratorT>
    static void ConstructElements(T* dest, RandomIteratorT start, RandomIteratorT end, CopyTag)
    {
        const i32 count = (i32)(end - start);
        assert(count > 0);
        for (i32 i = 0; i < count; ++i)
            new(dest + i) T(*(start + i));
    }

    /// Move-construct elements.
    template <class RandomIteratorT>
    static void ConstructElements(T* dest, RandomIteratorT start, RandomIteratorT end, MoveTag)
    {
        const i32 count = (i32)(end - start);
        assert(count >= 0);
        for (i32 i = 0; i < count; ++i)
            new(dest + i) T(std::move(*(start + i)));
    }

    /// Calculate new vector capacity.
    static i32 CalculateCapacity(i32 size, i32 capacity)
    {
        assert(size > 0 && capacity >= 0);

        if (!capacity)
        {
            return size;
        }
        else
        {
            while (capacity < size)
                capacity += (capacity + 1) >> 1; // += (capacity * 0.5 and round up)
            return capacity;
        }
    }

    /// Resize the vector and create/remove new elements as necessary.
    void DoResize(i32 newSize)
    {
        assert(newSize >= 0);

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
    /// If pos is ENDPOS, append the new elements at the end.
    template <class Tag, class RandomIteratorT>
    Iterator DoInsertElements(i32 pos, RandomIteratorT start, RandomIteratorT end, Tag)
    {
        assert((pos >= 0 && pos <= size_) || pos == ENDPOS);

        if (pos == ENDPOS)
            pos = size_;

        const i32 numElements = (i32)(end - start);
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
    Iterator DoEraseElements(i32 pos, i32 count)
    {
        assert(pos >= 0 && count > 0 && pos + count <= size_);
        T* buffer = Buffer();
        std::move(buffer + pos + count, buffer + size_, buffer + pos);
        Resize(size_ - count);
        return Begin() + pos;
    }

    /// Call the elements' destructors.
    static void DestructElements(T* dest, i32 count)
    {
        assert(count >= 0);

        while (count--)
        {
            dest->~T();
            ++dest;
        }
    }

    /// Move a range of elements within the vector. Only for POD Vector.
    void MoveRange(i32 dest, i32 src, i32 count)
    {
        assert(dest >= 0 && src >= 0 && count >= 0);

        if constexpr (std::is_trivial<T>::value && std::is_standard_layout<T>::value)
        {
            if (count)
                memmove(Buffer() + dest, Buffer() + src, count * sizeof(T));
        }
        else
        {
            // https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2022/p2593r0.html
            static_assert(always_false<T>); // static_assert(false);
        }
    }

    /// Copy elements from one buffer to another. Only for POD Vector.
    static void CopyElements(T* dest, const T* src, i32 count)
    {
        assert(count >= 0);

        if constexpr (std::is_trivial<T>::value && std::is_standard_layout<T>::value)
        {
            if (count)
                memcpy(dest, src, count * sizeof(T));
        }
        else
        {
            // https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2022/p2593r0.html
            static_assert(always_false<T>); // static_assert(false);
        }
    }
};

template <class T> typename Urho3D::Vector<T>::ConstIterator begin(const Urho3D::Vector<T>& v) { return v.Begin(); }

template <class T> typename Urho3D::Vector<T>::ConstIterator end(const Urho3D::Vector<T>& v) { return v.End(); }

template <class T> typename Urho3D::Vector<T>::Iterator begin(Urho3D::Vector<T>& v) { return v.Begin(); }

template <class T> typename Urho3D::Vector<T>::Iterator end(Urho3D::Vector<T>& v) { return v.End(); }

}
