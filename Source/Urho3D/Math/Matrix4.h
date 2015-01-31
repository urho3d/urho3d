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

#include "../Math/Quaternion.h"
#include "../Math/Vector4.h"

namespace Urho3D
{

class Matrix3x4;

/// 4x4 matrix for arbitrary linear transforms including projection.
class URHO3D_API Matrix4
{
public:
    /// Construct an identity matrix.
    Matrix4() :
        m00_(1.0f),
        m01_(0.0f),
        m02_(0.0f),
        m03_(0.0f),
        m10_(0.0f),
        m11_(1.0f),
        m12_(0.0f),
        m13_(0.0f),
        m20_(0.0f),
        m21_(0.0f),
        m22_(1.0f),
        m23_(0.0f),
        m30_(0.0f),
        m31_(0.0f),
        m32_(0.0f),
        m33_(1.0f)
    {
    }
    
    /// Copy-construct from another matrix.
    Matrix4(const Matrix4& matrix) :
        m00_(matrix.m00_),
        m01_(matrix.m01_),
        m02_(matrix.m02_),
        m03_(matrix.m03_),
        m10_(matrix.m10_),
        m11_(matrix.m11_),
        m12_(matrix.m12_),
        m13_(matrix.m13_),
        m20_(matrix.m20_),
        m21_(matrix.m21_),
        m22_(matrix.m22_),
        m23_(matrix.m23_),
        m30_(matrix.m30_),
        m31_(matrix.m31_),
        m32_(matrix.m32_),
        m33_(matrix.m33_)
    {
    }
    
    /// Copy-cnstruct from a 3x3 matrix and set the extra elements to identity.
    Matrix4(const Matrix3& matrix) :
        m00_(matrix.m00_),
        m01_(matrix.m01_),
        m02_(matrix.m02_),
        m03_(0.0f),
        m10_(matrix.m10_),
        m11_(matrix.m11_),
        m12_(matrix.m12_),
        m13_(0.0f),
        m20_(matrix.m20_),
        m21_(matrix.m21_),
        m22_(matrix.m22_),
        m23_(0.0f),
        m30_(0.0f),
        m31_(0.0f),
        m32_(0.0f),
        m33_(1.0f)
    {
    }
    
    // Construct from values.
    Matrix4(float v00, float v01, float v02, float v03,
            float v10, float v11, float v12, float v13,
            float v20, float v21, float v22, float v23,
            float v30, float v31, float v32, float v33) :
        m00_(v00),
        m01_(v01),
        m02_(v02),
        m03_(v03),
        m10_(v10),
        m11_(v11),
        m12_(v12),
        m13_(v13),
        m20_(v20),
        m21_(v21),
        m22_(v22),
        m23_(v23),
        m30_(v30),
        m31_(v31),
        m32_(v32),
        m33_(v33)
    {
    }
    
    /// Construct from a float array.
    Matrix4(const float* data) :
        m00_(data[0]),
        m01_(data[1]),
        m02_(data[2]),
        m03_(data[3]),
        m10_(data[4]),
        m11_(data[5]),
        m12_(data[6]),
        m13_(data[7]),
        m20_(data[8]),
        m21_(data[9]),
        m22_(data[10]),
        m23_(data[11]),
        m30_(data[12]),
        m31_(data[13]),
        m32_(data[14]),
        m33_(data[15])
    {
    }
    
    /// Assign from another matrix.
    Matrix4& operator = (const Matrix4& rhs)
    {
        m00_ = rhs.m00_;
        m01_ = rhs.m01_;
        m02_ = rhs.m02_;
        m03_ = rhs.m03_;
        m10_ = rhs.m10_;
        m11_ = rhs.m11_;
        m12_ = rhs.m12_;
        m13_ = rhs.m13_;
        m20_ = rhs.m20_;
        m21_ = rhs.m21_;
        m22_ = rhs.m22_;
        m23_ = rhs.m23_;
        m30_ = rhs.m30_;
        m31_ = rhs.m31_;
        m32_ = rhs.m32_;
        m33_ = rhs.m33_;
        return *this;
    }
    
