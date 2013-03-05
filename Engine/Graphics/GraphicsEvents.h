//
// Copyright (c) 2008-2013 the Urho3D project.
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

namespace Urho3D
{

/// Operating system window message.
EVENT(E_WINDOWMESSAGE, WindowMessage)
{
    PARAM(P_WINDOW, Window);                // int
    PARAM(P_MSG, Msg);                      // int
    PARAM(P_WPARAM, WParam);                // int
    PARAM(P_LPARAM, LParam);                // int
    PARAM(P_HANDLED, Handled);              // bool
}

/// New screen mode set.
EVENT(E_SCREENMODE, ScreenMode)
{
    PARAM(P_WIDTH, Width);                  // int
    PARAM(P_HEIGHT, Height);                // int
    PARAM(P_FULLSCREEN, Fullscreen);        // bool
    PARAM(P_RESIZABLE, Resizable);          // bool
}

/// Graphics features checked.
EVENT(E_GRAPHICSFEATURES, GraphicsFeatures)
{
}

/// Request for queuing autoupdated rendersurfaces
EVENT(E_RENDERSURFACEUPDATE, RenderSurfaceUpdate)
{
}

/// Frame rendering started.
EVENT(E_BEGINRENDERING, BeginRendering)
{
}

/// Frame rendering ended.
EVENT(E_ENDRENDERING, EndRendering)
{
}

}
