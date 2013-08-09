/*
  Simple DirectMedia Layer
  Copyright (C) 1997-2013 Sam Lantinga <slouken@libsdl.org>

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
#include "SDL_config.h"
#include "SDL_stdinc.h"

/* Math routines from uClibc: http://www.uclibc.org */

#ifdef HAVE_ATAN
#define atan            SDL_uclibc_atan
#else
#define atan            SDL_atan
#endif
double atan(double x);

#ifndef HAVE_ATAN2
#define __ieee754_atan2 SDL_atan2
#endif

#ifdef HAVE_COPYSIGN
#define copysign        SDL_uclibc_copysign
#else
#define copysign        SDL_copysign
#endif
double copysign(double x, double y);

#ifdef HAVE_COS
#define cos             SDL_uclibc_cos
#else
#define cos             SDL_cos
#endif
double cos(double x);

#ifdef HAVE_FABS
#define fabs            SDL_uclibc_fabs
#else
#define fabs            SDL_fabs
#endif
double fabs(double x);

#ifdef HAVE_FLOOR
#define floor           SDL_uclibc_floor
#else
#define floor           SDL_floor
#endif
double floor(double x);

#ifndef HAVE_LOG
#define __ieee754_log   SDL_log
#endif

#ifndef HAVE_POW
#define __ieee754_pow   SDL_pow
#endif

#ifdef HAVE_SCALBN
#define scalbn          SDL_uclibc_scalbn
#else
#define scalbn          SDL_scalbn
#endif
double scalbn(double x, int n);

#ifdef HAVE_SIN
#define sin             SDL_uclibc_sin
#else
#define sin             SDL_sin
#endif
double sin(double x);

#ifndef HAVE_SQRT
#define __ieee754_sqrt  SDL_sqrt
#endif

/* vi: set ts=4 sw=4 expandtab: */
