// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#ifdef URHO3D_IS_BUILDING
    #include "Urho3D.h"
#else
    #include <Urho3D/Urho3D.h>
#endif

// Macros with identifiers of c++ version.
#define URHO_CPP11_STANDARD (201103L)
#define URHO_CPP14_STANDARD (201402L)
#define URHO_CPP17_STANDARD (201703L)
#define URHO_CPP20_STANDARD (202000L) // speculative

// Macro that can be used to identify c++ version.
#ifndef URHO_CPLUSPLUS
    #if defined(_MSVC_LANG) && !defined(__clang__)
        // Note: VC14.0/1900 (VS2015) lacks too much from C++14
        #if (_MSC_VER == 1900)
            #define URHO_CPLUSPLUS URHO_CPP11_STANDARD
        #else
            #define URHO_CPLUSPLUS _MSVC_LANG
        #endif
    #else
        #define URHO_CPLUSPLUS __cplusplus
    #endif
#endif

// Macros with a strong guarantee of what c++ version is available.
#define URHO_CPP11_OR_LATER (URHO_CPLUSPLUS >= URHO_CPP11_STANDARD)
#define URHO_CPP14_OR_LATER (URHO_CPLUSPLUS >= URHO_CPP14_STANDARD)
#define URHO_CPP17_OR_LATER (URHO_CPLUSPLUS >= URHO_CPP17_STANDARD)

// Macros for specific c++ versions
#if URHO_CPP11_OR_LATER
    // Least match
    #define URHO_CPP11(x) x
    #define URHO_CPP14(x)
    #define URHO_CPP17(x)
    // Exact match
    #define URHO_CPP11_ONLY(x) x
    #define URHO_CPP14_ONLY(x)
    #define URHO_CPP17_ONLY(x)
#elif URHO_CPP14_OR_LATER
    // Least match
    #define URHO_CPP11(x) x
    #define URHO_CPP14(x) x
    #define URHO_CPP17(x)
    // Exact match
    #define URHO_CPP11_ONLY(x)
    #define URHO_CPP14_ONLY(x) x
    #define URHO_CPP17_ONLY(x)
#elif URHO_CPP17_OR_LATER
    // Least match
    #define URHO_CPP11(x) x
    #define URHO_CPP14(x) x
    #define URHO_CPP17(x) x
    // Exact match
    #define URHO_CPP11_ONLY(x)
    #define URHO_CPP14_ONLY(x)
    #define URHO_CPP17_ONLY(x) x
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
