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
#include "../Math/Vector3.h"

namespace Urho3D
{

/// Four-dimensional vector.
template<typename T>
class URHO3D_API BaseVector4
{
public:
    /// Construct a zero vector.
    BaseVector4() :
        x_(0),
        y_(0),
        z_(0),
        w_(0)
    {
    }

    /// Copy-construct from another vector.
    BaseVector4(const BaseVector4& vector) :
        x_(vector.x_),
        y_(vector.y_),
        z_(vector.z_),
        w_(vector.w_)
    {
    }

    /// Construct from a 3-dimensional vector and the W coordinate.
    BaseVector4(const Vector3& vector, T w) :
        x_(vector.x_),
        y_(vector.y_),
        z_(vector.z_),
        w_(w)
    {
    }

    /// Construct from coordinates.
    BaseVector4(T x, T y, T z, T w) :
        x_(x),
        y_(y),
        z_(z),
        w_(w)
    {
    }

    /// Construct from a number array.
    template<typename T2>
    explicit BaseVector4(const T2* data) :
        x_(data[0]),
        y_(data[1]),
        z_(data[2]),
        w_(data[3])
    {
        static_assert(std::is_arithmetic<T>::value, "Parameter must be array of arithmetic type.");
    }

    /// Assign from another vector.
    BaseVector4& operator =(const BaseVector4& rhs)
    {
        x_ = rhs.x_;
        y_ = rhs.y_;
        z_ = rhs.z_;
        w_ = rhs.w_;
        return *this;
    }

    /// Test for equality with another vector without epsilon.
    bool operator ==(const BaseVector4& rhs) const { return x_ == rhs.x_ && y_ == rhs.y_ && z_ == rhs.z_ && w_ == rhs.w_; }

    /// Test for inequality with another vector without epsilon.
    bool operator !=(const BaseVector4& rhs) const { return x_ != rhs.x_ || y_ != rhs.y_ || z_ != rhs.z_ || w_ != rhs.w_; }

    /// Add a vector.
    BaseVector4 operator +(const BaseVector4& rhs) const { return BaseVector4(x_ + rhs.x_, y_ + rhs.y_, z_ + rhs.z_, w_ + rhs.w_); }

    /// Return negation.
    BaseVector4 operator -() const { return BaseVector4(-x_, -y_, -z_, -w_); }

    /// Subtract a vector.
    BaseVector4 operator -(const BaseVector4& rhs) const { return BaseVector4(x_ - rhs.x_, y_ - rhs.y_, z_ - rhs.z_, w_ - rhs.w_); }

    /// Multiply with a scalar.
    BaseVector4 operator *(T rhs) const { return BaseVector4(x_ * rhs, y_ * rhs, z_ * rhs, w_ * rhs); }

    /// Multiply with a vector.
    BaseVector4 operator *(const BaseVector4& rhs) const { return BaseVector4(x_ * rhs.x_, y_ * rhs.y_, z_ * rhs.z_, w_ * rhs.w_); }

    /// Divide by a scalar.
    BaseVector4 operator /(T rhs) const { return BaseVector4(x_ / rhs, y_ / rhs, z_ / rhs, w_ / rhs); }

    /// Divide by a vector.
    BaseVector4 operator /(const BaseVector4& rhs) const { return BaseVector4(x_ / rhs.x_, y_ / rhs.y_, z_ / rhs.z_, w_ / rhs.w_); }

    /// Add-assign a vector.
    BaseVector4& operator +=(const BaseVector4& rhs)
    {
        x_ += rhs.x_;
        y_ += rhs.y_;
        z_ += rhs.z_;
        w_ += rhs.w_;
        return *this;
    }

    /// Subtract-assign a vector.
    BaseVector4& operator -=(const BaseVector4& rhs)
    {
        x_ -= rhs.x_;
        y_ -= rhs.y_;
        z_ -= rhs.z_;
        w_ -= rhs.w_;
        return *this;
    }

    /// Multiply-assign a scalar.
    BaseVector4& operator *=(T rhs)
    {
        x_ *= rhs;
        y_ *= rhs;
        z_ *= rhs;
        w_ *= rhs;
        return *this;
    }

    /// Multiply-assign a vector.
    BaseVector4& operator *=(const BaseVector4& rhs)
    {
        x_ *= rhs.x_;
        y_ *= rhs.y_;
        z_ *= rhs.z_;
        w_ *= rhs.w_;
        return *this;
    }

    /// Divide-assign a scalar.
    BaseVector4& operator /=(T rhs)
    {
        T invRhs = (T)(typename ScalarTypeSelector<T>::Type(1.0) / rhs);
        x_ *= invRhs;
        y_ *= invRhs;
        z_ *= invRhs;
        w_ *= invRhs;
        return *this;
    }

