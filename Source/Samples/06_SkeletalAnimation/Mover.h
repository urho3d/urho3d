// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include <Urho3D/Scene/LogicComponent.h>

using namespace Urho3D;

/// Custom logic component for moving the animated model and rotating at area edges.
class Mover : public LogicComponent
{
    URHO3D_OBJECT(Mover, LogicComponent);

public:
    /// Construct.
    explicit Mover(Context* context);

    /// Set motion parameters: forward movement speed, rotation speed, and movement boundaries.
    void SetParameters(float moveSpeed, float rotationSpeed, const BoundingBox& bounds);
    /// Handle scene update. Called by LogicComponent base class.
    void Update(float timeStep) override;

    /// Return forward movement speed.
    float GetMoveSpeed() const { return moveSpeed_; }
    /// Return rotation speed.
    float GetRotationSpeed() const { return rotationSpeed_; }
    /// Return movement boundaries.
    const BoundingBox& GetBounds() const { return bounds_; }

private:
    /// Forward movement speed.
    float moveSpeed_;
    /// Rotation speed.
    float rotationSpeed_;
    /// Movement boundaries.
    BoundingBox bounds_;
};
