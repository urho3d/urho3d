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

#include "../Core/Object.h"
#include "../Input/InputConstants.h"


namespace Urho3D
{

/// Mouse button pressed.
URHO3D_EVENT(E_MOUSEBUTTONDOWN, MouseButtonDown)
{
    URHO3D_PARAM(P_BUTTON, Button);                // int
    URHO3D_PARAM(P_BUTTONS, Buttons);              // int
    URHO3D_PARAM(P_QUALIFIERS, Qualifiers);        // int
}

/// Mouse button released.
URHO3D_EVENT(E_MOUSEBUTTONUP, MouseButtonUp)
{
    URHO3D_PARAM(P_BUTTON, Button);                // int
    URHO3D_PARAM(P_BUTTONS, Buttons);              // int
    URHO3D_PARAM(P_QUALIFIERS, Qualifiers);        // int
}

/// Mouse moved.
URHO3D_EVENT(E_MOUSEMOVE, MouseMove)
{
    URHO3D_PARAM(P_X, X);                          // int (only when mouse visible)
    URHO3D_PARAM(P_Y, Y);                          // int (only when mouse visible)
    URHO3D_PARAM(P_DX, DX);                        // int
    URHO3D_PARAM(P_DY, DY);                        // int
    URHO3D_PARAM(P_BUTTONS, Buttons);              // int
    URHO3D_PARAM(P_QUALIFIERS, Qualifiers);        // int
}

/// Mouse wheel moved.
URHO3D_EVENT(E_MOUSEWHEEL, MouseWheel)
{
    URHO3D_PARAM(P_WHEEL, Wheel);                  // int
    URHO3D_PARAM(P_BUTTONS, Buttons);              // int
    URHO3D_PARAM(P_QUALIFIERS, Qualifiers);        // int
}

/// Key pressed.
URHO3D_EVENT(E_KEYDOWN, KeyDown)
{
    URHO3D_PARAM(P_KEY, Key);                      // int
    URHO3D_PARAM(P_SCANCODE, Scancode);            // int
    URHO3D_PARAM(P_BUTTONS, Buttons);              // int
    URHO3D_PARAM(P_QUALIFIERS, Qualifiers);        // int
    URHO3D_PARAM(P_REPEAT, Repeat);                // bool
}

/// Key released.
URHO3D_EVENT(E_KEYUP, KeyUp)
{
    URHO3D_PARAM(P_KEY, Key);                      // int
    URHO3D_PARAM(P_SCANCODE, Scancode);            // int
    URHO3D_PARAM(P_BUTTONS, Buttons);              // int
    URHO3D_PARAM(P_QUALIFIERS, Qualifiers);        // int
}

/// Text input event.
URHO3D_EVENT(E_TEXTINPUT, TextInput)
{
    URHO3D_PARAM(P_TEXT, Text);                    // String
}

/// Text editing event.
URHO3D_EVENT(E_TEXTEDITING, TextEditing)
{
    URHO3D_PARAM(P_COMPOSITION, Composition);      // String
    URHO3D_PARAM(P_CURSOR, Cursor);                // int
    URHO3D_PARAM(P_SELECTION_LENGTH, SelectionLength);  // int
}

/// Joystick connected.
URHO3D_EVENT(E_JOYSTICKCONNECTED, JoystickConnected)
{
    URHO3D_PARAM(P_JOYSTICKID, JoystickID);        // int
}

/// Joystick disconnected.
URHO3D_EVENT(E_JOYSTICKDISCONNECTED, JoystickDisconnected)
{
    URHO3D_PARAM(P_JOYSTICKID, JoystickID);        // int
}

/// Joystick button pressed.
URHO3D_EVENT(E_JOYSTICKBUTTONDOWN, JoystickButtonDown)
{
    URHO3D_PARAM(P_JOYSTICKID, JoystickID);        // int
    URHO3D_PARAM(P_BUTTON, Button);                // int
}

/// Joystick button released.
URHO3D_EVENT(E_JOYSTICKBUTTONUP, JoystickButtonUp)
{
    URHO3D_PARAM(P_JOYSTICKID, JoystickID);        // int
    URHO3D_PARAM(P_BUTTON, Button);                // int
}

/// Joystick axis moved.
URHO3D_EVENT(E_JOYSTICKAXISMOVE, JoystickAxisMove)
{
    URHO3D_PARAM(P_JOYSTICKID, JoystickID);        // int
    URHO3D_PARAM(P_AXIS, Button);                  // int
    URHO3D_PARAM(P_POSITION, Position);            // float
}

/// Joystick POV hat moved.
URHO3D_EVENT(E_JOYSTICKHATMOVE, JoystickHatMove)
{
    URHO3D_PARAM(P_JOYSTICKID, JoystickID);        // int
    URHO3D_PARAM(P_HAT, Button);                   // int
    URHO3D_PARAM(P_POSITION, Position);            // int
}

/// Finger pressed on the screen.
URHO3D_EVENT(E_TOUCHBEGIN, TouchBegin)
{
    URHO3D_PARAM(P_TOUCHID, TouchID);              // int
    URHO3D_PARAM(P_X, X);                          // int
    URHO3D_PARAM(P_Y, Y);                          // int
    URHO3D_PARAM(P_PRESSURE, Pressure);            // float
}

/// Finger released from the screen.
URHO3D_EVENT(E_TOUCHEND, TouchEnd)
{
    URHO3D_PARAM(P_TOUCHID, TouchID);              // int
    URHO3D_PARAM(P_X, X);                          // int
    URHO3D_PARAM(P_Y, Y);                          // int
}

/// Finger moved on the screen.
URHO3D_EVENT(E_TOUCHMOVE, TouchMove)
{
    URHO3D_PARAM(P_TOUCHID, TouchID);              // int
    URHO3D_PARAM(P_X, X);                          // int
    URHO3D_PARAM(P_Y, Y);                          // int
    URHO3D_PARAM(P_DX, DX);                        // int
    URHO3D_PARAM(P_DY, DY);                        // int
    URHO3D_PARAM(P_PRESSURE, Pressure);            // float
}

/// A touch gesture finished recording.
URHO3D_EVENT(E_GESTURERECORDED, GestureRecorded)
{
    URHO3D_PARAM(P_GESTUREID, GestureID);          // unsigned
}

/// A recognized touch gesture was input by the user.
URHO3D_EVENT(E_GESTUREINPUT, GestureInput)
{
    URHO3D_PARAM(P_GESTUREID, GestureID);          // unsigned
    URHO3D_PARAM(P_CENTERX, CenterX);              // int
    URHO3D_PARAM(P_CENTERY, CenterY);              // int
    URHO3D_PARAM(P_NUMFINGERS, NumFingers);        // int
    URHO3D_PARAM(P_ERROR, Error);                  // float
}

/// Pinch/rotate multi-finger touch gesture motion update.
URHO3D_EVENT(E_MULTIGESTURE, MultiGesture)
{
    URHO3D_PARAM(P_CENTERX, CenterX);              // int
    URHO3D_PARAM(P_CENTERY, CenterY);              // int
    URHO3D_PARAM(P_NUMFINGERS, NumFingers);        // int
    URHO3D_PARAM(P_DTHETA, DTheta);                // float (degrees)
    URHO3D_PARAM(P_DDIST, DDist);                  // float
}

/// A file was drag-dropped into the application window.
URHO3D_EVENT(E_DROPFILE, DropFile)
{
    URHO3D_PARAM(P_FILENAME, FileName);            // String
}

/// Application input focus or minimization changed.
URHO3D_EVENT(E_INPUTFOCUS, InputFocus)
{
    URHO3D_PARAM(P_FOCUS, Focus);                  // bool
    URHO3D_PARAM(P_MINIMIZED, Minimized);          // bool
}

/// OS mouse cursor visibility changed.
URHO3D_EVENT(E_MOUSEVISIBLECHANGED, MouseVisibleChanged)
{
    URHO3D_PARAM(P_VISIBLE, Visible);              // bool
}

/// Mouse mode changed.
URHO3D_EVENT(E_MOUSEMODECHANGED, MouseModeChanged)
{
    URHO3D_PARAM(P_MODE, Mode);                    // MouseMode
    URHO3D_PARAM(P_MOUSELOCKED, MouseLocked);      // bool
}

/// Application exit requested.
URHO3D_EVENT(E_EXITREQUESTED, ExitRequested)
{
}

/// Raw SDL input event.
URHO3D_EVENT(E_SDLRAWINPUT, SDLRawInput)
{
    URHO3D_PARAM(P_SDLEVENT, SDLEvent);           // SDL_Event*
    URHO3D_PARAM(P_CONSUMED, Consumed);           // bool
}

/// Input handling begins.
URHO3D_EVENT(E_INPUTBEGIN, InputBegin)
{
}

/// Input handling ends.
URHO3D_EVENT(E_INPUTEND, InputEnd)
{
}

}