    /// Assign from a 3x3 matrix. Set the extra elements to identity.
    Matrix4& operator = (const Matrix3& rhs)
    {
        m00_ = rhs.m00_;
        m01_ = rhs.m01_;
        m02_ = rhs.m02_;
        m03_ = 0.0f;
        m10_ = rhs.m10_;
        m11_ = rhs.m11_;
        m12_ = rhs.m12_;
        m13_ = 0.0f;
        m20_ = rhs.m20_;
        m21_ = rhs.m21_;
        m22_ = rhs.m22_;
        m23_ = 0.0f;
        m30_ = 0.0f;
        m31_ = 0.0f;
        m32_ = 0.0f;
        m33_ = 1.0f;
        return *this;
    }
    
    /// Test for equality with another matrix without epsilon.
    bool operator == (const Matrix4& rhs) const
    {
        const float* leftData = Data();
        const float* rightData = rhs.Data();
        
        for (unsigned i = 0; i < 16; ++i)
        {
            if (leftData[i] != rightData[i])
                return false;
        }
        
        return true;
    }
    
    /// Test for inequality with another matrix without epsilon.
    bool operator != (const Matrix4& rhs) const { return !(*this == rhs); }
    
    /// Multiply a Vector3 which is assumed to represent position.
    Vector3 operator * (const Vector3& rhs) const
    {
        float invW = 1.0f / (m30_ * rhs.x_ + m31_ * rhs.y_ + m32_ * rhs.z_ + m33_);
        
        return Vector3(
            (m00_ * rhs.x_ + m01_ * rhs.y_ + m02_ * rhs.z_ + m03_) * invW,
            (m10_ * rhs.x_ + m11_ * rhs.y_ + m12_ * rhs.z_ + m13_) * invW,
            (m20_ * rhs.x_ + m21_ * rhs.y_ + m22_ * rhs.z_ + m23_) * invW
        );
    }
    
    /// Multiply a Vector4.
    Vector4 operator * (const Vector4& rhs) const
    {
        return Vector4(
            m00_ * rhs.x_ + m01_ * rhs.y_ + m02_ * rhs.z_ + m03_ * rhs.w_,
            m10_ * rhs.x_ + m11_ * rhs.y_ + m12_ * rhs.z_ + m13_ * rhs.w_,
            m20_ * rhs.x_ + m21_ * rhs.y_ + m22_ * rhs.z_ + m23_ * rhs.w_,
            m30_ * rhs.x_ + m31_ * rhs.y_ + m32_ * rhs.z_ + m33_ * rhs.w_
        );
    }
    
    /// Add a matrix.
    Matrix4 operator + (const Matrix4& rhs) const
    {
        return Matrix4(
            m00_ + rhs.m00_,
            m01_ + rhs.m01_,
            m02_ + rhs.m02_,
            m03_ + rhs.m03_,
            m10_ + rhs.m10_,
            m11_ + rhs.m11_,
            m12_ + rhs.m12_,
            m13_ + rhs.m13_,
            m20_ + rhs.m20_,
            m21_ + rhs.m21_,
            m22_ + rhs.m22_,
            m23_ + rhs.m23_,
            m30_ + rhs.m30_,
            m31_ + rhs.m31_,
            m32_ + rhs.m32_,
            m33_ + rhs.m33_
        );
    }
    
    /// Subtract a matrix.
    Matrix4 operator - (const Matrix4& rhs) const
    {
        return Matrix4(
            m00_ - rhs.m00_,
            m01_ - rhs.m01_,
            m02_ - rhs.m02_,
            m03_ - rhs.m03_,
            m10_ - rhs.m10_,
            m11_ - rhs.m11_,
            m12_ - rhs.m12_,
            m13_ - rhs.m13_,
            m20_ - rhs.m20_,
            m21_ - rhs.m21_,
            m22_ - rhs.m22_,
            m23_ - rhs.m23_,
            m30_ - rhs.m30_,
            m31_ - rhs.m31_,
            m32_ - rhs.m32_,
            m33_ - rhs.m33_
        );
    }
    
