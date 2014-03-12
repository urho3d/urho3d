//
// Copyright (c) 2008-2014 the Urho3D project.
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
#include "CollisionShape2D.h"
#include "Context.h"
#include "Log.h"
#include "Node.h"
#include "PhysicsUtils2D.h"
#include "RigidBody2D.h"

#include "DebugNew.h"

namespace Urho3D
{

extern const char* URHO2D_CATEGORY;

CollisionShape2D::CollisionShape2D(Context* context) : Component(context), 
    fixture_(0),
    fixtureDirty_(true)
{

}

CollisionShape2D::~CollisionShape2D()
{
    if (rigidBody_)
        rigidBody_->RemoveCollisionShape2D(this);

    ReleaseFixture();
    ReleaseFixtureShape();
}

void CollisionShape2D::RegisterObject(Context* context)
{
    context->RegisterFactory<CollisionShape2D>(URHO2D_CATEGORY);

    ACCESSOR_ATTRIBUTE(CollisionShape2D, VAR_BOOL, "Sensor", IsSensor, SetSensor, bool, false, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(CollisionShape2D, VAR_INT, "Category Bits", GetCategoryBits, SetCategoryBits, int, 0, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(CollisionShape2D, VAR_INT, "Mask Bits", GetMaskBits, SetMaskBits, int, 0, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(CollisionShape2D, VAR_INT, "Group Index", GetGroupIndex, SetGroupIndex, int, 0, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(CollisionShape2D, VAR_FLOAT, "Density", GetDensity, SetDensity, float, 0.0f, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(CollisionShape2D, VAR_FLOAT, "Friction", GetFriction, SetFriction, float, 0.2f, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(CollisionShape2D, VAR_FLOAT, "Restitution", GetRestitution, SetRestitution, float, 0.0f, AM_DEFAULT);

    COPY_BASE_ATTRIBUTES(CollisionShape2D, Component);
}

void CollisionShape2D::OnSetEnabled()
{
    if (IsEnabledEffective())
    {
        CreateFixture();
        if (rigidBody_)
            rigidBody_->AddCollisionShape2D(this);
    }
    else
    {
        if (rigidBody_)
            rigidBody_->RemoveCollisionShape2D(this);
        ReleaseFixture();
    }
}

void CollisionShape2D::SetSensor(bool sensor)
{
    if (fixtureDef_.isSensor == sensor)
        return;

    fixtureDef_.isSensor = sensor;

    if (fixture_ && !fixtureDirty_)
        fixture_->SetSensor(sensor);
    else
        fixtureDirty_ = true;

    MarkNetworkUpdate();
}

void CollisionShape2D::SetCategoryBits(int categoryBits)
{
    if (fixtureDef_.filter.categoryBits == categoryBits)
        return;

    fixtureDef_.filter.categoryBits = categoryBits;

    if (fixture_ && !fixtureDirty_)
        fixture_->SetFilterData(fixtureDef_.filter);
    else
        fixtureDirty_ = true;

    MarkNetworkUpdate();
}

void CollisionShape2D::SetMaskBits(int maskBits)
{
    if (fixtureDef_.filter.maskBits == maskBits)
        return;

    fixtureDef_.filter.maskBits = maskBits;

    if (fixture_ && !fixtureDirty_)
        fixture_->SetFilterData(fixtureDef_.filter);
    else
        fixtureDirty_ = true;

    MarkNetworkUpdate();
}

void CollisionShape2D::SetGroupIndex(int groupIndex)
{
    if (fixtureDef_.filter.groupIndex == groupIndex)
        return;

    fixtureDef_.filter.groupIndex = groupIndex;

    if (fixture_ && !fixtureDirty_)
        fixture_->SetFilterData(fixtureDef_.filter);
    else
        fixtureDirty_ = true;

    MarkNetworkUpdate();
}

void CollisionShape2D::SetDensity(float density)
{
    if (fixtureDef_.density == density)
        return;

    fixtureDef_.density = density;

    if (fixture_ && !fixtureDirty_)
        fixture_->SetDensity(density);
    else
        fixtureDirty_ = true;

    MarkNetworkUpdate();
}

void CollisionShape2D::SetFriction(float friction)
{
    if (fixtureDef_.friction == friction)
        return;

    fixtureDef_.friction = friction;

    if (fixture_ && !fixtureDirty_)
        fixture_->SetFriction(friction);
    else
        fixtureDirty_ = true;

    MarkNetworkUpdate();
}

void CollisionShape2D::SetRestitution(float restitution)
{
    if (fixtureDef_.restitution == restitution)
        return;

    fixtureDef_.restitution = restitution;

    if (fixture_ && !fixtureDirty_)
        fixture_->SetRestitution(restitution);
    else
        fixtureDirty_ = true;

    MarkNetworkUpdate();
}

void CollisionShape2D::SetCircle(float radius, const Vector2& center)
{
    ReleaseFixtureShape();

    b2CircleShape* shape = new b2CircleShape;
    shape->m_radius = radius;
    shape->m_p = ToB2Vec2(center);

    fixtureDef_.shape = shape;

    fixtureDirty_ = true;
    MarkNetworkUpdate();
}

void CollisionShape2D::SetBox(const Vector2& halfSize, const Vector2& center)
{
    ReleaseFixtureShape();

    b2PolygonShape* shape = new b2PolygonShape;
    if (center == Vector2::ZERO)
        shape->SetAsBox(halfSize.x_, halfSize.y_);
    else
        shape->SetAsBox(halfSize.x_, halfSize.y_, ToB2Vec2(center), 0.0f);

    fixtureDef_.shape = shape;

    fixtureDirty_ = true;
    MarkNetworkUpdate();
}

void CollisionShape2D::SetBox(float halfWidth, float halfHeight, const Vector2& center)
{
    SetBox(Vector2(halfWidth, halfHeight), center);
}

void CollisionShape2D::SetChain(const PODVector<Vector2>& vertices)
{
    ReleaseFixtureShape();

    unsigned count = vertices.Size();
    if (!count)
        return;
    
    b2ChainShape* shape = new b2ChainShape;
    b2Vec2* points = new b2Vec2[count];
    for (unsigned i = 0; i < count; ++i)
        points[i] = ToB2Vec2(vertices[i]);
    shape->CreateChain(points, count);
    delete [] points;

    fixtureDef_.shape = shape;

    fixtureDirty_ = true;
    MarkNetworkUpdate();
}

void CollisionShape2D::SetPolygon(const PODVector<Vector2>& vertices)
{
    ReleaseFixtureShape();

    unsigned count = Min(b2_maxPolygonVertices, vertices.Size());
    if (!count)
        return;

    b2PolygonShape* shape = new b2PolygonShape;
    b2Vec2* points = new b2Vec2[count];
    for (unsigned i = 0; i < count; ++i)
        points[i] = ToB2Vec2(vertices[i]);
    shape->Set(points, count);
    delete [] points;

    fixtureDef_.shape = shape;

    fixtureDirty_ = true;
    MarkNetworkUpdate();
}

void CollisionShape2D::SetEdge(const Vector2& vertex1, const Vector2& vertex2)
{
    ReleaseFixtureShape();

    b2EdgeShape* shape = new b2EdgeShape;
    shape->Set(ToB2Vec2(vertex1), ToB2Vec2(vertex2));
    fixtureDef_.shape = shape;

    fixtureDirty_ = true;
    MarkNetworkUpdate();
}

void CollisionShape2D::CreateFixture()
{
    if (fixture_)
        return;

    if (!rigidBody_)
        return;

    b2Body* body = rigidBody_->GetBody();
    if (!body)
        return;

    fixture_ = body->CreateFixture(&fixtureDef_);
    fixture_->SetUserData(this);
}

void CollisionShape2D::UpdateFixture()
{
    if (!fixtureDirty_)
        return;

    ReleaseFixture();
    CreateFixture();

    fixtureDirty_ = false;
}

void CollisionShape2D::ReleaseFixture()
{
    if (!fixture_)
        return;

    if (!rigidBody_)
        return;

    b2Body* body = rigidBody_->GetBody();
    if (!body)
        return;

    body->DestroyFixture(fixture_);
    fixture_ = 0;
}

void CollisionShape2D::ReleaseFixtureShape()
{
    if (!fixtureDef_.shape)
        return;
    delete fixtureDef_.shape;
    fixtureDef_.shape = 0;
}

float CollisionShape2D::GetMass() const
{
    if (!fixture_)
        return 0.0f;

    b2MassData massData;
    fixture_->GetMassData(&massData);

    return massData.mass;
}

float CollisionShape2D::GetInertia() const
{
    if (!fixture_)
        return 0.0f;

    b2MassData massData;
    fixture_->GetMassData(&massData);

    return massData.I;
}

Vector2 CollisionShape2D::GetMassCenter() const
{
    if (!fixture_)
        return Vector2::ZERO;
    
    b2MassData massData;
    fixture_->GetMassData(&massData);

    return ToVector2(massData.center);
}

void CollisionShape2D::OnNodeSet(Node* node)
{
    Component::OnNodeSet(node);

    if (node)
    {
        rigidBody_ = node->GetComponent<RigidBody2D>();
        if (rigidBody_)
            rigidBody_->AddCollisionShape2D(this);
        else
            LOGERROR("No right body component in node, can not create collision shape");
    }
}

}
