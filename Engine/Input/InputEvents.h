//
// Urho3D Engine
// Copyright (c) 2008-2011 Lasse Öörni
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

#ifdef USE_OPENGL
#include <GL/glfw3.h>
#endif

/// Mouse button pressed.
EVENT(E_MOUSEBUTTONDOWN, MouseButtonDown)
{
    PARAM(P_BUTTON, Button);              // int
    PARAM(P_BUTTONS, Buttons);            // int
    PARAM(P_QUALIFIERS, Qualifiers);      // int
}

/// Mouse button released.
EVENT(E_MOUSEBUTTONUP, MouseButtonUp)
{
    PARAM(P_BUTTON, Button);              // int
    PARAM(P_BUTTONS, Buttons);            // int
    PARAM(P_QUALIFIERS, Qualifiers);      // int
}

/// Mouse moved.
EVENT(E_MOUSEMOVE, MouseMove)
{
    PARAM(P_DX, DX);                      // int
    PARAM(P_DY, DY);                      // int
    PARAM(P_BUTTONS, Buttons);            // int
    PARAM(P_QUALIFIERS, Qualifiers);      // int
}

/// Mouse wheel moved.
EVENT(E_MOUSEWHEEL, MouseWheel)
{
    PARAM(P_WHEEL, Wheel);                // int
    PARAM(P_BUTTONS, Buttons);            // int
    PARAM(P_QUALIFIERS, Qualifiers);      // int
}

/// Key pressed.
EVENT(E_KEYDOWN, KeyDown)
{
    PARAM(P_KEY, Key);                    // int
    PARAM(P_BUTTONS, Buttons);            // int
    PARAM(P_QUALIFIERS, Qualifiers);      // int
    PARAM(P_REPEAT, Repeat);              // bool
}

/// Key released.
EVENT(E_KEYUP, KeyUp)
{
    PARAM(P_KEY, Key);                    // int
    PARAM(P_BUTTONS, Buttons);            // int
    PARAM(P_QUALIFIERS, Qualifiers);      // int
}

/// Character typed on the keyboard.
EVENT(E_CHAR, Char)
{
    PARAM(P_CHAR, Char);                  // int
    PARAM(P_BUTTONS, Buttons);            // int
    PARAM(P_QUALIFIERS, Qualifiers);      // int
}

/// Application activation state changed.
EVENT(E_ACTIVATION, Activation)
{
    PARAM(P_ACTIVE, Active);              // bool
    PARAM(P_MINIMIZED, Minimized);        // bool
}

static const int MOUSEB_LEFT = 1;
static const int MOUSEB_RIGHT = 2;
static const int MOUSEB_MIDDLE = 4;

static const int QUAL_SHIFT = 1;
static const int QUAL_CTRL = 2;
static const int QUAL_ALT = 4;

