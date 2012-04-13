//
// Urho3D Engine
// Copyright (c) 2008-2012 Lasse Öörni
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

#include "Precompiled.h"
#include "CollisionShape.h"
#include "Context.h"
#include "DebugRenderer.h"
#include "Geometry.h"
#include "Log.h"
#include "Model.h"
#include "PhysicsUtils.h"
#include "PhysicsWorld.h"
#include "Profiler.h"
#include "ResourceCache.h"
#include "RigidBody.h"
#include "Scene.h"

#include <BulletCollision/CollisionShapes/btBoxShape.h>
#include <BulletCollision/CollisionShapes/btCapsuleShape.h>
#include <BulletCollision/CollisionShapes/btCompoundShape.h>
#include <BulletCollision/CollisionShapes/btConeShape.h>
#include <BulletCollision/CollisionShapes/btConvexHullShape.h>
#include <BulletCollision/CollisionShapes/btCylinderShape.h>
#include <BulletCollision/CollisionShapes/btHeightfieldTerrainShape.h>
#include <BulletCollision/CollisionShapes/btScaledBvhTriangleMeshShape.h>
#include <BulletCollision/CollisionShapes/btSphereShape.h>
#include <BulletCollision/CollisionShapes/btTriangleMesh.h>
#include <BulletDynamics/Dynamics/btDiscreteDynamicsWorld.h>
#include <hull.h>

static const String typeNames[] = 
{
    "Box",
    "Sphere",
    "Cylinder",
    "Capsule",
    "Cone",
    "TriangleMesh",
    "ConvexHull",
    "Heightfield",
    ""
};

TriangleMeshData::TriangleMeshData(Model* model, unsigned lodLevel) :
    meshData_(0),
    shape_(0)
{
    modelName_ = model->GetName();
    meshData_ = new btTriangleMesh();
    const Vector<Vector<SharedPtr<Geometry> > >& geometries = model->GetGeometries();
    
    for (unsigned i = 0; i < geometries.Size(); ++i)
    {
        unsigned subGeometryLodLevel = lodLevel;
        if (subGeometryLodLevel >= geometries[i].Size())
            subGeometryLodLevel = geometries[i].Size() - 1;
        
        Geometry* geom = geometries[i][subGeometryLodLevel];
        if (!geom)
            continue;
        
        const unsigned char* vertexData;
        const unsigned char* indexData;
        unsigned vertexSize;
        unsigned indexSize;
        
        geom->GetRawData(vertexData, vertexSize, indexData, indexSize);
        if (!vertexData || !indexData)
            continue;
        
        unsigned indexStart = geom->GetIndexStart();
        unsigned indexCount = geom->GetIndexCount();
        
        // 16-bit indices
        if (indexSize == sizeof(unsigned short))
        {
            const unsigned short* indices = (const unsigned short*)indexData;
            
            for (unsigned j = indexStart; j < indexStart + indexCount; j += 3)
            {
                const Vector3& v0 = *((const Vector3*)(&vertexData[indices[j] * vertexSize]));
                const Vector3& v1 = *((const Vector3*)(&vertexData[indices[j + 1] * vertexSize]));
                const Vector3& v2 = *((const Vector3*)(&vertexData[indices[j + 2] * vertexSize]));
                meshData_->addTriangle(ToBtVector3(v0), ToBtVector3(v1), ToBtVector3(v2), true);
            }
        }
        // 32-bit indices
        else
        {
            const unsigned* indices = (const unsigned*)indexData;
            
            for (unsigned j = indexStart; j < indexStart + indexCount; j += 3)
            {
                const Vector3& v0 = *((const Vector3*)(&vertexData[indices[j] * vertexSize]));
                const Vector3& v1 = *((const Vector3*)(&vertexData[indices[j + 1] * vertexSize]));
                const Vector3& v2 = *((const Vector3*)(&vertexData[indices[j + 2] * vertexSize]));
                meshData_->addTriangle(ToBtVector3(v0), ToBtVector3(v1), ToBtVector3(v2), true);
            }
        }
    }
    
    shape_ = new btBvhTriangleMeshShape(meshData_, true, true);
}

TriangleMeshData::~TriangleMeshData()
{
    delete shape_;
    shape_ = 0;
    
    delete meshData_;
    meshData_ = 0;
}

