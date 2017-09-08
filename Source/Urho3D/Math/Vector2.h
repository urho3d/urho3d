//
// Copyright (c) 2008-2017 the Urho3D project.
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
#include "../Container/Str.h"
#include "../Math/MathDefs.h"

namespace Urho3D
{

/// Two-dimensional vector.
template<typename T>
class URHO3D_API BaseVector2
{
public:
    /// Construct a zero vector.
    BaseVector2() :
        x_(0),
        y_(0)
    {
    }

    /// Copy-construct from another vector.
    BaseVector2(const BaseVector2& vector) :
        x_(vector.x_),
        y_(vector.y_)
    {
    }

    /// Copy-construct from another vector.
    template<typename T2>
    explicit BaseVector2(const BaseVector2<T2>& vector) :
        x_((T)vector.x_),
        y_((T)vector.y_)
    {
        static_assert(std::is_arithmetic<T>::value, "Parameter must be array of arithmetic type.");
    }

    /// Construct from coordinates.
    BaseVector2(T x, T y) :
        x_(x),
        y_(y)
    {
    }

    /// Construct from a number array.
    template<typename T2>
    explicit BaseVector2(const T2* data) :
        x_(data[0]),
        y_(data[1])
    {
    }

    /// Assign from another vector.
    BaseVector2& operator =(const BaseVector2& rhs)
    {
        x_ = rhs.x_;
        y_ = rhs.y_;
        return *this;
    }

    /// Test for equality with another vector without epsilon.
    bool operator ==(const BaseVector2& rhs) const { return x_ == rhs.x_ && y_ == rhs.y_; }

    /// Test for inequality with another vector without epsilon.
    bool operator !=(const BaseVector2& rhs) const { return x_ != rhs.x_ || y_ != rhs.y_; }

    /// Add a vector.
    BaseVector2 operator +(const BaseVector2& rhs) const { return BaseVector2(x_ + rhs.x_, y_ + rhs.y_); }

    /// Return negation.
    BaseVector2 operator -() const { return BaseVector2(-x_, -y_); }

    /// Subtract a vector.
    BaseVector2 operator -(const BaseVector2& rhs) const { return BaseVector2(x_ - rhs.x_, y_ - rhs.y_); }

    /// Multiply with a scalar.
    BaseVector2 operator *(T rhs) const { return BaseVector2(x_ * rhs, y_ * rhs); }

    /// Multiply with a vector.
    BaseVector2 operator *(const BaseVector2& rhs) const { return BaseVector2(x_ * rhs.x_, y_ * rhs.y_); }

    /// Divide by a scalar.
    BaseVector2 operator /(T rhs) const { return BaseVector2(x_ / rhs, y_ / rhs); }

    /// Divide by a vector.
    BaseVector2 operator /(const BaseVector2& rhs) const { return BaseVector2(x_ / rhs.x_, y_ / rhs.y_); }

    /// Add-assign a vector.
    BaseVector2& operator +=(const BaseVector2& rhs)
    {
        x_ += rhs.x_;
        y_ += rhs.y_;
        return *this;
    }

    /// Subtract-assign a vector.
    BaseVector2& operator -=(const BaseVector2& rhs)
    {
        x_ -= rhs.x_;
        y_ -= rhs.y_;
        return *this;
    }

    /// Multiply-assign a scalar.
    BaseVector2& operator *=(T rhs)
    {
        x_ *= rhs;
        y_ *= rhs;
        return *this;
    }

    /// Multiply-assign a vector.
    BaseVector2& operator *=(const BaseVector2& rhs)
    {
        x_ *= rhs.x_;
        y_ *= rhs.y_;
        return *this;
    }

    /// Divide-assign a scalar.
    BaseVector2& operator /=(T rhs)
    {
        T invRhs = typename ScalarTypeSelector<T>::Type(1.0) / rhs;
        x_ *= invRhs;
        y_ *= invRhs;
        return *this;
    }

    /// Divide-assign a vector.
    BaseVector2& operator /=(const BaseVector2& rhs)
    {
        x_ /= rhs.x_;
        y_ /= rhs.y_;
        return *this;
    }

    /// Normalize to unit length.
    void Normalize()
    {
        T lenSquared = LengthSquared();
        if (!Urho3D::Equals(lenSquared, (T)1) && lenSquared > (T)0)
        {
            T invLen = typename ScalarTypeSelector<T>::Type(1.0) / sqrtf(lenSquared);
            x_ *= invLen;
            y_ *= invLen;
        }
    }

    /// Return length.
    T Length() const { return sqrtf(x_ * x_ + y_ * y_); }

    /// Return squared length.
    T LengthSquared() const { return x_ * x_ + y_ * y_; }

    /// Calculate dot product.
    T DotProduct(const BaseVector2& rhs) const { return x_ * rhs.x_ + y_ * rhs.y_; }

    /// Calculate absolute dot product.
    T AbsDotProduct(const BaseVector2& rhs) const { return Urho3D::Abs(x_ * rhs.x_) + Urho3D::Abs(y_ * rhs.y_); }

    /// Project vector onto axis.
    T ProjectOntoAxis(const BaseVector2& axis) const { return DotProduct(axis.Normalized()); }

