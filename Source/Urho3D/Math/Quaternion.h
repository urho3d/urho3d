//
// Copyright (c) 2008-2015 the Urho3D project.
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

#pragma once

#include "../Math/Matrix3.h"

namespace Urho3D
{

/// Rotation represented as a four-dimensional normalized vector.
class URHO3D_API Quaternion
{
public:
    /// Construct an identity quaternion.
    Quaternion() :
        w_(1.0f),
        x_(0.0f),
        y_(0.0f),
        z_(0.0f)
    {
    }
    
    /// Copy-construct from another quaternion.
    Quaternion(const Quaternion& quat) :
        w_(quat.w_),
        x_(quat.x_),
        y_(quat.y_),
        z_(quat.z_)
    {
    }
    
    /// Construct from values.
    Quaternion(float w, float x, float y, float z) :
        w_(w),
        x_(x),
        y_(y),
        z_(z)
    {
    }
    
    /// Construct from a float array.
    Quaternion(const float* data) :
        w_(data[0]),
        x_(data[1]),
        y_(data[2]),
        z_(data[3])
    {
    }
    
    /// Construct from an angle (in degrees) and axis.
    Quaternion(float angle, const Vector3& axis)
    {
        FromAngleAxis(angle, axis);
    }

    /// Construct from an angle (in degrees, for Urho2D).
    Quaternion(float angle)
    {
        FromAngleAxis(angle, Vector3::FORWARD);
    }
    
    /// Construct from Euler angles (in degrees.)
    Quaternion(float x, float y, float z)
    {
        FromEulerAngles(x, y, z);
    }
    
    /// Construct from the rotation difference between two direction vectors.
    Quaternion(const Vector3& start, const Vector3& end)
    {
        FromRotationTo(start, end);
    }
    
    /// Construct from orthonormal axes.
    Quaternion(const Vector3& xAxis, const Vector3& yAxis, const Vector3& zAxis)
    {
        FromAxes(xAxis, yAxis, zAxis);
    }

    /// Construct from a rotation matrix.
    Quaternion(const Matrix3& matrix)
    {
        FromRotationMatrix(matrix);
    }
    
    /// Assign from another quaternion.
    Quaternion& operator = (const Quaternion& rhs)
    {
        w_ = rhs.w_;
        x_ = rhs.x_;
        y_ = rhs.y_;
        z_ = rhs.z_;
        return *this;
    }
    
    /// Add-assign a quaternion.
    Quaternion& operator += (const Quaternion& rhs)
    {
        w_ += rhs.w_;
        x_ += rhs.x_;
        y_ += rhs.y_;
        z_ += rhs.z_;
        return *this;
    }
  
    /// Multiply-assign a scalar.
    Quaternion& operator *= (float rhs)
    {
        w_ *= rhs;
        x_ *= rhs;
        y_ *= rhs;
        z_ *= rhs;
        return *this;
    }
    
    /// Test for equality with another quaternion without epsilon.
    bool operator == (const Quaternion& rhs) const { return w_ == rhs.w_ && x_ == rhs.x_ && y_ == rhs.y_ && z_ == rhs.z_; }
    /// Test for inequality with another quaternion without epsilon.
    bool operator != (const Quaternion& rhs) const { return w_ != rhs.w_ || x_ != rhs.x_ || y_ != rhs.y_ || z_ != rhs.z_; }
    /// Multiply with a scalar.
    Quaternion operator * (float rhs) const { return Quaternion(w_ * rhs, x_ * rhs, y_ * rhs, z_ * rhs); }
    /// Return negation.
    Quaternion operator - () const { return Quaternion(-w_, -x_, -y_, -z_); }
    /// Add a quaternion.
    Quaternion operator + (const Quaternion& rhs) const { return Quaternion(w_ + rhs.w_, x_ + rhs.x_, y_ + rhs.y_, z_ + rhs.z_); }
    /// Subtract a quaternion.
    Quaternion operator - (const Quaternion& rhs) const { return Quaternion(w_ - rhs.w_, x_ - rhs.x_, y_ - rhs.y_, z_ - rhs.z_); }
    
    /// Multiply a quaternion.
    Quaternion operator * (const Quaternion& rhs) const
    {
        return Quaternion(
            w_ * rhs.w_ - x_ * rhs.x_ - y_ * rhs.y_ - z_ * rhs.z_,
            w_ * rhs.x_ + x_ * rhs.w_ + y_ * rhs.z_ - z_ * rhs.y_,
            w_ * rhs.y_ + y_ * rhs.w_ + z_ * rhs.x_ - x_ * rhs.z_,
            w_ * rhs.z_ + z_ * rhs.w_ + x_ * rhs.y_ - y_ * rhs.x_
        );
    }
    
