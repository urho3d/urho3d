/*
  Simple DirectMedia Layer
  Copyright (C) 1997-2016 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

// Modified by Lasse Oorni for Urho3D

#if defined(__clang_analyzer__) && !defined(SDL_DISABLE_ANALYZE_MACROS)
#define SDL_DISABLE_ANALYZE_MACROS 1
#endif

#include "../SDL_internal.h"

/* This file contains portable stdlib functions for SDL */

#include "SDL_stdinc.h"
#include "../libm/math_libm.h"


double
SDL_atan(double x)
{
#ifdef HAVE_ATAN
    return atan(x);
#else
    return SDL_uclibc_atan(x);
#endif /* HAVE_ATAN */
}

double
SDL_atan2(double x, double y)
{
#if defined(HAVE_ATAN2)
    return atan2(x, y);
#else
    return SDL_uclibc_atan2(x, y);
#endif /* HAVE_ATAN2 */
}

double
SDL_acos(double val)
{
#if defined(HAVE_ACOS)
    return acos(val);
#else
    double result;
    if (val == -1.0) {
        result = M_PI;
    } else {
        result = SDL_atan(SDL_sqrt(1.0 - val * val) / val);
        if (result < 0.0)
        {
            result += M_PI;
        }
    }
    return result;
#endif
}

double
SDL_asin(double val)
{
#if defined(HAVE_ASIN)
    return asin(val);
#else
    double result;
    if (val == -1.0) {
        result = -(M_PI / 2.0);
    } else {
        result = (M_PI / 2.0) - SDL_acos(val);
    }
    return result;
#endif
}

double
SDL_ceil(double x)
{
#ifdef HAVE_CEIL
    return ceil(x);
#else
    double integer = SDL_floor(x);
    double fraction = x - integer;
    if (fraction > 0.0) {
        integer += 1.0;
    }
    return integer;
#endif /* HAVE_CEIL */
}

double
SDL_copysign(double x, double y)
{
#if defined(HAVE_COPYSIGN)
    return copysign(x, y);
#elif defined(HAVE__COPYSIGN)
    return _copysign(x, y);
#else
    return SDL_uclibc_copysign(x, y);
#endif /* HAVE_COPYSIGN */
}

double
SDL_cos(double x)
{
#if defined(HAVE_COS)
    return cos(x);
#else
    return SDL_uclibc_cos(x);
#endif /* HAVE_COS */
}

float
SDL_cosf(float x)
{
#ifdef HAVE_COSF
    return cosf(x);
#else
    return (float)SDL_cos((double)x);
#endif
}

double
SDL_fabs(double x)
{
#if defined(HAVE_FABS)
    return fabs(x); 
#else
    return SDL_uclibc_fabs(x);
#endif /* HAVE_FABS */
}

double
SDL_floor(double x)
{
#if defined(HAVE_FLOOR)
    return floor(x);
#else
    return SDL_uclibc_floor(x);
#endif /* HAVE_FLOOR */
}

double
SDL_log(double x)
{
#if defined(HAVE_LOG)
    return log(x);
#else
    return SDL_uclibc_log(x);
#endif /* HAVE_LOG */
}

double
SDL_pow(double x, double y)
{
#if defined(HAVE_POW)
    return pow(x, y);
#else
    return SDL_uclibc_pow(x, y);
#endif /* HAVE_POW */
}

double
SDL_scalbn(double x, int n)
{
#if defined(HAVE_SCALBN)
    return scalbn(x, n);
#elif defined(HAVE__SCALB)
    return _scalb(x, n);
#else
    return SDL_uclibc_scalbn(x, n);
#endif /* HAVE_SCALBN */
}

double
SDL_sin(double x)
{
#if defined(HAVE_SIN)
    return sin(x);
#else
    return SDL_uclibc_sin(x);
#endif /* HAVE_SIN */
}

float 
SDL_sinf(float x)
{
#ifdef HAVE_SINF
    return sinf(x);
#else
    return (float)SDL_sin((double)x);
#endif /* HAVE_SINF */
}

double
SDL_sqrt(double x)
{
#if defined(HAVE_SQRT)
    return sqrt(x);
#else
    return SDL_uclibc_sqrt(x);
#endif
}

float
SDL_sqrtf(float x)
{
#if defined(HAVE_SQRTF)
    return sqrtf(x);
#else
    return (float)SDL_sqrt((double)x);
#endif
}

double
SDL_tan(double x)
{
#if defined(HAVE_TAN)
    return tan(x);
#else
    return SDL_uclibc_tan(x);
#endif
}

float
SDL_tanf(float x)
{
#if defined(HAVE_TANF)
    return tanf(x);
#else
    return (float)SDL_tan((double)x);
#endif
}

int SDL_abs(int x)
{
#ifdef HAVE_ABS
    return abs(x);
#else
    return ((x) < 0 ? -(x) : (x));
#endif
}

#ifdef HAVE_CTYPE_H
int SDL_isdigit(int x) { return isdigit(x); }
int SDL_isspace(int x) { return isspace(x); }
int SDL_toupper(int x) { return toupper(x); }
int SDL_tolower(int x) { return tolower(x); }
#else
int SDL_isdigit(int x) { return ((x) >= '0') && ((x) <= '9'); }
int SDL_isspace(int x) { return ((x) == ' ') || ((x) == '\t') || ((x) == '\r') || ((x) == '\n') || ((x) == '\f') || ((x) == '\v'); }
int SDL_toupper(int x) { return ((x) >= 'a') && ((x) <= 'z') ? ('A'+((x)-'a')) : (x); }
int SDL_tolower(int x) { return ((x) >= 'A') && ((x) <= 'Z') ? ('a'+((x)-'A')) : (x); }
#endif


#ifndef HAVE_LIBC
// Urho3D: disable MSVC runtime intrinsic replacements
#endif /* !HAVE_LIBC */

/* vi: set ts=4 sw=4 expandtab: */
