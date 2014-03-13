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
#include "Context.h"
#include "CollisionBox2D.h"
#include "PhysicsUtils2D.h"

#include "DebugNew.h"

namespace Urho3D
{

extern const char* URHO2D_CATEGORY;
static const Vector2 DEFAULT_BOX_SIZE(0.01f, 0.01f);

CollisionBox2D::CollisionBox2D(Context* context) : CollisionShape2D(context),
    size_(DEFAULT_BOX_SIZE),
    center_(Vector2::ZERO)
{
    boxShape_.SetAsBox(size_.x_ * 0.5f, size_.y_ * 0.5f);
    fixtureDef_.shape = &boxShape_;
}

CollisionBox2D::~CollisionBox2D()
{

}

void CollisionBox2D::RegisterObject(Context* context)
{
    context->RegisterFactory<CollisionBox2D>(URHO2D_CATEGORY);

    REF_ACCESSOR_ATTRIBUTE(CollisionBox2D, VAR_VECTOR2, "Size", GetSize, SetSize, Vector2, DEFAULT_BOX_SIZE, AM_DEFAULT);
    REF_ACCESSOR_ATTRIBUTE(CollisionBox2D, VAR_VECTOR2, "Center", GetCenter, SetCenter, Vector2, Vector2::ZERO, AM_DEFAULT);

    COPY_BASE_ATTRIBUTES(CollisionBox2D, CollisionShape2D);
}

void CollisionBox2D::SetSize(const Vector2& size)
{
    if (size == size_)
        return;

    size_ = size;

    MarkNetworkUpdate();
    RecreateFixture();
}

void CollisionBox2D::SetSize(float width, float height)
{
    SetSize(Vector2(width, height));
}

void CollisionBox2D::SetCenter(const Vector2& center)
{
    if (center == center_)
        return;

    center_ = center;

    MarkNetworkUpdate();
    RecreateFixture();
}

void CollisionBox2D::SetCenter(float x, float y)
{
    SetCenter(Vector2(x, y));
}

void CollisionBox2D::RecreateFixture()
{
    ReleaseFixture();

    if (center_ == Vector2::ZERO)
        boxShape_.SetAsBox(size_.x_ * 0.5f, size_.y_ * 0.5f);
    else
        boxShape_.SetAsBox(size_.x_ * 0.5f, size_.y_ * 0.5f, ToB2Vec2(center_), 0.0f);

    CreateFixture();
}

}
