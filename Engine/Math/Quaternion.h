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

#ifndef MATH_QUATERNION_H
#define MATH_QUATERNION_H

#include "Matrix3.h"

//! Rotation represented as a four-dimensional normalized vector
class Quaternion
{
public:
    //! Construct identity quaternion
    Quaternion() :
        mW(1.0f),
        mX(0.0f),
        mY(0.0f),
        mZ(0.0f)
    {
    }
    
    //! Copy-construct from another quaternion
    Quaternion(const Quaternion& quat) :
        mW(quat.mW),
        mX(quat.mX),
        mY(quat.mY),
        mZ(quat.mZ)
    {
    }
    
    //! Construct from values
    Quaternion(float w, float x, float y, float z) :
        mW(w),
        mX(x),
        mY(y),
        mZ(z)
    {
    }
    
    //! Construct from a float array
    Quaternion(const float* data) :
        mW(data[0]),
        mX(data[1]),
        mY(data[2]),
        mZ(data[3])
    {
    }
    
    //! Construct from an angle (in degrees) and axis
    Quaternion(float angle, const Vector3& axis);
    //! Construct from Euler angles (in degrees)
    Quaternion(const Vector3& euler);
    //! Construct from Euler angles (in degrees)
    Quaternion(float angleX, float angleY, float angleZ);
    //! Construct from the rotation difference between two vectors
    Quaternion(const Vector3& start, const Vector3& end);
    //! Construct from a rotation matrix
    Quaternion(const Matrix3& matrix);
    
    //! Assign from another quaternion
    Quaternion& operator = (const Quaternion& rhs)
    {
        mW = rhs.mW;
        mX = rhs.mX;
        mY = rhs.mY;
        mZ = rhs.mZ;
        
        return *this;
    }
    
    //! Add-assign a quaternion
    Quaternion& operator += (const Quaternion& rhs)
    {
        mW += rhs.mW;
        mX += rhs.mX;
        mY += rhs.mY;
        mZ += rhs.mZ;
        
        return *this;
    }
    
    //! Test for equality with another quaternion
    bool operator == (const Quaternion& rhs) const
    {
        return (mW == rhs.mW) && (mX == rhs.mX) && (mY == rhs.mY) && (mZ == rhs.mZ);
    }
    
    //! Test for inequality with another quaternion
    bool operator != (const Quaternion& rhs) const
    {
        return (mW != rhs.mW) || (mX != rhs.mX) || (mY != rhs.mY) || (mZ != rhs.mZ);
    }
    
    //! Multiply with a scalar
    Quaternion operator * (float rhs) const
    {
        return Quaternion(mW * rhs, mX * rhs, mY * rhs, mZ * rhs);
    }
    
    //! Multiply a Vector3
    Vector3 operator * (const Vector3& rhs) const
    {
        Vector3 qVec(mX,mY,mZ);
        Vector3 cross1(qVec.crossProduct(rhs));
        Vector3 cross2(qVec.crossProduct(cross1));
        return rhs + 2.0f * (cross1 * mW + cross2);
    }
    
    //! Return negation
    Quaternion operator - () const
    {
        return Quaternion(-mW, -mX, -mY, -mZ);
    }
    
    //! Add a quaternion
    Quaternion operator + (const Quaternion& rhs) const
    {
        return Quaternion(mW + rhs.mW, mX + rhs.mX, mY + rhs.mY, mZ + rhs.mZ);
    }
    
    //! Subtract a quaternion
    Quaternion operator - (const Quaternion& rhs) const
    {
        return Quaternion(mW - rhs.mW, mX - rhs.mX, mY - rhs.mY, mZ - rhs.mZ);
    }
    
    //! Multiply a quaternion
    Quaternion operator * (const Quaternion& rhs) const
    {
        return Quaternion(
            mW * rhs.mW - mX * rhs.mX - mY * rhs.mY - mZ * rhs.mZ,
            mW * rhs.mX + mX * rhs.mW + mY * rhs.mZ - mZ * rhs.mY,
            mW * rhs.mY + mY * rhs.mW + mZ * rhs.mX - mX * rhs.mZ,
            mW * rhs.mZ + mZ * rhs.mW + mX * rhs.mY - mY * rhs.mX
        );
    }
    
