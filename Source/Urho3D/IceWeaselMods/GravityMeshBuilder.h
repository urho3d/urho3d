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

    /// Data type used to represent a mesh of tetrahedrons who's vertices can be referenced more than once.
    typedef Vector<SharedPtr<SharedVertexTetrahedron> > SharedTetrahedralMesh;
    /// Data type to represent a number of triangles. There will always be a multiple of 3 vertices.
    typedef PODVector<Vertex*> Polyhedron;

    /*!
     * @brief Takes a list of gravity vector components and creates a triangulated mesh.
     */
    void Build(const PODVector<GravityVector*>& gravityVectors);

    /*!
     * @brief After building, the resulting mesh can be retrieved with this.
     */
    const SharedTetrahedralMesh& GetSharedTetrahedralMesh() const;

    const Polyhedron& GetHullMesh() const;

private:

    /*!
     * @brief Finds all tetrahedrons who's circumsphere contains a point.
     * @param[out] badTetrahedrons All tetrahedrons containing the point will be
     * stored in this list.
     * @param[in] point The 3D point to test for.
     */
    void FindBadTetrahedrons(SharedTetrahedralMesh* badTetrahedrons, Vector3 point) const;

    /*!
     * @brief Creates a list of triangles are the hull of the specified list of
     * tetrahedrons.
     * @param[out] polyhedron The polyhedron (a list of triangles) is written
     * to this parameter. It will be the hull of the provided list of
     * tetrahedrons.
     * @param[in] tetrahedrons The tetrahedrons to create the hull from.
     */
    static void CreateHullFromTetrahedrons(
        Polyhedron* polyhedron, const SharedTetrahedralMesh& tetrahedrons);

    /*!
     * @brief Removes the specified tetrahedrons from the triangulation result.
     * @param[in] tetrahedrons A list of tetrahedrons to remove.
     */
    void RemoveTetrahedronsFromTriangulation(const SharedTetrahedralMesh& tetrahedrons);

    /*!
     * @brief Creates tetrahedrons by connecting each triangle of a polyhedron
     * to that of the specified gravity vector.
     * @param[in] polyhedron The hull, or polyhedron.
     * @param[in] gravityVector The position, direction and force factor of the
     * gravity vector component is used to create the new vertex to which
     * the faces are connected.
     */
    void ReTriangulateGap(const Polyhedron& polyhedron,const GravityVector& gravityVector);

    /*!
     * @brief Cleans up the triangulation result such that no more connections
     * exist to the original super tetrahedron.
     */
    void CleanUp(SharedPtr<SharedVertexTetrahedron> superTetrahedron);

    SharedTetrahedralMesh triangulationResult_;
    Polyhedron hull_;
};

} // namespace Urho3D
