// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include "../Core/Object.h"

namespace Urho3D
{

/// New screen mode set.
URHO3D_EVENT(E_SCREENMODE, ScreenMode)
{
    URHO3D_PARAM(P_WIDTH, Width);                  // int
    URHO3D_PARAM(P_HEIGHT, Height);                // int
    URHO3D_PARAM(P_FULLSCREEN, Fullscreen);        // bool
    URHO3D_PARAM(P_BORDERLESS, Borderless);        // bool
    URHO3D_PARAM(P_RESIZABLE, Resizable);          // bool
    URHO3D_PARAM(P_HIGHDPI, HighDPI);              // bool
    URHO3D_PARAM(P_MONITOR, Monitor);              // int
    URHO3D_PARAM(P_REFRESHRATE, RefreshRate);      // int
}

/// Window position changed.
URHO3D_EVENT(E_WINDOWPOS, WindowPos)
{
    URHO3D_PARAM(P_X, X);                          // int
    URHO3D_PARAM(P_Y, Y);                          // int
}

/// Request for queuing rendersurfaces either in manual or always-update mode.
URHO3D_EVENT(E_RENDERSURFACEUPDATE, RenderSurfaceUpdate)
{
}

/// Frame rendering started.
URHO3D_EVENT(E_BEGINRENDERING, BeginRendering)
{
}

/// Frame rendering ended.
URHO3D_EVENT(E_ENDRENDERING, EndRendering)
{
}

/// Update of a view started.
URHO3D_EVENT(E_BEGINVIEWUPDATE, BeginViewUpdate)
{
    URHO3D_PARAM(P_VIEW, View);                    // View pointer
    URHO3D_PARAM(P_TEXTURE, Texture);              // Texture pointer
    URHO3D_PARAM(P_SURFACE, Surface);              // RenderSurface pointer
    URHO3D_PARAM(P_SCENE, Scene);                  // Scene pointer
    URHO3D_PARAM(P_CAMERA, Camera);                // Camera pointer
}

/// Update of a view ended.
URHO3D_EVENT(E_ENDVIEWUPDATE, EndViewUpdate)
{
    URHO3D_PARAM(P_VIEW, View);                    // View pointer
    URHO3D_PARAM(P_TEXTURE, Texture);              // Texture pointer
    URHO3D_PARAM(P_SURFACE, Surface);              // RenderSurface pointer
    URHO3D_PARAM(P_SCENE, Scene);                  // Scene pointer
    URHO3D_PARAM(P_CAMERA, Camera);                // Camera pointer
}

/// Render of a view started.
URHO3D_EVENT(E_BEGINVIEWRENDER, BeginViewRender)
{
    URHO3D_PARAM(P_VIEW, View);                    // View pointer
    URHO3D_PARAM(P_TEXTURE, Texture);              // Texture pointer
    URHO3D_PARAM(P_SURFACE, Surface);              // RenderSurface pointer
    URHO3D_PARAM(P_SCENE, Scene);                  // Scene pointer
    URHO3D_PARAM(P_CAMERA, Camera);                // Camera pointer
}

/// A view has allocated its screen buffers for rendering. They can be accessed now with View::FindNamedTexture().
URHO3D_EVENT(E_VIEWBUFFERSREADY, ViewBuffersReady)
{
    URHO3D_PARAM(P_VIEW, View);                    // View pointer
    URHO3D_PARAM(P_TEXTURE, Texture);              // Texture pointer
    URHO3D_PARAM(P_SURFACE, Surface);              // RenderSurface pointer
    URHO3D_PARAM(P_SCENE, Scene);                  // Scene pointer
    URHO3D_PARAM(P_CAMERA, Camera);                // Camera pointer
}

/// A view has set global shader parameters for a new combination of vertex/pixel shaders. Custom global parameters can now be set.
URHO3D_EVENT(E_VIEWGLOBALSHADERPARAMETERS, ViewGlobalShaderParameters)
{
    URHO3D_PARAM(P_VIEW, View);                    // View pointer
    URHO3D_PARAM(P_TEXTURE, Texture);              // Texture pointer
    URHO3D_PARAM(P_SURFACE, Surface);              // RenderSurface pointer
    URHO3D_PARAM(P_SCENE, Scene);                  // Scene pointer
    URHO3D_PARAM(P_CAMERA, Camera);                // Camera pointer
}

/// Render of a view ended. Its screen buffers are still accessible if needed.
URHO3D_EVENT(E_ENDVIEWRENDER, EndViewRender)
{
    URHO3D_PARAM(P_VIEW, View);                    // View pointer
    URHO3D_PARAM(P_TEXTURE, Texture);              // Texture pointer
    URHO3D_PARAM(P_SURFACE, Surface);              // RenderSurface pointer
    URHO3D_PARAM(P_SCENE, Scene);                  // Scene pointer
    URHO3D_PARAM(P_CAMERA, Camera);                // Camera pointer
}

/// Render of all views is finished for the frame.
URHO3D_EVENT(E_ENDALLVIEWSRENDER, EndAllViewsRender)
{
}

/// A render path event has occurred.
URHO3D_EVENT(E_RENDERPATHEVENT, RenderPathEvent)
{
    URHO3D_PARAM(P_NAME, Name);                    // String
}

/// Graphics context has been lost. Some or all (depending on the API) GPU objects have lost their contents.
URHO3D_EVENT(E_DEVICELOST, DeviceLost)
{
}

/// Graphics context has been recreated after being lost. GPU objects in the "data lost" state can be restored now.
URHO3D_EVENT(E_DEVICERESET, DeviceReset)
{
}

}
