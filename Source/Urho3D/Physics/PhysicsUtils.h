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
