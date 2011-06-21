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

#include "RefCounted.h"

/// Shared pointer template class. Can point to an object that derives from RefCounted
template <class T> class SharedPtr
{
public:
    /// Construct a null shared pointer
    SharedPtr() :
        ptr_(0)
    {
    }
    
    /// Copy-construct from another shared pointer
    SharedPtr(const SharedPtr<T>& rhs) :
        ptr_(rhs.ptr_)
    {
        if (ptr_)
            ptr_->AddRef();
    }
    
    /// Construct from a raw pointer
    explicit SharedPtr(T* ptr) :
        ptr_(ptr)
    {
        if (ptr_)
            ptr_->AddRef();
    }
    
    /// Destruct. Release the object reference
    ~SharedPtr()
    {
        Release();
    }
    
    /// Assign from another shared pointer
    SharedPtr<T>& operator = (const SharedPtr<T>& rhs)
    {
        if (ptr_ == rhs.ptr_)
            return *this;
        
        Release();
        
        ptr_ = rhs.ptr_;
        if (ptr_)
            ptr_->AddRef();
        
        return *this;
    }
    
    /// Assign from a raw pointer
    SharedPtr<T>& operator = (T* ptr)
    {
        if (ptr_ == ptr)
            return *this;
        
        Release();
        
        ptr_ = ptr;
        if (ptr_)
            ptr_->AddRef();
        
        return *this;
    }
    
    /// Point to the object
    T* operator -> () const { return ptr_; }
    /// Dereference the object
    T& operator * () const { return *ptr_; }
    /// Subscript the object if applicable
    T& operator [] (const int index) { return ptr_[index]; }
    /// Test for less than with another shared pointer
    bool operator < (const SharedPtr<T>& rhs) const { return ptr_ < rhs.ptr_; }
    /// Test for equality with another shared pointer
    bool operator == (const SharedPtr<T>& rhs) const { return ptr_ == rhs.ptr_; }
    /// Test for inequality with another shared pointer
    bool operator != (const SharedPtr<T>& rhs) const { return ptr_ != rhs.ptr_; }
    /// Return true if the pointer is not null
    operator bool () const { return ptr_ != 0; }
    /// Convert to a raw pointer
    operator T* () const { return ptr_; }
    
    /// Reset to null and release the object reference
    void Reset()
    {
        Release();
    }
    
    /// Perform a static cast from a shared pointer of another type
    template <class U> void StaticCast(const SharedPtr<U>& rhs)
    {
        Release();
        
        ptr_ = static_cast<T*>(rhs.GetPtr());
        if (ptr_)
            ptr_->AddRef();
    }
    
    /// Perform a dynamic cast from a shared pointer of another type
    template <class U> void DynamicCast(const SharedPtr<U>& rhs)
    {
        Release();
        
        ptr_ = dynamic_cast<T*>(rhs.GetPtr());
        if (ptr_)
            ptr_->AddRef();
    }
    
    /// Check if the pointer is null
    bool IsNull() const { return ptr_ == 0; }
    /// Check if the pointer is not null
    bool NotNull() const { return ptr_ != 0; }
    /// Return the raw pointer
    T* GetPtr() const { return ptr_; }
    /// Return the object's reference count, or 0 if the pointer is null
    unsigned GetRefCount() const { return ptr_ ? ptr_->GetRefCount() : 0; }
    /// Return the object's weak reference count, or 0 if the pointer is null
    unsigned GetWeakRefCount() const { return ptr_ ? ptr_->GetWeakRefCount() : 0; }
    /// Return pointer to the RefCount structure
    RefCount* GetRefCountPtr() const { return ptr_ ? ptr_->GetRefCountPtr() : 0; }
    /// Return hash value for HashSet & HashMap
    unsigned ToHash() const { return ((unsigned)ptr_) / sizeof(T); }
    
private:
    /// Prevent direct assignment from a shared pointer of another type
    template <class U> SharedPtr<T>& operator = (const SharedPtr<U>& rhs);
    
    /// Release the object reference. This will trigger its deletion if this was the last reference
    void Release()
    {
        if (ptr_)
        {
            ptr_->ReleaseRef();
            ptr_ = 0;
        }
    }
    
    /// Pointer to the object
    T* ptr_;
};

