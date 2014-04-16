//
// Copyright (c) 2008-2014 the Urho3D project.
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

#include "Object.h"

using namespace Urho3D;

namespace Urho3D
{
    class BorderImage;
    class Controls;
    class Node;
    class Scene;
}

const float TOUCH_SENSITIVITY_TODO = 5.0f;
const float GYROSCOPE_THRESHOLD = 0.1f;
const float CAMERA_MIN_DIST = 1.0f;
const float CAMERA_INITIAL_DIST = 5.0f;
const float CAMERA_MAX_DIST = 20.0f;

/// Mobile framework for Android/iOS
/// Gamepad from NinjaSnowWar
/// Gyroscope (activated by default)
/// Touches patterns:
///     - 1 finger touch  = pick object through raycast
///     - 1 or 2 fingers drag  = rotate camera
///     - 3 fingers touch = switch between first/third person view
///     - 4 fingers touch = switch shadows on/off
///     - 2 fingers sliding in opposite direction (up/down) = zoom in/out
///
/// 3 fingers touch & 4 fingers touch could be used to switch gyroscope on/off, activate/deactivate secondary viewport, activate a panel GUI, switch debug HUD/geometry, toggle console, switch the gyroscope...
///
/// Setup:
/// - On init, call 'InitTouchInput()' on mobile platforms and also set the scene_ & cameraNode_ member variables
///   -> to detect platform, use 'if (GetPlatform() == "Android" || GetPlatform() == "iOS")' from ProcessUtils.h
/// - Subscribe to touch events (Begin, Move, End) using 'SubscribeToTouchEvents()'
/// - Call the update function 'UpdateTouches()' from HandleUpdate or equivalent update handler function
class Touch : public Object
{
    OBJECT(Touch);

public:
    /// Construct.
    Touch(Context* context);
    /// Destruct.
    ~Touch();

    /// Initialize the touch UI.
    void InitTouchInput();
    /// Start responding to touch events.
    void SubscribeToTouchEvents();
    /// Update touch controls for the current frame.
    void UpdateTouches(Controls& controls);
    /// Handle finger touch begin.
    void HandleTouchBegin(StringHash eventType, VariantMap& eventData);
    /// Handle finger touch end.
    void HandleTouchEnd(StringHash eventType, VariantMap& eventData);

    /// Scene. Needs to be assigned by the application.
    WeakPtr<Scene> scene_;
    /// Camera node. Needs to be assigned by the application.
    WeakPtr<Node> cameraNode_;
    /// On-screen gamepad move button (left side.)
    WeakPtr<BorderImage> moveButton_;
    /// On-screen gamepad fire/jump button (right side.)
    WeakPtr<BorderImage> fireButton_;
    /// Size of gamepad buttons.
    int touchButtonSize_;
    /// Distance of gamepad buttons from the screen corners.
    int touchButtonBorder_;
    /// Current ID of the move touch, or -1 for none.
    int moveTouchID_;
    /// Current ID of the rotate touch, or -1 for none.
    int rotateTouchID_;
    /// Current ID of the fire/jump touch, or -1 for none.
    int fireTouchID_;
    /// Current camera zoom distance.
    float cameraDistance_;
    /// Current first person mode flag.
    bool firstPerson_;
    /// Pending new first person mode flag.
    bool newFirstPerson_;
    /// Pending new shadow mode flag.
    bool shadowMode_;
    /// Zoom flag.
    bool zoom_;
    /// Touch input initialized flag.
    bool touchEnabled_;
};

