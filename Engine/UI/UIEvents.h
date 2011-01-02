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

//! UI element has changed in some way
DEFINE_EVENT(EVENT_CHANGED, Changed)
{
    EVENT_PARAM(P_ELEMENT, Element);            // UIElement pointer
}

#endif // UI_UIEVENTS_H
