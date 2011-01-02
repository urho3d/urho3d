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

#ifndef MATH_VECTOR2_H
#define MATH_VECTOR2_H

#include "MathDefs.h"

//! A two-dimensional vector
class Vector2
{
public:
    //! Construct an undefined vector
    Vector2()
    {
    }
    
    //! Copy-construct from another vector
    Vector2(const Vector2& vector) :
        mX(vector.mX),
        mY(vector.mY)
    {
    }
    
    //! Construct from coordinates
    Vector2(float x, float y) :
        mX(x),
        mY(y)
    {
    }
    
    //! Construct from a float array
    Vector2(const float* data) :
        mX(data[0]),
        mY(data[1])
    {
    }
    
    //! Assign from another vector
    Vector2& operator = (const Vector2& rhs)
    {
        mX = rhs.mX;
        mY = rhs.mY;
        
        return *this;
    }
    
    //! Test for equality with another vector
    bool operator == (const Vector2& rhs) const
    {
        return (mX == rhs.mX) && (mY == rhs.mY);
    }
    
    //! Test for inequality with another vector
    bool operator != (const Vector2& rhs) const
    {
        return (mX != rhs.mX) || (mY != rhs.mY);
    }
    
    //! Add a vector
    Vector2 operator + (const Vector2& rhs) const
    {
        return Vector2(mX + rhs.mX, mY + rhs.mY);
    }
    
    //! Return negation
    Vector2 operator - () const
    {
        return Vector2(-mX, -mY);
    }
    
    //! Subtract a vector
    Vector2 operator - (const Vector2& rhs) const
    {
        return Vector2(mX - rhs.mX, mY - rhs.mY);
    }
    
    //! Multiply with a scalar
    Vector2 operator * (float rhs) const
    {
        return Vector2(mX * rhs, mY * rhs);
    }
    
    //! Multiply with a vector
    Vector2 operator * (const Vector2& rhs) const
    {
        return Vector2(mX * rhs.mX, mY * rhs.mY);
    }
    
    //! Divide by a scalar
    Vector2 operator / (float rhs) const
    {
        return Vector2(mX / rhs, mY / rhs);
    }
    
    //! Divide by a vector
    Vector2 operator / (const Vector2& rhs) const
    {
        return Vector2(mX / rhs.mX, mY / rhs.mY);
    }
    
    //! Add-assign a vector
    Vector2& operator += (const Vector2& rhs)
    {
        mX += rhs.mX;
        mY += rhs.mY;
        
        return *this;
    }
    
    //! Subtract-assign a vector
    Vector2& operator -= (const Vector2& rhs)
    {
        mX -= rhs.mX;
        mY -= rhs.mY;
        
        return *this;
    }
    
    //! Multiply-assign a scalar
    Vector2& operator *= (float rhs)
    {
        mX *= rhs;
        mY *= rhs;
        
        return *this;
    }
    
    //! Multiply-assign a vector
    Vector2& operator *= (const Vector2& rhs)
    {
        mX *= rhs.mX;
        mY *= rhs.mY;
        
        return *this;
    }
    
    //! Divide-assign a scalar
    Vector2& operator /= (float rhs)
    {
        mX /= rhs;
        mY /= rhs;
        
        return *this;
    }
    
    //! Divide-assign a vector
    Vector2& operator /= (const Vector2& rhs)
    {
        mX /= rhs.mX;
        mY /= rhs.mY;
        
        return *this;
    }
    
    //! Normalize to unit length and return the previous length
    float normalize()
    {
        float len = getLength();
        if (len < M_EPSILON)
            return len;
        
        float invLen = 1.0f / len;
        mX *= invLen;
        mY *= invLen;
        
        return len;
    }
    
    //! Return length
    float getLength() const
    {
        return sqrtf(mX * mX + mY * mY);
    }
    
    //! Return squared length
    float getLengthSquared() const
    {
        return mX * mX + mY * mY;
    }
    
