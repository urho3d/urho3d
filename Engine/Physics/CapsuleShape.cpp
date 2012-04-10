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
#include "CapsuleShape.h"
#include "Context.h"
#include "Node.h"
#include "PhysicsUtils.h"

#include <BulletCollision/CollisionShapes/btCapsuleShape.h>

OBJECTTYPESTATIC(CapsuleShape);

static const float DEFAULT_RADIUS = 0.5f;
static const float DEFAULT_HEIGHT = 1.0f;

CapsuleShape::CapsuleShape(Context* context) :
    CollisionShape(context),
    radius_(DEFAULT_RADIUS),
    height_(DEFAULT_HEIGHT)
{
}

void CapsuleShape::RegisterObject(Context* context)
{
    context->RegisterFactory<CapsuleShape>();
    
    ATTRIBUTE(CapsuleShape, VAR_VECTOR3, "Offset Position", position_, Vector3::ZERO, AM_DEFAULT);
    ATTRIBUTE(CapsuleShape, VAR_QUATERNION, "Offset Rotation", rotation_, Quaternion::IDENTITY, AM_DEFAULT);
    ATTRIBUTE(CapsuleShape, VAR_FLOAT, "Radius", radius_, DEFAULT_RADIUS, AM_DEFAULT);
    ATTRIBUTE(CapsuleShape, VAR_FLOAT, "Height", height_, DEFAULT_HEIGHT, AM_DEFAULT);
}

void CapsuleShape::SetRadius(float radius)
{
    if (radius != radius_)
    {
        radius_ = radius;
        UpdateCollisionShape();
        NotifyRigidBody();
    }
}

void CapsuleShape::SetHeight(float height)
{
    if (height != height_)
    {
        height_ = height;
        UpdateCollisionShape();
        NotifyRigidBody();
    }
}

void CapsuleShape::UpdateCollisionShape()
{
    if (node_)
    {
        delete shape_;
        shape_ = 0;
        
        shape_ = new btCapsuleShape(radius_, Max(height_ - 2.0f * radius_, 0.0f));
        shape_->setLocalScaling(ToBtVector3(node_->GetWorldScale()));
    }
}
