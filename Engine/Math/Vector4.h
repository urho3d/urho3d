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

#ifndef MATH_VECTOR4_H
#define MATH_VECTOR4_H

#include "Vector3.h"

//! A four-dimensional vector
class Vector4
{
public:
    //! Construct an undefined vector
    Vector4()
    {
    }
    
    //! Copy-construct from another vector
    Vector4(const Vector4& vector) :
        mX(vector.mX),
        mY(vector.mY),
        mZ(vector.mZ),
        mW(vector.mW)
    {
    }
    
    //! Construct from a Vector3 and the W coordinate
    Vector4(const Vector3& vector, float w) :
        mX(vector.mX),
        mY(vector.mY),
        mZ(vector.mZ),
        mW(w)
    {
    }
    
    //! Construct from coordinates
    Vector4(float x, float y, float z, float w) :
        mX(x),
        mY(y),
        mZ(z),
        mW(w)
    {
    }
    
    //! Construct from a float array
    Vector4(const float* data) :
        mX(data[0]),
        mY(data[1]),
        mZ(data[2]),
        mW(data[3])
    {
    }
    
    //! Assign from another vector
    Vector4& operator = (const Vector4& rhs)
    {
        mX = rhs.mX;
        mY = rhs.mY;
        mZ = rhs.mZ;
        mW = rhs.mW;
        
        return *this;
    }
    
    //! Test for equality with another vector
    bool operator == (const Vector4& rhs) const
    {
        return (mX == rhs.mX) && (mY == rhs.mY) && (mZ == rhs.mZ) && (mW == rhs.mW);
    }
    
    //! Test for inequality with another vector
    bool operator != (const Vector4& rhs) const
    {
        return (mX != rhs.mX) || (mY != rhs.mY) || (mZ != rhs.mZ) || (mW != rhs.mW);
    }
    
    //! Add a vector
    Vector4 operator + (const Vector4& rhs) const
    {
        return Vector4(mX + rhs.mX, mY + rhs.mY, mZ + rhs.mZ, mW + rhs.mW);
    }
    
    //! Return negation
    Vector4 operator - () const
    {
        return Vector4(-mX, -mY, -mZ, -mW);
    }
    
    //! Subtract a vector
    Vector4 operator - (const Vector4& rhs) const
    {
        return Vector4(mX - rhs.mX, mY - rhs.mY, mZ - rhs.mZ, mW - rhs.mW);
    }
    
    //! Multiply with a scalar
    Vector4 operator * (float rhs) const
    {
        return Vector4(mX * rhs, mY * rhs, mZ * rhs, mW * rhs);
    }
    
    //! Multiply with a vector
    Vector4 operator * (const Vector4& rhs) const
    {
        return Vector4(mX * rhs.mX, mY * rhs.mY, mZ * rhs.mZ, mW * rhs.mW);
    }
    
    //! Divide by a scalar
    Vector4 operator / (float rhs) const
    {
        return Vector4(mX / rhs, mY / rhs, mZ / rhs, mW / rhs);
    }
    
    //! Divide by a vector
    Vector4 operator / (const Vector4& rhs) const
    {
        return Vector4(mX / rhs.mX, mY / rhs.mY, mZ / rhs.mZ, mW / rhs.mW);
    }
    
    //! Add-assign a vector
    Vector4& operator += (const Vector4& rhs)
    {
        mX += rhs.mX;
        mY += rhs.mY;
        mZ += rhs.mZ;
        mW += rhs.mW;
        
        return *this;
    }
    
    //! Subtract-assign a vector
    Vector4& operator -= (const Vector4& rhs)
    {
        mX -= rhs.mX;
        mY -= rhs.mY;
        mZ -= rhs.mZ;
        mW -= rhs.mW;
        
        return *this;
    }
    
    //! Multiply-assign a scalar
    Vector4& operator *= (float rhs)
    {
        mX *= rhs;
        mY *= rhs;
        mZ *= rhs;
        mW *= rhs;
        
        return *this;
    }
    
    //! Multiply-assign a vector
    Vector4& operator *= (const Vector4& rhs)
    {
        mX *= rhs.mX;
        mY *= rhs.mY;
        mZ *= rhs.mZ;
        mW *= rhs.mW;
        
        return *this;
    }
    
    //! Divide-assign a scalar
    Vector4& operator /= (float rhs)
    {
        mX /= rhs;
        mY /= rhs;
        mZ /= rhs;
        mW /= rhs;
        
        return *this;
    }
    
    //! Divide-assign a vector
    Vector4& operator /= (const Vector4& rhs)
    {
        mX /= rhs.mX;
        mY /= rhs.mY;
        mZ /= rhs.mZ;
        mW /= rhs.mW;
        
        return *this;
    }
    
    //! Calculate dot product
    float dotProduct(const Vector4& rhs) const
    {
        return mX * rhs.mX + mY * rhs.mY + mZ * rhs.mZ + mW * rhs.mW;
    }
    
    //! Calculate absolute dot product
    float absDotProduct(const Vector4& rhs) const
    {
        return fabsf(mX * rhs.mX) + fabsf(mY * rhs.mY) + fabsf(mZ * rhs.mZ) + fabsf(mW * rhs.mW);
    }
    
    //! Linear interpolation with another vector
    Vector4 lerp(const Vector4& rhs, float t) const
    {
        return *this * (1.0f - t) + rhs * t;
    }
    
    //! Return float data
    const float* getData() const { return &mX; }
    
    //! X coordinate
    float mX;
    
    //! Y coordinate
    float mY;
    
    //! Z coordinate
    float mZ;
    
    //! W coordinate
    float mW;
    
    //! Zero vector
    static const Vector4 sZero;
    //! (1,1,1) vector
    static const Vector4 sUnity;
};

inline Vector4 operator * (float lhs, const Vector4& rhs) { return rhs * lhs; }

#endif // MATH_VECTOR4_H
