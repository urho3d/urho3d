// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include "../Precompiled.h"

#include "../Core/Context.h"
#include "../IO/MemoryBuffer.h"
#include "../IO/VectorBuffer.h"
#include "../Physics2D/CollisionPolygon2D.h"
#include "../Physics2D/PhysicsUtils2D.h"

#include "../DebugNew.h"

namespace Urho3D
{

extern const char* PHYSICS2D_CATEGORY;

CollisionPolygon2D::CollisionPolygon2D(Context* context) :
    CollisionShape2D(context)
{
    fixtureDef_.shape = &polygonShape_;
}

CollisionPolygon2D::~CollisionPolygon2D() = default;

void CollisionPolygon2D::RegisterObject(Context* context)
{
    context->RegisterFactory<CollisionPolygon2D>(PHYSICS2D_CATEGORY);

    URHO3D_ACCESSOR_ATTRIBUTE("Is Enabled", IsEnabled, SetEnabled, true, AM_DEFAULT);
    URHO3D_COPY_BASE_ATTRIBUTES(CollisionShape2D);
    URHO3D_ACCESSOR_ATTRIBUTE("Vertices", GetVerticesAttr, SetVerticesAttr, Variant::emptyBuffer, AM_FILE);
}

void CollisionPolygon2D::SetVertexCount(i32 count)
{
    assert(count >= 0);
    vertices_.Resize(count);
}

void CollisionPolygon2D::SetVertex(i32 index, const Vector2& vertex)
{
    assert(index >= 0);

    if (index >= vertices_.Size())
        return;

    vertices_[index] = vertex;

    if (index == vertices_.Size() - 1)
    {
        MarkNetworkUpdate();
        RecreateFixture();
    }
}

void CollisionPolygon2D::SetVertices(const Vector<Vector2>& vertices)
{
    vertices_ = vertices;

    MarkNetworkUpdate();
    RecreateFixture();
}

void CollisionPolygon2D::SetVerticesAttr(const Vector<byte>& value)
{
    if (value.Empty())
        return;

    Vector<Vector2> vertices;

    MemoryBuffer buffer(value);
    while (!buffer.IsEof())
        vertices.Push(buffer.ReadVector2());

    SetVertices(vertices);
}

Vector<byte> CollisionPolygon2D::GetVerticesAttr() const
{
    VectorBuffer ret;

    for (const Vector2& vertex : vertices_)
        ret.WriteVector2(vertex);

    return ret.GetBuffer();
}

void CollisionPolygon2D::ApplyNodeWorldScale()
{
    RecreateFixture();
}

void CollisionPolygon2D::RecreateFixture()
{
    ReleaseFixture();

    if (vertices_.Size() < 3)
        return;

    Vector<b2Vec2> b2Vertices;
    i32 count = vertices_.Size();
    b2Vertices.Resize(count);

    Vector2 worldScale(cachedWorldScale_.x_, cachedWorldScale_.y_);
    for (i32 i = 0; i < count; ++i)
        b2Vertices[i] = ToB2Vec2(vertices_[i] * worldScale);

    polygonShape_.Set(&b2Vertices[0], count);

    CreateFixture();
}

}
