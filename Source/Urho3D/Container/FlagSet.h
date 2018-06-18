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

#pragma once


#include <type_traits>


namespace Urho3D
{

/// Bitwise Type trait which enables against Enum value. for consumption by flagset class and it's global operators.
template<typename T> struct is_flagset
{
    constexpr static bool value = false;
};

/// A set of flags defined by an Enum.
template <class E, class = typename std::enable_if<is_flagset<E>::value>::type>
class FlagSet
{
public:
    /// Enum type
    using Enum = E;
    /// Integer type
    using Integer = typename std::underlying_type<Enum>::type;
public:
    /// Ctor by integer
    explicit FlagSet(Integer value)
        : value_(value)
    {
    }
    /// Empty constructor.
    FlagSet() = default;

    /// Copy constructor.
    FlagSet(const FlagSet& another) = default;

    /// Construct from Enum value.
    FlagSet(const Enum value)
        : value_((Integer) value)
    {
    }

    /// Assignment operator from flagset.
    FlagSet& operator = (const FlagSet& rhs) = default;

    /// Bitwise AND against Enum value.
    FlagSet& operator &= (const Enum value)
    {
        value_ &= (Integer) value;
        return *this;
    }

    /// Bitwise AND against flagset value.
    FlagSet& operator &= (const FlagSet value)
    {
        value_ &= value.value_;
        return *this;
    }

    /// Bitwise OR against Enum value.
    FlagSet& operator |= (const Enum value)
    {
        value_ |= (Integer) value;
        return *this;
    }

    /// Bitwise OR against flagset value.
    FlagSet& operator |= (const FlagSet value)
    {
        value_ |= value.value_;
        return *this;
    }

    /// Bitwise XOR against Enum value.
    FlagSet& operator ^= (const Enum value)
    {
        value_ ^= (Integer) value;
        return *this;
    }

    /// Bitwise XOR against flagset value.
    FlagSet& operator ^= (const FlagSet value)
    {
        value_ ^= value.value_;
        return *this;
    }

    /// Bitwise AND against Enum value.
    FlagSet operator & (const Enum value) const
    {
        return FlagSet(value_ & (Integer) value);
    }

    /// Bitwise AND against flagset value.
    FlagSet operator & (const FlagSet value) const
    {
        return FlagSet(value_ & value.value_);
    }

    /// Bitwise OR against Enum value.
    FlagSet operator | (const Enum value) const
    {
        return FlagSet(value_ | (Integer) value);
    }

    /// Bitwise OR against flagset value.
    FlagSet operator | (const FlagSet value) const
    {
        return FlagSet(value_ | value.value_);
    }

    /// Bitwise XOR against Enum value.
    FlagSet operator ^ (const Enum value) const
    {
        return FlagSet(value_ ^ (Integer) value);
    }

    /// Bitwise XOR against flagset value.
    FlagSet operator ^ (const FlagSet value) const
    {
        return FlagSet(value_ ^ value.value_);
    }

    /// Bitwise negation.
    FlagSet operator ~ () const
    {
        return FlagSet(~value_);
    }

    /// Boolean negation.
    bool operator ! () const
    {
        return !value_;
    }

    /// Returns true if any flag is set.
    operator bool () const
    {
        return value_ != 0;
    }

    /// Cast to underlying type of enum.
    operator Integer() const
    {
        return value_;
    }

    /// Cast to enum value.
    operator Enum() const
    {
        return (Enum)value_;
    }

    /// Equality check against enum value.
    bool operator ==(Enum rhs)
    {
        return value_ == (Integer)rhs;
    }

    /// Equality check against another flagset.
    bool operator ==(FlagSet rhs)
    {
        return value_ == rhs.value_;
    }

    /// Non-equality check against enum value.
    bool operator !=(Enum rhs)
    {
        return value_ != (Integer)rhs;
    }

    /// Non-equality check against another flagset value.
    bool operator !=(FlagSet rhs)
    {
        return value_ != rhs.value_;
    }

    /// Returns true if specified enum value is set.
    inline bool is(const Enum value) const
    {
        Integer flags = (Integer) value;
        return (value_ & flags) == flags && (flags != 0 || value_ == flags);
    }

protected:
    /// Value
    Integer value_ = 0;
};

}

/// Bitwise Operator OR for against Enum value.s
template <class Enum, class = typename std::enable_if<Urho3D::is_flagset<Enum>::value>::type>
Urho3D::FlagSet<Enum> operator |(const Enum lhs, const Enum rhs)
{
    return Urho3D::FlagSet<Enum>(lhs) | rhs;
}

/// Bitwise Operator AND for against Enum value.s
template <class Enum, class = typename std::enable_if<Urho3D::is_flagset<Enum>::value>::type>
Urho3D::FlagSet<Enum> operator & (const Enum lhs, const Enum rhs)
{
    return Urho3D::FlagSet<Enum>(lhs) & rhs;
}

/// Bitwise Operator XOR for against Enum value.s
template <class Enum, class = typename std::enable_if<Urho3D::is_flagset<Enum>::value>::type>
Urho3D::FlagSet<Enum> operator ^ (const Enum lhs, const Enum rhs)
{
    return Urho3D::FlagSet<Enum>(lhs) ^ rhs;
}

/// Bitwise Operator RESET for against Enum value.s
template <class Enum, class = typename std::enable_if<Urho3D::is_flagset<Enum>::value>::type>
Urho3D::FlagSet<Enum> operator ~ (const Enum rhs)
{
    return (Enum)(~(typename std::underlying_type<Enum>::type)rhs);
}
