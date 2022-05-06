// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include "../Core/Variant.h"

namespace Urho3D
{

/// %Controls sent over the network.
class URHO3D_API Controls
{
public:
    /// Construct.
    Controls();
    /// Destruct.
    ~Controls();

    /// Reset to initial state.
    void Reset();

    /// Set or release buttons.
    void Set(unsigned buttons, bool down = true)
    {
        if (down)
            buttons_ |= buttons;
        else
            buttons_ &= ~buttons;
    }

    /// Check if a button is held down.
    bool IsDown(unsigned button) const
    {
        return (buttons_ & button) != 0;
    }

    /// Check if a button was pressed on this frame. Requires previous frame's controls.
    bool IsPressed(unsigned button, const Controls& previousControls) const
    {
        return (buttons_ & button) != 0 && (previousControls.buttons_ & button) == 0;
    }

    /// Button state.
    unsigned buttons_;
    /// Mouse yaw.
    float yaw_;
    /// Mouse pitch.
    float pitch_;
    /// Extra control data.
    VariantMap extraData_;
};

}
