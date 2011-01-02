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

void BoundingBox::define(const std::vector<Vector3>& vertices)
{
    mDefined = false;
    for (std::vector<Vector3>::const_iterator i = vertices.begin(); i != vertices.end(); ++i)
        merge(*i);
}

void BoundingBox::define(const Vector3* vertices, unsigned count)
{
    if (!count)
        return;
    
    mDefined = false;
    merge(vertices, count);
}

void BoundingBox::define(const Frustum& frustum)
{
    define(frustum.getVertices(), NUM_FRUSTUM_VERTICES);
}

void BoundingBox::define(const Sphere& sphere)
{
    const Vector3& center = sphere.mCenter;
    float radius = sphere.mRadius;
    
    mMin = center + Vector3(-radius, -radius, -radius);
    mMax = center + Vector3(radius, radius, radius);
    mDefined = true;
}

void BoundingBox::merge(const std::vector<Vector3>& vertices)
{
    for (std::vector<Vector3>::const_iterator i = vertices.begin(); i != vertices.end(); ++i)
        merge(*i);
}

void BoundingBox::merge(const Vector3* vertices, unsigned count)
{
    while (count--)
    {
        merge(*vertices);
        ++vertices;
    }
}

void BoundingBox::merge(const Frustum& frustum)
{
    merge(frustum.getVertices(), NUM_FRUSTUM_VERTICES);
}

void BoundingBox::merge(const Sphere& sphere)
{
    const Vector3& center = sphere.mCenter;
    float radius = sphere.mRadius;
    
    merge(center + Vector3(radius, radius, radius));
    merge(center + Vector3(-radius, -radius, -radius));
}

void BoundingBox::intersect(const BoundingBox& box)
{
    if (box.mMin.mX > mMin.mX)
        mMin.mX = box.mMin.mX;
    if (box.mMax.mX < mMax.mX)
        mMax.mX = box.mMax.mX;
    if (box.mMin.mY > mMin.mY)
        mMin.mY = box.mMin.mY;
    if (box.mMax.mY < mMax.mY)
        mMax.mY = box.mMax.mY;
    if (box.mMin.mZ > mMin.mZ)
        mMin.mZ = box.mMin.mZ;
    if (box.mMax.mZ < mMax.mZ)
        mMax.mZ = box.mMax.mZ;
    
    if (mMin.mX > mMax.mX)
        std::swap(mMin.mX, mMax.mX);
    if (mMin.mY > mMax.mY)
        std::swap(mMin.mY, mMax.mY);
    if (mMin.mZ > mMax.mZ)
        std::swap(mMin.mZ, mMax.mZ);
}

void BoundingBox::transform(const Matrix3& transform)
{
    Vector3 newCenter = transform * getCenter();
    Vector3 oldEdge = getSize() * 0.5;
    
    Vector3 newEdge = Vector3(
        fabsf(transform.m00) * oldEdge.mX + fabsf(transform.m01) * oldEdge.mY + fabsf(transform.m02) * oldEdge.mZ,
        fabsf(transform.m10) * oldEdge.mX + fabsf(transform.m11) * oldEdge.mY + fabsf(transform.m12) * oldEdge.mZ,
        fabsf(transform.m20) * oldEdge.mX + fabsf(transform.m21) * oldEdge.mY + fabsf(transform.m22) * oldEdge.mZ
    );
    
    mMin = newCenter - newEdge;
    mMax = newCenter + newEdge;
}

void BoundingBox::transform(const Matrix4x3& transform)
{
    Vector3 newCenter = transform * getCenter();
    Vector3 oldEdge = getSize() * 0.5;
    
    Vector3 newEdge = Vector3(
        fabsf(transform.m00) * oldEdge.mX + fabsf(transform.m01) * oldEdge.mY + fabsf(transform.m02) * oldEdge.mZ,
        fabsf(transform.m10) * oldEdge.mX + fabsf(transform.m11) * oldEdge.mY + fabsf(transform.m12) * oldEdge.mZ,
        fabsf(transform.m20) * oldEdge.mX + fabsf(transform.m21) * oldEdge.mY + fabsf(transform.m22) * oldEdge.mZ
    );
    
    mMin = newCenter - newEdge;
    mMax = newCenter + newEdge;
}

