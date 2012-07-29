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
#include "DrawableEvents.h"
#include "Geometry.h"
#include "Log.h"
#include "Model.h"
#include "PhysicsUtils.h"
#include "PhysicsWorld.h"
#include "Profiler.h"
#include "ResourceCache.h"
#include "RigidBody.h"
#include "Scene.h"
#include "Terrain.h"

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

static const float DEFAULT_COLLISION_MARGIN = 0.04f;

static const char* typeNames[] = 
{
    "Box",
    "Sphere",
    "Cylinder",
    "Capsule",
    "Cone",
    "TriangleMesh",
    "ConvexHull",
    "Terrain",
    0
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
        {
            WriteToLog(model->GetContext(), LOG_WARNING, "Skipping null geometry for triangle mesh collision");
            continue;
        }
        
        const unsigned char* vertexData;
        const unsigned char* indexData;
        unsigned vertexSize;
        unsigned indexSize;
        unsigned elementMask;
        
        geom->GetRawData(vertexData, vertexSize, indexData, indexSize, elementMask);
        if (!vertexData || !indexData)
        {
            WriteToLog(model->GetContext(), LOG_WARNING, "Skipping geometry with no CPU-side geometry data for triangle mesh collision");
            continue;
        }
        
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

ConvexData::ConvexData(Model* model, unsigned lodLevel)
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
        {
            WriteToLog(model->GetContext(), LOG_WARNING, "Skipping null geometry for convex hull collision");
            continue;
        };
        
        const unsigned char* vertexData;
        const unsigned char* indexData;
        unsigned vertexSize;
        unsigned indexSize;
        unsigned elementMask;
        
        geom->GetRawData(vertexData, vertexSize, indexData, indexSize, elementMask);
        if (!vertexData || !indexData)
        {
            WriteToLog(model->GetContext(), LOG_WARNING, "Skipping geometry with no CPU-side geometry data for convex hull collision");
            continue;
        }
        
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
        desc.mSkinWidth = 0.0f;
        
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

HeightfieldData::HeightfieldData(Terrain* terrain) :
    heightData_(terrain->GetHeightData()),
    spacing_(terrain->GetSpacing()),
    size_(terrain->GetNumVertices()),
    minHeight_(0.0f),
    maxHeight_(0.0f)
{
    if (heightData_)
    {
        unsigned points = size_.x_ * size_.y_;
        float* data = heightData_.Get();
        
        for (unsigned i = 0; i < points; ++i)
        {
            if (!i)
                minHeight_ = maxHeight_ = data[i];
            else
            {
                minHeight_ = Min(minHeight_, data[i]);
                maxHeight_ = Max(maxHeight_, data[i]);
            }
        }
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
    cachedWorldScale_(Vector3::ONE),
    lodLevel_(0),
    margin_(DEFAULT_COLLISION_MARGIN),
    recreateShape_(false)
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
    REF_ACCESSOR_ATTRIBUTE(CollisionShape, VAR_VECTOR3, "Offset Position", GetPosition, SetPosition, Vector3, Vector3::ZERO, AM_DEFAULT);
    REF_ACCESSOR_ATTRIBUTE(CollisionShape, VAR_QUATERNION, "Offset Rotation", GetRotation, SetRotation, Quaternion, Quaternion::IDENTITY, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(CollisionShape, VAR_RESOURCEREF, "Model", GetModelAttr, SetModelAttr, ResourceRef, ResourceRef(Model::GetTypeStatic()), AM_DEFAULT);
    ATTRIBUTE(CollisionShape, VAR_INT, "LOD Level", lodLevel_, 0, AM_DEFAULT);
    ATTRIBUTE(CollisionShape, VAR_FLOAT, "Collision Margin", margin_, DEFAULT_COLLISION_MARGIN, AM_DEFAULT);
}

void CollisionShape::OnSetAttribute(const AttributeInfo& attr, const Variant& src)
{
    Component::OnSetAttribute(attr, src);
    
    // Change of any non-accessor attribute requires recreation of the collision shape
    if (!attr.accessor_)
        recreateShape_ = true;
}

void CollisionShape::ApplyAttributes()
{
    if (recreateShape_)
    {
        UpdateShape();
        NotifyRigidBody();
        recreateShape_ = false;
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
        
        Vector3 position = position_;
        // For terrains, undo the height centering performed automatically by Bullet
        if (shapeType_ == SHAPE_TERRAIN && geometry_)
        {
            HeightfieldData* heightfield = static_cast<HeightfieldData*>(geometry_.Get());
            position.y_ += (heightfield->minHeight_ + heightfield->maxHeight_) * 0.5f;
        }
        
        Vector3 worldPosition = worldTransform * position;
        Quaternion worldRotation = worldTransform.Rotation() * rotation_;
        
        btDiscreteDynamicsWorld* world = physicsWorld_->GetWorld();
        world->debugDrawObject(btTransform(ToBtQuaternion(worldRotation), ToBtVector3(worldPosition)), shape_, btVector3(0.0f,
            1.0f, 0.0f));
        
        physicsWorld_->SetDebugRenderer(0);
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
    MarkNetworkUpdate();
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
    MarkNetworkUpdate();
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
    MarkNetworkUpdate();
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
    MarkNetworkUpdate();
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
    MarkNetworkUpdate();
}

void CollisionShape::SetTriangleMesh(Model* model, unsigned lodLevel, const Vector3& scale, const Vector3& position, const Quaternion& rotation)
{
    if (!model)
    {
        LOGERROR("Null model, can not set triangle mesh");
        return;
    }
    
    shapeType_ = SHAPE_TRIANGLEMESH;
    model_ = model;
    lodLevel_ = lodLevel;
    size_ = scale;
    position_ = position;
    rotation_ = rotation;
    
    UpdateShape();
    NotifyRigidBody();
    MarkNetworkUpdate();
}

void CollisionShape::SetConvexHull(Model* model, unsigned lodLevel, const Vector3& scale, const Vector3& position, const Quaternion& rotation)
{
    if (!model)
    {
        LOGERROR("Null model, can not set convex hull");
        return;
    }
    
    shapeType_ = SHAPE_CONVEXHULL;
    model_ = model;
    lodLevel_ = lodLevel;
    size_ = scale;
    position_ = position;
    rotation_ = rotation;
    
    UpdateShape();
    NotifyRigidBody();
    MarkNetworkUpdate();
}

void CollisionShape::SetTerrain()
{
    Terrain* terrain = GetComponent<Terrain>();
    if (!terrain)
    {
        LOGERROR("No terrain component, can not set terrain shape");
        return;
    }
    
    shapeType_ = SHAPE_TERRAIN;
    
    UpdateShape();
    NotifyRigidBody();
    MarkNetworkUpdate();
}

void CollisionShape::SetShapeType(ShapeType type)
{
    if (type != shapeType_)
    {
        shapeType_ = type;
        UpdateShape();
        NotifyRigidBody();
        MarkNetworkUpdate();
    }
}

void CollisionShape::SetSize(const Vector3& size)
{
    if (size != size_)
    {
        size_ = size;
        UpdateShape();
        NotifyRigidBody();
        MarkNetworkUpdate();
    }
}

void CollisionShape::SetPosition(const Vector3& position)
{
    if (position != position_)
    {
        position_ = position;
        NotifyRigidBody();
        MarkNetworkUpdate();
    }
}

void CollisionShape::SetRotation(const Quaternion& rotation)
{
    if (rotation != rotation_)
    {
        rotation_ = rotation;
        NotifyRigidBody();
        MarkNetworkUpdate();
    }
}

void CollisionShape::SetTransform(const Vector3& position, const Quaternion& rotation)
{
    if (position != position_ || rotation != rotation_)
    {
        position_ = position;
        rotation_ = rotation;
        NotifyRigidBody();
        MarkNetworkUpdate();
    }
}

void CollisionShape::SetMargin(float margin)
{
    margin = Max(margin, 0.0f);
    
    if (margin != margin_)
    {
        if (shape_)
            shape_->setMargin(margin);
        margin_ = margin;
        MarkNetworkUpdate();
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
        MarkNetworkUpdate();
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
        MarkNetworkUpdate();
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
        Vector3 position = position_;
        // For terrains, undo the height centering performed automatically by Bullet
        if (shapeType_ == SHAPE_TERRAIN && geometry_)
        {
            HeightfieldData* heightfield = static_cast<HeightfieldData*>(geometry_.Get());
            position.y_ += (heightfield->minHeight_ + heightfield->maxHeight_) * 0.5f;
        }
        
        btTransform offset;
        offset.setOrigin(ToBtVector3(node_->GetWorldScale() * position));
        offset.setRotation(ToBtQuaternion(rotation_));
        compound->addChildShape(offset, shape_);
        
        // Finally tell the rigid body to update its mass
        rigidBody_->UpdateMass();
    }
}

void CollisionShape::SetModelAttr(ResourceRef value)
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    model_ = cache->GetResource<Model>(value.id_);
    recreateShape_ = true;
    MarkNetworkUpdate();
}

ResourceRef CollisionShape::GetModelAttr() const
{
    return GetResourceRef(model_, Model::GetTypeStatic());
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

void CollisionShape::OnNodeSet(Node* node)
{
    if (node)
    {
        Scene* scene = GetScene();
        if (scene)
        {
            physicsWorld_ = scene->GetComponent<PhysicsWorld>();
            if (physicsWorld_)
                physicsWorld_->AddCollisionShape(this);
            else
                LOGERROR("No physics world component in scene, can not create collision shape");
        }
        node->AddListener(this);
        
        // Terrain collision shape depends on the terrain component's geometry updates. Subscribe to them
        SubscribeToEvent(node, E_TERRAINCREATED, HANDLER(CollisionShape, HandleTerrainCreated));
        
        UpdateShape();
        NotifyRigidBody();
    }
}

void CollisionShape::OnMarkedDirty(Node* node)
{
    Vector3 newWorldScale = node_->GetWorldScale();
    if (!newWorldScale.Equals(cachedWorldScale_) && shape_)
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
            
        case SHAPE_TERRAIN:
            {
                HeightfieldData* heightfield = static_cast<HeightfieldData*>(geometry_.Get());
                shape_->setLocalScaling(ToBtVector3(Vector3(heightfield->spacing_.x_, 1.0f, heightfield->spacing_.z_) *
                    newWorldScale * size_));
            }
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
            size_ = size_.Abs();
            if (model_)
            {
                // Check the geometry cache
                String id = "TriMesh_" + model_->GetName() + "_" + String(lodLevel_);
                
                HashMap<String, SharedPtr<CollisionGeometryData> >& cache = physicsWorld_->GetGeometryCache();
                HashMap<String, SharedPtr<CollisionGeometryData> >::Iterator j = cache.Find(id);
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
            size_ = size_.Abs();
            if (model_)
            {
                // Check the geometry cache
                String id = "Convex_" + model_->GetName() + "_" + String(lodLevel_);
                
                HashMap<String, SharedPtr<CollisionGeometryData> >& cache = physicsWorld_->GetGeometryCache();
                HashMap<String, SharedPtr<CollisionGeometryData> >::Iterator j = cache.Find(id);
                if (j != cache.End())
                    geometry_ = j->second_;
                else
                {
                    geometry_ = new ConvexData(model_, lodLevel_);
                    cache[id] = geometry_;
                }
                
                ConvexData* convex = static_cast<ConvexData*>(geometry_.Get());
                shape_ = new btConvexHullShape((btScalar*)convex->vertexData_.Get(), convex->vertexCount_, sizeof(Vector3));
                shape_->setLocalScaling(ToBtVector3(newWorldScale * size_));
            }
            break;
            
        case SHAPE_TERRAIN:
            size_ = size_.Abs();
            {
                Terrain* terrain = GetComponent<Terrain>();
                if (terrain && terrain->GetHeightData())
                {
                    geometry_ = new HeightfieldData(terrain);
                    HeightfieldData* heightfield = static_cast<HeightfieldData*>(geometry_.Get());
                    
                    shape_ = new btHeightfieldTerrainShape(heightfield->size_.x_, heightfield->size_.y_,
                        heightfield->heightData_.Get(), 1.0f, heightfield->minHeight_, heightfield->maxHeight_, 1, PHY_FLOAT,
                        false);
                    shape_->setLocalScaling(ToBtVector3(Vector3(heightfield->spacing_.x_, 1.0f, heightfield->spacing_.z_) *
                        newWorldScale * size_));
                }
            }
            break;
        }
        
        if (shape_)
        {
            shape_->setUserPointer(this);
            shape_->setMargin(margin_);
        }
        
        cachedWorldScale_ = newWorldScale;
    }
    
    if (physicsWorld_)
        physicsWorld_->CleanupGeometryCache();
}

void CollisionShape::HandleTerrainCreated(StringHash eventType, VariantMap& eventData)
{
    if (shapeType_ == SHAPE_TERRAIN)
    {
        UpdateShape();
        NotifyRigidBody();
    }
}
