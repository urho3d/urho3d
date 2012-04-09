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
#include "BoxShape.h"
#include "Context.h"
#include "Node.h"
#include "PhysicsUtils.h"

#include <BulletCollision/CollisionShapes/btBoxShape.h>

OBJECTTYPESTATIC(BoxShape);

BoxShape::BoxShape(Context* context) :
    CollisionShape(context),
    collisionShape_(0),
    size_(Vector3::ONE)
{
}

BoxShape::~BoxShape()
{
    delete collisionShape_;
    collisionShape_ = 0;
    
    NotifyRigidBody();
}

void BoxShape::RegisterObject(Context* context)
{
    context->RegisterFactory<BoxShape>();
    
    ATTRIBUTE(BoxShape, VAR_VECTOR3, "Offset Position", position_, Vector3::ZERO, AM_DEFAULT);
    ATTRIBUTE(BoxShape, VAR_QUATERNION, "Offset Rotation", rotation_, Quaternion::IDENTITY, AM_DEFAULT);
    ATTRIBUTE(BoxShape, VAR_VECTOR3, "Size", size_, Vector3::ONE, AM_DEFAULT);
}

btCollisionShape* BoxShape::GetCollisionShape() const
{
    return collisionShape_;
}

void BoxShape::SetSize(const Vector3& size)
{
    if (size != size_)
    {
        size_ = size;
        UpdateCollisionShape();
        NotifyRigidBody();
    }
}

void BoxShape::UpdateCollisionShape()
{
    if (node_)
    {
        delete collisionShape_;
        collisionShape_ = 0;
        
        Vector3 worldSize = node_->GetWorldScale() * size_;
        collisionShape_ = new btBoxShape(ToBtVector3(worldSize * 0.5f));
    }
}
