//
// Copyright (c) 2008-2015 the Urho3D project.
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

#include "../Math/Vector2.h"

namespace Urho3D
{

/// Three-dimensional vector.
class URHO3D_API Vector3
{
public:
    /// Construct a zero vector.
    Vector3() :
        x_(0.0f),
        y_(0.0f),
        z_(0.0f)
    {
    }

    /// Copy-construct from another vector.
    Vector3(const Vector3& vector) :
        x_(vector.x_),
        y_(vector.y_),
        z_(vector.z_)
    {
    }

    /// Construct from a two-dimensional vector and the Z coordinate.
    Vector3(const Vector2& vector, float z) :
        x_(vector.x_),
        y_(vector.y_),
        z_(z)
    {
    }

    /// Construct from a two-dimensional vector (for Urho2D).
    Vector3(const Vector2& vector) :
        x_(vector.x_),
        y_(vector.y_),
        z_(0.0f)
    {
    }

    /// Construct from coordinates.
    Vector3(float x, float y, float z) :
        x_(x),
        y_(y),
        z_(z)
    {
    }

    /// Construct from two-dimensional coordinates (for Urho2D).
    Vector3(float x, float y) :
        x_(x),
        y_(y),
        z_(0.0f)
    {
    }

    /// Construct from a float array.
    explicit Vector3(const float* data) :
        x_(data[0]),
        y_(data[1]),
        z_(data[2])
    {
    }

    /// Assign from another vector.
    Vector3& operator =(const Vector3& rhs)
    {
        x_ = rhs.x_;
        y_ = rhs.y_;
        z_ = rhs.z_;
        return *this;
    }

    /// Test for equality with another vector without epsilon.
    bool operator ==(const Vector3& rhs) const { return x_ == rhs.x_ && y_ == rhs.y_ && z_ == rhs.z_; }

    /// Test for inequality with another vector without epsilon.
    bool operator !=(const Vector3& rhs) const { return x_ != rhs.x_ || y_ != rhs.y_ || z_ != rhs.z_; }

    /// Add a vector.
    Vector3 operator +(const Vector3& rhs) const { return Vector3(x_ + rhs.x_, y_ + rhs.y_, z_ + rhs.z_); }

    /// Return negation.
    Vector3 operator -() const { return Vector3(-x_, -y_, -z_); }

    /// Subtract a vector.
    Vector3 operator -(const Vector3& rhs) const { return Vector3(x_ - rhs.x_, y_ - rhs.y_, z_ - rhs.z_); }

    /// Multiply with a scalar.
    Vector3 operator *(float rhs) const { return Vector3(x_ * rhs, y_ * rhs, z_ * rhs); }

    /// Multiply with a vector.
    Vector3 operator *(const Vector3& rhs) const { return Vector3(x_ * rhs.x_, y_ * rhs.y_, z_ * rhs.z_); }

    /// Divide by a scalar.
    Vector3 operator /(float rhs) const { return Vector3(x_ / rhs, y_ / rhs, z_ / rhs); }

    /// Divide by a vector.
    Vector3 operator /(const Vector3& rhs) const { return Vector3(x_ / rhs.x_, y_ / rhs.y_, z_ / rhs.z_); }

    /// Add-assign a vector.
    Vector3& operator +=(const Vector3& rhs)
    {
        x_ += rhs.x_;
        y_ += rhs.y_;
        z_ += rhs.z_;
        return *this;
    }

    /// Subtract-assign a vector.
    Vector3& operator -=(const Vector3& rhs)
    {
        x_ -= rhs.x_;
        y_ -= rhs.y_;
        z_ -= rhs.z_;
        return *this;
    }

    /// Multiply-assign a scalar.
    Vector3& operator *=(float rhs)
    {
        x_ *= rhs;
        y_ *= rhs;
        z_ *= rhs;
        return *this;
    }

    /// Multiply-assign a vector.
    Vector3& operator *=(const Vector3& rhs)
    {
        x_ *= rhs.x_;
        y_ *= rhs.y_;
        z_ *= rhs.z_;
        return *this;
    }

