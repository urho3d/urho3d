// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include <Urho3D/Scene/LogicComponent.h>

// All Urho3D classes reside in namespace Urho3D
using namespace Urho3D;

const float MOVE_SPEED_X = 4.0f;
const int LIFES = 3;

/// Character2D component controling Imp behavior.
class Character2D : public LogicComponent
{
    URHO3D_OBJECT(Character2D, LogicComponent);

public:
    /// Construct.
    explicit Character2D(Context* context);

    /// Register object factory and attributes.
    static void RegisterObject(Context* context);

    /// Handle update. Called by LogicComponent base class.
    void Update(float timeStep) override;

    /// Handle player state/behavior when wounded.
    void HandleWoundedState(float timeStep);

    /// Handle death of the player.
    void HandleDeath();

    /// Flag when player is wounded.
    bool wounded_;
    /// Flag when player is dead.
    bool killed_;
    /// Timer for particle emitter duration.
    float timer_;
    /// Number of coins in the current level.
    int maxCoins_;
    /// Counter for remaining coins to pick.
    int remainingCoins_;
    /// Counter for remaining lifes.
    int remainingLifes_;
    /// Scaling factor based on tiles' aspect ratio (definitively set at tile map creation).
    float moveSpeedScale_;
    /// Camera's zoom (used to scale movement speed based on camera zoom).
    float zoom_;
};
