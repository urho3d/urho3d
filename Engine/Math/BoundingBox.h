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

#ifndef MATH_BOUNDINGBOX_H
#define MATH_BOUNDINGBOX_H

#include "Rect.h"
#include "Vector3.h"

#include <vector>

class Frustum;
class Matrix3;
class Matrix4;
class Matrix4x3;
class Ray;
class Sphere;

//! A three-dimensional axis-aligned bounding box
class BoundingBox
{
public:
    //! Construct with zero size
    BoundingBox() :
        mMin(Vector3::sZero),
        mMax(Vector3::sZero),
        mDefined(false)
    {
    }
    
    //! Copy-construct from another bounding box
    BoundingBox(const BoundingBox& box) :
        mMin(box.mMin),
        mMax(box.mMax),
        mDefined(box.mDefined)
    {
    }
    
    //! Construct from a Rect, with the Z dimension left zero
    BoundingBox(const Rect& rect) :
        mMin(Vector3(rect.mMin, 0.0f)),
        mMax(Vector3(rect.mMax, 0.0f)),
        mDefined(true)
    {
    }
    
    //! Construct from minimum and maximum vectors
    BoundingBox(const Vector3& min, const Vector3& max) :
        mMin(min),
        mMax(max),
        mDefined(true)
    {
    }
    
    //! Construct from minimum and maximum floats (all dimensions same)
    BoundingBox(float min, float max) :
        mMin(Vector3(min, min, min)),
        mMax(Vector3(max, max, max)),
        mDefined(true)
    {
    }
    
    //! Assign from another bounding box
    BoundingBox& operator = (const BoundingBox& rhs)
    {
        mMin = rhs.mMin;
        mMax = rhs.mMax;
        mDefined = rhs.mDefined;
        
        return *this;
    }
    
    //! Assign from a Rect, with the Z dimension left zero
    BoundingBox& operator = (const Rect& rhs)
    {
        mMin = Vector3(rhs.mMin, 0.0f);
        mMax = Vector3(rhs.mMax, 0.0f);
        mDefined = true;
        
        return *this;
    }
    
    //! Test for equality with another bounding box
    bool operator == (const BoundingBox& rhs) const
    {
        return ((mMin == rhs.mMin) && (mMax == rhs.mMax));
    }
    
    //! Test for inequality with another bounding box
    bool operator != (const BoundingBox& rhs) const
    {
        return ((mMin != rhs.mMin) || (mMax != rhs.mMax));
    }
    
    //! Define from minimum and maximum vectors
    void define(const Vector3& min, const Vector3& max)
    {
        mMin = min;
        mMax = max;
        mDefined = true;
    }
    
    //! Define from a point
    void define(const Vector3& point)
    {
        mMin = mMax = point;
        mDefined = true;
    }
    
    //! Define from minimum and maximum floats (all dimensions same) 
    void define(float min, float max)
    {
        mMin = Vector3(min, min, min);
        mMax = Vector3(max, max, max);
        mDefined = true;
    }
    
    //! Merge a point
    void merge(const Vector3& point)
    {
        if (!mDefined)
        {
            mMin = mMax = point;
            mDefined = true;
            return;
        }
        
        if (point.mX < mMin.mX) mMin.mX = point.mX;
        if (point.mY < mMin.mY) mMin.mY = point.mY;
        if (point.mZ < mMin.mZ) mMin.mZ = point.mZ;
        if (point.mX > mMax.mX) mMax.mX = point.mX;
        if (point.mY > mMax.mY) mMax.mY = point.mY;
        if (point.mZ > mMax.mZ) mMax.mZ = point.mZ;
    }
    
    //! Merge another bounding box
    void merge(const BoundingBox& box)
    {
        if (!mDefined)
        {
            mMin = box.mMin;
            mMax = box.mMax;
            mDefined = true;
            return;
        }
    
        if (box.mMin.mX < mMin.mX) mMin.mX = box.mMin.mX;
        if (box.mMin.mY < mMin.mY) mMin.mY = box.mMin.mY;
        if (box.mMin.mZ < mMin.mZ) mMin.mZ = box.mMin.mZ;
        if (box.mMax.mX > mMax.mX) mMax.mX = box.mMax.mX;
        if (box.mMax.mY > mMax.mY) mMax.mY = box.mMax.mY;
        if (box.mMax.mZ > mMax.mZ) mMax.mZ = box.mMax.mZ;
    }
    
