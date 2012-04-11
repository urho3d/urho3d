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

#include <BulletCollision/CollisionShapes/btCompoundShape.h>

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
