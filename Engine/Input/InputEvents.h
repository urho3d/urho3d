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

#ifndef INPUT_INPUTEVENTS_H
#define INPUT_INPUTEVENTS_H

#include "Event.h"

//! Mouse button pressed
DEFINE_EVENT(EVENT_MOUSEBUTTONDOWN, MouseButtonDown)
{
    EVENT_PARAM(P_BUTTON, Button);              // int
    EVENT_PARAM(P_BUTTONS, Buttons);            // int
    EVENT_PARAM(P_QUALIFIERS, Qualifiers);      // int
}

//! Mouse button released
DEFINE_EVENT(EVENT_MOUSEBUTTONUP, MouseButtonUp)
{
    EVENT_PARAM(P_BUTTON, Button);              // int
    EVENT_PARAM(P_BUTTONS, Buttons);            // int
    EVENT_PARAM(P_QUALIFIERS, Qualifiers);      // int
}

//! Mouse moved
DEFINE_EVENT(EVENT_MOUSEMOVE, MouseMove)
{
    EVENT_PARAM(P_X, X);                        // int
    EVENT_PARAM(P_Y, Y);                        // int
    EVENT_PARAM(P_BUTTONS, Buttons);            // int
    EVENT_PARAM(P_QUALIFIERS, Qualifiers);      // int
}

//! Mouse wheel moved
DEFINE_EVENT(EVENT_MOUSEWHEEL, MouseWheel)
{
    EVENT_PARAM(P_WHEEL, Wheel);                // int
    EVENT_PARAM(P_BUTTONS, Buttons);            // int
    EVENT_PARAM(P_QUALIFIERS, Qualifiers);      // int
}

//! Key pressed
DEFINE_EVENT(EVENT_KEYDOWN, KeyDown)
{
    EVENT_PARAM(P_KEY, Key);                    // int
    EVENT_PARAM(P_BUTTONS, Buttons);            // int
    EVENT_PARAM(P_QUALIFIERS, Qualifiers);      // int
}

//! Key released
DEFINE_EVENT(EVENT_KEYUP, KeyUp)
{
    EVENT_PARAM(P_KEY, Key);                    // int
    EVENT_PARAM(P_BUTTONS, Buttons);            // int
    EVENT_PARAM(P_QUALIFIERS, Qualifiers);      // int
}

//! Character typed on the keyboard
DEFINE_EVENT(EVENT_CHAR, Char)
{
    EVENT_PARAM(P_CHAR, Char);                  // int
    EVENT_PARAM(P_BUTTONS, Buttons);            // int
    EVENT_PARAM(P_QUALIFIERS, Qualifiers);      // int
}

static const int MOUSEB_LEFT = 1;
static const int MOUSEB_RIGHT = 2;
static const int MOUSEB_MIDDLE = 4;

static const int QUAL_SHIFT = 1;
static const int QUAL_CTRL = 2;

static const int KEY_BACK = 0x08;
static const int KEY_TAB = 0x09;
static const int KEY_CLEAR = 0x0c; 
static const int KEY_RETURN = 0x0d;
static const int KEY_SHIFT = 0x10;
static const int KEY_CTRL = 0x11;
static const int KEY_MENU = 0x12;
static const int KEY_PAUSE = 0x13;
static const int KEY_CAPITAL = 0x14;
static const int KEY_ESC = 0x1b;
static const int KEY_CONVERT = 0x1c;
static const int KEY_NONCONVERT = 0x1d;
static const int KEY_ACCEPT = 0x1e;
static const int KEY_MODECHANGE = 0x1f;
static const int KEY_SPACE = 0x20;
static const int KEY_PAGEUP = 0x21;
static const int KEY_PAGEDOWN = 0x22;
static const int KEY_END = 0x23;
static const int KEY_HOME = 0x24;
static const int KEY_LEFT = 0x25;
static const int KEY_UP = 0x26;
static const int KEY_RIGHT = 0x27;
static const int KEY_DOWN = 0x28;
static const int KEY_SELECT = 0x29;
static const int KEY_PRINT = 0x2a;
static const int KEY_EXECUTE = 0x2b;
static const int KEY_SNAPSHOT = 0x2c;
static const int KEY_INSERT = 0x2d;
static const int KEY_DELETE = 0x2e;
static const int KEY_HELP = 0x2f;
static const int KEY_LWIN = 0x5b;
static const int KEY_RWIN = 0x5c;
static const int KEY_APPS = 0x5d;
static const int KEY_SLEEP = 0x5f;
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
static const int KEY_SEPARATOR = 0x6c;
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
static const int KEY_SCROLL = 0x91;
static const int KEY_LSHIFT = 0xa0;
static const int KEY_RSHIFT = 0xa1;
static const int KEY_LCTRL = 0xa2;
static const int KEY_RCTRL = 0xa3;
static const int KEY_LMENU = 0xa4;
static const int KEY_RMENU = 0xa5;
static const int KEY_BROWSER_BACK = 0xa6;
static const int KEY_BROWSER_FORWARD = 0xa7;
static const int KEY_BROWSER_REFRESH = 0xa8;
static const int KEY_BROWSER_STOP = 0xa9;
static const int KEY_BROWSER_SEARCH = 0xaa;
static const int KEY_BROWSER_FAVORITES = 0xab;
static const int KEY_BROWSER_HOME = 0xac;
static const int KEY_VOLUME_MUTE = 0xad;
static const int KEY_VOLUME_DOWN = 0xae;
static const int KEY_VOLUME_UP = 0xaf;
static const int KEY_MEDIA_NEXT_TRACK = 0xb0;
static const int KEY_MEDIA_PREV_TRACK = 0xb1;
static const int KEY_MEDIA_STOP = 0xb2;
static const int KEY_MEDIA_PLAY_PAUSE = 0xb3;
static const int KEY_LAUNCH_MAIL = 0xb4;
static const int KEY_LAUNCH_MEDIA_SELECT = 0xb5;
static const int KEY_LAUNCH_APP1 = 0xb6;
static const int KEY_LAUNCH_APP2 = 0xb7;
static const int KEY_OEM_1 = 0xba;
static const int KEY_OEM_PLUS = 0xbb;
static const int KEY_OEM_COMMA = 0xbc;
static const int KEY_OEM_MINUS = 0xbd;
static const int KEY_OEM_PERIOD = 0xbe;
static const int KEY_OEM_2 = 0xbf;
static const int KEY_OEM_3 = 0xc0;
static const int KEY_OEM_4 = 0xdb;
static const int KEY_OEM_5 = 0xdc;
static const int KEY_OEM_6 = 0xdd;
static const int KEY_OEM_7 = 0xde;
static const int KEY_OEM_8 = 0xdf;

#endif // INPUT_INPUTEVENTS_H
