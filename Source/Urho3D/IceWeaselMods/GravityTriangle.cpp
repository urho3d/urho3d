#include "../IceWeaselMods/GravityTriangle.h"
#include "../Graphics/DebugRenderer.h"


namespace Urho3D
{

// ----------------------------------------------------------------------------
GravityTriangle::GravityTriangle(const Vector3 vertices[3],
                                 const Vector3 directions[3],
                                 const float forceFactors[3])
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
void GravityTriangle::DrawDebugGeometry(DebugRenderer* debug, bool depthTest, const Color& color) const
{
    for(unsigned i = 0; i != 3; ++i)
    {
        for(unsigned j = i + 1; j != 3; ++j)
            debug->AddLine(
                Vector3(vertices_[i].x_, vertices_[i].y_, vertices_[i].z_),
                Vector3(vertices_[j].x_, vertices_[j].y_, vertices_[j].z_),
                color, depthTest
            );
    }

    //debug->AddSphere(Sphere(sphereCenter_, (vertices_[0] - sphereCenter_).Length()), Color::GRAY, depthTest);
}

} // namespace Urho3D
