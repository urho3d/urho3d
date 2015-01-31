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
/// 2D chain collision component.
class URHO3D_API CollisionChain2D : public CollisionShape2D
{
    OBJECT(CollisionChain2D);

public:
    /// Construct.
    CollisionChain2D(Context* scontext);
    /// Destruct.
    virtual ~CollisionChain2D();
    /// Register object factory.
    static void RegisterObject(Context* context);

    /// Set loop.
    void SetLoop(bool loop);
    /// Set vertex count.
    void SetVertexCount(unsigned count);
    /// Set vertex.
    void SetVertex(unsigned index, const Vector2& vertex);
    /// Set vertices.
    void SetVertices(const PODVector<Vector2>& vertices);
    /// Set vertices attribute.
    void SetVerticesAttr(const PODVector<unsigned char>& value);

    /// Return loop.
    bool GetLoop() const { return loop_; }
    /// Return vertex count.
    unsigned GetVertexCount() const { return vertices_.Size(); }
    /// Return vertex.
    const Vector2& GetVertex(unsigned index) const { return (index < vertices_.Size()) ? vertices_[index] : Vector2::ZERO; }
    /// Return vertices.
    const PODVector<Vector2>& GetVertices() const { return vertices_; }
    /// Return vertices attribute.
    PODVector<unsigned char> GetVerticesAttr() const;

private:
    /// Apply node world scale.
    virtual void ApplyNodeWorldScale();
    /// Recreate fixture.
    void RecreateFixture();

    /// Chain shape.
    b2ChainShape chainShape_;
    /// Loop.
    bool loop_;
    /// Vertices.
    PODVector<Vector2> vertices_;
};

}
