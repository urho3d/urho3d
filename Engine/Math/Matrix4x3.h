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

#ifndef MATH_MATRIX4X3_H
#define MATH_MATRIX4X3_H

#include "Matrix4.h"

//! A 4x3 matrix for scene node transform calculations
class Matrix4x3
{
public:
    //! Construct an undefined matrix
    Matrix4x3()
    {
    }
    
    //! Copy-construct from another matrix
    Matrix4x3(const Matrix4x3& matrix) :
        m00(matrix.m00),
        m01(matrix.m01),
        m02(matrix.m02),
        m03(matrix.m03),
        m10(matrix.m10),
        m11(matrix.m11),
        m12(matrix.m12),
        m13(matrix.m13),
        m20(matrix.m20),
        m21(matrix.m21),
        m22(matrix.m22),
        m23(matrix.m23)
    {
    }
    
    //! Copy-construct from a 3x3 matrix and set the extra elements to identity
    Matrix4x3(const Matrix3& matrix) :
        m00(matrix.m00),
        m01(matrix.m01),
        m02(matrix.m02),
        m03(0.0f),
        m10(matrix.m10),
        m11(matrix.m11),
        m12(matrix.m12),
        m13(0.0f),
        m20(matrix.m20),
        m21(matrix.m21),
        m22(matrix.m22),
        m23(0.0f)
    {
    }
    
    // Construct from values
    Matrix4x3(float v00, float v01, float v02, float v03,
            float v10, float v11, float v12, float v13,
            float v20, float v21, float v22, float v23) :
        m00(v00),
        m01(v01),
        m02(v02),
        m03(v03),
        m10(v10),
        m11(v11),
        m12(v12),
        m13(v13),
        m20(v20),
        m21(v21),
        m22(v22),
        m23(v23)
    {
    }
    
    //! Construct from a float array
    Matrix4x3(float* data) :
        m00(data[0]),
        m01(data[1]),
        m02(data[2]),
        m03(data[3]),
        m10(data[4]),
        m11(data[5]),
        m12(data[6]),
        m13(data[7]),
        m20(data[8]),
        m21(data[9]),
        m22(data[10]),
        m23(data[11])
    {
    }
    
    //! Construct from translation, rotation and uniform scale
    Matrix4x3(const Vector3& translation, const Quaternion& rotation, float scale);
    //! Construct from translation, rotation matrix and uniform scale
    Matrix4x3(const Vector3& translation, const Matrix3& rotation, float scale);
    //! Construct from translation, rotation and nonuniform scale
    Matrix4x3(const Vector3& translation, const Quaternion& rotation, const Vector3& scale);
    //! Construct from translation, rotation matrix and nonuniform scale
    Matrix4x3(const Vector3& translation, const Matrix3& rotation, const Vector3& scale);
    
    //! Assign from another matrix
    Matrix4x3& operator = (const Matrix4x3& rhs)
    {
        m00 = rhs.m00;
        m01 = rhs.m01;
        m02 = rhs.m02;
        m03 = rhs.m03;
        m10 = rhs.m10;
        m11 = rhs.m11;
        m12 = rhs.m12;
        m13 = rhs.m13;
        m20 = rhs.m20;
        m21 = rhs.m21;
        m22 = rhs.m22;
        m23 = rhs.m23;
        
        return *this;
    }
    
    //! Assign from a 3x3 matrix and set the extra elements to identity
    Matrix4x3& operator = (const Matrix3& rhs)
    {
        m00 = rhs.m00;
        m01 = rhs.m01;
        m02 = rhs.m02;
        m03 = 0.0;
        m10 = rhs.m10;
        m11 = rhs.m11;
        m12 = rhs.m12;
        m13 = 0.0;
        m20 = rhs.m20;
        m21 = rhs.m21;
        m22 = rhs.m22;
        m23 = 0.0;
        
        return *this;
    }
    
    //! Multiply a Vector3 which is assumed to represent position
    Vector3 operator * (const Vector3& rhs) const
    {
        return Vector3(
            (m00 * rhs.mX + m01 * rhs.mY + m02 * rhs.mZ + m03),
            (m10 * rhs.mX + m11 * rhs.mY + m12 * rhs.mZ + m13),
            (m20 * rhs.mX + m21 * rhs.mY + m22 * rhs.mZ + m23)
        );
    }
    
    //! Multiply a Vector4
    Vector3 operator * (const Vector4& rhs) const
    {
        return Vector3(
            (m00 * rhs.mX + m01 * rhs.mY + m02 * rhs.mZ + m03 * rhs.mW),
            (m10 * rhs.mX + m11 * rhs.mY + m12 * rhs.mZ + m13 * rhs.mW),
            (m20 * rhs.mX + m21 * rhs.mY + m22 * rhs.mZ + m23 * rhs.mW)
        );
    }
    
