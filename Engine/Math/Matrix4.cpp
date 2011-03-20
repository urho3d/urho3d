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
#include "Matrix4.h"

const Matrix4 Matrix4::sZero(
    0.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f);

const Matrix4 Matrix4::sIdentity(
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f);

void Matrix4::getDecomposition(Vector3& translation, Quaternion& rotation, Vector3& scale) const
{
    translation.mX = m03;
    translation.mY = m13;
    translation.mZ = m23;
    
    Vector3 row1(m00, m10, m20);
    Vector3 row2(m01, m11, m21);
    Vector3 row3(m02, m12, m22);
    
    scale.mX = row1.getLength();
    scale.mY = row2.getLength();
    scale.mZ = row3.getLength();
    
    // Remove scaling from the 3x3 matrix to get rotation
    row1 /= scale.mX;
    row2 /= scale.mY;
    row3 /= scale.mZ;
    rotation.define(Matrix3(row1.mX, row2.mX, row3.mX, row1.mY, row2.mY, row3.mY, row1.mZ, row2.mZ, row3.mZ));
}

Matrix4 Matrix4::getInverse() const
{
    float v0 = m20 * m31 - m21 * m30;
    float v1 = m20 * m32 - m22 * m30;
    float v2 = m20 * m33 - m23 * m30;
    float v3 = m21 * m32 - m22 * m31;
    float v4 = m21 * m33 - m23 * m31;
    float v5 = m22 * m33 - m23 * m32;
    
    float i00 = (v5 * m11 - v4 * m12 + v3 * m13);
    float i10 = -(v5 * m10 - v2 * m12 + v1 * m13);
    float i20 = (v4 * m10 - v2 * m11 + v0 * m13);
    float i30 = -(v3 * m10 - v1 * m11 + v0 * m12);
    
    float invDet = 1.0f / (i00 * m00 + i10 * m01 + i20 * m02 + i30 * m03);
    
    i00 *= invDet;
    i10 *= invDet;
    i20 *= invDet;
    i30 *= invDet;
    
    float i01 = -(v5 * m01 - v4 * m02 + v3 * m03) * invDet;
    float i11 = (v5 * m00 - v2 * m02 + v1 * m03) * invDet;
    float i21 = -(v4 * m00 - v2 * m01 + v0 * m03) * invDet;
    float i31 = (v3 * m00 - v1 * m01 + v0 * m02) * invDet;
    
    v0 = m10 * m31 - m11 * m30;
    v1 = m10 * m32 - m12 * m30;
    v2 = m10 * m33 - m13 * m30;
    v3 = m11 * m32 - m12 * m31;
    v4 = m11 * m33 - m13 * m31;
    v5 = m12 * m33 - m13 * m32;
    
    float i02 = (v5 * m01 - v4 * m02 + v3 * m03) * invDet;
    float i12 = -(v5 * m00 - v2 * m02 + v1 * m03) * invDet;
    float i22 = (v4 * m00 - v2 * m01 + v0 * m03) * invDet;
    float i32 = -(v3 * m00 - v1 * m01 + v0 * m02) * invDet;
    
    v0 = m21 * m10 - m20 * m11;
    v1 = m22 * m10 - m20 * m12;
    v2 = m23 * m10 - m20 * m13;
    v3 = m22 * m11 - m21 * m12;
    v4 = m23 * m11 - m21 * m13;
    v5 = m23 * m12 - m22 * m13;
    
    float i03 = -(v5 * m01 - v4 * m02 + v3 * m03) * invDet;
    float i13 = (v5 * m00 - v2 * m02 + v1 * m03) * invDet;
    float i23 = -(v4 * m00 - v2 * m01 + v0 * m03) * invDet;
    float i33 = (v3 * m00 - v1 * m01 + v0 * m02) * invDet;
    
    return Matrix4(
        i00, i01, i02, i03,
        i10, i11, i12, i13,
        i20, i21, i22, i23,
        i30, i31, i32, i33);
}
