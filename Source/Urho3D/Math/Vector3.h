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
#include "../Math/Vector2.h"
#include "../Math/MathDefs.h"

namespace Urho3D
{

/// Three-dimensional vector.
template<typename T>
class URHO3D_API BaseVector3
{
public:
    /// Construct a zero vector.
    BaseVector3() :
        x_(0.0f),
        y_(0.0f),
        z_(0.0f)
    {
    }

    /// Copy-construct from another vector.
    BaseVector3(const BaseVector3& vector) :
        x_(vector.x_),
        y_(vector.y_),
        z_(vector.z_)
    {
    }

    /// Construct from a two-dimensional vector and the Z coordinate.
    BaseVector3(const BaseVector2<T>& vector, T z) :
        x_(vector.x_),
        y_(vector.y_),
        z_(z)
    {
    }

    /// Construct from a two-dimensional vector (for Urho2D).
    BaseVector3(const BaseVector2<T>& vector) :
        x_(vector.x_),
        y_(vector.y_),
        z_(0.0f)
    {
    }

    /// Construct from another Vector3.
    template<typename T2>
    explicit BaseVector3(const BaseVector3<T2>& vector) :
        x_((T)vector.x_),
        y_((T)vector.y_),
        z_((T)vector.z_)
    {
        static_assert(std::is_arithmetic<T>::value, "Parameter must be array of arithmetic type.");
    }

    /// Construct from coordinates.
    BaseVector3(T x, T y, T z) :
        x_(x),
        y_(y),
        z_(z)
    {
    }

    /// Construct from two-dimensional coordinates (for Urho2D).
    BaseVector3(T x, T y) :
        x_(x),
        y_(y),
        z_(0.0f)
    {
    }

    /// Construct from a number array.
    template<typename T2>
    explicit BaseVector3(const T2* data) :
        x_(data[0]),
        y_(data[1]),
        z_(data[2])
    {
    }

    /// Assign from another vector.
    BaseVector3& operator =(const BaseVector3& rhs)
    {
        x_ = rhs.x_;
        y_ = rhs.y_;
        z_ = rhs.z_;
        return *this;
    }

    /// Test for equality with another vector without epsilon.
    bool operator ==(const BaseVector3& rhs) const { return x_ == rhs.x_ && y_ == rhs.y_ && z_ == rhs.z_; }

    /// Test for inequality with another vector without epsilon.
    bool operator !=(const BaseVector3& rhs) const { return x_ != rhs.x_ || y_ != rhs.y_ || z_ != rhs.z_; }

    /// Add a vector.
    BaseVector3 operator +(const BaseVector3& rhs) const { return BaseVector3(x_ + rhs.x_, y_ + rhs.y_, z_ + rhs.z_); }

    /// Return negation.
    BaseVector3 operator -() const { return BaseVector3(-x_, -y_, -z_); }

    /// Subtract a vector.
    BaseVector3 operator -(const BaseVector3& rhs) const { return BaseVector3(x_ - rhs.x_, y_ - rhs.y_, z_ - rhs.z_); }

    /// Multiply with a scalar.
    BaseVector3 operator *(T rhs) const { return BaseVector3(x_ * rhs, y_ * rhs, z_ * rhs); }

    /// Multiply with a vector.
    BaseVector3 operator *(const BaseVector3& rhs) const { return BaseVector3(x_ * rhs.x_, y_ * rhs.y_, z_ * rhs.z_); }

    /// Divide by a scalar.
    BaseVector3 operator /(T rhs) const { return BaseVector3(x_ / rhs, y_ / rhs, z_ / rhs); }

    /// Divide by a vector.
    BaseVector3 operator /(const BaseVector3& rhs) const { return BaseVector3(x_ / rhs.x_, y_ / rhs.y_, z_ / rhs.z_); }

    /// Add-assign a vector.
    BaseVector3& operator +=(const BaseVector3& rhs)
    {
        x_ += rhs.x_;
        y_ += rhs.y_;
        z_ += rhs.z_;
        return *this;
    }

