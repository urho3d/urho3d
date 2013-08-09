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

// Modified by Lasse Oorni for Urho3D

/**
 *  \file SDL_stdinc.h
 *
 *  This is a general header that includes C language support.
 */

#ifndef _SDL_stdinc_h
#define _SDL_stdinc_h

#include "SDL_config.h"

#ifdef HAVE_SYS_TYPES_H
#include <sys/types.h>
#endif
#ifdef HAVE_STDIO_H
#include <stdio.h>
#endif
#if defined(STDC_HEADERS)
# include <stdlib.h>
# include <stddef.h>
# include <stdarg.h>
#else
# if defined(HAVE_STDLIB_H)
#  include <stdlib.h>
# elif defined(HAVE_MALLOC_H)
#  include <malloc.h>
# endif
# if defined(HAVE_STDDEF_H)
#  include <stddef.h>
# endif
# if defined(HAVE_STDARG_H)
#  include <stdarg.h>
# endif
#endif
#ifdef HAVE_STRING_H
# if !defined(STDC_HEADERS) && defined(HAVE_MEMORY_H)
#  include <memory.h>
# endif
# include <string.h>
#endif
#ifdef HAVE_STRINGS_H
# include <strings.h>
#endif
#if defined(HAVE_INTTYPES_H)
# include <inttypes.h>
#elif defined(HAVE_STDINT_H)
# include <stdint.h>
#endif
#ifdef HAVE_CTYPE_H
# include <ctype.h>
#endif
#ifdef HAVE_MATH_H
# include <math.h>
#endif
#if defined(HAVE_ICONV) && defined(HAVE_ICONV_H)
# include <iconv.h>
#endif

/**
 *  The number of elements in an array.
 */
#define SDL_arraysize(array)    (sizeof(array)/sizeof(array[0]))
#define SDL_TABLESIZE(table)    SDL_arraysize(table)

/**
 *  \name Cast operators
 *
 *  Use proper C++ casts when compiled as C++ to be compatible with the option
 *  -Wold-style-cast of GCC (and -Werror=old-style-cast in GCC 4.2 and above).
 */
/*@{*/
#ifdef __cplusplus
#define SDL_reinterpret_cast(type, expression) reinterpret_cast<type>(expression)
#define SDL_static_cast(type, expression) static_cast<type>(expression)
#define SDL_const_cast(type, expression) const_cast<type>(expression)
#else
#define SDL_reinterpret_cast(type, expression) ((type)(expression))
#define SDL_static_cast(type, expression) ((type)(expression))
#define SDL_const_cast(type, expression) ((type)(expression))
#endif
/*@}*//*Cast operators*/

/* Define a four character code as a Uint32 */
#define SDL_FOURCC(A, B, C, D) \
    ((SDL_static_cast(Uint32, SDL_static_cast(Uint8, (A))) << 0) | \
     (SDL_static_cast(Uint32, SDL_static_cast(Uint8, (B))) << 8) | \
     (SDL_static_cast(Uint32, SDL_static_cast(Uint8, (C))) << 16) | \
     (SDL_static_cast(Uint32, SDL_static_cast(Uint8, (D))) << 24))

/**
 *  \name Basic data types
 */
/*@{*/

typedef enum
{
    SDL_FALSE = 0,
    SDL_TRUE = 1
} SDL_bool;

/**
 * \brief A signed 8-bit integer type.
 */
typedef int8_t Sint8;
/**
 * \brief An unsigned 8-bit integer type.
 */
typedef uint8_t Uint8;
/**
 * \brief A signed 16-bit integer type.
 */
typedef int16_t Sint16;
/**
 * \brief An unsigned 16-bit integer type.
 */
typedef uint16_t Uint16;
/**
 * \brief A signed 32-bit integer type.
 */
typedef int32_t Sint32;
/**
 * \brief An unsigned 32-bit integer type.
 */
typedef uint32_t Uint32;

/**
 * \brief A signed 64-bit integer type.
 */
typedef int64_t Sint64;
/**
 * \brief An unsigned 64-bit integer type.
 */
typedef uint64_t Uint64;

/*@}*//*Basic data types*/


#define SDL_COMPILE_TIME_ASSERT(name, x)               \
       typedef int SDL_dummy_ ## name[(x) * 2 - 1]
/** \cond */
#ifndef DOXYGEN_SHOULD_IGNORE_THIS
SDL_COMPILE_TIME_ASSERT(uint8, sizeof(Uint8) == 1);
SDL_COMPILE_TIME_ASSERT(sint8, sizeof(Sint8) == 1);
SDL_COMPILE_TIME_ASSERT(uint16, sizeof(Uint16) == 2);
SDL_COMPILE_TIME_ASSERT(sint16, sizeof(Sint16) == 2);
SDL_COMPILE_TIME_ASSERT(uint32, sizeof(Uint32) == 4);
SDL_COMPILE_TIME_ASSERT(sint32, sizeof(Sint32) == 4);
SDL_COMPILE_TIME_ASSERT(uint64, sizeof(Uint64) == 8);
SDL_COMPILE_TIME_ASSERT(sint64, sizeof(Sint64) == 8);
#endif /* DOXYGEN_SHOULD_IGNORE_THIS */
/** \endcond */

