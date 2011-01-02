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
#include "Frustum.h"

void Sphere::define(const std::vector<Vector3>& vertices)
{
    mDefined = false;
    for (std::vector<Vector3>::const_iterator i = vertices.begin(); i != vertices.end(); ++i)
        merge(*i);
}

void Sphere::define(const Vector3* vertices, unsigned count)
{
    if (!count)
        return;
    
    mDefined = false;
    merge(vertices, count);
}

void Sphere::define(const BoundingBox& box)
{
    const Vector3& min = box.mMin;
    const Vector3& max = box.mMax;
    
    mDefined = false;
    merge(min);
    merge(Vector3(max.mX, min.mY, min.mZ));
    merge(Vector3(min.mX, max.mY, min.mZ));
    merge(Vector3(max.mX, max.mY, min.mZ));
    merge(Vector3(min.mX, min.mY, max.mZ));
    merge(Vector3(max.mX, min.mY, max.mZ));
    merge(Vector3(min.mX, max.mY, max.mZ));
    merge(max);
}

void Sphere::define(const Frustum& frustum)
{
    define(frustum.getVertices(), NUM_FRUSTUM_VERTICES);
}

void Sphere::merge(const std::vector<Vector3>& vertices)
{
    for (std::vector<Vector3>::const_iterator i = vertices.begin(); i != vertices.end(); ++i)
        merge(*i);
}

void Sphere::merge(const Vector3* vertices, unsigned count)
{
    while (count--)
    {
        merge(*vertices);
        ++vertices;
    }
}

void Sphere::merge(const BoundingBox& box)
{
    const Vector3& min = box.mMin;
    const Vector3& max = box.mMax;
    
    merge(min);
    merge(Vector3(max.mX, min.mY, min.mZ));
    merge(Vector3(min.mX, max.mY, min.mZ));
    merge(Vector3(max.mX, max.mY, min.mZ));
    merge(Vector3(min.mX, min.mY, max.mZ));
    merge(Vector3(max.mX, min.mY, max.mZ));
    merge(Vector3(min.mX, max.mY, max.mZ));
    merge(max);
}

void Sphere::merge(const Frustum& frustum)
{
    const Vector3* vertices = frustum.getVertices();
    merge(vertices, NUM_FRUSTUM_VERTICES);
}

void Sphere::merge(const Sphere& sphere)
{
    if (!mDefined)
    {
        mCenter = sphere.mCenter;
        mRadius = sphere.mRadius;
        mDefined = true;
        return;
    }
    
    Vector3 offset = sphere.mCenter - mCenter;
    float dist = offset.getLength();
    
    // If sphere fits inside, do nothing
    if (dist + sphere.mRadius < mRadius)
        return;
    
    // If we fit inside the other sphere, become it
    if (dist + mRadius < sphere.mRadius)
    {
        mCenter = sphere.mCenter;
        mRadius = sphere.mRadius;
    }
    else
    {
        Vector3 normalizedOffset = offset / dist;
        
        Vector3 min = mCenter - mRadius * normalizedOffset;
        Vector3 max = sphere.mCenter + sphere.mRadius * normalizedOffset;
        mCenter = (min + max) * 0.5f;
        mRadius = (max - mCenter).getLength();
    }
}

