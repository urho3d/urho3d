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

#ifndef RENDERER_RENDEREREVENTS_H
#define RENDERER_RENDEREREVENTS_H

#include "Event.h"

//! Operating system window message
DEFINE_EVENT(EVENT_WINDOWMESSAGE, WindowMessage)
{
    EVENT_PARAM(P_MSG, Msg);                    // int
    EVENT_PARAM(P_WPARAM, WParam);              // int
    EVENT_PARAM(P_LPARAM, LParam);              // int
    EVENT_PARAM(P_HANDLED, Handled);            // bool
}

//! Window resized
DEFINE_EVENT(EVENT_WINDOWRESIZED, WindowResized)
{
    EVENT_PARAM(P_WIDTH, Width);                // int
    EVENT_PARAM(P_HEIGHT, Height);              // int
}

//! Frame rendering started
DEFINE_EVENT(EVENT_BEGINFRAME, BeginFrame)
{
}

//! Frame rendering ended
DEFINE_EVENT(EVENT_ENDFRAME, EndFrame)
{
}

#endif // RENDERER_RENDEREREVENTS_H
