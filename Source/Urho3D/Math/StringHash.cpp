// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include "../Precompiled.h"

#include "../Container/HashMap.h"
#include "../Core/StringHashRegister.h"
#include "../IO/Log.h"
#include "../Math/StringHash.h"

#include <cstdio>

#include "../DebugNew.h"

namespace Urho3D
{

#ifdef URHO3D_HASH_DEBUG

// Expose map to let Visual Studio debugger access it if Urho3D is linked statically.
const StringMap* hashReverseMap = nullptr;

// Hide static global variables in functions to ensure initialization order.
static StringHashRegister& GetGlobalStringHashRegister()
{
    static StringHashRegister stringHashRegister(true /*thread safe*/ );
    hashReverseMap = &stringHashRegister.GetInternalMap();
    return stringHashRegister;
}

#endif

const StringHash StringHash::ZERO;

#ifdef URHO3D_HASH_DEBUG
StringHash::StringHash(const char* str) noexcept :
    value_(Calculate(str))
{
    Urho3D::GetGlobalStringHashRegister().RegisterString(*this, str);
}
#endif

StringHash::StringHash(const String& str) noexcept :
    value_(Calculate(str.CString()))
{
#ifdef URHO3D_HASH_DEBUG
    Urho3D::GetGlobalStringHashRegister().RegisterString(*this, str.CString());
#endif
}

StringHashRegister* StringHash::GetGlobalStringHashRegister()
{
#ifdef URHO3D_HASH_DEBUG
    return &Urho3D::GetGlobalStringHashRegister();
#else
    return nullptr;
#endif
}

String StringHash::ToString() const
{
    char tempBuffer[CONVERSION_BUFFER_LENGTH];
    sprintf(tempBuffer, "%08X", value_);
    return String(tempBuffer);
}

String StringHash::Reverse() const
{
#ifdef URHO3D_HASH_DEBUG
    return Urho3D::GetGlobalStringHashRegister().GetStringCopy(*this);
#else
    return String::EMPTY;
#endif
}

}
