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

#pragma once

#include "BoundingBox.h"
#include "Matrix4x3.h"
#include "Plane.h"
#include "Rect.h"
#include "Sphere.h"

enum FrustumPlane
{
    PLANE_NEAR = 0,
    PLANE_LEFT,
    PLANE_RIGHT,
    PLANE_UP,
    PLANE_DOWN,
    PLANE_FAR,
};

static const int NUM_FRUSTUM_PLANES = 6;
static const int NUM_FRUSTUM_VERTICES = 8;

/// Convex constructed of 6 planes
class Frustum
{
public:
    /// Construct an undefined frustum
    Frustum();
    /// Copy-construct from another frustum
    Frustum(const Frustum& frustum);
    
    /// Assign from another frustum
    Frustum& operator = (const Frustum& rhs);
    
    /// Define with projection parameters and a transform matrix
    void Define(float fov, float aspectRatio, float zoom, float nearZ, float farZ, const Matrix4x3& transform = Matrix4x3::IDENTITY);
    /// Define with near and far dimension vectors and a transform matrix
    void Define(const Vector3& near, const Vector3& far, const Matrix4x3& transform);
    /// Define with orthographic projection parameters and a transform matrix
    void DefineOrtho(float orthoSize, float aspectRatio, float zoom, float nearZ, float farZ, const Matrix4x3& transform = Matrix4x3::IDENTITY);
    /// Transform by a 3x3 matrix
    void Transform(const Matrix3& transform);
    /// Transform by a 4x3 matrix
    void Transform(const Matrix4x3& transform);
    
    /// Test if a point is inside or outside
    Intersection IsInside(const Vector3& point) const
    {
        for (unsigned i = 0; i < NUM_FRUSTUM_PLANES; ++i)
        {
            if (planes_[i].GetDistance(point) < 0.0)
                return OUTSIDE;
        }
        
        return INSIDE;
    }
    
    /// Test if a sphere is inside, outside or intersects
    Intersection IsInside(const Sphere& sphere) const
    {
        float radius = sphere.radius_;
        bool allInside = true;
        
        for (unsigned i = 0; i < NUM_FRUSTUM_PLANES; ++i)
        {
            float dist = planes_[i].GetDistance(sphere.center_);
            
            if (dist < -radius)
                return OUTSIDE;
            if (dist < radius)
                allInside = false;
        }
        
        return allInside ? INSIDE : INTERSECTS;
    }
    
    /// Test if a sphere if (partially) inside or outside
    Intersection IsInsideFast(const Sphere& sphere) const
    {
        float radius = sphere.radius_;
        
        for (unsigned i = 0; i < NUM_FRUSTUM_PLANES; ++i)
        {
            float dist = planes_[i].GetDistance(sphere.center_);
            
            if (dist < -radius)
                return OUTSIDE;
        }
        
        return INSIDE;
    }
    
    /// Test if a bounding box is inside, outside or intersects
    Intersection IsInside(const BoundingBox& box) const
    {
        Vector3 center = box.GetCenter();
        Vector3 edge = center - box.min_;
        bool allInside = true;
        
        for (unsigned i = 0; i < NUM_FRUSTUM_PLANES; ++i)
        {
            float dist = planes_[i].GetDistance(center);
            float absDist = planes_[i].GetAbsDistanceFast(edge);
            
            if (dist < -absDist)
                return OUTSIDE;
            if (dist < absDist)
                allInside = false;
        }
        
        return allInside ? INSIDE : INTERSECTS;
    }
    
    /// Test if a bounding box is (partially) inside or outside
    Intersection IsInsideFast(const BoundingBox& box) const
    {
        Vector3 center = box.GetCenter();
        Vector3 edge = center - box.min_;
        
        for (unsigned i = 0; i < NUM_FRUSTUM_PLANES; ++i)
        {
            float dist = planes_[i].GetDistance(center);
            float absDist = planes_[i].GetAbsDistanceFast(edge);
            
            if (dist < -absDist)
                return OUTSIDE;
        }
        
        return INSIDE;
    }
    
    /// Test if a bounding box is inside, outside or intersects. Use (and update) a plane bitmask to speed up testing a box hierarchy
    Intersection IsInsideMasked(const BoundingBox& box, unsigned& mask) const
    {
        Vector3 center = box.GetCenter();
        Vector3 edge = center - box.min_;
        bool allInside = true;
        
        for (unsigned i = 0; i < NUM_FRUSTUM_PLANES; ++i)
        {
            unsigned bit = 1 << i;
            if (!(mask & bit))
            {
                float dist = planes_[i].GetDistance(center);
                float absDist = planes_[i].GetAbsDistanceFast(edge);
                
                if (dist < -absDist)
                    return OUTSIDE;
                if (dist < absDist)
                    allInside = false;
                else
                    mask |= bit;
            }
        }
        
        return allInside ? INSIDE : INTERSECTS;
    }
    
    /// Test if a bounding box is (partially) inside or outside. Use a bitmask to skip unnecessary planes
    Intersection IsInsideFastMasked(const BoundingBox& box, unsigned mask) const
    {
        Vector3 center = box.GetCenter();
        Vector3 edge = center - box.min_;
        
        for (unsigned i = 0; i < NUM_FRUSTUM_PLANES; ++i)
        {
            unsigned bit = 1 << i;
            if (!(mask & bit))
            {
                float dist = planes_[i].GetDistance(center);
                float absDist = planes_[i].GetAbsDistanceFast(edge);
                
                if (dist < -absDist)
                    return OUTSIDE;
            }
        }
        
        return INSIDE;
    }
    
    /// Return all planes
    const Plane* GetPlanes() const { return &planes_[0]; }
    /// Return all vertices
    const Vector3* GetVertices() const { return &vertices_[0]; }
    /// Return a plane
    const Plane& GetPlane(FrustumPlane plane) const { return planes_[plane]; }
    /// Return transformed by a 3x3 matrix
    Frustum GetTransformed(const Matrix3& transform) const;
    /// Return transformed by a 4x3 matrix
    Frustum GetTransformed(const Matrix4x3& transform) const;
    /// Return projected by a 4x4 projection matrix
    Rect GetProjected(const Matrix4& transform) const;
    
    /// Update the planes. Called internally
    void UpdatePlanes();
    
    /// Frustum planes
    Plane planes_[NUM_FRUSTUM_PLANES];
    /// Frustum vertices
    Vector3 vertices_[NUM_FRUSTUM_VERTICES];
    /// Defined flag
    bool defined_;
};
