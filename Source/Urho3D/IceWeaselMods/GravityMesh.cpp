#include "../IceWeaselMods/GravityMesh.h"
#include "../IceWeaselMods/GravityMeshBuilder.h"
#include "../IceWeaselMods/Math.h"
#include "../IceWeaselMods/GravityVector.h"

#include "../Container/Ptr.h"
#include "../Graphics/DebugRenderer.h"
#include "../Math/BoundingBox.h"



namespace Urho3D
{


// ----------------------------------------------------------------------------
GravityMesh::GravityMesh(const GravityMeshBuilder::SharedTetrahedralMesh& sharedVertexMesh)
{
    SetMesh(sharedVertexMesh);
}

// ----------------------------------------------------------------------------
void GravityMesh::SetMesh(const GravityMeshBuilder::SharedTetrahedralMesh& sharedVertexMesh)
{
    tetrahedrons_.Clear();

    for(GravityMeshBuilder::SharedTetrahedralMesh::ConstIterator it = sharedVertexMesh.Begin();
        it != sharedVertexMesh.End();
        ++it)
    {
        GravityMeshBuilder::SharedVertexTetrahedron* t = *it;

        tetrahedrons_.Push(GravityTetrahedron(
            GravityPoint(t->v_[0]->position_, t->v_[0]->direction_, t->v_[0]->forceFactor_),
            GravityPoint(t->v_[1]->position_, t->v_[1]->direction_, t->v_[1]->forceFactor_),
            GravityPoint(t->v_[2]->position_, t->v_[2]->direction_, t->v_[2]->forceFactor_),
            GravityPoint(t->v_[3]->position_, t->v_[3]->direction_, t->v_[3]->forceFactor_)
        ));
    }
}

// ----------------------------------------------------------------------------
bool GravityMesh::Query(Vector3* gravity, const Vector3& position) const
{
    // Use a linear search for now. Can optimise later
    Vector<GravityTetrahedron>::ConstIterator tetrahedron = tetrahedrons_.Begin();
    for(; tetrahedron != tetrahedrons_.End(); ++tetrahedron)
    {
        Vector4 bary = tetrahedron->TransformToBarycentric(position);
        if(tetrahedron->PointLiesInside(bary))
        {
            if(gravity != NULL)
                *gravity = tetrahedron->InterpolateGravity(bary);
            return true;
        }
    }

    return false;
}

// ----------------------------------------------------------------------------
void GravityMesh::DrawDebugGeometry(DebugRenderer* debug, bool depthTest, Vector3 pos)
{
    unsigned count = 0;
    Vector<GravityTetrahedron>::Iterator it = tetrahedrons_.Begin();
    for(; it != tetrahedrons_.End(); ++it)
        if(it->PointLiesInside(it->TransformToBarycentric(pos)))
        {
            it->DrawDebugGeometry(debug, false, Color::RED);
            ++count;
        }
        else
            it->DrawDebugGeometry(debug, depthTest, Color::GRAY);

    //assert(count < 2); // Detects overlapping tetrahedrons (should never happen)
}

} // namespace Urho3D
