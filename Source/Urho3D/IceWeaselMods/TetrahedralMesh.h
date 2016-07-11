#pragma once

#include "../Math/Vector3.h"
#include "../Container/Ptr.h"
#include "../IceWeaselMods/Tetrahedron.h"


namespace Urho3D
{

class GravityVector;


class TetrahedralMesh : public RefCounted
{
public:
    TetrahedralMesh() {}

    /*!
     * @brief Triangulates the list of 3D positions into a tetrahedral mesh.
     */
    TetrahedralMesh(const PODVector<GravityVector*>& gravityVectors);

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
    const Tetrahedron* Query(Vector4* barycentric, const Vector3& position) const;

    void Build(const PODVector<GravityVector*>& gravityVectors);

    void DrawDebugGeometry(DebugRenderer* debug, bool depthTest, Vector3 pos);

private:
    Vector<Tetrahedron> tetrahedrons_;
};

} // namespace Urho3D
