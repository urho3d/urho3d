//
// Urho3D Engine
// Copyright (c) 2008-2012 Lasse Öörni
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

#include "BoundingBox.h"
#include "Drawable.h"
#include "Frustum.h"
#include "Ray.h"
#include "Sphere.h"

class Drawable;
class Node;

/// Base class for octree queries.
class OctreeQuery
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
    virtual ~OctreeQuery()
    {
    }
    
    /// Intersection test for an octant.
    virtual Intersection TestOctant(const BoundingBox& box, bool inside) const = 0;
    /// Intersection test for a drawable.
    virtual Intersection TestDrawable(Drawable* drawable, bool inside) const = 0;
    
    /// Result vector reference.
    PODVector<Drawable*>& result_;
    /// Drawable flags to include.
    unsigned char drawableFlags_;
    /// Drawable layers to include.
    unsigned viewMask_;
};

/// Point octree query.
class PointOctreeQuery : public OctreeQuery
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
    virtual Intersection TestOctant(const BoundingBox& box, bool inside) const;
    /// Intersection test for a drawable.
    virtual Intersection TestDrawable(Drawable* drawable, bool inside) const;
    
    /// Point.
    Vector3 point_;
};

/// %Sphere octree query.
class SphereOctreeQuery : public OctreeQuery
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
    virtual Intersection TestOctant(const BoundingBox& box, bool inside) const;
    /// Intersection test for a drawable.
    virtual Intersection TestDrawable(Drawable* drawable, bool inside) const;
    
    /// Sphere.
    Sphere sphere_;
};

/// Bounding box octree query.
class BoxOctreeQuery : public OctreeQuery
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
    virtual Intersection TestOctant(const BoundingBox& box, bool inside) const;
    /// Intersection test for a drawable.
    virtual Intersection TestDrawable(Drawable* drawable, bool inside) const;
    
    /// Bounding box.
    BoundingBox box_;
};

/// %Frustum octree query.
class FrustumOctreeQuery : public OctreeQuery
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
    virtual Intersection TestOctant(const BoundingBox& box, bool inside) const;
    /// Intersection test for a drawable.
    virtual Intersection TestDrawable(Drawable* drawable, bool inside) const;
    
    /// Frustum.
    Frustum frustum_;
};

/// Graphics raycast detail level.
enum RayQueryLevel
{
    RAY_AABB_NOSUBOBJECTS = 0,
    RAY_AABB,
    RAY_OBB,
    RAY_TRIANGLE
};

/// Raycast result.
struct RayQueryResult
{
    /// Drawable.
    Drawable* drawable_;
    /// Scene node.
    Node* node_;
    /// Distance from ray origin.
    float distance_;
    /// Drawable specific subobject if applicable.
    unsigned subObject_;
};

/// Raycast octree query.
class RayOctreeQuery
{
public:
    /// Construct with ray and query parameters.
    RayOctreeQuery(PODVector<RayQueryResult>& result, const Ray& ray, RayQueryLevel level = RAY_TRIANGLE,
        float maxDistance = M_INFINITY, unsigned char drawableFlags = DRAWABLE_ANY, unsigned viewMask = DEFAULT_VIEWMASK) :
        result_(result),
        ray_(ray),
        level_(level),
        maxDistance_(maxDistance),
        drawableFlags_(drawableFlags),
        viewMask_(viewMask)
    {
    }
    
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
