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

#ifndef COMMON_SHAREDPTR_H
#define COMMON_SHAREDPTR_H

#include "Exception.h"
#include "RefCount.h"

//! Shared pointer template class. Can point to an object that derives from RefCounted
template <class T> class SharedPtr
{
public:
    //! Construct a null shared pointer
    SharedPtr() :
        mPtr(0)
    {
    }
    
    //! Copy-construct from another shared pointer
    SharedPtr(const SharedPtr<T>& rhs) :
        mPtr(rhs.mPtr)
    {
        if (mPtr)
            mPtr->addRef();
    }
    
    //! Construct from a raw pointer
    explicit SharedPtr(T* ptr) :
        mPtr(ptr)
    {
        if (mPtr)
            mPtr->addRef();
    }
    
    //! Destruct. Release the object reference
    ~SharedPtr()
    {
        release();
    }
    
    //! Assign from another shared pointer
    SharedPtr<T>& operator = (const SharedPtr<T>& rhs)
    {
        if (mPtr == rhs.mPtr)
            return *this;
        
        release();
        
        mPtr = rhs.mPtr;
        if (mPtr)
            mPtr->addRef();
        
        return *this;
    }
    
    //! Assign from a raw pointer
    SharedPtr<T>& operator = (T* ptr)
    {
        if (mPtr == ptr)
            return *this;
        
        release();
        
        mPtr = ptr;
        if (mPtr)
            mPtr->addRef();
        
        return *this;
    }
    
    //! Point to the object
    T* operator -> () const { return mPtr; }
    //! Dereference the object
    T& operator * () const { return *mPtr; }
    //! Subscript the object if applicable
    T& operator [] (const int index) { return mPtr[index]; }
    //! Test for equality with another shared pointer
    bool operator == (const SharedPtr<T>& rhs) const { return mPtr == rhs.mPtr; }
    //! Test for inequality with another shared pointer
    bool operator != (const SharedPtr<T>& rhs) const { return mPtr != rhs.mPtr; }
    //! Return true if the pointer is not null
    operator bool () const { return mPtr != 0; }
    //! Convert to a raw pointer
    operator T* () const { return mPtr; }
    
    //! Reset to null and release the object reference
    void reset()
    {
        release();
    }
    
    //! Perform a static cast from a shared pointer of another type
    template <class U> void staticCast(const SharedPtr<U>& rhs)
    {
        release();
        
        mPtr = static_cast<T*>(rhs.getPtr());
        if (mPtr)
            mPtr->addRef();
    }
    
    //! Perform a dynamic cast from a shared pointer of another type
    template <class U> void dynamicCast(const SharedPtr<U>& rhs)
    {
        release();
        
        mPtr = dynamic_cast<T*>(rhs.getPtr());
        if (mPtr)
            mPtr->addRef();
    }
    
    //! Check if the pointer is null
    bool isNull() const { return mPtr == 0; }
    //! Check if the pointer is not null
    bool notNull() const { return mPtr != 0; }
    //! Return the raw pointer
    T* getPtr() const { return mPtr; }
    //! Return the object's reference count, or 0 if the pointer is null
    unsigned getRefCount() const { return mPtr ? mPtr->getRefCount() : 0; }
    //! Return the object's weak reference count, or 0 if the pointer is null
    unsigned getWeakRefCount() const { return mPtr ? mPtr->getWeakRefCount() : 0; }
    //! Return pointer to the RefCount structure
    RefCount* getRefCountPtr() const { return mPtr ? mPtr->getRefCountPtr() : 0; }
    
private:
    //! Prevent direct assignment from a shared pointer of another type
    template <class U> SharedPtr<T>& operator = (const SharedPtr<U>& rhs);
    
    //! Release the object reference. This will trigger its deletion if this was the last reference
    void release()
    {
        if (mPtr)
        {
            mPtr->releaseRef();
            mPtr = 0;
        }
    }
    
    //! Pointer to the object
    T* mPtr;
};

