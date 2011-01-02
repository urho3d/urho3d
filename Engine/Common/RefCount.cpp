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

#include "PreCompiled.h"
#include "Exception.h"
#include "RefCount.h"

RefCount::RefCount() :
    mRefs(0),
    mWeakRefs(0),
    mExpired(false)
{
}

RefCounted::RefCounted() :
    mRefCount(new RefCount())
{
    // Hold a weak ref to self to avoid possible double delete of the refcount
    ++(mRefCount->mWeakRefs);
}

RefCounted::~RefCounted()
{
    if (mRefCount)
    {
        #ifdef ENABLE_REFCOUNTED_CHECKS
        if (mRefCount->mRefs)
            EXCEPTION("Destructor called when references still exist");
        if (!mRefCount->mWeakRefs)
            EXCEPTION("Weak reference count mismatch on destruction");
        #endif
        
        // Mark object as expired, release the self weak ref and delete the refcount if no other weak refs exist
        mRefCount->mExpired = true;
        --(mRefCount->mWeakRefs);
        if (!mRefCount->mWeakRefs)
            delete mRefCount;
        
        mRefCount = 0;
    }
}

void RefCounted::addRef()
{
    ++(mRefCount->mRefs);
}

void RefCounted::releaseRef()
{
    #ifdef ENABLE_REFCOUNTED_CHECKS
    if (!mRefCount->mRefs)
        EXCEPTION("releaseRef() called when reference count is already zero");
    #endif
    
    --(mRefCount->mRefs);
    if (!mRefCount->mRefs)
        delete this;
}

unsigned RefCounted::getRefCount() const
{
    return mRefCount->mRefs;
}

unsigned RefCounted::getWeakRefCount() const
{
    // Subtract one to not return the internally held reference
    return mRefCount->mWeakRefs - 1;
}
