//
// Copyright (c) 2008-2022 the Urho3D project.
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

#include "../Physics2D/CollisionShape2D.h"

namespace Urho3D
{

/// 2D circle collision component.
class URHO3D_API CollisionCircle2D : public CollisionShape2D
{
    URHO3D_OBJECT(CollisionCircle2D, CollisionShape2D);

public:
    /// Construct.
    explicit CollisionCircle2D(Context* context);
    /// Destruct.
    ~CollisionCircle2D() override;
    /// Register object factory.
    /// @nobind
    static void RegisterObject(Context* context);

    /// Set radius.
    /// @property
    void SetRadius(float radius);
    /// Set center.
    /// @property
    void SetCenter(const Vector2& center);
    /// Set center.
    void SetCenter(float x, float y);

    /// Return radius.
    /// @property
    float GetRadius() const { return radius_; }

    /// Return center.
    /// @property
    const Vector2& GetCenter() const { return center_; }

private:
    /// Apply node world scale.
    void ApplyNodeWorldScale() override;
    /// Recreate fixture.
    void RecreateFixture();

    /// Circle shape.
    b2CircleShape circleShape_;
    /// Radius.
    float radius_;
    /// Center.
    Vector2 center_;
};

}