ConvexData::ConvexData(Model* model, unsigned lodLevel, float thickness)
{
    modelName_ = model->GetName();
    const Vector<Vector<SharedPtr<Geometry> > >& geometries = model->GetGeometries();
    
    PODVector<Vector3> originalVertices;
    
    for (unsigned i = 0; i < geometries.Size(); ++i)
    {
        unsigned subGeometryLodLevel = lodLevel;
        if (subGeometryLodLevel >= geometries[i].Size())
            subGeometryLodLevel = geometries[i].Size() - 1;
        
        Geometry* geom = geometries[i][subGeometryLodLevel];
        if (!geom)
            continue;
        
        const unsigned char* vertexData;
        const unsigned char* indexData;
        unsigned vertexSize;
        unsigned indexSize;
        
        geom->GetRawData(vertexData, vertexSize, indexData, indexSize);
        if (!vertexData || !indexData)
            continue;
        
        unsigned vertexStart = geom->GetVertexStart();
        unsigned vertexCount = geom->GetVertexCount();
        
        // Copy vertex data
        for (unsigned j = 0; j < vertexCount; ++j)
        {
            const Vector3& v = *((const Vector3*)(&vertexData[(vertexStart + j) * vertexSize]));
            originalVertices.Push(v);
        }
    }
    
    if (originalVertices.Size())
    {
        // Build the convex hull from the raw geometry
        StanHull::HullDesc desc;
        desc.SetHullFlag(StanHull::QF_TRIANGLES);
        desc.mVcount = originalVertices.Size();
        desc.mVertices = originalVertices[0].Data();
        desc.mVertexStride = 3 * sizeof(float);
        desc.mSkinWidth = thickness;
        
        StanHull::HullLibrary lib;
        StanHull::HullResult result;
        lib.CreateConvexHull(desc, result);
        
        vertexCount_ = result.mNumOutputVertices;
        vertexData_ = new Vector3[vertexCount_];
        // Copy vertex data
        memcpy(vertexData_.Get(), result.mOutputVertices, vertexCount_ * sizeof(Vector3));
        
        lib.ReleaseResult(result);
    }
    else
        vertexCount_ = 0;
}

ConvexData::~ConvexData()
{
}

HeightfieldData::HeightfieldData(Model* model, unsigned lodLevel, IntVector2 numPoints)
{
    modelName_ = model->GetName();
    
    const Vector<Vector<SharedPtr<Geometry> > >& geometries = model->GetGeometries();
    
    if (!geometries.Size())
        return;
    
    lodLevel = Clamp(lodLevel, 0, geometries[0].Size());
    
    Geometry* geom = geometries[0][lodLevel];
    if (!geom)
        return;
    
    const unsigned char* vertexData;
    const unsigned char* indexData;
    unsigned vertexSize;
    unsigned indexSize;
    
    geom->GetRawData(vertexData, vertexSize, indexData, indexSize);
    if (!vertexData || !indexData)
        return;
    
    unsigned indexStart = geom->GetIndexStart();
    unsigned indexCount = geom->GetIndexCount();
    
    // If X & Z size not specified, try to guess them
    if (numPoints == IntVector2::ZERO)
        numPoints.x_ = numPoints.y_ = (int)sqrtf((float)geom->GetVertexCount());
    else
    {
        numPoints.x_ = Max(numPoints.x_, 2);
        numPoints.y_ = Max(numPoints.y_, 2);
    }
    
    unsigned dataSize = numPoints.x_ * numPoints.y_;
    numPoints_ = numPoints;
    
    // Then allocate the heightfield
    BoundingBox box = model->GetBoundingBox();
    heightData_ = new float[dataSize];
    
    // Calculate spacing from model's bounding box
    xSpacing_ = (box.max_.x_ - box.min_.x_) / (numPoints.x_ - 1);
    zSpacing_ = (box.max_.z_ - box.min_.z_) / (numPoints.y_ - 1);
    
    // Initialize the heightfield with minimum height
    for (unsigned i = 0; i < dataSize; ++i)
        heightData_[i] = box.min_.y_;
    
    unsigned vertexStart = geom->GetVertexStart();
    unsigned vertexCount = geom->GetVertexCount();
    
    // Now go through vertex data and fit the vertices into the heightfield
    for (unsigned i = vertexStart; i < vertexStart + vertexCount; ++i)
    {
        const Vector3& vertex = *((const Vector3*)(&vertexData[i * vertexSize]));
        int x = (int)((vertex.x_ - box.min_.x_) / xSpacing_ + 0.25f);
        int z = (int)((vertex.z_ - box.min_.z_) / zSpacing_ + 0.25f);
        if (x >= numPoints.x_)
            x = numPoints.x_ - 1;
        if (z >= numPoints.y_)
            z = numPoints.y_ - 1;
        if (vertex.y_ > heightData_[z * numPoints.x_ + x])
            heightData_[z * numPoints.x_ + x] = vertex.y_;
    }
}

