// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

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

Frustum::Frustum(const Frustum& frustum) noexcept
{
    *this = frustum;
}

Frustum& Frustum::operator =(const Frustum& rhs) noexcept
{
    for (i32 i = 0; i < NUM_FRUSTUM_PLANES; ++i)
        planes_[i] = rhs.planes_[i];

    for (i32 i = 0; i < NUM_FRUSTUM_VERTICES; ++i)
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

void Frustum::Define(const Matrix4& projection)
{
    Matrix4 projInverse = projection.Inverse();

    vertices_[0] = projInverse * Vector3(1.0f, 1.0f, 0.0f);
    vertices_[1] = projInverse * Vector3(1.0f, -1.0f, 0.0f);
    vertices_[2] = projInverse * Vector3(-1.0f, -1.0f, 0.0f);
    vertices_[3] = projInverse * Vector3(-1.0f, 1.0f, 0.0f);
    vertices_[4] = projInverse * Vector3(1.0f, 1.0f, 1.0f);
    vertices_[5] = projInverse * Vector3(1.0f, -1.0f, 1.0f);
    vertices_[6] = projInverse * Vector3(-1.0f, -1.0f, 1.0f);
    vertices_[7] = projInverse * Vector3(-1.0f, 1.0f, 1.0f);

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

void Frustum::DefineSplit(const Matrix4& projection, float near, float far)
{
    Matrix4 projInverse = projection.Inverse();

    // Figure out depth values for near & far
    Vector4 nearTemp = projection * Vector4(0.0f, 0.0f, near, 1.0f);
    Vector4 farTemp = projection * Vector4(0.0f, 0.0f, far, 1.0f);
    float nearZ = nearTemp.z_ / nearTemp.w_;
    float farZ = farTemp.z_ / farTemp.w_;

    vertices_[0] = projInverse * Vector3(1.0f, 1.0f, nearZ);
    vertices_[1] = projInverse * Vector3(1.0f, -1.0f, nearZ);
    vertices_[2] = projInverse * Vector3(-1.0f, -1.0f, nearZ);
    vertices_[3] = projInverse * Vector3(-1.0f, 1.0f, nearZ);
    vertices_[4] = projInverse * Vector3(1.0f, 1.0f, farZ);
    vertices_[5] = projInverse * Vector3(1.0f, -1.0f, farZ);
    vertices_[6] = projInverse * Vector3(-1.0f, -1.0f, farZ);
    vertices_[7] = projInverse * Vector3(-1.0f, 1.0f, farZ);

    UpdatePlanes();
}

void Frustum::Transform(const Matrix3& transform)
{
    for (auto& vertice : vertices_)
        vertice = transform * vertice;

    UpdatePlanes();
}

void Frustum::Transform(const Matrix3x4& transform)
{
    for (auto& vertice : vertices_)
        vertice = transform * vertice;

    UpdatePlanes();
}

Frustum Frustum::Transformed(const Matrix3& transform) const
{
    Frustum transformed;

    for (i32 i = 0; i < NUM_FRUSTUM_VERTICES; ++i)
        transformed.vertices_[i] = transform * vertices_[i];

    transformed.UpdatePlanes();
    return transformed;
}

Frustum Frustum::Transformed(const Matrix3x4& transform) const
{
    Frustum transformed;

    for (i32 i = 0; i < NUM_FRUSTUM_VERTICES; ++i)
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
        for (auto& plane : planes_)
        {
            plane.normal_ = -plane.normal_;
            plane.d_ = -plane.d_;
        }
    }

}

}
