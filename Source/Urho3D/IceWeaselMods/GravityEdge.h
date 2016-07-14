#pragma once

#include "../Math/Vector3.h"
#include "../Math/Vector4.h"
#include "../Math/Matrix4.h"
#include "../IceWeaselMods/GravityPoint.h"


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
    GravityEdge(const GravityPoint& p0,
                const GravityPoint& p1,
                const Vector3& boundaryNormal0,
                const Vector3& boundaryNormal1);

    void FlipBoundaryCheck()
    {
        Vector3 tmp = boundaryNormal_[0];
        boundaryNormal_[0] = boundaryNormal_[1];
        boundaryNormal_[1] = tmp;
    }

    /*!
     * @brief Returns true if the specified barycentric coordinate lies inside
     * the triangle.
     */
    bool PointLiesInside(Vector2 bary) const
    {
        return (
            bary.x_ >= 0.0f &&
            bary.y_ >= 0.0f
        );
    }

    bool ProjectionAngleIsInBounds(const Vector3& cartesianTransform, const Vector3& position) const
    {
        Vector3 check = cartesianTransform - position;
        Vector3 cross = boundaryNormal_[0].CrossProduct(check);
        if(cross.DotProduct(check.CrossProduct(boundaryNormal_[1])) > 0 && (vertex_[1].position_ - vertex_[0].position_).DotProduct(cross) > 0)
            return true;
        return false;
    }

    /*!
     * @brief Transforms the specified point from a cartesian coordinate system
     * into the tetrahedron's barycentric coordinate system.
     *
     * This is useful for checking if point lies inside the tetrahedron, or for
     * interpolating values.
     */
    Vector2 ProjectAndTransformToBarycentric(const Vector3& cartesian) const
    {
        Vector4 result = transform_ * Vector4(cartesian, 1.0f);
        return Vector2(result.x_, result.y_);
    }

    Vector3 TransformToCartesian(const Vector2& barycentric) const
    {
        return barycentric.x_ * vertex_[0].position_ +
               barycentric.y_ * vertex_[1].position_;
    }

    Vector3 InterpolateGravity(const Vector2& barycentric) const
    {
        return (
            vertex_[0].direction_ * barycentric.x_ +
            vertex_[1].direction_ * barycentric.y_
        ).Normalized() * (
            vertex_[0].forceFactor_ * barycentric.x_ +
            vertex_[1].forceFactor_ * barycentric.y_
        );
    }

    void DrawDebugGeometry(DebugRenderer* debug, bool depthTest, const Color& color) const;

private:
    Matrix4 CalculateEdgeProjectionMatrix() const;
    Matrix4 CalculateBarycentricTransformationMatrix() const;

    GravityPoint vertex_[2];
    Vector3 boundaryNormal_[2];

    Matrix4 transform_;
};

} // namespace Urho3D
