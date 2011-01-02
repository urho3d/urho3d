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

#include "Precompiled.h"
#include "Matrix4x3.h"

const Matrix4x3 Matrix4x3::sZero(
    0.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f);

const Matrix4x3 Matrix4x3::sIdentity(
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f);

Matrix4x3::Matrix4x3(const Vector3& translation, const Quaternion& rotation, float scale)
{
    define(translation, rotation, scale);
}

Matrix4x3::Matrix4x3(const Vector3& translation, const Matrix3& rotation, float scale)
{
    define(translation, rotation, scale);
}

Matrix4x3::Matrix4x3(const Vector3& translation, const Quaternion& rotation, const Vector3& scale)
{
    define(translation, rotation, scale);
}

Matrix4x3::Matrix4x3(const Vector3& translation, const Matrix3& rotation, const Vector3& scale)
{
    define(translation, rotation, scale);
}

void Matrix4x3::define(const Vector3& translation, const Quaternion& rotation, float scale)
{
    Matrix3 scaleMatrix(Matrix3::sIdentity);
    scaleMatrix.setScale(scale);
    
    *this = rotation.getRotationMatrix() * scaleMatrix;
    setTranslation(translation);
}

void Matrix4x3::define(const Vector3& translation, const Matrix3& rotation, float scale)
{
    Matrix3 scaleMatrix(Matrix3::sIdentity);
    scaleMatrix.setScale(scale);
    
    *this = rotation * scaleMatrix;
    setTranslation(translation);
}

void Matrix4x3::define(const Vector3& translation, const Quaternion& rotation, const Vector3& scale)
{
    Matrix3 scaleMatrix(Matrix3::sIdentity);
    scaleMatrix.setScale(scale);
    
    *this = rotation.getRotationMatrix() * scaleMatrix;
    setTranslation(translation);
}

void Matrix4x3::define(const Vector3& translation, const Matrix3& rotation, const Vector3& scale)
{
    Matrix3 scaleMatrix(Matrix3::sIdentity);
    scaleMatrix.setScale(scale);
    
    *this = rotation * scaleMatrix;
    setTranslation(translation);
}

Matrix4x3 Matrix4x3::getInverse() const
{
    float det = m00 * m11 * m22 +
        m10 * m21 * m02 +
        m20 * m01 * m12 -
        m20 * m11 * m02 -
        m10 * m01 * m22 -
        m00 * m21 * m12;

    float invDet = 1.0f / det;

    Matrix4x3 out;

    out.m00 = (m11 * m22 - m21 * m12) * invDet;
    out.m01 = -(m01 * m22 - m21 * m02) * invDet;
    out.m02 = (m01 * m12 - m11 * m02) * invDet;
    out.m03 = -(m03 * out.m00 + m13 * out.m01 + m23 * out.m02);
    out.m10 = -(m10 * m22 - m20 * m12) * invDet;
    out.m11 = (m00 * m22 - m20 * m02) * invDet;
    out.m12 = -(m00 * m12 - m10 * m02) * invDet;
    out.m13 = -(m03 * out.m10 + m13 * out.m11 + m23 * out.m12);
    out.m20 = (m10 * m21 - m20 * m11) * invDet;
    out.m21 = -(m00 * m21 - m20 * m01) * invDet;
    out.m22 = (m00 * m11 - m10 * m01) * invDet;
    out.m23 = -(m03 * out.m20 + m13 * out.m21 + m23 * out.m22);
    
    return out;
}
