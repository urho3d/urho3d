#pragma once

#include "../Math/Vector3.h"
#include "../Math/Vector4.h"
#include "../Math/Matrix4.h"
#include "../IceWeaselMods/GravityPoint.h"


namespace Urho3D
{

class Color;
class DebugRenderer;
class GravityPoint;


class GravityTetrahedron
{
public:

    GravityTetrahedron() { assert(false); } // Required for Vector<GravityTetrahedron>

    /*!
     * @brief Constructs a tetrahedron from 4 vertex locations in cartesian
     * space.
     */
    GravityTetrahedron(const GravityPoint& p0,
                       const GravityPoint& p1,
                       const GravityPoint& p2,
                       const GravityPoint& p3);

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
        return barycentric.x_ * vertex_[0].position_ +
               barycentric.y_ * vertex_[1].position_ +
               barycentric.z_ * vertex_[2].position_ +
               barycentric.w_ * vertex_[3].position_;
    }

    Vector3 GetVertexPosition(unsigned char vertexID) const
    {
        assert(vertexID < 4);
        return vertex_[vertexID].position_;
    }

    Vector3 InterpolateGravity(const Vector4& barycentric) const
    {
        return (
            vertex_[0].position_ * barycentric.x_ +
            vertex_[1].position_ * barycentric.y_ +
            vertex_[2].position_ * barycentric.z_ +
            vertex_[3].position_ * barycentric.w_
        ).Normalized() * (
            vertex_[0].forceFactor_ * barycentric.x_ +
            vertex_[1].forceFactor_ * barycentric.y_ +
            vertex_[2].forceFactor_ * barycentric.z_ +
            vertex_[3].forceFactor_ * barycentric.w_
        );
    }

    void DrawDebugGeometry(DebugRenderer* debug, bool depthTest, const Color& color);

private:
    Matrix4 CalculateBarycentricTransformationMatrix() const;

    GravityPoint vertex_[4];

    Matrix4 transform_;
};

} // namespace Urho3D
