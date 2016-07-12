#include "../Graphics/DebugRenderer.h"
#include "../IceWeaselMods/GravityHull.h"
#include "../Math/Vector3.h"


namespace Urho3D
{

// ----------------------------------------------------------------------------
GravityHull::GravityHull(const GravityMeshBuilder::Polyhedron& polyhedron)
{
    SetMesh(polyhedron);
}

// ----------------------------------------------------------------------------
void GravityHull::SetMesh(const GravityMeshBuilder::Polyhedron& polyhedron)
{
    triangles_.Clear();

    if(polyhedron.Size() == 0)
        return;

    Vector<Vector3> trianglePositions;

    GravityMeshBuilder::Polyhedron::ConstIterator vertexIt = polyhedron.Begin();
    while(vertexIt != polyhedron.End())
    {
        GravityMeshBuilder::Vertex* vertex0 = *vertexIt++;
        GravityMeshBuilder::Vertex* vertex1 = *vertexIt++;
        GravityMeshBuilder::Vertex* vertex2 = *vertexIt++;

        Vector3 vertex[3] = {
            vertex0->position_,
            vertex1->position_,
            vertex2->position_
        };
        Vector3 direction[3] = {
            vertex0->direction_,
            vertex1->direction_,
            vertex2->direction_
        };
        float forceFactor[3] = {
            vertex0->forceFactor_,
            vertex1->forceFactor_,
            vertex2->forceFactor_
        };

        trianglePositions.Push(
            (vertex[0] + vertex[1] + vertex[2]) / 3.0f
        );

        triangles_.Push(GravityTriangle(vertex, direction, forceFactor));
    }

    center_ = Vector3::ZERO;
    for(Vector<Vector3>::ConstIterator it = trianglePositions.Begin(); it != trianglePositions.End(); ++it)
        center_ += *it;
    center_ /= trianglePositions.Size();
}

// ----------------------------------------------------------------------------
const GravityTriangle* GravityHull::Query(Vector3* barycentric, const Vector3& position) const
{
    Vector3 distanceVec = center_ - position;
    Vector3 direction = distanceVec.Normalized();
    float distanceSquared = distanceVec.LengthSquared();

    // Use a linear search for now. Can optimise later
    Vector<GravityTriangle>::ConstIterator triangle = triangles_.Begin();
    for(; triangle != triangles_.End(); ++triangle)
    {
        Vector3 bary = triangle->Intersect(position, direction);
        if(triangle->PointLiesInside(bary))
        {
            // It's possible we hit a triangle on the other side.
            Vector3 intersectionLocation = triangle->TransformToCartesian(bary);
            if((position - intersectionLocation).LengthSquared() > distanceSquared)
                continue;

            // We found the triangle, return it
            if(barycentric != NULL)
                *barycentric = bary;
            return &(*triangle);
        }
    }

    return NULL;
}

// ----------------------------------------------------------------------------
void GravityHull::DrawDebugGeometry(DebugRenderer* debug, bool depthTest, Vector3 pos) const
{
    for(Vector<GravityTriangle>::ConstIterator it = triangles_.Begin(); it != triangles_.End(); ++it)
    {
        it->DrawDebugGeometry(debug, depthTest, Color::GRAY);
    }

    Vector3 bary;
    const GravityTriangle* triangle = Query(&bary, pos);
    if(triangle)
        debug->AddSphere(Sphere(triangle->TransformToCartesian(bary), 0.1f), Color::RED, depthTest);
}

} // namespace Urho3D
