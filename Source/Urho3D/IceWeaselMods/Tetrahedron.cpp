#include "../IceWeaselMods/Tetrahedron.h"
#include "../IceWeaselMods/Math.h"

#include "../Graphics/DebugRenderer.h"
#include "../Math/Matrix2.h"


namespace Urho3D
{

// ----------------------------------------------------------------------------
Tetrahedron::Tetrahedron(const Vector3& v0,
                         const Vector3& v1,
                         const Vector3& v2,
                         const Vector3& v3)
{
    vertices_[0] = v0;
    vertices_[1] = v1;
    vertices_[2] = v2;
    vertices_[3] = v3;

    transform_ = CalculateBarycentricTransformationMatrix();
}

// ----------------------------------------------------------------------------
void Tetrahedron::SetValues(const Vector3& value0,
                            const Vector3& value1,
                            const Vector3& value2,
                            const Vector3& value3)
{
    value_[0] = value0;
    value_[1] = value1;
    value_[2] = value2;
    value_[3] = value3;
}

// ----------------------------------------------------------------------------
/*
void Tetrahedron::ExtendIntoInfinity(unsigned vertexID)
{
    assert(vertexID < 4);

    transform_ = CalculateBarycentricTransformationMatrix() *
                 CalculateSurfaceProjectionMatrix(vertexID);
}*/

// ----------------------------------------------------------------------------
Matrix4 Tetrahedron::CalculateSurfaceProjectionMatrix(unsigned excludeVertex) const
{
    // This function builds a projection matrix that will project a 3D point
    // onto one of the tetrahedron's triangles (namely the face that doesn't
    // contain any vertices equal to vertexID) before transforming the
    // projected point into barycentric coordinates. See doc for more details
    // on this, or see wikipedia:
    // https://en.wikipedia.org/wiki/Projection_(linear_algebra)#Properties_and_classification

    // Select 3 vertices that exclude vertexID (since vertexID is the
    // infinitely far away vertex)
    const Vector3* vertices[3];
    for(unsigned i = 0; i != 3; ++i)
        vertices[i] = i < excludeVertex ? &vertices_[i] : &vertices_[i + 1];

    // Let vertex 0 be our anchor point.
    Vector3 span1 = *vertices[1] - *vertices[0];
    Vector3 span2 = *vertices[2] - *vertices[0];

    // First calculate (A^T * A)^-1
    Matrix2 A = Matrix2(
        span1.x_*span1.x_ + span1.y_*span1.y_ + span1.z_*span1.z_,
        span1.x_*span2.x_ + span1.y_*span2.y_ + span1.z_*span2.z_,
        span2.x_*span1.x_ + span2.y_*span1.y_ + span2.z_*span1.z_,
        span2.x_*span2.x_ + span2.y_*span2.y_ + span2.z_*span2.z_
    ).Inverse();

    // Sandwich the resulting vector with A * b * A^T. The result is a
    // projection matrix without offset.
    Matrix3 projectOntoTriangle = Matrix3(
        // This is matrix A
        span1.x_, span2.x_, 0,
        span1.y_, span2.y_, 0,
        span1.z_, span2.z_, 0
    ) * Matrix3(
        // Matrix multiplication b * A^T
        A.m00_*span1.x_ + A.m01_*span2.x_,
        A.m00_*span1.y_ + A.m01_*span2.y_,
        A.m00_*span1.z_ + A.m01_*span2.z_,

        A.m10_*span1.x_ + A.m11_*span2.x_,
        A.m10_*span1.y_ + A.m11_*span2.y_,
        A.m10_*span1.z_ + A.m11_*span2.z_,

        0, 0, 0
    );

    // The to-be-transformed position needs to be translated by the anchor
    // point before being projected, then translated back. This is because
    // the tetrahedron very likely isn't located at (0, 0, 0)
    Matrix4 translateToOrigin(
        1, 0, 0, -vertices[0]->x_,
        0, 1, 0, -vertices[0]->y_,
        0, 0, 1, -vertices[0]->z_,
        0, 0, 0, 1
    );

    // Create final matrix. Note that the matrices are applied in reverse order
    // in which they were multiplied.
    return translateToOrigin.Inverse() *    // #3 Restore offset
           Matrix4(projectOntoTriangle) *   // #2 Project position onto one of the tetrahedron's triangles
           translateToOrigin;               // #1 Remove offset to origin
}

// ----------------------------------------------------------------------------
Matrix4 Tetrahedron::CalculateBarycentricTransformationMatrix() const
{
    // Barycentric transformation matrix
    // https://en.wikipedia.org/wiki/Barycentric_coordinate_system#Conversion_between_barycentric_and_Cartesian_coordinates
    return Matrix4(
        vertices_[0].x_, vertices_[1].x_, vertices_[2].x_, vertices_[3].x_,
        vertices_[0].y_, vertices_[1].y_, vertices_[2].y_, vertices_[3].y_,
        vertices_[0].z_, vertices_[1].z_, vertices_[2].z_, vertices_[3].z_,
        1, 1, 1, 1
    ).Inverse();
}

// ----------------------------------------------------------------------------
void Tetrahedron::DrawDebugGeometry(DebugRenderer* debug, bool depthTest, const Color& color)
{
    for(unsigned i = 0; i != 4; ++i)
    {
        for(unsigned j = i + 1; j != 4; ++j)
            debug->AddLine(
                Vector3(vertices_[i].x_, vertices_[i].y_, vertices_[i].z_),
                Vector3(vertices_[j].x_, vertices_[j].y_, vertices_[j].z_),
                color, depthTest
            );
    }

    //debug->AddSphere(Sphere(sphereCenter_, (vertices_[0] - sphereCenter_).Length()), Color::GRAY, depthTest);
}

} // namespace Urho3D
