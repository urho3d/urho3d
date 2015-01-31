//
// Copyright (c) 2008-2015 the Urho3D project.
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

#include <Urho3D/Network/Controls.h>
#include <Urho3D/Scene/LogicComponent.h>

namespace Urho3D
{

class Constraint;
class Node;
class RigidBody;

}

using namespace Urho3D;

const int CTRL_FORWARD = 1;
const int CTRL_BACK = 2;
const int CTRL_LEFT = 4;
const int CTRL_RIGHT = 8;

const float YAW_SENSITIVITY = 0.1f;
const float ENGINE_POWER = 10.0f;
const float DOWN_FORCE = 10.0f;
const float MAX_WHEEL_ANGLE = 22.5f;

/// Vehicle component, responsible for physical movement according to controls.
class Vehicle : public LogicComponent
{
    OBJECT(Vehicle)

public:
    /// Construct.
    Vehicle(Context* context);
    
    /// Register object factory and attributes.
    static void RegisterObject(Context* context);
    
    /// Perform post-load after deserialization. Acquire the components from the scene nodes.
    virtual void ApplyAttributes();
    /// Handle physics world update. Called by LogicComponent base class.
    virtual void FixedUpdate(float timeStep);
    
    /// Initialize the vehicle. Create rendering and physics components. Called by the application.
    void Init();
    
    /// Movement controls.
    Controls controls_;
    
private:
    /// Initialize a wheel and remember its scene node and ID.
    void InitWheel(const String& name, const Vector3& offset, WeakPtr<Node>& wheelNode, unsigned& wheelNodeID);
    /// Acquire wheel components from wheel scene nodes.
    void GetWheelComponents();

    
    // Wheel scene nodes.
    WeakPtr<Node> frontLeft_;
    WeakPtr<Node> frontRight_;
    WeakPtr<Node> rearLeft_;
    WeakPtr<Node> rearRight_;
    
    // Steering axle constraints.
    WeakPtr<Constraint> frontLeftAxis_;
    WeakPtr<Constraint> frontRightAxis_;
    
    // Hull and wheel rigid bodies.
    WeakPtr<RigidBody> hullBody_;
    WeakPtr<RigidBody> frontLeftBody_;
    WeakPtr<RigidBody> frontRightBody_;
    WeakPtr<RigidBody> rearLeftBody_;
    WeakPtr<RigidBody> rearRightBody_;
    
    // IDs of the wheel scene nodes for serialization.
    unsigned frontLeftID_;
    unsigned frontRightID_;
    unsigned rearLeftID_;
    unsigned rearRightID_;
    
    /// Current left/right steering amount (-1 to 1.)
    float steering_;
};
