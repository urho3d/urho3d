// Copyright (c) 2008-2022 the Urho3D project
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
    void SetVertexCount(unsigned count);

    /// Return vertex count.
    /// @property
    unsigned GetVertexCount() const { return vertices_.Size(); }

    /// Set vertex.
    void SetVertex(unsigned index, const Vector2& vertex);

    /// Return vertex.
    const Vector2& GetVertex(unsigned index) const { return (index < vertices_.Size()) ? vertices_[index] : Vector2::ZERO; }

    /// Set vertices. For non loop first and last must be ghost.
    void SetVertices(const PODVector<Vector2>& vertices);

    /// Return vertices.
    const PODVector<Vector2>& GetVertices() const { return vertices_; }

    /// Set vertices attribute. For non loop first and last must be ghost.
    void SetVerticesAttr(const PODVector<unsigned char>& value);

    /// Return vertices attribute.
    PODVector<unsigned char> GetVerticesAttr() const;

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
    PODVector<Vector2> vertices_;
};

}
