// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

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