HeightfieldData::~HeightfieldData()
{
}

OBJECTTYPESTATIC(CollisionShape);

CollisionShape::CollisionShape(Context* context) :
    Component(context),
    shape_(0),
    shapeType_(SHAPE_BOX),
    position_(Vector3::ZERO),
    rotation_(Quaternion::IDENTITY),
    size_(Vector3::ONE),
    lodLevel_(0),
    thickness_(0.0f),
    numPoints_(IntVector2::ZERO),
    cachedWorldScale_(Vector3::ONE),
    dirty_(false),
    flipEdges_(false)
{
}

CollisionShape::~CollisionShape()
{
    ReleaseShape();
    
    if (physicsWorld_)
        physicsWorld_->RemoveCollisionShape(this);
}

void CollisionShape::RegisterObject(Context* context)
{
    context->RegisterFactory<CollisionShape>();
    
    ENUM_ATTRIBUTE(CollisionShape, "Shape Type", shapeType_, typeNames, SHAPE_BOX, AM_DEFAULT);
    ATTRIBUTE(CollisionShape, VAR_VECTOR3, "Size", size_, Vector3::ONE, AM_DEFAULT);
    ATTRIBUTE(CollisionShape, VAR_VECTOR3, "Offset Position", position_, Vector3::ZERO, AM_DEFAULT);
    ATTRIBUTE(CollisionShape, VAR_QUATERNION, "Offset Rotation", rotation_, Quaternion::IDENTITY, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(CollisionShape, VAR_RESOURCEREF, "Model", GetModelAttr, SetModelAttr, ResourceRef, ResourceRef(Model::GetTypeStatic()), AM_DEFAULT);
    ATTRIBUTE(CollisionShape, VAR_INT, "LOD Level", lodLevel_, 0, AM_DEFAULT);
    ATTRIBUTE(CollisionShape, VAR_FLOAT, "Hull Thickness", thickness_, 0.0f, AM_DEFAULT);
    ATTRIBUTE(CollisionShape, VAR_INT, "Heightfield Points X", numPoints_.x_, 0, AM_DEFAULT);
    ATTRIBUTE(CollisionShape, VAR_INT, "Heightfield Points Z", numPoints_.y_, 0, AM_DEFAULT);
    ATTRIBUTE(CollisionShape, VAR_BOOL, "Heightfield Flip Edges", flipEdges_, false, AM_DEFAULT);
}

void CollisionShape::OnSetAttribute(const AttributeInfo& attr, const Variant& src)
{
    Serializable::OnSetAttribute(attr, src);
    dirty_ = true;
}

void CollisionShape::ApplyAttributes()
{
    if (dirty_)
    {
        UpdateShape();
        NotifyRigidBody();
        dirty_ = false;
    }
}

void CollisionShape::SetBox(const Vector3& size, const Vector3& position, const Quaternion& rotation)
{
    shapeType_ = SHAPE_BOX;
    size_ = size;
    position_ = position;
    rotation_ = rotation;
    model_.Reset();
    
    UpdateShape();
    NotifyRigidBody();
}

void CollisionShape::SetSphere(float diameter, const Vector3& position, const Quaternion& rotation)
{
    shapeType_ = SHAPE_SPHERE;
    size_ = Vector3(diameter, diameter, diameter);
    position_ = position;
    rotation_ = rotation;
    model_.Reset();
    
    UpdateShape();
    NotifyRigidBody();
}

void CollisionShape::SetCylinder(float diameter, float height, const Vector3& position, const Quaternion& rotation)
{
    shapeType_ = SHAPE_CYLINDER;
    size_ = Vector3(diameter, height, diameter);
    position_ = position;
    rotation_ = rotation;
    model_.Reset();
    
    UpdateShape();
    NotifyRigidBody();
}

void CollisionShape::SetCapsule(float diameter, float height, const Vector3& position, const Quaternion& rotation)
{
    shapeType_ = SHAPE_CAPSULE;
    size_ = Vector3(diameter, height, diameter);
    position_ = position;
    rotation_ = rotation;
    model_.Reset();
    
    UpdateShape();
    NotifyRigidBody();
}

void CollisionShape::SetCone(float diameter, float height, const Vector3& position, const Quaternion& rotation)
{
    shapeType_ = SHAPE_CONE;
    size_ = Vector3(diameter, height, diameter);
    position_ = position;
    rotation_ = rotation;
    model_.Reset();
    
    UpdateShape();
    NotifyRigidBody();
}

void CollisionShape::SetTriangleMesh(Model* model, unsigned lodLevel, const Vector3& size, const Vector3& position, const Quaternion& rotation)
{
    if (!model)
    {
        LOGERROR("Null model, can not set triangle mesh");
        return;
    }
    
    shapeType_ = SHAPE_TRIANGLEMESH;
    model_ = model;
    lodLevel_ = lodLevel;
    size_ = size.Abs();
    position_ = position;
    rotation_ = rotation;
    
    UpdateShape();
    NotifyRigidBody();
}

void CollisionShape::SetConvexHull(Model* model, unsigned lodLevel, float thickness, const Vector3& size, const Vector3& position, const Quaternion& rotation)
{
    if (!model)
    {
        LOGERROR("Null model, can not set convex hull");
        return;
    }
    
    shapeType_ = SHAPE_CONVEXHULL;
    model_ = model;
    lodLevel_ = lodLevel;
    thickness_ = thickness;
    size_ = size.Abs();
    position_ = position;
    rotation_ = rotation;
    
    UpdateShape();
    NotifyRigidBody();
}

void CollisionShape::SetHeightfield(Model* model, unsigned lodLevel, unsigned xPoints, unsigned zPoints, const Vector3& size, const Vector3& position, const Quaternion& rotation)
{
    if (!model)
    {
        LOGERROR("Null model, can not set heightfield");
        return;
    }
    
    shapeType_ = SHAPE_HEIGHTFIELD;
    model_ = model;
    lodLevel_ = lodLevel;
    numPoints_ = IntVector2(xPoints, zPoints);
    size_ = size.Abs();
    position_ = position;
    rotation_ = rotation;
    
    UpdateShape();
    NotifyRigidBody();
}

void CollisionShape::SetShapeType(ShapeType type)
{
    if (type != shapeType_)
    {
        shapeType_ = type;
        UpdateShape();
        NotifyRigidBody();
    }
}

void CollisionShape::SetSize(const Vector3& size)
{
    if (size != size_)
    {
        size_ = size;
        UpdateShape();
        NotifyRigidBody();
    }
}

void CollisionShape::SetPosition(const Vector3& position)
{
    if (position != position_)
    {
        position_ = position;
        NotifyRigidBody();
    }
}

void CollisionShape::SetRotation(const Quaternion& rotation)
{
    if (rotation != rotation_)
    {
        rotation_ = rotation;
        NotifyRigidBody();
    }
}

void CollisionShape::SetTransform(const Vector3& position, const Quaternion& rotation)
{
    if (position != position_ || rotation != rotation_)
    {
        position_ = position;
        rotation_ = rotation;
        NotifyRigidBody();
    }
}

void CollisionShape::SetModel(Model* model)
{
    if (model != model_)
    {
        model_ = model;
        if (shapeType_ >= SHAPE_TRIANGLEMESH)
        {
            UpdateShape();
            NotifyRigidBody();
        }
    }
}

void CollisionShape::SetLodLevel(unsigned lodLevel)
{
    if (lodLevel != lodLevel_)
    {
        lodLevel_ = lodLevel;
        if (shapeType_ >= SHAPE_TRIANGLEMESH)
        {
            UpdateShape();
            NotifyRigidBody();
        }
    }
}

void CollisionShape::SetThickness(float thickness)
{
    thickness = Max(thickness, 0.0f);
    
    if (thickness != thickness_)
    {
        thickness_ = thickness;
        if (shapeType_ == SHAPE_CONVEXHULL)
        {
            UpdateShape();
            NotifyRigidBody();
        }
    }
}

void CollisionShape::SetNumPoints(const IntVector2& numPoints)
{
    if (numPoints != numPoints_)
    {
        numPoints_ = numPoints;
        if (shapeType_ == SHAPE_HEIGHTFIELD)
        {
            UpdateShape();
            NotifyRigidBody();
        }
    }
}

void CollisionShape::SetFlipEdges(bool enable)
{
    if (enable != flipEdges_)
    {
        flipEdges_ = enable;
        if (shapeType_ == SHAPE_HEIGHTFIELD)
        {
            UpdateShape();
            NotifyRigidBody();
        }
    }
}

void CollisionShape::NotifyRigidBody()
{
    btCompoundShape* compound = GetParentCompoundShape();
    if (node_ && shape_ && compound)
    {
        // Remove the shape first to ensure it is not added twice
        compound->removeChildShape(shape_);
        
        // Then add with updated offset
        btTransform offset;
        offset.setOrigin(ToBtVector3(node_->GetWorldScale() * position_));
        offset.setRotation(ToBtQuaternion(rotation_));
        compound->addChildShape(offset, shape_);
        
        // Finally tell the rigid body to update its mass
        rigidBody_->UpdateMass();
    }
}

void CollisionShape::DrawDebugGeometry(DebugRenderer* debug, bool depthTest)
{
    if (debug && physicsWorld_ && shape_ && node_)
    {
        physicsWorld_->SetDebugRenderer(debug);
        physicsWorld_->SetDebugDepthTest(depthTest);
        
        // Use the rigid body's world transform if possible, as it may be different from the rendering transform
        Matrix3x4 worldTransform;
        RigidBody* body = GetComponent<RigidBody>();
        if (body)
            worldTransform = Matrix3x4(body->GetPosition(), body->GetRotation(), node_->GetWorldScale());
        else
            worldTransform = node_->GetWorldTransform();
        Vector3 worldPosition = worldTransform * position_;
        Quaternion worldRotation = worldTransform.Rotation() * rotation_;
        
        btDiscreteDynamicsWorld* world = physicsWorld_->GetWorld();
        world->debugDrawObject(btTransform(ToBtQuaternion(worldRotation), ToBtVector3(worldPosition)), shape_, btVector3(0.0f,
            1.0f, 0.0f));
        
        physicsWorld_->SetDebugRenderer(0);
    }
}

void CollisionShape::SetModelAttr(ResourceRef value)
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    model_ = cache->GetResource<Model>(value.id_);
    dirty_ = true;
}

