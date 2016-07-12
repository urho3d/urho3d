#pragma once

#include "../Container/Ptr.h"
#include "../Container/Vector.h"
#include "../Math/Vector3.h"


namespace Urho3D
{

class GravityVector;


struct GravityMeshBuilder
{
    /*!
     * @brief Reference counted vertex. Holds position, (gravitational)
     * direction, and (gravitational) force factor as attributes.
     */
    class Vertex : public RefCounted
    {
    public:
        Vertex(const Vector3& position,
               const Vector3& direction=Vector3::ZERO,
               float forceFactor=0.0f);

        Vector3 position_;
        Vector3 direction_;
        float forceFactor_;
    };

    /*!
     * @brief Construct a tetrahedron by using existing Vertex objects. Allows
     * for multiple tetrahedrons to share the same vertices.
     */
    class SharedVertexTetrahedron : public RefCounted
    {
    public:
        SharedVertexTetrahedron() {}
        SharedVertexTetrahedron(Vertex* v1, Vertex* v2, Vertex* v3, Vertex* v4);

        SharedPtr<Vertex> v_[4];
        Vector3 circumscibedSphereCenter_;
    };

    typedef Vector<SharedPtr<SharedVertexTetrahedron> > SharedVertexMesh;
    typedef PODVector<Vertex*> Polyhedron;

    void Build(const PODVector<GravityVector*>& gravityVectors);

    const SharedVertexMesh& GetSharedVertexMesh() const;

private:

    /*!
     * @brief Finds all tetrahedrons who's circumsphere contains a point.
     * @param[out] badTetrahedrons All tetrahedrons containing the point will be
     * stored in this list.
     * @param[in] point The 3D point to test for.
     */
    void FindBadTetrahedrons(SharedVertexMesh* badTetrahedrons, Vector3 point) const;

    /*!
     * @brief
     * @param[out] polyhedron
     * @param[in] badTetrahedrons
     */
    static void CreatePolyhedronFromBadTetrahedrons(
        Polyhedron* polyhedron, const SharedVertexMesh& badTetrahedrons);

    /*!
     * @brief
     * @param[in] badTetrahedrons
     */
    void RemoveBadTetrahedronsFromTriangulation(const SharedVertexMesh& badTetrahedrons);

    /*!
     * @brief
     * @param[in] polyhedron
     * @param[in] gravityVector
     */
    void ReTriangulateGap(const Polyhedron& polyhedron,const GravityVector& gravityVector);

    void CleanUp(SharedPtr<SharedVertexTetrahedron> superTetrahedron);

    SharedVertexMesh triangulationResult_;
};

} // namespace Urho3D
