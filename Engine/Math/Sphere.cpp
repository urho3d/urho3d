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

void Sphere::Define(const std::vector<Vector3>& vertices)
{
    defined_ = false;
    for (std::vector<Vector3>::const_iterator i = vertices.begin(); i != vertices.end(); ++i)
        Merge(*i);
}

void Sphere::Define(const Vector3* vertices, unsigned count)
{
    if (!count)
        return;
    
    defined_ = false;
    Merge(vertices, count);
}

void Sphere::Define(const BoundingBox& box)
{
    const Vector3& min = box.min_;
    const Vector3& max = box.max_;
    
    defined_ = false;
    Merge(min);
    Merge(Vector3(max.x_, min.y_, min.z_));
    Merge(Vector3(min.x_, max.y_, min.z_));
    Merge(Vector3(max.x_, max.y_, min.z_));
    Merge(Vector3(min.x_, min.y_, max.z_));
    Merge(Vector3(max.x_, min.y_, max.z_));
    Merge(Vector3(min.x_, max.y_, max.z_));
    Merge(max);
}

void Sphere::Define(const Frustum& frustum)
{
    Define(frustum.GetVertices(), NUM_FRUSTUM_VERTICES);
}

void Sphere::Merge(const std::vector<Vector3>& vertices)
{
    for (std::vector<Vector3>::const_iterator i = vertices.begin(); i != vertices.end(); ++i)
        Merge(*i);
}

void Sphere::Merge(const Vector3* vertices, unsigned count)
{
    while (count--)
    {
        Merge(*vertices);
        ++vertices;
    }
}

void Sphere::Merge(const BoundingBox& box)
{
    const Vector3& min = box.min_;
    const Vector3& max = box.max_;
    
    Merge(min);
    Merge(Vector3(max.x_, min.y_, min.z_));
    Merge(Vector3(min.x_, max.y_, min.z_));
    Merge(Vector3(max.x_, max.y_, min.z_));
    Merge(Vector3(min.x_, min.y_, max.z_));
    Merge(Vector3(max.x_, min.y_, max.z_));
    Merge(Vector3(min.x_, max.y_, max.z_));
    Merge(max);
}

void Sphere::Merge(const Frustum& frustum)
{
    const Vector3* vertices = frustum.GetVertices();
    Merge(vertices, NUM_FRUSTUM_VERTICES);
}

void Sphere::Merge(const Sphere& sphere)
{
    if (!defined_)
    {
        center_ = sphere.center_;
        radius_ = sphere.radius_;
        defined_ = true;
        return;
    }
    
    Vector3 offset = sphere.center_ - center_;
    float dist = offset.GetLength();
    
    // If sphere fits inside, do nothing
    if (dist + sphere.radius_ < radius_)
        return;
    
    // If we fit inside the other sphere, become it
    if (dist + radius_ < sphere.radius_)
    {
        center_ = sphere.center_;
        radius_ = sphere.radius_;
    }
    else
    {
        Vector3 NormalizedOffset = offset / dist;
        
        Vector3 min = center_ - radius_ * NormalizedOffset;
        Vector3 max = sphere.center_ + sphere.radius_ * NormalizedOffset;
        center_ = (min + max) * 0.5f;
        radius_ = (max - center_).GetLength();
    }
}