ResourceRef CollisionShape::GetModelAttr() const
{
    return GetResourceRef(model_, Model::GetTypeStatic());
}

void CollisionShape::OnNodeSet(Node* node)
{
    if (node)
    {
        Scene* scene = node->GetScene();
        if (scene)
        {
            physicsWorld_ = scene->GetComponent<PhysicsWorld>();
            if (physicsWorld_)
                physicsWorld_->AddCollisionShape(this);
        }
        node->AddListener(this);
        UpdateShape();
        NotifyRigidBody();
    }
}

void CollisionShape::OnMarkedDirty(Node* node)
{
    Vector3 newWorldScale = node_->GetWorldScale();
    if (newWorldScale != cachedWorldScale_ && shape_)
    {
        switch (shapeType_)
        {
        case SHAPE_BOX:
        case SHAPE_SPHERE:
        case SHAPE_CYLINDER:
        case SHAPE_CAPSULE:
        case SHAPE_CONE:
            shape_->setLocalScaling(ToBtVector3(newWorldScale));
            break;
        
        case SHAPE_TRIANGLEMESH:
        case SHAPE_CONVEXHULL:
            shape_->setLocalScaling(ToBtVector3(newWorldScale * size_));
            break;
            
        case SHAPE_HEIGHTFIELD:
            if (geometry_)
            {
                HeightfieldData* heightfield = static_cast<HeightfieldData*>(geometry_.Get());
                shape_->setLocalScaling(ToBtVector3(newWorldScale * Vector3(heightfield->xSpacing_, 1.0f, heightfield->zSpacing_)
                    * size_));
            }
            break;
        }
        
        NotifyRigidBody();
        
        cachedWorldScale_ = newWorldScale;
    }
}

