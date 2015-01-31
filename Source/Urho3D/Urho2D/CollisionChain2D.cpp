//
// Copyright (c) 2008-2015 the Urho3D project.
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

#include "../Core/Context.h"
#include "../Urho2D/CollisionChain2D.h"
#include "../IO/MemoryBuffer.h"
#include "../Urho2D/PhysicsUtils2D.h"
#include "../IO/VectorBuffer.h"

#include "../DebugNew.h"

namespace Urho3D
{

CollisionChain2D::CollisionChain2D(Context* context) :
    CollisionShape2D(context),
    loop_(false)
{
    fixtureDef_.shape = &chainShape_;
}

CollisionChain2D::~CollisionChain2D()
{
}

void CollisionChain2D::RegisterObject(Context* context)
{
    context->RegisterFactory<CollisionChain2D>();

    ACCESSOR_ATTRIBUTE("Is Enabled", IsEnabled, SetEnabled, bool, true, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE("Loop", GetLoop, SetLoop, bool, false, AM_DEFAULT);
    COPY_BASE_ATTRIBUTES(CollisionShape2D);
    MIXED_ACCESSOR_ATTRIBUTE("Vertices", GetVerticesAttr, SetVerticesAttr, PODVector<unsigned char>, Variant::emptyBuffer, AM_FILE);
}

void CollisionChain2D::SetLoop(bool loop)
{
    if (loop == loop_)
        return;

    loop_ = loop;

    MarkNetworkUpdate();
    RecreateFixture();
}

void CollisionChain2D::SetVertexCount(unsigned count)
{
    vertices_.Resize(count);
}

void CollisionChain2D::SetVertex(unsigned index, const Vector2& vertex)
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

void CollisionChain2D::SetVertices(const PODVector<Vector2>& vertices)
{
    vertices_ = vertices;

    MarkNetworkUpdate();
    RecreateFixture();
}

void CollisionChain2D::SetVerticesAttr(const PODVector<unsigned char>& value)
{
    if (value.Empty())
        return;

    PODVector<Vector2> vertices;

    MemoryBuffer buffer(value);
    while (!buffer.IsEof())
        vertices.Push(buffer.ReadVector2());

    SetVertices(vertices);
}

PODVector<unsigned char> CollisionChain2D::GetVerticesAttr() const
{
    VectorBuffer ret;

    for (unsigned i = 0; i < vertices_.Size(); ++i)
        ret.WriteVector2(vertices_[i]);

    return ret.GetBuffer();
}

void CollisionChain2D::ApplyNodeWorldScale()
{
    RecreateFixture();
}

void CollisionChain2D::RecreateFixture()
{
    ReleaseFixture();

    PODVector<b2Vec2> b2Vertices;
    unsigned count = vertices_.Size();
    b2Vertices.Resize(count);

    Vector2 worldScale(cachedWorldScale_.x_, cachedWorldScale_.y_);
    for (unsigned i = 0; i < count; ++i)
        b2Vertices[i] = ToB2Vec2(vertices_[i] * worldScale);

    if (loop_)
        chainShape_.CreateLoop(&b2Vertices[0], count);
    else
        chainShape_.CreateChain(&b2Vertices[0], count);

    CreateFixture();
}

}
