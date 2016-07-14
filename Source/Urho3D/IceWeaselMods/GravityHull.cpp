#include "../Graphics/DebugRenderer.h"
#include "../IceWeaselMods/GravityHull.h"
#include "../Math/Vector3.h"

#include <stdio.h>


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
    typedef GravityMeshBuilder::Vertex Vertex;
    typedef GravityMeshBuilder::Polyhedron Polyhedron;

    triangles_.Clear();
    edges_.Clear();
    points_.Clear();

    if(polyhedron.Size() == 0)
        return;

    Vector<Vector3> trianglePositions;

    Polyhedron::ConstIterator vertexIt = polyhedron.Begin();
    while(vertexIt != polyhedron.End())
    {
        Vertex* vertex0 = *vertexIt++;
        Vertex* vertex1 = *vertexIt++;
        Vertex* vertex2 = *vertexIt++;

        // Accumulate positions of triangle centres for average position
        trianglePositions.Push(
            (vertex0->position_ + vertex1->position_ + vertex2->position_) / 3.0f
        );

        // Add triangle
        triangles_.Push(GravityTriangle(
            GravityPoint(vertex0->position_, vertex0->direction_, vertex0->forceFactor_),
            GravityPoint(vertex1->position_, vertex1->direction_, vertex1->forceFactor_),
            GravityPoint(vertex2->position_, vertex2->direction_, vertex2->forceFactor_)
        ));

        // Add three points
        points_.Push(GravityPoint(vertex0->position_, vertex0->direction_, vertex0->forceFactor_));
        points_.Push(GravityPoint(vertex1->position_, vertex1->direction_, vertex1->forceFactor_));
        points_.Push(GravityPoint(vertex2->position_, vertex2->direction_, vertex2->forceFactor_));
    }

    // Average triangle centres to get centre of hull
    centre_ = Vector3::ZERO;
    for(Vector<Vector3>::ConstIterator it = trianglePositions.Begin(); it != trianglePositions.End(); ++it)
        centre_ += *it;
    centre_ /= trianglePositions.Size();

    // Make sure each triangle's normal vector is pointing away from centre of
    // the hull
    for(Vector<GravityTriangle>::Iterator it = triangles_.Begin(); it != triangles_.End(); ++it)
    {
        Vector3 outwards = it->GetVertex(0).position_ - centre_;
        if(outwards.DotProduct(it->GetNormal()) < 0)
            it->FlipNormal();
    }

    // With the centre and normals calculated, we can use that information to
    // construct edges. Each edge stores the normal vectors of both triangles
    // it joins in order to calculate if a projected point is projected from
    // the correct angle or not.
    //
    // We iterate the polyhedron and the triangles list simultaneously, because
    // it is more efficient to check for joined edges using the polyhedron data
    // structure than the triangles list. The triangles list is required to get
    // the calculated and adjusted normals.
    vertexIt = polyhedron.Begin();
    Vector<GravityTriangle>::ConstIterator triangleIt = triangles_.Begin();
    for(; vertexIt != polyhedron.End(); triangleIt++)
    {
        Vertex* vertex[3];
        vertex[0] = *vertexIt++;
        vertex[1] = *vertexIt++;
        vertex[2] = *vertexIt++;

        // find the three adjacent triangles
        Vector<GravityTriangle>::ConstIterator triangleIt2 = triangles_.Begin();
        Polyhedron::ConstIterator vertexIt2 = polyhedron.Begin();
        for(; vertexIt2 != polyhedron.End(); triangleIt2++)
        {
            Vertex* vertex2[3];
            vertex2[0] = *vertexIt2++;
            vertex2[1] = *vertexIt2++;
            vertex2[2] = *vertexIt2++;

            // skip self
            if(vertexIt == vertexIt2)
                continue;

            // joined[2] will contain two Vertex objects if we find an edge
            // that is shared between the two current triangles.
            Vertex* joined[2];
            Vertex** joinedPtr = joined;
            for(unsigned char i = 0; i != 3; ++i)
                for(unsigned char j = 0; j != 3; ++j)
                    if(vertex[i] == vertex2[j])
                        *joinedPtr++ = vertex[i];

            // Calculate number of vertices that were found joined.
            unsigned joinedCount = joinedPtr - joined;
            assert(joinedCount != 3);
            if(joinedCount != 2)
                continue;

            // Found a joined edge, add it
            edges_.Push(GravityEdge(
                GravityPoint(joined[0]->position_, joined[0]->direction_, joined[0]->forceFactor_),
                GravityPoint(joined[1]->position_, joined[1]->direction_, joined[1]->forceFactor_),
                triangleIt->GetNormal(),
                triangleIt2->GetNormal()
            ));

            // Make sure edge boundary check points outwards from the hull's
            // centre
            Vector2 bary = edges_.Back().ProjectAndTransformToBarycentric(centre_);
            if(edges_.Back().ProjectionAngleIsInBounds(edges_.Back().TransformToCartesian(bary), centre_))
                edges_.Back().FlipBoundaryCheck();
        }
    }
}

