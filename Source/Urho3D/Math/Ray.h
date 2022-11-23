// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include "../Math/Vector3.h"
#include "../Math/Matrix3x4.h"

namespace Urho3D
{

class BoundingBox;
class Frustum;
class Plane;
class Sphere;

/// Infinite straight line in three-dimensional space.
/// @allfloats
class URHO3D_API Ray
{
public:
    /// Construct a degenerate ray with zero origin and direction.
    Ray() noexcept = default;

    /// Construct from origin and direction. The direction will be normalized.
    Ray(const Vector3& origin, const Vector3& direction) noexcept
    {
        Define(origin, direction);
    }

    /// Copy-construct from another ray.
    Ray(const Ray& ray) noexcept = default;

    /// Assign from another ray.
    Ray& operator =(const Ray& rhs) noexcept = default;

    /// Check for equality with another ray.
    bool operator ==(const Ray& rhs) const { return origin_ == rhs.origin_ && direction_ == rhs.direction_; }

    /// Check for inequality with another ray.
    bool operator !=(const Ray& rhs) const { return origin_ != rhs.origin_ || direction_ != rhs.direction_; }

    /// Define from origin and direction. The direction will be normalized.
    void Define(const Vector3& origin, const Vector3& direction)
    {
        origin_ = origin;
        direction_ = direction.Normalized();
    }

    /// Project a point on the ray.
    Vector3 Project(const Vector3& point) const
    {
        Vector3 offset = point - origin_;
        return origin_ + offset.DotProduct(direction_) * direction_;
    }

    /// Return distance of a point from the ray.
    float Distance(const Vector3& point) const
    {
        Vector3 projected = Project(point);
        return (point - projected).Length();
    }

    /// Return closest point to another ray.
    Vector3 ClosestPoint(const Ray& ray) const;
    /// Return hit distance to a plane, or infinity if no hit.
    float HitDistance(const Plane& plane) const;
    /// Return hit distance to a bounding box, or infinity if no hit.
    float HitDistance(const BoundingBox& box) const;
    /// Return hit distance to a frustum, or infinity if no hit. If solidInside parameter is true (default) rays originating from inside return zero distance, otherwise the distance to the closest plane.
    float HitDistance(const Frustum& frustum, bool solidInside = true) const;
    /// Return hit distance to a sphere, or infinity if no hit.
    float HitDistance(const Sphere& sphere) const;
    /// Return hit distance to a triangle, or infinity if no hit. Optionally return hit normal and hit barycentric coordinate at intersect point.
    float HitDistance(const Vector3& v0, const Vector3& v1, const Vector3& v2, Vector3* outNormal = nullptr, Vector3* outBary = nullptr) const;
    /// Return hit distance to non-indexed geometry data, or infinity if no hit. Optionally return hit normal and hit uv coordinates at intersect point.
    float HitDistance
        (const void* vertexData, i32 vertexStride, i32 vertexStart, i32 vertexCount, Vector3* outNormal = nullptr,
            Vector2* outUV = nullptr, i32 uvOffset = 0) const;
    /// Return hit distance to indexed geometry data, or infinity if no hit. Optionally return hit normal and hit uv coordinates at intersect point.
    float HitDistance(const void* vertexData, i32 vertexStride, const void* indexData, i32 indexSize, i32 indexStart,
        i32 indexCount, Vector3* outNormal = nullptr, Vector2* outUV = nullptr, i32 uvOffset = 0) const;
    /// Return whether ray is inside non-indexed geometry.
    bool InsideGeometry(const void* vertexData, i32 vertexSize, i32 vertexStart, i32 vertexCount) const;
    /// Return whether ray is inside indexed geometry.
    bool InsideGeometry(const void* vertexData, i32 vertexSize, const void* indexData, i32 indexSize, i32 indexStart,
        i32 indexCount) const;
    /// Return transformed by a 3x4 matrix. This may result in a non-normalized direction.
    Ray Transformed(const Matrix3x4& transform) const;

    /// Ray origin.
    Vector3 origin_;
    /// Ray direction.
    Vector3 direction_;
};

}
