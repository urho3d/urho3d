// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include "../Precompiled.h"

#include "../Core/Context.h"
#include "../Physics2D/CollisionEdge2D.h"
#include "../Physics2D/PhysicsUtils2D.h"

#include "../DebugNew.h"

namespace Urho3D
{

extern const char* PHYSICS2D_CATEGORY;
static const Vector2 DEFAULT_VERTEX1(-0.01f, 0.0f);
static const Vector2 DEFAULT_VERTEX2(0.01f, 0.0f);

CollisionEdge2D::CollisionEdge2D(Context* context) :
    CollisionShape2D(context),
    vertex1_(DEFAULT_VERTEX1),
    vertex2_(DEFAULT_VERTEX2)
{
    Vector2 worldScale(cachedWorldScale_.x_, cachedWorldScale_.y_);
    edgeShape_.SetTwoSided(ToB2Vec2(vertex1_ * worldScale), ToB2Vec2(vertex2_ * worldScale));

    fixtureDef_.shape = &edgeShape_;
}

CollisionEdge2D::~CollisionEdge2D() = default;

void CollisionEdge2D::RegisterObject(Context* context)
{
    context->RegisterFactory<CollisionEdge2D>(PHYSICS2D_CATEGORY);

    URHO3D_ACCESSOR_ATTRIBUTE("Is Enabled", IsEnabled, SetEnabled, bool, true, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Vertex 1", GetVertex1, SetVertex1, Vector2, DEFAULT_VERTEX1, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Vertex 2", GetVertex2, SetVertex2, Vector2, DEFAULT_VERTEX2, AM_DEFAULT);
    URHO3D_COPY_BASE_ATTRIBUTES(CollisionShape2D);
}

void CollisionEdge2D::SetVertex1(const Vector2& vertex)
{
    SetVertices(vertex, vertex2_);
}

void CollisionEdge2D::SetVertex2(const Vector2& vertex)
{
    SetVertices(vertex1_, vertex);
}

void CollisionEdge2D::SetVertices(const Vector2& vertex1, const Vector2& vertex2)
{
    if (vertex1 == vertex1_ && vertex2 == vertex2_)
        return;

    vertex1_ = vertex1;
    vertex2_ = vertex2;

    MarkNetworkUpdate();
    RecreateFixture();
}

void CollisionEdge2D::ApplyNodeWorldScale()
{
    RecreateFixture();
}

void CollisionEdge2D::RecreateFixture()
{
    ReleaseFixture();

    Vector2 worldScale(cachedWorldScale_.x_, cachedWorldScale_.y_);
    edgeShape_.SetTwoSided(ToB2Vec2(vertex1_ * worldScale), ToB2Vec2(vertex2_ * worldScale));

    CreateFixture();
}

}
