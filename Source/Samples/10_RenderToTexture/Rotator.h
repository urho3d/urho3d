// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include <Urho3D/Scene/LogicComponent.h>

// All Urho3D classes reside in namespace Urho3D
using namespace Urho3D;

/// Custom logic component for rotating a scene node.
class Rotator : public LogicComponent
{
    URHO3D_OBJECT(Rotator, LogicComponent);

public:
    /// Construct.
    explicit Rotator(Context* context);

    /// Set rotation speed about the Euler axes. Will be scaled with scene update time step.
    void SetRotationSpeed(const Vector3& speed);
    /// Handle scene update. Called by LogicComponent base class.
    void Update(float timeStep) override;

    /// Return rotation speed.
    const Vector3& GetRotationSpeed() const { return rotationSpeed_; }

private:
    /// Rotation speed.
    Vector3 rotationSpeed_;
};
