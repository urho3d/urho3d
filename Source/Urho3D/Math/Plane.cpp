// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include "../Precompiled.h"

#include "../Math/Plane.h"

#include "../DebugNew.h"

namespace Urho3D
{

// Static initialization order can not be relied on, so do not use Vector3 constants
const Plane Plane::UP(Vector3(0.0f, 1.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f));

void Plane::Transform(const Matrix3& transform)
{
    Define(Matrix4(transform).Inverse().Transpose() * ToVector4());
}

void Plane::Transform(const Matrix3x4& transform)
{
    Define(transform.ToMatrix4().Inverse().Transpose() * ToVector4());
}

void Plane::Transform(const Matrix4& transform)
{
    Define(transform.Inverse().Transpose() * ToVector4());
}

Matrix3x4 Plane::ReflectionMatrix() const
{
    return Matrix3x4(
        -2.0f * normal_.x_ * normal_.x_ + 1.0f,
        -2.0f * normal_.x_ * normal_.y_,
        -2.0f * normal_.x_ * normal_.z_,
        -2.0f * normal_.x_ * d_,
        -2.0f * normal_.y_ * normal_.x_,
        -2.0f * normal_.y_ * normal_.y_ + 1.0f,
        -2.0f * normal_.y_ * normal_.z_,
        -2.0f * normal_.y_ * d_,
        -2.0f * normal_.z_ * normal_.x_,
        -2.0f * normal_.z_ * normal_.y_,
        -2.0f * normal_.z_ * normal_.z_ + 1.0f,
        -2.0f * normal_.z_ * d_
    );
}

Plane Plane::Transformed(const Matrix3& transform) const
{
    return Plane(Matrix4(transform).Inverse().Transpose() * ToVector4());
}

Plane Plane::Transformed(const Matrix3x4& transform) const
{
    return Plane(transform.ToMatrix4().Inverse().Transpose() * ToVector4());
}

Plane Plane::Transformed(const Matrix4& transform) const
{
    return Plane(transform.Inverse().Transpose() * ToVector4());
}

}
