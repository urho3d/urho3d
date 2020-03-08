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

#include <Urho3D/Scene/LogicComponent.h>

// All Urho3D classes reside in namespace Urho3D
using namespace Urho3D;

/// Mover logic component
///    - Handles entity (enemy, platform...) translation along a path (set of Vector2 points)
///    - Supports looping paths and animation flip
///    - Default speed is 0.8 if 'Speed' property is not set in the tmx file objects
class Mover : public LogicComponent
{
    URHO3D_OBJECT(Mover, LogicComponent);

public:
    /// Construct.
    explicit Mover(Context* context);

    /// Register object factory and attributes.
    static void RegisterObject(Context* context);

    /// Handle scene update. Called by LogicComponent base class.
    void Update(float timeStep) override;
    /// Return path attribute.
    PODVector<unsigned char> GetPathAttr() const;
    /// Set path attribute.
    void SetPathAttr(const PODVector<unsigned char>& value);

    /// Path.
    PODVector<Vector2> path_;
    /// Movement speed.
    float speed_;
    /// ID of the current path point.
    int currentPathID_;
    /// Timer for particle emitter duration.
    float emitTime_;
    /// Timer used for handling "attack" animation.
    float fightTimer_;
    /// Flip animation based on direction, or player position when fighting.
    float flip_;
};
