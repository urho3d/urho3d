#include "../IceWeaselMods/GravityEdge.h"
#include "../Graphics/DebugRenderer.h"
#include "../Math/Matrix2.h"


namespace Urho3D
{

// ----------------------------------------------------------------------------
GravityEdge::GravityEdge(const GravityPoint& p0,
                         const GravityPoint& p1,
                         const Vector3& boundaryNormal0,
                         const Vector3& boundaryNormal1)
{
    vertex_[0] = p0;
    vertex_[1] = p1;
    boundaryNormal_[0] = boundaryNormal0;
    boundaryNormal_[1] = boundaryNormal1;

    Matrix4 bt = CalculateBarycentricTransformationMatrix();
    Matrix4 et = CalculateEdgeProjectionMatrix();
    transform_ = bt * et;
                 ;
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
    Vector3 span = vertex_[1].position_ - vertex_[0].position_;

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
        1, 0, 0, -vertex_[0].position_.x_,
        0, 1, 0, -vertex_[0].position_.y_,
        0, 0, 1, -vertex_[0].position_.z_,
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
    Vector3 fix1 = vertex_[0].position_.CrossProduct(vertex_[1].position_);
    Vector3 fix2 = fix1 + vertex_[0].position_;
    // Barycentric transformation matrix
    // https://en.wikipedia.org/wiki/Barycentric_coordinate_system#Conversion_between_barycentric_and_Cartesian_coordinates
    return Matrix4(
        vertex_[0].position_.x_, vertex_[1].position_.x_, fix1.x_, fix2.x_,
        vertex_[0].position_.y_, vertex_[1].position_.y_, fix1.y_, fix2.y_,
        vertex_[0].position_.z_, vertex_[1].position_.z_, fix1.z_, fix2.z_,
        1, 1, 1, 1
    ).Inverse();
}

// ----------------------------------------------------------------------------
void GravityEdge::DrawDebugGeometry(DebugRenderer* debug, bool depthTest, const Color& color) const
{
    debug->AddLine(vertex_[0].position_, vertex_[1].position_, color, depthTest);

    debug->AddLine(vertex_[0].position_, vertex_[0].position_ + boundaryNormal_[0], Color::CYAN, depthTest);
    debug->AddLine(vertex_[0].position_, vertex_[0].position_ + boundaryNormal_[1], Color::CYAN, depthTest);
    debug->AddLine(vertex_[1].position_, vertex_[1].position_ + boundaryNormal_[0], Color::CYAN, depthTest);
    debug->AddLine(vertex_[1].position_, vertex_[1].position_ + boundaryNormal_[1], Color::CYAN, depthTest);
}

} // namespace Urho3D
