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

#include "../Container/RefCounted.h"
#include "../Container/Swap.h"

#include <cassert>
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
        if (ptr_)
        {
            RefCount* refCount = RefCountPtr();
            ++refCount->refs_; // 2 refs
            Reset(); // 1 ref
            --refCount->refs_; // 0 refs
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

    /// Return pointer to the RefCount structure.
    RefCount* RefCountPtr() const { return ptr_ ? ptr_->RefCountPtr() : nullptr; }

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
    WeakPtr() noexcept :
        ptr_(nullptr),
        refCount_(nullptr)
    {
    }

    /// Construct a null weak pointer.
    WeakPtr(std::nullptr_t) noexcept :   // NOLINT(google-explicit-constructor)
        ptr_(nullptr),
        refCount_(nullptr)
    {
    }

    /// Copy-construct from another weak pointer.
    WeakPtr(const WeakPtr<T>& rhs) noexcept :
        ptr_(rhs.ptr_),
        refCount_(rhs.refCount_)
    {
        AddRef();
    }

    /// Move-construct from another weak pointer.
    WeakPtr(WeakPtr<T>&& rhs) noexcept :
        ptr_(rhs.ptr_),
        refCount_(rhs.refCount_)
    {
        rhs.ptr_ = nullptr;
        rhs.refCount_ = nullptr;
    }

    /// Copy-construct from another weak pointer allowing implicit upcasting.
    template <class U> WeakPtr(const WeakPtr<U>& rhs) noexcept :   // NOLINT(google-explicit-constructor)
        ptr_(rhs.ptr_),
        refCount_(rhs.refCount_)
    {
        AddRef();
    }

    /// Construct from a shared pointer.
    WeakPtr(const SharedPtr<T>& rhs) noexcept : // NOLINT(google-explicit-constructor)
        ptr_(rhs.Get()),
        refCount_(rhs.RefCountPtr())
    {
        AddRef();
    }

    /// Construct from a raw pointer.
    explicit WeakPtr(T* ptr) noexcept :
        ptr_(ptr),
        refCount_(ptr ? ptr->RefCountPtr() : nullptr)
    {
        AddRef();
    }

    /// Destruct. Release the weak reference to the object.
    ~WeakPtr() noexcept
    {
        ReleaseRef();
    }

    /// Assign from a shared pointer.
    WeakPtr<T>& operator =(const SharedPtr<T>& rhs)
    {
        if (ptr_ == rhs.Get() && refCount_ == rhs.RefCountPtr())
            return *this;

        WeakPtr<T> copy(rhs);
        Swap(copy);

        return *this;
    }

    /// Assign from a weak pointer.
    WeakPtr<T>& operator =(const WeakPtr<T>& rhs)
    {
        if (ptr_ == rhs.ptr_ && refCount_ == rhs.refCount_)
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
        if (ptr_ == rhs.ptr_ && refCount_ == rhs.refCount_)
            return *this;

        ReleaseRef();
        ptr_ = rhs.ptr_;
        refCount_ = rhs.refCount_;
        AddRef();

        return *this;
    }

    /// Assign from a raw pointer.
    WeakPtr<T>& operator =(T* ptr)
    {
        RefCount* refCount = ptr ? ptr->RefCountPtr() : nullptr;

        if (ptr_ == ptr && refCount_ == refCount)
            return *this;

        ReleaseRef();
        ptr_ = ptr;
        refCount_ = refCount;
        AddRef();

        return *this;
    }

    /// Convert to a shared pointer. If expired, return a null shared pointer.
    SharedPtr<T> Lock() const
    {
        if (Expired())
            return SharedPtr<T>();
        else
            return SharedPtr<T>(ptr_);
    }

    /// Return raw pointer. If expired, return null.
    T* Get() const
    {
        return Expired() ? nullptr : ptr_;
    }

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
    template <class U> bool operator ==(const WeakPtr<U>& rhs) const { return ptr_ == rhs.ptr_ && refCount_ == rhs.refCount_; }

    /// Test for inequality with another weak pointer.
    template <class U> bool operator !=(const WeakPtr<U>& rhs) const { return ptr_ != rhs.ptr_ || refCount_ != rhs.refCount_; }

    /// Test for less than with another weak pointer.
    template <class U> bool operator <(const WeakPtr<U>& rhs) const { return ptr_ < rhs.ptr_; }

    /// Convert to a raw pointer, null if the object is expired.
    operator T*() const { return Get(); }   // NOLINT(google-explicit-constructor)

    /// Swap with another WeakPtr.
    void Swap(WeakPtr<T>& rhs)
    {
        Urho3D::Swap(ptr_, rhs.ptr_);
        Urho3D::Swap(refCount_, rhs.refCount_);
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
        ReleaseRef();
        ptr_ = static_cast<T*>(rhs.Get());
        refCount_ = rhs.refCount_;
        AddRef();
    }

    /// Perform a dynamic cast from a weak pointer of another type.
    template <class U> void DynamicCast(const WeakPtr<U>& rhs)
    {
        ReleaseRef();
        ptr_ = dynamic_cast<T*>(rhs.Get());

        if (ptr_)
        {
            refCount_ = rhs.refCount_;
            AddRef();
        }
        else
            refCount_ = 0;
    }

    /// Check if the pointer is null.
    bool Null() const { return refCount_ == nullptr; }

    /// Check if the pointer is not null.
    bool NotNull() const { return refCount_ != nullptr; }

    /// Return the object's reference count, or 0 if null pointer or if object has expired.
    int Refs() const { return (refCount_ && refCount_->refs_ >= 0) ? refCount_->refs_ : 0; }

    /// Return the object's weak reference count.
    int WeakRefs() const
    {
        if (!Expired())
            return ptr_->WeakRefs();
        else
            return refCount_ ? refCount_->weakRefs_ : 0;
    }

    /// Return whether the object has expired. If null pointer, always return true.
    bool Expired() const { return refCount_ ? refCount_->refs_ < 0 : true; }

    /// Return pointer to the RefCount structure.
    RefCount* RefCountPtr() const { return refCount_; }

    /// Return hash value for HashSet & HashMap.
    unsigned ToHash() const { return (unsigned)((size_t)ptr_ / sizeof(T)); }

private:
    template <class U> friend class WeakPtr;

    /// Add a weak reference to the object pointed to.
    void AddRef()
    {
        if (refCount_)
        {
            assert(refCount_->weakRefs_ >= 0);
            ++(refCount_->weakRefs_);
        }
    }

    /// Release the weak reference. Delete the Refcount structure if necessary.
    void ReleaseRef()
    {
        if (refCount_)
        {
            assert(refCount_->weakRefs_ > 0);
            --(refCount_->weakRefs_);

            if (Expired() && !refCount_->weakRefs_)
                delete refCount_;
        }

        ptr_ = nullptr;
        refCount_ = nullptr;
    }

    /// Pointer to the object.
    T* ptr_;
    /// Pointer to the RefCount structure.
    RefCount* refCount_;
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

/// Unique pointer template class.
template <class T> class UniquePtr
{
public:
    /// Construct empty.
    UniquePtr() : ptr_(nullptr) { }

    /// Construct from pointer.
    explicit UniquePtr(T* ptr) : ptr_(ptr) { }

    /// Prevent copy construction.
    UniquePtr(const UniquePtr&) = delete;
    /// Prevent assignment.
    UniquePtr& operator=(const UniquePtr&) = delete;

    /// Assign from pointer.
    UniquePtr& operator = (T* ptr)
    {
        Reset(ptr);
        return *this;
    }

    /// Construct empty.
    UniquePtr(std::nullptr_t) { }   // NOLINT(google-explicit-constructor)

    /// Move-construct from UniquePtr.
    UniquePtr(UniquePtr&& up) noexcept :
        ptr_(up.Detach()) {}

    /// Move-assign from UniquePtr.
    UniquePtr& operator =(UniquePtr&& up) noexcept
    {
        Reset(up.Detach());
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

    /// Test for less than with another unique pointer.
    template <class U>
    bool operator <(const UniquePtr<U>& rhs) const { return ptr_ < rhs.ptr_; }

    /// Test for equality with another unique pointer.
    template <class U>
    bool operator ==(const UniquePtr<U>& rhs) const { return ptr_ == rhs.ptr_; }

    /// Test for inequality with another unique pointer.
    template <class U>
    bool operator !=(const UniquePtr<U>& rhs) const { return ptr_ != rhs.ptr_; }

    /// Cast pointer to bool.
    operator bool() const { return !!ptr_; }    // NOLINT(google-explicit-constructor)

    /// Swap with another UniquePtr.
    void Swap(UniquePtr& up) { Urho3D::Swap(ptr_, up.ptr_); }

    /// Detach pointer from UniquePtr without destroying.
    T* Detach()
    {
        T* ptr = ptr_;
        ptr_ = nullptr;
        return ptr;
    }

    /// Check if the pointer is null.
    bool Null() const { return ptr_ == 0; }

    /// Check if the pointer is not null.
    bool NotNull() const { return ptr_ != 0; }

    /// Return the raw pointer.
    T* Get() const { return ptr_; }

    /// Reset.
    void Reset(T* ptr = nullptr)
    {
        CheckedDelete(ptr_);
        ptr_ = ptr;
    }

    /// Return hash value for HashSet & HashMap.
    unsigned ToHash() const { return (unsigned)((size_t)ptr_ / sizeof(T)); }

    /// Destruct.
    ~UniquePtr()
    {
        Reset();
    }

private:
    T* ptr_;

};

/// Swap two UniquePtr-s.
template <class T> void Swap(UniquePtr<T>& first, UniquePtr<T>& second)
{
    first.Swap(second);
}

/// Construct UniquePtr.
template <class T, class ... Args> UniquePtr<T> MakeUnique(Args && ... args)
{
    return UniquePtr<T>(new T(std::forward<Args>(args)...));
}

/// Construct SharedPtr.
template <class T, class ... Args> SharedPtr<T> MakeShared(Args && ... args)
{
    return SharedPtr<T>(new T(std::forward<Args>(args)...));
}

}
