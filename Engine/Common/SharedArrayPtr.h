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

#ifndef COMMON_SHAREDARRAYPTR_H
#define COMMON_SHAREDARRAYPTR_H

#include "Exception.h"
#include "RefCount.h"

//! Shared array pointer template class. Uses non-intrusive reference counting
template <class T> class SharedArrayPtr
{
public:
    //! Construct a null shared array pointer
    SharedArrayPtr() :
        mPtr(0),
        mRefCount(0)
    {
    }
    
    //! Copy-construct from another shared array pointer
    SharedArrayPtr(const SharedArrayPtr<T>& rhs) :
        mPtr(rhs.mPtr),
        mRefCount(rhs.mRefCount)
    {
        if (mRefCount)
            ++(mRefCount->mRefs);
    }
    
    //! Construct from a raw pointer
    explicit SharedArrayPtr(T* ptr) :
        mPtr(ptr),
        mRefCount(new RefCount())
    {
        ++(mRefCount->mRefs);
    }
    
    //! Destruct. Release the array reference
    ~SharedArrayPtr()
    {
        release();
    }
    
    //! Assign from another shared array pointer
    SharedArrayPtr<T>& operator = (const SharedArrayPtr<T>& rhs)
    {
        if (mPtr == rhs.mPtr)
            return *this;
        
        release();
        
        mPtr = rhs.mPtr;
        mRefCount = rhs.mRefCount;
        if (mRefCount)
            ++(mRefCount->mRefs);
        
        return *this;
    }
    
    //! Assign from a raw pointer
    SharedArrayPtr<T>& operator = (T* ptr)
    {
        if (mPtr == ptr)
            return *this;
        
        release();
        
        if (ptr)
        {
            mPtr = ptr;
            mRefCount = new RefCount();
            ++(mRefCount->mRefs);
        }
        
        return *this;
    }
    
    //! Point to the array
    T* operator -> () const { return mPtr; }
    //! Dereference the array
    T& operator * () const { return *mPtr; }
    //! Subscript the array
    T& operator [] (const int index) { return mPtr[index]; }
    //! Test for equality with another shared pointer
    bool operator == (const SharedArrayPtr<T>& rhs) const { return mPtr == rhs.mPtr; }
    //! Test for inequality with another shared pointer
    bool operator != (const SharedArrayPtr<T>& rhs) const { return mPtr != rhs.mPtr; }
    //! Return true if points to an array
    operator bool () const { return mPtr != 0; }
    //! Convert to a raw pointer
    operator T* () const { return mPtr; }
    
    //! Reset to null and release the array reference
    void reset()
    {
        release();
    }
    
    //! Perform a static cast from a shared array pointer of another type
    template <class U> void staticCast(const SharedArrayPtr<U>& rhs)
    {
        release();
        
        mPtr = static_cast<T*>(rhs.getPtr());
        mRefCount = rhs.getRefCountPtr();
        if (mRefCount)
            ++(mRefCount->mRefs);
    }
    
    //! Perform a dynatic cast from a shared array pointer of another type
    template <class U> void dynamicCast(const SharedArrayPtr<U>& rhs)
    {
        release();
        
        mPtr = dynamic_cast<T*>(rhs.getPtr());
        if (mPtr)
        {
            mRefCount = rhs.getRefCountPtr();
            if (mRefCount)
                ++(mRefCount->mRefs);
        }
        else
            mRefCount = 0;
    }
    
    //! Check if the pointer is null
    bool isNull() const { return mPtr == 0; }
    //! Check if the pointer is not null
    bool notNull() const { return mPtr != 0; }
    //! Return the raw pointer
    T* getPtr() const { return mPtr; }
    //! Return the array's reference count, or 0 if the pointer is null
    unsigned getRefCount() const { return mRefCount ? mRefCount->mRefs : 0; }
    //! Return the array's weak reference count, or 0 if the pointer is null
    unsigned getWeakRefCount() const { return mRefCount ? mRefCount->mWeakRefs : 0; }
    //! Return pointer to the RefCount structure
    RefCount* getRefCountPtr() const { return mRefCount; }
    
private:
    //! Prevent direct assignment from a shared array pointer of different type
    template <class U> SharedArrayPtr<T>& operator = (const SharedArrayPtr<U>& rhs);
    
    //! Release the array reference and delete it and the RefCount structure as applicable
    void release()
    {
        if (mRefCount)
        {
            if (mRefCount->mRefs)
            {
                --(mRefCount->mRefs);
                if (!mRefCount->mRefs)
                {
                    mRefCount->mExpired = true;
                    delete[] mPtr;
                }
            }
            
            if ((!mRefCount->mRefs) && (!mRefCount->mWeakRefs))
                delete mRefCount;
        }
        
        mPtr = 0;
        mRefCount = 0;
    }
    
    //! Pointer to the array
    T* mPtr;
    //! Pointer to the RefCount structure
    RefCount* mRefCount;
};

//! Perform a static cast from one shared array pointer type to another
template <class T, class U> SharedArrayPtr<T> staticCast(const SharedArrayPtr<U>& ptr)
{
    SharedArrayPtr<T> ret;
    ret.staticCast(ptr);
    return ret;
}

//! Perform a dynamic cast from one shared array pointer type to another
template <class T, class U> SharedArrayPtr<T> dynamicCast(const SharedArrayPtr<U>& ptr)
{
    SharedArrayPtr<T> ret;
    ret.dynamicCast(ptr);
    return ret;
}

