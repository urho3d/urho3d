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

#include <Urho3D/Core/Object.h>

using namespace Urho3D;

namespace Urho3D
{
    class Controls;
}

const float CAMERA_MIN_DIST = 1.0f;
const float CAMERA_INITIAL_DIST = 5.0f;
const float CAMERA_MAX_DIST = 20.0f;

/// Mobile framework for Android/iOS
/// Gamepad from NinjaSnowWar
/// Touches patterns:
///     - 1 finger touch  = pick object through raycast
///     - 1 or 2 fingers drag  = rotate camera
///     - 2 fingers sliding in opposite direction (up/down) = zoom in/out
///
/// Setup:
/// - Call the update function 'UpdateTouches()' from HandleUpdate or equivalent update handler function
class Touch : public Object
{
    URHO3D_OBJECT(Touch, Object);

public:
    /// Construct.
    Touch(Context* context, float touchSensitivity);
    /// Destruct.
    ~Touch() override;

    /// Update touch controls for the current frame.
    void UpdateTouches(Controls& controls);

    /// Touch sensitivity.
    float touchSensitivity_;
    /// Current camera zoom distance.
    float cameraDistance_;
    /// Zoom flag.
    bool zoom_;
    /// Gyroscope on/off flag.
    bool useGyroscope_;
};

