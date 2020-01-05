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

#include "../Precompiled.h"

#include "../Core/StringHashRegister.h"
#include "../Core/Mutex.h"
#include "../IO/Log.h"

#include <cstdio>

#include "../DebugNew.h"

namespace Urho3D
{

StringHashRegister::StringHashRegister(bool threadSafe)
{
    if (threadSafe)
        mutex_ = MakeUnique<Mutex>();
}


StringHashRegister::~StringHashRegister()       // NOLINT(hicpp-use-equals-default, modernize-use-equals-default)
{
    // Keep destructor here to let mutex_ destruct
}

StringHash StringHashRegister::RegisterString(const StringHash& hash, const char* string)
{
    if (mutex_)
        mutex_->Acquire();

    auto iter = map_.Find(hash);
    if (iter == map_.End())
    {
        map_.Populate(hash, string);
    }
    else if (iter->second_.Compare(string, false) != 0)
    {
        URHO3D_LOGWARNINGF("StringHash collision detected! Both \"%s\" and \"%s\" have hash #%s",
            string, iter->second_.CString(), hash.ToString().CString());
    }

    if (mutex_)
        mutex_->Release();

    return hash;
}

StringHash StringHashRegister::RegisterString(const char* string)
{
    StringHash hash(string);
    return RegisterString(hash, string);
}

String StringHashRegister::GetStringCopy(const StringHash& hash) const
{
    if (mutex_)
        mutex_->Acquire();

    const String copy = GetString(hash);

    if (mutex_)
        mutex_->Release();

    return copy;
}

bool StringHashRegister::Contains(const StringHash& hash) const
{
    if (mutex_)
        mutex_->Acquire();

    const bool contains = map_.Contains(hash);

    if (mutex_)
        mutex_->Release();

    return contains;
}

const String& StringHashRegister::GetString(const StringHash& hash) const
{
    auto iter = map_.Find(hash);
    return iter == map_.End() ? String::EMPTY : iter->second_;
}

}
