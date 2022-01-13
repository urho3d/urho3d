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

#include "../Scene/Component.h"

#include <Box2D/Box2D.h>

namespace Urho3D
{

class RigidBody2D;

/// 2D collision shape component.
class URHO3D_API CollisionShape2D : public Component
{
    URHO3D_OBJECT(CollisionShape2D, Component);

public:
    /// Construct.
    explicit CollisionShape2D(Context* context);
    /// Destruct.
    ~CollisionShape2D() override;
    /// Register object factory.
    /// @nobind
    static void RegisterObject(Context* context);

    /// Handle enabled/disabled state change.
    void OnSetEnabled() override;

    /// Set trigger.
    /// @property
    void SetTrigger(bool trigger);
    /// Set filter category bits.
    /// @property
    void SetCategoryBits(int categoryBits);
    /// Set filter mask bits.
    /// @property
    void SetMaskBits(int maskBits);
    /// Set filter group index.
    /// @property
    void SetGroupIndex(int groupIndex);
    /// Set density.
    /// @property
    void SetDensity(float density);
    /// Set friction.
    /// @property
    void SetFriction(float friction);
    /// Set restitution.
    /// @property
    void SetRestitution(float restitution);

    /// Create fixture.
    void CreateFixture();
    /// Release fixture.
    void ReleaseFixture();

    /// Return trigger.
    /// @property
    bool IsTrigger() const { return fixtureDef_.isSensor; }

    /// Return filter category bits.
    /// @property
    int GetCategoryBits() const { return fixtureDef_.filter.categoryBits; }

    /// Return filter mask bits.
    /// @property
    int GetMaskBits() const { return fixtureDef_.filter.maskBits; }

    /// Return filter group index.
    /// @property
    int GetGroupIndex() const { return fixtureDef_.filter.groupIndex; }

    /// Return density.
    /// @property
    float GetDensity() const { return fixtureDef_.density; }

    /// Return friction.
    /// @property
    float GetFriction() const { return fixtureDef_.friction; }

    /// Return restitution.
    /// @property
    float GetRestitution() const { return fixtureDef_.restitution; }

    /// Return mass.
    /// @property
    float GetMass() const;
    /// Return inertia.
    /// @property
    float GetInertia() const;
    /// Return mass center.
    /// @property
    Vector2 GetMassCenter() const;

    /// Return fixture.
    b2Fixture* GetFixture() const { return fixture_; }

protected:
    /// Handle node being assigned.
    void OnNodeSet(Node* node) override;
    /// Handle node transform being dirtied.
    void OnMarkedDirty(Node* node) override;
    /// Apply Node world scale.
    virtual void ApplyNodeWorldScale() = 0;

    /// Rigid body.
    WeakPtr<RigidBody2D> rigidBody_;
    /// Fixture def.
    b2FixtureDef fixtureDef_;
    /// Box2D fixture.
    b2Fixture* fixture_;
    /// Cached world scale.
    Vector3 cachedWorldScale_;
};

}
