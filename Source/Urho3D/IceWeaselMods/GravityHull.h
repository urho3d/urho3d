#pragma once

#include "../Container/Ptr.h"
#include "../IceWeaselMods/GravityMeshBuilder.h"
#include "../IceWeaselMods/GravityTriangle.h"


namespace Urho3D
{

class DebugRenderer;


class GravityHull : public RefCounted
{
public:
    GravityHull() {}
    GravityHull(const GravityMeshBuilder::Polyhedron& polyhedron);

    void SetMesh(const GravityMeshBuilder::Polyhedron& polyhedron);

    const GravityTriangle* Query(Vector3* barycentric, const Vector3& position) const;

    void DrawDebugGeometry(DebugRenderer* debug, bool depthTest, Vector3 pos) const;

private:
    Vector3 center_;
    Vector<GravityTriangle> triangles_;
};

} // namespace Urho3D
