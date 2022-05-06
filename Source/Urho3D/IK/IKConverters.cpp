// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include "../IK/IKConverters.h"

namespace Urho3D {

// ----------------------------------------------------------------------------
vec3_t Vec3Urho2IK(const Vector3& urho)
{
    vec3_t ret;
    ret.v.x = urho.x_;
    ret.v.y = urho.y_;
    ret.v.z = urho.z_;
    return ret;
}

// ----------------------------------------------------------------------------
Vector3 Vec3IK2Urho(const vec3_t* ik)
{
    return Vector3(ik->v.x, ik->v.y, ik->v.z);
}

// ----------------------------------------------------------------------------
quat_t QuatUrho2IK(const Quaternion& urho)
{
    quat_t ret;
    ret.q.x = urho.x_;
    ret.q.y = urho.y_;
    ret.q.z = urho.z_;
    ret.q.w = urho.w_;
    return ret;
}

// ----------------------------------------------------------------------------
Quaternion QuatIK2Urho(const quat_t* ik)
{
    return Quaternion(ik->q.w, ik->q.x, ik->q.y, ik->q.z);
}

}
