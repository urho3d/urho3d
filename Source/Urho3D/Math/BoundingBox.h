//
// Copyright (c) 2008-2015 the Urho3D project.
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

#include "../Math/Rect.h"
#include "../Math/Vector3.h"

namespace Urho3D
{

class Polyhedron;
class Frustum;
class Matrix3;
class Matrix4;
class Matrix3x4;
class Sphere;

/// Three-dimensional axis-aligned bounding box.
class URHO3D_API BoundingBox
{
public:
    /// Construct with zero size.
    BoundingBox() :
        min_(Vector3::ZERO),
        max_(Vector3::ZERO),
        defined_(false)
    {
    }
    
    /// Copy-construct from another bounding box.
    BoundingBox(const BoundingBox& box) :
        min_(box.min_),
        max_(box.max_),
        defined_(box.defined_)
    {
    }
    
    /// Construct from a rect, with the Z dimension left zero.
    BoundingBox(const Rect& rect) :
        min_(Vector3(rect.min_, 0.0f)),
        max_(Vector3(rect.max_, 0.0f)),
        defined_(true)
    {
    }
    
    /// Construct from minimum and maximum vectors.
    BoundingBox(const Vector3& min, const Vector3& max) :
        min_(min),
        max_(max),
        defined_(true)
    {
    }
    
    /// Construct from minimum and maximum floats (all dimensions same.)
    BoundingBox(float min, float max) :
        min_(Vector3(min, min, min)),
        max_(Vector3(max, max, max)),
        defined_(true)
    {
    }
    
    /// Construct from an array of vertices.
    BoundingBox(const Vector3* vertices, unsigned count) :
        defined_(false)
    {
        Define(vertices, count);
    }
    
    /// Construct from a frustum.
    BoundingBox(const Frustum& frustum) :
        defined_(false)
    {
        Define(frustum);
    }
    
    /// Construct from a polyhedron.
    BoundingBox(const Polyhedron& poly) :
        defined_(false)
    {
        Define(poly);
    }
    
    /// Construct from a sphere.
    BoundingBox(const Sphere& sphere) :
        defined_(false)
    {
        Define(sphere);
    }
    
    /// Assign from another bounding box.
    BoundingBox& operator = (const BoundingBox& rhs)
    {
        min_ = rhs.min_;
        max_ = rhs.max_;
        defined_ = rhs.defined_;
        return *this;
    }
    
    /// Assign from a Rect, with the Z dimension left zero.
    BoundingBox& operator = (const Rect& rhs)
    {
        min_ = Vector3(rhs.min_, 0.0f);
        max_ = Vector3(rhs.max_, 0.0f);
        defined_ = true;
        return *this;
    }
    
    /// Test for equality with another bounding box.
    bool operator == (const BoundingBox& rhs) const { return (min_ == rhs.min_ && max_ == rhs.max_); }
    
    /// Test for inequality with another bounding box.
    bool operator != (const BoundingBox& rhs) const { return (min_ != rhs.min_ || max_ != rhs.max_); }
    
    /// Define from another bounding box.
    void Define(const BoundingBox& box)
    {
        Define(box.min_, box.max_);
    }
    
    /// Define from a Rect.
    void Define(const Rect& rect)
    {
        Define(Vector3(rect.min_, 0.0f), Vector3(rect.max_, 0.0f));
    }
    
    /// Define from minimum and maximum vectors.
    void Define(const Vector3& min, const Vector3& max)
    {
        min_ = min;
        max_ = max;
        defined_ = true;
    }
    
    /// Define from minimum and maximum floats (all dimensions same.)
    void Define(float min, float max)
    {
        min_ = Vector3(min, min, min);
        max_ = Vector3(max, max, max);
        defined_ = true;
    }
    
    /// Define from a point.
    void Define(const Vector3& point)
    {
        min_ = max_ = point;
        defined_ = true;
    }
    
    /// Merge a point.
    void Merge(const Vector3& point)
    {
        if (!defined_)
        {
            min_ = max_ = point;
            defined_ = true;
            return;
        }
        
        if (point.x_ < min_.x_)
            min_.x_ = point.x_;
        if (point.y_ < min_.y_)
            min_.y_ = point.y_;
        if (point.z_ < min_.z_)
            min_.z_ = point.z_;
        if (point.x_ > max_.x_)
            max_.x_ = point.x_;
        if (point.y_ > max_.y_)
            max_.y_ = point.y_;
        if (point.z_ > max_.z_)
            max_.z_ = point.z_;
    }
    
