// Copyright (c) 2008-2023 the Urho3D project
// License: MIT

/// \file

#pragma once

#include "../Graphics/Drawable.h"
#include "../Math/BoundingBox.h"
#include "../Math/Frustum.h"
#include "../Math/Ray.h"
#include "../Math/Sphere.h"

namespace Urho3D
{

class Drawable;
class Node;

/// Base class for octree queries.
class URHO3D_API OctreeQuery
{
public:
    /// Construct with query parameters.
    OctreeQuery(Vector<Drawable*>& result, DrawableTypes drawableTypes, unsigned viewMask) :
        result_(result),
        drawableTypes_(drawableTypes),
        viewMask_(viewMask)
    {
    }

    /// Destruct.
    virtual ~OctreeQuery() = default;

    /// Prevent copy construction.
    OctreeQuery(const OctreeQuery& rhs) = delete;
    /// Prevent assignment.
    OctreeQuery& operator =(const OctreeQuery& rhs) = delete;

    /// Intersection test for an octant.
    virtual Intersection TestOctant(const BoundingBox& box, bool inside) = 0;
    /// Intersection test for drawables.
    virtual void TestDrawables(Drawable** start, Drawable** end, bool inside) = 0;

    /// Result vector reference.
    Vector<Drawable*>& result_;
    /// Drawable flags to include.
    DrawableTypes drawableTypes_;
    /// Drawable layers to include.
    unsigned viewMask_;
};

/// Point octree query.
/// @nobind
class URHO3D_API PointOctreeQuery : public OctreeQuery
{
public:
    /// Construct with point and query parameters.
    PointOctreeQuery(Vector<Drawable*>& result, const Vector3& point, DrawableTypes drawableTypes = DrawableTypes::Any,
        unsigned viewMask = DEFAULT_VIEWMASK) :
        OctreeQuery(result, drawableTypes, viewMask),
        point_(point)
    {
    }

    /// Intersection test for an octant.
    Intersection TestOctant(const BoundingBox& box, bool inside) override;
    /// Intersection test for drawables.
    void TestDrawables(Drawable** start, Drawable** end, bool inside) override;

    /// Point.
    Vector3 point_;
};

/// %Sphere octree query.
/// @nobind
class URHO3D_API SphereOctreeQuery : public OctreeQuery
{
public:
    /// Construct with sphere and query parameters.
    SphereOctreeQuery(Vector<Drawable*>& result, const Sphere& sphere, DrawableTypes drawableTypes = DrawableTypes::Any,
        unsigned viewMask = DEFAULT_VIEWMASK) :
        OctreeQuery(result, drawableTypes, viewMask),
        sphere_(sphere)
    {
    }

    /// Intersection test for an octant.
    Intersection TestOctant(const BoundingBox& box, bool inside) override;
    /// Intersection test for drawables.
    void TestDrawables(Drawable** start, Drawable** end, bool inside) override;

    /// Sphere.
    Sphere sphere_;
};

/// Bounding box octree query.
/// @nobind
class URHO3D_API BoxOctreeQuery : public OctreeQuery
{
public:
    /// Construct with bounding box and query parameters.
    BoxOctreeQuery(Vector<Drawable*>& result, const BoundingBox& box, DrawableTypes drawableTypes = DrawableTypes::Any,
        unsigned viewMask = DEFAULT_VIEWMASK) :
        OctreeQuery(result, drawableTypes, viewMask),
        box_(box)
    {
    }

    /// Intersection test for an octant.
    Intersection TestOctant(const BoundingBox& box, bool inside) override;
    /// Intersection test for drawables.
    void TestDrawables(Drawable** start, Drawable** end, bool inside) override;

    /// Bounding box.
    BoundingBox box_;
};

/// %Frustum octree query.
/// @nobind
class URHO3D_API FrustumOctreeQuery : public OctreeQuery
{
public:
    /// Construct with frustum and query parameters.
    FrustumOctreeQuery(Vector<Drawable*>& result, const Frustum& frustum, DrawableTypes drawableTypes = DrawableTypes::Any,
        unsigned viewMask = DEFAULT_VIEWMASK) :
        OctreeQuery(result, drawableTypes, viewMask),
        frustum_(frustum)
    {
    }