    /// Multiply a Vector3.
    Vector3 operator * (const Vector3& rhs) const
    {
        Vector3 qVec(x_,y_,z_);
        Vector3 cross1(qVec.CrossProduct(rhs));
        Vector3 cross2(qVec.CrossProduct(cross1));
        
        return rhs + 2.0f * (cross1 * w_ + cross2);
    }
    
    /// Define from an angle (in degrees) and axis.
    void FromAngleAxis(float angle, const Vector3& axis);
    /// Define from Euler angles (in degrees.)
    void FromEulerAngles(float x, float y, float z);
    /// Define from the rotation difference between two direction vectors.
    void FromRotationTo(const Vector3& start, const Vector3& end);
    /// Define from orthonormal axes.
    void FromAxes(const Vector3& xAxis, const Vector3& yAxis, const Vector3& zAxis);
    /// Define from a rotation matrix.
    void FromRotationMatrix(const Matrix3& matrix);
    /// Define from a direction to look in and an up direction. Return true if successful, or false if would result in a NaN, in which case the current value remains.
    bool FromLookRotation(const Vector3& direction, const Vector3& up = Vector3::UP);

    /// Normalize to unit length.
    void Normalize()
    {
        float lenSquared = LengthSquared();
        if (!Urho3D::Equals(lenSquared, 1.0f) && lenSquared > 0.0f)
        {
            float invLen = 1.0f / sqrtf(lenSquared);
            w_ *= invLen;
            x_ *= invLen;
            y_ *= invLen;
            z_ *= invLen;
        }
    }
    
    /// Return normalized to unit length.
    Quaternion Normalized() const
    {
        float lenSquared = LengthSquared();
        if (!Urho3D::Equals(lenSquared, 1.0f) && lenSquared > 0.0f)
        {
            float invLen = 1.0f / sqrtf(lenSquared);
            return *this * invLen;
        }
        else
            return *this;
    }
    
    /// Return inverse.
    Quaternion Inverse() const
    {
        float lenSquared = LengthSquared();
        if (lenSquared == 1.0f)
            return Conjugate();
        else if (lenSquared >= M_EPSILON)
            return Conjugate() * (1.0f / lenSquared);
        else
            return IDENTITY;
    }
    
    /// Return squared length.
    float LengthSquared() const { return w_ * w_ + x_ * x_ + y_ * y_ + z_ * z_; }
    /// Calculate dot product.
    float DotProduct(const Quaternion& rhs) const { return w_ * rhs.w_ + x_ * rhs.x_ + y_ * rhs.y_ + z_ * rhs.z_; }
    /// Test for equality with another quaternion with epsilon.
    bool Equals(const Quaternion& rhs) const { return Urho3D::Equals(w_, rhs.w_) && Urho3D::Equals(x_, rhs.x_) && Urho3D::Equals(y_, rhs.y_) && Urho3D::Equals(z_, rhs.z_); }
    /// Return whether is NaN.
    bool IsNaN() const { return Urho3D::IsNaN(w_) || Urho3D::IsNaN(x_) || Urho3D::IsNaN(y_) || Urho3D::IsNaN(z_); }
    /// Return conjugate.
    Quaternion Conjugate() const { return Quaternion(w_, -x_, -y_, -z_); }
    
    /// Return Euler angles in degrees.
    Vector3 EulerAngles() const;
    /// Return yaw angle in degrees.
    float YawAngle() const;
    /// Return pitch angle in degrees.
    float PitchAngle() const;
    /// Return roll angle in degrees.
    float RollAngle() const;
    /// Return the rotation matrix that corresponds to this quaternion.
    Matrix3 RotationMatrix() const;
    /// Spherical interpolation with another quaternion.
    Quaternion Slerp(Quaternion rhs, float t) const;
    /// Normalized linear interpolation with another quaternion.
    Quaternion Nlerp(Quaternion rhs, float t, bool shortestPath = false) const;
    /// Return float data.
    const float* Data() const { return &w_; }
    /// Return as string.
    String ToString() const;
    
    /// W coordinate.
    float w_;
    /// X coordinate.
    float x_;
    /// Y coordinate.
    float y_;
    /// Z coordinate.
    float z_;
    
    /// Identity quaternion.
    static const Quaternion IDENTITY;
};

}
