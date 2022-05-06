// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include "../Container/Str.h"
#include "../Math/MathDefs.h"

namespace Urho3D
{

class StringHashRegister;

/// 32-bit hash value for a string.
class URHO3D_API StringHash
{
public:
    /// Construct with zero value.
    StringHash() noexcept
        : value_(0)
    {
    }

    /// Copy-construct from another hash.
    StringHash(const StringHash& rhs) noexcept = default;

    /// Construct with an initial value.
    constexpr explicit StringHash(unsigned value) noexcept
        : value_(value)
    {
    }

#ifdef URHO3D_HASH_DEBUG
    /// Construct from a C string.
    StringHash(const char* str) noexcept;        // NOLINT(google-explicit-constructor)
#else
    constexpr StringHash(const char* str) noexcept
        : value_(Calculate(str))
    {
    }
#endif
                                                 
    /// Construct from a string.
    StringHash(const String& str) noexcept;      // NOLINT(google-explicit-constructor)

    /// Assign from another hash.
    StringHash& operator =(const StringHash& rhs) noexcept = default;

    /// Add a hash.
    StringHash operator +(const StringHash& rhs) const
    {
        StringHash ret;
        ret.value_ = value_ + rhs.value_;
        return ret;
    }

    /// Add-assign a hash.
    StringHash& operator +=(const StringHash& rhs)
    {
        value_ += rhs.value_;
        return *this;
    }

    /// Test for equality with another hash.
    bool operator ==(const StringHash& rhs) const { return value_ == rhs.value_; }

    /// Test for inequality with another hash.
    bool operator !=(const StringHash& rhs) const { return value_ != rhs.value_; }

    /// Test if less than another hash.
    bool operator <(const StringHash& rhs) const { return value_ < rhs.value_; }

    /// Test if greater than another hash.
    bool operator >(const StringHash& rhs) const { return value_ > rhs.value_; }

    /// Return true if nonzero hash value.
    explicit operator bool() const { return value_ != 0; }

    /// Return hash value.
    /// @property
    unsigned Value() const { return value_; }

    /// Return as string.
    String ToString() const;

    /// Return string which has specific hash value. Return first string if many (in order of calculation). Use for debug purposes only. Return empty string if URHO3D_HASH_DEBUG is off.
    String Reverse() const;

    /// Return hash value for HashSet & HashMap.
    unsigned ToHash() const { return value_; }

    /// Calculate hash value from a C string.
    static constexpr u32 Calculate(const char* str, unsigned hash = 0)
    {
        if (!str)
            return hash;

        while (*str)
        {
            hash = SDBMHash(hash, (unsigned char)*str++);
        }

        return hash;
    }

    /// Get global StringHashRegister. Use for debug purposes only. Return nullptr if URHO3D_HASH_DEBUG is off.
    static StringHashRegister* GetGlobalStringHashRegister();

    /// Zero hash.
    static const StringHash ZERO;

private:
    /// Hash value.
    unsigned value_;
};

constexpr StringHash operator ""_hash(const char* str, size_t)
{
    return StringHash(StringHash::Calculate(str));
}

}
