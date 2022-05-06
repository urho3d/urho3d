// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include "../Physics2D/CollisionShape2D.h"

namespace Urho3D
{

/// 2D edge collision component.
class URHO3D_API CollisionEdge2D : public CollisionShape2D
{
    URHO3D_OBJECT(CollisionEdge2D, CollisionShape2D);

public:
    /// Construct.
    explicit CollisionEdge2D(Context* context);
    /// Destruct.
    ~CollisionEdge2D() override;
    /// Register object factory.
    /// @nobind
    static void RegisterObject(Context* context);

    /// Set vertex 1.
    /// @property
    void SetVertex1(const Vector2& vertex);
    /// Set vertex 2.
    /// @property
    void SetVertex2(const Vector2& vertex);
    /// Set vertices.
    void SetVertices(const Vector2& vertex1, const Vector2& vertex2);

    /// Return vertex 1.
    /// @property
    const Vector2& GetVertex1() const { return vertex1_; }

    /// Return vertex 2.
    /// @property
    const Vector2& GetVertex2() const { return vertex2_; }

private:
    /// Apply node world scale.
    void ApplyNodeWorldScale() override;
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