BoundingBox BoundingBox::getTransformed(const Matrix3& transform) const
{
    Vector3 newCenter = transform * getCenter();
    Vector3 oldEdge = getSize() * 0.5;
    
    Vector3 newEdge = Vector3(
        fabsf(transform.m00) * oldEdge.mX + fabsf(transform.m01) * oldEdge.mY + fabsf(transform.m02) * oldEdge.mZ,
        fabsf(transform.m10) * oldEdge.mX + fabsf(transform.m11) * oldEdge.mY + fabsf(transform.m12) * oldEdge.mZ,
        fabsf(transform.m20) * oldEdge.mX + fabsf(transform.m21) * oldEdge.mY + fabsf(transform.m22) * oldEdge.mZ
    );
    
    return BoundingBox(newCenter - newEdge, newCenter + newEdge);
}

BoundingBox BoundingBox::getTransformed(const Matrix4x3& transform) const
{
    Vector3 newCenter = transform * getCenter();
    Vector3 oldEdge = getSize() * 0.5f;
    
    Vector3 newEdge = Vector3(
        fabsf(transform.m00) * oldEdge.mX + fabsf(transform.m01) * oldEdge.mY + fabsf(transform.m02) * oldEdge.mZ,
        fabsf(transform.m10) * oldEdge.mX + fabsf(transform.m11) * oldEdge.mY + fabsf(transform.m12) * oldEdge.mZ,
        fabsf(transform.m20) * oldEdge.mX + fabsf(transform.m21) * oldEdge.mY + fabsf(transform.m22) * oldEdge.mZ
    );
    
    return BoundingBox(newCenter - newEdge, newCenter + newEdge);
}

Rect BoundingBox::getProjected(const Matrix4& projection) const
{
    Vector3 projMin = mMin;
    Vector3 projMax = mMax;
    if (projMin.mZ < M_MIN_NEARCLIP)
        projMin.mZ = M_MIN_NEARCLIP;
    if (projMax.mZ < M_MIN_NEARCLIP)
        projMax.mZ = M_MIN_NEARCLIP;
    
    Vector3 vertices[8];
    
    vertices[0] = projMin;
    vertices[1] = Vector3(projMax.mX, projMin.mY, projMin.mZ);
    vertices[2] = Vector3(projMin.mX, projMax.mY, projMin.mZ);
    vertices[3] = Vector3(projMax.mX, projMax.mY, projMin.mZ);
    vertices[4] = Vector3(projMin.mX, projMin.mY, projMax.mZ);
    vertices[5] = Vector3(projMax.mX, projMin.mY, projMax.mZ);
    vertices[6] = Vector3(projMin.mX, projMax.mY, projMax.mZ);
    vertices[7] = projMax;
    
    Rect rect;
    for (unsigned i = 0; i < 8; ++i)
    {
        Vector3 projected = projection * vertices[i];
        rect.merge(Vector2(projected.mX, projected.mY));
    }
    
    return rect;
}

Intersection BoundingBox::isInside(const Sphere& sphere) const
{
    float distSquared = 0;
    float temp;
    
    const Vector3& center = sphere.mCenter;
    
    if (center.mX < mMin.mX)
    {
        temp = center.mX - mMin.mX;
        distSquared += temp * temp;
    }
    else if (center.mX > mMax.mX)
    {
        temp = center.mX - mMax.mX;
        distSquared += temp * temp;
    }
    if (center.mY < mMin.mY)
    {
        temp = center.mY - mMin.mY;
        distSquared += temp * temp;
    }
    else if (center.mY > mMax.mY)
    {
        temp = center.mY - mMax.mY;
        distSquared += temp * temp;
    }
    if (center.mZ < mMin.mZ)
    {
        temp = center.mZ - mMin.mZ;
        distSquared += temp * temp;
    }
    else if (center.mZ > mMax.mZ)
    {
        temp = center.mZ - mMax.mZ;
        distSquared += temp * temp;
    }
    
    float radius = sphere.mRadius;
    if (distSquared >= radius * radius)
        return OUTSIDE;
    
    if ((center.mX - radius < mMin.mX) || (center.mX + radius > mMax.mX))
        return INTERSECTS;
    if ((center.mY - radius < mMin.mY) || (center.mY + radius > mMax.mY))
        return INTERSECTS;
    if ((center.mZ - radius < mMin.mZ) || (center.mZ + radius > mMax.mZ))
        return INTERSECTS;
    
    return INSIDE;
}

