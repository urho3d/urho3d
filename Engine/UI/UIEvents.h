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

#ifndef UI_UIEVENTS_H
#define UI_UIEVENTS_H

#include "Event.h"

//! UI element resized
DEFINE_EVENT(EVENT_RESIZED, Resized)
{
    EVENT_PARAM(P_ELEMENT, Element);            // UIElement pointer
    EVENT_PARAM(P_WIDTH, Width);                // int
    EVENT_PARAM(P_Height, Height);              // int
}

//! UI element visibility changed
DEFINE_EVENT(EVENT_VISIBLECHANGED, VisibleChanged)
{
    EVENT_PARAM(P_ELEMENT, Element);            // UIElement pointer
    EVENT_PARAM(P_VISIBLE, Visible);            // bool
}

//! Trying to focus an UI element. Sent before checking for success. Also sent with 0 pointer for global defocus
DEFINE_EVENT(EVENT_TRYFOCUS, TryFocus)
{
    EVENT_PARAM(P_ELEMENT, Element);            // UIElement pointer
}

//! UI element focused
DEFINE_EVENT(EVENT_FOCUSED, Focused)
{
    EVENT_PARAM(P_ELEMENT, Element);            // UIElement pointer
}

//! UI element defocused
DEFINE_EVENT(EVENT_DEFOCUSED, Defocused)
{
    EVENT_PARAM(P_ELEMENT, Element);            // UIElement pointer
}

//! UI button pressed
DEFINE_EVENT(EVENT_PRESSED, Pressed)
{
    EVENT_PARAM(P_ELEMENT, Element);            // UIElement pointer
}

//! UI checkbox toggled
DEFINE_EVENT(EVENT_TOGGLED, Toggled)
{
    EVENT_PARAM(P_ELEMENT, Element);            // UIElement pointer
    EVENT_PARAM(P_STATE, State);                // bool
}

//! UI slider value changed
DEFINE_EVENT(EVENT_SLIDERCHANGED, SliderChanged)
{
    EVENT_PARAM(P_ELEMENT, Element);            // UIElement pointer
    EVENT_PARAM(P_VALUE, Value);                // float
}

//! UI scrollbar value changed
DEFINE_EVENT(EVENT_SCROLLBARCHANGED, ScrollBarChanged)
{
    EVENT_PARAM(P_ELEMENT, Element);            // UIElement pointer
    EVENT_PARAM(P_VALUE, Value);                // float
}

//! UI scrollview position changed
DEFINE_EVENT(EVENT_VIEWCHANGED, ViewChanged)
{
    EVENT_PARAM(P_ELEMENT, Element);            // UIElement pointer
    EVENT_PARAM(P_X, X);                        // int
    EVENT_PARAM(P_Y, Y);                        // int
}

//! Editable text changed
DEFINE_EVENT(EVENT_TEXTCHANGED, TextChanged)
{
    EVENT_PARAM(P_ELEMENT, Element);            // UIElement pointer
    EVENT_PARAM(P_TEXT, Text);                  // string
}

//! Text editing finished (enter pressed on a LineEdit)
DEFINE_EVENT(EVENT_TEXTFINISHED, TextFinished)
{
    EVENT_PARAM(P_ELEMENT, Element);            // UIElement pointer
    EVENT_PARAM(P_TEXT, Text);                  // string
}

//! Menu item selected
DEFINE_EVENT(EVENT_ITEMSELECTED, ItemSelected)
{
    EVENT_PARAM(P_ELEMENT, Element);            // UIElement pointer
}

#endif // UI_UIEVENTS_H