    /// Multiply with a scalar.
    Matrix4 operator * (float rhs) const
    {
        return Matrix4(
            m00_ * rhs,
            m01_ * rhs,
            m02_ * rhs,
            m03_ * rhs,
            m10_ * rhs,
            m11_ * rhs,
            m12_ * rhs,
            m13_ * rhs,
            m20_ * rhs,
            m21_ * rhs,
            m22_ * rhs,
            m23_ * rhs,
            m30_ * rhs,
            m31_ * rhs,
            m32_ * rhs,
            m33_ * rhs
        );
    }
    
    /// Multiply a matrix.
    Matrix4 operator * (const Matrix4& rhs) const
    {
        return Matrix4(
            m00_ * rhs.m00_ + m01_ * rhs.m10_ + m02_ * rhs.m20_ + m03_ * rhs.m30_,
            m00_ * rhs.m01_ + m01_ * rhs.m11_ + m02_ * rhs.m21_ + m03_ * rhs.m31_,
            m00_ * rhs.m02_ + m01_ * rhs.m12_ + m02_ * rhs.m22_ + m03_ * rhs.m32_,
            m00_ * rhs.m03_ + m01_ * rhs.m13_ + m02_ * rhs.m23_ + m03_ * rhs.m33_,
            m10_ * rhs.m00_ + m11_ * rhs.m10_ + m12_ * rhs.m20_ + m13_ * rhs.m30_,
            m10_ * rhs.m01_ + m11_ * rhs.m11_ + m12_ * rhs.m21_ + m13_ * rhs.m31_,
            m10_ * rhs.m02_ + m11_ * rhs.m12_ + m12_ * rhs.m22_ + m13_ * rhs.m32_,
            m10_ * rhs.m03_ + m11_ * rhs.m13_ + m12_ * rhs.m23_ + m13_ * rhs.m33_,
            m20_ * rhs.m00_ + m21_ * rhs.m10_ + m22_ * rhs.m20_ + m23_ * rhs.m30_,
            m20_ * rhs.m01_ + m21_ * rhs.m11_ + m22_ * rhs.m21_ + m23_ * rhs.m31_,
            m20_ * rhs.m02_ + m21_ * rhs.m12_ + m22_ * rhs.m22_ + m23_ * rhs.m32_,
            m20_ * rhs.m03_ + m21_ * rhs.m13_ + m22_ * rhs.m23_ + m23_ * rhs.m33_,
            m30_ * rhs.m00_ + m31_ * rhs.m10_ + m32_ * rhs.m20_ + m33_ * rhs.m30_,
            m30_ * rhs.m01_ + m31_ * rhs.m11_ + m32_ * rhs.m21_ + m33_ * rhs.m31_,
            m30_ * rhs.m02_ + m31_ * rhs.m12_ + m32_ * rhs.m22_ + m33_ * rhs.m32_,
            m30_ * rhs.m03_ + m31_ * rhs.m13_ + m32_ * rhs.m23_ + m33_ * rhs.m33_
        );
    }
    
    /// Multiply with a 3x4 matrix.
    Matrix4 operator * (const Matrix3x4& rhs) const;
    
    /// Set translation elements.
    void SetTranslation(const Vector3& translation)
    {
        m03_ = translation.x_;
        m13_ = translation.y_;
        m23_ = translation.z_;
    }
    
    /// Set rotation elements from a 3x3 matrix.
    void SetRotation(const Matrix3& rotation)
    {
        m00_ = rotation.m00_;
        m01_ = rotation.m01_;
        m02_ = rotation.m02_;
        m10_ = rotation.m10_;
        m11_ = rotation.m11_;
        m12_ = rotation.m12_;
        m20_ = rotation.m20_;
        m21_ = rotation.m21_;
        m22_ = rotation.m22_;
    }
    
    // Set scaling elements.
    void SetScale(const Vector3& scale)
    {
        m00_ = scale.x_;
        m11_ = scale.y_;
        m22_ = scale.z_;
    }
    
