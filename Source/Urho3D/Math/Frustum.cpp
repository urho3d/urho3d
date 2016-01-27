//
// Copyright (c) 2008-2016 the Urho3D project.
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

#include "../Precompiled.h"

#include "../Math/Frustum.h"

#include "../DebugNew.h"

namespace Urho3D
{

inline Vector3 ClipEdgeZ(const Vector3& v0, const Vector3& v1, float clipZ)
{
    return Vector3(
        v1.x_ + (v0.x_ - v1.x_) * ((clipZ - v1.z_) / (v0.z_ - v1.z_)),
        v1.y_ + (v0.y_ - v1.y_) * ((clipZ - v1.z_) / (v0.z_ - v1.z_)),
        clipZ
    );
}

void ProjectAndMergeEdge(Vector3 v0, Vector3 v1, Rect& rect, const Matrix4& projection)
{
    // Check if both vertices behind near plane
    if (v0.z_ < M_MIN_NEARCLIP && v1.z_ < M_MIN_NEARCLIP)
        return;

    // Check if need to clip one of the vertices
    if (v1.z_ < M_MIN_NEARCLIP)
        v1 = ClipEdgeZ(v1, v0, M_MIN_NEARCLIP);
    else if (v0.z_ < M_MIN_NEARCLIP)
        v0 = ClipEdgeZ(v0, v1, M_MIN_NEARCLIP);

    // Project, perspective divide and merge
    Vector3 tV0(projection * v0);
    Vector3 tV1(projection * v1);
    rect.Merge(Vector2(tV0.x_, tV0.y_));
    rect.Merge(Vector2(tV1.x_, tV1.y_));
}

Frustum::Frustum()
{
    UpdatePlanes();
}

Frustum::Frustum(const Frustum& frustum)
{
    *this = frustum;
}

Frustum& Frustum::operator =(const Frustum& rhs)
{
    for (unsigned i = 0; i < NUM_FRUSTUM_PLANES; ++i)
        planes_[i] = rhs.planes_[i];
    for (unsigned i = 0; i < NUM_FRUSTUM_VERTICES; ++i)
        vertices_[i] = rhs.vertices_[i];

    return *this;
}

void Frustum::Define(float fov, float aspectRatio, float zoom, float nearZ, float farZ, const Matrix3x4& transform)
{
    nearZ = Max(nearZ, 0.0f);
    farZ = Max(farZ, nearZ);
    float halfViewSize = tanf(fov * M_DEGTORAD_2) / zoom;
    Vector3 near, far;

    near.z_ = nearZ;
    near.y_ = near.z_ * halfViewSize;
    near.x_ = near.y_ * aspectRatio;
    far.z_ = farZ;
    far.y_ = far.z_ * halfViewSize;
    far.x_ = far.y_ * aspectRatio;

    Define(near, far, transform);
}

void Frustum::Define(const Vector3& near, const Vector3& far, const Matrix3x4& transform)
{
    vertices_[0] = transform * near;
    vertices_[1] = transform * Vector3(near.x_, -near.y_, near.z_);
    vertices_[2] = transform * Vector3(-near.x_, -near.y_, near.z_);
    vertices_[3] = transform * Vector3(-near.x_, near.y_, near.z_);
    vertices_[4] = transform * far;
    vertices_[5] = transform * Vector3(far.x_, -far.y_, far.z_);
    vertices_[6] = transform * Vector3(-far.x_, -far.y_, far.z_);
    vertices_[7] = transform * Vector3(-far.x_, far.y_, far.z_);

    UpdatePlanes();
}

void Frustum::Define(const BoundingBox& box, const Matrix3x4& transform)
{
    vertices_[0] = transform * Vector3(box.max_.x_, box.max_.y_, box.min_.z_);
    vertices_[1] = transform * Vector3(box.max_.x_, box.min_.y_, box.min_.z_);
    vertices_[2] = transform * Vector3(box.min_.x_, box.min_.y_, box.min_.z_);
    vertices_[3] = transform * Vector3(box.min_.x_, box.max_.y_, box.min_.z_);
    vertices_[4] = transform * Vector3(box.max_.x_, box.max_.y_, box.max_.z_);
    vertices_[5] = transform * Vector3(box.max_.x_, box.min_.y_, box.max_.z_);
    vertices_[6] = transform * Vector3(box.min_.x_, box.min_.y_, box.max_.z_);
    vertices_[7] = transform * Vector3(box.min_.x_, box.max_.y_, box.max_.z_);

    UpdatePlanes();
}

void Frustum::DefineOrtho(float orthoSize, float aspectRatio, float zoom, float nearZ, float farZ, const Matrix3x4& transform)
{
    nearZ = Max(nearZ, 0.0f);
    farZ = Max(farZ, nearZ);
    float halfViewSize = orthoSize * 0.5f / zoom;
    Vector3 near, far;

    near.z_ = nearZ;
    far.z_ = farZ;
    far.y_ = near.y_ = halfViewSize;
    far.x_ = near.x_ = near.y_ * aspectRatio;

    Define(near, far, transform);
}

void Frustum::Transform(const Matrix3& transform)
{
    for (unsigned i = 0; i < NUM_FRUSTUM_VERTICES; ++i)
        vertices_[i] = transform * vertices_[i];

    UpdatePlanes();
}

void Frustum::Transform(const Matrix3x4& transform)
{
    for (unsigned i = 0; i < NUM_FRUSTUM_VERTICES; ++i)
        vertices_[i] = transform * vertices_[i];

    UpdatePlanes();
}

Frustum Frustum::Transformed(const Matrix3& transform) const
{
    Frustum transformed;
    for (unsigned i = 0; i < NUM_FRUSTUM_VERTICES; ++i)
        transformed.vertices_[i] = transform * vertices_[i];

    transformed.UpdatePlanes();
    return transformed;
}

Frustum Frustum::Transformed(const Matrix3x4& transform) const
{
    Frustum transformed;
    for (unsigned i = 0; i < NUM_FRUSTUM_VERTICES; ++i)
        transformed.vertices_[i] = transform * vertices_[i];

    transformed.UpdatePlanes();
    return transformed;
}

Rect Frustum::Projected(const Matrix4& projection) const
{
    Rect rect;

    ProjectAndMergeEdge(vertices_[0], vertices_[4], rect, projection);
    ProjectAndMergeEdge(vertices_[1], vertices_[5], rect, projection);
    ProjectAndMergeEdge(vertices_[2], vertices_[6], rect, projection);
    ProjectAndMergeEdge(vertices_[3], vertices_[7], rect, projection);
    ProjectAndMergeEdge(vertices_[4], vertices_[5], rect, projection);
    ProjectAndMergeEdge(vertices_[5], vertices_[6], rect, projection);
    ProjectAndMergeEdge(vertices_[6], vertices_[7], rect, projection);
    ProjectAndMergeEdge(vertices_[7], vertices_[4], rect, projection);

    return rect;
}

void Frustum::UpdatePlanes()
{
    planes_[PLANE_NEAR].Define(vertices_[2], vertices_[1], vertices_[0]);
    planes_[PLANE_LEFT].Define(vertices_[3], vertices_[7], vertices_[6]);
    planes_[PLANE_RIGHT].Define(vertices_[1], vertices_[5], vertices_[4]);
    planes_[PLANE_UP].Define(vertices_[0], vertices_[4], vertices_[7]);
    planes_[PLANE_DOWN].Define(vertices_[6], vertices_[5], vertices_[1]);
    planes_[PLANE_FAR].Define(vertices_[5], vertices_[6], vertices_[7]);

    // Check if we ended up with inverted planes (reflected transform) and flip in that case
    if (planes_[PLANE_NEAR].Distance(vertices_[5]) < 0.0f)
    {
        for (unsigned i = 0; i < NUM_FRUSTUM_PLANES; ++i)
        {
            planes_[i].normal_ = -planes_[i].normal_;
            planes_[i].d_ = -planes_[i].d_;
        }
    }

}

}
