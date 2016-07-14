#pragma once

#include "../Math/Vector3.h"
#include "../Math/Vector4.h"
#include "../Math/Matrix4.h"
#include "../IceWeaselMods/GravityPoint.h"


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
    GravityTriangle(const GravityPoint& p0,
                    const GravityPoint& p1,
                    const GravityPoint& p2);

    const GravityPoint& GetVertex(unsigned char vertexID)
    {
        assert(vertexID < 3);
        return vertex_[vertexID];
    }

    const Vector3& GetNormal() const
            { return normal_; }

    void FlipNormal()
            { normal_ *= -1; }

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
        Vector3 edge1 = vertex_[1].position_ - vertex_[0].position_;
        Vector3 edge2 = vertex_[2].position_ - vertex_[0].position_;

        Vector3 p = direction.CrossProduct(edge2);
        float determinant = p.DotProduct(edge1);
#if DO_CULL
        if(determinant == 0.0f)
            return NO_INTERSECTION;
#endif

        Vector3 ray = origin - vertex_[0].position_;
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

    /*!
     * @brief Transforms the specified point from a cartesian coordinate system
     * into the tetrahedron's barycentric coordinate system.
     *
     * This is useful for checking if point lies inside the tetrahedron, or for
     * interpolating values.
     */
    Vector3 ProjectAndTransformToBarycentric(const Vector3& cartesian) const
    {
        Vector4 result = transform_ * Vector4(cartesian, 1.0f);
        return Vector3(result.x_, result.y_, result.z_);
    }

    Vector3 TransformToCartesian(const Vector3& barycentric) const
    {
        return barycentric.x_ * vertex_[0].position_ +
               barycentric.y_ * vertex_[1].position_ +
               barycentric.z_ * vertex_[2].position_;
    }

    Vector3 InterpolateGravity(const Vector3& barycentric) const
    {
        return (
            vertex_[0].direction_ * barycentric.x_ +
            vertex_[1].direction_ * barycentric.y_ +
            vertex_[2].direction_ * barycentric.z_
        ).Normalized() * (
            vertex_[0].forceFactor_ * barycentric.x_ +
            vertex_[1].forceFactor_ * barycentric.y_ +
            vertex_[2].forceFactor_ * barycentric.z_
        );
    }

    void DrawDebugGeometry(DebugRenderer* debug, bool depthTest, const Color& color) const;

private:
    Matrix4 CalculateSurfaceProjectionMatrix() const;
    Matrix4 CalculateBarycentricTransformationMatrix() const;

    GravityPoint vertex_[3];
    Vector3 normal_;

    Matrix4 transform_;
};

} // namespace Urho3D
