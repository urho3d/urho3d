// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include "../Container/Str.h"
#include "../Container/Vector.h"
#include "MathDefs.h"

namespace Urho3D
{

class URHO3D_API BigInt
{
public:
    /// i64 can conatins 10^9 * 10^9.
    using Digit = i64;

private:
    /// Sign (zero is positive).
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

    bool IsPositive() const { return positive_; }
    bool IsNegative() const { return !positive_; }
    bool IsZero() const;

    bool operator ==(const BigInt& rhs) const { return positive_ == rhs.positive_ && magnitude_ == rhs.magnitude_; }
    bool operator !=(const BigInt& rhs) const { return positive_ != rhs.positive_ || magnitude_ != rhs.magnitude_; }

    bool operator <(const BigInt& rhs) const;
    bool operator >(const BigInt& rhs) const { return rhs < *this; }

    bool operator <=(const BigInt& rhs) const { return *this == rhs || *this < rhs; }
    bool operator >=(const BigInt& rhs) const { return *this == rhs || *this > rhs; }

    BigInt operator +(const BigInt& rhs) const;
    BigInt operator -(const BigInt& rhs) const;
    BigInt operator *(const BigInt& rhs) const;

    /// Return 0 if rhs zero.
    BigInt operator /(const BigInt& rhs) const;
    
    /// Return 0 if rhs zero.
    BigInt operator %(const BigInt& rhs) const;

    BigInt operator -() const;

    BigInt& operator +=(const BigInt& rhs);
    BigInt& operator -=(const BigInt& rhs);
    BigInt& operator *=(const BigInt& rhs);
    BigInt& operator /=(const BigInt& rhs);
    BigInt& operator %=(const BigInt& rhs);

    /// Prefix increment operator.
    BigInt& operator++() { this->operator +=(1); return *this; }

    /// Postfix increment operator.
    BigInt operator++(int x) { BigInt ret = *this; ++*this; return ret; }

    /// Prefix decrement operator.
    BigInt& operator--() { this->operator -=(1); return *this; }

    /// Postfix decrement operator.
    BigInt operator--(int x) { BigInt ret = *this; --*this; return ret; }

    String ToString() const;
};

#if false // Without constraints this can cause conflicts
template <typename T> BigInt operator +(T lhs, const BigInt& rhs) { return BigInt(lhs) + rhs; }
template <typename T> BigInt operator -(T lhs, const BigInt& rhs) { return BigInt(lhs) - rhs; }
template <typename T> BigInt operator *(T lhs, const BigInt& rhs) { return BigInt(lhs) * rhs; }
template <typename T> BigInt operator /(T lhs, const BigInt& rhs) { return BigInt(lhs) / rhs; }
template <typename T> BigInt operator %(T lhs, const BigInt& rhs) { return BigInt(lhs) % rhs; }
#else
inline BigInt operator +(i32 lhs, const BigInt& rhs) { return BigInt(lhs) + rhs; }
inline BigInt operator +(u32 lhs, const BigInt& rhs) { return BigInt(lhs) + rhs; }
inline BigInt operator +(i64 lhs, const BigInt& rhs) { return BigInt(lhs) + rhs; }
inline BigInt operator +(u64 lhs, const BigInt& rhs) { return BigInt(lhs) + rhs; }

inline BigInt operator -(i32 lhs, const BigInt& rhs) { return BigInt(lhs) - rhs; }
inline BigInt operator -(u32 lhs, const BigInt& rhs) { return BigInt(lhs) - rhs; }
inline BigInt operator -(i64 lhs, const BigInt& rhs) { return BigInt(lhs) - rhs; }
inline BigInt operator -(u64 lhs, const BigInt& rhs) { return BigInt(lhs) - rhs; }

inline BigInt operator *(i32 lhs, const BigInt& rhs) { return BigInt(lhs) * rhs; }
inline BigInt operator *(u32 lhs, const BigInt& rhs) { return BigInt(lhs) * rhs; }
inline BigInt operator *(i64 lhs, const BigInt& rhs) { return BigInt(lhs) * rhs; }
inline BigInt operator *(u64 lhs, const BigInt& rhs) { return BigInt(lhs) * rhs; }

inline BigInt operator /(i32 lhs, const BigInt& rhs) { return BigInt(lhs) / rhs; }
inline BigInt operator /(u32 lhs, const BigInt& rhs) { return BigInt(lhs) / rhs; }
inline BigInt operator /(i64 lhs, const BigInt& rhs) { return BigInt(lhs) / rhs; }
inline BigInt operator /(u64 lhs, const BigInt& rhs) { return BigInt(lhs) / rhs; }

inline BigInt operator %(i32 lhs, const BigInt& rhs) { return BigInt(lhs) % rhs; }
inline BigInt operator %(u32 lhs, const BigInt& rhs) { return BigInt(lhs) % rhs; }
inline BigInt operator %(i64 lhs, const BigInt& rhs) { return BigInt(lhs) % rhs; }
inline BigInt operator %(u64 lhs, const BigInt& rhs) { return BigInt(lhs) % rhs; }
#endif

inline BigInt Abs(const BigInt& value) { return value.IsNegative() ? -value : value; }

} // namespace Urho3D
