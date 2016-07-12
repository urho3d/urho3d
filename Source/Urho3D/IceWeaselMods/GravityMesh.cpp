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
GravityMesh::GravityMesh(const GravityMeshBuilder::SharedVertexMesh& sharedVertexMesh)
{
    SetMesh(sharedVertexMesh);
}
void GravityMesh::SetMesh(const GravityMeshBuilder::SharedVertexMesh& sharedVertexMesh)
{
    tetrahedrons_.Clear();

    for(GravityMeshBuilder::SharedVertexMesh::ConstIterator it = sharedVertexMesh.Begin();
        it != sharedVertexMesh.End();
        ++it)
    {
        GravityMeshBuilder::SharedVertexTetrahedron* t = *it;

        Vector3 vertices[4] = {
            t->v_[0]->position_,
            t->v_[1]->position_,
            t->v_[2]->position_,
            t->v_[3]->position_};
        Vector3 directions[4] = {
            t->v_[0]->direction_,
            t->v_[1]->direction_,
            t->v_[2]->direction_,
            t->v_[3]->direction_
        };
        float forceFactors[4] = {
            t->v_[0]->forceFactor_,
            t->v_[1]->forceFactor_,
            t->v_[2]->forceFactor_,
            t->v_[3]->forceFactor_
        };

        tetrahedrons_.Push(GravityTetrahedron(vertices, directions, forceFactors));
    }
}

// ----------------------------------------------------------------------------
const GravityTetrahedron* GravityMesh::Query(Vector4* barycentric, const Vector3& position) const
{
    // Use a linear search for now. Can optimise later
    Vector<GravityTetrahedron>::ConstIterator tetrahedron = tetrahedrons_.Begin();
    for(; tetrahedron != tetrahedrons_.End(); ++tetrahedron)
    {
        Vector4 bary = tetrahedron->TransformToBarycentric(position);
        if(tetrahedron->PointLiesInside(bary))
        {
            if(barycentric != NULL)
                *barycentric = bary;
            return &(*tetrahedron);
        }
    }

    return NULL;
}

// ----------------------------------------------------------------------------
void GravityMesh::DrawDebugGeometry(DebugRenderer* debug, bool depthTest, Vector3 pos)
{
    unsigned count = 0;
    Vector<GravityTetrahedron>::Iterator it = tetrahedrons_.Begin();
    for(; it != tetrahedrons_.End(); ++it)
        if(it->PointLiesInside(pos))
        {
            it->DrawDebugGeometry(debug, false, Color::RED);
            ++count;
        }
        else
            it->DrawDebugGeometry(debug, depthTest, Color::WHITE);

    for(it = tetrahedrons_.Begin(); it != tetrahedrons_.End(); ++it)
        for(unsigned i = 0; i != 4; ++i)
            for(unsigned j = 0; j != 4; ++j)
            {
                Vector3 a = it->GetVertexPosition(i);
                Vector3 b = it->GetVertexPosition(j);
                debug->AddLine(a, b, Color::GRAY, depthTest);
            }

    //assert(count < 2); // Detects overlapping tetrahedrons (should never happen)
}

} // namespace Urho3D
