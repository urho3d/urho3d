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

/// Shared array pointer template class. Uses non-intrusive reference counting
template <class T> class SharedArrayPtr
{
public:
    /// Construct a null shared array pointer
    SharedArrayPtr() :
        ptr_(0),
        refCount_(0)
    {
    }
    
    /// Copy-construct from another shared array pointer
    SharedArrayPtr(const SharedArrayPtr<T>& rhs) :
        ptr_(rhs.ptr_),
        refCount_(rhs.refCount_)
    {
        if (refCount_)
            ++(refCount_->refs_);
    }
    
    /// Construct from a raw pointer
    explicit SharedArrayPtr(T* ptr) :
        ptr_(ptr),
        refCount_(new RefCount())
    {
        ++(refCount_->refs_);
    }
    
    /// Destruct. Release the array reference
    ~SharedArrayPtr()
    {
        Release();
    }
    
    /// Assign from another shared array pointer
    SharedArrayPtr<T>& operator = (const SharedArrayPtr<T>& rhs)
    {
        if (ptr_ == rhs.ptr_)
            return *this;
        
        Release();
        
        ptr_ = rhs.ptr_;
        refCount_ = rhs.refCount_;
        if (refCount_)
            ++(refCount_->refs_);
        
        return *this;
    }
    
    /// Assign from a raw pointer
    SharedArrayPtr<T>& operator = (T* ptr)
    {
        if (ptr_ == ptr)
            return *this;
        
        Release();
        
        if (ptr)
        {
            ptr_ = ptr;
            refCount_ = new RefCount();
            ++(refCount_->refs_);
        }
        
        return *this;
    }
    
    /// Point to the array
    T* operator -> () const { return ptr_; }
    /// Dereference the array
    T& operator * () const { return *ptr_; }
    /// Subscript the array
    T& operator [] (const int index) { return ptr_[index]; }
    /// Test for equality with another shared array pointer
    bool operator == (const SharedArrayPtr<T>& rhs) const { return ptr_ == rhs.ptr_; }
    /// Test for inequality with another shared array pointer
    bool operator != (const SharedArrayPtr<T>& rhs) const { return ptr_ != rhs.ptr_; }
    /// Test for less than with another array pointer
    bool operator < (const SharedArrayPtr<T>& rhs) const { return ptr_ < rhs.ptr_; }
    /// Return true if points to an array
    operator bool () const { return ptr_ != 0; }
    /// Convert to a raw pointer
    operator T* () const { return ptr_; }
    
    /// Reset to null and release the array reference
    void Reset()
    {
        Release();
    }
    
    /// Perform a static cast from a shared array pointer of another type
    template <class U> void StaticCast(const SharedArrayPtr<U>& rhs)
    {
        Release();
        
        ptr_ = static_cast<T*>(rhs.GetPtr());
        refCount_ = rhs.GetRefCountPtr();
        if (refCount_)
            ++(refCount_->refs_);
    }
    
    /// Perform a dynatic cast from a shared array pointer of another type
    template <class U> void DynamicCast(const SharedArrayPtr<U>& rhs)
    {
        Release();
        
        ptr_ = dynamic_cast<T*>(rhs.GetPtr());
        if (ptr_)
        {
            refCount_ = rhs.GetRefCountPtr();
            if (refCount_)
                ++(refCount_->refs_);
        }
        else
            refCount_ = 0;
    }
    
    /// Check if the pointer is null
    bool IsNull() const { return ptr_ == 0; }
    /// Check if the pointer is not null
    bool NotNull() const { return ptr_ != 0; }
    /// Return the raw pointer
    T* GetPtr() const { return ptr_; }
    /// Return the array's reference count, or 0 if the pointer is null
    unsigned GetRefCount() const { return refCount_ ? refCount_->refs_ : 0; }
    /// Return the array's weak reference count, or 0 if the pointer is null
    unsigned GetWeakRefCount() const { return refCount_ ? refCount_->weakRefs_ : 0; }
    /// Return pointer to the RefCount structure
    RefCount* GetRefCountPtr() const { return refCount_; }
    
private:
    /// Prevent direct assignment from a shared array pointer of different type
    template <class U> SharedArrayPtr<T>& operator = (const SharedArrayPtr<U>& rhs);
    
    /// Release the array reference and delete it and the RefCount structure as applicable
    void Release()
    {
        if (refCount_)
        {
            if (refCount_->refs_)
            {
                --(refCount_->refs_);
                if (!refCount_->refs_)
                {
                    refCount_->expired_ = true;
                    delete[] ptr_;
                }
            }
            
            if ((!refCount_->refs_) && (!refCount_->weakRefs_))
                delete refCount_;
        }
        
        ptr_ = 0;
        refCount_ = 0;
    }
    
    /// Pointer to the array
    T* ptr_;
    /// Pointer to the RefCount structure
    RefCount* refCount_;
};

/// Perform a static cast from one shared array pointer type to another
template <class T, class U> SharedArrayPtr<T> StaticCast(const SharedArrayPtr<U>& ptr)
{
    SharedArrayPtr<T> ret;
    ret.StaticCast(ptr);
    return ret;
}

/// Perform a dynamic cast from one shared array pointer type to another
template <class T, class U> SharedArrayPtr<T> DynamicCast(const SharedArrayPtr<U>& ptr)
{
    SharedArrayPtr<T> ret;
    ret.DynamicCast(ptr);
    return ret;
}

