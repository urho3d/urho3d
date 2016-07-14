#pragma once

#include "../Container/Ptr.h"
#include "../IceWeaselMods/GravityMeshBuilder.h"
#include "../IceWeaselMods/GravityTriangle.h"
#include "../IceWeaselMods/GravityEdge.h"


namespace Urho3D
{

class DebugRenderer;


class GravityHull : public RefCounted
{
public:
    GravityHull() {}
    GravityHull(const GravityMeshBuilder::Polyhedron& polyhedron);

    void SetMesh(const GravityMeshBuilder::Polyhedron& polyhedron);

    bool Query(Vector3* gravity, const Vector3& position);

    void DrawDebugGeometry(DebugRenderer* debug, bool depthTest, Vector3 pos) const;

private:
    Vector3 centre_;
    Vector<GravityTriangle> triangles_;
    Vector<GravityEdge> edges_;
    Vector<GravityPoint> points_;

    Vector3 lastIntersection_;
};

} // namespace Urho3D
