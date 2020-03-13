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

/// \file

#pragma once

#include "../Math/BoundingBox.h"
#include "../Math/Matrix3x4.h"
#include "../Math/Plane.h"
#include "../Math/Rect.h"
#include "../Math/Sphere.h"

namespace Urho3D
{

/// Frustum planes.
enum FrustumPlane
{
    PLANE_NEAR = 0,
    PLANE_LEFT,
    PLANE_RIGHT,
    PLANE_UP,
    PLANE_DOWN,
    PLANE_FAR,
};

static const unsigned NUM_FRUSTUM_PLANES = 6;
static const unsigned NUM_FRUSTUM_VERTICES = 8;

/// Convex constructed of 6 planes.
class URHO3D_API Frustum
{
public:
    /// Construct a degenerate frustum with all points at origin.
    Frustum() noexcept = default;

    /// Copy-construct from another frustum.
    Frustum(const Frustum& frustum) noexcept;

    /// Assign from another frustum.
    Frustum& operator =(const Frustum& rhs) noexcept;

    /// Define with projection parameters and a transform matrix.
    void
        Define(float fov, float aspectRatio, float zoom, float nearZ, float farZ, const Matrix3x4& transform = Matrix3x4::IDENTITY);
    /// Define with near and far dimension vectors and a transform matrix.
    void Define(const Vector3& near, const Vector3& far, const Matrix3x4& transform = Matrix3x4::IDENTITY);
    /// Define with a bounding box and a transform matrix.
    void Define(const BoundingBox& box, const Matrix3x4& transform = Matrix3x4::IDENTITY);
    /// Define from a projection or view-projection matrix.
    void Define(const Matrix4& projection);
    /// Define with orthographic projection parameters and a transform matrix.
    void DefineOrtho
        (float orthoSize, float aspectRatio, float zoom, float nearZ, float farZ, const Matrix3x4& transform = Matrix3x4::IDENTITY);
    /// Define a split (limited) frustum from a projection matrix, with near & far distances specified.
    void DefineSplit(const Matrix4& projection, float near, float far);
    /// Transform by a 3x3 matrix.
    void Transform(const Matrix3& transform);
    /// Transform by a 3x4 matrix.
    void Transform(const Matrix3x4& transform);

    /// Test if a point is inside or outside.
    Intersection IsInside(const Vector3& point) const
    {
        for (const auto& plane : planes_)
        {
            if (plane.Distance(point) < 0.0f)
                return OUTSIDE;
        }

        return INSIDE;
    }

    /// Test if a sphere is inside, outside or intersects.
    Intersection IsInside(const Sphere& sphere) const
    {
        bool allInside = true;
        for (const auto& plane : planes_)
        {
            float dist = plane.Distance(sphere.center_);
            if (dist < -sphere.radius_)
                return OUTSIDE;
            else if (dist < sphere.radius_)
                allInside = false;
        }

        return allInside ? INSIDE : INTERSECTS;
    }

    /// Test if a sphere if (partially) inside or outside.
    Intersection IsInsideFast(const Sphere& sphere) const
    {
        for (const auto& plane : planes_)
        {
            if (plane.Distance(sphere.center_) < -sphere.radius_)
                return OUTSIDE;
        }

        return INSIDE;
    }

    /// Test if a bounding box is inside, outside or intersects.
    Intersection IsInside(const BoundingBox& box) const
    {
        Vector3 center = box.Center();
        Vector3 edge = center - box.min_;
        bool allInside = true;

        for (const auto& plane : planes_)
        {
            float dist = plane.normal_.DotProduct(center) + plane.d_;
            float absDist = plane.absNormal_.DotProduct(edge);

            if (dist < -absDist)
                return OUTSIDE;
            else if (dist < absDist)
                allInside = false;
        }

        return allInside ? INSIDE : INTERSECTS;
    }

    /// Test if a bounding box is (partially) inside or outside.
    Intersection IsInsideFast(const BoundingBox& box) const
    {
        Vector3 center = box.Center();
        Vector3 edge = center - box.min_;

        for (const auto& plane : planes_)
        {
            float dist = plane.normal_.DotProduct(center) + plane.d_;
            float absDist = plane.absNormal_.DotProduct(edge);

            if (dist < -absDist)
                return OUTSIDE;
        }

        return INSIDE;
    }

    /// Return distance of a point to the frustum, or 0 if inside.
    float Distance(const Vector3& point) const
    {
        float distance = 0.0f;
        for (const auto& plane : planes_)
            distance = Max(-plane.Distance(point), distance);

        return distance;
    }

    /// Return transformed by a 3x3 matrix.
    Frustum Transformed(const Matrix3& transform) const;
    /// Return transformed by a 3x4 matrix.
    Frustum Transformed(const Matrix3x4& transform) const;
    /// Return projected by a 4x4 projection matrix.
    Rect Projected(const Matrix4& projection) const;

    /// Update the planes. Called internally.
    void UpdatePlanes();

    /// Frustum planes.
    Plane planes_[NUM_FRUSTUM_PLANES];
    /// Frustum vertices.
    Vector3 vertices_[NUM_FRUSTUM_VERTICES];
};

}
