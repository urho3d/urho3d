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
