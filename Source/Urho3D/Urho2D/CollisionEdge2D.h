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

#pragma once

#include "../Urho2D/CollisionShape2D.h"

namespace Urho3D
{

/// 2D edge collision component.
class URHO3D_API CollisionEdge2D : public CollisionShape2D
{
    URHO3D_OBJECT(CollisionEdge2D, CollisionShape2D);

public:
    /// Construct.
    CollisionEdge2D(Context* context);
    /// Destruct.
    virtual ~CollisionEdge2D();
    /// Register object factory.
    static void RegisterObject(Context* context);

    /// Set vertex 1.
    void SetVertex1(const Vector2& vertex);
    /// Set vertex 2.
    void SetVertex2(const Vector2& vertex);
    /// Set vertices.
    void SetVertices(const Vector2& vertex1, const Vector2& vertex2);

    /// Return vertex 1.
    const Vector2& GetVertex1() const { return vertex1_; }

    /// Return vertex 2.
    const Vector2& GetVertex2() const { return vertex2_; }

private:
    /// Apply node world scale.
    virtual void ApplyNodeWorldScale();
    /// Recreate fixture.
    void RecreateFixture();

    /// Edge shape.
    b2EdgeShape edgeShape_;
    /// Vertex 1.
    Vector2 vertex1_;
    /// Vertex 2.
    Vector2 vertex2_;
};

}
