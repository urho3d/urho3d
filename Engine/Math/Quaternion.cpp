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
#include "Quaternion.h"

const Quaternion Quaternion::sIdentity(1.0f, 0.0f, 0.0f, 0.0f);

Quaternion::Quaternion(float angle, const Vector3& Axis)
{
    define(angle, Axis);
}

Quaternion::Quaternion(const Vector3& euler)
{
    define(euler);
}

Quaternion::Quaternion(float angleX, float angleY, float angleZ)
{
    define(Vector3(angleX, angleY, angleZ));
}

Quaternion::Quaternion(const Vector3& start, const Vector3& end)
{
    define(start, end);
}

Quaternion::Quaternion(const Matrix3& matrix)
{
    define(matrix);
}

void Quaternion::define(float angle, const Vector3& axis)
{
    Vector3 normAxis = axis.getNormalized();
    float sinAngle = sinf((angle * M_DEGTORAD) * 0.5f);
    float cosAngle = cosf((angle * M_DEGTORAD) * 0.5f);
    
    mW = cosAngle;
    mX = normAxis.mX * sinAngle;
    mY = normAxis.mY * sinAngle;
    mZ = normAxis.mZ * sinAngle;
}

void Quaternion::define(const Vector3& euler)
{
    // Order of rotations: Z first, then X, then Y (mimics typical FPS camera with gimbal lock at top/bottom)
    float sinX = sinf((euler.mX * M_DEGTORAD) * 0.5f);
    float cosX = cosf((euler.mX * M_DEGTORAD) * 0.5f);
    float sinY = sinf((euler.mY * M_DEGTORAD) * 0.5f);
    float cosY = cosf((euler.mY * M_DEGTORAD) * 0.5f);
    float sinZ = sinf((euler.mZ * M_DEGTORAD) * 0.5f);
    float cosZ = cosf((euler.mZ * M_DEGTORAD) * 0.5f);
    
    mW = cosY * cosX * cosZ + sinY * sinX * sinZ;
    mX = cosY * sinX * cosZ + sinY * cosX * sinZ;
    mY = sinY * cosX * cosZ - cosY * sinX * sinZ;
    mZ = cosY * cosX * sinZ - sinY * sinX * cosZ;
}

void Quaternion::define(const Vector3& start, const Vector3& end)
{
    Vector3 normStart = start.getNormalized();
    Vector3 normEnd = end.getNormalized();
    
    float d = normStart.dotProduct(normEnd);
    
    if (d > -1.0f + M_EPSILON)
    {
        Vector3 c = normStart.crossProduct(normEnd);
        float s = sqrtf((1.0f + d) * 2.0f);
        float invS = 1.0f / s;
        
        mX = c.mX * invS;
        mY = c.mY * invS;
        mZ = c.mZ * invS;
        mW = 0.5f * s;
    }
    else
    {
        Vector3 tempAxis = Vector3::sRight.crossProduct(normStart);
        if (tempAxis.getLength() < M_EPSILON)
            tempAxis = Vector3::sUp.crossProduct(normStart);
        
        define(180.0f, tempAxis);
    }
}

