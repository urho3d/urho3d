// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include "../Math/Vector3.h"

namespace Urho3D
{

class BoundingBox;
class Frustum;
class Matrix3;
class Matrix3x4;
class Plane;

/// A convex volume built from polygon faces.
class URHO3D_API Polyhedron
{
public:
    /// Construct empty.
    Polyhedron() noexcept = default;
    /// Destruct.
    ~Polyhedron() noexcept = default;

    /// Copy-construct from another polyhedron.
    Polyhedron(const Polyhedron& polyhedron) :
        faces_(polyhedron.faces_)
    {
    }

    /// Construct from a list of faces.
    explicit Polyhedron(const Vector<PODVector<Vector3> >& faces) :
        faces_(faces)
    {
    }

    /// Construct from a bounding box.
    explicit Polyhedron(const BoundingBox& box)
    {
        Define(box);
    }

    /// Construct from a frustum.
    explicit Polyhedron(const Frustum& frustum)
    {
        Define(frustum);
    }

    /// Assign from another polyhedron.
    Polyhedron& operator =(const Polyhedron& rhs)
    {
        faces_ = rhs.faces_;
        return *this;
    }

    /// Define from a bounding box.
    void Define(const BoundingBox& box);
    /// Define from a frustum.
    void Define(const Frustum& frustum);
    /// Add a triangle face.
    void AddFace(const Vector3& v0, const Vector3& v1, const Vector3& v2);
    /// Add a quadrilateral face.
    void AddFace(const Vector3& v0, const Vector3& v1, const Vector3& v2, const Vector3& v3);
    /// Add an arbitrary face.
    void AddFace(const PODVector<Vector3>& face);
    /// Clip with a plane.
    void Clip(const Plane& plane);
    /// Clip with a bounding box.
    void Clip(const BoundingBox& box);
    /// Clip with a frustum.
    void Clip(const Frustum& frustum);
    /// Clear all faces.
    void Clear();
    /// Transform with a 3x3 matrix.
    void Transform(const Matrix3& transform);
    /// Transform with a 3x4 matrix.
    void Transform(const Matrix3x4& transform);

    /// Return transformed with a 3x3 matrix.
    Polyhedron Transformed(const Matrix3& transform) const;
    /// Return transformed with a 3x4 matrix.
    Polyhedron Transformed(const Matrix3x4& transform) const;

    /// Return whether is empty.
    bool Empty() const { return faces_.Empty(); }

    /// Polygon faces.
    Vector<PODVector<Vector3> > faces_;

private:
    /// Set a triangle face by index.
    void SetFace(unsigned index, const Vector3& v0, const Vector3& v1, const Vector3& v2);
    /// Set a quadrilateral face by index.
    void SetFace(unsigned index, const Vector3& v0, const Vector3& v1, const Vector3& v2, const Vector3& v3);
    /// Internal vector for clipped vertices.
    PODVector<Vector3> clippedVertices_;
    /// Internal vector for the new face being constructed.
    PODVector<Vector3> outFace_;
};

}
