// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

// This is defined in the release version and disables assert().
// We need assert() to work even in the release version
#ifdef NDEBUG
    #undef NDEBUG
#endif

#include <cassert>
