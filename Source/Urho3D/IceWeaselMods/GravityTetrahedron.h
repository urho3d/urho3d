#pragma once

#include "../Math/Vector3.h"
#include "../Math/Vector4.h"
#include "../Math/Matrix4.h"


namespace Urho3D
{

class Color;
class DebugRenderer;


class GravityTetrahedron
{
public:

    GravityTetrahedron() { assert(false); } // Required for Vector<GravityTetrahedron>

    /*!
     * @brief Constructs a tetrahedron from 4 vertex locations in cartesian
     * space.
     */
    GravityTetrahedron(const Vector3 vertices[4],
                       const Vector3 directions[4],
                       const float forceFactors[4]);

    /*!
     * @brief Returns true if the specified barycentric coordinate lies inside
     * the tetrahedron.
     */
    bool PointLiesInside(const Vector4& bary) const
    {
        return (
            bary.x_ >= 0.0f &&
            bary.y_ >= 0.0f &&
            bary.z_ >= 0.0f &&
            bary.w_ >= 0.0f
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

    Vector3 TransformToCartesian(const Vector4& barycentric) const
    {
        return barycentric.x_ * vertices_[0] +
               barycentric.y_ * vertices_[1] +
               barycentric.z_ * vertices_[2] +
               barycentric.w_ * vertices_[3];
    }

    Vector3 GetVertexPosition(unsigned char vertexID) const
    {
        assert(vertexID < 4);
        return vertices_[vertexID];
    }

    Vector3 Interpolate(const Vector4& barycentric) const
    {
        return (
            directions_[0] * barycentric.x_ +
            directions_[1] * barycentric.y_ +
            directions_[2] * barycentric.z_ +
            directions_[3] * barycentric.w_
        ).Normalized() * (
            forceFactors_[0] * barycentric.x_ +
            forceFactors_[1] * barycentric.y_ +
            forceFactors_[2] * barycentric.z_ +
            forceFactors_[3] * barycentric.w_
        );
    }

    void DrawDebugGeometry(DebugRenderer* debug, bool depthTest, const Color& color);

private:
    Matrix4 CalculateBarycentricTransformationMatrix() const;

    Vector3 vertices_[4];
    Vector3 directions_[4];
    float forceFactors_[4];

    Matrix4 transform_;
};

} // namespace Urho3D