//! Perform a static cast from one shared pointer type to another
template <class T, class U> SharedPtr<T> staticCast(const SharedPtr<U>& ptr)
{
    SharedPtr<T> ret;
    ret.staticCast(ptr);
    return ret;
}

//! Perform a dynamic cast from one weak pointer type to another
template <class T, class U> SharedPtr<T> dynamicCast(const SharedPtr<U>& ptr)
{
    SharedPtr<T> ret;
    ret.dynamicCast(ptr);
    return ret;
}

//! Weak pointer template class. Can point to an object that derives from RefCounted, but does not keep it alive
template <class T> class WeakPtr
{
public:
    //! Construct a null weak pointer
    WeakPtr() :
        mPtr(0),
        mRefCount(0)
    {
    }
    
    //! Construct from a shared pointer
    WeakPtr(const SharedPtr<T>& rhs) :
        mPtr(rhs.getPtr()),
        mRefCount(rhs.getRefCountPtr())
    {
        if (mRefCount)
            ++(mRefCount->mWeakRefs);
    }
    
    //! Copy-construct from another weak pointer
    WeakPtr(const WeakPtr<T>& rhs) :
        mPtr(rhs.mPtr),
        mRefCount(rhs.mRefCount)
    {
        if (mRefCount)
            ++(mRefCount->mWeakRefs);
    }
    
    //! Construct from a raw pointer
    explicit WeakPtr(T* ptr) :
        mPtr(ptr),
        mRefCount(ptr ? ptr->getRefCountPtr() : 0)
    {
        if (mRefCount)
            ++(mRefCount->mWeakRefs);
    }
    
    //! Destruct. Release the weak reference to the object
    ~WeakPtr()
    {
        release();
    }
    
    //! Assign from a shared pointer
    WeakPtr<T>& operator = (const SharedPtr<T>& rhs)
    {
        if ((mPtr == rhs.getPtr()) && (mRefCount == rhs.getRefCountPtr()))
            return *this;
        
        release();
        
        mPtr = rhs.getPtr();
        mRefCount = rhs.getRefCountPtr();
        if (mRefCount)
            ++(mRefCount->mWeakRefs);
        
        return *this;
    }
    
    //! Assign from a weak pointer
    WeakPtr<T>& operator = (const WeakPtr<T>& rhs)
    {
        if ((mPtr == rhs.mPtr) && (mRefCount == rhs.mRefCount))
            return *this;
        
        release();
        
        mPtr = rhs.mPtr;
        mRefCount = rhs.mRefCount;
        if (mRefCount)
            ++(mRefCount->mWeakRefs);
        
        return *this;
    }
    
    //! Assign from a raw pointer
    WeakPtr<T>& operator = (T* ptr)
    {
        RefCount* refCount = ptr ? ptr->getRefCountPtr() : 0;
        
        if ((mPtr == ptr) && (mRefCount == refCount))
            return *this;
        
        release();
        
        mPtr = ptr;
        mRefCount = refCount;
        if (mRefCount)
            ++(mRefCount->mWeakRefs);
        
        return *this;
    }
    
    //! Convert to a shared pointer. If expired, return a null shared pointer
    SharedPtr<T> toShared() const
    {
        if (isExpired())
            return SharedPtr<T>();
        else
            return SharedPtr<T>(mPtr);
    }
    
    //! Return raw pointer. If expired, return null
    T* getPtr() const
    {
        if (isExpired())
            return 0;
        else
            return mPtr;
    }
    
    //! Point to the object. If RefCounted safety checks are enabled, throw an exception if the object has expired
    T* operator -> () const
    {
        #ifdef ENABLE_REFCOUNTED_CHECKS
        if (isExpired())
            EXCEPTION("Dereference of an expired RefCounted object");
        #endif
        
        return getPtr();
    }
    
    //! Dereference the object. If RefCounted safety checks are enabled, throw an exception if the object has expired
    T& operator * () const
    {
        #ifdef ENABLE_REFCOUNTED_CHECKS
        if (isExpired())
            EXCEPTION("Dereference of an expired RefCounted object");
        #endif
        
        return *getPtr();
    }
    
    //! Subscript the object if applicable. If RefCounted safety checks are enabled, throw an exception if the object has expired
    T& operator [] (const int index)
    {
        #ifdef ENABLE_REFCOUNTED_CHECKS
        if (isExpired())
            EXCEPTION("Dereference of an expired RefCounted object");
        #endif
        
        return mPtr[index];
    }
    
    //! Test for equality with another weak pointer
    bool operator == (const WeakPtr<T>& rhs) const { return (mPtr == rhs.mPtr) && (mRefCount == rhs.mRefCount); }
    //! Test for inequality with another weak pointer
    bool operator != (const WeakPtr<T>& rhs) const { return (mPtr != rhs.mPtr) || (mRefCount != rhs.mRefCount); }
    //! Return true if points to an object which is not expired
    operator bool () const { return !isExpired(); }
    //! Convert to a raw pointer, null if the object is expired
    operator T* () const { return getPtr(); }
    
    //! Reset to null and release the weak reference
    void reset()
    {
        release();
    }
    
    //! Perform a static cast from a weak pointer of another type
    template <class U> void staticCast(const WeakPtr<U>& rhs)
    {
        release();
        
        mPtr = static_cast<T*>(rhs.getPtr());
        mRefCount = rhs.mRefCount;
        if (mRefCount)
            ++(mRefCount->mWeakRefs);
    }
    
    //! Perform a dynamic cast from a weak pointer of another type
    template <class U> void dynamicCast(const WeakPtr<U>& rhs)
    {
        release();
        
        mPtr = dynamic_cast<T*>(rhs.getPtr());
        if (mPtr)
        {
            mRefCount = rhs.mRefCount;
            if (mRefCount)
                ++(mRefCount->mWeakRefs);
        }
        else
            mRefCount = 0;
    }
    
    //! Check if the pointer is null
    bool isNull() const { return mRefCount == 0; }
    //! Check if the pointer is not null. It does not matter whether the object has expired or not
    bool notNull() const { return mRefCount != 0; }
    //! Return the object's reference count, or 0 if null pointer or if object is expired
    unsigned getRefCount() const { return mRefCount ? mRefCount->mRefs : 0; }
    
    //! Return the object's weak reference count
    unsigned getWeakRefCount() const
    {
        if (!isExpired)
            return mPtr->getWeakRefCount();
        
        return mRefCount ? mRefCount->mWeakRefs : 0;
    }
    
    //! Return whether the object has expired. If null pointer, always return true
    bool isExpired() const { return mRefCount ? mRefCount->mExpired : true; }
    //! Return pointer to the RefCount structure
    RefCount* getRefCountPtr() const { return mRefCount; }
    
private:
    //! Prevent direct assignment from a weak pointer of different type
    template <class U> WeakPtr<T>& operator = (const WeakPtr<U>& rhs);
    
    //! Release the weak reference. Delete the Refcount structure if the object has expired and this was the last weak reference
    void release()
    {
        if (mRefCount)
        {
            if (mRefCount->mWeakRefs)
                --(mRefCount->mWeakRefs);
            
            if ((!mRefCount->mRefs) && (!mRefCount->mWeakRefs))
                delete mRefCount;
        }
        
        mPtr = 0;
        mRefCount = 0;
    }
    
    //! Pointer to the object
    T* mPtr;
    //! Pointer to the RefCount structure
    RefCount* mRefCount;
};

//! Perform a static cast from one weak pointer type to another
template <class T, class U> WeakPtr<T> staticCast(const WeakPtr<U>& ptr)
{
    WeakPtr<T> ret;
    ret.staticCast(ptr);
    return ret;
}

//! Perform a dynamic cast from one weak pointer type to another
template <class T, class U> WeakPtr<T> dynamicCast(const WeakPtr<U>& ptr)
{
    WeakPtr<T> ret;
    ret.dynamicCast(ptr);
    return ret;
}

#endif // COMMON_SHAREDPTR_H
