#include "../IceWeaselMods/GravityTriangle.h"
#include "../Graphics/DebugRenderer.h"
#include "../Math/Matrix2.h"


namespace Urho3D
{

// ----------------------------------------------------------------------------
GravityTriangle::GravityTriangle(const GravityPoint& p0,
                                 const GravityPoint& p1,
                                 const GravityPoint& p2)
{
    vertex_[0] = p0;
    vertex_[1] = p1;
    vertex_[2] = p2;

    normal_ = (vertex_[1].position_ - vertex_[0].position_).CrossProduct(vertex_[2].position_ - vertex_[0].position_).Normalized();

    transform_ = CalculateBarycentricTransformationMatrix() *
                 CalculateSurfaceProjectionMatrix();
}

// ----------------------------------------------------------------------------
Matrix4 GravityTriangle::CalculateSurfaceProjectionMatrix() const
{
    // This function builds a projection matrix that will project a 3D point
    // onto one of the tetrahedron's triangles (namely the face that doesn't
    // contain any vertices in the infinity mask) before transforming the
    // projected point into barycentric coordinates.
    //
    // See doc/interpolating-values-using-a-tetrahedral-mesh/ for more details
    // on this, or see wikipedia:
    // https://en.wikipedia.org/wiki/Projection_(linear_algebra)#Properties_and_classification

    // Let vertex 0 be our anchor point.
    Vector3 span1 = vertex_[1].position_ - vertex_[0].position_;
    Vector3 span2 = vertex_[2].position_ - vertex_[0].position_;

    // First calculate (A^T * A)^-1
    Matrix2 B = Matrix2(
        span1.x_*span1.x_ + span1.y_*span1.y_ + span1.z_*span1.z_,
        span1.x_*span2.x_ + span1.y_*span2.y_ + span1.z_*span2.z_,
        span2.x_*span1.x_ + span2.y_*span1.y_ + span2.z_*span1.z_,
        span2.x_*span2.x_ + span2.y_*span2.y_ + span2.z_*span2.z_
    ).Inverse();

    // Sandwich the resulting vector with A * B * A^T. The result is a
    // projection matrix without offset.
    Matrix3 projectOntoTriangle = Matrix3(
        // This is matrix A
        span1.x_, span2.x_, 0,
        span1.y_, span2.y_, 0,
        span1.z_, span2.z_, 0
    ) * Matrix3(
        // Matrix multiplication B * A^T
        B.m00_*span1.x_ + B.m01_*span2.x_,
        B.m00_*span1.y_ + B.m01_*span2.y_,
        B.m00_*span1.z_ + B.m01_*span2.z_,

        B.m10_*span1.x_ + B.m11_*span2.x_,
        B.m10_*span1.y_ + B.m11_*span2.y_,
        B.m10_*span1.z_ + B.m11_*span2.z_,

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
Matrix4 GravityTriangle::CalculateBarycentricTransformationMatrix() const
{
    // Barycentric transformation matrix
    // https://en.wikipedia.org/wiki/Barycentric_coordinate_system#Conversion_between_barycentric_and_Cartesian_coordinates
    return Matrix4(
        vertex_[0].position_.x_, vertex_[1].position_.x_, vertex_[2].position_.x_, 0,
        vertex_[0].position_.y_, vertex_[1].position_.y_, vertex_[2].position_.y_, 0,
        vertex_[0].position_.z_, vertex_[1].position_.z_, vertex_[2].position_.z_, 0,
        1, 1, 1, 1
    ).Inverse();
}

// ----------------------------------------------------------------------------
void GravityTriangle::DrawDebugGeometry(DebugRenderer* debug, bool depthTest, const Color& color) const
{
    Vector3 average(Vector3::ZERO);
    for(unsigned i = 0; i != 3; ++i)
    {
        for(unsigned j = i + 1; j != 3; ++j)
            debug->AddLine(vertex_[i].position_, vertex_[j].position_, color, depthTest);
        average += vertex_[i].position_;
    }
    average /= 3.0f;
    debug->AddLine(average, average + normal_, Color::CYAN, depthTest);
}

} // namespace Urho3D
