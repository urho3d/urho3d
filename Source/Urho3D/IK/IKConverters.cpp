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