#ifndef USE_OPENGL
static const int KEY_BACKSPACE = 0x08;
static const int KEY_TAB = 0x09;
static const int KEY_RETURN = 0x0d;
static const int KEY_PAUSE = 0x13;
static const int KEY_CAPSLOCK = 0x14;
static const int KEY_ESC = 0x1b;
static const int KEY_SPACE = 0x20;
static const int KEY_PAGEUP = 0x21;
static const int KEY_PAGEDOWN = 0x22;
static const int KEY_END = 0x23;
static const int KEY_HOME = 0x24;
static const int KEY_LEFT = 0x25;
static const int KEY_UP = 0x26;
static const int KEY_RIGHT = 0x27;
static const int KEY_DOWN = 0x28;
static const int KEY_INSERT = 0x2d;
static const int KEY_DELETE = 0x2e;
static const int KEY_LWIN = 0x5b;
static const int KEY_RWIN = 0x5c;
static const int KEY_APPS = 0x5d;
static const int KEY_NUMPAD0 = 0x60;
static const int KEY_NUMPAD1 = 0x61;
static const int KEY_NUMPAD2 = 0x62;
static const int KEY_NUMPAD3 = 0x63;
static const int KEY_NUMPAD4 = 0x64;
static const int KEY_NUMPAD5 = 0x65;
static const int KEY_NUMPAD6 = 0x66;
static const int KEY_NUMPAD7 = 0x67;
static const int KEY_NUMPAD8 = 0x68;
static const int KEY_NUMPAD9 = 0x69;
static const int KEY_MULTIPLY = 0x6a;
static const int KEY_ADD = 0x6b;
static const int KEY_SUBTRACT = 0x6d;
static const int KEY_DECIMAL = 0x6e;
static const int KEY_DIVIDE = 0x6f;
static const int KEY_F1 = 0x70;
static const int KEY_F2 = 0x71;
static const int KEY_F3 = 0x72;
static const int KEY_F4 = 0x73;
static const int KEY_F5 = 0x74;
static const int KEY_F6 = 0x75;
static const int KEY_F7 = 0x76;
static const int KEY_F8 = 0x77;
static const int KEY_F9 = 0x78;
static const int KEY_F10 = 0x79;
static const int KEY_F11 = 0x7a;
static const int KEY_F12 = 0x7b;
static const int KEY_F13 = 0x7c;
static const int KEY_F14 = 0x7d;
static const int KEY_F15 = 0x7e;
static const int KEY_F16 = 0x7f;
static const int KEY_F17 = 0x80;
static const int KEY_F18 = 0x81;
static const int KEY_F19 = 0x82;
static const int KEY_F20 = 0x83;
static const int KEY_F21 = 0x84;
static const int KEY_F22 = 0x85;
static const int KEY_F23 = 0x86;
static const int KEY_F24 = 0x87;
static const int KEY_NUMLOCK = 0x90;
static const int KEY_SCROLLLOCK = 0x91;
static const int KEY_LSHIFT = 0xa0;
static const int KEY_RSHIFT = 0xa1;
static const int KEY_LCTRL = 0xa2;
static const int KEY_RCTRL = 0xa3;
static const int KEY_LALT = 0xa4;
static const int KEY_RALT = 0xa5;
#else
static const int KEY_BACKSPACE = GLFW_KEY_BACKSPACE;
static const int KEY_TAB = GLFW_KEY_TAB;
static const int KEY_RETURN = GLFW_KEY_ENTER;
static const int KEY_PAUSE = GLFW_KEY_PAUSE;
static const int KEY_CAPSLOCK = GLFW_KEY_CAPS_LOCK;
static const int KEY_ESC = GLFW_KEY_ESC;
static const int KEY_SPACE = GLFW_KEY_SPACE;
static const int KEY_PAGEUP = GLFW_KEY_PAGEUP;
static const int KEY_PAGEDOWN = GLFW_KEY_PAGEDOWN;
static const int KEY_END = GLFW_KEY_END;
static const int KEY_HOME = GLFW_KEY_HOME;
static const int KEY_LEFT = GLFW_KEY_LEFT;
static const int KEY_UP = GLFW_KEY_UP;
static const int KEY_RIGHT = GLFW_KEY_RIGHT;
static const int KEY_DOWN = GLFW_KEY_DOWN;
static const int KEY_INSERT = GLFW_KEY_INSERT;
static const int KEY_DELETE = GLFW_KEY_DEL;
static const int KEY_LWIN = GLFW_KEY_LSUPER;
static const int KEY_RWIN = GLFW_KEY_RSUPER;
static const int KEY_APPS = GLFW_KEY_MENU;
static const int KEY_NUMPAD0 = GLFW_KEY_KP_0;
static const int KEY_NUMPAD1 = GLFW_KEY_KP_1;
static const int KEY_NUMPAD2 = GLFW_KEY_KP_2;
static const int KEY_NUMPAD3 = GLFW_KEY_KP_3;
static const int KEY_NUMPAD4 = GLFW_KEY_KP_4;
static const int KEY_NUMPAD5 = GLFW_KEY_KP_5;
static const int KEY_NUMPAD6 = GLFW_KEY_KP_6;
static const int KEY_NUMPAD7 = GLFW_KEY_KP_7;
static const int KEY_NUMPAD8 = GLFW_KEY_KP_8;
static const int KEY_NUMPAD9 = GLFW_KEY_KP_9;
static const int KEY_MULTIPLY = GLFW_KEY_KP_MULTIPLY;
static const int KEY_ADD = GLFW_KEY_KP_ADD;
static const int KEY_SUBTRACT = GLFW_KEY_KP_SUBTRACT;
static const int KEY_DECIMAL = GLFW_KEY_KP_DECIMAL;
static const int KEY_DIVIDE = GLFW_KEY_KP_DIVIDE;
static const int KEY_F1 = GLFW_KEY_F1;
static const int KEY_F2 = GLFW_KEY_F2;
static const int KEY_F3 = GLFW_KEY_F3;
static const int KEY_F4 = GLFW_KEY_F4;
static const int KEY_F5 = GLFW_KEY_F5;
static const int KEY_F6 = GLFW_KEY_F6;
static const int KEY_F7 = GLFW_KEY_F7;
static const int KEY_F8 = GLFW_KEY_F8;
static const int KEY_F9 = GLFW_KEY_F9;
static const int KEY_F10 = GLFW_KEY_F10;
static const int KEY_F11 = GLFW_KEY_F11;
static const int KEY_F12 = GLFW_KEY_F12;
static const int KEY_F13 = GLFW_KEY_F13;
static const int KEY_F14 = GLFW_KEY_F14;
static const int KEY_F15 = GLFW_KEY_F15;
static const int KEY_F16 = GLFW_KEY_F16;
static const int KEY_F17 = GLFW_KEY_F17;
static const int KEY_F18 = GLFW_KEY_F18;
static const int KEY_F19 = GLFW_KEY_F19;
static const int KEY_F20 = GLFW_KEY_F20;
static const int KEY_F21 = GLFW_KEY_F21;
static const int KEY_F22 = GLFW_KEY_F22;
static const int KEY_F23 = GLFW_KEY_F23;
static const int KEY_F24 = GLFW_KEY_F24;
static const int KEY_NUMLOCK = GLFW_KEY_KP_NUM_LOCK;
static const int KEY_SCROLLLOCK = GLFW_KEY_SCROLL_LOCK;
static const int KEY_LSHIFT = GLFW_KEY_LSHIFT;
static const int KEY_RSHIFT = GLFW_KEY_RSHIFT;
static const int KEY_LCTRL = GLFW_KEY_LCTRL;
static const int KEY_RCTRL = GLFW_KEY_RCTRL;
static const int KEY_LALT = GLFW_KEY_LALT;
static const int KEY_RALT = GLFW_KEY_RALT;
#endif
