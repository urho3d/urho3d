#include "../IceWeaselMods/GravityMeshBuilder.h"
#include "../IceWeaselMods/Math.h"
#include "../IceWeaselMods/GravityVector.h"
#include "../Math/BoundingBox.h"


namespace Urho3D {


// ============================================================================
GravityMeshBuilder::
Vertex::Vertex(const Vector3& position,
               const Vector3& direction,
               float forceFactor) :
    position_(position),
    direction_(direction),
    forceFactor_(forceFactor)
{}


// ============================================================================
GravityMeshBuilder::
SharedVertexTetrahedron::SharedVertexTetrahedron(Vertex* v1, Vertex* v2,
                                                 Vertex* v3, Vertex* v4)
{
    v_[0] = v1; v_[1] = v2; v_[2] = v3; v_[3] = v4;
    circumscibedSphereCenter_ = Math::CircumscribeSphere(v1->position_,
                                                         v2->position_,
                                                         v3->position_,
                                                         v4->position_);
}


// ============================================================================
struct Face
{
    Face() {}
    Face(GravityMeshBuilder::Vertex* v1,
         GravityMeshBuilder::Vertex* v2,
         GravityMeshBuilder::Vertex* v3) :
        marked_(true)
    {
        v_[0] = v1;
        v_[1] = v2;
        v_[2] = v3;
    }

    bool FaceIsShared(const Face* other)
    {
        unsigned count = 0;
        for(unsigned i = 0; i != 3; ++i)
            for(unsigned j = 0; j != 3; ++j)
                if(other->v_[i] == v_[j])
                    if(++count == 3)
                        return true;
        return false;
    }

