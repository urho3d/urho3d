// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include "../Precompiled.h"

#include "../Core/StringHashRegister.h"
#include "../Core/Mutex.h"
#include "../IO/Log.h"

#include <cstdio>

#include "../DebugNew.h"

using namespace std;

namespace Urho3D
{

StringHashRegister::StringHashRegister(bool threadSafe)
{
    if (threadSafe)
        mutex_ = make_unique<Mutex>();
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
