// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include "../Container/HashMap.h"
#include "../Container/Ptr.h"
#include "../Math/StringHash.h"

#include <memory>

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
    std::unique_ptr<Mutex> mutex_;
};

}
