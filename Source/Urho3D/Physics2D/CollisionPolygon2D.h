// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include "../Physics2D/CollisionShape2D.h"

namespace Urho3D
{

/// 2D polygon collision component.
class URHO3D_API CollisionPolygon2D : public CollisionShape2D
{
    URHO3D_OBJECT(CollisionPolygon2D, CollisionShape2D);

public:
    /// Construct.
    explicit CollisionPolygon2D(Context* context);
    /// Destruct.
    ~CollisionPolygon2D() override;
    /// Register object factory.
    /// @nobind
    static void RegisterObject(Context* context);

    /// Set vertex count.
    /// @property
    void SetVertexCount(i32 count);
    /// Set vertex.
    void SetVertex(i32 index, const Vector2& vertex);
    /// Set vertices.
    void SetVertices(const Vector<Vector2>& vertices);

    /// Return vertex count.
    /// @property
    i32 GetVertexCount() const { return vertices_.Size(); }

    /// Return vertex.
    const Vector2& GetVertex(i32 index) const
    {
        assert(index >= 0);
        return (index < vertices_.Size()) ? vertices_[index] : Vector2::ZERO;
    }

    /// Return vertices.
    const Vector<Vector2>& GetVertices() const { return vertices_; }

    /// Set vertices attribute.
    void SetVerticesAttr(const Vector<byte>& value);
    /// Return vertices attribute.
    Vector<byte> GetVerticesAttr() const;

private:
    /// Apply node world scale.
    void ApplyNodeWorldScale() override;
    /// Recreate fixture.
    void RecreateFixture();

    /// Polygon shape.
    b2PolygonShape polygonShape_;
    /// Vertices.
    Vector<Vector2> vertices_;
};

}
