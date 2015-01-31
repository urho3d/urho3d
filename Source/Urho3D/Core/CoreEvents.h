//
// Copyright (c) 2008-2015 the Urho3D project.
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

namespace Urho3D
{

/// Frame begin event.
EVENT(E_BEGINFRAME, BeginFrame)
{
    PARAM(P_FRAMENUMBER, FrameNumber);      // unsigned
    PARAM(P_TIMESTEP, TimeStep);            // float
}

/// Application-wide logic update event.
EVENT(E_UPDATE, Update)
{
    PARAM(P_TIMESTEP, TimeStep);            // float
}

/// Application-wide logic post-update event.
EVENT(E_POSTUPDATE, PostUpdate)
{
    PARAM(P_TIMESTEP, TimeStep);            // float
}

/// Render update event.
EVENT(E_RENDERUPDATE, RenderUpdate)
{
    PARAM(P_TIMESTEP, TimeStep);            // float
}

/// Post-render update event.
EVENT(E_POSTRENDERUPDATE, PostRenderUpdate)
{
    PARAM(P_TIMESTEP, TimeStep);            // float
}

/// Frame end event.
EVENT(E_ENDFRAME, EndFrame)
{
}

}