    /// Divide-assign a vector.
    BaseVector4& operator /=(const BaseVector4& rhs)
    {
        x_ /= rhs.x_;
        y_ /= rhs.y_;
        z_ /= rhs.z_;
        w_ /= rhs.w_;
        return *this;
    }

    /// Calculate dot product.
    T DotProduct(const BaseVector4& rhs) const { return x_ * rhs.x_ + y_ * rhs.y_ + z_ * rhs.z_ + w_ * rhs.w_; }

    /// Calculate absolute dot product.
    T AbsDotProduct(const BaseVector4& rhs) const
    {
        return Urho3D::Abs(x_ * rhs.x_) + Urho3D::Abs(y_ * rhs.y_) + Urho3D::Abs(z_ * rhs.z_) + Urho3D::Abs(w_ * rhs.w_);
    }

    /// Project vector onto axis.
    T ProjectOntoAxis(const Vector3& axis) const { return DotProduct(BaseVector4(axis.Normalized(), 0.0f)); }

    /// Return absolute vector.
    BaseVector4 Abs() const { return BaseVector4(Urho3D::Abs(x_), Urho3D::Abs(y_), Urho3D::Abs(z_), Urho3D::Abs(w_)); }

    /// Linear interpolation with another vector.
    BaseVector4 Lerp(const BaseVector4& rhs, T t) const { return *this * (typename ScalarTypeSelector<T>::Type(1.0) - t) + rhs * t; }

    /// Test for equality with another vector with epsilon.
    bool Equals(const BaseVector4& rhs) const
    {
        return Urho3D::Equals(x_, rhs.x_) && Urho3D::Equals(y_, rhs.y_) && Urho3D::Equals(z_, rhs.z_) && Urho3D::Equals(w_, rhs.w_);
    }

    /// Return whether is NaN.
    bool IsNaN() const { return Urho3D::IsNaN(x_) || Urho3D::IsNaN(y_) || Urho3D::IsNaN(z_) || Urho3D::IsNaN(w_); }

    /// Return number data.
    const T* Data() const { return &x_; }

    /// Return as string.
    String ToString() const;

    /// X coordinate.
    T x_;
    /// Y coordinate.
    T y_;
    /// Z coordinate.
    T z_;
    /// W coordinate.
    T w_;

    /// Zero vector.
    static const BaseVector4 ZERO;
    /// (1,1,1) vector.
    static const BaseVector4 ONE;
};

typedef BaseVector4<float> Vector4;
typedef BaseVector4<int> IntVector4;

template class URHO3D_API BaseVector4<float>;
template class URHO3D_API BaseVector4<int>;

/// Multiply Vector4 with a scalar.
template<typename T> inline BaseVector4<T> operator *(T lhs, const BaseVector4<T>& rhs) { return rhs * lhs; }

/// Per-component linear interpolation between two 4-vectors.
template<typename T> inline BaseVector4<T> VectorLerp(const BaseVector4<T>& lhs, const BaseVector4<T>& rhs, const BaseVector4<T>& t) { return lhs + (rhs - lhs) * t; }

/// Per-component min of two 4-vectors.
template<typename T> inline BaseVector4<T> VectorMin(const BaseVector4<T>& lhs, const BaseVector4<T>& rhs) { return BaseVector4<T>(Min(lhs.x_, rhs.x_), Min(lhs.y_, rhs.y_), Min(lhs.z_, rhs.z_), Min(lhs.w_, rhs.w_)); }

/// Per-component max of two 4-vectors.
template<typename T> inline BaseVector4<T> VectorMax(const BaseVector4<T>& lhs, const BaseVector4<T>& rhs) { return BaseVector4<T>(Max(lhs.x_, rhs.x_), Max(lhs.y_, rhs.y_), Max(lhs.z_, rhs.z_), Max(lhs.w_, rhs.w_)); }

/// Per-component floor of 4-vector.
template<typename T> inline BaseVector4<T> VectorFloor(const BaseVector4<T>& vec) { return BaseVector4<T>(Floor(vec.x_), Floor(vec.y_), Floor(vec.z_), Floor(vec.w_)); }

/// Per-component round of 4-vector.
template<typename T> inline BaseVector4<T> VectorRound(const BaseVector4<T>& vec) { return BaseVector4<T>(Round(vec.x_), Round(vec.y_), Round(vec.z_), Round(vec.w_)); }

/// Per-component ceil of 4-vector.
template<typename T> inline BaseVector4<T> VectorCeil(const BaseVector4<T>& vec) { return BaseVector4<T>(Ceil(vec.x_), Ceil(vec.y_), Ceil(vec.z_), Ceil(vec.w_)); }

}
