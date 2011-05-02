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

#include "Precompiled.h"
#include "RefCounted.h"

#include "DebugNew.h"

RefCounted::RefCounted() :
    refCount_(new RefCount())
{
    // Hold a weak ref to self to avoid possible double delete of the refcount
    ++(refCount_->weakRefs_);
}

RefCounted::~RefCounted()
{
    if (refCount_)
    {
        // Mark object as expired, release the self weak ref and delete the refcount if no other weak refs exist
        refCount_->expired_ = true;
        --(refCount_->weakRefs_);
        if (!refCount_->weakRefs_)
            delete refCount_;
        
        refCount_ = 0;
    }
}

void RefCounted::AddRef()
{
    ++(refCount_->refs_);
}

void RefCounted::ReleaseRef()
{
    --(refCount_->refs_);
    if (!refCount_->refs_)
        delete this;
}

unsigned RefCounted::GetRefCount() const
{
    return refCount_->refs_;
}

unsigned RefCounted::GetWeakRefCount() const
{
    // Subtract one to not return the internally held reference
    return refCount_->weakRefs_ - 1;
}
