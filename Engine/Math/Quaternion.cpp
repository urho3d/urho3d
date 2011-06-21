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

#include <cstdio>

const Quaternion Quaternion::IDENTITY;

Quaternion::Quaternion(float angle, const Vector3& axis)
{
    Vector3 normAxis = axis.Normalized();
    float sinAngle = sinf((angle * M_DEGTORAD) * 0.5f);
    float cosAngle = cosf((angle * M_DEGTORAD) * 0.5f);
    
    w_ = cosAngle;
    x_ = normAxis.x_ * sinAngle;
    y_ = normAxis.y_ * sinAngle;
    z_ = normAxis.z_ * sinAngle;
}

Quaternion::Quaternion(float x, float y, float z)
{
    // Order of rotations: Z first, then X, then Y (mimics typical FPS camera with gimbal lock at top/bottom)
    float sinX = sinf((x * M_DEGTORAD) * 0.5f);
    float cosX = cosf((x * M_DEGTORAD) * 0.5f);
    float sinY = sinf((y * M_DEGTORAD) * 0.5f);
    float cosY = cosf((y * M_DEGTORAD) * 0.5f);
    float sinZ = sinf((z * M_DEGTORAD) * 0.5f);
    float cosZ = cosf((z * M_DEGTORAD) * 0.5f);
    
    w_ = cosY * cosX * cosZ + sinY * sinX * sinZ;
    x_ = cosY * sinX * cosZ + sinY * cosX * sinZ;
    y_ = sinY * cosX * cosZ - cosY * sinX * sinZ;
    z_ = cosY * cosX * sinZ - sinY * sinX * cosZ;
}

Quaternion::Quaternion(const Vector3& start, const Vector3& end)
{
    Vector3 normStart = start.Normalized();
    Vector3 normEnd = end.Normalized();
    
    float d = normStart.DotProduct(normEnd);
    
    if (d > -1.0f + M_EPSILON)
    {
        Vector3 c = normStart.CrossProduct(normEnd);
        float s = sqrtf((1.0f + d) * 2.0f);
        float invS = 1.0f / s;
        
        x_ = c.x_ * invS;
        y_ = c.y_ * invS;
        z_ = c.z_ * invS;
        w_ = 0.5f * s;
    }
    else
    {
        Vector3 axis = Vector3::RIGHT.CrossProduct(normStart);
        if (axis.Length() < M_EPSILON)
            axis = Vector3::UP.CrossProduct(normStart);
        float angle = 180.0f;
        
        Vector3 normAxis = axis.Normalized();
        float sinAngle = sinf((angle * M_DEGTORAD) * 0.5f);
        float cosAngle = cosf((angle * M_DEGTORAD) * 0.5f);
        
        w_ = cosAngle;
        x_ = normAxis.x_ * sinAngle;
        y_ = normAxis.y_ * sinAngle;
        z_ = normAxis.z_ * sinAngle;
    }
}

Quaternion::Quaternion(const Matrix3& matrix)
{
    float t = matrix.m00_ + matrix.m11_ + matrix.m22_ + 1.0f;
    
    if (t > 0.001f)
    {
        float s = sqrtf(t) * 2.0f;
        float invS = 1.0f / s;
        
        x_ = (matrix.m21_ - matrix.m12_) * invS;
        y_ = (matrix.m02_ - matrix.m20_) * invS;
        z_ = (matrix.m10_ - matrix.m01_) * invS;
        w_ = 0.25f * s;
    }
    else
    {
        if (matrix.m00_ > matrix.m11_ && matrix.m00_ > matrix.m22_)
        {
            float s = sqrtf(1.0f + matrix.m00_ - matrix.m11_ - matrix.m22_) * 2.0f;
            float invS = 1.0f / s;
            
            x_ = 0.25f * s;
            y_ = (matrix.m01_ + matrix.m10_) * invS;
            z_ = (matrix.m20_ + matrix.m02_) * invS;
            w_ = (matrix.m21_ - matrix.m12_) * invS;
        }
        else if (matrix.m11_ > matrix.m22_)
        {
            float s = sqrtf(1.0f + matrix.m11_ - matrix.m00_ - matrix.m22_) * 2.0f;
            float invS = 1.0f / s;
            
            x_ = (matrix.m01_ + matrix.m10_) * invS;
            y_ = 0.25f * s;
            z_ = (matrix.m12_ + matrix.m21_) * invS;
            w_ = (matrix.m02_ - matrix.m20_) * invS;
        }
        else
        {
            float s = sqrtf(1.0f + matrix.m22_ - matrix.m00_ - matrix.m11_) * 2.0f;
            float invS = 1.0f / s;
            
            x_ = (matrix.m02_ + matrix.m20_) * invS;
            y_ = (matrix.m12_ + matrix.m21_) * invS;
            z_ = 0.25f * s;
            w_ = (matrix.m10_ - matrix.m01_) * invS;
        }
    }
}

