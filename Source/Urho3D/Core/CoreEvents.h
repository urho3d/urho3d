// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include "../Core/Object.h"

namespace Urho3D
{

/// Frame begin event.
URHO3D_EVENT(E_BEGINFRAME, BeginFrame)
{
    URHO3D_PARAM(P_FRAMENUMBER, FrameNumber);      // unsigned
    URHO3D_PARAM(P_TIMESTEP, TimeStep);            // float
}

/// Application-wide logic update event.
URHO3D_EVENT(E_UPDATE, Update)
{
    URHO3D_PARAM(P_TIMESTEP, TimeStep);            // float
}

/// Application-wide logic post-update event.
URHO3D_EVENT(E_POSTUPDATE, PostUpdate)
{
    URHO3D_PARAM(P_TIMESTEP, TimeStep);            // float
}

/// Render update event.
URHO3D_EVENT(E_RENDERUPDATE, RenderUpdate)
{
    URHO3D_PARAM(P_TIMESTEP, TimeStep);            // float
}

/// Post-render update event.
URHO3D_EVENT(E_POSTRENDERUPDATE, PostRenderUpdate)
{
    URHO3D_PARAM(P_TIMESTEP, TimeStep);            // float
}

/// Frame end event.
URHO3D_EVENT(E_ENDFRAME, EndFrame)
{
}

}
