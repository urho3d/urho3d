#include "../IceWeaselMods/GravityTetrahedron.h"
#include "../IceWeaselMods/Math.h"

#include "../Graphics/DebugRenderer.h"
#include "../Math/Matrix2.h"


namespace Urho3D
{

// ----------------------------------------------------------------------------
GravityTetrahedron::GravityTetrahedron(const Vector3 vertices[4],
                                       const Vector3 directions[4],
                                       const float forceFactors[4]) :
    infiniteVerticesMask_(0)
{
    vertices_[0]         = *vertices++;
    vertices_[1]         = *vertices++;
    vertices_[2]         = *vertices++;
    vertices_[3]         = *vertices++;

    if(directions)
    {
        directions_[0]   = *directions++;
        directions_[1]   = *directions++;
        directions_[2]   = *directions++;
        directions_[3]   = *directions++;
    }

    if(forceFactors)
    {
        forceFactors_[0] = *forceFactors++;
        forceFactors_[1] = *forceFactors++;
        forceFactors_[2] = *forceFactors++;
        forceFactors_[3] = *forceFactors++;
    }

    transform_ = CalculateBarycentricTransformationMatrix();
}

// ----------------------------------------------------------------------------
Matrix4 GravityTetrahedron::CalculateBarycentricTransformationMatrix() const
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
void GravityTetrahedron::DrawDebugGeometry(DebugRenderer* debug, bool depthTest, const Color& color)
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