Vector3 Quaternion::EulerAngles() const
{
    // Derivation from http://www.geometrictools.com/Documentation/EulerAngles.pdf
    // Order of rotations: Z first, then X, then Y
    float check = 2.0f * (-y_ * z_ + w_ * x_);
    
    if (check < -0.995f)
    {
        return Vector3(
            -90.0f,
            0.0f,
            -atan2f(2.0f * (x_ * z_ - w_ * y_), 1.0f - 2.0f * (y_ * y_ + z_ * z_)) * M_RADTODEG
        );
    }
    else if (check > 0.995f)
    {
        return Vector3(
            90.0f,
            0.0f,
            atan2f(2.0f * (x_ * z_ - w_ * y_), 1.0f - 2.0f * (y_ * y_ + z_ * z_)) * M_RADTODEG
        );
    }
    else
    {
        return Vector3(
            asinf(check) * M_RADTODEG,
            atan2f(2.0f * (x_ * z_ + w_ * y_), 1.0f - 2.0f * (x_ * x_ + y_ * y_)) * M_RADTODEG,
            atan2f(2.0f * (x_ * y_ + w_ * z_), 1.0f - 2.0f * (x_ * x_ + z_ * z_)) * M_RADTODEG
        );
    }
}

float Quaternion::YawAngle() const
{
    return EulerAngles().y_;
}

float Quaternion::PitchAngle() const
{
    return EulerAngles().x_;
}

float Quaternion::RollAngle() const
{
    return EulerAngles().z_;
}

Matrix3 Quaternion::RotationMatrix() const
{
    return Matrix3(
        1.0f - 2.0f * y_ * y_ - 2.0f * z_ * z_,
        2.0f * x_ * y_ - 2.0f * w_ * z_,
        2.0f * x_ * z_ + 2.0f * w_ * y_,
        2.0f * x_ * y_ + 2.0f * w_ * z_,
        1.0f - 2.0f * x_ * x_ - 2.0f * z_ * z_,
        2.0f * y_ * z_ - 2.0f * w_ * x_,
        2.0f * x_ * z_ - 2.0f * w_ * y_,
        2.0f * y_ * z_ + 2.0f * w_ * x_,
        1.0f - 2.0f * x_ * x_ - 2.0f * y_ * y_
    );
}

Quaternion Quaternion::Slerp(Quaternion rhs, float t) const
{
    float cosAngle = DotProduct(rhs);
    
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
        float invSinAngle = 1.0f / sinAngle;
        t1 = sinf((1.0f - t) * angle) * invSinAngle;
        t2 = sinf(t * angle) * invSinAngle;
    }
    else
    {
        t1 = 1.0f - t;
        t2 = t;
    }
    
    return *this * t1 + rhs * t2;
}

String Quaternion::ToString() const
{
    char tempBuffer[CONVERSION_BUFFER_LENGTH];
    sprintf(tempBuffer, "%g %g %g %g", w_, x_, y_, z_);
    return String(tempBuffer);
}
