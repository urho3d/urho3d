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
#include "RigidBody.h"
#include "Scene.h"

#include <BulletCollision/CollisionShapes/btBvhTriangleMeshShape.h>
#include <BulletCollision/CollisionShapes/btCompoundShape.h>
#include <BulletCollision/CollisionShapes/btTriangleMesh.h>
#include <hull.h>

TriangleMeshData::TriangleMeshData(Model* model, unsigned lodLevel, const Vector3& scale) :
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
                meshData_->addTriangle(ToBtVector3(scale * v0), ToBtVector3(scale * v1), ToBtVector3(scale * v2), true);
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
                meshData_->addTriangle(ToBtVector3(scale * v0), ToBtVector3(scale * v1), ToBtVector3(scale * v2), true);
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

ConvexHullData::ConvexHullData(Model* model, unsigned lodLevel, float thickness, const Vector3& scale)
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
            originalVertices.Push(scale * v);
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

ConvexHullData::~ConvexHullData()
{
}

HeightfieldData::HeightfieldData(Model* model, IntVector2 numPoints, float thickness, unsigned lodLevel,
    const Vector3& scale)
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
    unsigned dataSize = numPoints.x_ * numPoints.y_;
    
    // Then allocate the heightfield
    BoundingBox box = model->GetBoundingBox();
    heightData_ = new float[dataSize];
    
    // Calculate spacing from model's bounding box
    float xSpacing = (box.max_.x_ - box.min_.x_) / (numPoints.x_ - 1);
    float zSpacing = (box.max_.z_ - box.min_.z_) / (numPoints.y_ - 1);
    
    // Initialize the heightfield with minimum height
    for (unsigned i = 0; i < dataSize; ++i)
        heightData_[i] = box.min_.y_ * scale.y_;
    
    unsigned vertexStart = geom->GetVertexStart();
    unsigned vertexCount = geom->GetVertexCount();
    
    // Now go through vertex data and fit the vertices into the heightfield
    for (unsigned i = vertexStart; i < vertexStart + vertexCount; ++i)
    {
        const Vector3& vertex = *((const Vector3*)(&vertexData[i * vertexSize]));
        int x = (int)((vertex.x_ - box.min_.x_) / xSpacing + 0.25f);
        int z = (int)((vertex.z_ - box.min_.z_) / zSpacing + 0.25f);
        if (x >= numPoints.x_)
            x = numPoints.x_ - 1;
        if (z >= numPoints.y_)
            z = numPoints.y_ - 1;
        if (vertex.y_ > heightData_[z * numPoints.x_ + x])
            heightData_[z * numPoints.x_ + x] = vertex.y_ * scale.y_;
    }
}

HeightfieldData::~HeightfieldData()
{
}

OBJECTTYPESTATIC(CollisionShape);

CollisionShape::CollisionShape(Context* context) :
    Component(context),
    shape_(0),
    position_(Vector3::ZERO),
    rotation_(Quaternion::IDENTITY),
    cachedWorldScale_(Vector3::ONE),
    dirty_(false)
{
}

CollisionShape::~CollisionShape()
{
    ReleaseShape();
    
    if (physicsWorld_)
        physicsWorld_->RemoveCollisionShape(this);
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
        UpdateCollisionShape();
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

btCompoundShape* CollisionShape::GetParentCompoundShape()
{
    if (!rigidBody_)
        rigidBody_ = GetComponent<RigidBody>();
    
    return rigidBody_ ? rigidBody_->GetCompoundShape() : 0;
}

void CollisionShape::DrawDebugGeometry(DebugRenderer* debug, bool depthTest)
{
    /// \todo Implement
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
        UpdateCollisionShape();
        NotifyRigidBody();
    }
}

void CollisionShape::OnMarkedDirty(Node* node)
{
    Vector3 newWorldScale = node_->GetWorldScale();
    if (newWorldScale != cachedWorldScale_)
    {
        if (shape_)
            shape_->setLocalScaling(ToBtVector3(newWorldScale));
        NotifyRigidBody();
        
        cachedWorldScale_ = newWorldScale;
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
    
    dirty_ = false;
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
}