    /// Subtract-assign a vector.
    BaseVector3& operator -=(const BaseVector3& rhs)
    {
        x_ -= rhs.x_;
        y_ -= rhs.y_;
        z_ -= rhs.z_;
        return *this;
    }

    /// Multiply-assign a scalar.
    BaseVector3& operator *=(T rhs)
    {
        x_ *= rhs;
        y_ *= rhs;
        z_ *= rhs;
        return *this;
    }

    /// Multiply-assign a vector.
    BaseVector3& operator *=(const BaseVector3& rhs)
    {
        x_ *= rhs.x_;
        y_ *= rhs.y_;
        z_ *= rhs.z_;
        return *this;
    }

    /// Divide-assign a scalar.
    BaseVector3& operator /=(T rhs)
    {
        T invRhs = typename ScalarTypeSelector<T>::Type(1.0) / rhs;
        x_ *= invRhs;
        y_ *= invRhs;
        z_ *= invRhs;
        return *this;
    }

    /// Divide-assign a vector.
    BaseVector3& operator /=(const BaseVector3& rhs)
    {
        x_ /= rhs.x_;
        y_ /= rhs.y_;
        z_ /= rhs.z_;
        return *this;
    }

    /// Normalize to unit length.
    void Normalize()
    {
        T lenSquared = LengthSquared();
        if (!Urho3D::Equals(lenSquared, (T)1) && lenSquared > 0)
        {
            T invLen = typename ScalarTypeSelector<T>::Type(1.0) / sqrtf(lenSquared);
            x_ *= invLen;
            y_ *= invLen;
            z_ *= invLen;
        }
    }

    /// Return length.
    T Length() const { return sqrtf(x_ * x_ + y_ * y_ + z_ * z_); }

    /// Return squared length.
    T LengthSquared() const { return x_ * x_ + y_ * y_ + z_ * z_; }

    /// Calculate dot product.
    T DotProduct(const BaseVector3& rhs) const { return x_ * rhs.x_ + y_ * rhs.y_ + z_ * rhs.z_; }

    /// Calculate absolute dot product.
    T AbsDotProduct(const BaseVector3& rhs) const
    {
        return Urho3D::Abs(x_ * rhs.x_) + Urho3D::Abs(y_ * rhs.y_) + Urho3D::Abs(z_ * rhs.z_);
    }

    /// Project vector onto axis.
    T ProjectOntoAxis(const BaseVector3& axis) const { return DotProduct(axis.Normalized()); }

    /// Make vector orthogonal to the axis.
    BaseVector3 Orthogonalize(const BaseVector3& axis) const { return axis.CrossProduct(*this).CrossProduct(axis).Normalized(); }

    /// Calculate cross product.
    BaseVector3 CrossProduct(const BaseVector3& rhs) const
    {
        return BaseVector3(
            y_ * rhs.z_ - z_ * rhs.y_,
            z_ * rhs.x_ - x_ * rhs.z_,
            x_ * rhs.y_ - y_ * rhs.x_
        );
    }

    /// Return absolute vector.
    BaseVector3 Abs() const { return BaseVector3(Urho3D::Abs(x_), Urho3D::Abs(y_), Urho3D::Abs(z_)); }

    /// Linear interpolation with another vector.
    BaseVector3 Lerp(const BaseVector3& rhs, T t) const { return *this * (typename ScalarTypeSelector<T>::Type(1.0) - t) + rhs * t; }

    /// Test for equality with another vector with epsilon.
    bool Equals(const BaseVector3& rhs) const
    {
        return Urho3D::Equals(x_, rhs.x_) && Urho3D::Equals(y_, rhs.y_) && Urho3D::Equals(z_, rhs.z_);
    }

    /// Returns the angle between this vector and another vector in degrees.
    T Angle(const BaseVector3& rhs) const { return Urho3D::Acos(DotProduct(rhs) / (Length() * rhs.Length())); }

    /// Return whether is NaN.
    bool IsNaN() const { return Urho3D::IsNaN(x_) || Urho3D::IsNaN(y_) || Urho3D::IsNaN(z_); }

