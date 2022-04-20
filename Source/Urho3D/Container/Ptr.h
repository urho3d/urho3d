//
// Copyright (c) 2008-2022 the Urho3D project.
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

#include "../Container/RefCounted.h"
#include "../Container/Swap.h"

#include <cassert>
#include <cmath>
#include <cstddef>
#include <utility>

namespace Urho3D
{

/// Shared pointer template class with intrusive reference counting.
template <class T> class SharedPtr
{
public:
    /// Construct a null shared pointer.
    SharedPtr() noexcept :
        ptr_(nullptr)
    {
    }

    /// Construct a null shared pointer.
    SharedPtr(std::nullptr_t) noexcept :     // NOLINT(google-explicit-constructor)
        ptr_(nullptr)
    {
    }

    /// Copy-construct from another shared pointer.
    SharedPtr(const SharedPtr<T>& rhs) noexcept :
        ptr_(rhs.ptr_)
    {
        AddRef();
    }

    /// Move-construct from another shared pointer.
    SharedPtr(SharedPtr<T>&& rhs) noexcept :
        ptr_(rhs.ptr_)
    {
        rhs.ptr_ = nullptr;
    }

    /// Copy-construct from another shared pointer allowing implicit upcasting.
    template <class U> SharedPtr(const SharedPtr<U>& rhs) noexcept :    // NOLINT(google-explicit-constructor)
        ptr_(rhs.ptr_)
    {
        AddRef();
    }

    /// Construct from a raw pointer.
    explicit SharedPtr(T* ptr) noexcept :
        ptr_(ptr)
    {
        AddRef();
    }

    /// Destruct. Release the object reference.
    ~SharedPtr() noexcept
    {
        ReleaseRef();
    }

    /// Assign from another shared pointer.
    SharedPtr<T>& operator =(const SharedPtr<T>& rhs)
    {
        if (ptr_ == rhs.ptr_)
            return *this;

        SharedPtr<T> copy(rhs);
        Swap(copy);

        return *this;
    }

    /// Move-assign from another shared pointer.
    SharedPtr<T>& operator =(SharedPtr<T>&& rhs)
    {
        SharedPtr<T> copy(std::move(rhs));
        Swap(copy);

        return *this;
    }

    /// Assign from another shared pointer allowing implicit upcasting.
    template <class U> SharedPtr<T>& operator =(const SharedPtr<U>& rhs)
    {
        if (ptr_ == rhs.ptr_)
            return *this;

        SharedPtr<T> copy(rhs);
        Swap(copy);

        return *this;
    }

    /// Assign from a raw pointer.
    SharedPtr<T>& operator =(T* ptr)
    {
        if (ptr_ == ptr)
            return *this;

        SharedPtr<T> copy(ptr);
        Swap(copy);

        return *this;
    }

    /// Point to the object.
    T* operator ->() const
    {
        assert(ptr_);
        return ptr_;
    }

    /// Dereference the object.
    T& operator *() const
    {
        assert(ptr_);
        return *ptr_;
    }

    /// Subscript the object if applicable.
    T& operator [](int index)
    {
        assert(ptr_);
        return ptr_[index];
    }

    /// Test for less than with another shared pointer.
    template <class U> bool operator <(const SharedPtr<U>& rhs) const { return ptr_ < rhs.ptr_; }

    /// Test for equality with another shared pointer.
    template <class U> bool operator ==(const SharedPtr<U>& rhs) const { return ptr_ == rhs.ptr_; }

    /// Test for inequality with another shared pointer.
    template <class U> bool operator !=(const SharedPtr<U>& rhs) const { return ptr_ != rhs.ptr_; }

    /// Convert to a raw pointer.
    operator T*() const { return ptr_; }    // NOLINT(google-explicit-constructor)

    /// Swap with another SharedPtr.
    void Swap(SharedPtr<T>& rhs) { Urho3D::Swap(ptr_, rhs.ptr_); }

    /// Reset with another pointer.
    void Reset(T* ptr = nullptr)
    {
        SharedPtr<T> copy(ptr);
        Swap(copy);
    }

    /// Detach without destroying the object even if the refcount goes zero. To be used for scripting language interoperation.
    T* Detach()
    {
        T* ptr = ptr_;
        
        if (ptr)
        {
            ptr->SetRefs(ptr->Refs() + 1); // 2 refs
            Reset(); // 1 ref
            ptr->SetRefs(ptr->Refs() - 1); // 0 refs
        }
        
        return ptr;
    }

    /// Perform a static cast from a shared pointer of another type.
    template <class U> void StaticCast(const SharedPtr<U>& rhs)
    {
        SharedPtr<T> copy(static_cast<T*>(rhs.Get()));
        Swap(copy);
    }

    /// Perform a dynamic cast from a shared pointer of another type.
    template <class U> void DynamicCast(const SharedPtr<U>& rhs)
    {
        SharedPtr<T> copy(dynamic_cast<T*>(rhs.Get()));
        Swap(copy);
    }

    /// Check if the pointer is null.
    bool Null() const { return ptr_ == 0; }

    /// Check if the pointer is not null.
    bool NotNull() const { return ptr_ != nullptr; }

    /// Return the raw pointer.
    T* Get() const { return ptr_; }

    /// Return the object's reference count, or 0 if the pointer is null.
    int Refs() const { return ptr_ ? ptr_->Refs() : 0; }

    /// Return the object's weak reference count, or 0 if the pointer is null.
    int WeakRefs() const { return ptr_ ? ptr_->WeakRefs() : 0; }

    /// Return hash value for HashSet & HashMap.
    unsigned ToHash() const { return (unsigned)((size_t)ptr_ / sizeof(T)); }

private:
    template <class U> friend class SharedPtr;

    /// Add a reference to the object pointed to.
    void AddRef()
    {
        if (ptr_)
            ptr_->AddRef();
    }

    /// Release the object reference and delete it if necessary.
    void ReleaseRef()
    {
        if (ptr_)
        {
            ptr_->ReleaseRef();
            ptr_ = nullptr;
        }
    }

    /// Pointer to the object.
    T* ptr_;
};

/// Perform a static cast from one shared pointer type to another.
template <class T, class U> SharedPtr<T> StaticCast(const SharedPtr<U>& ptr)
{
    SharedPtr<T> ret;
    ret.StaticCast(ptr);
    return ret;
}

/// Perform a dynamic cast from one weak pointer type to another.
template <class T, class U> SharedPtr<T> DynamicCast(const SharedPtr<U>& ptr)
{
    SharedPtr<T> ret;
    ret.DynamicCast(ptr);
    return ret;
}

/// Weak pointer template class with intrusive reference counting. Does not keep the object pointed to alive.
template <class T> class WeakPtr
{
public:
    /// Construct a null weak pointer.
    WeakPtr() noexcept
        : ptr_(nullptr)
        , weakRefsPtr_(nullptr)
    {
    }

    /// Construct a null weak pointer.
    WeakPtr(std::nullptr_t) noexcept   // NOLINT(google-explicit-constructor)
        : ptr_(nullptr)
        , weakRefsPtr_(nullptr)
    {
    }

    /// Copy-construct from another weak pointer.
    WeakPtr(const WeakPtr<T>& rhs) noexcept
        : ptr_(rhs.ptr_)
        , weakRefsPtr_(rhs.weakRefsPtr_)
    {
        AddWeakRef();
    }

    /// Move-construct from another weak pointer.
    WeakPtr(WeakPtr<T>&& rhs) noexcept
        : ptr_(rhs.ptr_)
        , weakRefsPtr_(rhs.weakRefsPtr_)
    {
        rhs.ptr_ = nullptr;
        rhs.weakRefsPtr_ = nullptr;
    }

    /// Copy-construct from another weak pointer allowing implicit upcasting.
    template <class U> WeakPtr(const WeakPtr<U>& rhs) noexcept   // NOLINT(google-explicit-constructor)
        : ptr_(rhs.ptr_)
        , weakRefsPtr_(rhs.weakRefsPtr_)
    {
        AddWeakRef();
    }

    /// Construct from a shared pointer.
    WeakPtr(const SharedPtr<T>& rhs) noexcept // NOLINT(google-explicit-constructor)
    {
        ptr_ = rhs.Get();

        if (!ptr_)
        {
            weakRefsPtr_ = nullptr;
        }
        else
        {
            weakRefsPtr_ = ptr_->GetOrCreateWeakRefs();
            assert(*weakRefsPtr_ >= 0);
            ++(*weakRefsPtr_);
        }
    }

    /// Construct from a raw pointer.
    explicit WeakPtr(T* ptr) noexcept
    {
        ptr_ = ptr;

        if (!ptr_)
        {
            weakRefsPtr_ = nullptr;
        }
        else
        {
            weakRefsPtr_ = ptr_->GetOrCreateWeakRefs();
            assert(*weakRefsPtr_ >= 0);
            ++(*weakRefsPtr_);
        }
    }

    /// Destruct. Release the weak reference to the object.
    ~WeakPtr() noexcept
    {
        ReleaseWeakRef();
    }

    /// Assign from a shared pointer.
    WeakPtr<T>& operator =(const SharedPtr<T>& rhs)
    {
        if (ptr_ == rhs.Get())
            return *this;

        WeakPtr<T> copy(rhs);
        Swap(copy);

        return *this;
    }

    /// Assign from a weak pointer.
    WeakPtr<T>& operator =(const WeakPtr<T>& rhs)
    {
        if (ptr_ == rhs.ptr_)
            return *this;

        WeakPtr<T> copy(rhs);
        Swap(copy);

        return *this;
    }

    /// Move-assign from another weak pointer.
    WeakPtr<T>& operator =(WeakPtr<T>&& rhs)
    {
        WeakPtr<T> copy(std::move(rhs));
        Swap(copy);

        return *this;
    }

    /// Assign from another weak pointer allowing implicit upcasting.
    template <class U> WeakPtr<T>& operator =(const WeakPtr<U>& rhs)
    {
        if (ptr_ == rhs.ptr_)
            return *this;

        ReleaseWeakRef();
        ptr_ = rhs.ptr_;
        weakRefsPtr_ = rhs.weakRefsPtr_;
        AddWeakRef();

        return *this;
    }

    /// Assign from a raw pointer.
    WeakPtr<T>& operator =(T* ptr)
    {
        if (ptr_ == ptr)
            return *this;

        ReleaseWeakRef();
        
        if (ptr)
        {
            ptr_ = ptr;
            weakRefsPtr_ = ptr_->GetOrCreateWeakRefs();
            assert(*weakRefsPtr_ >= 0);
            ++(*weakRefsPtr_);
        }

        return *this;
    }

    /// Convert to a shared pointer. If expired, return a null shared pointer.
    SharedPtr<T> Lock() const { return Expired() ? SharedPtr<T>() : SharedPtr<T>(ptr_); }

    /// Return raw pointer. If expired, return null.
    T* Get() const { return Expired() ? nullptr : ptr_; }

    /// Point to the object.
    T* operator ->() const
    {
        T* rawPtr = Get();
        assert(rawPtr);
        return rawPtr;
    }

    /// Dereference the object.
    T& operator *() const
    {
        T* rawPtr = Get();
        assert(rawPtr);
        return *rawPtr;
    }

    /// Subscript the object if applicable.
    T& operator [](int index)
    {
        T* rawPtr = Get();
        assert(rawPtr);
        return (*rawPtr)[index];
    }

    /// Test for equality with another weak pointer.
    template <class U> bool operator ==(const WeakPtr<U>& rhs) const { return ptr_ == rhs.ptr_; }

    /// Test for inequality with another weak pointer.
    template <class U> bool operator !=(const WeakPtr<U>& rhs) const { return ptr_ != rhs.ptr_; }

    /// Test for less than with another weak pointer.
    template <class U> bool operator <(const WeakPtr<U>& rhs) const { return ptr_ < rhs.ptr_; }

    /// Convert to a raw pointer, null if the object is expired.
    operator T*() const { return Get(); }   // NOLINT(google-explicit-constructor)

    /// Swap with another WeakPtr.
    void Swap(WeakPtr<T>& rhs)
    {
        Urho3D::Swap(ptr_, rhs.ptr_);
        Urho3D::Swap(weakRefsPtr_, rhs.weakRefsPtr_);
    }

    /// Reset with another pointer.
    void Reset(T* ptr = nullptr)
    {
        WeakPtr<T> copy(ptr);
        Swap(copy);
    }

    /// Perform a static cast from a weak pointer of another type.
    template <class U> void StaticCast(const WeakPtr<U>& rhs)
    {
        ReleaseWeakRef();
        ptr_ = static_cast<T*>(rhs.Get());
        
        if (ptr_)
        {
            weakRefsPtr_ = rhs.GetOrCreateWeakRefs();
            assert(*weakRefsPtr_ > 0);
            ++(*weakRefsPtr_);
        }
    }

    /// Perform a dynamic cast from a weak pointer of another type.
    template <class U> void DynamicCast(const WeakPtr<U>& rhs)
    {
        ReleaseWeakRef();
        ptr_ = dynamic_cast<T*>(rhs.Get());

        if (ptr_)
        {
            weakRefsPtr_ = rhs.GetOrCreateWeakRefs();
            assert(*weakRefsPtr_ > 0);
            ++(*weakRefsPtr_);
        }
    }

    /// Check if the pointer is null.
    bool Null() const { return weakRefsPtr_ == nullptr; }

    /// Check if the pointer is not null.
    bool NotNull() const { return !Null(); }

    /// Return the object's reference count, or 0 if null pointer or if object has destroyed.
    int Refs() const
    {
        if (!weakRefsPtr_)
            return 0;

        assert(*weakRefsPtr_ != 0);

        if (*weakRefsPtr_ > 0) // The object is alive
        {
            assert(ptr_);
            return ptr_->Refs();
        }
        else // Negative values mean the object has been destroyed
        {
            return 0;
        }
    }

    /// Return the object's weak reference count.
    int WeakRefs() const
    {
        if (!weakRefsPtr_)
            return 0;

        assert(*weakRefsPtr_ != 0);
        return abs(*weakRefsPtr_); // Can be negative if object has been destroyed
    }

    /// Return whether the object has destroyed. If null pointer, always return true.
    bool Expired() const
    {
        if (!weakRefsPtr_)
            return true;

        assert(*weakRefsPtr_ != 0);
        return *weakRefsPtr_ < 0;
    }

    /// Return hash value for HashSet & HashMap.
    unsigned ToHash() const { return (unsigned)((size_t)ptr_ / sizeof(T)); }

private:
    template <class U> friend class WeakPtr;

    /// Add a weak reference to the object pointed to.
    void AddWeakRef()
    {
        if (!weakRefsPtr_)
            return;

        assert(*weakRefsPtr_ != 0);

        if (*weakRefsPtr_ < 0) // Negative values mean the object has been destroyed
            --(*weakRefsPtr_);
        else // *weakRefsPtr_ > 0 mean the object is alive
            ++(*weakRefsPtr_);
    }

    /// Release the weak reference. Delete the weak reference counter if necessary.
    void ReleaseWeakRef()
    {
        if (!weakRefsPtr_)
            return;

        assert(*weakRefsPtr_ != 0);

        if (*weakRefsPtr_ < 0) // Negative values mean the object has been destroyed
        {
            ++(*weakRefsPtr_);
                
            if (*weakRefsPtr_ == 0) // This WeakPtr is the last
                delete weakRefsPtr_;
        }
        else // *weakRefsPtr_ > 0 mean the object is alive
        {
            --(*weakRefsPtr_);
            
            // Don't delete the weak reference counter even if there are no more WeakPtr
            // to avoid allocating memory again when new WeakPtr will be created
        }

        ptr_ = nullptr;
        weakRefsPtr_ = nullptr;
    }

    /// Pointer to the object.
    T* ptr_;
    
    /// Pointer to the weak reference counter.
    int* weakRefsPtr_;
};

/// Perform a static cast from one weak pointer type to another.
template <class T, class U> WeakPtr<T> StaticCast(const WeakPtr<U>& ptr)
{
    WeakPtr<T> ret;
    ret.StaticCast(ptr);
    return ret;
}

/// Perform a dynamic cast from one weak pointer type to another.
template <class T, class U> WeakPtr<T> DynamicCast(const WeakPtr<U>& ptr)
{
    WeakPtr<T> ret;
    ret.DynamicCast(ptr);
    return ret;
}

/// Delete object of type T. T must be complete. See boost::checked_delete.
template<class T> inline void CheckedDelete(T* x)
{
    // intentionally complex - simplification causes regressions
    using type_must_be_complete = char[sizeof(T) ? 1 : -1];
    (void) sizeof(type_must_be_complete);
    delete x;
}

/// Construct SharedPtr.
template <class T, class ... Args> SharedPtr<T> MakeShared(Args && ... args)
{
    return SharedPtr<T>(new T(std::forward<Args>(args)...));
}

}
