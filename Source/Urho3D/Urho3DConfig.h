// Copyright (c) 2008-2023 the Urho3D project
// License: MIT

#pragma once

#ifdef URHO3D_IS_BUILDING
    #include "Urho3D.h"
#else
    #include <Urho3D/Urho3D.h>
#endif

// Macros with identifiers of c++ version.
#define URHO_CPP17_STANDARD (201703L)
#define URHO_CPP20_STANDARD (202002L)

// Macro that can be used to identify c++ version.
#ifndef URHO_CPLUSPLUS
    #if defined(_MSVC_LANG) && !defined(__clang__)
        #define URHO_CPLUSPLUS _MSVC_LANG
    #else
        #define URHO_CPLUSPLUS __cplusplus
    #endif
#endif

// Macros with a strong guarantee of what c++ version is available.
#define URHO_CPP17_OR_LATER (URHO_CPLUSPLUS >= URHO_CPP17_STANDARD)
#define URHO_CPP20_OR_LATER (URHO_CPLUSPLUS >= URHO_CPP20_STANDARD)

// Macros for specific c++ versions
#if URHO_CPP20_OR_LATER
    // Least match
    #define URHO_CPP17(x) x
    #define URHO_CPP20(x) x

    // Exact match
    #define URHO_CPP17_ONLY(x)
    #define URHO_CPP20_ONLY(x) x
#elif URHO_CPP17_OR_LATER
    // Least match
    #define URHO_CPP17(x) x
    #define URHO_CPP20(x)

    // Exact match
    #define URHO_CPP17_ONLY(x) x
    #define URHO_CPP20_ONLY(x)
#else
    #error Compiler does not support required c++ standard. How did you get here?
#endif

// Case insensitive string comparison.
#ifdef _WIN32
    #define URHO_STRICMP(a,b) stricmp(a,b)
    #define URHO_STRNICMP(a,b,n) strnicmp(a,b,n)
#else
    #define URHO_STRICMP(a,b) strcasecmp(a,b)
    #define URHO_STRNICMP(a,b,n) strncasecmp(a,b,n)
#endif
