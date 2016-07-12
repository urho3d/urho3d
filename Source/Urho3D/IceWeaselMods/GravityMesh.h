#pragma once

#include "../Math/Vector3.h"
#include "../Container/Ptr.h"
#include "../IceWeaselMods/GravityMeshBuilder.h"
#include "../IceWeaselMods/GravityTetrahedron.h"


namespace Urho3D
{

class DebugRenderer;
class GravityVector;


class GravityMesh : public RefCounted
{
public:
    GravityMesh() {}

    /*!
     * @brief Triangulates the list of 3D positions into a tetrahedral mesh.
     */
    GravityMesh(const GravityMeshBuilder::SharedVertexMesh& sharedVertexMesh);

    /*!
     * @brief Queries which tetrahedron a point is located in.
     * @param[out] barycentric If this is not NULL, then the barycentric
     * coordinates used for the bounds check are written to this parameter.
     * These can be directly used for interpolation.
     * @return If the search returned successful, the tetrahedron object is
     * returned. If no tetrahedron was found (e.g. the point exists outside of)
     * the mesh's hull), then NULL is returned.
     * @param[in] position The position to query.
     */
    const GravityTetrahedron* Query(Vector4* barycentric, const Vector3& position) const;

    void SetMesh(const GravityMeshBuilder::SharedVertexMesh& sharedVertexMesh);

    void DrawDebugGeometry(DebugRenderer* debug, bool depthTest, Vector3 pos);

private:
    Vector<GravityTetrahedron> tetrahedrons_;
};

} // namespace Urho3D