Intersection Sphere::isInside(const BoundingBox& box) const
{
    float radiusSquared = mRadius * mRadius;
    float distSquared = 0;
    float temp;
    
    Vector3 min = box.mMin;
    Vector3 max = box.mMax;
    
    if (mCenter.mX < min.mX)
    {
        temp = mCenter.mX - min.mX;
        distSquared += temp * temp;
    }
    else if (mCenter.mX > max.mX)
    {
        temp = mCenter.mX - max.mX;
        distSquared += temp * temp;
    }
    if (mCenter.mY < min.mY)
    {
        temp = mCenter.mY - min.mY;
        distSquared += temp * temp;
    }
    else if (mCenter.mY > max.mY)
    {
        temp = mCenter.mY - max.mY;
        distSquared += temp * temp;
    }
    if (mCenter.mZ < min.mZ)
    {
        temp = mCenter.mZ - min.mZ;
        distSquared += temp * temp;
    }
    else if (mCenter.mZ > max.mZ)
    {
        temp = mCenter.mZ - max.mZ;
        distSquared += temp * temp;
    }
    
    if (distSquared >= radiusSquared)
        return OUTSIDE;
    
    min -= mCenter;
    max -= mCenter;
    
    Vector3 tempVec = min; // - - -
    if (tempVec.getLengthSquared() >= radiusSquared)
        return INTERSECTS;
    tempVec.mX = max.mX; // + - -
    if (tempVec.getLengthSquared() >= radiusSquared)
        return INTERSECTS;
    tempVec.mY = max.mY; // + + -
    if (tempVec.getLengthSquared() >= radiusSquared)
        return INTERSECTS;
    tempVec.mX = min.mX; // - + -
    if (tempVec.getLengthSquared() >= radiusSquared)
        return INTERSECTS;
    tempVec.mZ = max.mZ; // - + +
    if (tempVec.getLengthSquared() >= radiusSquared)
        return INTERSECTS;
    tempVec.mY = min.mY; // - - +
    if (tempVec.getLengthSquared() >= radiusSquared)
        return INTERSECTS;
    tempVec.mX = max.mX; // + - +
    if (tempVec.getLengthSquared() >= radiusSquared)
        return INTERSECTS;
    tempVec.mY = max.mY; // + + +
    if (tempVec.getLengthSquared() >= radiusSquared)
        return INTERSECTS;
    
    return INSIDE;
}

Intersection Sphere::isInsideFast(const BoundingBox& box) const
{
    float radiusSquared = mRadius * mRadius;
    float distSquared = 0;
    float temp;
    
    Vector3 min = box.mMin;
    Vector3 max = box.mMax;
    
    if (mCenter.mX < min.mX)
    {
        temp = mCenter.mX - min.mX;
        distSquared += temp * temp;
    }
    else if (mCenter.mX > max.mX)
    {
        temp = mCenter.mX - max.mX;
        distSquared += temp * temp;
    }
    if (mCenter.mY < min.mY)
    {
        temp = mCenter.mY - min.mY;
        distSquared += temp * temp;
    }
    else if (mCenter.mY > max.mY)
    {
        temp = mCenter.mY - max.mY;
        distSquared += temp * temp;
    }
    if (mCenter.mZ < min.mZ)
    {
        temp = mCenter.mZ - min.mZ;
        distSquared += temp * temp;
    }
    else if (mCenter.mZ > max.mZ)
    {
        temp = mCenter.mZ - max.mZ;
        distSquared += temp * temp;
    }
    
    if (distSquared >= radiusSquared)
        return OUTSIDE;
    else
        return INSIDE;
}

float Sphere::getDistance(const Ray& ray) const
{
    Vector3 centeredOrigin = ray.mOrigin - mCenter;
    float squaredRadius = mRadius * mRadius;
    
    // Check if ray originates inside the sphere
    if (centeredOrigin.getLengthSquared() <= squaredRadius)
        return 0.0f;
    
    // Calculate intersection by quadratic equation
    float a = ray.mDirection.dotProduct(ray.mDirection);
    float b = 2.0f * centeredOrigin.dotProduct(ray.mDirection);
    float c = centeredOrigin.dotProduct(centeredOrigin) - squaredRadius;
    
    float d = b * b - 4.0f * a * c;

    // No solution
    if (d < 0.0f)
        return M_INFINITY;
    
    // Get the nearer solution
    float dSqrt = sqrtf(d);
    float dist = (-b - dSqrt) / (2.0f * a);
    if (dist >= 0.0f)
        return dist;
    else
        return (-b + dSqrt) / (2.0f * a);
}
