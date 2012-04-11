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
#include "Model.h"
#include "Node.h"
#include "PhysicsUtils.h"
#include "PhysicsWorld.h"
#include "ResourceCache.h"
#include "TriangleMeshShape.h"

#include <BulletCollision/CollisionShapes/btScaledBvhTriangleMeshShape.h>
#include <stdio.h>

OBJECTTYPESTATIC(TriangleMeshShape);

TriangleMeshShape::TriangleMeshShape(Context* context) :
    CollisionShape(context),
    size_(Vector3::ONE),
    lodLevel_(0)
{
}

TriangleMeshShape::~TriangleMeshShape()
{
    // Release shape first before letting go of the mesh geometry
    ReleaseShape();
    
    geometry_.Reset();
    if (physicsWorld_)
        physicsWorld_->CleanupGeometryCache();
}

void TriangleMeshShape::RegisterObject(Context* context)
{
    context->RegisterFactory<TriangleMeshShape>();
    
    ACCESSOR_ATTRIBUTE(TriangleMeshShape, VAR_RESOURCEREF, "Model", GetModelAttr, SetModelAttr, ResourceRef, ResourceRef(Model::GetTypeStatic()), AM_DEFAULT);
    ATTRIBUTE(TriangleMeshShape, VAR_INT, "LOD Level", lodLevel_, 0, AM_DEFAULT);
    ATTRIBUTE(TriangleMeshShape, VAR_VECTOR3, "Offset Position", position_, Vector3::ZERO, AM_DEFAULT);
    ATTRIBUTE(TriangleMeshShape, VAR_QUATERNION, "Offset Rotation", rotation_, Quaternion::IDENTITY, AM_DEFAULT);
    ATTRIBUTE(TriangleMeshShape, VAR_VECTOR3, "Size", size_, Vector3::ONE, AM_DEFAULT);
}

void TriangleMeshShape::SetModel(Model* model)
{
    if (model != model_)
    {
        model_ = model;
        UpdateCollisionShape();
        NotifyRigidBody();
    }
}

void TriangleMeshShape::SetLodLevel(unsigned lodLevel)
{
    if (lodLevel != lodLevel_)
    {
        lodLevel_ = lodLevel;
        UpdateCollisionShape();
        NotifyRigidBody();
    }
}

void TriangleMeshShape::SetSize(const Vector3& size)
{
    if (size != size_)
    {
        size_ = size;
        UpdateCollisionShape();
        NotifyRigidBody();
    }
}

Model* TriangleMeshShape::GetModel() const
{
    return model_;
}

void TriangleMeshShape::SetModelAttr(ResourceRef value)
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    model_ = cache->GetResource<Model>(value.id_);
    dirty_ = true;
}

ResourceRef TriangleMeshShape::GetModelAttr() const
{
    return GetResourceRef(model_, Model::GetTypeStatic());
}

void TriangleMeshShape::UpdateCollisionShape()
{
    if (node_)
    {
        ReleaseShape();
        
        if (model_ && physicsWorld_)
        {
            char sizeText[CONVERSION_BUFFER_LENGTH];
            sprintf(sizeText, "%.3f%.3f%.3f", size_.x_, size_.y_, size_.z_);
            
            // Check the geometry cache
            String id = model_->GetName() + "_" + String(lodLevel_) + "_" + String(sizeText);
            
            Map<String, SharedPtr<TriangleMeshData> >& cache = physicsWorld_->GetTriangleMeshCache();
            Map<String, SharedPtr<TriangleMeshData> >::Iterator j = cache.Find(id);
            if (j != cache.End())
                geometry_ = j->second_;
            else
            {
                geometry_ = new TriangleMeshData(model_, lodLevel_, size_);
                cache[id] = geometry_;
            }
            
            shape_ = new btScaledBvhTriangleMeshShape(geometry_->shape_, ToBtVector3(node_->GetWorldScale()));
        }
        else
            geometry_.Reset();
        
        if (physicsWorld_)
            physicsWorld_->CleanupGeometryCache();
    }
}
