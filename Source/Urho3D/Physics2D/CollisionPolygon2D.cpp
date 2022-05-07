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

    URHO3D_ACCESSOR_ATTRIBUTE("Is Enabled", IsEnabled, SetEnabled, bool, true, AM_DEFAULT);
    URHO3D_COPY_BASE_ATTRIBUTES(CollisionShape2D);
    URHO3D_MIXED_ACCESSOR_ATTRIBUTE("Vertices", GetVerticesAttr, SetVerticesAttr, PODVector<unsigned char>, Variant::emptyBuffer, AM_FILE);
}

void CollisionPolygon2D::SetVertexCount(unsigned count)
{
    vertices_.Resize(count);
}

void CollisionPolygon2D::SetVertex(unsigned index, const Vector2& vertex)
{
    if (index >= vertices_.Size())
        return;

    vertices_[index] = vertex;

    if (index == vertices_.Size() - 1)
    {
        MarkNetworkUpdate();
        RecreateFixture();
    }
}

void CollisionPolygon2D::SetVertices(const PODVector<Vector2>& vertices)
{
    vertices_ = vertices;

    MarkNetworkUpdate();
    RecreateFixture();
}

void CollisionPolygon2D::SetVerticesAttr(const PODVector<unsigned char>& value)
{
    if (value.Empty())
        return;

    PODVector<Vector2> vertices;

    MemoryBuffer buffer(value);
    while (!buffer.IsEof())
        vertices.Push(buffer.ReadVector2());

    SetVertices(vertices);
}

PODVector<unsigned char> CollisionPolygon2D::GetVerticesAttr() const
{
    VectorBuffer ret;

    for (unsigned i = 0; i < vertices_.Size(); ++i)
        ret.WriteVector2(vertices_[i]);

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

    PODVector<b2Vec2> b2Vertices;
    unsigned count = vertices_.Size();
    b2Vertices.Resize(count);

    Vector2 worldScale(cachedWorldScale_.x_, cachedWorldScale_.y_);
    for (unsigned i = 0; i < count; ++i)
        b2Vertices[i] = ToB2Vec2(vertices_[i] * worldScale);

    polygonShape_.Set(&b2Vertices[0], count);

    CreateFixture();
}

}
