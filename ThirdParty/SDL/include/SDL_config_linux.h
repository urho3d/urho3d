/* include/SDL_config.h.  Generated from SDL_config.h.in by configure.  */
/*
  Simple DirectMedia Layer
  Copyright (C) 1997-2011 Sam Lantinga <slouken@libsdl.org>

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

// Modified by Lasse Öörni for Urho3D

#ifndef _SDL_config_linux_h
#define _SDL_config_linux_h

/**
 *  \file SDL_config.h.in
 *
 *  This is a set of defines to configure the SDL features
 */

/* General platform specific identifiers */
#include "SDL_platform.h"


/* Make sure that this isn't included by Visual C++ */
#ifdef _MSC_VER
#error You should run hg revert SDL_config.h 
#endif

/* C language features */
/* #undef const */
/* #undef inline */
/* #undef volatile */

/* C datatypes */
#define SIZEOF_VOIDP 4
#define HAVE_GCC_ATOMICS 1
/* #undef HAVE_GCC_SYNC_LOCK_TEST_AND_SET */

/* Comment this if you want to build without any C library requirements */
#define HAVE_LIBC 1
#if HAVE_LIBC

/* Useful headers */
#define HAVE_ALLOCA_H 1
#define HAVE_SYS_TYPES_H 1
#define HAVE_STDIO_H 1
#define STDC_HEADERS 1
#define HAVE_STDLIB_H 1
#define HAVE_STDARG_H 1
#define HAVE_MALLOC_H 1
#define HAVE_MEMORY_H 1
#define HAVE_STRING_H 1
#define HAVE_STRINGS_H 1
#define HAVE_INTTYPES_H 1
#define HAVE_STDINT_H 1
#define HAVE_CTYPE_H 1
#define HAVE_MATH_H 1
#define HAVE_ICONV_H 1
#define HAVE_SIGNAL_H 1
/* #undef HAVE_ALTIVEC_H */

/* C library functions */
#define HAVE_MALLOC 1
#define HAVE_CALLOC 1
#define HAVE_REALLOC 1
#define HAVE_FREE 1
#define HAVE_ALLOCA 1
#ifndef __WIN32__ /* Don't use C runtime versions of these on Windows */
#define HAVE_GETENV 1
#define HAVE_SETENV 1
#define HAVE_PUTENV 1
#define HAVE_UNSETENV 1
#endif
#define HAVE_QSORT 1
#define HAVE_ABS 1
#define HAVE_BCOPY 1
#define HAVE_MEMSET 1
#define HAVE_MEMCPY 1
#define HAVE_MEMMOVE 1
#define HAVE_MEMCMP 1
#define HAVE_STRLEN 1
/* #undef HAVE_STRLCPY */
/* #undef HAVE_STRLCAT */
#define HAVE_STRDUP 1
/* #undef HAVE__STRREV */
/* #undef HAVE__STRUPR */
/* #undef HAVE__STRLWR */
/* #undef HAVE_INDEX */
/* #undef HAVE_RINDEX */
#define HAVE_STRCHR 1
#define HAVE_STRRCHR 1
#define HAVE_STRSTR 1
/* #undef HAVE_ITOA */
/* #undef HAVE__LTOA */
/* #undef HAVE__UITOA */
/* #undef HAVE__ULTOA */
#define HAVE_STRTOL 1
#define HAVE_STRTOUL 1
/* #undef HAVE__I64TOA */
/* #undef HAVE__UI64TOA */
#define HAVE_STRTOLL 1
#define HAVE_STRTOULL 1
#define HAVE_STRTOD 1
#define HAVE_ATOI 1
#define HAVE_ATOF 1
#define HAVE_STRCMP 1
#define HAVE_STRNCMP 1
/* #undef HAVE__STRICMP */
#define HAVE_STRCASECMP 1
/* #undef HAVE__STRNICMP */
#define HAVE_STRNCASECMP 1
#define HAVE_SSCANF 1
#define HAVE_SNPRINTF 1
#define HAVE_VSNPRINTF 1
#define HAVE_M_PI /**/
#define HAVE_ATAN 1
#define HAVE_ATAN2 1
#define HAVE_CEIL 1
#define HAVE_COPYSIGN 1
#define HAVE_COS 1
#define HAVE_COSF 1
#define HAVE_FABS 1
#define HAVE_FLOOR 1
#define HAVE_LOG 1
#define HAVE_POW 1
#define HAVE_SCALBN 1
#define HAVE_SIN 1
#define HAVE_SINF 1
#define HAVE_SQRT 1
#define HAVE_SIGACTION 1
#define HAVE_SETJMP 1
#define HAVE_NANOSLEEP 1
#define HAVE_SYSCONF 1
/* #undef HAVE_SYSCTLBYNAME */
/* #undef HAVE_CLOCK_GETTIME */
/* #undef HAVE_GETPAGESIZE */
#define HAVE_MPROTECT 1
#define HAVE_ICONV 1

#else
/* We may need some replacement for stdarg.h here */
#include <stdarg.h>
#endif /* HAVE_LIBC */

/* SDL internal assertion support */
/* #undef SDL_DEFAULT_ASSERT_LEVEL */

/* Allow disabling of core subsystems */
#define SDL_JOYSTICK_DISABLED 1
#define SDL_HAPTIC_DISABLED 1
#define SDL_POWER_DISABLED 1

/* Enable various audio drivers */
#define SDL_AUDIO_DRIVER_ALSA 1
#define SDL_AUDIO_DRIVER_ALSA_DYNAMIC "libasound.so.2"
#define SDL_AUDIO_DRIVER_DUMMY 1
#define SDL_AUDIO_DRIVER_OSS 1

/* Enable various input drivers */
#define SDL_INPUT_LINUXEV 1

/* Enable various shared object loading systems */
#define SDL_LOADSO_DLOPEN 1

/* Enable various threading systems */
#define SDL_THREAD_PTHREAD 1
#define SDL_THREAD_PTHREAD_RECURSIVE_MUTEX 1

/* Enable various timer systems */
#define SDL_TIMER_UNIX 1

/* Enable various video drivers */
#define SDL_VIDEO_DRIVER_X11 1
#define SDL_VIDEO_DRIVER_X11_DYNAMIC "libX11.so.6"
#define SDL_VIDEO_DRIVER_X11_DYNAMIC_XEXT "libXext.so.6"
#define SDL_VIDEO_DRIVER_X11_DYNAMIC_XVIDMODE "libXxf86vm.so.1"
#define SDL_VIDEO_DRIVER_X11_XSHAPE 1
#define SDL_VIDEO_DRIVER_X11_XVIDMODE 1
#define SDL_VIDEO_RENDER_OGL 1

/* Enable OpenGL support */
#define SDL_VIDEO_OPENGL 1
#define SDL_VIDEO_OPENGL_GLX 1

/* Enable assembly routines */
#define SDL_ASSEMBLY_ROUTINES 1

#endif /* _SDL_config_linux_h */
