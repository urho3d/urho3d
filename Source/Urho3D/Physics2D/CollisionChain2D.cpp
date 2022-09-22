// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include "../Precompiled.h"

#include "../Core/Context.h"
#include "../IO/MemoryBuffer.h"
#include "../IO/VectorBuffer.h"
#include "../Physics2D/CollisionChain2D.h"
#include "../Physics2D/PhysicsUtils2D.h"

#include "../DebugNew.h"

namespace Urho3D
{

extern const char* PHYSICS2D_CATEGORY;

CollisionChain2D::CollisionChain2D(Context* context) :
    CollisionShape2D(context),
    loop_(false)
{
    fixtureDef_.shape = &chainShape_;
}

CollisionChain2D::~CollisionChain2D() = default;

void CollisionChain2D::RegisterObject(Context* context)
{
    context->RegisterFactory<CollisionChain2D>(PHYSICS2D_CATEGORY);

    URHO3D_ACCESSOR_ATTRIBUTE("Is Enabled", IsEnabled, SetEnabled, bool, true, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Loop", GetLoop, SetLoop, bool, false, AM_DEFAULT);
    URHO3D_COPY_BASE_ATTRIBUTES(CollisionShape2D);
    URHO3D_ACCESSOR_ATTRIBUTE("Vertices", GetVerticesAttr, SetVerticesAttr, Vector<u8>, Variant::emptyBuffer, AM_FILE);
}

void CollisionChain2D::SetLoop(bool loop)
{
    if (loop == loop_)
        return;

    loop_ = loop;

    MarkNetworkUpdate();
    RecreateFixture();
}

void CollisionChain2D::SetVertexCount(i32 count)
{
    assert(count >= 0);
    vertices_.Resize(count);
}

void CollisionChain2D::SetVertex(i32 index, const Vector2& vertex)
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

void CollisionChain2D::SetVertices(const Vector<Vector2>& vertices)
{
    vertices_ = vertices;

    MarkNetworkUpdate();
    RecreateFixture();
}

void CollisionChain2D::SetVerticesAttr(const Vector<u8>& value)
{
    if (value.Empty())
        return;

    Vector<Vector2> vertices;

    MemoryBuffer buffer(value);
    while (!buffer.IsEof())
        vertices.Push(buffer.ReadVector2());

    SetVertices(vertices);
}

Vector<u8> CollisionChain2D::GetVerticesAttr() const
{
    VectorBuffer ret;

    for (const Vector2& vertex : vertices_)
        ret.WriteVector2(vertex);

    return ret.GetBuffer();
}

void CollisionChain2D::ApplyNodeWorldScale()
{
    RecreateFixture();
}

void CollisionChain2D::RecreateFixture()
{
    ReleaseFixture();

    Vector<b2Vec2> b2Vertices;
    i32 count = vertices_.Size();
    b2Vertices.Resize(count);

    Vector2 worldScale(cachedWorldScale_.x_, cachedWorldScale_.y_);
    for (i32 i = 0; i < count; ++i)
        b2Vertices[i] = ToB2Vec2(vertices_[i] * worldScale);

    chainShape_.Clear();

    if (loop_)
    {
        if (count < 2)
            return;

        chainShape_.CreateLoop(&b2Vertices[0], count);
    }
    else
    {
        if (count < 4)
            return;

        chainShape_.CreateChain(&b2Vertices[1], count - 2, b2Vertices[0], b2Vertices[count - 1]);
    }

    CreateFixture();
}

}