    // Set uniform scaling elements.
    void SetScale(float scale)
    {
        m00_ = scale;
        m11_ = scale;
        m22_ = scale;
    }
    
    /// Return the combined rotation and scaling matrix.
    Matrix3 ToMatrix3() const
    {
        return Matrix3(
            m00_,
            m01_,
            m02_,
            m10_,
            m11_,
            m12_,
            m20_,
            m21_,
            m22_
        );
    }
    
    /// Return the rotation matrix with scaling removed.
    Matrix3 RotationMatrix() const
    {
        Vector3 invScale(
            1.0f / sqrtf(m00_ * m00_ + m10_ * m10_ + m20_ * m20_),
            1.0f / sqrtf(m01_ * m01_ + m11_ * m11_ + m21_ * m21_),
            1.0f / sqrtf(m02_ * m02_ + m12_ * m12_ + m22_ * m22_)
        );
        
        return ToMatrix3().Scaled(invScale);
    }
    
    /// Return the translation part.
    Vector3 Translation() const
    {
        return Vector3(
            m03_,
            m13_,
            m23_
        );
    }
    
    /// Return the rotation part.
    Quaternion Rotation() const { return Quaternion(RotationMatrix()); }
    
    /// Return the scaling part
    Vector3 Scale() const
    {
        return Vector3(
            sqrtf(m00_ * m00_ + m10_ * m10_ + m20_ * m20_),
            sqrtf(m01_ * m01_ + m11_ * m11_ + m21_ * m21_),
            sqrtf(m02_ * m02_ + m12_ * m12_ + m22_ * m22_)
        );
    }
    
    /// Return transpose
    Matrix4 Transpose() const
    {
        return Matrix4(
            m00_,
            m10_,
            m20_,
            m30_,
            m01_,
            m11_,
            m21_,
            m31_,
            m02_,
            m12_,
            m22_,
            m32_,
            m03_,
            m13_,
            m23_,
            m33_
        );
    }
    
    /// Test for equality with another matrix with epsilon.
    bool Equals(const Matrix4& rhs) const
    {
        const float* leftData = Data();
        const float* rightData = rhs.Data();
        
        for (unsigned i = 0; i < 16; ++i)
        {
            if (!Urho3D::Equals(leftData[i], rightData[i]))
                return false;
        }
        
        return true;
    }
    
    /// Return decomposition to translation, rotation and scale.
    void Decompose(Vector3& translation, Quaternion& rotation, Vector3& scale) const;
    /// Return inverse.
    Matrix4 Inverse() const;
    
    /// Return float data
    const float* Data() const { return &m00_; }
    /// Return as string.
    String ToString() const;
    
    float m00_;
    float m01_;
    float m02_;
    float m03_;
    float m10_;
    float m11_;
    float m12_;
    float m13_;
    float m20_;
    float m21_;
    float m22_;
    float m23_;
    float m30_;
    float m31_;
    float m32_;
    float m33_;
    
    /// Bulk transpose matrices.
    static void BulkTranspose(float* dest, const float* src, unsigned count)
    {
        for (unsigned i = 0; i < count; ++i)
        {
            dest[0] = src[0];
            dest[1] = src[4];
            dest[2] = src[8];
            dest[3] = src[12];
            dest[4] = src[1];
            dest[5] = src[5];
            dest[6] = src[9];
            dest[7] = src[13];
            dest[8] = src[2];
            dest[9] = src[6];
            dest[10] = src[10];
            dest[11] = src[14];
            dest[12] = src[3];
            dest[13] = src[7];
            dest[14] = src[11];
            dest[15] = src[15];
            
            dest += 16;
            src += 16;
        }
    }
    
    /// Zero matrix.
    static const Matrix4 ZERO;
    /// Identity matrix.
    static const Matrix4 IDENTITY;
};

/// Multiply a 4x4 matrix with a scalar
inline Matrix4 operator * (float lhs, const Matrix4& rhs) { return rhs * lhs; }

}
