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
#include "Plane.h"

Plane::Plane()
{
}

Plane::Plane(const Plane& plane) :
    mNormal(plane.mNormal),
    mD(plane.mD)
{
}

Plane::Plane(const Vector3& v0, const Vector3& v1, const Vector3& v2)
{
    define(v0, v1, v2);
}

Plane::Plane(const Vector3& normal, const Vector3& point)
{
    define(normal, point);
}

void Plane::define(const Vector3& v0, const Vector3& v1, const Vector3& v2)
{
    Vector3 dist1 = v1 - v0;
    Vector3 dist2 = v2 - v0;
    
    mNormal = (dist1.crossProduct(dist2)).getNormalized();
    mAbsNormal = Vector3(fabsf(mNormal.mX), fabsf(mNormal.mY), fabsf(mNormal.mZ));
    mD = -mNormal.dotProduct(v0);
}

void Plane::define(const Vector3& normal, const Vector3& point)
{
    mNormal = normal;
    mAbsNormal = Vector3(fabsf(mNormal.mX), fabsf(mNormal.mY), fabsf(mNormal.mZ));
    mD = -mNormal.dotProduct(point);
}
