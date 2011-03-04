//
// Urho3D Engine
// Copyright (c) 2008-2011 Lasse Öörni
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#ifndef PHYSICS_COLLISIONSHAPE_H
#define PHYSICS_COLLISIONSHAPE_H

#include "BoundingBox.h"
#include "Quaternion.h"
#include "PhysicsDefs.h"
#include "Resource.h"
#include "SharedPtr.h"
#include "SharedArrayPtr.h"

class Geometry;
class Model;

//! Collision subshape type
enum ShapeType
{
    SHAPE_BOX = 0,
    SHAPE_SPHERE,
    SHAPE_CAPSULE,
    SHAPE_CYLINDER,
    SHAPE_TRIANGLEMESH,
    SHAPE_HEIGHTFIELD
};

//! Base class for collision subshape geometry data
struct CollisionGeometryData : public RefCounted
{
    //! Identifier (model name)
    std::string mID;
    //! Memory use in bytes
    unsigned mMemoryUse;
};

//! Triangle mesh geometry data
struct TriangleMeshData : public CollisionGeometryData
{
    //! Construct from a model
    TriangleMeshData(const Model* model, bool makeConvexHull, float skinWidth, unsigned lodLevel);
    //! Construct by scaling existing geometry data
    TriangleMeshData(const TriangleMeshData* source, const Vector3& scale = Vector3::sUnity);
    //! Destruct. Free geometry data
    ~TriangleMeshData();
    
    //! ODE trimesh geometry ID
    dTriMeshDataID mTriMesh;
    //! Number of vertices
    unsigned mVertexCount;
    //! Number of indices
    unsigned mIndexCount;
    //! Skin width (for convex hulls)
    float mSkinWidth;
    //! Vertex data
    SharedArrayPtr<Vector3> mVertexData;
    //! Index data
    SharedArrayPtr<unsigned> mIndexData;
};

//! Heightfield geometry data
struct HeightfieldData : public CollisionGeometryData
{
    //! Construct from a model
    HeightfieldData(const Model* model, unsigned xPoints, unsigned zPoints, float thickness, unsigned lodLevel);
    //! Construct by scaling existing geometry data
    HeightfieldData(const HeightfieldData* source, const Vector3& scale = Vector3::sUnity);
    //! Destruct. Free geometry data
    ~HeightfieldData();
    
    //! ODE heightfield geometry ID
    dHeightfieldDataID mHeightfield;
    //! Number of points along the X-axis
    unsigned mXPoints;
    //! Number of points along the Z-axis
    unsigned mZPoints;
    //! Thickness below the heightfield
    float mThickness;
    //! Bounding box
    BoundingBox mBoundingBox;
    //! Height values
    SharedArrayPtr<float> mHeightData;
};

//! Collision subshape
struct CollisionSubShape
{
    //! Shape type
    ShapeType mType;
    //! Position offset
    Vector3 mPosition;
    //! Rotation
    Quaternion mRotation;
    //! Bounding box dimensions
    Vector3 mSize;
    //! Geometry data
    SharedPtr<CollisionGeometryData> mGeometryData;
};

//! Physics collision shape resource
class CollisionShape : public Resource
{
    DEFINE_TYPE(CollisionShape);
    
public:
    //! Construct with name
    CollisionShape(const std::string& name = std::string());
    //! Destruct. Free subshapes and clean up unused data from the geometry data cache
    virtual ~CollisionShape();
    
    //! Load resource. Throw exception on error
    virtual void load(Deserializer& source, ResourceCache* cache = 0);
    
    //! Add a sphere subshape
    void addSphere(float radius, const Vector3& position = Vector3::sZero, const Quaternion& rotation = Quaternion::sIdentity);
    //! Add a box subshape
    void addBox(const Vector3& size, const Vector3& position = Vector3::sZero, const Quaternion& rotation = Quaternion::sIdentity);
    //! Add a cylinder subshape
    void addCylinder(float radius, float height, const Vector3& position = Vector3::sZero, const Quaternion& rotation = Quaternion::sIdentity);
    //! Add a capsule subshape
    void addCapsule(float radius, float height, const Vector3& position = Vector3::sZero, const Quaternion& rotation = Quaternion::sIdentity);
    //! Add a trianglemesh subshape
    void addTriangleMesh(const Model* model, unsigned lodLevel = M_MAX_UNSIGNED, const Vector3& position = Vector3::sZero, const Quaternion& rotation = Quaternion::sIdentity);
    //! Add a heightfield subshape
    void addHeightfield(const Model* model, unsigned xPoints, unsigned zPoints, float thickness = 1.0f, unsigned lodLevel = M_MAX_UNSIGNED, const Vector3& position = Vector3::sZero, const Quaternion& rotation = Quaternion::sIdentity);
    //! Add a convex hull subshape (internally an ODE trimesh as well)
    void addConvexHull(const Model* model, float skinWidth = 0.0f, unsigned lodLevel = M_MAX_UNSIGNED, const Vector3& position = Vector3::sZero, const Quaternion& rotation = Quaternion::sIdentity);
    //! Remove all subshapes
    void clear();
    
    //! Create copies of the geometries for a rigid body
    void createGeometries(std::vector<dGeomID>& geoms, std::vector<SharedPtr<CollisionGeometryData> >& geomDatas, dSpaceID space, const Vector3& scale);
    //! Attach geometries to the rigid body
    void setBodyAndTransforms(const std::vector<dGeomID>& geoms, dBodyID body, const Vector3& position, const Quaternion& rotation, const Vector3& scale);
    //! Calculate mass
    void calculateMass(void* dest, const std::vector<dGeomID>& geoms, float density, const Vector3& scale = Vector3::sUnity);
    
    //! Return number of subshapes
    unsigned getNumSubShapes() const { return mSubShapes.size(); }
    //! Return all subshapes
    const std::vector<CollisionSubShape>& getSubShapes() const { return mSubShapes; }
    
    //! Remove unused geometry data from the trimesh and heightfield caches
    static void cleanupCaches();
    
private:
    //! Subshapes
    std::vector<CollisionSubShape> mSubShapes;
    
    //! Cache for trimesh geometries, including scaled copies
    static std::map<std::string, SharedPtr<TriangleMeshData> > sTriangleMeshCache;
    //! Cache for heightfield geometry, including scaled copies
    static std::map<std::string, SharedPtr<HeightfieldData> > sHeightfieldCache;
};

#endif // PHYSICS_COLLISIONSHAPE_H
