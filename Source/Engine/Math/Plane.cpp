//
// Copyright (c) 2008-2013 the Urho3D project.
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
#include "Plane.h"

namespace Urho3D
{

// Static initialization order can not be relied on, so do not use Vector3 constants
const Plane Plane::UP(Vector3(0.0f, 1.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f));

void Plane::Transform(const Matrix3& transform)
{
    *this = Transformed(transform);
}

void Plane::Transform(const Matrix3x4& transform)
{
    *this = Transformed(transform);
}

void Plane::Transform(const Matrix4& transform)
{
    *this = Transformed(transform);
}

Matrix3x4 Plane::ReflectionMatrix() const
{
    float negIntercept = -intercept_;

    return Matrix3x4(
        -2.0f * normal_.x_ * normal_.x_ + 1.0f,
        -2.0f * normal_.x_ * normal_.y_,
        -2.0f * normal_.x_ * normal_.z_,
        -2.0f * normal_.x_ * negIntercept,
        -2.0f * normal_.y_ * normal_.x_ ,
        -2.0f * normal_.y_ * normal_.y_ + 1.0f,
        -2.0f * normal_.y_ * normal_.z_,
        -2.0f * normal_.y_ * negIntercept,
        -2.0f * normal_.z_ * normal_.x_,
        -2.0f * normal_.z_ * normal_.y_,
        -2.0f * normal_.z_ * normal_.z_ + 1.0f,
        -2.0f * normal_.z_ * negIntercept
    );
}

Plane Plane::Transformed(const Matrix3& transform) const
{
    Vector3 newNormal = (transform * normal_).Normalized();
    Vector3 newPoint = newNormal * intercept_;
    return Plane(newNormal, newPoint);
}

Plane Plane::Transformed(const Matrix3x4& transform) const
{
    Vector3 newNormal = (transform * normal_).Normalized();
    Vector3 newPoint = transform * (normal_ * intercept_);
    return Plane(newNormal, newPoint);
}

Plane Plane::Transformed(const Matrix4& transform) const
{
    return Plane(transform.Inverse().Transpose() * ToVector4());
}

}
