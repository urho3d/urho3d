#pragma once

#include "../Math/Vector3.h"
#include "../Math/Vector4.h"
#include "../Math/Matrix4.h"


namespace Urho3D
{

class Color;
class DebugRenderer;


class GravityTriangle
{
public:
    GravityTriangle() { assert(false); } // Required for Vector<GravityTriangle>

    /*!
     * @brief Constructs a triangle from 4 vertex locations in cartesian
     * space.
     */
    GravityTriangle(const Vector3 vertices[3],
                    const Vector3 directions[3],
                    const float forceFactors[3]);
    /*!
     * @brief Returns true if the specified barycentric coordinate lies inside
     * the triangle.
     */
    bool PointLiesInside(const Vector3& bary) const
    {
        return (
            bary.x_ >= 0.0f &&
            bary.y_ >= 0.0f &&
            bary.z_ >= 0.0f
        );
    }

    Vector3 Intersect(const Vector3& origin, const Vector3& direction) const
    {
#define NO_INTERSECTION Vector3(-1, -1, -1)
#define DO_CULL 0

        // Algorithm taken from:
        // "Fast, Minimum Storage Ray/Triangle Intersection"
        // See doc/research/
        Vector3 edge1 = vertices_[1] - vertices_[0];
        Vector3 edge2 = vertices_[2] - vertices_[0];

        Vector3 p = direction.CrossProduct(edge2);
        float determinant = p.DotProduct(edge1);
#if DO_CULL
        if(determinant == 0.0f)
            return NO_INTERSECTION;
#endif

        Vector3 ray = origin - vertices_[0];
        float u = p.DotProduct(ray);
#if DO_CULL
        if(u < 0.0f || u > determinant)
            return NO_INTERSECTION;
#endif

        Vector3 q = ray.CrossProduct(edge1);
        float v = q.DotProduct(direction);
#if DO_CULL
        if(v < 0.0f || v > determinant)
            return NO_INTERSECTION;
#endif

        determinant = 1.0f / determinant;
        u *= determinant;
        v *= determinant;

        return Vector3(1.0f - u - v, u, v);
    }

    Vector3 Interpolate(const Vector3& barycentric) const
    {
        return (
            directions_[0] * barycentric.x_ +
            directions_[1] * barycentric.y_ +
            directions_[2] * barycentric.z_
        ).Normalized() * (
            forceFactors_[0] * barycentric.x_ +
            forceFactors_[1] * barycentric.y_ +
            forceFactors_[2] * barycentric.z_
        );
    }

    Vector3 TransformToCartesian(const Vector3& barycentric) const
    {
        return barycentric.x_ * vertices_[0] +
               barycentric.y_ * vertices_[1] +
               barycentric.z_ * vertices_[2];
    }

    void DrawDebugGeometry(DebugRenderer* debug, bool depthTest, const Color& color) const;

private:
    Vector3 vertices_[3];
    Vector3 directions_[3];
    float forceFactors_[3];
};

} // namespace Urho3D
