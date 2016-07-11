#pragma once

#include <Urho3D/Math/Vector3.h>
#include <Urho3D/Math/Matrix3.h>

namespace Urho3D
{


class Math
{
public:

    /*!
     * @brief Projects a point onto the plane defined by a non-degenerate
     * triangle and checks if that point is within the triangle's boundaries.
     * @param[out] pointOnTriangle The 3D location of the projected point onto
     * the plane defined by the triangle is written to this parameter. The
     * parameter may be NULL.
     * @param[in] pointToProject A point in 3D space to project onto the
     * triangle.
     * @param[in] v0 First vertex of the triangle.
     * @param[in] v1 Second vertex of the triangle.
     * @param[in] v2 Third vertex of the triangle.
     * @return Returns true if the point was inside of the triangle, false if
     * the point was outside of the triangle.
     */
    static bool ProjectOntoTriangle(Urho3D::Vector3* pointOnTriangle,
                                    const Urho3D::Vector3& pointToProject,
                                    const Urho3D::Vector3& v0,
                                    const Urho3D::Vector3& v1,
                                    const Urho3D::Vector3& v2)
    {
        // http://math.stackexchange.com/questions/544946/determine-if-projection-of-3d-point-onto-plane-is-within-a-triangle
        Urho3D::Vector3 edge1 = v1 - v0;
        Urho3D::Vector3 edge2 = v2 - v0;
        Urho3D::Vector3 normal = v1.CrossProduct(v2);
        Urho3D::Vector3 w = pointToProject - v0;
        float normalSquared = normal.DotProduct(normal);

        float gamma = edge1.CrossProduct(w).DotProduct(normal) / normalSquared;
        float beta  = w.CrossProduct(edge2).DotProduct(normal) / normalSquared;
        float alpha = 1.0f - gamma - beta;

        if(pointOnTriangle)
            *pointOnTriangle = alpha * v0 + beta * v1 + gamma * v2;

        return (
            0.0f <= alpha && alpha <= 1.0f &&
            0.0f <= beta  && beta  <= 1.0f &&
            0.0f <= gamma && gamma <= 1.0f
        );
    }

    static float DistanceToPlane(const Urho3D::Vector3& pointToProject,
                                 const Urho3D::Vector3& v0,
                                 const Urho3D::Vector3& v1,
                                 const Urho3D::Vector3& v2)
    {
        Urho3D::Vector3 normal = v1.CrossProduct(v2);
        Urho3D::Vector3 w = pointToProject - v0;

        return w.DotProduct(normal.Normalized());
    }

    static Urho3D::Vector3 CircumscribeSphere(const Urho3D::Vector3& v0,
                                              const Urho3D::Vector3& v1,
                                              const Urho3D::Vector3& v2,
                                              const Urho3D::Vector3& v3)
    {
        Urho3D::Vector3 a = v1 - v0;
        Urho3D::Vector3 b = v2 - v0;
        Urho3D::Vector3 c = v3 - v0;

        float aa = a.LengthSquared();
        float bb = b.LengthSquared();
        float cc = c.LengthSquared();

        Urho3D::Vector3 numerator(
            cc * a.CrossProduct(b) +
            bb * c.CrossProduct(a) +
            aa * b.CrossProduct(c)
        );

        float denominator = 2.0f * b.CrossProduct(c).DotProduct(a);

        return v0 + numerator / denominator;
    }
};

} // namespace Urho3D