    /// Divide-assign a scalar.
    Vector3& operator /=(float rhs)
    {
        float invRhs = 1.0f / rhs;
        x_ *= invRhs;
        y_ *= invRhs;
        z_ *= invRhs;
        return *this;
    }

    /// Divide-assign a vector.
    Vector3& operator /=(const Vector3& rhs)
    {
        x_ /= rhs.x_;
        y_ /= rhs.y_;
        z_ /= rhs.z_;
        return *this;
    }

    /// Normalize to unit length.
    void Normalize()
    {
        float lenSquared = LengthSquared();
        if (!Urho3D::Equals(lenSquared, 1.0f) && lenSquared > 0.0f)
        {
            float invLen = 1.0f / sqrtf(lenSquared);
            x_ *= invLen;
            y_ *= invLen;
            z_ *= invLen;
        }
    }

    /// Return length.
    float Length() const { return sqrtf(x_ * x_ + y_ * y_ + z_ * z_); }

    /// Return squared length.
    float LengthSquared() const { return x_ * x_ + y_ * y_ + z_ * z_; }

    /// Calculate dot product.
    float DotProduct(const Vector3& rhs) const { return x_ * rhs.x_ + y_ * rhs.y_ + z_ * rhs.z_; }

    /// Calculate absolute dot product.
    float AbsDotProduct(const Vector3& rhs) const
    {
        return Urho3D::Abs(x_ * rhs.x_) + Urho3D::Abs(y_ * rhs.y_) + Urho3D::Abs(z_ * rhs.z_);
    }

    /// Calculate cross product.
    Vector3 CrossProduct(const Vector3& rhs) const
    {
        return Vector3(
            y_ * rhs.z_ - z_ * rhs.y_,
            z_ * rhs.x_ - x_ * rhs.z_,
            x_ * rhs.y_ - y_ * rhs.x_
        );
    }

    /// Return absolute vector.
    Vector3 Abs() const { return Vector3(Urho3D::Abs(x_), Urho3D::Abs(y_), Urho3D::Abs(z_)); }

    /// Linear interpolation with another vector.
    Vector3 Lerp(const Vector3& rhs, float t) const { return *this * (1.0f - t) + rhs * t; }

    /// Test for equality with another vector with epsilon.
    bool Equals(const Vector3& rhs) const
    {
        return Urho3D::Equals(x_, rhs.x_) && Urho3D::Equals(y_, rhs.y_) && Urho3D::Equals(z_, rhs.z_);
    }

    /// Returns the angle between this vector and another vector in degrees.
    float Angle(const Vector3& rhs) const { return Urho3D::Acos(DotProduct(rhs) / (Length() * rhs.Length())); }

    /// Return whether is NaN.
    bool IsNaN() const { return Urho3D::IsNaN(x_) || Urho3D::IsNaN(y_) || Urho3D::IsNaN(z_); }

    /// Return normalized to unit length.
    Vector3 Normalized() const
    {
        float lenSquared = LengthSquared();
        if (!Urho3D::Equals(lenSquared, 1.0f) && lenSquared > 0.0f)
        {
            float invLen = 1.0f / sqrtf(lenSquared);
            return *this * invLen;
        }
        else
            return *this;
    }

    /// Return float data.
    const float* Data() const { return &x_; }

    /// Return as string.
    String ToString() const;

    /// X coordinate.
    float x_;
    /// Y coordinate.
    float y_;
    /// Z coordinate.
    float z_;

    /// Zero vector.
    static const Vector3 ZERO;
    /// (-1,0,0) vector.
    static const Vector3 LEFT;
    /// (1,0,0) vector.
    static const Vector3 RIGHT;
    /// (0,1,0) vector.
    static const Vector3 UP;
    /// (0,-1,0) vector.
    static const Vector3 DOWN;
    /// (0,0,1) vector.
    static const Vector3 FORWARD;
    /// (0,0,-1) vector.
    static const Vector3 BACK;
    /// (1,1,1) vector.
    static const Vector3 ONE;
};

/// Multiply Vector3 with a scalar.
inline Vector3 operator *(float lhs, const Vector3& rhs) { return rhs * lhs; }

}
