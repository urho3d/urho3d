//
// Urho3D Engine
// Copyright (c) 2008-2011 Lasse Öörni
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

#include "Vector2.h"

/// Three-dimensional vector
class Vector3
{
public:
    /// Construct an undefined vector
    Vector3()
    {
    }
    
    /// Copy-construct from another vector
    Vector3(const Vector3& vector) :
        x_(vector.x_),
        y_(vector.y_),
        z_(vector.z_)
    {
    }
    
    /// Construct from a two-dimensional vector and the Z coordinate
    Vector3(const Vector2& vector, float z) :
        x_(vector.x_),
        y_(vector.y_),
        z_(z)
    {
    }
    
    /// Construct from coordinates
    Vector3(float x, float y, float z) :
        x_(x),
        y_(y),
        z_(z)
    {
    }
    
    /// Construct from a float array
    Vector3(const float* data) :
        x_(data[0]),
        y_(data[1]),
        z_(data[2])
    {
    }
    
    /// Assign from another vector
    Vector3& operator = (const Vector3& rhs)
    {
        x_ = rhs.x_;
        y_ = rhs.y_;
        z_ = rhs.z_;
        
        return *this;
    }
    
    /// Test for equality with another vector
    bool operator == (const Vector3& rhs) const { return Equals(x_, rhs.x_) && Equals(y_, rhs.y_) && Equals(z_, rhs.z_); }
    /// Test for inequality with another vector
    bool operator != (const Vector3& rhs) const { return (!Equals(x_, rhs.x_)) || (!Equals(y_, rhs.y_)) || (!Equals(z_, rhs.z_)); }
    /// Add a vector
    Vector3 operator + (const Vector3& rhs) const { return Vector3(x_ + rhs.x_, y_ + rhs.y_, z_ + rhs.z_); }
    /// Return negation
    Vector3 operator - () const { return Vector3(-x_, -y_, -z_); }
    /// Subtract a vector
    Vector3 operator - (const Vector3& rhs) const { return Vector3(x_ - rhs.x_, y_ - rhs.y_, z_ - rhs.z_); }
    /// Multiply with a scalar
    Vector3 operator * (float rhs) const { return Vector3(x_ * rhs, y_ * rhs, z_ * rhs); }
    /// Multiply with a vector
    Vector3 operator * (const Vector3& rhs) const { return Vector3(x_ * rhs.x_, y_ * rhs.y_, z_ * rhs.z_); }
    /// Divide by a scalar
    Vector3 operator / (float rhs) const { return Vector3(x_ / rhs, y_ / rhs, z_ / rhs); }
    /// Divide by a vector
    Vector3 operator / (const Vector3& rhs) const { return Vector3(x_ / rhs.x_, y_ / rhs.y_, z_ / rhs.z_); }
    
    /// Add-assign a vector
    Vector3& operator += (const Vector3& rhs)
    {
        x_ += rhs.x_;
        y_ += rhs.y_;
        z_ += rhs.z_;
        
        return *this;
    }
    
    /// Subtract-assign a vector
    Vector3& operator -= (const Vector3& rhs)
    {
        x_ -= rhs.x_;
        y_ -= rhs.y_;
        z_ -= rhs.z_;
        
        return *this;
    }
    
    /// Multiply-assign a scalar
    Vector3& operator *= (float rhs)
    {
        x_ *= rhs;
        y_ *= rhs;
        z_ *= rhs;
        
        return *this;
    }
    
    /// Multiply-assign a vector
    Vector3& operator *= (const Vector3& rhs)
    {
        x_ *= rhs.x_;
        y_ *= rhs.y_;
        z_ *= rhs.z_;
        
        return *this;
    }
    
    /// Divide-assign a scalar
    Vector3& operator /= (float rhs)
    {
        x_ /= rhs;
        y_ /= rhs;
        z_ /= rhs;
        
        return *this;
    }
    
    /// Divide-assign a vector
    Vector3& operator /= (const Vector3& rhs)
    {
        x_ /= rhs.x_;
        y_ /= rhs.y_;
        z_ /= rhs.z_;
        
        return *this;
    }
    
    /// Normalize to unit length and return the previous length
    float Normalize()
    {
        float len = Length();
        if (len < M_EPSILON)
            return len;
        
        float invLen = 1.0f / len;
        
        x_ *= invLen;
        y_ *= invLen;
        z_ *= invLen;
        
        return len;
    }
    
    /// Normalize to unit length using fast inverse square root
    void NormalizeFast()
    {
        float invLen = FastInvSqrt(x_ * x_ + y_ * y_ + z_ * z_);
        x_ *= invLen;
        y_ *= invLen;
        z_ *= invLen;
    }
    
    /// Return length
    float Length() const { return sqrtf(x_ * x_ + y_ * y_ + z_ * z_); }
    /// Return length using fast square root
    float LengthFast() const { return FastSqrt(x_ * x_ + y_ * y_ + z_ * z_); }
    /// Return squared length
    float LengthSquared() const { return x_ * x_ + y_ * y_ + z_ * z_; }
    /// Calculate dot product
    float DotProduct(const Vector3& rhs) const { return x_ * rhs.x_ + y_ * rhs.y_ + z_ * rhs.z_; }
    /// Calculate absolute dot product
    float AbsDotProduct(const Vector3& rhs) const { return fabsf(x_ * rhs.x_) + fabsf(y_ * rhs.y_) + fabsf(z_ * rhs.z_); }
    
    /// Calculate cross product
    Vector3 CrossProduct(const Vector3& rhs) const
    {
        return Vector3(
            y_ * rhs.z_ - z_ * rhs.y_,
            z_ * rhs.x_ - x_ * rhs.z_,
            x_ * rhs.y_ - y_ * rhs.x_
        );
    }
    
    /// Linear interpolation with another vector
    Vector3 Lerp(const Vector3& rhs, float t) const { return *this * (1.0f - t) + rhs * t; }
    
    /// Return normalized to unit length
    Vector3 Normalized() const
    {
        float len = Length();
        if (len < M_EPSILON)
            return *this;
        
        float invLen = 1.0f / len;
        
        return *this * invLen;
    }
    
    /// Return normalized to unit length using fast inverse square root
    Vector3 NormalizedFast() const
    {
        float invLen = FastInvSqrt(x_ * x_ + y_ * y_ + z_ * z_);
        
        return *this * invLen;
    }
    
    /// Return float data
    const float* GetData() const { return &x_; }
    /// Return as string
    String ToString() const;
    
    /// X coordinate
    float x_;
    /// Y coordinate
    float y_;
    /// Z coordinate
    float z_;
    
    /// Zero vector
    static const Vector3 ZERO;
    /// (-1,0,0) vector
    static const Vector3 LEFT;
    /// (1,0,0) vector
    static const Vector3 RIGHT;
    /// (0,1,0) vector
    static const Vector3 UP;
    /// (0,-1,0) vector
    static const Vector3 DOWN;
    /// (0,0,1) vector
    static const Vector3 FORWARD;
    /// (0,0,-1) vector
    static const Vector3 BACK;
    /// (1,1,1) vector
    static const Vector3 UNITY;
};

/// Multiply Vector3 with a scalar
inline Vector3 operator * (float lhs, const Vector3& rhs) { return rhs * lhs; }
