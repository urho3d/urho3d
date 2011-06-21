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

#include "MathDefs.h"
#include "StringBase.h"

/// Two-dimensional vector
class Vector2
{
public:
    /// Construct an undefined vector
    Vector2()
    {
    }
    
    /// Copy-construct from another vector
    Vector2(const Vector2& vector) :
        x_(vector.x_),
        y_(vector.y_)
    {
    }
    
    /// Construct from coordinates
    Vector2(float x, float y) :
        x_(x),
        y_(y)
    {
    }
    
    /// Construct from a float array
    Vector2(const float* data) :
        x_(data[0]),
        y_(data[1])
    {
    }
    
    /// Assign from another vector
    Vector2& operator = (const Vector2& rhs)
    {
        x_ = rhs.x_;
        y_ = rhs.y_;
        
        return *this;
    }
    
    /// Test for equality with another vector
    bool operator == (const Vector2& rhs) const { return Equals(x_, rhs.x_) && Equals(y_, rhs.y_); }
    /// Test for inequality with another vector
    bool operator != (const Vector2& rhs) const { return !Equals(x_, rhs.x_) || !Equals(y_, rhs.y_); }
    /// Add a vector
    Vector2 operator + (const Vector2& rhs) const { return Vector2(x_ + rhs.x_, y_ + rhs.y_); }
    /// Return negation
    Vector2 operator - () const { return Vector2(-x_, -y_); }
    /// Subtract a vector
    Vector2 operator - (const Vector2& rhs) const { return Vector2(x_ - rhs.x_, y_ - rhs.y_); }
    /// Multiply with a scalar
    Vector2 operator * (float rhs) const { return Vector2(x_ * rhs, y_ * rhs); }
    /// Multiply with a vector
    Vector2 operator * (const Vector2& rhs) const { return Vector2(x_ * rhs.x_, y_ * rhs.y_); }
    /// Divide by a scalar
    Vector2 operator / (float rhs) const { return Vector2(x_ / rhs, y_ / rhs); }
    /// Divide by a vector
    Vector2 operator / (const Vector2& rhs) const { return Vector2(x_ / rhs.x_, y_ / rhs.y_); }
    
    /// Add-assign a vector
    Vector2& operator += (const Vector2& rhs)
    {
        x_ += rhs.x_;
        y_ += rhs.y_;
        
        return *this;
    }
    
    /// Subtract-assign a vector
    Vector2& operator -= (const Vector2& rhs)
    {
        x_ -= rhs.x_;
        y_ -= rhs.y_;
        
        return *this;
    }
    
    /// Multiply-assign a scalar
    Vector2& operator *= (float rhs)
    {
        x_ *= rhs;
        y_ *= rhs;
        
        return *this;
    }
    
    /// Multiply-assign a vector
    Vector2& operator *= (const Vector2& rhs)
    {
        x_ *= rhs.x_;
        y_ *= rhs.y_;
        
        return *this;
    }
    
    /// Divide-assign a scalar
    Vector2& operator /= (float rhs)
    {
        x_ /= rhs;
        y_ /= rhs;
        
        return *this;
    }
    
    /// Divide-assign a vector
    Vector2& operator /= (const Vector2& rhs)
    {
        x_ /= rhs.x_;
        y_ /= rhs.y_;
        
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
        
        return len;
    }
    
    /// Normalize to unit length using fast inverse square root
    void NormalizeFast()
    {
        float invLen = FastInvSqrt(x_ * x_ + y_ * y_);
        x_ *= invLen;
        y_ *= invLen;
    }
    
    /// Return length
    float Length() const { return sqrtf(x_ * x_ + y_ * y_); }
    /// Return length using fast square root
    float LengthFast() const { return FastSqrt(x_ * x_ + y_ * y_); }
    /// Return squared length
    float LengthSquared() const { return x_ * x_ + y_ * y_; }
    /// Calculate dot product
    float DotProduct(const Vector2& rhs) const { return x_ * rhs.x_ + y_ * rhs.y_; }
    /// Calculate absolute dot product
    float AbsDotProduct(const Vector2& rhs) const { return fabsf(x_ * rhs.x_) + fabsf(y_ * rhs.y_); }
    /// Linear interpolation with another vector
    Vector2 Lerp(const Vector2& rhs, float t) const { return *this * (1.0f - t) + rhs * t; }
    
