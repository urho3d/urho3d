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

#pragma once

#include "../Container/HashMap.h"
#include "../Container/Ptr.h"
#include "../Math/StringHash.h"

namespace Urho3D
{

class Mutex;

/// Helper class used for StringHash reversing.
class URHO3D_API StringHashRegister
{
public:
    /// Construct. threadSafe controls whether the RegisterString and GetStringCopy are thread-safe.
    StringHashRegister(bool threadSafe);
    /// Destruct.
    ~StringHashRegister();

    /// Register string for hash reverse mapping. Could be used from StringHash ctor.
    StringHash RegisterString(const StringHash& hash, const char* string);
    /// Register string for hash reverse mapping.
    StringHash RegisterString(const char* string);
    /// Return string for given StringHash. Return empty string if not found.
    String GetStringCopy(const StringHash& hash) const;
    /// Return whether the string in contained in the register.
    bool Contains(const StringHash& hash) const;

    /// Return String for given StringHash. Return value is unsafe to use if RegisterString is called from other threads.
    const String& GetString(const StringHash& hash) const;
    /// Return map of hashes. Return value is unsafe to use if RegisterString is called from other threads.
    const StringMap& GetInternalMap() const { return map_; }

private:
    /// Hash to string map.
    StringMap map_;
    /// Mutex.
    UniquePtr<Mutex> mutex_;
};

}