    //! Define from a vector of vertices
    void define(const std::vector<Vector3>& vertices);
    //! Define from an array of vertices
    void define(const Vector3* vertices, unsigned count);
    //! Define from a frustum
    void define(const Frustum& frustum);
    //! Define from a sphere
    void define(const Sphere& sphere);
    //! Merge a vector of vertices
    void merge(const std::vector<Vector3>& vertices);
    //! Merge an array of vertices
    void merge(const Vector3* vertices, unsigned count);
    //! Merge a frustum
    void merge(const Frustum& frustum);
    //! Merge a sphere
    void merge(const Sphere& sphere);
    //! Intersect with another bounding box
    void intersect(const BoundingBox& box);
    //! Transform with a 3x3 matrix
    void transform(const Matrix3& transform);
    //! Transform with a 4x3 matrix
    void transform(const Matrix4x3& transform);
    
    //! Return center
    Vector3 getCenter() const { return (mMax + mMin) * 0.5f; }
    //! Return size
    Vector3 getSize() const { return mMax - mMin; }
    //! Return half-size
    Vector3 getHalfSize() const { return (mMax - mMin) * 0.5f; }
    
    //! Return transformed by a 3x3 matrix
    BoundingBox getTransformed(const Matrix3& transform) const;
    //! Return transformed by a 4x3 matrix
    BoundingBox getTransformed(const Matrix4x3& transform) const;
    //! Return projected by a 4x4 projection matrix
    Rect getProjected(const Matrix4& projection) const;
    
    //! Test if a point is inside
    Intersection isInside(const Vector3& point) const
    {
        if ((point.mX < mMin.mX) || (point.mX > mMax.mX))
            return OUTSIDE;
        
        if ((point.mY < mMin.mY) || (point.mY > mMax.mY))
            return OUTSIDE;
        
        if ((point.mZ < mMin.mZ) || (point.mZ > mMax.mZ))
            return OUTSIDE;
        
        return INSIDE;
    }
    
    //! Test if another bounding box is inside, outside or intersects
    Intersection isInside(const BoundingBox& box) const
    {
        if ((box.mMax.mX < mMin.mX) || (box.mMin.mX > mMax.mX))
            return OUTSIDE;
        
        if ((box.mMax.mY < mMin.mY) || (box.mMin.mY > mMax.mY))
            return OUTSIDE;
        
        if ((box.mMax.mZ < mMin.mZ) || (box.mMin.mZ > mMax.mZ))
            return OUTSIDE;
        
        if ((box.mMin.mX < mMin.mX) || (box.mMax.mX > mMax.mX))
            return INTERSECTS;
        
        if ((box.mMin.mY < mMin.mY) || (box.mMax.mY > mMax.mY))
            return INTERSECTS;
        
        if ((box.mMin.mZ < mMin.mZ) || (box.mMax.mZ > mMax.mZ))
            return INTERSECTS;
        
        return INSIDE;
    }
    
    //! Test if another bounding box is (partially) inside or outside
    Intersection isInsideFast(const BoundingBox& box) const
    {
        if ((box.mMax.mX < mMin.mX) || (box.mMin.mX > mMax.mX))
            return OUTSIDE;
        
        if ((box.mMax.mY < mMin.mY) || (box.mMin.mY > mMax.mY))
            return OUTSIDE;
        
        if ((box.mMax.mZ < mMin.mZ) || (box.mMin.mZ > mMax.mZ))
            return OUTSIDE;
        
        return INSIDE;
    }
    
    //! Test if a sphere is inside, outside or intersects
    Intersection isInside(const Sphere& sphere) const;
    //! Test if a sphere is (partially) inside or outside
    Intersection isInsideFast(const Sphere& sphere) const;
    //! Return ray hit distance, or infinity if no hit
    float getDistance(const Ray& ray) const;
    
    //! Minimum vector
    Vector3 mMin;
    //! Maximum vector
    Vector3 mMax;
    //! Defined flag
    bool mDefined;
};

#endif // MATH_BOUNDINGBOX_H