btCompoundShape* CollisionShape::GetParentCompoundShape()
{
    if (!rigidBody_)
        rigidBody_ = GetComponent<RigidBody>();
    
    return rigidBody_ ? rigidBody_->GetCompoundShape() : 0;
}

void CollisionShape::UpdateShape()
{
    PROFILE(UpdateCollisionShape);
    
    ReleaseShape();
    
    if (!physicsWorld_)
        return;
    
    if (node_)
    {
        Vector3 newWorldScale = node_->GetWorldScale();
        
        switch (shapeType_)
        {
        case SHAPE_BOX:
            shape_ = new btBoxShape(ToBtVector3(size_ * 0.5f));
            shape_->setLocalScaling(ToBtVector3(newWorldScale));
            break;
            
        case SHAPE_SPHERE:
            shape_ = new btSphereShape(size_.x_ * 0.5f);
            shape_->setLocalScaling(ToBtVector3(newWorldScale));
            break;
            
        case SHAPE_CYLINDER:
            shape_ = new btCylinderShape(btVector3(size_.x_ * 0.5f, size_.y_ * 0.5f, size_.x_ * 0.5f));
            shape_->setLocalScaling(ToBtVector3(newWorldScale));
            break;
            
        case SHAPE_CAPSULE:
            shape_ = new btCapsuleShape(size_.x_ * 0.5f, Max(size_.y_  - size_.x_, 0.0f));
            shape_->setLocalScaling(ToBtVector3(newWorldScale));
            break;
            
        case SHAPE_CONE:
            shape_ = new btConeShape(size_.x_ * 0.5f, size_.y_);
            shape_->setLocalScaling(ToBtVector3(newWorldScale));
            break;
            
        case SHAPE_TRIANGLEMESH:
            if (model_)
            {
                // Check the geometry cache
                String id = "TriMesh_" + model_->GetName() + "_" + String(lodLevel_);
                
                Map<String, SharedPtr<CollisionGeometryData> >& cache = physicsWorld_->GetGeometryCache();
                Map<String, SharedPtr<CollisionGeometryData> >::Iterator j = cache.Find(id);
                if (j != cache.End())
                    geometry_ = j->second_;
                else
                {
                    geometry_ = new TriangleMeshData(model_, lodLevel_);
                    cache[id] = geometry_;
                }
                
                TriangleMeshData* triMesh = static_cast<TriangleMeshData*>(geometry_.Get());
                shape_ = new btScaledBvhTriangleMeshShape(triMesh->shape_, ToBtVector3(newWorldScale * size_));
            }
            break;
            
        case SHAPE_CONVEXHULL:
            if (model_)
            {
                // Check the geometry cache
                String id = "Convex_" + model_->GetName() + "_" + String(lodLevel_) + "_" + String(thickness_);
                
                Map<String, SharedPtr<CollisionGeometryData> >& cache = physicsWorld_->GetGeometryCache();
                Map<String, SharedPtr<CollisionGeometryData> >::Iterator j = cache.Find(id);
                if (j != cache.End())
                    geometry_ = j->second_;
                else
                {
                    geometry_ = new ConvexData(model_, lodLevel_, thickness_);
                    cache[id] = geometry_;
                }
                
                ConvexData* convex = static_cast<ConvexData*>(geometry_.Get());
                shape_ = new btConvexHullShape((btScalar*)convex->vertexData_.Get(), convex->vertexCount_, sizeof(Vector3));
                shape_->setLocalScaling(ToBtVector3(newWorldScale * size_));
            }
            break;
            
        case SHAPE_HEIGHTFIELD:
            if (model_)
            {
                // Check the geometry cache
                String id = "Heightfield_" + model_->GetName() + "_" + String(lodLevel_) + String(numPoints_) + "_" + 
                    String(flipEdges_);
                
                Map<String, SharedPtr<CollisionGeometryData> >& cache = physicsWorld_->GetGeometryCache();
                Map<String, SharedPtr<CollisionGeometryData> >::Iterator j = cache.Find(id);
                if (j != cache.End())
                    geometry_ = j->second_;
                else
                {
                    geometry_ = new HeightfieldData(model_, lodLevel_, numPoints_);
                    cache[id] = geometry_;
                }
                
                HeightfieldData* heightfield = static_cast<HeightfieldData*>(geometry_.Get());
                shape_ = new btHeightfieldTerrainShape(heightfield->numPoints_.x_, heightfield->numPoints_.y_,
                    heightfield->heightData_.Get(), 1.0f, heightfield->boundingBox_.min_.y_, heightfield->boundingBox_.max_.y_, 1,
                    PHY_FLOAT, flipEdges_);
                shape_->setLocalScaling(ToBtVector3(newWorldScale * Vector3(heightfield->xSpacing_, 1.0f,
                    heightfield->zSpacing_) * size_));
            }
            break;
        }
        
        cachedWorldScale_ = newWorldScale;
    }
    
    if (physicsWorld_)
        physicsWorld_->CleanupGeometryCache();
}

void CollisionShape::ReleaseShape()
{
    btCompoundShape* compound = GetParentCompoundShape();
    if (shape_ && compound)
    {
        compound->removeChildShape(shape_);
        rigidBody_->UpdateMass();
    }
    
    delete shape_;
    shape_ = 0;
    
    geometry_.Reset();
    
    if (physicsWorld_)
        physicsWorld_->CleanupGeometryCache();
}
