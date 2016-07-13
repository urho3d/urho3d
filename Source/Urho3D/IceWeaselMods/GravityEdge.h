#pragma once

#include "../Math/Vector3.h"
#include "../Math/Vector4.h"
#include "../Math/Matrix4.h"


namespace Urho3D
{

class Color;
class DebugRenderer;


class GravityEdge
{
public:
    GravityEdge() { assert(false); } // Required for Vector<GravityEdge>

    /*!
     * @brief Constructs a triangle from 4 vertex locations in cartesian
     * space.
     */
    GravityEdge(const Vector3 vertices[2],
                const Vector3 directions[2],
                const float forceFactors[2]);
    /*!
     * @brief Returns true if the specified barycentric coordinate lies inside
     * the triangle.
     */
    bool PointLiesInside(const Vector2& bary) const
    {
        return (
            bary.x_ >= 0.0f &&
            bary.y_ >= 0.0f
        );
    }

    /*!
     * @brief Transforms the specified point from a cartesian coordinate system
     * into the tetrahedron's barycentric coordinate system.
     *
     * This is useful for checking if point lies inside the tetrahedron, or for
     * interpolating values.
     */
    Vector4 TransformToBarycentric(const Vector3& cartesian) const
    {
        return transform_ * Vector4(cartesian, 1.0f);
    }

    Vector3 TransformToCartesian(const Vector2& barycentric) const
    {
        return barycentric.x_ * vertices_[0] +
               barycentric.y_ * vertices_[1];
    }

    Vector3 Interpolate(const Vector2& barycentric) const
    {
        return (
            directions_[0] * barycentric.x_ +
            directions_[1] * barycentric.y_
        ).Normalized() * (
            forceFactors_[0] * barycentric.x_ +
            forceFactors_[1] * barycentric.y_
        );
    }

    void DrawDebugGeometry(DebugRenderer* debug, bool depthTest, const Color& color) const;

private:
    Matrix4 CalculateEdgeProjectionMatrix() const;
    Matrix4 CalculateBarycentricTransformationMatrix() const;

    Vector3 vertices_[2];
    Vector3 directions_[2];
    float forceFactors_[2];

    Matrix4 transform_;
};

} // namespace Urho3D
