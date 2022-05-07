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
private:
    /// Sign.
    bool positive_;

    /// Array of digits with base 10^9 and reverse order.
    Vector<i32> magnitude_;

public:
    BigInt();
    BigInt(const String& str);

    bool operator ==(const BigInt& rhs) const { return positive_ == rhs.positive_ && magnitude_ == rhs.magnitude_; }
    bool operator !=(const BigInt& rhs) const { return positive_ != rhs.positive_ || magnitude_ != rhs.magnitude_; }

    bool operator <(const BigInt& rhs) const;
    bool operator >(const BigInt& rhs) const { return rhs < *this; }

    BigInt operator +(const BigInt& rhs) const;
    BigInt operator -(const BigInt& rhs) const;

    String ToString() const;
};

} // namespace Urho3D
