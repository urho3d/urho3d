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

#ifndef RENDERER_OCTREEQUERY_H
#define RENDERER_OCTREEQUERY_H

#include "BoundingBox.h"
#include "Frustum.h"
#include "Ray.h"
#include "Sphere.h"

#include <vector>

class OcclusionBuffer;
class VolumeNode;

//! Base class for octree queries
class OctreeQuery
{
public:
    //! Construct with result vector, include/exclude flags and whether to get only occluders or shadowcasters
    OctreeQuery(std::vector<VolumeNode*>& result, unsigned nodeFlags, bool occludersOnly, bool shadowCastersOnly) :
        mResult(result),
        mNodeFlags(nodeFlags),
        mOccludersOnly(occludersOnly),
        mShadowCastersOnly(shadowCastersOnly)
    {
    }
    
    //! Destruct
    virtual ~OctreeQuery()
    {
    }
    
    //! Intersection test for an octant
    virtual Intersection testOctant(const BoundingBox& box, unsigned& mask) const = 0;
    //! Intersection test for a scene node
    virtual Intersection testNode(const BoundingBox& box, unsigned& mask) const = 0;
    
    //! Result vector reference
    std::vector<VolumeNode*>& mResult;
    //! Scene node flags to include
    unsigned mNodeFlags;
    //! Get occluders only flag
    bool mOccludersOnly;
    //! Get shadowcasters only flag
    bool mShadowCastersOnly;
};

//! Point octree query
class PointOctreeQuery : public OctreeQuery
{
public:
    //! Construct with point and query parameters
    PointOctreeQuery(std::vector<VolumeNode*>& result, const Vector3& point, unsigned nodeFlags, bool occludersOnly = false,
        bool shadowCastersOnly = false) :
        OctreeQuery(result, nodeFlags, occludersOnly, shadowCastersOnly),
        mPoint(point)
    {
    }
    
    //! Intersection test for an octant
    virtual Intersection testOctant(const BoundingBox& box, unsigned& mask) const;
    //! Intersection test for a scene node
    virtual Intersection testNode(const BoundingBox& box, unsigned& mask) const;
    
    //! Point
    Vector3 mPoint;
};

//! Sphere octree query
class SphereOctreeQuery : public OctreeQuery
{
public:
    //! Construct with sphere and query parameters
    SphereOctreeQuery(std::vector<VolumeNode*>& result, const Sphere& sphere, unsigned nodeFlags, bool occludersOnly = false,
        bool shadowCastersOnly = false) :
        OctreeQuery(result, nodeFlags, occludersOnly, shadowCastersOnly),
        mSphere(sphere)
    {
    }
    
    //! Intersection test for an octant
    virtual Intersection testOctant(const BoundingBox& box, unsigned& mask) const;
    //! Intersection test for a scene node
    virtual Intersection testNode(const BoundingBox& box, unsigned& mask) const;
    
    //! Sphere
    Sphere mSphere;
};

//! Bounding box octree query
class BoxOctreeQuery : public OctreeQuery
{
public:
    //! Construct with bounding box and query parameters
    BoxOctreeQuery(std::vector<VolumeNode*>& result, const BoundingBox& box, unsigned nodeFlags, bool occludersOnly = false,
        bool shadowCastersOnly = false) :
        OctreeQuery(result, nodeFlags, occludersOnly, shadowCastersOnly),
        mBox(box)
    {
    }
    
    //! Intersection test for an octant
    virtual Intersection testOctant(const BoundingBox& box, unsigned& mask) const;
    //! Intersection test for a scene node
    virtual Intersection testNode(const BoundingBox& box, unsigned& mask) const;
    
    //! Bounding box
    BoundingBox mBox;
};

//! Frustum octree query
class FrustumOctreeQuery : public OctreeQuery
{
public:
    //! Construct with frustum and query parameters
    FrustumOctreeQuery(std::vector<VolumeNode*>& result, const Frustum& frustum, unsigned nodeFlags, bool occludersOnly = false,
        bool shadowCastersOnly = false) :
        OctreeQuery(result, nodeFlags, occludersOnly, shadowCastersOnly),
        mFrustum(frustum)
    {
    }
    
    //! Intersection test for an octant
    virtual Intersection testNode(const BoundingBox& box, unsigned& mask) const;
    //! Intersection test for a scene node
    virtual Intersection testOctant(const BoundingBox& box, unsigned& mask) const;
    
    //! Frustum
    Frustum mFrustum;
};

//! Frustum octree query with occlusion
class OccludedFrustumOctreeQuery : public OctreeQuery
{
public:
    //! Construct with frustum, occlusion buffer pointer and query parameters
    OccludedFrustumOctreeQuery(std::vector<VolumeNode*>& result, const Frustum& frustum, OcclusionBuffer* buffer,
            unsigned nodeFlags, bool occludersOnly = false, bool shadowCastersOnly = false) :
        OctreeQuery(result, nodeFlags, occludersOnly, shadowCastersOnly),
        mFrustum(frustum),
        mBuffer(buffer)
    {
    }
    
    //! Intersection test for an octant
    virtual Intersection testOctant(const BoundingBox& box, unsigned& mask) const;
    //! Intersection test for a scene node
    virtual Intersection testNode(const BoundingBox& box, unsigned& mask) const;
    
    //! Frustum
    Frustum mFrustum;
    //! Occlusion buffer
    OcclusionBuffer* mBuffer;
};

//! Renderer raycast detail level
enum RayQueryLevel
{
    RAY_AABB_NOSUBOBJECTS = 0,
    RAY_AABB,
    RAY_OBB,
    RAY_TRIANGLE
};

//! Raycast result
struct RayQueryResult
{
    //! Construct
    RayQueryResult() :
        mSubObject(M_MAX_UNSIGNED)
    {
    }
    
    //! Scene node
    VolumeNode* mNode;
    //! Distance from ray origin
    float mDistance;
    //! Scene node specific subobject (instance, bone etc.)
    unsigned mSubObject;
};

//! Ray octree query
class RayOctreeQuery
{
public:
    //! Construct with ray and query parameters
    RayOctreeQuery(std::vector<RayQueryResult>& result, const Ray& ray, unsigned nodeFlags, bool occludersOnly = false,
        bool shadowCastersOnly = false, float maxDistance = M_INFINITY, RayQueryLevel level = RAY_TRIANGLE) :
        mRay(ray),
        mResult(result),
        mNodeFlags(nodeFlags),
        mOccludersOnly(occludersOnly),
        mShadowCastersOnly(shadowCastersOnly),
        mMaxDistance(maxDistance),
        mLevel(level)
    {
    }
    
    //! Ray
    Ray mRay;
    //! Result vector reference
    std::vector<RayQueryResult>& mResult;
    //! Scene node flags to include
    unsigned mNodeFlags;
    //! Get occluders only flag
    bool mOccludersOnly;
    //! Get shadowcasters only flag
    bool mShadowCastersOnly;
    //! Maximum ray distance
    float mMaxDistance;
    //! Raycast detail level
    RayQueryLevel mLevel;
};

#endif // RENDERER_OCTREEQUERY_H
