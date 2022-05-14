// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include "BigInt.h"

#include "../Container/Pair.h"
#include "../Core/StringUtils.h"

#include "../DebugNew.h"

namespace Urho3D
{

#if true
    static constexpr BigInt::Digit BASE = 1000'000'000; // 10^9

    // Number of decimal digits in each magnitude_ element
    static constexpr i32 BASE_DIGITS = 9;
#else // For tests
    static constexpr BigInt::Digit BASE = 10;
    static constexpr i32 BASE_DIGITS = 1;
#endif

// Compare magnitudes
static bool FirstIsLess(const Vector<BigInt::Digit>& first, const Vector<BigInt::Digit>& second)
{
    if (first.Size() != second.Size())
        return first.Size() < second.Size();

    for (i32 i = (i32)first.Size() - 1; i >= 0; --i)
    {
        if (first[i] != second[i])
            return first[i] < second[i];
    }

    return false; // first == b
}

// a + b
static Vector<BigInt::Digit> SumMagnitudes(const Vector<BigInt::Digit>& a, const Vector<BigInt::Digit>& b)
{
    Vector<BigInt::Digit> ret;

    u32 maxSize = Max(a.Size(), b.Size());
    ret.Resize(maxSize, 0);

    for (u32 i = 0; i < maxSize; ++i)
    {
        BigInt::Digit a_element = i < a.Size() ? a[i] : 0;
        BigInt::Digit b_element = i < b.Size() ? b[i] : 0;
        BigInt::Digit sum = a_element + b_element;

        ret[i] += sum; // ret[i] can be not zero

        while (ret[i] >= BASE)
        {
            ret[i] -= BASE; // Use div & mod instead loop?

            if (i + 1 < ret.Size())
                ++ret[i + 1];
            else
                ret.Push(1);
        }
    }

    return ret;
}

// a - b (a must be >= b)
static Vector<BigInt::Digit> DiffMagnitudes(const Vector<BigInt::Digit>& a, const Vector<BigInt::Digit>& b)
{
    Vector<BigInt::Digit> ret;
    ret.Resize(a.Size(), 0);

    for (u32 i = 0; i < a.Size(); ++i)
    {
        BigInt::Digit a_element = a[i];
        BigInt::Digit b_element = i < b.Size() ? b[i] : 0;
        BigInt::Digit diff = a_element - b_element;

        ret[i] += diff; // ret[i] can be not zero

        while (ret[i] < 0)
        {
            ret[i] += BASE;

            assert(i + 1 < ret.Size());
            --ret[i + 1];
        }
    }

    // Remove leading zeros
    while (ret.Size() >= 2 && ret.Back() == 0)
        ret.Pop();

    return ret;
}

// Return quotient and remainder.
// If denominator == 0, then return {0, 0}
Pair<BigInt, BigInt> DivMod(BigInt numerator, BigInt denominator)
{
    if (denominator == 0)
        return {0, 0};

    BigInt absNum = Abs(numerator);
    BigInt absDenom = Abs(denominator);

    BigInt quotient = 0;
    BigInt remainder = absNum;

    // The Simplest and slowest way
    while (remainder >= absDenom)
    {
        ++quotient;
        remainder -= absDenom;

        String strQ = quotient.ToString();
        String strRem = remainder.ToString();
        int a = 0;
    }

    // https://en.cppreference.com/w/cpp/language/operator_arithmetic
    // (a/b)*b + a%b == a
    // 7/3 = {2, 1}    | 2*3 + 1 == 7
    // -7/3 = {-2, -1} | -2*3 + -1 == -7
    // 7/-3 = {-2, 1}  | -2*-3 + 1 == 7
    // -7/-3 = {2, -1} | 2*-3 + -1 == -7

    if (numerator.IsPositive() != denominator.IsPositive())
        quotient = -quotient;

    if (numerator.IsNegative())
        remainder = -remainder;

    return {quotient, remainder};
}

BigInt::BigInt()
{
    // Init as zero
    positive_ = true;
    magnitude_.Resize(1, 0);
}

BigInt::BigInt(const String& str)
{
    if (str.Empty())
    {
        // Init as zero
        positive_ = true;
        magnitude_.Resize(1, 0);
        return;
    }

    i32 firstDigitPos;

    if (str[0] == '-')
    {
        positive_ = false;
        firstDigitPos = 1;
    }
    else if (str[0] == '+')
    {
        positive_ = true;
        firstDigitPos = 1;
    }
    else
    {
        positive_ = true;
        firstDigitPos = 0;
    }

    // Skip leading zeros
    for (i32 i = firstDigitPos; i < (i32)str.Length(); ++i)
    {
        if (str[i] != '0')
            break;

        ++firstDigitPos;
    }

    i32 lastDigitPos = -1;
    for (i32 i = firstDigitPos; i < (i32)str.Length(); ++i)
    {
        if (!IsDigit(str[i]))
            break;
        
        lastDigitPos = i;
    }

    if (lastDigitPos == -1)
    {
        // Init as zero
        positive_ = true;
        magnitude_.Resize(1, 0);
        return;
    }

    i32 numDigits = lastDigitPos - firstDigitPos + 1;
    magnitude_.Reserve(numDigits / BASE_DIGITS + 1);

    // Retrieve chunks of 9 digits in reverse order and save to single i32
    i32 i = lastDigitPos - BASE_DIGITS + 1;
    for (; i > firstDigitPos; i -= BASE_DIGITS)
    {
        String chunk = str.Substring(i, BASE_DIGITS);
        magnitude_.Push(ToInt64(chunk)); // To Digit
    }

    String lastChunk = str.Substring(firstDigitPos, BASE_DIGITS + i - firstDigitPos);
    magnitude_.Push(ToInt64(lastChunk)); // To Digit
}

BigInt::BigInt(i32 value)
{
    positive_ = (value >= 0);
    value = Urho3D::Abs(value);

    while (value != 0)
    {
        Digit mod = value % BASE;
        magnitude_.Push(mod);
        value /= BASE;
    }

    if (!magnitude_.Size()) // value == 0
        magnitude_.Push(0);
}

BigInt::BigInt(i64 value)
{
    positive_ = (value >= 0);
    value = Urho3D::Abs(value);

    while (value != 0)
    {
        Digit mod = value % BASE;
        magnitude_.Push(mod);
        value /= BASE;
    }
    
    if (!magnitude_.Size()) // value == 0
        magnitude_.Push(0);
}

BigInt::BigInt(u32 value)
{
    positive_ = true;

    while (value != 0)
    {
        Digit mod = value % BASE;
        magnitude_.Push(mod);
        value /= BASE;
    }

    if (!magnitude_.Size()) // value == 0
        magnitude_.Push(0);
}

BigInt::BigInt(u64 value)
{
    positive_ = true;

    while (value != 0)
    {
        Digit mod = (Digit)(value % BASE);
        magnitude_.Push(mod);
        value /= BASE;
    }

    if (!magnitude_.Size()) // value == 0
        magnitude_.Push(0);
}

bool BigInt::IsZero() const
{
    assert(magnitude_.Size() > 0);

    if (magnitude_.Size() == 1 && magnitude_[0] == 0)
    {
        assert(positive_);
        return true;
    }

    return false;
}

bool BigInt::operator <(const BigInt& rhs) const
{
    if (positive_ != rhs.positive_)
        return !positive_;

    if (positive_)
        return FirstIsLess(magnitude_, rhs.magnitude_);
    else
        return FirstIsLess(rhs.magnitude_, magnitude_);
}

String BigInt::ToString() const
{
    assert(magnitude_.Size() > 0);

    String ret;

    if (!positive_)
        ret = "-";

    // Beginning of the number without leading zeros
    i32 i = (i32)magnitude_.Size() - 1;
    ret += String(magnitude_[i]);
    --i;

    // Another chunks with leading zeros
    for (; i >= 0; --i)
    {
        String str(magnitude_[i]);
        
        if (str.Length() < BASE_DIGITS)
        {
            String zeros('0', BASE_DIGITS - str.Length());
            str = zeros + str;
        }

        ret += str;
    }

    return ret;
}

BigInt BigInt::operator +(const BigInt& rhs) const
{
    BigInt ret;

    if (positive_ == rhs.positive_)
    {
        ret.positive_ = positive_;
        ret.magnitude_ = SumMagnitudes(magnitude_, rhs.magnitude_);
    }
    else
    {
        if (FirstIsLess(magnitude_, rhs.magnitude_))
        {
            ret.positive_ = rhs.positive_;
            ret.magnitude_ = DiffMagnitudes(rhs.magnitude_, magnitude_);
        }
        else
        {
            ret.positive_ = positive_;
            ret.magnitude_ = DiffMagnitudes(magnitude_, rhs.magnitude_);
        }
    }
    
    return ret;
}

BigInt BigInt::operator -(const BigInt& rhs) const
{
    BigInt ret;

    if (positive_ != rhs.positive_)
    {
        ret.positive_ = positive_;
        ret.magnitude_ = SumMagnitudes(magnitude_, rhs.magnitude_);
    }
    else
    {
        if (FirstIsLess(magnitude_, rhs.magnitude_))
        {
            ret.positive_ = !rhs.positive_;
            ret.magnitude_ = DiffMagnitudes(rhs.magnitude_, magnitude_);
        }
        else
        {
            ret.positive_ = positive_;
            ret.magnitude_ = DiffMagnitudes(magnitude_, rhs.magnitude_);
        }
    }

    return ret;
}

BigInt BigInt::operator *(const BigInt& rhs) const
{
    BigInt ret;
    ret.magnitude_.Resize(magnitude_.Size() + rhs.magnitude_.Size(), 0);

    if (positive_ == rhs.positive_)
        ret.positive_ = true;
    else
        ret.positive_ = false;

    for (u32 this_index = 0; this_index < magnitude_.Size(); ++this_index)
    {
        for (u32 rhs_index = 0; rhs_index < rhs.magnitude_.Size(); ++rhs_index)
            ret.magnitude_[this_index + rhs_index] += magnitude_[this_index] * rhs.magnitude_[rhs_index];
    }

    for (u32 i = 0; i < ret.magnitude_.Size() - 1; ++i)
    {
        ret.magnitude_[i + 1] += ret.magnitude_[i] / BASE;
        ret.magnitude_[i] %= BASE;
    }

    // Remove leading zeros
    while (ret.magnitude_.Size() >= 2 && ret.magnitude_.Back() == 0)
        ret.magnitude_.Pop();

    return ret;
}

BigInt BigInt::operator /(const BigInt& rhs) const
{
    Pair<BigInt, BigInt> divMod = DivMod(*this, rhs);
    return divMod.first_;
}

BigInt BigInt::operator %(const BigInt& rhs) const
{
    Pair<BigInt, BigInt> divMod = DivMod(*this, rhs);
    return divMod.second_;
}

BigInt BigInt::operator -() const
{
    BigInt ret = *this;
    if (!ret.IsZero())
        ret.positive_ = !ret.positive_;
    return ret;
}

BigInt& BigInt::operator +=(const BigInt& rhs)
{
    BigInt result = *this + rhs;
    Swap(this->positive_, result.positive_);
    Swap(this->magnitude_, result.magnitude_);
    return *this;
}

BigInt& BigInt::operator -=(const BigInt& rhs)
{
    BigInt result = *this - rhs;
    Swap(this->positive_, result.positive_);
    Swap(this->magnitude_, result.magnitude_);
    return *this;
}

BigInt& BigInt::operator *=(const BigInt& rhs)
{
    BigInt result = *this * rhs;
    Swap(this->positive_, result.positive_);
    Swap(this->magnitude_, result.magnitude_);
    return *this;
}

BigInt& BigInt::operator /=(const BigInt& rhs)
{
    BigInt result = *this / rhs;
    Swap(this->positive_, result.positive_);
    Swap(this->magnitude_, result.magnitude_);
    return *this;
}

BigInt& BigInt::operator %=(const BigInt& rhs)
{
    BigInt result = *this % rhs;
    Swap(this->positive_, result.positive_);
    Swap(this->magnitude_, result.magnitude_);
    return *this;
}

} // namespace Urho3D