    //! Add a matrix
    Matrix4x3 operator + (const Matrix4x3& rhs) const
    {
        return Matrix4x3(
            m00 + rhs.m00,
            m01 + rhs.m01,
            m02 + rhs.m02,
            m03 + rhs.m03,
            m10 + rhs.m10,
            m11 + rhs.m11,
            m12 + rhs.m12,
            m13 + rhs.m13,
            m20 + rhs.m20,
            m21 + rhs.m21,
            m22 + rhs.m22,
            m23 + rhs.m23
        );
    }
    
    //! Subtract a matrix
    Matrix4x3 operator - (const Matrix4x3& rhs) const
    {
        return Matrix4x3(
            m00 - rhs.m00,
            m01 - rhs.m01,
            m02 - rhs.m02,
            m03 - rhs.m03,
            m10 - rhs.m10,
            m11 - rhs.m11,
            m12 - rhs.m12,
            m13 - rhs.m13,
            m20 - rhs.m20,
            m21 - rhs.m21,
            m22 - rhs.m22,
            m23 - rhs.m23
        );
    }
    
    //! Multiply with a scalar
    Matrix4x3 operator * (float rhs) const
    {
        return Matrix4x3(
            m00 * rhs,
            m01 * rhs,
            m02 * rhs,
            m03 * rhs,
            m10 * rhs,
            m11 * rhs,
            m12 * rhs,
            m13 * rhs,
            m20 * rhs,
            m21 * rhs,
            m22 * rhs,
            m23 * rhs
        );
    }
    
    //! Multiply a matrix
    Matrix4x3 operator * (const Matrix4x3& rhs) const
    {
        return Matrix4x3(
            m00 * rhs.m00 + m01 * rhs.m10 + m02 * rhs.m20,
            m00 * rhs.m01 + m01 * rhs.m11 + m02 * rhs.m21,
            m00 * rhs.m02 + m01 * rhs.m12 + m02 * rhs.m22,
            m00 * rhs.m03 + m01 * rhs.m13 + m02 * rhs.m23 + m03,
            m10 * rhs.m00 + m11 * rhs.m10 + m12 * rhs.m20,
            m10 * rhs.m01 + m11 * rhs.m11 + m12 * rhs.m21,
            m10 * rhs.m02 + m11 * rhs.m12 + m12 * rhs.m22,
            m10 * rhs.m03 + m11 * rhs.m13 + m12 * rhs.m23 + m13,
            m20 * rhs.m00 + m21 * rhs.m10 + m22 * rhs.m20,
            m20 * rhs.m01 + m21 * rhs.m11 + m22 * rhs.m21,
            m20 * rhs.m02 + m21 * rhs.m12 + m22 * rhs.m22,
            m20 * rhs.m03 + m21 * rhs.m13 + m22 * rhs.m23 + m23
        );
    }
    
    //! Multiply a 4x4 matrix
    Matrix4 operator * (const Matrix4& rhs) const
    {
        return Matrix4(
            m00 * rhs.m00 + m01 * rhs.m10 + m02 * rhs.m20 + m03 * rhs.m30,
            m00 * rhs.m01 + m01 * rhs.m11 + m02 * rhs.m21 + m03 * rhs.m31,
            m00 * rhs.m02 + m01 * rhs.m12 + m02 * rhs.m22 + m03 * rhs.m32,
            m00 * rhs.m03 + m01 * rhs.m13 + m02 * rhs.m23 + m03 * rhs.m33,
            m10 * rhs.m00 + m11 * rhs.m10 + m12 * rhs.m20 + m13 * rhs.m30,
            m10 * rhs.m01 + m11 * rhs.m11 + m12 * rhs.m21 + m13 * rhs.m31,
            m10 * rhs.m02 + m11 * rhs.m12 + m12 * rhs.m22 + m13 * rhs.m32,
            m10 * rhs.m03 + m11 * rhs.m13 + m12 * rhs.m23 + m13 * rhs.m33,
            m20 * rhs.m00 + m21 * rhs.m10 + m22 * rhs.m20 + m23 * rhs.m30,
            m20 * rhs.m01 + m21 * rhs.m11 + m22 * rhs.m21 + m23 * rhs.m31,
            m20 * rhs.m02 + m21 * rhs.m12 + m22 * rhs.m22 + m23 * rhs.m32,
            m20 * rhs.m03 + m21 * rhs.m13 + m22 * rhs.m23 + m23 * rhs.m33,
            rhs.m30,
            rhs.m31,
            rhs.m32,
            rhs.m33
        );
    }
    
