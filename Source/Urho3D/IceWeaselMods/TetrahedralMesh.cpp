#include "../IceWeaselMods/TetrahedralMesh.h"
#include "../IceWeaselMods/Tetrahedron.h"
#include "../IceWeaselMods/Math.h"

#include "../Container/Ptr.h"
#include "../Graphics/DebugRenderer.h"
#include "../Math/BoundingBox.h"



namespace Urho3D
{

namespace internal {


class Vertex : public RefCounted
{
public:
    Vertex(const Vector3& position) : position_(position) {}
    Vector3 position_;
};

class Tetrahedron : public RefCounted
{
public:
    Tetrahedron();
    Tetrahedron(Vertex* v1, Vertex* v2, Vertex* v3, Vertex* v4) { Set(v1, v2, v3, v4); }
    void Set(Vertex* v1, Vertex* v2, Vertex* v3, Vertex* v4) {
        v_[0] = v1; v_[1] = v2; v_[2] = v3; v_[3] = v4;
        circumscibedSphereCenter_ = Math::CircumscribeSphere(v1->position_, v2->position_, v3->position_, v4->position_);
    }

    SharedPtr<Vertex> v_[4];
    Vector3 circumscibedSphereCenter_;
};

class Face
{
public:
    Face() {}
    Face(Vertex* v1, Vertex* v2, Vertex* v3) :
        marked_(true)
    { v_[0] = v1; v_[1] = v2; v_[2] = v3; }

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

