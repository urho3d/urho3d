//
// Urho3D Engine
// Copyright (c) 2008-2012 Lasse Öörni
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

#include <SDL_joystick.h>
#include <SDL_keycode.h>

/// Mouse button pressed.
EVENT(E_MOUSEBUTTONDOWN, MouseButtonDown)
{
    PARAM(P_BUTTON, Button);                // int
    PARAM(P_BUTTONS, Buttons);              // int
    PARAM(P_QUALIFIERS, Qualifiers);        // int
}

/// Mouse button released.
EVENT(E_MOUSEBUTTONUP, MouseButtonUp)
{
    PARAM(P_BUTTON, Button);                // int
    PARAM(P_BUTTONS, Buttons);              // int
    PARAM(P_QUALIFIERS, Qualifiers);        // int
}

/// Mouse moved.
EVENT(E_MOUSEMOVE, MouseMove)
{
    PARAM(P_DX, DX);                        // int
    PARAM(P_DY, DY);                        // int
    PARAM(P_BUTTONS, Buttons);              // int
    PARAM(P_QUALIFIERS, Qualifiers);        // int
}

/// Mouse wheel moved.
EVENT(E_MOUSEWHEEL, MouseWheel)
{
    PARAM(P_WHEEL, Wheel);                  // int
    PARAM(P_BUTTONS, Buttons);              // int
    PARAM(P_QUALIFIERS, Qualifiers);        // int
}

/// Key pressed.
EVENT(E_KEYDOWN, KeyDown)
{
    PARAM(P_KEY, Key);                      // int
    PARAM(P_BUTTONS, Buttons);              // int
    PARAM(P_QUALIFIERS, Qualifiers);        // int
    PARAM(P_REPEAT, Repeat);                // bool
}

/// Key released.
EVENT(E_KEYUP, KeyUp)
{
    PARAM(P_KEY, Key);                      // int
    PARAM(P_BUTTONS, Buttons);              // int
    PARAM(P_QUALIFIERS, Qualifiers);        // int
}

/// Character typed on the keyboard.
EVENT(E_CHAR, Char)
{
    PARAM(P_CHAR, Char);                    // int
    PARAM(P_BUTTONS, Buttons);              // int
    PARAM(P_QUALIFIERS, Qualifiers);        // int
}

/// Finger pressed on the screen.
EVENT(E_TOUCHBEGIN, TouchBegin)
{
    PARAM(P_TOUCHID, TouchID);              // int
    PARAM(P_X, X);                          // int
    PARAM(P_Y, Y);                          // int
    PARAM(P_PRESSURE, Pressure);            // int
}

/// Finger released from the screen.
EVENT(E_TOUCHEND, TouchEnd)
{
    PARAM(P_TOUCHID, TouchID);              // int
    PARAM(P_X, X);                          // int
    PARAM(P_Y, Y);                          // int
}

/// Finger moved on the screen.
EVENT(E_TOUCHMOVE, TouchMove)
{
    PARAM(P_TOUCHID, TouchID);              // int
    PARAM(P_X, X);                          // int
    PARAM(P_Y, Y);                          // int
    PARAM(P_DX, DX);                        // int
    PARAM(P_DY, DY);                        // int
    PARAM(P_PRESSURE, Pressure);            // int
}

/// Application activation state changed.
EVENT(E_ACTIVATION, Activation)
{
    PARAM(P_ACTIVE, Active);                // bool
    PARAM(P_MINIMIZED, Minimized);          // bool
}

static const int MOUSEB_LEFT = 1;
static const int MOUSEB_MIDDLE = 2;
static const int MOUSEB_RIGHT = 4;

static const int QUAL_SHIFT = 1;
static const int QUAL_CTRL = 2;
static const int QUAL_ALT = 4;
static const int QUAL_ANY = 8;

