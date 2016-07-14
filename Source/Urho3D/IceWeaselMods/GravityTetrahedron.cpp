#include "../IceWeaselMods/GravityTetrahedron.h"
#include "../IceWeaselMods/GravityPoint.h"
#include "../IceWeaselMods/Math.h"

#include "../Graphics/DebugRenderer.h"
#include "../Math/Matrix2.h"


namespace Urho3D
{

// ----------------------------------------------------------------------------
GravityTetrahedron::GravityTetrahedron(const GravityPoint& p0,
                                       const GravityPoint& p1,
                                       const GravityPoint& p2,
                                       const GravityPoint& p3)
{
    vertex_[0] = p0;
    vertex_[1] = p1;
    vertex_[2] = p2;
    vertex_[3] = p3;

    transform_ = CalculateBarycentricTransformationMatrix();
}

// ----------------------------------------------------------------------------
Matrix4 GravityTetrahedron::CalculateBarycentricTransformationMatrix() const
{
    // Barycentric transformation matrix
    // https://en.wikipedia.org/wiki/Barycentric_coordinate_system#Conversion_between_barycentric_and_Cartesian_coordinates
    return Matrix4(
        vertex_[0].position_.x_, vertex_[1].position_.x_, vertex_[2].position_.x_, vertex_[3].position_.x_,
        vertex_[0].position_.y_, vertex_[1].position_.y_, vertex_[2].position_.y_, vertex_[3].position_.y_,
        vertex_[0].position_.z_, vertex_[1].position_.z_, vertex_[2].position_.z_, vertex_[3].position_.z_,
        1, 1, 1, 1
    ).Inverse();
}

// ----------------------------------------------------------------------------
void GravityTetrahedron::DrawDebugGeometry(DebugRenderer* debug, bool depthTest, const Color& color)
{
    for(unsigned i = 0; i != 4; ++i)
    {
        for(unsigned j = i + 1; j != 4; ++j)
            debug->AddLine(
                Vector3(vertex_[i].position_.x_, vertex_[i].position_.y_, vertex_[i].position_.z_),
                Vector3(vertex_[j].position_.x_, vertex_[j].position_.y_, vertex_[j].position_.z_),
                color, depthTest
            );
    }

    //debug->AddSphere(Sphere(sphereCenter_, (vertex_[0] - sphereCenter_).Length()), Color::GRAY, depthTest);
}

} // namespace Urho3D