Intersection Sphere::IsInside(const BoundingBox& box) const
{
    float radiusSquared = radius_ * radius_;
    float distSquared = 0;
    float temp;
    
    Vector3 min = box.min_;
    Vector3 max = box.max_;
    
    if (center_.x_ < min.x_)
    {
        temp = center_.x_ - min.x_;
        distSquared += temp * temp;
    }
    else if (center_.x_ > max.x_)
    {
        temp = center_.x_ - max.x_;
        distSquared += temp * temp;
    }
    if (center_.y_ < min.y_)
    {
        temp = center_.y_ - min.y_;
        distSquared += temp * temp;
    }
    else if (center_.y_ > max.y_)
    {
        temp = center_.y_ - max.y_;
        distSquared += temp * temp;
    }
    if (center_.z_ < min.z_)
    {
        temp = center_.z_ - min.z_;
        distSquared += temp * temp;
    }
    else if (center_.z_ > max.z_)
    {
        temp = center_.z_ - max.z_;
        distSquared += temp * temp;
    }
    
    if (distSquared >= radiusSquared)
        return OUTSIDE;
    
    min -= center_;
    max -= center_;
    
    Vector3 tempVec = min; // - - -
    if (tempVec.GetLengthSquared() >= radiusSquared)
        return INTERSECTS;
    tempVec.x_ = max.x_; // + - -
    if (tempVec.GetLengthSquared() >= radiusSquared)
        return INTERSECTS;
    tempVec.y_ = max.y_; // + + -
    if (tempVec.GetLengthSquared() >= radiusSquared)
        return INTERSECTS;
    tempVec.x_ = min.x_; // - + -
    if (tempVec.GetLengthSquared() >= radiusSquared)
        return INTERSECTS;
    tempVec.z_ = max.z_; // - + +
    if (tempVec.GetLengthSquared() >= radiusSquared)
        return INTERSECTS;
    tempVec.y_ = min.y_; // - - +
    if (tempVec.GetLengthSquared() >= radiusSquared)
        return INTERSECTS;
    tempVec.x_ = max.x_; // + - +
    if (tempVec.GetLengthSquared() >= radiusSquared)
        return INTERSECTS;
    tempVec.y_ = max.y_; // + + +
    if (tempVec.GetLengthSquared() >= radiusSquared)
        return INTERSECTS;
    
    return INSIDE;
}

Intersection Sphere::IsInsideFast(const BoundingBox& box) const
{
    float radiusSquared = radius_ * radius_;
    float distSquared = 0;
    float temp;
    
    Vector3 min = box.min_;
    Vector3 max = box.max_;
    
    if (center_.x_ < min.x_)
    {
        temp = center_.x_ - min.x_;
        distSquared += temp * temp;
    }
    else if (center_.x_ > max.x_)
    {
        temp = center_.x_ - max.x_;
        distSquared += temp * temp;
    }
    if (center_.y_ < min.y_)
    {
        temp = center_.y_ - min.y_;
        distSquared += temp * temp;
    }
    else if (center_.y_ > max.y_)
    {
        temp = center_.y_ - max.y_;
        distSquared += temp * temp;
    }
    if (center_.z_ < min.z_)
    {
        temp = center_.z_ - min.z_;
        distSquared += temp * temp;
    }
    else if (center_.z_ > max.z_)
    {
        temp = center_.z_ - max.z_;
        distSquared += temp * temp;
    }
    
    if (distSquared >= radiusSquared)
        return OUTSIDE;
    else
        return INSIDE;
}

float Sphere::GetDistance(const Ray& ray) const
{
    Vector3 centeredOrigin = ray.origin_ - center_;
    float squaredRadius = radius_ * radius_;
    
    // Check if ray originates inside the sphere
    if (centeredOrigin.GetLengthSquared() <= squaredRadius)
        return 0.0f;
    
    // Calculate intersection by quadratic equation
    float a = ray.direction_.DotProduct(ray.direction_);
    float b = 2.0f * centeredOrigin.DotProduct(ray.direction_);
    float c = centeredOrigin.DotProduct(centeredOrigin) - squaredRadius;
    
    float d = b * b - 4.0f * a * c;

    // No solution
    if (d < 0.0f)
        return M_INFINITY;
    
    // Get the nearer solution
    float dSqrt = sqrtf(d);
    float dist = (-b - dSqrt) / (2.0f * a);
    if (dist >= 0.0f)
        return dist;
    else
        return (-b + dSqrt) / (2.0f * a);
}
