//
// Copyright (c) 2008-2020 the Urho3D project.
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

#include <Urho3D/Input/Controls.h>
#include <Urho3D/Scene/LogicComponent.h>

namespace Urho3D
{

class Constraint;
class Node;
class RigidBody;

}

using namespace Urho3D;

const unsigned CTRL_FORWARD = 1;
const unsigned CTRL_BACK = 2;
const unsigned CTRL_LEFT = 4;
const unsigned CTRL_RIGHT = 8;

const float YAW_SENSITIVITY = 0.1f;
const float ENGINE_POWER = 10.0f;
const float DOWN_FORCE = 10.0f;
const float MAX_WHEEL_ANGLE = 22.5f;

/// Vehicle component, responsible for physical movement according to controls.
class Vehicle : public LogicComponent
{
    URHO3D_OBJECT(Vehicle, LogicComponent)

public:
    /// Construct.
    explicit Vehicle(Context* context);

    /// Register object factory and attributes.
    static void RegisterObject(Context* context);

    /// Perform post-load after deserialization. Acquire the components from the scene nodes.
    void ApplyAttributes() override;
    /// Handle physics world update. Called by LogicComponent base class.
    void FixedUpdate(float timeStep) override;

    /// Initialize the vehicle. Create rendering and physics components. Called by the application.
    void Init();

    /// Movement controls.
    Controls controls_;

private:
    /// Initialize a wheel and remember its scene node and ID.
    void InitWheel(const String& name, const Vector3& offset, WeakPtr<Node>& wheelNode, unsigned& wheelNodeID);
    /// Acquire wheel components from wheel scene nodes.
    void GetWheelComponents();

    /// Wheel scene front-left node.
    WeakPtr<Node> frontLeft_;
    /// Wheel scene front-right node.
    WeakPtr<Node> frontRight_;
    /// Wheel scene rear-left node.
    WeakPtr<Node> rearLeft_;
    /// Wheel scene rear-right node.
    WeakPtr<Node> rearRight_;

    /// Steering front-left axle constraint.
    WeakPtr<Constraint> frontLeftAxis_;
    /// Steering front-right axle constraint.
    WeakPtr<Constraint> frontRightAxis_;

    /// Hull and wheel hull rigid bodies.
    WeakPtr<RigidBody> hullBody_;
    /// Hull and wheel front-left rigid bodies.
    WeakPtr<RigidBody> frontLeftBody_;
    /// Hull and wheel front-right rigid bodies.
    WeakPtr<RigidBody> frontRightBody_;
    /// Hull and wheel rear-left rigid bodies.
    WeakPtr<RigidBody> rearLeftBody_;
    /// Hull and wheel rear-right rigid bodies.
    WeakPtr<RigidBody> rearRightBody_;

    /// ID of the front-left wheel scene node for serialization.
    unsigned frontLeftID_{};
    /// ID of the front-right wheel scene node for serialization.
    unsigned frontRightID_{};
    /// ID of the rear-left wheel scene node for serialization.
    unsigned rearLeftID_{};
    /// ID of the rear-right wheel scene node for serialization.
    unsigned rearRightID_{};

    /// Current left/right steering amount (-1 to 1).
    float steering_{};
};