    //! Set translation elements
    void setTranslation(const Vector3& translation)
    {
        m03 = translation.mX;
        m13 = translation.mY;
        m23 = translation.mZ;
    }
    
    //! Set rotation elements from a 3x3 matrix
    void setRotation(const Matrix3& rotation)
    {
        m00 = rotation.m00;
        m01 = rotation.m01;
        m02 = rotation.m02;
        m10 = rotation.m10;
        m11 = rotation.m11;
        m12 = rotation.m12;
        m20 = rotation.m20;
        m21 = rotation.m21;
        m22 = rotation.m22;
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
    
    //! Define from translation, rotation and uniform scale
    void define(const Vector3& translation, const Quaternion& rotation, float scale);
    //! Define from translation, rotation matrix and uniform scale
    void define(const Vector3& translation, const Matrix3& rotation, float scale);
    //! Define from translation, rotation and nonuniform scale
    void define(const Vector3& translation, const Quaternion& rotation, const Vector3& scale);
    //! Define from translation, rotation matrix and nonuniform scale
    void define(const Vector3& translation, const Matrix3& rotation, const Vector3& scale);
    
    //! Return the rotation matrix
    Matrix3 getRotationMatrix() const
    {
        return Matrix3(
            m00,
            m01,
            m02,
            m10,
            m11,
            m12,
            m20,
            m21,
            m22
        );
    }
    
    //! Return the translation elements
    Vector3 getTranslation() const
    {
        return Vector3(
            m03,
            m13,
            m23
        );
    }
    
    //! Return the scaling elements
    Vector3 getScale() const
    {
        return Vector3(
            m00,
            m11,
            m22
        );
    }
    
    //! Return inverse
    Matrix4x3 getInverse() const;
    
    //! Return float data
    const float* getData() const { return &m00; }
    
    float m00;
    float m01;
    float m02;
    float m03;
    float m10;
    float m11;
    float m12;
    float m13;
    float m20;
    float m21;
    float m22;
    float m23;
    
    //! Zero matrix
    static const Matrix4x3 sZero;
    //! Identity matrix
    static const Matrix4x3 sIdentity;
};

//! Multiply a 4x3 matrix with a scalar
inline Matrix4x3 operator * (float lhs, const Matrix4x3& rhs) { return rhs * lhs; }

//! Multiply a 4x3 matrix with a 4x4 matrix
inline Matrix4 operator * (const Matrix4& lhs, const Matrix4x3& rhs)
{
    return Matrix4(
        lhs.m00 * rhs.m00 + lhs.m01 * rhs.m10 + lhs.m02 * rhs.m20,
        lhs.m00 * rhs.m01 + lhs.m01 * rhs.m11 + lhs.m02 * rhs.m21,
        lhs.m00 * rhs.m02 + lhs.m01 * rhs.m12 + lhs.m02 * rhs.m22,
        lhs.m00 * rhs.m03 + lhs.m01 * rhs.m13 + lhs.m02 * rhs.m23 + lhs.m03,
        lhs.m10 * rhs.m00 + lhs.m11 * rhs.m10 + lhs.m12 * rhs.m20,
        lhs.m10 * rhs.m01 + lhs.m11 * rhs.m11 + lhs.m12 * rhs.m21,
        lhs.m10 * rhs.m02 + lhs.m11 * rhs.m12 + lhs.m12 * rhs.m22,
        lhs.m10 * rhs.m03 + lhs.m11 * rhs.m13 + lhs.m12 * rhs.m23 + lhs.m13,
        lhs.m20 * rhs.m00 + lhs.m21 * rhs.m10 + lhs.m22 * rhs.m20,
        lhs.m20 * rhs.m01 + lhs.m21 * rhs.m11 + lhs.m22 * rhs.m21,
        lhs.m20 * rhs.m02 + lhs.m21 * rhs.m12 + lhs.m22 * rhs.m22,
        lhs.m20 * rhs.m03 + lhs.m21 * rhs.m13 + lhs.m22 * rhs.m23 + lhs.m23,
        lhs.m30 * rhs.m00 + lhs.m31 * rhs.m10 + lhs.m32 * rhs.m20,
        lhs.m30 * rhs.m01 + lhs.m31 * rhs.m11 + lhs.m32 * rhs.m21,
        lhs.m30 * rhs.m02 + lhs.m31 * rhs.m12 + lhs.m32 * rhs.m22,
        lhs.m30 * rhs.m03 + lhs.m31 * rhs.m13 + lhs.m32 * rhs.m23 + lhs.m33
    );
}

#endif // MATH_MATRIX4X3_H
