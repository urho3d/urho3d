// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

/// \file
/// @nobindfile

#pragma once

#include "../Math/Quaternion.h"
#include "../Math/Vector3.h"

#include <Bullet/LinearMath/btVector3.h>
#include <Bullet/LinearMath/btQuaternion.h>

namespace Urho3D
{

inline btVector3 ToBtVector3(const Vector3& vector)
{
    return btVector3(vector.x_, vector.y_, vector.z_);
}

inline btQuaternion ToBtQuaternion(const Quaternion& quaternion)
{
    return btQuaternion(quaternion.x_, quaternion.y_, quaternion.z_, quaternion.w_);
}

inline Vector3 ToVector3(const btVector3& vector)
{
    return Vector3(vector.x(), vector.y(), vector.z());
}

inline Quaternion ToQuaternion(const btQuaternion& quaternion)
{
    return Quaternion(quaternion.w(), quaternion.x(), quaternion.y(), quaternion.z());
}

inline bool HasWorldScaleChanged(const Vector3& oldWorldScale, const Vector3& newWorldScale)
{
    Vector3 delta = newWorldScale - oldWorldScale;
    float dot = delta.DotProduct(delta);
    return dot > 0.01f;
}

}
