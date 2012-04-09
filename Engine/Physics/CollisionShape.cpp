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
#include "Log.h"
#include "PhysicsWorld.h"
#include "RigidBody.h"
#include "Scene.h"

#include "DebugNew.h"

CollisionShape::CollisionShape(Context* context) :
    Component(context),
    position_(Vector3::ZERO),
    rotation_(Quaternion::IDENTITY),
    dirty_(true)
{
}

CollisionShape::~CollisionShape()
{
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
        NotifyRigidBody();
}

void CollisionShape::SetPosition(const Vector3& position)
{
    position_ = position;
    NotifyRigidBody();
}

void CollisionShape::SetRotation(const Quaternion& rotation)
{
    rotation_ = rotation;
    NotifyRigidBody();
}

void CollisionShape::SetTransform(const Vector3& position, const Quaternion& rotation)
{
    position_ = position;
    rotation_ = rotation;
    NotifyRigidBody();
}

void CollisionShape::DrawDebugGeometry(DebugRenderer* debug, bool depthTest)
{
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
    }
}

void CollisionShape::NotifyRigidBody()
{
    RigidBody* rigidBody = GetComponent<RigidBody>();
    if (rigidBody)
        rigidBody->UpdateCollisionShape(this);
    dirty_ = false;
}
