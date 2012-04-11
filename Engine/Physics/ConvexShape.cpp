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
#include "Context.h"
#include "Geometry.h"
#include "Model.h"
#include "Node.h"
#include "PhysicsUtils.h"
#include "PhysicsWorld.h"
#include "ResourceCache.h"
#include "ConvexShape.h"

#include <BulletCollision/CollisionShapes/btConvexHullShape.h>
#include <hull.h>

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

OBJECTTYPESTATIC(ConvexShape);

ConvexShape::ConvexShape(Context* context) :
    CollisionShape(context),
    size_(Vector3::ONE),
    lodLevel_(0),
    thickness_(0.0f)
{
}

ConvexShape::~ConvexShape()
{
    // Release shape first before letting go of the geometry
    ReleaseShape();
    
    geometry_.Reset();
    if (physicsWorld_)
        physicsWorld_->CleanupGeometryCache();
}

void ConvexShape::RegisterObject(Context* context)
{
    context->RegisterFactory<ConvexShape>();
    
    ACCESSOR_ATTRIBUTE(ConvexShape, VAR_RESOURCEREF, "Model", GetModelAttr, SetModelAttr, ResourceRef, ResourceRef(Model::GetTypeStatic()), AM_DEFAULT);
    ATTRIBUTE(ConvexShape, VAR_INT, "LOD Level", lodLevel_, 0, AM_DEFAULT);
    ATTRIBUTE(ConvexShape, VAR_FLOAT, "Thickness", thickness_, 0.0f, AM_DEFAULT);
    ATTRIBUTE(ConvexShape, VAR_VECTOR3, "Offset Position", position_, Vector3::ZERO, AM_DEFAULT);
    ATTRIBUTE(ConvexShape, VAR_QUATERNION, "Offset Rotation", rotation_, Quaternion::IDENTITY, AM_DEFAULT);
    ATTRIBUTE(ConvexShape, VAR_VECTOR3, "Size", size_, Vector3::ONE, AM_DEFAULT);
}

void ConvexShape::SetModel(Model* model)
{
    if (model != model_)
    {
        model_ = model;
        UpdateCollisionShape();
        NotifyRigidBody();
    }
}

void ConvexShape::SetLodLevel(unsigned lodLevel)
{
    if (lodLevel != lodLevel_)
    {
        lodLevel_ = lodLevel;
        UpdateCollisionShape();
        NotifyRigidBody();
    }
}

void ConvexShape::SetThickness(float thickness)
{
    thickness = Max(thickness, 0.0f);
    
    if (thickness != thickness_)
    {
        thickness_ = thickness;
        UpdateCollisionShape();
        NotifyRigidBody();
    }
}

void ConvexShape::SetSize(const Vector3& size)
{
    if (size != size_)
    {
        size_ = size;
        UpdateCollisionShape();
        NotifyRigidBody();
    }
}

Model* ConvexShape::GetModel() const
{
    return model_;
}

void ConvexShape::SetModelAttr(ResourceRef value)
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    model_ = cache->GetResource<Model>(value.id_);
    dirty_ = true;
}

ResourceRef ConvexShape::GetModelAttr() const
{
    return GetResourceRef(model_, Model::GetTypeStatic());
}

void ConvexShape::OnMarkedDirty(Node* node)
{
    Vector3 newWorldScale = node_->GetWorldScale();
    if (newWorldScale != cachedWorldScale_)
    {
        if (shape_)
            shape_->setLocalScaling(ToBtVector3(newWorldScale * size_));
        NotifyRigidBody();
        
        cachedWorldScale_ = newWorldScale;
    }
}

void ConvexShape::UpdateCollisionShape()
{
    ReleaseShape();
    
    if (node_ && model_ && physicsWorld_)
    {
        // Check the geometry cache
        String id = model_->GetName() + "_" + String(lodLevel_) + "_" + String(thickness_);
        
        Map<String, SharedPtr<ConvexData> >& cache = physicsWorld_->GetConvexCache();
        Map<String, SharedPtr<ConvexData> >::Iterator j = cache.Find(id);
        if (j != cache.End())
            geometry_ = j->second_;
        else
        {
            geometry_ = new ConvexData(model_, lodLevel_, thickness_);
            cache[id] = geometry_;
        }
        
        shape_ = new btConvexHullShape((btScalar*)geometry_->vertexData_.Get(), geometry_->vertexCount_, sizeof(Vector3));
        shape_->setLocalScaling(ToBtVector3(node_->GetWorldScale() * size_));
    }
    else
        geometry_.Reset();
    
    if (physicsWorld_)
        physicsWorld_->CleanupGeometryCache();
}
