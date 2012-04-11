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
#include "Node.h"
#include "PhysicsUtils.h"
#include "SphereShape.h"

#include <BulletCollision/CollisionShapes/btSphereShape.h>

OBJECTTYPESTATIC(SphereShape);

static const float DEFAULT_RADIUS = 0.5f;

SphereShape::SphereShape(Context* context) :
    CollisionShape(context),
    radius_(DEFAULT_RADIUS)
{
}

void SphereShape::RegisterObject(Context* context)
{
    context->RegisterFactory<SphereShape>();
    
    ATTRIBUTE(SphereShape, VAR_VECTOR3, "Offset Position", position_, Vector3::ZERO, AM_DEFAULT);
    ATTRIBUTE(SphereShape, VAR_QUATERNION, "Offset Rotation", rotation_, Quaternion::IDENTITY, AM_DEFAULT);
    ATTRIBUTE(SphereShape, VAR_FLOAT, "Radius", radius_, DEFAULT_RADIUS, AM_DEFAULT);
}

void SphereShape::SetRadius(float radius)
{
    if (radius != radius_)
    {
        radius_ = radius;
        UpdateCollisionShape();
        NotifyRigidBody();
    }
}

void SphereShape::UpdateCollisionShape()
{
    if (node_)
    {
        ReleaseShape();
        
        shape_ = new btSphereShape(radius_);
        shape_->setLocalScaling(ToBtVector3(node_->GetWorldScale()));
    }
}
