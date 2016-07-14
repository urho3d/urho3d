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
     * @brief Creates the gravity mesh from a shared vertex mesh (provided by
     * GravityMeshBuilder).
     *
     * The mesh is split into individual tetrahedron objects.
     */
    GravityMesh(const GravityMeshBuilder::SharedTetrahedralMesh& sharedVertexMesh);

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
    bool Query(Vector3* gravity, const Vector3& position) const;

    /*!
     * @brief Replaces the existing gravity mesh (if any) with a shared vertex
     * mesh (provided by GravityMeshBuilder).
     *
     * The mesh is split into individual tetrahedron objects.
     */
    void SetMesh(const GravityMeshBuilder::SharedTetrahedralMesh& sharedVertexMesh);

    void DrawDebugGeometry(DebugRenderer* debug, bool depthTest, Vector3 pos);

private:
    // TODO consider just using GravityMeshBuilder::SharedTetrahedralMesh directly
    Vector<GravityTetrahedron> tetrahedrons_;
};

} // namespace Urho3D
