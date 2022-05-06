// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#ifdef URHO3D_IS_BUILDING
#include "Urho3D.h"
#else
#include <Urho3D/Urho3D.h>
#endif

namespace Urho3D
{

/// Return git description of the HEAD when building the library.
URHO3D_API const char* GetRevision();

/// Return baked-in compiler defines used when building the library.
URHO3D_API const char* GetCompilerDefines();

}
