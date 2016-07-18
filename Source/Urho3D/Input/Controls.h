//
// Copyright (c) 2008-2016 the Urho3D project.
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
