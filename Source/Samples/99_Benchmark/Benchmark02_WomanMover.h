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

#include <Urho3D/Scene/LogicComponent.h>
#include <Urho3D/Math/BoundingBox.h>

namespace U3D = Urho3D;

// Custom logic component for moving the animated model and rotating at area edges
class Benchmark02_WomanMover : public U3D::LogicComponent
{
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