    /// Returns the angle between this vector and another vector in degrees.
    T Angle(const BaseVector2& rhs) const { return Urho3D::Acos(DotProduct(rhs) / (Length() * rhs.Length())); }

    /// Return absolute vector.
    BaseVector2 Abs() const { return BaseVector2(Urho3D::Abs(x_), Urho3D::Abs(y_)); }

    /// Linear interpolation with another vector.
    BaseVector2 Lerp(const BaseVector2& rhs, T t) const { return *this * (typename ScalarTypeSelector<T>::Type(1.0) - t) + rhs * t; }

    /// Test for equality with another vector with epsilon.
    bool Equals(const BaseVector2& rhs) const { return Urho3D::Equals(x_, rhs.x_) && Urho3D::Equals(y_, rhs.y_); }

    /// Return whether is NaN.
    bool IsNaN() const { return Urho3D::IsNaN(x_) || Urho3D::IsNaN(y_); }

    /// Return normalized to unit length.
    BaseVector2 Normalized() const
    {
        T lenSquared = LengthSquared();
        if (!Urho3D::Equals(lenSquared, (T)1) && lenSquared > 0)
        {
            T invLen = typename ScalarTypeSelector<T>::Type(1.0) / sqrtf(lenSquared);
            return *this * invLen;
        }
        else
            return *this;
    }

    /// Return data array.
    const T* Data() const { return &x_; }

    /// Return as string.
    String ToString() const;

    /// Return hash value for HashSet & HashMap.
    unsigned ToHash() const { return (unsigned)(x_ * 31 + y_); }

    /// X coordinate.
    T x_;
    /// Y coordinate.
    T y_;

    /// Zero vector.
    static const BaseVector2<T> ZERO;
    /// (-1,0) vector.
    static const BaseVector2<T> LEFT;
    /// (1,0) vector.
    static const BaseVector2<T> RIGHT;
    /// (0,1) vector.
    static const BaseVector2<T> UP;
    /// (0,-1) vector.
    static const BaseVector2<T> DOWN;
    /// (1,1) vector.
    static const BaseVector2<T> ONE;
};

typedef BaseVector2<float> Vector2;
typedef BaseVector2<int> IntVector2;

template class URHO3D_API BaseVector2<float>;
template class URHO3D_API BaseVector2<int>;

/// Multiply Vector2 with a scalar
template<typename T> inline BaseVector2<T> operator *(T lhs, const BaseVector2<T>& rhs) { return rhs * lhs; }

/// Multiply-asign Vector2 with a scalar
template<typename T> inline BaseVector2<T> operator *=(T lhs, const BaseVector2<T>& rhs) { return rhs * lhs; }

/// Per-component linear interpolation between two 2-vectors.
template<typename T> inline BaseVector2<T> VectorLerp(const BaseVector2<T>& lhs, const BaseVector2<T>& rhs, const BaseVector2<T>& t) { return lhs + (rhs - lhs) * t; }

/// Per-component min of two 2-vectors.
template<typename T> inline BaseVector2<T> VectorMin(const BaseVector2<T>& lhs, const BaseVector2<T>& rhs) { return BaseVector2<T>(Min(lhs.x_, rhs.x_), Min(lhs.y_, rhs.y_)); }

/// Per-component max of two 2-vectors.
template<typename T> inline BaseVector2<T> VectorMax(const BaseVector2<T>& lhs, const BaseVector2<T>& rhs) { return BaseVector2<T>(Max(lhs.x_, rhs.x_), Max(lhs.y_, rhs.y_)); }

/// Per-component floor of 2-vector.
template<typename T> inline BaseVector2<T> VectorFloor(const BaseVector2<T>& vec) { return BaseVector2<T>(Floor(vec.x_), Floor(vec.y_)); }

/// Per-component round of 2-vector.
template<typename T> inline BaseVector2<T> VectorRound(const BaseVector2<T>& vec) { return BaseVector2<T>(Round(vec.x_), Round(vec.y_)); }

/// Per-component ceil of 2-vector.
template<typename T> inline BaseVector2<T> VectorCeil(const BaseVector2<T>& vec) { return BaseVector2<T>(Ceil(vec.x_), Ceil(vec.y_)); }

/// Per-component floor of 2-vector. Returns IntVector2.
inline IntVector2 VectorFloorToInt(const Vector2& vec) { return IntVector2(FloorToInt(vec.x_), FloorToInt(vec.y_)); }

/// Per-component round of 2-vector. Returns IntVector2.
inline IntVector2 VectorRoundToInt(const Vector2& vec) { return IntVector2(RoundToInt(vec.x_), RoundToInt(vec.y_)); }

/// Per-component ceil of 2-vector. Returns IntVector2.
inline IntVector2 VectorCeilToInt(const Vector2& vec) { return IntVector2(CeilToInt(vec.x_), CeilToInt(vec.y_)); }

/// Return a random value from [0, 1) from 2-vector seed.
/// http://stackoverflow.com/questions/12964279/whats-the-origin-of-this-glsl-rand-one-liner
inline float StableRandom(const Vector2& seed) { return Fract(Sin(seed.DotProduct(Vector2(12.9898f, 78.233f)) * M_RADTODEG) * 43758.5453f); }

/// Return a random value from [0, 1) from scalar seed.
inline float StableRandom(float seed) { return StableRandom(Vector2(seed, seed)); }

}
