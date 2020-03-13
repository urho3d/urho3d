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
    OctreeQuery(PODVector<Drawable*>& result, unsigned char drawableFlags, unsigned viewMask) :
        result_(result),
        drawableFlags_(drawableFlags),
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
    PODVector<Drawable*>& result_;
    /// Drawable flags to include.
    unsigned char drawableFlags_;
    /// Drawable layers to include.
    unsigned viewMask_;
};

/// Point octree query.
class URHO3D_API PointOctreeQuery : public OctreeQuery
{
public:
    /// Construct with point and query parameters.
    PointOctreeQuery(PODVector<Drawable*>& result, const Vector3& point, unsigned char drawableFlags = DRAWABLE_ANY,
        unsigned viewMask = DEFAULT_VIEWMASK) :
        OctreeQuery(result, drawableFlags, viewMask),
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
class URHO3D_API SphereOctreeQuery : public OctreeQuery
{
public:
    /// Construct with sphere and query parameters.
    SphereOctreeQuery(PODVector<Drawable*>& result, const Sphere& sphere, unsigned char drawableFlags = DRAWABLE_ANY,
        unsigned viewMask = DEFAULT_VIEWMASK) :
        OctreeQuery(result, drawableFlags, viewMask),
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
class URHO3D_API BoxOctreeQuery : public OctreeQuery
{
public:
    /// Construct with bounding box and query parameters.
    BoxOctreeQuery(PODVector<Drawable*>& result, const BoundingBox& box, unsigned char drawableFlags = DRAWABLE_ANY,
        unsigned viewMask = DEFAULT_VIEWMASK) :
        OctreeQuery(result, drawableFlags, viewMask),
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
class URHO3D_API FrustumOctreeQuery : public OctreeQuery
{
public:
    /// Construct with frustum and query parameters.
    FrustumOctreeQuery(PODVector<Drawable*>& result, const Frustum& frustum, unsigned char drawableFlags = DRAWABLE_ANY,
        unsigned viewMask = DEFAULT_VIEWMASK) :
        OctreeQuery(result, drawableFlags, viewMask),
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
    unsigned subObject_{};
};

/// Raycast octree query.
class URHO3D_API RayOctreeQuery
{
public:
    /// Construct with ray and query parameters.
    RayOctreeQuery(PODVector<RayQueryResult>& result, const Ray& ray, RayQueryLevel level = RAY_TRIANGLE,
        float maxDistance = M_INFINITY, unsigned char drawableFlags = DRAWABLE_ANY, unsigned viewMask = DEFAULT_VIEWMASK) :
        result_(result),
        ray_(ray),
        drawableFlags_(drawableFlags),
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
    PODVector<RayQueryResult>& result_;
    /// Ray.
    Ray ray_;
    /// Drawable flags to include.
    unsigned char drawableFlags_;
    /// Drawable layers to include.
    unsigned viewMask_;
    /// Maximum ray distance.
    float maxDistance_;
    /// Raycast detail level.
    RayQueryLevel level_;
};

class URHO3D_API AllContentOctreeQuery : public OctreeQuery
{
public:
    /// Construct.
    AllContentOctreeQuery(PODVector<Drawable*>& result, unsigned char drawableFlags, unsigned viewMask) :
        OctreeQuery(result, drawableFlags, viewMask)
    {
    }

    /// Intersection test for an octant.
    Intersection TestOctant(const BoundingBox& box, bool inside) override;
    /// Intersection test for drawables.
    void TestDrawables(Drawable** start, Drawable** end, bool inside) override;
};

}
