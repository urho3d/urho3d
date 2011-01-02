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

Quaternion::Quaternion(float angleX, float angleY, float angleZ)
{
    fromEulerAngles(angleX, angleY, angleZ);
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

void Quaternion::fromEulerAngles(float angleX, float angleY, float angleZ)
{
    // Order of rotations: Z first, then X, then Y (mimics typical FPS camera with gimbal lock at top/bottom)
    float sinX = sinf((angleX * M_DEGTORAD) * 0.5f);
    float cosX = cosf((angleX * M_DEGTORAD) * 0.5f);
    float sinY = sinf((angleY * M_DEGTORAD) * 0.5f);
    float cosY = cosf((angleY * M_DEGTORAD) * 0.5f);
    float sinZ = sinf((angleZ * M_DEGTORAD) * 0.5f);
    float cosZ = cosf((angleZ * M_DEGTORAD) * 0.5f);
    
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

void Quaternion::getEulerAngles(float& angleX, float& angleY, float& angleZ) const
{
    // Check for singularities
    float check = mX * mY + mZ * mW;
    if (check > 0.499f)
    {
        angleX = 2.0f * atan2f(mX, mW) * M_RADTODEG;
        angleY = 90.0f;
        angleZ = 0.0f;
        return;
    }
    if (check < -0.499f)
    {
        angleX = -2.0f * atan2f(mX, mW) * M_RADTODEG;
        angleY = -90.0f;
        angleZ = 0.0f;
        return;
    }
    
    float xSquared = mX * mX;
    float ySquared = mY * mY;
    float zSquared = mZ * mZ;
    
    angleX = atan2f(2.0f * mY * mW - 2.0f * mX * mZ, 1.0f - 2.0f * ySquared - 2.0f * zSquared) * M_RADTODEG;
    angleY = asinf(2.0f * check) * M_RADTODEG;
    angleZ = atan2f(2.0f * mX * mW - 2.0f * mY * mZ, 1.0f - 2.0f * xSquared - 2.0f * zSquared) * M_RADTODEG;
}

float Quaternion::getYaw() const
{
    float x, y, z;
    getEulerAngles(x, y, z);
    return x;
}

float Quaternion::getPitch() const
{
    float x, y, z;
    getEulerAngles(x, y, z);
    return y;
}

float Quaternion::getRoll() const
{
    float x, y, z;
    getEulerAngles(x, y, z);
    return z;
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