    //! Calculate dot product
    float dotProduct(const Vector2& rhs) const
    {
        return mX * rhs.mX + mY * rhs.mY;
    }
    
    //! Calculate absolute dot product
    float absDotProduct(const Vector2& rhs) const
    {
        return fabsf(mX * rhs.mX) + fabsf(mY * rhs.mY);
    }
    
    //! Linear interpolation with another vector
    Vector2 lerp(const Vector2& rhs, float t) const
    {
        return *this * (1.0f - t) + rhs * t;
    }
    
    //! Return normalized to unit length
    Vector2 getNormalized() const
    {
        float len = getLength();
        if (len < M_EPSILON)
            return *this;
        
        float invLen = 1.0f / len;
        return *this * invLen;
    }
    
    //! Return float data
    const float* getData() const { return &mX; }
    
    //! X coordinate
    float mX;
    //! Y coordinate
    float mY;
    
    //! Zero vector
    static const Vector2 sZero;
    //! (-1,0) vector
    static const Vector2 sLeft;
    //! (1,0) vector
    static const Vector2 sRight;
    //! (0,1) vector
    static const Vector2 sUp;
    //! (0,-1) vector
    static const Vector2 sDown;
    //! (1,1) vector
    static const Vector2 sUnity;
};

//! Multiply Vector2 with a scalar
inline Vector2 operator * (float lhs, const Vector2& rhs) { return rhs * lhs; }

//! A two-dimensional vector with integer values
class IntVector2
{
public:
    //! Construct an undefined vector
    IntVector2()
    {
    }
    
    //! Construct from coordinates
    IntVector2(int x, int y) :
        mX(x),
        mY(y)
    {
    }
    
    //! Test for equality with another vector
    bool operator == (const IntVector2& rhs) const
    {
        return (mX == rhs.mX) && (mY == rhs.mY);
    }
    
    //! Test for inequality with another vector
    bool operator != (const IntVector2& rhs) const
    {
        return (mX != rhs.mX) ||(mY != rhs.mY);
    }
    
    //! Add a vector
    IntVector2 operator + (const IntVector2& rhs) const
    {
        return IntVector2(mX + rhs.mX, mY + rhs.mY);
    }
    
    //! Return negation
    IntVector2 operator - () const
    {
        return IntVector2(-mX, -mY);
    }
    
    //! Subtract a vector
    IntVector2 operator - (const IntVector2& rhs) const
    {
        return IntVector2(mX - rhs.mX, mY - rhs.mY);
    }
    
    //! Multiply with a scalar
    IntVector2 operator * (int rhs) const
    {
        return IntVector2(mX * rhs, mY * rhs);
    }
    
    //! Divide by a scalar
    IntVector2 operator / (int rhs) const
    {
        return IntVector2(mX / rhs, mY / rhs);
    }
    
    //! Add-assign a vector
    IntVector2& operator += (const IntVector2& rhs)
    {
        mX += rhs.mX;
        mY += rhs.mY;
        
        return *this;
    }
    
    //! Subtract-assign a vector
    IntVector2& operator -= (const IntVector2& rhs)
    {
        mX -= rhs.mX;
        mY -= rhs.mY;
        
        return *this;
    }
    
    //! Multiply-assign a scalar
    IntVector2& operator *= (int rhs)
    {
        mX *= rhs;
        mY *= rhs;
        
        return *this;
    }
    
    //! Divide-assign a scalar
    IntVector2& operator /= (int rhs)
    {
        mX /= rhs;
        mY /= rhs;
        
        return *this;
    }
    
    //! Return integer data
    const int* getData() const { return &mX; }
    
    //! X coordinate
    int mX;
    //! Y coordinate
    int mY;
    
    //! Zero vector
    static const IntVector2 sZero;
};

//! Multiply IntVector2 with a scalar
inline IntVector2 operator * (int lhs, const IntVector2& rhs) { return rhs * lhs; }

#endif // MATH_VECTOR2_H