/* Check to make sure enums are the size of ints, for structure packing.
   For both Watcom C/C++ and Borland C/C++ the compiler option that makes
   enums having the size of an int must be enabled.
   This is "-b" for Borland C/C++ and "-ei" for Watcom C/C++ (v11).
*/

/** \cond */
#ifndef DOXYGEN_SHOULD_IGNORE_THIS
#if !defined(__ANDROID__)
   /* TODO: include/SDL_stdinc.h:174: error: size of array 'SDL_dummy_enum' is negative */
typedef enum
{
    DUMMY_ENUM_VALUE
} SDL_DUMMY_ENUM;

SDL_COMPILE_TIME_ASSERT(enum, sizeof(SDL_DUMMY_ENUM) == sizeof(int));
#endif
#endif /* DOXYGEN_SHOULD_IGNORE_THIS */
/** \endcond */

#include "begin_code.h"
/* Set up for C function definitions, even when using C++ */
#ifdef __cplusplus
extern "C" {
#endif

#if defined(HAVE_ALLOCA) && !defined(alloca)
# if defined(HAVE_ALLOCA_H)
#  include <alloca.h>
# elif defined(__GNUC__)
#  define alloca __builtin_alloca
# elif defined(_MSC_VER)
#  include <malloc.h>
#  define alloca _alloca
# elif defined(__WATCOMC__)
#  include <malloc.h>
# elif defined(__BORLANDC__)
#  include <malloc.h>
# elif defined(__DMC__)
#  include <stdlib.h>
# elif defined(__AIX__)
#pragma alloca
# elif defined(__MRC__)
void *alloca(unsigned);
# else
char *alloca();
# endif
#endif
#ifdef HAVE_ALLOCA
#define SDL_stack_alloc(type, count)    (type*)alloca(sizeof(type)*(count))
#define SDL_stack_free(data)
#else
#define SDL_stack_alloc(type, count)    (type*)SDL_malloc(sizeof(type)*(count))
#define SDL_stack_free(data)            SDL_free(data)
#endif


/* SDL stdinc inline functions:

   The theory here is that by default we forcibly inline what we can, and your
   app will use the inline version by default. However we expose a non-inline
   version too, so the symbol is always available in the library even if your app
   bypassed the inline version. The SDL_*_inline versions aren't guaranteed to
   exist, so never call them directly; use SDL_* instead, and trust the system
   to give you the right thing.

   The benefit here is that you can dlsym() these functions, which you
   couldn't if you had macros, you can link against a foreign build of SDL
   even if you configured differently, and you can drop the unconfigured SDL
   headers into a project without #defining HAVE_MALLOC (etc) and still link.

   If you want to disable the inline functions and just use SDL's functions,
   you can define SDL_STDINC_NO_INLINES before including this file.
*/

extern DECLSPEC void *SDLCALL SDL_malloc(size_t size);
#if defined(HAVE_MALLOC) && !defined(SDL_STDINC_NO_INLINES)
SDL_FORCE_INLINE void *SDL_malloc_inline(size_t size) { return malloc(size); }
#define SDL_malloc SDL_malloc_inline
#endif

extern DECLSPEC void *SDLCALL SDL_calloc(size_t nmemb, size_t size);
#if defined(HAVE_CALLOC) && !defined(SDL_STDINC_NO_INLINES)
SDL_FORCE_INLINE void *SDL_calloc_inline(size_t nmemb, size_t size) { return calloc(nmemb, size); }
#define SDL_calloc SDL_calloc_inline
#endif

extern DECLSPEC void *SDLCALL SDL_realloc(void *mem, size_t size);
#if defined(HAVE_REALLOC) && !defined(SDL_STDINC_NO_INLINES)
SDL_FORCE_INLINE void *SDL_realloc_inline(void *mem, size_t size) { return realloc(mem, size); }
#define SDL_realloc SDL_realloc_inline
#endif

extern DECLSPEC void SDLCALL SDL_free(void *mem);
#if defined(HAVE_FREE) && !defined(SDL_STDINC_NO_INLINES)
SDL_FORCE_INLINE void SDL_free_inline(void *mem) { free(mem); }
#define SDL_free SDL_free_inline
#endif

extern DECLSPEC char *SDLCALL SDL_getenv(const char *name);
#if defined(HAVE_GETENV) && !defined(SDL_STDINC_NO_INLINES)
SDL_FORCE_INLINE char *SDL_getenv_inline(const char *name) { return getenv(name); }
#define SDL_getenv SDL_getenv_inline
#endif

extern DECLSPEC int SDLCALL SDL_setenv(const char *name, const char *value, int overwrite);
#if defined(HAVE_SETENV) && !defined(SDL_STDINC_NO_INLINES)
SDL_FORCE_INLINE int SDL_setenv_inline(const char *name, const char *value, int overwrite) { return setenv(name, value, overwrite); }
#define SDL_setenv SDL_setenv_inline
#endif

extern DECLSPEC void SDLCALL SDL_qsort(void *base, size_t nmemb, size_t size, int (*compare) (const void *, const void *));
#if defined(HAVE_QSORT) && !defined(SDL_STDINC_NO_INLINES)
SDL_FORCE_INLINE void SDL_qsort_inline(void *base, size_t nmemb, size_t size, int (*compare) (const void *, const void *)) { qsort(base, nmemb, size, compare); }
#define SDL_qsort SDL_qsort_inline
#endif

extern DECLSPEC int SDLCALL SDL_abs(int x);
#ifndef SDL_STDINC_NO_INLINES
#ifdef HAVE_ABS
SDL_FORCE_INLINE int SDL_abs_inline(int x) { return abs(x); }
#else
SDL_FORCE_INLINE int SDL_abs_inline(int x) { return ((x) < 0 ? -(x) : (x)); }
#endif
#define SDL_abs SDL_abs_inline
#endif /* !SDL_STDINC_NO_INLINES */

/* !!! FIXME: these have side effects. You probably shouldn't use them. */
/* !!! FIXME: Maybe we do forceinline functions of SDL_mini, SDL_minf, etc? */
#define SDL_min(x, y) (((x) < (y)) ? (x) : (y))
#define SDL_max(x, y) (((x) > (y)) ? (x) : (y))

extern DECLSPEC int SDLCALL SDL_isdigit(int x);
extern DECLSPEC int SDLCALL SDL_isspace(int x);
extern DECLSPEC int SDLCALL SDL_toupper(int x);
extern DECLSPEC int SDLCALL SDL_tolower(int x);
#ifndef SDL_STDINC_NO_INLINES
#ifdef HAVE_CTYPE_H
SDL_FORCE_INLINE int SDL_isdigit_inline(int x) { return isdigit(x); }
SDL_FORCE_INLINE int SDL_isspace_inline(int x) { return isspace(x); }
SDL_FORCE_INLINE int SDL_toupper_inline(int x) { return toupper(x); }
SDL_FORCE_INLINE int SDL_tolower_inline(int x) { return tolower(x); }
#else
SDL_FORCE_INLINE int SDL_isdigit_inline(int x) { return ((x) >= '0') && ((x) <= '9'); }
SDL_FORCE_INLINE int SDL_isspace_inline(int x) { return ((x) == ' ') || ((x) == '\t') || ((x) == '\r') || ((x) == '\n'); }
SDL_FORCE_INLINE int SDL_toupper_inline(int x) { return ((x) >= 'a') && ((x) <= 'z') ? ('A'+((x)-'a')) : (x); }
SDL_FORCE_INLINE int SDL_tolower_inline(int x) { return ((x) >= 'A') && ((x) <= 'Z') ? ('a'+((x)-'A')) : (x); }
#endif
#define SDL_isdigit SDL_isdigit_inline
#define SDL_isspace SDL_isspace_inline
#define SDL_toupper SDL_toupper_inline
#define SDL_tolower SDL_tolower_inline
#endif /* !SDL_STDINC_NO_INLINES */

extern DECLSPEC void *SDLCALL SDL_memset(void *dst, int c, size_t len);
#if defined(HAVE_MEMSET) && !defined(SDL_STDINC_NO_INLINES)
SDL_FORCE_INLINE void *SDL_memset_inline(void *dst, int c, size_t len) { return memset(dst, c, len); }
#define SDL_memset SDL_memset_inline
#endif

#define SDL_zero(x) SDL_memset(&(x), 0, sizeof((x)))
#define SDL_zerop(x) SDL_memset((x), 0, sizeof(*(x)))

/* !!! FIXME: does this _really_ beat memset() on any modern platform? */
SDL_FORCE_INLINE void SDL_memset4(void *dst, int val, size_t len)
{
#if defined(__GNUC__) && defined(i386)
    int u0, u1, u2;
    __asm__ __volatile__ (
        "cld \n\t"
        "rep ; stosl \n\t"
        : "=&D" (u0), "=&a" (u1), "=&c" (u2)
        : "0" (dst), "1" (val), "2" (SDL_static_cast(Uint32, len))
        : "memory"
    );
/* !!! FIXME: amd64? */
#else
    size_t _n = (len + 3) / 4;
    Uint32 *_p = SDL_static_cast(Uint32 *, dst);
    Uint32 _val = (val);
    if (len == 0)
        return;
    switch (len % 4)
    {
        case 0: do {    *_p++ = _val;
        case 3:         *_p++ = _val;
        case 2:         *_p++ = _val;
        case 1:         *_p++ = _val;
        } while ( --_n );
    }
#endif
}


extern DECLSPEC void *SDLCALL SDL_memcpy(void *dst, const void *src, size_t len);
#if !defined(SDL_STDINC_NO_INLINES)
#if defined(__MACOSX__) && defined(HAVE_MEMCPY)
SDL_FORCE_INLINE void *SDL_memcpy_inline(void *dst, const void *src, size_t len)
{
    /* We can count on memcpy existing on Mac OS X and being well-tuned. */
    return memcpy(dst, src, len);
}
#define SDL_memcpy SDL_memcpy_inline
#elif defined(__GNUC__) && defined(i386) && !defined(__WIN32__)
SDL_FORCE_INLINE void *SDL_memcpy_inline(void *dst, const void *src, size_t len)
{
    /* !!! FIXME: does this _really_ beat memcpy() on any modern platform? */
    /* !!! FIXME: shouldn't we just force the inputs to ecx/edi/esi instead of this tapdance with outputs? */
    /* !!! FIXME: amd64? */
    int u0, u1, u2;
    __asm__ __volatile__ (
        "cld \n\t"
        "rep ; movsl \n\t"
        "testb $2,%b4 \n\t"
        "je 1f \n\t"
        "movsw \n"
        "1:\ttestb $1,%b4 \n\t"
        "je 2f \n\t"
        "movsb \n"
        "2:"
        : "=&c" (u0), "=&D" (u1), "=&S" (u2)
        : "0" (SDL_static_cast(unsigned, len)/4), "q" (len), "1" (dst), "2" (src)
        : "memory"
    );
    return dst;
}
#define SDL_memcpy SDL_memcpy_inline
#elif defined(HAVE_MEMCPY)
SDL_FORCE_INLINE void *SDL_memcpy_inline(void *dst, const void *src, size_t len)
{
    return memcpy(dst, src, len);
}
#define SDL_memcpy SDL_memcpy_inline
#elif defined(HAVE_BCOPY)  /* !!! FIXME: is there _really_ ever a time where you have bcopy and not memcpy? */
SDL_FORCE_INLINE void *SDL_memcpy_inline(void *dst, const void *src, size_t len)
{
    bcopy(src, dst, len);
    return dst;
}
#define SDL_memcpy SDL_memcpy_inline
#endif
#endif /* !SDL_STDINC_NO_INLINES */


SDL_FORCE_INLINE void *SDL_memcpy4(void *dst, const void *src, size_t dwords)
{
#if defined(__GNUC__) && defined(i386)
    /* !!! FIXME: does this _really_ beat memcpy() on any modern platform? */
    /* !!! FIXME: shouldn't we just force the inputs to ecx/edi/esi instead of this tapdance with outputs? */
    int ecx, edi, esi;
    __asm__ __volatile__ (
        "cld \n\t"
        "rep ; movsl \n\t"
        : "=&c" (ecx), "=&D" (edi), "=&S" (esi)
        : "0" (SDL_static_cast(unsigned, dwords)), "1" (dst), "2" (src)
        : "memory"
    );
    return dst;
#else
    return SDL_memcpy(dst, src, dwords * 4);
#endif
}

extern DECLSPEC void *SDLCALL SDL_memmove(void *dst, const void *src, size_t len);
#if defined(HAVE_MEMMOVE) && !defined(SDL_STDINC_NO_INLINES)
SDL_FORCE_INLINE void *SDL_memmove_inline(void *dst, const void *src, size_t len) { return memmove(dst, src, len); }
#define SDL_memmove SDL_memmove_inline
#endif

extern DECLSPEC int SDLCALL SDL_memcmp(const void *s1, const void *s2, size_t len);
#if defined(HAVE_MEMCMP) && !defined(SDL_STDINC_NO_INLINES)
SDL_FORCE_INLINE int SDL_memcmp_inline(const void *s1, const void *s2, size_t len) { return memcmp(s1, s2, len); }
#define SDL_memcmp SDL_memcmp_inline
#endif

extern DECLSPEC size_t SDLCALL SDL_strlen(const char *str);
#if defined(HAVE_STRLEN) && !defined(SDL_STDINC_NO_INLINES)
SDL_FORCE_INLINE size_t SDL_strlen_inline(const char *str) { return strlen(str); }
#define SDL_strlen SDL_strlen_inline
#endif

extern DECLSPEC size_t SDLCALL SDL_wcslen(const wchar_t *wstr);
#if defined(HAVE_WCSLEN) && !defined(SDL_STDINC_NO_INLINES)
SDL_FORCE_INLINE size_t SDL_wcslen_inline(const wchar_t *wstr) { return wcslen(wstr); }
#define SDL_wcslen SDL_wcslen_inline
#endif

extern DECLSPEC size_t SDLCALL SDL_wcslcpy(wchar_t *dst, const wchar_t *src, size_t maxlen);
#if defined(HAVE_WCSLCPY) && !defined(SDL_STDINC_NO_INLINES)
SDL_FORCE_INLINE size_t SDL_wcslcpy_inline(wchar_t *dst, const wchar_t *src, size_t maxlen) { return wcslcpy(dst, src, maxlen); }
#define SDL_wcslcpy SDL_wcslcpy_inline
#endif

extern DECLSPEC size_t SDLCALL SDL_wcslcat(wchar_t *dst, const wchar_t *src, size_t maxlen);
#if defined(HAVE_WCSLCAT) && !defined(SDL_STDINC_NO_INLINES)
SDL_FORCE_INLINE size_t SDL_wcslcat_inline(wchar_t *dst, const wchar_t *src, size_t maxlen) { return wcslcat(dst, src, maxlen); }
#define SDL_wcslcat SDL_wcslcat_inline
#endif

extern DECLSPEC size_t SDLCALL SDL_strlcpy(char *dst, const char *src, size_t maxlen);
#if defined(HAVE_STRLCPY) && !defined(SDL_STDINC_NO_INLINES)
SDL_FORCE_INLINE size_t SDL_strlcpy_inline(char *dst, const char *src, size_t maxlen) { return strlcpy(dst, src, maxlen); }
#define SDL_strlcpy SDL_strlcpy_inline
#else
#endif

extern DECLSPEC size_t SDLCALL SDL_utf8strlcpy(char *dst, const char *src, size_t dst_bytes);

extern DECLSPEC size_t SDLCALL SDL_strlcat(char *dst, const char *src, size_t maxlen);
#if defined(HAVE_STRLCAT) && !defined(SDL_STDINC_NO_INLINES)
SDL_FORCE_INLINE size_t SDL_strlcat_inline(char *dst, const char *src, size_t maxlen) { return strlcat(dst, src, maxlen); }
#define SDL_strlcat SDL_strlcat_inline
#endif

extern DECLSPEC char *SDLCALL SDL_strdup(const char *str);
#if defined(HAVE_STRDUP) && !defined(SDL_STDINC_NO_INLINES)
SDL_FORCE_INLINE char *SDL_strdup_inline(const char *str) { return strdup(str); }
#define SDL_strdup SDL_strdup_inline
#endif

extern DECLSPEC char *SDLCALL SDL_strrev(char *str);
#if defined(HAVE__STRREV) && !defined(SDL_STDINC_NO_INLINES)
SDL_FORCE_INLINE char *SDL_strrev_inline(char *str) { return _strrev(str); }
#define SDL_strrev SDL_strrev_inline
#endif

extern DECLSPEC char *SDLCALL SDL_strupr(char *str);
#if defined(HAVE__STRUPR) && !defined(SDL_STDINC_NO_INLINES)
SDL_FORCE_INLINE char *SDL_strupr_inline(char *str) { return _strupr(str); }
#define SDL_strupr SDL_strupr_inline
#endif

extern DECLSPEC char *SDLCALL SDL_strlwr(char *str);
#if defined(HAVE__STRLWR) && !defined(SDL_STDINC_NO_INLINES)
SDL_FORCE_INLINE char *SDL_strlwr_inline(char *str) { return _strlwr(str); }
#define SDL_strlwr SDL_strlwr_inline
#endif

extern DECLSPEC char *SDLCALL SDL_strchr(const char *str, int c);
#ifndef SDL_STDINC_NO_INLINES
#ifdef HAVE_STRCHR
SDL_FORCE_INLINE char *SDL_strchr_inline(const char *str, int c) { return SDL_const_cast(char*,strchr(str, c)); }
#define SDL_strchr SDL_strchr_inline
#elif defined(HAVE_INDEX)  /* !!! FIXME: is there anywhere that has this but not strchr? */
SDL_FORCE_INLINE char *SDL_strchr_inline(const char *str, int c) { return SDL_const_cast(char*,index(str, c)); }
#define SDL_strchr SDL_strchr_inline
#endif
#endif /* !SDL_STDINC_NO_INLINES */

extern DECLSPEC char *SDLCALL SDL_strrchr(const char *str, int c);
#ifndef SDL_STDINC_NO_INLINES
#ifdef HAVE_STRRCHR
SDL_FORCE_INLINE char *SDL_strrchr_inline(const char *str, int c) { return SDL_const_cast(char*,strrchr(str, c)); }
#define SDL_strrchr SDL_strrchr_inline
#elif defined(HAVE_RINDEX)  /* !!! FIXME: is there anywhere that has this but not strrchr? */
SDL_FORCE_INLINE char *SDL_strrchr_inline(const char *str, int c) { return SDL_const_cast(char*,rindex(str, c)); }
#define SDL_strrchr SDL_strrchr_inline
#endif
#endif /* !SDL_STDINC_NO_INLINES */

extern DECLSPEC char *SDLCALL SDL_strstr(const char *haystack, const char *needle);
#if defined(HAVE_STRSTR) && !defined(SDL_STDINC_NO_INLINES)
SDL_FORCE_INLINE char *SDL_strstr_inline(const char *haystack, const char *needle) { return SDL_const_cast(char*,strstr(haystack, needle)); }
#define SDL_strstr SDL_strstr_inline
#endif

extern DECLSPEC char *SDLCALL SDL_ltoa(long value, char *str, int radix);
#if defined(HAVE__LTOA) && !defined(SDL_STDINC_NO_INLINES)
SDL_FORCE_INLINE char *SDL_ltoa_inline(long value, char *str, int radix) { return _ltoa(value, str, radix); }
#define SDL_ltoa SDL_ltoa_inline
#endif

extern DECLSPEC char *SDLCALL SDL_itoa(int value, char *str, int radix);
#ifndef SDL_STDINC_NO_INLINES
#ifdef HAVE_ITOA
// Urho3D: fix deprecation warning
SDL_FORCE_INLINE char *SDL_itoa_inline(int value, char *str, int radix) { return _itoa(value, str, radix); }
#else
SDL_FORCE_INLINE char *SDL_itoa_inline(int value, char *str, int radix) { return SDL_ltoa((long)value, str, radix); }
#endif
#define SDL_itoa SDL_itoa_inline
#endif /* !SDL_STDINC_NO_INLINES */

extern DECLSPEC char *SDLCALL SDL_ultoa(unsigned long value, char *str, int radix);
#if defined(HAVE__ULTOA) && !defined(SDL_STDINC_NO_INLINES)
SDL_FORCE_INLINE char *SDL_ultoa_inline(unsigned long value, char *str, int radix) { return _ultoa(value, str, radix); }
#define SDL_ultoa SDL_ultoa_inline
#endif

extern DECLSPEC char *SDLCALL SDL_uitoa(unsigned int value, char *str, int radix);
#ifndef SDL_STDINC_NO_INLINES
#ifdef HAVE__UITOA
SDL_FORCE_INLINE char *SDL_uitoa_inline(unsigned int value, char *str, int radix) { return _uitoa(value, str, radix); }
#else
SDL_FORCE_INLINE char *SDL_uitoa_inline(unsigned int value, char *str, int radix) { return SDL_ultoa((unsigned long)value, str, radix); }
#endif
#define SDL_uitoa SDL_uitoa_inline
#endif /* !SDL_STDINC_NO_INLINES */


extern DECLSPEC long SDLCALL SDL_strtol(const char *str, char **endp, int base);
#if defined(HAVE_STRTOL) && !defined(SDL_STDINC_NO_INLINES)
SDL_FORCE_INLINE long SDL_strtol_inline(const char *str, char **endp, int base) { return strtol(str, endp, base); }
#define SDL_strtol SDL_strtol_inline
#endif

extern DECLSPEC unsigned long SDLCALL SDL_strtoul(const char *str, char **endp, int base);
#if defined(HAVE_STRTOUL) && !defined(SDL_STDINC_NO_INLINES)
SDL_FORCE_INLINE unsigned long SDLCALL SDL_strtoul_inline(const char *str, char **endp, int base) { return strtoul(str, endp, base); }
#define SDL_strtoul SDL_strtoul_inline
#endif

extern DECLSPEC char *SDLCALL SDL_lltoa(Sint64 value, char *str, int radix);
#if defined(HAVE__I64TOA) && !defined(SDL_STDINC_NO_INLINES)
SDL_FORCE_INLINE char *SDL_lltoa_inline(Sint64 value, char *str, int radix) { return _i64toa(value, str, radix); }
#define SDL_lltoa SDL_lltoa_inline
#endif

extern DECLSPEC char *SDLCALL SDL_ulltoa(Uint64 value, char *str, int radix);
#if defined(HAVE__UI64TOA) && !defined(SDL_STDINC_NO_INLINES)
SDL_FORCE_INLINE char *SDL_ulltoa_inline(Uint64 value, char *str, int radix) { return _ui64toa(value, str, radix); }
#define SDL_ulltoa SDL_ulltoa_inline
#endif

// Urho3D: disabled
/*
extern DECLSPEC Sint64 SDLCALL SDL_strtoll(const char *str, char **endp, int base);
#if defined(HAVE_STRTOLL) && !defined(SDL_STDINC_NO_INLINES)
SDL_FORCE_INLINE Sint64 SDL_strtoll_inline(const char *str, char **endp, int base) { return strtoll(str, endp, base); }
#define SDL_strtoll SDL_strtoll_inline
#endif
*/

extern DECLSPEC Uint64 SDLCALL SDL_strtoull(const char *str, char **endp, int base);
#if defined(HAVE_STRTOULL) && !defined(SDL_STDINC_NO_INLINES)
SDL_FORCE_INLINE Uint64 SDL_strtoull_inline(const char *str, char **endp, int base) { return strtoull(str, endp, base); }
#define SDL_strtoull SDL_strtoull_inline
#endif

extern DECLSPEC double SDLCALL SDL_strtod(const char *str, char **endp);
#if defined(HAVE_STRTOD) && !defined(SDL_STDINC_NO_INLINES)
SDL_FORCE_INLINE double SDL_strtod_inline(const char *str, char **endp) { return strtod(str, endp); }
#define SDL_strtod SDL_strtod_inline
#endif

extern DECLSPEC int SDLCALL SDL_atoi(const char *str);
#ifndef SDL_STDINC_NO_INLINES
#ifdef HAVE_ATOI
SDL_FORCE_INLINE int SDL_atoi_inline(const char *str) { return atoi(str); }
#else
SDL_FORCE_INLINE int SDL_atoi_inline(const char *str) { return SDL_strtol(str, NULL, 0); }
#endif
#define SDL_atoi SDL_atoi_inline
#endif /* !SDL_STDINC_NO_INLINES */

extern DECLSPEC double SDLCALL SDL_atof(const char *str);
#ifndef SDL_STDINC_NO_INLINES
#ifdef HAVE_ATOF
SDL_FORCE_INLINE double SDL_atof_inline(const char *str) { return (double) atof(str); }
#else
SDL_FORCE_INLINE double SDL_atof_inline(const char *str) { return SDL_strtod(str, NULL); }
#endif
#define SDL_atof SDL_atof_inline
#endif /* !SDL_STDINC_NO_INLINES */


extern DECLSPEC int SDLCALL SDL_strcmp(const char *str1, const char *str2);
#if defined(HAVE_STRCMP) && !defined(SDL_STDINC_NO_INLINES)
SDL_FORCE_INLINE int SDL_strcmp_inline(const char *str1, const char *str2) { return strcmp(str1, str2); }
#define SDL_strcmp SDL_strcmp_inline
#endif

extern DECLSPEC int SDLCALL SDL_strncmp(const char *str1, const char *str2, size_t maxlen);
#if defined(HAVE_STRNCMP) && !defined(SDL_STDINC_NO_INLINES)
SDL_FORCE_INLINE int SDL_strncmp_inline(const char *str1, const char *str2, size_t maxlen) { return strncmp(str1, str2, maxlen); }
#define SDL_strncmp SDL_strncmp_inline
#endif

extern DECLSPEC int SDLCALL SDL_strcasecmp(const char *str1, const char *str2);
#ifndef SDL_STDINC_NO_INLINES
#ifdef HAVE_STRCASECMP
SDL_FORCE_INLINE int SDL_strcasecmp_inline(const char *str1, const char *str2) { return strcasecmp(str1, str2); }
#define SDL_strcasecmp SDL_strcasecmp_inline
#elif defined(HAVE__STRICMP)
SDL_FORCE_INLINE int SDL_strcasecmp_inline(const char *str1, const char *str2) { return _stricmp(str1, str2); }
#define SDL_strcasecmp SDL_strcasecmp_inline
#endif
#endif /* !SDL_STDINC_NO_INLINES */

extern DECLSPEC int SDLCALL SDL_strncasecmp(const char *str1, const char *str2, size_t len);
#ifndef SDL_STDINC_NO_INLINES
#ifdef HAVE_STRNCASECMP
SDL_FORCE_INLINE int SDL_strncasecmp_inline(const char *str1, const char *str2, size_t len) { return strncasecmp(str1, str2, len); }
#define SDL_strncasecmp SDL_strncasecmp_inline
#elif defined(HAVE__STRNICMP)
SDL_FORCE_INLINE int SDL_strncasecmp_inline(const char *str1, const char *str2, size_t len) { return _strnicmp(str1, str2, len); }
#define SDL_strncasecmp SDL_strncasecmp_inline
#endif
#endif /* !SDL_STDINC_NO_INLINES */

/* Not doing SDL_*_inline functions for these, because of the varargs. */
extern DECLSPEC int SDLCALL SDL_sscanf(const char *text, const char *fmt, ...);
#ifdef HAVE_SSCANF
#define SDL_sscanf sscanf
#endif

extern DECLSPEC int SDLCALL SDL_snprintf(char *text, size_t maxlen, const char *fmt, ...);
#ifdef HAVE_SNPRINTF
#define SDL_snprintf snprintf
#endif

extern DECLSPEC int SDLCALL SDL_vsnprintf(char *text, size_t maxlen, const char *fmt, va_list ap);
#if defined(HAVE_VSNPRINTF) && !defined(SDL_STDINC_NO_INLINES)
SDL_FORCE_INLINE int SDL_vsnprintf_inline(char *text, size_t maxlen, const char *fmt, va_list ap) { return vsnprintf(text, maxlen, fmt, ap); }
#define SDL_vsnprintf SDL_vsnprintf_inline
#endif

#ifndef HAVE_M_PI
#ifndef M_PI
#define M_PI    3.14159265358979323846264338327950288   /* pi */
#endif
#endif

extern DECLSPEC double SDLCALL SDL_atan(double x);
#if defined(HAVE_ATAN) && !defined(SDL_STDINC_NO_INLINES)
SDL_FORCE_INLINE double SDL_atan_inline(double x) { return atan(x); }
#define SDL_atan SDL_atan_inline
#endif

extern DECLSPEC double SDLCALL SDL_atan2(double x, double y);
#if defined(HAVE_ATAN2) && !defined(SDL_STDINC_NO_INLINES)
SDL_FORCE_INLINE double SDL_atan2_inline(double x, double y) { return atan2(x, y); }
#define SDL_atan2 SDL_atan2_inline
#endif

extern DECLSPEC double SDLCALL SDL_ceil(double x);
#ifndef SDL_STDINC_NO_INLINES
#ifdef HAVE_CEIL
SDL_FORCE_INLINE double SDL_ceil_inline(double x) { return ceil(x); }
#else
SDL_FORCE_INLINE double SDL_ceil_inline(double x) { return (double)(int)((x)+0.5); }
#endif
#define SDL_ceil SDL_ceil_inline
#endif /* !SDL_STDINC_NO_INLINES */

// Urho3D: disabled
/*
extern DECLSPEC double SDLCALL SDL_copysign(double x, double y);
#if defined(HAVE_COPYSIGN) && !defined(SDL_STDINC_NO_INLINES)
SDL_FORCE_INLINE double SDL_copysign_inline(double x, double y) { return copysign(x, y); }
#define SDL_copysign SDL_copysign_inline
#endif
*/

extern DECLSPEC double SDLCALL SDL_cos(double x);
#if defined(HAVE_COS) && !defined(SDL_STDINC_NO_INLINES)
SDL_FORCE_INLINE double SDL_cos_inline(double x) { return cos(x); }
#define SDL_cos SDL_cos_inline
#endif

extern DECLSPEC float SDLCALL SDL_cosf(float x);
#ifndef SDL_STDINC_NO_INLINES
#ifdef HAVE_COSF
SDL_FORCE_INLINE float SDL_cosf_inline(float x) { return cosf(x); }
#else
SDL_FORCE_INLINE float SDL_cosf_inline(float x) { return (float)SDL_cos((double)x); }
#endif
#define SDL_cosf SDL_cosf_inline
#endif /* !SDL_STDINC_NO_INLINES */

extern DECLSPEC double SDLCALL SDL_fabs(double x);
#if defined(HAVE_FABS) && !defined(SDL_STDINC_NO_INLINES)
SDL_FORCE_INLINE double SDL_fabs_inline(double x) { return fabs(x); }
#define SDL_fabs SDL_fabs_inline
#endif

extern DECLSPEC double SDLCALL SDL_floor(double x);
#if defined(HAVE_FLOOR) && !defined(SDL_STDINC_NO_INLINES)
SDL_FORCE_INLINE double SDL_floor_inline(double x) { return floor(x); }
#define SDL_floor SDL_floor_inline
#endif

extern DECLSPEC double SDLCALL SDL_log(double x);
#if defined(HAVE_LOG) && !defined(SDL_STDINC_NO_INLINES)
SDL_FORCE_INLINE double SDL_log_inline(double x) { return log(x); }
#define SDL_log SDL_log_inline
#endif

extern DECLSPEC double SDLCALL SDL_pow(double x, double y);
#if defined(HAVE_POW) && !defined(SDL_STDINC_NO_INLINES)
SDL_FORCE_INLINE double SDL_pow_inline(double x, double y) { return pow(x, y); }
#define SDL_pow SDL_pow_inline
#endif

// Urho3D: disabled
/*
extern DECLSPEC double SDLCALL SDL_scalbn(double x, int n);
#if defined(HAVE_SCALBN) && !defined(SDL_STDINC_NO_INLINES)
SDL_FORCE_INLINE double SDL_scalbn_inline(double x, int n) { return scalbn(x, n); }
#define SDL_scalbn SDL_scalbn_inline
#endif
*/

extern DECLSPEC double SDLCALL SDL_sin(double x);
#if defined(HAVE_SIN) && !defined(SDL_STDINC_NO_INLINES)
SDL_FORCE_INLINE double SDL_sin_inline(double x) { return sin(x); }
#define SDL_sin SDL_sin_inline
#endif

extern DECLSPEC float SDLCALL SDL_sinf(float x);
#ifndef SDL_STDINC_NO_INLINES
#ifdef HAVE_SINF
SDL_FORCE_INLINE float SDL_sinf_inline(float x) { return sinf(x); }
#else
SDL_FORCE_INLINE float SDL_sinf_inline(float x) { return (float)SDL_sin((double)x); }
#endif
#define SDL_sinf SDL_sinf_inline
#endif /* !SDL_STDINC_NO_INLINES */

extern DECLSPEC double SDLCALL SDL_sqrt(double x);
#if defined(HAVE_SQRT) && !defined(SDL_STDINC_NO_INLINES)
SDL_FORCE_INLINE double SDL_sqrt_inline(double x) { return sqrt(x); }
#define SDL_sqrt SDL_sqrt_inline
#endif

/* The SDL implementation of iconv() returns these error codes */
#define SDL_ICONV_ERROR     (size_t)-1
#define SDL_ICONV_E2BIG     (size_t)-2
#define SDL_ICONV_EILSEQ    (size_t)-3
#define SDL_ICONV_EINVAL    (size_t)-4

/* SDL_iconv_* are now always real symbols/types, not macros or inlined. */
typedef struct _SDL_iconv_t *SDL_iconv_t;
extern DECLSPEC SDL_iconv_t SDLCALL SDL_iconv_open(const char *tocode,
                                                   const char *fromcode);
extern DECLSPEC int SDLCALL SDL_iconv_close(SDL_iconv_t cd);
extern DECLSPEC size_t SDLCALL SDL_iconv(SDL_iconv_t cd, const char **inbuf,
                                         size_t * inbytesleft, char **outbuf,
                                         size_t * outbytesleft);
/**
 *  This function converts a string between encodings in one pass, returning a
 *  string that must be freed with SDL_free() or NULL on error.
 */
extern DECLSPEC char *SDLCALL SDL_iconv_string(const char *tocode,
                                               const char *fromcode,
                                               const char *inbuf,
                                               size_t inbytesleft);
#define SDL_iconv_utf8_locale(S)    SDL_iconv_string("", "UTF-8", S, SDL_strlen(S)+1)
#define SDL_iconv_utf8_ucs2(S)      (Uint16 *)SDL_iconv_string("UCS-2-INTERNAL", "UTF-8", S, SDL_strlen(S)+1)
#define SDL_iconv_utf8_ucs4(S)      (Uint32 *)SDL_iconv_string("UCS-4-INTERNAL", "UTF-8", S, SDL_strlen(S)+1)

/* Ends C function definitions when using C++ */
#ifdef __cplusplus
}
#endif
#include "close_code.h"

#endif /* _SDL_stdinc_h */

/* vi: set ts=4 sw=4 expandtab: */