// ----------------------------------------------------------------------------
bool GravityHull::Query(Vector3* gravity, const Vector3& position)
{
    /* NOTE This method works, but was removed because the results were not
     * good enough.
    Vector3 distanceVec = centre_ - position;
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
    }*/

    Vector3 distanceVec =  position - centre_;

    // Try all faces first
    for(Vector<GravityTriangle>::ConstIterator triangle = triangles_.Begin();
        triangle != triangles_.End();
        ++triangle)
    {
        Vector3 bary = triangle->ProjectAndTransformToBarycentric(position);
        if(triangle->PointLiesInside(bary))
        {
            // It's possible we hit a triangle on the other side
            if(distanceVec.DotProduct(triangle->GetNormal()) < 0)
                continue;

            // We found the triangle, interpolate gravity vector and return
            if(gravity != NULL)
                *gravity = triangle->InterpolateGravity(bary);
            lastIntersection_ = triangle->TransformToCartesian(bary);
            return true;
        }
    }

    // Try all edges
    for(Vector<GravityEdge>::ConstIterator edge = edges_.Begin();
        edge != edges_.End();
        ++edge)
    {
        Vector2 bary = edge->ProjectAndTransformToBarycentric(position);
        if(edge->PointLiesInside(bary))
        {
            // It's possible we're not projecting from the correct angle
            if(!edge->ProjectionAngleIsInBounds(edge->TransformToCartesian(bary), position))
                continue;

            // Found the edge, interpolate gravity vector and return
            if(gravity != NULL)
                *gravity = edge->InterpolateGravity(bary);
            lastIntersection_ = edge->TransformToCartesian(bary);
            return true;
        }
    }

    // Find closest vertex as a last resort
    float distanceSquared = M_INFINITY;
    const GravityPoint* foundPoint = NULL;
    for(Vector<GravityPoint>::ConstIterator point = points_.Begin();
        point != points_.End();
        ++point)
    {
        float newDist = (point->position_ - position).LengthSquared();
        if(newDist < distanceSquared)
        {
            distanceSquared = newDist;
            foundPoint = &(*point);
        }
    }
    if(foundPoint != NULL)
    {
        if(gravity != NULL)
            *gravity = foundPoint->direction_ * foundPoint->forceFactor_;
        lastIntersection_ = foundPoint->position_;
        return true;
    }

    return false;
}

// ----------------------------------------------------------------------------
void GravityHull::DrawDebugGeometry(DebugRenderer* debug, bool depthTest, Vector3 pos) const
{
    for(Vector<GravityTriangle>::ConstIterator it = triangles_.Begin(); it != triangles_.End(); ++it)
        it->DrawDebugGeometry(debug, depthTest, Color::WHITE);

    for(Vector<GravityEdge>::ConstIterator it = edges_.Begin(); it != edges_.End(); ++it)
        it->DrawDebugGeometry(debug, depthTest, Color::WHITE);

    debug->AddSphere(Sphere(lastIntersection_, 1.0f), Color::RED, depthTest);
}

} // namespace Urho3D
