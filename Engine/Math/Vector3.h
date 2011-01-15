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

#ifndef MATH_VECTOR3_H
#define MATH_VECTOR3_H

#include "Vector2.h"

//! A three-dimensional vector
class Vector3
{
public:
    //! Construct an undefined vector
    Vector3()
    {
    }
    
    //! Copy-construct from another vector
    Vector3(const Vector3& vector) :
        mX(vector.mX),
        mY(vector.mY),
        mZ(vector.mZ)
    {
    }
    
    //! Construct from a two-dimensional vector and the Z coordinate
    Vector3(const Vector2& vector, float z) :
        mX(vector.mX),
        mY(vector.mY),
        mZ(z)
    {
    }
    
    //! Construct from coordinates
    Vector3(float x, float y, float z) :
        mX(x),
        mY(y),
        mZ(z)
    {
    }
    
    //! Construct from a float array
    Vector3(const float* data) :
        mX(data[0]),
        mY(data[1]),
        mZ(data[2])
    {
    }
    
    //! Assign from another vector
    Vector3& operator = (const Vector3& rhs)
    {
        mX = rhs.mX;
        mY = rhs.mY;
        mZ = rhs.mZ;
        
        return *this;
    }
    
    //! Test for equality with another vector
    bool operator == (const Vector3& rhs) const
    {
        return (mX == rhs.mX) && (mY == rhs.mY) && (mZ == rhs.mZ);
    }
    
    //! Test for inequality with another vector
    bool operator != (const Vector3& rhs) const
    {
        return (mX != rhs.mX) || (mY != rhs.mY) || (mZ != rhs.mZ);
    }
    
    //! Add a vector
    Vector3 operator + (const Vector3& rhs) const
    {
        return Vector3(mX + rhs.mX, mY + rhs.mY, mZ + rhs.mZ);
    }
    
    //! Return negation
    Vector3 operator - () const
    {
        return Vector3(-mX, -mY, -mZ);
    }
    
    //! Subtract a vector
    Vector3 operator - (const Vector3& rhs) const
    {
        return Vector3(mX - rhs.mX, mY - rhs.mY, mZ - rhs.mZ);
    }
    
    //! Multiply with a scalar
    Vector3 operator * (float rhs) const
    {
        return Vector3(mX * rhs, mY * rhs, mZ * rhs);
    }
    
    //! Multiply with a vector
    Vector3 operator * (const Vector3& rhs) const
    {
        return Vector3(mX * rhs.mX, mY * rhs.mY, mZ * rhs.mZ);
    }
    
    //! Divide by a scalar
    Vector3 operator / (float rhs) const
    {
        return Vector3(mX / rhs, mY / rhs, mZ / rhs);
    }
    
    //! Divide by a vector
    Vector3 operator / (const Vector3& rhs) const
    {
        return Vector3(mX / rhs.mX, mY / rhs.mY, mZ / rhs.mZ);
    }
    
    //! Add-assign a vector
    Vector3& operator += (const Vector3& rhs)
    {
        mX += rhs.mX;
        mY += rhs.mY;
        mZ += rhs.mZ;
        
        return *this;
    }
    
    //! Subtract-assign a vector
    Vector3& operator -= (const Vector3& rhs)
    {
        mX -= rhs.mX;
        mY -= rhs.mY;
        mZ -= rhs.mZ;
        
        return *this;
    }
    
    //! Multiply-assign a scalar
    Vector3& operator *= (float rhs)
    {
        mX *= rhs;
        mY *= rhs;
        mZ *= rhs;
        
        return *this;
    }
    
    //! Multiply-assign a vector
    Vector3& operator *= (const Vector3& rhs)
    {
        mX *= rhs.mX;
        mY *= rhs.mY;
        mZ *= rhs.mZ;
        
        return *this;
    }
    
    //! Divide-assign a scalar
    Vector3& operator /= (float rhs)
    {
        mX /= rhs;
        mY /= rhs;
        mZ /= rhs;
        
        return *this;
    }
    
    //! Divide-assign a vector
    Vector3& operator /= (const Vector3& rhs)
    {
        mX /= rhs.mX;
        mY /= rhs.mY;
        mZ /= rhs.mZ;
        
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
        mZ *= invLen;
        
        return len;
    }
    
    //! Normalize to unit length using fast inverse square root
    void normalizeFast()
    {
        float invLen = fastInvSqrt(mX * mX + mY * mY + mZ * mZ);
        mX *= invLen;
        mY *= invLen;
        mZ *= invLen;
    }
    
    //! Return length
    float getLength() const
    {
        return sqrtf(mX * mX + mY * mY + mZ * mZ);
    }
    
    //! Return length using fast square root
    float getLengthFast() const
    {
        return fastSqrt(mX * mX + mY * mY + mZ * mZ);
    }
    
    //! Return squared length
    float getLengthSquared() const
    {
        return mX * mX + mY * mY + mZ * mZ;
    }
    
    //! Calculate dot product
    float dotProduct(const Vector3& rhs) const
    {
        return mX * rhs.mX + mY * rhs.mY + mZ * rhs.mZ;
    }
    
    //! Calculate absolute dot product
    float absDotProduct(const Vector3& rhs) const
    {
        return fabsf(mX * rhs.mX) + fabsf(mY * rhs.mY) + fabsf(mZ * rhs.mZ);
    }
    
    //! Calculate cross product
    Vector3 crossProduct(const Vector3& rhs) const
    {
        return Vector3(
            mY * rhs.mZ - mZ * rhs.mY,
            mZ * rhs.mX - mX * rhs.mZ,
            mX * rhs.mY - mY * rhs.mX
        );
    }
    
    //! Linear interpolation with another vector
    Vector3 lerp(const Vector3& rhs, float t) const
    {
        return *this * (1.0f - t) + rhs * t;
    }
    
    //! Return normalized to unit length
    Vector3 getNormalized() const
    {
        float len = getLength();
        if (len < M_EPSILON)
            return *this;
        
        float invLen = 1.0f / len;
        return *this * invLen;
    }
    
    //! Return normalized to unit length using fast inverse square root
    Vector3 getNormalizedFast() const
    {
        float invLen = fastInvSqrt(mX * mX + mY * mY + mZ * mZ);
        return *this * invLen;
    }
    
    //! Return float data
    const float* getData() const { return &mX; }
    
    //! X coordinate
    float mX;
    //! Y coordinate
    float mY;
    //! Z coordinate
    float mZ;
    
    //! Zero vector
    static const Vector3 sZero;
    //! (-1,0,0) vector
    static const Vector3 sLeft;
    //! (1,0,0) vector
    static const Vector3 sRight;
    //! (0,1,0) vector
    static const Vector3 sUp;
    //! (0,-1,0) vector
    static const Vector3 sDown;
    //! (0,0,1) vector
    static const Vector3 sForward;
    //! (0,0,-1) vector
    static const Vector3 sBack;
    //! (1,1,1) vector
    static const Vector3 sUnity;
};

//! Multiply Vector3 with a scalar
inline Vector3 operator * (float lhs, const Vector3& rhs) { return rhs * lhs; }

#endif // MATH_VECTOR3_H
