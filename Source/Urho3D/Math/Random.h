// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#ifdef URHO3D_IS_BUILDING
#include "Urho3D.h"
#else
#include <Urho3D/Urho3D.h>
#endif

#include "../Base/PrimitiveTypes.h"

namespace Urho3D
{

/// Set the random seed. The default seed is 1.
URHO3D_API void SetRandomSeed(unsigned seed);
/// Return the current random seed.
URHO3D_API unsigned GetRandomSeed();
/// Return a random number between 0-32767. Should operate similarly to MSVC rand().
/// @alias{RandomInt}
URHO3D_API int Rand();
/// Return a standard normal distributed number.
URHO3D_API float RandStandardNormal();

}
