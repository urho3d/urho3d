// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include <Urho3D/Scene/LogicComponent.h>
#include <Urho3D/Math/BoundingBox.h>

namespace U3D = Urho3D;

// Custom logic component for moving the animated model and rotating at area edges
class Benchmark02_WomanMover : public U3D::LogicComponent
{
public:
    URHO3D_OBJECT(Benchmark02_WomanMover, LogicComponent);

private:
    // Forward movement speed
    float moveSpeed_;
    
    // Rotation speed
    float rotationSpeed_;
    
    // Movement boundaries
    U3D::BoundingBox bounds_;

public:
    explicit Benchmark02_WomanMover(U3D::Context* context);

    // Set motion parameters: forward movement speed, rotation speed, and movement boundaries
    void SetParameters(float moveSpeed, float rotationSpeed, const U3D::BoundingBox& bounds);
    
    // Handle scene update. Called by LogicComponent base class
    void Update(float timeStep) override;

    // Return forward movement speed
    float GetMoveSpeed() const { return moveSpeed_; }
    
    // Return rotation speed
    float GetRotationSpeed() const { return rotationSpeed_; }
    
    // Return movement boundaries
    const U3D::BoundingBox& GetBounds() const { return bounds_; }
};