Intersection BoundingBox::isInsideFast(const Sphere& sphere) const
{
    float distSquared = 0;
    float temp;
    
    const Vector3& center = sphere.mCenter;
    
    if (center.mX < mMin.mX)
    {
        temp = center.mX - mMin.mX;
        distSquared += temp * temp;
    }
    else if (center.mX > mMax.mX)
    {
        temp = center.mX - mMax.mX;
        distSquared += temp * temp;
    }
    if (center.mY < mMin.mY)
    {
        temp = center.mY - mMin.mY;
        distSquared += temp * temp;
    }
    else if (center.mY > mMax.mY)
    {
        temp = center.mY - mMax.mY;
        distSquared += temp * temp;
    }
    if (center.mZ < mMin.mZ)
    {
        temp = center.mZ - mMin.mZ;
        distSquared += temp * temp;
    }
    else if (center.mZ > mMax.mZ)
    {
        temp = center.mZ - mMax.mZ;
        distSquared += temp * temp;
    }
    
    float radius = sphere.mRadius;
    if (distSquared >= radius * radius)
        return OUTSIDE;
    
    return INSIDE;
}

float BoundingBox::getDistance(const Ray& ray) const
{
    // If undefined, no hit (infinite distance)
    if (!mDefined)
        return M_INFINITY;
    
    // Check for ray origin being inside the box
    if (isInside(ray.mOrigin))
        return 0.0f;
    
    float dist = M_INFINITY;
    
    // Check for intersecting in the X-direction
    if ((ray.mOrigin.mX < mMin.mX) && (ray.mDirection.mX > 0.0f))
    {
        float x = (mMin.mX - ray.mOrigin.mX) / ray.mDirection.mX;
        if (x < dist)
        {
            Vector3 point = ray.mOrigin + x * ray.mDirection;
            if ((point.mY >= mMin.mY) && (point.mY <= mMax.mY) &&
                (point.mZ >= mMin.mZ) && (point.mZ <= mMax.mZ))
                dist = x;
        }
    }
    if ((ray.mOrigin.mX > mMax.mX) && (ray.mDirection.mX < 0.0f))
    {
        float x = (mMax.mX - ray.mOrigin.mX) / ray.mDirection.mX;
        if (x < dist)
        {
            Vector3 point = ray.mOrigin + x * ray.mDirection;
            if ((point.mY >= mMin.mY) && (point.mY <= mMax.mY) &&
                (point.mZ >= mMin.mZ) && (point.mZ <= mMax.mZ))
                dist = x;
        }
    }
    // Check for intersecting in the Y-direction
    if ((ray.mOrigin.mY < mMin.mY) && (ray.mDirection.mY > 0.0f))
    {
        float x = (mMin.mY - ray.mOrigin.mY) / ray.mDirection.mY;
        if (x < dist)
        {
            Vector3 point = ray.mOrigin + x * ray.mDirection;
            if ((point.mX >= mMin.mX) && (point.mX <= mMax.mX) &&
                (point.mZ >= mMin.mZ) && (point.mZ <= mMax.mZ))
                dist = x;
        }
    }
    if ((ray.mOrigin.mY > mMax.mY) && (ray.mDirection.mY < 0.0f))
    {
        float x = (mMax.mY - ray.mOrigin.mY) / ray.mDirection.mY;
        if (x < dist)
        {
            Vector3 point = ray.mOrigin + x * ray.mDirection;
            if ((point.mX >= mMin.mX) && (point.mX <= mMax.mX) &&
                (point.mZ >= mMin.mZ) && (point.mZ <= mMax.mZ))
                dist = x;
        }
    }
    // Check for intersecting in the Z-direction
    if ((ray.mOrigin.mZ < mMin.mZ) && (ray.mDirection.mZ > 0.0f))
    {
        float x = (mMin.mZ - ray.mOrigin.mZ) / ray.mDirection.mZ;
        if (x < dist)
        {
            Vector3 point = ray.mOrigin + x * ray.mDirection;
            if ((point.mX >= mMin.mX) && (point.mX <= mMax.mX) &&
                (point.mY >= mMin.mY) && (point.mY <= mMax.mY))
                dist = x;
        }
    }
    if ((ray.mOrigin.mZ > mMax.mZ) && (ray.mDirection.mZ < 0.0f))
    {
        float x = (mMax.mZ - ray.mOrigin.mZ) / ray.mDirection.mZ;
        if (x < dist)
        {
            Vector3 point = ray.mOrigin + x * ray.mDirection;
            if ((point.mX >= mMin.mX) && (point.mX <= mMax.mX) &&
                (point.mY >= mMin.mY) && (point.mY <= mMax.mY))
                dist = x;
        }
    }
    
    return dist;
}