    /// Intersection test for an octant.
    Intersection TestOctant(const BoundingBox& box, bool inside) override;
    /// Intersection test for drawables.
    void TestDrawables(Drawable** start, Drawable** end, bool inside) override;

    /// Frustum.
    Frustum frustum_;
};

/// General octree query result. Used for Lua bindings only.
struct URHO3D_API OctreeQueryResult
{
    /// Construct with defaults.
    OctreeQueryResult() :
        drawable_(nullptr),
        node_(nullptr)
    {
    }

    /// Test for inequality, added to prevent GCC from complaining.
    bool operator !=(const OctreeQueryResult& rhs) const { return drawable_ != rhs.drawable_ || node_ != rhs.node_; }

    /// Drawable.
    Drawable* drawable_;
    /// Scene node.
    Node* node_;
};

/// Graphics raycast detail level.
enum RayQueryLevel
{
    RAY_AABB = 0,
    RAY_OBB,
    RAY_TRIANGLE,
    RAY_TRIANGLE_UV
};

/// Raycast result.
struct URHO3D_API RayQueryResult
{
    /// Construct with defaults.
    RayQueryResult() :
        drawable_(nullptr),
        node_(nullptr)
    {
    }

    /// Test for inequality, added to prevent GCC from complaining.
    bool operator !=(const RayQueryResult& rhs) const
    {
        return position_ != rhs.position_ ||
               normal_ != rhs.normal_ ||
               textureUV_ != rhs.textureUV_ ||
               distance_ != rhs.distance_ ||
               drawable_ != rhs.drawable_ ||
               node_ != rhs.node_ ||
               subObject_ != rhs.subObject_;
    }

    /// Hit position in world space.
    Vector3 position_;
    /// Hit normal in world space. Negation of ray direction if per-triangle data not available.
    Vector3 normal_;
    /// Hit texture position.
    Vector2 textureUV_;
    /// Distance from ray origin.
    float distance_{};
    /// Drawable.
    Drawable* drawable_;
    /// Scene node.
    Node* node_;
    /// Drawable specific subobject if applicable.
    i32 subObject_{};
};

/// Raycast octree query.
/// @nobind
class URHO3D_API RayOctreeQuery
{
public:
    /// Construct with ray and query parameters.
    RayOctreeQuery(Vector<RayQueryResult>& result, const Ray& ray, RayQueryLevel level = RAY_TRIANGLE,
        float maxDistance = M_INFINITY, DrawableTypes drawableTypes = DrawableTypes::Any, unsigned viewMask = DEFAULT_VIEWMASK) :
        result_(result),
        ray_(ray),
        drawableTypes_(drawableTypes),
        viewMask_(viewMask),
        maxDistance_(maxDistance),
        level_(level)
    {
    }

    /// Prevent copy construction.
    RayOctreeQuery(const RayOctreeQuery& rhs) = delete;
    /// Prevent assignment.
    RayOctreeQuery& operator =(const RayOctreeQuery& rhs) = delete;

    /// Result vector reference.
    Vector<RayQueryResult>& result_;
    /// Ray.
    Ray ray_;
    /// Drawable types to include.
    DrawableTypes drawableTypes_;
    /// Drawable layers to include.
    unsigned viewMask_;
    /// Maximum ray distance.
    float maxDistance_;
    /// Raycast detail level.
    RayQueryLevel level_;
};

/// @nobind
class URHO3D_API AllContentOctreeQuery : public OctreeQuery
{
public:
    /// Construct.
    AllContentOctreeQuery(Vector<Drawable*>& result, DrawableTypes drawableTypes, unsigned viewMask) :
        OctreeQuery(result, drawableTypes, viewMask)
    {
    }

    /// Intersection test for an octant.
    Intersection TestOctant(const BoundingBox& box, bool inside) override;
    /// Intersection test for drawables.
    void TestDrawables(Drawable** start, Drawable** end, bool inside) override;
};

}
