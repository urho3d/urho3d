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
#include "../Math/Polyhedron.h"

#include "../DebugNew.h"

namespace Urho3D
{

void BoundingBox::Define(const Vector3* vertices, unsigned count)
{
    Clear();

    if (!count)
        return;

    Merge(vertices, count);
}

void BoundingBox::Define(const Frustum& frustum)
{
    Clear();
    Define(frustum.vertices_, NUM_FRUSTUM_VERTICES);
}

void BoundingBox::Define(const Polyhedron& poly)
{
    Clear();
    Merge(poly);
}

void BoundingBox::Define(const Sphere& sphere)
{
    const Vector3& center = sphere.center_;
    float radius = sphere.radius_;

    min_ = center + Vector3(-radius, -radius, -radius);
    max_ = center + Vector3(radius, radius, radius);
}

void BoundingBox::Merge(const Vector3* vertices, unsigned count)
{
    while (count--)
        Merge(*vertices++);
}

void BoundingBox::Merge(const Frustum& frustum)
{
    Merge(frustum.vertices_, NUM_FRUSTUM_VERTICES);
}

void BoundingBox::Merge(const Polyhedron& poly)
{
    for (unsigned i = 0; i < poly.faces_.Size(); ++i)
    {
        const PODVector<Vector3>& face = poly.faces_[i];
        if (!face.Empty())
            Merge(&face[0], face.Size());
    }
}

void BoundingBox::Merge(const Sphere& sphere)
{
    const Vector3& center = sphere.center_;
    float radius = sphere.radius_;

    Merge(center + Vector3(radius, radius, radius));
    Merge(center + Vector3(-radius, -radius, -radius));
}

void BoundingBox::Clip(const BoundingBox& box)
{
    if (box.min_.x_ > min_.x_)
        min_.x_ = box.min_.x_;
    if (box.max_.x_ < max_.x_)
        max_.x_ = box.max_.x_;
    if (box.min_.y_ > min_.y_)
        min_.y_ = box.min_.y_;
    if (box.max_.y_ < max_.y_)
        max_.y_ = box.max_.y_;
    if (box.min_.z_ > min_.z_)
        min_.z_ = box.min_.z_;
    if (box.max_.z_ < max_.z_)
        max_.z_ = box.max_.z_;

    if (min_.x_ > max_.x_ || min_.y_ > max_.y_ || min_.z_ > max_.z_)
    {
        min_ = Vector3(M_INFINITY, M_INFINITY, M_INFINITY);
        max_ = Vector3(-M_INFINITY, -M_INFINITY, -M_INFINITY);
    }
}

void BoundingBox::Transform(const Matrix3& transform)
{
    *this = Transformed(Matrix3x4(transform));
}

void BoundingBox::Transform(const Matrix3x4& transform)
{
    *this = Transformed(transform);
}

BoundingBox BoundingBox::Transformed(const Matrix3& transform) const
{
    return Transformed(Matrix3x4(transform));
}

BoundingBox BoundingBox::Transformed(const Matrix3x4& transform) const
{
#ifdef URHO3D_SSE
    const __m128 one = _mm_set_ss(1.f);
    __m128 minPt = _mm_movelh_ps(_mm_loadl_pi(_mm_setzero_ps(), (const __m64*)&min_.x_), _mm_unpacklo_ps(_mm_set_ss(min_.z_), one));
    __m128 maxPt = _mm_movelh_ps(_mm_loadl_pi(_mm_setzero_ps(), (const __m64*)&max_.x_), _mm_unpacklo_ps(_mm_set_ss(max_.z_), one));
    __m128 centerPoint = _mm_mul_ps(_mm_add_ps(minPt, maxPt), _mm_set1_ps(0.5f));
    __m128 halfSize = _mm_sub_ps(centerPoint, minPt);
    __m128 m0 = _mm_loadu_ps(&transform.m00_);
    __m128 m1 = _mm_loadu_ps(&transform.m10_);
    __m128 m2 = _mm_loadu_ps(&transform.m20_);
    __m128 r0 = _mm_mul_ps(m0, centerPoint);
    __m128 r1 = _mm_mul_ps(m1, centerPoint);
    __m128 t0 = _mm_add_ps(_mm_unpacklo_ps(r0, r1), _mm_unpackhi_ps(r0, r1));
    __m128 r2 = _mm_mul_ps(m2, centerPoint);
    const __m128 zero = _mm_setzero_ps();
    __m128 t2 = _mm_add_ps(_mm_unpacklo_ps(r2, zero), _mm_unpackhi_ps(r2, zero));
    __m128 newCenter = _mm_add_ps(_mm_movelh_ps(t0, t2), _mm_movehl_ps(t2, t0));
    const __m128 absMask = _mm_castsi128_ps(_mm_set1_epi32(0x7FFFFFFF));
    __m128 x = _mm_and_ps(absMask, _mm_mul_ps(m0, halfSize));
    __m128 y = _mm_and_ps(absMask, _mm_mul_ps(m1, halfSize));
    __m128 z = _mm_and_ps(absMask, _mm_mul_ps(m2, halfSize));
    t0 = _mm_add_ps(_mm_unpacklo_ps(x, y), _mm_unpackhi_ps(x, y));
    t2 = _mm_add_ps(_mm_unpacklo_ps(z, zero), _mm_unpackhi_ps(z, zero));
    __m128 newDir = _mm_add_ps(_mm_movelh_ps(t0, t2), _mm_movehl_ps(t2, t0));
    return BoundingBox(_mm_sub_ps(newCenter, newDir), _mm_add_ps(newCenter, newDir));
#else
    Vector3 newCenter = transform * Center();
    Vector3 oldEdge = Size() * 0.5f;
    Vector3 newEdge = Vector3(
        Abs(transform.m00_) * oldEdge.x_ + Abs(transform.m01_) * oldEdge.y_ + Abs(transform.m02_) * oldEdge.z_,
        Abs(transform.m10_) * oldEdge.x_ + Abs(transform.m11_) * oldEdge.y_ + Abs(transform.m12_) * oldEdge.z_,
        Abs(transform.m20_) * oldEdge.x_ + Abs(transform.m21_) * oldEdge.y_ + Abs(transform.m22_) * oldEdge.z_
    );

    return BoundingBox(newCenter - newEdge, newCenter + newEdge);
#endif
}

Rect BoundingBox::Projected(const Matrix4& projection) const
{
    Vector3 projMin = min_;
    Vector3 projMax = max_;
    if (projMin.z_ < M_MIN_NEARCLIP)
        projMin.z_ = M_MIN_NEARCLIP;
    if (projMax.z_ < M_MIN_NEARCLIP)
        projMax.z_ = M_MIN_NEARCLIP;

    Vector3 vertices[8];
    vertices[0] = projMin;
    vertices[1] = Vector3(projMax.x_, projMin.y_, projMin.z_);
    vertices[2] = Vector3(projMin.x_, projMax.y_, projMin.z_);
    vertices[3] = Vector3(projMax.x_, projMax.y_, projMin.z_);
    vertices[4] = Vector3(projMin.x_, projMin.y_, projMax.z_);
    vertices[5] = Vector3(projMax.x_, projMin.y_, projMax.z_);
    vertices[6] = Vector3(projMin.x_, projMax.y_, projMax.z_);
    vertices[7] = projMax;

    Rect rect;
    for (unsigned i = 0; i < 8; ++i)
    {
        Vector3 projected = projection * vertices[i];
        rect.Merge(Vector2(projected.x_, projected.y_));
    }

    return rect;
}

Intersection BoundingBox::IsInside(const Sphere& sphere) const
{
    float distSquared = 0;
    float temp;
    const Vector3& center = sphere.center_;

    if (center.x_ < min_.x_)
    {
        temp = center.x_ - min_.x_;
        distSquared += temp * temp;
    }
    else if (center.x_ > max_.x_)
    {
        temp = center.x_ - max_.x_;
        distSquared += temp * temp;
    }
    if (center.y_ < min_.y_)
    {
        temp = center.y_ - min_.y_;
        distSquared += temp * temp;
    }
    else if (center.y_ > max_.y_)
    {
        temp = center.y_ - max_.y_;
        distSquared += temp * temp;
    }
    if (center.z_ < min_.z_)
    {
        temp = center.z_ - min_.z_;
        distSquared += temp * temp;
    }
    else if (center.z_ > max_.z_)
    {
        temp = center.z_ - max_.z_;
        distSquared += temp * temp;
    }

    float radius = sphere.radius_;
    if (distSquared >= radius * radius)
        return OUTSIDE;
    else if (center.x_ - radius < min_.x_ || center.x_ + radius > max_.x_ || center.y_ - radius < min_.y_ ||
             center.y_ + radius > max_.y_ || center.z_ - radius < min_.z_ || center.z_ + radius > max_.z_)
        return INTERSECTS;
    else
        return INSIDE;
}

Intersection BoundingBox::IsInsideFast(const Sphere& sphere) const
{
    float distSquared = 0;
    float temp;
    const Vector3& center = sphere.center_;

    if (center.x_ < min_.x_)
    {
        temp = center.x_ - min_.x_;
        distSquared += temp * temp;
    }
    else if (center.x_ > max_.x_)
    {
        temp = center.x_ - max_.x_;
        distSquared += temp * temp;
    }
    if (center.y_ < min_.y_)
    {
        temp = center.y_ - min_.y_;
        distSquared += temp * temp;
    }
    else if (center.y_ > max_.y_)
    {
        temp = center.y_ - max_.y_;
        distSquared += temp * temp;
    }
    if (center.z_ < min_.z_)
    {
        temp = center.z_ - min_.z_;
        distSquared += temp * temp;
    }
    else if (center.z_ > max_.z_)
    {
        temp = center.z_ - max_.z_;
        distSquared += temp * temp;
    }

    float radius = sphere.radius_;
    if (distSquared >= radius * radius)
        return OUTSIDE;
    else
        return INSIDE;
}

String BoundingBox::ToString() const
{
    return min_.ToString() + " - " + max_.ToString();
}

}