/// Weak array pointer template class. Uses non-intrusive reference counting
template <class T> class WeakArrayPtr
{
public:
    /// Construct a null weak array pointer
    WeakArrayPtr() :
        ptr_(0),
        refCount_(0)
    {
    }
    
    /// Construct from a shared array pointer
    WeakArrayPtr(const SharedArrayPtr<T>& rhs) :
        ptr_(rhs.GetPtr()),
        refCount_(rhs.GetRefCountPtr())
    {
        if (refCount_)
            ++(refCount_->weakRefs_);
    }
    
    /// Copy-construct from another weak array pointer
    WeakArrayPtr(const WeakArrayPtr<T>& rhs) :
        ptr_(rhs.ptr_),
        refCount_(rhs.refCount_)
    {
        if (refCount_)
            ++(refCount_->weakRefs_);
    }
    
    /// Destruct. Release the weak reference to the array
    ~WeakArrayPtr()
    {
        Release();
    }
    
    /// Assign from a shared array pointer
    WeakArrayPtr<T>& operator = (const SharedArrayPtr<T>& rhs)
    {
        if ((ptr_ == rhs.GetPtr()) && (refCount_ == rhs.GetRefCountPtr()))
            return *this;
        
        Release();
        
        ptr_ = rhs.GetPtr();
        refCount_ = rhs.GetRefCountPtr();
        if (refCount_)
            ++(refCount_->weakRefs_);
        
        return *this;
    }
    
    /// Assign from another weak array pointer
    WeakArrayPtr<T>& operator = (const WeakArrayPtr<T>& rhs)
    {
        if ((ptr_ == rhs.ptr_) && (refCount_ == rhs.refCount_))
            return *this;
        
        Release();
        
        ptr_ = rhs.ptr_;
        refCount_ = rhs.refCount_;
        if (refCount_)
            ++(refCount_->weakRefs_);
        
        return *this;
    }
    
    /// Convert to shared array pointer. If expired, return a null shared array pointer
    SharedArrayPtr<T> ToShared() const
    {
        if (IsExpired())
            return SharedArrayPtr<T>();
        else
            return SharedArrayPtr<T>(ptr_, refCount_);
    }
    
    /// Return raw pointer. If expired, return null
    T* GetPtr() const
    {
        if (IsExpired())
            return 0;
        else
            return ptr_;
    }
    
    /// Point to the array
    T* operator -> () const
    {
        return GetPtr();
    }
    
    /// Dereference the array
    T& operator * () const
    {
        return *GetPtr();
    }
    
    /// Subscript the array
    T& operator [] (const int index)
    {
        return (*GetPtr())[index];
    }
    
    /// Test for equality with another weak array pointer
    bool operator == (const WeakArrayPtr<T>& rhs) const { return (ptr_ == rhs.ptr_) && (refCount_ == rhs.refCount_); }
    /// Test for inequality with another weak array pointer
    bool operator != (const WeakArrayPtr<T>& rhs) const { return (ptr_ != rhs.ptr_) || (refCount_ != rhs.refCount_); }
    /// Test for less than with another weak array pointer
    bool operator < (const WeakArrayPtr<T>& rhs) const { return ptr_ < rhs.ptr_; }
    /// Return true if points to an array which is not expired
    operator bool () const { return !IsExpired(); }
    /// Convert to a raw pointer, null if array is expired
    operator T* () const { return GetPtr(); }
    
    /// Reset to null and release the weak reference
    void Reset()
    {
        Release();
    }
    
    /// Perform a static cast from a weak array pointer of another type
    template <class U> void StaticCast(const WeakArrayPtr<U>& rhs)
    {
        Release();
        
        ptr_ = static_cast<T*>(rhs.GetPtr());
        refCount_ = rhs.refCount_;
        if (refCount_)
            ++(refCount_->weakRefs_);
    }
    
    /// Perform a dynamic cast from a weak array pointer of another type
    template <class U> void DynamicCast(const WeakArrayPtr<U>& rhs)
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
    /// Check if the pointer is not null
    bool NotNull() const { return refCount_ != 0; }
    /// Return the array's reference count, or 0 if null pointer or if array is expired
    unsigned GetRefCount() const { return refCount_ ? refCount_->refs_ : 0; }
    /// Return the array's weak reference count
    unsigned GetWeakRefCount() const { return refCount_ ? refCount_->weakRefs_ : 0; }
    /// Return whether the array has expired. If null pointer, always return true
    bool IsExpired() const { return refCount_ ? refCount_->expired_ : true; }
    /// Return pointer to RefCount structure
    RefCount* GetRefCountPtr() const { return refCount_; }
    
private:
    /// Prevent direct assignment from a weak array pointer of different type
    template <class U> WeakArrayPtr<T>& operator = (const WeakArrayPtr<U>& rhs);
    
    /// Release the weak reference. Delete the Refcount structure if the array has expired and this was the last weak reference
    void Release()
    {
        if (refCount_)
        {
            if (refCount_->weakRefs_)
                --(refCount_->weakRefs_);
            
            if ((!refCount_->refs_) && (!refCount_->weakRefs_))
                delete refCount_;
        }
        
        ptr_ = 0;
        refCount_ = 0;
    }
    
    /// Pointer to the array
    T* ptr_;
    /// Pointer to the RefCount structure
    RefCount* refCount_;
};

/// Perform a static cast from one weak array pointer type to another
template <class T, class U> WeakArrayPtr<T> StaticCast(const WeakArrayPtr<U>& ptr)
{
    WeakArrayPtr<T> ret;
    ret.StaticCast(ptr);
    return ret;
}

/// Perform a dynamic cast from one weak pointer type to another
template <class T, class U> WeakArrayPtr<T> DynamicCast(const WeakArrayPtr<U>& ptr)
{
    WeakArrayPtr<T> ret;
    ret.DynamicCast(ptr);
    return ret;
}
