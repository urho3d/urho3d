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

#include "../Math/Quaternion.h"

#include <cstdio>

#include "../DebugNew.h"

namespace Urho3D
{

const Quaternion Quaternion::IDENTITY;

void Quaternion::FromAngleAxis(float angle, const Vector3& axis)
{
    Vector3 normAxis = axis.Normalized();
    angle *= M_DEGTORAD_2;
    float sinAngle = sinf(angle);
    float cosAngle = cosf(angle);

    w_ = cosAngle;
    x_ = normAxis.x_ * sinAngle;
    y_ = normAxis.y_ * sinAngle;
    z_ = normAxis.z_ * sinAngle;
}

void Quaternion::FromEulerAngles(float x, float y, float z)
{
    // Order of rotations: Z first, then X, then Y (mimics typical FPS camera with gimbal lock at top/bottom)
    x *= M_DEGTORAD_2;
    y *= M_DEGTORAD_2;
    z *= M_DEGTORAD_2;
    float sinX = sinf(x);
    float cosX = cosf(x);
    float sinY = sinf(y);
    float cosY = cosf(y);
    float sinZ = sinf(z);
    float cosZ = cosf(z);

    w_ = cosY * cosX * cosZ + sinY * sinX * sinZ;
    x_ = cosY * sinX * cosZ + sinY * cosX * sinZ;
    y_ = sinY * cosX * cosZ - cosY * sinX * sinZ;
    z_ = cosY * cosX * sinZ - sinY * sinX * cosZ;
}

void Quaternion::FromRotationTo(const Vector3& start, const Vector3& end)
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

        FromAngleAxis(180.f, axis);
    }
}

void Quaternion::FromAxes(const Vector3& xAxis, const Vector3& yAxis, const Vector3& zAxis)
{
    Matrix3 matrix(
        xAxis.x_, yAxis.x_, zAxis.x_,
        xAxis.y_, yAxis.y_, zAxis.y_,
        xAxis.z_, yAxis.z_, zAxis.z_
    );

    FromRotationMatrix(matrix);
}

void Quaternion::FromRotationMatrix(const Matrix3& matrix)
{
    float t = matrix.m00_ + matrix.m11_ + matrix.m22_;

    if (t > 0.0f)
    {
        float invS = 0.5f / sqrtf(1.0f + t);

        x_ = (matrix.m21_ - matrix.m12_) * invS;
        y_ = (matrix.m02_ - matrix.m20_) * invS;
        z_ = (matrix.m10_ - matrix.m01_) * invS;
        w_ = 0.25f / invS;
    }
    else
    {
        if (matrix.m00_ > matrix.m11_ && matrix.m00_ > matrix.m22_)
        {
            float invS = 0.5f / sqrtf(1.0f + matrix.m00_ - matrix.m11_ - matrix.m22_);

            x_ = 0.25f / invS;
            y_ = (matrix.m01_ + matrix.m10_) * invS;
            z_ = (matrix.m20_ + matrix.m02_) * invS;
            w_ = (matrix.m21_ - matrix.m12_) * invS;
        }
        else if (matrix.m11_ > matrix.m22_)
        {
            float invS = 0.5f / sqrtf(1.0f + matrix.m11_ - matrix.m00_ - matrix.m22_);

            x_ = (matrix.m01_ + matrix.m10_) * invS;
            y_ = 0.25f / invS;
            z_ = (matrix.m12_ + matrix.m21_) * invS;
            w_ = (matrix.m02_ - matrix.m20_) * invS;
        }
        else
        {
            float invS = 0.5f / sqrtf(1.0f + matrix.m22_ - matrix.m00_ - matrix.m11_);

            x_ = (matrix.m02_ + matrix.m20_) * invS;
            y_ = (matrix.m12_ + matrix.m21_) * invS;
            z_ = 0.25f / invS;
            w_ = (matrix.m10_ - matrix.m01_) * invS;
        }
    }
}

bool Quaternion::FromLookRotation(const Vector3& direction, const Vector3& up)
{
    Quaternion ret;
    Vector3 forward = direction.Normalized();

    Vector3 v = forward.CrossProduct(up);
    // If direction & up are parallel and crossproduct becomes zero, use FromRotationTo() fallback
    if (v.LengthSquared() >= M_EPSILON)
    {
        v.Normalize();
        Vector3 up = v.CrossProduct(forward);
        Vector3 right = up.CrossProduct(forward);
        ret.FromAxes(right, up, forward);
    }
    else
        ret.FromRotationTo(Vector3::FORWARD, forward);

    if (!ret.IsNaN())
    {
        (*this) = ret;
        return true;
    }
    else
        return false;
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

Urho3D::Vector3 Quaternion::Axis() const
{
    return Vector3(x_, y_, z_) / sqrt(1. - w_ * w_);
}

float Quaternion::Angle() const
{
    return 2 * Acos(w_);
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

Quaternion Quaternion::Slerp(const Quaternion& rhs, float t) const
{
    // Use fast approximation for Emscripten builds
#ifdef __EMSCRIPTEN__
    float angle = DotProduct(rhs);
    float sign = 1.f; // Multiply by a sign of +/-1 to guarantee we rotate the shorter arc.
    if (angle < 0.f)
    {
        angle = -angle;
        sign = -1.f;
    }

    float a;
    float b;
    if (angle < 0.999f) // perform spherical linear interpolation.
    {
        // angle = acos(angle); // After this, angle is in the range pi/2 -> 0 as the original angle variable ranged from 0 -> 1.
        angle = (-0.69813170079773212f * angle * angle - 0.87266462599716477f) * angle + 1.5707963267948966f;
        float ta = t*angle;
        // Manually compute the two sines by using a very rough approximation.
        float ta2 = ta*ta;
        b = ((5.64311797634681035370e-03f * ta2 - 1.55271410633428644799e-01f) * ta2 + 9.87862135574673806965e-01f) * ta;
        a = angle - ta;
        float a2 = a*a;
        a = ((5.64311797634681035370e-03f * a2 - 1.55271410633428644799e-01f) * a2 + 9.87862135574673806965e-01f) * a;
    }
    else // If angle is close to taking the denominator to zero, resort to linear interpolation (and normalization).
    {
        a = 1.f - t;
        b = t;
    }
    // Lerp and renormalize.
    return (*this * (a * sign) + rhs * b).Normalized();
#else
    // Favor accuracy for native code builds
    float cosAngle = DotProduct(rhs);
    float sign = 1.0f;
    // Enable shortest path rotation
    if (cosAngle < 0.0f)
    {
        cosAngle = -cosAngle;
        sign = -1.0f;
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

    return *this * t1 + (rhs * sign) * t2;
#endif
}

Quaternion Quaternion::Nlerp(const Quaternion& rhs, float t, bool shortestPath) const
{
    Quaternion result;
    float fCos = DotProduct(rhs);
    if (fCos < 0.0f && shortestPath)
        result = (*this) + (((-rhs) - (*this)) * t);
    else
        result = (*this) + ((rhs - (*this)) * t);
    result.Normalize();
    return result;
}

String Quaternion::ToString() const
{
    char tempBuffer[CONVERSION_BUFFER_LENGTH];
    sprintf(tempBuffer, "%g %g %g %g", w_, x_, y_, z_);
    return String(tempBuffer);
}

}
