// Copyright (c) 2008-2023 the Urho3D project
// License: MIT

#pragma once

#include "../Physics2D/CollisionShape2D.h"

namespace Urho3D
{
/// 2D chain collision component.
class URHO3D_API CollisionChain2D : public CollisionShape2D
{
    URHO3D_OBJECT(CollisionChain2D, CollisionShape2D);

public:
    /// Construct.
    explicit CollisionChain2D(Context* context);

    /// Destruct.
    ~CollisionChain2D() override;

    /// Register object factory.
    /// @nobind
    static void RegisterObject(Context* context);

    /// Set loop.
    /// @property
    void SetLoop(bool loop);

    /// Return loop.
    /// @property
    bool GetLoop() const { return loop_; }

    /// Set vertex count.
    /// @property
    void SetVertexCount(i32 count);

    /// Return vertex count.
    /// @property
    i32 GetVertexCount() const { return vertices_.Size(); }

    /// Set vertex.
    void SetVertex(i32 index, const Vector2& vertex);

    /// Return vertex.
    const Vector2& GetVertex(i32 index) const
    {
        assert(index >= 0);
        return (index < vertices_.Size()) ? vertices_[index] : Vector2::ZERO;
    }

    /// Set vertices. For non loop first and last must be ghost.
    void SetVertices(const Vector<Vector2>& vertices);

    /// Return vertices.
    const Vector<Vector2>& GetVertices() const { return vertices_; }

    /// Set vertices attribute. For non loop first and last must be ghost.
    void SetVerticesAttr(const Vector<byte>& value);

    /// Return vertices attribute.
    Vector<byte> GetVerticesAttr() const;

private:
    /// Apply node world scale.
    void ApplyNodeWorldScale() override;

    /// Recreate fixture.
    void RecreateFixture();

    /// Chain shape.
    b2ChainShape chainShape_;

    /// Loop.
    bool loop_;

    /// Vertices.
    Vector<Vector2> vertices_;
};

}
