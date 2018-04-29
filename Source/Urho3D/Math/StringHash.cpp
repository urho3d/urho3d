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

#include "../Math/MathDefs.h"
#include "../Math/StringHash.h"
#include "../Container/HashMap.h"
#include "../Core/Mutex.h"
#include "../IO/Log.h"

#include <cstdio>

#include "../DebugNew.h"

namespace Urho3D
{

#ifdef URHO3D_HASH_DEBUG

// Expose map to let Visual Studio debugger access it if Urho3D is linked statically.
StringMap* hashReverseMap = nullptr;

// Hide static global variables in functions to ensure initialization order.
// @{
static Mutex& GetHashReverseMapMutex()
{
    static Mutex mutex;
    return mutex;
}

static StringMap& GetHashReverseMap()
{
    static StringMap map;
    hashReverseMap = &map;
    return map;
}
// @}

static void AddStringHash(const StringHash& hash, const char* string)
{
    Mutex& guard = GetHashReverseMapMutex();
    guard.Acquire();

    StringMap& map = GetHashReverseMap();
    auto iter = map.Find(hash);
    if (iter == map.End())
    {
        map.Populate(hash, string);
    }
    else if (iter->second_.Compare(string, false) != 0)
    {
        URHO3D_LOGWARNINGF("String hash collision detected! Both \"%s\" and \"%s\" have hash #%s",
            string, iter->second_.CString(), hash.ToString().CString());
    }

    guard.Release();
}

static String ReverseStringHash(const StringHash& hash)
{
    Mutex& guard = GetHashReverseMapMutex();
    guard.Acquire();

    const StringMap& map = GetHashReverseMap();
    auto iter = map.Find(hash);
    String result = iter == map.End() ? String::EMPTY : iter->second_;

    guard.Release();
    return result;
}

#else

static void AddStringHash(const StringHash& /*hash*/, const char* /*string*/)
{
    // Do nothing
}

static String ReverseStringHash(const StringHash& /*hash*/)
{
    // Do nothing
    return String::EMPTY;
}

#endif

const StringHash StringHash::ZERO;

StringHash::StringHash(const char* str) noexcept :
    value_(Calculate(str))
{
    AddStringHash(*this, str);
}

StringHash::StringHash(const String& str) noexcept :
    value_(Calculate(str.CString()))
{
    AddStringHash(*this, str.CString());
}

unsigned StringHash::Calculate(const char* str, unsigned hash)
{
    if (!str)
        return hash;

    while (*str)
    {
        // Perform the actual hashing as case-insensitive
        char c = *str;
        hash = SDBMHash(hash, (unsigned char)tolower(c));
        ++str;
    }

    return hash;
}

const StringMap* StringHash::GetHashReverseMap()
{
#ifdef URHO3D_HASH_DEBUG
    return &Urho3D::GetHashReverseMap();
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
    return ReverseStringHash(*this);
}

}
