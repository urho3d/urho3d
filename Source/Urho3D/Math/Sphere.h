// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include "../Math/Vector3.h"

namespace Urho3D
{

class BoundingBox;
class Polyhedron;
class Frustum;

/// %Sphere in three-dimensional space.
/// @allfloats
class URHO3D_API Sphere
{
public:
    /// Construct undefined.
    Sphere() noexcept :
        center_(Vector3::ZERO),
        radius_(-M_INFINITY)
    {
    }

    /// Copy-construct from another sphere.
    Sphere(const Sphere& sphere) noexcept = default;

    /// Construct from center and radius.
    Sphere(const Vector3& center, float radius) noexcept :
        center_(center),
        radius_(radius)
    {
    }

    /// Construct from an array of vertices.
    Sphere(const Vector3* vertices, i32 count) noexcept
    {
        Define(vertices, count);
    }

    /// Construct from a bounding box.
    explicit Sphere(const BoundingBox& box) noexcept
    {
        Define(box);
    }

    /// Construct from a frustum.
    explicit Sphere(const Frustum& frustum) noexcept
    {
        Define(frustum);
    }

    /// Construct from a polyhedron.
    explicit Sphere(const Polyhedron& poly) noexcept
    {
        Define(poly);
    }

    /// Assign from another sphere.
    Sphere& operator =(const Sphere& rhs) noexcept = default;

    /// Test for equality with another sphere.
    bool operator ==(const Sphere& rhs) const { return center_ == rhs.center_ && radius_ == rhs.radius_; }

    /// Test for inequality with another sphere.
    bool operator !=(const Sphere& rhs) const { return center_ != rhs.center_ || radius_ != rhs.radius_; }

    /// Define from another sphere.
    void Define(const Sphere& sphere)
    {
        Define(sphere.center_, sphere.radius_);
    }

    /// Define from center and radius.
    void Define(const Vector3& center, float radius)
    {
        center_ = center;
        radius_ = radius;
    }

    /// Define from an array of vertices.
    void Define(const Vector3* vertices, i32 count);
    /// Define from a bounding box.
    void Define(const BoundingBox& box);
    /// Define from a frustum.
    void Define(const Frustum& frustum);
    /// Define from a polyhedron.
    void Define(const Polyhedron& poly);

    /// Merge a point.
    void Merge(const Vector3& point)
    {
        if (radius_ < 0.0f)
        {
            center_ = point;
            radius_ = 0.0f;
            return;
        }

        Vector3 offset = point - center_;
        float dist = offset.Length();

        if (dist > radius_)
        {
            float half = (dist - radius_) * 0.5f;
            radius_ += half;
            center_ += (half / dist) * offset;
        }
    }

    /// Merge an array of vertices.
    void Merge(const Vector3* vertices, i32 count);
    /// Merge a bounding box.
    void Merge(const BoundingBox& box);
    /// Merge a frustum.
    void Merge(const Frustum& frustum);
    /// Merge a polyhedron.
    void Merge(const Polyhedron& poly);
    /// Merge a sphere.
    void Merge(const Sphere& sphere);

    /// Clear to undefined state.
    void Clear()
    {
        center_ = Vector3::ZERO;
        radius_ = -M_INFINITY;
    }

    /// Return true if this sphere is defined via a previous call to Define() or Merge().
    bool Defined() const
    {
        return radius_ >= 0.0f;
    }

    /// Test if a point is inside.
    Intersection IsInside(const Vector3& point) const
    {
        float distSquared = (point - center_).LengthSquared();
        if (distSquared < radius_ * radius_)
            return INSIDE;
        else
            return OUTSIDE;
    }

    /// Test if another sphere is inside, outside or intersects.
    Intersection IsInside(const Sphere& sphere) const
    {
        float dist = (sphere.center_ - center_).Length();
        if (dist >= sphere.radius_ + radius_)
            return OUTSIDE;
        else if (dist + sphere.radius_ < radius_)
            return INSIDE;
        else
            return INTERSECTS;
    }

    /// Test if another sphere is (partially) inside or outside.
    Intersection IsInsideFast(const Sphere& sphere) const
    {
        float distSquared = (sphere.center_ - center_).LengthSquared();
        float combined = sphere.radius_ + radius_;

        if (distSquared >= combined * combined)
            return OUTSIDE;
        else
            return INSIDE;
    }

    /// Test if a bounding box is inside, outside or intersects.
    Intersection IsInside(const BoundingBox& box) const;
    /// Test if a bounding box is (partially) inside or outside.
    Intersection IsInsideFast(const BoundingBox& box) const;

    /// Return distance of a point to the surface, or 0 if inside.
    float Distance(const Vector3& point) const { return Max((point - center_).Length() - radius_, 0.0f); }
    /// Return point on the sphere relative to sphere position.
    Vector3 GetLocalPoint(float theta, float phi) const;
    /// Return point on the sphere.
    Vector3 GetPoint(float theta, float phi) const { return center_ + GetLocalPoint(theta, phi); }

    /// Sphere center.
    Vector3 center_;
    /// Sphere radius.
    float radius_{};
};

}