static const int KEY_BACKSPACE = SDLK_BACKSPACE;
static const int KEY_TAB = SDLK_TAB;
static const int KEY_RETURN = SDLK_RETURN;
static const int KEY_SHIFT = SDLK_LSHIFT;
static const int KEY_CTRL = SDLK_LCTRL;
static const int KEY_ALT = SDLK_LALT;
static const int KEY_PAUSE = SDLK_PAUSE;
static const int KEY_CAPSLOCK = SDLK_CAPSLOCK;
static const int KEY_ESC = SDLK_ESCAPE;
static const int KEY_SPACE = SDLK_SPACE;
static const int KEY_PAGEUP = SDLK_PAGEUP;
static const int KEY_PAGEDOWN = SDLK_PAGEDOWN;
static const int KEY_END = SDLK_END;
static const int KEY_HOME = SDLK_HOME;
static const int KEY_LEFT = SDLK_LEFT;
static const int KEY_UP = SDLK_UP;
static const int KEY_RIGHT = SDLK_RIGHT;
static const int KEY_DOWN = SDLK_DOWN;
static const int KEY_SELECT = SDLK_SELECT;
static const int KEY_PRINTSCREEN = SDLK_PRINTSCREEN;
static const int KEY_INSERT = SDLK_INSERT;
static const int KEY_DELETE = SDLK_DELETE;
static const int KEY_LWIN = SDLK_LGUI;
static const int KEY_RWIN = SDLK_RGUI;
static const int KEY_APPS = SDLK_APPLICATION;
static const int KEY_NUMPAD0 = SDLK_KP_0;
static const int KEY_NUMPAD1 = SDLK_KP_1;
static const int KEY_NUMPAD2 = SDLK_KP_2;
static const int KEY_NUMPAD3 = SDLK_KP_3;
static const int KEY_NUMPAD4 = SDLK_KP_4;
static const int KEY_NUMPAD5 = SDLK_KP_5;
static const int KEY_NUMPAD6 = SDLK_KP_6;
static const int KEY_NUMPAD7 = SDLK_KP_7;
static const int KEY_NUMPAD8 = SDLK_KP_8;
static const int KEY_NUMPAD9 = SDLK_KP_9;
static const int KEY_MULTIPLY = SDLK_KP_MULTIPLY;
static const int KEY_ADD = SDLK_KP_PLUS;
static const int KEY_SUBTRACT = SDLK_KP_MINUS;
static const int KEY_DECIMAL = SDLK_KP_PERIOD;
static const int KEY_DIVIDE = SDLK_KP_DIVIDE;
static const int KEY_F1 = SDLK_F1;
static const int KEY_F2 = SDLK_F2;
static const int KEY_F3 = SDLK_F3;
static const int KEY_F4 = SDLK_F4;
static const int KEY_F5 = SDLK_F5;
static const int KEY_F6 = SDLK_F6;
static const int KEY_F7 = SDLK_F7;
static const int KEY_F8 = SDLK_F8;
static const int KEY_F9 = SDLK_F9;
static const int KEY_F10 = SDLK_F10;
static const int KEY_F11 = SDLK_F11;
static const int KEY_F12 = SDLK_F12;
static const int KEY_F13 = SDLK_F13;
static const int KEY_F14 = SDLK_F14;
static const int KEY_F15 = SDLK_F15;
static const int KEY_F16 = SDLK_F16;
static const int KEY_F17 = SDLK_F17;
static const int KEY_F18 = SDLK_F18;
static const int KEY_F19 = SDLK_F19;
static const int KEY_F20 = SDLK_F20;
static const int KEY_F21 = SDLK_F21;
static const int KEY_F22 = SDLK_F22;
static const int KEY_F23 = SDLK_F23;
static const int KEY_F24 = SDLK_F24;
static const int KEY_NUMLOCK = SDLK_NUMLOCKCLEAR;
static const int KEY_SCROLLLOCK = SDLK_SCROLLLOCK;
static const int KEY_LSHIFT = SDLK_LSHIFT;
static const int KEY_RSHIFT = SDLK_RSHIFT;
static const int KEY_LCTRL = SDLK_LCTRL;
static const int KEY_RCTRL = SDLK_RCTRL;
static const int KEY_LALT = SDLK_LALT;
static const int KEY_RALT = SDLK_RALT;

static const int HAT_CENTER = SDL_HAT_CENTERED;
static const int HAT_UP = SDL_HAT_UP;
static const int HAT_RIGHT = SDL_HAT_RIGHT;
static const int HAT_DOWN = SDL_HAT_DOWN;
static const int HAT_LEFT = SDL_HAT_LEFT;
