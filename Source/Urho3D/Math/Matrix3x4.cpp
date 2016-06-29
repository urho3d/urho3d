//
// Copyright (c) 2008-2016 the Urho3D project.
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

#include <cstdio>

#include "../DebugNew.h"

namespace Urho3D
{

const Matrix3x4 Matrix3x4::ZERO(
    0.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f);

const Matrix3x4 Matrix3x4::IDENTITY;

void Matrix3x4::Decompose(Vector3& translation, Quaternion& rotation, Vector3& scale) const
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

Matrix3x4 Matrix3x4::Inverse() const
{
    float det = m00_ * m11_ * m22_ +
                m10_ * m21_ * m02_ +
                m20_ * m01_ * m12_ -
                m20_ * m11_ * m02_ -
                m10_ * m01_ * m22_ -
                m00_ * m21_ * m12_;

    float invDet = 1.0f / det;
    Matrix3x4 ret;

    ret.m00_ = (m11_ * m22_ - m21_ * m12_) * invDet;
    ret.m01_ = -(m01_ * m22_ - m21_ * m02_) * invDet;
    ret.m02_ = (m01_ * m12_ - m11_ * m02_) * invDet;
    ret.m03_ = -(m03_ * ret.m00_ + m13_ * ret.m01_ + m23_ * ret.m02_);
    ret.m10_ = -(m10_ * m22_ - m20_ * m12_) * invDet;
    ret.m11_ = (m00_ * m22_ - m20_ * m02_) * invDet;
    ret.m12_ = -(m00_ * m12_ - m10_ * m02_) * invDet;
    ret.m13_ = -(m03_ * ret.m10_ + m13_ * ret.m11_ + m23_ * ret.m12_);
    ret.m20_ = (m10_ * m21_ - m20_ * m11_) * invDet;
    ret.m21_ = -(m00_ * m21_ - m20_ * m01_) * invDet;
    ret.m22_ = (m00_ * m11_ - m10_ * m01_) * invDet;
    ret.m23_ = -(m03_ * ret.m20_ + m13_ * ret.m21_ + m23_ * ret.m22_);

    return ret;
}

String Matrix3x4::ToString() const
{
    char tempBuffer[MATRIX_CONVERSION_BUFFER_LENGTH];
    sprintf(tempBuffer, "%g %g %g %g %g %g %g %g %g %g %g %g", m00_, m01_, m02_, m03_, m10_, m11_, m12_, m13_, m20_, m21_, m22_,
        m23_);
    return String(tempBuffer);
}

}
