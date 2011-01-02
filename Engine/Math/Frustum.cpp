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

#include "Precompiled.h"
#include "Frustum.h"

inline Vector3 clipEdgeZ(const Vector3& v0, const Vector3& v1, float clipZ)
{
    return Vector3(
        v1.mX + (v0.mX - v1.mX) * ((clipZ - v1.mZ) / (v0.mZ - v1.mZ)),
        v1.mY + (v0.mY - v1.mY) * ((clipZ - v1.mZ) / (v0.mZ - v1.mZ)),
        clipZ
    );
}

void projectAndMergeEdge(Vector3 v0, Vector3 v1, Rect& rect, const Matrix4& projection)
{
    // Check if both vertices behind near plane
    if ((v0.mZ < M_MIN_NEARCLIP) && (v1.mZ < M_MIN_NEARCLIP))
        return;
    
    // Check if need to clip one of the vertices
    if (v1.mZ < M_MIN_NEARCLIP)
        v1 = clipEdgeZ(v1, v0, M_MIN_NEARCLIP);
    else if (v0.mZ < M_MIN_NEARCLIP)
        v0 = clipEdgeZ(v0, v1, M_MIN_NEARCLIP);
    
    // Project, perspective divide and merge
    Vector3 tV0(projection * v0);
    Vector3 tV1(projection * v1);
    rect.merge(Vector2(tV0.mX, tV0.mY));
    rect.merge(Vector2(tV1.mX, tV1.mY));
}

Frustum::Frustum() :
    mDefined(false)
{
}

Frustum::Frustum(const Frustum& frustum)
{
    *this = frustum;
}

Frustum& Frustum::operator = (const Frustum& rhs)
{
    for (unsigned i = 0; i < NUM_FRUSTUM_PLANES; ++i)
        mPlanes[i] = rhs.mPlanes[i];
    for (unsigned i = 0; i < NUM_FRUSTUM_VERTICES; ++i)
        mVertices[i] = rhs.mVertices[i];
    mDefined = rhs.mDefined;
    
    return *this;
}

void Frustum::define(float fov, float aspectRatio, float zoom, float nearZ, float farZ, const Matrix4x3& transform)
{
    float halfViewSize = tanf(fov * M_DEGTORAD * 0.5f) / zoom;
    Vector3 near;
    Vector3 far;
    
    nearZ = max(nearZ, 0.0f);
    farZ = max(farZ, nearZ);
    
    near.mZ = nearZ;
    near.mY = near.mZ * halfViewSize;
    near.mX = near.mY * aspectRatio;
    far.mZ = farZ;
    far.mY = far.mZ * halfViewSize;
    far.mX = far.mY * aspectRatio;
    
    define(near, far, transform);
}

void Frustum::define(const Vector3& near, const Vector3& far, const Matrix4x3& transform)
{
    mVertices[0] = transform * near;
    mVertices[1] = transform * Vector3(near.mX, -near.mY, near.mZ);
    mVertices[2] = transform * Vector3(-near.mX, -near.mY, near.mZ);
    mVertices[3] = transform * Vector3(-near.mX, near.mY, near.mZ);
    mVertices[4] = transform * far;
    mVertices[5] = transform * Vector3(far.mX, -far.mY, far.mZ);
    mVertices[6] = transform * Vector3(-far.mX, -far.mY, far.mZ);
    mVertices[7] = transform * Vector3(-far.mX, far.mY, far.mZ);
    
    updatePlanes();
}

void Frustum::defineOrtho(float orthoSize, float aspectRatio, float zoom, float nearZ, float farZ, const Matrix4x3& transform)
{
    float halfViewSize = orthoSize * 0.5f / zoom;
    Vector3 near;
    Vector3 far;
    
    nearZ = max(nearZ, 0.0f);
    farZ = max(farZ, nearZ);
    
    near.mZ = nearZ;
    far.mZ = farZ;
    far.mY = near.mY = halfViewSize;
    far.mX = near.mX = near.mY * aspectRatio;
    
    define(near, far, transform);
}

void Frustum::transform(const Matrix3& transform)
{
    for (unsigned i = 0; i < NUM_FRUSTUM_VERTICES; ++i)
        mVertices[i] = transform * mVertices[i];
    updatePlanes();
}

void Frustum::transform(const Matrix4x3& transform)
{
    for (unsigned i = 0; i < NUM_FRUSTUM_VERTICES; ++i)
        mVertices[i] = transform * mVertices[i];
    updatePlanes();
}

void Frustum::updatePlanes()
{
    mPlanes[PLANE_NEAR].define(mVertices[2], mVertices[1], mVertices[0]);
    mPlanes[PLANE_LEFT].define(mVertices[3], mVertices[7], mVertices[6]);
    mPlanes[PLANE_RIGHT].define(mVertices[1], mVertices[5], mVertices[4]);
    mPlanes[PLANE_UP].define(mVertices[0], mVertices[4], mVertices[7]);
    mPlanes[PLANE_DOWN].define(mVertices[6], mVertices[5], mVertices[1]);
    mPlanes[PLANE_FAR].define(mVertices[5], mVertices[6], mVertices[7]);
    mDefined = true;
}

Frustum Frustum::getTransformed(const Matrix3& transform) const
{
    Frustum transformed;
    
    for (unsigned i = 0; i < NUM_FRUSTUM_VERTICES; ++i)
        transformed.mVertices[i] = transform * mVertices[i];
    transformed.updatePlanes();
    
    return transformed;
}

Frustum Frustum::getTransformed(const Matrix4x3& transform) const
{
    Frustum transformed;
    
    for (unsigned i = 0; i < NUM_FRUSTUM_VERTICES; ++i)
        transformed.mVertices[i] = transform * mVertices[i];
    transformed.updatePlanes();
    
    return transformed;
}

Rect Frustum::getProjected(const Matrix4& projection) const
{
    Rect rect;
    
    projectAndMergeEdge(mVertices[0], mVertices[4], rect, projection);
    projectAndMergeEdge(mVertices[1], mVertices[5], rect, projection);
    projectAndMergeEdge(mVertices[2], mVertices[6], rect, projection);
    projectAndMergeEdge(mVertices[3], mVertices[7], rect, projection);
    projectAndMergeEdge(mVertices[4], mVertices[5], rect, projection);
    projectAndMergeEdge(mVertices[5], mVertices[6], rect, projection);
    projectAndMergeEdge(mVertices[6], mVertices[7], rect, projection);
    projectAndMergeEdge(mVertices[7], mVertices[4], rect, projection);
    
    return rect;
}