/// Perform a static cast from one shared pointer type to another
template <class T, class U> SharedPtr<T> StaticCast(const SharedPtr<U>& ptr)
{
    SharedPtr<T> ret;
    ret.StaticCast(ptr);
    return ret;
}

/// Perform a dynamic cast from one weak pointer type to another
template <class T, class U> SharedPtr<T> DynamicCast(const SharedPtr<U>& ptr)
{
    SharedPtr<T> ret;
    ret.DynamicCast(ptr);
    return ret;
}

/// Weak pointer template class. Can point to an object that derives from RefCounted, but does not keep it alive
template <class T> class WeakPtr
{
public:
    /// Construct a null weak pointer
    WeakPtr() :
        ptr_(0),
        refCount_(0)
    {
    }
    
    /// Construct from a shared pointer
    WeakPtr(const SharedPtr<T>& rhs) :
        ptr_(rhs.GetPtr()),
        refCount_(rhs.GetRefCountPtr())
    {
        if (refCount_)
            ++(refCount_->weakRefs_);
    }
    
    /// Copy-construct from another weak pointer
    WeakPtr(const WeakPtr<T>& rhs) :
        ptr_(rhs.ptr_),
        refCount_(rhs.refCount_)
    {
        if (refCount_)
            ++(refCount_->weakRefs_);
    }
    
    /// Construct from a raw pointer
    explicit WeakPtr(T* ptr) :
        ptr_(ptr),
        refCount_(ptr ? ptr->GetRefCountPtr() : 0)
    {
        if (refCount_)
            ++(refCount_->weakRefs_);
    }
    
    /// Destruct. Release the weak reference to the object
    ~WeakPtr()
    {
        Release();
    }
    
    /// Assign from a shared pointer
    WeakPtr<T>& operator = (const SharedPtr<T>& rhs)
    {
        if (ptr_ == rhs.GetPtr() && refCount_ == rhs.GetRefCountPtr())
            return *this;
        
        Release();
        
        ptr_ = rhs.GetPtr();
        refCount_ = rhs.GetRefCountPtr();
        if (refCount_)
            ++(refCount_->weakRefs_);
        
        return *this;
    }
    
    /// Assign from a weak pointer
    WeakPtr<T>& operator = (const WeakPtr<T>& rhs)
    {
        if (ptr_ == rhs.ptr_ && refCount_ == rhs.refCount_)
            return *this;
        
        Release();
        
        ptr_ = rhs.ptr_;
        refCount_ = rhs.refCount_;
        if (refCount_)
            ++(refCount_->weakRefs_);
        
        return *this;
    }
    
    /// Assign from a raw pointer
    WeakPtr<T>& operator = (T* ptr)
    {
        RefCount* refCount = ptr ? ptr->GetRefCountPtr() : 0;
        
        if (ptr_ == ptr && refCount_ == refCount)
            return *this;
        
        Release();
        
        ptr_ = ptr;
        refCount_ = refCount;
        if (refCount_)
            ++(refCount_->weakRefs_);
        
        return *this;
    }
    
    /// Convert to a shared pointer. If expired, return a null shared pointer
    SharedPtr<T> ToShared() const
    {
        if (IsExpired())
            return SharedPtr<T>();
        else
            return SharedPtr<T>(ptr_);
    }
    
    /// Return raw pointer. If expired, return null
    T* GetPtr() const
    {
        if (IsExpired())
            return 0;
        else
            return ptr_;
    }
    
    /// Point to the object
    T* operator -> () const
    {
        return GetPtr();
    }
    
    /// Dereference the object
    T& operator * () const
    {
        return *GetPtr();
    }
    
    /// Subscript the object if applicable
    T& operator [] (const int index)
    {
        return (*GetPtr())[index];
    }
    
    /// Test for equality with another weak pointer
    bool operator == (const WeakPtr<T>& rhs) const { return ptr_ == rhs.ptr_ && refCount_ == rhs.refCount_; }
    /// Test for inequality with another weak pointer
    bool operator != (const WeakPtr<T>& rhs) const { return ptr_ != rhs.ptr_ || refCount_ != rhs.refCount_; }
    /// Test for less than with another weak pointer
    bool operator < (const SharedPtr<T>& rhs) const { return ptr_ < rhs.ptr_; }
    /// Return true if points to an object which is not expired
    operator bool () const { return !IsExpired(); }
    /// Convert to a raw pointer, null if the object is expired
    operator T* () const { return GetPtr(); }
    
    /// Reset to null and release the weak reference
    void Reset()
    {
        Release();
    }
    
    /// Perform a static cast from a weak pointer of another type
    template <class U> void StaticCast(const WeakPtr<U>& rhs)
    {
        Release();
        
        ptr_ = static_cast<T*>(rhs.GetPtr());
        refCount_ = rhs.refCount_;
        if (refCount_)
            ++(refCount_->weakRefs_);
    }
    
    /// Perform a dynamic cast from a weak pointer of another type
    template <class U> void DynamicCast(const WeakPtr<U>& rhs)
    {
        Release();
        
        ptr_ = dynamic_cast<T*>(rhs.GetPtr());
        if (ptr_)
        {
            refCount_ = rhs.refCount_;
            if (refCount_)
                ++(refCount_->weakRefs_);
        }
        else
            refCount_ = 0;
    }
    
    /// Check if the pointer is null
    bool IsNull() const { return refCount_ == 0; }
    /// Check if the pointer is not null. It does not matter whether the object has expired or not
    bool NotNull() const { return refCount_ != 0; }
    /// Return the object's reference count, or 0 if null pointer or if object is expired
    unsigned GetRefCount() const { return refCount_ ? refCount_->refs_ : 0; }
    
    /// Return the object's weak reference count
    unsigned GetWeakRefCount() const
    {
        if (!IsExpired())
            return ptr_->GetWeakRefCount();
        
        return refCount_ ? refCount_->weakRefs_ : 0;
    }
    
    /// Return whether the object has expired. If null pointer, always return true
    bool IsExpired() const { return refCount_ ? refCount_->expired_ : true; }
    /// Return pointer to the RefCount structure
    RefCount* GetRefCountPtr() const { return refCount_; }
    /// Return hash value for HashSet & HashMap
    unsigned ToHash() const { return ((unsigned)ptr_) / sizeof(T); }
    
private:
    /// Prevent direct assignment from a weak pointer of different type
    template <class U> WeakPtr<T>& operator = (const WeakPtr<U>& rhs);
    
    /// Release the weak reference. Delete the Refcount structure if the object has expired and this was the last weak reference
    void Release()
    {
        if (refCount_)
        {
            if (refCount_->weakRefs_)
                --(refCount_->weakRefs_);
            
            if (!refCount_->refs_ && !refCount_->weakRefs_)
                delete refCount_;
        }
        
        ptr_ = 0;
        refCount_ = 0;
    }
    
    /// Pointer to the object
    T* ptr_;
    /// Pointer to the RefCount structure
    RefCount* refCount_;
};

/// Perform a static cast from one weak pointer type to another
template <class T, class U> WeakPtr<T> StaticCast(const WeakPtr<U>& ptr)
{
    WeakPtr<T> ret;
    ret.StaticCast(ptr);
    return ret;
}

/// Perform a dynamic cast from one weak pointer type to another
template <class T, class U> WeakPtr<T> DynamicCast(const WeakPtr<U>& ptr)
{
    WeakPtr<T> ret;
    ret.DynamicCast(ptr);
    return ret;
}
