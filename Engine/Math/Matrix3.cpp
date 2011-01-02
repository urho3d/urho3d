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
#include "Matrix3.h"

const Matrix3 Matrix3::sZero(
    0.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 0.0f);

const Matrix3 Matrix3::sIdentity(
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f);

void Matrix3::setRotation(float angle, const Vector3& axis)
{
    Vector3 normAxis = axis.getNormalized();
    float sinAngle = sinf(angle * M_DEGTORAD);
    float cosAngle = cosf(angle * M_DEGTORAD);
    
    m00 = normAxis.mX * normAxis.mX + cosAngle * (1.0f - normAxis.mX * normAxis.mX);
    m01 = normAxis.mX * normAxis.mY * (1.0f - cosAngle) - sinAngle * normAxis.mZ;
    m02 = normAxis.mX * normAxis.mZ * (1.0f - cosAngle) + sinAngle * normAxis.mY;
    m10 = normAxis.mX * normAxis.mY * (1.0f - cosAngle) + sinAngle * normAxis.mZ;
    m11 = normAxis.mY * normAxis.mY + cosAngle * (1.0f - normAxis.mY * normAxis.mY);
    m12 = normAxis.mY * normAxis.mZ * (1.0f - cosAngle) - sinAngle * normAxis.mX;
    m20 = normAxis.mX * normAxis.mZ * (1.0f - cosAngle) - sinAngle * normAxis.mY;
    m21 = normAxis.mY * normAxis.mZ * (1.0f - cosAngle) + sinAngle * normAxis.mX;
    m22 = normAxis.mZ * normAxis.mZ + cosAngle * (1.0f - normAxis.mZ * normAxis.mZ);
}

Matrix3 Matrix3::getInverse() const
{
    float det = m00 * m11 * m22 +
        m10 * m21 * m02 +
        m20 * m01 * m12 -
        m20 * m11 * m02 -
        m10 * m01 * m22 -
        m00 * m21 * m12;
    
    float invDet = 1.0f / det;
    
    return Matrix3(
        (m11 * m22 - m21 * m12) * invDet,
        -(m01 * m22 - m21 * m02) * invDet,
        (m01 * m12 - m11 * m02) * invDet,
        -(m10 * m22 - m20 * m12) * invDet,
        (m00 * m22 - m20 * m02) * invDet,
        -(m00 * m12 - m10 * m02) * invDet,
        (m10 * m21 - m20 * m11) * invDet,
        -(m00 * m21 - m20 * m01) * invDet,
        (m00 * m11 - m10 * m01) * invDet
    );
}
