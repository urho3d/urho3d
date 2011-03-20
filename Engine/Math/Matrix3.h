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

#ifndef MATH_MATRIX3_H
#define MATH_MATRIX3_H

#include "Vector3.h"

//! A 3x3 matrix for rotation and scaling
class Matrix3
{
public:
    //! Construct an undefined matrix
    Matrix3()
    {
    }
    
    //! Copy-construct from another matrix
    Matrix3(const Matrix3& matrix) :
        m00(matrix.m00),
        m01(matrix.m01),
        m02(matrix.m02),
        m10(matrix.m10),
        m11(matrix.m11),
        m12(matrix.m12),
        m20(matrix.m20),
        m21(matrix.m21),
        m22(matrix.m22)
    {
    }
    
    //! Construct from values
    Matrix3(float v00, float v01, float v02,
            float v10, float v11, float v12,
            float v20, float v21, float v22) :
        m00(v00),
        m01(v01),
        m02(v02),
        m10(v10),
        m11(v11),
        m12(v12),
        m20(v20),
        m21(v21),
        m22(v22)
    {
    }
    
    //! Construct from a float array
    Matrix3(float* data) :
        m00(data[0]),
        m01(data[1]),
        m02(data[2]),
        m10(data[3]),
        m11(data[4]),
        m12(data[5]),
        m20(data[6]),
        m21(data[7]),
        m22(data[8])
    {
    }
    
    //! Assign from another matrix
    Matrix3& operator = (const Matrix3& rhs)
    {
        m00 = rhs.m00;
        m01 = rhs.m01;
        m02 = rhs.m02;
        m10 = rhs.m10;
        m11 = rhs.m11;
        m12 = rhs.m12;
        m20 = rhs.m20;
        m21 = rhs.m21;
        m22 = rhs.m22;
        
        return *this;
    }
    
    //! Multiply a Vector3
    Vector3 operator * (const Vector3& rhs) const
    {
        return Vector3(
            m00 * rhs.mX + m01 * rhs.mY + m02 * rhs.mZ,
            m10 * rhs.mX + m11 * rhs.mY + m12 * rhs.mZ,
            m20 * rhs.mX + m21 * rhs.mY + m22 * rhs.mZ
        );
    }
    
    //! Add a matrix
    Matrix3 operator + (const Matrix3& rhs) const
    {
        return Matrix3(
            m00 + rhs.m00,
            m01 + rhs.m01,
            m02 + rhs.m02,
            m10 + rhs.m10,
            m11 + rhs.m11,
            m12 + rhs.m12,
            m20 + rhs.m20,
            m21 + rhs.m21,
            m22 + rhs.m22
        );
    }
    
    //! Subtract a matrix
    Matrix3 operator - (const Matrix3& rhs) const
    {
        return Matrix3(
            m00 - rhs.m00,
            m01 - rhs.m01,
            m02 - rhs.m02,
            m10 - rhs.m10,
            m11 - rhs.m11,
            m12 - rhs.m12,
            m20 - rhs.m20,
            m21 - rhs.m21,
            m22 - rhs.m22
        );
    }
    
    //! Multiply with a scalar
    Matrix3 operator * (float rhs) const
    {
        return Matrix3(
            m00 * rhs,
            m01 * rhs,
            m02 * rhs,
            m10 * rhs,
            m11 * rhs,
            m12 * rhs,
            m20 * rhs,
            m21 * rhs,
            m22 * rhs
        );
    }
    
    //! Multiply a matrix
    Matrix3 operator * (const Matrix3& rhs) const
    {
        return Matrix3(
            m00 * rhs.m00 + m01 * rhs.m10 + m02 * rhs.m20,
            m00 * rhs.m01 + m01 * rhs.m11 + m02 * rhs.m21,
            m00 * rhs.m02 + m01 * rhs.m12 + m02 * rhs.m22,
            m10 * rhs.m00 + m11 * rhs.m10 + m12 * rhs.m20,
            m10 * rhs.m01 + m11 * rhs.m11 + m12 * rhs.m21,
            m10 * rhs.m02 + m11 * rhs.m12 + m12 * rhs.m22,
            m20 * rhs.m00 + m21 * rhs.m10 + m22 * rhs.m20,
            m20 * rhs.m01 + m21 * rhs.m11 + m22 * rhs.m21,
            m20 * rhs.m02 + m21 * rhs.m12 + m22 * rhs.m22
        );
    }
    
    //! Set scaling elements
    void setScale(const Vector3& scale)
    {
        m00 = scale.mX;
        m11 = scale.mY;
        m22 = scale.mZ;
    }
    
    //! Set uniform scaling elements
    void setScale(float scale)
    {
        m00 = scale;
        m11 = scale;
        m22 = scale;
    }
    
    //! Return transpose
    Matrix3 getTranspose() const
    {
        return Matrix3(
            m00,
            m10,
            m20,
            m01,
            m11,
            m21,
            m02,
            m12,
            m22
        );
    }
    
    //! Return scaled by a vector
    Matrix3 getScaled(const Vector3& scale) const
    {
        return Matrix3(
            m00 * scale.mX,
            m01 * scale.mY,
            m02 * scale.mZ,
            m10 * scale.mX,
            m11 * scale.mY,
            m12 * scale.mZ,
            m20 * scale.mX,
            m21 * scale.mY,
            m22 * scale.mZ
        );
    }
    
    //! Return inverse
    Matrix3 getInverse() const;
    
    //! Return float data
    const float* getData() const { return &m00; }
    
    float m00;
    float m01;
    float m02;
    float m10;
    float m11;
    float m12;
    float m20;
    float m21;
    float m22;
    
    //! Zero matrix
    static const Matrix3 sZero;
    //! Identity matrix
    static const Matrix3 sIdentity;
};

//! Multiply a 3x3 matrix with a scalar
inline Matrix3 operator * (float lhs, const Matrix3& rhs) { return rhs * lhs; }

#endif // MATH_MATRIX3_H