    /// Return normalized to unit length.
    BaseVector3 Normalized() const
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
    unsigned ToHash() const
    {
        unsigned hash = 37;
        hash = 37 + (x_ * hash);
        hash = 37 + (y_ * hash);
        hash = 37 + (z_ * hash);
        return hash;
    }

    /// X coordinate.
    T x_;
    /// Y coordinate.
    T y_;
    /// Z coordinate.
    T z_;

    /// Zero vector.
    static const BaseVector3 ZERO;
    /// (-1,0,0) vector.
    static const BaseVector3 LEFT;
    /// (1,0,0) vector.
    static const BaseVector3 RIGHT;
    /// (0,1,0) vector.
    static const BaseVector3 UP;
    /// (0,-1,0) vector.
    static const BaseVector3 DOWN;
    /// (0,0,1) vector.
    static const BaseVector3 FORWARD;
    /// (0,0,-1) vector.
    static const BaseVector3 BACK;
    /// (1,1,1) vector.
    static const BaseVector3 ONE;
};

typedef BaseVector3<float> Vector3;
typedef BaseVector3<int> IntVector3;

template class URHO3D_API BaseVector3<float>;
template class URHO3D_API BaseVector3<int>;

/// Multiply Vector3 with a scalar.
template<typename T> inline BaseVector3<T> operator *(float lhs, const BaseVector3<T>& rhs) { return rhs * lhs; }

/// Per-component linear interpolation between two 3-vectors.
template<typename T> inline BaseVector3<T> VectorLerp(const BaseVector3<T>& lhs, const BaseVector3<T>& rhs, const BaseVector3<T>& t) { return lhs + (rhs - lhs) * t; }

/// Per-component min of two 3-vectors.
template<typename T> inline BaseVector3<T> VectorMin(const BaseVector3<T>& lhs, const BaseVector3<T>& rhs) { return BaseVector3<T>(Min(lhs.x_, rhs.x_), Min(lhs.y_, rhs.y_), Min(lhs.z_, rhs.z_)); }

/// Per-component max of two 3-vectors.
template<typename T> inline BaseVector3<T> VectorMax(const BaseVector3<T>& lhs, const BaseVector3<T>& rhs) { return BaseVector3<T>(Max(lhs.x_, rhs.x_), Max(lhs.y_, rhs.y_), Max(lhs.z_, rhs.z_)); }

/// Per-component floor of 3-vector.
template<typename T> inline BaseVector3<T> VectorFloor(const BaseVector3<T>& vec) { return BaseVector3<T>(Floor(vec.x_), Floor(vec.y_), Floor(vec.z_)); }

/// Per-component round of 3-vector.
template<typename T> inline BaseVector3<T> VectorRound(const BaseVector3<T>& vec) { return BaseVector3<T>(Round(vec.x_), Round(vec.y_), Round(vec.z_)); }

/// Per-component ceil of 3-vector.
template<typename T> inline BaseVector3<T> VectorCeil(const BaseVector3<T>& vec) { return BaseVector3<T>(Ceil(vec.x_), Ceil(vec.y_), Ceil(vec.z_)); }

/// Per-component floor of 3-vector. Returns IntVector3.
inline IntVector3 VectorFloorToInt(const Vector3& vec) { return IntVector3(FloorToInt(vec.x_), FloorToInt(vec.y_), FloorToInt(vec.z_)); }

/// Per-component round of 3-vector. Returns IntVector3.
inline IntVector3 VectorRoundToInt(const Vector3& vec) { return IntVector3(RoundToInt(vec.x_), RoundToInt(vec.y_), RoundToInt(vec.z_)); }

/// Per-component ceil of 3-vector. Returns IntVector3.
inline IntVector3 VectorCeilToInt(const Vector3& vec) { return IntVector3(CeilToInt(vec.x_), CeilToInt(vec.y_), CeilToInt(vec.z_)); }

/// Return a random value from [0, 1) from 3-vector seed.
inline float StableRandom(const Vector3& seed) { return StableRandom(Vector2(StableRandom(Vector2(seed.x_, seed.y_)), seed.z_)); }

}