    /// Return normalized to unit length
    Vector2 Normalized() const
    {
        float len = Length();
        if (len < M_EPSILON)
            return *this;
        
        float invLen = 1.0f / len;
        
        return *this * invLen;
    }
    
    /// Return normalized to unit length using fast inverse square root
    Vector2 NormalizedFast() const
    {
        float invLen = FastInvSqrt(x_ * x_ + y_ * y_);
        
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
    
    /// Zero vector
    static const Vector2 ZERO;
    /// (-1,0) vector
    static const Vector2 LEFT;
    /// (1,0) vector
    static const Vector2 RIGHT;
    /// (0,1) vector
    static const Vector2 UP;
    /// (0,-1) vector
    static const Vector2 DOWN;
    /// (1,1) vector
    static const Vector2 UNITY;
};

/// Multiply Vector2 with a scalar
inline Vector2 operator * (float lhs, const Vector2& rhs) { return rhs * lhs; }

/// Two-dimensional vector with integer values
class IntVector2
{
public:
    /// Construct an undefined vector
    IntVector2()
    {
    }
    
    /// Construct from coordinates
    IntVector2(int x, int y) :
        x_(x),
        y_(y)
    {
    }
    
    /// Copy-construct from another vector
    IntVector2(const IntVector2& rhs) :
        x_(rhs.x_),
        y_(rhs.y_)
    {
    }
    
    /// Test for equality with another vector
    bool operator == (const IntVector2& rhs) const { return x_ == rhs.x_ && y_ == rhs.y_; }
    /// Test for inequality with another vector
    bool operator != (const IntVector2& rhs) const { return x_ != rhs.x_ || y_ != rhs.y_; }
    /// Add a vector
    IntVector2 operator + (const IntVector2& rhs) const { return IntVector2(x_ + rhs.x_, y_ + rhs.y_); }
    /// Return negation
    IntVector2 operator - () const { return IntVector2(-x_, -y_); }
    /// Subtract a vector
    IntVector2 operator - (const IntVector2& rhs) const { return IntVector2(x_ - rhs.x_, y_ - rhs.y_); }
    /// Multiply with a scalar
    IntVector2 operator * (int rhs) const { return IntVector2(x_ * rhs, y_ * rhs); }
    /// Divide by a scalar
    IntVector2 operator / (int rhs) const { return IntVector2(x_ / rhs, y_ / rhs); }
    
    /// Add-assign a vector
    IntVector2& operator += (const IntVector2& rhs)
    {
        x_ += rhs.x_;
        y_ += rhs.y_;
        
        return *this;
    }
    
    /// Subtract-assign a vector
    IntVector2& operator -= (const IntVector2& rhs)
    {
        x_ -= rhs.x_;
        y_ -= rhs.y_;
        
        return *this;
    }
    
    /// Multiply-assign a scalar
    IntVector2& operator *= (int rhs)
    {
        x_ *= rhs;
        y_ *= rhs;
        
        return *this;
    }
    
    /// Divide-assign a scalar
    IntVector2& operator /= (int rhs)
    {
        x_ /= rhs;
        y_ /= rhs;
        
        return *this;
    }
    
    /// Return integer data
    const int* GetData() const { return &x_; }
    /// Return as string
    String ToString() const;
    
    /// X coordinate
    int x_;
    /// Y coordinate
    int y_;
    
    /// Zero vector
    static const IntVector2 ZERO;
};

/// Multiply IntVector2 with a scalar
inline IntVector2 operator * (int lhs, const IntVector2& rhs) { return rhs * lhs; }