    //! Normalize to unit length and return the previous length
    float normalize()
    {
        float len = sqrtf(mW * mW + mX * mX + mY * mY + mZ * mZ);
        if (len < M_EPSILON)
            return len;
        
        float invLen = 1.0f / len;
        mW *= invLen;
        mX *= invLen;
        mY *= invLen;
        mZ *= invLen;
        
        return len;
    }
    
    //! Normalize to unit length using fast inverse square root
    void normalizeFast()
    {
        float invLen = fastInvSqrt(mW * mW + mX * mX + mY * mY + mZ * mZ);
        mW *= invLen;
        mX *= invLen;
        mY *= invLen;
        mZ *= invLen;
    }
    
    //! Define from an angle (in degrees) and axis
    void define(float angle, const Vector3& axis);
    //! Define from Euler angles (in degrees)
    void define(const Vector3& euler);
    //! Define from the rotation difference between two vectors
    void define(const Vector3& start, const Vector3& end);
    //! Define from a rotation matrix
    void define(const Matrix3& matrix);
    
    //! Return normalized to unit length
    Quaternion getNormalized() const
    {
        float len = sqrtf(mW * mW + mX * mX + mY * mY + mZ * mZ);
        if (len < M_EPSILON)
            return sIdentity;
        
        float invLen = 1.0f / len;
        return *this * invLen;
    }
    
    //! Return normalized to unit length, using fast inverse square root
    Quaternion getNormalizedFast() const
    {
        float invLen = fastInvSqrt(mW * mW + mX * mX + mY * mY + mZ * mZ);
        return *this * invLen;
    }
    
    //! Return inverse
    Quaternion getInverse() const
    {
        float lenSquared = mW * mW + mX * mX + mY * mY + mZ * mZ;
        if (lenSquared < M_EPSILON)
            return sIdentity;
        
        float invLenSquared = 1.0f / lenSquared;
        return Quaternion(
            mW * invLenSquared,
            -mX * invLenSquared,
            -mY * invLenSquared,
            -mZ * invLenSquared
        );
    }
    
    //! Return squared length
    float getLengthSquared() const
    {
        return mW * mW + mX * mX + mY * mY + mZ * mZ;
    }
    
    //! Calculate dot product
    float dotProduct(const Quaternion& rhs) const
    {
        return mW * rhs.mW + mX * rhs.mX + mY * rhs.mY + mZ * rhs.mZ;
    }
    
    //! Normalized interpolation with another quaternion
    Quaternion nlerp(const Quaternion& rhs, float t) const
    {
        return (*this * (1.0f - t) + rhs * t).getNormalized();
    }
    
    //! Normalized interpolation with another quaternion, using fast inverse square root
    Quaternion nlerpFast(const Quaternion& rhs, float t) const
    {
        return (*this * (1.0f - t) + rhs * t).getNormalizedFast();
    }
    
    //! Return Euler angles (in degrees)
    Vector3 getEulerAngles() const;
    //! Return yaw angle in degrees
    float getYaw() const;
    //! Return pitch angle in degrees
    float getPitch() const;
    //! Return roll angle in degrees
    float getRoll() const;
    //! Convert to rotation matrix
    Matrix3 getRotationMatrix() const;
    //! Spherical interpolation with another quaternion
    Quaternion slerp(Quaternion rhs, float t) const;
    //! Return float data
    const float* getData() const { return &mW; }
    
    //! W coordinate
    float mW;
    //! X coordinate
    float mX;
    //! Y coordinate
    float mY;
    //! Z coordinate
    float mZ;
    
    //! Identity quaternion
    static const Quaternion sIdentity;
};

#endif // MATH_QUATERNION_H
