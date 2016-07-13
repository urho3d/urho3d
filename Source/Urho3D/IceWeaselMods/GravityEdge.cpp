#include "../IceWeaselMods/GravityEdge.h"
#include "../Graphics/DebugRenderer.h"
#include "../Math/Matrix2.h"


namespace Urho3D
{

// ----------------------------------------------------------------------------
GravityEdge::GravityEdge(const Vector3 vertices[2],
                         const Vector3 directions[2],
                         const float forceFactors[2])
{
    vertices_[0]         = *vertices++;
    vertices_[1]         = *vertices++;
    vertices_[2]         = *vertices++;

    if(directions)
    {
        directions_[0]   = *directions++;
        directions_[1]   = *directions++;
        directions_[2]   = *directions++;
    }

    if(forceFactors)
    {
        forceFactors_[0] = *forceFactors++;
        forceFactors_[1] = *forceFactors++;
        forceFactors_[2] = *forceFactors++;
    }
}

// ----------------------------------------------------------------------------
Matrix4 GravityEdge::CalculateEdgeProjectionMatrix() const
{
    // This function builds a projection matrix that will project a 3D point
    // onto one of the tetrahedron's edges (namely the edges that doesn't
    // contain any vertices in the infinity mask) before transforming the
    // projected point into barycentric coordinates.
    //
    // See doc/interpolating-values-using-a-tetrahedral-mesh/ for more details
    // on this, or see wikipedia:
    // https://en.wikipedia.org/wiki/Projection_(linear_algebra)#Properties_and_classification

    // Let vertex 0 be our anchor point.
    Vector3 span = *vertices_[1] - *vertices_[0];

    // First calculate (A^T * A)^-1
    float B = span.x_*span.x_ + span.y_*span.y_ + span.z_*span.z_;
    B = 1.0f / B; // Inverse

    // Sandwich the resulting vector with A * B * A^T. The result is a
    // projection matrix without offset.
    Matrix3 projectOntoTriangle = Matrix3(
        // This is matrix A
        span.x_, 0, 0,
        span.y_, 0, 0,
        span.z_, 0, 0
    ) * Matrix3(
        // Matrix multiplication B * A^T
        B*span.x_,
        B*span.y_,
        B*span.z_,

        0, 0, 0,
        0, 0, 0
    );

    // The to-be-transformed position needs to be translated by the anchor
    // point before being projected, then translated back. This is because
    // the tetrahedron very likely isn't located at (0, 0, 0)
    Matrix4 translateToOrigin(
        1, 0, 0, -vertices_[0].x_,
        0, 1, 0, -vertices_[0].y_,
        0, 0, 1, -vertices_[0].z_,
        0, 0, 0, 1
    );

    // Create final matrix. Note that the matrices are applied in reverse order
    // in which they were multiplied.
    return translateToOrigin.Inverse() *    // #3 Restore offset
           Matrix4(projectOntoTriangle) *   // #2 Project position onto one of the tetrahedron's triangles
           translateToOrigin;               // #1 Remove offset to origin
}

// ----------------------------------------------------------------------------
Matrix4 GravityEdge::CalculateBarycentricTransformationMatrix() const
{
    // Barycentric transformation matrix
    // https://en.wikipedia.org/wiki/Barycentric_coordinate_system#Conversion_between_barycentric_and_Cartesian_coordinates
    return Matrix4(
        vertices_[0].x_, vertices_[1].x_, vertices_[2].x_, 0,
        vertices_[0].y_, vertices_[1].y_, vertices_[2].y_, 0,
        vertices_[0].z_, vertices_[1].z_, vertices_[2].z_, 0,
        1, 1, 1, 1
    ).Inverse();
}

// ----------------------------------------------------------------------------
void GravityEdge::DrawDebugGeometry(DebugRenderer* debug, bool depthTest, const Color& color) const
{
    for(unsigned i = 0; i != 2; ++i)
    {
        for(unsigned j = i + 1; j != 2; ++j)
            debug->AddLine(
                Vector3(vertices_[i].x_, vertices_[i].y_, vertices_[i].z_),
                Vector3(vertices_[j].x_, vertices_[j].y_, vertices_[j].z_),
                color, depthTest
            );
    }

    //debug->AddSphere(Sphere(sphereCenter_, (vertices_[0] - sphereCenter_).Length()), Color::GRAY, depthTest);
}

} // namespace Urho3D
