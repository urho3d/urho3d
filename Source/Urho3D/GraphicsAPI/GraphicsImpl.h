// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

// Note: GraphicsImpl class is purposefully API-specific. It should not be used by Urho3D client applications,
// unless required for e.g. integration of 3rd party libraries that interface directly with the graphics device.

#ifdef URHO3D_OPENGL
#include "OpenGL/OGLGraphicsImpl.h"
#endif

#ifdef URHO3D_D3D9
#include "Direct3D9/D3D9GraphicsImpl.h"
#endif

#ifdef URHO3D_D3D11
#include "Direct3D11/D3D11GraphicsImpl.h"
#endif
