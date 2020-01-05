//
// Copyright (c) 2008-2020 the Urho3D project.
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

#include "../Precompiled.h"

#include "../Math/Matrix3x4.h"
#include "../Math/Matrix4.h"

#include <cstdio>

#include "../DebugNew.h"

namespace Urho3D
{

const Matrix4 Matrix4::ZERO(
    0.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f);

const Matrix4 Matrix4::IDENTITY;

Matrix4 Matrix4::operator *(const Matrix3x4& rhs) const
{
    return Matrix4(
        m00_ * rhs.m00_ + m01_ * rhs.m10_ + m02_ * rhs.m20_,
        m00_ * rhs.m01_ + m01_ * rhs.m11_ + m02_ * rhs.m21_,
        m00_ * rhs.m02_ + m01_ * rhs.m12_ + m02_ * rhs.m22_,
        m00_ * rhs.m03_ + m01_ * rhs.m13_ + m02_ * rhs.m23_ + m03_,
        m10_ * rhs.m00_ + m11_ * rhs.m10_ + m12_ * rhs.m20_,
        m10_ * rhs.m01_ + m11_ * rhs.m11_ + m12_ * rhs.m21_,
        m10_ * rhs.m02_ + m11_ * rhs.m12_ + m12_ * rhs.m22_,
        m10_ * rhs.m03_ + m11_ * rhs.m13_ + m12_ * rhs.m23_ + m13_,
        m20_ * rhs.m00_ + m21_ * rhs.m10_ + m22_ * rhs.m20_,
        m20_ * rhs.m01_ + m21_ * rhs.m11_ + m22_ * rhs.m21_,
        m20_ * rhs.m02_ + m21_ * rhs.m12_ + m22_ * rhs.m22_,
        m20_ * rhs.m03_ + m21_ * rhs.m13_ + m22_ * rhs.m23_ + m23_,
        m30_ * rhs.m00_ + m31_ * rhs.m10_ + m32_ * rhs.m20_,
        m30_ * rhs.m01_ + m31_ * rhs.m11_ + m32_ * rhs.m21_,
        m30_ * rhs.m02_ + m31_ * rhs.m12_ + m32_ * rhs.m22_,
        m30_ * rhs.m03_ + m31_ * rhs.m13_ + m32_ * rhs.m23_ + m33_
    );
}

void Matrix4::Decompose(Vector3& translation, Quaternion& rotation, Vector3& scale) const
{
    translation.x_ = m03_;
    translation.y_ = m13_;
    translation.z_ = m23_;

    scale.x_ = sqrtf(m00_ * m00_ + m10_ * m10_ + m20_ * m20_);
    scale.y_ = sqrtf(m01_ * m01_ + m11_ * m11_ + m21_ * m21_);
    scale.z_ = sqrtf(m02_ * m02_ + m12_ * m12_ + m22_ * m22_);

    Vector3 invScale(1.0f / scale.x_, 1.0f / scale.y_, 1.0f / scale.z_);
    rotation = Quaternion(ToMatrix3().Scaled(invScale));
}

Matrix4 Matrix4::Inverse() const
{
    float v0 = m20_ * m31_ - m21_ * m30_;
    float v1 = m20_ * m32_ - m22_ * m30_;
    float v2 = m20_ * m33_ - m23_ * m30_;
    float v3 = m21_ * m32_ - m22_ * m31_;
    float v4 = m21_ * m33_ - m23_ * m31_;
    float v5 = m22_ * m33_ - m23_ * m32_;

    float i00 = (v5 * m11_ - v4 * m12_ + v3 * m13_);
    float i10 = -(v5 * m10_ - v2 * m12_ + v1 * m13_);
    float i20 = (v4 * m10_ - v2 * m11_ + v0 * m13_);
    float i30 = -(v3 * m10_ - v1 * m11_ + v0 * m12_);

    float invDet = 1.0f / (i00 * m00_ + i10 * m01_ + i20 * m02_ + i30 * m03_);

    i00 *= invDet;
    i10 *= invDet;
    i20 *= invDet;
    i30 *= invDet;

    float i01 = -(v5 * m01_ - v4 * m02_ + v3 * m03_) * invDet;
    float i11 = (v5 * m00_ - v2 * m02_ + v1 * m03_) * invDet;
    float i21 = -(v4 * m00_ - v2 * m01_ + v0 * m03_) * invDet;
    float i31 = (v3 * m00_ - v1 * m01_ + v0 * m02_) * invDet;

    v0 = m10_ * m31_ - m11_ * m30_;
    v1 = m10_ * m32_ - m12_ * m30_;
    v2 = m10_ * m33_ - m13_ * m30_;
    v3 = m11_ * m32_ - m12_ * m31_;
    v4 = m11_ * m33_ - m13_ * m31_;
    v5 = m12_ * m33_ - m13_ * m32_;

    float i02 = (v5 * m01_ - v4 * m02_ + v3 * m03_) * invDet;
    float i12 = -(v5 * m00_ - v2 * m02_ + v1 * m03_) * invDet;
    float i22 = (v4 * m00_ - v2 * m01_ + v0 * m03_) * invDet;
    float i32 = -(v3 * m00_ - v1 * m01_ + v0 * m02_) * invDet;

    v0 = m21_ * m10_ - m20_ * m11_;
    v1 = m22_ * m10_ - m20_ * m12_;
    v2 = m23_ * m10_ - m20_ * m13_;
    v3 = m22_ * m11_ - m21_ * m12_;
    v4 = m23_ * m11_ - m21_ * m13_;
    v5 = m23_ * m12_ - m22_ * m13_;

    float i03 = -(v5 * m01_ - v4 * m02_ + v3 * m03_) * invDet;
    float i13 = (v5 * m00_ - v2 * m02_ + v1 * m03_) * invDet;
    float i23 = -(v4 * m00_ - v2 * m01_ + v0 * m03_) * invDet;
    float i33 = (v3 * m00_ - v1 * m01_ + v0 * m02_) * invDet;

    return Matrix4(
        i00, i01, i02, i03,
        i10, i11, i12, i13,
        i20, i21, i22, i23,
        i30, i31, i32, i33);
}

String Matrix4::ToString() const
{
    char tempBuffer[MATRIX_CONVERSION_BUFFER_LENGTH];
    sprintf(tempBuffer, "%g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g", m00_, m01_, m02_, m03_, m10_, m11_, m12_, m13_, m20_,
        m21_, m22_, m23_, m30_, m31_, m32_, m33_);
    return String(tempBuffer);
}

}