    /// Merge another bounding box.
    void Merge(const BoundingBox& box)
    {
        if (!defined_)
        {
            min_ = box.min_;
            max_ = box.max_;
            defined_ = true;
            return;
        }
    
        if (box.min_.x_ < min_.x_)
            min_.x_ = box.min_.x_;
        if (box.min_.y_ < min_.y_)
            min_.y_ = box.min_.y_;
        if (box.min_.z_ < min_.z_)
            min_.z_ = box.min_.z_;
        if (box.max_.x_ > max_.x_)
            max_.x_ = box.max_.x_;
        if (box.max_.y_ > max_.y_)
            max_.y_ = box.max_.y_;
        if (box.max_.z_ > max_.z_)
            max_.z_ = box.max_.z_;
    }
    
    /// Define from an array of vertices.
    void Define(const Vector3* vertices, unsigned count);
    /// Define from a frustum.
    void Define(const Frustum& frustum);
    /// Define from a polyhedron.
    void Define(const Polyhedron& poly);
    /// Define from a sphere.
    void Define(const Sphere& sphere);
    /// Merge an array of vertices.
    void Merge(const Vector3* vertices, unsigned count);
    /// Merge a frustum.
    void Merge(const Frustum& frustum);
    /// Merge a polyhedron.
    void Merge(const Polyhedron& poly);
    /// Merge a sphere.
    void Merge(const Sphere& sphere);
    /// Clip with another bounding box.
    void Clip(const BoundingBox& box);
    /// Transform with a 3x3 matrix.
    void Transform(const Matrix3& transform);
    /// Transform with a 3x4 matrix.
    void Transform(const Matrix3x4& transform);
    
    /// Clear to undefined state.
    void Clear()
    {
        min_ = Vector3::ZERO;
        max_ = Vector3::ZERO;
        defined_ = false;
    }
    
    /// Return center.
    Vector3 Center() const { return (max_ + min_) * 0.5f; }
    /// Return size.
    Vector3 Size() const { return max_ - min_; }
    /// Return half-size.
    Vector3 HalfSize() const { return (max_ - min_) * 0.5f; }
    
    /// Return transformed by a 3x3 matrix.
    BoundingBox Transformed(const Matrix3& transform) const;
    /// Return transformed by a 3x4 matrix.
    BoundingBox Transformed(const Matrix3x4& transform) const;
    /// Return projected by a 4x4 projection matrix.
    Rect Projected(const Matrix4& projection) const;
    
    /// Test if a point is inside.
    Intersection IsInside(const Vector3& point) const
    {
        if (point.x_ < min_.x_ || point.x_ > max_.x_ || point.y_ < min_.y_ || point.y_ > max_.y_ ||
            point.z_ < min_.z_ || point.z_ > max_.z_)
            return OUTSIDE;
        else
            return INSIDE;
    }
    
    /// Test if another bounding box is inside, outside or intersects.
    Intersection IsInside(const BoundingBox& box) const
    {
        if (box.max_.x_ < min_.x_ || box.min_.x_ > max_.x_ || box.max_.y_ < min_.y_ || box.min_.y_ > max_.y_ ||
            box.max_.z_ < min_.z_ || box.min_.z_ > max_.z_)
            return OUTSIDE;
        else if (box.min_.x_ < min_.x_ || box.max_.x_ > max_.x_ || box.min_.y_ < min_.y_ || box.max_.y_ > max_.y_ ||
            box.min_.z_ < min_.z_ || box.max_.z_ > max_.z_)
            return INTERSECTS;
        else
            return INSIDE;
    }
    
    /// Test if another bounding box is (partially) inside or outside.
    Intersection IsInsideFast(const BoundingBox& box) const
    {
        if (box.max_.x_ < min_.x_ || box.min_.x_ > max_.x_ || box.max_.y_ < min_.y_ || box.min_.y_ > max_.y_ ||
            box.max_.z_ < min_.z_ || box.min_.z_ > max_.z_)
            return OUTSIDE;
        else
            return INSIDE;
    }
    
    /// Test if a sphere is inside, outside or intersects.
    Intersection IsInside(const Sphere& sphere) const;
    /// Test if a sphere is (partially) inside or outside.
    Intersection IsInsideFast(const Sphere& sphere) const;
    
    /// Return as string.
    String ToString() const;
    
    /// Minimum vector.
    Vector3 min_;
    /// Maximum vector.
    Vector3 max_;
    /// Defined flag.
    bool defined_;
};

}