    Vertex* v_[3];
    bool marked_;
};

} // namespace internal

// ----------------------------------------------------------------------------
static internal::Tetrahedron* ConstructSuperTetrahedron(const Vector<Vector3>& pointList)
{
    // Compute bounding box
    BoundingBox aabb;
    Vector<Vector3>::ConstIterator it = pointList.Begin();
    for(; it != pointList.End(); ++it)
    {
        if(aabb.min_.x_ > it->x_) aabb.min_.x_ = it->x_;
        if(aabb.min_.y_ > it->y_) aabb.min_.y_ = it->y_;
        if(aabb.min_.z_ > it->z_) aabb.min_.z_ = it->z_;
        if(aabb.max_.x_ < it->x_) aabb.max_.x_ = it->x_;
        if(aabb.max_.y_ < it->y_) aabb.max_.y_ = it->y_;
        if(aabb.max_.z_ < it->z_) aabb.max_.z_ = it->z_;
    }

    // Expand bounding box by factor 3 plus a small error margin
    aabb.min_.x_ -= (aabb.max_.x_ - aabb.min_.x_) * 2.2f;
    aabb.min_.y_ -= (aabb.max_.y_ - aabb.min_.y_) * 2.2f;
    aabb.min_.z_ -= (aabb.max_.z_ - aabb.min_.z_) * 2.2f;
    aabb.max_.x_ += Abs(aabb.max_.x_ * 0.1f);
    aabb.max_.y_ += Abs(aabb.max_.y_ * 0.1f);
    aabb.max_.z_ += Abs(aabb.max_.z_ * 0.1f);

    // This tetrahedron should encompass all vertices in the list
    return new internal::Tetrahedron(
        new internal::Vertex(aabb.max_),
        new internal::Vertex(Vector3(aabb.min_.x_, aabb.max_.y_, aabb.max_.z_)),
        new internal::Vertex(Vector3(aabb.max_.x_, aabb.min_.y_, aabb.max_.z_)),
        new internal::Vertex(Vector3(aabb.max_.x_, aabb.max_.y_, aabb.min_.z_))
    );
}

// ----------------------------------------------------------------------------
TetrahedralMesh::TetrahedralMesh(const Vector<Vector3>& pointList)
{
    Build(pointList);
}

// ----------------------------------------------------------------------------
const Tetrahedron* TetrahedralMesh::Query(const Vector3& position, Vector4* barycentric) const
{
    // Use a linear search for now. Can optimise later
    Vector<Tetrahedron>::ConstIterator tetrahedron = tetrahedrons_.Begin();
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
/*!
 * @brief Finds all tetrahedrons who's circumsphere contains a point.
 * @param[out] badTetrahedrons All tetrahedrons containing the point will be
 * stored in this list.
 * @param[in] triangulationResult The current state of the triangulation.
 * @param[in] point The 3D point to test for.
 */
static void FindBadTetrahedrons(Vector<SharedPtr<internal::Tetrahedron> >* badTetrahedrons,
                                const Vector<SharedPtr<internal::Tetrahedron> >& triangulationResult,
                                Vector3 point)
{
    badTetrahedrons->Clear();

    Vector<SharedPtr<internal::Tetrahedron> >::ConstIterator tetrahedron = triangulationResult.Begin();
    for(; tetrahedron != triangulationResult.End(); ++tetrahedron)
    {
        internal::Tetrahedron* t = *tetrahedron;

        Vector3 circumsphereCenter = Math::CircumscribeSphere(
            t->v_[0]->position_,
            t->v_[1]->position_,
            t->v_[2]->position_,
            t->v_[3]->position_
        );
        float radiusSquared = (circumsphereCenter - t->v_[0]->position_).LengthSquared();

        // Test if point is inside circumcircle of tetrahedron. Add to bad list
        if((point - circumsphereCenter).LengthSquared() < radiusSquared)
            badTetrahedrons->Push(SharedPtr<internal::Tetrahedron>(t));

        /* Tests if a point is inside a tetrahedron
        if(Urho3D::Tetrahedron(t->v_[0]->position_,
                                t->v_[1]->position_,
                                t->v_[2]->position_,
                                t->v_[3]->position_).PointLiesInside(*vertIt))
            badTetrahedrons.Push(SharedPtr<internal::Tetrahedron>(t));*/
    }
}

// ----------------------------------------------------------------------------
static void CreatePolyhedronFromBadTetrahedrons(Vector<internal::Vertex*>* polyhedron,
                                                const Vector<SharedPtr<internal::Tetrahedron> >& badTetrahedrons)
{
    polyhedron->Clear();

    // Create a list of faces from the bad tetrahedrons. Note that by default
    // all faces are marked initially.
    unsigned numFaces = badTetrahedrons.Size() * 4;
    internal::Face* face = new internal::Face[numFaces];
    Vector<SharedPtr<internal::Tetrahedron> >::ConstIterator tetrahedron = badTetrahedrons.Begin();
    for(unsigned i = 0; tetrahedron != badTetrahedrons.End(); ++tetrahedron, i += 4)
    {
        internal::Tetrahedron* t = *tetrahedron;
        face[i+0] = internal::Face(t->v_[0], t->v_[1], t->v_[2]);
        face[i+1] = internal::Face(t->v_[3], t->v_[0], t->v_[1]);
        face[i+2] = internal::Face(t->v_[3], t->v_[1], t->v_[2]);
        face[i+3] = internal::Face(t->v_[3], t->v_[2], t->v_[0]);
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
void TetrahedralMesh::Build(const Vector<Vector3>& pointList)
{
    tetrahedrons_.Clear();

    // Create triangulation list and add super tetrahedron to it.
    Vector<SharedPtr<internal::Tetrahedron> > triangulationResult;
    SharedPtr<internal::Tetrahedron> superTetrahedron(ConstructSuperTetrahedron(pointList));
    triangulationResult.Push(superTetrahedron);

    Vector<SharedPtr<internal::Tetrahedron> > badTetrahedrons;
    Vector<internal::Vertex*> polyhedron;

    Vector<Vector3>::ConstIterator point = pointList.Begin();
    for(; point != pointList.End(); ++point)
    {
        // First find all tetrahedrons that are no longer valid due to the insertion
        FindBadTetrahedrons(&badTetrahedrons, triangulationResult, *point);

        // Find the boundary of the hole
        CreatePolyhedronFromBadTetrahedrons(&polyhedron, badTetrahedrons);

        // Remove bad tetrahedrons from triangulation
        Vector<SharedPtr<internal::Tetrahedron> >::ConstIterator tetrahedron = badTetrahedrons.Begin();
        for(; tetrahedron != badTetrahedrons.End(); ++tetrahedron)
        {
            triangulationResult.Remove(*tetrahedron);
        }

        // Re-triangulate the hole
        Vector<internal::Vertex*>::Iterator vertex = polyhedron.Begin();
        SharedPtr<internal::Vertex> connectToVertex(new internal::Vertex(*point));
        while(vertex != polyhedron.End())
        {
            internal::Vertex* v1 = *vertex++;
            internal::Vertex* v2 = *vertex++;
            internal::Vertex* v3 = *vertex++;
            triangulationResult.Push(SharedPtr<internal::Tetrahedron>(
                new internal::Tetrahedron(connectToVertex, v1, v2, v3)
            ));
        }
    }

    Vector<SharedPtr<internal::Tetrahedron> >::ConstIterator tetIt = triangulationResult.Begin();
    for(; tetIt != triangulationResult.End(); ++tetIt)
    {
        internal::Tetrahedron* t = *tetIt;

        for(int i = 0; i != 4; ++i)
            for(int j = 0; j != 4; ++j)
                if(t->v_[i] == superTetrahedron->v_[j])
                    goto break_skip;

        tetrahedrons_.Push(Tetrahedron(
            t->v_[0]->position_,
            t->v_[1]->position_,
            t->v_[2]->position_,
            t->v_[3]->position_
        ));

        break_skip: continue;
    }
}

// ----------------------------------------------------------------------------
void TetrahedralMesh::DrawDebugGeometry(DebugRenderer* debug, bool depthTest, Vector3 pos)
{
    Vector<Tetrahedron>::Iterator it = tetrahedrons_.Begin();
    unsigned count = 0;
    for(; it != tetrahedrons_.End(); ++it)
        if(it->PointLiesInside(pos))
        {
            it->DrawDebugGeometry(debug, false, Color::RED);
            ++count;
        }
        else
            it->DrawDebugGeometry(debug, depthTest, Color::WHITE);

    assert(count < 2); // Detects overlapping tetrahedrons (should never happen)
}

} // namespace Urho3D
