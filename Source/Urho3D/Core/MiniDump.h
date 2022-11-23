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

#if defined(_MSC_VER) && defined(URHO3D_MINIDUMPS)
/// Write a minidump. Needs to be called from within a structured exception handler.
URHO3D_API int WriteMiniDump(const char* applicationName, void* exceptionPointers);
#endif

}