void Quaternion::define(const Matrix3& matrix)
{
    float t = matrix.m00 + matrix.m11 + matrix.m22 + 1.0f;
    if (t > 0.0f)
    {
        float s = sqrtf(t) * 2.0f;
        float invS = 1.0f / s;
        
        mX = (matrix.m21 - matrix.m12) * invS;
        mY = (matrix.m02 - matrix.m20) * invS;
        mZ = (matrix.m10 - matrix.m01) * invS;
        mW = 0.25f * s;
    }
    else
    {
        if ((matrix.m00 > matrix.m11) && (matrix.m00 > matrix.m22))
        {
            float s = sqrtf(1.0f + matrix.m00 - matrix.m11 - matrix.m22) * 2.0f;
            float invS = 1.0f / s;
            
            mX = 0.25f * s;
            mY = (matrix.m01 + matrix.m10) * invS;
            mZ = (matrix.m20 + matrix.m02) * invS;
            mW = (matrix.m21 - matrix.m12) * invS;
        }
        else if (matrix.m11 > matrix.m22)
        {
            float s = sqrtf(1.0f + matrix.m11 - matrix.m00 - matrix.m22) * 2.0f;
            float invS = 1.0f / s;
            
            mX = (matrix.m01 + matrix.m10) * invS;
            mY = 0.25f * s;
            mZ = (matrix.m12 + matrix.m21) * invS;
            mW = (matrix.m02 - matrix.m20) * invS;
        }
        else
        {
            float s = sqrtf(1.0f + matrix.m22 - matrix.m00 - matrix.m11) * 2.0f;
            float invS = 1.0f / s;
            
            mX = (matrix.m02 + matrix.m20) * invS;
            mY = (matrix.m12 + matrix.m21) * invS;
            mZ = 0.25f * s;
            mW = (matrix.m10 - matrix.m01) * invS;
        }
    }
}

Vector3 Quaternion::getEulerAngles() const
{
    // Derivation from http://www.geometrictools.com/Documentation/EulerAngles.pdf
    // Order of rotations: Z first, then X, then Y
    float check = 2.0f * (-mY * mZ + mW * mX);
    
    if (check < -0.995f)
    {
        return Vector3(
            -90.0f,
            0.0f,
            -atan2f(2.0f * (mX * mZ - mW * mY), 1.0f - 2.0f * (mY * mY + mZ * mZ)) * M_RADTODEG
        );
    }
    else if (check > 0.995f)
    {
        return Vector3(
            90.0f,
            0.0f,
            atan2f(2.0f * (mX * mZ - mW * mY), 1.0f - 2.0f * (mY * mY + mZ * mZ)) * M_RADTODEG
        );
    }
    else
    {
        return Vector3(
            asinf(check) * M_RADTODEG,
            atan2f(2.0f * (mX * mZ + mW * mY), 1.0f - 2.0f * (mX * mX + mY * mY)) * M_RADTODEG,
            atan2f(2.0f * (mX * mY + mW * mZ), 1.0f - 2.0f * (mX * mX + mZ * mZ)) * M_RADTODEG
        );
    }
}

float Quaternion::getYaw() const
{
    return getEulerAngles().mY;
}

float Quaternion::getPitch() const
{
    return getEulerAngles().mX;
}

float Quaternion::getRoll() const
{
    return getEulerAngles().mZ;
}

Matrix3 Quaternion::getRotationMatrix() const
{
    return Matrix3(
        1.0f - 2.0f * mY * mY - 2.0f * mZ * mZ,
        2.0f * mX * mY - 2.0f * mW * mZ,
        2.0f * mX * mZ + 2.0f * mW * mY,
        2.0f * mX * mY + 2.0f * mW * mZ,
        1.0f - 2.0f * mX * mX - 2.0f * mZ * mZ,
        2.0f * mY * mZ - 2.0f * mW * mX,
        2.0f * mX * mZ - 2.0f * mW * mY,
        2.0f * mY * mZ + 2.0f * mW * mX,
        1.0f - 2.0f * mX * mX - 2.0f * mY * mY
    );
}

Quaternion Quaternion::slerp(Quaternion rhs, float t) const
{
    float cosAngle = dotProduct(rhs);
    
    // Enable shortest path rotation
    if (cosAngle < 0.0f)
    {
        cosAngle = -cosAngle;
        rhs = -rhs;
    }
    
    float angle = acosf(cosAngle);
    float sinAngle = sinf(angle);
    
    float t1, t2;
    
    if (sinAngle > 0.001f)
    {
        t1 = sinf((1.0f - t) * angle) / sinAngle;
        t2 = sinf(t * angle) / sinAngle;
    }
    else
    {
        t1 = 1.0f - t;
        t2 = t;
    }
    
    return *this * t1 + rhs * t2;
}

