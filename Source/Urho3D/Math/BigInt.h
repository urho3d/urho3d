// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include "../Container/Pair.h"
#include "../Container/Str.h"
#include "../Container/Vector.h"
#include "MathDefs.h"

namespace Urho3D
{

/// @nobind
class URHO3D_API BigInt
{
public:
    /// i64 can conatins 10^9 * 10^9.
    using Digit = i64;

private:
    /// Sign.
    bool positive_;

    /// Array of digits with base 10^9 and reverse order (each element contains value in range [0 .. BASE-1]).
    Vector<Digit> magnitude_;

public:
    BigInt();
    BigInt(const String& str);
    BigInt(i32 value);
    BigInt(i64 value);
    BigInt(u32 value);
    BigInt(u64 value);

    bool operator ==(const BigInt& rhs) const { return positive_ == rhs.positive_ && magnitude_ == rhs.magnitude_; }
    bool operator !=(const BigInt& rhs) const { return positive_ != rhs.positive_ || magnitude_ != rhs.magnitude_; }

    bool operator <(const BigInt& rhs) const;
    bool operator >(const BigInt& rhs) const { return rhs < *this; }

    BigInt operator +(const BigInt& rhs) const;
    BigInt operator -(const BigInt& rhs) const;
    BigInt operator *(const BigInt& rhs) const;

    BigInt& operator +=(const BigInt& rhs);
    BigInt& operator -=(const BigInt& rhs);
    BigInt& operator *=(const BigInt& rhs);

    /// Prefix increment operator.
    BigInt& operator++() { this->operator +=(1); return *this; }

    /// Postfix increment operator.
    BigInt operator++(int) { BigInt ret = *this; ++*this; return ret; }

    /// Prefix decrement operator.
    BigInt& operator--() { this->operator -=(1); return *this; }

    /// Postfix decrement operator.
    BigInt operator--(int) { BigInt ret = *this; --*this; return ret; }

    String ToString() const;
};

} // namespace Urho3D
