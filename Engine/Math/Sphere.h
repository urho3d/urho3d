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

#ifndef MATH_SPHERE_H
#define MATH_SPHERE_H

#include "Vector3.h"

class BoundingBox;
class Frustum;
class Ray;

//! A sphere in three-dimensional space
class Sphere
{
public:
    //! Construct an undefined sphere
    Sphere() :
        mDefined(false)
    {
    }
    
    //! Copy-construct from another sphere
    Sphere(const Sphere& sphere) :
        mCenter(sphere.mCenter),
        mRadius(sphere.mRadius),
        mDefined(sphere.mDefined)
    {
    }
    
    //! Construct from center and radius
    Sphere(const Vector3& center, float radius) :
        mCenter(center),
        mRadius(radius),
        mDefined(true)
    {
    }
    
    //! Assign from another sphere
    Sphere& operator = (const Sphere& rhs)
    {
        mCenter = rhs.mCenter;
        mRadius = rhs.mRadius;
        mDefined = rhs.mDefined;
        
        return *this;
    }
    
    //! Test for equality with another sphere
    bool operator == (const Sphere& rhs) const
    {
        return (mCenter == rhs.mCenter) && (mRadius == rhs.mRadius);
    }
    
    //! Test for inequality with another sphere
    bool operator != (const Sphere& rhs) const
    {
        return (mCenter != rhs.mCenter) || (mRadius != rhs.mRadius);
    }
    
    //! Define from center and radius
    void define(const Vector3& center, float radius)
    {
        mCenter = center;
        mRadius = radius;
        mDefined = true;
    }
    
    //! Define from a vector of vertices
    void define(const std::vector<Vector3>& vertices);
    //! Define from an array of vertices
    void define(const Vector3* vertices, unsigned count);
    //! Define from a boundingBox
    void define(const BoundingBox& box);
    //! Define from a frustum
    void define(const Frustum& frustum);
    
    //! Merge a point
    void merge(const Vector3& point)
    {
        if (!mDefined)
        {
            mCenter = point;
            mRadius = 0.0f;
            mDefined = true;
            return;
        }
        
        Vector3 offset = point - mCenter;
        float dist = offset.getLength();
        if (dist > mRadius)
        {
            float half = (dist - mRadius) * 0.5f;
            mRadius += half;
            mCenter += (half / dist) * offset;
        }
    }
    
    //! Merge a vector of vertices
    void merge(const std::vector<Vector3>& vertices);
    //! Merge an array of vertices
    void merge(const Vector3* vertices, unsigned count);
    //! Merge a bounding box
    void merge(const BoundingBox& box);
    //! Merge a frustum
    void merge(const Frustum& frustum);
    //! Merge a sphere
    void merge(const Sphere& sphere);
    
    //! Test if a point is inside
    Intersection isInside(const Vector3& point) const
    {
        float distSquared = (point - mCenter).getLengthSquared();
        
        if (distSquared < mRadius * mRadius)
            return INSIDE;
        else
            return OUTSIDE;
    }
    
    //! Test if another sphere is inside, outside or intersects
    Intersection isInside(const Sphere& sphere) const
    {
        float dist = (sphere.mCenter - mCenter).getLength();
        
        if (dist >= sphere.mRadius + mRadius)
            return OUTSIDE;
        if (dist + sphere.mRadius < mRadius)
            return INSIDE;
        return INTERSECTS;
    }
    
    //! Test if another sphere is (partially) inside or outside
    Intersection isInsideFast(const Sphere& sphere) const
    {
        float distSquared = (sphere.mCenter - mCenter).getLengthSquared();
        float combined = sphere.mRadius + mRadius;
        
        if (distSquared >= combined * combined)
            return OUTSIDE;
        else
            return INSIDE;
    }
    
    //! Test if a bounding box is inside, outside or intersects
    Intersection isInside(const BoundingBox& box) const;
    //! Test if a bounding box is (partially) inside or outside
    Intersection isInsideFast(const BoundingBox& box) const;
    //! Return distance to a ray, or infinity if no intersection
    float getDistance(const Ray& ray) const;
    
    //! Sphere center
    Vector3 mCenter;
    //! Sphere radius
    float mRadius;
    //! Defined flag
    bool mDefined;
};

#endif // MATH_SPHERE_H
