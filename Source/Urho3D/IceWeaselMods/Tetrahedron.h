#pragma once

#include <Urho3D/Math/Vector3.h>
#include <Urho3D/Math/Vector4.h>
#include <Urho3D/Math/Matrix4.h>


namespace Urho3D
{

class DebugRenderer;
class Color;


class Tetrahedron
{
public:

    Tetrahedron() { assert(false); } // Required for Vector<Tetrahedron>

    /*!
     * @brief Constructs a tetrahedron from 4 vertex locations in cartesian
     * space.
     */
    Tetrahedron(const Vector3& v0,
                const Vector3& v1,
                const Vector3& v2,
                const Vector3& v3);

    void SetValues(const Vector3& value0,
                   const Vector3& value1,
                   const Vector3& value2,
                   const Vector3& value3);

    /*!
     * @brief Returns true if the specified 3D point lies inside the
     * tetrahedron.
     */
    bool PointLiesInside(const Vector3& point) const
    {
        return PointLiesInside(TransformToBarycentric(point));
    }

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
    Vector4 TransformToBarycentric(const Vector3& point) const
    {
        return transform_ * Vector4(point, 1.0f);
    }

    Vector3 TransformToCartesian(const Vector4& barycentric) const
    {
        return barycentric.x_ * vertices_[0] +
               barycentric.y_ * vertices_[1] +
               barycentric.z_ * vertices_[2] +
               barycentric.w_ * vertices_[3];
    }

    Vector3 interpolate(const Vector3& point) const
    {
        return interpolate(TransformToBarycentric(point));
    }

    Vector3 interpolate(const Vector4& barycentric) const
    {
        return barycentric.x_ * value_[0] +
               barycentric.y_ * value_[1] +
               barycentric.z_ * value_[2] +
               barycentric.w_ * value_[3];
    }

    Vector3 GetVertexPosition(unsigned vertexID) const
    {
        assert(vertexID < 4);
        return vertices_[vertexID];
    }

    void DrawDebugGeometry(DebugRenderer* debug, bool depthTest, const Color& color);

private:
    Matrix4 CalculateSurfaceProjectionMatrix(unsigned excludeVertex) const;
    Matrix4 CalculateBarycentricTransformationMatrix() const;

    Vector3 vertices_[4];
    Vector3 value_[4];
    Matrix4 transform_;
};

} // namespace Urho3D