    GravityMeshBuilder::Vertex* v_[3];
    bool marked_;
};


// ============================================================================
static GravityMeshBuilder::SharedVertexTetrahedron*
ConstructSuperTetrahedron(const PODVector<GravityVector*>& gravityVectors)
{
    typedef GravityMeshBuilder::Vertex Vertex;
    typedef GravityMeshBuilder::SharedVertexTetrahedron SharedVertexTetrahedron;

    // Compute bounding box
    BoundingBox aabb;
    for(PODVector<GravityVector*>::ConstIterator it = gravityVectors.Begin();
        it != gravityVectors.End();
        ++it)
    {
        const Vector3& pos = (*it)->GetPosition();
        if(aabb.min_.x_ > pos.x_) aabb.min_.x_ = pos.x_;
        if(aabb.min_.y_ > pos.y_) aabb.min_.y_ = pos.y_;
        if(aabb.min_.z_ > pos.z_) aabb.min_.z_ = pos.z_;
        if(aabb.max_.x_ < pos.x_) aabb.max_.x_ = pos.x_;
        if(aabb.max_.y_ < pos.y_) aabb.max_.y_ = pos.y_;
        if(aabb.max_.z_ < pos.z_) aabb.max_.z_ = pos.z_;
    }

    // Expand bounding box by factor 3 plus a small error margin
    aabb.min_.x_ -= (aabb.max_.x_ - aabb.min_.x_) * 2.2f;
    aabb.min_.y_ -= (aabb.max_.y_ - aabb.min_.y_) * 2.2f;
    aabb.min_.z_ -= (aabb.max_.z_ - aabb.min_.z_) * 2.2f;
    aabb.max_.x_ += Abs(aabb.max_.x_ * 0.1f);
    aabb.max_.y_ += Abs(aabb.max_.y_ * 0.1f);
    aabb.max_.z_ += Abs(aabb.max_.z_ * 0.1f);

    // This tetrahedron should encompass all vertices in the list
    return new SharedVertexTetrahedron(
        new Vertex(aabb.max_),
        new Vertex(Vector3(aabb.min_.x_, aabb.max_.y_, aabb.max_.z_)),
        new Vertex(Vector3(aabb.max_.x_, aabb.min_.y_, aabb.max_.z_)),
        new Vertex(Vector3(aabb.max_.x_, aabb.max_.y_, aabb.min_.z_))
    );
}

// ----------------------------------------------------------------------------
void GravityMeshBuilder::Build(const PODVector<GravityVector*>& gravityVectors)
{
    triangulationResult_.Clear();
    hull_.Clear();

    SharedTetrahedralMesh badTetrahedrons;
    Polyhedron polyhedron;

    // Add super tetrahedron as the first tetrahedron to the list.
    SharedPtr<SharedVertexTetrahedron> superTetrahedron(ConstructSuperTetrahedron(gravityVectors));
    triangulationResult_.Push(superTetrahedron);

    // Iterate over all gravity vectors, add each as a vertex to the mesh one by one
    for(PODVector<GravityVector*>::ConstIterator gravityVectorsIt = gravityVectors.Begin();
        gravityVectorsIt != gravityVectors.End();
        ++gravityVectorsIt)
    {
        GravityVector* gravityVector = *gravityVectorsIt;

        FindBadTetrahedrons(&badTetrahedrons, gravityVector->GetPosition());
        CreateHullFromTetrahedrons(&polyhedron, badTetrahedrons);
        RemoveTetrahedronsFromTriangulation(badTetrahedrons);
        ReTriangulateGap(polyhedron, *gravityVector);
    }

    CleanUp(superTetrahedron);

    // The mesh is built. We can extract the hull by marking all tetrahedrons
    // in the mesh as "bad" and running it through the face-face comparison
    // code. This will return a list of all triangles that don't touch each
    // other, i.e. the hull.
    CreateHullFromTetrahedrons(&hull_, triangulationResult_);
}

// ----------------------------------------------------------------------------
const GravityMeshBuilder::SharedTetrahedralMesh& GravityMeshBuilder::GetSharedTetrahedralMesh() const
{
    return triangulationResult_;
}

// ----------------------------------------------------------------------------
const GravityMeshBuilder::Polyhedron& GravityMeshBuilder::GetHullMesh() const
{
    return hull_;
}

// ----------------------------------------------------------------------------
void GravityMeshBuilder::FindBadTetrahedrons(
    SharedTetrahedralMesh* badTetrahedrons,
    Vector3 point) const
{
    badTetrahedrons->Clear();

    // Iterate all tetrahedrons in current triangulation and calculate their
    // circumsphere. If the vertex location (point) we are adding is within the
    // sphere, then we add that tetrahedron to the bad list.
    for(SharedTetrahedralMesh::ConstIterator tetrahedron = triangulationResult_.Begin();
        tetrahedron != triangulationResult_.End();
        ++tetrahedron)
    {
        SharedVertexTetrahedron* t = *tetrahedron;

        Vector3 circumsphereCenter = Math::CircumscribeSphere(
            t->v_[0]->position_,
            t->v_[1]->position_,
            t->v_[2]->position_,
            t->v_[3]->position_
        );

        // Test if point is inside circumcircle of tetrahedron. Add to bad list
        float radiusSquared = (circumsphereCenter - t->v_[0]->position_).LengthSquared();
        if((point - circumsphereCenter).LengthSquared() < radiusSquared)
            badTetrahedrons->Push(SharedPtr<SharedVertexTetrahedron>(t));
    }
}

// ----------------------------------------------------------------------------
void GravityMeshBuilder::CreateHullFromTetrahedrons(
    Polyhedron* polyhedron,
    const SharedTetrahedralMesh& tetrahedrons)
{
    polyhedron->Clear();

    // Create a list of faces from the bad tetrahedrons. Note that by default
    // all faces are marked initially.
    unsigned numFaces = tetrahedrons.Size() * 4;
    Face* face = new Face[numFaces];
    SharedTetrahedralMesh::ConstIterator tetrahedron = tetrahedrons.Begin();
    for(unsigned i = 0; tetrahedron != tetrahedrons.End(); ++tetrahedron, i += 4)
    {
        SharedVertexTetrahedron* t = *tetrahedron;
        face[i+0] = Face(t->v_[0], t->v_[1], t->v_[2]);
        face[i+1] = Face(t->v_[3], t->v_[0], t->v_[1]);
        face[i+2] = Face(t->v_[3], t->v_[1], t->v_[2]);
        face[i+3] = Face(t->v_[3], t->v_[2], t->v_[0]);
    }

    // Check each face against all of the other faces, see if they are
    // connected. If they are, unmark them.
    for(unsigned i = 0; i != numFaces; ++i)
        for(unsigned j = i+1; j != numFaces; ++j)
            if(face[i].FaceIsShared(&face[j]))
            {
                face[i].marked_ = false;
                face[j].marked_ = false;
            }

    // The remaining marked faces are the hull of the bad tetrahedrons. Add
    // them to the polyhedron so they can be connected with the new vertex.
    for(unsigned i = 0; i != numFaces; ++i)
        if(face[i].marked_)
        {
            polyhedron->Push(face[i].v_[0]);
            polyhedron->Push(face[i].v_[1]);
            polyhedron->Push(face[i].v_[2]);
        }

    delete[] face;
}

// ----------------------------------------------------------------------------
void GravityMeshBuilder::RemoveTetrahedronsFromTriangulation(
    const GravityMeshBuilder::SharedTetrahedralMesh& tetrahedrons)
{
    for(SharedTetrahedralMesh::ConstIterator tetrahedronIt = tetrahedrons.Begin();
        tetrahedronIt != tetrahedrons.End();
        ++tetrahedronIt)
    {
        triangulationResult_.Remove(*tetrahedronIt);
    }
}

// ----------------------------------------------------------------------------
void GravityMeshBuilder::ReTriangulateGap(const Polyhedron& polyhedron,
                                          const GravityVector& gravityVector)
{

    // Create an internal Vertex object from the gravity vector component.
    SharedPtr<Vertex> connectToVertex(new Vertex(
        gravityVector.GetPosition(),
        gravityVector.GetDirection(),
        gravityVector.GetForceFactor()
    ));

    // Connect all faces in the polyhedron to the new vertex to form new
    // tetrahedrons.
    Polyhedron::ConstIterator vertex = polyhedron.Begin();
    while(vertex != polyhedron.End())
    {
        Vertex* v1 = *vertex++;
        Vertex* v2 = *vertex++;
        Vertex* v3 = *vertex++;
        triangulationResult_.Push(SharedPtr<SharedVertexTetrahedron>(
            new SharedVertexTetrahedron(connectToVertex, v1, v2, v3)
        ));
    }
}

// ----------------------------------------------------------------------------
void GravityMeshBuilder::CleanUp(SharedPtr<SharedVertexTetrahedron> superTetrahedron)
{
    SharedTetrahedralMesh::Iterator tetrahedron = triangulationResult_.Begin();
    while(tetrahedron != triangulationResult_.End())
    {
        SharedVertexTetrahedron* t = *tetrahedron;

        for(int i = 0; i != 4; ++i)
            for(int j = 0; j != 4; ++j)
                if(t->v_[i] == superTetrahedron->v_[j])
                {
                    tetrahedron = triangulationResult_.Erase(tetrahedron);
                    goto break_dont_increment_iterator;
                }

        ++tetrahedron;
        break_dont_increment_iterator: continue;
    }
}

} // namespace Urho3D
