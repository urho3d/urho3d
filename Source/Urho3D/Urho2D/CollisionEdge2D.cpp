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
#include "../Core/Context.h"
#include "../Urho2D/CollisionEdge2D.h"
#include "../Urho2D/PhysicsUtils2D.h"

#include "../DebugNew.h"

namespace Urho3D
{

extern const char* URHO2D_CATEGORY;
static const Vector2 DEFAULT_VERTEX1(-0.01f, 0.0f);
static const Vector2 DEFAULT_VERTEX2(0.01f, 0.0f);

CollisionEdge2D::CollisionEdge2D(Context* context) :
    CollisionShape2D(context),
    vertex1_(DEFAULT_VERTEX1),
    vertex2_(DEFAULT_VERTEX2)

{
    Vector2 worldScale(cachedWorldScale_.x_, cachedWorldScale_.y_);
    edgeShape_.Set(ToB2Vec2(vertex1_ * worldScale), ToB2Vec2(vertex2_ * worldScale));

    fixtureDef_.shape = &edgeShape_;
}

CollisionEdge2D::~CollisionEdge2D()
{
}

void CollisionEdge2D::RegisterObject(Context* context)
{
    context->RegisterFactory<CollisionEdge2D>(URHO2D_CATEGORY);

    ACCESSOR_ATTRIBUTE("Is Enabled", IsEnabled, SetEnabled, bool, true, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE("Vertex 1", GetVertex1, SetVertex1, Vector2, DEFAULT_VERTEX1, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE("Vertex 2", GetVertex2, SetVertex2, Vector2, DEFAULT_VERTEX2, AM_DEFAULT);
    COPY_BASE_ATTRIBUTES(CollisionShape2D);
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
    edgeShape_.Set(ToB2Vec2(vertex1_ * worldScale), ToB2Vec2(vertex2_ * worldScale));

    CreateFixture();
}

}