//! Weak array pointer template class. Uses non-intrusive reference counting
template <class T> class WeakArrayPtr
{
public:
    //! Construct a null weak array pointer
    WeakArrayPtr() :
        mPtr(0),
        mRefCount(0)
    {
    }
    
    //! Construct from a shared array pointer
    WeakArrayPtr(const SharedArrayPtr<T>& rhs) :
        mPtr(rhs.getPtr()),
        mRefCount(rhs.getRefCountPtr())
    {
        if (mRefCount)
            ++(mRefCount->mWeakRefs);
    }
    
    //! Copy-construct from another weak array pointer
    WeakArrayPtr(const WeakArrayPtr<T>& rhs) :
        mPtr(rhs.mPtr),
        mRefCount(rhs.mRefCount)
    {
        if (mRefCount)
            ++(mRefCount->mWeakRefs);
    }
    
    //! Destruct. Release the weak reference to the array
    ~WeakArrayPtr()
    {
        release();
    }
    
    //! Assign from a shared array pointer
    WeakArrayPtr<T>& operator = (const SharedArrayPtr<T>& rhs)
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
    
    //! Assign from another weak array pointer
    WeakArrayPtr<T>& operator = (const WeakArrayPtr<T>& rhs)
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
    
    //! Convert to shared array pointer. If expired, return a null shared array pointer
    SharedArrayPtr<T> toShared() const
    {
        if (isExpired())
            return SharedArrayPtr<T>();
        else
            return SharedArrayPtr<T>(mPtr, mRefCount);
    }
    
    //! Return raw pointer. If expired, return null
    T* getPtr() const
    {
        if (isExpired())
            return 0;
        else
            return mPtr;
    }
    
    //! Point to the array. If RefCounted safety checks are enabled, throw an exception if the array has expired
    T* operator -> () const
    {
        #ifdef ENABLE_REFCOUNTED_CHECKS
        if (isExpired())
            EXCEPTION("Dereference of an expired RefCounted array");
        #endif
        
        return getPtr();
    }
    
    //! Dereference the array. If RefCounted safety checks are enabled, throw an exception if the array has expired
    T& operator * () const
    {
        #ifdef ENABLE_REFCOUNTED_CHECKS
        if (isExpired())
            EXCEPTION("Dereference of an expired RefCounted array");
        #endif
        
        return *getPtr();
    }
    
    //! Subscript the array. If RefCounted safety checks are enabled, throw an exception if the array has expired
    T& operator [] (const int index)
    {
        #ifdef ENABLE_REFCOUNTED_CHECKS
        if (isExpired())
            EXCEPTION("Dereference of an expired RefCounted array");
        #endif
        
        return mPtr[index];
    }
    
    //! Test for equality with another weak array pointer
    bool operator == (const WeakArrayPtr<T>& rhs) const { return (mPtr == rhs.mPtr) && (mRefCount == rhs.mRefCount); }
    //! Test for inequality with another weak array pointer
    bool operator != (const WeakArrayPtr<T>& rhs) const { return (mPtr != rhs.mPtr) || (mRefCount != rhs.mRefCount); }
    //! Return true if points to an array which is not expired
    operator bool () const { return !isExpired(); }
    //! Convert to a raw pointer, null if array is expired
    operator T* () const { return getPtr(); }
    
    //! Reset to null and release the weak reference
    void reset()
    {
        release();
    }
    
    //! Perform a static cast from a weak array pointer of another type
    template <class U> void staticCast(const WeakArrayPtr<U>& rhs)
    {
        release();
        
        mPtr = static_cast<T*>(rhs.getPtr());
        mRefCount = rhs.mRefCount;
        if (mRefCount)
            ++(mRefCount->mWeakRefs);
    }
    
    //! Perform a dynamic cast from a weak array pointer of another type
    template <class U> void dynamicCast(const WeakArrayPtr<U>& rhs)
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
    //! Check if the pointer is not null
    bool notNull() const { return mRefCount != 0; }
    //! Return the array's reference count, or 0 if null pointer or if array is expired
    unsigned getRefCount() const { return mRefCount ? mRefCount->mRefs : 0; }
    //! Return the array's weak reference count
    unsigned getWeakRefCount() const { return mRefCount ? mRefCount->mWeakRefs : 0; }
    //! Return whether the array has expired. If null pointer, always return true
    bool isExpired() const { return mRefCount ? mRefCount->mExpired : true; }
    //! Return pointer to RefCount structure
    RefCount* getRefCountPtr() const { return mRefCount; }
    
private:
    //! Prevent direct assignment from a weak array pointer of different type
    template <class U> WeakArrayPtr<T>& operator = (const WeakArrayPtr<U>& rhs);
    
    //! Release the weak reference. Delete the Refcount structure if the array has expired and this was the last weak reference
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
    
    //! Pointer to the array
    T* mPtr;
    //! Pointer to the RefCount structure
    RefCount* mRefCount;
};

//! Perform a static cast from one weak array pointer type to another
template <class T, class U> WeakArrayPtr<T> staticCast(const WeakArrayPtr<U>& ptr)
{
    WeakArrayPtr<T> ret;
    ret.staticCast(ptr);
    return ret;
}

//! Perform a dynamic cast from one weak pointer type to another
template <class T, class U> WeakArrayPtr<T> dynamicCast(const WeakArrayPtr<U>& ptr)
{
    WeakArrayPtr<T> ret;
    ret.dynamicCast(ptr);
    return ret;
}

#endif // COMMON_SHAREDARRAYPTR_H
