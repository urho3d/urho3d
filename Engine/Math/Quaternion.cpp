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
    fromAngleAxis(angle, Axis);
}

Quaternion::Quaternion(const Vector3& euler)
{
    fromEulerAngles(euler);
}

Quaternion::Quaternion(float angleX, float angleY, float angleZ)
{
    fromEulerAngles(Vector3(angleX, angleY, angleZ));
}

Quaternion::Quaternion(const Vector3& start, const Vector3& end)
{
    fromRotationTo(start, end);
}

void Quaternion::fromAngleAxis(float angle, const Vector3& axis)
{
    Vector3 normAxis = axis.getNormalized();
    float sinAngle = sinf((angle * M_DEGTORAD) * 0.5f);
    float cosAngle = cosf((angle * M_DEGTORAD) * 0.5f);
    
    mW = cosAngle;
    mX = normAxis.mX * sinAngle;
    mY = normAxis.mY * sinAngle;
    mZ = normAxis.mZ * sinAngle;
}

void Quaternion::fromEulerAngles(const Vector3& euler)
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

void Quaternion::fromRotationTo(const Vector3& start, const Vector3& end)
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
        mW = s * 0.5f;
    }
    else
    {
        Vector3 tempAxis = Vector3::sRight.crossProduct(normStart);
        if (tempAxis.getLength() < M_EPSILON)
            tempAxis = Vector3::sUp.crossProduct(normStart);
        
        fromAngleAxis(180.0f, tempAxis);
    }
}

Vector3 Quaternion::getEulerAngles() const
{
    // Derivation from http://www.geometrictools.com/Documentation/EulerAngles.pdf
    
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

