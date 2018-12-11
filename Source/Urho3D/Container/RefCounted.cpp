//
// Copyright (c) 2008-2018 the Urho3D project.
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

#include "../Precompiled.h"

#include "../Container/RefCounted.h"

#include "../DebugNew.h"

namespace Urho3D
{

RefCounted::RefCounted() :
    refs_(0),
    weakRefs_(0)
{
}

RefCounted::~RefCounted()
{
    assert(refs_ == 0);

    // Mark object as expired
    refs_ = -1;
}

void RefCounted::AddRef()
{
    assert(refs_ >= 0);
    refs_++;
}

void RefCounted::ReleaseRef()
{
    assert(refs_ > 0);
    refs_--;
    if (!refs_)
    {
        if (!weakRefs_)
            delete this;
        else
            this->~RefCounted();
    }
}

void RefCounted::DecrementRef()
{
    assert(refs_ > 0);
    refs_--;
    assert(!(refs_ == 0 && weakRefs_ != 0));
}

void RefCounted::AddWeakRef()
{
    weakRefs_++;
}

void RefCounted::ReleaseWeakRef()
{
    assert(weakRefs_ > 0);
    weakRefs_--;
    if (!weakRefs_ && refs_ == -1)
        operator delete(this);
}

}
