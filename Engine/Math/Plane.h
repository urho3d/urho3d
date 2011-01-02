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

#ifndef MATH_PLANE_H
#define MATH_PLANE_H

#include "Ray.h"
#include "Vector3.h"

class Ray;

//! A surface in three-dimensional space
class Plane
{
public:
    //! Construct an undefined plane
    Plane();
    //! Copy-construct from another plane
    Plane(const Plane& plane);
    //! Construct from 3 vertices
    Plane(const Vector3& v0, const Vector3& v1, const Vector3& v2);
    //! Construct from a normal vector and a point on the plane
    Plane(const Vector3& normal, const Vector3& point);
    
    //! Define from 3 vertices
    void define(const Vector3& v0, const Vector3& v1, const Vector3& v2);
    //! Define from a normal vector and a point on the plane
    void define(const Vector3& normal, const Vector3& point);
    
    //! Return distance to a point
    float getDistance(const Vector3& point) const
    {
        return mNormal.dotProduct(point) + mD;
    }
    
    //! Return absolute distance to a point
    float getAbsDistance(const Vector3& point) const
    {
        return mNormal.absDotProduct(point);
    }
    
    //! Return absolute distance to a point which has only positive coordinates
    float getAbsDistanceFast(const Vector3& absPoint) const
    {
        // Point must contain only positive X, Y, Z
        return mAbsNormal.dotProduct(absPoint);
    }
    
    //! Return ray hit distance, or infinity if no hit
    float getDistance(const Ray& ray) const
    {
        float d = mNormal.dotProduct(ray.mDirection);
        if (fabsf(d) < M_EPSILON)
            return M_INFINITY;
        float n = mNormal.dotProduct(ray.mOrigin) + mD;
        return -n / d;
    }
    
    //! Plane normal
    Vector3 mNormal;
    //! Plane absolute normal
    Vector3 mAbsNormal;
    //! Plane intercept parameter
    float mD;
};

#endif // MATH_PLANE_H
